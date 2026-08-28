/**
 *******************************************************************************
 * @file        hal_uart.c
 * @author      ABOV R&D Division
 * @brief       UART Serial Communication
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

#if defined(_UART)
#include "hal_uart.h"
#include "hal_uart_prv.h"

#include "hll_uart.h"

#if defined(_DMAC) && defined(DMA_UART_NUM)
#include "hpl_dma.h"
#endif

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
#include "hpl_nmi.h"
#endif

typedef struct UART_CTRL_BLOCK
{
    UART_OPS_e               eOps;
    pfnUART_IRQ_Handler_t    pfnHandler;
    void                     *pContext;

#if defined(_DMAC) && defined(DMA_UART_NUM)
    DMA_ID_e                 eDmaId;
    bool                     bDmaEnabled;
#endif

    UART_BUSY_e              eTxBusy;
    UART_BUSY_e              eRxBusy;
    uint8_t                  *pun8TxBuf;
    uint8_t                  *pun8RxBuf;
    uint32_t                 un32TxLen;
    uint32_t                 un32RxLen;
    uint32_t                 un32TxCnt;
    uint32_t                 un32RxCnt;

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
    bool                    bNmiEnable;
#endif

} UART_CTRL_BLK_t;

static UART_CTRL_BLK_t s_tUcb[UART_CH_NUM];

static void PRV_UART_IRQHandler(UART_ID_e eId);

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
static void PRV_UART_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < UART_CH_NUM; i++)
    {
        if(s_tUcb[i].bNmiEnable == true)
        {
            PRV_UART_IRQHandler((UART_ID_e)i);
        }
    }
}
#endif

#if defined(_DMAC) && defined(DMA_UART_NUM) && defined (UART_FEATURE_DMA_INTERNAL_INTERRUPT)
static void PRV_UART_DMAHandler(uint32_t un32Event, void *pContext)
{
    PRV_UART_IRQHandler((UART_ID_e)(un32Event));
}
#endif

static UART_Type *PRV_UART_GetReg(P_UART_ID_e eId)
{
    return UART_GetReg((uint32_t)eId);
}

#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
static HAL_ERR_e PRV_UART_SetScuEnable(P_UART_ID_e eId, bool bEnable)
{
    return UART_SetScuEnable((P_UART_ID_e)eId, bEnable);
}
#endif

#if defined(_DMAC) && defined(DMA_UART_NUM)
static HAL_ERR_e PRV_UART_SetDMA(UART_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    UART_CTRL_BLK_t *ptUcb;
    DMA_ID_e eDmaId;

    ptUcb = &s_tUcb[(uint32_t)eId];

    eErr = HPL_DMA_Init(DMA_PERI_UART, (uint8_t)eId);
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

#if defined (UART_FEATURE_DMA_INTERNAL_INTERRUPT)
    eErr = HPL_DMA_SetIRQ(DMA_PERI_UART, &PRV_UART_DMAHandler, NULL, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }
#endif

    return eErr;
}
#endif

HAL_ERR_e HAL_UART_Init(UART_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    UART_CTRL_BLK_t *ptUcb;
#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    UART_Type *ptUart;
#endif
    uint32_t un32Data;

    if((uint32_t)eId >= UART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    eErr = HLL_UART_SetClockEnable(eId, true);
#else
    eErr = PRV_UART_SetScuEnable((P_UART_ID_e)eId, true);
#endif
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    ptUart = PRV_UART_GetReg((P_UART_ID_e)eId);
#endif
    ptUcb = &s_tUcb[(uint32_t)eId];

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    while (HLL_UART_GetRxReady(eId))
    {
        /* Warning Message [Pa130] at IAR */
        un32Data = HLL_UART_ReceiveByte(eId);
        (void)un32Data;
    }

    while (!HLL_UART_GetTxReady(eId))
    {
    }

    HLL_UART_ClearControl(eId);

    (void)HLL_UART_GetLineStatus(eId);
    (void)HLL_UART_GetIntrStatus(eId);
#else
    while (GET_UART_LSR_DR(ptUart))
    {
        /* Warning Message [Pa130] at IAR */
        un32Data=GET_UART_RBR_DATA(ptUart);
        (void)un32Data;
    }

    while (!GET_UART_LSR_THRE(ptUart))
    {
    }

    SET_UART_IER(ptUart, 0);
    SET_UART_LCR(ptUart, 0);
    SET_UART_DCR(ptUart, 0);

    GET_UART_LSR(ptUart);
    GET_UART_IIR(ptUart);
#endif

    memset(ptUcb, 0x00, sizeof(UART_CTRL_BLK_t));

    return eErr;
}

HAL_ERR_e HAL_UART_Uninit(UART_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= UART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    eErr = HLL_UART_SetClockEnable(eId, false);
    eIrq = HLL_UART_GetIRQNum(eId);
#else
    eErr = PRV_UART_SetScuEnable((P_UART_ID_e)eId, false);
    eIrq = UART_GetIRQNum((P_UART_ID_e)eId);
#endif
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tUcb[(uint32_t)eId], 0, sizeof(UART_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_UART_SetClkConfig(UART_ID_e eId, UART_CLK_CFG_t *ptClkCfg)
{
    if((uint32_t)eId >= UART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    return HLL_UART_SetClkSource(eId, ptClkCfg->eMccr, ptClkCfg->un8MccrDiv);
#else
    return UART_SetClk((P_UART_ID_e)eId, (P_UART_CLK_MCCR_e)ptClkCfg->eMccr, ptClkCfg->un8MccrDiv);
#endif
}

HAL_ERR_e HAL_UART_SetConfig(UART_ID_e eId, UART_CFG_t *ptCfg)
{
#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    UART_Type *ptUart;
#endif
    bool bEnable = false;

    if((uint32_t)eId >= UART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    ptUart = PRV_UART_GetReg((P_UART_ID_e)eId);
#endif

    if(ptCfg->eData >= UART_DATA_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    if(ptCfg->eParity >= UART_PARITY_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    if(ptCfg->eStop >= UART_STOP_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    /*
     * Data/parity/stop are only actually written to hardware here, once all
     * three are known valid -- HLL_UART_SetFormat() applies them together,
     * so unlike the pre-HLL code below there is no partial write on a late
     * validation failure.
     */
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_UART_SetFormat(eId, ptCfg->eParity, ptCfg->eData, ptCfg->eStop);
#else
    SET_UART_LCR_DLEN(ptUart,(uint32_t)ptCfg->eData);

    if(ptCfg->eParity != UART_PARITY_NONE)
    {
        SET_UART_PARITY(ptUart,(uint32_t)ptCfg->eParity);
    }

    SET_UART_LCR_STOPBIT(ptUart,(uint32_t)ptCfg->eStop);
#endif

    if(ptCfg->bIntrLSEnable)
    {
        bEnable = true;
    }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    {
        uint32_t un32Bdr, un32Bfr;

        HLL_UART_SetLineIntrEnable(eId, bEnable);

        HLL_UART_CalcUartBaud(ptCfg->un32BaudRate, &un32Bdr, &un32Bfr);
        HLL_UART_SetBaudRate(eId, un32Bdr, un32Bfr);
    }
#else
    SET_UART_IER_RLSIE(ptUart, bEnable);

    {
        uint32_t un32Numer = UART_GetNumer();
        uint32_t un32Denom = 16 * ptCfg->un32BaudRate;
        uint32_t un32Bdr = un32Numer / un32Denom;
        uint32_t un32Fd = un32Numer - (un32Bdr * un32Denom);
        uint32_t un32Bfr = (un32Fd * 256) / un32Denom;

        SET_UART_BDR_BDR(ptUart, (uint32_t)(un32Bdr & 0xFFFF));
        SET_UART_BFR_BFR(ptUart, (uint32_t)(un32Bfr & 0xFF));
    }
#endif

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_UART_SetIRQ(UART_ID_e eId, UART_OPS_e eOps, pfnUART_IRQ_Handler_t pfnHandler,
                          void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    UART_CTRL_BLK_t *ptUcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= UART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUcb = &s_tUcb[(uint32_t)eId];

    /*
     * NVIC setup is always performed here regardless of HLL support: only
     * the IRQ-number lookup below switches implementation.
     */
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    eIrq = HLL_UART_GetIRQNum(eId);
#else
    eIrq = UART_GetIRQNum((P_UART_ID_e)eId);
#endif

    switch(eOps)
    {
        case UART_OPS_INTR:
#if defined(_DMAC) && defined(DMA_UART_NUM)
        case UART_OPS_INTR_DMA:
#endif
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            if(ptUcb->bNmiEnable == true)
            {
                (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
                ptUcb->bNmiEnable = false;
            }
#endif
#if defined(UART_FEATURE_IRQ_UNMASK_ENABLE)
            PRV_UART_SetIntrUnMask(eIrq, true);
#endif
            ptUcb->pfnHandler = pfnHandler;
            ptUcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);

#if defined(_DMAC) && defined(DMA_UART_NUM)
            if(eOps == UART_OPS_INTR_DMA)
            {
                eErr = PRV_UART_SetDMA(eId);
            }
#endif
            break;
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
        case UART_OPS_NMI:
        case UART_OPS_NMI_DMA:
            eErr = HPL_NMI_SetSource(eIrq, &PRV_UART_NMIHandler, pContext, true);
            if(eErr == HAL_ERR_OK)
            {
                ptUcb->pfnHandler = pfnHandler;
                ptUcb->pContext = pContext;
            }
            ptUcb->bNmiEnable = true;
#if defined(_DMAC) && defined(DMA_UART_NUM)
            if(eOps == UART_OPS_NMI_DMA)
            {
                eErr = PRV_UART_SetDMA(eId);
            }
#endif
            break;
#endif
        case UART_OPS_POLL:
        default:
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
            ptUcb->bNmiEnable = false;
#endif
#if defined(_DMAC) && defined(DMA_UART_NUM)
            if(ptUcb->bDmaEnabled == true)
            {
                HPL_DMA_Uninit(DMA_PERI_UART, (uint8_t)eId);
                ptUcb->bDmaEnabled = false;
            }
#endif
#if defined(UART_FEATURE_IRQ_UNMASK_ENABLE)
            PRV_UART_SetIntrUnMask(eIrq, false);
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

HAL_ERR_e HAL_UART_Transmit(UART_ID_e eId, uint8_t *pun8Out, uint32_t un32Len, bool bEnForcePoll)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    UART_CTRL_BLK_t *ptUcb;
#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    UART_Type *ptUart;
#endif
#if defined(_DMAC) && defined(DMA_UART_NUM)
    DMA_CFG_t tDmaCfg =
    {
        .ePeri = DMA_PERI_UART,
        .ePeriId = (DMA_PERI_ID_e)eId,
        .un32PeriNum = 0,
        .eSize = DMA_BUS_SIZE_BYTE,
        .eDir = DMA_DIR_MEM_TO_PERI
    };
#endif

    if((uint32_t)eId >= UART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    ptUart = PRV_UART_GetReg((P_UART_ID_e)eId);
#endif
    ptUcb = &s_tUcb[(uint32_t)eId];

    if (ptUcb->eTxBusy == UART_BUSY_TX)
    {
        return HAL_ERR_BUSY;
    }

    ptUcb->eTxBusy = UART_BUSY_TX;
    ptUcb->pun8TxBuf = (uint8_t *)pun8Out;
    ptUcb->un32TxLen = un32Len;
    ptUcb->un32TxCnt = 0;

    if (ptUcb->eOps == UART_OPS_POLL || bEnForcePoll == true)
    {
        while (ptUcb->un32TxLen > ptUcb->un32TxCnt)
        {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            HLL_UART_TransmitByte(eId, ptUcb->pun8TxBuf[ptUcb->un32TxCnt++]);
            while (!HLL_UART_GetTxReady(eId))
            {
            }
#else
            SET_UART_THR_DATA(ptUart,ptUcb->pun8TxBuf[ptUcb->un32TxCnt++]);
            while (!GET_UART_LSR_THRE(ptUart))
            {
            }
#endif
        }

        ptUcb->eTxBusy = UART_BUSY_NONE;
    }
    else
    {
#if defined(_DMAC) && defined(DMA_UART_NUM)
        if(ptUcb->eOps == UART_OPS_INTR_DMA
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
           || ptUcb->eOps == UART_OPS_NMI_DMA
#endif
          )
        {
            eErr = (HAL_ERR_e)HPL_DMA_GetPeriSelectNumber(DMA_PERI_UART, (DMA_PERI_ID_e)eId, DMA_PERI_COM_TX, &tDmaCfg.un32PeriNum);
            if(eErr == HAL_ERR_OK)
            {
                HPL_DMA_SetConfig(ptUcb->eDmaId, &tDmaCfg);
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
                HLL_UART_SetTxDmaIntrEnable(eId, true);
#if defined (UART_FEATURE_DMA_INTERNAL_INTERRUPT)
                HPL_DMA_Start(ptUcb->eDmaId, (uint32_t)ptUcb->pun8TxBuf, (uint32_t)GET_UART_TDR_ADDR(PRV_UART_GetReg((P_UART_ID_e)eId)), ptUcb->un32TxLen);
#else
                HPL_DMA_Start(ptUcb->eDmaId, (uint32_t)ptUcb->pun8TxBuf, (uint32_t)PRV_UART_GetReg((P_UART_ID_e)eId), ptUcb->un32TxLen);
#endif
#else
                SET_UART_IER_DTXIEN(ptUart, true);
#if defined (UART_FEATURE_DMA_INTERNAL_INTERRUPT)
                HPL_DMA_Start(ptUcb->eDmaId, (uint32_t)ptUcb->pun8TxBuf, (uint32_t)GET_UART_TDR_ADDR(ptUart), ptUcb->un32TxLen);
#else
                HPL_DMA_Start(ptUcb->eDmaId, (uint32_t)ptUcb->pun8TxBuf, (uint32_t)ptUart, ptUcb->un32TxLen);
#endif
#endif
            }
        }
        else
#endif
        {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            if (HLL_UART_GetTxReady(eId))
            {
                HLL_UART_TransmitByte(eId, ptUcb->pun8TxBuf[ptUcb->un32TxCnt++]);
            }
            HLL_UART_SetTxReadyIntrEnable(eId, true);
#else
            if (GET_UART_LSR_THRE(ptUart))
            {
                SET_UART_THR_DATA(ptUart, ptUcb->pun8TxBuf[ptUcb->un32TxCnt++]);
            }
            SET_UART_IER_THREIE(ptUart, true);
#endif
        }
    }

    return eErr;
}

HAL_ERR_e HAL_UART_Receive(UART_ID_e eId, uint8_t *pun8In, uint32_t un32Len, bool bEnForcePoll)
{
    UART_CTRL_BLK_t *ptUcb;
#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    UART_Type *ptUart;
#endif
    uint32_t un32Status, un32Timeout;
    IRQn_Type eIrq;
    HAL_ERR_e eErr = HAL_ERR_OK;
#if defined(_DMAC) && defined(DMA_UART_NUM)
    DMA_CFG_t tDmaCfg =
    {
        .ePeri = DMA_PERI_UART,
        .ePeriId = (DMA_PERI_ID_e)eId,
        .un32PeriNum = 0,
        .eSize = DMA_BUS_SIZE_BYTE,
        .eDir = DMA_DIR_PERI_TO_MEM
    };
#endif

    if((uint32_t)eId >= UART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    ptUart = PRV_UART_GetReg((P_UART_ID_e)eId);
#endif
    ptUcb = &s_tUcb[(uint32_t)eId];

    if (ptUcb->eRxBusy == UART_BUSY_RX)
    {
        return HAL_ERR_BUSY;
    }

    ptUcb->eRxBusy = UART_BUSY_RX;
    ptUcb->pun8RxBuf = (uint8_t *)pun8In;
    ptUcb->un32RxLen = un32Len;
    ptUcb->un32RxCnt = 0;

    if (ptUcb->eOps == UART_OPS_POLL || bEnForcePoll == true)
    {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
        eIrq = HLL_UART_GetIRQNum(eId);
#else
        eIrq = UART_GetIRQNum((P_UART_ID_e)eId);
#endif
        if (ptUcb->eOps != UART_OPS_POLL)
        {
            NVIC_DisableIRQ(eIrq);
        }

        while (ptUcb->un32RxLen > ptUcb->un32RxCnt)
        {
            un32Status = 0;
            un32Timeout = UART_RX_TIMEOUT;

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            while (!HLL_UART_GetRxReady(eId) && un32Timeout)
#else
            while (!GET_UART_LSR_DR(ptUart) && un32Timeout)
#endif
            {
                un32Timeout--;
            }

            if (un32Timeout == 0)
            {
                ptUcb->eRxBusy = UART_BUSY_NONE;
                eErr = HAL_ERR_TIMEOUT;
                break;
            }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            /*
             * HLL_UART_GetLineStatus() returns the raw ELSR register (see
             * HAL_UART_GetLineStatus()); UART_LINE_STATUS_e mirrors ELSR's
             * bit layout 1:1, so masking against it here is equivalent to
             * the individual GET_UART_LSR_FE/PE/OE reads below.
             */
            un32Status = HLL_UART_GetLineStatus(eId) &
                         (UART_LINE_STATUS_FRAME_ERROR | UART_LINE_STATUS_PARITY_ERROR |
                          UART_LINE_STATUS_OVERRUN_ERROR);
#else
            un32Status |= GET_UART_LSR_FE(ptUart);
            un32Status |= GET_UART_LSR_PE(ptUart);
            un32Status |= GET_UART_LSR_OE(ptUart);
#endif

            if (un32Status)
            {
                ptUcb->eRxBusy = UART_BUSY_NONE;
                eErr = HAL_ERR_HW;
                break;
            }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            ptUcb->pun8RxBuf[ptUcb->un32RxCnt++] = HLL_UART_ReceiveByte(eId);
#else
            ptUcb->pun8RxBuf[ptUcb->un32RxCnt++] = GET_UART_RBR_DATA(ptUart);
#endif
        }

        ptUcb->eRxBusy = UART_BUSY_NONE;
        if (ptUcb->eOps != UART_OPS_POLL)
        {
            NVIC_EnableIRQ(eIrq);
        }
    }
    else
    {
        /* Warning Message [Pa130] at IAR */
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
        uint32_t un32Data = HLL_UART_ReceiveByte(eId);
#else
        uint32_t un32Data = GET_UART_RBR_DATA(ptUart);
#endif
        (void)un32Data;

#if defined(_DMAC) && defined(DMA_UART_NUM)
        if(ptUcb->eOps == UART_OPS_INTR_DMA
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
           || ptUcb->eOps == UART_OPS_NMI_DMA
#endif
          )
        {
            eErr = (HAL_ERR_e)HPL_DMA_GetPeriSelectNumber(DMA_PERI_UART, (DMA_PERI_ID_e)eId, DMA_PERI_COM_RX, &tDmaCfg.un32PeriNum);
            if(eErr == HAL_ERR_OK)
            {
                HPL_DMA_SetConfig(ptUcb->eDmaId, &tDmaCfg);
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
                HLL_UART_SetRxDmaIntrEnable(eId, true);
#if defined (UART_FEATURE_DMA_INTERNAL_INTERRUPT)
                HPL_DMA_Start(ptUcb->eDmaId, (uint32_t)GET_UART_RDR_ADDR(PRV_UART_GetReg((P_UART_ID_e)eId)), (uint32_t)ptUcb->pun8RxBuf, ptUcb->un32RxLen);
#else
                HPL_DMA_Start(ptUcb->eDmaId, (uint32_t)PRV_UART_GetReg((P_UART_ID_e)eId), (uint32_t)ptUcb->pun8RxBuf, ptUcb->un32RxLen);
#endif
#else
                SET_UART_IER_DRXIEN(ptUart, true);
#if defined (UART_FEATURE_DMA_INTERNAL_INTERRUPT)
                HPL_DMA_Start(ptUcb->eDmaId, (uint32_t)GET_UART_RDR_ADDR(ptUart), (uint32_t)ptUcb->pun8RxBuf, ptUcb->un32RxLen);
#else
                HPL_DMA_Start(ptUcb->eDmaId, (uint32_t)ptUart, (uint32_t)ptUcb->pun8RxBuf, ptUcb->un32RxLen);
#endif
#endif
            }
        }
        else
#endif
        {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            HLL_UART_SetRxIntrEnable(eId, true);
#else
            SET_UART_IER_DRIE(ptUart, true);
#endif
        }
    }

    return eErr;
}

HAL_ERR_e HAL_UART_Abort(UART_ID_e eId)
{
    UART_CTRL_BLK_t *ptUcb;

    if((uint32_t)eId >= UART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUcb = &s_tUcb[(uint32_t)eId];

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_UART_SetBreak(eId, true);
    HLL_UART_SetBreak(eId, false);
#else
    {
        UART_Type *ptUart = PRV_UART_GetReg((P_UART_ID_e)eId);

        SET_UART_LCR_BREAK(ptUart, true);
        SET_UART_LCR_BREAK(ptUart, false);
    }
#endif

    ptUcb->eTxBusy = UART_BUSY_NONE;
    ptUcb->eRxBusy = UART_BUSY_NONE;

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_UART_GetBusyStatus(UART_ID_e eId, bool *pbBusy)
{
    if((uint32_t)eId >= UART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    *pbBusy = !HLL_UART_GetTxComplete(eId);
#else
    {
        UART_Type *ptUart = PRV_UART_GetReg((P_UART_ID_e)eId);

        *pbBusy = !GET_UART_LSR_TEMT(ptUart);
    }
#endif

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_UART_GetLineStatus(UART_ID_e eId, uint8_t *pun8Status)
{
    if((uint32_t)eId >= UART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    *pun8Status = (uint8_t)HLL_UART_GetLineStatus(eId);
#else
    {
        UART_Type *ptUart = PRV_UART_GetReg((P_UART_ID_e)eId);

        *pun8Status = (uint8_t)((GET_UART_LSR(ptUart)) & 0x7F);
    }
#endif

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_UART_SetIFDelay(UART_ID_e eId, uint8_t un8Delay)
{
    if((uint32_t)eId >= UART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_UART_SetIFDelay(eId, un8Delay);
#else
    {
        UART_Type *ptUart = PRV_UART_GetReg((P_UART_ID_e)eId);

        SET_UART_IDTR_WAITVAL(ptUart, un8Delay);
    }
#endif

    return HAL_ERR_OK;
}

static void PRV_UART_IRQHandler(UART_ID_e eId)
{
    UART_CTRL_BLK_t *ptUcb;
#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    UART_Type *ptUart;
#endif
    uint32_t un32Data;
    volatile uint32_t un32IntStatus;
    volatile uint32_t un32Event = 0;

    if((uint32_t)eId >= UART_CH_NUM)
    {
        return;
    }

#if !defined(AUDK32_FEATURE_HLL_SUPPORT)
    ptUart = PRV_UART_GetReg((P_UART_ID_e)eId);
#endif
    ptUcb = &s_tUcb[(uint32_t)eId];

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    un32IntStatus = HLL_UART_GetIntrStatus(eId);
#else
    un32IntStatus = GET_UART_IIR(ptUart);
#endif

    if ((un32IntStatus & UART_IIR_RX_LINE_ERROR) == UART_IIR_RX_LINE_ERROR)
    {
        un32Event |= UART_EVENT_LINE_ERROR;

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
        /* See the equivalent comment in HAL_UART_Receive(). */
        {
            uint32_t un32Line = HLL_UART_GetLineStatus(eId);

            if (un32Line & UART_LINE_STATUS_BREAK)
            {
                un32Event |= UART_EVENT_BREAK_ERROR;
            }
            if (un32Line & UART_LINE_STATUS_FRAME_ERROR)
            {
                un32Event |= UART_EVENT_FRAME_ERROR;
            }
            if (un32Line & UART_LINE_STATUS_PARITY_ERROR)
            {
                un32Event |= UART_EVENT_PARITY_ERROR;
            }
            if (un32Line & UART_LINE_STATUS_OVERRUN_ERROR)
            {
                un32Event |= UART_EVENT_OVERFLOW_ERROR;
            }
        }

        /* Warning Message [Pa130] at IAR */
        un32Data = HLL_UART_ReceiveByte(eId);
        (void)un32Data;
        /* Full IER reset has no dedicated HLL wrapper; fall back to the
         * register directly, as HLL_USART_* does for its own DMA-address
         * edge cases. */
        SET_UART_IER(PRV_UART_GetReg((P_UART_ID_e)eId), 0x00);
#else
        if (GET_UART_LSR_BI(ptUart))
        {
            un32Event |= UART_EVENT_BREAK_ERROR;
        }
        if (GET_UART_LSR_FE(ptUart))
        {
            un32Event |= UART_EVENT_FRAME_ERROR;
        }
        if (GET_UART_LSR_PE(ptUart))
        {
            un32Event |= UART_EVENT_PARITY_ERROR;
        }
        if (GET_UART_LSR_OE(ptUart))
        {
            un32Event |= UART_EVENT_OVERFLOW_ERROR;
        }

        /* Warning Message [Pa130] at IAR */
        un32Data=GET_UART_RBR_DATA(ptUart);
        (void)un32Data;
        SET_UART_IER(ptUart, 0x00);
#endif
    }
    else
    {
#if defined(_DMAC) && defined(DMA_UART_NUM)
#if defined (UART_FEATURE_DMA_INTERNAL_INTERRUPT)
        if (ptUcb->eOps == UART_OPS_INTR_DMA)
        {
            if (ptUcb->eTxBusy == UART_BUSY_TX)
            {
                un32Event |= UART_EVENT_TX_DONE;
                ptUcb->eTxBusy = UART_BUSY_NONE;
            }

            if (ptUcb->eRxBusy == UART_BUSY_RX)
            {
                un32Event |= UART_EVENT_RX_DONE;
                ptUcb->eRxBusy = UART_BUSY_NONE;
            }

            HPL_DMA_Stop(ptUcb->eDmaId);
            ptUcb->bDmaEnabled = false;
            goto done;
        }

#else
        if ((un32IntStatus & UART_IIR_RX_DMA_DONE) == UART_IIR_RX_DMA_DONE)
        {
            ptUcb->eRxBusy = UART_BUSY_NONE;
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            HLL_UART_SetRxDmaIntrEnable(eId, false);
#else
            SET_UART_IER_DRXIEN(ptUart, false);
#endif
            HPL_DMA_Stop(ptUcb->eDmaId);
            un32Event |= UART_EVENT_RX_DONE;
            goto done;
        }

        if ((un32IntStatus & UART_IIR_TX_DMA_DONE) == UART_IIR_TX_DMA_DONE)
        {
            ptUcb->eTxBusy = UART_BUSY_NONE;
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            HLL_UART_SetTxDmaIntrEnable(eId, false);
#else
            SET_UART_IER_DTXIEN(ptUart, false);
#endif
            HPL_DMA_Stop(ptUcb->eDmaId);
            un32Event |= UART_EVENT_TX_DONE;
            goto done;
        }
#endif
#endif
        if (un32IntStatus & UART_IIR_RX_DATA_AVAIL)
        {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
            ptUcb->pun8RxBuf[ptUcb->un32RxCnt++] = HLL_UART_ReceiveByte(eId);
#else
            ptUcb->pun8RxBuf[ptUcb->un32RxCnt++] = GET_UART_RBR_DATA(ptUart);
#endif

            if (ptUcb->un32RxLen == ptUcb->un32RxCnt)
            {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
                HLL_UART_SetRxIntrEnable(eId, false);
#else
                SET_UART_IER_DRIE(ptUart, false);
#endif
                ptUcb->eRxBusy = UART_BUSY_NONE;
                un32Event |= UART_EVENT_RX_DONE;
            }
            goto done;
        }

        if ((un32IntStatus & UART_IIR_TX_HOLD_EMPTY) || (un32IntStatus & UART_IIR_TX_EMPTY))
        {
            if (ptUcb->un32TxLen != ptUcb->un32TxCnt)
            {
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
                HLL_UART_TransmitByte(eId, ptUcb->pun8TxBuf[ptUcb->un32TxCnt++]);
#else
                SET_UART_THR_DATA(ptUart, ptUcb->pun8TxBuf[ptUcb->un32TxCnt++]);
#endif
            }
            else
            {
                ptUcb->eTxBusy = UART_BUSY_NONE;
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
                HLL_UART_SetTxReadyIntrEnable(eId, false);
#else
                SET_UART_IER_THREIE(ptUart, false);
#endif
                un32Event |= UART_EVENT_TX_DONE;
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

void UART0_IRQHandler(void)
{
    PRV_UART_IRQHandler(UART_ID_0);
}

void UART1_IRQHandler(void)
{
    PRV_UART_IRQHandler(UART_ID_1);
}

void UART2_IRQHandler(void)
{
    PRV_UART_IRQHandler(UART_ID_2);
}

void UART3_IRQHandler(void)
{
    PRV_UART_IRQHandler(UART_ID_3);
}

void UART4_IRQHandler(void)
{
    PRV_UART_IRQHandler(UART_ID_4);
}

void UART5_IRQHandler(void)
{
    PRV_UART_IRQHandler(UART_ID_5);
}

void UART6_IRQHandler(void)
{
    PRV_UART_IRQHandler(UART_ID_6);
}

void UART7_IRQHandler(void)
{
    PRV_UART_IRQHandler(UART_ID_7);
}

void UART8_IRQHandler(void)
{
    PRV_UART_IRQHandler(UART_ID_8);
}

void UART9_IRQHandler(void)
{
    PRV_UART_IRQHandler(UART_ID_9);
}

void UART10_IRQHandler(void)
{
    PRV_UART_IRQHandler(UART_ID_10);
}

void UART11_IRQHandler(void)
{
    PRV_UART_IRQHandler(UART_ID_11);
}

void UART12_IRQHandler(void)
{
    PRV_UART_IRQHandler(UART_ID_12);
}

#endif /* _UART */
