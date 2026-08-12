/**
 *******************************************************************************
 * @file        bare.h
 * @author      ABOV R&D Division
 * @brief       Board configuration on which A31C11x is mounted
 *
 * Copyright 2026 ABOV Semiconductor Co.,Ltd. All rights reserved.
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
#define TIMER1_CLKSRC_USE_PCLK      0
#define TIMER1_CLKSRC_USE_HSI       1
#define DEFAULT_HSI_1MHZ_DIV        32   /* HSI is 32MHz, so that divide by 32 to get 1MHz */

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

/* TIMER11 Port */
#define TIMER11_OUT0_PORT           4    /* Port E */
#define TIMER11_OUT0_PORT_ID        7
#define TIMER11_OUT0_MUX_ID         2
#define TIMER11_CAP0_PORT           4    /* Port E */
#define TIMER11_CAP0_PORT_ID        7
#define TIMER11_CAP0_MUX_ID         2
/* TIMER11 External Clock Port */
#define TIMER11_EXTCLK_PORT         4    /* Port E */
#define TIMER11_EXTCLK_PORT_ID      7
#define TIMER11_EXTCLK_MUX_ID       2

/* TIMER12 Port */
#define TIMER12_OUT0_PORT           4    /* Port E */
#define TIMER12_OUT0_PORT_ID        0
#define TIMER12_OUT0_MUX_ID         2
#define TIMER12_CAP0_PORT           4    /* Port E */
#define TIMER12_CAP0_PORT_ID        0
#define TIMER12_CAP0_MUX_ID         2
/* TIMER12 External Clock Port */
#define TIMER12_EXTCLK_PORT         4    /* Port E */
#define TIMER12_EXTCLK_PORT_ID      0
#define TIMER12_EXTCLK_MUX_ID       2

/* TIMER13 Port */
#define TIMER13_OUT0_PORT           4    /* Port E */
#define TIMER13_OUT0_PORT_ID        1
#define TIMER13_OUT0_MUX_ID         2
#define TIMER13_CAP0_PORT           4    /* Port E */
#define TIMER13_CAP0_PORT_ID        1
#define TIMER13_CAP0_MUX_ID         2
/* TIMER13 External Clock Port */
#define TIMER13_EXTCLK_PORT         4    /* Port E */
#define TIMER13_EXTCLK_PORT_ID      1
#define TIMER13_EXTCLK_MUX_ID       2

/* UART0 Port */
#define UART0_TX_PORT               5    /* Port F */
#define UART0_TX_PORT_ID            0
#define UART0_TX_MUX_ID             4
#define UART0_RX_PORT               5    /* Port F */
#define UART0_RX_PORT_ID            1
#define UART0_RX_MUX_ID             4

/* ADC15 Port */
#define ADC15_IN_PORT               4    /* Port A */
#define ADC15_IN_PORT_ID            1
#define ADC15_IN_MUX_ID             7
/* ADC16 Port */
#define ADC16_IN_PORT               4    /* Port A */
#define ADC16_IN_PORT_ID            2
#define ADC16_IN_MUX_ID             7
/* ADC17 Port */
#define ADC17_IN_PORT               4    /* Port A */
#define ADC17_IN_PORT_ID            3
#define ADC17_IN_MUX_ID             7

/* CLKO Port */
#define CLKO_PORT                   1    /* Port B */
#define CLKO_PORT_ID                2
#define CLKO_MUX_ID                 3
#endif /* _BARE_H_ */
