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

static USART_Type *PRV_USART_GetReg(USART_ID_e eId)
{
    return USART_GetReg((uint32_t)eId);
}

static HAL_ERR_e PRV_USART_SetScuEnable(P_USART_ID_e eId, bool bEnable)
{
    return USART_SetScuEnable((P_USART_ID_e)eId, bEnable);
}

HAL_ERR_e HAL_USART_Init(USART_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= USART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_USART_SetScuEnable((P_USART_ID_e)eId, true);
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

    eErr = PRV_USART_SetScuEnable((P_USART_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = USART_GetIRQNum((P_USART_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tUcb[(uint32_t)eId], 0x00, sizeof(USART_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_USART_SetConfig(USART_ID_e eId, USART_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    USART_Type *ptUsart;
    USART_CTRL_BLK_t *ptUcb;
    uint32_t un32Numer, un32Denom, un8Bcv = 2;
    uint32_t un32Bdr, un32Bfr, un32Fd;

    if((uint32_t)eId >= USART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUsart = PRV_USART_GetReg(eId);
    ptUcb = &s_tUcb[(uint32_t)eId];

    /* Clear Control Regisers */
    SET_USART_CR(ptUsart, 0x00);
    SET_USART_CR2(ptUsart, 0x00);

    if(ptCfg->eMode < USART_MODE_MAX)
    {
        SET_USART_CR_MODE(ptUsart, USART_MODE((uint8_t)ptCfg->eMode));
        ptUcb->eMode = ptCfg->eMode;
    }
    else
    {
        return HAL_ERR_PARAMETER;
    }

    switch(ptCfg->eMode)
    {
        case USART_MODE_UART:
            SET_USART_CR_PARITY(ptUsart, USART_PARITY((uint8_t)ptCfg->tCfg.tUart.eParity));
            SET_USART_CR_DLEN(ptUsart, USART_DATA((uint8_t)ptCfg->tCfg.tUart.eData));
            SET_USART_CR_STOPBIT(ptUsart, (uint32_t)ptCfg->tCfg.tUart.eStop);
            SET_USART_CR_DBLS(ptUsart, ptCfg->tCfg.tUart.bDoubleSpeed);
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
            SET_USART_CR_MS(ptUsart, (uint8_t)ptCfg->tCfg.tUsrt.eMs);
            SET_USART_CR_PARITY(ptUsart, USART_PARITY((uint8_t)ptCfg->tCfg.tUsrt.eParity));
            SET_USART_CR_DLEN(ptUsart, USART_DATA((uint8_t)ptCfg->tCfg.tUsrt.eData));
            SET_USART_CR_STOPBIT(ptUsart, (uint32_t)ptCfg->tCfg.tUsrt.eStop);
            SET_USART_CR_CPACK(ptUsart, (uint8_t)ptCfg->tCfg.tUsrt.eClkPol);
            ptUcb->eData = ptCfg->tCfg.tUsrt.eData;
            break;
        case USART_MODE_SPI:
            SET_USART_CR_MS(ptUsart, (uint8_t)ptCfg->tCfg.tSpi.eMs);
            SET_USART_CR_BIT_ORDER(ptUsart, (uint8_t)ptCfg->tCfg.tSpi.eBitOrder);
            SET_USART_CR_CPACK(ptUsart, (uint8_t)ptCfg->tCfg.tSpi.eClkPol);
            SET_USART_CR_CPSCK(ptUsart, (uint8_t)ptCfg->tCfg.tSpi.eClkPha);
            SET_USART_CR_SWAP_MS_PORT(ptUsart, (uint8_t)ptCfg->tCfg.tSpi.bSwapMSPort);
            ptUcb->bSSGenDisable = ptCfg->tCfg.tSpi.bSSGenDisable;
            ptUcb->bRxSCKGen = ptCfg->tCfg.tSpi.bRxSCKGen;
#if defined(USART_FEATURE_RX_DISABLE_IN_SPI_SLAVE)
            if(ptCfg->tCfg.tSpi.eMs == USART_MS_SLAVE)
            {
                SET_USART_CR_SREN(ptUsart, !ptCfg->tCfg.tSpi.bSlvRecvDisable);
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
        SET_USART_CR_RTO_CNT(ptUsart, ptCfg->tRTO.un32RTOCount);
    }

    ptUcb->bRTOEnable = ptCfg->tRTO.bEnable;
#endif

    if(ptCfg->eMode == USART_MODE_SPI)
    {
        SET_USART_CR_BDR(ptUsart, (uint16_t)ptCfg->un32BaudRate & 0xFFFF);
#if defined(USART_FEATURE_MASTER_SS_PIN_BY_GPIO)
        if(ptCfg->tCfg.tSpi.eMs == USART_MS_MASTER)
        {
            SET_USART_CR_SSEN(ptUsart, false);
        }
        else
#endif
        {
            SET_USART_CR_SSEN(ptUsart, !ptCfg->tCfg.tSpi.bSSGenDisable);
        }
        
    }
    else
    {
        un32Numer = PRV_USART_GetNumer();
        un32Denom = un8Bcv * ptCfg->un32BaudRate;
        un32Bdr = un32Numer / un32Denom;
        un32Fd = un32Numer - (un32Bdr * un32Denom);
        un32Bfr = (un32Fd * 256) / un32Denom;

        SET_USART_CR_BDR(ptUsart, (uint32_t)((un32Bdr - 1) & 0xFFFF));
        SET_USART_CR_FPCR(ptUsart, (uint32_t)(un32Bfr & 0xFF));
        SET_USART_CR_FPCREN(ptUsart, true);

    }

    SET_USART_CR_TXEN(ptUsart, true);
    SET_USART_CR_RXEN(ptUsart, true);

    /* 
     * Must enable USART Block after setting Master mode or Polarity and Phase at SPI Mode.
     */
    SET_USART_CR_EN(ptUsart, true);

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
    eIrq = USART_GetIRQNum((P_USART_ID_e)eId);

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
    USART_Type *ptUsart;
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

    ptUsart = PRV_USART_GetReg(eId);
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
                SET_USART_CR_TXBIT_NINTH(ptUsart, (*(ptUcb->pun8TxBuf++) & 0x1));
            }

#if defined(USART_FEATURE_MASTER_SS_PIN_BY_GPIO)
            if(ptUcb->eMode == USART_MODE_SPI && !ptUcb->bSSGenDisable)
            {
                USART_SetSSPort((P_USART_ID_e)eId, false);
            }
#endif
            SET_USART_IER_DR_FLAG(ptUsart, true);
            SET_USART_DR(ptUsart, *(ptUcb->pun8TxBuf++));
            ptUcb->un32TxCnt++;
            while (!GET_USART_IER_DR_FLAG(ptUsart))
            {
            }
#if defined(USART_FEATURE_MASTER_SS_PIN_BY_GPIO)
            if(ptUcb->eMode == USART_MODE_SPI && !ptUcb->bSSGenDisable)
            {
                USART_SetSSPort((P_USART_ID_e)eId, true);
            }
#endif
        }
        
        /* If bEnForcePoll == true, check and clear TX Complete Interrupt Flag */
        if(GET_USART_IER_TXC_EN(ptUsart) && bEnForcePoll == true)
        {
            SET_USART_IER_TXC_EN(ptUsart, false);
        }

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
                SET_USART_IER_DMATXC_EN(ptUsart, true);
                HPL_DMA_Start(ptUcb->eDmaId, (uint32_t)ptUcb->pun8TxBuf, (uint32_t)GET_USART_DR_TX_ADDR(ptUsart), ptUcb->un32TxLen);
            }
        }
        else
#endif
        {
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
        }
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_USART_Receive(USART_ID_e eId, uint8_t *pun8In, uint32_t un32Len, bool bEnForcePoll)
{
    USART_CTRL_BLK_t *ptUcb;
    USART_Type *ptUsart;
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

    ptUsart = PRV_USART_GetReg(eId);
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
    SET_USART_CR_RTO_EN(ptUsart, ptUcb->bRTOEnable);
#endif

    if (ptUcb->eOps == USART_OPS_POLL || bEnForcePoll == true)
    {
        eIrq = USART_GetIRQNum((P_USART_ID_e)eId);
        if (ptUcb->eOps != USART_OPS_POLL)
        {
            NVIC_DisableIRQ(eIrq);
        }

        while (ptUcb->un32RxLen > ptUcb->un32RxCnt)
        {
            un32Status = 0;
            un32Timeout = USART_RX_TIMEOUT;

            while (!GET_USART_IER_RXC_FLAG(ptUsart) && un32Timeout)
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
#if defined (USART_FEATURE_NO_NINTH_BIT_REG)
                *(ptUcb->pun8RxBuf++) = ((GET_USART_DR(ptUsart) & 0x0100) >> 8);
#else
                *(ptUcb->pun8RxBuf++) = GET_USART_CR_RXBIT_NINTH(ptUsart);
#endif
            }

            *(ptUcb->pun8RxBuf++) = GET_USART_DR(ptUsart);
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
                SET_USART_IER_DMARXC_EN(ptUsart, true);
                HPL_DMA_Start(ptUcb->eDmaId, (uint32_t)GET_USART_DR_RX_ADDR(ptUsart), (uint32_t)ptUcb->pun8RxBuf, ptUcb->un32RxLen);
            }
        }
        else
#endif
        {
#if defined(USART_FEATURE_RX_TIME_OUT)
            SET_USART_IER_RTO_EN(ptUsart, ptUcb->bRTOEnable);
#endif
            /* Clear data buffer before starting to receive data */
            un32Data = GET_USART_DR(ptUsart);
            (void)un32Data;
            SET_USART_IER_RXC_EN(ptUsart, true);
            if (ptUcb->bRxSCKGen)
            {
                SET_USART_DR(ptUsart, 0x00);
            }
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
    USART_Type *ptUsart;

    if((uint32_t)eId >= USART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUsart = PRV_USART_GetReg(eId);

    USART_SetWkupSrc((P_USART_ID_e)eId, bEnable); 
    SET_USART_IER_WAKE_EN(ptUsart, bEnable);

    return HAL_ERR_OK;
}

static void PRV_USART_IRQHandler(USART_ID_e eId)
{
    USART_CTRL_BLK_t *ptUcb;
    USART_Type *ptUsart;
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
    ptUsart = PRV_USART_GetReg(eId);

    un32IntStatus = GET_USART_SR(ptUsart);
    SET_USART_SR(ptUsart, (un32IntStatus & USART_STATUS_MASK_BITS));

#if defined(_DMAC) && defined(DMA_USART_NUM)
    if (un32IntStatus & USART_STATUS_DMARX)
    {
        SET_USART_IER_DMARXC_EN(ptUsart, false);
        HPL_DMA_Stop(ptUcb->eDmaId);
    }

    if (un32IntStatus & USART_STATUS_DMATX)
    {
        SET_USART_IER_DMATXC_EN(ptUsart, false);
        HPL_DMA_Stop(ptUcb->eDmaId);
    }
#endif

    if(ptUcb->pContext != NULL)
    {
        ptContext = (USART_Context_t *)ptUcb->pContext;
        USART_GetWkupEvent((P_USART_ID_e)eId, &ptContext->bWakeup);
        if(ptContext->bWakeup)
        {
            SET_USART_IER_WAKE_EN(ptUsart, false);
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
            SET_USART_IER_RTO_FLAG(ptUsart, true); 
            SET_USART_IER_RTO_EN(ptUsart, false);
            SET_USART_CR_RTO_EN(ptUsart, false);
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
            SET_USART_IER_DR_FLAG(ptUsart, true);
            un32Event |= USART_EVENT_RX_DONE;
            goto done;
        }

        if (un32IntStatus & USART_STATUS_DMATX)
        {
            ptUcb->eTxBusy = USART_BUSY_NONE;
            SET_USART_IER_DR_FLAG(ptUsart, true);
            un32Event |= USART_EVENT_TX_DONE;
            goto done;
        }
#endif
#endif

        if ((un32IntStatus & USART_STATUS_RXC) && (ptUcb->eRxBusy == USART_BUSY_RX))
        {
#if defined (USART_FEATURE_NO_NINTH_BIT_REG)
            un16Data = GET_USART_DR(ptUsart);
#endif
            if(ptUcb->eMode != USART_MODE_SPI && ptUcb->eData == USART_DATA_9)
            {
#if defined (USART_FEATURE_NO_NINTH_BIT_REG)
                *(ptUcb->pun8RxBuf++) = ((un16Data >> 8) & 0x1);
#else
                *(ptUcb->pun8RxBuf++) = GET_USART_CR_RXBIT_NINTH(ptUsart);
#endif
            }

#if defined (USART_FEATURE_NO_NINTH_BIT_REG)
            *(ptUcb->pun8RxBuf++) = un16Data & 0xFF;
#else
            *(ptUcb->pun8RxBuf++) = GET_USART_DR(ptUsart);
#endif
            ptUcb->un32RxCnt++;

            if (ptUcb->un32RxLen == ptUcb->un32RxCnt)
            {
                ptUcb->eRxBusy = USART_BUSY_NONE;
                SET_USART_IER_RXC_EN(ptUsart, false);
                un32Event |= USART_EVENT_RX_DONE;
            }
            else
            {
                if (ptUcb->bRxSCKGen)
                {
                    SET_USART_DR(ptUsart, 0x00);
                }
            }
            goto done;
        }

        if ((un32IntStatus & USART_STATUS_TXC) && (ptUcb->eTxBusy == USART_BUSY_TX))
        {
#if defined(USART_FEATURE_MASTER_SS_PIN_BY_GPIO)
            if(ptUcb->eMode == USART_MODE_SPI && !ptUcb->bSSGenDisable)
            {
                USART_SetSSPort((P_USART_ID_e)eId, true);
            }
#endif
            if (ptUcb->un32TxLen != ptUcb->un32TxCnt)
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
                    un16Data |= ((*(ptUcb->pun8TxBuf++) & 0x1) << 8);
                  
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
            else
            {
                ptUcb->eTxBusy = USART_BUSY_NONE;
                SET_USART_IER_TXC_EN(ptUsart, false);
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
    USART_Type *ptUsart;
    uint32_t un32IntStatus;
    
    ptUsart = PRV_USART_GetReg(USART_ID_0);
    un32IntStatus = GET_USART_SR(ptUsart);
    if (un32IntStatus & 0x60)
    {
        PRV_USART_IRQHandler(USART_ID_0);
    }
    ptUsart = PRV_USART_GetReg(USART_ID_1);
    un32IntStatus = GET_USART_SR(ptUsart);
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
