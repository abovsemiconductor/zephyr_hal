/**
 *******************************************************************************
 * @file        hal_cfmc_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed CFMC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_CFMC_F1X_H_
#define _HAL_CFMC_F1X_H_

#include "abov_config.h"

#if (CONFIG_CFMC_VER_EXT == 0)

#if (CONFIG_CFMC_VER_MINOR == 0)
#include "hal_cfmc_f_01_00_00.h"
#elif (CONFIG_CFMC_VER_MINOR == 1)
#include "hal_cfmc_f_01_00_01.h"
#else
#error "define CONFIG_CFMC_VER_MINOR of V-type CFMC at config_xxx.h"
#endif

#else
#error "define CONFIG_CFMC_VER_EXT of V-type CFMC at config_xxx.h"
#endif

#endif /* _HAL_CFMC_F1X_H_ */
