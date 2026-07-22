/**
 *******************************************************************************
 * @file        stk_a34g43a_yln_a.h
 * @author      ABOV R&D Division
 * @brief       STK (Startup Kit Board on which A34G43AYLN is mounted)
 *
 * Copyright 2025 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _STK_A34G43A_YLN_A_
#define _STK_A34G43A_YLN_A_

/* STK LED */
#define FIRST_LED_ID                0
#define LAST_LED_ID                 5
#define LED_PORT_ID                 1    /* Port B */

#define USER_SW1_PORT               2   /* Port C */
#define USER_SW1_PORT_ID            9
#define USER_SW1_IRQ_NUM            GPIOC_IRQn
#define USER_SW2_PORT               4   /* Port E */
#define USER_SW2_PORT_ID            0
#define USER_SW2_IRQ_NUM            GPIOE_IRQn

/* MicroSD */
#define MSD_SPI_CH_ID               10
#define MSD_SPI_PORT                5   /* Port F */
#define MSD_SPI_SS_PORT_ID          10
#define MSD_SPI_SS_MUX_ID           3
#define MSD_SPI_SCK_PORT_ID         11
#define MSD_SPI_SCK_MUX_ID          3
#define MSD_SPI_MOSI_PORT_ID        13
#define MSD_SPI_MOSI_MUX_ID         3
#define MSD_SPI_MISO_PORT_ID        12
#define MSD_SPI_MISO_MUX_ID         3
#define MSD_GPIO_PORT               5   /* Port F */
#define MSD_GPIO_PORT_ID            9

/* Add your configuration */
#define TIMER1_CLKSRC_USE_PCLK      0
#define DEFAULT_HSE_1MHZ_DIV        8    /* 8MHz / 8 = 1MHz */

#endif /* _STK_A34G43A_YLN_A_ */
