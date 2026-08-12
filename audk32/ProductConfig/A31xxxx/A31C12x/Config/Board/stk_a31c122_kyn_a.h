/**
 *******************************************************************************
 * @file        stk_a31c122_kyn_a.h
 * @author      ABOV R&D Division
 * @brief       STK (Startup Kit Board on which A31C144RLN is mounted)
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _STK_A31C122_KYN_A_H_
#define _STK_A31C122_KYN_A_H_

/* STK LED */
#define FIRST_LED_ID                0
#define LAST_LED_ID                 7
#define LED_PORT_ID                 4   /* Port E */

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
#define TIMER10_OUT0_MUX_ID         2
#define TIMER10_CAP0_PORT           4    /* Port E */
#define TIMER10_CAP0_PORT_ID        6
#define TIMER10_CAP0_MUX_ID         2

/* TIMER10 External Clock Port */
#define TIMER10_EXTCLK_PORT         4    /* Port E */
#define TIMER10_EXTCLK_PORT_ID      6
#define TIMER10_EXTCLK_MUX_ID       2

/* USART1 Port */
#define USART1_TX_PORT              3    /* Port D */
#define USART1_TX_PORT_ID           2
#define USART1_TX_MUX_ID            1
#define USART1_RX_PORT              3    /* Port D */
#define USART1_RX_PORT_ID           3
#define USART1_RX_MUX_ID            1

/* ADC0 Port */
#define ADC0_IN_PORT                0    /* Port A */
#define ADC0_IN_PORT_ID             2
#define ADC0_IN_MUX_ID              7

/* CLKO Port */
#define CLKO_PORT                   1    /* Port B */
#define CLKO_PORT_ID                2
#define CLKO_MUX_ID                 3

#endif /* _STK_A31C122_KYN_A_H_ */
