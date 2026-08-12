/**
 *******************************************************************************
 * @file        hal_trng_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for TRNG
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TRNG_PRV_H_
#define _HAL_TRNG_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_TRNG_ID_0,
    P_TRNG_ID_1,
    P_TRNG_ID_2,
    P_TRNG_ID_3,
    P_TRNG_ID_4,
    P_TRNG_ID_5,
    P_TRNG_ID_6,
    P_TRNG_ID_7,
    P_TRNG_ID_8,
    P_TRNG_ID_9,
    P_TRNG_ID_MAX
} P_TRNG_ID_e;

#if (CONFIG_TRNG_VER_VENDOR == 'F')

#if (CONFIG_TRNG_VER_MAJOR == 1)
#include "Fx/F1x/hal_trng_f1x.h"
#else /* CONFIG_TRNG_VER_MAJOR */
#error "define CONFIG_TRNG_VER_MAJOR of F-type TRNG at config_xxx.h"
#endif

#else /* CONFIG_TRNG_VER_VENDOR */
#error "define CONFIG_TRNG_VER_VENDOR of TRNG at config_xxx.h"
#endif

#endif /* _HAL_TRNG_PRV_H_ */
