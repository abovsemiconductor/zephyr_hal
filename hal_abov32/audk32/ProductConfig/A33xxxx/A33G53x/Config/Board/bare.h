/**
 *******************************************************************************
 * @file        bare.h
 * @author      ABOV R&D Division
 * @brief       Board configuration on which A33G53x is mounted
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _BARE_H_
#define _BARE_H_

/* Add your configuration */
#define TIMER1N_CLKSRC_USE_PCLK     1
#define DEFAULT_HSE_1MHZ_DIV        8    /* 8MHz / 8 = 1MHz */

/* I2C0 Port */
#define I2C0_SCL_PORT               1    /* Port B */
#define I2C0_SCL_PORT_ID            14
#define I2C0_SCL_MUX_ID             1
#define I2C0_SDA_PORT               1    /* Port B */
#define I2C0_SDA_PORT_ID            15
#define I2C0_SDA_MUX_ID             1

/* SPI0 Port */
#define SPI0_SS_PORT                1    /* Port B */
#define SPI0_SS_PORT_ID             10
#define SPI0_SS_MUX_ID              1
#define SPI0_SCK_PORT               1    /* Port B */
#define SPI0_SCK_PORT_ID            11
#define SPI0_SCK_MUX_ID             1
#define SPI0_MOSI_PORT              1    /* Port B */
#define SPI0_MOSI_PORT_ID           12
#define SPI0_MOSI_MUX_ID            1
#define SPI0_MISO_PORT              1    /* Port B */
#define SPI0_MISO_PORT_ID           13
#define SPI0_MISO_MUX_ID            1

/* TIMER10 Port */
#define TIMER10_OUT0_PORT           1    /* Port B */
#define TIMER10_OUT0_PORT_ID        0
#define TIMER10_OUT0_MUX_ID         1
#define TIMER10_CAP0_PORT           0    /* Port A */
#define TIMER10_CAP0_PORT_ID        6
#define TIMER10_CAP0_MUX_ID         1

/* TIMER10 External Clock Port */
#define TIMER10_EXTCLK_PORT         0    /* Port A */
#define TIMER10_EXTCLK_PORT_ID      6
#define TIMER10_EXTCLK_MUX_ID       1

/* UART1 Port */
#define UART1_TX_PORT               3    /* Port D */
#define UART1_TX_PORT_ID            13
#define UART1_TX_MUX_ID             1
#define UART1_RX_PORT               3    /* Port D */
#define UART1_RX_PORT_ID            12
#define UART1_RX_MUX_ID             1

/* ADC0 Port */
#define ADC0_IN_PORT                0    /* Port A */
#define ADC0_IN_PORT_ID             0
#define ADC0_IN_MUX_ID              3

/* ADC1 Port */
#define ADC1_IN_PORT                0    /* Port A */
#define ADC1_IN_PORT_ID             1
#define ADC1_IN_MUX_ID              3

/* ADC2 Port */
#define ADC2_IN_PORT                0    /* Port A */
#define ADC2_IN_PORT_ID             2
#define ADC2_IN_MUX_ID              3

#endif /* _BARE_H_ */
