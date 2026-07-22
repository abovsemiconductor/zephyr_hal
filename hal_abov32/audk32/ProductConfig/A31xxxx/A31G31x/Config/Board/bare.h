/**
 *******************************************************************************
 * @file        bare.h
 * @author      ABOV R&D Division
 * @brief       Board configuration on which A31G31x is mounted
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
#define DEFAULT_HSE_1MHZ_DIV        16    /* 16MHz / 16 = 1MHz */

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
#define TIMER10_EXTCLK_PORT         2    /* Port C */
#define TIMER10_EXTCLK_PORT_ID      11
#define TIMER10_EXTCLK_MUX_ID       1

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
#define TIMER30_EXTCLK_PORT_ID      6
#define TIMER30_EXTCLK_MUX_ID       1

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
#define DAC0_OUT_PORT_ID            6
#define DAC0_OUT_MUX_ID             3

/* LCD0 Port */
#define LCD0_SEG0_PORT              4    /* Port E */
#define LCD0_SEG0_PORT_ID           3
#define LCD0_SEG0_MUX_ID            0
#define LCD0_SEG1_PORT              4    /* Port E */
#define LCD0_SEG1_PORT_ID           4
#define LCD0_SEG1_MUX_ID            0
#define LCD0_SEG2_PORT              4    /* Port E */
#define LCD0_SEG2_PORT_ID           5
#define LCD0_SEG2_MUX_ID            0
#define LCD0_SEG3_PORT              4    /* Port E */
#define LCD0_SEG3_PORT_ID           6
#define LCD0_SEG3_MUX_ID            0
#define LCD0_SEG4_PORT              4    /* Port E */
#define LCD0_SEG4_PORT_ID           7
#define LCD0_SEG4_MUX_ID            0
#define LCD0_SEG5_PORT              4    /* Port E */
#define LCD0_SEG5_PORT_ID           14
#define LCD0_SEG5_MUX_ID            0
#define LCD0_SEG6_PORT              4    /* Port E */
#define LCD0_SEG6_PORT_ID           15
#define LCD0_SEG6_MUX_ID            0
#define LCD0_SEG7_PORT              3    /* Port D */
#define LCD0_SEG7_PORT_ID           5
#define LCD0_SEG7_MUX_ID            0
#define LCD0_SEG8_PORT              3    /* Port D */
#define LCD0_SEG8_PORT_ID           4
#define LCD0_SEG8_MUX_ID            0
#define LCD0_SEG9_PORT              3    /* Port D */
#define LCD0_SEG9_PORT_ID           3
#define LCD0_SEG9_MUX_ID            0
#define LCD0_SEG10_PORT             3    /* Port D */
#define LCD0_SEG10_PORT_ID          2
#define LCD0_SEG10_MUX_ID           0
#define LCD0_SEG11_PORT             3    /* Port D */
#define LCD0_SEG11_PORT_ID          1
#define LCD0_SEG11_MUX_ID           0
#define LCD0_SEG12_PORT             3    /* Port D */
#define LCD0_SEG12_PORT_ID          0
#define LCD0_SEG12_MUX_ID           0
#define LCD0_SEG13_PORT             2    /* Port C */
#define LCD0_SEG13_PORT_ID          12
#define LCD0_SEG13_MUX_ID           0
#define LCD0_SEG14_PORT             2    /* Port C */
#define LCD0_SEG14_PORT_ID          11
#define LCD0_SEG14_MUX_ID           0
#define LCD0_SEG15_PORT             2    /* Port C */
#define LCD0_SEG15_PORT_ID          10
#define LCD0_SEG15_MUX_ID           0
#define LCD0_SEG16_PORT             2    /* Port C */
#define LCD0_SEG16_PORT_ID          9
#define LCD0_SEG16_MUX_ID           0
#define LCD0_SEG17_PORT             2    /* Port C */
#define LCD0_SEG17_PORT_ID          8
#define LCD0_SEG17_MUX_ID           0
#define LCD0_SEG18_PORT             2    /* Port C */
#define LCD0_SEG18_PORT_ID          7
#define LCD0_SEG18_MUX_ID           0
#define LCD0_SEG19_PORT             2    /* Port C */
#define LCD0_SEG19_PORT_ID          6
#define LCD0_SEG19_MUX_ID           0
#define LCD0_SEG20_PORT             2    /* Port C */
#define LCD0_SEG20_PORT_ID          5
#define LCD0_SEG20_MUX_ID           0
#define LCD0_SEG21_PORT             2    /* Port C */
#define LCD0_SEG21_PORT_ID          4
#define LCD0_SEG21_MUX_ID           0
#define LCD0_SEG22_PORT             2    /* Port C */
#define LCD0_SEG22_PORT_ID          3
#define LCD0_SEG22_MUX_ID           0
#define LCD0_SEG23_PORT             2    /* Port C */
#define LCD0_SEG23_PORT_ID          2
#define LCD0_SEG23_MUX_ID           0
#define LCD0_SEG24_PORT             2    /* Port C */
#define LCD0_SEG24_PORT_ID          1
#define LCD0_SEG24_MUX_ID           0
#define LCD0_SEG25_PORT             2    /* Port C */
#define LCD0_SEG25_PORT_ID          0
#define LCD0_SEG25_MUX_ID           0
#define LCD0_SEG26_PORT             1    /* Port B */
#define LCD0_SEG26_PORT_ID          15
#define LCD0_SEG26_MUX_ID           0
#define LCD0_SEG27_PORT             1    /* Port B */
#define LCD0_SEG27_PORT_ID          14
#define LCD0_SEG27_MUX_ID           0
#define LCD0_SEG28_PORT             1    /* Port B */
#define LCD0_SEG28_PORT_ID          13
#define LCD0_SEG28_MUX_ID           0
#define LCD0_SEG29_PORT             1    /* Port B */
#define LCD0_SEG29_PORT_ID          12
#define LCD0_SEG29_MUX_ID           0
#define LCD0_SEG30_PORT             1    /* Port B */
#define LCD0_SEG30_PORT_ID          11
#define LCD0_SEG30_MUX_ID           0
#define LCD0_SEG31_PORT             1    /* Port B */
#define LCD0_SEG31_PORT_ID          10
#define LCD0_SEG31_MUX_ID           0
#define LCD0_SEG32_PORT             1    /* Port B */
#define LCD0_SEG32_PORT_ID          9
#define LCD0_SEG32_MUX_ID           0
#define LCD0_SEG33_PORT             1    /* Port B */
#define LCD0_SEG33_PORT_ID          8
#define LCD0_SEG33_MUX_ID           0
#define LCD0_SEG34_PORT             1    /* Port B */
#define LCD0_SEG34_PORT_ID          7
#define LCD0_SEG34_MUX_ID           0
#define LCD0_SEG35_PORT             1    /* Port B */
#define LCD0_SEG35_PORT_ID          6
#define LCD0_SEG35_MUX_ID           0
#define LCD0_SEG36_PORT             1    /* Port B */
#define LCD0_SEG36_PORT_ID          5
#define LCD0_SEG36_MUX_ID           0
#define LCD0_SEG37_PORT             1    /* Port B */
#define LCD0_SEG37_PORT_ID          4
#define LCD0_SEG37_MUX_ID           0
#define LCD0_SEG38_PORT             1    /* Port B */
#define LCD0_SEG38_PORT_ID          3
#define LCD0_SEG38_MUX_ID           0
#define LCD0_SEG39_PORT             1    /* Port B */
#define LCD0_SEG39_PORT_ID          2
#define LCD0_SEG39_MUX_ID           0
#define LCD0_SEG40_PORT             1    /* Port B */
#define LCD0_SEG40_PORT_ID          1
#define LCD0_SEG40_MUX_ID           0
#define LCD0_SEG41_PORT             1    /* Port B */
#define LCD0_SEG41_PORT_ID          0
#define LCD0_SEG41_MUX_ID           0
#define LCD0_SEG42_PORT             0    /* Port A */
#define LCD0_SEG42_PORT_ID          7
#define LCD0_SEG42_MUX_ID           0
#define LCD0_SEG43_PORT             0    /* Port A */
#define LCD0_SEG43_PORT_ID          6
#define LCD0_SEG43_MUX_ID           0

#define LCD0_COM0_PORT              4    /* Port E */
#define LCD0_COM0_PORT_ID           0
#define LCD0_COM0_MUX_ID            0
#define LCD0_COM1_PORT              4    /* Port E */
#define LCD0_COM1_PORT_ID           1
#define LCD0_COM1_MUX_ID            0
#define LCD0_COM2_PORT              4    /* Port E */
#define LCD0_COM2_PORT_ID           2
#define LCD0_COM2_MUX_ID            0
#define LCD0_COM3_PORT              4    /* Port E */
#define LCD0_COM3_PORT_ID           3
#define LCD0_COM3_MUX_ID            0
#define LCD0_COM4_PORT              4    /* Port E */
#define LCD0_COM4_PORT_ID           4
#define LCD0_COM4_MUX_ID            0
#define LCD0_COM5_PORT              4    /* Port E */
#define LCD0_COM5_PORT_ID           5
#define LCD0_COM5_MUX_ID            0
#define LCD0_COM6_PORT              4    /* Port E */
#define LCD0_COM6_PORT_ID           6
#define LCD0_COM6_MUX_ID            0
#define LCD0_COM7_PORT              4    /* Port E */
#define LCD0_COM7_PORT_ID           7
#define LCD0_COM7_MUX_ID            0

#define LCD0_VLC0_PORT              4    /* Port E */
#define LCD0_VLC0_PORT_ID           8
#define LCD0_VLC0_MUX_ID            0
#define LCD0_VLC1_PORT              4    /* Port E */
#define LCD0_VLC1_PORT_ID           9
#define LCD0_VLC1_MUX_ID            0
#define LCD0_VLC2_PORT              4    /* Port E */
#define LCD0_VLC2_PORT_ID           10
#define LCD0_VLC2_MUX_ID            0
#define LCD0_VLC3_PORT              4    /* Port E */
#define LCD0_VLC3_PORT_ID           11
#define LCD0_VLC3_MUX_ID            0

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

/* CMP0 Port */
#define CMP0_IN_PORT                0    /* Port A */
#define CMP0_IN_PORT_ID             2
#define CMP0_IN_MUX_ID              3

/* CMP1 Port */
#define CMP1_IN_PORT                0    /* Port A */
#define CMP1_IN_PORT_ID             3
#define CMP1_IN_MUX_ID              3

/* CMP2 Port */
#define CMP2_IN_PORT                0    /* Port A */
#define CMP2_IN_PORT_ID             4
#define CMP2_IN_MUX_ID              3

/* CMP3 Port */
#define CMP3_IN_PORT                0    /* Port A */
#define CMP3_IN_PORT_ID             5
#define CMP3_IN_MUX_ID              3

/* CMP4 Port */
#define CMP4_IN_PORT                0    /* Port A */
#define CMP4_IN_PORT_ID             6
#define CMP4_IN_MUX_ID              3

/* CMP5 Port */
#define CMP5_IN_PORT                0    /* Port A */
#define CMP5_IN_PORT_ID             7
#define CMP5_IN_MUX_ID              3

/* CLKO Port */
#define CLKO_PORT                   5    /* Port F */
#define CLKO_PORT_ID                4
#define CLKO_MUX_ID                 1

/* LED ISEG Port */
#define LED_ISEG0_ID                1    /* Port B */
#define LED_ISEG0_PORT_ID           1    
#define LED_ISEG0_MUX_ID            4

#define LED_ISEG1_ID                1    /* Port B */
#define LED_ISEG1_PORT_ID           0    
#define LED_ISEG1_MUX_ID            4

#define LED_ISEG2_ID                0    /* Port A */
#define LED_ISEG2_PORT_ID           7    
#define LED_ISEG2_MUX_ID            4

#define LED_ISEG3_ID                0    /* Port A */
#define LED_ISEG3_PORT_ID           6    
#define LED_ISEG3_MUX_ID            4

#define LED_ISEG4_ID                0    /* Port A */
#define LED_ISEG4_PORT_ID           5    
#define LED_ISEG4_MUX_ID            4

#define LED_ISEG5_ID                0    /* Port A */
#define LED_ISEG5_PORT_ID           4    
#define LED_ISEG5_MUX_ID            4

#define LED_ISEG6_ID                0    /* Port A */
#define LED_ISEG6_PORT_ID           3    
#define LED_ISEG6_MUX_ID            4

#define LED_ISEG7_ID                0    /* Port A */
#define LED_ISEG7_PORT_ID           2    
#define LED_ISEG7_MUX_ID            4

#define LED_ISEG8_ID                0    /* Port A */
#define LED_ISEG8_PORT_ID           1    
#define LED_ISEG8_MUX_ID            4

#define LED_ISEG9_ID                0    /* Port A */
#define LED_ISEG9_PORT_ID           0    
#define LED_ISEG9_MUX_ID            4

#define LED_ISEG10_ID               5    /* Port F */
#define LED_ISEG10_PORT_ID          0    
#define LED_ISEG10_MUX_ID           4

/* LED ICOM Port */
#define LED_ICOM0_ID                4    /* Port E */
#define LED_ICOM0_PORT_ID           0    
#define LED_ICOM0_MUX_ID            4

#define LED_ICOM1_ID                4    /* Port E */
#define LED_ICOM1_PORT_ID           1    
#define LED_ICOM1_MUX_ID            4

#define LED_ICOM2_ID                4    /* Port E */
#define LED_ICOM2_PORT_ID           2    
#define LED_ICOM2_MUX_ID            4

#define LED_ICOM3_ID                4    /* Port E */
#define LED_ICOM3_PORT_ID           3    
#define LED_ICOM3_MUX_ID            4

#define LED_ICOM4_ID                4    /* Port E */
#define LED_ICOM4_PORT_ID           4    
#define LED_ICOM4_MUX_ID            4

#define LED_ICOM5_ID                4    /* Port E */
#define LED_ICOM5_PORT_ID           5    
#define LED_ICOM5_MUX_ID            4

#define LED_ICOM6_ID                4    /* Port E */
#define LED_ICOM6_PORT_ID           6    
#define LED_ICOM6_MUX_ID            4

#define LED_ICOM7_ID                4    /* Port E */
#define LED_ICOM7_PORT_ID           7    
#define LED_ICOM7_MUX_ID            4

#define LED_ICOM8_ID                3    /* Port D */
#define LED_ICOM8_PORT_ID           5    
#define LED_ICOM8_MUX_ID            4

#define LED_ICOM9_ID                3    /* Port D */
#define LED_ICOM9_PORT_ID           4    
#define LED_ICOM9_MUX_ID            4

#define LED_ICOM10_ID               3    /* Port D */
#define LED_ICOM10_PORT_ID          3    
#define LED_ICOM10_MUX_ID           4

#define LED_ICOM11_ID               3    /* Port D */
#define LED_ICOM11_PORT_ID          2    
#define LED_ICOM11_MUX_ID           4

#define LED_ICOM12_ID               3    /* Port D */
#define LED_ICOM12_PORT_ID          1    
#define LED_ICOM12_MUX_ID           4

#define LED_ICOM13_ID               3    /* Port D */
#define LED_ICOM13_PORT_ID          0    
#define LED_ICOM13_MUX_ID           4

#define LED_ICOM14_ID               2    /* Port C */
#define LED_ICOM14_PORT_ID          4    
#define LED_ICOM14_MUX_ID           4

#define LED_ICOM15_ID               2    /* Port C */
#define LED_ICOM15_PORT_ID          3    
#define LED_ICOM15_MUX_ID           4

#define LED_ICOM16_ID               2    /* Port C */
#define LED_ICOM16_PORT_ID          2    
#define LED_ICOM16_MUX_ID           4

#define LED_ICOM17_ID               2    /* Port C */
#define LED_ICOM17_PORT_ID          1    
#define LED_ICOM17_MUX_ID           4

#define LED_ICOM18_ID               2    /* Port C */
#define LED_ICOM18_PORT_ID          0    
#define LED_ICOM18_MUX_ID           4

/* system */
#define LED_ICOM19_ID               2    /* Port C */
#define LED_ICOM19_PORT_ID          0    
#define LED_ICOM19_MUX_ID           4

#define LED_ICOM20_ID               2    /* Port C */
#define LED_ICOM20_PORT_ID          0    
#define LED_ICOM20_MUX_ID           4

#define LED_ICOM21_ID               2    /* Port C */
#define LED_ICOM21_PORT_ID          0    
#define LED_ICOM21_MUX_ID           4

#define LED_ICOM22_ID               2    /* Port C */
#define LED_ICOM22_PORT_ID          0    
#define LED_ICOM22_MUX_ID           4

#define LED_ICOM23_ID               2    /* Port C */
#define LED_ICOM23_PORT_ID          0    
#define LED_ICOM23_MUX_ID           4
/* system */
#define LED_ICOM24_ID               1    /* Port B */
#define LED_ICOM24_PORT_ID          2    
#define LED_ICOM24_MUX_ID           4

#define LED_ICOM25_ID               1    /* Port B */
#define LED_ICOM25_PORT_ID          1    
#define LED_ICOM25_MUX_ID           4

#define LED_ICOM26_ID               1    /* Port B */
#define LED_ICOM26_PORT_ID          0    
#define LED_ICOM26_MUX_ID           4

#endif /* _BARE_H_ */
