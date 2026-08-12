/**
 *******************************************************************************
 * @file        hpl_nmi.c
 * @author      ABOV R&D Division
 * @brief       Direct Memory Access
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

#if defined(_NMI)
#include "hpl_nmi.h"
#include "hpl_nmi_prv.h"

typedef struct
{
    bool                    bEnable;
    pfnNMI_IRQ_Handler_t    pfnHandler;
    void                    *pContext;
} NMI_RES_BLK_t;

static NMI_RES_BLK_t s_tNrb[NMI_INTR_MAX];

HAL_ERR_e PRV_NMI_SetEnable(NMI_INTR_e eNmi, bool bEnable)
{
    return NMI_SetEnable((P_NMI_INTR_e)eNmi, bEnable);
}

HAL_ERR_e HPL_NMI_SetIRQ(NMI_INTR_e eNmi, pfnNMI_IRQ_Handler_t pfnHandler, void *pContext, bool bEnable)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    NMI_RES_BLK_t *ptNrb;

    ptNrb = &s_tNrb[(uint8_t)eNmi];
    ptNrb->bEnable = bEnable;

    eErr = PRV_NMI_SetEnable(eNmi, ptNrb->bEnable);
    if(eErr == HAL_ERR_OK)
    {
        if(ptNrb->bEnable == true)
        {
            ptNrb->pfnHandler = pfnHandler;
            ptNrb->pContext = pContext;
        }
        else
        {
            ptNrb->pfnHandler = NULL;
            ptNrb->pContext = NULL;
        }
    }

    return eErr;
}

HAL_ERR_e HPL_NMI_SetEnable(NMI_INTR_e eNmi, bool bEnable)
{
    return NMI_SetEnable((P_NMI_INTR_e)eNmi, bEnable);
}

HAL_ERR_e HPL_NMI_SetSource(IRQn_Type eIrq, pfnNMI_IRQ_Handler_t pfnHandler, void *pContext, bool bEnable)
{
#if defined(CONFIG_NMI_ANY_INTERRUPT)
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type*)SCU_REG_BASE;
    NMI_RES_BLK_t *ptNrb;

    ptNrb = &s_tNrb[NMI_MAX_NUM-1];

    SET_SCU_NMI_EN(ptScu, bEnable);

    ptNrb->bEnable = bEnable;

    if(ptNrb->bEnable == true)
    {
        SET_SCU_NMI_SRC(ptScu, (uint8_t)eIrq);
        ptNrb->pfnHandler = pfnHandler;
        ptNrb->pContext = pContext;
    }
    else
    {
        SET_SCU_NMI_SRC(ptScu, 0);
        ptNrb->pfnHandler = NULL;
        ptNrb->pContext = NULL;
    }

    return eErr;
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

static void PRV_NMI_IRQHandler(void)
{
    SCU_Type *ptScu = (SCU_Type*)SCU_REG_BASE;
    uint32_t un32Status = 0;
    int32_t n32Cnt = 0;

    un32Status = GET_SCU_NMI_STATUS(ptScu);
#if defined(SCUNMI_FEATURE_CLEAR_STATUS)
    SET_SCU_NMI_STATUS(ptScu, un32Status);
#endif

    for(n32Cnt = 0; n32Cnt < NMI_MAX_NUM; n32Cnt++)
    {
        if(s_tNrb[n32Cnt].bEnable == true 
           && (un32Status & BIT(n32Cnt))
           && s_tNrb[n32Cnt].pfnHandler != NULL)
        {
            s_tNrb[n32Cnt].pfnHandler(true, s_tNrb[n32Cnt].pContext);
        }
    }

#if defined(CONFIG_NMI_ANY_INTERRUPT)
    if(s_tNrb[NMI_MAX_NUM-1].bEnable == true
       && (un32Status & SCU_NMI_SRC_SR_BIT))
    {
        s_tNrb[NMI_MAX_NUM-1].pfnHandler(true, s_tNrb[NMI_MAX_NUM-1].pContext);
    }
#endif
}

void NMI_IRQHandler(void)
{
    PRV_NMI_IRQHandler();
}

#endif /* _NMI */
