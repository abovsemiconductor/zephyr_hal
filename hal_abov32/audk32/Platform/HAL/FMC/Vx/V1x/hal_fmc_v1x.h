/**
 *******************************************************************************
 * @file        hal_fmc_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed FMC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_FMC_V1X_H_
#define _HAL_FMC_V1X_H_

#include "abov_config.h"

#if (CONFIG_FMC_VER_EXT == 0)

#if (CONFIG_FMC_VER_MINOR == 0)
#include "hal_fmc_v_01_00_00.h"
#else
#error "define CONFIG_FMC_VER_MINOR of V-type FMC at config_xxx.h"
#endif

#elif (CONFIG_FMC_VER_EXT == 1)

#if (CONFIG_FMC_VER_MINOR == 0)
#include "hal_fmc_v_01_01_00.h"
#else
#error "define CONFIG_FMC_VER_MINOR of V-type FMC at config_xxx.h"
#endif

#else
#error "define CONFIG_FMC_VER_EXT of V-type FMC at config_xxx.h"
#endif

#endif /* _HAL_FMC_V1X_H_ */
