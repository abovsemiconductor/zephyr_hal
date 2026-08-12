/**
 *******************************************************************************
 * @file        hal_vrefbuf_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed VREFBUF
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_VREFBUF_V1X_H_
#define _HAL_VREFBUF_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define VREFBUF_CH_NUM                                    CONFIG_VREFBUF_MAX_COUNT

#if (CONFIG_VREFBUF_VER_EXT == 0)

#if (CONFIG_VREFBUF_VER_MINOR == 0)
#include "hal_vrefbuf_v_01_00_00.h"
#else
#error "define CONFIG_VREFBUF_VER_MINOR of V-type VREFBUF at config_xxx.h"
#endif

#else
#error "define CONFIG_VREFBUF_VER_EXT of V-type VREFBUF at config_xxx.h"
#endif

static __inline VREFBUF_Type *VREFBUF_GetReg(P_VREFBUF_ID_e eId)
{
    return (VREFBUF_Type *)(VREFBUF_REG_BASE + (VREFBUF_REG_OFFSET * (uint32_t)eId));
}

static __inline IRQn_Type VREFBUF_GetIRQNum(P_VREFBUF_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(VREFBUF_0_IRQ)
        case P_VREFBUF_ID_0:
            eIrq = VREFBUF_0_IRQ;
            break;
#endif
#if defined(VREFBUF_1_IRQ)
        case P_VREFBUF_ID_1:
            eIrq = VREFBUF_1_IRQ;
            break;
#endif
#if defined(VREFBUF_2_IRQ)
        case P_VREFBUF_ID_2:
            eIrq = VREFBUF_2_IRQ;
            break;
#endif
#if defined(VREFBUF_3_IRQ)
        case P_VREFBUF_ID_3:
            eIrq = VREFBUF_3_IRQ;
            break;
#endif
#if defined(VREFBUF_4_IRQ)
        case P_VREFBUF_ID_4:
            eIrq = VREFBUF_4_IRQ;
            break;
#endif
#if defined(VREFBUF_5_IRQ)
        case P_VREFBUF_ID_5:
            eIrq = VREFBUF_5_IRQ;
            break;
#endif
#if defined(VREFBUF_6_IRQ)
        case P_VREFBUF_ID_6:
            eIrq = VREFBUF_6_IRQ;
            break;
#endif
#if defined(VREFBUF_7_IRQ)
        case P_VREFBUF_ID_7:
            eIrq = VREFBUF_7_IRQ;
            break;
#endif
#if defined(VREFBUF_8_IRQ)
        case P_VREFBUF_ID_8:
            eIrq = VREFBUF_8_IRQ;
            break;
#endif
#if defined(VREFBUF_9_IRQ)
        case P_VREFBUF_ID_9:
            eIrq = VREFBUF_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline HAL_ERR_e VREFBUF_SetScuEnable(P_VREFBUF_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= VREFBUF_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_VREFBUF_PER(ptScu, un32Enable);
    SET_SCU_VREFBUF_PCER(ptScu, un32Enable);

    return HAL_ERR_OK;
}

#endif /* _HAL_VREFBUF_V1X_H_ */
