/**
 *******************************************************************************
 * @file        hal_qspi_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for QSPI
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_QSPI_PRV_H_
#define _HAL_QSPI_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_QSPI_ID_0,
    P_QSPI_ID_1,
    P_QSPI_ID_2,
    P_QSPI_ID_3,
    P_QSPI_ID_4,
    P_QSPI_ID_5,
    P_QSPI_ID_6,
    P_QSPI_ID_7,
    P_QSPI_ID_8,
    P_QSPI_ID_9,
    P_QSPI_ID_MAX
} P_QSPI_ID_e;

#if (CONFIG_QSPI_VER_VENDOR == 'V')

#if (CONFIG_QSPI_VER_MAJOR == 1)
#include "Vx/V1x/hal_qspi_v1x.h"
#else
#error "define CONFIG_QSPI_VER_MAJOR of V-type QSPI at config_xxx.h"
#endif

#elif (CONFIG_QSPI_VER_VENDOR == 'F')

#else
#error "define CONFIG_QSPI_VER_VENDOR of QSPI at config_xxx.h"
#endif

#endif /* _HAL_QSPI_PRV_H_ */
