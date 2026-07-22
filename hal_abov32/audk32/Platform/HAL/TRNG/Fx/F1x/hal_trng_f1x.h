/**
 *******************************************************************************
 * @file        hal_trng_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed TTRNG
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TTRNG_F1X_H_
#define _HAL_TTRNG_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define TRNG_CH_NUM                                    CONFIG_TRNG_MAX_COUNT

#if (CONFIG_TRNG_VER_EXT == 0)

#if (CONFIG_TRNG_VER_MINOR == 0)
#include "hal_trng_f_01_00_00.h"
#else
#error "define CONFIG_TRNG_VER_MINOR of F-type TRNG at config_xxx.h"
#endif

#else
#error "define CONFIG_TRNG_VER_EXT of F-type TRNG at config_xxx.h"
#endif

static __inline TRNG_Type *TRNG_GetReg(P_TRNG_ID_e eId)
{
    return (TRNG_Type *)(TRNG_REG_BASE + (TRNG_REG_OFFSET * (uint32_t)eId));
}

static __inline IRQn_Type TRNG_GetIRQNum(P_TRNG_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(TRNG_0_IRQ)
        case P_TRNG_ID_0:
            eIrq = TRNG_0_IRQ;
            break;
#endif
#if defined(TRNG_1_IRQ)
        case P_TRNG_ID_1:
            eIrq = TRNG_1_IRQ;
            break;
#endif
#if defined(TRNG_2_IRQ)
        case P_TRNG_ID_2:
            eIrq = TRNG_2_IRQ;
            break;
#endif
#if defined(TRNG_3_IRQ)
        case P_TRNG_ID_3:
            eIrq = TRNG_3_IRQ;
            break;
#endif
#if defined(TRNG_4_IRQ)
        case P_TRNG_ID_4:
            eIrq = TRNG_4_IRQ;
            break;
#endif
#if defined(TRNG_5_IRQ)
        case P_TRNG_ID_5:
            eIrq = TRNG_5_IRQ;
            break;
#endif
#if defined(TRNG_6_IRQ)
        case P_TRNG_ID_6:
            eIrq = TRNG_6_IRQ;
            break;
#endif
#if defined(TRNG_7_IRQ)
        case P_TRNG_ID_7:
            eIrq = TRNG_7_IRQ;
            break;
#endif
#if defined(TRNG_8_IRQ)
        case P_TRNG_ID_8:
            eIrq = TRNG_8_IRQ;
            break;
#endif
#if defined(TRNG_9_IRQ)
        case P_TRNG_ID_9:
            eIrq = TRNG_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline HAL_ERR_e TRNG_SetScuEnable(P_TRNG_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_TRNG_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_TRNG_PER(ptScu, un32Enable);
    SET_SCU_TRNG_PCER(ptScu, un32Enable);

    return HAL_ERR_OK;
}

#if defined(TRNG_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void TRNG_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, bEnable);
}
#endif

#endif /* _HAL_TRNG_F1X_H_ */
