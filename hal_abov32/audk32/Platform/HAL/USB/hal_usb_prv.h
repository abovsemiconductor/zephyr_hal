/**
 *******************************************************************************
 * @file        hal_usb_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for USB
 *
 * Copyright 2025 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_USB_PRV_H_
#define _HAL_USB_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_USB_ID_0,
    P_USB_ID_1,
    P_USB_ID_2,
    P_USB_ID_3,
    P_USB_ID_4,
    P_USB_ID_5,
    P_USB_ID_6,
    P_USB_ID_7,
    P_USB_ID_8,
    P_USB_ID_9,
    P_USB_ID_MAX
} P_USB_ID_e;

typedef enum
{
    P_USB_CLK_MCCR_LSI,
    P_USB_CLK_MCCR_LSE,
    P_USB_CLK_MCCR_MCLK,
    P_USB_CLK_MCCR_HSI,
    P_USB_CLK_MCCR_HSE,
    P_USB_CLK_MCCR_PLL,
    P_USB_CLK_MCCR_MAX
} P_USB_CLK_MCCR_e;

typedef enum
{
    P_USB_CLK_MCCR,
    P_USB_CLK_MAX
} P_USB_CLK_e;

#if (CONFIG_USB_VER_VENDOR == 'F')

#if (CONFIG_USB_VER_MAJOR == 1)
#include "Fx/F1x/hal_usb_f1x.h"
#else
#error "define CONFIG_USB_VER_MAJOR of F-type USB at config_xxx.h"
#endif

#elif (CONFIG_USB_VER_VENDOR == 'V')

#if (CONFIG_USB_VER_MAJOR == 1)
#include "Vx/V1x/hal_usb_v1x.h"
#else
#error "define CONFIG_USB_VER_MAJOR of V-type USB at config_xxx.h"
#endif

#else
#error "define CONFIG_USB_VER_VENDOR of USB at config_xxx.h"
#endif

#endif /* _HAL_USB_PRV_H_ */
