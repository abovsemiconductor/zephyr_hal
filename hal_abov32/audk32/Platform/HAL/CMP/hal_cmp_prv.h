/**
 *******************************************************************************
 * @file        hal_cmp_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for CMP
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_CMP_PRV_H_
#define _HAL_CMP_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_CMP_ID_0,
    P_CMP_ID_1,
    P_CMP_ID_2,
    P_CMP_ID_3,
    P_CMP_ID_4,
    P_CMP_ID_5,
    P_CMP_ID_6,
    P_CMP_ID_7,
    P_CMP_ID_8,
    P_CMP_ID_9,
    P_CMP_ID_MAX
} P_CMP_ID_e;

#if (CONFIG_CMP_VER_VENDOR == 'V')

#if (CONFIG_CMP_VER_MAJOR == 1)
#include "Vx/V1x/hal_cmp_v1x.h"
#elif (CONFIG_CMP_VER_MAJOR == 2)
#include "Vx/V2x/hal_cmp_v2x.h"
#else
#error "define CONFIG_CMP_VER_MAJOR of V-type CMP at config_xxx.h"
#endif

#elif (CONFIG_CMP_VER_VENDOR == 'F')

#if (CONFIG_CMP_VER_MAJOR == 1)
#include "Fx/F1x/hal_cmp_f1x.h"
#else
#error "define CONFIG_CMP_VER_MAJOR of F-type CMP at config_xxx.h"
#endif

#else
#error "define CONFIG_CMP_VER_VENDOR of CMP at config_xxx.h"
#endif

#endif /* _HAL_CMP_PRV_H_ */
