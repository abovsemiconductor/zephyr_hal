/**
 *******************************************************************************
 * @file        hal_timer3_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed timer3
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER3_F1X_H_
#define _HAL_TIMER3_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define TIMER3_CH_NUM                                 CONFIG_TIMER3_MAX_COUNT

#if (CONFIG_TIMER3_VER_EXT == 0)

#if (CONFIG_TIMER3_VER_MINOR == 0)
#include "hal_timer3_f_01_00_00.h"
#elif (CONFIG_TIMER3_VER_MINOR == 1)
#include "hal_timer3_f_01_00_01.h"
#elif (CONFIG_TIMER3_VER_MINOR == 2)
#include "hal_timer3_f_01_00_02.h"
#elif (CONFIG_TIMER3_VER_MINOR == 3)
#include "hal_timer3_f_01_00_03.h"
#else
#error "define CONFIG_TIMER3_VER_MINOR of F-type TIMER3 at config_xxx.h"
#endif

#else
#error "define CONFIG_TIMER3_VER_EXT of F-type TIMER3 at config_xxx.h"
#endif

static __inline HAL_ERR_e TIMER3_SetScuEnable(P_TIMER3_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_TIMER3_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_TIMER3_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_TIMER3_PCER(ptScu, (uint32_t)eId, un32Enable);

    return HAL_ERR_OK;
}

static __inline uint32_t TIMER3_GetRegOffset(void)
{
    return TIMER3_REG_OFFSET_CNT;
}

static __inline TIMER3_Type *TIMER3_GetReg(uint32_t un32Id)
{
    return (TIMER3_Type *)(TIMER3_REG_BASE + (TIMER3_REG_OFFSET * un32Id));
}

static __inline IRQn_Type TIMER3_GetIRQNum(P_TIMER3_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(TIMER3_0_IRQ)
        case P_TIMER3_ID_0:
            eIrq = TIMER3_0_IRQ;
            break;
#endif
#if defined(TIMER3_1_IRQ)
        case P_TIMER3_ID_1:
            eIrq = TIMER3_1_IRQ;
            break;
#endif
#if defined(TIMER3_2_IRQ)
        case P_TIMER3_ID_2:
            eIrq = TIMER3_2_IRQ;
            break;
#endif
#if defined(TIMER3_3_IRQ)
        case P_TIMER3_ID_3:
            eIrq = TIMER3_3_IRQ;
            break;
#endif
#if defined(TIMER3_4_IRQ)
        case P_TIMER3_ID_4:
            eIrq = TIMER3_4_IRQ;
            break;
#endif
#if defined(TIMER3_5_IRQ)
        case P_TIMER3_ID_5:
            eIrq = TIMER3_5_IRQ;
            break;
#endif
#if defined(TIMER3_6_IRQ)
        case P_TIMER3_ID_6:
            eIrq = TIMER3_6_IRQ;
            break;
#endif
#if defined(TIMER3_7_IRQ)
        case P_TIMER3_ID_7:
            eIrq = TIMER3_7_IRQ;
            break;
#endif
#if defined(TIMER3_8_IRQ)
        case P_TIMER3_ID_8:
            eIrq = TIMER3_8_IRQ;
            break;
#endif
#if defined(TIMER3_9_IRQ)
        case P_TIMER3_ID_9:
            eIrq = TIMER3_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __INLINE HAL_ERR_e TIMER3_SetMccrClk(P_TIMER3_ID_e eId, TIMER3_Type *ptTimer, P_TIMER3_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
#if defined(TIMER3_FEATURE_ONLY_MAIN_CLOCK)
#else
    uint8_t un8MccrSel;
#endif

    SET_SCU_TIMER3_PPCLKSR_CLK0(ptScu, false);

#if defined(TIMER3_FEATURE_ONLY_MAIN_CLOCK)
#else
    switch(eMccr)
    {
        case P_TIMER3_CLK_MCCR_LSI:
            un8MccrSel = TIMER3_CLK_MCCR_SRC_LSI;
            break;
        case P_TIMER3_CLK_MCCR_LSE:
            un8MccrSel = TIMER3_CLK_MCCR_SRC_LSE;
            break;
        case P_TIMER3_CLK_MCCR_MCLK:
            un8MccrSel = TIMER3_CLK_MCCR_SRC_MCLK;
            break;
        case P_TIMER3_CLK_MCCR_HSI:
            un8MccrSel = TIMER3_CLK_MCCR_SRC_HSI;
            break;
        case P_TIMER3_CLK_MCCR_HSE:
            un8MccrSel = TIMER3_CLK_MCCR_SRC_HSE;
            break;
        case P_TIMER3_CLK_MCCR_PLL:
            un8MccrSel = TIMER3_CLK_MCCR_SRC_PLL;
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    SET_SCU_TIMER3_MCCR_SEL0(ptScu, un8MccrSel);
    SET_SCU_TIMER3_MCCR_DIV0(ptScu, un8MccrDiv);
#endif

    return eErr;
}

static __INLINE HAL_ERR_e TIMER3_SetExtClk(P_TIMER3_ID_e eId, TIMER3_Type *ptTimer, P_TIMER3_EXTCLK_EDGE_e eExtClkEdge)
{
    (void)eId;

    /* external clock */
    SET_TIMER3_CR_CLK(ptTimer, true);

    /* external clock edge */
    if(eExtClkEdge < P_TIMER3_EXTCLK_EDGE_MAX)
    {
        SET_TIMER3_CR_EXTCLK_EDGE(ptTimer, (uint32_t)eExtClkEdge);
    }
    else
    {
        return HAL_ERR_PARAMETER;
    }

    return HAL_ERR_OK;
}

static __INLINE HAL_ERR_e TIMER3_SetPClk(P_TIMER3_ID_e eId, TIMER3_Type *ptTimer, P_TIMER3_PCLK_DIV_e ePClkDiv)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    (void)ePClkDiv;

    /* peri clock */
    SET_SCU_TIMER3_PPCLKSR_CLK0(ptScu, true);

    /* internal pre-scaler clock */
    SET_TIMER3_CR_CLK(ptTimer, false);

    return HAL_ERR_OK;
}

#if defined(TIMER3_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void TIMER3_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, (uint8_t)eIrq, bEnable);
}
#endif

#endif /* _HAL_TIMER3_F1X_H_ */
