/**
 *******************************************************************************
 * @file        hal_pcu_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed PCU
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_PCU_V1X_H_
#define _HAL_PCU_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define PCU_PORT_GROUP_NUM                            CONFIG_PCU_MAX_COUNT

#if (CONFIG_PCU_VER_EXT == 0)

#if (CONFIG_PCU_VER_MINOR == 0)
#include "hal_pcu_v_01_00_00.h"
#elif (CONFIG_PCU_VER_MINOR == 1)
#include "hal_pcu_v_01_00_01.h"
#elif (CONFIG_PCU_VER_MINOR == 2)
#include "hal_pcu_v_01_00_02.h"
#elif (CONFIG_PCU_VER_MINOR == 3)
#include "hal_pcu_v_01_00_03.h"
#elif (CONFIG_PCU_VER_MINOR == 4)
#include "hal_pcu_v_01_00_04.h"
#else
#error "define CONFIG_PCU_VER_MINOR of V-type PCU at config_xxx.h"
#endif

#else
#error "define CONFIG_PCU_VER_EXT of V-type PCU at config_xxx.h"
#endif

static __inline PORT_Type *PCU_GetReg(uint32_t un32Id)
{
    return (PORT_Type *)(PCU_REG_BASE + (PCU_REG_OFFSET * un32Id));
}

static __inline GPIO_Type *PCU_GPIO_GetReg(uint32_t un32Id)
{
    return (GPIO_Type *)(PCU_REG_BASE + (PCU_REG_OFFSET * un32Id));
}

static __inline IRQn_Type PCU_GetIRQNum(P_PCU_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(PCU_0_IRQ)
        case P_PCU_ID_A:
            eIrq = PCU_0_IRQ;
            break;
#endif
#if defined(PCU_1_IRQ)
        case P_PCU_ID_B:
            eIrq = PCU_1_IRQ;
            break;
#endif
#if defined(PCU_2_IRQ)
        case P_PCU_ID_C:
            eIrq = PCU_2_IRQ;
            break;
#endif
#if defined(PCU_3_IRQ)
        case P_PCU_ID_D:
            eIrq = PCU_3_IRQ;
            break;
#endif
#if defined(PCU_4_IRQ)
        case P_PCU_ID_E:
            eIrq = PCU_4_IRQ;
            break;
#endif
#if defined(PCU_5_IRQ)
        case P_PCU_ID_F:
            eIrq = PCU_5_IRQ;
            break;
#endif
#if defined(PCU_6_IRQ)
        case P_PCU_ID_G:
            eIrq = PCU_6_IRQ;
            break;
#endif
#if defined(PCU_7_IRQ)
        case P_PCU_ID_H:
            eIrq = PCU_7_IRQ;
            break;
#endif
#if defined(PCU_8_IRQ)
        case P_PCU_ID_I:
            eIrq = PCU_8_IRQ;
            break;
#endif
#if defined(PCU_9_IRQ)
        case P_PCU_ID_J:
            eIrq = PCU_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline HAL_ERR_e PCU_GetValidPort(P_PCU_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    switch(eId)
    {
        case P_PCU_ID_A:
        case P_PCU_ID_B:
        case P_PCU_ID_C:
#if (CONFIG_PCU_VER_MINOR == 2)
        case P_PCU_ID_F:
#endif
             break;
#if (CONFIG_PCU_VER_MINOR != 2)
        case P_PCU_ID_D:
        case P_PCU_ID_E:
        case P_PCU_ID_F:
            break;
#endif
        default:
            eErr = HAL_ERR_PARAMETER; 
            break;
    }

    return eErr;
}

static __inline HAL_ERR_e PCU_SetDebounceClk(P_PCU_ID_e eId, P_PCU_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    switch(eId)
    {
        case P_PCU_ID_A:
        case P_PCU_ID_B:
        case P_PCU_ID_C:
#if (CONFIG_PCU_VER_MINOR == 2)
        case P_PCU_ID_F:
#endif
             SET_SCU_PCU_MCCR_SEL0(ptScu, PCU_MCCR_CLK(eMccr)); 
             SET_SCU_PCU_MCCR_DIV0(ptScu, un8MccrDiv); 
            break;
#if (CONFIG_PCU_VER_MINOR != 2)
        case P_PCU_ID_D:
        case P_PCU_ID_E:
        case P_PCU_ID_F:
             SET_SCU_PCU_MCCR_SEL1(ptScu, PCU_MCCR_CLK(eMccr)); 
             SET_SCU_PCU_MCCR_DIV1(ptScu, un8MccrDiv); 
            break;
#endif
        default:
            eErr = HAL_ERR_PARAMETER; 
            break;
    }

    return eErr;
}

static __inline HAL_ERR_e PCU_SetIntrPort(P_PCU_ID_e eId, P_PCU_PIN_ID_e ePinId, P_PCU_INTR_MODE_e eMode, 
                                          P_PCU_INTR_TRG_e eTrg, uint8_t un8IntNum)
{
    PORT_Type *ptPcu;

    ptPcu = PCU_GetReg(eId);

    SET_PCU_ACCESS_EN();

    SET_PCU_ICR_EN(ptPcu, (uint32_t)eTrg, PCU_INTR_BIT((uint32_t)ePinId));
    SET_PCU_IER_EN(ptPcu, (uint32_t)eMode, PCU_INTR_BIT((uint32_t)ePinId));

    SET_PCU_ACCESS_DIS();

    return HAL_ERR_OK;
}

static __inline HAL_ERR_e PCU_GetIntrPort(P_PCU_ID_e eId, P_PCU_PIN_ID_e ePinId, P_PCU_INTR_STATUS_e *peStatus) 
{
    PORT_Type *ptPcu;

    ptPcu = PCU_GetReg(eId);

    *peStatus = (P_PCU_INTR_STATUS_e)GET_PCU_IER_ST(ptPcu, PCU_INTR_BIT((uint32_t)ePinId));

    SET_PCU_ACCESS_EN();

    /* clear status flag */
    SET_PCU_IER_ST(ptPcu, 0x3, PCU_INTR_BIT((uint32_t)ePinId));
  
    SET_PCU_ACCESS_DIS();

    return HAL_ERR_OK;
}

#endif /* _HAL_PCU_V1X_H_ */
