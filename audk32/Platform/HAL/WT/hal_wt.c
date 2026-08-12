/**
 *******************************************************************************
 * @file        hal_wt.c
 * @author      ABOV R&D Division
 * @brief       Watch Timer
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

#if defined(_WT)
#include "hal_wt.h"
#include "hal_wt_prv.h"

typedef struct
{
    WT_OPS_e               eOps;
    pfnWT_IRQ_Handler_t    pfnHandler;
    void                   *pContext;
} WT_CTRL_BLK_t;

static WT_CTRL_BLK_t s_tWcb[WT_CH_NUM];

static WT_Type *PRV_WT_GetReg(WT_ID_e eId)
{
    return WT_GetReg((P_WT_ID_e)eId);
}

static HAL_ERR_e PRV_WT_SetScuEnable(P_WT_ID_e eId, bool bEnable)
{
    return WT_SetScuEnable((P_WT_ID_e)eId, bEnable);
}

HAL_ERR_e HAL_WT_Init(WT_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= WT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_WT_SetScuEnable((P_WT_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tWcb[(uint32_t)eId], 0x00, sizeof(WT_CTRL_BLK_t));

    return eErr;
}

HAL_ERR_e HAL_WT_Uninit(WT_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= WT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_WT_SetScuEnable((P_WT_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = WT_GetIRQNum((P_WT_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tWcb[(uint32_t)eId], 0, sizeof(WT_CTRL_BLK_t));

    return eErr;
}

HAL_ERR_e HAL_WT_SetClkConfig(WT_ID_e eId, WT_CLK_CFG_t *ptClkCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= WT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = WT_SetClk((P_WT_ID_e)eId, (P_WT_CLK_e)ptClkCfg->eClk, (P_WT_CLK_MCCR_e)ptClkCfg->eMccr, ptClkCfg->un8MccrDiv);

    return eErr;
}

HAL_ERR_e HAL_WT_SetConfig(WT_ID_e eId, WT_CFG_t *ptCfg)
{
    WT_Type *ptWt;

    if((uint32_t)eId >= WT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptWt = PRV_WT_GetReg(eId);

    SET_WT_CR_INTV(ptWt, ptCfg->eIntv);
    SET_WT_IER_EN(ptWt, ptCfg->bIntrEnable);
    SET_WT_DR_MATCH_CNT(ptWt, ptCfg->un16MatchCnt);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_WT_SetIRQ(WT_ID_e eId, WT_OPS_e eOps, pfnWT_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio)
{
    WT_CTRL_BLK_t *ptWcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= WT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptWcb = &s_tWcb[(uint32_t)eId];
    eIrq = WT_GetIRQNum((P_WT_ID_e)eId);

    switch(eOps)
    {
        case WT_OPS_INTR:
#if defined(WT_FEATURE_IRQ_UNMASK_ENABLE)
            PRV_WT_SetIntrUnMask(eIrq, true);
#endif
            ptWcb->pfnHandler = pfnHandler;
            ptWcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            break;
        case WT_OPS_POLL:
        default:
#if defined(WT_FEATURE_IRQ_UNMASK_ENABLE)
            PRV_WT_SetIntrUnMask(eIrq, false);
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptWcb->pContext = NULL;
            ptWcb->pfnHandler = NULL;
            break;
    }

    ptWcb->eOps = eOps;

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_WT_Start(WT_ID_e eId)
{
    WT_Type *ptWt;

    if((uint32_t)eId >= WT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptWt = PRV_WT_GetReg(eId);
    SET_WT_CR_EN(ptWt, true);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_WT_Stop(WT_ID_e eId)
{
    WT_Type *ptWt;

    if((uint32_t)eId >= WT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptWt = PRV_WT_GetReg(eId);
    SET_WT_CR_EN(ptWt, false);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_WT_GetEvent(WT_ID_e eId, bool *pbEvt)
{
    WT_Type *ptWt;

    if((uint32_t)eId >= WT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptWt = PRV_WT_GetReg(eId);

    if(GET_WT_IER_FLAG(ptWt))
    {
        *pbEvt = true;
        SET_WT_IER_FLAG(ptWt, true);
    }
    else
    {
        *pbEvt = false;
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_WT_SetWakeupSrc(WT_ID_e eId, bool bEnable)
{
    (void)eId;
    WT_SetWkupSrc(bEnable);
    return HAL_ERR_OK;
}

void PRV_WT_IRQHandler(WT_ID_e eId)
{
    WT_Type *ptWt;
    WT_CTRL_BLK_t *ptWcb;
    WT_Context_t *ptContext;
    uint32_t un32Event = 0;

    ptWt = PRV_WT_GetReg(eId);
    ptWcb = &s_tWcb[(uint32_t)eId];
    
    if(ptWcb->pContext != NULL)
    {
        ptContext = (WT_Context_t *)ptWcb->pContext;
        WT_GetWkupEvent(&ptContext->bWakeup);
    }

    if(GET_WT_IER_FLAG(ptWt))
    {
        un32Event |= WT_EVENT_MATCH;
        SET_WT_IER_FLAG(ptWt, true);
    }

    if(ptWcb->pfnHandler && un32Event != 0)
    {
        ptWcb->pfnHandler(un32Event, ptWcb->pContext);
    }
}

void WT0_IRQHandler(void)
{
    PRV_WT_IRQHandler(WT_ID_0);
}

void WT1_IRQHandler(void)
{
    PRV_WT_IRQHandler(WT_ID_1);
}

#endif /* _WT */
