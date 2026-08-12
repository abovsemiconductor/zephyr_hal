/**
 *******************************************************************************
 * @file        hal_lcd_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for LCD
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_LCD_PRV_H_
#define _HAL_LCD_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_LCD_ID_0,
    P_LCD_ID_1,
    P_LCD_ID_2,
    P_LCD_ID_3,
    P_LCD_ID_4,
    P_LCD_ID_5,
    P_LCD_ID_6,
    P_LCD_ID_7,
    P_LCD_ID_8,
    P_LCD_ID_9,
    P_LCD_ID_MAX
} P_LCD_ID_e;

typedef enum
{
    P_LCD_CLK_MCCR_LSI,
    P_LCD_CLK_MCCR_LSE,
    P_LCD_CLK_MCCR_MCLK,
    P_LCD_CLK_MCCR_HSI,
    P_LCD_CLK_MCCR_HSE,
    P_LCD_CLK_MCCR_PLL,
    P_LCD_CLK_MCCR_MAX
} P_LCD_CLK_MCCR_e;

typedef enum
{
    P_LCD_CLK_MCCR,
    P_LCD_CLK_LSE,
    P_LCD_CLK_WDTRC,
    P_LCD_CLK_MAX
} P_LCD_CLK_e;

#if (CONFIG_LCD_VER_VENDOR == 'F')

#if (CONFIG_LCD_VER_MAJOR == 1)
#include "Fx/F1x/hal_lcd_f1x.h"
#else
#error "define CONFIG_LCD_VER_MAJOR of F-type LCD at config_xxx.h"
#endif

#else
#error "define CONFIG_LCD_VER_VENDOR of LCD at config_xxx.h"
#endif

#endif /* _HAL_LCD_PRV_H_ */
