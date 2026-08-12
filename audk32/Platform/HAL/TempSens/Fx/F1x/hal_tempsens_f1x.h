/**
 *******************************************************************************
 * @file        hal_tempsens_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed TempSens
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TEMPSENS_F1X_H_
#define _HAL_TEMPSENS_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define TEMPSENS_CH_NUM                                     CONFIG_TEMPSENS_MAX_COUNT

#if (CONFIG_TEMPSENS_VER_EXT == 0)

#if (CONFIG_TEMPSENS_VER_MINOR == 0)
#include "hal_tempsens_f_01_00_00.h"
#elif (CONFIG_TEMPSENS_VER_MINOR == 1)
#include "hal_tempsens_f_01_00_01.h"
#else
#error "define CONFIG_TEMPSENS_VER_MINOR of F-type TEMPSENS at config_xxx.h"
#endif

#else
#error "define CONFIG_TEMPSENS_VER_EXT of F-type TEMPSENS at config_xxx.h"
#endif

static __inline TEMPSENS_Type *TEMPSENS_GetReg(P_TEMPSENS_ID_e eId)
{
    return (TEMPSENS_Type *)(TEMPSENS_REG_BASE);
}

static __inline IRQn_Type TEMPSENS_GetIRQNum(P_TEMPSENS_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(TEMPSENS_0_IRQ)
        case P_TEMPSENS_ID_0:
            eIrq = TEMPSENS_0_IRQ;
            break;
#endif
#if defined(TEMPSENS_1_IRQ)
        case P_TEMPSENS_ID_1:
            eIrq = TEMPSENS_1_IRQ;
            break;
#endif
#if defined(TEMPSENS_2_IRQ)
        case P_TEMPSENS_ID_2:
            eIrq = TEMPSENS_2_IRQ;
            break;
#endif
#if defined(TEMPSENS_3_IRQ)
        case P_TEMPSENS_ID_3:
            eIrq = TEMPSENS_3_IRQ;
            break;
#endif
#if defined(TEMPSENS_4_IRQ)
        case P_TEMPSENS_ID_4:
            eIrq = TEMPSENS_4_IRQ;
            break;
#endif
#if defined(TEMPSENS_5_IRQ)
        case P_TEMPSENS_ID_5:
            eIrq = TEMPSENS_5_IRQ;
            break;
#endif
#if defined(TEMPSENS_6_IRQ)
        case P_TEMPSENS_ID_6:
            eIrq = TEMPSENS_6_IRQ;
            break;
#endif
#if defined(TEMPSENS_7_IRQ)
        case P_TEMPSENS_ID_7:
            eIrq = TEMPSENS_7_IRQ;
            break;
#endif
#if defined(TEMPSENS_8_IRQ)
        case P_TEMPSENS_ID_8:
            eIrq = TEMPSENS_8_IRQ;
            break;
#endif
#if defined(TEMPSENS_9_IRQ)
        case P_TEMPSENS_ID_9:
            eIrq = TEMPSENS_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline HAL_ERR_e TEMPSENS_SetScuEnable(P_TEMPSENS_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    (void)eId;

    if((uint32_t)eId >= CONFIG_TEMPSENS_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_TEMPSENS_PER(ptScu, un32Enable);
    SET_SCU_TEMPSENS_PCER(ptScu, un32Enable);

    return HAL_ERR_OK;
}

static __inline HAL_ERR_e TEMPSENS_SetClk(P_TEMPSENS_ID_e eId, P_TEMPSENS_REF_CLK_e eRefClk, P_TEMPSENS_SEN_CLK_e eSenClk)
{
    return HAL_ERR_OK;
}

static __inline HAL_ERR_e TEMPSENS_SetRefCount(P_TEMPSENS_ID_e eId, P_TEMPSENS_REF_CLK_e eRefClk)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TEMPSENS_Type *ptTs;
    uint32_t un32RefCount = 0;

    if((uint32_t)eId >= CONFIG_TEMPSENS_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    un32RefCount = (SystemPeriClock / TEMPSENS_REF_CLK_DIV); 

    ptTs = TEMPSENS_GetReg(eId);
    SET_TEMPSENS_DR_PERIOD(ptTs, un32RefCount);

    return eErr;
}

#if defined(TEMPSENS_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void TEMPSENS_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, bEnable);
}
#endif

#endif /* _HAL_TEMPSENS_F1X_H_ */
