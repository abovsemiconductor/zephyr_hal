/**
 *******************************************************************************
 * @file        hal_rng_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for RNG
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_RNG_PRV_H_
#define _HAL_RNG_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_RNG_ID_0,
    P_RNG_ID_1,
    P_RNG_ID_2,
    P_RNG_ID_3,
    P_RNG_ID_4,
    P_RNG_ID_5,
    P_RNG_ID_6,
    P_RNG_ID_7,
    P_RNG_ID_8,
    P_RNG_ID_9,
    P_RNG_ID_MAX
} P_RNG_ID_e;

#if (CONFIG_RNG_VER_VENDOR == 'V')

#if (CONFIG_RNG_VER_MAJOR == 1)
#include "Vx/V1x/hal_rng_v1x.h"
#else /* CONFIG_RNG_VER_MAJOR */
#error "define CONFIG_RNG_VER_MAJOR of V-type RNG at config_xxx.h"
#endif

#else /* CONFIG_RNG_VER_VENDOR */
#error "define CONFIG_RNG_VER_VENDOR of RNG at config_xxx.h"
#endif

#endif /* _HAL_RNG_PRV_H_ */
