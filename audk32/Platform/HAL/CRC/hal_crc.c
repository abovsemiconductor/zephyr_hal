/**
 *******************************************************************************
 * @file        hal_crc.c
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

#if defined(_CRC)
#include "hal_crc.h"
#include "hal_crc_prv.h"

#if defined(_DMAC) && defined(DMA_CRC_NUM)
#include "hpl_dma.h"
#endif

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
#include "hpl_nmi.h"
#endif

typedef struct
{
    CRC_OPS_e               eOps;
    pfnCRC_IRQ_Handler_t    pfnHandler;
    void                    *pContext;

#if defined(_DMAC) && defined(DMA_CRC_NUM)
    DMA_ID_e                eDmaId;
    bool                    bDmaEnable;
#endif

    uint8_t                 *pun8Value;
    uint32_t                *pun32AlignData;

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
    bool                    bNmiEnable;
#endif
} CRC_CTRL_BLK_t;

static CRC_CTRL_BLK_t s_tCcb[CRC_CH_NUM];

static void PRV_CRC_IRQHandler(CRC_ID_e eId);

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
static void PRV_CRC_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < CRC_CH_NUM; i++)
    {
        if(s_tCcb[i].bNmiEnable == true)
        {
            PRV_CRC_IRQHandler((CRC_ID_e)i);
        }
    }
}
#endif

static CRC_Type *PRV_CRC_GetReg(P_CRC_ID_e eId)
{
    return CRC_GetReg((P_CRC_ID_e)eId);
}

static HAL_ERR_e PRV_CRC_SetScuEnable(P_CRC_ID_e eId, bool bEnable)
{
    return CRC_SetScuEnable((P_CRC_ID_e)eId, bEnable);
}

HAL_ERR_e HAL_CRC_Init(CRC_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= CRC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_CRC_SetScuEnable((P_CRC_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tCcb[(uint32_t)eId], 0x00, sizeof(CRC_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_CRC_Uninit(CRC_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= CRC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_CRC_SetScuEnable((P_CRC_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tCcb[(uint32_t)eId], 0x00, sizeof(CRC_CTRL_BLK_t));

    /* Forcily, disable NVIC Interrupt */
    eIrq = CRC_GetIRQNum((P_CRC_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_CRC_SetConfig(CRC_ID_e eId, CRC_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    CRC_Type *ptCrc;
#if defined(_DMAC) && defined(DMA_CRC_NUM)
    CRC_CTRL_BLK_t *ptCcb;
    P_CRC_DMA_BUS_SIZE_e eBusSize;
    DMA_ID_e eDmaId;
    DMA_CFG_t tCfg =
    {
        .un32PeriNum = 0,
        .eSize = DMA_BUS_SIZE_WORD,
        .eDir = DMA_DIR_MEM_TO_PERI
    };
#endif

    if((uint32_t)eId >= CRC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptCrc = PRV_CRC_GetReg((P_CRC_ID_e)eId);
#if defined(_DMAC) && defined(DMA_CRC_NUM)
    ptCcb = &s_tCcb[(uint32_t)eId];
#endif

    if(ptCfg->eMode == CRC_MODE_CHKSUM)
    {
        if(CRC_CHKSUM_NOT_AVAIL)
        {
            return HAL_ERR_NOT_SUPPORTED;
        }
    }

    if(ptCfg->eMode == CRC_MODE_CRC)
    {
        eErr = CRC_GetSupportPoly((P_CRC_POLY_e)ptCfg->ePoly);
        if(eErr != HAL_ERR_OK)
        {
            return HAL_ERR_NOT_SUPPORTED;
        }
    }

    SET_CRC_CR_MODE(ptCrc, ptCfg->eMode);    /* Set CRC or Checksum(if support) */
    SET_CRC_CR_OP_MODE(ptCrc, false);    /* Forcibly, disable Auto mode */

#if defined(_DMAC) && defined(DMA_CRC_NUM)
    ptCcb->bDmaEnable = false;
#endif

    if(ptCfg->bIntrEnable == true)
    {
#if defined(_DMAC) && defined(DMA_CRC_NUM)
        eErr = (HAL_ERR_e)HPL_DMA_GetAvailChannel(&eDmaId);
        if(eErr != HAL_ERR_OK)
        {
            return eErr;
        }

        eBusSize = CRC_GetDMABusSize();
        switch(eBusSize)
        {
            case P_CRC_DMA_BUS_SIZE_WORD:
                tCfg.eSize = DMA_BUS_SIZE_WORD;
                break;
            case P_CRC_DMA_BUS_SIZE_BYTE:
            default:
                tCfg.eSize = DMA_BUS_SIZE_BYTE;
                break;
        }

        eErr = HPL_DMA_Init(DMA_PERI_CRC, (uint8_t)eId);
        if(eErr != HAL_ERR_OK)
        {
            return eErr;
        }

        eErr = (HAL_ERR_e)HPL_DMA_GetPeriSelectNumber(DMA_PERI_CRC, DMA_PERI_ID_0, DMA_PERI_COM_TX, &tCfg.un32PeriNum);
        if(eErr == HAL_ERR_OK)
        {
            ptCcb->bDmaEnable = true;
            ptCcb->eDmaId = eDmaId;
            HPL_DMA_SetConfig(ptCcb->eDmaId, &tCfg);
        }
        else
        {
            return eErr;
        }
#endif
    }

    SET_CRC_CR_POLY(ptCrc, CRC_INT_POLY(ptCfg->ePoly));     /* Polynomial Mode */
    SET_CRC_CR_INP(ptCrc, CRC_INT_INP(ptCfg->eFirstIn));    /* First-In Mode (LSB or MSB) */

    /* Output Control if Support */
    SET_CRC_CR_OUTP(ptCrc, ptCfg->tOutputCfg.eFirstOut);
    SET_CRC_CR_OUTP_INV(ptCrc, ptCfg->tOutputCfg.eInv);

#if defined (CRC_FEATURE_INPUT_CONF_MODE)
    SET_CRC_CR_INDATA_SIZE(ptCrc, ptCfg->tInputCfg.eInDataSize);
    SET_CRC_CR_INDATA_COMPLE(ptCrc, ptCfg->tInputCfg.bComplement);
#endif

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_CRC_SetIRQ(CRC_ID_e eId, CRC_OPS_e eOps, pfnCRC_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio)
{
#if defined(CRC_FEATURE_UNSUPPORT_IRQ)
    return HAL_ERR_NOT_SUPPORTED;
#else
    HAL_ERR_e eErr = HAL_ERR_OK;
    CRC_CTRL_BLK_t *ptCcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= CRC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(eOps == CRC_OPS_INTR_DMA)
    {
#if defined(_DMAC) && defined(DMA_CRC_NUM)
#else
        return HAL_ERR_NOT_SUPPORTED;
#endif
    }

    ptCcb = &s_tCcb[(uint32_t)eId];
    eIrq = CRC_GetIRQNum((P_CRC_ID_e)eId);

    switch(eOps)
    {
#if defined(_DMAC) && defined(DMA_CRC_NUM)
        case CRC_OPS_INTR_DMA:
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            if(ptCcb->bNmiEnable == true)
            {
                (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
                ptCcb->bNmiEnable = false;
            }
#endif
            ptCcb->pfnHandler = pfnHandler;
            ptCcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            break;
#endif

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
        case CRC_OPS_NMI_DMA:
            eErr = HPL_NMI_SetSource(eIrq, &PRV_CRC_NMIHandler, pContext, true);
            if(eErr == HAL_ERR_OK)
            {
                ptCcb->pfnHandler = pfnHandler;
                ptCcb->pContext = pContext;
            }
            ptCcb->bNmiEnable = true;
            break;
#endif
        case CRC_OPS_POLL:
        default:
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
            ptCcb->bNmiEnable = false;
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptCcb->pContext = NULL;
            ptCcb->pfnHandler = NULL;
            break;
    }

    ptCcb->eOps = eOps;

    return eErr;
#endif
}

HAL_ERR_e HAL_CRC_SetCompute(CRC_ID_e eId, uint32_t un32Init, uint8_t *pun8Data, uint32_t un32Len, uint32_t *pun32Out)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    CRC_Type *ptCrc;
#if defined(_DMAC) && defined(DMA_CRC_NUM)
    CRC_CTRL_BLK_t *ptCcb;
    uint32_t un32IDR = 0;
    uint32_t un32AlignData = 0;
    uint32_t un32AlignLen = 0;
#endif

    if((uint32_t)eId >= CRC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptCrc = PRV_CRC_GetReg((P_CRC_ID_e)eId);
#if defined(_DMAC) && defined(DMA_CRC_NUM)
    ptCcb = &s_tCcb[(uint32_t)eId];
#endif

    SET_CRC_CR_OUT_CLR(ptCrc, true);
    SET_CRC_DR_INIT(ptCrc, un32Init);
    SET_CRC_CR_EN(ptCrc, true);

#if defined(_DMAC) && defined(DMA_CRC_NUM)
    if(ptCcb->bDmaEnable)
    {
        ptCcb->pun8Value = pun8Data;
        SET_CRC_IER_DMA_EN(ptCrc, true);
        eErr = CRC_GetAlignData(pun8Data, un32Len, &un32AlignData, &un32AlignLen);
        if(eErr != HAL_ERR_OK)
            return eErr;

        un32IDR = (uint32_t)GET_CRC_IN_ADDR(ptCrc);

        if(un32AlignLen == 0)
        {
            ptCcb->pun32AlignData = NULL;
            HPL_DMA_Start(ptCcb->eDmaId, (uint32_t)pun8Data, un32IDR, un32Len);
        }
        else
        {
            ptCcb->pun32AlignData = (uint32_t *)un32AlignData;
            HPL_DMA_Start(ptCcb->eDmaId, (uint32_t)ptCcb->pun32AlignData, un32IDR, un32AlignLen);
        }
    }
    else
#endif
    {
        CRC_SetData(ptCrc, pun8Data, un32Len);
        *pun32Out = GET_CRC_DR_OUT(ptCrc);
        SET_CRC_CR_EN(ptCrc, false);
    }

    return eErr;
}

HAL_ERR_e HAL_CRC_GetResult(CRC_ID_e eId, uint32_t *pun32Out)
{
    CRC_Type *ptCrc;

    if((uint32_t)eId >= CRC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptCrc = PRV_CRC_GetReg((P_CRC_ID_e)eId);
    *pun32Out = GET_CRC_DR_OUT(ptCrc);

     return HAL_ERR_OK;
}

HAL_ERR_e HAL_CRC_SetWaitComplete(CRC_ID_e eId, uint32_t un32Timeout)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
#if defined(_DMAC) && defined(DMA_CRC_NUM)
    CRC_CTRL_BLK_t *ptCcb;
#endif

    if((uint32_t)eId >= CRC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if defined(_DMAC) && defined(DMA_CRC_NUM)
    ptCcb = &s_tCcb[(uint32_t)eId];
    if(ptCcb->bDmaEnable)
    {
        eErr = (HAL_ERR_e)HPL_DMA_SetWaitComplete(ptCcb->eDmaId, un32Timeout);
    }
#endif

    return eErr;
}

HAL_ERR_e HAL_CRC_SetIRQClear(CRC_ID_e eId)
{
#if defined(CRC_FEATURE_UNSUPPORT_IRQ)
    return HAL_ERR_NOT_SUPPORTED;
#else
    CRC_Type *ptCrc;
#if defined(_DMAC) && defined(DMA_CRC_NUM)
    CRC_CTRL_BLK_t *ptCcb;
#endif

    if((uint32_t)eId >= CRC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptCrc = PRV_CRC_GetReg((P_CRC_ID_e)eId);

    SET_CRC_IER_DMA_EN(ptCrc, false);

    SET_CRC_IER_DMA_FLAG(ptCrc, true);

#if defined(_DMAC) && defined(DMA_CRC_NUM)
    ptCcb = &s_tCcb[(uint32_t)eId];

    HPL_DMA_SetClear(ptCcb->eDmaId);

    HPL_DMA_Stop(ptCcb->eDmaId);
    
    HPL_DMA_Uninit(DMA_PERI_CRC, (uint8_t)eId);
#endif

    return HAL_ERR_OK;
#endif
}

void PRV_CRC_IRQHandler(CRC_ID_e eId)
{
#if defined(CRC_FEATURE_UNSUPPORT_IRQ)
    return;
#else
    CRC_Type *ptCrc = (CRC_Type *)CRC_BASE;
    CRC_CTRL_BLK_t *ptCcb;

    if((uint32_t)eId >= CRC_CH_NUM)
    {
        return;
    }

    ptCrc = PRV_CRC_GetReg((P_CRC_ID_e)eId);
    ptCcb = &s_tCcb[(uint32_t)eId];

    SET_CRC_IER_DMA_EN(ptCrc, false);
    SET_CRC_IER_DMA_FLAG(ptCrc, true);

#if defined(_DMAC) && defined(DMA_CRC_NUM)
    HPL_DMA_SetClear(ptCcb->eDmaId);
    HPL_DMA_Stop(ptCcb->eDmaId);
    HPL_DMA_Uninit(DMA_PERI_CRC, (uint8_t)eId);
#endif

    if(ptCcb->pun32AlignData != NULL)
    {
        free(ptCcb->pun32AlignData);
        ptCcb->pun32AlignData = NULL;
    }

    if(ptCcb->pfnHandler != NULL)
    {
        ptCcb->pfnHandler(0, ptCcb->pContext);
    }
#endif
}

void CRC0_IRQHandler(void)
{
    PRV_CRC_IRQHandler(CRC_ID_0);
}

void CRC1_IRQHandler(void)
{
    PRV_CRC_IRQHandler(CRC_ID_1);
}

#endif /* _CRC */
