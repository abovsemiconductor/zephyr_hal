/**
 *******************************************************************************
 * @file        debug_a33g52x.h
 * @author      ABOV R&D Division
 * @brief       A33G52x debug config file
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _DEBUG_A33G52X_H_
#define _DEBUG_A33G52X_H_

/* Default Debug Configuration */
#define CONFIG_DEBUG                     TARGET_BOARD_DEBUG_ENABLE
#define CONFIG_DEBUG_MODULE_UART         1
#define CONFIG_DEBUG_MODULE_STR          "UART"
#define CONFIG_DEBUG_SERIAL_FIFO         1
#define DEBUG_UART_CLK                   0    /* Peri Clock */
#define DEBUG_UART_CLK_MCCR              0
#define DEBUG_UART_CLK_MCCR_DIV          0
#define APP_UART_BAUD                    38400
#define DRIVER_PRIORITY_LOWEST           15

#if ((TARGET_SERIAL_MODULE == BD_SERIAL_MODULE_NONE) \
    || (TARGET_SERIAL_MODULE == BD_SERIAL_MODULE_UART && TARGET_SERIAL_CHANNEL_ID == BD_SERIAL_CHANNEL_ID_0))
#define DEBUG_UART_ID                    0
#define DEBUG_PORT_ID                    2    /* PORT C */
#define DEBUG_RX_PORT_ID                 8
#define DEBUG_RX_ALT_ID                  1
#define DEBUG_TX_PORT_ID                 9
#define DEBUG_TX_ALT_ID                  1

#elif (TARGET_SERIAL_MODULE == BD_SERIAL_MODULE_UART)

#if (TARGET_SERIAL_CHANNEL_ID == BD_SERIAL_CHANNEL_ID_1)
#define DEBUG_UART_ID                    1
#define DEBUG_PORT_ID                    3    /* PORT D */
#define DEBUG_RX_PORT_ID                 12
#define DEBUG_RX_ALT_ID                  1
#define DEBUG_TX_PORT_ID                 13
#define DEBUG_TX_ALT_ID                  1

#elif (TARGET_SERIAL_CHANNEL_ID == BD_SERIAL_CHANNEL_ID_2)
#define DEBUG_UART_ID                    2
#define DEBUG_PORT_ID                    2    /* PORT C */
#define DEBUG_RX_PORT_ID                 10
#define DEBUG_RX_ALT_ID                  1
#define DEBUG_TX_PORT_ID                 11
#define DEBUG_TX_ALT_ID                  1

#elif (TARGET_SERIAL_CHANNEL_ID == BD_SERIAL_CHANNEL_ID_3)
#define DEBUG_UART_ID                    3
#define DEBUG_PORT_ID                    4    /* PORT E */
#define DEBUG_RX_PORT_ID                 6
#define DEBUG_RX_ALT_ID                  2
#define DEBUG_TX_PORT_ID                 7
#define DEBUG_TX_ALT_ID                  2

#else
#error Only UART channel id 0 ~ 3 as a debug log can be used.
#endif /* TARGET_SERIAL_CHANNEL_ID */

#else
#error Only UART module as a debug log can be used.
#endif /* TARGET_SERIAL_MODULE */

#endif /* _DEBUG_A33G52X_H_ */
