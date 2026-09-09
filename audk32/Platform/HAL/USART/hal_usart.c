/**
 *******************************************************************************
 * @file        hal_usart.c
 * @author      ABOV R&D Division
 * @brief       USART serial communication
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

#if defined(_USART)
#include "hal_usart.h"
#include "hal_usart_prv.h"

#include "hll_usart.h"

#if defined(_DMAC) && defined(DMA_USART_NUM)
#include "hpl_dma.h"
#endif

typedef struct
{
    USART_OPS_e               eOps;
    pfnUSART_IRQ_Handler_t    pfnHandler;
    void                      *pContext;

#if defined(_DMAC) && defined(DMA_USART_NUM)
    DMA_ID_e                  eDmaId;
    bool                      bDmaEnabled;
#endif
    USART_MODE_e              eMode;
    USART_DATA_e              eData;
#if defined(USART_FEATURE_RX_TIME_OUT)
    bool                      bRTOEnable;
#endif
    bool                      bSSGenDisable;
    bool                      bRxSCKGen;

    USART_BUSY_e              eTxBusy;
    USART_BUSY_e              eRxBusy;
    uint8_t                   *pun8TxBuf;
    uint8_t                   *pun8RxBuf;
    uint32_t                  un32TxLen;
    uint32_t                  un32RxLen;
    uint32_t                  un32TxCnt;
    uint32_t                  un32RxCnt;
} USART_CTRL_BLK_t;

static USART_CTRL_BLK_t s_tUcb[USART_CH_NUM];

static void PRV_USART_IRQHandler(USART_ID_e eId);

#if defined(_DMAC) && defined(DMA_USART_NUM) && defined (USART_FEATURE_DMA_INTERNAL_INTERRUPT)
static void PRV_USART_DMAHandler(uint32_t un32Event, void *pContext)
{
    PRV_USART_IRQHandler((USART_ID_e)(un32Event));
}
#endif

#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
static USART_Type *PRV_USART_GetReg(USART_ID_e eId)
{
    return USART_GetReg((uint32_t)eId);
}
#endif

#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
static HAL_ERR_e PRV_USART_SetScuEnable(P_USART_ID_e eId, bool bEnable)
{
    return USART_SetScuEnable((P_USART_ID_e)eId, bEnable);
}
#endif

HAL_ERR_e HAL_USART_Init(USART_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= USART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    eErr = HLL_USART_SetClockEnable(eId, true);
#else
    eErr = PRV_USART_SetScuEnable((P_USART_ID_e)eId, true);
#endif
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tUcb[(uint32_t)eId], 0x00, sizeof(USART_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_USART_Uninit(USART_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= USART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    eErr = HLL_USART_SetClockEnable(eId, false);
    eIrq = HLL_USART_GetIRQNum(eId);
#else
    eErr = PRV_USART_SetScuEnable((P_USART_ID_e)eId, false);
    eIrq = USART_GetIRQNum((P_USART_ID_e)eId);
#endif
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tUcb[(uint32_t)eId], 0x00, sizeof(USART_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_USART_SetConfig(USART_ID_e eId, USART_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    USART_CTRL_BLK_t *ptUcb;
    uint32_t un32Numer, un32Denom, un8Bcv = 2;
    uint32_t un32Bdr, un32Bfr, un32Fd;
#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    USART_Type *ptUsart;
#endif

    if((uint32_t)eId >= USART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    ptUsart = PRV_USART_GetReg(eId);
#endif
    ptUcb = &s_tUcb[(uint32_t)eId];

    /* Clear Control Regisers */
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_USART_ClearControl(eId);
#else
    SET_USART_CR(ptUsart, 0x00);
    SET_USART_CR2(ptUsart, 0x00);
#endif

    if(ptCfg->eMode < USART_MODE_MAX)
    {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
        HLL_USART_SetMode(eId, ptCfg->eMode);
#else
        SET_USART_CR_MODE(ptUsart, USART_MODE((uint8_t)ptCfg->eMode));
#endif
        ptUcb->eMode = ptCfg->eMode;
    }
    else
    {
        return HAL_ERR_PARAMETER;
    }

    switch(ptCfg->eMode)
    {
        case USART_MODE_UART:
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            HLL_USART_SetUartFormat(eId, ptCfg->tCfg.tUart.eParity, ptCfg->tCfg.tUart.eData,
                                     ptCfg->tCfg.tUart.eStop, ptCfg->tCfg.tUart.bDoubleSpeed);
#else
            SET_USART_CR_PARITY(ptUsart, USART_PARITY((uint8_t)ptCfg->tCfg.tUart.eParity));
            SET_USART_CR_DLEN(ptUsart, USART_DATA((uint8_t)ptCfg->tCfg.tUart.eData));
            SET_USART_CR_STOPBIT(ptUsart, (uint32_t)ptCfg->tCfg.tUart.eStop);
            SET_USART_CR_DBLS(ptUsart, ptCfg->tCfg.tUart.bDoubleSpeed);
#endif
            if(ptCfg->tCfg.tUart.bDoubleSpeed == true)
            {
                un8Bcv = 8;
            }
            else
            {
                un8Bcv = 16;
            }
            ptUcb->eData = ptCfg->tCfg.tUart.eData;
            break;
        case USART_MODE_USRT:
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            HLL_USART_SetUsrtFormat(eId, ptCfg->tCfg.tUsrt.eMs, ptCfg->tCfg.tUsrt.eParity,
                                     ptCfg->tCfg.tUsrt.eData, ptCfg->tCfg.tUsrt.eStop,
                                     ptCfg->tCfg.tUsrt.eClkPol);
#else
            SET_USART_CR_MS(ptUsart, (uint8_t)ptCfg->tCfg.tUsrt.eMs);
            SET_USART_CR_PARITY(ptUsart, USART_PARITY((uint8_t)ptCfg->tCfg.tUsrt.eParity));
            SET_USART_CR_DLEN(ptUsart, USART_DATA((uint8_t)ptCfg->tCfg.tUsrt.eData));
            SET_USART_CR_STOPBIT(ptUsart, (uint32_t)ptCfg->tCfg.tUsrt.eStop);
            SET_USART_CR_CPACK(ptUsart, (uint8_t)ptCfg->tCfg.tUsrt.eClkPol);
#endif
            ptUcb->eData = ptCfg->tCfg.tUsrt.eData;
            break;
        case USART_MODE_SPI:
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            HLL_USART_SetSpiFormat(eId, ptCfg->tCfg.tSpi.eMs, ptCfg->tCfg.tSpi.eBitOrder,
                                    ptCfg->tCfg.tSpi.eClkPol, ptCfg->tCfg.tSpi.eClkPha,
                                    ptCfg->tCfg.tSpi.bSwapMSPort);
#else
            SET_USART_CR_MS(ptUsart, (uint8_t)ptCfg->tCfg.tSpi.eMs);
            SET_USART_CR_BIT_ORDER(ptUsart, (uint8_t)ptCfg->tCfg.tSpi.eBitOrder);
            SET_USART_CR_CPACK(ptUsart, (uint8_t)ptCfg->tCfg.tSpi.eClkPol);
            SET_USART_CR_CPSCK(ptUsart, (uint8_t)ptCfg->tCfg.tSpi.eClkPha);
            SET_USART_CR_SWAP_MS_PORT(ptUsart, (uint8_t)ptCfg->tCfg.tSpi.bSwapMSPort);
#endif
            ptUcb->bSSGenDisable = ptCfg->tCfg.tSpi.bSSGenDisable;
            ptUcb->bRxSCKGen = ptCfg->tCfg.tSpi.bRxSCKGen;
#if defined(USART_FEATURE_RX_DISABLE_IN_SPI_SLAVE)
            if(ptCfg->tCfg.tSpi.eMs == USART_MS_SLAVE)
            {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
                HLL_USART_SetSpiSlaveRxEnable(eId, !ptCfg->tCfg.tSpi.bSlvRecvDisable);
#else
                SET_USART_CR_SREN(ptUsart, !ptCfg->tCfg.tSpi.bSlvRecvDisable);
#endif
            }
#endif
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

#if defined(USART_FEATURE_RX_TIME_OUT)
    if(ptCfg->tRTO.bEnable == true)
    {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
        HLL_USART_SetRtoCount(eId, ptCfg->tRTO.un32RTOCount);
#else
        SET_USART_CR_RTO_CNT(ptUsart, ptCfg->tRTO.un32RTOCount);
#endif
    }

    ptUcb->bRTOEnable = ptCfg->tRTO.bEnable;
#endif

    if(ptCfg->eMode == USART_MODE_SPI)
    {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
        HLL_USART_SetSpiBaudRaw(eId, (uint16_t)ptCfg->un32BaudRate & 0xFFFF);
#else
        SET_USART_CR_BDR(ptUsart, (uint16_t)ptCfg->un32BaudRate & 0xFFFF);
#endif
#if defined(USART_FEATURE_MASTER_SS_PIN_BY_GPIO)
        if(ptCfg->tCfg.tSpi.eMs == USART_MS_MASTER)
        {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            HLL_USART_SetSpiSSEnable(eId, false);
#else
            SET_USART_CR_SSEN(ptUsart, false);
#endif
        }
        else
#endif
        {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            HLL_USART_SetSpiSSEnable(eId, !ptCfg->tCfg.tSpi.bSSGenDisable);
#else
            SET_USART_CR_SSEN(ptUsart, !ptCfg->tCfg.tSpi.bSSGenDisable);
#endif
        }

    }
    else
    {
        un32Numer = PRV_USART_GetNumer();
        un32Denom = un8Bcv * ptCfg->un32BaudRate;
        un32Bdr = un32Numer / un32Denom;
        un32Fd = un32Numer - (un32Bdr * un32Denom);
        un32Bfr = (un32Fd * 256) / un32Denom;

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
        HLL_USART_SetBaudRate(eId, (un32Bdr - 1), un32Bfr);
#else
        SET_USART_CR_BDR(ptUsart, (uint32_t)((un32Bdr - 1) & 0xFFFF));
        SET_USART_CR_FPCR(ptUsart, (uint32_t)(un32Bfr & 0xFF));
        SET_USART_CR_FPCREN(ptUsart, true);
#endif

    }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_USART_SetTxEnable(eId, true);
    HLL_USART_SetRxEnable(eId, true);
#else
    SET_USART_CR_TXEN(ptUsart, true);
    SET_USART_CR_RXEN(ptUsart, true);
#endif

    /*
     * Must enable USART Block after setting Master mode or Polarity and Phase at SPI Mode.
     */
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_USART_SetEnable(eId, true);
#else
    SET_USART_CR_EN(ptUsart, true);
#endif

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_USART_SetIRQ(USART_ID_e eId, USART_OPS_e eOps, pfnUSART_IRQ_Handler_t pfnHandler,
                           void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    USART_CTRL_BLK_t *ptUcb;
    IRQn_Type eIrq;
#if defined(_DMAC) && defined(DMA_USART_NUM)
    DMA_ID_e eDmaId;
#endif

    if((uint32_t)eId >= USART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUcb = &s_tUcb[(uint32_t)eId];

    /*
     * NVIC setup is always performed here regardless of HLL support: only
     * the IRQ-number lookup below switches implementation. Whether the
     * fixed-name weak handlers this file installs (USARTx_IRQHandler) are
     * actually the ones wired into a given vector table is an integration
     * concern, not a reason to skip HAL-level IRQ setup.
     */
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    eIrq = HLL_USART_GetIRQNum(eId);
#else
    eIrq = USART_GetIRQNum((P_USART_ID_e)eId);
#endif

    switch(eOps)
    {
        case USART_OPS_INTR:
#if defined(_DMAC) && defined(DMA_USART_NUM)
        case USART_OPS_INTR_DMA:
#endif
#if defined(USART_FEATURE_IRQ_UNMASK_ENABLE)
            PRV_USART_SetIntrUnMask(eIrq, true);
#endif
            ptUcb->pfnHandler = pfnHandler;
            ptUcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);

#if defined(_DMAC) && defined(DMA_USART_NUM)
            if(eOps == USART_OPS_INTR_DMA)
            {
                eErr = HPL_DMA_Init(DMA_PERI_USART, (uint8_t)eId);
                if(eErr != HAL_ERR_OK)
                {
                    return eErr;
                }

                eErr = (HAL_ERR_e)HPL_DMA_GetAvailChannel(&eDmaId);
                if(eErr == HAL_ERR_OK)
                {
                    ptUcb->eDmaId = eDmaId;
                    ptUcb->bDmaEnabled = true;
                }
#if defined (USART_FEATURE_DMA_INTERNAL_INTERRUPT)
                eErr = HPL_DMA_SetIRQ(DMA_PERI_USART, &PRV_USART_DMAHandler, NULL, true);
                if(eErr != HAL_ERR_OK)
                {
                    return eErr;
                }
#endif
            }
#endif
             break;
        case USART_OPS_POLL:
        default:
#if defined(_DMAC) && defined(DMA_USART_NUM)
            if(ptUcb->bDmaEnabled == true)
            {
                HPL_DMA_Uninit(DMA_PERI_USART, (uint8_t)eId);
                ptUcb->bDmaEnabled = false;
            }
#endif
#if defined(USART_FEATURE_IRQ_UNMASK_ENABLE)
            PRV_USART_SetIntrUnMask(eIrq, false);
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptUcb->pfnHandler = NULL;
            ptUcb->pContext = NULL;
            break;
    }

    ptUcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_USART_Transmit(USART_ID_e eId, uint8_t *pun8Out, uint32_t un32Len, bool bEnForcePoll)
{
    USART_CTRL_BLK_t *ptUcb;
#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    USART_Type *ptUsart;
#endif
#if defined(_DMAC) && defined(DMA_USART_NUM)
    HAL_ERR_e eErr = HAL_ERR_OK;
    DMA_CFG_t tDmaCfg =
    {
        .ePeri = DMA_PERI_USART,
        .ePeriId = (DMA_PERI_ID_e)eId,
        .un32PeriNum = 0,
        .eSize = DMA_BUS_SIZE_BYTE,
        .eDir = DMA_DIR_MEM_TO_PERI
    };
#endif
#if defined (USART_FEATURE_NO_NINTH_BIT_REG)
    uint16_t un16Data = 0;
#endif

    if((uint32_t)eId >= USART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    ptUsart = PRV_USART_GetReg(eId);
#endif
    ptUcb = &s_tUcb[eId];

    if (ptUcb->eTxBusy == USART_BUSY_TX)
    {
        return HAL_ERR_BUSY;
    }

    ptUcb->eTxBusy = USART_BUSY_TX;
    ptUcb->pun8TxBuf = (uint8_t *)pun8Out;
    ptUcb->un32TxLen = un32Len;
    ptUcb->un32TxCnt = 0;

    if (ptUcb->eOps == USART_OPS_POLL || bEnForcePoll == true)
    {
        while (ptUcb->un32TxLen > ptUcb->un32TxCnt)
        {
            if(ptUcb->eMode != USART_MODE_SPI && ptUcb->eData == USART_DATA_9)
            {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
                HLL_USART_SetTxNinthBit(eId, (*(ptUcb->pun8TxBuf++) & 0x1) != 0);
#else
                SET_USART_CR_TXBIT_NINTH(ptUsart, (*(ptUcb->pun8TxBuf++) & 0x1));
#endif
            }

#if defined(USART_FEATURE_MASTER_SS_PIN_BY_GPIO)
            if(ptUcb->eMode == USART_MODE_SPI && !ptUcb->bSSGenDisable)
            {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
                HLL_USART_SetSpiSlaveSelect(eId, false);
#else
                USART_SetSSPort((P_USART_ID_e)eId, false);
#endif
            }
#endif
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            HLL_USART_TransmitByte(eId, *(ptUcb->pun8TxBuf++));
#else
            SET_USART_IER_DR_FLAG(ptUsart, true);
            SET_USART_DR(ptUsart, *(ptUcb->pun8TxBuf++));
#endif
            ptUcb->un32TxCnt++;
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            while (!HLL_USART_GetTxReady(eId))
            {
            }
#else
            while (!GET_USART_IER_DR_FLAG(ptUsart))
            {
            }
#endif
#if defined(USART_FEATURE_MASTER_SS_PIN_BY_GPIO)
            if(ptUcb->eMode == USART_MODE_SPI && !ptUcb->bSSGenDisable)
            {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
                HLL_USART_SetSpiSlaveSelect(eId, true);
#else
                USART_SetSSPort((P_USART_ID_e)eId, true);
#endif
            }
#endif
        }

        /* If bEnForcePoll == true, check and clear TX Complete Interrupt Flag */
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
        if(HLL_USART_GetTxIntrEnable(eId) && bEnForcePoll == true)
        {
            HLL_USART_SetTxIntrEnable(eId, false);
        }
#else
        if(GET_USART_IER_TXC_EN(ptUsart) && bEnForcePoll == true)
        {
            SET_USART_IER_TXC_EN(ptUsart, false);
        }
#endif

        ptUcb->eTxBusy = USART_BUSY_NONE;
    }
    else
    {
#if defined(_DMAC) && defined(DMA_USART_NUM)
        if(ptUcb->eOps == USART_OPS_INTR_DMA)
        {
            eErr = (HAL_ERR_e)HPL_DMA_GetPeriSelectNumber(DMA_PERI_USART, (DMA_PERI_ID_e)eId, DMA_PERI_COM_TX, &tDmaCfg.un32PeriNum);
            if(eErr == HAL_ERR_OK)
            {
                HPL_DMA_SetConfig(ptUcb->eDmaId, &tDmaCfg);
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
                HLL_USART_SetTxIntrEnable(eId, true);
                HPL_DMA_Start(ptUcb->eDmaId, (uint32_t)ptUcb->pun8TxBuf, (uint32_t)GET_USART_DR_TX_ADDR(PRV_USART_GetReg(eId)), ptUcb->un32TxLen);
#else
                SET_USART_IER_DMATXC_EN(ptUsart, true);
                HPL_DMA_Start(ptUcb->eDmaId, (uint32_t)ptUcb->pun8TxBuf, (uint32_t)GET_USART_DR_TX_ADDR(ptUsart), ptUcb->un32TxLen);
#endif
            }
        }
        else
#endif
        {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            if (HLL_USART_GetTxReady(eId))
            {
                if(ptUcb->eMode != USART_MODE_SPI && ptUcb->eData == USART_DATA_9)
                {
                    HLL_USART_SetTxNinthBit(eId, (*(ptUcb->pun8TxBuf++) & 0x1) != 0);
                }

                HLL_USART_TransmitByte(eId, *(ptUcb->pun8TxBuf++));
                ptUcb->un32TxCnt++;
            }

            HLL_USART_SetTxIntrEnable(eId, true);
#else
            if (GET_USART_IER_DR_FLAG(ptUsart))
            {
#if defined(USART_FEATURE_MASTER_SS_PIN_BY_GPIO)
                if(ptUcb->eMode == USART_MODE_SPI && !ptUcb->bSSGenDisable)
                {
                    USART_SetSSPort((P_USART_ID_e)eId, false);
                }
#endif
                if(ptUcb->eMode != USART_MODE_SPI && ptUcb->eData == USART_DATA_9)
                {

#if defined (USART_FEATURE_NO_NINTH_BIT_REG)
                    un16Data = ((*(ptUcb->pun8TxBuf++) & 0x1) << 8);
#else
                    SET_USART_CR_TXBIT_NINTH(ptUsart, (*(ptUcb->pun8TxBuf++) & 0x1));
#endif
                }

                SET_USART_IER_DR_FLAG(ptUsart, true);
#if defined (USART_FEATURE_NO_NINTH_BIT_REG)
                un16Data |= *(ptUcb->pun8TxBuf++);
                SET_USART_DR(ptUsart, un16Data);
#else
                SET_USART_DR(ptUsart, *(ptUcb->pun8TxBuf++));
#endif
                ptUcb->un32TxCnt++;
            }

            SET_USART_IER_TXC_EN(ptUsart, true);
#endif
        }
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_USART_Receive(USART_ID_e eId, uint8_t *pun8In, uint32_t un32Len, bool bEnForcePoll)
{
    USART_CTRL_BLK_t *ptUcb;
#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    USART_Type *ptUsart;
#endif
    uint32_t un32Status, un32Timeout;
    uint32_t un32Data;
    IRQn_Type eIrq;
    HAL_ERR_e eErr = HAL_ERR_OK;
#if defined(_DMAC) && defined(DMA_USART_NUM)
    DMA_CFG_t tDmaCfg =
    {
        .ePeri = DMA_PERI_USART,
        .ePeriId = (DMA_PERI_ID_e)eId,
        .un32PeriNum = 0,
        .eSize = DMA_BUS_SIZE_BYTE,
        .eDir = DMA_DIR_PERI_TO_MEM
    };
#endif

    if((uint32_t)eId >= USART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    ptUsart = PRV_USART_GetReg(eId);
#endif
    ptUcb = &s_tUcb[eId];

    if (ptUcb->eRxBusy == USART_BUSY_RX)
    {
        return HAL_ERR_BUSY;
    }

    ptUcb->eRxBusy = USART_BUSY_RX;
    ptUcb->pun8RxBuf = (uint8_t *)pun8In;
    ptUcb->un32RxLen = un32Len;
    ptUcb->un32RxCnt = 0;

#if defined(USART_FEATURE_RX_TIME_OUT)
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_USART_SetRtoEnable(eId, ptUcb->bRTOEnable);
#else
    SET_USART_CR_RTO_EN(ptUsart, ptUcb->bRTOEnable);
#endif
#endif

    if (ptUcb->eOps == USART_OPS_POLL || bEnForcePoll == true)
    {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
        eIrq = HLL_USART_GetIRQNum(eId);
#else
        eIrq = USART_GetIRQNum((P_USART_ID_e)eId);
#endif
        if (ptUcb->eOps != USART_OPS_POLL)
        {
            NVIC_DisableIRQ(eIrq);
        }

        while (ptUcb->un32RxLen > ptUcb->un32RxCnt)
        {
            un32Status = 0;
            un32Timeout = USART_RX_TIMEOUT;

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            while (!HLL_USART_GetRxReady(eId) && un32Timeout)
#else
            while (!GET_USART_IER_RXC_FLAG(ptUsart) && un32Timeout)
#endif
            {
                un32Timeout--;
            }

            if (un32Timeout == 0)
            {
                ptUcb->eRxBusy = USART_BUSY_NONE;
                eErr = HAL_ERR_TIMEOUT;
                break;
            }

            if (un32Status)
            {
                ptUcb->eRxBusy = USART_BUSY_NONE;
                eErr = HAL_ERR_HW;
                break;
            }

            if(ptUcb->eMode != USART_MODE_SPI && ptUcb->eData == USART_DATA_9)
            {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
                *(ptUcb->pun8RxBuf++) = HLL_USART_GetRxNinthBit(eId);
#else
                *(ptUcb->pun8RxBuf++) = GET_USART_CR_RXBIT_NINTH(ptUsart);
#endif
            }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            *(ptUcb->pun8RxBuf++) = (uint8_t)HLL_USART_ReceiveByte(eId);
#else
            *(ptUcb->pun8RxBuf++) = GET_USART_DR(ptUsart);
#endif
            ptUcb->un32RxCnt++;
        }

        ptUcb->eRxBusy = USART_BUSY_NONE;

        if (ptUcb->eOps != USART_OPS_POLL)
        {
            NVIC_EnableIRQ(eIrq);
        }
    }
    else
    {
#if defined(_DMAC) && defined(DMA_USART_NUM)
        if(ptUcb->eOps == USART_OPS_INTR_DMA)
        {
            eErr = (HAL_ERR_e)HPL_DMA_GetPeriSelectNumber(DMA_PERI_USART, (DMA_PERI_ID_e)eId, DMA_PERI_COM_RX, &tDmaCfg.un32PeriNum);
            if(eErr == HAL_ERR_OK)
            {
                HPL_DMA_SetConfig(ptUcb->eDmaId, &tDmaCfg);
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
                HLL_USART_SetRxIntrEnable(eId, true);
                HPL_DMA_Start(ptUcb->eDmaId, (uint32_t)GET_USART_DR_RX_ADDR(PRV_USART_GetReg(eId)), (uint32_t)ptUcb->pun8RxBuf, ptUcb->un32RxLen);
#else
                SET_USART_IER_DMARXC_EN(ptUsart, true);
                HPL_DMA_Start(ptUcb->eDmaId, (uint32_t)GET_USART_DR_RX_ADDR(ptUsart), (uint32_t)ptUcb->pun8RxBuf, ptUcb->un32RxLen);
#endif
            }
        }
        else
#endif
        {
#if defined(USART_FEATURE_RX_TIME_OUT)
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            HLL_USART_SetRtoIntrEnable(eId, ptUcb->bRTOEnable);
#else
            SET_USART_IER_RTO_EN(ptUsart, ptUcb->bRTOEnable);
#endif
#endif
            /* Clear data buffer before starting to receive data */
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            un32Data = HLL_USART_ReceiveByte(eId);
            (void)un32Data;
            HLL_USART_SetRxIntrEnable(eId, true);
            if (ptUcb->bRxSCKGen)
            {
                HLL_USART_TransmitByte(eId, 0x00);
            }
#else
            un32Data = GET_USART_DR(ptUsart);
            (void)un32Data;
            SET_USART_IER_RXC_EN(ptUsart, true);
            if (ptUcb->bRxSCKGen)
            {
                SET_USART_DR(ptUsart, 0x00);
            }
#endif
        }
    }

    return eErr;
}

HAL_ERR_e HAL_USART_Abort(USART_ID_e eId)
{
    USART_CTRL_BLK_t *ptUcb;

    if((uint32_t)eId >= USART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUcb = &s_tUcb[eId];

    ptUcb->eTxBusy = USART_BUSY_NONE;

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_USART_AbortRx(USART_ID_e eId)
{
    USART_CTRL_BLK_t *ptUcb;

    if((uint32_t)eId >= USART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUcb = &s_tUcb[eId];

    ptUcb->eRxBusy = USART_BUSY_NONE;

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_USART_SetWakeupSrc(USART_ID_e eId, bool bEnable)
{
    if((uint32_t)eId >= USART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_USART_SetWakeupSrc(eId, bEnable);
#else
    {
        USART_Type *ptUsart = PRV_USART_GetReg(eId);

        USART_SetWkupSrc((P_USART_ID_e)eId, bEnable);
        SET_USART_IER_WAKE_EN(ptUsart, bEnable);
    }
#endif

    return HAL_ERR_OK;
}

static void PRV_USART_IRQHandler(USART_ID_e eId)
{
    USART_CTRL_BLK_t *ptUcb;
#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    USART_Type *ptUsart;
#endif
    USART_Context_t *ptContext;
    uint32_t un32IntStatus;
    uint32_t un32Event = 0;
#if defined (USART_FEATURE_NO_NINTH_BIT_REG)
    uint16_t un16Data = 0;
#endif

    if((uint32_t)eId >= USART_CH_NUM)
    {
        return;
    }

    ptUcb = &s_tUcb[eId];
#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    ptUsart = PRV_USART_GetReg(eId);
#endif

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    un32IntStatus = HLL_USART_GetStatus(eId);
    HLL_USART_ClearStatus(eId, un32IntStatus);
#else
    un32IntStatus = GET_USART_SR(ptUsart);
    SET_USART_SR(ptUsart, (un32IntStatus & USART_STATUS_MASK_BITS));
#endif

#if defined(_DMAC) && defined(DMA_USART_NUM)
    if (un32IntStatus & USART_STATUS_DMARX)
    {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
        HLL_USART_SetRxIntrEnable(eId, false);
#else
        SET_USART_IER_DMARXC_EN(ptUsart, false);
#endif
        HPL_DMA_Stop(ptUcb->eDmaId);
    }

    if (un32IntStatus & USART_STATUS_DMATX)
    {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
        HLL_USART_SetTxIntrEnable(eId, false);
#else
        SET_USART_IER_DMATXC_EN(ptUsart, false);
#endif
        HPL_DMA_Stop(ptUcb->eDmaId);
    }
#endif

    if(ptUcb->pContext != NULL)
    {
        ptContext = (USART_Context_t *)ptUcb->pContext;
        USART_GetWkupEvent((P_USART_ID_e)eId, &ptContext->bWakeup);
        if(ptContext->bWakeup)
        {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            HLL_USART_SetWakeupSrc(eId, false);
#else
            SET_USART_IER_WAKE_EN(ptUsart, false);
#endif
        }
    }

    if ((un32IntStatus & 0x1F))
    {
        if (un32IntStatus & USART_STATUS_PE)
        {
            un32Event |= USART_EVENT_PARITY_ERROR;
        }
        if (un32IntStatus & USART_STATUS_FE)
        {
            un32Event |= USART_EVENT_FRAME_ERROR;
        }
        if (un32IntStatus & USART_STATUS_DOR)
        {
            un32Event |= USART_EVENT_OVERFLOW_ERROR;
        }
        if (un32IntStatus & USART_STATUS_WAKE)
        {
            un32Event |= USART_EVENT_WAKE_UP;
        }
#if defined(USART_FEATURE_RX_TIME_OUT)
        if (un32IntStatus & USART_STATUS_RTO)
        {
            un32Event |= USART_EVENT_RX_TIMEOUT;
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            HLL_USART_ClearRtoFlag(eId);
            HLL_USART_SetRtoIntrEnable(eId, false);
            HLL_USART_SetRtoEnable(eId, false);
#else
            SET_USART_IER_RTO_FLAG(ptUsart, true);
            SET_USART_IER_RTO_EN(ptUsart, false);
            SET_USART_CR_RTO_EN(ptUsart, false);
#endif
        }
#endif
    }
    else
    {
#if defined(_DMAC) && defined(DMA_USART_NUM)
#if defined (USART_FEATURE_DMA_INTERNAL_INTERRUPT)
        if (ptUcb->eOps == USART_OPS_INTR_DMA)
        {
            if (ptUcb->eTxBusy == USART_BUSY_TX)
            {
                un32Event |= USART_EVENT_TX_DONE;
                ptUcb->eTxBusy = USART_BUSY_NONE;
            }

            if (ptUcb->eRxBusy == USART_BUSY_RX)
            {
                un32Event |= USART_EVENT_RX_DONE;
                ptUcb->eRxBusy = USART_BUSY_NONE;
            }

            HPL_DMA_Stop(ptUcb->eDmaId);
            ptUcb->bDmaEnabled = false;
            goto done;
        }
#else
        if (un32IntStatus & USART_STATUS_DMARX)
        {
            ptUcb->eRxBusy = USART_BUSY_NONE;
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            HLL_USART_ClearStatus(eId, USART_STATUS_DMARX);
#else
            SET_USART_IER_DR_FLAG(ptUsart, true);
#endif
            un32Event |= USART_EVENT_RX_DONE;
            goto done;
        }

        if (un32IntStatus & USART_STATUS_DMATX)
        {
            ptUcb->eTxBusy = USART_BUSY_NONE;
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            HLL_USART_ClearStatus(eId, USART_STATUS_DMATX);
#else
            SET_USART_IER_DR_FLAG(ptUsart, true);
#endif
            un32Event |= USART_EVENT_TX_DONE;
            goto done;
        }
#endif
#endif

        if ((un32IntStatus & USART_STATUS_RXC) && (ptUcb->eRxBusy == USART_BUSY_RX))
        {
#if defined (USART_FEATURE_NO_NINTH_BIT_REG)
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            un16Data = (uint16_t)HLL_USART_ReceiveByte(eId);
#else
            un16Data = GET_USART_DR(ptUsart);
#endif
#endif
            if(ptUcb->eMode != USART_MODE_SPI && ptUcb->eData == USART_DATA_9)
            {
#if defined (USART_FEATURE_NO_NINTH_BIT_REG)
                *(ptUcb->pun8RxBuf++) = ((un16Data >> 8) & 0x1);
#elif defined(AUDK32_FEATURE_HLL_SUPPORT)
                *(ptUcb->pun8RxBuf++) = HLL_USART_GetRxNinthBit(eId);
#else
                *(ptUcb->pun8RxBuf++) = GET_USART_CR_RXBIT_NINTH(ptUsart);
#endif
            }

#if defined (USART_FEATURE_NO_NINTH_BIT_REG)
            *(ptUcb->pun8RxBuf++) = un16Data & 0xFF;
#elif defined(AUDK32_FEATURE_HLL_SUPPORT)
            *(ptUcb->pun8RxBuf++) = (uint8_t)HLL_USART_ReceiveByte(eId);
#else
            *(ptUcb->pun8RxBuf++) = GET_USART_DR(ptUsart);
#endif
            ptUcb->un32RxCnt++;

            if (ptUcb->un32RxLen == ptUcb->un32RxCnt)
            {
                ptUcb->eRxBusy = USART_BUSY_NONE;
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
                HLL_USART_SetRxIntrEnable(eId, false);
#else
                SET_USART_IER_RXC_EN(ptUsart, false);
#endif
                un32Event |= USART_EVENT_RX_DONE;
            }
            else
            {
                if (ptUcb->bRxSCKGen)
                {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
                    HLL_USART_TransmitByte(eId, 0x00);
#else
                    SET_USART_DR(ptUsart, 0x00);
#endif
                }
            }
            goto done;
        }

        if ((un32IntStatus & USART_STATUS_TXC) && (ptUcb->eTxBusy == USART_BUSY_TX))
        {
#if defined(USART_FEATURE_MASTER_SS_PIN_BY_GPIO)
            if(ptUcb->eMode == USART_MODE_SPI && !ptUcb->bSSGenDisable)
            {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
                HLL_USART_SetSpiSlaveSelect(eId, true);
#else
                USART_SetSSPort((P_USART_ID_e)eId, true);
#endif
            }
#endif
            if (ptUcb->un32TxLen != ptUcb->un32TxCnt)
            {
#if defined(USART_FEATURE_MASTER_SS_PIN_BY_GPIO)
                if(ptUcb->eMode == USART_MODE_SPI && !ptUcb->bSSGenDisable)
                {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
                    HLL_USART_SetSpiSlaveSelect(eId, false);
#else
                    USART_SetSSPort((P_USART_ID_e)eId, false);
#endif
                }
#endif
                if(ptUcb->eMode != USART_MODE_SPI && ptUcb->eData == USART_DATA_9)
                {
#if defined (USART_FEATURE_NO_NINTH_BIT_REG)
                    un16Data |= ((*(ptUcb->pun8TxBuf++) & 0x1) << 8);

#elif defined(AUDK32_FEATURE_HLL_SUPPORT)
                    HLL_USART_SetTxNinthBit(eId, (*(ptUcb->pun8TxBuf++) & 0x1) != 0);
#else
                    SET_USART_CR_TXBIT_NINTH(ptUsart, (*(ptUcb->pun8TxBuf++) & 0x1));
#endif
                }

#if defined (USART_FEATURE_NO_NINTH_BIT_REG)
                SET_USART_IER_DR_FLAG(ptUsart, true);
                un16Data |= *(ptUcb->pun8TxBuf++);
                SET_USART_DR(ptUsart, un16Data);
#elif defined(AUDK32_FEATURE_HLL_SUPPORT)
                HLL_USART_TransmitByte(eId, *(ptUcb->pun8TxBuf++));
#else
                SET_USART_IER_DR_FLAG(ptUsart, true);
                SET_USART_DR(ptUsart, *(ptUcb->pun8TxBuf++));
#endif
                ptUcb->un32TxCnt++;
            }
            else
            {
                ptUcb->eTxBusy = USART_BUSY_NONE;
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
                HLL_USART_SetTxIntrEnable(eId, false);
#else
                SET_USART_IER_TXC_EN(ptUsart, false);
#endif
                un32Event |= USART_EVENT_TX_DONE;
            }

            goto done;
        }
    }

done:

    if (ptUcb->pfnHandler && un32Event)
    {
        ptUcb->pfnHandler(un32Event, ptUcb->pContext);
    }
}

void USART0_IRQHandler(void)
{
#if defined (USART_FEATURE_SUPPORT_MULTI_IRQ)
    uint32_t un32IntStatus;

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    un32IntStatus = HLL_USART_GetStatus(USART_ID_0);
#else
    un32IntStatus = GET_USART_SR(PRV_USART_GetReg(USART_ID_0));
#endif
    if (un32IntStatus & 0x60)
    {
        PRV_USART_IRQHandler(USART_ID_0);
    }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    un32IntStatus = HLL_USART_GetStatus(USART_ID_1);
#else
    un32IntStatus = GET_USART_SR(PRV_USART_GetReg(USART_ID_1));
#endif
    if (un32IntStatus & 0x60)
    {
        PRV_USART_IRQHandler(USART_ID_1);
    }
#else
    PRV_USART_IRQHandler(USART_ID_0);
#endif
}

void USART1_IRQHandler(void)
{
    PRV_USART_IRQHandler(USART_ID_1);
}

void USART2_IRQHandler(void)
{
    PRV_USART_IRQHandler(USART_ID_2);
}

void USART3_IRQHandler(void)
{
    PRV_USART_IRQHandler(USART_ID_3);
}

void USART4_IRQHandler(void)
{
    PRV_USART_IRQHandler(USART_ID_4);
}

void USART5_IRQHandler(void)
{
    PRV_USART_IRQHandler(USART_ID_5);
}

#endif /* _USART */
