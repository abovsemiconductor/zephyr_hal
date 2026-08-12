/**
 *******************************************************************************
 * @file        hal_dac.c
 * @author      ABOV R&D Division
 * @brief       N-bits Digital to Analog Converter
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

#if defined(_DAC)
#include "hal_dac.h"
#include "hal_dac_prv.h"

#if defined(_DMAC) && defined(DMA_DAC_NUM)
#include "hpl_dma.h"
#endif

typedef struct
{

    DAC_OPS_e             eOps;
#if ((CONFIG_DAC_OPS_INTERRUPT == 1) || CONFIG_DAC_OPS_INTERRUPT_DMA == 1)
    pfnDAC_IRQ_Handler_t pfnHandler;
    void                 *pContext;

#if defined(_DMAC) && defined(DMA_DAC_NUM)
    bool                 bDmaEnabled;
    DMA_ID_e             eDmaId;
#endif

#endif

    DAC_MODE_e           eMode;
    DAC_AUTO_DIR_e       eAutoDir;
} DAC_CTRL_BLK_t;

static DAC_CTRL_BLK_t s_tDcb[DAC_CH_NUM];

static DAC_Type *PRV_DAC_GetReg(P_DAC_ID_e eId)
{
    return DAC_GetReg((P_DAC_ID_e)eId);
}

static HAL_ERR_e PRV_DAC_SetScuEnable(P_DAC_ID_e eId, bool bEnable)
{
    return DAC_SetScuEnable((P_DAC_ID_e)eId, bEnable);
}

HAL_ERR_e HAL_DAC_Init(DAC_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= DAC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_DAC_SetScuEnable((P_DAC_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tDcb[(uint32_t)eId], 0, sizeof(DAC_CTRL_BLK_t));

    return eErr;
}

HAL_ERR_e HAL_DAC_Uninit(DAC_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
#if (CONFIG_DAC_OPS_INTERRUPT == 1)
    IRQn_Type eIrq;
#endif

    if((uint32_t)eId >= DAC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_DAC_SetScuEnable((P_DAC_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

#if (CONFIG_DAC_OPS_INTERRUPT == 1)
    /* Forcily, disable NVIC Interrupt */
    eIrq = DAC_GetIRQNum((P_DAC_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);
#endif

    memset(&s_tDcb[(uint32_t)eId], 0, sizeof(DAC_CTRL_BLK_t));

    return eErr;
}

uint32_t HAL_DAC_GetMaxResolution(void)
{
    return DAC_RESOLUTION;
}

HAL_ERR_e HAL_DAC_SetConfig(DAC_ID_e eId, DAC_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    DAC_Type *ptDac;
    DAC_CTRL_BLK_t *ptDcb;

    if((uint32_t)eId >= DAC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptDac = PRV_DAC_GetReg((P_DAC_ID_e)eId);
    ptDcb = &s_tDcb[(uint32_t)eId];

    SET_DAC_CR_RELOAD(ptDac, DAC_RELOAD(ptCfg->eRLod));
    SET_DAC_CR_REF(ptDac, ptCfg->eRef);
#if defined(DAC_FEATURE_BIAS_ENABLE)
    SET_DAC_CR_BIAS_EN(ptDac, true);
#endif
#if defined(DAC_FEATURE_OUTPUT_BUFFER)
    SET_DAC_CR_BUF_MODE_EN(ptDac, ptCfg->bOutBuffer);
    SET_DAC_CR_BUF_EN(ptDac, ptCfg->bOutBuffer);
    SET_DAC_CR_BYPASS_MODE_EN(ptDac, !ptCfg->bOutBuffer);
#endif
    SET_DAC_CR_PG(ptDac, ptCfg->ePg);

    eErr = DAC_SetOutPort(ptDac, ptCfg->un8OutPort);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    ptDcb->eMode = ptCfg->eMode;
    ptDcb->eAutoDir = ptCfg->eAutoDir;

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_DAC_SetOfsConfig(DAC_ID_e eId, DAC_OFS_CFG_t *ptCfg)
{
#if defined(DAC_FEATURE_BUFFER_OFFSET)
    DAC_Type *ptDac;

    if((uint32_t)eId >= DAC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptDac = PRV_DAC_GetReg((P_DAC_ID_e)eId);

    SET_DAC_CR_OFS_EN(ptDac, ptCfg->bEnable);
    SET_DAC_CR_OFS_DIR(ptDac, ptCfg->eOfs);
    SET_DAC_DR_OFS(ptDac, ptCfg->un8Ofs);

    return HAL_ERR_OK;
#else
    (void)eId;
    (void)*ptCfg;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_DAC_SetIRQ(DAC_ID_e eId, DAC_OPS_e eOps, pfnDAC_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    DAC_CTRL_BLK_t *ptDcb;
#if (CONFIG_DAC_OPS_INTERRUPT == 1 || CONFIG_DAC_OPS_INTERRUPT_DMA == 1)
    IRQn_Type eIrq;
#if defined(_DMAC) && defined(DMA_DAC_NUM)
    DMA_ID_e eDmaId;
#endif
#endif

    if((uint32_t)eId >= DAC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(eOps == DAC_OPS_INTR)
    {
#if (CONFIG_DAC_OPS_INTERRUPT == 1)
#else
        return HAL_ERR_NOT_SUPPORTED;
#endif
    }

    if(eOps == DAC_OPS_INTR_DMA)
    {
#if (CONFIG_DAC_OPS_INTERRUPT_DMA == 1)
#else
        return HAL_ERR_NOT_SUPPORTED;
#endif
    }

    ptDcb = &s_tDcb[(uint32_t)eId];
#if (CONFIG_DAC_OPS_INTERRUPT == 1 || CONFIG_DAC_OPS_INTERRUPT_DMA == 1)
    eIrq = DAC_GetIRQNum((P_DAC_ID_e)eId);
#endif

    switch(eOps)
    {
#if (CONFIG_DAC_OPS_INTERRUPT == 1 || CONFIG_DAC_OPS_INTERRUPT_DMA == 1)
        case DAC_OPS_INTR:
        case DAC_OPS_INTR_DMA:
            ptDcb->pfnHandler = pfnHandler;
            ptDcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
#if defined(_DMAC) && defined(DMA_DAC_NUM)
            if(eOps == DAC_OPS_INTR_DMA)
            {
                eErr = HPL_DMA_Init(DMA_PERI_DAC, (uint8_t)eId);
                if(eErr != HAL_ERR_OK)
                {
                    return eErr;
                }
                eErr = (HAL_ERR_e)HPL_DMA_GetAvailChannel(&eDmaId);
                if(eErr == HAL_ERR_OK)
                {
                    ptDcb->eDmaId = eDmaId;
                    ptDcb->bDmaEnabled = true;
                }
            }
#endif
            break;
#endif
        case DAC_OPS_POLL:
        default:
#if (CONFIG_DAC_OPS_INTERRUPT == 1 || CONFIG_DAC_OPS_INTERRUPT_DMA == 1)
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
#if defined(_DMAC) && defined(DMA_DAC_NUM)
            if(ptDcb->bDmaEnabled == true)
            {
                HPL_DMA_Uninit(DMA_PERI_DAC, (uint8_t)eId);
                ptDcb->bDmaEnabled = false;
            }
#endif
            ptDcb->pContext = NULL;
            ptDcb->pfnHandler = NULL;
#endif
            break;
    }

    ptDcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_DAC_SetDMA(DAC_ID_e eId, uint32_t un32Addr, uint32_t un32Len)
{
#if defined(_DMAC) && defined(DMA_DAC_NUM)
    HAL_ERR_e eErr = HAL_ERR_OK;
    DAC_Type *ptDac;
    DAC_CTRL_BLK_t *ptDcb;
    DMA_CFG_t tDmaCfg =
    {
        .un32PeriNum = 0,
        .eSize = DMA_BUS_SIZE_HALFWORD,
        .eDir = DMA_DIR_MEM_TO_PERI
    };

    if((uint32_t)eId >= DAC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptDac = PRV_DAC_GetReg((P_DAC_ID_e)eId);
    ptDcb = &s_tDcb[(uint32_t)eId];

    eErr = (HAL_ERR_e)HPL_DMA_GetPeriSelectNumber(DMA_PERI_DAC, (DMA_PERI_ID_e)eId, DMA_PERI_COM_TX, &tDmaCfg.un32PeriNum);
    if(eErr == HAL_ERR_OK)
    {
        HPL_DMA_SetConfig(ptDcb->eDmaId, &tDmaCfg);
        SET_DAC_IER_DMA_FLAG(ptDac, true);
        SET_DAC_IER_DMA_UNDER_FLAG(ptDac, true);
        SET_DAC_IER_DMA_EN(ptDac, true);
        SET_DAC_IER_DMA_UNDER_EN(ptDac, true);
        HPL_DMA_Start(ptDcb->eDmaId, un32Addr, (uint32_t)GET_DAC_DR_ADDR(ptDac), un32Len);
    }

    return eErr;
#else
    (void)eId;
    (void)un32Addr;
    (void)un32Len;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_DAC_Start(DAC_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    DAC_Type *ptDac;
    DAC_CTRL_BLK_t *ptDcb;

    if((uint32_t)eId >= DAC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptDac = PRV_DAC_GetReg((P_DAC_ID_e)eId);
    ptDcb = &s_tDcb[(uint32_t)eId];

    SET_DAC_CR_BF_CLEAR(ptDac, true);
    SET_DAC_CR_AUTO(ptDac, ptDcb->eMode);

    if(ptDcb->eMode == DAC_MODE_AUTO)
    {
        if(ptDcb->eAutoDir == DAC_AUTO_DIR_INC)
        {
            SET_DAC_CR_EN(ptDac, true);
        }
        else
        {
            SET_DAC_CR_EN(ptDac, false);
        }

#if (CONFIG_DAC_OPS_INTERRUPT == 1)
        /* Only interrupt for auto incre/decre mode */
        if(ptDcb->eOps == DAC_OPS_INTR)
        {
            SET_DAC_IER_EN(ptDac, true);
        }
#endif

    }
    else
    {
        SET_DAC_CR_EN(ptDac, true);
    }

#if defined(DAC_FEATURE_BUFFER_ENABLE_WITH_DELAY)
    SystemDelayUS(50);
    SET_DAC_CR_BUF_EN(ptDac, true);
#endif

    return eErr;
}

HAL_ERR_e HAL_DAC_Stop(DAC_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    DAC_Type *ptDac = (DAC_Type *)DAC_BASE;

    if((uint32_t)eId >= DAC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptDac = PRV_DAC_GetReg((P_DAC_ID_e)eId);

    SET_DAC_CR_EN(ptDac, false);

    return eErr;
}

HAL_ERR_e HAL_DAC_SetData(DAC_ID_e eId, uint16_t un16Data)
{
    DAC_Type *ptDac;

    if((uint32_t)eId >= DAC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptDac = PRV_DAC_GetReg((P_DAC_ID_e)eId);
    SET_DAC_DR_IN(ptDac, un16Data << DAC_DR_SHIFT);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_DAC_GetData(DAC_ID_e eId, uint16_t *pun16Data)
{
    DAC_Type *ptDac;

    if((uint32_t)eId >= DAC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptDac = PRV_DAC_GetReg((P_DAC_ID_e)eId);
    *pun16Data = GET_DAC_DR_OUT(ptDac);

    return HAL_ERR_OK;
}

#if (CONFIG_DAC_OPS_INTERRUPT == 1 || CONFIG_DAC_OPS_INTERRUPT_DMA == 1)
void PRV_DAC_IRQHandler(DAC_ID_e eId)
{
    DAC_Type *ptDac;
    DAC_CTRL_BLK_t *ptDcb;
    uint32_t un32Event = 0;

    ptDac = PRV_DAC_GetReg((P_DAC_ID_e)eId);
    ptDcb = &s_tDcb[(uint32_t)eId];

    switch(ptDcb->eOps)
    {
        case DAC_OPS_INTR:
            if(GET_DAC_IER_FLAG(ptDac))
            {
                un32Event |= DAC_EVENT_DATA_REACHED;
            }
            SET_DAC_IER_FLAG(ptDac, true);
            SET_DAC_IER_EN(ptDac, false);
            break;
#if defined(_DMAC) && defined(DMA_DAC_NUM)
        case DAC_OPS_INTR_DMA:
            if(GET_DAC_IER_DMA_FLAG(ptDac))
            {
                un32Event |= DAC_EVENT_RX_DONE;
                SET_DAC_IER_DMA_FLAG(ptDac, true);
            }

            SET_DAC_IER_DMA_EN(ptDac, false);

            if(GET_DAC_IER_DMA_UNDER_FLAG(ptDac))
            {
                un32Event |= DAC_EVENT_RX_UNDERRUN;
                SET_DAC_IER_DMA_UNDER_FLAG(ptDac, true);
            }

            SET_DAC_IER_DMA_UNDER_FLAG(ptDac, false);
            HPL_DMA_Stop(ptDcb->eDmaId);
            break;
#endif
        default:
            break;
    }

    if(ptDcb->pfnHandler != NULL && un32Event != 0)
    {
        ptDcb->pfnHandler(un32Event, ptDcb->pContext);
    }
}

void DAC0_IRQHandler(void)
{
    PRV_DAC_IRQHandler(DAC_ID_0);
}

#endif

#endif /* _DAC */
