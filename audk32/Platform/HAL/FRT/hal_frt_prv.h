/**
 *******************************************************************************
 * @file        hal_frt_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for FRT
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_FRT_PRV_H_
#define _HAL_FRT_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_FRT_ID_0,
    P_FRT_ID_1,
    P_FRT_ID_2,
    P_FRT_ID_3,
    P_FRT_ID_4,
    P_FRT_ID_5,
    P_FRT_ID_6,
    P_FRT_ID_7,
    P_FRT_ID_8,
    P_FRT_ID_9,
    P_FRT_ID_MAX
} P_FRT_ID_e;

typedef enum
{
    P_FRT_CLK_PCLK,
    P_FRT_CLK_MCCR,
    P_FRT_CLK_MAX
} P_FRT_CLK_e;

typedef enum
{
    P_FRT_CLK_MCCR_LSI,
    P_FRT_CLK_MCCR_LSE,
    P_FRT_CLK_MCCR_MCLK,
    P_FRT_CLK_MCCR_HSI,
    P_FRT_CLK_MCCR_HSE,
    P_FRT_CLK_MCCR_PLL,
    P_FRT_CLK_MCCR_MAX
} P_FRT_CLK_MCCR_e;

#if (CONFIG_FRT_VER_VENDOR == 'V')

#if (CONFIG_FRT_VER_MAJOR == 1)
#include "Vx/V1x/hal_frt_v1x.h"
#else
#error "define CONFIG_FRT_VER_MAJOR of V-type Free Run Timer at config_xxx.h"
#endif

#else
#error "define CONFIG_FRT_VER_VENDOR of Free Run Timer at config_xxx.h"
#endif

#endif /* _HAL_FRT_PRV_H_ */
