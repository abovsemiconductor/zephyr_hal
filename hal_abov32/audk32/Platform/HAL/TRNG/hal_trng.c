/**
 *******************************************************************************
 * @file        hal_trng.c
 * @author      ABOV R&D Division
 * @brief       True Random Number Generator (TRNG)
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

#if defined(_TRNG)
#include "hal_trng.h"
#include "hal_trng_prv.h"

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
#include "hpl_nmi.h"
#endif

typedef struct
{
    TRNG_OPS_e               eOps;
    pfnTRNG_IRQ_Handler_t    pfnHandler;
    void                    *pContext;

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
    bool                    bNmiEnable;
#endif

} TRNG_CTRL_BLK_t;

static TRNG_CTRL_BLK_t s_tTcb[TRNG_CH_NUM];

static void PRV_TRNG_IRQHandler(TRNG_ID_e eId);

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
static void PRV_TRNG_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < TRNG_CH_NUM; i++)
    {
        if(s_tTcb[i].bNmiEnable == true)
        {
            PRV_TRNG_IRQHandler((TRNG_ID_e)i);
        }
    }
}
#endif

static TRNG_Type *PRV_TRNG_GetReg(P_TRNG_ID_e eId)
{
    return TRNG_GetReg((P_TRNG_ID_e)eId);
}

static HAL_ERR_e PRV_TRNG_SetScuEnable(P_TRNG_ID_e eId, bool bEnable)
{
    return TRNG_SetScuEnable((P_TRNG_ID_e)eId, bEnable);
}

HAL_ERR_e HAL_TRNG_Init(TRNG_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= TRNG_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_TRNG_SetScuEnable((P_TRNG_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tTcb[(uint32_t)eId], 0x00, sizeof(TRNG_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TRNG_Uninit(TRNG_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= TRNG_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_TRNG_SetScuEnable((P_TRNG_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tTcb[(uint32_t)eId], 0x00, sizeof(TRNG_CTRL_BLK_t));

    /* Forcily, disable NVIC Interrupt */
    eIrq = TRNG_GetIRQNum((P_TRNG_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TRNG_SetConfig(TRNG_ID_e eId, TRNG_CFG_t *ptCfg)
{
    TRNG_Type *ptTrng;

    if((uint32_t)eId >= TRNG_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTrng = PRV_TRNG_GetReg((P_TRNG_ID_e)eId);

    if(ptCfg->un8IntrEnable & TRNG_INTR_READY)
    {
        SET_TRNG_IER_RDY_EN(ptTrng, true);
    }
    else
    {
        SET_TRNG_IER_RDY_EN(ptTrng, false);
    }

    if(ptCfg->un8IntrEnable & TRNG_INTR_ERROR)
    {
        SET_TRNG_IER_ERR_EN(ptTrng, true);
    }
    else
    {
        SET_TRNG_IER_ERR_EN(ptTrng, false);
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TRNG_SetIRQ(TRNG_ID_e eId, TRNG_OPS_e eOps, pfnTRNG_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TRNG_CTRL_BLK_t *ptTcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= TRNG_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTcb = &s_tTcb[(uint32_t)eId];
    eIrq = TRNG_GetIRQNum((P_TRNG_ID_e)eId);

    switch(eOps)
    {
        case TRNG_OPS_INTR:
#if defined (TRNG_FEATURE_IRQ_UNMASK_ENABLE)
            TRNG_SetIntrUnMask(eIrq, true);
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
        case TRNG_OPS_NMI:
            eErr = HPL_NMI_SetSource(eIrq, &PRV_TRNG_NMIHandler, pContext, true);
            if(eErr == HAL_ERR_OK)
            {
                ptTcb->pfnHandler = pfnHandler;
                ptTcb->pContext = pContext;
            }
            ptTcb->bNmiEnable = true;
            break;
#endif
        case TRNG_OPS_POLL:
        default:
#if defined (TRNG_FEATURE_IRQ_UNMASK_ENABLE)
            TRNG_SetIntrUnMask(eIrq, false);
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

HAL_ERR_e HAL_TRNG_SetGenerate(TRNG_ID_e eId, bool bEnable)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TRNG_Type *ptTrng;

    if((uint32_t)eId >= TRNG_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTrng = PRV_TRNG_GetReg((P_TRNG_ID_e)eId);
    SET_TRNG_CR_EN(ptTrng, bEnable);

    return eErr;
}

HAL_ERR_e HAL_TRNG_GetResult(TRNG_ID_e eId, uint32_t *pun32Out)
{
    TRNG_Type *ptTrng;

    if((uint32_t)eId >= TRNG_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTrng = PRV_TRNG_GetReg((P_TRNG_ID_e)eId);
    *pun32Out = GET_TRNG_DR_TRNGD_VAL(ptTrng);

     return HAL_ERR_OK;
}

HAL_ERR_e HAL_TRNG_SetWaitComplete(TRNG_ID_e eId, uint32_t un32Timeout)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TRNG_Type *ptTrng;

    if((uint32_t)eId >= TRNG_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTrng = PRV_TRNG_GetReg((P_TRNG_ID_e)eId);

    while(!GET_TRNG_SR_RDY_FLAG(ptTrng) && !GET_TRNG_SR_ERR_FLAG(ptTrng))
    {
        un32Timeout--;
        if(un32Timeout == 0)
        {
            eErr = HAL_ERR_TIMEOUT;
            break;
        }
    }

    if(GET_TRNG_SR_ERR_FLAG(ptTrng))
    {
        SET_TRNG_SR_ERR_FLAG(ptTrng, true);
        eErr = HAL_ERR_HW;
    }

    return eErr;
}

void PRV_TRNG_IRQHandler(TRNG_ID_e eId)
{
    TRNG_Type *ptTrng;
    TRNG_CTRL_BLK_t *ptTcb;
    uint32_t un32Event = 0;

    if((uint32_t)eId >= TRNG_CH_NUM)
    {
        return;
    }

    ptTrng = PRV_TRNG_GetReg((P_TRNG_ID_e)eId);
    ptTcb = &s_tTcb[(uint32_t)eId];

    if(GET_TRNG_IER_RDY_FLAG(ptTrng))
    {
        un32Event |= TRNG_EVENT_READY;
        SET_TRNG_IER_RDY_FLAG(ptTrng, true);
    }

    if(GET_TRNG_IER_ERR_FLAG(ptTrng))
    {
        un32Event |= TRNG_EVENT_ERROR;
        SET_TRNG_IER_ERR_FLAG(ptTrng, true);
        SET_TRNG_SR_ERR_FLAG(ptTrng, true);
    }

    if(ptTcb->pfnHandler != NULL)
    {
        ptTcb->pfnHandler(un32Event, ptTcb->pContext);
    }
}

void TRNG0_IRQHandler(void)
{
    PRV_TRNG_IRQHandler(TRNG_ID_0);
}

#endif /* _TRNG */
