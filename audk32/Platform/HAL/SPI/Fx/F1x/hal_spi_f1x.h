/**
 *******************************************************************************
 * @file        hal_spi_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed SPI
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_SPI_F1X_H_
#define _HAL_SPI_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define SPI_CH_NUM                                    CONFIG_SPI_MAX_COUNT

#if (CONFIG_SPI_VER_EXT == 0)

#if (CONFIG_SPI_VER_MINOR == 0)
#include "hal_spi_f_01_00_00.h"
#elif (CONFIG_SPI_VER_MINOR == 1)
#include "hal_spi_f_01_00_01.h"
#elif (CONFIG_SPI_VER_MINOR == 2)
#include "hal_spi_f_01_00_02.h"
#else
#error "define CONFIG_SPI_VER_MINOR of F-type SPI at config_xxx.h"
#endif

#else
#error "define CONFIG_SPI_VER_EXT of F-type SPI at config_xxx.h"
#endif

static __inline HAL_ERR_e SPI_SetScuEnable(P_SPI_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId > CONFIG_SPI_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_SPI_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_SPI_PCER(ptScu, (uint32_t)eId, un32Enable);

    return eErr;
}

static __inline SPI_Type *SPI_GetReg(P_SPI_ID_e eId)
{
    return (SPI_Type *)(SPI_REG_BASE + (SPI_REG_OFFSET * (uint32_t)eId));
}

static __inline IRQn_Type SPI_GetIRQNum(P_SPI_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(SPI_0_IRQ)
        case P_SPI_ID_0:
            eIrq = SPI_0_IRQ;
            break;
#endif
#if defined(SPI_1_IRQ)
        case P_SPI_ID_1:
            eIrq = SPI_1_IRQ;
            break;
#endif
#if defined(SPI_2_IRQ)
        case P_SPI_ID_2:
            eIrq = SPI_2_IRQ;
            break;
#endif
#if defined(SPI_3_IRQ)
        case P_SPI_ID_3:
            eIrq = SPI_3_IRQ;
            break;
#endif
#if defined(SPI_4_IRQ)
        case P_SPI_ID_4:
            eIrq = SPI_4_IRQ;
            break;
#endif
#if defined(SPI_5_IRQ)
        case P_SPI_ID_5:
            eIrq = SPI_5_IRQ;
            break;
#endif
#if defined(SPI_6_IRQ)
        case P_SPI_ID_6:
            eIrq = SPI_6_IRQ;
            break;
#endif
#if defined(SPI_7_IRQ)
        case P_SPI_ID_7:
            eIrq = SPI_7_IRQ;
            break;
#endif
#if defined(SPI_8_IRQ)
        case P_SPI_ID_8:
            eIrq = SPI_8_IRQ;
            break;
#endif
#if defined(SPI_9_IRQ)
        case P_SPI_ID_9:
            eIrq = SPI_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

#if defined(SPI_FEATURE_MASTER_SS_PIN_BY_GPIO)
static __inline void SPI_SetSSPort(P_SPI_ID_e eId, bool bLevel)
{
    PORT_Type *ptPcu;
    uint8_t un8PortNum = 0;

    switch(eId)
    {
#if (CONFIG_SPI_MAX_COUNT > 0)
        case P_SPI_ID_0:
            ptPcu = (PORT_Type *)SPI_0_SS_PORT;
            un8PortNum = SPI_0_SS_PIN;
            break; 
#endif
#if (CONFIG_SPI_MAX_COUNT > 1)
        case P_SPI_ID_1:
            ptPcu = (PORT_Type *)SPI_1_SS_PORT;
            un8PortNum = SPI_1_SS_PIN;
            break; 
#endif
#if (CONFIG_SPI_MAX_COUNT > 2)
        case P_SPI_ID_2:
            ptPcu = (PORT_Type *)SPI_2_SS_PORT;
            un8PortNum = SPI_2_SS_PIN;
            break; 
#endif
#if (CONFIG_SPI_MAX_COUNT > 3)
        case P_SPI_ID_3:
            ptPcu = (PORT_Type *)SPI_3_SS_PORT;
            un8PortNum = SPI_3_SS_PIN;
            break; 
#endif
        default:
            return;
    }

    SET_PCU_SPI_SS_PIN(ptPcu, un8PortNum, bLevel);
}
#endif

#if defined(SPI_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void SPI_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, (uint8_t)eIrq, bEnable);
}
#endif

#endif /* _HAL_SPI_F1X_H_ */
