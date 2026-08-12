/**
 *******************************************************************************
 * @file        hal_tempsens.c
 * @author      ABOV R&D Division
 * @brief       Temperature Sensor
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

#if defined(_TEMPSENS)
#include "hal_tempsens.h"
#include "hal_tempsens_prv.h"

typedef struct
{
    TEMPSENS_OPS_e               eOps;
    pfnTEMPSENS_IRQ_Handler_t    pfnHandler;
    void                         *pContext;

    float                        fSlope;
    float                        fOffset;
} TEMPSENS_CTRL_BLK_t;

static TEMPSENS_CTRL_BLK_t s_tTcb[TEMPSENS_CH_NUM];

static TEMPSENS_Type *PRV_TEMPSENS_GetReg(P_TEMPSENS_ID_e eId)
{
    return TEMPSENS_GetReg((P_TEMPSENS_ID_e)eId);
}

static HAL_ERR_e PRV_TEMPSENS_SetScuEnable(P_TEMPSENS_ID_e eId, bool bEnable)
{
    return TEMPSENS_SetScuEnable((P_TEMPSENS_ID_e)eId, bEnable);
}

HAL_ERR_e HAL_TEMPSENS_Init(TEMPSENS_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TEMPSENS_Type *ptTs;

    if((uint32_t)eId >= TEMPSENS_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_TEMPSENS_SetScuEnable((P_TEMPSENS_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tTcb[(uint32_t)eId], 0, sizeof(TEMPSENS_CTRL_BLK_t));

    ptTs = PRV_TEMPSENS_GetReg((P_TEMPSENS_ID_e)eId);
    SET_TEMPSENS_CR_EN(ptTs, true);

    return eErr;
}

HAL_ERR_e HAL_TEMPSENS_Uninit(TEMPSENS_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TEMPSENS_Type *ptTs;
#if (TEMPSENS_OPS_INTR_SUPPORT)
    IRQn_Type eIrq;
#endif

    if((uint32_t)eId >= TEMPSENS_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTs = PRV_TEMPSENS_GetReg((P_TEMPSENS_ID_e)eId);
    SET_TEMPSENS_CR_EN(ptTs, false);

    eErr = PRV_TEMPSENS_SetScuEnable((P_TEMPSENS_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

#if (TEMPSENS_OPS_INTR_SUPPORT)
    /* Forcily, disable NVIC Interrupt */
    eIrq = TEMPSENS_GetIRQNum((P_TEMPSENS_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);
#endif

    memset(&s_tTcb[(uint32_t)eId], 0, sizeof(TEMPSENS_CTRL_BLK_t));


    return eErr;
}

HAL_ERR_e HAL_TEMPSENS_SetConfig(TEMPSENS_ID_e eId, TEMPSENS_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
#if defined (TEMPSENS_FEATURE_READ_REF_DATA_VX) || defined (TEMPSENS_FEATURE_READ_REF_DATA_FX)
    TEMPSENS_CTRL_BLK_t *ptTcb;
    uint32_t un32HighTemp, un32LowTemp;
#endif

    if((uint32_t)eId >= TEMPSENS_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if defined (TEMPSENS_FEATURE_READ_REF_DATA_VX) || defined (TEMPSENS_FEATURE_READ_REF_DATA_FX)
    ptTcb = &s_tTcb[(uint32_t)eId];
#endif

    eErr = TEMPSENS_SetClk((P_TEMPSENS_ID_e)eId, (P_TEMPSENS_REF_CLK_e)ptCfg->eRefClk, (P_TEMPSENS_SEN_CLK_e)ptCfg->eSenClk);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    eErr = TEMPSENS_SetRefCount((P_TEMPSENS_ID_e)eId, (P_TEMPSENS_REF_CLK_e)ptCfg->eRefClk);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

#if defined (TEMPSENS_FEATURE_READ_REF_DATA_VX)
    un32HighTemp = ((*(uint32_t *)(TEMPSENS_REF_HIGH_TEMP_ADDR)) * TEMPSENS_REF_CLK_DIV) / (0x2000);
    un32LowTemp = ((*(uint32_t *)(TEMPSENS_REF_LOW_TEMP_ADDR)) * TEMPSENS_REF_CLK_DIV) / (0x2000);
    ptTcb->fSlope = (TEMPSENS_REF_HIGH_TEMP - TEMPSENS_REF_LOW_TEMP) / ((float)un32HighTemp - (float)un32LowTemp);
    ptTcb->fOffset = 30 - (ptTcb->fSlope * (float)un32LowTemp);
#elif defined (TEMPSENS_FEATURE_READ_REF_DATA_FX)
    un32HighTemp = (*(uint32_t *)(TEMPSENS_REF_HIGH_TEMP_ADDR));
    un32LowTemp = (*(uint32_t *)(TEMPSENS_REF_LOW_TEMP_ADDR));
    ptTcb->fSlope = ((float)(un32HighTemp/1000) - (float)(un32LowTemp/1000)) / (TEMPSENS_REF_HIGH_TEMP - TEMPSENS_REF_LOW_TEMP);
    ptTcb->fOffset = un32LowTemp/1000;
#endif

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TEMPSENS_SetIRQ(TEMPSENS_ID_e eId, TEMPSENS_OPS_e eOps, pfnTEMPSENS_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TEMPSENS_CTRL_BLK_t *ptTcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= TEMPSENS_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(eOps == TEMPSENS_OPS_INTR && !TEMPSENS_OPS_INTR_SUPPORT)
    {
        return HAL_ERR_NOT_SUPPORTED;
    }

    ptTcb = &s_tTcb[(uint32_t)eId];
    eIrq = TEMPSENS_GetIRQNum((P_TEMPSENS_ID_e)eId);

    switch(eOps)
    {
#if (TEMPSENS_OPS_INTR_SUPPORT)
        case TEMPSENS_OPS_INTR:
#if defined (TEMPSENS_FEATURE_IRQ_UNMASK_ENABLE)
            TEMPSENS_SetIntrUnMask(eIrq, true);
#endif
            ptTcb->pfnHandler = pfnHandler;
            ptTcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            break;
#endif
        case TEMPSENS_OPS_POLL:
        default:
#if defined (TEMPSENS_FEATURE_IRQ_UNMASK_ENABLE)
            TEMPSENS_SetIntrUnMask(eIrq, false);
#endif
#if (TEMPSENS_OPS_INTR_SUPPORT)
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
#endif
            ptTcb->pContext = NULL;
            ptTcb->pfnHandler = NULL;
            break;
    }

    ptTcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_TEMPSENS_Start(TEMPSENS_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TEMPSENS_Type *ptTs;
    TEMPSENS_CTRL_BLK_t *ptTcb;

    if((uint32_t)eId >= TEMPSENS_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTs = PRV_TEMPSENS_GetReg((P_TEMPSENS_ID_e)eId);
    ptTcb = &s_tTcb[(uint32_t)eId];

    if(ptTcb->eOps == TEMPSENS_OPS_INTR)
    {
        SET_TEMPSENS_IER_EN(ptTs, true);
    }

    SET_TEMPSENS_CR_START(ptTs, true);

    return eErr;
}

HAL_ERR_e HAL_TEMPSENS_Stop(TEMPSENS_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TEMPSENS_Type *ptTs;
    TEMPSENS_CTRL_BLK_t *ptTcb;

    if((uint32_t)eId >= TEMPSENS_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTs = PRV_TEMPSENS_GetReg((P_TEMPSENS_ID_e)eId);
    ptTcb = &s_tTcb[(uint32_t)eId];

    if(ptTcb->eOps == TEMPSENS_OPS_INTR)
    {
        SET_TEMPSENS_IER_EN(ptTs, false);
    }

    SET_TEMPSENS_CR_START(ptTs, false);

    return eErr;
}

HAL_ERR_e HAL_TEMPSENS_GetData(TEMPSENS_ID_e eId, uint32_t *pun32Data)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TEMPSENS_Type *ptTs;

    if((uint32_t)eId >= TEMPSENS_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTs = PRV_TEMPSENS_GetReg((P_TEMPSENS_ID_e)eId);
    *pun32Data = GET_TEMPSENS_DR_SENSE(ptTs);

    return eErr;
}

HAL_ERR_e HAL_TEMPSENS_GetTemp(TEMPSENS_ID_e eId, int8_t *pn8Temp)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
#if defined (TEMPSENS_FEATURE_READ_REF_DATA_VX) || defined (TEMPSENS_FEATURE_READ_REF_DATA_FX)
    TEMPSENS_Type *ptTs;
    TEMPSENS_CTRL_BLK_t *ptTcb;
    uint32_t un32SensCnt = 0;
#endif
    float fTemp = 0;

    if((uint32_t)eId >= TEMPSENS_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if defined (TEMPSENS_FEATURE_READ_REF_DATA_VX) || defined (TEMPSENS_FEATURE_READ_REF_DATA_FX)
    ptTs = PRV_TEMPSENS_GetReg((P_TEMPSENS_ID_e)eId);
    ptTcb = &s_tTcb[(uint32_t)eId];
    un32SensCnt = GET_TEMPSENS_DR_SENSE(ptTs);
#endif

    
#if defined (TEMPSENS_FEATURE_READ_REF_DATA_VX)
    fTemp = (float)(ptTcb->fSlope * un32SensCnt) + ptTcb->fOffset;
#elif defined (TEMPSENS_FEATURE_READ_REF_DATA_FX)
    fTemp = (((un32SensCnt/1000) - ptTcb->fOffset) / (float)ptTcb->fSlope) + 30;
#endif
    *pn8Temp = (int8_t)fTemp;

    return eErr;
}

HAL_ERR_e HAL_TEMPSENS_SetWaitComplete(TEMPSENS_ID_e eId, uint32_t un32Timeout)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TEMPSENS_Type *ptTs;

    if((uint32_t)eId >= TEMPSENS_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTs = PRV_TEMPSENS_GetReg((P_TEMPSENS_ID_e)eId);

    while(!GET_TEMPSENS_SR_FLAG(ptTs))
    {
        un32Timeout--;
        if(un32Timeout == 0)
        {
            eErr = HAL_ERR_TIMEOUT;
            break;
        }
    }

    SET_TEMPSENS_SR_FLAG(ptTs, true);

    return eErr;
}

void PRV_TEMPSENS_IRQHandler(TEMPSENS_ID_e eId)
{
    TEMPSENS_Type *ptTs;
    TEMPSENS_CTRL_BLK_t *ptTcb;
    uint32_t un32Event = 0;

    if((uint32_t)eId >= TEMPSENS_CH_NUM)
    {
        return;
    }

    ptTs = TEMPSENS_GetReg((P_TEMPSENS_ID_e)eId);
    ptTcb = &s_tTcb[(uint32_t)eId];

    switch(ptTcb->eOps)
    {
        case TEMPSENS_OPS_INTR:
             if(GET_TEMPSENS_SR_FLAG(ptTs))
             {
                 un32Event |= TEMPSENS_EVENT_MATCHED;
             }
             SET_TEMPSENS_SR_FLAG(ptTs, true);
             break;
        default:
             break;
    }

    if(ptTcb != NULL)
    {
        if(ptTcb->pfnHandler != NULL && un32Event != 0)
        {
            ptTcb->pfnHandler(un32Event, ptTcb->pContext);
        }
    }
}

void TEMPSENS0_IRQHandler(void)
{
    PRV_TEMPSENS_IRQHandler(TEMPSENS_ID_0);
}

#endif /* _TEMPSENS */
