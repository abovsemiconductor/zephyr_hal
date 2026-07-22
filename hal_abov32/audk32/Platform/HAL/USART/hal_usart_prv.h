/**
 *******************************************************************************
 * @file        hal_usart_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for USART
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_USART_PRV_H_
#define _HAL_USART_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_USART_ID_0   = 0,                        /**< USART 0 */
    P_USART_ID_1   = 1,                        /**< USART 1 */
    P_USART_ID_2   = 2,                        /**< USART 2 */
    P_USART_ID_3   = 3,                        /**< USART 3 */
    P_USART_ID_4   = 4,                        /**< USART 4 */
    P_USART_ID_5   = 5,                        /**< USART 5 */
    P_USART_ID_MAX,                            /**< USART max */
} P_USART_ID_e;

#if (CONFIG_USART_VER_VENDOR == 'F')

#if (CONFIG_USART_VER_MAJOR == 1)
#include "Fx/F1x/hal_usart_f1x.h"
#else
#error "define CONFIG_USART_VER_MAJOR of F-type USART at config_xxx.h"
#endif

#else
#error "define CONFIG_USART_VER_VENDOR of USART at config_xxx.h"
#endif

#endif /* _HAL_USART_PRV_H_ */
