/**
 *******************************************************************************
 * @file        bare.h
 * @author      ABOV R&D Division
 * @brief       Board configuration on which A31G21x is mounted
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
#define TIMER1_CLKSRC_USE_PCLK      0
#define DEFAULT_HSE_1MHZ_DIV        8    /* 8MHz / 8 = 1MHz */

/* I2C0 Port */
#define I2C0_SCL_PORT               3    /* Port D */
#define I2C0_SCL_PORT_ID            0
#define I2C0_SCL_MUX_ID             1
#define I2C0_SDA_PORT               3    /* Port D */
#define I2C0_SDA_PORT_ID            1
#define I2C0_SDA_MUX_ID             1

/* SPI0 Port */
#define SPI0_SS_PORT                3    /* Port D */
#define SPI0_SS_PORT_ID             0
#define SPI0_SS_MUX_ID              2
#define SPI0_SCK_PORT               2    /* Port C */
#define SPI0_SCK_PORT_ID            4
#define SPI0_SCK_MUX_ID             2
#define SPI0_MOSI_PORT              2    /* Port C */
#define SPI0_MOSI_PORT_ID           2
#define SPI0_MOSI_MUX_ID            2
#define SPI0_MISO_PORT              2    /* Port C */
#define SPI0_MISO_PORT_ID           3
#define SPI0_MISO_MUX_ID            2

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

/* TIMER20 Port */
#define TIMER20_OUT0_PORT           2    /* Port C */
#define TIMER20_OUT0_PORT_ID        0
#define TIMER20_OUT0_MUX_ID         1
#define TIMER20_CAP0_PORT           2    /* Port C */
#define TIMER20_CAP0_PORT_ID        0
#define TIMER20_CAP0_MUX_ID         2
#define TIMER20_OUT1_PORT           2    /* Port C */
#define TIMER20_OUT1_PORT_ID        1
#define TIMER20_OUT1_MUX_ID         1
#define TIMER20_CAP1_PORT           2    /* Port C */
#define TIMER20_CAP1_PORT_ID        1
#define TIMER20_CAP1_MUX_ID         2

/* TIMER20 External Clock Port */
#define TIMER20_EXTCLK_PORT         2    /* Port C */
#define TIMER20_EXTCLK_PORT_ID      2
#define TIMER20_EXTCLK_MUX_ID       1

/* TIMER30 Port */
#define TIMER30_PWMAA_PORT          4    /* Port E */
#define TIMER30_PWMAA_PORT_ID       0
#define TIMER30_PWMAA_MUX_ID        1
#define TIMER30_PWMAB_PORT          4    /* Port E */
#define TIMER30_PWMAB_PORT_ID       1
#define TIMER30_PWMAB_MUX_ID        1
#define TIMER30_PWMBA_PORT          4    /* Port E */
#define TIMER30_PWMBA_PORT_ID       2
#define TIMER30_PWMBA_MUX_ID        1
#define TIMER30_PWMBB_PORT          4    /* Port E */
#define TIMER30_PWMBB_PORT_ID       3
#define TIMER30_PWMBB_MUX_ID        1
#define TIMER30_PWMCA_PORT          4    /* Port E */
#define TIMER30_PWMCA_PORT_ID       4
#define TIMER30_PWMCA_MUX_ID        1
#define TIMER30_PWMCB_PORT          4    /* Port E */
#define TIMER30_PWMCB_PORT_ID       5
#define TIMER30_PWMCB_MUX_ID        1

/* TIMER30 Capture Port */
#define TIMER30_CAP_PORT            5    /* Port F */
#define TIMER30_CAP_PORT_ID         7
#define TIMER30_CAP_MUX_ID          1

/* TIMER30 External Clock Port */
#define TIMER30_EXTCLK_PORT         5    /* Port F */
#define TIMER30_EXTCLK_PORT_ID      2
#define TIMER30_EXTCLK_MUX_ID       2

/* TIMER30 BLNK Port */
#define TIMER30_BLNK_PORT           5    /* Port F */
#define TIMER30_BLNK_PORT_ID        5
#define TIMER30_BLNK_MUX_ID         1

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

/* ADC1 Port */
#define ADC1_IN_PORT                0    /* Port A */
#define ADC1_IN_PORT_ID             1
#define ADC1_IN_MUX_ID              3

/* ADC2 Port */
#define ADC2_IN_PORT                0    /* Port A */
#define ADC2_IN_PORT_ID             2
#define ADC2_IN_MUX_ID              3

/* CLKO Port */
#define CLKO_PORT                   5    /* Port F */
#define CLKO_PORT_ID                4
#define CLKO_MUX_ID                 1

/* LED ISEG Port */
#define LED_ISEG0_ID                4    /* Port E */
#define LED_ISEG0_PORT_ID           2    
#define LED_ISEG0_MUX_ID            4

#define LED_ISEG1_ID                4    /* Port E */
#define LED_ISEG1_PORT_ID           3    
#define LED_ISEG1_MUX_ID            4

#define LED_ISEG2_ID                4    /* Port E */
#define LED_ISEG2_PORT_ID           4    
#define LED_ISEG2_MUX_ID            4

#define LED_ISEG3_ID                4    /* Port E */
#define LED_ISEG3_PORT_ID           5    
#define LED_ISEG3_MUX_ID            4

#define LED_ISEG4_ID                4    /* Port E */
#define LED_ISEG4_PORT_ID           6    
#define LED_ISEG4_MUX_ID            4

#define LED_ISEG5_ID                4    /* Port E */
#define LED_ISEG5_PORT_ID           7    
#define LED_ISEG5_MUX_ID            4

#define LED_ISEG6_ID                3    /* Port D */
#define LED_ISEG6_PORT_ID           5    
#define LED_ISEG6_MUX_ID            4

#define LED_ISEG7_ID                3    /* Port D */
#define LED_ISEG7_PORT_ID           4    
#define LED_ISEG7_MUX_ID            4

#define LED_ISEG8_ID                3    /* Port D */
#define LED_ISEG8_PORT_ID           3    
#define LED_ISEG8_MUX_ID            4

#define LED_ISEG9_ID                3    /* Port D */
#define LED_ISEG9_PORT_ID           2    
#define LED_ISEG9_MUX_ID            4

/* LED ICOM Port */
#define LED_ICOM0_ID                3    /* Port D */
#define LED_ICOM0_PORT_ID           1    
#define LED_ICOM0_MUX_ID            4

#define LED_ICOM1_ID                3    /* Port D */
#define LED_ICOM1_PORT_ID           0    
#define LED_ICOM1_MUX_ID            4

#define LED_ICOM2_ID                2    /* Port C */
#define LED_ICOM2_PORT_ID           4    
#define LED_ICOM2_MUX_ID            4

#define LED_ICOM3_ID                2    /* Port C */
#define LED_ICOM3_PORT_ID           3    
#define LED_ICOM3_MUX_ID            4

#define LED_ICOM4_ID                2    /* Port C */
#define LED_ICOM4_PORT_ID           2    
#define LED_ICOM4_MUX_ID            4

#define LED_ICOM5_ID                2    /* Port C */
#define LED_ICOM5_PORT_ID           1    
#define LED_ICOM5_MUX_ID            4

#define LED_ICOM6_ID                2    /* Port C */
#define LED_ICOM6_PORT_ID           0    
#define LED_ICOM6_MUX_ID            4

#define LED_ICOM7_ID                1    /* Port B */
#define LED_ICOM7_PORT_ID           2    
#define LED_ICOM7_MUX_ID            4

#define LED_ICOM8_ID                1    /* Port B */
#define LED_ICOM8_PORT_ID           1    
#define LED_ICOM8_MUX_ID            4

#define LED_ICOM9_ID                1    /* Port B */
#define LED_ICOM9_PORT_ID           0    
#define LED_ICOM9_MUX_ID            4

#define LED_ICOM10_ID               0    /* Port A */
#define LED_ICOM10_PORT_ID          7    
#define LED_ICOM10_MUX_ID           4

#define LED_ICOM11_ID               0    /* Port A */
#define LED_ICOM11_PORT_ID          6    
#define LED_ICOM11_MUX_ID           4

#define LED_ICOM12_ID               0    /* Port A */
#define LED_ICOM12_PORT_ID          5    
#define LED_ICOM12_MUX_ID           4

#define LED_ICOM13_ID               0    /* Port A */
#define LED_ICOM13_PORT_ID          4    
#define LED_ICOM13_MUX_ID           4

#define LED_ICOM14_ID               0    /* Port A */
#define LED_ICOM14_PORT_ID          3    
#define LED_ICOM14_MUX_ID           4

#define LED_ICOM15_ID               0    /* Port A */
#define LED_ICOM15_PORT_ID          2   
#define LED_ICOM15_MUX_ID           4

#endif /* _BARE_H_ */
