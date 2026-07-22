/**
 *******************************************************************************
 * @file        hal_scu_vx.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for Vx typed SCU
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_SCU_VX_H_
#define _HAL_SCU_VX_H_

#include "abov_config.h"

/* Feature(Function) Global Configuration Define */
#define SCU_FEATURE_VX_CLOCK_MONITOR
#define SCU_FEATURE_VX_CLOCK_RESET_SOURCE
#define SCU_FEATURE_VX_EXT_HSE_CONTROL
#define SCU_FEATURE_VX_EXT_LSE_CONTROL
#define SCU_FEATURE_VX_EXT_LSI_CONTROL
#define SCU_FEATURE_VX_SCU_CLOCK_IRQ_HANDLER
#define SCU_FEATURE_VX_RESET_ENABLE
#define SCU_FEATURE_VX_AON_SOURCE

#if (CONFIG_SCU_VER_MAJOR == 1)
#include "V1x/hal_scu_v1x.h"
#elif (CONFIG_SCU_VER_MAJOR == 2)
#include "V2x/hal_scu_v2x.h"
#elif (CONFIG_SCU_VER_MAJOR == 3)
#include "V3x/hal_scu_v3x.h"
#elif (CONFIG_SCU_VER_MAJOR == 4)
#include "V4x/hal_scu_v4x.h"
#else /* CONFIG_SCU_VER_MAJOR */
#error "define CONFIG_SCU_VER_MAJOR of V-type SCU at config_xxx.h"
#endif

#endif /* _HAL_SCH_VX_H_ */
