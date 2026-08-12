/**
 *******************************************************************************
 * @file        hal_timer4e.c
 * @author      ABOV R&D Division
 * @brief       two-output typed timer
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

#if defined(_TIMER4E)
#include "hal_timer4e.h"
#include "hal_timer4e_prv.h"
#if defined(TIMER4E_FEATURE_NMI_BLANK) && defined(_NMI)
#include "hpl_nmi.h"
#endif

typedef struct
{
     TIMER4E_OPS_e                eOps;
     pfnTIMER4E_IRQ_Handler_t     pfnHandler;
     void                         *pContext;

     TIMER4E_MODE_e               eMode;
} TIMER4E_CTRL_BLK_t;

static TIMER4E_CTRL_BLK_t s_tTcb[TIMER4E_CH_NUM];

static void PRV_TIMER4E_IRQHandler(TIMER4E_ID_e eId);

#if defined(TIMER4E_FEATURE_NMI_BLANK) && defined(_NMI)
static void PRV_TIMER4E_NMIHandler(uint32_t un32Event, void *pContext)
{
    PRV_TIMER4E_IRQHandler(TIMER4E_ID_0);
}
#endif

static TIMER4E_Type *PRV_TIMER4E_GetReg(TIMER4E_ID_e eId)
{
    return TIMER4E_GetReg((uint32_t)eId);
}

static HAL_ERR_e PRV_TIMER4E_SetScuEnable(P_TIMER4E_ID_e eId, bool bEnable)
{
    return TIMER4E_SetScuEnable(eId, bEnable);
}

HAL_ERR_e HAL_TIMER4E_Init(TIMER4E_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER4E_Type *ptTimer;

    if((uint32_t)eId >= TIMER4E_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_TIMER4E_SetScuEnable((P_TIMER4E_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tTcb[(uint32_t)eId], 0x00, sizeof(TIMER4E_CTRL_BLK_t));

    ptTimer = PRV_TIMER4E_GetReg(eId);
    /* clear control register */
    SET_TIMER4E_CR(ptTimer, 0x00);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER4E_Uninit(TIMER4E_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= TIMER4E_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_TIMER4E_SetScuEnable((P_TIMER4E_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = TIMER4E_GetIRQNum((P_TIMER4E_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tTcb[(uint32_t)eId], 0x00, sizeof(TIMER4E_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER4E_SetClkConfig(TIMER4E_ID_e eId, TIMER4E_CLK_CFG_t *ptClkCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER4E_Type *ptTimer;

    if((uint32_t)eId >= TIMER4E_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(ptClkCfg->un16PreScale >= TIMER4E_PRESCALE_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    ptTimer = PRV_TIMER4E_GetReg(eId);

    switch(ptClkCfg->eClk)
    {
        case TIMER4E_CLK_EXT:
            TIMER4E_SetExtClk((P_TIMER4E_ID_e)eId, ptTimer,
                             (P_TIMER4E_EXTCLK_EDGE_e)ptClkCfg->uSubClk.eExtClkEdge);
            break;
        case TIMER4E_CLK_PCLK:
            TIMER4E_SetPClk((P_TIMER4E_ID_e)eId, ptTimer,
                           (P_TIMER4E_PCLK_DIV_e)P_TIMER4E_PCLK_DIV_MAX);
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    /* Prescale */
    SET_TIMER4E_PREDR(ptTimer, ptClkCfg->un16PreScale);

    return eErr;
}

HAL_ERR_e HAL_TIMER4E_SetConfig(TIMER4E_ID_e eId, TIMER4E_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER4E_Type *ptTimer;
    TIMER4E_CTRL_BLK_t *ptTcb;

    if((uint32_t)eId >= TIMER4E_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(ptCfg->eMode >= TIMER4E_MODE_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    ptTimer = PRV_TIMER4E_GetReg(eId);
    ptTcb = &s_tTcb[eId];

    /* Clear Count Register */
    SET_TIMER4E_CR_CLR(ptTimer, true);

    /* working mode */
    SET_TIMER4E_CR_MODE(ptTimer, (uint8_t)ptCfg->eMode);

#if TIMER4E_INTERRUPT_ENABLE_CONCURRENT
    SET_TIMER4E_IER(ptTimer, (uint8_t)ptCfg->un16IntrEnable);
#else
    /* clear interrupt enable*/
    SET_TIMER4E_IER(ptTimer, 0x00);

    if(ptCfg->un16IntrEnable)
    {
        if(ptCfg->un16IntrEnable & TIMER4E_INTR_PERIOD_MATCH)
        {
            SET_TIMER4E_IER_MATCH_P_EN(ptTimer, true);
        }
        if(ptCfg->un16IntrEnable & TIMER4E_INTR_MATCH_CH_A_UP_DOWN)
        {
            SET_TIMER4E_IER_MATCH_A_EN(ptTimer, (ptCfg->un16IntrEnable & TIMER4E_INTR_MATCH_CH_A_UP_DOWN));
        }
        if(ptCfg->un16IntrEnable & TIMER4E_INTR_MATCH_CH_B_UP_DOWN)
        {
            SET_TIMER4E_IER_MATCH_B_EN(ptTimer, (ptCfg->un16IntrEnable & TIMER4E_INTR_MATCH_CH_B_UP_DOWN) >> 2);
        }
        if(ptCfg->un16IntrEnable & TIMER4E_INTR_BOTTOM)
        {
            SET_TIMER4E_IER_BOTTOM_EN(ptTimer, true);
        }

        /* if capture mode select */
        if(ptCfg->eMode == TIMER4E_MODE_CAPTURE && ptCfg->un16IntrEnable & TIMER4E_INTR_CAPTURE)
        {
            SET_TIMER4E_IER_CAP_EN(ptTimer, true);
        }

        /* if force output enabled */
        if(ptCfg->tFrcInpCfg.bEnable == true && ptCfg->un16IntrEnable & TIMER4E_INTR_OUTPUT_FORCE)
        {
            SET_TIMER4E_IER_FRC_EN(ptTimer, true);
        }
    }
#endif

    /* if capture mode select */
    if(ptCfg->eMode == TIMER4E_MODE_CAPTURE)
    {
        SET_TIMER4E_CR_CAPPORT_POL(ptTimer, (uint8_t)ptCfg->eCapClr);
    }

    /* Enable Timer4e counter synchronized with Timer4e others */
    SET_TIMER4E_CR_SYNCNT_EN(ptTimer, ptCfg->tSyncCnt.bEnable);
    if(ptCfg->tSyncCnt.bEnable == true)
    {
        SET_TIMER4E_CR_SYNCNT_ID(ptTimer, (uint8_t)ptCfg->tSyncCnt.eId);
    }

    /* Enable Force Input for Output level */
    SET_TIMER4E_CR_FRC_EN(ptTimer, ptCfg->tFrcInpCfg.bEnable);
    if(ptCfg->tFrcInpCfg.bEnable == true)
    {
        SET_TIMER4E_CR_FRC_ID(ptTimer, (uint8_t)ptCfg->tFrcInpCfg.eId);
    }

    /* output mode and configuration */
    SET_TIMER4E_CR_A_PORT_OUTEN(ptTimer, (uint8_t)ptCfg->tOutputsCfg.tAPortCfg.bEnable);
    SET_TIMER4E_CR_A_PORT_OUTDEF_POL(ptTimer, (uint8_t)ptCfg->tOutputsCfg.tAPortCfg.eDisPol);
    SET_TIMER4E_CR_A_PORT_OUTSTART_POL(ptTimer, (uint8_t)ptCfg->tOutputsCfg.tAPortCfg.eEnPol);
    SET_TIMER4E_CR_B_PORT_OUTEN(ptTimer, (uint8_t)ptCfg->tOutputsCfg.tBPortCfg.bEnable);
    SET_TIMER4E_CR_B_PORT_OUTDEF_POL(ptTimer, (uint8_t)ptCfg->tOutputsCfg.tBPortCfg.eDisPol);
    SET_TIMER4E_CR_B_PORT_OUTSTART_POL(ptTimer, (uint8_t)ptCfg->tOutputsCfg.tBPortCfg.eEnPol);

    /* output delay configuration */
    SET_TIMER4E_CR_OUTPUT_DLY(ptTimer, ptCfg->tDlyCfg.bEnable);
    SET_TIMER4E_CR_OUTPUT_DLY_POS(ptTimer, (uint8_t)ptCfg->tDlyCfg.ePos);
    SET_TIMER4E_CR_OUTPUT_DLY_VALUE(ptTimer, (uint16_t)ptCfg->tDlyCfg.un16Value);

    /* reload */
    SET_TIMER4E_CR_RELOAD(ptTimer, ptCfg->eReload);

    /* Set Period */
    SET_TIMER4E_DR_P(ptTimer, ptCfg->utData.tGRD.un16DataP);
    /* Set Data A */
    SET_TIMER4E_DR_A(ptTimer, ptCfg->utData.tGRD.un16DataA);
    /* Set Data B */
    SET_TIMER4E_DR_B(ptTimer, ptCfg->utData.tGRD.un16DataB);

    ptTcb->eMode = ptCfg->eMode;

    return eErr;
}

HAL_ERR_e HAL_TIMER4E_SetAdcTrgConfig(TIMER4E_ID_e eId, TIMER4E_ADCTRG_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER4E_Type *ptTimer;

    if((uint32_t)eId >= TIMER4E_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER4E_GetReg(eId);
    SET_TIMER4E_ADCTRG(ptTimer, ptCfg->un16Enable);

    return eErr;
}

HAL_ERR_e HAL_TIMER4E_SetIRQ(TIMER4E_ID_e eId, TIMER4E_OPS_e eOps, pfnTIMER4E_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio, bool bBlnkNonMask)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER4E_CTRL_BLK_t *ptTcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= TIMER4E_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if defined(TIMER4E_FEATURE_NMI_BLANK) && defined(_NMI)
#else
    if(bBlnkNonMask == true)
    {
        return HAL_ERR_NOT_SUPPORTED;
    }
#endif

    ptTcb = &s_tTcb[(uint32_t)eId];
    eIrq = TIMER4E_GetIRQNum((P_TIMER4E_ID_e)eId);

    switch(eOps)
    {
        case TIMER4E_OPS_INTR:
#if defined(TIMER4E_FEATURE_IRQ_UNMASK_ENABLE)
            TIMER4E_SetIntrUnMask(eIrq, true);
#endif
#if defined(TIMER4E_FEATURE_NMI_BLANK) && defined(_NMI)
            eErr = HPL_NMI_SetIRQ(NMI_INTR_TIMER4E_BLNK, &PRV_TIMER4E_NMIHandler, NULL, bBlnkNonMask);
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            ptTcb->pfnHandler = pfnHandler;
            ptTcb->pContext = pContext;
            break;
        case TIMER4E_OPS_POLL:
        default:
#if defined(TIMER4E_FEATURE_IRQ_UNMASK_ENABLE)
            TIMER4E_SetIntrUnMask(eIrq, false);
#endif
#if defined(TIMER4E_FEATURE_NMI_BLANK) && defined(_NMI)
            eErr = HPL_NMI_SetIRQ(NMI_INTR_TIMER4E_BLNK, NULL, NULL, false);
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

HAL_ERR_e HAL_TIMER4E_SetOutputPort(TIMER4E_ID_e eId, TIMER4E_OUTPUTS_CFG_t *ptCfg)
{
    TIMER4E_Type *ptTimer;

    if((uint32_t)eId >= TIMER4E_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER4E_GetReg(eId);

    /* output mode and configuration */
    SET_TIMER4E_CR_A_PORT_OUTEN(ptTimer, (uint8_t)ptCfg->tAPortCfg.bEnable);
    SET_TIMER4E_CR_A_PORT_OUTDEF_POL(ptTimer, (uint8_t)ptCfg->tAPortCfg.eDisPol);
    SET_TIMER4E_CR_A_PORT_OUTSTART_POL(ptTimer, (uint8_t)ptCfg->tAPortCfg.eEnPol);
    SET_TIMER4E_CR_B_PORT_OUTEN(ptTimer, (uint8_t)ptCfg->tBPortCfg.bEnable);
    SET_TIMER4E_CR_B_PORT_OUTDEF_POL(ptTimer, (uint8_t)ptCfg->tBPortCfg.eDisPol);
    SET_TIMER4E_CR_B_PORT_OUTSTART_POL(ptTimer, (uint8_t)ptCfg->tBPortCfg.eEnPol);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER4E_GetStatus(TIMER4E_ID_e eId, uint32_t *pun32Status)
{
    TIMER4E_Type *ptTimer;

    if((uint32_t)eId >= TIMER4E_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER4E_GetReg(eId);
    *pun32Status = GET_TIMER4E_IER_FLAG(ptTimer);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER4E_SetData(TIMER4E_ID_e eId, TIMER4E_DATA_e eSel, uint32_t un32Data)
{
    TIMER4E_Type *ptTimer;

    if((uint32_t)eId >= TIMER4E_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER4E_GetReg(eId);

    switch(eSel)
    {
        case TIMER4E_DATA_P:
             SET_TIMER4E_DR_P(ptTimer, un32Data);
             break;
        case TIMER4E_DATA_A:
             SET_TIMER4E_DR_A(ptTimer, un32Data);
             break;
        case TIMER4E_DATA_B:
             SET_TIMER4E_DR_B(ptTimer, un32Data);
             break;
        default:
             break;
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER4E_GetData(TIMER4E_ID_e eId, TIMER4E_DATA_e eSel, uint32_t *pun32Data)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER4E_Type *ptTimer;

    if((uint32_t)eId >= TIMER4E_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER4E_GetReg(eId);

    switch(eSel)
    {
        case TIMER4E_DATA_P:
             *pun32Data = GET_TIMER4E_DR_P(ptTimer);
             break;
        case TIMER4E_DATA_A:
             *pun32Data = GET_TIMER4E_DR_A(ptTimer);
             break;
        case TIMER4E_DATA_B:
             *pun32Data = GET_TIMER4E_DR_B(ptTimer);
             break;
        case TIMER4E_DATA_CAP:
             *pun32Data = GET_TIMER4E_DR_CAP(ptTimer);
             break;
        default:
            *pun32Data = 0;
             eErr = HAL_ERR_PARAMETER;
             break;
    }

    return eErr;
}

HAL_ERR_e HAL_TIMER4E_Start(TIMER4E_ID_e eId)
{
    TIMER4E_Type *ptTimer;

    if((uint32_t)eId >= TIMER4E_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER4E_GetReg(eId);
    SET_TIMER4E_CR_EN(ptTimer, true);
    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER4E_Stop(TIMER4E_ID_e eId)
{
    TIMER4E_Type *ptTimer;

    if((uint32_t)eId >= TIMER4E_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER4E_GetReg(eId);
    SET_TIMER4E_CR_EN(ptTimer, false);
    return HAL_ERR_OK;
}

static void PRV_TIMER4E_IRQHandler(TIMER4E_ID_e eId)
{
    TIMER4E_Type *ptTimer;
    TIMER4E_CTRL_BLK_t *ptTcb;
    uint32_t un32Event = 0, un32Status = 0;

    ptTimer = PRV_TIMER4E_GetReg(eId);
    ptTcb = &s_tTcb[eId];

    /* get interrupt flag */
    un32Status = (uint32_t)GET_TIMER4E_IER_FLAG(ptTimer);

    /* clear interrupt flag */
    SET_TIMER4E_IER_FLAG(ptTimer, (uint8_t)(un32Status & 0xFF));

    if (un32Status & TIMER4E_INTR_FLAG_MA)
    {
        un32Event |= TIMER4E_EVENT_MATCH_CH_A;
    }

    if (un32Status & TIMER4E_INTR_FLAG_MB)
    {
        un32Event |= TIMER4E_EVENT_MATCH_CH_B;
    }

    if (un32Status & TIMER4E_INTR_FLAG_PM)
    {
        un32Event |= TIMER4E_EVENT_PERIOD_MATCH;
    }

    if (un32Status & TIMER4E_INTR_FLAG_BT)
    {
        un32Event |= TIMER4E_EVENT_BOTTOM;
    }

    if (un32Status & TIMER4E_INTR_FLAG_CA)
    {
        un32Event |= TIMER4E_EVENT_CAPTURE;
    }

    if (un32Status & TIMER4E_INTR_FLAG_OF)
    {
        un32Event |= TIMER4E_EVENT_OUTPUT_FORCE;
    }

    if(ptTcb->pfnHandler != NULL && un32Event)
    {
        ptTcb->pfnHandler(un32Event, ptTcb->pContext);
    }
}

void TIMER4E0_IRQHandler(void)
{
    PRV_TIMER4E_IRQHandler(TIMER4E_ID_0);
}

void TIMER4E1_IRQHandler(void)
{
    PRV_TIMER4E_IRQHandler(TIMER4E_ID_1);
}

void TIMER4E2_IRQHandler(void)
{
    PRV_TIMER4E_IRQHandler(TIMER4E_ID_2);
}

void TIMER4E3_IRQHandler(void)
{
    PRV_TIMER4E_IRQHandler(TIMER4E_ID_3);
}

void TIMER4E4_IRQHandler(void)
{
    PRV_TIMER4E_IRQHandler(TIMER4E_ID_4);
}

void TIMER4E5_IRQHandler(void)
{
    PRV_TIMER4E_IRQHandler(TIMER4E_ID_5);
}

void TIMER4E6_IRQHandler(void)
{
    PRV_TIMER4E_IRQHandler(TIMER4E_ID_6);
}

void TIMER4E7_IRQHandler(void)
{
    PRV_TIMER4E_IRQHandler(TIMER4E_ID_7);
}

void TIMER4E8_IRQHandler(void)
{
    PRV_TIMER4E_IRQHandler(TIMER4E_ID_8);
}

void TIMER4E9_IRQHandler(void)
{
    PRV_TIMER4E_IRQHandler(TIMER4E_ID_9);
}

#endif /* _TIMER4E */
