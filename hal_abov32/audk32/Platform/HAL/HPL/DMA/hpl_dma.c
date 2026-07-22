/**
 *******************************************************************************
 * @file        hpl_dma.c
 * @author      ABOV R&D Division
 * @brief       Direct Memory Access
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

#if defined(_DMAC)
#include "hpl_dma.h"
#include "hpl_dma_prv.h"

#if defined (DMA_FEATURE_INTERNAL_INTERRUPT)
typedef struct
{
    bool                    bEnable;
    pfnDMA_IRQ_Handler_t    pfnHandler;
    void                    *pContext;
} DMA_INTR_BLK_t;
#endif

typedef struct
{
    bool    bEnable;
    DMA_PERI_e ePeri;
    DMA_PERI_ID_e ePeriId;
} DMA_CTRL_BLK_t;

typedef struct
{
    uint16_t un16Dma;
#if defined(DMA_UART_NUM)
    uint16_t un16Uart;
#endif

#if defined(DMA_USART_NUM)
    uint16_t un16Usart;
#endif

#if defined(DMA_SPI_NUM)
    uint16_t un16Spi;
#endif

#if defined(DMA_CRC_NUM)
    uint16_t un16Crc;
#endif

#if defined(DMA_ADC_NUM)
    uint16_t un16Adc;
#endif

#if defined(DMA_DAC_NUM)
    uint16_t un16Dac;
#endif

#if defined(DMA_AES_NUM)
    uint16_t un16Aes;
#endif

#if defined(DMA_I2C_NUM)
    uint16_t un16I2c;
#endif

#if defined(DMA_LPUART_NUM)
    uint16_t un16Lpuart;
#endif

#if defined (DMA_FEATURE_INTERNAL_INTERRUPT)

#if defined(DMA_UART_NUM)
    DMA_INTR_BLK_t    tUartDib;
#endif
#if defined(DMA_USART_NUM)
    DMA_INTR_BLK_t    tUsartDib;
#endif

#if defined(DMA_SPI_NUM)
    DMA_INTR_BLK_t    tSpiDib;
#endif

#if defined(DMA_CRC_NUM)
    DMA_INTR_BLK_t    tCrcDib;
#endif

#if defined(DMA_ADC_NUM)
    DMA_INTR_BLK_t    tAdcDib;
#endif

#if defined(DMA_DAC_NUM)
    DMA_INTR_BLK_t    tDacDib;
#endif

#if defined(DMA_AES_NUM)
    DMA_INTR_BLK_t    tAesDib;
#endif

#if defined(DMA_I2C_NUM)
    DMA_INTR_BLK_t    tI2cDib;
#endif

#if defined(DMA_LPUART_NUM)
    DMA_INTR_BLK_t    tLpUartDib;
#endif

#endif /* DMA_FATURE_INTERNAL_INTERRUPT */

} DMA_RES_BLK_t;


static bool s_bDmaInit = false;
static bool s_abDMASetup[DMA_CH_NUM];
static DMA_CTRL_BLK_t s_tDcb[DMA_CH_NUM];
static DMA_RES_BLK_t s_tDrb;

static DMA_Type *PRV_DMA_GetReg(DMA_ID_e eId)
{
    return DMA_GetReg((P_DMA_ID_e)eId);
}

#if defined (DMA_FEATURE_INTERNAL_INTERRUPT)
static void PRV_DMA_SetIntrEnable(bool bEnable)
{
    IRQn_Type eIrq;

    for (uint8_t i = 0; i < DMA_MAX_IRQ; i++)
    {
        eIrq = DMA_GetIRQNum(i);
        NVIC_ClearPendingIRQ(eIrq); 
        if (bEnable)
        {
            NVIC_SetPriority(eIrq, 0);
            NVIC_EnableIRQ(eIrq);
#if defined(DMA_FEATURE_IRQ_UNMASK_ENABLE)
            DMA_SetIntrUnMask(eIrq, true);
#endif
        }
        else
        {
            NVIC_DisableIRQ(eIrq);
#if defined(DMA_FEATURE_IRQ_UNMASK_ENABLE)
            DMA_SetIntrUnMask(eIrq, false);
#endif
        }
    }
}

DMA_INTR_BLK_t* PRV_DMA_GetIntrBlk(DMA_PERI_e ePeri)
{
    DMA_INTR_BLK_t *ptDib = NULL;

    switch(ePeri)
    {
        case DMA_PERI_IDLE:
            break;
#if defined(DMA_UART_NUM)
        case DMA_PERI_UART:
            ptDib = &s_tDrb.tUartDib;
            break;
#endif
#if defined(DMA_USART_NUM)
        case DMA_PERI_USART:
            ptDib = &s_tDrb.tUsartDib;
            break;
#endif
#if defined(DMA_SPI_NUM)
	case DMA_PERI_SPI:
            ptDib = &s_tDrb.tSpiDib;
            break;
#endif
#if defined(DMA_CRC_NUM)
        case DMA_PERI_CRC:
            ptDib = &s_tDrb.tCrcDib;
            break;
#endif
#if defined(DMA_ADC_NUM)
        case DMA_PERI_ADC:
            ptDib = &s_tDrb.tAdcDib;
            break;
#endif
#if defined(DMA_DAC_NUM)
        case DMA_PERI_DAC:
            ptDib = &s_tDrb.tDacDib;
            break;
#endif
#if defined(DMA_AES_NUM)
        case DMA_PERI_AES:
            ptDib = &s_tDrb.tAesDib;
            break;
#endif
#if defined(DMA_I2C_NUM)
        case DMA_PERI_I2C:
            ptDib = &s_tDrb.tI2cDib;
            break;
#endif
#if defined(DMA_LPUART_NUM)
        case DMA_PERI_LPUART:
            ptDib = &s_tDrb.tLpUartDib;
            break;
#endif
        default:
            break;
    }

    return ptDib;
}
#endif

HAL_ERR_e HPL_DMA_Init(DMA_PERI_e ePeri, uint8_t un8ChNum)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    
    if(s_bDmaInit == false)
    {
        memset(&s_tDrb, 0x00, sizeof(DMA_RES_BLK_t));
        memset(&s_abDMASetup, 0x00, sizeof(s_abDMASetup));
        memset(s_tDcb, 0x00, sizeof(DMA_CTRL_BLK_t)*DMA_CH_NUM);
#if defined (DMA_FEATURE_INTERNAL_INTERRUPT)
        PRV_DMA_SetIntrEnable(true);
#endif
    }

    switch(ePeri)
    {
        case DMA_PERI_IDLE:
            break;
#if defined(DMA_UART_NUM)
        case DMA_PERI_UART:
            s_tDrb.un16Uart |= (1UL) << un8ChNum;
            s_tDrb.un16Dma |= (1UL) << DMA_PERI_UART;
            break;
#endif
#if defined(DMA_USART_NUM)
        case DMA_PERI_USART:
            s_tDrb.un16Usart |= (1UL) << un8ChNum;
            s_tDrb.un16Dma |= (1UL) << DMA_PERI_USART;
            break;
#endif
#if defined(DMA_SPI_NUM)
	case DMA_PERI_SPI:
            s_tDrb.un16Spi |= (1UL) << un8ChNum;
            s_tDrb.un16Dma |= (1UL) << DMA_PERI_SPI;
            break;
#endif
#if defined(DMA_CRC_NUM)
        case DMA_PERI_CRC:
            s_tDrb.un16Crc |= (1UL) << un8ChNum;
            s_tDrb.un16Dma |= (1UL) << DMA_PERI_CRC;
            break;
#endif
#if defined(DMA_ADC_NUM)
        case DMA_PERI_ADC:
            s_tDrb.un16Adc |= (1UL) << un8ChNum;
            s_tDrb.un16Dma |= (1UL) << DMA_PERI_ADC;
            break;
#endif
#if defined(DMA_DAC_NUM)
        case DMA_PERI_DAC:
            s_tDrb.un16Dac |= (1UL) << un8ChNum;
            s_tDrb.un16Dma |= (1UL) << DMA_PERI_DAC;
            break;
#endif
#if defined(DMA_AES_NUM)
        case DMA_PERI_AES:
            s_tDrb.un16Aes |= (1UL) << un8ChNum;
            s_tDrb.un16Dma |= (1UL) << DMA_PERI_AES;
            break;
#endif
#if defined(DMA_I2C_NUM)
        case DMA_PERI_I2C:
            s_tDrb.un16I2c |= (1UL) << un8ChNum;
            s_tDrb.un16Dma |= (1UL) << DMA_PERI_I2C;
            break;
#endif
#if defined(DMA_LPUART_NUM)
        case DMA_PERI_LPUART:
            s_tDrb.un16Lpuart |= (1UL) << un8ChNum;
            s_tDrb.un16Dma |= (1UL) << DMA_PERI_LPUART;
            break;
#endif
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    if (s_bDmaInit == false)
    {
        eErr = DMA_SetScuEnable(true);
        s_bDmaInit = true;
    }

    return eErr;
}

HAL_ERR_e HPL_DMA_Uninit(DMA_PERI_e ePeri, uint8_t un8ChNum)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    switch(ePeri)
    {
        case DMA_PERI_IDLE:
            break;
#if defined(DMA_UART_NUM)
        case DMA_PERI_UART:
            s_tDrb.un16Uart &=  ~((1UL) << un8ChNum);
            if(s_tDrb.un16Uart == 0)
            {
                s_tDrb.un16Dma &= ~((1UL) << DMA_PERI_UART);
            }
            break;
#endif
#if defined(DMA_USART_NUM)
        case DMA_PERI_USART:
            s_tDrb.un16Usart &= ~((1UL) << un8ChNum);
            if(s_tDrb.un16Usart == 0)
            {
                s_tDrb.un16Dma &= ~((1UL) << DMA_PERI_USART);
            }
            break;
#endif
#if defined(DMA_SPI_NUM)
	case DMA_PERI_SPI:
            s_tDrb.un16Spi &= ~((1UL) << un8ChNum);
            if(s_tDrb.un16Spi == 0)
            {
                s_tDrb.un16Dma &= ~((1UL) << DMA_PERI_SPI);
            }
            break;
#endif
#if defined(DMA_CRC_NUM)
        case DMA_PERI_CRC:
            s_tDrb.un16Crc &= ~((1UL) << un8ChNum);
            if(s_tDrb.un16Crc == 0)
            {
                s_tDrb.un16Dma &= ~((1UL) << DMA_PERI_CRC);
            }
            break;
#endif
#if defined(DMA_ADC_NUM)
        case DMA_PERI_ADC:
            s_tDrb.un16Adc &= ~((1UL) << un8ChNum);
            if(s_tDrb.un16Adc == 0)
            {
                s_tDrb.un16Dma &= ~((1UL) << DMA_PERI_ADC);
            }
            break;
#endif
#if defined(DMA_DAC_NUM)
        case DMA_PERI_DAC:
            s_tDrb.un16Dac &= ~((1UL) << un8ChNum);
            if(s_tDrb.un16Dac == 0)
            {
                s_tDrb.un16Dma &= ~((1UL) << DMA_PERI_DAC);
            }
            break;
#endif
#if defined(DMA_AES_NUM)
        case DMA_PERI_AES:
            s_tDrb.un16Aes &= ~((1UL) << un8ChNum);
            if(s_tDrb.un16Aes == 0)
            {
                s_tDrb.un16Dma &= ~((1UL) << DMA_PERI_AES);
            }
            break;
#endif
#if defined(DMA_I2C_NUM)
        case DMA_PERI_I2C:
            s_tDrb.un16I2c &= ~((1UL) << un8ChNum);
            if(s_tDrb.un16I2c == 0)
            {
                s_tDrb.un16Dma &= ~((1UL) << DMA_PERI_I2C);
            }
            break;
#endif
#if defined(DMA_LPUART_NUM)
        case DMA_PERI_LPUART:
            s_tDrb.un16Lpuart &= ~((1UL) << un8ChNum);
            if(s_tDrb.un16Lpuart == 0)
            {
                s_tDrb.un16Dma &= ~((1UL) << DMA_PERI_LPUART);
            }
            break;
#endif
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    if (s_tDrb.un16Dma == 0)
    {

#if defined (DMA_FEATURE_INTERNAL_INTERRUPT)
        PRV_DMA_SetIntrEnable(false);
#endif
        memset(&s_abDMASetup, 0x00, sizeof(s_abDMASetup));
        memset(&s_tDrb, 0x00, sizeof(DMA_RES_BLK_t));
        s_bDmaInit = false;
        eErr = DMA_SetScuEnable(false);
    }

    return eErr;
}

HAL_ERR_e HPL_DMA_SetIRQ(DMA_PERI_e ePeri, pfnDMA_IRQ_Handler_t pfnHandler, void *pContext, bool bEnable)
{

#if defined (DMA_FEATURE_INTERNAL_INTERRUPT)
    HAL_ERR_e eErr = HAL_ERR_OK;
    DMA_INTR_BLK_t *ptDib = NULL;

    switch(ePeri)
    {
        case DMA_PERI_IDLE:
            break;
#if defined(DMA_UART_NUM)
        case DMA_PERI_UART:
            ptDib = &s_tDrb.tUartDib;
            break;
#endif
#if defined(DMA_USART_NUM)
        case DMA_PERI_USART:
            ptDib = &s_tDrb.tUsartDib;
            break;
#endif
#if defined(DMA_SPI_NUM)
	case DMA_PERI_SPI:
            ptDib = &s_tDrb.tSpiDib;
            break;
#endif
#if defined(DMA_CRC_NUM)
        case DMA_PERI_CRC:
            ptDib = &s_tDrb.tCrcDib;
            break;
#endif
#if defined(DMA_ADC_NUM)
        case DMA_PERI_ADC:
            ptDib = &s_tDrb.tAdcDib;
            break;
#endif
#if defined(DMA_DAC_NUM)
        case DMA_PERI_DAC:
            ptDib = &s_tDrb.tDacDib;
            break;
#endif
#if defined(DMA_AES_NUM)
        case DMA_PERI_AES:
            ptDib = &s_tDrb.tAesDib;
            break;
#endif
#if defined(DMA_I2C_NUM)
        case DMA_PERI_I2C:
            ptDib = &s_tDrb.tI2cDib;
            break;
#endif
#if defined(DMA_LPUART_NUM)
        case DMA_PERI_LPUART:
            ptDib = &s_tDrb.tLpUartDib;
            break;
#endif
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    if (eErr == HAL_ERR_OK)
    {
        memset(ptDib, 0x00, sizeof(DMA_INTR_BLK_t));
        if (bEnable)
        {
            ptDib->bEnable = true;
            ptDib->pfnHandler = pfnHandler;
            ptDib->pContext = pContext;
        }
    }

    return eErr;
#else
    (void)ePeri;
    (void)pfnHandler;
    (void)pContext;
    return HAL_ERR_NOT_SUPPORTED;
#endif

}

HAL_ERR_e HPL_DMA_GetAvailChannel(DMA_ID_e *peId)
{
    int32_t u32Idx = 0;
    for(u32Idx = 0; u32Idx < DMA_CH_NUM; u32Idx++)
    {
        if (s_abDMASetup[u32Idx] == false)
        {
            *peId = (DMA_ID_e)u32Idx;
            return HAL_ERR_OK;
        }
    }

    return HAL_ERR_NO_RESOURCE;
}

HAL_ERR_e HPL_DMA_GetPeriSelectNumber(DMA_PERI_e ePeri, DMA_PERI_ID_e ePeriId, DMA_PERI_COM_e eCom, uint32_t *pun32SelNum)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    switch(ePeri)
    {
        case DMA_PERI_IDLE:
            *pun32SelNum = 0;
            break;
#if defined(DMA_UART_NUM)
        case DMA_PERI_UART:
            *pun32SelNum = DMA_UART_NUM(ePeriId, eCom);
            break;
#endif
#if defined(DMA_USART_NUM)
        case DMA_PERI_USART:
            *pun32SelNum = DMA_USART_NUM(ePeriId, eCom);
            break;
#endif
#if defined(DMA_SPI_NUM)
        case DMA_PERI_SPI:
            *pun32SelNum = DMA_SPI_NUM(ePeriId, eCom);
            break;
#endif
#if defined(DMA_CRC_NUM)
        case DMA_PERI_CRC:
            *pun32SelNum = DMA_CRC_NUM(ePeriId);
            break;
#endif
#if defined(DMA_ADC_NUM)
        case DMA_PERI_ADC:
            *pun32SelNum = DMA_ADC_NUM(ePeriId);
            break;
#endif
#if defined(DMA_DAC_NUM)
        case DMA_PERI_DAC:
            *pun32SelNum = DMA_DAC_NUM(ePeriId);
            break;
#endif
#if defined(DMA_AES_NUM)
        case DMA_PERI_AES:
            *pun32SelNum = DMA_AES_NUM(ePeriId, eCom);
            break;
#endif
#if defined(DMA_I2C_NUM)
        case DMA_PERI_I2C:
            *pun32SelNum = DMA_I2C_NUM(ePeriId, eCom);
            break;
#endif
#if defined(DMA_LPUART_NUM)
        case DMA_PERI_LPUART:
            *pun32SelNum = DMA_LPUART_NUM(ePeriId, eCom);
            break;
#endif
        default:
            eErr = HAL_ERR_NOT_SUPPORTED;
            break;
    }

    return eErr;
}

HAL_ERR_e HPL_DMA_SetConfig(DMA_ID_e eId, DMA_CFG_t *ptCfg)
{
    DMA_Type *ptDMA;
    DMA_CTRL_BLK_t *ptDcb; 

    if((uint32_t)eId >= DMA_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if (s_abDMASetup[eId] != false)
    {
        return HAL_ERR_BUSY;
    }

    ptDMA = PRV_DMA_GetReg(eId);
    ptDcb = &s_tDcb[(uint32_t)eId];

    SET_DMA_CR_PERISEL(ptDMA, ptCfg->un32PeriNum);
    SET_DMA_CR_SIZE(ptDMA, ptCfg->eSize);
    SET_DMA_CR_DIR(ptDMA, ptCfg->eDir);

    s_abDMASetup[eId] = true;
    ptDcb->bEnable = true;
    ptDcb->ePeri = ptCfg->ePeri;
    ptDcb->ePeriId = ptCfg->ePeriId;

    return HAL_ERR_OK;
}

HAL_ERR_e HPL_DMA_SetClear(DMA_ID_e eId)
{
    DMA_Type *ptDMA;

    if((uint32_t)eId >= DMA_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptDMA = PRV_DMA_GetReg(eId);

    SET_DMA_CR_CLEAR(ptDMA, true);

    return HAL_ERR_OK;
}

HAL_ERR_e HPL_DMA_Start(DMA_ID_e eId, uint32_t un32Src, uint32_t un32Dst, uint32_t un32Len)
{
    DMA_Type *ptDMA;
    DMA_DIR_e eDir;

    if((uint32_t)eId >= DMA_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if (s_abDMASetup[eId] == false)
    {
        return HAL_ERR_PARAMETER;
    }

    ptDMA = PRV_DMA_GetReg(eId);

    SET_DMA_CR_LEN(ptDMA, un32Len);

    eDir = (DMA_DIR_e)GET_DMA_CR_DIR(ptDMA);

    if(eDir == DMA_DIR_MEM_TO_PERI)
    {
        SET_DMA_ADDR_PAR(ptDMA, un32Dst);
        SET_DMA_ADDR_MAR(ptDMA, un32Src);
    }
    else
    {
        SET_DMA_ADDR_PAR(ptDMA, un32Src);
        SET_DMA_ADDR_MAR(ptDMA, un32Dst);
    }

#if defined (DMA_FEATURE_INTERNAL_INTERRUPT)
    SET_DMA_IER_ERR_EN(ptDMA, true); 
    SET_DMA_IER_EN(ptDMA, true);
#endif

    SET_DMA_CR_EN(ptDMA, true);

    return HAL_ERR_OK;
}

HAL_ERR_e HPL_DMA_Stop(DMA_ID_e eId)
{
    DMA_Type *ptDMA;
    DMA_CTRL_BLK_t *ptDcb; 

    if((uint32_t)eId >= DMA_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptDMA = PRV_DMA_GetReg(eId);
    ptDcb = &s_tDcb[(uint32_t)eId];

    s_abDMASetup[eId] = false;
    ptDcb->bEnable = false;
    ptDcb->ePeri = DMA_PERI_MAX;
    ptDcb->ePeriId = DMA_PERI_ID_MAX;

    SET_DMA_CR_EN(ptDMA, false);

    return HAL_ERR_OK;
}

HAL_ERR_e HPL_DMA_SetWaitComplete(DMA_ID_e eId, uint32_t un32Timeout)
{
    DMA_Type *ptDMA;
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= DMA_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptDMA = PRV_DMA_GetReg(eId);

    while(GET_DMA_SR_EOT(ptDMA) == 0)
    {
        un32Timeout--;
        if(un32Timeout == 0)
        {
            eErr = HAL_ERR_TIMEOUT;
            break;
        }
    }

    return eErr;
}

#if defined (DMA_FEATURE_INTERNAL_INTERRUPT)
HAL_ERR_e HPL_DMA_GetComplete(DMA_ID_e eId, bool *pbComplete)
{
    DMA_Type *ptDMA;

    if((uint32_t)eId >= DMA_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptDMA = PRV_DMA_GetReg(eId);

    if (GET_DMA_IER_FLAG(ptDMA))
    {
        *pbComplete = true; 
        SET_DMA_IER_FLAG(ptDMA, true);
    }
    else
    {
        *pbComplete = false;
    }
    
    return HAL_ERR_OK; 
}

static void PRV_DMA_IRQHandler(P_DMA_IRQ_ID_e eIrqId)
{
    DMA_Type *ptDMA;
    DMA_ID_e eId;
    DMA_CTRL_BLK_t *ptDcb; 
    DMA_INTR_BLK_t *ptDib;
    uint8_t un8IrqStartIdx = 0, un8IrqEndIdx = 0;

    switch(eIrqId)
    {
#if defined (DMA_0_IRQ)
        case P_DMA_IRQ_ID_0:
            un8IrqStartIdx = DMA_IRQ_0_START_IDX;
            un8IrqEndIdx = DMA_IRQ_0_END_IDX;
            break;
#endif
#if defined (DMA_1_IRQ)
        case P_DMA_IRQ_ID_1:
            un8IrqStartIdx = DMA_IRQ_1_START_IDX;
            un8IrqEndIdx = DMA_IRQ_1_END_IDX;
            break;
#endif
#if defined (DMA_2_IRQ)
        case P_DMA_IRQ_ID_2:
            un8IrqStartIdx = DMA_IRQ_2_START_IDX;
            un8IrqEndIdx = DMA_IRQ_2_END_IDX;
            break;
#endif
#if defined (DMA_3_IRQ)
        case P_DMA_IRQ_ID_3:
            un8IrqStartIdx = DMA_IRQ_3_START_IDX;
            un8IrqEndIdx = DMA_IRQ_3_END_IDX;
            break;
#endif
#if defined (DMA_4_IRQ)
        case P_DMA_IRQ_ID_4:
            un8IrqStartIdx = DMA_IRQ_4_START_IDX;
            un8IrqEndIdx = DMA_IRQ_4_END_IDX;
            break;
#endif
#if defined (DMA_5_IRQ)
        case P_DMA_IRQ_ID_5:
            un8IrqStartIdx = DMA_IRQ_5_START_IDX;
            un8IrqEndIdx = DMA_IRQ_5_END_IDX;
            break;
#endif
#if defined (DMA_6_IRQ)
        case P_DMA_IRQ_ID_6:
            un8IrqStartIdx = DMA_IRQ_6_START_IDX;
            un8IrqEndIdx = DMA_IRQ_6_END_IDX;
            break;
#endif
#if defined (DMA_7_IRQ)
        case P_DMA_IRQ_ID_7:
            un8IrqStartIdx = DMA_IRQ_7_START_IDX;
            un8IrqEndIdx = DMA_IRQ_7_END_IDX;
            break;
#endif
#if defined (DMA_8_IRQ)
        case P_DMA_IRQ_ID_8:
            un8IrqStartIdx = DMA_IRQ_8_START_IDX;
            un8IrqEndIdx = DMA_IRQ_8_END_IDX;
            break;
#endif
#if defined (DMA_9_IRQ)
        case P_DMA_IRQ_ID_9:
            un8IrqStartIdx = DMA_IRQ_9_START_IDX;
            un8IrqEndIdx = DMA_IRQ_9_END_IDX;
            break;
#endif
        default:
            break;
    }

    for (uint8_t i = un8IrqStartIdx; i < un8IrqEndIdx + 1; i++)
    {
        ptDMA = PRV_DMA_GetReg((DMA_ID_e)i);
        if (GET_DMA_IER_FLAG(ptDMA))
        {
            SET_DMA_IER_FLAG(ptDMA, true);
            eId = (DMA_ID_e)i;
            break; 
        }
    }
    
    ptDcb = &s_tDcb[(uint32_t)eId];
    ptDib = PRV_DMA_GetIntrBlk(ptDcb->ePeri);

    if (ptDib != NULL && ptDib->bEnable == true && ptDib->pfnHandler != NULL)
    {
        ptDib->pfnHandler((uint32_t)ptDcb->ePeriId, NULL);
    }
}

void DMA0_IRQHandler(void)
{
    PRV_DMA_IRQHandler(P_DMA_IRQ_ID_0);
}

void DMA1_IRQHandler(void)
{
    PRV_DMA_IRQHandler(P_DMA_IRQ_ID_1);
}

void DMA2_IRQHandler(void)
{
    PRV_DMA_IRQHandler(P_DMA_IRQ_ID_2);
}

void DMA3_IRQHandler(void)
{
    PRV_DMA_IRQHandler(P_DMA_IRQ_ID_3);
}

void DMA4_IRQHandler(void)
{
    PRV_DMA_IRQHandler(P_DMA_IRQ_ID_4);
}

void DMA5_IRQHandler(void)
{
    PRV_DMA_IRQHandler(P_DMA_IRQ_ID_5);
}

void DMA6_IRQHandler(void)
{
    PRV_DMA_IRQHandler(P_DMA_IRQ_ID_6);
}

void DMA7_IRQHandler(void)
{
    PRV_DMA_IRQHandler(P_DMA_IRQ_ID_7);
}

void DMA8_IRQHandler(void)
{
    PRV_DMA_IRQHandler(P_DMA_IRQ_ID_8);
}

void DMA9_IRQHandler(void)
{
    PRV_DMA_IRQHandler(P_DMA_IRQ_ID_9);
}

#endif

#endif /* _DMAC */
