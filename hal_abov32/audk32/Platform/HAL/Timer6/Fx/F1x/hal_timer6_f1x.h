/**
 *******************************************************************************
 * @file        hal_timer6_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed Timer6
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER6_F1X_H_
#define _HAL_TIMER6_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define TIMER6_CH_NUM                                 CONFIG_TIMER6_MAX_COUNT

#if (CONFIG_TIMER6_VER_EXT == 0)

#if (CONFIG_TIMER6_VER_MINOR == 0)
#include "hal_timer6_f_01_00_00.h"
#else
#error "define CONFIG_TIMER6_VER_MINOR of F-type TIMER6 at config_xxx.h"
#endif

#else
#error "define CONFIG_TIMER6_VER_EXT of F-type TIMER6 at config_xxx.h"
#endif

static __inline HAL_ERR_e TIMER6_SetScuEnable(P_TIMER6_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= CONFIG_TIMER6_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_TIMER6_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_TIMER6_PCER(ptScu, (uint32_t)eId, un32Enable);

    return eErr;
}

static __inline uint32_t TIMER6_GetRegOffset(void)
{
    return TIMER6_REG_OFFSET_CNT;
}

static __inline TIMER6_Type *TIMER6_GetReg(uint32_t un32Id)
{
    return (TIMER6_Type *)(TIMER6_REG_BASE + (TIMER6_REG_OFFSET * un32Id));
}

static __inline IRQn_Type TIMER6_GetIRQNum(P_TIMER6_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(TIMER6_0_IRQ)
        case P_TIMER6_ID_0:
            eIrq = TIMER6_0_IRQ;
            break;
#endif
#if defined(TIMER6_1_IRQ)
        case P_TIMER6_ID_1:
            eIrq = TIMER6_1_IRQ;
            break;
#endif
#if defined(TIMER6_2_IRQ)
        case P_TIMER6_ID_2:
            eIrq = TIMER6_2_IRQ;
            break;
#endif
#if defined(TIMER6_3_IRQ)
        case P_TIMER6_ID_3:
            eIrq = TIMER6_3_IRQ;
            break;
#endif
#if defined(TIMER6_4_IRQ)
        case P_TIMER6_ID_4:
            eIrq = TIMER6_4_IRQ;
            break;
#endif
#if defined(TIMER6_5_IRQ)
        case P_TIMER6_ID_5:
            eIrq = TIMER6_5_IRQ;
            break;
#endif
#if defined(TIMER6_6_IRQ)
        case P_TIMER6_ID_6:
            eIrq = TIMER6_6_IRQ;
            break;
#endif
#if defined(TIMER6_7_IRQ)
        case P_TIMER6_ID_7:
            eIrq = TIMER6_7_IRQ;
            break;
#endif
#if defined(TIMER6_8_IRQ)
        case P_TIMER6_ID_8:
            eIrq = TIMER6_8_IRQ;
            break;
#endif
#if defined(TIMER6_9_IRQ)
        case P_TIMER6_ID_9:
            eIrq = TIMER6_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

#if defined(TIMER6_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void TIMER6_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, (uint8_t)eIrq, bEnable);
}
#endif

#endif /* _HAL_TIMER6_F1X_H_ */
