/**
 *******************************************************************************
 * @file        hal_frt_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed FRT
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_FRT_V1X_H_
#define _HAL_FRT_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define FRT_CH_NUM                                    CONFIG_FRT_MAX_COUNT

#if (CONFIG_FRT_VER_EXT == 0)

#if (CONFIG_FRT_VER_MINOR == 0)
#include "hal_frt_v_01_00_00.h"
#elif (CONFIG_FRT_VER_MINOR == 1)
#include "hal_frt_v_01_00_01.h"
#else
#error "define CONFIG_FRT_VER_MINOR of V-type FRT at config_xxx.h"
#endif

#else
#error "define CONFIG_FRT_VER_EXT of V-type FRT at config_xxx.h"
#endif

static __inline HAL_ERR_e FRT_SetScuEnable(P_FRT_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    HAL_ERR_e eErr = HAL_ERR_OK;

    switch(eId)
    {
#if (CONFIG_FRT_MAX_COUNT > 0)
        case P_FRT_ID_0:
            SET_SCU_FRT_PER0(ptScu, un32Enable);
            SET_SCU_FRT_PCER0(ptScu, un32Enable);
            break;
#endif
#if (CONFIG_FRT_MAX_COUNT > 1)
        case P_FRT_ID_1:
            SET_SCU_FRT_PER1(ptScu, un32Enable);
            SET_SCU_FRT_PCER1(ptScu, un32Enable);
            break;
#endif
        default:
            eErr = HAL_ERR_INVALID_ID;
            break;
    }

    return eErr;
}

static __inline FRT_Type *FRT_GetReg(P_FRT_ID_e eId)
{
    return (FRT_Type *)(FRT_REG_BASE + (FRT_REG_OFFSET * (uint32_t)eId));
}

static __inline HAL_ERR_e FRT_SetMccrClk(P_FRT_ID_e eId, P_FRT_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    switch(eId)
    {
#if (CONFIG_FRT_MAX_COUNT > 0)
        case P_FRT_ID_0:
            SET_SCU_FRT_MCCR_SEL0(ptScu, SCU_MCCR_MODE(eMccr));
            SET_SCU_FRT_MCCR_DIV0(ptScu, un8MccrDiv);
            break;
#endif
#if (CONFIG_FRT_MAX_COUNT > 1)
        case P_FRT_ID_1:
            SET_SCU_FRT_MCCR_SEL1(ptScu, SCU_MCCR_MODE(eMccr));
            SET_SCU_FRT_MCCR_DIV1(ptScu, un8MccrDiv);
            break;
#endif
        case P_FRT_ID_2:
        case P_FRT_ID_3:
        case P_FRT_ID_4:
        case P_FRT_ID_5:
        case P_FRT_ID_6:
        case P_FRT_ID_7:
        case P_FRT_ID_8:
        case P_FRT_ID_9:
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    return eErr;
}

static __inline IRQn_Type FRT_GetIRQNum(P_FRT_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(FRT_0_IRQ)
        case P_FRT_ID_0:
            eIrq = FRT_0_IRQ;
            break;
#endif
#if defined(FRT_1_IRQ)
        case P_FRT_ID_1:
            eIrq = FRT_1_IRQ;
            break;
#endif
#if defined(FRT_2_IRQ)
        case P_FRT_ID_2:
            eIrq = FRT_2_IRQ;
            break;
#endif
#if defined(FRT_3_IRQ)
        case P_FRT_ID_3:
            eIrq = FRT_3_IRQ;
            break;
#endif
#if defined(FRT_4_IRQ)
        case P_FRT_ID_4:
            eIrq = FRT_4_IRQ;
            break;
#endif
#if defined(FRT_5_IRQ)
        case P_FRT_ID_5:
            eIrq = FRT_5_IRQ;
            break;
#endif
#if defined(FRT_6_IRQ)
        case P_FRT_ID_6:
            eIrq = FRT_6_IRQ;
            break;
#endif
#if defined(FRT_7_IRQ)
        case P_FRT_ID_7:
            eIrq = FRT_7_IRQ;
            break;
#endif
#if defined(FRT_8_IRQ)
        case P_FRT_ID_8:
            eIrq = FRT_8_IRQ;
            break;
#endif
#if defined(FRT_9_IRQ)
        case P_FRT_ID_9:
            eIrq = FRT_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

#endif /* _HAL_FRT_V1X_H_ */
