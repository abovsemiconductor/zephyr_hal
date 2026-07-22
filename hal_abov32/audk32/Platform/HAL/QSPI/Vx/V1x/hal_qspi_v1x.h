/**
 *******************************************************************************
 * @file        hal_qspi_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed QSPI
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_QSPI_V1X_H_
#define _HAL_QSPI_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define QSPI_CH_NUM                                    CONFIG_QSPI_MAX_COUNT

#if (CONFIG_QSPI_VER_EXT == 0)

#if (CONFIG_QSPI_VER_MINOR == 0)
#include "hal_qspi_v_01_00_00.h"
#else
#error "define CONFIG_QSPI_VER_MINOR of V-type QSPI at config_xxx.h"
#endif

#else
#error "define CONFIG_QSPI_VER_EXT of V-type QSPI at config_xxx.h"
#endif

static __inline HAL_ERR_e QSPI_SetScuEnable(P_QSPI_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId > CONFIG_QSPI_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_QSPI_PRER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_QSPI_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_QSPI_PCER(ptScu, (uint32_t)eId, un32Enable);

    return eErr;
}

static __inline QSPI_Type *QSPI_GetReg(P_QSPI_ID_e eId)
{
    return (QSPI_Type *)(QSPI_REG_BASE + (QSPI_REG_OFFSET * (uint32_t)eId));
}

static __inline uint8_t QSPI_GetDuration(QSPI_PHASE_WIDTH_e eWidth, QSPI_BUS_MODE_e eMode, QSPI_SAMPLE_RATE_e eSampleRate)
{
    uint8_t un8Cycles;

    un8Cycles = QSPI_PHASE_BITWIDTH(eWidth) / ((uint8_t)eMode * ((uint8_t)eSampleRate + 1U));

    return (un8Cycles > 0U) ? (un8Cycles - 1U) : 0U;
}

static __inline IRQn_Type QSPI_GetIRQNum(P_QSPI_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(QSPI_0_IRQ)
        case P_QSPI_ID_0:
            eIrq = QSPI_0_IRQ;
            break;
#endif
#if defined(QSPI_1_IRQ)
        case P_QSPI_ID_1:
            eIrq = QSPI_1_IRQ;
            break;
#endif
#if defined(QSPI_2_IRQ)
        case P_QSPI_ID_2:
            eIrq = QSPI_2_IRQ;
            break;
#endif
#if defined(QSPI_3_IRQ)
        case P_QSPI_ID_3:
            eIrq = QSPI_3_IRQ;
            break;
#endif
#if defined(QSPI_4_IRQ)
        case P_QSPI_ID_4:
            eIrq = QSPI_4_IRQ;
            break;
#endif
#if defined(QSPI_5_IRQ)
        case P_QSPI_ID_5:
            eIrq = QSPI_5_IRQ;
            break;
#endif
#if defined(QSPI_6_IRQ)
        case P_QSPI_ID_6:
            eIrq = QSPI_6_IRQ;
            break;
#endif
#if defined(QSPI_7_IRQ)
        case P_QSPI_ID_7:
            eIrq = QSPI_7_IRQ;
            break;
#endif
#if defined(QSPI_8_IRQ)
        case QP_SPI_ID_8:
            eIrq = QSPI_8_IRQ;
            break;
#endif
#if defined(QSPI_9_IRQ)
        case P_QSPI_ID_9:
            eIrq = QSPI_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

#endif /* _HAL_SPI_V1X_H_ */
