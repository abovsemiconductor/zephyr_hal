/**
 *******************************************************************************
 * @file        hal_timer4.c
 * @author      ABOV R&D Division
 * @brief       4N typed timer
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

#if defined(_TIMER4)
#include "hal_timer4.h"
#include "hal_timer4_prv.h"

typedef struct
{
     TIMER4_OPS_e               eOps;
     pfnTIMER4_IRQ_Handler_t    pfnHandler;
     void                       *pContext;

     TIMER4_MODE_e              eMode;
     uint8_t                    un8PwmEvt;
} TIMER4_CTRL_BLK_t;

static TIMER4_CTRL_BLK_t s_tTcb[TIMER4_CH_NUM];

static TIMER4_Type *PRV_TIMER4_GetReg(TIMER4_ID_e eId)
{
    return TIMER4_GetReg((uint32_t)eId);
}

static HAL_ERR_e PRV_TIMER4_SetScuEnable(P_TIMER4_ID_e eId, bool bEnable)
{
    return TIMER4_SetScuEnable(eId, bEnable);
}

HAL_ERR_e HAL_TIMER4_Init(TIMER4_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER4_Type *ptTimer;

    if((uint32_t)eId >= TIMER4_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_TIMER4_SetScuEnable((P_TIMER4_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tTcb[(uint32_t)eId], 0x00, sizeof(TIMER4_CTRL_BLK_t));

    ptTimer = PRV_TIMER4_GetReg(eId);
    /* clear control register */
    SET_TIMER4_CR(ptTimer, 0x00);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER4_Uninit(TIMER4_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= TIMER4_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_TIMER4_SetScuEnable((P_TIMER4_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = TIMER4_GetIRQNum((P_TIMER4_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tTcb[(uint32_t)eId], 0x00, sizeof(TIMER4_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER4_SetClkConfig(TIMER4_ID_e eId, TIMER4_CLK_CFG_t *ptClkCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER4_Type *ptTimer;

    if((uint32_t)eId >= TIMER4_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(ptClkCfg->un16PreScale >= TIMER4_PRESCALE_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    ptTimer = PRV_TIMER4_GetReg(eId);

    switch(ptClkCfg->eClk)
    {
        case TIMER4_CLK_MCCR:
             eErr = TIMER4_SetMccrClk((P_TIMER4_ID_e)eId, ptTimer, 
                                     (P_TIMER4_CLK_MCCR_e)ptClkCfg->uSubClk.eMccr,
                                     ptClkCfg->un8MccrDiv);
            break;
        case TIMER4_CLK_EXT:
            eErr = TIMER4_SetExtClk((P_TIMER4_ID_e)eId, ptTimer,
                                   (P_TIMER4_EXTCLK_EDGE_e)ptClkCfg->uSubClk.eExtClkEdge);
            break;
        case TIMER4_CLK_PCLK:
            eErr = TIMER4_SetPClk((P_TIMER4_ID_e)eId, ptTimer,
                                 (P_TIMER4_PCLK_DIV_e)P_TIMER4_PCLK_DIV_MAX);
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    /* Prescale */
    SET_TIMER4_PREDR(ptTimer, ptClkCfg->un16PreScale);

    return eErr;
}

HAL_ERR_e HAL_TIMER4_SetConfig(TIMER4_ID_e eId, TIMER4_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER4_Type *ptTimer;
    TIMER4_CTRL_BLK_t *ptTcb;
    TIMER4_MODE_e eMode;
    TIMER4_POL_e ePol;

    if((uint32_t)eId >= TIMER4_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(ptCfg->eMode >= TIMER4_MODE_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    ptTimer = PRV_TIMER4_GetReg(eId);
    ptTcb = &s_tTcb[eId];

    /* mode */
    eMode = (TIMER4_MODE_e)TIMER4_ConvMode((P_TIMER4_MODE_e)ptCfg->eMode);
    SET_TIMER4_CR_MODE(ptTimer, (uint32_t)eMode);

    /* polarity */
    ePol = (TIMER4_POL_e)TIMER4_ConvPol((P_TIMER4_POL_e)ptCfg->ePol);
    SET_TIMER4_CR_OUTPORT_POL(ptTimer, ePol);

    if(ptCfg->bIntrEnable)
    {
        /* enable interrupt */
        SET_TIMER4_IER_CLR(ptTimer);
        switch(ptCfg->eMode)
        {
            case TIMER4_MODE_PERIODIC:
            case TIMER4_MODE_ONESHOT:
            case TIMER4_MODE_PWM:
                SET_TIMER4_IER_MATCH_EN(ptTimer, true);
                break;
            case TIMER4_MODE_CAPTURE:
                SET_TIMER4_IER_CAP_EN(ptTimer, true);
                break;
            default:
                eErr = HAL_ERR_PARAMETER;
                break;
        }
    }

    if(eErr == HAL_ERR_OK)
    {
        ptTcb->eMode = ptCfg->eMode;

        if(ptCfg->eMode == TIMER4_MODE_PWM)
        {
            /* Set DUTY */
            SET_TIMER4_DR_DUTY(ptTimer, ptCfg->utData.tPWM.un16Duty);
            /* Set PERIOD */
            SET_TIMER4_DR_PERIOD(ptTimer, ptCfg->utData.tPWM.un16Period);
            ptTcb->un8PwmEvt = TIMER4_EVENT_PWM_DUTY | TIMER4_EVENT_PWM_PERIOD;
        }
        else
        {
            /* Set Data A (GRA) */
            SET_TIMER4_DR_A(ptTimer, ptCfg->utData.tGRD.un16DataA);
            /* Set Data B (GRB) */
            SET_TIMER4_DR_B(ptTimer, ptCfg->utData.tGRD.un16DataB);
            if(ptCfg->eMode == TIMER4_MODE_CAPTURE)
            {
                SET_TIMER4_CR_CAPPORT_POL(ptTimer, (uint8_t)ptCfg->tCapCfg.eEdge);
                SET_TIMER4_CR_CAP_CH(ptTimer, (uint8_t)ptCfg->tCapCfg.eCh);
                SET_TIMER4_CAP_PREDR(ptTimer, ptCfg->tCapCfg.un16EdgeCount);
            }
        }

        /* Clear Count Register */
        SET_TIMER4_CR_CLR(ptTimer, true);
    }

    return eErr;
}

HAL_ERR_e HAL_TIMER4_SetIRQ(TIMER4_ID_e eId, TIMER4_OPS_e eOps, pfnTIMER4_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER4_CTRL_BLK_t *ptTcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= TIMER4_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTcb = &s_tTcb[(uint32_t)eId];
    eIrq = TIMER4_GetIRQNum((P_TIMER4_ID_e)eId);

    switch(eOps)
    {
        case TIMER4_OPS_INTR:
            ptTcb->pfnHandler = pfnHandler;
            ptTcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            break;
        case TIMER4_OPS_POLL:
        default:
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptTcb->pContext = NULL;
            ptTcb->pfnHandler = NULL;
            break;
    }

    ptTcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_TIMER4_GetStatus(TIMER4_ID_e eId, uint32_t *pun32Status)
{
    TIMER4_Type *ptTimer;

    if((uint32_t)eId >= TIMER4_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER4_GetReg(eId);
    *pun32Status = TIMER4_GetIntFlag(ptTimer);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER4_SetPolarity(TIMER4_ID_e eId, TIMER4_POL_e ePol)
{
    TIMER4_Type *ptTimer;

    if((uint32_t)eId >= TIMER4_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ePol = (TIMER4_POL_e)TIMER4_ConvPol((P_TIMER4_POL_e)ePol);
    ptTimer = PRV_TIMER4_GetReg(eId);
    SET_TIMER4_CR_OUTPORT_POL(ptTimer, ePol);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER4_SetData(TIMER4_ID_e eId, TIMER4_DATA_e eSel, uint32_t un32Data)
{
    TIMER4_Type *ptTimer;

    if((uint32_t)eId >= TIMER4_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER4_GetReg(eId);

    switch(eSel)
    {
        case TIMER4_DATA_A:
             SET_TIMER4_DR_A(ptTimer, un32Data);
             break;
        case TIMER4_DATA_B:
             SET_TIMER4_DR_B(ptTimer, un32Data);
             break;
        default:
             break;
    }

    return HAL_ERR_OK;

}

HAL_ERR_e HAL_TIMER4_GetData(TIMER4_ID_e eId, TIMER4_DATA_e eSel, uint32_t *pun32Data)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER4_Type *ptTimer;

    if((uint32_t)eId >= TIMER4_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER4_GetReg(eId);

    switch(eSel)
    {
        case TIMER4_DATA_A:
             *pun32Data = GET_TIMER4_DR_A(ptTimer);
             break;
        case TIMER4_DATA_B:
             *pun32Data = GET_TIMER4_DR_B(ptTimer);
             break;
        case TIMER4_DATA_CAP_A:
             *pun32Data = GET_TIMER4_DR_CAPA(ptTimer);
             break;
        case TIMER4_DATA_CAP_B:
             *pun32Data = GET_TIMER4_DR_CAPB(ptTimer);
             break;
        default:
            *pun32Data = 0;
             eErr = HAL_ERR_PARAMETER;
             break;
    }

    return eErr;
}

HAL_ERR_e HAL_TIMER4_Start(TIMER4_ID_e eId)
{
    TIMER4_Type *ptTimer;

    if((uint32_t)eId >= TIMER4_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER4_GetReg(eId);
    SET_TIMER4_CR_EN(ptTimer, true);
    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER4_Stop(TIMER4_ID_e eId)
{
    TIMER4_Type *ptTimer;

    if((uint32_t)eId >= TIMER4_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER4_GetReg(eId);
    SET_TIMER4_CR_EN(ptTimer, false);
    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER4_SetPause(TIMER4_ID_e eId, bool bPause)
{
    TIMER4_Type *ptTimer;

    if((uint32_t)eId >= TIMER4_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }
    ptTimer = PRV_TIMER4_GetReg(eId);
    SET_TIMER4_CR_PAUSE(ptTimer, bPause);
    return HAL_ERR_OK;
}

static void PRV_TIMER4_IRQHandler(TIMER4_ID_e eId)
{
    TIMER4_Type *ptTimer;
    TIMER4_CTRL_BLK_t *ptTcb;
    uint32_t un32Event=0;
    uint8_t un8Status=0;

    ptTimer = PRV_TIMER4_GetReg(eId);
    ptTcb = &s_tTcb[eId];

    un8Status = TIMER4_GetIntFlag(ptTimer);
    if(un8Status & P_TIMER4_INTR_FLAG_MATCH || un8Status & P_TIMER4_INTR_FLAG_CAP)
    {
        switch(ptTcb->eMode)
        {
            case TIMER4_MODE_PERIODIC:
            case TIMER4_MODE_ONESHOT:
                un32Event |= TIMER4_EVENT_PERIODIC_MATCH;
                break;
            case TIMER4_MODE_PWM:
                if(ptTcb->un8PwmEvt & TIMER4_EVENT_PWM_DUTY)
                {
                    if(TIMER4_ONLY_PWM_PERIOD)
                    {
                        un32Event |= TIMER4_EVENT_PWM_PERIOD;
                    }
                    else
                    {
                        un32Event |= TIMER4_EVENT_PWM_DUTY;
                    }
                }
                break;
            case TIMER4_MODE_CAPTURE:
                un32Event |= TIMER4_EVENT_CAPTURE_A;
                break;
            default:
                break;
        }
    }

    if(un8Status & P_TIMER4_INTR_FLAG_B)
    {
        switch(ptTcb->eMode)
        {
            case TIMER4_MODE_PERIODIC:
            case TIMER4_MODE_ONESHOT:
                un32Event |= TIMER4_EVENT_PERIODIC_MATCH;
                break;
            case TIMER4_MODE_PWM:
                if(ptTcb->un8PwmEvt & TIMER4_EVENT_PWM_DUTY)
                {
                    un32Event |= TIMER4_EVENT_PWM_PERIOD;
                }
                break;
            case TIMER4_MODE_CAPTURE:
                un32Event |= TIMER4_EVENT_CAPTURE_B;
                break;
            default:
                break;
        }

    }

    if(un32Event != 0)
    {
        /* clear status */ 
        SET_TIMER4_IER_MATCH_FLAG(ptTimer, true);
        SET_TIMER4_IER_CAP_FLAG(ptTimer, true);
    }

    if(ptTcb->pfnHandler != NULL && un32Event)
    {
        ptTcb->pfnHandler(un32Event, ptTcb->pContext);
    }
}

void TIMER40_IRQHandler(void)
{
    PRV_TIMER4_IRQHandler(TIMER4_ID_0);
}

void TIMER41_IRQHandler(void)
{
    PRV_TIMER4_IRQHandler(TIMER4_ID_1);
}

void TIMER42_IRQHandler(void)
{
    PRV_TIMER4_IRQHandler(TIMER4_ID_2);
}

void TIMER43_IRQHandler(void)
{
    PRV_TIMER4_IRQHandler(TIMER4_ID_3);
}

void TIMER44_IRQHandler(void)
{
    PRV_TIMER4_IRQHandler(TIMER4_ID_4);
}

void TIMER45_IRQHandler(void)
{
    PRV_TIMER4_IRQHandler(TIMER4_ID_5);
}

void TIMER46_IRQHandler(void)
{
    PRV_TIMER4_IRQHandler(TIMER4_ID_6);
}

void TIMER47_IRQHandler(void)
{
    PRV_TIMER4_IRQHandler(TIMER4_ID_7);
}

void TIMER48_IRQHandler(void)
{
    PRV_TIMER4_IRQHandler(TIMER4_ID_8);
}

void TIMER49_IRQHandler(void)
{
    PRV_TIMER4_IRQHandler(TIMER4_ID_9);
}

#endif /* _TIMER4 */
