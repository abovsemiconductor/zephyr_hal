/**
 *******************************************************************************
 * @file        hal_pcu_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed PCU
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_PCU_F1X_H_
#define _HAL_PCU_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define PCU_PORT_GROUP_NUM                            CONFIG_PCU_MAX_COUNT

#if (CONFIG_PCU_VER_EXT == 0)

#if (CONFIG_PCU_VER_MINOR == 0)
#include "hal_pcu_f_01_00_00.h"
#elif (CONFIG_PCU_VER_MINOR == 1)
#include "hal_pcu_f_01_00_01.h"
#elif (CONFIG_PCU_VER_MINOR == 2)
#include "hal_pcu_f_01_00_02.h"
#else
#error "define CONFIG_PCU_VER_MINOR of F-type PCU at config_xxx.h"
#endif

#else
#error "define CONFIG_PCU_VER_EXT of F-type PCU at config_xxx.h"
#endif

#define PCU_DEBOUNCE_DIV_MAX                          6

static __inline PORT_Type *PCU_GetReg(uint32_t un32Id)
{
    return (PORT_Type *)(PCU_REG_BASE + (PCU_REG_OFFSET * un32Id));
}

static __inline GPIO_Type *PCU_GPIO_GetReg(uint32_t un32Id)
{
    return (GPIO_Type *)(PCU_REG_BASE + (PCU_REG_OFFSET * un32Id));
}

static __inline IRQn_Type PCU_GetIRQNum(P_PCU_EINT_ID_e eEIntId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eEIntId)
    {
#if defined(PCU_0_IRQ)
        case P_PCU_EINT_ID_0:
            eIrq = PCU_0_IRQ;
            break;
#endif
#if defined(PCU_1_IRQ)
        case P_PCU_EINT_ID_1:
            eIrq = PCU_1_IRQ;
            break;
#endif
#if defined(PCU_2_IRQ)
        case P_PCU_EINT_ID_2:
            eIrq = PCU_2_IRQ;
            break;
#endif
#if defined(PCU_3_IRQ)
        case P_PCU_EINT_ID_3:
            eIrq = PCU_3_IRQ;
            break;
#endif
#if defined(PCU_4_IRQ)
        case P_PCU_EINT_ID_4:
            eIrq = PCU_4_IRQ;
            break;
#endif
#if defined(PCU_5_IRQ)
        case P_PCU_EINT_ID_5:
            eIrq = PCU_5_IRQ;
            break;
#endif
#if defined(PCU_6_IRQ)
        case P_PCU_EINT_ID_6:
            eIrq = PCU_6_IRQ;
            break;
#endif
#if defined(PCU_7_IRQ)
        case P_PCU_EINT_ID_7:
            eIrq = PCU_7_IRQ;
            break;
#endif
#if defined(PCU_8_IRQ)
        case P_PCU_EINT_ID_8:
            eIrq = PCU_8_IRQ;
            break;
#endif
#if defined(PCU_9_IRQ)
        case P_PCU_EINT_ID_9:
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
        case P_PCU_ID_D:
#if (CONFIG_PCU_VER_MINOR == 2)
#else
        case P_PCU_ID_E:
#endif
        case P_PCU_ID_F:
            break;
        default:
            eErr = HAL_ERR_PARAMETER; 
            break;
    }

    return eErr;
}

static __inline HAL_ERR_e PCU_SetDebounceClk(P_PCU_ID_e eId, P_PCU_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    PORT_Type *ptPort;

    if(un8MccrDiv >= PCU_DEBOUNCE_DIV_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    ptPort = PCU_GetReg((uint32_t)eId);

    switch(eId)
    {
        case P_PCU_ID_A:
        case P_PCU_ID_B:
        case P_PCU_ID_C:
        case P_PCU_ID_D:
        case P_PCU_ID_E:
        case P_PCU_ID_F:
            SET_PCU_DEBOUNCE_CLK(ptPort, un8MccrDiv); 
            break;
        default:
            eErr = HAL_ERR_PARAMETER; 
            break;
    }

    return eErr;
}

static __inline HAL_ERR_e PCU_SetIntrPort(P_PCU_ID_e eId, P_PCU_PIN_ID_e ePinId, P_PCU_INTR_MODE_e eMode, 
                                          P_PCU_INTR_TRG_e eTrg, uint8_t un8IntNum)
{
    INTC_Type *ptIntc = (INTC_Type *)PCU_INTC_REG_BASE;
    uint32_t un32AddrReg, un32TrgAddrReg, un32ModeAddrReg;
    uint8_t un8RegOffset, un8DataOffset;

    un32AddrReg = (uint32_t)GET_PCU_IER_CFG_BASE_ADDR(ptIntc);
    un32ModeAddrReg = (uint32_t)PCU_INTC_MODE_REG_BASE;
    un32TrgAddrReg = (uint32_t)PCU_INTC_TRG_REG_BASE;

    if((uint8_t)ePinId < 8)
    {
        un8RegOffset = un8IntNum*PCU_INTC_CFG_REG_OFFSET;
    }
    else
    {
        un8RegOffset = (un8IntNum*PCU_INTC_CFG_REG_OFFSET) + PCU_INTC_CFG_REG_OFFSET2;
    }

    un8DataOffset = (((uint8_t)ePinId % 8) * PCU_INTC_CFG_BIT_OFFSET);
    SET_PCU_IER_CFG_PORT_SEL(un32AddrReg, un8RegOffset, un8DataOffset, (uint8_t)eId);

    SET_PCU_IER_CFG_PORT_MODE(un32ModeAddrReg, ((uint32_t)eId * PCU_INTC_CFG_REG_OFFSET), ((uint32_t)ePinId * PCU_INTC_MODE_BIT_OFFSET), (uint8_t)eMode);

    SET_PCU_IER_CFG_PORT_TRG(un32TrgAddrReg, ((uint32_t)eId * PCU_INTC_CFG_REG_OFFSET), ((uint32_t)ePinId), PCU_INTC_TRG((uint8_t)eMode));

    return HAL_ERR_OK;
}

static __inline HAL_ERR_e PCU_GetIntrPort(P_PCU_ID_e eId, P_PCU_PIN_ID_e ePinId, P_PCU_INTR_STATUS_e *peStatus) 
{
    (void)eId;
    (void)ePinId;
    (void)peStatus;
    return HAL_ERR_NOT_SUPPORTED;
}

#if defined(PCU_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void PCU_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, (uint8_t)eIrq, bEnable);
}
#endif

#endif /* _HAL_PCU_F1X_H_ */
