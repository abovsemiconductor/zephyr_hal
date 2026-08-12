/**
 *******************************************************************************
 * @file        hal_pga_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for PGA
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_PGA_PRV_H_
#define _HAL_PGA_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_PGA_ID_0,
    P_PGA_ID_1,
    P_PGA_ID_2,
    P_PGA_ID_3,
    P_PGA_ID_4,
    P_PGA_ID_5,
    P_PGA_ID_6,
    P_PGA_ID_7,
    P_PGA_ID_8,
    P_PGA_ID_9,
    P_PGA_ID_MAX
} P_PGA_ID_e;

#if (CONFIG_PGA_VER_VENDOR == 'V')

#if (CONFIG_PGA_VER_MAJOR == 1)
#include "Vx/V1x/hal_pga_v1x.h"
#else /* CONFIG_PGA_VER_MAJOR */
#error "define CONFIG_PGA_VER_MAJOR of V-type PGA at config_xxx.h"
#endif

#else /* CONFIG_PGA_VER_VENDOR */
#error "define CONFIG_PGA_VER_VENDOR of PGA at config_xxx.h"
#endif

#endif /* _HAL_PGA_PRV_H_ */
