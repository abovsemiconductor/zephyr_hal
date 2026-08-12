/**
 *******************************************************************************
 * @file        hal_scu_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for SCU
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_SCU_PRV_H_
#define _HAL_SCU_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_SCUCLK_SRC_HSE,                       /* High Speed External OSC (MXOSC) */
    P_SCUCLK_SRC_HSI,                       /* High Speed Internal OSC (IOSC) */
    P_SCUCLK_SRC_LSI,                       /* Low Speed Internal OSC (ROSC) */
    P_SCUCLK_SRC_WDT = P_SCUCLK_SRC_LSI,    /* Watchdog Timer Internal OSC (WDTRC) */
    P_SCUCLK_SRC_LSE,                       /* Low Speed External Sub OSC (SXOSC) */
    P_SCUCLK_SRC_PLL,                       /* Phase-Locked Loop (PLL) Clock Source */
    P_SCUCLK_SRC_PLL_HSI,                   /* PLL from HSI Clock */
    P_SCUCLK_SRC_PLL_HSE,                   /* PLL from HSE Clock */
    P_SCUCLK_SRC_MCLK,                      /* Main Clock Source */
    P_SCUCLK_SRC_HCLK,                      /* System Clock Source */
    P_SCUCLK_SRC_PCLK,                      /* Peripheral Clock Source */
    P_SCUCLK_SRC_MAX
} P_SCUCLK_SRC_e;

typedef enum
{
    P_SCUCLK_DIV_NONE,
    P_SCUCLK_DIV_2,
    P_SCUCLK_DIV_4,
    P_SCUCLK_DIV_8,
    P_SCUCLK_DIV_16,
    P_SCUCLK_DIV_32,
    P_SCUCLK_DIV_64,
    P_SCUCLK_DIV_128,
    P_SCUCLK_DIV_256,
    P_SCUCLK_DIV_512,
    P_SCUCLK_DIV_MAX
} P_SCUCLK_DIV_e;

typedef enum
{
    P_SCUCLK_PLL_SRC_HSI,       /* High Speed Internal OSC (IOSC) */
    P_SCUCLK_PLL_SRC_HSE,       /* High Speed External OSC (MXOSC) */
    P_SCUCLK_PLL_SRC_MAX
} P_SCUCLK_PLL_SRC_e;

#if (CONFIG_SCU_VER_VENDOR == 'V')
#include "Vx/hal_scu_vx.h"

#elif (CONFIG_SCU_VER_VENDOR == 'F')
#include "Fx/hal_scu_fx.h"

#else /* CONFIG_SCU_VER_VENDOR */
#error "define CONFIG_SCU_VER_VENDOR of SCU at config_xxx.h"
#endif

#endif /* _SCH_PRV_H_ */
