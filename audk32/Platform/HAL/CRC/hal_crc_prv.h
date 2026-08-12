/**
 *******************************************************************************
 * @file        hal_crc_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for CRC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_CRC_PRV_H_
#define _HAL_CRC_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_CRC_ID_0,
    P_CRC_ID_1,
    P_CRC_ID_2,
    P_CRC_ID_3,
    P_CRC_ID_4,
    P_CRC_ID_5,
    P_CRC_ID_6,
    P_CRC_ID_7,
    P_CRC_ID_8,
    P_CRC_ID_9,
    P_CRC_ID_MAX
} P_CRC_ID_e;

typedef enum
{
    P_CRC_POLY_32,
    P_CRC_POLY_16,
    P_CRC_POLY_8,
    P_CRC_POLY_7,
    P_CRC_POLY_16_CCITT,
    P_CRC_POLY_MAX
} P_CRC_POLY_e;

typedef enum
{
    P_CRC_DMA_BUS_SIZE_BYTE,
    P_CRC_DMA_BUS_SIZE_WORD,
    P_CRC_DMA_BUS_SIZE_MAX
} P_CRC_DMA_BUS_SIZE_e;

#if (CONFIG_CRC_VER_VENDOR == 'F')

#if (CONFIG_CRC_VER_MAJOR == 1)
#include "Fx/F1x/hal_crc_f1x.h"
#else
#error "define CONFIG_CRC_VER_MAJOR of F-type CRC at config_xxx.h"
#endif

#elif (CONFIG_CRC_VER_VENDOR == 'V')

#if (CONFIG_CRC_VER_MAJOR == 1)
#include "Vx/V1x/hal_crc_v1x.h"
#elif (CONFIG_CRC_VER_MAJOR == 2)
#include "Vx/V2x/hal_crc_v2x.h"
#else /* CONFIG_CRC_VER_MAJOR */
#error "define CONFIG_CRC_VER_MAJOR of V-type CRC at config_xxx.h"
#endif

#else /* CONFIG_CRC_VER_VENDOR */
#error "define CONFIG_CRC_VER_VENDOR of CRC at config_xxx.h"
#endif

#endif /* _HAL_CRC_PRV_H_ */
