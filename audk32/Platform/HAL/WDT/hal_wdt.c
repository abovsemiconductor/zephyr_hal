/**
 *******************************************************************************
 * @file        hal_wdt.c
 * @author      ABOV R&D Division
 * @brief       Watch Dog Timer
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

#if defined(_WDT)
#include "hal_wdt.h"
#include "hal_wdt_prv.h"

#include "hll_wdt.h"

#if defined(_NMI) && defined(WDT_FEATURE_NMI)
#include "hpl_nmi.h"
#endif

typedef struct
{
    WDT_OPS_e               eOps;
    pfnWDT_IRQ_Handler_t    pfnHandler;
    void                    *pContext;

    uint8_t                 un8Mode;
    uint8_t                 un8IntrEnable;
    uint32_t                un32InitCnt;
} WDT_CTRL_BLK_t;

static WDT_CTRL_BLK_t s_tWcb[WDT_CH_NUM];

static void PRV_WDT_IRQHandler(WDT_ID_e eId);

#if defined(_NMI) && defined(WDT_FEATURE_NMI)
static void PRV_WDT_NMIHandler(uint32_t un32Event, void *pContext)
{
    /* Need to get Id */
    PRV_WDT_IRQHandler(WDT_ID_0);
}
#endif

#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
static WDT_Type *PRV_WDT_GetReg(WDT_ID_e eId)
{
    return WDT_GetReg((P_WDT_ID_e)eId);
}
#endif

HAL_ERR_e HAL_WDT_Init(WDT_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= WDT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    memset(&s_tWcb[(uint32_t)eId], 0x00, sizeof(WDT_CTRL_BLK_t));

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_WDT_SetAccessEnable(eId, true);
#else
    {
        WDT_Type *ptWdt = PRV_WDT_GetReg(eId);

        SET_WDT_ACCESS_EN(ptWdt, true);
    }
#endif

    return eErr;
}

HAL_ERR_e HAL_WDT_Uninit(WDT_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_WDT_SetAccessEnable(eId, false);
    eIrq = HLL_WDT_GetIRQNum(eId);
#else
    {
        WDT_Type *ptWdt = PRV_WDT_GetReg(eId);

        SET_WDT_ACCESS_EN(ptWdt, false);
    }

    eIrq = WDT_GetIRQNum((P_WDT_ID_e)eId);
#endif

    /* Forcily, disable NVIC Interrupt */
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    /* clear local context by id */
    memset(&s_tWcb[(uint32_t)eId], 0x00, sizeof(WDT_CTRL_BLK_t));

    return eErr;
}

HAL_ERR_e HAL_WDT_SetClkConfig(WDT_ID_e eId, WDT_CLK_CFG_t *ptClkCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= WDT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    eErr = HLL_WDT_SetClkSource(eId, ptClkCfg->eClk, ptClkCfg->eMccr, ptClkCfg->un8MccrDiv);

    HLL_WDT_SetClkPreDiv(eId, ptClkCfg->ePreDiv);
#else
    eErr = WDT_SetClk((P_WDT_ID_e)eId, (P_WDT_CLK_e)ptClkCfg->eClk, (P_WDT_CLK_MCCR_e)ptClkCfg->eMccr, ptClkCfg->un8MccrDiv);

    {
        WDT_Type *ptWdt = PRV_WDT_GetReg(eId);

        SET_WDT_CR_CLK_PREDIV(ptWdt, WDT_CLK_PREDIV_MODE(ptClkCfg->ePreDiv));
    }
#endif

    return eErr;
}

HAL_ERR_e HAL_WDT_SetConfig(WDT_ID_e eId, WDT_CFG_t *ptCfg)
{
#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    WDT_Type *ptWdt;
#endif
    WDT_CTRL_BLK_t *ptWcb;
    bool bEnable = false;

    if((uint32_t)eId >= WDT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    ptWdt = PRV_WDT_GetReg(eId);
#endif
    ptWcb = &s_tWcb[(uint32_t)eId];

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_WDT_SetWriteEnable(eId);
#else
    SET_WDT_ACCESS_KEY(ptWdt, WDT_WRITE_ACCESS_EN);
#endif

    ptWcb->un8Mode = ptCfg->un8Mode;

    ptWcb->un8IntrEnable = ptCfg->un8IntrEnable;
    if(ptCfg->un8IntrEnable & WDT_INTR_MATCH)
    {
        bEnable = true;
    }
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_WDT_SetMatchIntrEnable(eId, bEnable);
#else
    SET_WDT_IER_MATCH_EN(ptWdt, bEnable);
#endif

    bEnable = false;
    if(ptCfg->un8IntrEnable & WDT_INTR_UNDERFLOW)
    {
        bEnable = true;
    }
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_WDT_SetUnderflowIntrEnable(eId, bEnable);
#else
    SET_WDT_IER_UDF_EN(ptWdt, bEnable);
#endif

    bEnable = false;
    if(ptCfg->un8Mode & WDT_MODE_RST)
    {
        bEnable = true;
    }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_WDT_SetResetEnable(bEnable);
#else
    WDT_SetResetEnable(bEnable);
#endif

    ptWcb->un32InitCnt = ptCfg->un32InitCnt;

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_WDT_SetLoadValue(eId, ptWcb->un32InitCnt);
    HLL_WDT_Reload(eId, ptWcb->un32InitCnt);
#else
    SET_WDT_DR_LOAD(ptWdt, ptWcb->un32InitCnt);

    SET_WDT_DR_RELOAD(ptWdt, ptWcb->un32InitCnt);
#endif

#if defined(WDT_FEATURE_RELOAD_COUNT_WITH_WINDR)
    /* Check Counter value is updated */
    while(1)
    {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
        if(ptWcb->un32InitCnt == HLL_WDT_GetCount(eId))
#else
        if(ptWcb->un32InitCnt == GET_WDT_DR_CNT(ptWdt))
#endif
        {
            break;
        }
    }

    /* After then, write match(window) counter value  */
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_WDT_SetMatchValue(eId, ptCfg->un32MatchCnt);
#else
    SET_WDT_DR_MATCH(ptWdt, ptCfg->un32MatchCnt);
#endif
#endif

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_WDT_SetWriteDisable(eId);
#else
    SET_WDT_ACCESS_KEY(ptWdt, WDT_WRITE_ACCESS_DIS);
#endif

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_WDT_SetIRQ(WDT_ID_e eId, WDT_OPS_e eOps, pfnWDT_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio, bool bNonMask)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    WDT_CTRL_BLK_t *ptWcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= WDT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptWcb = &s_tWcb[(uint32_t)eId];

    /*
     * NVIC setup is always performed here regardless of HLL support: only
     * the IRQ-number lookup below switches implementation.
     */
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    eIrq = HLL_WDT_GetIRQNum(eId);
#else
    eIrq = WDT_GetIRQNum((P_WDT_ID_e)eId);
#endif

    switch(eOps)
    {
        case WDT_OPS_INTR:
#if defined(WDT_FEATURE_IRQ_UNMASK_ENABLE)
            PRV_WDT_SetIntrUnMask(eIrq, true);
#endif
#if defined(_NMI) && defined(WDT_FEATURE_NMI)
            eErr = HPL_NMI_SetIRQ(NMI_INTR_WDT, &PRV_WDT_NMIHandler, NULL, bNonMask);
            if(bNonMask == false)
            {
#endif
                NVIC_ClearPendingIRQ(eIrq);
                NVIC_SetPriority(eIrq, un32IRQPrio);
                NVIC_EnableIRQ(eIrq);
#if defined(_NMI) && defined(WDT_FEATURE_NMI)
            }
#endif
            ptWcb->pfnHandler = pfnHandler;
            ptWcb->pContext = pContext;
            break;
        case WDT_OPS_POLL:
        default:
#if defined(WDT_FEATURE_IRQ_UNMASK_ENABLE)
            PRV_WDT_SetIntrUnMask(eIrq, false);
#endif
#if defined(_NMI) && defined(WDT_FEATURE_NMI)
            eErr = HPL_NMI_SetIRQ(NMI_INTR_WDT, NULL, NULL, false);
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptWcb->pContext = NULL;
            ptWcb->pfnHandler = NULL;
            break;
    }

    ptWcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_WDT_Start(WDT_ID_e eId)
{
#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    WDT_Type *ptWdt;
#endif
    WDT_CTRL_BLK_t *ptWcb;

    if((uint32_t)eId >= WDT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    ptWdt = PRV_WDT_GetReg(eId);
#endif
    ptWcb = &s_tWcb[(uint32_t)eId];

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_WDT_SetWriteEnable(eId);

    if(ptWcb->un8Mode & WDT_MODE_RST)
    {
        HLL_WDT_SetRstEnable(eId, true);
    }

    HLL_WDT_SetCountEnable(eId, true);

    HLL_WDT_SetWriteDisable(eId);
#else
    SET_WDT_ACCESS_KEY(ptWdt, WDT_WRITE_ACCESS_EN);

    if(ptWcb->un8Mode & WDT_MODE_RST)
    {
        SET_WDT_CR_RST_EN(ptWdt, true);
    }

    SET_WDT_CR_CNT_EN(ptWdt, true);

    SET_WDT_ACCESS_KEY(ptWdt, WDT_WRITE_ACCESS_DIS);
#endif

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_WDT_Stop(WDT_ID_e eId)
{
#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    WDT_Type *ptWdt;
#endif
    WDT_CTRL_BLK_t *ptWcb;

    if((uint32_t)eId >= WDT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    ptWdt = PRV_WDT_GetReg(eId);
#endif
    ptWcb = &s_tWcb[(uint32_t)eId];

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_WDT_SetWriteEnable(eId);

    HLL_WDT_SetCountEnable(eId, WDT_CNT_STOP);

    if(ptWcb->un8Mode & WDT_MODE_RST)
    {
        HLL_WDT_SetRstEnable(eId, WDT_RST_STOP);
    }

    HLL_WDT_SetWriteDisable(eId);
#else
    SET_WDT_ACCESS_KEY(ptWdt, WDT_WRITE_ACCESS_EN);

    SET_WDT_CR_CNT_EN(ptWdt, WDT_CNT_STOP);

    if(ptWcb->un8Mode & WDT_MODE_RST)
    {
        SET_WDT_CR_RST_EN(ptWdt, WDT_RST_STOP);
    }

    SET_WDT_ACCESS_KEY(ptWdt, WDT_WRITE_ACCESS_DIS);
#endif

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_WDT_GetCount(WDT_ID_e eId, uint32_t *pun32Count)
{
    if((uint32_t)eId >= WDT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_WDT_SetWriteEnable(eId);

    *pun32Count = HLL_WDT_GetCount(eId);

    HLL_WDT_SetWriteDisable(eId);
#else
    {
        WDT_Type *ptWdt = PRV_WDT_GetReg(eId);

        SET_WDT_ACCESS_KEY(ptWdt, WDT_WRITE_ACCESS_EN);

        *pun32Count = GET_WDT_DR_CNT(ptWdt);

        SET_WDT_ACCESS_KEY(ptWdt, WDT_WRITE_ACCESS_DIS);
    }
#endif

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_WDT_SetReload(WDT_ID_e eId, uint32_t un32Data)
{
    if((uint32_t)eId > WDT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if defined(WDT_FEATURE_RELOAD_COUNT_WITH_WINDR)
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    /* Get match(window) counter value */
    uint32_t un32Cnt = HLL_WDT_GetMatchValue(eId);

    while(1)
    {
        /* check counter value is equal or less then match(window) counter */
        if(HLL_WDT_GetCount(eId) <= un32Cnt)
        {
            break;
        }
    }
#else
    WDT_Type *ptWdt = PRV_WDT_GetReg(eId);
    /* Get match(window) counter value */
    uint32_t un32Cnt = GET_WDT_DR_MATCH(ptWdt);

    while(1)
    {
        /* check counter value is equal or less then match(window) counter */
        if(GET_WDT_DR_CNT(ptWdt) <= un32Cnt)
        {
            break;
        }
    }
#endif
#endif

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_WDT_Reload(eId, un32Data);
#else
    {
#if !defined(WDT_FEATURE_RELOAD_COUNT_WITH_WINDR)
        WDT_Type *ptWdt = PRV_WDT_GetReg(eId);
#endif
        SET_WDT_DR_RELOAD(ptWdt, un32Data);
    }
#endif

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_WDT_SetWakeupSrc(WDT_ID_e eId, bool bEnable)
{
    (void)eId;

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_WDT_SetWakeupSrc(bEnable);
#else
    WDT_SetWkupSrc(bEnable);
#endif

    return HAL_ERR_OK;
}

static void PRV_WDT_IRQHandler(WDT_ID_e eId)
{
#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    WDT_Type *ptWdt;
#endif
    WDT_CTRL_BLK_t *ptWcb;
    WDT_Context_t *ptContext;
    uint32_t un32Event = 0;

#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    ptWdt = PRV_WDT_GetReg(eId);
#endif
    ptWcb = &s_tWcb[(uint32_t)eId];

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_WDT_SetWriteEnable(eId);
#else
    SET_WDT_ACCESS_KEY(ptWdt, WDT_WRITE_ACCESS_EN);
#endif

    if(ptWcb->pContext != NULL)
    {
        ptContext = (WDT_Context_t *)ptWcb->pContext;
        ptContext->un8Mode = ptWcb->un8Mode;
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
        HLL_WDT_GetWakeupEvent(&ptContext->bWakeup);
#else
        WDT_GetWkupEvent(&ptContext->bWakeup);
#endif
    }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    if(HLL_WDT_GetUnderflowFlag(eId))
    {
        un32Event |= WDT_EVENT_UNDERFLOW;
        HLL_WDT_ClearUnderflowFlag(eId);
    }

    if(HLL_WDT_GetMatchFlag(eId))
    {
        un32Event |= WDT_EVENT_MATCH;
        HLL_WDT_ClearMatchFlag(eId);
    }

    HLL_WDT_SetWriteDisable(eId);
#else
    if(GET_WDT_IER_UDF_FLAG(ptWdt))
    {
        un32Event |= WDT_EVENT_UNDERFLOW;
        SET_WDT_IER_UDF_FLAG(ptWdt, true);
    }

    if(GET_WDT_IER_MATCH_FLAG(ptWdt))
    {
        un32Event |= WDT_EVENT_MATCH;
        SET_WDT_IER_MATCH_FLAG(ptWdt, true);
    }

    SET_WDT_ACCESS_KEY(ptWdt, WDT_WRITE_ACCESS_DIS);
#endif

    if(ptWcb->pfnHandler && un32Event != 0)
    {
        ptWcb->pfnHandler(un32Event, ptWcb->pContext);
    }
}

void WDT0_IRQHandler(void)
{
    PRV_WDT_IRQHandler(WDT_ID_0);
}

void WDT1_IRQHandler(void)
{
    PRV_WDT_IRQHandler(WDT_ID_1);
}

#endif /* _WDT */
