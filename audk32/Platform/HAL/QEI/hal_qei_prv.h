/**
 *******************************************************************************
 * @file        hal_qei_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for QEI
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_QEI_PRV_H_
#define _HAL_QEI_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_QEI_ID_0,
    P_QEI_ID_1,
    P_QEI_ID_2,
    P_QEI_ID_3,
    P_QEI_ID_4,
    P_QEI_ID_5,
    P_QEI_ID_6,
    P_QEI_ID_7,
    P_QEI_ID_8,
    P_QEI_ID_9,
    P_QEI_ID_MAX
} P_QEI_ID_e;

#if (CONFIG_QEI_VER_VENDOR == 'V')

#if (CONFIG_QEI_VER_MAJOR == 1)
#include "Vx/V1x/hal_qei_v1x.h"
#else
#error "define CONFIG_QEI_VER_MAJOR of V-type QEI at config_xxx.h"
#endif

#else
#error "define CONFIG_QEI_VER_VENDOR of QEI at config_xxx.h"
#endif

#endif /* _HAL_QEI_PRV_H_ */
