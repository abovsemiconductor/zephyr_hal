/**
 *******************************************************************************
 * @file        hal_aes_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for AES
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_AES_PRV_H_
#define _HAL_AES_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_AES_ID_0,
    P_AES_ID_1,
    P_AES_ID_2,
    P_AES_ID_3,
    P_AES_ID_4,
    P_AES_ID_5,
    P_AES_ID_6,
    P_AES_ID_7,
    P_AES_ID_8,
    P_AES_ID_9,
    P_AES_ID_MAX
} P_AES_ID_e;

#if (CONFIG_AES_VER_VENDOR == 'V')

#if (CONFIG_AES_VER_MAJOR == 1)
#include "Vx/V1x/hal_aes_v1x.h"
#else /* CONFIG_AES_VER_MAJOR */
#error "define CONFIG_AES_VER_MAJOR of V-type AES at config_xxx.h"
#endif

#elif (CONFIG_AES_VER_VENDOR == 'F')

#if (CONFIG_AES_VER_MAJOR == 1)
#include "Fx/F1x/hal_aes_f1x.h"
#else /* CONFIG_AES_VER_MAJOR */
#error "define CONFIG_AES_VER_MAJOR of F-type AES at config_xxx.h"
#endif

#else /* CONFIG_AES_VER_VENDOR */
#error "define CONFIG_AES_VER_VENDOR of AES at config_xxx.h"
#endif

#endif /* _HAL_AES_PRV_H_ */
