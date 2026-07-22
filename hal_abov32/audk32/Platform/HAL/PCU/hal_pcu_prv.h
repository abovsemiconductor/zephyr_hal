/**
 *******************************************************************************
 * @file        hal_pcu_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for PCU
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_PCU_PRV_H_
#define _HAL_PCU_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_PCU_ID_A,
    P_PCU_ID_B,
    P_PCU_ID_C,
    P_PCU_ID_D,
    P_PCU_ID_E,
    P_PCU_ID_F,
    P_PCU_ID_G,
    P_PCU_ID_MAX
} P_PCU_ID_e;

typedef enum
{
    P_PCU_PIN_ID_0,
    P_PCU_PIN_ID_1,
    P_PCU_PIN_ID_2,
    P_PCU_PIN_ID_3,
    P_PCU_PIN_ID_4,
    P_PCU_PIN_ID_5,
    P_PCU_PIN_ID_6,
    P_PCU_PIN_ID_7,
    P_PCU_PIN_ID_8,
    P_PCU_PIN_ID_9,
    P_PCU_PIN_ID_10,
    P_PCU_PIN_ID_11,
    P_PCU_PIN_ID_12,
    P_PCU_PIN_ID_13,
    P_PCU_PIN_ID_14,
    P_PCU_PIN_ID_15,
    P_PCU_PIN_ID_MAX
} P_PCU_PIN_ID_e;

typedef enum
{
    P_PCU_INOUT_INPUT,                /**< Input Mode */
    P_PCU_INOUT_ANG_INPUT,            /**< Input Mode with Analog Port */
    P_PCU_INOUT_OUTPUT_PUSH_PULL,     /**< Output Mode with Push-Pull */
    P_PCU_INOUT_OUTPUT_OPEN_DRAIN,    /**< Output Mode with Open-Drain */
    P_PCU_INOUT_MAX
} P_PCU_INOUT_e;

typedef enum
{
    P_PCU_PORT_LOW,
    P_PCU_PORT_HIGH,
    P_PCU_PORT_MAX
} P_PCU_PORT_e;

typedef enum
{
    P_PCU_CLK_MCCR_LSI,
    P_PCU_CLK_MCCR_LSE,
    P_PCU_CLK_MCCR_MCLK,
    P_PCU_CLK_MCCR_HSI,
    P_PCU_CLK_MCCR_HSE,
    P_PCU_CLK_MCCR_PLL,
    P_PCU_CLK_MCCR_MAX
} P_PCU_CLK_MCCR_e;

typedef enum
{
    P_PCU_INTR_STATUS_NONE,
    P_PCU_INTR_STATUS_LOW_FALL,     /**< Low Level or Falling Edge detected */
    P_PCU_INTR_STATUS_HIGH_RISE,    /**< High Level or Rising Edge detected */
    P_PCU_INTR_STATUS_BOTH,         /**< Both Level or Edge detected */
    P_PCU_INTR_STATUS_MAX
} P_PCU_INTR_STATUS_e;

typedef enum
{
    P_PCU_INTR_MODE_DISABLE,
    P_PCU_INTR_MODE_LEVEL_NONPEND,    /**< Clear Automatically Interrupt Flag */ 
    P_PCU_INTR_MODE_LEVEL_PEND,       /**< Not Clear Interrupt Flag */
    P_PCU_INTR_MODE_EDGE,             /**< Rising or Falling or Both Edge */
    P_PCU_INTR_MODE_MAX
} P_PCU_INTR_MODE_e;

typedef enum
{
    P_PCU_INTR_TRG_DISABLE,          
    P_PCU_INTR_TRG_LOW_FALLING,        /**< Low Level or Falling Edge Trigger */
    P_PCU_INTR_TRG_HIGH_RISING,        /**< High Level or Rising Edge Trigger */
    P_PCU_INTR_TRG_BOTH_LEVEL_EDGE,    /**< Both Level or Edge Trigger */
    P_PCU_INTR_TRG_MAX
} P_PCU_INTR_TRG_e;

typedef enum
{
    P_PCU_EINT_ID_0,
    P_PCU_EINT_ID_1,
    P_PCU_EINT_ID_2,
    P_PCU_EINT_ID_3,
    P_PCU_EINT_ID_4,
    P_PCU_EINT_ID_5,
    P_PCU_EINT_ID_6,
    P_PCU_EINT_ID_7,
    P_PCU_EINT_ID_8,
    P_PCU_EINT_ID_9,
    P_PCU_EINT_ID_MAX
} P_PCU_EINT_ID_e;

#define MASK_1BIT                                     0x01
#define MASK_2BITS                                    0x03
#define MASK_3BITS                                    0x07
#define MASK_4BITS                                    0x0F
#define ALT_OFFSET                                    0x08

#define SET_REG_BIT(Peri,Data,RegName,Msk,Pos)        (Peri->RegName = ((Peri->RegName & ~(Msk << Pos)) \
                                                      | (Data << Pos)))
#define GET_REG_BIT(Peri,RegName,Msk,Pos)             ((Peri->RegName & (Msk << Pos)) >> Pos)

#if (CONFIG_PCU_VER_VENDOR == 'F')

#if (CONFIG_PCU_VER_MAJOR == 1)
#include "Fx/F1x/hal_pcu_f1x.h"
#else /* CONFIG_PCU_VER_MAJOR */
#error "define CONFIG_PCU_VER_MAJOR of F-type PCU at config_xxx.h"
#endif

#elif (CONFIG_PCU_VER_VENDOR == 'V')

#if (CONFIG_PCU_VER_MAJOR == 1)
#include "Vx/V1x/hal_pcu_v1x.h"
#elif (CONFIG_PCU_VER_MAJOR == 2)
#include "Vx/V2x/hal_pcu_v2x.h"
#elif (CONFIG_PCU_VER_MAJOR == 3)
#include "Vx/V3x/hal_pcu_v3x.h"
#else /* CONFIG_PCU_VER_MAJOR */
#error "define CONFIG_PCU_VER_MAJOR of V-type PCU at config_xxx.h"
#endif

#else /* CONFIG_PCU_VER_VENDOR */
#error "define CONFIG_PCU_VER_VENDOR of PCU at config_xxx.h"
#endif

#endif /* _HAL_PCU_PRV_H_ */
