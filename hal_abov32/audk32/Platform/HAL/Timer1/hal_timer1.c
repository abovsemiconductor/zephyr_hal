/**
 *******************************************************************************
 * @file        hal_timer1.c
 * @author      ABOV R&D Division
 * @brief       1N typed Timer
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

#if defined(_TIMER1)
#include "hal_timer1.h"
#include "hal_timer1_prv.h"

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
#include "hpl_nmi.h"
#endif

typedef struct
{
     TIMER1_OPS_e               eOps;
     pfnTIMER1_IRQ_Handler_t    pfnHandler;
     void                       *pContext;

     TIMER1_MODE_e              eMode;
     uint8_t                    un8PwmEvt;

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
    bool                    bNmiEnable;
#endif

} TIMER1_CTRL_BLK_t;

static TIMER1_CTRL_BLK_t s_tTcb[TIMER1_CH_NUM];

static void PRV_TIMER1_IRQHandler(TIMER1_ID_e eId);

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
static void PRV_TIMER1_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < TIMER1_CH_NUM; i++)
    {
        if(s_tTcb[i].bNmiEnable == true)
        {
            PRV_TIMER1_IRQHandler((TIMER1_ID_e)i);
        }
    }
}
#endif

static TIMER1_Type *PRV_TIMER1_GetReg(TIMER1_ID_e eId)
{
    return TIMER1_GetReg((uint32_t)eId);
}

static HAL_ERR_e PRV_TIMER1_SetScuEnable(P_TIMER1_ID_e eId, bool bEnable)
{
    return TIMER1_SetScuEnable(eId, bEnable);
}

HAL_ERR_e HAL_TIMER1_Init(TIMER1_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER1_Type *ptTimer;

    if((uint32_t)eId >= TIMER1_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_TIMER1_SetScuEnable((P_TIMER1_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    ptTimer = PRV_TIMER1_GetReg(eId);
    memset(&s_tTcb[(uint32_t)eId], 0x00, sizeof(TIMER1_CTRL_BLK_t));

    /* clear control register */
    SET_TIMER1_CR(ptTimer, 0x00);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER1_Uninit(TIMER1_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= TIMER1_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_TIMER1_SetScuEnable((P_TIMER1_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = TIMER1_GetIRQNum((P_TIMER1_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER1_SetClkConfig(TIMER1_ID_e eId, TIMER1_CLK_CFG_t *ptClkCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER1_Type *ptTimer;

    if((uint32_t)eId >= TIMER1_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(ptClkCfg->un16PreScale >= TIMER1_PRESCALE_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    ptTimer = PRV_TIMER1_GetReg(eId);

    switch(ptClkCfg->eClk)
    {
        case TIMER1_CLK_MCCR:
            TIMER1_SetMccrClk((P_TIMER1_ID_e)eId, ptTimer, 
                              (P_TIMER1_CLK_MCCR_e)ptClkCfg->uSubClk.eMccr,
                              ptClkCfg->un8MccrDiv);
            break;
        case TIMER1_CLK_EXT:
            TIMER1_SetExtClk((P_TIMER1_ID_e)eId, ptTimer,
                             (P_TIMER1_EXTCLK_EDGE_e)ptClkCfg->uSubClk.eExtClkEdge);
            break;
        case TIMER1_CLK_PCLK:
            TIMER1_SetPClk((P_TIMER1_ID_e)eId, ptTimer,
                           (P_TIMER1_PCLK_DIV_e)ptClkCfg->uSubClk.ePClkDiv);
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    /* Prescale */
    SET_TIMER1_PREDR(ptTimer, ptClkCfg->un16PreScale);

    return eErr;
}

HAL_ERR_e HAL_TIMER1_SetConfig(TIMER1_ID_e eId, TIMER1_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER1_Type *ptTimer;
    TIMER1_CTRL_BLK_t *ptTcb;
    TIMER1_MODE_e eMode;
    TIMER1_POL_e ePol;

    if((uint32_t)eId >= TIMER1_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(ptCfg->eMode >= TIMER1_MODE_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    ptTimer = PRV_TIMER1_GetReg(eId);
    ptTcb = &s_tTcb[eId];
    
    /* mode */
    eMode = (TIMER1_MODE_e)TIMER1_ConvMode((P_TIMER1_MODE_e)ptCfg->eMode);
    SET_TIMER1_CR_MODE(ptTimer, (uint32_t)eMode);

    /* polarity */
    ePol = (TIMER1_POL_e)TIMER1_ConvPol((P_TIMER1_POL_e)ptCfg->ePol);
    SET_TIMER1_CR_OUTPORT_POL(ptTimer, ePol);

    if(ptCfg->bIntrEnable)
    {
        /* enable interrupt */
        SET_TIMER1_IER_CLR(ptTimer);
        switch(ptCfg->eMode)
        {
            case TIMER1_MODE_PERIODIC:
            case TIMER1_MODE_ONESHOT:
                SET_TIMER1_IER_MATCH_EN(ptTimer, true);
                break;
            case TIMER1_MODE_PWM:
                SET_TIMER1_IER_MATCH_EN(ptTimer, true);
                /* Set Output TnIO pin if it is available */
                SET_TIMER1_CR_IOPORT_SEL(ptTimer, TIMER1_PORT_OUT);
                break;
            case TIMER1_MODE_CAPTURE:
                SET_TIMER1_IER_CAP_EN(ptTimer, true);
                SET_TIMER1_CR_CAPPORT_POL(ptTimer, (uint8_t)ptCfg->eCapClr);
                break;
            default:
                eErr = HAL_ERR_PARAMETER;
                break;
         }
    }

    if(eErr == HAL_ERR_OK)
    {
        ptTcb->eMode = ptCfg->eMode;

#if defined(TIMER1_FEATURE_OVERFLOW_INTERRUPT)
        if(ptCfg->bOVFIntrEnable)
        {
            SET_TIMER1_IER_OVF_EN(ptTimer, true);
        }
#endif

        if(ptCfg->eMode == TIMER1_MODE_PWM)
        {
            /* Set DUTY */
            SET_TIMER1_DR_DUTY(ptTimer,ptCfg->utData.tPWM.un16Duty);
            /* Set PERIOD */
            SET_TIMER1_DR_PERIOD(ptTimer,ptCfg->utData.tPWM.un16Period);
            ptTcb->un8PwmEvt = TIMER1_EVENT_PWM_DUTY | TIMER1_EVENT_PWM_PERIOD;
        }
        else
        {
            /* Set Data A (GRA) */
            SET_TIMER1_DR_A(ptTimer,ptCfg->utData.tGRD.un16DataA);
            /* Set Data B (GRB) */
            SET_TIMER1_DR_B(ptTimer,ptCfg->utData.tGRD.un16DataB);
        }

        /* Clear Count Register */
        SET_TIMER1_CR_CLR(ptTimer, true);
    }

    return eErr;
}

HAL_ERR_e HAL_TIMER1_SetAdcTrgConfig(TIMER1_ID_e eId, TIMER1_ADCTRG_CFG_t *ptCfg)
{
#if defined(TIMER1_FEATURE_ADC_TRIGGER_CONFIG)
    TIMER1_Type *ptTimer;

    if((uint32_t)eId >= TIMER1_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }
    ptTimer = PRV_TIMER1_GetReg(eId);
    SET_TIMER1_CR_ADCTRG_EN(ptTimer, ptCfg->bEnable);
    if(ptCfg->bEnable)
    {
        SET_TIMER1_CR_ADCTRG_MODE(ptTimer, ptCfg->eMode);
        if(ptCfg->eMode != TIMER1_ADCTRG_MODE_NORMAL)
        {
            SET_TIMER1_DR_ADCTRG_PNT(ptTimer, ptCfg->un16TrgPnt);
        }
    }
    return HAL_ERR_OK;
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_TIMER1_SetIRQ(TIMER1_ID_e eId, TIMER1_OPS_e eOps, pfnTIMER1_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER1_CTRL_BLK_t *ptTcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= TIMER1_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTcb = &s_tTcb[(uint32_t)eId];
    eIrq = TIMER1_GetIRQNum((P_TIMER1_ID_e)eId);

    switch(eOps)
    {
        case TIMER1_OPS_INTR:
#if defined(TIMER1_FEATURE_IRQ_UNMASK_ENABLE)
            TIMER1_SetIntrUnMask(eIrq, true);
#endif
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            if(ptTcb->bNmiEnable == true)
            {
                (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
                ptTcb->bNmiEnable = false;
            }
#endif
            ptTcb->pfnHandler = pfnHandler;
            ptTcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            break;
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
        case TIMER1_OPS_NMI:
            eErr = HPL_NMI_SetSource(eIrq, &PRV_TIMER1_NMIHandler, pContext, true);
            if(eErr == HAL_ERR_OK)
            {
                ptTcb->pfnHandler = pfnHandler;
                ptTcb->pContext = pContext;
            }
            ptTcb->bNmiEnable = true;
            break;
#endif
        case TIMER1_OPS_POLL:
        default:
#if defined(TIMER1_FEATURE_IRQ_UNMASK_ENABLE)
            TIMER1_SetIntrUnMask(eIrq, false);
#endif
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
            ptTcb->bNmiEnable = false;
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

HAL_ERR_e HAL_TIMER1_GetStatus(TIMER1_ID_e eId, uint32_t *pun32Status)
{
    TIMER1_Type *ptTimer;

    if((uint32_t)eId >= TIMER1_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER1_GetReg(eId);
    *pun32Status = TIMER1_GetIntFlag(ptTimer);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER1_SetData(TIMER1_ID_e eId, TIMER1_DATA_e eSel, uint32_t un32Data)
{
    TIMER1_Type *ptTimer;

    if((uint32_t)eId >= TIMER1_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER1_GetReg(eId);

    switch(eSel)
    {
        case TIMER1_DATA_A:
             SET_TIMER1_DR_A(ptTimer, un32Data);
             break;
        case TIMER1_DATA_B:
             SET_TIMER1_DR_B(ptTimer, un32Data);
             break;
        default:
             break;
    }

    return HAL_ERR_OK;

}

HAL_ERR_e HAL_TIMER1_GetData(TIMER1_ID_e eId, TIMER1_DATA_e eSel, uint32_t *pun32Data)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER1_Type *ptTimer;

    if((uint32_t)eId >= TIMER1_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER1_GetReg(eId);

    switch(eSel)
    {
        case TIMER1_DATA_A:
             *pun32Data = GET_TIMER1_DR_A(ptTimer);
             break;
        case TIMER1_DATA_B:
             *pun32Data = GET_TIMER1_DR_B(ptTimer);
             break;
        case TIMER1_DATA_CAP_A:
             *pun32Data = GET_TIMER1_DR_CAPA(ptTimer);
#if defined(TIMER1_FEATURE_CLEAR_CAPTURE_DATA)
             SET_TIMER1_DR_A(ptTimer, 0x0);
#endif
             break;
        case TIMER1_DATA_CAP_B:
             *pun32Data = GET_TIMER1_DR_CAPB(ptTimer);
#if defined(TIMER1_FEATURE_CLEAR_CAPTURE_DATA)
             SET_TIMER1_DR_B(ptTimer, 0x0);
#endif
        case TIMER1_DATA_CNT:
             *pun32Data = GET_TIMER1_CNT(ptTimer);
             break;
        default:
            *pun32Data = 0;
             eErr = HAL_ERR_PARAMETER;
             break;
    }

    return eErr;
}

HAL_ERR_e HAL_TIMER1_Start(TIMER1_ID_e eId)
{
    TIMER1_Type *ptTimer;

    if((uint32_t)eId >= TIMER1_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER1_GetReg(eId);
    SET_TIMER1_CR_EN(ptTimer, true);
    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER1_Stop(TIMER1_ID_e eId)
{
    TIMER1_Type *ptTimer;

    if((uint32_t)eId >= TIMER1_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER1_GetReg(eId);
    SET_TIMER1_CR_EN(ptTimer, false);
    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER1_SetPause(TIMER1_ID_e eId, bool bPause)
{
#if defined(TIMER1_FEATURE_PAUSE)
    TIMER1_Type *ptTimer;

    if((uint32_t)eId >= TIMER1_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }
    ptTimer = PRV_TIMER1_GetReg(eId);
    SET_TIMER1_CR_PAUSE(ptTimer, bPause);
    return HAL_ERR_OK;
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_TIMER1_SetT30Sync(TIMER1_ID_e eId, TIMER1_T30SYNC_CFG_t *ptCfg)
{
#if defined(TIMER1_FEATURE_SYNC_TIMER3)
    TIMER1_Type *ptTimer;

    if((uint32_t)eId >= TIMER1_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }
    ptTimer = PRV_TIMER1_GetReg(eId);
    SET_TIMER1_CR_T30_SSYNC(ptTimer, ptCfg->bSsync);
    SET_TIMER1_CR_T30_CSYNC(ptTimer, ptCfg->bCsync);
    return HAL_ERR_OK;
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_TIMER1_SetDataUpdateMode(TIMER1_ID_e eId, TIMER1_UPDATE_e eUpdate)
{
    return HAL_ERR_NOT_SUPPORTED;
}

HAL_ERR_e HAL_TIMER1_SetInOutPort(TIMER1_ID_e eId, TIMER1_PORT_e ePort)
{
    TIMER1_Type *ptTimer;

    if((uint32_t)eId >= TIMER1_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER1_GetReg(eId);
    SET_TIMER1_CR_IOPORT_SEL(ptTimer,(uint8_t)ePort);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER1_SetInversionPort(TIMER1_ID_e eId, TIMER1_INV_e eInv)
{
    TIMER1_Type *ptTimer;

    if((uint32_t)eId >= TIMER1_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER1_GetReg(eId);
    SET_TIMER1_CR_OUTPORT_INV(ptTimer,(uint8_t)eInv);

    return HAL_ERR_OK;
}

static void PRV_TIMER1_IRQHandler(TIMER1_ID_e eId)
{
    TIMER1_Type *ptTimer;
    TIMER1_CTRL_BLK_t *ptTcb;
    uint32_t un32Event=0;
    uint8_t un8Status=0;

    ptTimer = PRV_TIMER1_GetReg(eId);
    ptTcb = &s_tTcb[eId];

    un8Status = TIMER1_GetIntFlag(ptTimer);
    if(un8Status & P_TIMER1_INTR_FLAG_MATCH || un8Status & P_TIMER1_INTR_FLAG_CAP)
    {
        switch(ptTcb->eMode)
        {
            case TIMER1_MODE_PERIODIC:
            case TIMER1_MODE_ONESHOT:
                un32Event |= TIMER1_EVENT_PERIODIC_MATCH;
                break;
            case TIMER1_MODE_PWM:
                if(ptTcb->un8PwmEvt & TIMER1_EVENT_PWM_DUTY)
                {
                    if(TIMER1_ONLY_PWM_PERIOD)
                    {
                        un32Event |= TIMER1_EVENT_PWM_PERIOD;
                    }
                    else
                    {
                        un32Event |= TIMER1_EVENT_PWM_DUTY;
                    }
                }
                break;
            case TIMER1_MODE_CAPTURE:
                un32Event |= TIMER1_EVENT_CAPTURE_A;
                break;
            default:
                break;
        }
    }

    if(un8Status & P_TIMER1_INTR_FLAG_B)
    {
        switch(ptTcb->eMode)
        {
            case TIMER1_MODE_PERIODIC:
            case TIMER1_MODE_ONESHOT:
                un32Event |= TIMER1_EVENT_PERIODIC_MATCH;
                break;
            case TIMER1_MODE_PWM:
                if(ptTcb->un8PwmEvt & TIMER1_EVENT_PWM_DUTY)
                {
                    un32Event |= TIMER1_EVENT_PWM_PERIOD;
                }
                break;
            case TIMER1_MODE_CAPTURE:
                un32Event |= TIMER1_EVENT_CAPTURE_B;
                break;
            default:
                break;
        }

    }

    if(un32Event != 0)
    {
        /* clear status */ 
        SET_TIMER1_IER_MATCH_FLAG(ptTimer, true);
        SET_TIMER1_IER_CAP_FLAG(ptTimer, true);
    }

#if defined(TIMER1_FEATURE_OVERFLOW_INTERRUPT)
    if(un8Status & P_TIMER1_INTR_FLAG_OVF)
    {
        un32Event |= TIMER1_EVENT_OVERFLOW;
        SET_TIMER1_IER_OVF_FLAG(ptTimer, true);
    }
#endif

    if(ptTcb->pfnHandler != NULL && un32Event)
    {
        ptTcb->pfnHandler(un32Event, ptTcb->pContext);
    }
}

void TIMER10_IRQHandler(void)
{
#if defined (TIMER1_FEATURE_SUPPORT_MULTI_IRQ)
    uint8_t un8Status = 0;
    un8Status = TIMER1_GetIntFlag(PRV_TIMER1_GetReg(TIMER1_ID_0));
    if(un8Status & P_TIMER1_INTR_FLAG_MATCH || un8Status & P_TIMER1_INTR_FLAG_CAP)
    {
        PRV_TIMER1_IRQHandler(TIMER1_ID_0);
        return;
    }
    un8Status = TIMER1_GetIntFlag(PRV_TIMER1_GetReg(TIMER1_ID_1));
    if(un8Status & P_TIMER1_INTR_FLAG_MATCH || un8Status & P_TIMER1_INTR_FLAG_CAP)
    {
        PRV_TIMER1_IRQHandler(TIMER1_ID_1);
        return;
    }
#else
    PRV_TIMER1_IRQHandler(TIMER1_ID_0);
#endif
}

void TIMER11_IRQHandler(void)
{
    PRV_TIMER1_IRQHandler(TIMER1_ID_1);
}

void TIMER12_IRQHandler(void)
{
#if defined (TIMER1_FEATURE_SUPPORT_MULTI_IRQ)
    uint8_t un8Status = 0;
    un8Status = TIMER1_GetIntFlag(PRV_TIMER1_GetReg(TIMER1_ID_2));
    if(un8Status & P_TIMER1_INTR_FLAG_MATCH || un8Status & P_TIMER1_INTR_FLAG_CAP)
    {
        PRV_TIMER1_IRQHandler(TIMER1_ID_2);
        return;
    }
    un8Status = TIMER1_GetIntFlag(PRV_TIMER1_GetReg(TIMER1_ID_3));
    if(un8Status & P_TIMER1_INTR_FLAG_MATCH || un8Status & P_TIMER1_INTR_FLAG_CAP)
    {
        PRV_TIMER1_IRQHandler(TIMER1_ID_3);
        return;
    }
#else
    PRV_TIMER1_IRQHandler(TIMER1_ID_2);
#endif
}

void TIMER13_IRQHandler(void)
{
    PRV_TIMER1_IRQHandler(TIMER1_ID_3);
}

void TIMER14_IRQHandler(void)
{
    PRV_TIMER1_IRQHandler(TIMER1_ID_4);
}

void TIMER15_IRQHandler(void)
{
    PRV_TIMER1_IRQHandler(TIMER1_ID_5);
}

void TIMER16_IRQHandler(void)
{
    PRV_TIMER1_IRQHandler(TIMER1_ID_6);
}

void TIMER17_IRQHandler(void)
{
    PRV_TIMER1_IRQHandler(TIMER1_ID_7);
}

void TIMER18_IRQHandler(void)
{
    PRV_TIMER1_IRQHandler(TIMER1_ID_8);
}

void TIMER19_IRQHandler(void)
{
    PRV_TIMER1_IRQHandler(TIMER1_ID_9);
}

void TIMER110_IRQHandler(void)
{
    PRV_TIMER1_IRQHandler(TIMER1_ID_10);
}

void TIMER111_IRQHandler(void)
{
    PRV_TIMER1_IRQHandler(TIMER1_ID_11);
}

#endif /* _TIMER1 */
