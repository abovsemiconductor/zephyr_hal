/**
 *******************************************************************************
 * @file        stk_a34l716_vln_a.h
 * @author      ABOV R&D Division
 * @brief       STK (Startup Kit Board on which A34L716VLN is mounted)
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _STK_A34L716_VLN_A_H_
#define _STK_A34L716_VLN_A_H_

#define STK_LED_PORT_NON_SEQUENTIAL

static inline uint8_t STK_LED_GetPortID(uint32_t un32LedID)
{
    uint8_t un8PortId = 0;

    switch(un32LedID)
    {
        case 0:
        case 1:
            un8PortId = 2;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            un8PortId = 4;
            break;
        default:
            un8PortId = 2;
            break;
    }

    return un8PortId;
}

static inline uint8_t STK_LED_GetPinID(uint32_t un32LedID)
{
    uint8_t un8PinId = 0;

    switch(un32LedID)
    {
        case 0:
            un8PinId = 10;
            break;
        case 1:
            un8PinId = 11;
            break;
        case 2:
            un8PinId = 13;
            break;
        case 3:
            un8PinId = 14;
            break;
        case 4:
            un8PinId = 15;
            break;
        case 5:
            un8PinId = 4;
            break;
        default:
            un8PinId = 10;
            break;
    }

    return un8PinId;
}

/* STK LED */
#define FIRST_LED_ID                0
#define LAST_LED_ID                 5
#define LED_PORT_ID                 2    /* Port C */

/* Add your configuration */
#define TIMER1_CLKSRC_USE_PCLK      0
#define DEFAULT_HSE_1MHZ_DIV        8    /* 8MHz / 8 = 1MHz */

/* I2C0 Port */
#define I2C0_SCL_PORT               2    /* Port C */
#define I2C0_SCL_PORT_ID            7
#define I2C0_SCL_MUX_ID             1
#define I2C0_SDA_PORT               2    /* Port C */
#define I2C0_SDA_PORT_ID            8
#define I2C0_SDA_MUX_ID             1

/* SPI0 Port */
#define SPI0_SS_PORT                0    /* Port A */
#define SPI0_SS_PORT_ID             12
#define SPI0_SS_MUX_ID              1
#define SPI0_SCK_PORT               0    /* Port A */
#define SPI0_SCK_PORT_ID            13
#define SPI0_SCK_MUX_ID             1
#define SPI0_MOSI_PORT              0    /* Port A */
#define SPI0_MOSI_PORT_ID           14
#define SPI0_MOSI_MUX_ID            1
#define SPI0_MISO_PORT              0    /* Port A */
#define SPI0_MISO_PORT_ID           15
#define SPI0_MISO_MUX_ID            1

/* TIMER10 Port */
#define TIMER10_OUT0_PORT           0    /* Port A */
#define TIMER10_OUT0_PORT_ID        4
#define TIMER10_OUT0_MUX_ID         2
#define TIMER10_CAP1_PORT           0    /* Port A */
#define TIMER10_CAP1_PORT_ID        5
#define TIMER10_CAP1_MUX_ID         2

/* TIMER10 External Clock Port */
#define TIMER10_EXTCLK_PORT         0    /* Port A */
#define TIMER10_EXTCLK_PORT_ID      6
#define TIMER10_EXTCLK_MUX_ID       2

/* UART1 Port */
#define UART1_TX_PORT               2    /* Port C */
#define UART1_TX_PORT_ID            6
#define UART1_TX_MUX_ID             1
#define UART1_RX_PORT               2    /* Port C */
#define UART1_RX_PORT_ID            5
#define UART1_RX_MUX_ID             1

/* ADC0 Port */
#define ADC0_IN_PORT                0    /* Port A */
#define ADC0_IN_PORT_ID             0
#define ADC0_IN_MUX_ID              7

/* ADC1 Port */
#define ADC1_IN_PORT                0    /* Port A */
#define ADC1_IN_PORT_ID             1
#define ADC1_IN_MUX_ID              7

/* ADC2 Port */
#define ADC2_IN_PORT                0    /* Port A */
#define ADC2_IN_PORT_ID             2
#define ADC2_IN_MUX_ID              7

#endif /* _STK_A34L716_VLN_A_H_ */
