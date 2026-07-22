/**
 *******************************************************************************
 * @file        stk_a31l222_frn_a.h
 * @author      ABOV R&D Division
 * @brief       STK (Startup Kit Board on which A31L222FRN is mounted)
 *
 * Copyright 2025 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _STK_A31L222_FRN_A_H_
#define _STK_A31L222_FRN_A_H_

/* STK LED */
#define FIRST_LED_ID                4
#define LAST_LED_ID                 7
#define LED_PORT_ID                 0   /* Port A */

/* Add your configuration */
#define TIMER1_CLKSRC_USE_PCLK      0
#define DEFAULT_HSE_1MHZ_DIV        8    /* 8MHz / 8 = 1MHz */

#endif /* _STK_A31L222_FRN_A_H_ */
