/**
 *******************************************************************************
 * @file        hal_rng.c
 * @author      ABOV R&D Division
 * @brief       Random Number Generator (RNG)
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

#if defined(_RNG)
#include "hal_rng.h"
#include "hal_rng_prv.h"

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
#include "hpl_nmi.h"
#endif

typedef struct
{
    RNG_OPS_e               eOps;
    pfnRNG_IRQ_Handler_t    pfnHandler;
    void                    *pContext;

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
    bool                    bNmiEnable;
#endif

} RNG_CTRL_BLK_t;

static RNG_CTRL_BLK_t s_tRcb[RNG_CH_NUM];

static void PRV_RNG_IRQHandler(RNG_ID_e eId);

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
static void PRV_RNG_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < RNG_CH_NUM; i++)
    {
        if(s_tRcb[i].bNmiEnable == true)
        {
            PRV_RNG_IRQHandler((RNG_ID_e)i);
        }
    }
}
#endif

static RNG_Type *PRV_RNG_GetReg(P_RNG_ID_e eId)
{
    return RNG_GetReg((P_RNG_ID_e)eId);
}

static HAL_ERR_e PRV_RNG_SetScuEnable(P_RNG_ID_e eId, bool bEnable)
{
    return RNG_SetScuEnable((P_RNG_ID_e)eId, bEnable);
}

HAL_ERR_e HAL_RNG_Init(RNG_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= RNG_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_RNG_SetScuEnable((P_RNG_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tRcb[(uint32_t)eId], 0x00, sizeof(RNG_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_RNG_Uninit(RNG_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= RNG_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_RNG_SetScuEnable((P_RNG_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tRcb[(uint32_t)eId], 0x00, sizeof(RNG_CTRL_BLK_t));

    /* Forcily, disable NVIC Interrupt */
    eIrq = RNG_GetIRQNum((P_RNG_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_RNG_SetConfig(RNG_ID_e eId, RNG_CFG_t *ptCfg)
{
    RNG_Type *ptRng;

    if((uint32_t)eId >= RNG_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptRng = PRV_RNG_GetReg((P_RNG_ID_e)eId);

    SET_RNG_CR_LFS_SEL(ptRng, ptCfg->eClkLFS);
    SET_RNG_CR_CAS_SEL(ptRng, ptCfg->eClkCAS);

    if(ptCfg->un8IntrEnable & RNG_INTR_READY)
    {
        SET_RNG_IER_RDY_EN(ptRng, true);
    }
    else
    {
        SET_RNG_IER_RDY_EN(ptRng, false);
    }

    if(ptCfg->un8IntrEnable & RNG_INTR_ERROR)
    {
        SET_RNG_IER_ERR_EN(ptRng, true);
    }
    else
    {
        SET_RNG_IER_ERR_EN(ptRng, false);
    }

    SET_RNG_CR_GCP_VAL(ptRng, ptCfg->un16GenTime);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_RNG_SetIRQ(RNG_ID_e eId, RNG_OPS_e eOps, pfnRNG_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    RNG_CTRL_BLK_t *ptRcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= RNG_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptRcb = &s_tRcb[(uint32_t)eId];
    eIrq = RNG_GetIRQNum((P_RNG_ID_e)eId);

    switch(eOps)
    {
        case RNG_OPS_INTR:
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            if(ptRcb->bNmiEnable == true)
            {
                (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
                ptRcb->bNmiEnable = false;
            }
#endif
            ptRcb->pfnHandler = pfnHandler;
            ptRcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            break;
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
        case RNG_OPS_NMI:
            eErr = HPL_NMI_SetSource(eIrq, &PRV_RNG_NMIHandler, pContext, true);
            if(eErr == HAL_ERR_OK)
            {
                ptRcb->pfnHandler = pfnHandler;
                ptRcb->pContext = pContext;
            }
            ptRcb->bNmiEnable = true;
            break;
#endif
        case RNG_OPS_POLL:
        default:
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
            ptRcb->bNmiEnable = false;
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptRcb->pContext = NULL;
            ptRcb->pfnHandler = NULL;
            break;
    }

    ptRcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_RNG_SetSeed(RNG_ID_e eId, uint32_t un32Seed)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    RNG_Type *ptRng;

    if((uint32_t)eId >= RNG_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptRng = PRV_RNG_GetReg((P_RNG_ID_e)eId);
    SET_RNG_DR_SEED_VAL(ptRng, un32Seed);

    return eErr;
}

HAL_ERR_e HAL_RNG_SetGenerate(RNG_ID_e eId, bool bEnable)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    RNG_Type *ptRng;

    if((uint32_t)eId >= RNG_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptRng = PRV_RNG_GetReg((P_RNG_ID_e)eId);
    SET_RNG_CR_EN(ptRng, bEnable);

    return eErr;
}

HAL_ERR_e HAL_RNG_GetResult(RNG_ID_e eId, uint32_t *pun32Out)
{
    RNG_Type *ptRng;

    if((uint32_t)eId >= RNG_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptRng = PRV_RNG_GetReg((P_RNG_ID_e)eId);
    *pun32Out = GET_RNG_DR_RNGD_VAL(ptRng);

     return HAL_ERR_OK;
}

HAL_ERR_e HAL_RNG_SetWaitComplete(RNG_ID_e eId, uint32_t un32Timeout)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    RNG_Type *ptRng;

    if((uint32_t)eId >= RNG_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptRng = PRV_RNG_GetReg((P_RNG_ID_e)eId);

    while(!GET_RNG_SR_RDY_FLAG(ptRng) && !GET_RNG_SR_ERR_FLAG(ptRng))
    {
        un32Timeout--;
        if(un32Timeout == 0)
        {
            eErr = HAL_ERR_TIMEOUT;
            break;
        }
    }

    if(GET_RNG_SR_ERR_FLAG(ptRng))
    {
        SET_RNG_SR_ERR_FLAG(ptRng, true);
        eErr = HAL_ERR_HW;
    }

    return eErr;
}

void PRV_RNG_IRQHandler(RNG_ID_e eId)
{
    RNG_Type *ptRng;
    RNG_CTRL_BLK_t *ptRcb;
    uint32_t un32Event = 0;

    if((uint32_t)eId >= RNG_CH_NUM)
    {
        return;
    }

    ptRng = PRV_RNG_GetReg((P_RNG_ID_e)eId);
    ptRcb = &s_tRcb[(uint32_t)eId];

    if(GET_RNG_IER_RDY_FLAG(ptRng))
    {
        un32Event |= RNG_EVENT_READY;
        SET_RNG_IER_RDY_FLAG(ptRng, true);
    }

    if(GET_RNG_IER_ERR_FLAG(ptRng))
    {
        un32Event |= RNG_EVENT_ERROR;
        SET_RNG_IER_ERR_FLAG(ptRng, true);
        SET_RNG_SR_ERR_FLAG(ptRng, true);
    }

    if(ptRcb->pfnHandler != NULL)
    {
        ptRcb->pfnHandler(un32Event, ptRcb->pContext);
    }
}

void RNG0_IRQHandler(void)
{
    PRV_RNG_IRQHandler(RNG_ID_0);
}

#endif /* _RNG */
