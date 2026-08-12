/**
 *******************************************************************************
 * @file        bare.h
 * @author      ABOV R&D Division
 * @brief       Board configuration on which A31G32x is mounted
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
#define I2C0_SCL_PORT               1    /* Port B */
#define I2C0_SCL_PORT_ID            8
#define I2C0_SCL_MUX_ID             1
#define I2C0_SDA_PORT               1    /* Port B */
#define I2C0_SDA_PORT_ID            9
#define I2C0_SDA_MUX_ID             1

/* SPI0 Port */
#define SPI0_SS_PORT                0    /* Port A */
#define SPI0_SS_PORT_ID             4
#define SPI0_SS_MUX_ID              0
#define SPI0_SCK_PORT               0    /* Port A */
#define SPI0_SCK_PORT_ID            5
#define SPI0_SCK_MUX_ID             0
#define SPI0_MOSI_PORT              0    /* Port A */
#define SPI0_MOSI_PORT_ID           7
#define SPI0_MOSI_MUX_ID            0
#define SPI0_MISO_PORT              0    /* Port A */
#define SPI0_MISO_PORT_ID           6
#define SPI0_MISO_MUX_ID            0

/* TIMER10 Port */
#define TIMER10_OUT0_PORT           1    /* Port B */
#define TIMER10_OUT0_PORT_ID        14
#define TIMER10_OUT0_MUX_ID         6
#define TIMER10_CAP0_PORT           0    /* Port A */
#define TIMER10_CAP0_PORT_ID        3
#define TIMER10_CAP0_MUX_ID         5

/* TIMER10 External Clock Port */
#define TIMER10_EXTCLK_PORT         1    /* Port B */
#define TIMER10_EXTCLK_PORT_ID      15
#define TIMER10_EXTCLK_MUX_ID       4

/* TIMER20 Port */
#define TIMER20_OUT0_PORT           1    /* Port B */
#define TIMER20_OUT0_PORT_ID        3
#define TIMER20_OUT0_MUX_ID         6
#define TIMER20_CAP0_PORT           1    /* Port B */
#define TIMER20_CAP0_PORT_ID        10
#define TIMER20_CAP0_MUX_ID         5
#define TIMER20_OUT1_PORT           1    /* Port B */
#define TIMER20_OUT1_PORT_ID        5
#define TIMER20_OUT1_MUX_ID         6
#define TIMER20_CAP1_PORT           2    /* Port C */
#define TIMER20_CAP1_PORT_ID        5
#define TIMER20_CAP1_MUX_ID         5

/* TIMER20 External Clock Port */
#define TIMER20_EXTCLK_PORT         0    /* Port A */
#define TIMER20_EXTCLK_PORT_ID      5
#define TIMER20_EXTCLK_MUX_ID       4

/* TIMER30 Port */
#define TIMER30_PWMAA_PORT          0    /* Port A */
#define TIMER30_PWMAA_PORT_ID       8
#define TIMER30_PWMAA_MUX_ID        3
#define TIMER30_PWMAB_PORT          0    /* Port A */
#define TIMER30_PWMAB_PORT_ID       7
#define TIMER30_PWMAB_MUX_ID        3
#define TIMER30_PWMBA_PORT          0    /* Port A */
#define TIMER30_PWMBA_PORT_ID       9
#define TIMER30_PWMBA_MUX_ID        3
#define TIMER30_PWMBB_PORT          1    /* Port B */
#define TIMER30_PWMBB_PORT_ID       0
#define TIMER30_PWMBB_MUX_ID        3
#define TIMER30_PWMCA_PORT          0    /* Port A */
#define TIMER30_PWMCA_PORT_ID       10
#define TIMER30_PWMCA_MUX_ID        3
#define TIMER30_PWMCB_PORT          1    /* Port B */
#define TIMER30_PWMCB_PORT_ID       1
#define TIMER30_PWMCB_MUX_ID        3

/* TIMER30 Capture Port */
#define TIMER30_CAP_PORT            0    /* Port A */
#define TIMER30_CAP_PORT_ID         12
#define TIMER30_CAP_MUX_ID          4

/* TIMER30 External Clock Port */
#define TIMER30_EXTCLK_PORT         0    /* Port A */
#define TIMER30_EXTCLK_PORT_ID      12
#define TIMER30_EXTCLK_MUX_ID       3

/* TIMER30 BLNK Port */
#define TIMER30_BLNK_PORT           0    /* Port A */
#define TIMER30_BLNK_PORT_ID        6
#define TIMER30_BLNK_MUX_ID         3

/* TIMER40 Port */
#define TIMER40_OUT0_PORT           0    /* Port A */
#define TIMER40_OUT0_PORT_ID        0
#define TIMER40_OUT0_MUX_ID         8
#define TIMER40_CAP0_PORT           1    /* Port B */
#define TIMER40_CAP0_PORT_ID        4
#define TIMER40_CAP0_MUX_ID         7
#define TIMER40_CAP1_PORT           2    /* Port C */
#define TIMER40_CAP1_PORT_ID        7
#define TIMER40_CAP1_MUX_ID         7
#define TIMER40_CAP2_PORT           2    /* Port C */
#define TIMER40_CAP2_PORT_ID        8
#define TIMER40_CAP2_MUX_ID         7

/* TIMER40 External Clock Port */
#define TIMER40_EXTCLK_PORT         2    /* Port C */
#define TIMER40_EXTCLK_PORT_ID      9
#define TIMER40_EXTCLK_MUX_ID       7

/* USART1 Port */
#define USART1_TX_PORT              0    /* Port A */
#define USART1_TX_PORT_ID           2
#define USART1_TX_MUX_ID            0
#define USART1_RX_PORT              0    /* Port A */
#define USART1_RX_PORT_ID           3
#define USART1_RX_MUX_ID            0

/* USART1 SPI Port */
#define USART1_SS_PORT              0    /* Port A */
#define USART1_SS_PORT_ID           1
#define USART1_SS_MUX_ID            2
#define USART1_SCK_PORT             0    /* Port A */
#define USART1_SCK_PORT_ID          4
#define USART1_SCK_MUX_ID           2
#define USART1_MOSI_PORT            0    /* Port A */
#define USART1_MOSI_PORT_ID         2
#define USART1_MOSI_MUX_ID          2
#define USART1_MISO_PORT            0    /* Port A */
#define USART1_MISO_PORT_ID         3
#define USART1_MISO_MUX_ID          2

/* DAC0 Port */
#define DAC0_OUT_PORT               0    /* Port A */
#define DAC0_OUT_PORT_ID            4
#define DAC0_OUT_MUX_ID             10

/* ADC0 Port */
#define ADC0_IN_PORT                0    /* Port A */
#define ADC0_IN_PORT_ID             0
#define ADC0_IN_MUX_ID              10

/* ADC1 Port */
#define ADC1_IN_PORT                0    /* Port A */
#define ADC1_IN_PORT_ID             1
#define ADC1_IN_MUX_ID              10

/* ADC2 Port */
#define ADC2_IN_PORT                0    /* Port A */
#define ADC2_IN_PORT_ID             2
#define ADC2_IN_MUX_ID              10

/* CLKO Port */
#define CLKO_PORT                   5    /* Port F */
#define CLKO_PORT_ID                0
#define CLKO_MUX_ID                 1

/* CMP0 Port */
#define CMP0_IN_PORT                0    /* Port A */
#define CMP0_IN_PORT_ID             0
#define CMP0_IN_MUX_ID              10

/* CMP1 Port */
#define CMP1_IN_PORT                0    /* Port A */
#define CMP1_IN_PORT_ID             1
#define CMP1_IN_MUX_ID              10

/* CMP2 Port */
#define CMP2_IN_PORT                0    /* Port A */
#define CMP2_IN_PORT_ID             2
#define CMP2_IN_MUX_ID              10

/* CMP3 Port */
#define CMP3_IN_PORT                0    /* Port A */
#define CMP3_IN_PORT_ID             3
#define CMP3_IN_MUX_ID              10

/* CMP4 Port */
#define CMP4_IN_PORT                0    /* Port A */
#define CMP4_IN_PORT_ID             4
#define CMP4_IN_MUX_ID              10

/* CMP5 Port */
#define CMP5_IN_PORT                0    /* Port A */
#define CMP5_IN_PORT_ID             5
#define CMP5_IN_MUX_ID              10

/* CMP6 Port */
#define CMP6_IN_PORT                2    /* Port C */
#define CMP6_IN_PORT_ID             0
#define CMP6_IN_MUX_ID              10

/* CMP7 Port */
#define CMP7_IN_PORT                2    /* Port C */
#define CMP7_IN_PORT_ID             1
#define CMP7_IN_MUX_ID              10

/* EBI AD0 Port (PB5) */
#define EBI_AD0_PORT                1   /* Port B */
#define EBI_AD0_PORT_ID             5
#define EBI_AD0_MUX_ID              9

/* EBI AD0 Port (PC1) */
/* #define EBI_AD0_PORT                2    */ /* Port C */
/* #define EBI_AD0_PORT_ID             1    */
/* #define EBI_AD0_MUX_ID              9    */

/* EBI AD1 Port (PB4) */
#define EBI_AD1_PORT                1   /* Port B */
#define EBI_AD1_PORT_ID             4
#define EBI_AD1_MUX_ID              9

/* EBI AD1 Port (PC2) */
/* #define EBI_AD1_PORT                2    */ /* Port C */
/* #define EBI_AD1_PORT_ID             2    */
/* #define EBI_AD1_MUX_ID              9    */

/* EBI AD2 Port (PB2) */
#define EBI_AD2_PORT                1   /* Port B */
#define EBI_AD2_PORT_ID             3
#define EBI_AD2_MUX_ID              9

/* EBI AD2 Port (PC3) */
/* #define EBI_AD2_PORT                2    */ /* Port C */
/* #define EBI_AD2_PORT_ID             3    */
/* #define EBI_AD2_MUX_ID              9    */

/* EBI AD3 Port (PA12) */
#define EBI_AD3_PORT                0   /* Port A */
#define EBI_AD3_PORT_ID             12
#define EBI_AD3_MUX_ID              9

/* EBI AD4 Port (PA11) */
#define EBI_AD4_PORT                0   /* Port A */
#define EBI_AD4_PORT_ID             11
#define EBI_AD4_MUX_ID              9

/* EBI AD5 Port (PA10) */
#define EBI_AD5_PORT                0   /* Port A */
#define EBI_AD5_PORT_ID             10
#define EBI_AD5_MUX_ID              9

/* EBI AD6 Port (PA9) */
#define EBI_AD6_PORT                0   /* Port A */
#define EBI_AD6_PORT_ID             9
#define EBI_AD6_MUX_ID              9

/* EBI AD7 Port (PA8) */
#define EBI_AD7_PORT                0   /* Port A */
#define EBI_AD7_PORT_ID             8
#define EBI_AD7_MUX_ID              9

/* EBI AD8 Port (PB15) */
#define EBI_AD8_PORT                1   /* Port B */
#define EBI_AD8_PORT_ID             15
#define EBI_AD8_MUX_ID              9

/* EBI AD9 Port (PA14) */
#define EBI_AD9_PORT                1   /* Port B */
#define EBI_AD9_PORT_ID             14
#define EBI_AD9_MUX_ID              9

/* EBI AD10 Port (PA13) */
#define EBI_AD10_PORT               1   /* Port B */
#define EBI_AD10_PORT_ID            13
#define EBI_AD10_MUX_ID             9

/* EBI AD11 Port (PA12) */
#define EBI_AD11_PORT               1   /* Port B */
#define EBI_AD11_PORT_ID            12
#define EBI_AD11_MUX_ID             9

/* EBI AD12 Port (PA11) */
#define EBI_AD12_PORT               1   /* Port B */
#define EBI_AD12_PORT_ID            11
#define EBI_AD12_MUX_ID             9

/* EBI AD13 Port (PA10) */
#define EBI_AD13_PORT               1   /* Port B */
#define EBI_AD13_PORT_ID            10
#define EBI_AD13_MUX_ID             9

/* EBI AD14 Port (PB2) */
#define EBI_AD14_PORT               1   /* Port B */
#define EBI_AD14_PORT_ID            2
#define EBI_AD14_MUX_ID             9

/* EBI AD15 Port (PB1) */
#define EBI_AD15_PORT               1   /* Port B */
#define EBI_AD15_PORT_ID            1
#define EBI_AD15_MUX_ID             9

/* EBI A16 Port (PB5) */
#define EBI_A16_PORT                1   /* Port B */
#define EBI_A16_PORT_ID             5
#define EBI_A16_MUX_ID              9

/* EBI A17 Port (PC5) */
#define EBI_A17_PORT                2   /* Port C */
#define EBI_A17_PORT_ID             5
#define EBI_A17_MUX_ID              9

/* EBI A18 Port (PC4) */
#define EBI_A18_PORT                2   /* Port C */
#define EBI_A18_PORT_ID             4
#define EBI_A18_MUX_ID              9

/* EBI A19 Port (PA7) */
#define EBI_A19_PORT                0   /* Port A */
#define EBI_A19_PORT_ID             7
#define EBI_A19_MUX_ID              9

/* EBI ALE Port (PA15) */
#define EBI_ALE_PORT                0   /* Port A */
#define EBI_ALE_PORT_ID             15
#define EBI_ALE_MUX_ID              9

/* EBI UDS Port (PC7) */
#define EBI_UDS_PORT                2   /* Port C */
#define EBI_UDS_PORT_ID             7
#define EBI_UDS_MUX_ID              9

/* EBI LDS Port (PC10) */
#define EBI_LDS_PORT                2   /* Port C */
#define EBI_LDS_PORT_ID             10
#define EBI_LDS_MUX_ID              9

/* EBI UWR Port (PC8) */
#define EBI_UWR_PORT                2   /* Port C */
#define EBI_UWR_PORT_ID             8
#define EBI_UWR_MUX_ID              9

/* EBI LWR Port (PC0) */
#define EBI_LWR_PORT                2   /* Port C */
#define EBI_LWR_PORT_ID             0
#define EBI_LWR_MUX_ID              9

/* EBI LWR Port (PC0) */
/* #define EBI_LWR_PORT                2    */ /* Port C */
/* #define EBI_LWR_PORT_ID             0    */
/* #define EBI_LWR_MUX_ID              9    */

/* EBI RD Port (PA6) */
#define EBI_RD_PORT                 0   /* Port A */
#define EBI_RD_PORT_ID              6
#define EBI_RD_MUX_ID               9

/* EBI CS0 Port (PB7) */
#define EBI_CS0_PORT                1   /* Port B */
#define EBI_CS0_PORT_ID             7
#define EBI_CS0_MUX_ID              9

/* EBI CS1 Port (PF2) */
#define EBI_CS1_PORT                5   /* Port F */
#define EBI_CS1_PORT_ID             2
#define EBI_CS1_MUX_ID              9

/* EBI CS2 Port (PF12) */
#define EBI_CS2_PORT                5   /* Port B */
#define EBI_CS2_PORT_ID             12
#define EBI_CS2_MUX_ID              9

/* EBI CS3 Port (PC9) */
#define EBI_CS3_PORT                2   /* Port C */
#define EBI_CS3_PORT_ID             9
#define EBI_CS3_MUX_ID              9

/* EBI NWAIT Port (PC9) */
#define EBI_NWAIT_PORT              2   /* Port C */
#define EBI_NWAIT_PORT_ID           6
#define EBI_NWAIT_MUX_ID            9

/* RTC0 Port */
#define RTC0_IN_PORT                2    /* Port C */
#define RTC0_IN_PORT_ID             13 
#define RTC0_IN_MUX_ID              7

#endif /* _BARE_H_ */
