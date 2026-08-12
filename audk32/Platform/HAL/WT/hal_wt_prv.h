/**
 *******************************************************************************
 * @file        hal_wt_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for WT
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_WT_PRV_H_
#define _HAL_WT_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_WT_ID_0,
    P_WT_ID_1,
    P_WT_ID_2,
    P_WT_ID_3,
    P_WT_ID_4,
    P_WT_ID_5,
    P_WT_ID_6,
    P_WT_ID_7,
    P_WT_ID_8,
    P_WT_ID_9,
    P_WT_ID_MAX
} P_WT_ID_e;

typedef enum
{
    P_WT_CLK_MCCR_LSI,
    P_WT_CLK_MCCR_LSE,
    P_WT_CLK_MCCR_MCLK,
    P_WT_CLK_MCCR_HSI,
    P_WT_CLK_MCCR_HSE,
    P_WT_CLK_MCCR_PLL,
    P_WT_CLK_MCCR_MAX
} P_WT_CLK_MCCR_e;

typedef enum
{
    P_WT_CLK_MCCR,
    P_WT_CLK_LSE,
    P_WT_CLK_WDTRC,
    P_WT_CLK_MAX
} P_WT_CLK_e;

#if (CONFIG_WT_VER_VENDOR == 'F')

#if (CONFIG_WT_VER_MAJOR == 1)
#include "Fx/F1x/hal_wt_f1x.h"
#else
#error "define CONFIG_WT_VER_MAJOR of F-type Watch Timer at config_xxx.h"
#endif

#else
#error "define CONFIG_WT_VER_VENDOR of Watch Timer at config_xxx.h"
#endif

#endif /* _HAL_WT_PRV_H_ */
