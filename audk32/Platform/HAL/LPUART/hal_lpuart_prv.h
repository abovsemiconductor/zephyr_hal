/**
 *******************************************************************************
 * @file        hal_lpuart_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for LPUART
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_LPUART_PRV_H_
#define _HAL_LPUART_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_LPUART_ID_0   = 0,                        /**< LPUART 0 */
    P_LPUART_ID_1   = 1,                        /**< LPUART 1 */
    P_LPUART_ID_2   = 2,                        /**< LPUART 2 */
    P_LPUART_ID_3   = 3,                        /**< LPUART 3 */
    P_LPUART_ID_4   = 4,                        /**< LPUART 4 */
    P_LPUART_ID_5   = 5,                        /**< LPUART 5 */
    P_LPUART_ID_MAX,                            /**< LPUART max */
} P_LPUART_ID_e;

typedef enum
{
    P_LPUART_CLK_MCCR_LSI,
    P_LPUART_CLK_MCCR_LSE,
    P_LPUART_CLK_MCCR_MCLK,
    P_LPUART_CLK_MCCR_HSI,
    P_LPUART_CLK_MCCR_HSE,
    P_LPUART_CLK_MCCR_PLL,
    P_LPUART_CLK_MCCR_MAX
} P_LPUART_CLK_MCCR_e;

#if (CONFIG_LPUART_VER_VENDOR == 'F')

#if (CONFIG_LPUART_VER_MAJOR == 1)
#include "Fx/F1x/hal_lpuart_f1x.h"
#else
#error "define CONFIG_LPUART_VER_MAJOR of F-type LPUART at config_xxx.h"
#endif

#else
#error "define CONFIG_LPUART_VER_VENDOR of LPUART at config_xxx.h"
#endif

#endif /* _HAL_LPUART_PRV_H_ */
