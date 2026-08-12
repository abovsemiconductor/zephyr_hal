/**
 *******************************************************************************
 * @file        debug_a34l71x.h
 * @author      ABOV R&D Division
 * @brief       A34L71x debug config file
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _DEBUG_A34L71X_H_
#define _DEBUG_A34L71X_H_

/* Default Debug Configuration */
#define CONFIG_DEBUG                     TARGET_BOARD_DEBUG_ENABLE
#define CONFIG_DEBUG_SERIAL_FIFO         1
#define DEBUG_UART_CLK                   1    /* MCCR Clock */
#define DEBUG_UART_CLK_MCCR              2    /* MCLK */
#define DEBUG_UART_CLK_MCCR_DIV          4
#define APP_UART_BAUD                    38400
#define DRIVER_PRIORITY_LOWEST           15

#if ((TARGET_SERIAL_MODULE == BD_SERIAL_MODULE_NONE) \
    || (TARGET_SERIAL_MODULE == BD_SERIAL_MODULE_UART && TARGET_SERIAL_CHANNEL_ID == BD_SERIAL_CHANNEL_ID_0))
#if (CONFIG_HAL_UART == 1)
#define CONFIG_DEBUG_MODULE_UART         1
#endif
#define CONFIG_DEBUG_MODULE_STR          "UART"
#define DEBUG_UART_ID                    0
#define DEBUG_PORT_ID                    3    /* PORT D */
#define DEBUG_RX_PORT_ID                 0
#define DEBUG_RX_ALT_ID                  3
#define DEBUG_TX_PORT_ID                 1
#define DEBUG_TX_ALT_ID                  3

#elif (TARGET_SERIAL_MODULE == BD_SERIAL_MODULE_UART)
#error Only UART channel id 0 as a debug log can be used.

#elif (TARGET_SERIAL_MODULE == BD_SERIAL_MODULE_USART)
#if (CONFIG_HAL_USART == 1)
#define CONFIG_DEBUG_MODULE_USART        1
#endif
#define CONFIG_DEBUG_MODULE_STR          "USART"

#if (TARGET_SERIAL_CHANNEL_ID == BD_SERIAL_CHANNEL_ID_0)
#define DEBUG_UART_ID                    0
#define DEBUG_PORT_ID                    4 /* PORT E */
#define DEBUG_RX_PORT_ID                 12
#define DEBUG_RX_ALT_ID                  1
#define DEBUG_TX_PORT_ID                 11
#define DEBUG_TX_ALT_ID                  1

#elif (TARGET_SERIAL_CHANNEL_ID == BD_SERIAL_CHANNEL_ID_1)
#define DEBUG_UART_ID                    1
#define DEBUG_PORT_ID                    2 /* PORT C */
#define DEBUG_RX_PORT_ID                 11
#define DEBUG_RX_ALT_ID                  1
#define DEBUG_TX_PORT_ID                 10
#define DEBUG_TX_ALT_ID                  1

#else
#error Only USART channel id 0 ~ 1 as a debug log can be used.
#endif

#else
#error Only UART or USART module as a debug log can be used.
#endif /* TARGET_SERIAL_MODULE */

#endif /* _DEBUG_A34L71X_H_ */
