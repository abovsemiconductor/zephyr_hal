/**
 *******************************************************************************
 * @file        hal_dac_v3x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V3x typed DAC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_DAC_V3X_H_
#define _HAL_DAC_V3X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define DAC_CH_NUM                                    CONFIG_DAC_MAX_COUNT

#if (CONFIG_DAC_VER_EXT == 0)

#if (CONFIG_DAC_VER_MINOR == 0)
#include "hal_dac_v_03_00_00.h"
#elif (CONFIG_DAC_VER_MINOR == 1)
#include "hal_dac_v_03_00_01.h"
#else
#error "define CONFIG_DAC_VER_MINOR of V-type DAC at config_xxx.h"
#endif

#else
#error "define CONFIG_DAC_VER_EXT of V-type DAC at config_xxx.h"
#endif

static __inline DAC_Type *DAC_GetReg(P_DAC_ID_e eId)
{
    return (DAC_Type *)(DAC_REG_BASE + (DAC_REG_OFFSET * (uint32_t)eId));
}

static __inline IRQn_Type DAC_GetIRQNum(P_DAC_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(DAC_0_IRQ)
        case P_DAC_ID_0:
            eIrq = DAC_0_IRQ;
            break;
#endif
#if defined(DAC_1_IRQ)
        case P_DAC_ID_1:
            eIrq = DAC_1_IRQ;
            break;
#endif
#if defined(DAC_2_IRQ)
        case P_DAC_ID_2:
            eIrq = DAC_2_IRQ;
            break;
#endif
#if defined(DAC_3_IRQ)
        case P_DAC_ID_3:
            eIrq = DAC_3_IRQ;
            break;
#endif
#if defined(DAC_4_IRQ)
        case P_DAC_ID_4:
            eIrq = DAC_4_IRQ;
            break;
#endif
#if defined(DAC_5_IRQ)
        case P_DAC_ID_5:
            eIrq = DAC_5_IRQ;
            break;
#endif
#if defined(DAC_6_IRQ)
        case P_DAC_ID_6:
            eIrq = DAC_6_IRQ;
            break;
#endif
#if defined(DAC_7_IRQ)
        case P_DAC_ID_7:
            eIrq = DAC_7_IRQ;
            break;
#endif
#if defined(DAC_8_IRQ)
        case P_DAC_ID_8:
            eIrq = DAC_8_IRQ;
            break;
#endif
#if defined(DAC_9_IRQ)
        case P_DAC_ID_9:
            eIrq = DAC_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline HAL_ERR_e DAC_SetScuEnable(P_DAC_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_DAC_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_DAC_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_DAC_PCER(ptScu, (uint32_t)eId, un32Enable);

    return HAL_ERR_OK;
}

static __inline HAL_ERR_e DAC_SetOutPort(DAC_Type *ptDac, uint8_t un8OutPort)
{
    (void)ptDac;
    (void)un8OutPort;
    return HAL_ERR_OK;
}

#endif /* _HAL_DAC_V3X_H_ */
