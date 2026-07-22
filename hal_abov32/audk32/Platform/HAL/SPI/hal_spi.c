/**
 *******************************************************************************
 * @file        hal_spi.c
 * @author      ABOV R&D Division
 * @brief       SPI communication
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

#if defined(_SPI)
#include "hal_spi.h"
#include "hal_spi_prv.h"

#if defined(_DMAC) && defined(DMA_SPI_NUM)
#include "hpl_dma.h"
#endif

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
#include "hpl_nmi.h"
#endif

#define SPI_POLLING_DELAY           20
#define SPI_DEFAULT_TX_DMA_DELAY    100
#define SPI_DUMMY_DATA              0x1FFFF

typedef struct
{
    SPI_OPS_e               eOps;
    pfnSPI_IRQ_Handler_t    pfnHandler;
    void                    *pContext;

#if defined(_DMAC) && defined(DMA_SPI_NUM)
    DMA_ID_e                eDmaId;
    bool                    bDmaEnabled;
#endif

    SPI_MODE_e              eMode;
    bool                    bTxBusy;
    bool                    bRxBusy;
    uint8_t                 *pun8TxBuf;
    uint8_t                 *pun8RxBuf;
    uint32_t                un32TxLen;
    uint32_t                un32RxLen;
    uint32_t                un32TxCnt;
    uint32_t                un32RxCnt;
#if defined (SPI_FEATURE_MASTER_SS_PIN_BY_GPIO)
    uint16_t                un16Baudrate;
#endif

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
    bool                    bNmiEnable;
#endif

} SPI_CTRL_BLK_t;

static SPI_CTRL_BLK_t s_tScb[SPI_CH_NUM];

static void PRV_SPI_IRQHandler(SPI_ID_e eId);

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
static void PRV_SPI_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < SPI_CH_NUM; i++)
    {
        if(s_tScb[i].bNmiEnable == true)
        {
            PRV_SPI_IRQHandler((SPI_ID_e)i);
        }
    }
}
#endif

#if defined(_DMAC) && defined(DMA_SPI_NUM) && defined (SPI_FEATURE_DMA_INTERNAL_INTERRUPT)
static void PRV_SPI_DMAHandler(uint32_t un32Event, void *pContext)
{
    PRV_SPI_IRQHandler((SPI_ID_e)(un32Event));
}
#endif

static SPI_Type *PRV_SPI_GetReg(SPI_ID_e eId)
{
    return SPI_GetReg((P_SPI_ID_e)eId);
}

static HAL_ERR_e PRV_SPI_SetScuEnable(P_SPI_ID_e eId, bool bEnable)
{
    return SPI_SetScuEnable((P_SPI_ID_e)eId, bEnable);
}

#if defined(_DMAC) && defined(DMA_SPI_NUM)
static HAL_ERR_e PRV_SPI_SetDMA(SPI_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SPI_CTRL_BLK_t *ptScb;
    DMA_ID_e eDmaId;

    ptScb = &s_tScb[(uint32_t)eId];

    eErr = HPL_DMA_Init(DMA_PERI_SPI, (uint8_t)eId);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    eErr = (HAL_ERR_e)HPL_DMA_GetAvailChannel(&eDmaId);
    if(eErr == HAL_ERR_OK)
    {
        ptScb->eDmaId = eDmaId;
        ptScb->bDmaEnabled = true;
    }

#if defined (SPI_FEATURE_DMA_INTERNAL_INTERRUPT)
    eErr = HPL_DMA_SetIRQ(DMA_PERI_SPI, &PRV_SPI_DMAHandler, NULL, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }
#endif

    return eErr;
}
#endif

#if defined(EXTRN_HAL_SPI_TRANSCEIVE)
static void PRV_SPI_Transmit(SPI_Type *ptSpi, uint8_t *pun8TxBuf, uint32_t un32Len)
{
    uint32_t un32TxData;
    uint32_t un32Step;

    while(un32Len)
    {
        un32TxData = 0;
        switch(GET_SPI_CR_DATA_BIT(ptSpi))
        {
            case SPI_DATA_17:
                un32TxData |= (*pun8TxBuf++ << 16);
                un32TxData |= (*pun8TxBuf++ << 8);
                un32TxData |= *pun8TxBuf++;
                un32Step = 3;
                break;
            case SPI_DATA_16:
            case SPI_DATA_9:
                un32TxData |= (*pun8TxBuf++ << 8);
                un32TxData |= *pun8TxBuf++;
                un32Step = 2;                
                break;
            case SPI_DATA_8:
            default:
                un32TxData |= *pun8TxBuf++;
                un32Step = 1;                
				break;
        }
    
        while(!(GET_SPI_SR_TX_RDY(ptSpi) && GET_SPI_SR_TX_IDLE(ptSpi)));
        SET_SPI_DR_TX(ptSpi, un32TxData);
    
        un32Len = un32Len - un32Step;
    }
    while(!(GET_SPI_SR_TX_RDY(ptSpi) && GET_SPI_SR_TX_IDLE(ptSpi)));    
}

static void PRV_SPI_Receive(SPI_Type *ptSpi, uint8_t *pun8RxBuf, uint32_t un32Len)
{
    uint32_t un32RxData;
    uint32_t un32Step;

    while(un32Len)
    {
        while(!GET_SPI_SR_RX_RDY(ptSpi));
        un32RxData = GET_SPI_DR_RX(ptSpi);    

        switch(GET_SPI_CR_DATA_BIT(ptSpi))
        {
            case SPI_DATA_17:
                *pun8RxBuf++ = (uint8_t)(un32RxData);
                *pun8RxBuf++ = (uint8_t)(un32RxData >> 8);
                *pun8RxBuf++ = (uint8_t)((un32RxData >> 16) & 0x01);
                 un32Step = 3;
                 break;
            case SPI_DATA_16:
            case SPI_DATA_9:            
                *pun8RxBuf++ = (uint8_t)(un32RxData >> 0);
                *pun8RxBuf++ = (uint8_t)(un32RxData >> 8);
                un32Step = 2;
                break;
            case SPI_DATA_8:
            default:
                 *pun8RxBuf++ = (uint8_t)un32RxData;
                 un32Step = 1;
                 break;
        }
        
        un32Len = un32Len - un32Step;
//        printf(">0x%x\n", un32RxData);
        
    }
}
#endif

HAL_ERR_e HAL_SPI_Init(SPI_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= SPI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_SPI_SetScuEnable((P_SPI_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tScb[(uint32_t)eId], 0x00, sizeof(SPI_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_SPI_Uninit(SPI_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= SPI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_SPI_SetScuEnable((P_SPI_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = SPI_GetIRQNum((P_SPI_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tScb[(uint32_t)eId], 0x00, sizeof(SPI_CTRL_BLK_t));

    return eErr;
}

HAL_ERR_e HAL_SPI_SetConfig(SPI_ID_e eId, SPI_CFG_t *ptCfg)
{
    SPI_Type *ptSpi;
    bool bCPol = false, bCPha = false;
    uint16_t un16Value = 0;
#if defined (SPI_FEATURE_MASTER_SS_PIN_BY_GPIO)
    SPI_CTRL_BLK_t *ptScb;
#endif

    if((uint32_t)eId >= SPI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if((ptCfg->eMode >= SPI_MODE_MAX)
        || (ptCfg->eData >= SPI_DATA_MAX)
        || (ptCfg->eBitOrder >= SPI_BIT_ORDER_MAX)
        || (ptCfg->eClkMode >= SPI_CLK_MODE_MAX))
    {
        return HAL_ERR_NOT_SUPPORTED;
    }

    ptSpi = PRV_SPI_GetReg(eId);
#if defined (SPI_FEATURE_MASTER_SS_PIN_BY_GPIO)
    ptScb = &s_tScb[(uint32_t)eId];
#endif

    SET_SPI_CR_MODE(ptSpi,(uint8_t)ptCfg->eMode);

    SET_SPI_CR_DATA_BIT(ptSpi,(uint8_t)ptCfg->eData);

    SET_SPI_CR_BIT_ORDER(ptSpi,(uint8_t)ptCfg->eBitOrder);

    switch(ptCfg->eClkMode)
    {
        case SPI_CLK_MODE_CPOL_0_CPHA_0:
            break;
        case SPI_CLK_MODE_CPOL_0_CPHA_1:
            bCPha = true;
            break;
        case SPI_CLK_MODE_CPOL_1_CPHA_0:
            bCPol = true;
            break;
        case SPI_CLK_MODE_CPOL_1_CPHA_1:
            bCPol = true;
            bCPha = true;
            break;
        default:
            break;
    }

    SET_SPI_CR_CPOL(ptSpi,bCPol);
    SET_SPI_CR_CPHA(ptSpi,bCPha);

    SET_SPI_CR_SS_MANUAL(ptSpi, (uint8_t)ptCfg->bSSManual);

    SET_SPI_CR_SS_POL(ptSpi, (uint8_t)ptCfg->eSSPol);

    if(ptCfg->un16BaudRate < 2)
    {
        un16Value = 0x02;
    }
    else
    {
        un16Value = ptCfg->un16BaudRate;
    }
    SET_SPI_CR_BAUDRATE(ptSpi, un16Value);
#if defined (SPI_FEATURE_MASTER_SS_PIN_BY_GPIO)
    ptScb->un16Baudrate = un16Value;
#endif

    if(ptCfg->un8DelayStart == 0)
    {
        un16Value = 1;
    }
    else
    {
        un16Value = ptCfg->un8DelayStart;
    }
    SET_SPI_CR_DELAY_START(ptSpi, un16Value);

    if(ptCfg->un8DelayBurst == 0)
    {
        un16Value = 1;
    }
    else
    {
        un16Value = ptCfg->un8DelayBurst;
    }
    SET_SPI_CR_DELAY_BURST(ptSpi, un16Value);

    if(ptCfg->un8DelayStop == 0)
    {
        un16Value = 1;
    }
    else
    {
        un16Value = ptCfg->un8DelayStop;
    }
    SET_SPI_CR_DELAY_STOP(ptSpi, un16Value);

#if defined (SPI_FEATURE_MASTER_SS_PIN_BY_GPIO)
    if (ptCfg->eMode == SPI_MODE_SLAVE)
    {
        SET_SPI_CR_SS_EN(ptSpi, true);
    }
    else
    {
        SET_SPI_CR_SS_EN(ptSpi, false);
    }
#else
    SET_SPI_CR_SS_EN(ptSpi, true);
    if (ptCfg->eMode == SPI_MODE_SLAVE)
    {
        SET_SPI_CR_SS_MASK(ptSpi, true);
    }
    else
    {
        SET_SPI_CR_SS_MASK(ptSpi, false);
    }
#endif

    SET_SPI_CR_EN(ptSpi, true);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_SPI_SetIRQ(SPI_ID_e eId, SPI_OPS_e eOps, pfnSPI_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SPI_CTRL_BLK_t *ptScb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= SPI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(eOps == SPI_OPS_INTR_DMA)
    {
#if defined(_DMAC) && defined(DMA_SPI_NUM)
#else
        return HAL_ERR_NOT_SUPPORTED;
#endif
    }

    ptScb = &s_tScb[(uint32_t)eId];
    eIrq = SPI_GetIRQNum((P_SPI_ID_e)eId);

    switch(eOps)
    {
        case SPI_OPS_INTR:
        case SPI_OPS_INTR_DMA:
#if defined(SPI_FEATURE_IRQ_UNMASK_ENABLE)
            SPI_SetIntrUnMask(eIrq, true);
#endif
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            if(ptScb->bNmiEnable == true)
            {
                (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
                ptScb->bNmiEnable = false;
            }
#endif
            ptScb->pfnHandler = pfnHandler;
            ptScb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
#if defined(_DMAC) && defined(DMA_SPI_NUM)
            if(eOps == SPI_OPS_INTR_DMA)
            {
                eErr = PRV_SPI_SetDMA(eId);
            }
#endif
            break;
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
        case SPI_OPS_NMI:
        case SPI_OPS_NMI_DMA:
            eErr = HPL_NMI_SetSource(eIrq, &PRV_SPI_NMIHandler, pContext, true);
            if(eErr == HAL_ERR_OK)
            {
                ptScb->pfnHandler = pfnHandler;
                ptScb->pContext = pContext;
            }
            ptScb->bNmiEnable = true;
#if defined(_DMAC) && defined(DMA_SPI_NUM)
            if(eOps == SPI_OPS_NMI_DMA)
            {
                eErr = PRV_SPI_SetDMA(eId);
            }
#endif
            break;
#endif
        case SPI_OPS_POLL:
        default:
#if defined(SPI_FEATURE_IRQ_UNMASK_ENABLE)
            SPI_SetIntrUnMask(eIrq, false);
#endif
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
            ptScb->bNmiEnable = false;
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
#if defined(_DMAC) && defined(DMA_SPI_NUM)
            if(ptScb->bDmaEnabled == true)
            {
                (void)HPL_DMA_Uninit(DMA_PERI_SPI, (uint8_t)eId);
                ptScb->bDmaEnabled = false;
            }
#endif
            ptScb->pContext = NULL;
            ptScb->pfnHandler = NULL;
            break;
    }

    ptScb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_SPI_Transmit(SPI_ID_e eId, uint8_t *pun8Out, uint32_t un32Len, bool bEnForcePoll)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SPI_CTRL_BLK_t *ptScb;
    SPI_Type *ptSpi;
    bool bCompleted = false;
    uint32_t un32TxData = 0;
#if defined(_DMAC) && defined(DMA_SPI_NUM)
    DMA_CFG_t tDmaCfg =
    {
        .ePeri = DMA_PERI_SPI,
        .ePeriId = (DMA_PERI_ID_e)eId,
        .un32PeriNum = 0,
        .eSize = DMA_BUS_SIZE_HALFWORD,
        .eDir = DMA_DIR_MEM_TO_PERI
    };
#endif

    if((uint32_t)eId >= SPI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptSpi = PRV_SPI_GetReg(eId);
    ptScb = &s_tScb[eId];

    if (ptScb->bTxBusy == true)
    {
        return HAL_ERR_BUSY;
    }

    ptScb->bTxBusy = true;
    ptScb->pun8TxBuf = (uint8_t *)pun8Out;
    ptScb->un32TxLen = un32Len;
    ptScb->un32TxCnt = 0;
    ptScb->un32RxLen = 0;

    SET_SPI_CR_TXBUF_CLEAR(ptSpi);

    if(ptScb->eOps == SPI_OPS_POLL || bEnForcePoll)
    {
        while(!bCompleted)
        {
            if(ptScb->un32TxCnt >= ptScb->un32TxLen)
            {
                SET_SPI_DR_TX(ptSpi, 0xFF);
                bCompleted = true;
                continue;
            }

            while(!GET_SPI_SR_TX_RDY(ptSpi))
            {
                /* Waiting for Tx Ready */
            }
#if defined(SPI_FEATURE_MASTER_SS_PIN_BY_GPIO)
            SPI_SetSSPort((P_SPI_ID_e)eId, true);
#endif

#if defined(SPI_POLLING_DELAY)
            {
                for(int i = 0; i < SPI_POLLING_DELAY; i++)
                {
                    __NOP();
                }
            }
#endif
#if defined (SPI_FEATURE_ONLY_8BIT_DATA_TX_RX)
            un32TxData |= *ptScb->pun8TxBuf++;
#else
            switch(GET_SPI_CR_DATA_BIT(ptSpi))
            {
                case SPI_DATA_17:
                    un32TxData |= (*ptScb->pun8TxBuf++ << 16);
                case SPI_DATA_16:
                case SPI_DATA_9:
                    un32TxData |= (*ptScb->pun8TxBuf++ << 8);
                case SPI_DATA_8:
                    un32TxData |= *ptScb->pun8TxBuf++;
                    break;
                default:
                    break;
            }
#endif

#if defined(SPI_FEATURE_MASTER_SS_PIN_BY_GPIO)
            SPI_SetSSPort((P_SPI_ID_e)eId, false);
#endif
            un32TxData |= *ptScb->pun8TxBuf++;
            SET_SPI_DR_TX(ptSpi, un32TxData);
            ptScb->un32TxCnt++;
            un32TxData = 0;
        }

#if defined (SPI_FEATURE_NOT_SUPPORTED_UNDERRUN_FLAG)
#else
        if(GET_SPI_SR_TX_UDR(ptSpi))
        {
            /* Clear Transmit Underrun flag */
            SET_SPI_DR_TX(ptSpi, 0xFF);
            eErr = HAL_ERR_HW;
        }
#endif

        ptScb->bTxBusy = false;
    }
    else
    {
#if defined(_DMAC) && defined(DMA_SPI_NUM)
        if(ptScb->eOps == SPI_OPS_INTR_DMA
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
           || ptScb->eOps == SPI_OPS_NMI_DMA
#endif
          )
        {
            if(!GET_SPI_CR_DATA_BIT(ptSpi))
            {
                tDmaCfg.eSize = DMA_BUS_SIZE_BYTE;
            }

            eErr = (HAL_ERR_e)HPL_DMA_GetPeriSelectNumber(DMA_PERI_SPI, (DMA_PERI_ID_e)eId, DMA_PERI_COM_TX, &tDmaCfg.un32PeriNum);
            if(eErr != HAL_ERR_OK)
            {
                return eErr;
            }

#if defined (SPI_FEATURE_MASTER_SS_PIN_BY_GPIO)
            SPI_SetSSPort((P_SPI_ID_e)eId, false);
#endif
            HPL_DMA_SetConfig(ptScb->eDmaId, &tDmaCfg);
            SET_SPI_IER_DMATX_EN(ptSpi, true);
#if defined (SPI_FEATURE_DMA_INTERNAL_INTERRUPT)
            HPL_DMA_Start(ptScb->eDmaId, (uint32_t)ptScb->pun8TxBuf, (uint32_t)GET_SPI_DR_TX_ADDR(ptSpi), ptScb->un32TxLen);
#else
            HPL_DMA_Start(ptScb->eDmaId, (uint32_t)ptScb->pun8TxBuf, (uint32_t)ptSpi, ptScb->un32TxLen);
#endif
        }
        else
#endif
        {
#if defined (SPI_FEATURE_MASTER_SS_PIN_BY_GPIO)
            SPI_SetSSPort((P_SPI_ID_e)eId, false);
#endif
#if defined (SPI_FEATURE_ONLY_8BIT_DATA_TX_RX)
            un32TxData = *ptScb->pun8TxBuf++;
            SET_SPI_DR_TX(ptSpi, un32TxData);
            ptScb->un32TxCnt++;
#endif
            SET_SPI_IER_TX_EN(ptSpi, true);
        }

    }

    return eErr;
}

HAL_ERR_e HAL_SPI_Receive(SPI_ID_e eId, uint8_t *pun8In, uint32_t un32Len, bool bEnForcePoll)
{

    HAL_ERR_e eErr = HAL_ERR_OK;
    SPI_CTRL_BLK_t *ptScb;
    SPI_Type *ptSpi;
    uint32_t un32RxData;
    bool bCompleted = false;
#if defined(_DMAC) && defined(DMA_SPI_NUM)
    DMA_CFG_t tDmaCfg =
    {
        .ePeri = DMA_PERI_SPI,
        .ePeriId = (DMA_PERI_ID_e)eId,
        .un32PeriNum = 0,
        .eSize = DMA_BUS_SIZE_HALFWORD,
        .eDir = DMA_DIR_PERI_TO_MEM
    };
#endif

    if((uint32_t)eId >= SPI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptScb = &s_tScb[eId];
    ptSpi = PRV_SPI_GetReg(eId);

    if (ptScb->bRxBusy == true)
    {
        return HAL_ERR_BUSY;
    }

    ptScb->bRxBusy = true;
    ptScb->pun8RxBuf = (uint8_t *)pun8In;
    ptScb->un32RxLen = un32Len;
    ptScb->un32RxCnt = 0;
    ptScb->un32TxLen = 0;

    SET_SPI_CR_RXBUF_CLEAR(ptSpi);

    if(ptScb->eOps == SPI_OPS_POLL || bEnForcePoll == true)
    {
        while(!bCompleted)
        {
            if(ptScb->un32RxCnt >= ptScb->un32RxLen)
            {
                bCompleted = true;
                continue;
            }

            while(!GET_SPI_SR_RX_RDY(ptSpi))
            {
                /* Waiting for Rx Ready */
            }

            un32RxData = GET_SPI_DR_RX(ptSpi);
#if defined (SPI_FEATURE_ONLY_8BIT_DATA_TX_RX)
            *(ptScb->pun8RxBuf++) = (uint8_t)(un32RxData);
#else
            switch(GET_SPI_CR_DATA_BIT(ptSpi))
            {
                case SPI_DATA_17:
                     *(ptScb->pun8RxBuf++) = (uint8_t)(un32RxData >> 16);
                case SPI_DATA_16:
                case SPI_DATA_9:
                     *(ptScb->pun8RxBuf++) = (uint8_t)(un32RxData >> 8);
                case SPI_DATA_8:
                     break;
                default:
                    break;
            }
#endif
            ptScb->un32RxCnt++;
            un32RxData = 0;
        }

#if defined (SPI_FEATURE_NOT_SUPPORTED_OVERRUN_FLAG)
#else
        if(!GET_SPI_SR_RX_OVR(ptSpi))
        {
            /* Clear Receive Overrun flag */
            un32RxData = GET_SPI_DR_RX(ptSpi);
            eErr = HAL_ERR_HW;
        }
#endif
        ptScb->bRxBusy = false;
    }
    else
    {
#if defined(_DMAC) && defined(DMA_SPI_NUM)
        if(ptScb->eOps == SPI_OPS_INTR_DMA
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
           || ptScb->eOps == SPI_OPS_NMI_DMA
#endif
          )
        {
            /* DMA */
            if(!GET_SPI_CR_DATA_BIT(ptSpi))
            {
                tDmaCfg.eSize = DMA_BUS_SIZE_BYTE;
            }

            eErr = (HAL_ERR_e)HPL_DMA_GetPeriSelectNumber(DMA_PERI_SPI, (DMA_PERI_ID_e)eId, DMA_PERI_COM_RX, &tDmaCfg.un32PeriNum);
            if(eErr != HAL_ERR_OK)
            {
                return eErr;
            }

            HPL_DMA_SetConfig(ptScb->eDmaId, &tDmaCfg);
            SET_SPI_IER_DMARX_EN(ptSpi, true);
#if defined (SPI_FEATURE_DMA_INTERNAL_INTERRUPT)
            HPL_DMA_Start(ptScb->eDmaId,(uint32_t)GET_SPI_DR_RX_ADDR(ptSpi), (uint32_t)ptScb->pun8RxBuf, ptScb->un32RxLen);
#else
            HPL_DMA_Start(ptScb->eDmaId,(uint32_t)ptSpi, (uint32_t)ptScb->pun8RxBuf, ptScb->un32RxLen);
#endif

        }
        else
#endif
        {
            SET_SPI_DR_TX(ptSpi, 0xFF);
            SET_SPI_IER_RX_EN(ptSpi, true);
        }
    }
    return eErr;
}

#if defined(EXTRN_HAL_SPI_TRANSCEIVE)
HAL_ERR_e HAL_SPI_Transceive(SPI_ID_e eId, uint8_t *pun8RxBuf, uint8_t *pun8TxBuf, uint32_t un32Len, bool bEnForcePoll)
{
    SPI_CTRL_BLK_t *ptScb;
    SPI_Type *ptSpi;
    uint32_t un32Step=0;

    if((uint32_t)eId >= SPI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptScb = &s_tScb[eId];
    ptSpi = PRV_SPI_GetReg(eId);

    if(ptScb->eOps != SPI_OPS_POLL && bEnForcePoll != true)
    {
        return HAL_ERR_NOT_SUPPORTED;
    }
    if (!GET_SPI_CR_SS_MANUAL(ptSpi))
    {
        return HAL_ERR_INVALID_USE;
    }

    SET_SPI_IER_TX_EN(ptSpi, false);
    SET_SPI_IER_RX_EN(ptSpi, false);
    SET_SPI_CR_TXBUF_CLEAR(ptSpi);

    switch (GET_SPI_CR_DATA_BIT(ptSpi)) 
    {
        case SPI_DATA_17:
            un32Step = 3;
            break;
        case SPI_DATA_16:
        case SPI_DATA_9:
            un32Step = 2;
            break;
        case SPI_DATA_8:
        default:          
            un32Step = 1;
            break;
    }    

    if (pun8RxBuf && pun8TxBuf) /* Extended SPI protocol inclduing Rx only */
    {
//        uint8_t *rx_base = pun8RxBuf;
        
        while(un32Len)
        {
            PRV_SPI_Transmit(ptSpi, pun8TxBuf, un32Step);
            PRV_SPI_Receive(ptSpi, pun8RxBuf, un32Step);

            pun8TxBuf = pun8TxBuf + un32Step;
            pun8RxBuf = pun8RxBuf + un32Step;
            un32Len = un32Len - un32Step;
        }

//        printf("0x%x 0x%x 0x%x\n", rx_base[0], rx_base[1], rx_base[2]);
    }
    else if (pun8TxBuf) /* Tx only */
    {
        PRV_SPI_Transmit(ptSpi, pun8TxBuf, un32Len);
    }
    else 
    {
        return HAL_ERR_PARAMETER;
    }
		
		return HAL_ERR_OK;
}
#endif

HAL_ERR_e HAL_SPI_SetSwapPort(SPI_ID_e eId, bool bSwap)
{

#if defined (SPI_FEATURE_SWAP_PORT)
    SPI_Type *ptSpi;

    if((uint32_t)eId >= SPI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptSpi = PRV_SPI_GetReg(eId);
    SET_SPI_CR_SWAP_PORT(ptSpi, bSwap);
    return HAL_ERR_OK;
#else
    (void)eId;
    (void)bSwap;
    return HAL_ERR_NOT_SUPPORTED;
#endif

}

static void PRV_SPI_IRQHandler(SPI_ID_e eId)
{
    SPI_CTRL_BLK_t *ptScb;
    SPI_Type *ptSpi;
    volatile uint32_t un32Event = 0;
    uint32_t un32Data = 0;

    if((uint32_t)eId >= SPI_CH_NUM)
    {
        return;
    }

    ptSpi = PRV_SPI_GetReg(eId);
    ptScb = &s_tScb[eId];

#if defined (SPI_FEATURE_NOT_SUPPORTED_SS_DETECT_FLAG)
#else
    if(ptScb->eMode == SPI_MODE_SLAVE)
    {
        if(GET_SPI_SR_SS_DETECT(ptSpi))
        {
            SET_SPI_SR_SS_DETECT(ptSpi, false);
        }
    }
#endif

#if defined(_DMAC) && defined(DMA_SPI_NUM)
#if defined (SPI_FEATURE_DMA_INTERNAL_INTERRUPT)
    if (ptScb->eOps == SPI_OPS_INTR_DMA)
    {
        if (ptScb->bTxBusy == true)
        {
            un32Event |= SPI_EVENT_TX_DONE;
#if defined (SPI_FEATURE_MASTER_SS_PIN_BY_GPIO)
            if (ptScb-> un16Baudrate < 1000)
            {
                SystemDelayUS(ptScb->un16Baudrate);
            }
            else
            {
                SystemDelayUS(SPI_DEFAULT_TX_DMA_DELAY);
            }
#endif
            ptScb->bTxBusy = false;
        }

        if (ptScb->bRxBusy == true)
        {
            un32Event |= SPI_EVENT_RX_DONE;
            ptScb->bRxBusy = false;
        }

#if defined (SPI_FEATURE_MASTER_SS_PIN_BY_GPIO)
        SPI_SetSSPort((P_SPI_ID_e)eId, true);
#endif
        HPL_DMA_Stop(ptScb->eDmaId);
        ptScb->bDmaEnabled = false;
        goto done;
    }
#else
    if(ptScb->eOps == SPI_OPS_INTR_DMA || ptScb->eOps == SPI_OPS_NMI_DMA)
    {
        if((ptScb->bTxBusy == true) && GET_SPI_SR_DMATX_DONE(ptSpi))
        {
            SET_SPI_SR_DMATX_DONE(ptSpi, false);
            SET_SPI_IER_DMATX_EN(ptSpi, false);
            un32Event |= SPI_EVENT_TX_DONE;
            ptScb->bTxBusy = false;
            HPL_DMA_Stop(ptScb->eDmaId);
        }

        if((ptScb->bRxBusy == true) && GET_SPI_SR_DMARX_DONE(ptSpi))
        {
            SET_SPI_SR_DMARX_DONE(ptSpi, false);
            SET_SPI_IER_DMARX_EN(ptSpi, false);
            un32Event |= SPI_EVENT_RX_DONE;
            ptScb->bRxBusy = false;
            HPL_DMA_Stop(ptScb->eDmaId);
        }
    }
#endif
#endif

    /* Interrupt Transmit */
    if(ptScb->un32TxLen != 0 && ptScb->bTxBusy == true)
    {
        if(ptScb->un32TxCnt >= ptScb->un32TxLen)
        {
            un32Event |= SPI_EVENT_TX_DONE;
            ptScb->bTxBusy = false;
            SET_SPI_IER_TX_EN(ptSpi, false);
#if defined(SPI_FEATURE_MASTER_SS_PIN_BY_GPIO)
            SPI_SetSSPort((P_SPI_ID_e)eId, true);
#endif
            goto done;
        }

        if (ptScb->un32TxCnt < ptScb->un32TxLen)
        {
#if defined (SPI_FEATURE_ONLY_8BIT_DATA_TX_RX)
#else
            if(GET_SPI_SR_TX_RDY(ptSpi) && GET_SPI_SR_TX_IDLE(ptSpi))
#endif
            {
#if defined (SPI_FEATURE_MASTER_SS_PIN_BY_GPIO)
                SPI_SetSSPort((P_SPI_ID_e)eId, true);
#endif
#if defined (SPI_FEATURE_ONLY_8BIT_DATA_TX_RX)
                un32Data = *ptScb->pun8TxBuf++;
#else
                switch(GET_SPI_CR_DATA_BIT(ptSpi))
                {
                    case SPI_DATA_17:
                        un32Data |= (*ptScb->pun8TxBuf++ << 16);
                    case SPI_DATA_16:
                    case SPI_DATA_9:
                        un32Data |= (*ptScb->pun8TxBuf++ << 8);
                    case SPI_DATA_8:
                        un32Data |= *ptScb->pun8TxBuf++;
                        break;
                    default:
                        break;
                }
#endif
                SET_SPI_DR_TX(ptSpi, un32Data);
                ptScb->un32TxCnt++;
                un32Data = 0;
#if defined(SPI_FEATURE_MASTER_SS_PIN_BY_GPIO)
                SPI_SetSSPort((P_SPI_ID_e)eId, false);
#endif
                goto done;
            }
        }
    }

    /* Interrupt Receive */
    if(ptScb->un32RxLen != 0 && ptScb->bRxBusy == true)
    {
        if(ptScb->un32RxCnt < ptScb->un32RxLen)
        {
#if defined (SPI_FEATURE_ONLY_8BIT_DATA_TX_RX)
#else
            if(GET_SPI_SR_RX_RDY(ptSpi) && GET_SPI_SR_BUSY(ptSpi))
#endif
            {
                un32Data = GET_SPI_DR_RX(ptSpi);

#if defined (SPI_FEATURE_ONLY_8BIT_DATA_TX_RX)
                *(ptScb->pun8RxBuf++) = (uint8_t)(un32Data);
#else
                switch(GET_SPI_CR_DATA_BIT(ptSpi))
                {
                    case SPI_DATA_17:
                         *(ptScb->pun8RxBuf++) = (uint8_t)(un32Data >> 16);
                    case SPI_DATA_16:
                    case SPI_DATA_9:
                         *(ptScb->pun8RxBuf++) = (uint8_t)(un32Data >> 8);
                    case SPI_DATA_8:
                         *(ptScb->pun8RxBuf++) = (uint8_t)(un32Data);
                         break;
                    default:
                         break;
                }
#endif
                ptScb->un32RxCnt++;

                if(ptScb->un32RxCnt >= ptScb->un32RxLen)
                {
                    un32Event |= SPI_EVENT_RX_DONE;
                    ptScb->bRxBusy = false;
                    SET_SPI_IER_RX_EN(ptSpi, false);
                    goto done;
                }
            }
        }
    }

    if(ptScb->eOps == SPI_OPS_INTR || ptScb->eOps == SPI_OPS_NMI)
    {
#if defined (SPI_FEATURE_NOT_SUPPORTED_UNDERRUN_FLAG)
#else
        if(GET_SPI_SR_TX_UDR(ptSpi) && ptScb->bTxBusy == true)
        {
            /* Clear Transmit Underrun flag */
            SET_SPI_DR_TX(ptSpi, 0xFF);
            un32Event |= SPI_EVENT_UNDERRUN;
        }
#endif

#if defined (SPI_FEATURE_NOT_SUPPORTED_OVERRUN_FLAG)
#else
        if(GET_SPI_SR_RX_OVR(ptSpi))
        {
            /* Clear Receive Overrun flag */
            GET_SPI_DR_RX(ptSpi);
            un32Event |= SPI_EVENT_OVERRUN;
        }
#endif
    }

done:
#if defined (SPI_FEATURE_ONLY_8BIT_DATA_TX_RX)
#if defined (SPI_FEATURE_SUPPORT_MULTI_IRQ)
#else
    SET_SPI_IER_FLAG(ptSpi, true);
#endif
#endif

    if (ptScb->pfnHandler && un32Event)
    {
        ptScb->pfnHandler(un32Event, ptScb->pContext);
    }
}

void SPI0_IRQHandler(void)
{
#if defined (SPI_FEATURE_SUPPORT_MULTI_IRQ)
    SPI_Type *ptSpi;
    ptSpi = PRV_SPI_GetReg(SPI_ID_0);
    if (GET_SPI_IER_FLAG(ptSpi))
    {
        PRV_SPI_IRQHandler(SPI_ID_0);
        SET_SPI_IER_FLAG(ptSpi, true);
        return;
    }
    ptSpi = PRV_SPI_GetReg(SPI_ID_1);
    if (GET_SPI_IER_FLAG(ptSpi))
    {
        PRV_SPI_IRQHandler(SPI_ID_1);
        SET_SPI_IER_FLAG(ptSpi, true);
        return;
    }
#else
    PRV_SPI_IRQHandler(SPI_ID_0);
#endif
}

void SPI1_IRQHandler(void)
{
#if defined (SPI_FEATURE_SUPPORT_MULTI_IRQ)
    SPI_Type *ptSpi;
    ptSpi = PRV_SPI_GetReg(SPI_ID_2);
    if (GET_SPI_IER_FLAG(ptSpi))
    {
        PRV_SPI_IRQHandler(SPI_ID_2);
        SET_SPI_IER_FLAG(ptSpi, true);
        return;
    }
    ptSpi = PRV_SPI_GetReg(SPI_ID_3);
    if (GET_SPI_IER_FLAG(ptSpi))
    {
        PRV_SPI_IRQHandler(SPI_ID_3);
        SET_SPI_IER_FLAG(ptSpi, true);
        return;
    }
#else
    PRV_SPI_IRQHandler(SPI_ID_1);
#endif
}

void SPI2_IRQHandler(void)
{
    PRV_SPI_IRQHandler(SPI_ID_2);
}

void SPI3_IRQHandler(void)
{
    PRV_SPI_IRQHandler(SPI_ID_3);
}

void SPI4_IRQHandler(void)
{
    PRV_SPI_IRQHandler(SPI_ID_4);
}

void SPI5_IRQHandler(void)
{
    PRV_SPI_IRQHandler(SPI_ID_5);
}

void SPI6_IRQHandler(void)
{
    PRV_SPI_IRQHandler(SPI_ID_6);
}

void SPI7_IRQHandler(void)
{
    PRV_SPI_IRQHandler(SPI_ID_7);
}

void SPI8_IRQHandler(void)
{
    PRV_SPI_IRQHandler(SPI_ID_8);
}

void SPI9_IRQHandler(void)
{
    PRV_SPI_IRQHandler(SPI_ID_9);
}

void SPI10_IRQHandler(void)
{
    PRV_SPI_IRQHandler(SPI_ID_10);
}

void SPI11_IRQHandler(void)
{
    PRV_SPI_IRQHandler(SPI_ID_11);
}

#endif /* _SPI */
