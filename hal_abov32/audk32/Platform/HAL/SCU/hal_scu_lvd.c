/**
 *******************************************************************************
 * @file        hal_scu_lvd.c
 * @author      ABOV R&D Division 
 * @brief       LVD sub system in System Control Unit
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

#if defined(_SCU_LVD)
#include "hal_scu.h"
#include "hal_scu_lvd.h"
#include "hal_scu_prv.h"
#if defined(_NMI)
#include "hpl_nmi.h"
#endif

typedef struct
{
    bool                           bNonMask;
    pfnSCULVD_IND_IRQ_Handler_t    pfnHandler;
    void                           *pContext;
} SCULVD_CTRL_BLK_t;

static SCULVD_CTRL_BLK_t s_tLcb;

HAL_ERR_e HAL_SCU_LVD_SetIRQIndicator(pfnSCULVD_IND_IRQ_Handler_t pfnHandler, void *pContext, uint32_t un32IRQPrio, SCULVD_IND_INTR_e eIntr)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCULV_Type *ptSculv = (SCULV_Type *)SCULV_REG_BASE;
    bool bEnable = false;

    switch(eIntr)
    {
        case SCULVD_IND_INTR_NONE:
#if defined(SCU_FEATURE_IRQ_UNMASK_ENABLE)
            SCU_SetIntrUnMask(SCULVD_IRQ, false);
#endif
            s_tLcb.pfnHandler = NULL;
            s_tLcb.pContext = NULL; 
            NVIC_ClearPendingIRQ(SCULVD_IRQ);
            NVIC_DisableIRQ(SCULVD_IRQ);
            s_tLcb.bNonMask = false;
            break;
        case SCULVD_IND_INTR_MASK:
#if defined(SCU_FEATURE_IRQ_UNMASK_ENABLE)
            SCU_SetIntrUnMask(SCULVD_IRQ, true);
#endif
            NVIC_ClearPendingIRQ(SCULVD_IRQ);
            NVIC_SetPriority(SCULVD_IRQ, un32IRQPrio);
            NVIC_EnableIRQ(SCULVD_IRQ);
            s_tLcb.pfnHandler = pfnHandler;
            s_tLcb.pContext = pContext; 
            s_tLcb.bNonMask = false;
            bEnable = true;
            break;
        case SCULVD_IND_INTR_NON_MASK:
#if defined(SCU_FEATURE_IRQ_UNMASK_ENABLE)
            SCU_SetIntrUnMask(SCULVD_IRQ, false);
#endif
            s_tLcb.bNonMask = true;
            s_tLcb.pfnHandler = NULL;
            s_tLcb.pContext = NULL; 
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

#if defined(_NMI)
    eErr = HPL_NMI_SetIRQ(NMI_INTR_LVD, (pfnNMI_IRQ_Handler_t)pfnHandler, pContext, s_tLcb.bNonMask);
    if(eErr != HAL_ERR_OK)
    {
         return eErr;
    }
#endif

    SET_SCU_LVD_IND_INTR_EN(ptSculv, bEnable);

    return eErr;
}

HAL_ERR_e HAL_SCU_LVD_SetIndicatorEnable(SCULVD_IND_LVL_e eLevel, bool bEnable)
{
    SCULV_Type *ptSculv = (SCULV_Type *)SCULV_REG_BASE;

#if defined(SCU_FEATURE_LVI_CLOCK_ENABLE)
    SCULVD_SetScuEnable(bEnable);
#endif

    SET_SCU_LVD_IND_SEL(ptSculv, (uint32_t)eLevel);
    SET_SCU_LVD_IND_EN(ptSculv, bEnable);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_SCU_LVD_SetIndicatorAlwalysOn(bool bEnable)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
#if defined(SCU_FEATURE_LVI_ALWAYS_ON)
    SCULV_Type *ptSculv = (SCULV_Type *)SCULV_REG_BASE;
    SET_SCU_LVD_IND_AON(ptSculv, bEnable);
#else
    (void)bEnable;
    eErr = HAL_ERR_NOT_SUPPORTED;
#endif
    return eErr;
}

HAL_ERR_e HAL_SCU_LVD_SetResetEnable(SCULVD_RST_LVL_e eLevel, bool bEnable, bool bPowerDown)
{
    SCULV_Type *ptSculv = (SCULV_Type *)SCULV_REG_BASE;
    SCUCONF_Type *ptScuConf = (SCUCONF_Type *)SCUCONF_REG_BASE;

    SET_SCU_LVD_RST_SEL(ptScuConf, (uint32_t)eLevel);

    if(bEnable)
    {
        SET_SCU_LVD_RST_ENM(ptScuConf, SCULVD_RST_OP_LVREN);
        SET_SCU_LVD_RST_EN(ptSculv, SCULVD_RST_EN);
    }
    else
    {
        SET_SCU_LVD_RST_ENM(ptScuConf, SCULVD_RST_OP_MASTER);
        SET_SCU_LVD_RST_EN(ptSculv, SCULVD_RST_DIS);
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_SCU_LVD_SetResetAlwaysOn(bool bEnable)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
#if defined(SCU_FEATURE_LVR_ALWAYS_ON)
    SCULV_Type *ptSculv = (SCULV_Type *)SCULV_REG_BASE;
    SET_SCU_LVD_RST_AON(ptSculv, bEnable);
#else
    (void)bEnable;
    eErr = HAL_ERR_NOT_SUPPORTED;
#endif
    return eErr;
}

HAL_ERR_e HAL_SCU_LVD_SetWakeupSrc(bool bEnable)
{
    SCULVD_SetWkupSrc(bEnable);
    return HAL_ERR_OK;
}

HAL_ERR_e HAL_SCU_LVD_SetResetSrc(bool bEnable)
{
    SCULVD_SetResetSrc(bEnable);
    return HAL_ERR_OK;
}

HAL_ERR_e HAL_SCU_LVD_GetResetSrcEvent(bool *pbEvent)
{
    SCULVD_GetResetSrcEvent(pbEvent);
    return HAL_ERR_OK;
}

void PRV_SCU_LVD_IRQHandler(void)
{ 
    SCULVD_Context_t *ptContext;
    SCULV_Type *ptSculv = (SCULV_Type *)SCULV_REG_BASE;
    uint32_t un32Event = SCULVD_IND_EVENT_MASK;
    
    if(s_tLcb.pContext != NULL)
    {
        ptContext = (SCULVD_Context_t *)s_tLcb.pContext;
        SCULVD_GetWkupEvent(&ptContext->bWakeup);
    }

    SET_SCU_LVD_IND_INTR_FLAG(ptSculv, true);

    if(s_tLcb.pfnHandler != NULL)
    {
        s_tLcb.pfnHandler(un32Event,s_tLcb.pContext);
    }
}

void SCULVD_IRQHandler(void)
{
    PRV_SCU_LVD_IRQHandler();
}

#endif /* _SCU_LVD */
