/**
 *******************************************************************************
 * @file        hal_dac_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for DAC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_DAC_PRV_H_
#define _HAL_DAC_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_DAC_ID_0,
    P_DAC_ID_1,
    P_DAC_ID_2,
    P_DAC_ID_3,
    P_DAC_ID_4,
    P_DAC_ID_5,
    P_DAC_ID_6,
    P_DAC_ID_7,
    P_DAC_ID_8,
    P_DAC_ID_9,
    P_DAC_ID_MAX
} P_DAC_ID_e;

typedef enum
{
    P_DAC_OUT_PORT1 = (1UL << 0),
    P_DAC_OUT_PORT2 = (1UL << 1),
    P_DAC_OUT_PORT3 = (1UL << 2),
    P_DAC_OUT_MAX
} P_DAC_OUT_e;

#if (CONFIG_DAC_VER_VENDOR == 'V')

#if (CONFIG_DAC_VER_MAJOR == 1)
#include "Vx/V1x/hal_dac_v1x.h"
#elif (CONFIG_DAC_VER_MAJOR == 2)
#include "Vx/V2x/hal_dac_v2x.h"
#elif (CONFIG_DAC_VER_MAJOR == 3)
#include "Vx/V3x/hal_dac_v3x.h"
#else
#error "define CONFIG_DAC_VER_MAJOR of V-type DAC at config_xxx.h"
#endif

#else
#error "define CONFIG_DAC_VER_VENDOR of DAC at config_xxx.h"
#endif

#endif /* _HAL_DAC_PRV_H_ */
