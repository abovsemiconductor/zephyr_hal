/**
 *******************************************************************************
 * @file        hal_adc.c
 * @author      ABOV R&D Division
 * @brief       N-bits Analog to Digital Converter
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

#if defined(_ADC)
#include "hal_adc.h"
#include "hal_adc_prv.h"

#if defined(_DMAC) && defined(DMA_ADC_NUM)
#include "hpl_dma.h"
#endif

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
#include "hpl_nmi.h"
#endif

#define ADC_PRE_INIT_SEQ_TIMEOUT    100000

typedef struct
{
    /* Interrupt and DMA */
    ADC_OPS_e               eOps;
    pfnADC_IRQ_Handler_t    pfnHandler;
    void                    *pContext;
#if defined(_DMAC) && defined(DMA_ADC_NUM)
    DMA_ID_e                eDmaId;
    bool                    bDmaEnabled;
#endif

    ADC_MODE_e              eMode;
    ADC_TRG_SRC_e           eTrgSrc;
    bool                    bAutoRestart;

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
    bool                    bNmiEnable;
#endif

} ADC_CTRL_BLK_t;

static ADC_CTRL_BLK_t s_tAcb[ADC_CH_NUM];

static void PRV_ADC_IRQHandler(ADC_ID_e eId);

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
static void PRV_ADC_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < ADC_CH_NUM; i++)
    {
        if(s_tAcb[i].bNmiEnable == true)
        {
            PRV_ADC_IRQHandler((ADC_ID_e)i);
        }
    }
}
#endif

static ADC_Type *PRV_ADC_GetReg(P_ADC_ID_e eId)
{
    return ADC_GetReg((P_ADC_ID_e)eId);
}

static HAL_ERR_e PRV_ADC_SetScuEnable(P_ADC_ID_e eId, bool bEnable)
{
    return ADC_SetScuEnable((P_ADC_ID_e)eId, bEnable);
}

#if defined(_DMAC) && defined(DMA_ADC_NUM) && defined (ADC_FEATURE_DMA_INTERNAL_INTERRUPT)
static void PRV_ADC_DMAHandler(uint32_t un32Event, void *pContext)
{
    PRV_ADC_IRQHandler((ADC_ID_e)(un32Event));
}
#endif

#if defined(ADC_FEATURE_V1X_PRE_INIT)
static HAL_ERR_e PRV_ADC_PreInit(P_ADC_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    ADC_Type *ptAdc;
    uint32_t un32Timeout = ADC_PRE_INIT_SEQ_TIMEOUT;
    uint32_t un32Status = 0;
    
    ptAdc = PRV_ADC_GetReg((P_ADC_ID_e)eId);

    /* ADC block enable */
    SET_ADC_CR_EN(ptAdc, true);

    /* Powerdown disable */
    SET_ADC_CR_ADCPD(ptAdc, false);

    /* Peri clock select */
    SET_ADC_CR_EXTCLK(ptAdc, 0x00);
    SET_ADC_CR_PCLKINV(ptAdc, 0x00);
    SET_ADC_DR_PREDIV(ptAdc, 0x02);
#if defined(ADC_FEATURE_INPUT_MODE)
    SET_ADC_CR_INMODE_SEL(ptAdc, true);
#endif

    /* Burst mode */
    SET_ADC_CR_MODE(ptAdc, ADC_MODE_SEL(ADC_MODE_BURST));

    /* Max sequence count */
    SET_ADC_CR_SEQCNT(ptAdc, (ADC_MAX_SEQUENCE-1));

    SET_ADC_CR_START(ptAdc, true);

    while(!GET_ADC_IER_SEQ_FLAG(ptAdc))
    {
        un32Timeout--;
        if(un32Timeout == 0)
        {
            eErr = HAL_ERR_TIMEOUT;
            break;
        }
    }

    un32Status = GET_ADC_IER_FLAG(ptAdc); 
    SET_ADC_IER_FLAG(ptAdc, un32Status);

    return eErr;
}
#endif

#if defined(_DMAC) && defined(DMA_ADC_NUM)
static HAL_ERR_e PRV_ADC_SetDMA(ADC_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    ADC_CTRL_BLK_t *ptAcb;
    DMA_ID_e eDmaId;

    ptAcb = &s_tAcb[(uint32_t)eId];

    eErr = HPL_DMA_Init(DMA_PERI_ADC, (uint8_t)eId);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    eErr = (HAL_ERR_e)HPL_DMA_GetAvailChannel(&eDmaId);
    if(eErr == HAL_ERR_OK)
    {
        ptAcb->eDmaId = eDmaId;
        ptAcb->bDmaEnabled = true;
    }

#if defined (ADC_FEATURE_DMA_INTERNAL_INTERRUPT)
    eErr = HPL_DMA_SetIRQ(DMA_PERI_ADC, &PRV_ADC_DMAHandler, NULL, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }
#endif

    return eErr;
}
#endif

HAL_ERR_e HAL_ADC_Init(ADC_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= ADC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_ADC_SetScuEnable((P_ADC_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tAcb[(uint32_t)eId], 0, sizeof(ADC_CTRL_BLK_t));

#if defined(ADC_FEATURE_V1X_PRE_INIT)
    /* ADC block should be initialized by executing the burst mode once. */
    eErr = PRV_ADC_PreInit((P_ADC_ID_e)eId);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }
#else
    {
        ADC_Type *ptAdc;
        ptAdc = PRV_ADC_GetReg((P_ADC_ID_e)eId);
        /* ADC block enable */
        SET_ADC_CR_EN(ptAdc, true);
    }
#endif

    return eErr;
}

HAL_ERR_e HAL_ADC_Uninit(ADC_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    ADC_Type *ptAdc;
    IRQn_Type eIrq;

    if((uint32_t)eId >= ADC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAdc = PRV_ADC_GetReg((P_ADC_ID_e)eId);
    SET_ADC_CR_EN(ptAdc, false);

    eErr = PRV_ADC_SetScuEnable((P_ADC_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = ADC_GetIRQNum((P_ADC_ID_e)eId);
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
    (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
#endif
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tAcb[(uint32_t)eId], 0, sizeof(ADC_CTRL_BLK_t));

    return eErr;
}

HAL_ERR_e HAL_ADC_SetClkConfig(ADC_ID_e eId, ADC_CLK_CFG_t *ptClkCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    ADC_Type *ptAdc;

    if((uint32_t)eId >= ADC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAdc = PRV_ADC_GetReg((P_ADC_ID_e)eId);

    if(ptClkCfg->eClk == ADC_CLK_MCCR)
    {
#if defined(ADC_FEATURE_MCCR_CLOCK)
        SET_ADC_DR_PREDIV(ptAdc, 0x00);
        SET_ADC_CR_EXTCLK(ptAdc, 0x01);
        eErr = ADC_SetMccrClk((P_ADC_ID_e)eId, (P_ADC_CLK_MCCR_e)ptClkCfg->eMccr, ptClkCfg->un8MccrDiv);
#else
        eErr = HAL_ERR_NOT_SUPPORTED;
#endif
    }
    else
    {
        SET_ADC_CR_EXTCLK(ptAdc, 0x00);
        SET_ADC_CR_PCLKINV(ptAdc, ptClkCfg->bPClkInv);
        SET_ADC_DR_PREDIV(ptAdc, ptClkCfg->un8PClkDiv);
    }

    return eErr;
}

HAL_ERR_e HAL_ADC_SetConfig(ADC_ID_e eId, ADC_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    ADC_Type *ptAdc;
    ADC_CTRL_BLK_t *ptAcb;

    if((uint32_t)eId >= ADC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAdc = PRV_ADC_GetReg((P_ADC_ID_e)eId);
    ptAcb = &s_tAcb[(uint32_t)eId];

    if(ptCfg->eRef == ADC_REF_EXT && !ADC_EXTERNAL_PIN)
    {
        return HAL_ERR_NOT_SUPPORTED;
    }

    if(ptCfg->eMode != ADC_MODE_SINGLE && !ADC_MODE_ONLY_SINGLE)
    {
        return HAL_ERR_NOT_SUPPORTED;
    }

    SET_ADC_CR_ADCPD(ptAdc, ptCfg->bSleep);

    SET_ADC_CR_REF(ptAdc, ptCfg->eRef);

    SET_ADC_CR_MODE(ptAdc, ADC_MODE_SEL(ptCfg->eMode));

    SET_ADC_DR_SAMPLETIME(ptAdc, ptCfg->un8SamplingTime);
    SET_ADC_CR_SEQCNT(ptAdc, (uint8_t)(ptCfg->un8SeqCnt));
    SET_ADC_CR_CHINFO(ptAdc, ptCfg->bChInfo);
    SET_ADC_CR_TRGINFO(ptAdc, ptCfg->bTrgInfo);

    SET_ADC_CR_TRG_SRC(ptAdc, ADC_TRG_SRC(ptCfg->eBaseTrgSrc));

    SET_ADC_CR_ARST(ptAdc, ptCfg->bAutoRestart);

    SET_ADC_CR_TRG_CLR(ptAdc, true);

    ptAcb->eMode = ptCfg->eMode;

    return eErr;
}

HAL_ERR_e HAL_ADC_SetIRQ(ADC_ID_e eId, ADC_OPS_e eOps, pfnADC_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    ADC_CTRL_BLK_t *ptAcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= ADC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(eOps == ADC_OPS_INTR_DMA)
    {
#if defined(_DMAC) && defined(DMA_ADC_NUM)
#else
        return HAL_ERR_NOT_SUPPORTED;
#endif
    }

    ptAcb = &s_tAcb[(uint32_t)eId];
    eIrq = ADC_GetIRQNum((P_ADC_ID_e)eId);

    switch(eOps)
    {
        case ADC_OPS_INTR:
        case ADC_OPS_INTR_DMA:
#if defined(ADC_FEATURE_IRQ_UNMASK_ENABLE)
            ADC_SetIntrUnMask(eIrq, true);
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
#if defined(_DMAC) && defined(DMA_ADC_NUM)
            if(eOps == ADC_OPS_INTR_DMA)
            {
                eErr = PRV_ADC_SetDMA(eId);
            }
#endif
            break;
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
        case ADC_OPS_NMI:
        case ADC_OPS_NMI_DMA:
#if defined(ADC_FEATURE_IRQ_UNMASK_ENABLE)
            ADC_SetIntrUnMask(eIrq, true);
#endif
            eErr = HPL_NMI_SetSource(eIrq, &PRV_ADC_NMIHandler, pContext, true);
            if(eErr == HAL_ERR_OK)
            {
                ptAcb->pfnHandler = pfnHandler;
                ptAcb->pContext = pContext;
            }
            ptAcb->bNmiEnable = true;
#if defined(_DMAC) && defined(DMA_ADC_NUM)
            if(eOps == ADC_OPS_NMI_DMA)
            {
                eErr = PRV_ADC_SetDMA(eId);
            }
#endif
            break;
#endif
        case ADC_OPS_POLL:
        default:
#if defined(ADC_FEATURE_IRQ_UNMASK_ENABLE)
            ADC_SetIntrUnMask(eIrq, false);
#endif
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
            ptAcb->bNmiEnable = false;
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
#if defined(_DMAC) && defined(DMA_ADC_NUM)
            if(ptAcb->bDmaEnabled == true)
            {
                eErr = PRV_ADC_SetDMA(eId);
            }
#endif
            ptAcb->pContext = NULL;
            ptAcb->pfnHandler = NULL;
            break;
    }

    ptAcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_ADC_SetDMA(ADC_ID_e eId, uint32_t un32Addr, uint32_t un32Len)
{
#if defined(_DMAC) && defined(DMA_ADC_NUM)
    HAL_ERR_e eErr = HAL_ERR_OK;
    ADC_Type *ptAdc;
    ADC_CTRL_BLK_t *ptAcb;
    DMA_CFG_t tDmaCfg =
    {
        .ePeri = DMA_PERI_ADC,
        .ePeriId = (DMA_PERI_ID_e)eId,
        .un32PeriNum = 0,
        .eSize = DMA_BUS_SIZE_HALFWORD,
        .eDir = DMA_DIR_PERI_TO_MEM
    };

    if((uint32_t)eId >= ADC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAdc = PRV_ADC_GetReg((P_ADC_ID_e)eId);
    ptAcb = &s_tAcb[(uint32_t)eId];

    eErr = (HAL_ERR_e)HPL_DMA_GetPeriSelectNumber(DMA_PERI_ADC, (DMA_PERI_ID_e)eId, DMA_PERI_COM_RX, &tDmaCfg.un32PeriNum);
    if(eErr == HAL_ERR_OK)
    {
        HPL_DMA_SetConfig(ptAcb->eDmaId, &tDmaCfg);
        SET_ADC_CR_DMA_EN(ptAdc, true);
        SET_ADC_IER_DMA_EN(ptAdc, true);
        HPL_DMA_Start(ptAcb->eDmaId, (uint32_t)GET_ADC_DR_DDR_ADDR(ptAdc), un32Addr, un32Len);
    }

    return eErr;
#else
    (void)eId;
    (void)un32Addr;
    (void)un32Len;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_ADC_Start(ADC_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    ADC_Type *ptAdc;
    ADC_CTRL_BLK_t *ptAcb;

    if((uint32_t)eId >= ADC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAdc = PRV_ADC_GetReg((P_ADC_ID_e)eId);
    ptAcb = &s_tAcb[(uint32_t)eId];

    SET_ADC_IER_SINGLE_FLAG(ptAdc, false);
    SET_ADC_IER_SEQ_FLAG(ptAdc, false);
    SET_ADC_IER_TRG_FLAG(ptAdc, false);
#if defined (ADC_FEATURE_OVERRUN_INTR)
    SET_ADC_IER_OVR_EN(ptAdc, false);
#endif
#if defined (ADC_FEATURE_STABLE_INTR)
    SET_ADC_IER_STB_EN(ptAdc, false);
#endif

    if(ptAcb->eOps == ADC_OPS_POLL)
    {
        SET_ADC_IER_SINGLE_EN(ptAdc, false);
        SET_ADC_IER_SEQ_EN(ptAdc, false);
        SET_ADC_IER_TRG_EN(ptAdc, false);
#if defined (ADC_FEATURE_OVERRUN_INTR)
        SET_ADC_IER_OVR_EN(ptAdc, false);
#endif
#if defined (ADC_FEATURE_STABLE_INTR)
        SET_ADC_IER_STB_EN(ptAdc, false);
#endif
    }
    else
    {
        SET_ADC_IER_SINGLE_EN(ptAdc, true);
        SET_ADC_IER_SEQ_EN(ptAdc, true);
        SET_ADC_IER_TRG_EN(ptAdc, true);
#if defined (ADC_FEATURE_OVERRUN_INTR)
        SET_ADC_IER_OVR_EN(ptAdc, true);
#endif
#if defined (ADC_FEATURE_STABLE_INTR)
        SET_ADC_IER_STB_EN(ptAdc, true);
#endif
    }

#if defined (ADC_FEATURE_READY_BIT)
    SET_ADC_CR_READY(ptAdc, true);
#endif

    SET_ADC_CR_START(ptAdc, true);

    return eErr;
}

HAL_ERR_e HAL_ADC_Stop(ADC_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    ADC_Type *ptAdc;
    ADC_CTRL_BLK_t *ptAcb;

    if((uint32_t)eId >= ADC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAdc = PRV_ADC_GetReg((P_ADC_ID_e)eId);
    ptAcb = &s_tAcb[(uint32_t)eId];

    SET_ADC_CR_ARST(ptAdc, false);

#if defined (ADC_FEATURE_READY_BIT)
    SET_ADC_CR_READY(ptAdc, false);
#endif

    if(ptAcb->eTrgSrc == ADC_TRG_SRC_ADST)
    {
        SET_ADC_CR_STOP(ptAdc, false);
    }

    if(ptAcb->eOps == ADC_OPS_INTR || ptAcb->eOps == ADC_OPS_INTR_DMA
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
       || ptAcb->eOps == ADC_OPS_NMI || ptAcb->eOps == ADC_OPS_NMI_DMA
#endif

      )
    {
        SET_ADC_IER_SINGLE_EN(ptAdc, false);
        SET_ADC_IER_SEQ_EN(ptAdc, false);
        SET_ADC_IER_TRG_EN(ptAdc, false);
#if defined (ADC_FEATURE_OVERRUN_INTR)
        SET_ADC_IER_OVR_EN(ptAdc, false);
#endif
#if defined (ADC_FEATURE_STABLE_INTR)
        SET_ADC_IER_STB_EN(ptAdc, false);
#endif
#if defined(_DMAC) && defined(DMA_ADC_NUM)
        SET_ADC_IER_DMA_EN(ptAdc, false);
        SET_ADC_CR_DMA_EN(ptAdc, false);
        if(ptAcb->eOps == ADC_OPS_INTR_DMA)
        {
            HPL_DMA_Stop(ptAcb->eDmaId);
        }
#endif
    }

    return eErr;
}

HAL_ERR_e HAL_ADC_SetWaitComplete(ADC_ID_e eId, uint32_t un32Timeout)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    ADC_Type *ptAdc;

    if((uint32_t)eId >= ADC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAdc = PRV_ADC_GetReg((P_ADC_ID_e)eId);

    while(!GET_ADC_IER_SINGLE_FLAG(ptAdc))
    {
        un32Timeout--;
        if(un32Timeout == 0)
        {
            eErr = HAL_ERR_TIMEOUT;
            break;
        }
    }

    SET_ADC_IER_SINGLE_FLAG(ptAdc, false);

    return eErr;
}

HAL_ERR_e HAL_ADC_GetData(ADC_ID_e eId, uint8_t un8SeqNum, ADC_SEQ_DATA_t *ptData)
{
    ADC_Type *ptAdc;
    uint32_t un32DataReg;

    if((uint32_t)eId >= ADC_CH_NUM || un8SeqNum >= ADC_MAX_SEQUENCE)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAdc = PRV_ADC_GetReg((P_ADC_ID_e)eId);

    if(ptData->bReadDDR == true)
    {
#if defined (_DMAC) && defined(DMA_ADC_NUM)
        un32DataReg = (uint32_t)GET_ADC_DR_DDR_ADDR(ptAdc);
#else
        return HAL_ERR_NOT_SUPPORTED;
#endif
    }
    else
    {
        un32DataReg = (uint32_t)GET_ADC_DR_BASE_ADDR(ptAdc) + (un8SeqNum * 4);
    }

    ptData->un16Result = GET_ADC_DR_OUT(un32DataReg);
    ptData->un8ChInfo = GET_ADC_DR_CHINFO(un32DataReg);
    ptData->un8TrgInfo = GET_ADC_DR_TRGINFO(un32DataReg);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_ADC_SetSeqConfig(ADC_ID_e eId, ADC_SEQ_TRG_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    ADC_Type *ptAdc;
    ADC_CTRL_BLK_t *ptAcb;

    if((uint32_t)eId >= ADC_CH_NUM || ptCfg == NULL)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAdc = PRV_ADC_GetReg((P_ADC_ID_e)eId);
    ptAcb = &s_tAcb[(uint32_t)eId];

    switch(ptCfg->eType)
    {
#if defined (ADC_FEATURE_SEQ_TRG_TYPE_SINGLE)
        case ADC_TRG_TYPE_SINGLE:
            eErr = ADC_SET_SEQ_TRG_SINGLE(ptAdc, ptCfg->utCfg.tSgl.un8ChNum, (P_ADC_TRG_e)ptCfg->eTrgSrc, ptCfg->un8TrgNum);
            break;
#elif defined (ADC_FEATURE_SEQ_TRG_TYPE_SHARE)
        case ADC_TRG_TYPE_SHARE:
            eErr = ADC_SET_SEQ_TRG_SHARE(ptAdc, ptCfg->utCfg.tShe.un32ChNum, (P_ADC_TRG_e)ptCfg->eTrgSrc, ptCfg->un8TrgNum, (P_ADC_EXT_TRG_e)ptCfg->utCfg.tShe.eExtTrg);
            break;
#elif defined (ADC_FEATURE_SEQ_TRG_TYPE_INDEPENDENT)
        case ADC_TRG_TYPE_INDEPENDENT:
            eErr = ADC_SET_SEQ_TRG_INDEPENDENT(ptAdc, ptCfg->utCfg.tInd.un8SeqNum, ptCfg->utCfg.tInd.un8ChNum, ptCfg->utCfg.tInd.un8SamplingTime, (P_ADC_TRG_e)ptCfg->eTrgSrc, ptCfg->un8TrgNum);
            break;
#endif
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    ptAcb->eTrgSrc = ptCfg->eTrgSrc;

    return eErr;
}

HAL_ERR_e HAL_ADC_SetCmpConfig(ADC_ID_e eId, ADC_CMP_CFG_t *ptCfg)
{
#if defined(ADC_FEATURE_COMPARATOR)
    HAL_ERR_e eErr = HAL_ERR_OK;
    ADC_Type *ptAdc;

    if((uint32_t)eId >= ADC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAdc = PRV_ADC_GetReg((P_ADC_ID_e)eId);

    SET_ADC_CR_CMP_EN(ptAdc, eId, ptCfg->bEnable);

    if(ptCfg->bEnable == true)
    {
        SET_ADC_IER_CMP_EN(ptAdc, eId, ptCfg->bIntrEnable);
        SET_ADC_CR_CMP_TRG(ptAdc, eId, ptCfg->bIntrTrg);
        SET_ADC_CR_CMP_CH(ptAdc, eId, ptCfg->un8ChNum);
        SET_ADC_DR_CMP(ptAdc, eId, ptCfg->un16Data);
    }

    return eErr;
#else
    (void)eId;
    (void)*ptCfg;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_ADC_SetBufDlyConfig(ADC_ID_e eId, ADC_BUF_DLY_CFG_t *ptCfg)
{
#if defined(ADC_FEATURE_BUFFER_DELAY)
    HAL_ERR_e eErr = HAL_ERR_OK;
    ADC_Type *ptAdc;

    if((uint32_t)eId >= ADC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAdc = PRV_ADC_GetReg((P_ADC_ID_e)eId);

    SET_ADC_CR_BUF_DLY_EN(ptAdc, ptCfg->bEnable);
    SET_ADC_CR_BUF_DLY_SEL(ptAdc, ptCfg->un8Delay);
    SET_ADC_CR_BUF_DLY_BYPASS(ptAdc, ptCfg->bBypass);

    return eErr;
#else
    (void)eId;
    (void)*ptCfg;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_ADC_SetOVSConfig(ADC_ID_e eId, ADC_OVS_CFG_t *ptCfg)
{
#if defined(ADC_FEATURE_HAS_OVER_SAMPLING)
    HAL_ERR_e eErr = HAL_ERR_OK;
    ADC_Type *ptAdc;

    if((uint32_t)eId >= ADC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAdc = PRV_ADC_GetReg((P_ADC_ID_e)eId);

    SET_ADC_CR_OVS_EN(ptAdc, ptCfg->bEnable);
    SET_ADC_CR_OVS_RATIO(ptAdc, ptCfg->un8Ratio);
    SET_ADC_CR_OVS_DATA_SHIFT(ptAdc, ptCfg->un8DataShift);

    return eErr;
#else
    (void)eId;
    (void)*ptCfg;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

uint32_t HAL_ADC_GetMaxResolution(void)
{
    return ADC_RESOLUTION;
}

static void PRV_ADC_IRQHandler(ADC_ID_e eId)
{
    ADC_Type *ptAdc;
    ADC_CTRL_BLK_t *ptAcb;
    uint32_t un32Event = 0;
    uint32_t un32Status = 0;

    ptAdc = PRV_ADC_GetReg((P_ADC_ID_e)eId);
    ptAcb = &s_tAcb[(uint32_t)eId];

#if defined(_DMAC) && defined(DMA_ADC_NUM)
#if defined (ADC_FEATURE_DMA_INTERNAL_INTERRUPT)
    if (ptAcb->eOps == ADC_OPS_INTR_DMA)
    {
        un32Event |= ADC_EVENT_SINGLE_CAPTURED;
        goto done;
    }
#else
#endif
#endif

    un32Status = GET_ADC_IER_FLAG(ptAdc); 
    SET_ADC_IER_FLAG(ptAdc, un32Status);

    if(un32Status & BIT_ADC_IER_SINGLE_FLAG)
    {
        un32Event |= ADC_EVENT_SINGLE_CAPTURED;
    }

    if(un32Status & BIT_ADC_IER_SEQ_FLAG)
    {
        un32Event |= ADC_EVENT_BURST_CAPTURED;
    }

    if(un32Status & BIT_ADC_IER_TRG_FLAG)
    {
        un32Event |= ADC_EVENT_CONVERSION_TRIGGER;
    }

    if(un32Status & BIT_ADC_IER_CMP_FLAG(eId))
    {
        un32Event |= ADC_EVENT_COMPARE_MATCHED;
    }

#if defined(_DMAC) && defined(DMA_ADC_NUM)
#if defined (ADC_FEATURE_DMA_INTERNAL_INTERRUPT)
done:
#endif
#endif

    if(ptAcb->pfnHandler != NULL && un32Event != 0)
    {
        ptAcb->pfnHandler(un32Event, ptAcb->pContext);
    }
}

void ADC0_IRQHandler(void)
{
    PRV_ADC_IRQHandler(ADC_ID_0);
}

void ADC1_IRQHandler(void)
{
    PRV_ADC_IRQHandler(ADC_ID_1);
}

void ADC2_IRQHandler(void)
{
    PRV_ADC_IRQHandler(ADC_ID_2);
}

#endif /* _ADC */
