/**
 *******************************************************************************
 * @file        hal_led_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed LED
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_LED_V1X_H_
#define _HAL_LED_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define LED_CH_NUM                                    CONFIG_LED_MAX_COUNT
#define LED_ICOM_CH_NUM                               CONFIG_LED_MAX_ICOM_CH_NUM
#define LED_ISEG_CH_NUM                               CONFIG_LED_MAX_ISEG_CH_NUM

#if (CONFIG_LED_VER_EXT == 0)

#if (CONFIG_LED_VER_MINOR == 0)
#include "hal_led_v_01_00_00.h"
#elif (CONFIG_LED_VER_MINOR == 1)
#include "hal_led_v_01_00_01.h"
#else
#error "define CONFIG_LED_VER_MINOR of V-type LED at config_xxx.h"
#endif

#elif (CONFIG_LED_VER_EXT == 1)

#if (CONFIG_LED_VER_MINOR == 0)
#include "hal_led_v_01_01_00.h"
#else
#error "define CONFIG_LED_VER_MINOR of V-type LED at config_xxx.h"
#endif

#else
#error "define CONFIG_LED_VER_EXT of V-type LED at config_xxx.h"
#endif

static __inline LED_Type *LED_GetReg(P_LED_ID_e eId)
{
    return (LED_Type *)(LED_REG_BASE + (uint32_t)eId);
}

static __inline IRQn_Type LED_GetIRQNum(P_LED_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(LED_0_IRQ)
        case P_LED_ID_0:
            eIrq = LED_0_IRQ;
            break;
#endif
#if defined(LED_1_IRQ)
        case P_LED_ID_1:
            eIrq = LED_1_IRQ;
            break;
#endif
#if defined(LED_2_IRQ)
        case P_LED_ID_2:
            eIrq = LED_2_IRQ;
            break;
#endif
#if defined(LED_3_IRQ)
        case P_LED_ID_3:
            eIrq = LED_3_IRQ;
            break;
#endif
#if defined(LED_4_IRQ)
        case P_LED_ID_4:
            eIrq = LED_4_IRQ;
            break;
#endif
#if defined(LED_5_IRQ)
        case P_LED_ID_5:
            eIrq = LED_5_IRQ;
            break;
#endif
#if defined(LED_6_IRQ)
        case P_LED_ID_6:
            eIrq = LED_6_IRQ;
            break;
#endif
#if defined(LED_7_IRQ)
        case P_LED_ID_7:
            eIrq = LED_7_IRQ;
            break;
#endif
#if defined(LED_8_IRQ)
        case P_LED_ID_8:
            eIrq = LED_8_IRQ;
            break;
#endif
#if defined(LED_9_IRQ)
        case P_LED_ID_9:
            eIrq = LED_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline HAL_ERR_e LED_SetScuEnable(P_LED_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_LED_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_LED_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_LED_PCER(ptScu, (uint32_t)eId, un32Enable);

    return HAL_ERR_OK;
}

static __inline HAL_ERR_e LED_SetClk(P_LED_ID_e eId, P_LED_CLK_e eClk, P_LED_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_LED_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_LED_PPCLKSR(ptScu, eClk);

    if(eClk == P_LED_CLK_MCCR)
    {
        SET_SCU_LED_MCCR_SEL(ptScu, SCU_MCCR_MODE(eMccr));
        SET_SCU_LED_MCCR_DIV(ptScu, un8MccrDiv);
    }

    return HAL_ERR_OK;
}

#endif /* _HAL_LED_V1X_H_ */
