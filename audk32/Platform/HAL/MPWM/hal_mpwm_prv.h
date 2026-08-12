/**
 *******************************************************************************
 * @file        hal_mpwm_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for MPWM
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_MPWM_PRV_H_
#define _HAL_MPWM_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_MPWM_ID_0,
    P_MPWM_ID_1,
    P_MPWM_ID_2,
    P_MPWM_ID_3,
    P_MPWM_ID_4,
    P_MPWM_ID_5,
    P_MPWM_ID_6,
    P_MPWM_ID_7,
    P_MPWM_ID_8,
    P_MPWM_ID_9,
    P_MPWM_ID_MAX
} P_MPWM_ID_e;

typedef enum
{
    P_MPWM_POL_LOW,
    P_MPWM_POL_HIGH,
    P_MPWM_POL_MAX
} P_MPWM_POL_e;

typedef enum
{
    P_MPWM_CLK_MCCR_LSI,
    P_MPWM_CLK_MCCR_LSE,
    P_MPWM_CLK_MCCR_MCLK,
    P_MPWM_CLK_MCCR_HSI,
    P_MPWM_CLK_MCCR_HSE,
    P_MPWM_CLK_MCCR_PLL,
    P_MPWM_CLK_MCCR_NONE,
    P_MPWM_CLK_MCCR_MAX
} P_MPWM_CLK_MCCR_e;

typedef enum
{
    P_MPWM_INTR_PROT,
    P_MPWM_INTR_OV,
    P_MPWM_INTR_SIG_U,
    P_MPWM_INTR_SIG_V,
    P_MPWM_INTR_SIG_W,
    P_MPWM_INTR_PWM,
    P_MPWM_INTR_MAX
} P_MPWM_INTR_e;

typedef enum
{
    P_MPWM_CLK_MCCR,
    P_MPWM_CLK_MAX
} P_MPWM_CLK_e;

#if (CONFIG_MPWM_VER_VENDOR == 'V')

#if (CONFIG_MPWM_VER_MAJOR == 1)
#include "Vx/V1x/hal_mpwm_v1x.h"
#else
#error "define CONFIG_MPWM_VER_MAJOR of V-type MPWM at config_xxx.h"
#endif

#else
#error "define CONFIG_MPWM_VER_VENDOR of MPWM at config_xxx.h"
#endif

#endif /* _HAL_MPWM_PRV_H_ */
