/**
 *******************************************************************************
 * @file        hal_lpuart.c
 * @author      ABOV R&D Division
 * @brief       LPUART Serial Communication
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

#if defined(_LPUART)
#include "hal_lpuart.h"
#include "hal_lpuart_prv.h"

#if defined(_DMAC) && defined(DMA_LPUART_NUM)
#include "hpl_dma.h"
#endif

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
#include "hpl_nmi.h"
#endif

typedef struct LPUART_CTRL_BLOCK
{
    LPUART_OPS_e               eOps;
    pfnLPUART_IRQ_Handler_t    pfnHandler;
    void                       *pContext;

#if defined(_DMAC) && defined(DMA_LPUART_NUM)
    DMA_ID_e                   eDmaId;
    bool                       bDmaEnabled;
#endif

    LPUART_BUSY_e              eTxBusy;
    LPUART_BUSY_e              eRxBusy;
    uint8_t                    *pun8TxBuf;
    uint8_t                    *pun8RxBuf;
    uint32_t                   un32TxLen;
    uint32_t                   un32RxLen;
    uint32_t                   un32TxCnt;
    uint32_t                   un32RxCnt;

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
    bool                       bNmiEnable;
#endif
} LPUART_CTRL_BLK_t;

static LPUART_CTRL_BLK_t s_tLcb[LPUART_CH_NUM];

static void PRV_LPUART_IRQHandler(LPUART_ID_e eId);

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
static void PRV_LPUART_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < LPUART_CH_NUM; i++)
    {
        if(s_tLcb[i].bNmiEnable == true)
        {
            PRV_LPUART_IRQHandler((LPUART_ID_e)i);
        }
    }
}
#endif

#if defined(_DMAC) && defined(DMA_LPUART_NUM) && defined (LPUART_FEATURE_DMA_INTERNAL_INTERRUPT)
static void PRV_LPUART_DMAHandler(uint32_t un32Event, void *pContext)
{
    PRV_LPUART_IRQHandler((LPUART_ID_e)(un32Event));
}
#endif

static LPUART_Type *PRV_LPUART_GetReg(P_LPUART_ID_e eId)
{
    return LPUART_GetReg((uint32_t)eId);
}

static HAL_ERR_e PRV_LPUART_SetScuEnable(P_LPUART_ID_e eId, bool bEnable)
{
    return LPUART_SetScuEnable((P_LPUART_ID_e)eId, bEnable);
}

#if defined(_DMAC) && defined(DMA_LPUART_NUM)
static HAL_ERR_e PRV_LPUART_SetDMA(LPUART_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LPUART_CTRL_BLK_t *ptLcb;
    DMA_ID_e eDmaId;

    ptLcb = &s_tLcb[(uint32_t)eId];

    eErr = HPL_DMA_Init(DMA_PERI_LPUART, (uint8_t)eId);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    eErr = HPL_DMA_GetAvailChannel(&eDmaId);
    if(eErr == HAL_ERR_OK)
    {
        ptLcb->eDmaId = eDmaId;
        ptLcb->bDmaEnabled = true;
    }

#if defined (LPUART_FEATURE_DMA_INTERNAL_INTERRUPT)
    eErr = HPL_DMA_SetIRQ(DMA_PERI_LPUART, &PRV_LPUART_DMAHandler, NULL, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }
#endif

    return eErr;
}
#endif

HAL_ERR_e HAL_LPUART_Init(LPUART_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LPUART_CTRL_BLK_t *ptLcb;
    LPUART_Type *ptLpUart;

    if((uint32_t)eId >= LPUART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_LPUART_SetScuEnable((P_LPUART_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    ptLpUart = PRV_LPUART_GetReg((P_LPUART_ID_e)eId);
    ptLcb = &s_tLcb[(uint32_t)eId];

    SET_LPUART_CR_EN(ptLpUart, true);
    SET_LPUART_IER(ptLpUart, 0);

    memset(ptLcb, 0x00, sizeof(LPUART_CTRL_BLK_t));
    return eErr;
}

HAL_ERR_e HAL_LPUART_Uninit(LPUART_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LPUART_Type *ptLpUart;
    IRQn_Type eIrq;

    if((uint32_t)eId >= LPUART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLpUart = PRV_LPUART_GetReg((P_LPUART_ID_e)eId);
    
    SET_LPUART_CR_EN(ptLpUart, false);

    PRV_LPUART_SetReset((P_LPUART_ID_e)eId, true);
    PRV_LPUART_SetReset((P_LPUART_ID_e)eId, false);

    eErr = PRV_LPUART_SetScuEnable((P_LPUART_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = LPUART_GetIRQNum((P_LPUART_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tLcb[(uint32_t)eId], 0, sizeof(LPUART_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_LPUART_SetClkConfig(LPUART_ID_e eId, LPUART_CLK_CFG_t *ptClkCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= LPUART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    switch(ptClkCfg->eClk)
    {
        case LPUART_CLK_PCLK:
            SET_SCU_LPUART_CLK_SEL(ptScu, eId, LPUART_CLK_PCLK);
            break;
        case LPUART_CLK_MCCR:
            eErr = LPUART_SetMccrClk((P_LPUART_ID_e)eId, (P_LPUART_CLK_MCCR_e)ptClkCfg->eMccr, ptClkCfg->un8MccrDiv);
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    return eErr;
}

HAL_ERR_e HAL_LPUART_SetConfig(LPUART_ID_e eId, LPUART_CFG_t *ptCfg)
{
    LPUART_Type *ptLpUart;
    uint32_t un32Sampling = 0;
    uint32_t un32Numer, un32Denom;
    uint32_t un32Bdr;

    if((uint32_t)eId >= LPUART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLpUart = PRV_LPUART_GetReg((P_LPUART_ID_e)eId);

    if(ptCfg->eData < LPUART_DATA_MAX)
    {
        SET_LPUART_CR_DLEN(ptLpUart,(uint32_t)ptCfg->eData);
    }
    else
    {
        return HAL_ERR_PARAMETER;
    }

    if(ptCfg->eParity < LPUART_PARITY_MAX)
    {
        if(ptCfg->eParity != LPUART_PARITY_NONE)
        {
            SET_LPUART_CR_PARITY_EN(ptLpUart, true);
            SET_LPUART_CR_STICK_PARITY_EN(ptLpUart, true);
            SET_LPUART_CR_PARITY(ptLpUart, (uint32_t)ptCfg->eParity);
        }
        else
        {
            SET_LPUART_CR_PARITY_EN(ptLpUart, false);
            SET_LPUART_CR_STICK_PARITY_EN(ptLpUart, false);
        }
    }
    else
    {
        return HAL_ERR_PARAMETER;
    }

    if(ptCfg->eStop < LPUART_STOP_MAX)
    {
        SET_LPUART_CR_STOPBIT(ptLpUart, (uint32_t)ptCfg->eStop);
    }
    else
    {
        return HAL_ERR_PARAMETER;
    }

    SET_LPUART_CR_OVS(ptLpUart, (uint32_t)ptCfg->eOVS);

    SET_LPUART_CR_TXEN(ptLpUart, true);
    SET_LPUART_CR_RXEN(ptLpUart, true);

    switch(ptCfg->eOVS)
    {
        case LPUART_OVS_16:
            un32Sampling = 16;
            break;
        case LPUART_OVS_8:
            un32Sampling = 8;
            break;
        case LPUART_OVS_NONE:
            un32Sampling = 1;
            break;
        default:
            un32Sampling = 16;
            break;
    }

    un32Numer = LPUART_GetNumer((P_LPUART_ID_e)eId);
    un32Denom = un32Sampling * ptCfg->un32BaudRate;
    un32Bdr = (un32Numer / un32Denom);

    SET_LPUART_BDR_BDR(ptLpUart, (uint32_t)((un32Bdr - 1) & 0xFFFF));


    return HAL_ERR_OK;
}

HAL_ERR_e HAL_LPUART_SetIRQ(LPUART_ID_e eId, LPUART_OPS_e eOps, pfnLPUART_IRQ_Handler_t pfnHandler,
                          void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LPUART_CTRL_BLK_t *ptLcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= LPUART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLcb = &s_tLcb[(uint32_t)eId];
    eIrq = LPUART_GetIRQNum((P_LPUART_ID_e)eId);

    switch(eOps)
    {
        case LPUART_OPS_INTR:
#if defined(_DMAC) && defined(DMA_LPUART_NUM)
        case LPUART_OPS_INTR_DMA:
#endif
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            if(ptLcb->bNmiEnable == true)
            {
                (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
                ptLcb->bNmiEnable = false;
            }
#endif
#if defined(LPUART_FEATURE_IRQ_UNMASK_ENABLE)
            PRV_LPUART_SetIntrUnMask(eIrq, true);
#endif
            ptLcb->pfnHandler = pfnHandler;
            ptLcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);

#if defined(_DMAC) && defined(DMA_LPUART_NUM)
            if(eOps == LPUART_OPS_INTR_DMA)
            {
                eErr = PRV_LPUART_SetDMA(eId);
            }
#endif
            break;
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
        case LPUART_OPS_NMI:
        case LPUART_OPS_NMI_DMA:
            eErr = HPL_NMI_SetSource(eIrq, &PRV_LPUART_NMIHandler, pContext, true);
            if(eErr == HAL_ERR_OK)
            {
                ptLcb->pfnHandler = pfnHandler;
                ptLcb->pContext = pContext;
            }
            ptLcb->bNmiEnable = true;
#if defined(_DMAC) && defined(DMA_LPUART_NUM)
            if(eOps == LPUART_OPS_NMI_DMA)
            {
                eErr = PRV_LPUART_SetDMA(eId);
            }
#endif
            break;
#endif
        case LPUART_OPS_POLL:
        default:
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
            ptLcb->bNmiEnable = false;
#endif
#if defined(_DMAC) && defined(DMA_LPUART_NUM)
            if(ptLcb->bDmaEnabled == true)
            {
                HPL_DMA_Uninit(DMA_PERI_LPUART, (uint8_t)eId);
                ptLcb->bDmaEnabled = false;
            }
#endif
#if defined(LPUART_FEATURE_IRQ_UNMASK_ENABLE)
            PRV_LPUART_SetIntrUnMask(eIrq, false);
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptLcb->pfnHandler = NULL;
            ptLcb->pContext = NULL;
            break;
    }

    ptLcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_LPUART_Transmit(LPUART_ID_e eId, uint8_t *pun8Out, uint32_t un32Len, bool bEnForcePoll)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LPUART_CTRL_BLK_t *ptLcb;
    LPUART_Type *ptLpUart;
#if defined(_DMAC) && defined(DMA_LPUART_NUM)
    DMA_CFG_t tDmaCfg =
    {
        .ePeri = DMA_PERI_LPUART,
        .ePeriId = (DMA_PERI_ID_e)eId,
        .un32PeriNum = 0,
        .eSize = DMA_BUS_SIZE_BYTE,
        .eDir = DMA_DIR_MEM_TO_PERI
    };
#endif

    if((uint32_t)eId >= LPUART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLpUart = PRV_LPUART_GetReg((P_LPUART_ID_e)eId);
    ptLcb = &s_tLcb[(uint32_t)eId];

    if (ptLcb->eTxBusy == LPUART_BUSY_TX)
    {
        return HAL_ERR_BUSY;
    }

    ptLcb->eTxBusy = LPUART_BUSY_TX;
    ptLcb->pun8TxBuf = (uint8_t *)pun8Out;
    ptLcb->un32TxLen = un32Len;
    ptLcb->un32TxCnt = 0;

    if (ptLcb->eOps == LPUART_OPS_POLL || bEnForcePoll == true)
    {
        while (ptLcb->un32TxLen > ptLcb->un32TxCnt)
        {
            SET_LPUART_TDR_DATA(ptLpUart,ptLcb->pun8TxBuf[ptLcb->un32TxCnt++]);
            while (!GET_LPUART_IFSR_TXC(ptLpUart))
            {
            }
            SET_LPUART_IFSR_TXC(ptLpUart, true);
        }
        ptLcb->eTxBusy = LPUART_BUSY_NONE;
    }
    else
    {
#if defined(_DMAC) && defined(DMA_LPUART_NUM)
        if(ptLcb->eOps == LPUART_OPS_INTR_DMA
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
           || ptLcb->eOps == LPUART_OPS_NMI_DMA
#endif
          )
        {
            eErr = (HAL_ERR_e)HPL_DMA_GetPeriSelectNumber(DMA_PERI_LPUART, (DMA_PERI_ID_e)eId, DMA_PERI_COM_TX, &tDmaCfg.un32PeriNum);
            if(eErr == HAL_ERR_OK)
            {
                HPL_DMA_SetConfig(ptLcb->eDmaId, &tDmaCfg);
                SET_LPUART_IER_DTXIEN(ptLpUart, true);
                HPL_DMA_Start(ptLcb->eDmaId, (uint32_t)ptLcb->pun8TxBuf, (uint32_t)GET_LPUART_TDR_ADDR(ptLpUart), ptLcb->un32TxLen);
            }
        }
        else
#endif
        {
            SET_LPUART_IFSR_TXC(ptLpUart, true);
            SET_LPUART_TDR_DATA(ptLpUart, ptLcb->pun8TxBuf[ptLcb->un32TxCnt++]);
            SET_LPUART_IER_TXC(ptLpUart, true);
        }
    }

    return eErr;
}

HAL_ERR_e HAL_LPUART_Receive(LPUART_ID_e eId, uint8_t *pun8In, uint32_t un32Len, bool bEnForcePoll)
{
    LPUART_CTRL_BLK_t *ptLcb;
    LPUART_Type *ptLpUart;
    uint32_t un32Status, un32Timeout;
    IRQn_Type eIrq;
    HAL_ERR_e eErr = HAL_ERR_OK;
#if defined(_DMAC) && defined(DMA_LPUART_NUM)
    DMA_CFG_t tDmaCfg =
    {
        .ePeri = DMA_PERI_LPUART,
        .ePeriId = (DMA_PERI_ID_e)eId,
        .un32PeriNum = 0,
        .eSize = DMA_BUS_SIZE_BYTE,
        .eDir = DMA_DIR_PERI_TO_MEM
    };
#endif

    if((uint32_t)eId >= LPUART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLpUart = PRV_LPUART_GetReg((P_LPUART_ID_e)eId);
    ptLcb = &s_tLcb[(uint32_t)eId];

    if (ptLcb->eRxBusy == LPUART_BUSY_RX)
    {
        return HAL_ERR_BUSY;
    }

    ptLcb->eRxBusy = LPUART_BUSY_RX;
    ptLcb->pun8RxBuf = (uint8_t *)pun8In;
    ptLcb->un32RxLen = un32Len;
    ptLcb->un32RxCnt = 0;

    if (ptLcb->eOps == LPUART_OPS_POLL || bEnForcePoll == true)
    {
        eIrq = LPUART_GetIRQNum((P_LPUART_ID_e)eId);
        if (ptLcb->eOps != LPUART_OPS_POLL)
        {
            NVIC_DisableIRQ(eIrq);
        }

        while (ptLcb->un32RxLen > ptLcb->un32RxCnt)
        {
            un32Status = 0;
            un32Timeout = LPUART_RX_TIMEOUT;
            while (!GET_LPUART_IFSR_RXC(ptLpUart) && un32Timeout)
            {
                un32Timeout--;
            }

            if (un32Timeout == 0)
            {
                ptLcb->eRxBusy = LPUART_BUSY_NONE;
                eErr = HAL_ERR_TIMEOUT;
                break;
            }

            un32Status |= GET_LPUART_IFSR_FE(ptLpUart);
            un32Status |= GET_LPUART_IFSR_PE(ptLpUart);
            un32Status |= GET_LPUART_IFSR_OE(ptLpUart);

            if (un32Status)
            {
                ptLcb->eRxBusy = LPUART_BUSY_NONE;
                eErr = HAL_ERR_HW;
                break;
            }
            ptLcb->pun8RxBuf[ptLcb->un32RxCnt++] = GET_LPUART_RDR_DATA(ptLpUart);
            SET_LPUART_IFSR_RXC(ptLpUart, true);
        }

        ptLcb->eRxBusy = LPUART_BUSY_NONE;
        if (ptLcb->eOps != LPUART_OPS_POLL)
        {
            NVIC_EnableIRQ(eIrq);
        }
    }
    else
    {
        /* Warning Message [Pa130] at IAR */
        uint32_t un32Data = GET_LPUART_RDR_DATA(ptLpUart);
        (void)un32Data;

#if defined(_DMAC) && defined(DMA_LPUART_NUM)
        if(ptLcb->eOps == LPUART_OPS_INTR_DMA
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
           || ptLcb->eOps == LPUART_OPS_NMI_DMA
#endif
          )
        {
            eErr = (HAL_ERR_e)HPL_DMA_GetPeriSelectNumber(DMA_PERI_LPUART, (DMA_PERI_ID_e)eId, DMA_PERI_COM_RX, &tDmaCfg.un32PeriNum);
            if(eErr == HAL_ERR_OK)
            {
                HPL_DMA_SetConfig(ptLcb->eDmaId, &tDmaCfg);
                SET_LPUART_IER_DRXIEN(ptLpUart, true);
                HPL_DMA_Start(ptLcb->eDmaId, (uint32_t)GET_LPUART_RDR_ADDR(ptLpUart), (uint32_t)ptLcb->pun8RxBuf, ptLcb->un32RxLen);
            }
        }
        else
#endif
        {
            SET_LPUART_IER_RXC(ptLpUart, true);
        }
    }

    return eErr;
}

HAL_ERR_e HAL_LPUART_Abort(LPUART_ID_e eId)
{
    LPUART_CTRL_BLK_t *ptLcb;

    if((uint32_t)eId >= LPUART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLcb = &s_tLcb[(uint32_t)eId];

    ptLcb->eTxBusy = LPUART_BUSY_NONE;
    ptLcb->eRxBusy = LPUART_BUSY_NONE;

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_LPUART_GetBusyStatus(LPUART_ID_e eId, bool *pbBusy)
{
    if((uint32_t)eId >= LPUART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_LPUART_GetLineStatus(LPUART_ID_e eId, uint8_t *pun8Status)
{

    (void)pun8Status;

    if((uint32_t)eId >= LPUART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_LPUART_SetIFDelay(LPUART_ID_e eId, uint8_t un8Delay)
{
    (void)un8Delay;

    if((uint32_t)eId >= LPUART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_LPUART_SetBaudRateCompensation(LPUART_ID_e eId, LPUART_BC_CFG_t *ptBcCfg)
{
    LPUART_Type *ptLpUart;

    if((uint32_t)eId >= LPUART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLpUart = PRV_LPUART_GetReg((P_LPUART_ID_e)eId);

    if(ptBcCfg->bEnable == true)
    {
        SET_LPUART_BCMP_SIGN(ptLpUart, (uint8_t)ptBcCfg->eBC);
        SET_LPUART_BCMP_BIT(ptLpUart, ptBcCfg->un16BC);
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_LPUART_SetReceiveCharDetect(LPUART_ID_e eId, LPUART_RCD_CFG_t *ptRcdCfg)
{
    LPUART_Type *ptLpUart;

    if((uint32_t)eId >= LPUART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLpUart = PRV_LPUART_GetReg((P_LPUART_ID_e)eId);

    if(ptRcdCfg->bEnable == true)
    {
        SET_LPUART_RCDR_DATA(ptLpUart, ptRcdCfg->un8RCDData);
        SET_LPUART_IER_RCD_EN(ptLpUart, ptRcdCfg->bIntrEnable);
    }

    SET_LPUART_CR_RCD_EN(ptLpUart, ptRcdCfg->bEnable);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_LPUART_SetTransmitDelay(LPUART_ID_e eId, LPUART_TXDLY_CFG_t *ptTxDlyCfg)
{
    LPUART_Type *ptLpUart;

    if((uint32_t)eId >= LPUART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLpUart = PRV_LPUART_GetReg((P_LPUART_ID_e)eId);

    if(ptTxDlyCfg->bEnable == true)
    {
        SET_LPUART_DLYDR_DATA(ptLpUart, ptTxDlyCfg->un8Delay);
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_LPUART_SetDataEnable(LPUART_ID_e eId, LPUART_DE_CFG_t *ptDeCfg)
{
    LPUART_Type *ptLpUart;

    if ((uint32_t)eId >= LPUART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLpUart = PRV_LPUART_GetReg((P_LPUART_ID_e)eId);

    if (ptDeCfg->bEnable == true)
    {
        SET_LPUART_CR_DE_STIME(ptLpUart, ptDeCfg->un8StartTime);
        SET_LPUART_CR_DE_FTIME(ptLpUart, ptDeCfg->un8FinishTime);
        SET_LPUART_CR_DE_POL(ptLpUart, ptDeCfg->bPolarity);
    }

    SET_LPUART_CR_DE_EN(ptLpUart, ptDeCfg->bEnable);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_LPUART_SetReceiveTimeout(LPUART_ID_e eId, LPUART_RTO_CFG_t *ptRtoCfg)
{
    LPUART_Type *ptLpUart;

    if ((uint32_t)eId >= LPUART_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLpUart = PRV_LPUART_GetReg((P_LPUART_ID_e)eId);

    if(ptRtoCfg->bEnable == true)
    {
        SET_LPUART_CR_RTO_CNT(ptLpUart, ptRtoCfg->un32TimeOut);
        SET_LPUART_IER_RTO_EN(ptLpUart, ptRtoCfg->bIntrEnable);
    }

    SET_LPUART_CR_RTO_EN(ptLpUart, ptRtoCfg->bEnable);

    return HAL_ERR_OK;
}

static void PRV_LPUART_IRQHandler(LPUART_ID_e eId)
{
    LPUART_CTRL_BLK_t *ptLcb;
    LPUART_Type *ptLpUart;
    uint32_t un32Data;
    volatile uint32_t un32IntStatus;
    volatile uint32_t un32Event = 0;

    if((uint32_t)eId >= LPUART_CH_NUM)
    {
        return;
    }

    ptLpUart = PRV_LPUART_GetReg((P_LPUART_ID_e)eId);
    ptLcb = &s_tLcb[(uint32_t)eId];

    un32IntStatus = GET_LPUART_IFSR(ptLpUart);

    if (GET_LPUART_IFSR_FE(ptLpUart))
    {
        un32Event |= LPUART_EVENT_FRAME_ERROR;
    }

    if (GET_LPUART_IFSR_PE(ptLpUart))
    {
        un32Event |= LPUART_EVENT_PARITY_ERROR;
    }

    if (GET_LPUART_IFSR_OE(ptLpUart))
    {
        un32Event |= LPUART_EVENT_OVERFLOW_ERROR;
    }

    if (GET_LPUART_IFSR_RTO(ptLpUart))
    {
        un32Event |= LPUART_EVENT_RTO;
        SET_LPUART_CR_RTO_EN(ptLpUart, false);
    }

    if (GET_LPUART_IFSR_RDC(ptLpUart))
    {
        un32Event |= LPUART_EVENT_RCD;
    }

    if (un32Event != 0)
    {
        /* Warning Message [Pa130] at IAR */
        un32Data = GET_LPUART_RDR_DATA(ptLpUart);
        (void)un32Data;
        SET_LPUART_IER(ptLpUart, 0x00);
    }
    else
    {
#if defined(_DMAC) && defined(DMA_LPUART_NUM)
#if defined (LPUART_FEATURE_DMA_INTERNAL_INTERRUPT)
        if (ptLcb->eOps == LPUART_OPS_INTR_DMA)
        {
            if (ptLcb->eTxBusy == LPUART_BUSY_TX)
            {
                un32Event |= LPUART_EVENT_TX_DONE;
                ptLcb->eTxBusy = LPUART_BUSY_NONE;
            }

            if (ptLcb->eRxBusy == LPUART_BUSY_RX)
            {
                un32Event |= LPUART_EVENT_RX_DONE;
                ptLcb->eRxBusy = LPUART_BUSY_NONE;
            }

            HPL_DMA_Stop(ptLcb->eDmaId);
            ptLcb->bDmaEnabled = false;
            goto done;
        }
#else
        if ((un32IntStatus & LPUART_IIR_DMA_RX_DONE) == LPUART_IIR_DMA_RX_DONE)
        {
            ptLcb->eRxBusy = LPUART_BUSY_NONE;
            SET_LPUART_IER_DRXIEN(ptLpUart, false);
            HPL_DMA_Stop(ptLcb->eDmaId);
            un32Event |= LPUART_EVENT_RX_DONE;
            goto done;
        }

        if ((un32IntStatus & LPUART_IIR_DMA_RX_DONE) == LPUART_IIR_DMA_RX_DONE)
        {
            ptLcb->eTxBusy = LPUART_BUSY_NONE;
            SET_LPUART_IER_DTXIEN(ptLpUart, false);
            HPL_DMA_Stop(ptLcb->eDmaId);
            un32Event |= LPUART_EVENT_TX_DONE;
            goto done;
        }
#endif
#endif
        if (un32IntStatus & LPUART_IIR_RX_DONE)
        {
            SET_LPUART_IFSR_RXC(ptLpUart, true);

            ptLcb->pun8RxBuf[ptLcb->un32RxCnt++] = GET_LPUART_RDR_DATA(ptLpUart);

            if (ptLcb->un32RxLen == ptLcb->un32RxCnt)
            {
                SET_LPUART_IER_RXC(ptLpUart, false);
                ptLcb->eRxBusy = LPUART_BUSY_NONE;
                un32Event |= LPUART_EVENT_RX_DONE;
            }

            goto done;
        }

        if (un32IntStatus & LPUART_IIR_TX_DONE)
        {
            SET_LPUART_IFSR_TXC(ptLpUart, true);

            if (ptLcb->un32TxLen != ptLcb->un32TxCnt)
            {
                SET_LPUART_TDR_DATA(ptLpUart, ptLcb->pun8TxBuf[ptLcb->un32TxCnt++]);
            }
            else
            {
                ptLcb->eTxBusy = LPUART_BUSY_NONE;
                SET_LPUART_IER_TXC(ptLpUart, false);
                un32Event |= LPUART_EVENT_TX_DONE;
            }

            goto done;
        }
    }

done:

    if (ptLcb->pfnHandler && un32Event)
    {
        ptLcb->pfnHandler(un32Event, ptLcb->pContext);
    }
}

void LPUART0_IRQHandler(void)
{
#if defined (LPUART_FEATURE_SUPPORT_MULTI_IRQ)
    LPUART_Type *ptLpUart;
    uint32_t un32IntStatus;
    
    ptLpUart = PRV_LPUART_GetReg(P_LPUART_ID_0);
    un32IntStatus = GET_LPUART_IFSR(ptLpUart);
    if (un32IntStatus & 0xFF)
    {
        PRV_LPUART_IRQHandler(LPUART_ID_0);
    }
    ptLpUart = PRV_LPUART_GetReg(P_LPUART_ID_1);
    un32IntStatus = GET_LPUART_IFSR(ptLpUart);
    if (un32IntStatus & 0xFF)
    {
        PRV_LPUART_IRQHandler(LPUART_ID_1);
    }
#else
    PRV_LPUART_IRQHandler(LPUART_ID_0);
#endif
}

void LPUART1_IRQHandler(void)
{
    PRV_LPUART_IRQHandler(LPUART_ID_1);
}

void LPUART2_IRQHandler(void)
{
    PRV_LPUART_IRQHandler(LPUART_ID_2);
}

void LPUART3_IRQHandler(void)
{
    PRV_LPUART_IRQHandler(LPUART_ID_3);
}

void LPUART4_IRQHandler(void)
{
    PRV_LPUART_IRQHandler(LPUART_ID_4);
}

void LPUART5_IRQHandler(void)
{
    PRV_LPUART_IRQHandler(LPUART_ID_5);
}

#endif /* _LPUART */
