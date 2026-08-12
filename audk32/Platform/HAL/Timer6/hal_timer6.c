/**
 *******************************************************************************
 * @file        hal_timer6.c
 * @author      ABOV R&D Division
 * @brief       6N typed Timer
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

#if defined(_TIMER6)
#include "hal_timer6.h"
#include "hal_timer6_prv.h"

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
#include "hpl_nmi.h"
#endif

typedef struct
{
    TIMER6_OPS_e               eOps;
    pfnTIMER6_IRQ_Handler_t    pfnHandler;
    void                       *pContext;

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
    bool                       bNmiEnable;
#endif

} TIMER6_CTRL_BLK_t;

static TIMER6_CTRL_BLK_t s_tTcb[TIMER6_CH_NUM];

static void PRV_TIMER6_IRQHandler(TIMER6_ID_e eId);

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
static void PRV_TIMER6_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < TIMER6_CH_NUM; i++)
    {
        if(s_tTcb[i].bNmiEnable == true)
        {
            PRV_TIMER6_IRQHandler((TIMER6_ID_e)i);
        }
    }
}
#endif

static TIMER6_Type *PRV_TIMER6_GetReg(TIMER6_ID_e eId)
{
    return TIMER6_GetReg((uint32_t)eId);
}

static HAL_ERR_e PRV_TIMER6_SetScuEnable(P_TIMER6_ID_e eId, bool bEnable)
{
    return TIMER6_SetScuEnable(eId, bEnable);
}

HAL_ERR_e HAL_TIMER6_Init(TIMER6_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER6_Type *ptTimer;

    if((uint32_t)eId >= TIMER6_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_TIMER6_SetScuEnable((P_TIMER6_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    ptTimer = PRV_TIMER6_GetReg(eId);
    memset(&s_tTcb[(uint32_t)eId], 0x00, sizeof(TIMER6_CTRL_BLK_t));

    /* clear control register */
    SET_TIMER6_CR(ptTimer, 0x00);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER6_Uninit(TIMER6_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= TIMER6_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_TIMER6_SetScuEnable((P_TIMER6_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = TIMER6_GetIRQNum((P_TIMER6_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER6_SetConfig(TIMER6_ID_e eId, TIMER6_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER6_Type *ptTimer;

    if((uint32_t)eId >= TIMER6_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER6_GetReg(eId);
    
    if(ptCfg->bIntrEnable)
    {
        /* enable interrupt */
        SET_TIMER6_IER_MATCH_EN(ptTimer, true);
    }
    else
    {
        /* disable interrupt */
        SET_TIMER6_IER_MATCH_EN(ptTimer, false);
    }

    /* Set Data */
    SET_TIMER6_DR(ptTimer, ptCfg->un16Data);

    /* Clear Count Register */
    SET_TIMER6_CR_CLR(ptTimer, true);

    return eErr;
}

HAL_ERR_e HAL_TIMER6_SetIRQ(TIMER6_ID_e eId, TIMER6_OPS_e eOps, pfnTIMER6_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER6_CTRL_BLK_t *ptTcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= TIMER6_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTcb = &s_tTcb[(uint32_t)eId];
    eIrq = TIMER6_GetIRQNum((P_TIMER6_ID_e)eId);

    switch(eOps)
    {
        case TIMER6_OPS_INTR:
#if defined(TIMER6_FEATURE_IRQ_UNMASK_ENABLE)
            TIMER6_SetIntrUnMask(eIrq, true);
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
        case TIMER6_OPS_NMI:
            eErr = HPL_NMI_SetSource(eIrq, &PRV_TIMER6_NMIHandler, pContext, true);
            if(eErr == HAL_ERR_OK)
            {
                ptTcb->pfnHandler = pfnHandler;
                ptTcb->pContext = pContext;
            }
            ptTcb->bNmiEnable = true;
            break;
#endif
        case TIMER6_OPS_POLL:
        default:
#if defined(TIMER6_FEATURE_IRQ_UNMASK_ENABLE)
            TIMER6_SetIntrUnMask(eIrq, false);
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

HAL_ERR_e HAL_TIMER6_GetStatus(TIMER6_ID_e eId, uint32_t *pun32Status)
{
    TIMER6_Type *ptTimer;

    if((uint32_t)eId >= TIMER6_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER6_GetReg(eId);
    if (GET_TIMER6_IER_MATCH_FLAG(ptTimer))
    {
        *pun32Status = TIMER6_INTR_FLAG_MATCH;
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER6_GetData(TIMER6_ID_e eId, uint32_t *pun32Data)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER6_Type *ptTimer;

    if((uint32_t)eId >= TIMER6_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER6_GetReg(eId);
    *pun32Data = GET_TIMER6_DR(ptTimer);
    return eErr;
}

HAL_ERR_e HAL_TIMER6_Start(TIMER6_ID_e eId)
{
    TIMER6_Type *ptTimer;

    if((uint32_t)eId >= TIMER6_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER6_GetReg(eId);
    SET_TIMER6_CR_EN(ptTimer, true);
    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER6_Stop(TIMER6_ID_e eId)
{
    TIMER6_Type *ptTimer;

    if((uint32_t)eId >= TIMER6_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER6_GetReg(eId);
    SET_TIMER6_CR_EN(ptTimer, false);
    return HAL_ERR_OK;
}

static void PRV_TIMER6_IRQHandler(TIMER6_ID_e eId)
{
    TIMER6_Type *ptTimer;
    TIMER6_CTRL_BLK_t *ptTcb;
    uint32_t un32Event = 0;

    ptTimer = PRV_TIMER6_GetReg(eId);
    ptTcb = &s_tTcb[(uint32_t)eId];

    if (GET_TIMER6_IER_MATCH_FLAG(ptTimer))
    {
        un32Event = TIMER6_EVENT_PERIODIC_MATCH;
        /* clear status */ 
        SET_TIMER6_IER_MATCH_FLAG(ptTimer, true);
    }

    if(ptTcb->pfnHandler != NULL && un32Event)
    {
        ptTcb->pfnHandler(un32Event, ptTcb->pContext);
    }
}

void TIMER60_IRQHandler(void)
{
    PRV_TIMER6_IRQHandler(TIMER6_ID_0);
}

void TIMER61_IRQHandler(void)
{
    PRV_TIMER6_IRQHandler(TIMER6_ID_1);
}

void TIMER62_IRQHandler(void)
{
    PRV_TIMER6_IRQHandler(TIMER6_ID_2);
}

void TIMER63_IRQHandler(void)
{
    PRV_TIMER6_IRQHandler(TIMER6_ID_3);
}

void TIMER64_IRQHandler(void)
{
    PRV_TIMER6_IRQHandler(TIMER6_ID_4);
}

void TIMER65_IRQHandler(void)
{
    PRV_TIMER6_IRQHandler(TIMER6_ID_5);
}

void TIMER66_IRQHandler(void)
{
    PRV_TIMER6_IRQHandler(TIMER6_ID_6);
}

void TIMER67_IRQHandler(void)
{
    PRV_TIMER6_IRQHandler(TIMER6_ID_7);
}

void TIMER68_IRQHandler(void)
{
    PRV_TIMER6_IRQHandler(TIMER6_ID_8);
}

void TIMER69_IRQHandler(void)
{
    PRV_TIMER6_IRQHandler(TIMER6_ID_9);
}

#endif /* _TIMER6 */
