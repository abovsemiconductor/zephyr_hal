/**
 *******************************************************************************
 * @file        hal_vrefbuf.c
 * @author      ABOV R&D Division
 * @brief       Cyclic Redundancy Check
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

#if defined(_VREFBUF)
#include "hal_vrefbuf.h"
#include "hal_vrefbuf_prv.h"

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
#include "hpl_nmi.h"
#endif

typedef struct
{
    VREFBUF_OPS_e               eOps;
    pfnVREFBUF_IRQ_Handler_t    pfnHandler;
    void                    *pContext;

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
    bool                    bNmiEnable;
#endif
} VREFBUF_CTRL_BLK_t;

static VREFBUF_CTRL_BLK_t s_tVcb[VREFBUF_CH_NUM];

static void PRV_VREFBUF_IRQHandler(VREFBUF_ID_e eId);

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
static void PRV_VREFBUF_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < VREFBUF_CH_NUM; i++)
    {
        if(s_tVcb[i].bNmiEnable == true)
        {
            PRV_VREFBUF_IRQHandler((VREFBUF_ID_e)i);
        }
    }
}
#endif

static VREFBUF_Type *PRV_VREFBUF_GetReg(P_VREFBUF_ID_e eId)
{
    return VREFBUF_GetReg((P_VREFBUF_ID_e)eId);
}

static HAL_ERR_e PRV_VREFBUF_SetScuEnable(P_VREFBUF_ID_e eId, bool bEnable)
{
    return VREFBUF_SetScuEnable((P_VREFBUF_ID_e)eId, bEnable);
}

HAL_ERR_e HAL_VREFBUF_Init(VREFBUF_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= VREFBUF_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_VREFBUF_SetScuEnable((P_VREFBUF_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tVcb[(uint32_t)eId], 0x00, sizeof(VREFBUF_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_VREFBUF_Uninit(VREFBUF_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= VREFBUF_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_VREFBUF_SetScuEnable((P_VREFBUF_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tVcb[(uint32_t)eId], 0x00, sizeof(VREFBUF_CTRL_BLK_t));

    /* Forcily, disable NVIC Interrupt */
    eIrq = VREFBUF_GetIRQNum((P_VREFBUF_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_VREFBUF_SetConfig(VREFBUF_ID_e eId, VREFBUF_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    VREFBUF_Type *ptVRef;

    if((uint32_t)eId >= VREFBUF_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptVRef = PRV_VREFBUF_GetReg((P_VREFBUF_ID_e)eId);

    switch(ptCfg->eMode)
    {
        case VREFBUF_MODE_NONE:
            break;
        case VREFBUF_MODE_EXTERNAL:
            break;
        case VREFBUF_MODE_VDDEXT:
            SET_VREFBUF_TCR_STABLE_TIME(ptVRef, ptCfg->un32StlTime);
            break;
        case VREFBUF_MODE_INTERNAL:
            SET_VREFBUF_CR_VREF_VOLT(ptVRef, ptCfg->eVoltage);
            SET_VREFBUF_TCR_STABLE_TIME(ptVRef, ptCfg->un32StlTime);
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    SET_VREFBUF_CR_MODE(ptVRef, ptCfg->eMode);

    return eErr;
}

HAL_ERR_e HAL_VREFBUF_SetIRQ(VREFBUF_ID_e eId, VREFBUF_OPS_e eOps, pfnVREFBUF_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    VREFBUF_Type *ptVRef;
    VREFBUF_CTRL_BLK_t *ptVcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= VREFBUF_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptVRef = PRV_VREFBUF_GetReg((P_VREFBUF_ID_e)eId);
    ptVcb = &s_tVcb[(uint32_t)eId];
    eIrq = VREFBUF_GetIRQNum((P_VREFBUF_ID_e)eId);

    switch(eOps)
    {
        case VREFBUF_OPS_INTR:
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            if(ptVcb->bNmiEnable == true)
            {
                (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
                ptVcb->bNmiEnable = false;
            }
#endif
            ptVcb->pfnHandler = pfnHandler;
            ptVcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);

            SET_VREFBUF_IER_EN(ptVRef, true);
            break;
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
        case VREFBUF_OPS_NMI:
            eErr = HPL_NMI_SetSource(eIrq, &PRV_VREFBUF_NMIHandler, pContext, true);
            if(eErr == HAL_ERR_OK)
            {
                ptVcb->pfnHandler = pfnHandler;
                ptVcb->pContext = pContext;
            }
            ptVcb->bNmiEnable = true;
            break;
#endif
        case VREFBUF_OPS_POLL:
        default:
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
            ptVcb->bNmiEnable = false;
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptVcb->pfnHandler = NULL;
            ptVcb->pContext = NULL;
            break;
    }

    ptVcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_VREFBUF_SetWaitStable(VREFBUF_ID_e eId, uint32_t un32Timeout)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    VREFBUF_Type *ptVRef;

    if((uint32_t)eId >= VREFBUF_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptVRef = PRV_VREFBUF_GetReg((P_VREFBUF_ID_e)eId);

    while(!GET_VREFBUF_SR_STABLE(ptVRef))
    {
        un32Timeout--;
        if(un32Timeout == 0)
        {
            eErr = HAL_ERR_TIMEOUT;
            break;
        }
    }

    SET_VREFBUF_SR_STABLE(ptVRef, true);

    return eErr;
}

static void PRV_VREFBUF_IRQHandler(VREFBUF_ID_e eId)
{
    VREFBUF_Type *ptVRef;
    VREFBUF_CTRL_BLK_t *ptVcb;

    if((uint32_t)eId >= VREFBUF_CH_NUM)
    {
        return;
    }

    ptVRef = PRV_VREFBUF_GetReg((P_VREFBUF_ID_e)eId);
    ptVcb = &s_tVcb[(uint32_t)eId];

    SET_VREFBUF_IER_EN(ptVRef, false);

    if(ptVcb->pfnHandler != NULL)
    {
        ptVcb->pfnHandler(0, ptVcb->pContext);
    }
}

void VREFBUF0_IRQHandler(void)
{
    PRV_VREFBUF_IRQHandler(VREFBUF_ID_0);
}

void VREFBUF1_IRQHandler(void)
{
    PRV_VREFBUF_IRQHandler(VREFBUF_ID_1);
}

#endif /* _VREFBUF */
