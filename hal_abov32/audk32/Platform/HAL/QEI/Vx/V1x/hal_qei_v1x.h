/**
 *******************************************************************************
 * @file        hal_qei_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed QEI
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_QEI_V1X_H_
#define _HAL_QEI_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define QEI_CH_NUM                                 CONFIG_QEI_MAX_COUNT

#if (CONFIG_QEI_VER_EXT == 0)

#if (CONFIG_QEI_VER_MINOR == 0)
#include "hal_qei_v_01_00_00.h"
#else
#error "define CONFIG_QEI_VER_MINOR of V-type QEI at config_xxx.h"
#endif

#else
#error "define CONFIG_QEI_VER_EXT of V-type QEI at config_xxx.h"
#endif

static __inline HAL_ERR_e QEI_SetScuEnable(P_QEI_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_QEI_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_QEI_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_QEI_PCER(ptScu, (uint32_t)eId, un32Enable);

    return HAL_ERR_OK;
}

static __inline QEI_Type *QEI_GetReg(uint32_t un32Id)
{
    return (QEI_Type *)(QEI_REG_BASE + (QEI_REG_OFFSET * un32Id));
}

static __inline IRQn_Type QEI_GetIRQNum(P_QEI_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(QEI_0_IRQ)
        case P_QEI_ID_0:
            eIrq = QEI_0_IRQ;
            break;
#endif
#if defined(QEI_1_IRQ)
        case P_QEI_ID_1:
            eIrq = QEI_1_IRQ;
            break;
#endif
#if defined(QEI_2_IRQ)
        case P_QEI_ID_2:
            eIrq = QEI_2_IRQ;
            break;
#endif
#if defined(QEI_3_IRQ)
        case P_QEI_ID_3:
            eIrq = QEI_3_IRQ;
            break;
#endif
#if defined(QEI_4_IRQ)
        case P_QEI_ID_4:
            eIrq = QEI_4_IRQ;
            break;
#endif
#if defined(QEI_5_IRQ)
        case P_QEI_ID_5:
            eIrq = QEI_5_IRQ;
            break;
#endif
#if defined(QEI_6_IRQ)
        case P_QEI_ID_6:
            eIrq = QEI_6_IRQ;
            break;
#endif
#if defined(QEI_7_IRQ)
        case P_QEI_ID_7:
            eIrq = QEI_7_IRQ;
            break;
#endif
#if defined(QEI_8_IRQ)
        case P_QEI_ID_8:
            eIrq = QEI_8_IRQ;
            break;
#endif
#if defined(QEI_9_IRQ)
        case P_QEI_ID_9:
            eIrq = QEI_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

#endif /* _HAL_QEI_V1X_H_ */
