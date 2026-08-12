/**
 *******************************************************************************
 * @file        hal_qei.c
 * @author      ABOV R&D Division
 * @brief       Quardrature Encoder InterFace
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

#if defined(_QEI)
#include "hal_qei.h"
#include "hal_qei_prv.h"

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
#include "hpl_nmi.h"
#endif

typedef struct
{
     QEI_OPS_e               eOps;
     pfnQEI_IRQ_Handler_t    pfnHandler;
     void                    *pContext;
     bool                    bVelEnable;

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
    bool                    bNmiEnable;
#endif

} QEI_CTRL_BLK_t;

static QEI_CTRL_BLK_t s_tQcb[QEI_CH_NUM];

static void PRV_QEI_IRQHandler(QEI_ID_e eId);

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
static void PRV_QEI_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < QEI_CH_NUM; i++)
    {
        if(s_tQcb[i].bNmiEnable == true)
        {
            PRV_QEI_IRQHandler((QEI_ID_e)i);
        }
    }
}
#endif

static QEI_Type *PRV_QEI_GetReg(QEI_ID_e eId)
{
    return QEI_GetReg((uint32_t)eId);
}

static HAL_ERR_e PRV_QEI_SetScuEnable(P_QEI_ID_e eId, bool bEnable)
{
    return QEI_SetScuEnable(eId, bEnable);
}

HAL_ERR_e HAL_QEI_Init(QEI_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    QEI_Type *ptQei;

    if((uint32_t)eId >= QEI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_QEI_SetScuEnable((P_QEI_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tQcb[(uint32_t)eId], 0x00, sizeof(QEI_CTRL_BLK_t));

    ptQei = PRV_QEI_GetReg(eId);
    SET_QEI_CR_EN(ptQei, true);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_QEI_Uninit(QEI_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= QEI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_QEI_SetScuEnable((P_QEI_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcibly, disable Protection Interrupt */
    eIrq = QEI_GetIRQNum((P_QEI_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tQcb[(uint32_t)eId], 0x00, sizeof(QEI_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_QEI_SetConfig(QEI_ID_e eId, QEI_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    QEI_Type *ptQei;

    if((uint32_t)eId >= QEI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptQei = PRV_QEI_GetReg(eId);

    SET_QEI_CR_SIG_MODE(ptQei, (uint8_t)ptCfg->eSigMode);
    SET_QEI_CR_CAP_CNT_EDGE(ptQei, (uint8_t)ptCfg->eCapCnt);
    SET_QEI_CR_POS_CNTER_RST(ptQei, (uint8_t)ptCfg->ePosRst);
    SET_QEI_CR_PHA_PHB_SWAP(ptQei, (uint8_t)ptCfg->bSwap);
    SET_QEI_CR_POS_CHANGE_DIR(ptQei, (uint8_t)ptCfg->bPosCntDir);
    SET_QEI_CR_IDX_CHANGE_DIR(ptQei, (uint8_t)ptCfg->bIdxCntDir);
    SET_QEI_CR_IDX_SIG_INVERT(ptQei, (uint8_t)ptCfg->bIdxPulseInverted);
    SET_QEI_CR_IDX_GATING(ptQei, QEI_IDX_GATING(ptCfg->ePosRstIdx));
    SET_QEI_DR_POS_MAX(ptQei, (uint32_t)ptCfg->un32PosMaxValue);
    SET_QEI_IER(ptQei, (uint16_t)ptCfg->un16IntrEnable, QEI_INTR_BASE_MASK);

    return eErr;
}

HAL_ERR_e HAL_QEI_SetVelConfig(QEI_ID_e eId, QEI_VEL_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    QEI_Type *ptQei;
    QEI_CTRL_BLK_t *ptQcb;

    if((uint32_t)eId >= QEI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptQei = PRV_QEI_GetReg(eId);
    ptQcb = &s_tQcb[(uint32_t)eId];

    ptQcb->bVelEnable = ptCfg->bEnable; 

    if(ptCfg->bEnable)
    {
        SET_QEI_DR_VEL_RELOAD(ptQei, ptCfg->un16Reload);
        SET_QEI_DR_VEL_TIMER(ptQei, ptCfg->un16Timer);
        SET_QEI_DR_VEL_CMP(ptQei, ptCfg->un16Compare);

        SET_QEI_IER_VEL_TIMER_EN(ptQei, ptCfg->bIntrEnable);
        SET_QEI_IER_VEL_CMP_EN(ptQei, ptCfg->bIntrEnable);
    }
    else
    {
        SET_QEI_IER_VEL_TIMER_EN(ptQei, false);
        SET_QEI_IER_VEL_CMP_EN(ptQei, false);
    }

    return eErr;
}

HAL_ERR_e HAL_QEI_SetIRQ(QEI_ID_e eId, QEI_OPS_e eOps, pfnQEI_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    QEI_CTRL_BLK_t *ptQcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= QEI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptQcb = &s_tQcb[(uint32_t)eId];
    eIrq = QEI_GetIRQNum((P_QEI_ID_e)eId);

    switch(eOps)
    {
        case QEI_OPS_INTR:
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            if(ptQcb->bNmiEnable == true)
            {
                (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
                ptQcb->bNmiEnable = false;
            }
#endif
            ptQcb->pfnHandler = pfnHandler;
            ptQcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            break;
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
        case QEI_OPS_NMI:
            eErr = HPL_NMI_SetSource(eIrq, &PRV_QEI_NMIHandler, pContext, true);
            if(eErr == HAL_ERR_OK)
            {
                ptQcb->pfnHandler = pfnHandler;
                ptQcb->pContext = pContext;
            }
            ptQcb->bNmiEnable = true;
            break;
#endif
        case QEI_OPS_POLL:
        default:
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            if(ptQcb->bNmiEnable == true)
            {
                (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
                ptQcb->bNmiEnable = false;
            }
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptQcb->pContext = NULL;
            ptQcb->pfnHandler = NULL;
            break;
    }

    ptQcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_QEI_SetCounterClear(QEI_ID_e eId, uint8_t un8Counter)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    QEI_Type *ptQei;

    if((uint32_t)eId >= QEI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptQei = PRV_QEI_GetReg(eId);

    SET_QEI_CR_CNTER_CLEAR(ptQei, un8Counter, QEI_COUNTER_CLEAR_MASK);

    if(un8Counter & QEI_COUNTER_VELOCITY)
    {
        SET_QEI_DR_VEL_TIMER(ptQei, QEI_VELOCITY_TIMER_CLEAR);
    }

    return eErr;
}

HAL_ERR_e HAL_QEI_SetCompare(QEI_ID_e eId, QEI_COUNTER_e eCounter, QEI_CMP_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    QEI_Type *ptQei;

    if((uint32_t)eId >= QEI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptQei = PRV_QEI_GetReg(eId);

    switch(eCounter)
    {
        case QEI_COUNTER_POSITION:
            SET_QEI_IER_POS_CMPX_EN(ptQei, ptCfg->un8Num, ptCfg->bIntrEnable);
            SET_QEI_DR_POS_CMPX(ptQei, ptCfg->un8Num, ptCfg->un32Compare);
            break;
        case QEI_COUNTER_INDEX:
            SET_QEI_IER_IDX_CMP_EN(ptQei, ptCfg->bIntrEnable);
            SET_QEI_DR_IDX_CMP(ptQei, ptCfg->un32Compare);
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    return eErr;

}

HAL_ERR_e HAL_QEI_Start(QEI_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    QEI_Type *ptQei;
    QEI_CTRL_BLK_t *ptQcb;

    if((uint32_t)eId >= QEI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptQei = PRV_QEI_GetReg(eId);
    ptQcb = &s_tQcb[(uint32_t)eId];

    /* Position counter clear before start */
    SET_QEI_DR_POS_CNTER(ptQei, 0);

    /* Index counter clear before start */
    SET_QEI_DR_IDX_CNTER(ptQei, 0);

    SET_QEI_CR_EN(ptQei, true);
 
    if(ptQcb->bVelEnable == true)
    {
        SET_QEI_CR_VELOCITY_EN(ptQei, true);
    }

    return eErr;
}

HAL_ERR_e HAL_QEI_Stop(QEI_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    QEI_Type *ptQei;
    QEI_CTRL_BLK_t *ptQcb;

    if((uint32_t)eId >= QEI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptQei = PRV_QEI_GetReg(eId);
    ptQcb = &s_tQcb[(uint32_t)eId];

    SET_QEI_CR_EN(ptQei, false);

    if(ptQcb->bVelEnable == true)
    {
        SET_QEI_CR_VELOCITY_EN(ptQei, false);
    }

    return eErr;
}

HAL_ERR_e HAL_QEI_GetCount(QEI_ID_e eId, QEI_COUNTER_e eCounter, uint32_t *pun32Count)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    QEI_Type *ptQei;

    if((uint32_t)eId >= QEI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptQei = PRV_QEI_GetReg(eId);

    switch(eCounter)
    {
        case QEI_COUNTER_POSITION:
            *pun32Count = GET_QEI_DR_POS_CNTER(ptQei);
            break;
        case QEI_COUNTER_INDEX:
            *pun32Count = GET_QEI_DR_IDX_CNTER(ptQei);
            break;
        case QEI_COUNTER_VELOCITY:
            *pun32Count = GET_QEI_DR_VEL_CAP(ptQei);
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    return eErr;
}

HAL_ERR_e HAL_QEI_GetDirection(QEI_ID_e eId, QEI_DIR_e *peDir)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    QEI_Type *ptQei;

    if((uint32_t)eId >= QEI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptQei = PRV_QEI_GetReg(eId);

    *peDir = (QEI_DIR_e)GET_QEI_SR_DIRECTION(ptQei);

    return eErr;
}

static void PRV_QEI_IRQHandler(QEI_ID_e eId)
{
    QEI_Type *ptQei;
    QEI_CTRL_BLK_t *ptQcb;
    uint32_t un32Event = 0;

    ptQei = PRV_QEI_GetReg(eId);
    ptQcb = &s_tQcb[eId];

    un32Event = GET_QEI_IER_FLAG(ptQei);
    SET_QEI_IER_CLEAR(ptQei, un32Event);

    if(ptQcb->pfnHandler != NULL && un32Event)
    {
        ptQcb->pfnHandler(un32Event, ptQcb->pContext);
    }
}

void QEI0_IRQHandler(void)
{
    PRV_QEI_IRQHandler(QEI_ID_0);
}

void QEI1_IRQHandler(void)
{
    PRV_QEI_IRQHandler(QEI_ID_1);
}

void QEI2_IRQHandler(void)
{
    PRV_QEI_IRQHandler(QEI_ID_2);
}

void QEI3_IRQHandler(void)
{
    PRV_QEI_IRQHandler(QEI_ID_3);
}

#endif /* _QEI */
