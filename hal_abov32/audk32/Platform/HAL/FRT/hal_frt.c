/**
 *******************************************************************************
 * @file        hal_frt.c
 * @author      ABOV R&D Division
 * @brief       Free Run Timer
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

#if defined(_FRT)
#include "hal_frt.h"
#include "hal_frt_prv.h"

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
#include "hpl_nmi.h"
#endif

typedef struct
{
    FRT_OPS_e               eOps;
    pfnFRT_IRQ_Handler_t    pfnHandler;
    void                    *pContext;

    FRT_INTR_e              eIntr;
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
    bool                    bNmiEnable;
#endif
} FRT_CTRL_BLK_t;

static FRT_CTRL_BLK_t s_tFcb[FRT_CH_NUM];

static void PRV_FRT_IRQHandler(FRT_ID_e eId);

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
static void PRV_FRT_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < FRT_CH_NUM; i++)
    {
        if(s_tFcb[i].bNmiEnable == true)
        {
            PRV_FRT_IRQHandler((FRT_ID_e)i);
        }
    }
}
#endif

static FRT_Type *PRV_FRT_GetReg(FRT_ID_e eId)
{
    return FRT_GetReg((P_FRT_ID_e)eId);
}

static HAL_ERR_e PRV_FRT_SetScuEnable(P_FRT_ID_e eId, bool bEnable)
{
    return FRT_SetScuEnable((P_FRT_ID_e)eId, bEnable);
}

HAL_ERR_e HAL_FRT_Init(FRT_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= FRT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_FRT_SetScuEnable((P_FRT_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tFcb[(uint32_t)eId], 0x00, sizeof(FRT_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_FRT_Uninit(FRT_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= FRT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_FRT_SetScuEnable((P_FRT_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = FRT_GetIRQNum((P_FRT_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tFcb[(uint32_t)eId], 0x00, sizeof(FRT_CTRL_BLK_t));

    return eErr;
}

HAL_ERR_e HAL_FRT_SetConfig(FRT_ID_e eId, FRT_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    FRT_Type *ptFrt;
    FRT_CTRL_BLK_t *ptFcb;

    if((uint32_t)eId >= FRT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptFrt = PRV_FRT_GetReg(eId);
    ptFcb = &s_tFcb[(uint32_t)eId];

    SET_FRT_CR_MODE(ptFrt, (uint32_t)ptCfg->eMode);

    switch(ptCfg->eIntr)
    {
        case FRT_INTR_MATCH:
            SET_FRT_IER_MATCH_EN(ptFrt, true);
            break;
        case FRT_INTR_OVERFLOW:
            SET_FRT_IER_OVF_EN(ptFrt, true);
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    if(eErr != HAL_ERR_OK)
    {
        return HAL_ERR_PARAMETER;
    }

    ptFcb->eIntr = ptCfg->eIntr;

    SET_FRT_DR_MATCH_CNT(ptFrt, ptCfg->un32MatchCnt);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_FRT_SetClkConfig(FRT_ID_e eId, FRT_CLK_CFG_t *ptClkCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    FRT_Type *ptFrt;

    if((uint32_t)eId >= FRT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptFrt = PRV_FRT_GetReg(eId);

    switch (ptClkCfg->eClk)
    {
        case FRT_CLK_MCCR:
            SET_FRT_CR_CLK_SEL(ptFrt, (uint8_t)FRT_CLK_MCCR);
            eErr = FRT_SetMccrClk((P_FRT_ID_e)eId, (P_FRT_CLK_MCCR_e)ptClkCfg->eMccr, ptClkCfg->un8MccrDiv);
            break;
        case FRT_CLK_PCLK:
            SET_FRT_CR_CLK_SEL(ptFrt, (uint8_t)FRT_CLK_PCLK);
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    SET_FRT_CR_CLK_PREDIV(ptFrt, ptClkCfg->ePreDiv);

    return eErr;
}

HAL_ERR_e HAL_FRT_SetIRQ(FRT_ID_e eId, FRT_OPS_e eOps, pfnFRT_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    FRT_CTRL_BLK_t *ptFcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= FRT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptFcb = &s_tFcb[(uint32_t)eId];
    eIrq = FRT_GetIRQNum((P_FRT_ID_e)eId);

    switch(eOps)
    {
        case FRT_OPS_INTR:
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            if(ptFcb->bNmiEnable == true)
            {
                (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
                ptFcb->bNmiEnable = false;
            }
#endif
            ptFcb->pfnHandler = pfnHandler;
            ptFcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            break;
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
        case FRT_OPS_NMI:
            eErr = HPL_NMI_SetSource(eIrq, &PRV_FRT_NMIHandler, pContext, true);
            if(eErr == HAL_ERR_OK)
            {
                ptFcb->pfnHandler = pfnHandler;
                ptFcb->pContext = pContext;
            }
            ptFcb->bNmiEnable = true;
            break;
#endif
        case FRT_OPS_POLL:
        default:
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
            ptFcb->bNmiEnable = false;
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptFcb->pContext = NULL;
            ptFcb->pfnHandler = NULL;
            break;
    }

    ptFcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_FRT_Start(FRT_ID_e eId, bool bResume)
{
    FRT_Type *ptFrt;

    if((uint32_t)eId >= FRT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptFrt = PRV_FRT_GetReg(eId);
    SET_FRT_CR_EN(ptFrt, true);

    /* To clear counter, FRT must be running */
    if(bResume == false)
    {
        SET_FRT_DR_CNT(ptFrt, 0);
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_FRT_Stop(FRT_ID_e eId)
{
    FRT_Type *ptFrt;

    if((uint32_t)eId >= FRT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptFrt = PRV_FRT_GetReg(eId);
    SET_FRT_CR_EN(ptFrt, false);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_FRT_SetWaitComplete(FRT_ID_e eId, uint32_t un32Timeout, uint8_t *pun8Event)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    FRT_Type *ptFrt;
    FRT_CTRL_BLK_t *ptFcb;
    uint32_t un32IntrTimeout;

    if((uint32_t)eId >= FRT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptFrt = PRV_FRT_GetReg(eId);
    ptFcb = &s_tFcb[(uint32_t)eId];

    if(ptFcb->eIntr == FRT_INTR_OVERFLOW)
    {
        un32IntrTimeout = un32Timeout;

        while(!GET_FRT_IER_OVF_FLAG(ptFrt))
        {
            un32IntrTimeout--;
            if(un32IntrTimeout == 0)
            {
                eErr = HAL_ERR_TIMEOUT;
                break;
            }
        }

        SET_FRT_IER_OVF_FLAG(ptFrt, true);
        if(eErr != HAL_ERR_TIMEOUT)
        {
            *pun8Event |= FRT_EVENT_OVERFLOW;
        }
    }

    if(ptFcb->eIntr == FRT_INTR_MATCH)
    {
        un32IntrTimeout = un32Timeout;

        while(!GET_FRT_IER_MATCH_FLAG(ptFrt))
        {
            un32IntrTimeout--;
            if(un32IntrTimeout == 0)
            {
                eErr = HAL_ERR_TIMEOUT;
                break;
            }
        }

        SET_FRT_IER_MATCH_FLAG(ptFrt, true);

        if(eErr != HAL_ERR_TIMEOUT)
        {
            *pun8Event |= FRT_EVENT_MATCH;
        }
    }

    return eErr;
}

HAL_ERR_e HAL_FRT_ReadCount(FRT_ID_e eId, bool bMatch ,uint32_t *pun32Count)
{
    FRT_Type *ptFrt;

    if((uint32_t)eId >= FRT_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptFrt = PRV_FRT_GetReg(eId);

    if(bMatch == false)
    {
        *pun32Count = GET_FRT_DR_CNT(ptFrt);
    }
    else
    {
        *pun32Count = GET_FRT_DR_MATCH_CNT(ptFrt);
    }

    return HAL_ERR_OK;
}

void PRV_FRT_IRQHandler(FRT_ID_e eId)
{
    FRT_Type *ptFrt;
    FRT_CTRL_BLK_t *ptFcb;
    uint32_t un32Event = 0;

    ptFrt = PRV_FRT_GetReg(eId);
    ptFcb = &s_tFcb[(uint32_t)eId];

    if(GET_FRT_IER_OVF_FLAG(ptFrt))
    {
        SET_FRT_IER_OVF_FLAG(ptFrt, FRT_CLEAR);
        un32Event |= FRT_EVENT_OVERFLOW;
    }
    if(GET_FRT_IER_MATCH_FLAG(ptFrt))
    {
        SET_FRT_IER_MATCH_FLAG(ptFrt, FRT_CLEAR);
        un32Event |= FRT_EVENT_MATCH;
    }

    if(ptFcb->pfnHandler)
    {
        ptFcb->pfnHandler(un32Event,ptFcb->pContext);
    }
}

void FRT0_IRQHandler(void)
{
    PRV_FRT_IRQHandler(FRT_ID_0);
}

void FRT1_IRQHandler(void)
{
    PRV_FRT_IRQHandler(FRT_ID_1);
}

#endif /* _FRT */
