/**
 *******************************************************************************
 * @file        hal_mpwm_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed MPWM
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_MPWM_V1X_H_
#define _HAL_MPWM_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define MPWM_CH_NUM                                 CONFIG_MPWM_MAX_COUNT

#if (CONFIG_MPWM_VER_EXT == 0)

#if (CONFIG_MPWM_VER_MINOR == 0)
#include "hal_mpwm_v_01_00_00.h"
#elif (CONFIG_MPWM_VER_MINOR == 1)
#include "hal_mpwm_v_01_00_01.h"
#elif (CONFIG_MPWM_VER_MINOR == 2)
#include "hal_mpwm_v_01_00_02.h"
#else
#error "define CONFIG_MPWM_VER_MINOR of V-type MPWM at config_xxx.h"
#endif

#else
#error "define CONFIG_MPWM_VER_EXT of V-type MPWM at config_xxx.h"
#endif

static __inline HAL_ERR_e MPWM_SetScuEnable(P_MPWM_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_MPWM_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_MPWM_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_MPWM_PCER(ptScu, (uint32_t)eId, un32Enable);

    return HAL_ERR_OK;
}

static __inline uint32_t MPWM_GetRegOffset(void)
{
    return MPWM_REG_OFFSET_CNT;
}

static __inline MPWM_Type *MPWM_GetReg(uint32_t un32Id)
{
    return (MPWM_Type *)(MPWM_REG_BASE + (MPWM_REG_OFFSET * un32Id));
}

static __inline IRQn_Type MPWM_GetIRQNum(P_MPWM_ID_e eId, P_MPWM_INTR_e eIntrId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eIntrId)
    {
#if defined(MPWM_START_PROT_IRQ)
        case P_MPWM_INTR_PROT:
            eIrq = (IRQn_Type)(MPWM_START_PROT_IRQ + ((uint32_t)eId * MPWM_IRQ_OFFSET));
            break;
#endif
#if defined(MPWM_START_OV_IRQ)
        case P_MPWM_INTR_OV:
            eIrq = (IRQn_Type)(MPWM_START_OV_IRQ + ((uint32_t)eId * MPWM_IRQ_OFFSET));
            break;
#endif

        /* Individual IP */
#if defined(MPWM_START_SIG_U_IRQ)
        case P_MPWM_INTR_SIG_U:
            eIrq = (IRQn_Type)(MPWM_START_SIG_U_IRQ + ((uint32_t)eId * MPWM_IRQ_OFFSET));
            break;
#endif
#if defined(MPWM_START_SIG_V_IRQ)
        case P_MPWM_INTR_SIG_V:
            eIrq = (IRQn_Type)(MPWM_START_SIG_V_IRQ + ((uint32_t)eId * MPWM_IRQ_OFFSET));
            break;
#endif
#if defined(MPWM_START_SIG_W_IRQ)
        case P_MPWM_INTR_SIG_W:
            eIrq = (IRQn_Type)(MPWM_START_SIG_W_IRQ + ((uint32_t)eId * MPWM_IRQ_OFFSET));
            break;
#endif

        /* Only Motor/Normal PWM */
#if defined(MPWM_START_PWM_IRQ)
        case P_MPWM_INTR_PWM:
            eIrq = (IRQn_Type)(MPWM_START_PWM_IRQ + ((uint32_t)eId * MPWM_IRQ_OFFSET));
            break;
#endif

        default:
            break;
    }

    return eIrq;
}

static __INLINE HAL_ERR_e MPWM_SetMccrClk(P_MPWM_ID_e eId, P_MPWM_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    uint8_t un8MccrSel;

    switch(eMccr)
    {
        case P_MPWM_CLK_MCCR_LSI:
            un8MccrSel = MPWM_CLK_MCCR_SRC_LSI;
            break;
        case P_MPWM_CLK_MCCR_LSE:
            un8MccrSel = MPWM_CLK_MCCR_SRC_LSE;
            break;
        case P_MPWM_CLK_MCCR_MCLK:
            un8MccrSel = MPWM_CLK_MCCR_SRC_MCLK;
            break;
        case P_MPWM_CLK_MCCR_HSI:
            un8MccrSel = MPWM_CLK_MCCR_SRC_HSI;
            break;
        case P_MPWM_CLK_MCCR_HSE:
            un8MccrSel = MPWM_CLK_MCCR_SRC_HSE;
            break;
        case P_MPWM_CLK_MCCR_PLL:
            un8MccrSel = MPWM_CLK_MCCR_SRC_PLL;
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    SET_SCU_MPWM_MCCR_SEL(ptScu, (uint8_t)eId, un8MccrSel);
    SET_SCU_MPWM_MCCR_DIV(ptScu, (uint8_t)eId, un8MccrDiv);

    return eErr;
}

#endif /* _HAL_MPWM_V1X_H_ */
