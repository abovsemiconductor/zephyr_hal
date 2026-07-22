/**
 *******************************************************************************
 * @file        hal_rtc_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for RTC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_RTC_PRV_H_
#define _HAL_RTC_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_RTC_ID_0,
    P_RTC_ID_1,
    P_RTC_ID_2,
    P_RTC_ID_3,
    P_RTC_ID_4,
    P_RTC_ID_5,
    P_RTC_ID_6,
    P_RTC_ID_7,
    P_RTC_ID_8,
    P_RTC_ID_9,
    P_RTC_ID_MAX
} P_RTC_ID_e;

/**
 * RTC clock source
 */
typedef enum
{
    P_RTC_CLK_LSI40KHZ,              /*<** 40KHz clock */
    P_RTC_CLK_WDTRC,                 /*<** Watch Dog Timer Clock */
    P_RTC_CLK_MCCR,                  /*<** MCCR clock */
    P_RTC_CLK_MAX
} P_RTC_CLK_e;

/**
 * RTC mccr clock source
 */
typedef enum
{
    P_RTC_CLK_MCCR_LSI,
    P_RTC_CLK_MCCR_LSE,
    P_RTC_CLK_MCCR_MCLK,
    P_RTC_CLK_MCCR_HSI,
    P_RTC_CLK_MCCR_HSE,
    P_RTC_CLK_MCCR_PLL,
    P_RTC_CLK_MCCR_MAX
} P_RTC_CLK_MCCR_e;

/**
 * RTC function
 */
typedef enum
{
    P_RTC_FUNC_WATCH,
    P_RTC_FUNC_ALARM,
    P_RTC_FUNC_TIMESTAMP,
    P_RTC_FUNC_MAX
} P_RTC_FUNC_e;

#if (CONFIG_RTC_VER_VENDOR == 'V')

#if (CONFIG_RTC_VER_MAJOR == 1)
#include "Vx/V1x/hal_rtc_v1x.h"
#else
#error "define CONFIG_RTC_VER_MAJOR of V-type RTC at config_xxx.h"
#endif

#elif (CONFIG_RTC_VER_VENDOR == 'F')

#if (CONFIG_RTC_VER_MAJOR == 1)
#include "Fx/F1x/hal_rtc_f1x.h"
#else
#error "define CONFIG_RTC_VER_MAJOR of F-type RTC at config_xxx.h"
#endif

#else
#error "define CONFIG_RTC_VER_VENDOR of RTC at config_xxx.h"
#endif

#endif /* _HAL_RTC_PRV_H_ */
