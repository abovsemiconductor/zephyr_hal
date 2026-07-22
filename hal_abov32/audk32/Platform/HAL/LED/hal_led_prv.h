/**
 *******************************************************************************
 * @file        hal_led_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for LED
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_LED_PRV_H_
#define _HAL_LED_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_LED_ID_0,
    P_LED_ID_1,
    P_LED_ID_2,
    P_LED_ID_3,
    P_LED_ID_4,
    P_LED_ID_5,
    P_LED_ID_6,
    P_LED_ID_7,
    P_LED_ID_8,
    P_LED_ID_9,
    P_LED_ID_MAX
} P_LED_ID_e;

typedef enum
{
    P_LED_CLK_MCCR_LSI,
    P_LED_CLK_MCCR_LSE,
    P_LED_CLK_MCCR_MCLK,
    P_LED_CLK_MCCR_HSI,
    P_LED_CLK_MCCR_HSE,
    P_LED_CLK_MCCR_PLL,
    P_LED_CLK_MCCR_MAX
} P_LED_CLK_MCCR_e;

typedef enum
{
    P_LED_CLK_MCCR,
    P_LED_CLK_PCLK,
    P_LED_CLK_MAX
} P_LED_CLK_e;

#if (CONFIG_LED_VER_VENDOR == 'V')

#if (CONFIG_LED_VER_MAJOR == 1)
#include "Vx/V1x/hal_led_v1x.h"
#else /* CONFIG_LED_VER_MAJOR */
#error "define CONFIG_LED_VER_MAJOR of V-type LED at config_xxx.h"
#endif

#else /* CONFIG_LED_VER_VENDOR */
#error "define CONFIG_LED_VER_VENDOR of LED at config_xxx.h"
#endif

#endif /* _HAL_LED_PRV_H_ */
