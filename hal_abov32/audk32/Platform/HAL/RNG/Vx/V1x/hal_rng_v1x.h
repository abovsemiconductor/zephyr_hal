/**
 *******************************************************************************
 * @file        hal_rng_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed RNG
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_RNG_V1X_H_
#define _HAL_RNG_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define RNG_CH_NUM                                    CONFIG_RNG_MAX_COUNT

#if (CONFIG_RNG_VER_EXT == 0)

#if (CONFIG_RNG_VER_MINOR == 0)
#include "hal_rng_v_01_00_00.h"
#else
#error "define CONFIG_RNG_VER_MINOR of V-type RNG at config_xxx.h"
#endif

#else
#error "define CONFIG_RNG_VER_EXT of V-type RNG at config_xxx.h"
#endif

static __inline RNG_Type *RNG_GetReg(P_RNG_ID_e eId)
{
    return (RNG_Type *)(RNG_REG_BASE + (RNG_REG_OFFSET * (uint32_t)eId));
}

static __inline IRQn_Type RNG_GetIRQNum(P_RNG_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(RNG_0_IRQ)
        case P_RNG_ID_0:
            eIrq = RNG_0_IRQ;
            break;
#endif
#if defined(RNG_1_IRQ)
        case P_RNG_ID_1:
            eIrq = RNG_1_IRQ;
            break;
#endif
#if defined(RNG_2_IRQ)
        case P_RNG_ID_2:
            eIrq = RNG_2_IRQ;
            break;
#endif
#if defined(RNG_3_IRQ)
        case P_RNG_ID_3:
            eIrq = RNG_3_IRQ;
            break;
#endif
#if defined(RNG_4_IRQ)
        case P_RNG_ID_4:
            eIrq = RNG_4_IRQ;
            break;
#endif
#if defined(RNG_5_IRQ)
        case P_RNG_ID_5:
            eIrq = RNG_5_IRQ;
            break;
#endif
#if defined(RNG_6_IRQ)
        case P_RNG_ID_6:
            eIrq = RNG_6_IRQ;
            break;
#endif
#if defined(RNG_7_IRQ)
        case P_RNG_ID_7:
            eIrq = RNG_7_IRQ;
            break;
#endif
#if defined(RNG_8_IRQ)
        case P_RNG_ID_8:
            eIrq = RNG_8_IRQ;
            break;
#endif
#if defined(RNG_9_IRQ)
        case P_RNG_ID_9:
            eIrq = RNG_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline HAL_ERR_e RNG_SetScuEnable(P_RNG_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_RNG_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_RNG_PER(ptScu, un32Enable);
    SET_SCU_RNG_PCER(ptScu, un32Enable);

    return HAL_ERR_OK;
}

#endif /* _HAL_RNG_V1X_H_ */
