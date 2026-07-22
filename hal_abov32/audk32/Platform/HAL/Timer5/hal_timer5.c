/**
 *******************************************************************************
 * @file        hal_timer5.c
 * @author      ABOV R&D Division
 * @brief       5n typed Timer
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#include "abov_config.h"

#if defined(_TIMER5)
#include "hal_timer5.h"
#include "hal_timer5_prv.h"

typedef struct
{
     TIMER5_OPS_e                eOps;
     pfnTIMER5_IRQ_Handler_t    pfnHandler;
     void                       *pContext;

     TIMER5_MODE_e              eMode;
     uint8_t                    un8PwmEvt;
} TIMER5_CTRL_BLK_t;

static TIMER5_CTRL_BLK_t s_tTcb[TIMER5_CH_NUM];

static TIMER5_Type *PRV_TIMER5_GetReg(TIMER5_ID_e eId)
{
    return TIMER5_GetReg((uint32_t)eId);
}

static HAL_ERR_e PRV_TIMER5_SetScuEnable(P_TIMER5_ID_e eId, bool bEnable)
{
    return TIMER5_SetScuEnable(eId, bEnable);
}

HAL_ERR_e HAL_TIMER5_Init(TIMER5_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER5_Type *ptTimer;

    if((uint32_t)eId >= TIMER5_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_TIMER5_SetScuEnable((P_TIMER5_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tTcb[(uint32_t)eId], 0x00, sizeof(TIMER5_CTRL_BLK_t));

    ptTimer = PRV_TIMER5_GetReg(eId);
    /* clear control register */
    SET_TIMER5_CR(ptTimer, 0x00);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER5_Uninit(TIMER5_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= TIMER5_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_TIMER5_SetScuEnable((P_TIMER5_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = TIMER5_GetIRQNum((P_TIMER5_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tTcb[(uint32_t)eId], 0x00, sizeof(TIMER5_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER5_SetClkConfig(TIMER5_ID_e eId, TIMER5_CLK_CFG_t *ptClkCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER5_Type *ptTimer;

    if((uint32_t)eId >= TIMER5_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(ptClkCfg->un16PreScale >= TIMER5_PRESCALE_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    ptTimer = PRV_TIMER5_GetReg(eId);

    switch(ptClkCfg->eClk)
    {
        case TIMER5_CLK_MCCR:
             eErr = TIMER5_SetMccrClk((P_TIMER5_ID_e)eId, ptTimer, 
                                     (P_TIMER5_CLK_MCCR_e)ptClkCfg->uSubClk.eMccr,
                                     0);
            break;
        case TIMER5_CLK_EXT:
            eErr = TIMER5_SetExtClk((P_TIMER5_ID_e)eId, ptTimer,
                                   (P_TIMER5_EXTCLK_EDGE_e)ptClkCfg->uSubClk.eExtClkEdge);
            break;
        case TIMER5_CLK_PCLK:
            eErr = TIMER5_SetPClk((P_TIMER5_ID_e)eId, ptTimer,
                                 (P_TIMER5_PCLK_DIV_e)P_TIMER5_PCLK_DIV_MAX);
            break;
        case TIMER5_CLK_WDTRC:
            eErr = TIMER5_SetWDTRC((P_TIMER5_ID_e)eId, ptTimer);
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    /* Prescale */
    SET_TIMER5_PREDR(ptTimer, ptClkCfg->un16PreScale);

    return eErr;
}

HAL_ERR_e HAL_TIMER5_SetConfig(TIMER5_ID_e eId, TIMER5_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER5_Type *ptTimer;
    TIMER5_CTRL_BLK_t *ptTcb;
    TIMER5_MODE_e eMode;
    TIMER5_POL_e ePol;

    if((uint32_t)eId >= TIMER5_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(ptCfg->eMode >= TIMER5_MODE_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    ptTimer = PRV_TIMER5_GetReg(eId);
    ptTcb = &s_tTcb[eId];

    /* mode */
    eMode = (TIMER5_MODE_e)TIMER5_ConvMode((P_TIMER5_MODE_e)ptCfg->eMode);
    SET_TIMER5_CR_MODE(ptTimer, (uint32_t)eMode);

    /* polarity */
    ePol = (TIMER5_POL_e)TIMER5_ConvPol((P_TIMER5_POL_e)ptCfg->ePol);
    SET_TIMER5_CR_OUTPORT_POL(ptTimer, ePol);

    if(ptCfg->bIntrEnable)
    {
        /* enable interrupt */
        SET_TIMER5_IER_CLR(ptTimer);
        switch(ptCfg->eMode)
        {
            case TIMER5_MODE_PERIODIC:
            case TIMER5_MODE_ONESHOT:
            case TIMER5_MODE_PWM:
                SET_TIMER5_IER_MATCH_EN(ptTimer, true);
                break;
            case TIMER5_MODE_CAPTURE:
                SET_TIMER5_IER_CAP_EN(ptTimer, true);
                break;
            default:
                eErr = HAL_ERR_PARAMETER;
                break;
        }
    }

    if(eErr == HAL_ERR_OK)
    {
        ptTcb->eMode = ptCfg->eMode;

        if(ptCfg->eMode == TIMER5_MODE_PWM)
        {
            /* Set DUTY */
            SET_TIMER5_DR_DUTY(ptTimer, ptCfg->utData.tPWM.un16Duty);
            /* Set PERIOD */
            SET_TIMER5_DR_PERIOD(ptTimer, ptCfg->utData.tPWM.un16Period);
            ptTcb->un8PwmEvt = TIMER5_EVENT_PWM_DUTY | TIMER5_EVENT_PWM_PERIOD;
        }
        else
        {
            /* Set Data A (GRA) */
            SET_TIMER5_DR_A(ptTimer, ptCfg->utData.tGRD.un16DataA);
            /* Set Data B (GRB) */
            SET_TIMER5_DR_B(ptTimer, ptCfg->utData.tGRD.un16DataB);
            if(ptCfg->eMode == TIMER5_MODE_CAPTURE)
            {
                SET_TIMER5_CR_CAPPORT_POL(ptTimer, (uint8_t)ptCfg->tCapCfg.eEdge);
                SET_TIMER5_CR_CAP_SIG(ptTimer, (uint8_t)ptCfg->tCapCfg.eSig);
                SET_TIMER5_CR_CAP_KEEPCNT(ptTimer, (~(ptCfg->tCapCfg.bKeepCount) & 0x00000001));
            }
        }

        /* Clear Count Register */
        SET_TIMER5_CR_CLR(ptTimer, true);
    }

    return eErr;
}

HAL_ERR_e HAL_TIMER5_SetIRQ(TIMER5_ID_e eId, TIMER5_OPS_e eOps, pfnTIMER5_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER5_CTRL_BLK_t *ptTcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= TIMER5_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTcb = &s_tTcb[(uint32_t)eId];
    eIrq = TIMER5_GetIRQNum((P_TIMER5_ID_e)eId);

    switch(eOps)
    {
        case TIMER5_OPS_INTR:
#if defined(TIMER5_FEATURE_IRQ_UNMASK_ENABLE)
            TIMER5_SetIntrUnMask(eIrq, true);
#endif
            ptTcb->pfnHandler = pfnHandler;
            ptTcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            break;
        case TIMER5_OPS_POLL:
        default:
#if defined(TIMER5_FEATURE_IRQ_UNMASK_ENABLE)
            TIMER5_SetIntrUnMask(eIrq, false);
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

HAL_ERR_e HAL_TIMER5_GetStatus(TIMER5_ID_e eId, uint32_t *pun32Status)
{
    TIMER5_Type *ptTimer;

    if((uint32_t)eId >= TIMER5_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER5_GetReg(eId);
    *pun32Status = TIMER5_GetIntFlag(ptTimer);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER5_SetPolarity(TIMER5_ID_e eId, TIMER5_POL_e ePol)
{
    TIMER5_Type *ptTimer;

    if((uint32_t)eId >= TIMER5_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ePol = (TIMER5_POL_e)TIMER5_ConvPol((P_TIMER5_POL_e)ePol);
    ptTimer = PRV_TIMER5_GetReg(eId);
    SET_TIMER5_CR_OUTPORT_POL(ptTimer, ePol);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER5_SetData(TIMER5_ID_e eId, TIMER5_DATA_e eSel, uint32_t un32Data)
{
    TIMER5_Type *ptTimer;

    if((uint32_t)eId >= TIMER5_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER5_GetReg(eId);

    switch(eSel)
    {
        case TIMER5_DATA_A:
             SET_TIMER5_DR_A(ptTimer, un32Data);
             break;
        case TIMER5_DATA_B:
             SET_TIMER5_DR_B(ptTimer, un32Data);
             break;
        default:
             break;
    }

    return HAL_ERR_OK;

}

HAL_ERR_e HAL_TIMER5_GetData(TIMER5_ID_e eId, TIMER5_DATA_e eSel, uint32_t *pun32Data)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER5_Type *ptTimer;

    if((uint32_t)eId >= TIMER5_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER5_GetReg(eId);

    switch(eSel)
    {
        case TIMER5_DATA_A:
             *pun32Data = GET_TIMER5_DR_A(ptTimer);
             break;
        case TIMER5_DATA_B:
             *pun32Data = GET_TIMER5_DR_B(ptTimer);
             break;
        case TIMER5_DATA_CAP_A:
             *pun32Data = GET_TIMER5_DR_CAPA(ptTimer);
             break;
        case TIMER5_DATA_CAP_B:
             *pun32Data = GET_TIMER5_DR_CAPB(ptTimer);
             break;
        default:
            *pun32Data = 0;
             eErr = HAL_ERR_PARAMETER;
             break;
    }

    return eErr;
}

HAL_ERR_e HAL_TIMER5_Start(TIMER5_ID_e eId)
{
    TIMER5_Type *ptTimer;

    if((uint32_t)eId >= TIMER5_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER5_GetReg(eId);
    SET_TIMER5_CR_EN(ptTimer, true);
    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER5_Stop(TIMER5_ID_e eId)
{
    TIMER5_Type *ptTimer;

    if((uint32_t)eId >= TIMER5_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER5_GetReg(eId);
    SET_TIMER5_CR_EN(ptTimer, false);
    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER5_SetPause(TIMER5_ID_e eId, bool bPause)
{
    TIMER5_Type *ptTimer;

    if((uint32_t)eId >= TIMER5_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }
    ptTimer = PRV_TIMER5_GetReg(eId);
    SET_TIMER5_CR_PAUSE(ptTimer, bPause);
    return HAL_ERR_OK;
}

static void PRV_TIMER5_IRQHandler(TIMER5_ID_e eId)
{
    TIMER5_Type *ptTimer;
    TIMER5_CTRL_BLK_t *ptTcb;
    uint32_t un32Event=0;
    uint8_t un8Status=0;

    ptTimer = PRV_TIMER5_GetReg(eId);
    ptTcb = &s_tTcb[eId];

    un8Status = TIMER5_GetIntFlag(ptTimer);
    if(un8Status & P_TIMER5_INTR_FLAG_MATCH || un8Status & P_TIMER5_INTR_FLAG_CAP)
    {
        switch(ptTcb->eMode)
        {
            case TIMER5_MODE_PERIODIC:
            case TIMER5_MODE_ONESHOT:
                un32Event |= TIMER5_EVENT_PERIODIC_MATCH;
                break;
            case TIMER5_MODE_PWM:
                if(ptTcb->un8PwmEvt & TIMER5_EVENT_PWM_DUTY)
                {
                    if(TIMER5_ONLY_PWM_PERIOD)
                    {
                        un32Event |= TIMER5_EVENT_PWM_PERIOD;
                    }
                    else
                    {
                        un32Event |= TIMER5_EVENT_PWM_DUTY;
                    }
                }
                break;
            case TIMER5_MODE_CAPTURE:
                un32Event |= TIMER5_EVENT_CAPTURE_A;
                break;
            default:
                break;
        }
    }

    if(un8Status & P_TIMER5_INTR_FLAG_B)
    {
        switch(ptTcb->eMode)
        {
            case TIMER5_MODE_PERIODIC:
            case TIMER5_MODE_ONESHOT:
                un32Event |= TIMER5_EVENT_PERIODIC_MATCH;
                break;
            case TIMER5_MODE_PWM:
                if(ptTcb->un8PwmEvt & TIMER5_EVENT_PWM_DUTY)
                {
                    un32Event |= TIMER5_EVENT_PWM_PERIOD;
                }
                break;
            case TIMER5_MODE_CAPTURE:
                un32Event |= TIMER5_EVENT_CAPTURE_B;
                break;
            default:
                break;
        }

    }

    if(un32Event != 0)
    {
        /* clear status */ 
        SET_TIMER5_IER_MATCH_FLAG(ptTimer, true);
        SET_TIMER5_IER_CAP_FLAG(ptTimer, true);
    }

    if(ptTcb->pfnHandler != NULL && un32Event)
    {
        ptTcb->pfnHandler(un32Event, ptTcb->pContext);
    }
}

void TIMER50_IRQHandler(void)
{
    PRV_TIMER5_IRQHandler(TIMER5_ID_0);
}

void TIMER51_IRQHandler(void)
{
    PRV_TIMER5_IRQHandler(TIMER5_ID_1);
}

void TIMER52_IRQHandler(void)
{
    PRV_TIMER5_IRQHandler(TIMER5_ID_2);
}

void TIMER53_IRQHandler(void)
{
    PRV_TIMER5_IRQHandler(TIMER5_ID_3);
}

void TIMER54_IRQHandler(void)
{
    PRV_TIMER5_IRQHandler(TIMER5_ID_4);
}

void TIMER55_IRQHandler(void)
{
    PRV_TIMER5_IRQHandler(TIMER5_ID_5);
}

void TIMER56_IRQHandler(void)
{
    PRV_TIMER5_IRQHandler(TIMER5_ID_6);
}

void TIMER57_IRQHandler(void)
{
    PRV_TIMER5_IRQHandler(TIMER5_ID_7);
}

void TIMER58_IRQHandler(void)
{
    PRV_TIMER5_IRQHandler(TIMER5_ID_8);
}

void TIMER59_IRQHandler(void)
{
    PRV_TIMER5_IRQHandler(TIMER5_ID_9);
}

#endif /* _TIMER5 */
