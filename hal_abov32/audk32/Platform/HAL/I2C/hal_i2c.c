/**
 *******************************************************************************
 * @file        hal_i2c.c
 * @author      ABOV R&D Division
 * @brief       I2C communication
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

#if defined(_I2C)
#include "hal_i2c.h"
#include "hal_i2c_prv.h"

#if defined(_DMAC) && defined(DMA_I2C_NUM)
#include "hpl_dma.h"
#endif

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
#include "hpl_nmi.h"
#endif

typedef struct
{
    I2C_OPS_e               eOps;
    pfnI2C_IRQ_Handler_t    pfnHandler;
    void                    *pContext;

#if defined(_DMAC) && defined(DMA_I2C_NUM)
    DMA_ID_e                eDmaId;
    bool                    bDmaEnabled;
#endif

    I2C_MODE_e              eMode;
    bool                    bTxBusy;
    bool                    bRxBusy;
    uint8_t                 *pun8TxBuf;
    uint8_t                 *pun8RxBuf;
    uint32_t                un32TxLen;
    uint32_t                un32RxLen;
    uint32_t                un32TxCnt;
    uint32_t                un32RxCnt;
 
    bool                    bGCDetected;

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
    bool                    bNmiEnable;
#endif

} I2C_CTRL_BLK_t;

static I2C_CTRL_BLK_t s_tIcb[I2C_CH_NUM];

static void PRV_I2C_IRQHandler(I2C_ID_e eId);

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
static void PRV_I2C_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < I2C_CH_NUM; i++)
    {
        if(s_tIcb[i].bNmiEnable == true)
        {
            PRV_I2C_IRQHandler((I2C_ID_e)i);
        }
    }
}
#endif

#if defined(_DMAC) && defined(DMA_I2C_NUM) && defined (I2C_FEATURE_DMA_INTERNAL_INTERRUPT)
static void PRV_I2C_DMAHandler(uint32_t un32Event, void *pContext)
{
    PRV_I2C_IRQHandler((I2C_ID_e)(un32Event));
}
#endif

static I2C_Type *PRV_I2C_GetReg(I2C_ID_e eId)
{
    return I2C_GetReg((P_I2C_ID_e)eId);
}

static HAL_ERR_e PRV_I2C_SetScuEnable(P_I2C_ID_e eId, bool bEnable)
{
    return I2C_SetScuEnable((P_I2C_ID_e)eId, bEnable);
}

#if defined(_DMAC) && defined(DMA_I2C_NUM)
static HAL_ERR_e PRV_I2C_SetDMA(I2C_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    I2C_CTRL_BLK_t *ptIcb;
    DMA_ID_e eDmaId;

    ptIcb = &s_tIcb[(uint32_t)eId];

    eErr = HPL_DMA_Init(DMA_PERI_I2C, (uint8_t)eId);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    eErr = HPL_DMA_GetAvailChannel(&eDmaId);
    if(eErr == HAL_ERR_OK)
    {
        ptIcb->eDmaId = eDmaId;
        ptIcb->bDmaEnabled = true;
    }

#if defined (I2C_FEATURE_DMA_INTERNAL_INTERRUPT)
    eErr = HPL_DMA_SetIRQ(DMA_PERI_I2C, &PRV_I2C_DMAHandler, NULL, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }
#endif

    return eErr;
}
#endif

static uint32_t PRV_I2C_GetOpStatus(I2C_Type *ptI2c)
{
    uint32_t un32Status = 0;

    while(!GET_I2C_IER_FLAG(ptI2c))
    {
        /* Waiting for Interrupt Event */
    }
    un32Status = GET_I2C_SR(ptI2c);

    return un32Status;
}

static void PRV_I2C_SetOpStop(I2C_Type *ptI2c)
{
    SET_I2C_CR_STOP(ptI2c, true);

    while(!GET_I2C_IER_FLAG(ptI2c))
    {
        /* Waiting for Interrupt Event */
    }

    SET_I2C_CR_STOP(ptI2c, false);
}

HAL_ERR_e HAL_I2C_Init(I2C_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= I2C_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_I2C_SetScuEnable((P_I2C_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tIcb[(uint32_t)eId], 0x00, sizeof(I2C_CTRL_BLK_t));

    SET_I2C_CR_EN(PRV_I2C_GetReg(eId), true);

    return eErr;
}

HAL_ERR_e HAL_I2C_Uninit(I2C_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= I2C_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_I2C_CR_EN(PRV_I2C_GetReg(eId), false);

    eErr = PRV_I2C_SetScuEnable((P_I2C_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = I2C_GetIRQNum((P_I2C_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tIcb[(uint32_t)eId], 0x00, sizeof(I2C_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_I2C_SetConfig(I2C_ID_e eId, I2C_CFG_t *ptCfg)
{
    I2C_Type *ptI2c;
    I2C_CTRL_BLK_t *ptIcb;
    uint16_t un16Scll, un16Sclh;

    if((uint32_t)eId >= I2C_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptI2c = PRV_I2C_GetReg(eId);
    ptIcb = &s_tIcb[(uint32_t)eId];

    ptIcb->eMode = ptCfg->eMode;

    SET_I2C_CR_SLAVEADDR(ptI2c, ptCfg->un8OwnSlvAddr);
    SET_I2C_CR_SLAVEADDR2(ptI2c, ptCfg->un8OwnSlvAddr2);

    SET_I2C_CR_GNRLADDR(ptI2c, ptCfg->bSaGcEnable);
    SET_I2C_CR_GNRLADDR2(ptI2c, ptCfg->bSa2GcEnable);

    if(ptCfg->uPeriod.tFreq.un32Freq != 0)
    {
        un16Scll = ((SystemPeriClock / ptCfg->uPeriod.tFreq.un32Freq) / 2) - 2;
        un16Sclh = un16Scll - 1;
    }
    else
    {
        un16Scll = ptCfg->uPeriod.tDuty.un16Low;
        un16Sclh = ptCfg->uPeriod.tDuty.un16High;
    }

    SET_I2C_CR_SCLL(ptI2c, un16Scll);
    SET_I2C_CR_SCLH(ptI2c, un16Sclh);

    SET_I2C_CR_SDA_HOLD_EN(ptI2c, ptCfg->tSdht.bEnable);

    if(ptCfg->tSdht.bEnable == true)
    {
        SET_I2C_CR_SDA_HOLD(ptI2c, ptCfg->tSdht.un16Hold);
    }
    else
    {
        SET_I2C_CR_SDA_HOLD(ptI2c, 0);
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_I2C_SetIRQ(I2C_ID_e eId, I2C_OPS_e eOps, pfnI2C_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    I2C_CTRL_BLK_t *ptIcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= I2C_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptIcb = &s_tIcb[(uint32_t)eId];

    eIrq = I2C_GetIRQNum((P_I2C_ID_e)eId);

    switch(eOps)
    {
        case I2C_OPS_INTR:
#if defined(_DMAC) && defined(DMA_I2C_NUM)
        case I2C_OPS_INTR_DMA:
#endif
#if defined(I2C_FEATURE_IRQ_UNMASK_ENABLE)
            I2C_SetIntrUnMask(eIrq, true);
#endif
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            if(ptIcb->bNmiEnable == true)
            {
                (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
                ptIcb->bNmiEnable = false;
            }
#endif
            ptIcb->pfnHandler = pfnHandler;
            ptIcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
#if defined(_DMAC) && defined(DMA_I2C_NUM)
            if(eOps == I2C_OPS_INTR_DMA)
            {
                eErr = PRV_I2C_SetDMA(eId);
            }
#endif
            break;
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
        case I2C_OPS_NMI:
        case I2C_OPS_NMI_DMA:
            eErr = HPL_NMI_SetSource(eIrq, &PRV_I2C_NMIHandler, pContext, true);
            if(eErr == HAL_ERR_OK)
            {
                ptIcb->pfnHandler = pfnHandler;
                ptIcb->pContext = pContext;
            }
            ptIcb->bNmiEnable = true;
#if defined(_DMAC) && defined(DMA_I2C_NUM)
            if(eOps == I2C_OPS_NMI_DMA)
            {
                eErr = PRV_I2C_SetDMA(eId);
            }
#endif
            break;
#endif
        case I2C_OPS_POLL:
        default:
#if defined(I2C_FEATURE_IRQ_UNMASK_ENABLE)
            I2C_SetIntrUnMask(eIrq, false);
#endif
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
            ptIcb->bNmiEnable = false;
#endif
#if defined(_DMAC) && defined(DMA_I2C_NUM)
            if(ptIcb->bDmaEnabled == true)
            {
                HPL_DMA_Uninit(DMA_PERI_I2C, (uint8_t)eId);
                ptIcb->bDmaEnabled = false;
            }
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptIcb->pContext = NULL;
            ptIcb->pfnHandler = NULL;
            break;
    }

    ptIcb->eOps = eOps;

    return eErr;
}


HAL_ERR_e HAL_I2C_Transmit(I2C_ID_e eId, uint8_t un8SlaveAddr, uint8_t *pun8Out, uint32_t un32Len,
                           bool bEnForcePoll)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    I2C_CTRL_BLK_t *ptIcb;
    I2C_Type *ptI2c;
    uint32_t un32Status;
    bool bIntrEnable = true, bSend = false, bCompleted = false;
#if defined(_DMAC) && defined(DMA_I2C_NUM)
    DMA_CFG_t tDmaCfg =
    {
        .ePeri = DMA_PERI_I2C,
        .ePeriId = (DMA_PERI_ID_e)eId,
        .un32PeriNum = 0,
        .eSize = DMA_BUS_SIZE_BYTE,
        .eDir = DMA_DIR_MEM_TO_PERI
    };
#endif

    if((uint32_t)eId >= I2C_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptI2c = PRV_I2C_GetReg(eId);
    ptIcb = &s_tIcb[eId];

    if (ptIcb->bTxBusy == true)
    {
        return HAL_ERR_BUSY;
    }

    ptIcb->bTxBusy = true;
    ptIcb->pun8TxBuf = (uint8_t *)pun8Out;
    ptIcb->un32TxLen = un32Len;
    ptIcb->un32TxCnt = 0;

    if(ptIcb->eOps == I2C_OPS_POLL || bEnForcePoll == true)
    {
        bIntrEnable = false;
    }

    SET_I2C_IER_EN(ptI2c, bIntrEnable);
    SET_I2C_CR_ACK(ptI2c, true);
    SET_I2C_SR_CLEAR(ptI2c);

    if(ptIcb->eMode == I2C_MODE_MASTER)
    {
        SET_I2C_DR_TX(ptI2c, (un8SlaveAddr << 1));
        SET_I2C_CR_START(ptI2c, true);
    }

    if(bIntrEnable == false)
    {
        while(!bCompleted)
        {
            un32Status = PRV_I2C_GetOpStatus(ptI2c);
            switch(un32Status)
            {
                case I2C_MASTER_TX_ADDR_ACK:
                case I2C_SLAVE_TX_SEL_ACK:
                case I2C_SLAVE_TX_GC_ACK:
                    bSend = true;
                    break;
                case I2C_SLAVE_TX_DATA_NOACK:
                    bSend = false;
                    bCompleted = true;
                    break;
                case I2C_SLAVE_TX_DONE:
                    if(ptIcb->un32TxCnt >= ptIcb->un32TxLen)
                    {
                        bSend = false;
                        bCompleted = true;
                    }
                    break;
                case I2C_TX_DATA_ACK:
                    bSend = true;
                    bCompleted = false;
                    if(ptIcb->un32TxCnt >= ptIcb->un32TxLen)
                    {
                        bSend = false;
                        if(ptIcb->eMode == I2C_MODE_MASTER)
                        {
                            PRV_I2C_SetOpStop(ptI2c);
                        }
                        SET_I2C_SR_CLEAR(ptI2c);
                    }
                    break;
                default:
                    bSend = false;
                    eErr = HAL_ERR_HW;
                    break;
            }

            if(eErr != HAL_ERR_OK)
            {
                break;
            }

            if(bSend == true)
            {
                if(ptIcb->un32TxCnt == ptIcb->un32TxLen - 1)
                {
                    SET_I2C_CR_ACK(ptI2c, false);
                }
                SET_I2C_DR_TX(ptI2c,ptIcb->pun8TxBuf[ptIcb->un32TxCnt++]);
                SET_I2C_SR_CLEAR(ptI2c);
            }
        }

        ptIcb->bTxBusy = false;
    }
    else
    {
#if defined(_DMAC) && defined(DMA_I2C_NUM)
        if(ptIcb->eOps == I2C_OPS_INTR_DMA
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
           || ptIcb->eOps == I2C_OPS_NMI_DMA
#endif
          )
        {
            eErr = (HAL_ERR_e)HPL_DMA_GetPeriSelectNumber(DMA_PERI_I2C, (DMA_PERI_ID_e)eId, DMA_PERI_COM_TX, &tDmaCfg.un32PeriNum);
            if(eErr == HAL_ERR_OK)
            {
                HPL_DMA_SetConfig(ptIcb->eDmaId, &tDmaCfg);
                SET_I2C_IER_EN(ptI2c, true);
            }
        }
#endif
    }

    return eErr;
}

HAL_ERR_e HAL_I2C_Receive(I2C_ID_e eId, uint8_t un8SlaveAddr, uint8_t *pun8In, uint32_t un32Len,
                          bool bEnForcePoll)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    I2C_CTRL_BLK_t *ptIcb;
    I2C_Type *ptI2c;
    uint32_t un32Status;
    bool bIntrEnable = true, bReceive = false, bCompleted = false;
#if defined(_DMAC) && defined(DMA_I2C_NUM)
    DMA_CFG_t tDmaCfg =
    {
        .ePeri = DMA_PERI_I2C,
        .ePeriId = (DMA_PERI_ID_e)eId,
        .un32PeriNum = 0,
        .eSize = DMA_BUS_SIZE_BYTE,
        .eDir = DMA_DIR_PERI_TO_MEM
    };
#endif

    if((uint32_t)eId >= I2C_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptI2c = PRV_I2C_GetReg(eId);
    ptIcb = &s_tIcb[eId];

    if (ptIcb->bRxBusy == true)
    {
        return HAL_ERR_BUSY;
    }

    ptIcb->bRxBusy = true;
    ptIcb->pun8RxBuf = (uint8_t *)pun8In;
    ptIcb->un32RxLen = un32Len;
    ptIcb->un32RxCnt = 0;

    if(ptIcb->eOps == I2C_OPS_POLL || bEnForcePoll == true)
    {
        bIntrEnable = false;
    }

    SET_I2C_IER_EN(ptI2c, bIntrEnable);
    SET_I2C_CR_ACK(ptI2c, true);
    SET_I2C_SR_CLEAR(ptI2c);

    if(ptIcb->eMode == I2C_MODE_MASTER)
    {
        SET_I2C_DR_TX(ptI2c, (un8SlaveAddr << 1) | 0x01);
        SET_I2C_CR_START(ptI2c, true);
    }

    if(bIntrEnable == false)
    {
        ptIcb->bGCDetected = false;

        while(!bCompleted)
        {
            un32Status = PRV_I2C_GetOpStatus(ptI2c);
            switch(un32Status)
            {
                case I2C_MASTER_RX_ADDR_ACK:
                    if(ptIcb->eMode == I2C_MODE_MASTER)
                    {
                        bReceive = false;
                        ptIcb->bGCDetected = true;
                    }
                    break;
                case I2C_SLAVE_RX_SEL_ACK:
                    if(ptIcb->eMode == I2C_MODE_SLAVE)
                    {
                        bReceive = false;
                        ptIcb->bGCDetected = true;
                    }
                    break;
                case I2C_SLAVE_RX_GC_ACK:
                    if(ptIcb->eMode == I2C_MODE_SLAVE)
                    {
                        bReceive = false;
                        ptIcb->bGCDetected = true;
                    }
                    break;
                case I2C_SLAVE_RX_DONE:
                    if(ptIcb->un32RxCnt >= ptIcb->un32RxLen 
                       && ptIcb->bGCDetected == true)
                    {
                        bReceive = false;
                        bCompleted = true;
                        ptIcb->un32RxCnt = 0;
                        ptIcb->bGCDetected = false;
                    }
                    break;
                case I2C_MASTER_RX_DATA_NOACK:
                    bReceive = false;
                    bCompleted = true;
                    break;
                case I2C_RX_DATA_ACK:
                    bReceive = true;
                    bCompleted = false;
                    if(ptIcb->un32RxCnt >= ptIcb->un32RxLen && ptIcb->bGCDetected == true)
                    {
                        bReceive = false;
                        bCompleted = false;
                        if(ptIcb->eMode == I2C_MODE_MASTER)
                        {
                            PRV_I2C_SetOpStop(ptI2c);
                        }
                        SET_I2C_SR_CLEAR(ptI2c);
                    }
                    break;
                default:
                    bReceive = false;
                    eErr = HAL_ERR_HW;
                    break;
            }

            if(eErr != HAL_ERR_OK)
            {
                break;
            }

            if(bReceive == true && ptIcb->bGCDetected == true)
            {
                if(ptIcb->un32RxCnt == ptIcb->un32RxLen - 1)
                {
                    SET_I2C_CR_ACK(ptI2c, false);
                }

                ptIcb->pun8RxBuf[ptIcb->un32RxCnt++] = GET_I2C_DR_RX(ptI2c);
            }
            
            if(ptIcb->un32RxCnt < ptIcb->un32RxLen)
            {
                SET_I2C_SR_CLEAR(ptI2c);
            }
        }

        ptIcb->bRxBusy = false;

    }
    else
    {
#if defined(_DMAC) && defined(DMA_I2C_NUM)
        if(ptIcb->eOps == I2C_OPS_INTR_DMA
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
           || ptrILcb->eOps == I2C_OPS_NMI_DMA
#endif
          )
        {
            eErr = (HAL_ERR_e)HPL_DMA_GetPeriSelectNumber(DMA_PERI_I2C, (DMA_PERI_ID_e)eId, DMA_PERI_COM_RX, &tDmaCfg.un32PeriNum);
            if(eErr == HAL_ERR_OK)
            {
                HPL_DMA_SetConfig(ptIcb->eDmaId, &tDmaCfg);
            }
        }
#endif
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_I2C_SetWakeupSrc(I2C_ID_e eId, bool bEnable)
{
    if((uint32_t)eId >= I2C_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    I2C_SetWkupSrc((P_I2C_ID_e)eId, bEnable); 
    return HAL_ERR_OK;
}

HAL_ERR_e HAL_I2C_SetSltpConfig(I2C_ID_e eId, I2C_SLTP_CFG_t *ptCfg)
{
#if defined(I2C_FEATURE_LOW_TIMEOUT_PERIOD)
    I2C_Type *ptI2c;

    if((uint32_t)eId >= I2C_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptI2c = PRV_I2C_GetReg(eId);

    SET_I2C_CR_SCL_LOW_TO_EN(ptI2c, ptCfg->bEnable);
    if(ptCfg->bEnable == true)
    {
        SET_I2C_IER_SCL_LOW_TO_EN(ptI2c, ptCfg->bIntrEnable);
        SET_I2C_DR_SCL_LOW_TO(ptI2c, ptCfg->un32Timeout);
    }

    return HAL_ERR_OK;
#else
    (void)eId;
    (void)ptCfg;
    return HAL_ERR_NOT_SUPPORTED;
#endif    
}

HAL_ERR_e HAL_I2C_SetMaulConfig(I2C_ID_e eId, I2C_MAUL_CFG_t *ptCfg)
{
#if defined(I2C_FEATURE_MANUAL_BUS_CONTROL)
    I2C_Type *ptI2c;

    if((uint32_t)eId >= I2C_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptI2c = PRV_I2C_GetReg(eId);

    SET_I2C_CR_SCL_MAUL_EN(ptI2c, ptCfg->bSclMaulEnable);
    SET_I2C_CR_SDA_MAUL_EN(ptI2c, ptCfg->bSdaMaulEnable);

    return HAL_ERR_OK;
#else
    (void)eId;
    (void)ptCfg;
    return HAL_ERR_NOT_SUPPORTED;
#endif    
}

HAL_ERR_e HAL_I2C_SetSclMaul(I2C_ID_e eId, bool bLevel)
{
#if defined(I2C_FEATURE_MANUAL_BUS_CONTROL)
    I2C_Type *ptI2c;
    uint32_t un32Timeout = I2C_MANUAL_TIMEOUT;

    if((uint32_t)eId >= I2C_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptI2c = PRV_I2C_GetReg(eId);

    SET_I2C_CR_SCL_MAUL_OUT(ptI2c, bLevel);

    while(un32Timeout)
    {
        if(GET_I2C_SR_SCL_MAUL_STA(ptI2c) == bLevel)
        {
            break;
        }
        un32Timeout--;
    }

    if(un32Timeout == 0)
    {
        return HAL_ERR_TIMEOUT;
    }

    return HAL_ERR_OK;
#else
    (void)eId;
    (void)bLevel;
    return HAL_ERR_NOT_SUPPORTED;
#endif    
}

HAL_ERR_e HAL_I2C_SetSdaMaul(I2C_ID_e eId, bool bLevel)
{
#if defined(I2C_FEATURE_MANUAL_BUS_CONTROL)
    I2C_Type *ptI2c;
    uint32_t un32Timeout = I2C_MANUAL_TIMEOUT;

    if((uint32_t)eId >= I2C_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptI2c = PRV_I2C_GetReg(eId);

    SET_I2C_CR_SDA_MAUL_OUT(ptI2c, bLevel);

    while(un32Timeout)
    {
        if(GET_I2C_SR_SDA_MAUL_STA(ptI2c) == bLevel)
        {
            break;
        }
        un32Timeout--;
    }

    if(un32Timeout == 0)
    {
        return HAL_ERR_TIMEOUT;
    }

    return HAL_ERR_OK;
#else
    (void)eId;
    (void)bLevel;
    return HAL_ERR_NOT_SUPPORTED;
#endif    
}

static void PRV_I2C_IRQHandler(I2C_ID_e eId)
{
    I2C_CTRL_BLK_t *ptIcb;
    I2C_Type *ptI2c;
    I2C_Context_t *ptContext;
    volatile uint32_t un32Status;
    volatile uint32_t un32Event = 0;
    bool bSend = false, bReceive = false;

    if((uint32_t)eId >= I2C_CH_NUM)
    {
        return;
    }

    ptI2c = PRV_I2C_GetReg(eId);
    ptIcb = &s_tIcb[eId];

    if(ptIcb->pContext != NULL)
    {
        ptContext = (I2C_Context_t *)ptIcb->pContext;
        I2C_GetWkupEvent((P_I2C_ID_e)eId, &ptContext->bWakeup);
    }

    un32Status = GET_I2C_SR(ptI2c);

#if defined(I2C_FEATURE_MANUAL_BUS_CONTROL)
    if(un32Status & I2C_STATUS_SLT_TO)
    {
        un32Event = I2C_EVENT_SCL_LOW_TIMEOUT;
    }
#endif

#if defined (_DMAC) && defined (DMA_I2C_NUM)
#if defined (I2C_FEATURE_DMA_INTERNAL_INTERRUPT)
    if (!GET_I2C_IER_EN(ptI2c))
    {
        if (ptIcb->eOps == I2C_OPS_INTR_DMA || ptIcb->eOps == I2C_OPS_NMI_DMA)
        {
            if (ptIcb->bTxBusy == true)
            {
                un32Event |= I2C_EVENT_TX_DONE;
                ptIcb->bTxBusy = false;
            }

            if (ptIcb->bRxBusy == true)
            {
                un32Event |= I2C_EVENT_RX_DONE;
                ptIcb->bRxBusy = false;
            }

            HPL_DMA_Stop(ptIcb->eDmaId);
            ptIcb->bDmaEnabled = false;

            SET_I2C_CR_STOP(ptI2c, true);
            SET_I2C_CR_ACK(ptI2c, false);

            goto done;
        }
    }
#else
#endif
#endif

    switch(un32Status)
    {
        case I2C_SLAVE_TX_DONE:
            if(ptIcb->un32TxCnt >= ptIcb->un32TxLen && ptIcb->bTxBusy == true)
            {
                bSend = false;
                un32Event |= I2C_EVENT_TX_DONE;
                ptIcb->un32TxCnt = 0;
                ptIcb->un32TxLen = 0;
                ptIcb->bTxBusy = false;
            }
            break;
        case I2C_SLAVE_TX_SEL_ACK:
            bSend = true;
            if(ptIcb->eMode == I2C_MODE_MASTER)
            {
                if(ptIcb->un32TxCnt >= ptIcb->un32TxLen)
                {
                    bSend = false;
                    SET_I2C_CR_STOP(ptI2c, true);
                    SET_I2C_CR_ACK(ptI2c, false);
                }
            }
#if defined (_DMAC) && defined (DMA_I2C_NUM)
#if defined (I2C_FEATURE_DMA_INTERNAL_INTERRUPT)
            if (ptIcb->eOps == I2C_OPS_INTR_DMA || ptIcb->eOps == I2C_OPS_NMI_DMA)
            {
                SET_I2C_IER_EN(ptI2c, false);
                HPL_DMA_Start(ptIcb->eDmaId, (uint32_t)ptIcb->pun8TxBuf, (uint32_t)GET_I2C_TDR_ADDR(ptI2c), ptIcb->un32TxLen);
            }
#endif
#endif
            break;
        case I2C_MASTER_TX_ADDR_ACK:
            bSend = true;
            if(ptIcb->eMode == I2C_MODE_MASTER)
            {
                if(ptIcb->un32TxCnt >= ptIcb->un32TxLen)
                {
                    bSend = false;
                    SET_I2C_CR_STOP(ptI2c, true);
                    SET_I2C_CR_ACK(ptI2c, false);
                }
            }

#if defined (_DMAC) && defined (DMA_I2C_NUM)
#if defined (I2C_FEATURE_DMA_INTERNAL_INTERRUPT)
            if (ptIcb->eOps == I2C_OPS_INTR_DMA || ptIcb->eOps == I2C_OPS_NMI_DMA)
            {
                SET_I2C_IER_EN(ptI2c, false);
                if (ptIcb->bTxBusy == true)
                {
                    HPL_DMA_Start(ptIcb->eDmaId, (uint32_t)ptIcb->pun8TxBuf, (uint32_t)GET_I2C_TDR_ADDR(ptI2c), ptIcb->un32TxLen);
                }
                else
                {
                    HPL_DMA_Start(ptIcb->eDmaId, (uint32_t)GET_I2C_RDR_ADDR(ptI2c), (uint32_t)ptIcb->pun8RxBuf, ptIcb->un32RxLen);
                }
            }
#endif
#endif
            break;
        case I2C_SLAVE_TX_DATA_NOACK:
        case I2C_SLAVE_TX_GC_ACK:
        case I2C_TX_DATA_ACK:
            bSend = true;
            if(ptIcb->eMode == I2C_MODE_MASTER)
            {
                if(ptIcb->un32TxCnt >= ptIcb->un32TxLen)
                {
                    bSend = false;
                    SET_I2C_CR_STOP(ptI2c, true);
                    SET_I2C_CR_ACK(ptI2c, false);
                }
            }
            break;
        case I2C_MASTER_RX_ADDR_ACK:
            if(ptIcb->eMode == I2C_MODE_MASTER)
            {
                bReceive = false;
                ptIcb->bGCDetected = true;

                if(ptIcb->un32RxCnt + 1 == ptIcb->un32RxLen)
                {
                    SET_I2C_CR_ACK(ptI2c, false);
                }
            }

#if defined (_DMAC) && defined (DMA_I2C_NUM)
#if defined (I2C_FEATURE_DMA_INTERNAL_INTERRUPT)
            if (ptIcb->eOps == I2C_OPS_INTR_DMA || ptIcb->eOps == I2C_OPS_NMI_DMA)
            {
                SET_I2C_IER_EN(ptI2c, false);
                HPL_DMA_Start(ptIcb->eDmaId, (uint32_t)GET_I2C_RDR_ADDR(ptI2c), (uint32_t)ptIcb->pun8RxBuf, ptIcb->un32RxLen);
            }
#endif
#endif
            break;
        case I2C_SLAVE_RX_SEL_ACK:
            if(ptIcb->eMode == I2C_MODE_SLAVE)
            {
                bReceive = false;
                ptIcb->bGCDetected = true;
            }
#if defined (_DMAC) && defined (DMA_I2C_NUM)
#if defined (I2C_FEATURE_DMA_INTERNAL_INTERRUPT)
            if (ptIcb->eOps == I2C_OPS_INTR_DMA || ptIcb->eOps == I2C_OPS_NMI_DMA)
            {
                SET_I2C_IER_EN(ptI2c, false);
                HPL_DMA_Start(ptIcb->eDmaId, (uint32_t)GET_I2C_RDR_ADDR(ptI2c), (uint32_t)ptIcb->pun8RxBuf, ptIcb->un32RxLen);
            }
#endif
#endif
            break;
        case I2C_SLAVE_RX_GC_ACK:
            if(ptIcb->eMode == I2C_MODE_SLAVE)
            {
                bReceive = true;
                ptIcb->bGCDetected = true;
            }
            break;
        case I2C_SLAVE_RX_DONE:
            if(ptIcb->un32RxCnt >= ptIcb->un32RxLen 
               && ptIcb->bGCDetected == true)
            {
                bReceive = false;
                un32Event |= I2C_EVENT_RX_DONE;
                ptIcb->un32RxCnt = 0;
                ptIcb->bRxBusy = false;
                ptIcb->bGCDetected = false;
            }
            break;
        case I2C_MASTER_RX_DATA_NOACK:
        case I2C_RX_DATA_ACK:
            if(ptIcb->eMode == I2C_MODE_MASTER)
            {
                if(ptIcb->un32RxCnt + 1 == ptIcb->un32RxLen -1)
                {
                    SET_I2C_CR_ACK(ptI2c, false);
                }
                else
                {
                    if(ptIcb->un32RxCnt == ptIcb->un32RxLen -1)
                    {
                        SET_I2C_CR_STOP(ptI2c, true);
                    }
                }
            }
            bReceive = true;
            break;
        case I2C_MASTER_TX_ADDR_NOACK:
            bSend = false;
            if(ptIcb->eMode == I2C_MODE_MASTER)
            {
                SET_I2C_CR_START(ptI2c, true);
            }
            break;
        default:
            bSend = false;
            break;
    }

    if(bSend == true)
    {
        SET_I2C_DR_TX(ptI2c,ptIcb->pun8TxBuf[ptIcb->un32TxCnt++]);
    }

    if(bReceive == true && ptIcb->bGCDetected == true)
    {
        ptIcb->pun8RxBuf[ptIcb->un32RxCnt++] = GET_I2C_DR_RX(ptI2c);
    }

#if defined (_DMAC) && defined (DMA_I2C_NUM)
done:
#endif

    if (ptIcb->pfnHandler && un32Event)
    {
        ptIcb->pfnHandler(un32Event, ptIcb->pContext);
    }

    SET_I2C_SR_CLEAR(ptI2c);
}

void I2C0_IRQHandler(void)
{
    PRV_I2C_IRQHandler(I2C_ID_0);
}

void I2C1_IRQHandler(void)
{
    PRV_I2C_IRQHandler(I2C_ID_1);
}

void I2C2_IRQHandler(void)
{
    PRV_I2C_IRQHandler(I2C_ID_2);
}

void I2C3_IRQHandler(void)
{
    PRV_I2C_IRQHandler(I2C_ID_3);
}

void I2C4_IRQHandler(void)
{
    PRV_I2C_IRQHandler(I2C_ID_4);
}

void I2C5_IRQHandler(void)
{
    PRV_I2C_IRQHandler(I2C_ID_5);
}

#endif /* _I2C */
