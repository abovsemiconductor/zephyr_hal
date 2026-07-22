/**
 *******************************************************************************
 * @file        hal_timer4_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for timer4
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER4_PRV_H_
#define _HAL_TIMER4_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_TIMER4_ID_0,
    P_TIMER4_ID_1,
    P_TIMER4_ID_2,
    P_TIMER4_ID_3,
    P_TIMER4_ID_4,
    P_TIMER4_ID_5,
    P_TIMER4_ID_6,
    P_TIMER4_ID_7,
    P_TIMER4_ID_8,
    P_TIMER4_ID_9,
    P_TIMER4_ID_MAX
} P_TIMER4_ID_e;

typedef enum
{
    P_TIMER4_MODE_COUNTER,
    P_TIMER4_MODE_CAPTURE,
    P_TIMER4_MODE_ONESHOT,
    P_TIMER4_MODE_PWM,
    P_TIMER4_MODE_MAX
} P_TIMER4_MODE_e;

typedef enum
{
    P_TIMER4_POL_LOW,
    P_TIMER4_POL_HIGH,
    P_TIMER4_POL_MAX
} P_TIMER4_POL_e;

typedef enum
{
    P_TIMER4_PCLK_DIV_2,
    P_TIMER4_PCLK_DIV_4,
    P_TIMER4_PCLK_DIV_16,
    P_TIMER4_PCLK_DIV_64,
    P_TIMER4_PCLK_DIV_MAX
} P_TIMER4_PCLK_DIV_e;

typedef enum
{
    P_TIMER4_CLK_MCCR_LSI,
    P_TIMER4_CLK_MCCR_LSE,
    P_TIMER4_CLK_MCCR_MCLK,
    P_TIMER4_CLK_MCCR_HSI,
    P_TIMER4_CLK_MCCR_HSE,
    P_TIMER4_CLK_MCCR_PLL,
    P_TIMER4_CLK_MCCR_NONE,
    P_TIMER4_CLK_MCCR_MAX
} P_TIMER4_CLK_MCCR_e;

typedef enum
{
    P_TIMER4_INTR_FLAG_NONE,
    P_TIMER4_INTR_FLAG_CAP   = (1UL << 0),
    P_TIMER4_INTR_FLAG_MATCH = (1UL << 1),
    P_TIMER4_INTR_FLAG_A     = P_TIMER4_INTR_FLAG_MATCH,
    P_TIMER4_INTR_FLAG_B     = (1UL << 2),
    P_TIMER4_INTR_FLAG_OVF   = (1UL << 3),
    P_TIMER4_INTR_FLAG_MAX   = 255
} P_TIMER4_INT_FLAG_e;

typedef enum
{
    P_TIMER4_CLK_MCCR,
    P_TIMER4_CLK_EXT,
    P_TIMER4_CLK_PCLK,
    P_TIMER4_CLK_MAX
} P_TIMER4_CLK_e;

typedef enum
{
    P_TIMER4_EXTCLK_EDGE_FALLING,
    P_TIMER4_EXTCLK_EDGE_RISING,
    P_TIMER4_EXTCLK_EDGE_MAX
} P_TIMER4_EXTCLK_EDGE_e;

#if (CONFIG_TIMER4_VER_VENDOR == 'F')

#if (CONFIG_TIMER4_VER_MAJOR == 1)
#include "Fx/F1x/hal_timer4_f1x.h"
#else
#error "define CONFIG_TIMER4_VER_MAJOR of F-type Timer4 at config_xxx.h"
#endif

#else
#error "define CONFIG_TIMER4_VER_VENDOR of Timer4 at config_xxx.h"
#endif

#endif /* _HAL_TIMER4_PRV_H_ */
