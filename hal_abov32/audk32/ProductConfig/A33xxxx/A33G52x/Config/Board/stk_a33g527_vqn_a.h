/**
 *******************************************************************************
 * @file        stk_a33g527_vqn_a.h
 * @author      ABOV R&D Division
 * @brief       STK (Startup Kit Board on which A33G527VQN is mounted)
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _STK_A33G527_VQN_A_H_
#define _STK_A33G527_VQN_A_H_

/* STK LED */
#define FIRST_LED_ID    0
#define LAST_LED_ID     5
#define LED_PORT_ID     3    /* Port D */

#define TIMER1N_CLKSRC_USE_PCLK     1
#define DEFAULT_HSE_1MHZ_DIV        8    /* 8MHz / 8 = 1MHz */

#endif /* _STK_A33G527_VQN_A_H_ */
