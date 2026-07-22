/**
 *******************************************************************************
 * @file        stk_a31c111_fun_a.h
 * @author      ABOV R&D Division
 * @brief       STK (Startup Kit Board on which A31C111FUN is mounted)
 *
 * Copyright 2026 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _STK_A31C111_FUN_A_H_
#define _STK_A31C111_FUN_A_H_

/* STK LED */
#define FIRST_LED_ID                0
#define LAST_LED_ID                 7
#define LED_PORT_ID                 4   /* Port E */

/* Add your configuration */
#define TIMER1_CLKSRC_USE_PCLK      0
#define TIMER1_CLKSRC_USE_HSI       1
#define DEFAULT_HSI_1MHZ_DIV        32   /* HSI is 32MHz, so that divide by 32 to get 1MHz */

/* GPIO */
#define GPIO_OUTPUT_PORT            0    /* Port A */
#define GPIO_OUTPUT_PORT_ID         7
#define GPIO_INPUT_PORT             4   /* Port E */
#define GPIO_INPUT_PORT_ID          7
#define GPIO_INPUT_PORT_INTR_NUM    12

/* I2C0 Port */
#define I2C0_SCL_PORT               3    /* Port D */
#define I2C0_SCL_PORT_ID            0
#define I2C0_SCL_MUX_ID             1
#define I2C0_SDA_PORT               3    /* Port D */
#define I2C0_SDA_PORT_ID            1
#define I2C0_SDA_MUX_ID             1

/* TIMER10 Port */
#define TIMER10_OUT0_PORT           4    /* Port E */
#define TIMER10_OUT0_PORT_ID        6
#define TIMER10_OUT0_MUX_ID         2
/* TIMER11 Port */
#define TIMER11_CAP1_PORT           4    /* Port E */
#define TIMER11_CAP1_PORT_ID        7
#define TIMER11_CAP1_MUX_ID         2
/* TIMER12 Port */
#define TIMER12_OUT2_PORT           4    /* Port E */
#define TIMER12_OUT2_PORT_ID        0
#define TIMER12_OUT2_MUX_ID         2
/* TIMER13 Port */
#define TIMER13_CAP3_PORT           4    /* Port E */
#define TIMER13_CAP3_PORT_ID        1
#define TIMER13_CAP3_MUX_ID         2

/* USART0 Port */
#define USART0_SS_PORT              1    /* Port B */
#define USART0_SS_PORT_ID           3
#define USART0_SS_MUX_ID            4
#define USART0_SCK_PORT             1    /* Port B */
#define USART0_SCK_PORT_ID          2
#define USART0_SCK_MUX_ID           4
#define USART0_MOSI_PORT            1    /* Port B */
#define USART0_MOSI_PORT_ID         0
#define USART0_MOSI_MUX_ID          4
#define USART0_MISO_PORT            1    /* Port B */
#define USART0_MISO_PORT_ID         1
#define USART0_MISO_MUX_ID          4
#define USART0_RX_PORT              1    /* Port B */
#define USART0_RX_PORT_ID           0
#define USART0_RX_MUX_ID            1
#define USART0_TX_PORT              1    /* Port B */
#define USART0_TX_PORT_ID           1
#define USART0_TX_MUX_ID            1

/* ADC0 Port */
#define ADC0_IN_PORT                4    /* Port E */
#define ADC0_IN_PORT_ID             2
#define ADC0_IN_MUX_ID              7
#define ADC0_IN_CHANNEL_NUM         16

/* CLKO Port */
#define CLKO_PORT                   1    /* Port B */
#define CLKO_PORT_ID                2
#define CLKO_MUX_ID                 3

/* UART0 Port */
#define UART0_RX_PORT               5    /* Port F */
#define UART0_RX_PORT_ID            1
#define UART0_RX_MUX_ID             4
#define UART0_TX_PORT               5    /* Port F */
#define UART0_TX_PORT_ID            0
#define UART0_TX_MUX_ID             4

#endif /* _STK_A31C111_FUN_A_H_ */
