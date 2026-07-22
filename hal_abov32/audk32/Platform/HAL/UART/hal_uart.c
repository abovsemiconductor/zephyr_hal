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

static HAL_ERR_e PRV_UART_SetScuEnable(P_UART_ID_e eId, bool bEnable)
{
    return UART_SetScuEnable((P_UART_ID_e)eId, bEnable);
}

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
    UART_Type *ptUart;
    uint32_t un32Data;

    if((uint32_t)eId >= UART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_UART_SetScuEnable((P_UART_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    ptUart = PRV_UART_GetReg((P_UART_ID_e)eId);
    ptUcb = &s_tUcb[(uint32_t)eId];

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

    eErr = PRV_UART_SetScuEnable((P_UART_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = UART_GetIRQNum((P_UART_ID_e)eId);
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

    return UART_SetClk((P_UART_ID_e)eId, (P_UART_CLK_MCCR_e)ptClkCfg->eMccr, ptClkCfg->un8MccrDiv);
}

HAL_ERR_e HAL_UART_SetConfig(UART_ID_e eId, UART_CFG_t *ptCfg)
{
    UART_Type *ptUart;
    uint32_t un32Numer, un32Denom;
    uint32_t un32Bdr, un32Bfr, un32Fd;
    bool bEnable = false;

    if((uint32_t)eId >= UART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUart = PRV_UART_GetReg((P_UART_ID_e)eId);

    if(ptCfg->eData < UART_DATA_MAX)
    {
        SET_UART_LCR_DLEN(ptUart,(uint32_t)ptCfg->eData);
    }
    else
    {
        return HAL_ERR_PARAMETER;
    }

    if(ptCfg->eParity < UART_PARITY_MAX)
    {
        if(ptCfg->eParity != UART_PARITY_NONE)
        {
            SET_UART_PARITY(ptUart,(uint32_t)ptCfg->eParity);
        }
    }
    else
    {
        return HAL_ERR_PARAMETER;
    }

    if(ptCfg->eStop < UART_STOP_MAX)
    {
        SET_UART_LCR_STOPBIT(ptUart,(uint32_t)ptCfg->eStop);
    }
    else
    {
        return HAL_ERR_PARAMETER;
    }

    if(ptCfg->bIntrLSEnable)
    {
        bEnable = true;
    }

    SET_UART_IER_RLSIE(ptUart, bEnable);

    un32Numer = UART_GetNumer();
    un32Denom = 16 * ptCfg->un32BaudRate;

    un32Bdr = un32Numer / un32Denom;
    un32Fd = un32Numer - (un32Bdr * un32Denom);
    un32Bfr = (un32Fd * 256) / un32Denom;

    SET_UART_BDR_BDR(ptUart, (uint32_t)(un32Bdr & 0xFFFF));
    SET_UART_BFR_BFR(ptUart, (uint32_t)(un32Bfr & 0xFF));

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
    eIrq = UART_GetIRQNum((P_UART_ID_e)eId);

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
    UART_Type *ptUart;
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

    ptUart = PRV_UART_GetReg((P_UART_ID_e)eId);
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
            SET_UART_THR_DATA(ptUart,ptUcb->pun8TxBuf[ptUcb->un32TxCnt++]);
            while (!GET_UART_LSR_THRE(ptUart))
            {
            }
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
                SET_UART_IER_DTXIEN(ptUart, true);
#if defined (UART_FEATURE_DMA_INTERNAL_INTERRUPT)
                HPL_DMA_Start(ptUcb->eDmaId, (uint32_t)ptUcb->pun8TxBuf, (uint32_t)GET_UART_TDR_ADDR(ptUart), ptUcb->un32TxLen);
#else
                HPL_DMA_Start(ptUcb->eDmaId, (uint32_t)ptUcb->pun8TxBuf, (uint32_t)ptUart, ptUcb->un32TxLen);
#endif
            }
        }
        else
#endif
        {
            if (GET_UART_LSR_THRE(ptUart))
            {
                SET_UART_THR_DATA(ptUart, ptUcb->pun8TxBuf[ptUcb->un32TxCnt++]);
            }
            SET_UART_IER_THREIE(ptUart, true);
        }
    }

    return eErr;
}

HAL_ERR_e HAL_UART_Receive(UART_ID_e eId, uint8_t *pun8In, uint32_t un32Len, bool bEnForcePoll)
{
    UART_CTRL_BLK_t *ptUcb;
    UART_Type *ptUart;
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

    ptUart = PRV_UART_GetReg((P_UART_ID_e)eId);
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
        eIrq = UART_GetIRQNum((P_UART_ID_e)eId);
        if (ptUcb->eOps != UART_OPS_POLL)
        {
            NVIC_DisableIRQ(eIrq);
        }

        while (ptUcb->un32RxLen > ptUcb->un32RxCnt)
        {
            un32Status = 0;
            un32Timeout = UART_RX_TIMEOUT;
            while (!GET_UART_LSR_DR(ptUart) && un32Timeout)
            {
                un32Timeout--;
            }

            if (un32Timeout == 0)
            {
                ptUcb->eRxBusy = UART_BUSY_NONE;
                eErr = HAL_ERR_TIMEOUT;
                break;
            }

            un32Status |= GET_UART_LSR_FE(ptUart);
            un32Status |= GET_UART_LSR_PE(ptUart);
            un32Status |= GET_UART_LSR_OE(ptUart);

            if (un32Status)
            {
                ptUcb->eRxBusy = UART_BUSY_NONE;
                eErr = HAL_ERR_HW;
                break;
            }
            ptUcb->pun8RxBuf[ptUcb->un32RxCnt++] = GET_UART_RBR_DATA(ptUart);
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
        uint32_t un32Data = GET_UART_RBR_DATA(ptUart);
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
                SET_UART_IER_DRXIEN(ptUart, true);
#if defined (UART_FEATURE_DMA_INTERNAL_INTERRUPT)
                HPL_DMA_Start(ptUcb->eDmaId, (uint32_t)GET_UART_RDR_ADDR(ptUart), (uint32_t)ptUcb->pun8RxBuf, ptUcb->un32RxLen);
#else
                HPL_DMA_Start(ptUcb->eDmaId, (uint32_t)ptUart, (uint32_t)ptUcb->pun8RxBuf, ptUcb->un32RxLen);
#endif
            }
        }
        else
#endif
        {
            SET_UART_IER_DRIE(ptUart, true);
        }
    }

    return eErr;
}

HAL_ERR_e HAL_UART_Abort(UART_ID_e eId)
{
    UART_Type *ptUart;
    UART_CTRL_BLK_t *ptUcb;

    if((uint32_t)eId >= UART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUart = PRV_UART_GetReg((P_UART_ID_e)eId);
    ptUcb = &s_tUcb[(uint32_t)eId];

    SET_UART_LCR_BREAK(ptUart, true);
    SET_UART_LCR_BREAK(ptUart, false);

    ptUcb->eTxBusy = UART_BUSY_NONE;
    ptUcb->eRxBusy = UART_BUSY_NONE;

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_UART_GetBusyStatus(UART_ID_e eId, bool *pbBusy)
{
    UART_Type *ptUart;

    if((uint32_t)eId >= UART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUart = PRV_UART_GetReg((P_UART_ID_e)eId);

    if (GET_UART_LSR_TEMT(ptUart))
    {
        *pbBusy = false;
    }
    else
    {
        *pbBusy = true;
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_UART_GetLineStatus(UART_ID_e eId, uint8_t *pun8Status)
{
    UART_Type *ptUart;

    if((uint32_t)eId >= UART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUart = PRV_UART_GetReg((P_UART_ID_e)eId);
    *pun8Status = ((GET_UART_LSR(ptUart)) & 0x7F);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_UART_SetIFDelay(UART_ID_e eId, uint8_t un8Delay)
{
    UART_Type *ptUart;

    if((uint32_t)eId >= UART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUart = PRV_UART_GetReg((P_UART_ID_e)eId);
    SET_UART_IDTR_WAITVAL(ptUart, un8Delay);

    return HAL_ERR_OK;
}

static void PRV_UART_IRQHandler(UART_ID_e eId)
{
    UART_CTRL_BLK_t *ptUcb;
    UART_Type *ptUart;
    uint32_t un32Data;
    volatile uint32_t un32IntStatus;
    volatile uint32_t un32Event = 0;

    if((uint32_t)eId >= UART_CH_NUM)
    {
        return;
    }

    ptUart = PRV_UART_GetReg((P_UART_ID_e)eId);
    ptUcb = &s_tUcb[(uint32_t)eId];

    un32IntStatus = GET_UART_IIR(ptUart);

    if ((un32IntStatus & UART_IIR_RX_LINE_ERROR) == UART_IIR_RX_LINE_ERROR)
    {
        un32Event |= UART_EVENT_LINE_ERROR;

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
            SET_UART_IER_DRXIEN(ptUart, false);
            HPL_DMA_Stop(ptUcb->eDmaId);
            un32Event |= UART_EVENT_RX_DONE;
            goto done;
        }

        if ((un32IntStatus & UART_IIR_TX_DMA_DONE) == UART_IIR_TX_DMA_DONE)
        {
            ptUcb->eTxBusy = UART_BUSY_NONE;
            SET_UART_IER_DTXIEN(ptUart, false);
            HPL_DMA_Stop(ptUcb->eDmaId);
            un32Event |= UART_EVENT_TX_DONE;
            goto done;
        }
#endif
#endif
        if (un32IntStatus & UART_IIR_RX_DATA_AVAIL)
        {
            ptUcb->pun8RxBuf[ptUcb->un32RxCnt++] = GET_UART_RBR_DATA(ptUart);

            if (ptUcb->un32RxLen == ptUcb->un32RxCnt)
            {
                SET_UART_IER_DRIE(ptUart, false);
                ptUcb->eRxBusy = UART_BUSY_NONE;
                un32Event |= UART_EVENT_RX_DONE;
            }
            goto done;
        }

        if ((un32IntStatus & UART_IIR_TX_HOLD_EMPTY) || (un32IntStatus & UART_IIR_TX_EMPTY))
        {
            if (ptUcb->un32TxLen != ptUcb->un32TxCnt)
            {
                SET_UART_THR_DATA(ptUart, ptUcb->pun8TxBuf[ptUcb->un32TxCnt++]);
            }
            else
            {
                ptUcb->eTxBusy = UART_BUSY_NONE;
                SET_UART_IER_THREIE(ptUart, false);
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
