/**
 *******************************************************************************
 * @file        hal_tempsens_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for TempSens
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TEMPSENS_PRV_H_
#define _HAL_TEMPSENS_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_TEMPSENS_ID_0,
    P_TEMPSENS_ID_1,
    P_TEMPSENS_ID_2,
    P_TEMPSENS_ID_3,
    P_TEMPSENS_ID_4,
    P_TEMPSENS_ID_5,
    P_TEMPSENS_ID_6,
    P_TEMPSENS_ID_7,
    P_TEMPSENS_ID_8,
    P_TEMPSENS_ID_9,
    P_TEMPSENS_ID_MAX
} P_TEMPSENS_ID_e;

/**
 * TEMPSENS reference clock
 */
typedef enum
{
    P_TEMPSENS_REF_CLK_HSI,
    P_TEMPSENS_REF_CLK_MCLK,
    P_TEMPSENS_REF_CLK_HSE,
    P_TEMPSENS_REF_CLK_LSE,
    P_TEMPSENS_REF_CLK_MAX
} P_TEMPSENS_REF_CLK_e;

/**
 * TEMPSENS sense clock
 */
typedef enum
{
    P_TEMPSENS_SEN_CLK_LSITS,
    P_TEMPSENS_SEN_CLK_MAX
} P_TEMPSENS_SEN_CLK_e;

#if (CONFIG_TEMPSENS_VER_VENDOR == 'V')

#if (CONFIG_TEMPSENS_VER_MAJOR == 1)
#include "Vx/V1x/hal_tempsens_v1x.h"
#else
#error "define CONFIG_TEMPSENS_VER_MAJOR of V-type TEMPSENS at config_xxx.h"
#endif

#elif (CONFIG_TEMPSENS_VER_VENDOR == 'F')

#if (CONFIG_TEMPSENS_VER_MAJOR == 1)
#include "Fx/F1x/hal_tempsens_f1x.h"
#else
#error "define CONFIG_TEMPSENS_VER_MAJOR of F-type TEMPSENS at config_xxx.h"
#endif

#else
#error "define CONFIG_TEMPSENS_VER_VENDOR of TEMPSENS at config_xxx.h"
#endif

#endif /* _HAL_TEMPSENS_PRV_H_ */
