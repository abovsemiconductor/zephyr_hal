/**
 *******************************************************************************
 * @file        hal_adc_f2x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F2x typed ADC
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_ADC_F2X_H_
#define _HAL_ADC_F2X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define ADC_CH_NUM                                    CONFIG_ADC_MAX_COUNT

#if (CONFIG_ADC_VER_EXT == 0)

#if (CONFIG_ADC_VER_MINOR == 0)
#include "hal_adc_f_02_00_00.h"
#elif (CONFIG_ADC_VER_MINOR == 1)
#include "hal_adc_f_02_00_01.h"
#else
#error "define CONFIG_ADC_VER_MINOR of F-type ADC at config_xxx.h"
#endif

#else
#error "define CONFIG_ADC_VER_EXT of F-type ADC at config_xxx.h"
#endif

static __inline ADC_Type *ADC_GetReg(P_ADC_ID_e eId)
{
    return (ADC_Type *)(ADC_REG_BASE + (ADC_REG_OFFSET * (uint32_t)eId));
}

static __inline HAL_ERR_e ADC_SetScuEnable(P_ADC_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_ADC_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_ADC_PER(ptScu,(uint32_t)eId,un32Enable);
    SET_SCU_ADC_PCER(ptScu,(uint32_t)eId,un32Enable);

    return HAL_ERR_OK;
}

static __inline IRQn_Type ADC_GetIRQNum(P_ADC_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(ADC_0_IRQ)
        case P_ADC_ID_0:
            eIrq = ADC_0_IRQ;
            break;
#endif
#if defined(ADC_1_IRQ)
        case P_ADC_ID_1:
            eIrq = ADC_1_IRQ;
            break;
#endif
#if defined(ADC_2_IRQ)
        case P_ADC_ID_2:
            eIrq = ADC_2_IRQ;
            break;
#endif
#if defined(ADC_3_IRQ)
        case P_ADC_ID_3:
            eIrq = ADC_3_IRQ;
            break;
#endif
#if defined(ADC_4_IRQ)
        case P_ADC_ID_4:
            eIrq = ADC_4_IRQ;
            break;
#endif
#if defined(ADC_5_IRQ)
        case P_ADC_ID_5:
            eIrq = ADC_5_IRQ;
            break;
#endif
#if defined(ADC_6_IRQ)
        case P_ADC_ID_6:
            eIrq = ADC_6_IRQ;
            break;
#endif
#if defined(ADC_7_IRQ)
        case P_ADC_ID_7:
            eIrq = ADC_7_IRQ;
            break;
#endif
#if defined(ADC_8_IRQ)
        case P_ADC_ID_8:
            eIrq = ADC_8_IRQ;
            break;
#endif
#if defined(ADC_9_IRQ)
        case P_ADC_ID_9:
            eIrq = ADC_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline HAL_ERR_e ADC_SetMccrClk(P_ADC_ID_e eId, P_ADC_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
    (void)eId;
    (void)eMccr;
    (void)un8MccrDiv;
    return HAL_ERR_NOT_SUPPORTED;
}

#if defined (ADC_FEATURE_SEQ_TRG_TYPE_SINGLE)
#define ADC_SET_SEQ_TRG_SINGLE(a, b, c, d)    ADC_SetSeqTrgSingle(a, b, c, d)
#else
#define ADC_SET_SEQ_TRG_SINGLE(a, b, c, d)    (void)0
#endif

#if defined (ADC_FEATURE_SEQ_TRG_TYPE_SHARE)
static __inline HAL_ERR_e ADC_SetSeqTrgShare(ADC_Type *ptAdc, uint32_t un32ChNum, P_ADC_TRG_e eTrg, uint8_t un8TrgNum, P_ADC_EXT_TRG_e eExtTrg)
{
    SET_ADC_CR_CH_SEL0(ptAdc, un32ChNum);
    SET_ADC_CR_SEQTRG_SRC(ptAdc, ADC_SEQTRG_SRC(eTrg, un8TrgNum)); 
    if (eTrg == ADC_TRG_SRC_EXT)
        SET_ADC_CR_SEQTRG_EXT_EDGE(ptAdc, eExtTrg);
    return HAL_ERR_OK;
}
#define ADC_SET_SEQ_TRG_SHARE(a, b, c, d, e) ADC_SetSeqTrgShare(a, b, c, d, e)
#else
#define ADC_SET_SEQ_TRG_SHARE(a, b, c, d, e)    (void)0
#endif

#if defined (ADC_FEATURE_SEQ_TRG_TYPE_INDEPENDENT)
#else
#define ADC_SET_SEQ_TRG_INDEPENDENT(a, b, c, d)    (void)0
#endif

#if defined(ADC_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void ADC_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, (uint8_t)eIrq, bEnable);
}
#endif

#endif /* _HAL_ADC_F1X_H_ */
