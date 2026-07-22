/**
 *******************************************************************************
 * @file        hal_adc_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ADC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_ADC_PRV_H_
#define _HAL_ADC_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_ADC_ID_0,
    P_ADC_ID_1,
    P_ADC_ID_2,
    P_ADC_ID_3,
    P_ADC_ID_4,
    P_ADC_ID_5,
    P_ADC_ID_6,
    P_ADC_ID_7,
    P_ADC_ID_8,
    P_ADC_ID_9,
    P_ADC_ID_MAX
} P_ADC_ID_e;

typedef enum
{
    P_ADC_CLK_MCCR_LSI,
    P_ADC_CLK_MCCR_LSE,
    P_ADC_CLK_MCCR_MCLK,
    P_ADC_CLK_MCCR_HSI,
    P_ADC_CLK_MCCR_HSE,
    P_ADC_CLK_MCCR_PLL,
    P_ADC_CLK_MCCR_MAX
} P_ADC_CLK_MCCR_e;

typedef enum
{
    P_ADC_TRG_ADST,     /**< A/DC Conversion Start bit */
    P_ADC_TRG_TIMER1,   /**< Timer1 Trigger signal */
    P_ADC_TRG_TIMER2,   /**< Timer2 Trigger signal */
    P_ADC_TRG_TIMER3,   /**< Timer3 Trigger signal */
    P_ADC_TRG_TIMER4,   /**< Timer4 Trigger signal */
    P_ADC_TRG_TIMER4E = P_ADC_TRG_TIMER4,   /**< Timer4 Trigger signal */
    P_ADC_TRG_MPWM0,    /**< MPWM0 Trigger signal */
    P_ADC_TRG_MPWM1,    /**< MPWM1 Trigger signal */
    P_ADC_TRG_EXT,      /**< External Trigger signal */
    P_ADC_TRG_NONE,     /**< Disable Trigger source */
    P_ADC_TRG_MAX
} P_ADC_TRG_e;

typedef enum
{
    P_ADC_EXT_TRG_NONE,    /**< Disable External Trigger */
    P_ADC_EXT_TRG_FALL,    /**< Falling Edge Trigger */
    P_ADC_EXT_TRG_RISE,    /**< Rising Edge Trigger */
    P_ADC_EXT_TRG_BOTH,    /**< Falling and Rising Edge Trigger */
    P_ADC_EXT_TRG_MAX
} P_ADC_EXT_TRG_e;

#if (CONFIG_ADC_VER_VENDOR == 'F')

#if (CONFIG_ADC_VER_MAJOR == 1)
#include "Fx/F1x/hal_adc_f1x.h"
#elif (CONFIG_ADC_VER_MAJOR == 2)
#include "Fx/F2x/hal_adc_f2x.h"
#else
#error "define CONFIG_ADC_VER_MAJOR of F-type ADC at config_xxx.h"
#endif

#elif (CONFIG_ADC_VER_VENDOR == 'V')

#if (CONFIG_ADC_VER_MAJOR == 1)
#include "Vx/V1x/hal_adc_v1x.h"
#else
#error "define CONFIG_ADC_VER_MAJOR of V-type ADC at config_xxx.h"
#endif

#else
#error "define CONFIG_ADC_VER_VENDOR of ADC at config_xxx.h"
#endif

#endif /* _HAL_ADC_PRV_H_ */
