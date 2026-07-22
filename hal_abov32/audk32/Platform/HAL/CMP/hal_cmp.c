/**
 *******************************************************************************
 * @file        hal_cmp.c
 * @author      ABOV R&D Division
 * @brief       Comparator
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

#if defined(_CMP)
#include "hal_cmp.h"
#include "hal_cmp_prv.h"

#if defined(_NMI)
#if (CONFIG_CMP_NMI_INTERRUPT == 1) || defined(CONFIG_NMI_ANY_INTERRUPT)
#include "hpl_nmi.h"
#endif
#endif

typedef struct
{
    CMP_OPS_e               eOps;

#if (CONFIG_CMP_OPS_INTERRUPT == 1)
    pfnCMP_IRQ_Handler_t    pfnHandler;
    void                    *pContext;
#endif

    CMP_INTR_TRG_e          eIntrTrg;

#if defined(_NMI) && ((CONFIG_CMP_NMI_INTERRUPT == 1) || defined(CONFIG_NMI_ANY_INTERRUPT))
    bool                    bNmiEnable;
#endif

} CMP_CTRL_BLK_t;

static CMP_CTRL_BLK_t s_tCcb[CMP_CH_NUM];

static void PRV_CMP_IRQHandler(CMP_ID_e eId);

#if defined(_NMI) && ((CONFIG_CMP_NMI_INTERRUPT == 1) || defined(CONFIG_NMI_ANY_INTERRUPT))
static void PRV_CMP_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < CMP_CH_NUM; i++)
    {
        if(s_tCcb[i].bNmiEnable == true)
        {
            PRV_CMP_IRQHandler((CMP_ID_e)i);
        }
    }
}
#endif

static CMP_Type *PRV_CMP_GetReg(P_CMP_ID_e eId)
{
    return CMP_GetReg((P_CMP_ID_e)eId);
}

static HAL_ERR_e PRV_CMP_SetScuEnable(P_CMP_ID_e eId, bool bEnable)
{
    return CMP_SetScuEnable((P_CMP_ID_e)eId, bEnable);
}

HAL_ERR_e HAL_CMP_Init(CMP_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= CMP_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_CMP_SetScuEnable((P_CMP_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tCcb[(uint32_t)eId], 0, sizeof(CMP_CTRL_BLK_t));

    return eErr;
}

HAL_ERR_e HAL_CMP_Uninit(CMP_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
#if (CONFIG_CMP_OPS_INTERRUPT == 1)
    IRQn_Type eIrq;
#endif

    if((uint32_t)eId >= CMP_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_CMP_SetScuEnable((P_CMP_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

#if (CONFIG_CMP_OPS_INTERRUPT == 1)
    /* Forcily, disable NVIC Interrupt */
    eIrq = CMP_GetIRQNum((P_CMP_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);
#endif

    memset(&s_tCcb[(uint32_t)eId], 0, sizeof(CMP_CTRL_BLK_t));

    return eErr;
}

HAL_ERR_e HAL_CMP_SetConfig(CMP_ID_e eId, CMP_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    CMP_Type *ptCmp;
    CMP_CTRL_BLK_t *ptCcb;

    if((uint32_t)eId >= CMP_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptCmp = PRV_CMP_GetReg((P_CMP_ID_e)eId);
    ptCcb = &s_tCcb[(uint32_t)eId];

    SET_CMP_CR_INPUT(ptCmp, eId, ptCfg->eInSrc);
    SET_CMP_CR_REF(ptCmp, eId, ptCfg->eRefSrc);

    SET_CMP_CR_HYSS(ptCmp, eId, ptCfg->eHyss);

#if (CONFIG_CMP_VER_MAJOR == 1)
    SET_CMP_CR_INTR_TRG(ptCmp, eId, ptCfg->eIntrTrg);
    SET_CMP_CR_INTR_POL(ptCmp, eId, ptCfg->bIntrPol);
#elif (CONFIG_CMP_VER_MAJOR == 2)
    SET_CMP_CR_INTR_TRG(ptCmp, eId, (uint8_t)ptCfg->eIntrTrg, (uint8_t)ptCfg->bIntrPol);
#endif
    ptCcb->eIntrTrg = ptCfg->eIntrTrg;

    SET_CMP_CR_TRG_POL(ptCmp, eId, ptCfg->bTrgOutPol);

    if(ptCfg->tDbc.bEnable == true)
    {
        SET_CMP_DR_DBNC_CLK_DIV(ptCmp, ptCfg->tDbc.un16ClkDiv);
        SET_CMP_DR_DBNC_SHIFT(ptCmp, eId, ptCfg->tDbc.un8Shift);
        SET_CMP_CR_DBNC_CLK(ptCmp, ptCfg->tDbc.bLSIClk);
    }
    else
    {
        SET_CMP_DR_DBNC_CLK_DIV(ptCmp, 0x0);
        SET_CMP_DR_DBNC_SHIFT(ptCmp, eId, 0x0);
    }

    /* extend configuration */
    SET_CMP_CR_WINDOW_EN(ptCmp, ptCfg->tExt.bWindowEn);
    SET_CMP_CR_INTREF_EN(ptCmp, ptCfg->tExt.bIntRefEn);
#if defined (CMP_FEATURE_INTERNAL_REFERENCE_VOLTAGE_LEVEL)
    SET_CMP_CR_INTREF_VOL_LVL(ptCmp, ptCfg->tExt.un8IntRefVLvl);
#endif
    SET_CMP_CR_PWR(ptCmp, eId, ptCfg->tExt.ePwr);

    return eErr;
}

HAL_ERR_e HAL_CMP_SetIRQ(CMP_ID_e eId, CMP_OPS_e eOps, pfnCMP_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio, bool bNonMask)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    CMP_CTRL_BLK_t *ptCcb;
#if (CONFIG_CMP_OPS_INTERRUPT == 1)
    IRQn_Type eIrq;
#endif

    if((uint32_t)eId >= CMP_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(bNonMask == true)
    {
#if (CONFIG_CMP_OPS_INTERRUPT == 1)
#else
        return HAL_ERR_NOT_SUPPORTED;
#endif
    }

    ptCcb = &s_tCcb[(uint32_t)eId];
#if (CONFIG_CMP_OPS_INTERRUPT == 1)
    eIrq = CMP_GetIRQNum((P_CMP_ID_e)eId);
#endif

    switch(eOps)
    {
#if (CONFIG_CMP_OPS_INTERRUPT == 1)
        case CMP_OPS_INTR:
#if defined(CMP_FEATURE_IRQ_UNMASK_ENABLE)
            CMP_SetIntrUnMask(eIrq, true);
#endif
#if defined(_NMI)
#if (CONFIG_CMP_NMI_INTERRUPT == 1)
            eErr = HPL_NMI_SetIRQ(NMI_INTR_CMP, NULL, NULL, false);
#endif
#if defined (CONFIG_NMI_ANY_INTERRUPT)
            if(ptCcb->bNmiEnable == true)
            {
                (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
                ptCcb->bNmiEnable = false;
            }
#endif
#endif /* _NMI */

            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            ptCcb->pfnHandler = pfnHandler;
            ptCcb->pContext = pContext;
            break;
#endif /* CONFIG_CMP_OPS_INTERRUPT */

#if defined(_NMI)
        case CMP_OPS_NMI:
#if defined(CMP_FEATURE_IRQ_UNMASK_ENABLE)
            CMP_SetIntrUnMask(eIrq, true);
#endif
#if (CONFIG_CMP_NMI_INTERRUPT == 1)
            eErr = HPL_NMI_SetIRQ(NMI_INTR_CMP, &PRV_CMP_NMIHandler, NULL, true);
#endif
#if defined(CONFIG_NMI_ANY_INTERRUPT)
            eErr = HPL_NMI_SetSource(eIrq, &PRV_CMP_NMIHandler, pContext, true);
            ptCcb->bNmiEnable = true;
#endif
            if(eErr == HAL_ERR_OK)
            {
                ptCcb->pfnHandler = pfnHandler;
                ptCcb->pContext = pContext;
            }
            break;
#endif /* _NMI */
        case CMP_OPS_POLL:
        default:
#if defined(CMP_FEATURE_IRQ_UNMASK_ENABLE)
            CMP_SetIntrUnMask(eIrq, false);
#endif
#if (CONFIG_CMP_OPS_INTERRUPT == 1)
#if defined(_NMI)
#if (CONFIG_CMP_NMI_INTERRUPT == 1)
            eErr = HPL_NMI_SetIRQ(NMI_INTR_CMP, NULL, NULL, false);
#endif
#if defined (CONFIG_NMI_ANY_INTERRUPT)
            if(ptCcb->bNmiEnable == true)
            {
                (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
                ptCcb->bNmiEnable = false;
            }
#endif
#endif /* _NMI */

            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptCcb->pContext = NULL;
            ptCcb->pfnHandler = NULL;
#endif
            break;
    }

    ptCcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_CMP_Start(CMP_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    CMP_Type *ptCmp;
    CMP_CTRL_BLK_t *ptCcb;

    if((uint32_t)eId >= CMP_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptCmp = CMP_GetReg((P_CMP_ID_e)eId);
    ptCcb = &s_tCcb[(uint32_t)eId];

#if defined(CMP_FEATURE_POST_ENABLE_INTERRUPT)
    SET_CMP_CR_EN(ptCmp, eId, true);
#endif

    SET_CMP_IER_FLAG_CLR(ptCmp, eId, true);

    if(ptCcb->eOps == CMP_OPS_INTR || ptCcb->eOps == CMP_OPS_NMI)
    {
        SET_CMP_IER_EN(ptCmp, eId, true);
    }

#if defined(CMP_FEATURE_POST_ENABLE_INTERRUPT)
#else
    SET_CMP_CR_EN(ptCmp, eId, true);
#endif

    return eErr;
}

HAL_ERR_e HAL_CMP_Stop(CMP_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    CMP_Type *ptCmp;
    CMP_CTRL_BLK_t *ptCcb;

    if((uint32_t)eId >= CMP_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptCmp = CMP_GetReg((P_CMP_ID_e)eId);
    ptCcb = &s_tCcb[(uint32_t)eId];

    if(ptCcb->eOps == CMP_OPS_INTR || ptCcb->eOps == CMP_OPS_NMI)
    {
        SET_CMP_IER_EN(ptCmp, eId, false);
    }

    SET_CMP_CR_EN(ptCmp, eId, false);

    return eErr;
}

HAL_ERR_e HAL_CMP_SetWaitComplete(CMP_ID_e eId, uint32_t un32Timeout)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    CMP_Type *ptCmp;

    if((uint32_t)eId >= CMP_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptCmp = CMP_GetReg((P_CMP_ID_e)eId);

    while(!GET_CMP_IER_FLAG(ptCmp, eId))
    {
        un32Timeout--;
        if(un32Timeout == 0)
        {
            eErr = HAL_ERR_TIMEOUT;
            break;
        }
    }

    SET_CMP_IER_FLAG_CLR(ptCmp, eId, true);

    return eErr;
}

HAL_ERR_e HAL_CMP_SetWakeupSrc(CMP_ID_e eId, bool bEnable)
{
    (void)eId;

    CMP_SetWkupSrc(bEnable); 
    return HAL_ERR_OK;
}

#if (CONFIG_CMP_OPS_INTERRUPT == 1)
static void PRV_CMP_IRQHandler(CMP_ID_e eId)
{
    CMP_Type *ptCmp;
    CMP_CTRL_BLK_t *ptCcb = NULL;
    uint32_t un32Status = 0;
    uint32_t un32Event = 0;
#if (CONFIG_CMP_VER_MAJOR == 1)
    CMP_Context_t *ptContext;
    bool bWakeupEvent = false;
#endif

#if (CONFIG_CMP_VER_MAJOR == 1)
    ptCmp = PRV_CMP_GetReg((P_CMP_ID_e)eId);

    CMP_GetWkupEvent(&bWakeupEvent);
    un32Status = GET_CMP_IER(ptCmp);
    if(un32Status & CMP_INTR_ASSERTED_C0)
    {
        ptCcb = &s_tCcb[(uint32_t)CMP_ID_0];
        SET_CMP_IER_FLAG_CLR(ptCmp, CMP_ID_0, true);
    }

    if(un32Status & CMP_INTR_ASSERTED_C1)
    {
         ptCcb = &s_tCcb[(uint32_t)CMP_ID_1];
         SET_CMP_IER_FLAG_CLR(ptCmp, CMP_ID_1, true);
    }

    if(ptCcb->pContext != NULL)
    {
        ptContext = (CMP_Context_t *)ptCcb->pContext;
        ptContext->bWakeup = bWakeupEvent;
    }

#elif (CONFIG_CMP_VER_MAJOR == 2)
    ptCmp = PRV_CMP_GetReg((P_CMP_ID_e)eId);
    ptCcb = &s_tCcb[(uint32_t)eId];

    un32Status = GET_CMP_IER(ptCmp, eId);
    if(un32Status & CMP_INTR_ASSERTED_C0)
    {
        SET_CMP_IER_FLAG_CLR(ptCmp, (P_CMP_ID_e)eId, true);
    }
#endif

    if(ptCcb != NULL)
    {
        switch(ptCcb->eIntrTrg)
        {
            case CMP_INTR_TRG_LEVEL:
                 un32Event = CMP_EVENT_LEVEL;
                 break;
            case CMP_INTR_TRG_RISING:
                 un32Event = CMP_EVENT_RISING;
                 break;
            case CMP_INTR_TRG_FALLING:
                 un32Event = CMP_EVENT_FALLING;
                 break;
            case CMP_INTR_TRG_BOTH_EDGE:
                 un32Event = CMP_EVENT_BOTH_EDGE;
                 break;
            default:
                 break;
        }

        if(ptCcb->pfnHandler != NULL && un32Event != 0)
        {
            ptCcb->pfnHandler(un32Event, ptCcb->pContext);
        }
    }
}

void CMP0_IRQHandler(void)
{
    PRV_CMP_IRQHandler(CMP_ID_0);
}

void CMP1_IRQHandler(void)
{
    PRV_CMP_IRQHandler(CMP_ID_1);
}

void CMP2_IRQHandler(void)
{
    PRV_CMP_IRQHandler(CMP_ID_2);
}

void CMP3_IRQHandler(void)
{
    PRV_CMP_IRQHandler(CMP_ID_3);
}
#endif /* CONFIG_CMP_OPS_INTERRUPT */

#endif /* _CMP */
