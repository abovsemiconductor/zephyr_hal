/**
 *******************************************************************************
 * @file        hal_timer4e_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for timer4e
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER4E_PRV_H_
#define _HAL_TIMER4E_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_TIMER4E_ID_0,
    P_TIMER4E_ID_1,
    P_TIMER4E_ID_2,
    P_TIMER4E_ID_3,
    P_TIMER4E_ID_4,
    P_TIMER4E_ID_5,
    P_TIMER4E_ID_6,
    P_TIMER4E_ID_7,
    P_TIMER4E_ID_8,
    P_TIMER4E_ID_9,
    P_TIMER4E_ID_MAX
} P_TIMER4E_ID_e;

typedef enum
{
    P_TIMER4E_POL_LOW,
    P_TIMER4E_POL_HIGH,
    P_TIMER4E_POL_MAX
} P_TIMER4E_POL_e;

typedef enum
{
    P_TIMER4E_PCLK_DIV_2,
    P_TIMER4E_PCLK_DIV_4,
    P_TIMER4E_PCLK_DIV_16,
    P_TIMER4E_PCLK_DIV_64,
    P_TIMER4E_PCLK_DIV_MAX
} P_TIMER4E_PCLK_DIV_e;

typedef enum
{
    P_TIMER4E_CLK_EXT,
    P_TIMER4E_CLK_PCLK,
    P_TIMER4E_CLK_MAX
} P_TIMER4E_CLK_e;

typedef enum
{
    P_TIMER4E_EXTCLK_EDGE_FALLING,
    P_TIMER4E_EXTCLK_EDGE_RISING,
    P_TIMER4E_EXTCLK_EDGE_MAX
} P_TIMER4E_EXTCLK_EDGE_e;

#if (CONFIG_TIMER4E_VER_VENDOR == 'F')

#if (CONFIG_TIMER4E_VER_MAJOR == 1)
#include "Fx/F1x/hal_timer4e_f1x.h"
#else
#error "define CONFIG_TIMER4E_VER_MAJOR of F-type Timer4E at config_xxx.h"
#endif

#else
#error "define CONFIG_TIMER4E_VER_VENDOR of Timer4E at config_xxx.h"
#endif

#endif /* _HAL_TIMER4E_PRV_H_ */
