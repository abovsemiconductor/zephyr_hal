/**
 *******************************************************************************
 * @file        hal_spi_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for SPI
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_SPI_PRV_H_
#define _HAL_SPI_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_SPI_ID_0,
    P_SPI_ID_1,
    P_SPI_ID_2,
    P_SPI_ID_3,
    P_SPI_ID_4,
    P_SPI_ID_5,
    P_SPI_ID_6,
    P_SPI_ID_7,
    P_SPI_ID_8,
    P_SPI_ID_9,
    P_SPI_ID_10,
    P_SPI_ID_11,
    P_SPI_ID_MAX
} P_SPI_ID_e;

#if (CONFIG_SPI_VER_VENDOR == 'V')

#if (CONFIG_SPI_VER_MAJOR == 1)
#include "Vx/V1x/hal_spi_v1x.h"
#else
#error "define CONFIG_SPI_VER_MAJOR of V-type SPI at config_xxx.h"
#endif

#elif (CONFIG_SPI_VER_VENDOR == 'F')

#if (CONFIG_SPI_VER_MAJOR == 1)
#include "Fx/F1x/hal_spi_f1x.h"
#else
#error "define CONFIG_SPI_VER_MAJOR of F-type SPI at config_xxx.h"
#endif

#else
#error "define CONFIG_SPI_VER_VENDOR of SPI at config_xxx.h"
#endif

#endif /* _HAL_SPI_PRV_H_ */
