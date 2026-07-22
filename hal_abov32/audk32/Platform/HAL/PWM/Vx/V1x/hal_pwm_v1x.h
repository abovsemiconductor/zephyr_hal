/**
 *******************************************************************************
 * @file        hal_pwm_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed PWM 
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_PWM_V1X_H_
#define _HAL_PWM_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define PWM_CH_NUM                                 CONFIG_PWM_MAX_COUNT

#if (CONFIG_PWM_VER_EXT == 0)

#if (CONFIG_PWM_VER_MINOR == 0)
#include "hal_pwm_v_01_00_00.h"
#elif (CONFIG_PWM_VER_MINOR == 1)
#include "hal_pwm_v_01_00_01.h"
#else
#error "define CONFIG_PWM_VER_MINOR of V-type PWM at config_xxx.h"
#endif

#else
#error "define CONFIG_PWM_VER_EXT of V-type PWM at config_xxx.h"
#endif

static __inline HAL_ERR_e PWM_SetScuEnable(P_PWM_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= CONFIG_PWM_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_PWM_PER(ptScu, SCU_ENABLE((uint32_t)eId), un32Enable);
    SET_SCU_PWM_PCER(ptScu, SCU_ENABLE((uint32_t)eId), un32Enable);

    return eErr;
}

static __INLINE PWM_Type *PWM_GetReg(uint32_t un32Id)
{
#if defined(PWM_REG_PWM_OFFSET)
    return (PWM_Type *)(PWM_REG_BASE + ((PWM_REG_PWM_OFFSET * PWM_ID_DIV(un32Id)) + (PWM_REG_OFFSET * PWM_ID_MOD(un32Id))));
#else
    return (PWM_Type *)(PWM_REG_BASE + (PWM_REG_OFFSET * un32Id));
#endif
}

static __INLINE PWMPRS_Type *PWM_GetPrsReg(uint32_t un32Id)
{
    return (PWMPRS_Type *)(PWM_PRS_REG_BASE + (PWM_PRS_REG_OFFSET * PWM_PRS_ID(un32Id)));
}

static __inline IRQn_Type PWM_GetIRQNum(P_PWM_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(PWM_0_IRQ)
        case P_PWM_ID_0:
            eIrq = PWM_0_IRQ;
            break;
#endif
#if defined(PWM_1_IRQ)
        case P_PWM_ID_1:
            eIrq = PWM_1_IRQ;
            break;
#endif
#if defined(PWM_2_IRQ)
        case P_PWM_ID_2:
            eIrq = PWM_2_IRQ;
            break;
#endif
#if defined(PWM_3_IRQ)
        case P_PWM_ID_3:
            eIrq = PWM_3_IRQ;
            break;
#endif
#if defined(PWM_4_IRQ)
        case P_PWM_ID_4:
            eIrq = PWM_4_IRQ;
            break;
#endif
#if defined(PWM_5_IRQ)
        case P_PWM_ID_5:
            eIrq = PWM_5_IRQ;
            break;
#endif
#if defined(PWM_6_IRQ)
        case P_PWM_ID_6:
            eIrq = PWM_6_IRQ;
            break;
#endif
#if defined(PWM_7_IRQ)
        case P_PWM_ID_7:
            eIrq = PWM_7_IRQ;
            break;
#endif
#if defined(PWM_8_IRQ)
        case P_PWM_ID_8:
            eIrq = PWM_8_IRQ;
            break;
#endif
#if defined(PWM_9_IRQ)
        case P_PWM_ID_9:
            eIrq = PWM_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

#endif /* _HAL_PWM_V1X_H_ */
