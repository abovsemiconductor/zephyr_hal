/**
 *******************************************************************************
 * @file        stk_a31t518_rln_a.h
 * @author      ABOV R&D Division
 * @brief       STK (Startup Kit Board on which A31T518RLN is mounted)
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _STK_A31T518_RLN_A_H_
#define _STK_A31T518_RLN_A_H_

/* STK LED */
#define FIRST_LED_ID                0
#define LAST_LED_ID                 5
#define LED_PORT_ID                 4   /* Port E */

#define USER_SW1_PORT               5   /* Port F */
#define USER_SW1_PORT_ID            6
#define USER_SW1_IRQ_NUM            GPIOEF_IRQn
#define USER_SW2_PORT               5   /* Port F */
#define USER_SW2_PORT_ID            7
#define USER_SW2_IRQ_NUM            GPIOEF_IRQn

/* Add your configuration */
#define TIMER1_CLKSRC_USE_PCLK      0
#define DEFAULT_HSE_1MHZ_DIV        8    /* 8MHz / 8 = 1MHz */

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
#define TIMER10_OUT0_MUX_ID         1
#define TIMER10_CAP0_PORT           4    /* Port E */
#define TIMER10_CAP0_PORT_ID        6
#define TIMER10_CAP0_MUX_ID         2

/* TIMER10 External Clock Port */
#define TIMER10_EXTCLK_PORT         3    /* Port D */
#define TIMER10_EXTCLK_PORT_ID      1
#define TIMER10_EXTCLK_MUX_ID       2

/* UART1 Port */
#define UART1_TX_PORT               1    /* Port B */
#define UART1_TX_PORT_ID            6
#define UART1_TX_MUX_ID             1
#define UART1_RX_PORT               1    /* Port B */
#define UART1_RX_PORT_ID            7
#define UART1_RX_MUX_ID             1

/* USART1 Port */
#define USART1_TX_PORT              3    /* Port D */
#define USART1_TX_PORT_ID           2
#define USART1_TX_MUX_ID            1
#define USART1_RX_PORT              3    /* Port D */
#define USART1_RX_PORT_ID           3
#define USART1_RX_MUX_ID            1

/* USART1 SPI Port */
#define USART1_SS_PORT              3    /* Port D */
#define USART1_SS_PORT_ID           5
#define USART1_SS_MUX_ID            2
#define USART1_SCK_PORT             3    /* Port D */
#define USART1_SCK_PORT_ID          4
#define USART1_SCK_MUX_ID           2
#define USART1_MOSI_PORT            3    /* Port D */
#define USART1_MOSI_PORT_ID         2
#define USART1_MOSI_MUX_ID          2
#define USART1_MISO_PORT            3    /* Port D */
#define USART1_MISO_PORT_ID         3
#define USART1_MISO_MUX_ID          2

/* DAC0 Port */
#define DAC0_OUT_PORT               0    /* Port A */
#define DAC0_OUT_PORT_ID            7
#define DAC0_OUT_MUX_ID             3

/* ADC0 Port */
#define ADC0_IN_PORT                0    /* Port A */
#define ADC0_IN_PORT_ID             0
#define ADC0_IN_MUX_ID              3

/* CLKO Port */
#define CLKO_PORT                   5    /* Port F */
#define CLKO_PORT_ID                4
#define CLKO_MUX_ID                 1

#endif /* _STK_A31T518_RLN_A_H_ */
