/**
 *******************************************************************************
 * @file        hal_i2c_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for I2C
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_I2C_PRV_H_
#define _HAL_I2C_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_I2C_ID_0,
    P_I2C_ID_1,
    P_I2C_ID_2,
    P_I2C_ID_3,
    P_I2C_ID_4,
    P_I2C_ID_5,
    P_I2C_ID_6,
    P_I2C_ID_7,
    P_I2C_ID_8,
    P_I2C_ID_9,
    P_I2C_ID_MAX
} P_I2C_ID_e;

#if (CONFIG_I2C_VER_VENDOR == 'F')

#if (CONFIG_I2C_VER_MAJOR == 1)
#include "Fx/F1x/hal_i2c_f1x.h"
#else
#error "define CONFIG_I2C_VER_MAJOR of F-type I2C at config_xxx.h"
#endif

#elif (CONFIG_I2C_VER_VENDOR == 'V')

#if (CONFIG_I2C_VER_MAJOR == 1)
#include "Vx/V1x/hal_i2c_v1x.h"
#else
#error "define CONFIG_I2C_VER_MAJOR of V-type I2C at config_xxx.h"
#endif

#else
#error "define CONFIG_I2C_VER_VENDOR of I2C at config_xxx.h"
#endif

#endif /* _HAL_I2C_PRV_H_ */
