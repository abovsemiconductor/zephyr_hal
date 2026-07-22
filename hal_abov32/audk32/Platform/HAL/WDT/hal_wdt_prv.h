/**
 *******************************************************************************
 * @file        hal_wdt_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for WDT
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_WDT_PRV_H_
#define _HAL_WDT_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_WDT_ID_0,
    P_WDT_ID_1,
    P_WDT_ID_2,
    P_WDT_ID_3,
    P_WDT_ID_4,
    P_WDT_ID_5,
    P_WDT_ID_6,
    P_WDT_ID_7,
    P_WDT_ID_8,
    P_WDT_ID_9,
    P_WDT_ID_MAX
} P_WDT_ID_e;

typedef enum
{
    P_WDT_CLK_MCCR_LSI,
    P_WDT_CLK_MCCR_LSE,
    P_WDT_CLK_MCCR_MCLK,
    P_WDT_CLK_MCCR_HSI,
    P_WDT_CLK_MCCR_HSE,
    P_WDT_CLK_MCCR_PLL,
    P_WDT_CLK_MCCR_MAX
} P_WDT_CLK_MCCR_e;

typedef enum
{
    P_WDT_CLK_WDTRC,
    P_WDT_CLK_MCCR,
    P_WDT_CLK_PCLK,
    P_WDT_CLK_MAX
} P_WDT_CLK_e;

#if (CONFIG_WDT_VER_VENDOR == 'F')

#if (CONFIG_WDT_VER_MAJOR == 1)
#include "Fx/F1x/hal_wdt_f1x.h"
#else
#error "define CONFIG_WDT_VER_MAJOR of F-type WDT at config_xxx.h"
#endif

#elif (CONFIG_WDT_VER_VENDOR == 'V')

#if (CONFIG_WDT_VER_MAJOR == 1)
#include "Vx/V1x/hal_wdt_v1x.h"
#else
#error "define CONFIG_WDT_VER_MAJOR of V-type WDT at config_xxx.h"
#endif

#else
#error "define CONFIG_WDT_VER_VENDOR of WDT at config_xxx.h"
#endif

#endif /* _HAL_WDT_PRV_H_ */
