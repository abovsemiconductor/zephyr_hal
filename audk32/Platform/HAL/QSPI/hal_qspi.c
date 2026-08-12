/**
 *******************************************************************************
 * @file        hal_qspi.c
 * @author      ABOV R&D Division
 * @brief       Quad Serial Peripheral Interface
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

#if defined(_QSPI)
#include "hal_qspi.h"
#include "hal_qspi_prv.h"

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
#include "hpl_nmi.h"
#endif

typedef struct
{
    QSPI_OPS_e               eOps;
    pfnQSPI_IRQ_Handler_t    pfnHandler;
    void                    *pContext;

    bool                    bDmaEnabled;
    bool                    bTxBusy;
    bool                    bRxBusy;
    uint8_t                 *pun8TxBuf;
    uint8_t                 *pun8RxBuf;
    uint32_t                un32TxLen;
    uint32_t                un32RxLen;
    uint32_t                un32TxCnt;
    uint32_t                un32RxCnt;

    QSPI_OP_MODE_e          eOpMode;
    QSPI_PHASE_WIDTH_e      eCmdWidth;
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
    bool                    bNmiEnable;
#endif
} QSPI_CTRL_BLK_t;

static QSPI_CTRL_BLK_t s_tQscb[QSPI_CH_NUM];

static void PRV_QSPI_IRQHandler(QSPI_ID_e eId);

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
static void PRV_QSPI_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < QSPI_CH_NUM; i++)
    {
        if(s_tQscb[i].bNmiEnable == true)
        {
            PRV_QSPI_IRQHandler((QSPI_ID_e)i);
        }
    }
}
#endif

static QSPI_Type *PRV_QSPI_GetReg(QSPI_ID_e eId)
{
    return QSPI_GetReg((P_QSPI_ID_e)eId);
}

static HAL_ERR_e PRV_QSPI_SetScuEnable(P_QSPI_ID_e eId, bool bEnable)
{
    return QSPI_SetScuEnable((P_QSPI_ID_e)eId, bEnable);
}

static HAL_ERR_e PRV_QSPI_SetDMA(QSPI_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    QSPI_Type *ptQspi;
    QSPI_CTRL_BLK_t *ptQscb;

    if ((uint32_t)eId >= QSPI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }
    ptQspi = PRV_QSPI_GetReg(eId);
    ptQscb = &s_tQscb[(uint32_t)eId];

    ptQscb->bDmaEnabled = true;
    SET_QSPI_GCR_DMA_EN(ptQspi, true);

    return eErr;
}

HAL_ERR_e HAL_QSPI_Init(QSPI_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= QSPI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    memset(&s_tQscb[(uint32_t)eId], 0x00, sizeof(QSPI_CTRL_BLK_t));

    eErr = PRV_QSPI_SetScuEnable((P_QSPI_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_QSPI_Uninit(QSPI_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= QSPI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_QSPI_SetScuEnable((P_QSPI_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = QSPI_GetIRQNum((P_QSPI_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tQscb[(uint32_t)eId], 0x00, sizeof(QSPI_CTRL_BLK_t));

    return eErr;
}

HAL_ERR_e HAL_QSPI_SetConfig(QSPI_ID_e eId, QSPI_CFG_t *ptCfg)
{
    QSPI_Type *ptQspi;
    bool bCPol = false;

    if((uint32_t)eId >= QSPI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(ptCfg->eClkMode >= QSPI_CLK_MODE_MAX)
    {
        return HAL_ERR_NOT_SUPPORTED;
    }

    if(ptCfg->un8PRDivider % 2)
    {
        return HAL_ERR_NOT_SUPPORTED;
    }
    else if((ptCfg->un8SamplePoint < ptCfg->un8PRDivider)
            || (ptCfg->un8SamplePoint > (ptCfg->un8PRDivider * 2)))
    {
        return HAL_ERR_PARAMETER;
    }

    ptQspi = PRV_QSPI_GetReg(eId);
    switch(ptCfg->eClkMode)
    {
        case QSPI_CLK_MODE_TRANS_0_CPOL_0:
            bCPol = false;
            break;
        case QSPI_CLK_MODE_TRANS_0_CPOL_1:
            bCPol = true;
            break;
        default:
            break;
    }

    SET_QSPI_GCR_SW_RESET(ptQspi, true);

    SET_QSPI_CLKCFGR_PRD(ptQspi, (ptCfg->un8PRDivider - 1));
    SET_QSPI_CLKCFGR_MINCSL(ptQspi, (ptCfg->un8MinCsLow - 1));
    SET_QSPI_CLKCFGR_SP(ptQspi, ptCfg->un8SamplePoint);
    SET_QSPI_CLKCFGR_TRANS(ptQspi, ptCfg->eTransEdge);
    SET_QSPI_CLKCFGR_CPOL(ptQspi, bCPol);

    SET_QSPI_CSR_CS(ptQspi, (uint8_t)ptCfg->bCSLine);
    SET_QSPI_HTR_TIME(ptQspi, ptCfg->un8HoldTime);
    SET_QSPI_MINCSHR_MINCSH(ptQspi, (ptCfg->un8MinCsHigh - 1));

    SET_QSPI_GCR_SW_RESET(ptQspi, false);
    
    return HAL_ERR_OK;
}

HAL_ERR_e HAL_QSPI_SetIRQ(QSPI_ID_e eId, QSPI_OPS_e eOps, pfnQSPI_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    QSPI_CTRL_BLK_t *ptQscb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= QSPI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptQscb = &s_tQscb[(uint32_t)eId];
    eIrq = QSPI_GetIRQNum((P_QSPI_ID_e)eId);

    switch(eOps)
    {
        case QSPI_OPS_INTR:
        case QSPI_OPS_INTR_DMA:
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            if(ptQscb->bNmiEnable == true)
            {
                (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
                ptQscb->bNmiEnable = false;
            }
#endif
            ptQscb->pfnHandler = pfnHandler;
            ptQscb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            break;
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
        case QSPI_OPS_NMI:
        case QSPI_OPS_NMI_DMA:
            eErr = HPL_NMI_SetSource(eIrq, &PRV_QSPI_NMIHandler, pContext, true);
            if(eErr == HAL_ERR_OK)
            {
                ptQscb->pfnHandler = pfnHandler;
                ptQscb->pContext = pContext;
            }
            ptQscb->bNmiEnable = true;
            break;
#endif
        case QSPI_OPS_POLL:
        default:
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
            ptQscb->bNmiEnable = false;
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);

            ptQscb->pContext = NULL;
            ptQscb->pfnHandler = NULL;
            break;
    }

    ptQscb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_QSPI_SetPhaseConfig(QSPI_ID_e eId, QSPI_PHASE_CFG_t *ptPhaCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    QSPI_Type *ptQspi;
    QSPI_CTRL_BLK_t *ptQscb;
    uint8_t un8Dur = 0x7;
    uint32_t un32Addr = 0;

    if((uint32_t)eId >= QSPI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptQscb = &s_tQscb[eId];
    ptQspi = PRV_QSPI_GetReg(eId);

    if(ptPhaCfg->eOpMode >= QSPI_OP_MODE_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    ptQscb->eOpMode = ptPhaCfg->eOpMode;

    switch (ptPhaCfg->ePhaseType)
    {
    case QSPI_PHASE_CMD:
        ptQscb->eCmdWidth = ptPhaCfg->tPhaCfg.tCmd.eWidth;
        un8Dur = QSPI_GetDuration(ptPhaCfg->tPhaCfg.tCmd.eWidth, ptPhaCfg->eBusMode, ptPhaCfg->eSampleRate);
        if (ptPhaCfg->eOpMode == QSPI_OP_MODE_DIRECT)
        {
            SET_QSPI_XIPCMD_SKIP(ptQspi, ptPhaCfg->bSkip);
            SET_QSPI_XIPCMD_MODE(ptQspi, ptPhaCfg->eBusMode);
            SET_QSPI_XIPCMD_DDR(ptQspi, ptPhaCfg->eSampleRate);
            SET_QSPI_XIPCMD_DURATION(ptQspi, un8Dur);
        }
        else
        {
            SET_QSPI_CMD_SKIP(ptQspi, ptPhaCfg->bSkip);
            SET_QSPI_CMD_MODE(ptQspi, ptPhaCfg->eBusMode);
            SET_QSPI_CMD_DDR(ptQspi, ptPhaCfg->eSampleRate);
            SET_QSPI_CMD_DURATION(ptQspi, un8Dur);
        }
        break;
    case QSPI_PHASE_ADDR:
        ptPhaCfg->tPhaCfg.tAddr.un8Mask = 3;
        un32Addr = (ptPhaCfg->tPhaCfg.tAddr.un32Addr << ((QSPI_PHASE_WIDTH_32BIT - ptPhaCfg->tPhaCfg.tAddr.eWidth) * 8));
        un8Dur = QSPI_GetDuration(ptPhaCfg->tPhaCfg.tAddr.eWidth, ptPhaCfg->eBusMode, ptPhaCfg->eSampleRate);
        if (ptPhaCfg->eOpMode == QSPI_OP_MODE_DIRECT)
        {
            SET_QSPI_XIPADDR_MODE(ptQspi, ptPhaCfg->eBusMode);
            SET_QSPI_XIPADDR_DDR(ptQspi, ptPhaCfg->eSampleRate);
            SET_QSPI_XIPADDR_MASK(ptQspi, ptPhaCfg->tPhaCfg.tAddr.un8Mask);
            SET_QSPI_XIPADDR_ADDRESS(ptQspi, un32Addr);
        }
        else
        {
            SET_QSPI_ADDR_SKIP(ptQspi, ptPhaCfg->bSkip);
            SET_QSPI_ADDR_MODE(ptQspi, ptPhaCfg->eBusMode);
            SET_QSPI_ADDR_DDR(ptQspi, ptPhaCfg->eSampleRate);
            SET_QSPI_ADDR_MASK(ptQspi, ptPhaCfg->tPhaCfg.tAddr.un8Mask);
            SET_QSPI_ADDR_ADDRESS(ptQspi, un32Addr);
            SET_QSPI_ADDR_DURATION(ptQspi, un8Dur);
        }
        break;
    case QSPI_PHASE_MBIT:
    un8Dur = QSPI_GetDuration(ptPhaCfg->tPhaCfg.tMBits.eWidth, ptPhaCfg->eBusMode, ptPhaCfg->eSampleRate);
        if (ptPhaCfg->eOpMode == QSPI_OP_MODE_DIRECT)
        {
            SET_QSPI_XIPMBITS_SKIP(ptQspi, ptPhaCfg->bSkip);
            SET_QSPI_XIPMBITS_MODE(ptQspi, ptPhaCfg->eBusMode);
            SET_QSPI_XIPMBITS_DDR(ptQspi, ptPhaCfg->eSampleRate);
            SET_QSPI_XIPMBR_MODE(ptQspi, ptPhaCfg->tPhaCfg.tMBits.un32ModeBits);
            SET_QSPI_XIPMBITS_DURATION(ptQspi, un8Dur);
        }
        else
        {
            SET_QSPI_MBITS_SKIP(ptQspi, ptPhaCfg->bSkip);
            SET_QSPI_MBITS_MODE(ptQspi, ptPhaCfg->eBusMode);
            SET_QSPI_MBITS_DDR(ptQspi, ptPhaCfg->eSampleRate);
            SET_QSPI_MBR_MODE(ptQspi, ptPhaCfg->tPhaCfg.tMBits.un32ModeBits);
            SET_QSPI_MBITS_DURATION(ptQspi, un8Dur);
        }
        break;
    case QSPI_PHASE_DUMMY:
        ptPhaCfg->tPhaCfg.tDmy.bNoWrLatency = true;
        if (ptPhaCfg->eOpMode == QSPI_OP_MODE_DIRECT)
        {
            SET_QSPI_XIPDMY_SKIP(ptQspi, ptPhaCfg->bSkip);
            SET_QSPI_XIPDMY_DURATION(ptQspi, ptPhaCfg->tPhaCfg.tDmy.un8Cycles - 1);
            SET_QSPI_XIPDMY_NO_W_LATENCY(ptQspi, ptPhaCfg->tPhaCfg.tDmy.bNoWrLatency);
        }
        else
        {
            SET_QSPI_DMY_SKIP(ptQspi, ptPhaCfg->bSkip);
            SET_QSPI_DMY_DURATION(ptQspi, ptPhaCfg->tPhaCfg.tDmy.un8Cycles - 1);
            SET_QSPI_DMY_NO_W_LATENCY(ptQspi, ptPhaCfg->tPhaCfg.tDmy.bNoWrLatency);
        }
        break;
    case QSPI_PHASE_DATA:
        if (ptPhaCfg->eOpMode == QSPI_OP_MODE_DIRECT)
        {
            SET_QSPI_XIPDATA_MODE(ptQspi, ptPhaCfg->eBusMode);
            SET_QSPI_XIPDATA_DDR(ptQspi, ptPhaCfg->eSampleRate);
            SET_QSPI_XIPDATA_FLIP(ptQspi, ptPhaCfg->tPhaCfg.tData.eFlipMode);
        }
        else
        {
            SET_QSPI_DATA_SKIP(ptQspi, ptPhaCfg->bSkip);
            SET_QSPI_DATA_MODE(ptQspi, ptPhaCfg->eBusMode);
            SET_QSPI_DATA_DDR(ptQspi, ptPhaCfg->eSampleRate);
            SET_QSPI_DATA_FLIP(ptQspi, ptPhaCfg->tPhaCfg.tData.eFlipMode);
            SET_QSPI_DATA_DIRECTION(ptQspi, ptPhaCfg->tPhaCfg.tData.eDirMode);
            SET_QSPI_DATA_SIZE(ptQspi, ((ptPhaCfg->tPhaCfg.tData.un32Size * 8) - 1));
        }
        break;
    default:
        break;
    }

    return eErr;
}

HAL_ERR_e HAL_QSPI_SetDmaConfig(QSPI_ID_e eId, QSPI_DMA_CFG_t *ptDmaCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    QSPI_Type *ptQspi;

    if((uint32_t)eId >= QSPI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptQspi = PRV_QSPI_GetReg(eId);

    SET_QSPI_DMASTAR_ADDR(ptQspi, ptDmaCfg->un32DescAddr);
    SET_QSPI_DMAFBLSR(ptQspi, ptDmaCfg->eFixedBurstLen);

    eErr = PRV_QSPI_SetDMA(eId);

    return eErr;
}

HAL_ERR_e HAL_QSPI_Command(QSPI_ID_e eId, uint16_t un16Cmd, uint32_t un32Timeout)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    QSPI_Type *ptQspi;
    QSPI_CTRL_BLK_t *ptQscb;
    uint16_t un16Command;

    if((uint32_t)eId >= QSPI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptQscb = &s_tQscb[eId];
    ptQspi = PRV_QSPI_GetReg(eId);

    while(GET_QSPI_SR_BUSY(ptQspi))
    {
        un32Timeout--;
        if(un32Timeout == 0)
        {
            return HAL_ERR_TIMEOUT;
        }
    }

    if(ptQscb->eCmdWidth > QSPI_PHASE_WIDTH_16BIT)
    {
        return HAL_ERR_INVALID_USE;
    }
    un16Command = (un16Cmd << ((QSPI_PHASE_WIDTH_16BIT - ptQscb->eCmdWidth) * 8));

    if(ptQscb->eOpMode == QSPI_OP_MODE_DIRECT)
    {
        SET_QSPI_XIPCMD_COMMAND(ptQspi, un16Command);
    }
    else
    {
        SET_QSPI_CMD_COMMAND(ptQspi, un16Command);
    }

    return eErr;
}

HAL_ERR_e HAL_QSPI_Transmit(QSPI_ID_e eId, uint8_t *pun8Out, uint32_t un32Len, bool bEnForcePoll)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    QSPI_CTRL_BLK_t *ptQscb;
    QSPI_Type *ptQspi;
    volatile uint32_t un32TxData;
    uint32_t un32LeftBytes;
    uint8_t un8WriteBytes;
    bool bCompleted = false;

    if((uint32_t)eId >= QSPI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptQscb = &s_tQscb[eId];
    ptQspi = PRV_QSPI_GetReg(eId);

    if (ptQscb->bTxBusy == true)
    {
        return HAL_ERR_BUSY;
    }

    ptQscb->bTxBusy = true;
    ptQscb->pun8TxBuf = (uint8_t *)pun8Out;
    ptQscb->un32TxLen = un32Len;
    ptQscb->un32TxCnt = 0;
    ptQscb->un32RxLen = 0;

    if(ptQscb->eOps == QSPI_OPS_POLL || bEnForcePoll)
    {
        while(!bCompleted)
        {
            if(ptQscb->un32TxCnt >= ptQscb->un32TxLen)
            {
                bCompleted = true;
                continue;
            }

            while(!GET_QSPI_FSR_EMPTY(ptQspi))
            {
                /* Waiting for Tx Ready */
            }

            un32LeftBytes = ptQscb->un32TxLen - ptQscb->un32TxCnt;
            un8WriteBytes = (un32LeftBytes >= 4) ? 4 : un32LeftBytes;

            un32TxData = 0;
            for(uint8_t un8CurByte = 0; un8CurByte < un8WriteBytes; un8CurByte++)
            {
                un32TxData |= (*ptQscb->pun8TxBuf++ << (24 - (un8CurByte * 8)));
            }
            SET_QSPI_DATA_TX(ptQspi, un32TxData);
            ptQscb->un32TxCnt += un8WriteBytes;
        }
        ptQscb->bTxBusy = false;
    }
    else if(ptQscb->bDmaEnabled == true)
    {
        SET_QSPI_IER_DMA_ERR_EN(ptQspi,true);
        SET_QSPI_IER_DMA_EN(ptQspi,true);
    }
    else
    {
        SET_QSPI_IER_TX_ERR_EN(ptQspi,true);    // Must be set before enabling IER_TX_EN
        SET_QSPI_IER_TX_EN(ptQspi,true);
    }
    return eErr;
}

HAL_ERR_e HAL_QSPI_Receive(QSPI_ID_e eId, uint8_t *pun8In, uint32_t un32Len, bool bEnForcePoll)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    QSPI_CTRL_BLK_t *ptQscb;
    QSPI_Type *ptQspi;
    uint32_t un32RxData;
    uint32_t un32LeftBytes;
    uint8_t un8ReadBytes;
    bool bCompleted = false;

    if((uint32_t)eId >= QSPI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptQscb = &s_tQscb[eId];
    ptQspi = PRV_QSPI_GetReg(eId);

    if (ptQscb->bRxBusy == true)
    {
        return HAL_ERR_BUSY;
    }

    ptQscb->bRxBusy = true;
    ptQscb->pun8RxBuf = (uint8_t *)pun8In;
    ptQscb->un32RxLen = un32Len;
    ptQscb->un32RxCnt = 0;

    if(ptQscb->eOps == QSPI_OPS_POLL || bEnForcePoll == true)
    {
        while(!bCompleted)
        {
            if(ptQscb->un32RxCnt >= ptQscb->un32RxLen)
            {
                bCompleted = true;
                continue;
            }

            while(GET_QSPI_FSR_EMPTY(ptQspi))
            {
                /* Waiting for Rx Ready */
            }

            un32RxData = GET_QSPI_DATA_RX(ptQspi);

            un32LeftBytes = ptQscb->un32RxLen - ptQscb->un32RxCnt;
            un8ReadBytes = (un32LeftBytes >= 4) ? 4 : un32LeftBytes;

            switch (un8ReadBytes)
            {
            case 4:
                *(ptQscb->pun8RxBuf++) = (uint8_t)(un32RxData >> 24);
            case 3:
                *(ptQscb->pun8RxBuf++) = (uint8_t)(un32RxData >> 16);
            case 2:
                *(ptQscb->pun8RxBuf++) = (uint8_t)(un32RxData >> 8);
            case 1:
                *(ptQscb->pun8RxBuf++) = (uint8_t)(un32RxData);
                break;
            default:
                break;
            }
            ptQscb->un32RxCnt += un8ReadBytes;
            un32RxData = 0;
        }
        ptQscb->bRxBusy = false;
    }
    else
    {
        if (ptQscb->bDmaEnabled == true)
        {
            SET_QSPI_IER_DMA_ERR_EN(ptQspi,true);
            SET_QSPI_IER_DMA_EN(ptQspi,true);
        }
        else
        {
            SET_QSPI_IER_RX_ERR_EN(ptQspi, true);
            SET_QSPI_IER_RX_EN(ptQspi, true);
            SET_QSPI_IER_NOT_BUSY_EN(ptQspi, true); // Must be set after enabling IER_RX_EX
        }
    }

    return eErr;
}

static void PRV_QSPI_IRQHandler(QSPI_ID_e eId)
{
    QSPI_CTRL_BLK_t *ptQscb;
    QSPI_Type *ptQspi;
    volatile uint32_t un32Event = 0;
    uint32_t un32Data = 0;
    uint8_t un8DataBytes;
    uint32_t un32LeftBytes;

    if((uint32_t)eId >= QSPI_CH_NUM)
    {
        return;
    }

    ptQspi = PRV_QSPI_GetReg(eId);
    ptQscb = &s_tQscb[eId];

    if(ptQscb->bDmaEnabled == true)
    {
        if((ptQscb->bTxBusy == true))
        {
            if(GET_QSPI_DMASR_ERR(ptQspi))
            {
                SET_QSPI_GCR_SW_RESET(ptQspi, true);
                un32Event |= QSPI_EVENT_TX_ERROR;
            }

            if (GET_QSPI_DMASR_IRQ(ptQspi))
            {
                un32Event |= QSPI_EVENT_TX_DONE;
            }
            SET_QSPI_IER_DMA_ERR_EN(ptQspi,false);
            SET_QSPI_IER_DMA_EN(ptQspi,false);
            SET_QSPI_DMASR_IRQ(ptQspi, false);
            SET_QSPI_DMASR_ERR(ptQspi, false);
            ptQscb->bTxBusy = false;
            SET_QSPI_GCR_DMA_EN(ptQspi, false);
            ptQscb->bDmaEnabled = false;    // DMA mode is automatically disabled after one transfer is completed.
            goto done;
        }

        if(ptQscb->bRxBusy == true)
        {
            if(GET_QSPI_DMASR_ERR(ptQspi))
            {
                SET_QSPI_GCR_SW_RESET(ptQspi, true);
                un32Event |= QSPI_EVENT_RX_ERROR;
            }
            if (GET_QSPI_DMASR_IRQ(ptQspi))
            {
                un32Event |= QSPI_EVENT_RX_DONE;
            }
            SET_QSPI_IER_DMA_ERR_EN(ptQspi,false);
            SET_QSPI_IER_DMA_EN(ptQspi,false);
            SET_QSPI_DMASR_IRQ(ptQspi, false);
            SET_QSPI_DMASR_ERR(ptQspi, false);
            ptQscb->bRxBusy = false;
            SET_QSPI_GCR_DMA_EN(ptQspi, false);
            ptQscb->bDmaEnabled = false;    // DMA mode is automatically disabled after one transfer is completed.
            goto done;
        }
    }

    /* Interrupt Transmit */
    if(ptQscb->un32TxLen != 0 && ptQscb->bTxBusy == true)
    {
        if(ptQscb->un32TxCnt >= ptQscb->un32TxLen)
        {
            un32Event |= QSPI_EVENT_TX_DONE;
            ptQscb->bTxBusy = false;
            SET_QSPI_IER_TX_ERR_EN(ptQspi, false);
            SET_QSPI_IER_TX_EN(ptQspi, false);
            goto done;
        }
        if (GET_QSPI_SR_TX_RDY(ptQspi) && GET_QSPI_SR_RDY(ptQspi))
        {
            un32LeftBytes = ptQscb->un32TxLen - ptQscb->un32TxCnt;
            un8DataBytes = (un32LeftBytes >= 4) ? 4 : un32LeftBytes;

            for (uint8_t un8CurByte = 0; un8CurByte < un8DataBytes; un8CurByte++)
            {
                un32Data |= (*ptQscb->pun8TxBuf++ << (24 - (un8CurByte * 8)));
            }
            SET_QSPI_DATA_TX(ptQspi, un32Data);
            ptQscb->un32TxCnt += un8DataBytes;
            un32Data = 0;
            goto done;
        }
        if(GET_QSPI_SR_TX_ERR(ptQspi))
        {
            /* Clear Transmit Error flag */
            un32Event |= QSPI_EVENT_TX_ERROR;
            ptQscb->bTxBusy = false;
            SET_QSPI_IER_TX_ERR_EN(ptQspi, false);
            SET_QSPI_SR_TX_ERR(ptQspi, true);
        }
    }

    /* Interrupt Receive */
    if (ptQscb->un32RxLen != 0 && ptQscb->bRxBusy == true)
    {
        if (ptQscb->un32RxCnt < ptQscb->un32RxLen)
        {
            if (GET_QSPI_SR_RX_RDY(ptQspi) || !GET_QSPI_SR_BUSY(ptQspi))
            {
                if (!GET_QSPI_FSR_EMPTY(ptQspi))
                {
                    un32Data = GET_QSPI_DATA_RX(ptQspi);

                    un32LeftBytes = ptQscb->un32RxLen - ptQscb->un32RxCnt;
                    un8DataBytes = (un32LeftBytes >= 4) ? 4 : un32LeftBytes;

                    switch (un8DataBytes)
                    {
                    case 4:
                        *(ptQscb->pun8RxBuf++) = (uint8_t)(un32Data >> 24);
                    case 3:
                        *(ptQscb->pun8RxBuf++) = (uint8_t)(un32Data >> 16);
                    case 2:
                        *(ptQscb->pun8RxBuf++) = (uint8_t)(un32Data >> 8);
                    case 1:
                        *(ptQscb->pun8RxBuf++) = (uint8_t)(un32Data);
                        break;
                    default:
                        break;
                    }
                    ptQscb->un32RxCnt += un8DataBytes;
                    un32Data = 0;

                    if (ptQscb->un32RxCnt >= ptQscb->un32RxLen)
                    {
                        un32Event |= QSPI_EVENT_RX_DONE;
                        ptQscb->bRxBusy = false;
                        SET_QSPI_IER_NOT_BUSY_EN(ptQspi, false);
                        SET_QSPI_IER_RX_ERR_EN(ptQspi, false);
                        SET_QSPI_IER_RX_EN(ptQspi, false);
                        goto done;
                    }
                }
            }
        }
        if (GET_QSPI_SR_RX_ERR(ptQspi))
        {
            /* Clear Receive Error flag */
            un32Event |= QSPI_EVENT_RX_ERROR;
            ptQscb->bRxBusy = false;
            SET_QSPI_IER_NOT_BUSY_EN(ptQspi, false);
            SET_QSPI_IER_RX_ERR_EN(ptQspi, false);
            SET_QSPI_SR_RX_ERR(ptQspi, true);
        }
    }
done:
    if (ptQscb->pfnHandler && un32Event)
    {
        ptQscb->pfnHandler(un32Event, ptQscb->pContext);
    }
}

void QSPI0_IRQHandler(void)
{
    PRV_QSPI_IRQHandler(QSPI_ID_0);
}

#endif /* _QSPI */
