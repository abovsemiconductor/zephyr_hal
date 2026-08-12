/**
 *******************************************************************************
 * @file        hal_hsicmu_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed HSICMU
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_HSICMU_V1X_H_
#define _HAL_HSICMU_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define HSICMU_CH_NUM                                    CONFIG_HSICMU_MAX_COUNT

#if (CONFIG_HSICMU_VER_EXT == 0)

#if (CONFIG_HSICMU_VER_MINOR == 0)
#include "hal_hsicmu_v_01_00_00.h"
#else
#error "define CONFIG_HSICMU_VER_MINOR of V-type HSICMU at config_xxx.h"
#endif

#else
#error "define CONFIG_HSICMU_VER_EXT of V-type HSICMU at config_xxx.h"
#endif

static __inline HSICMU_Type *HSICMU_GetReg(P_HSICMU_ID_e eId)
{
    return (HSICMU_Type *)(HSICMU_REG_BASE + (HSICMU_REG_OFFSET * (uint32_t)eId));
}

static __inline IRQn_Type HSICMU_GetIRQNum(P_HSICMU_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(HSICMU_0_IRQ)
        case P_HSICMU_ID_0:
            eIrq = HSICMU_0_IRQ;
            break;
#endif
#if defined(HSICMU_1_IRQ)
        case P_HSICMU_ID_1:
            eIrq = HSICMU_1_IRQ;
            break;
#endif
#if defined(HSICMU_2_IRQ)
        case P_HSICMU_ID_2:
            eIrq = HSICMU_2_IRQ;
            break;
#endif
#if defined(HSICMU_3_IRQ)
        case P_HSICMU_ID_3:
            eIrq = HSICMU_3_IRQ;
            break;
#endif
#if defined(HSICMU_4_IRQ)
        case P_HSICMU_ID_4:
            eIrq = HSICMU_4_IRQ;
            break;
#endif
#if defined(HSICMU_5_IRQ)
        case P_HSICMU_ID_5:
            eIrq = HSICMU_5_IRQ;
            break;
#endif
#if defined(HSICMU_6_IRQ)
        case P_HSICMU_ID_6:
            eIrq = HSICMU_6_IRQ;
            break;
#endif
#if defined(HSICMU_7_IRQ)
        case P_HSICMU_ID_7:
            eIrq = HSICMU_7_IRQ;
            break;
#endif
#if defined(HSICMU_8_IRQ)
        case P_HSICMU_ID_8:
            eIrq = HSICMU_8_IRQ;
            break;
#endif
#if defined(HSICMU_9_IRQ)
        case P_HSICMU_ID_9:
            eIrq = HSICMU_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline HAL_ERR_e HSICMU_SetScuEnable(P_HSICMU_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= HSICMU_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_HSICMU_PER(ptScu, eId, un32Enable);
    SET_SCU_HSICMU_PCER(ptScu, eId, un32Enable);

    return HAL_ERR_OK;
}

#endif /* _HAL_HSICMU_V1X_H_ */
