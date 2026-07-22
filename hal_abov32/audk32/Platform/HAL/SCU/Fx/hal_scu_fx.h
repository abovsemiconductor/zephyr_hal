/**
 *******************************************************************************
 * @file        hal_scu_fx.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for Fx typed SCU
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_SCU_FX_H_
#define _HAL_SCU_FX_H_

#include "abov_config.h"

/* Feature(Function) Global Configuration Define */
#define SCU_FEATURE_FX_CLOCK_MONITOR
#define SCU_FEATURE_FX_SCU_CLOCK_IRQ_HANDLER

#if (CONFIG_SCU_VER_MAJOR == 1)
#include "F1x/hal_scu_f1x.h"
#elif (CONFIG_SCU_VER_MAJOR == 2)
#include "F2x/hal_scu_f2x.h"
#else /* CONFIG_SCU_VER_MAJOR */
#error "define CONFIG_SCU_VER_MAJOR of F-type SCU at config_xxx.h"
#endif

#endif /* _HAL_SCH_FX_H_ */
