/**
 *******************************************************************************
 * @file        hal_adc_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed ADC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_ADC_V1X_H_
#define _HAL_ADC_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define ADC_CH_NUM                                    CONFIG_ADC_MAX_COUNT

#if (CONFIG_ADC_VER_EXT == 0)

#if (CONFIG_ADC_VER_MINOR == 0)
#include "hal_adc_v_01_00_00.h"
#elif (CONFIG_ADC_VER_MINOR == 1)
#include "hal_adc_v_01_00_01.h"
#elif (CONFIG_ADC_VER_MINOR == 2)
#include "hal_adc_v_01_00_02.h"
#elif (CONFIG_ADC_VER_MINOR == 3)
#include "hal_adc_v_01_00_03.h"
#elif (CONFIG_ADC_VER_MINOR == 4)
#include "hal_adc_v_01_00_04.h"
#elif (CONFIG_ADC_VER_MINOR == 5)
#include "hal_adc_v_01_00_05.h"
#elif (CONFIG_ADC_VER_MINOR == 6)
#include "hal_adc_v_01_00_06.h"
#else
#error "define CONFIG_ADC_VER_MINOR of V-type ADC at config_xxx.h"
#endif

#elif (CONFIG_ADC_VER_EXT == 1)

#if (CONFIG_ADC_VER_MINOR == 0)
#include "hal_adc_v_01_01_00.h"
#elif (CONFIG_ADC_VER_MINOR == 1)
#include "hal_adc_v_01_01_01.h"
#else
#error "define CONFIG_ADC_VER_MINOR of V-type ADC at config_xxx.h"
#endif

#elif (CONFIG_ADC_VER_EXT == 2)

#if (CONFIG_ADC_VER_MINOR == 0)
#include "hal_adc_v_01_02_00.h"
#else
#error "define CONFIG_ADC_VER_MINOR of V-type ADC at config_xxx.h"
#endif


#elif (CONFIG_ADC_VER_EXT == 3)

#if (CONFIG_ADC_VER_MINOR == 0)
#include "hal_adc_v_01_03_00.h"
#else
#error "define CONFIG_ADC_VER_MINOR of V-type ADC at config_xxx.h"
#endif

#else
#error "define CONFIG_ADC_VER_EXT of V-type ADC at config_xxx.h"
#endif

/* Feature(Function) Global Configuration Define */
#define ADC_FEATURE_V1X_PRE_INIT

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

    SET_SCU_ADC_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_ADC_PCER(ptScu, (uint32_t)eId, un32Enable);

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
#if defined(ADC_FEATURE_MCCR_CLOCK)
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_ADC_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_ADC_MCCR_SEL(ptScu, ADC_MCCR_CLK(eMccr));
    SET_SCU_ADC_MCCR_DIV(ptScu, un8MccrDiv);
    return HAL_ERR_OK;
#else
    (void)eId;
    (void)eMccr;
    (void)un8MccrDiv;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}


#if defined (ADC_FEATURE_SEQ_TRG_TYPE_SINGLE)
static __inline HAL_ERR_e ADC_SetSeqTrgSingle(P_ADC_ID_e eId, uint8_t un8ChNum, P_ADC_TRG_e eTrg, uint8_t un8TrgNum)
{

}
#define ADC_SET_SEQ_TRG_SINGLE(a, b, c, d)    ADC_SetSeqTrgSingle(a, b, c, d)
#else
#define ADC_SET_SEQ_TRG_SINGLE(a, b, c, d)    (void)0
#endif

#if defined (ADC_FEATURE_SEQ_TRG_TYPE_SHARE)
static __inline HAL_ERR_e ADC_SetSeqTrgShare(P_ADC_ID_e eId, uint8_t un8ChNum, P_ADC_TRG_e eTrg, uint8_t un8TrgNum)
{

}
#define ADC_SET_SEQ_TRG_SHARE(a, b, c, d)     ADC_SetSeqTrgShare(a, b, c, d)
#else
#define ADC_SET_SEQ_TRG_SHARE(a, b, c, d)    (void)0
#endif

#if defined (ADC_FEATURE_SEQ_TRG_TYPE_INDEPENDENT)
static __inline HAL_ERR_e ADC_SetSeqTrgIndependent(ADC_Type *ptAdc, uint8_t un8SeqNum, uint8_t un8ChNum, uint8_t un8SamplingTime, P_ADC_TRG_e eTrg, uint8_t un8TrgNum)
{
#if defined (ADC_FEATURE_SEQUENCE_8_OVER)
    SET_ADC_CR_CH_SEL(GET_ADC_SCSR_BASE_ADDR(ptAdc), un8SeqNum, un8ChNum);
    SET_ADC_CR_SEQTRG_SRC(GET_ADC_TRG_BASE_ADDR(ptAdc), un8SeqNum, ADC_SEQTRG_SRC(eTrg, un8TrgNum));
#else
    if(un8SeqNum < 4)
    {
        SET_ADC_CR_CH_SEL0(ptAdc, un8ChNum, un8SeqNum*ADC_SEQ_CH_OFFSET);
    }
    else
    {
        SET_ADC_CR_CH_SEL1(ptAdc, un8ChNum, (un8SeqNum-ADC_SEQ_OFFSET)*ADC_SEQ_CH_OFFSET);
    }
    SET_ADC_CR_SEQTRG_SRC(ptAdc, ADC_SEQTRG_SRC(eTrg, un8TrgNum), ADC_SEQTRG_OFFSET(un8SeqNum));
#endif

#if defined(ADC_FEATURE_SEQ_SAMPLING_TIME_INDEPENDENT)
    SET_ADC_CSTR_SEQCH_SAMPLING((uint32_t)GET_ADC_CSTR_BASE_ADDR(ptAdc), un8SeqNum, un8SamplingTime);
#endif
    return HAL_ERR_OK;
}
#define ADC_SET_SEQ_TRG_INDEPENDENT(a, b, c, d, e, f)     ADC_SetSeqTrgIndependent(a, b, c, d, e, f)
#else
#define ADC_SET_SEQ_TRG_INDEPENDENT(a, b, c, d, e, f)    (void)0
#endif

#endif /* _HAL_ADC_V1X_H_ */
