/**
 *******************************************************************************
 * @file        hal_aes.c
 * @author      ABOV R&D Division
 * @brief       Advanced Encryption Standard
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

#if defined(_AES)
#include "hal_aes.h"
#include "hal_aes_prv.h"

#if defined(_DMAC) && defined(DMA_AES_NUM)
#include "hpl_dma.h"
#endif

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
#include "hpl_nmi.h"
#endif

typedef struct
{
    AES_OPS_e               eOps;
    pfnAES_IRQ_Handler_t    pfnHandler;
    void                    *pContext;
#if defined(_DMAC) && defined(DMA_AES_NUM)
    DMA_ID_e                eDmaInId;
    bool                    bDmaInEnabled;
    DMA_ID_e                eDmaOutId;
    bool                    bDmaOutEnabled;
#endif

    AES_CHAIN_MODE_e        eChainMode;
    AES_CIPHER_MODE_e       eCipherMode;
    uint32_t                *pun32InBuf; 
    uint32_t                *pun32OutBuf; 
    uint32_t                un32Len; 
    uint32_t                un32Cnt; 
    bool                    bBusy;

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
    bool                    bNmiEnable;
#endif

} AES_CTRL_BLK_t;

static AES_CTRL_BLK_t s_tAcb[AES_CH_NUM];

static void PRV_AES_IRQHandler(AES_ID_e eId);

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
static void PRV_AES_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < AES_CH_NUM; i++)
    {
        if(s_tAcb[i].bNmiEnable == true)
        {
            PRV_AES_IRQHandler((AES_ID_e)i);
        }
    }
}
#endif

#if defined(_DMAC) && defined(DMA_AES_NUM) && defined (AES_FEATURE_DMA_INTERNAL_INTERRUPT)
static void PRV_AES_DMAHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < AES_CH_NUM; i++)
    {
        PRV_AES_IRQHandler((AES_ID_e)i);
    }
}
#endif

static AES_Type *PRV_AES_GetReg(P_AES_ID_e eId)
{
    return AES_GetReg((P_AES_ID_e)eId);
}

static HAL_ERR_e PRV_AES_SetScuEnable(P_AES_ID_e eId, bool bEnable)
{
    return AES_SetScuEnable((P_AES_ID_e)eId, bEnable);
}

#if defined(_DMAC) && defined(DMA_AES_NUM)
static HAL_ERR_e PRV_AES_SetDMA(P_AES_ID_e eId, DMA_PERI_COM_e eCom)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    AES_CTRL_BLK_t *ptAcb;
    DMA_ID_e eDmaId;
    DMA_CFG_t tDmaCfg =
    {
        .ePeri = DMA_PERI_AES,
        .ePeriId = (DMA_PERI_ID_e)eId,
        .un32PeriNum = 0,
        .eSize = DMA_BUS_SIZE_WORD,
        .eDir = DMA_DIR_PERI_TO_MEM
    };

    eErr = HPL_DMA_Init(DMA_PERI_AES, (uint8_t)eId);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    eErr = (HAL_ERR_e)HPL_DMA_GetAvailChannel(&eDmaId);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }
    
    if(eCom == DMA_PERI_COM_TX)
    {
        tDmaCfg.eDir = DMA_DIR_MEM_TO_PERI;
    }

#if defined (AES_FEATURE_DMA_INTERNAL_INTERRUPT)
    eErr = HPL_DMA_SetIRQ(DMA_PERI_AES, &PRV_AES_DMAHandler, NULL, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }
#endif
    
    eErr = (HAL_ERR_e)HPL_DMA_GetPeriSelectNumber(DMA_PERI_AES, (DMA_PERI_ID_e)eId, eCom, &tDmaCfg.un32PeriNum);
    if(eErr == HAL_ERR_OK)
    {
        eErr = HPL_DMA_SetConfig(eDmaId, &tDmaCfg);
        if(eErr != HAL_ERR_OK)
        {
            return eErr;
        }
         
        ptAcb = &s_tAcb[(uint32_t)eId];

        if(eCom == DMA_PERI_COM_TX)
        {
            ptAcb->eDmaInId = eDmaId;
            ptAcb->bDmaInEnabled = true;
        }
        else
        {
            ptAcb->eDmaOutId = eDmaId;
            ptAcb->bDmaOutEnabled = true;
        }

    }

    return eErr;
}
#endif

HAL_ERR_e HAL_AES_Init(AES_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= AES_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_AES_SetScuEnable((P_AES_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tAcb[(uint32_t)eId], 0x00, sizeof(AES_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_AES_Uninit(AES_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;
#if defined(_DMAC) && defined(DMA_AES_NUM)
    AES_CTRL_BLK_t *ptAcb;
#endif

    if((uint32_t)eId >= AES_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_AES_SetScuEnable((P_AES_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

#if defined(_DMAC) && defined(DMA_AES_NUM)
    ptAcb = &s_tAcb[(uint32_t)eId];

    if(ptAcb->bDmaInEnabled == true || ptAcb->bDmaOutEnabled == true)
    {
        HPL_DMA_Uninit(DMA_PERI_AES, (uint8_t)eId);
    }
#endif

    memset(&s_tAcb[(uint32_t)eId], 0x00, sizeof(AES_CTRL_BLK_t));

    /* Forcily, disable NVIC Interrupt */
    eIrq = AES_GetIRQNum((P_AES_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_AES_SetConfig(AES_ID_e eId, AES_CFG_t *ptCfg)
{
    AES_Type *ptAes;
    AES_CTRL_BLK_t *ptAcb;

    if ((uint32_t)eId >= AES_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if defined (AES_FEATURE_CHAIN_ONLY_ECB)
    if (ptCfg->eChainMode != AES_CHAIN_MODE_ECB)
    {
        return HAL_ERR_PARAMETER;
    }
#endif

#if defined (AES_FEATURE_ONE_INOUT_ALIGN)
    if (ptCfg->eTextInAlign != ptCfg->eTextOutAlign)
    {
        return HAL_ERR_PARAMETER;
    }
#endif

    ptAes = PRV_AES_GetReg((P_AES_ID_e)eId);
    SET_AES_CR_CHAIN_MODE(ptAes, ptCfg->eChainMode);
    SET_AES_CR_CIPHER_MODE(ptAes, AES_CIPHER_MODE(ptCfg->eCipherMode));
    SET_AES_CR_TEXT_IN_SEL(ptAes, AES_TEXT_ALIGN(ptCfg->eTextInAlign));
    SET_AES_CR_TEXT_OUT_SEL(ptAes, AES_TEXT_ALIGN(ptCfg->eTextOutAlign));

    SET_AES_IER_ENC_DONE_EN(ptAes, false);
    SET_AES_IER_DEC_DONE_EN(ptAes, false);

    if(ptCfg->un8IntrEnable & AES_INTR_ENC_DONE)
    {
        SET_AES_IER_ENC_DONE_EN(ptAes, true);
    }

    if(ptCfg->un8IntrEnable & AES_INTR_DEC_DONE)
    {
        SET_AES_IER_DEC_DONE_EN(ptAes, true);
    }

    ptAcb = &s_tAcb[(uint32_t)eId];
    ptAcb->eCipherMode = ptCfg->eCipherMode;
    ptAcb->eChainMode = ptCfg->eChainMode;

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_AES_SetIRQ(AES_ID_e eId, AES_OPS_e eOps, pfnAES_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    AES_CTRL_BLK_t *ptAcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= AES_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAcb = &s_tAcb[(uint32_t)eId];
    eIrq = AES_GetIRQNum((P_AES_ID_e)eId);

    switch(eOps)
    {
        case AES_OPS_INTR:
        case AES_OPS_INTR_DMA:
#if defined (AES_FEATURE_IRQ_UNMASK_ENABLE)
            AES_SetIntrUnMask(eIrq, true);
#endif
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            if(ptAcb->bNmiEnable == true)
            {
                (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
                ptAcb->bNmiEnable = false;
            }
#endif
            ptAcb->pfnHandler = pfnHandler;
            ptAcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
#if defined(_DMAC) && defined(DMA_AES_NUM)
            if(eOps == AES_OPS_INTR_DMA)
            {
                /* assigne DMA RX resource */
                eErr = PRV_AES_SetDMA((P_AES_ID_e)eId, DMA_PERI_COM_RX);
                if(eErr != HAL_ERR_OK)
                {
                    return eErr;
                }

                /* assigne DMA TX resource */
                eErr = PRV_AES_SetDMA((P_AES_ID_e)eId, DMA_PERI_COM_TX);
                if(eErr != HAL_ERR_OK)
                {
                    return eErr;
                }

            }
#endif
            break;
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
        case AES_OPS_NMI:
            eErr = HPL_NMI_SetSource(eIrq, &PRV_AES_NMIHandler, pContext, true);
            if(eErr == HAL_ERR_OK)
            {
                ptAcb->pfnHandler = pfnHandler;
                ptAcb->pContext = pContext;
            }
            ptAcb->bNmiEnable = true;
            break;
#endif

        case AES_OPS_POLL:
        default:
#if defined (AES_FEATURE_IRQ_UNMASK_ENABLE)
            AES_SetIntrUnMask(eIrq, true);
#endif
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
            ptAcb->bNmiEnable = false;
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
#if defined(_DMAC) && defined(DMA_AES_NUM)
            if(ptAcb->bDmaInEnabled == true || ptAcb->bDmaOutEnabled == true)
            {
                HPL_DMA_Uninit(DMA_PERI_AES, (uint8_t)eId);
                ptAcb->bDmaInEnabled = false;
                ptAcb->bDmaOutEnabled = false;
            }
#endif
            ptAcb->pContext = NULL;
            ptAcb->pfnHandler = NULL;
            break;
    }

    ptAcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_AES_SetKey(AES_ID_e eId, uint32_t *pun32Key)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    AES_Type *ptAes;
    uint32_t un32AddrReg;

    if((uint32_t)eId >= AES_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAes = PRV_AES_GetReg((P_AES_ID_e)eId);

    for(int i = 0; i < AES_KEY_REG_COUNT; i++)
    {
        un32AddrReg = (uint32_t)(GET_AES_DR_KEY_BASE_ADDR(ptAes) + i);
        *(volatile uint32_t *)un32AddrReg = pun32Key[i];
    }  

    return eErr;
}

HAL_ERR_e HAL_AES_SetIVKey(AES_ID_e eId, uint32_t *pun32IVKey)
{
#if defined (AES_FEATURE_INIT_VECTOR)
    HAL_ERR_e eErr = HAL_ERR_OK;
    AES_Type *ptAes;
    uint32_t un32AddrReg;

    if((uint32_t)eId >= AES_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAes = PRV_AES_GetReg((P_AES_ID_e)eId);

    for(int i = 0; i < AES_KEY_REG_COUNT; i++)
    {
        un32AddrReg = (uint32_t)(GET_AES_DR_IV_BASE_ADDR(ptAes) + i);
        *(volatile uint32_t *)un32AddrReg = pun32IVKey[i];
    }  

    return eErr;
#else
    (void)eId;
    (void)pun32IVKey;
    return HAL_ERR_NOT_SUPPORTED;
#endif

}

HAL_ERR_e HAL_AES_SetCompute(AES_ID_e eId, uint32_t *pun32Data, uint32_t un32Len, uint32_t *pun32Out)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    AES_Type *ptAes;
    AES_CTRL_BLK_t *ptAcb;
    uint32_t un32AddrReg;

    if((uint32_t)eId >= AES_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAes = PRV_AES_GetReg((P_AES_ID_e)eId);
    ptAcb = &s_tAcb[(uint32_t)eId];

    if(ptAcb->bBusy == true)
    {
        return HAL_ERR_BUSY;
    }

    ptAcb->pun32InBuf = pun32Data;
    ptAcb->pun32OutBuf = pun32Out;
    ptAcb->un32Len = un32Len;
    ptAcb->un32Cnt = 0;

#if defined (AES_FEATURE_DESC_KEY_EXPANSION)
    if(ptAcb->eCipherMode == AES_CIPHER_MODE_DEC)
    {
        if (ptAcb->eChainMode != AES_CHAIN_MODE_CTR)
        {
            AES_SetDescKeyExp();
        }
    }    
#endif

    SET_AES_CR_EN(ptAes, true);

    if(ptAcb->eOps == AES_OPS_POLL)
    {
        while(ptAcb->un32Cnt < ptAcb->un32Len)
        {
            SET_AES_CR_IN_FIFO_FLUSH(ptAes, true);
            SET_AES_CR_OUT_FIFO_FLUSH(ptAes, true);

            for(int i = 0; i < AES_BYTE_LENGTH; i++)
            {
                SET_AES_DR_INFIFO_VAL(ptAes, ptAcb->pun32InBuf[ptAcb->un32Cnt++]);
            }

            while(!GET_AES_IER_ENC_DONE_FLAG(ptAes) && !GET_AES_IER_DEC_DONE_FLAG(ptAes))
            {
            }

            if(ptAcb->eCipherMode == AES_CIPHER_MODE_ENC)
            {
                SET_AES_IER_ENC_DONE_FLAG(ptAes, true);
            }
            else
            {
                SET_AES_IER_DEC_DONE_FLAG(ptAes, true);
            }

            for(int i = 0; i < AES_BYTE_LENGTH; i++)
            {
#if defined (AES_FEATURE_READ_SINGLE_BUFFER)
                un32AddrReg = (uint32_t)(GET_AES_DR_TEXT_OUT_ADDR(ptAes));
#else
                un32AddrReg = (uint32_t)(GET_AES_DR_TEXT_OUT_ADDR(ptAes) + i);
#endif
                ptAcb->pun32OutBuf[ptAcb->un32Cnt - (AES_BYTE_LENGTH - i)] = (uint32_t)(*(volatile uint32_t *)un32AddrReg);
            }  
        }
    }
    else
    {
#if defined(_DMAC) && defined(DMA_AES_NUM)
        if(ptAcb->eOps == AES_OPS_INTR_DMA)
        {
            SET_AES_CR_IN_FIFO_FLUSH(ptAes, true);
            SET_AES_CR_OUT_FIFO_FLUSH(ptAes, true);

            SET_AES_IER_IN_DMA_EN(ptAes, true);
            SET_AES_IER_OUT_DMA_EN(ptAes, true);

#if defined (AES_FEATURE_DMA_INTERNAL_INTERRUPT)
            SET_AES_IER_ENC_DONE_EN(ptAes, false);
            SET_AES_IER_DEC_DONE_EN(ptAes, false);
#endif

            /* Start Out Dma */
            if(ptAcb->bDmaOutEnabled == true)
            {
                eErr = HPL_DMA_Start(ptAcb->eDmaOutId, (uint32_t)GET_AES_DR_OUTFIFO_ADDR(ptAes), (uint32_t)pun32Out, un32Len);
            }
            else
            {
                eErr = HAL_ERR_INVALID_USE;
            }

            /* Start In Dma */
            if(ptAcb->bDmaInEnabled == true)
            {
                eErr = HPL_DMA_Start(ptAcb->eDmaInId, (uint32_t)pun32Data, (uint32_t)GET_AES_DR_INFIFO_ADDR(ptAes), un32Len);
            }
            else
            {
                eErr = HAL_ERR_INVALID_USE;
            }

            if(eErr == HAL_ERR_OK)
            {
                ptAcb->bBusy = true;
            }
        }
        else
#endif
        {
            ptAcb->bBusy = true;

            SET_AES_CR_IN_FIFO_FLUSH(ptAes, true);
            SET_AES_CR_OUT_FIFO_FLUSH(ptAes, true);

            for(int i = 0; i < AES_BYTE_LENGTH; i++)
            {
                SET_AES_DR_INFIFO_VAL(ptAes, ptAcb->pun32InBuf[ptAcb->un32Cnt++]);
            }
        }
    }

    return eErr;
}

HAL_ERR_e HAL_AES_GetResult(AES_ID_e eId, uint32_t *pun32Out)
{
    AES_Type *ptAes;
    uint32_t un32AddrReg = 0;

    if((uint32_t)eId >= AES_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAes = PRV_AES_GetReg((P_AES_ID_e)eId);

    for(int i = 0; i < AES_BYTE_LENGTH; i++)
    {
#if defined (AES_FEATURE_READ_SINGLE_BUFFER)
        un32AddrReg = (uint32_t)(GET_AES_DR_TEXT_OUT_ADDR(ptAes));
#else
        un32AddrReg = (uint32_t)(GET_AES_DR_TEXT_OUT_ADDR(ptAes) + i);
#endif
        pun32Out[i] = (uint32_t)(*(volatile uint32_t *)un32AddrReg);
    }

    return HAL_ERR_OK;
}

void PRV_AES_IRQHandler(AES_ID_e eId)
{
    AES_Type *ptAes;
    AES_CTRL_BLK_t *ptAcb;
    uint32_t un32Event = 0;
    uint32_t un32AddrReg = 0;

    if((uint32_t)eId >= AES_CH_NUM)
    {
        return;
    }

    ptAes = PRV_AES_GetReg((P_AES_ID_e)eId);
    ptAcb = &s_tAcb[(uint32_t)eId];

    if(GET_AES_IER_ENC_DONE_FLAG(ptAes))
    {
        un32Event |= AES_EVENT_ENC_DONE;
        SET_AES_IER_ENC_DONE_FLAG(ptAes, true);
    }
  
    if(GET_AES_IER_DEC_DONE_FLAG(ptAes))
    {
        un32Event |= AES_EVENT_DEC_DONE;
        SET_AES_IER_DEC_DONE_FLAG(ptAes, true);
    }

#if defined(_DMAC) && defined(DMA_AES_NUM)
#if defined (AES_FEATURE_DMA_INTERNAL_INTERRUPT)
    if (ptAcb->eOps == AES_OPS_INTR_DMA)
    {
        if(ptAcb->eCipherMode == AES_CIPHER_MODE_ENC)
        {
            un32Event = AES_EVENT_ENC_DONE;
        }
        if(ptAcb->eCipherMode == AES_CIPHER_MODE_DEC)
        {
            un32Event = AES_EVENT_DEC_DONE;
        }
        ptAcb->bBusy = false;
        SET_AES_CR_EN(ptAes, false);
        HPL_DMA_Stop(ptAcb->eDmaInId);
        ptAcb->bDmaInEnabled = false;
        HPL_DMA_Stop(ptAcb->eDmaOutId);
        ptAcb->bDmaOutEnabled = false;
    }
#else
    if(GET_AES_IER_IN_DMA_FLAG(ptAes))
    {
        /* waiting for out dma flag */
        un32Event = 0;
        SET_AES_IER_IN_DMA_FLAG(ptAes, true);
    }
  
    if(GET_AES_IER_OUT_DMA_FLAG(ptAes))
    {
        SET_AES_IER_OUT_DMA_FLAG(ptAes, true);
        /* Done */
        ptAcb->bBusy = false;
    }
#endif
#endif

    if((un32Event != 0) && ((ptAcb->eOps == AES_OPS_INTR) || ptAcb->eOps == AES_OPS_NMI))
    {
        for(int i = 0; i < AES_BYTE_LENGTH; i++)
        {
#if defined (AES_FEATURE_READ_SINGLE_BUFFER)
            un32AddrReg = (uint32_t)(GET_AES_DR_TEXT_OUT_ADDR(ptAes));
#else
            un32AddrReg = (uint32_t)(GET_AES_DR_TEXT_OUT_ADDR(ptAes) + i);
#endif
            ptAcb->pun32OutBuf[ptAcb->un32Cnt - (AES_BYTE_LENGTH - i)] = (uint32_t)(*(volatile uint32_t *)un32AddrReg);
        }  

        SET_AES_CR_IN_FIFO_FLUSH(ptAes, true);
        SET_AES_CR_OUT_FIFO_FLUSH(ptAes, true);

        if(ptAcb->un32Cnt < ptAcb->un32Len)
        {
            for(int i = 0; i < AES_BYTE_LENGTH; i++)
            {
                SET_AES_DR_INFIFO_VAL(ptAes, ptAcb->pun32InBuf[ptAcb->un32Cnt++]);
            }
            un32Event = 0;
        }
        else
        {
            /* Done */
            ptAcb->bBusy = false;
            SET_AES_CR_EN(ptAes, false);
        }
    }

    if((ptAcb->pfnHandler != NULL) && (un32Event != 0))
    {
        ptAcb->pfnHandler(un32Event, ptAcb->pContext);
    }
}

void AES0_IRQHandler(void)
{
    PRV_AES_IRQHandler(AES_ID_0);
}

#endif /* _AES */
