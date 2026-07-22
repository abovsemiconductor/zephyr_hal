/**
 *******************************************************************************
 * @file        hal_pwm_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for PWM
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_PWM_PRV_H_
#define _HAL_PWM_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_PWM_ID_0,
    P_PWM_ID_1,
    P_PWM_ID_2,
    P_PWM_ID_3,
    P_PWM_ID_4,
    P_PWM_ID_5,
    P_PWM_ID_6,
    P_PWM_ID_7,
    P_PWM_ID_8,
    P_PWM_ID_9,
    P_PWM_ID_MAX
} P_PWM_ID_e;

#if (CONFIG_PWM_VER_VENDOR == 'V')

#if (CONFIG_PWM_VER_MAJOR == 1)
#include "Vx/V1x/hal_pwm_v1x.h"
#else
#error "define CONFIG_PWM_VER_MAJOR of V-type PWM at config_xxx.h"
#endif

#else
#error "define CONFIG_PWM_VER_VENDOR of PWM at config_xxx.h"
#endif


#endif /* _HAL_PWM_PRV_H_ */
