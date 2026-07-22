/**
 *******************************************************************************
 * @file        hal_timer2.c
 * @author      ABOV R&D Division
 * @brief       2N typed Timer
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#include "abov_config.h"

#if defined(_TIMER2)
#include "hal_timer2.h"
#include "hal_timer2_prv.h"

typedef struct
{
     TIMER2_OPS_e                eOps;
     pfnTIMER2_IRQ_Handler_t    pfnHandler;
     void                       *pContext;

     TIMER2_MODE_e              eMode;
     uint8_t                    un8PwmEvt;
} TIMER2_CTRL_BLK_t;

static TIMER2_CTRL_BLK_t s_tTcb[TIMER2_CH_NUM];

static TIMER2_Type *PRV_TIMER2_GetReg(TIMER2_ID_e eId)
{
    return TIMER2_GetReg((uint32_t)eId);
}

static HAL_ERR_e PRV_TIMER2_SetScuEnable(P_TIMER2_ID_e eId, bool bEnable)
{
    return TIMER2_SetScuEnable(eId, bEnable);
}

HAL_ERR_e HAL_TIMER2_Init(TIMER2_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER2_Type *ptTimer;

    if((uint32_t)eId >= TIMER2_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_TIMER2_SetScuEnable((P_TIMER2_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tTcb[(uint32_t)eId], 0x00, sizeof(TIMER2_CTRL_BLK_t));

    ptTimer = PRV_TIMER2_GetReg(eId);
    /* clear control register */
    SET_TIMER2_CR(ptTimer, 0x00);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER2_Uninit(TIMER2_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= TIMER2_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_TIMER2_SetScuEnable((P_TIMER2_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = TIMER2_GetIRQNum((P_TIMER2_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tTcb[(uint32_t)eId], 0x00, sizeof(TIMER2_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER2_SetClkConfig(TIMER2_ID_e eId, TIMER2_CLK_CFG_t *ptClkCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER2_Type *ptTimer;

    if((uint32_t)eId >= TIMER2_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(ptClkCfg->un16PreScale >= TIMER2_PRESCALE_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    ptTimer = PRV_TIMER2_GetReg(eId);

    switch(ptClkCfg->eClk)
    {
        case TIMER2_CLK_MCCR:
             eErr = TIMER2_SetMccrClk((P_TIMER2_ID_e)eId, ptTimer, 
                                     (P_TIMER2_CLK_MCCR_e)ptClkCfg->uSubClk.eMccr,
                                     ptClkCfg->un8MccrDiv);
            break;
        case TIMER2_CLK_EXT:
            eErr = TIMER2_SetExtClk((P_TIMER2_ID_e)eId, ptTimer,
                                   (P_TIMER2_EXTCLK_EDGE_e)ptClkCfg->uSubClk.eExtClkEdge);
            break;
        case TIMER2_CLK_PCLK:
            eErr = TIMER2_SetPClk((P_TIMER2_ID_e)eId, ptTimer,
                                 (P_TIMER2_PCLK_DIV_e)P_TIMER2_PCLK_DIV_MAX);
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    /* Prescale */
    SET_TIMER2_PREDR(ptTimer, ptClkCfg->un16PreScale);

    return eErr;
}

HAL_ERR_e HAL_TIMER2_SetConfig(TIMER2_ID_e eId, TIMER2_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER2_Type *ptTimer;
    TIMER2_CTRL_BLK_t *ptTcb;
    TIMER2_MODE_e eMode;
    TIMER2_POL_e ePol;

    if((uint32_t)eId >= TIMER2_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(ptCfg->eMode >= TIMER2_MODE_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    ptTimer = PRV_TIMER2_GetReg(eId);
    ptTcb = &s_tTcb[eId];

    /* mode */
    eMode = (TIMER2_MODE_e)TIMER2_ConvMode((P_TIMER2_MODE_e)ptCfg->eMode);
    SET_TIMER2_CR_MODE(ptTimer, (uint32_t)eMode);

    /* polarity */
    ePol = (TIMER2_POL_e)TIMER2_ConvPol((P_TIMER2_POL_e)ptCfg->ePol);
    SET_TIMER2_CR_OUTPORT_POL(ptTimer, ePol);

    if(ptCfg->bIntrEnable)
    {
        /* enable interrupt */
        SET_TIMER2_IER_CLR(ptTimer);
        switch(ptCfg->eMode)
        {
            case TIMER2_MODE_PERIODIC:
            case TIMER2_MODE_ONESHOT:
            case TIMER2_MODE_PWM:
                SET_TIMER2_IER_MATCH_EN(ptTimer, true);
                break;
            case TIMER2_MODE_CAPTURE:
                SET_TIMER2_IER_CAP_EN(ptTimer, true);
                break;
            default:
                eErr = HAL_ERR_PARAMETER;
                break;
        }
    }

    if(eErr == HAL_ERR_OK)
    {
        ptTcb->eMode = ptCfg->eMode;

        if(ptCfg->eMode == TIMER2_MODE_PWM)
        {
            /* Set DUTY */
            SET_TIMER2_DR_DUTY(ptTimer, ptCfg->utData.tPWM.un32Duty);
            /* Set PERIOD */
            SET_TIMER2_DR_PERIOD(ptTimer, ptCfg->utData.tPWM.un32Period);
            ptTcb->un8PwmEvt = TIMER2_EVENT_PWM_DUTY | TIMER2_EVENT_PWM_PERIOD;
        }
        else
        {
            /* Set Data A (GRA) */
            SET_TIMER2_DR_A(ptTimer, ptCfg->utData.tGRD.un32DataA);
            /* Set Data B (GRB) */
            SET_TIMER2_DR_B(ptTimer, ptCfg->utData.tGRD.un32DataB);
            if(ptCfg->eMode == TIMER2_MODE_CAPTURE)
            {
                SET_TIMER2_CR_CAPPORT_POL(ptTimer, (uint8_t)ptCfg->tCapCfg.eEdge);
                SET_TIMER2_CR_CAP_SIG(ptTimer, (uint8_t)ptCfg->tCapCfg.eSig);
                SET_TIMER2_CR_CAP_KEEPCNT(ptTimer, ptCfg->tCapCfg.bKeepCount);
            }
        }

        /* Clear Count Register */
        SET_TIMER2_CR_CLR(ptTimer, true);
    }

    return eErr;
}

HAL_ERR_e HAL_TIMER2_SetIRQ(TIMER2_ID_e eId, TIMER2_OPS_e eOps, pfnTIMER2_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER2_CTRL_BLK_t *ptTcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= TIMER2_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTcb = &s_tTcb[(uint32_t)eId];
    eIrq = TIMER2_GetIRQNum((P_TIMER2_ID_e)eId);

    switch(eOps)
    {
        case TIMER2_OPS_INTR:
#if defined(TIMER2_FEATURE_IRQ_UNMASK_ENABLE)
            TIMER2_SetIntrUnMask(eIrq, true);
#endif
            ptTcb->pfnHandler = pfnHandler;
            ptTcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            break;
        case TIMER2_OPS_POLL:
        default:
#if defined(TIMER2_FEATURE_IRQ_UNMASK_ENABLE)
            TIMER2_SetIntrUnMask(eIrq, false);
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptTcb->pContext = NULL;
            ptTcb->pfnHandler = NULL;
            break;
    }

    ptTcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_TIMER2_GetStatus(TIMER2_ID_e eId, uint32_t *pun32Status)
{
    TIMER2_Type *ptTimer;

    if((uint32_t)eId >= TIMER2_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER2_GetReg(eId);
    *pun32Status = TIMER2_GetIntFlag(ptTimer);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER2_SetPolarity(TIMER2_ID_e eId, TIMER2_POL_e ePol)
{
    TIMER2_Type *ptTimer;

    if((uint32_t)eId >= TIMER2_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ePol = (TIMER2_POL_e)TIMER2_ConvPol((P_TIMER2_POL_e)ePol);
    ptTimer = PRV_TIMER2_GetReg(eId);
    SET_TIMER2_CR_OUTPORT_POL(ptTimer, ePol);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER2_SetData(TIMER2_ID_e eId, TIMER2_DATA_e eSel, uint32_t un32Data)
{
    TIMER2_Type *ptTimer;

    if((uint32_t)eId >= TIMER2_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER2_GetReg(eId);

    switch(eSel)
    {
        case TIMER2_DATA_A:
             SET_TIMER2_DR_A(ptTimer, un32Data);
             break;
        case TIMER2_DATA_B:
             SET_TIMER2_DR_B(ptTimer, un32Data);
             break;
        default:
             break;
    }

    return HAL_ERR_OK;

}

HAL_ERR_e HAL_TIMER2_GetData(TIMER2_ID_e eId, TIMER2_DATA_e eSel, uint32_t *pun32Data)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER2_Type *ptTimer;

    if((uint32_t)eId >= TIMER2_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER2_GetReg(eId);

    switch(eSel)
    {
        case TIMER2_DATA_A:
             *pun32Data = GET_TIMER2_DR_A(ptTimer);
             break;
        case TIMER2_DATA_B:
             *pun32Data = GET_TIMER2_DR_B(ptTimer);
             break;
        case TIMER2_DATA_CAP_A:
             *pun32Data = GET_TIMER2_DR_CAPA(ptTimer);
             break;
        case TIMER2_DATA_CAP_B:
             *pun32Data = GET_TIMER2_DR_CAPB(ptTimer);
             break;
        default:
            *pun32Data = 0;
             eErr = HAL_ERR_PARAMETER;
             break;
    }

    return eErr;
}

HAL_ERR_e HAL_TIMER2_Start(TIMER2_ID_e eId)
{
    TIMER2_Type *ptTimer;

    if((uint32_t)eId >= TIMER2_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER2_GetReg(eId);
    SET_TIMER2_CR_EN(ptTimer, true);
    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER2_Stop(TIMER2_ID_e eId)
{
    TIMER2_Type *ptTimer;

    if((uint32_t)eId >= TIMER2_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER2_GetReg(eId);
    SET_TIMER2_CR_EN(ptTimer, false);
    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER2_SetPause(TIMER2_ID_e eId, bool bPause)
{
    TIMER2_Type *ptTimer;

    if((uint32_t)eId >= TIMER2_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }
    ptTimer = PRV_TIMER2_GetReg(eId);
    SET_TIMER2_CR_PAUSE(ptTimer, bPause);
    return HAL_ERR_OK;
}

static void PRV_TIMER2_IRQHandler(TIMER2_ID_e eId)
{
    TIMER2_Type *ptTimer;
    TIMER2_CTRL_BLK_t *ptTcb;
    uint32_t un32Event=0;
    uint8_t un8Status=0;

    ptTimer = PRV_TIMER2_GetReg(eId);
    ptTcb = &s_tTcb[eId];

    un8Status = TIMER2_GetIntFlag(ptTimer);
    if(un8Status & P_TIMER2_INTR_FLAG_MATCH || un8Status & P_TIMER2_INTR_FLAG_CAP)
    {
        switch(ptTcb->eMode)
        {
            case TIMER2_MODE_PERIODIC:
            case TIMER2_MODE_ONESHOT:
                un32Event |= TIMER2_EVENT_PERIODIC_MATCH;
                break;
            case TIMER2_MODE_PWM:
                if(ptTcb->un8PwmEvt & TIMER2_EVENT_PWM_DUTY)
                {
                    if(TIMER2_ONLY_PWM_PERIOD)
                    {
                        un32Event |= TIMER2_EVENT_PWM_PERIOD;
                    }
                    else
                    {
                        un32Event |= TIMER2_EVENT_PWM_DUTY;
                    }
                }
                break;
            case TIMER2_MODE_CAPTURE:
                un32Event |= TIMER2_EVENT_CAPTURE_A;
                break;
            default:
                break;
        }
    }

    if(un8Status & P_TIMER2_INTR_FLAG_B)
    {
        switch(ptTcb->eMode)
        {
            case TIMER2_MODE_PERIODIC:
            case TIMER2_MODE_ONESHOT:
                un32Event |= TIMER2_EVENT_PERIODIC_MATCH;
                break;
            case TIMER2_MODE_PWM:
                if(ptTcb->un8PwmEvt & TIMER2_EVENT_PWM_DUTY)
                {
                    un32Event |= TIMER2_EVENT_PWM_PERIOD;
                }
                break;
            case TIMER2_MODE_CAPTURE:
                un32Event |= TIMER2_EVENT_CAPTURE_B;
                break;
            default:
                break;
        }

    }

    if(un32Event != 0)
    {
        /* clear status */ 
        SET_TIMER2_IER_MATCH_FLAG(ptTimer, true);
        SET_TIMER2_IER_CAP_FLAG(ptTimer, true);
    }

    if(ptTcb->pfnHandler != NULL && un32Event)
    {
        ptTcb->pfnHandler(un32Event, ptTcb->pContext);
    }
}

void TIMER20_IRQHandler(void)
{
    PRV_TIMER2_IRQHandler(TIMER2_ID_0);
}

void TIMER21_IRQHandler(void)
{
    PRV_TIMER2_IRQHandler(TIMER2_ID_1);
}

void TIMER22_IRQHandler(void)
{
    PRV_TIMER2_IRQHandler(TIMER2_ID_2);
}

void TIMER23_IRQHandler(void)
{
    PRV_TIMER2_IRQHandler(TIMER2_ID_3);
}

void TIMER24_IRQHandler(void)
{
    PRV_TIMER2_IRQHandler(TIMER2_ID_4);
}

void TIMER25_IRQHandler(void)
{
    PRV_TIMER2_IRQHandler(TIMER2_ID_5);
}

void TIMER26_IRQHandler(void)
{
    PRV_TIMER2_IRQHandler(TIMER2_ID_6);
}

void TIMER27_IRQHandler(void)
{
    PRV_TIMER2_IRQHandler(TIMER2_ID_7);
}

void TIMER28_IRQHandler(void)
{
    PRV_TIMER2_IRQHandler(TIMER2_ID_8);
}

void TIMER29_IRQHandler(void)
{
    PRV_TIMER2_IRQHandler(TIMER2_ID_9);
}

#endif /* _TIMER2 */
