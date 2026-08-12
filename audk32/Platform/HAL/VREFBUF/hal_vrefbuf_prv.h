/**
 *******************************************************************************
 * @file        hal_vrefbuf_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for VREFBUF
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_VREFBUF_PRV_H_
#define _HAL_VREFBUF_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_VREFBUF_ID_0,
    P_VREFBUF_ID_1,
    P_VREFBUF_ID_2,
    P_VREFBUF_ID_3,
    P_VREFBUF_ID_4,
    P_VREFBUF_ID_5,
    P_VREFBUF_ID_6,
    P_VREFBUF_ID_7,
    P_VREFBUF_ID_8,
    P_VREFBUF_ID_9,
    P_VREFBUF_ID_MAX
} P_VREFBUF_ID_e;

typedef enum
{
    P_VREFBUF_MODE_NONE,        /**< Reserved */
    P_VREFBUF_MODE_EXTERNAL,    /**< External mode */
    P_VREFBUF_MODE_VDDEXT,      /**< Bypass mode */
    P_VREFBUF_MODE_INTERNAL,    /**< Buf mode, 2.0V or 2.5V source */
    P_VREFBUF_MODE_MAX
} P_VREFBUF_MODE_e;

#if (CONFIG_VREFBUF_VER_VENDOR == 'V')

#if (CONFIG_VREFBUF_VER_MAJOR == 1)
#include "Vx/V1x/hal_vrefbuf_v1x.h"
#else /* CONFIG_VREFBUF_VER_MAJOR */
#error "define CONFIG_VREFBUF_VER_MAJOR of V-type VREFBUF at config_xxx.h"
#endif

#else /* CONFIG_VREFBUF_VER_VENDOR */
#error "define CONFIG_VREFBUF_VER_VENDOR of VREFBUF at config_xxx.h"
#endif

#endif /* _HAL_VREFBUF_PRV_H_ */
