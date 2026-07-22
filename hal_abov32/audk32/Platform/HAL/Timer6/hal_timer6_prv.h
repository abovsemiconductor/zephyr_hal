/**
 *******************************************************************************
 * @file        hal_timer6_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for Timer6
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER6_PRV_H_
#define _HAL_TIMER6_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_TIMER6_ID_0,
    P_TIMER6_ID_1,
    P_TIMER6_ID_2,
    P_TIMER6_ID_3,
    P_TIMER6_ID_4,
    P_TIMER6_ID_5,
    P_TIMER6_ID_6,
    P_TIMER6_ID_7,
    P_TIMER6_ID_8,
    P_TIMER6_ID_9,
    P_TIMER6_ID_MAX
} P_TIMER6_ID_e;

typedef enum
{
    P_TIMER6_MODE_COUNTER,
    P_TIMER6_MODE_MAX
} P_TIMER6_MODE_e;

typedef enum
{
    P_TIMER6_INTR_FLAG_MATCH,
    P_TIMER6_INTR_FLAG_MAX
} P_TIMER6_INT_FLAG_e;

#if (CONFIG_TIMER6_VER_VENDOR == 'F')

#if (CONFIG_TIMER6_VER_MAJOR == 1)
#include "Fx/F1x/hal_timer6_f1x.h"
#else
#error "define CONFIG_TIMER6_VER_MAJOR of F-type Timer6 at config_xxx.h"
#endif

#else
#error "define CONFIG_TIMER6_VER_VENDOR of Timer6 at config_xxx.h"
#endif


#endif /* _HAL_TIMER6_PRV_H_ */
