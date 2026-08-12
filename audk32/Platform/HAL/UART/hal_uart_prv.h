/**
 *******************************************************************************
 * @file        hal_uart_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for UART
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_UART_PRV_H_
#define _HAL_UART_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_UART_ID_0   = 0,                        /**< UART 0 */
    P_UART_ID_1   = 1,                        /**< UART 1 */
    P_UART_ID_2   = 2,                        /**< UART 2 */
    P_UART_ID_3   = 3,                        /**< UART 3 */
    P_UART_ID_4   = 4,                        /**< UART 4 */
    P_UART_ID_5   = 5,                        /**< UART 5 */
    P_UART_ID_6   = 6,                        /**< UART 6 */
    P_UART_ID_7   = 7,                        /**< UART 7 */
    P_UART_ID_8   = 8,                        /**< UART 8 */
    P_UART_ID_9   = 9,                        /**< UART 9 */
    P_UART_ID_10  = 10,                       /**< UART 10 */
    P_UART_ID_11  = 11,                       /**< UART 11 */
    P_UART_ID_12  = 12,                       /**< UART 12 */
    P_UART_ID_MAX,                            /**< UART max */
} P_UART_ID_e;

typedef enum
{
    P_UART_CLK_MCCR_LSI,
    P_UART_CLK_MCCR_LSE,
    P_UART_CLK_MCCR_MCLK,
    P_UART_CLK_MCCR_HSI,
    P_UART_CLK_MCCR_HSE,
    P_UART_CLK_MCCR_PLL,
    P_UART_CLK_MCCR_MAX
} P_UART_CLK_MCCR_e;

#if (CONFIG_UART_VER_VENDOR == 'V')

#if (CONFIG_UART_VER_MAJOR == 1)
#include "Vx/V1x/hal_uart_v1x.h"
#else
#error "define CONFIG_UART_VER_MAJOR of V-type UART at config_xxx.h"
#endif

#else
#error "define CONFIG_UART_VER_VENDOR of UART at config_xxx.h"
#endif

#endif /* _HAL_UART_PRV_H_ */
