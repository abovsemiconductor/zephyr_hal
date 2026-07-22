/**
 *******************************************************************************
 * @file        hal_aes_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed AES
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_AES_V1X_H_
#define _HAL_AES_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define AES_CH_NUM                                    CONFIG_AES_MAX_COUNT

#if (CONFIG_AES_VER_EXT == 0)

#if (CONFIG_AES_VER_MINOR == 0)
#include "hal_aes_v_01_00_00.h"
#else
#error "define CONFIG_AES_VER_MINOR of V-type AES at config_xxx.h"
#endif

#else
#error "define CONFIG_AES_VER_EXT of V-type AES at config_xxx.h"
#endif

static __inline AES_Type *AES_GetReg(P_AES_ID_e eId)
{
    return (AES_Type *)(AES_REG_BASE + (AES_REG_OFFSET * (uint32_t)eId));
}

static __inline IRQn_Type AES_GetIRQNum(P_AES_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(AES_0_IRQ)
        case P_AES_ID_0:
            eIrq = AES_0_IRQ;
            break;
#endif
#if defined(AES_1_IRQ)
        case P_AES_ID_1:
            eIrq = AES_1_IRQ;
            break;
#endif
#if defined(AES_2_IRQ)
        case P_AES_ID_2:
            eIrq = AES_2_IRQ;
            break;
#endif
#if defined(AES_3_IRQ)
        case P_AES_ID_3:
            eIrq = AES_3_IRQ;
            break;
#endif
#if defined(AES_4_IRQ)
        case P_AES_ID_4:
            eIrq = AES_4_IRQ;
            break;
#endif
#if defined(AES_5_IRQ)
        case P_AES_ID_5:
            eIrq = AES_5_IRQ;
            break;
#endif
#if defined(AES_6_IRQ)
        case P_AES_ID_6:
            eIrq = AES_6_IRQ;
            break;
#endif
#if defined(AES_7_IRQ)
        case P_AES_ID_7:
            eIrq = AES_7_IRQ;
            break;
#endif
#if defined(AES_8_IRQ)
        case P_AES_ID_8:
            eIrq = AES_8_IRQ;
            break;
#endif
#if defined(AES_9_IRQ)
        case P_AES_ID_9:
            eIrq = AES_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline HAL_ERR_e AES_SetScuEnable(P_AES_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_AES_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_AES_PER(ptScu, un32Enable);
    SET_SCU_AES_PCER(ptScu, un32Enable);

    return HAL_ERR_OK;
}

#endif /* _HAL_AES_V1X_H_ */
