/**
 *******************************************************************************
 * @file        hal_timer4e_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed timer4e
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER4E_F1X_H_
#define _HAL_TIMER4E_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define TIMER4E_CH_NUM                                 CONFIG_TIMER4E_MAX_COUNT

#if (CONFIG_TIMER4E_VER_EXT == 0)

#if (CONFIG_TIMER4E_VER_MINOR == 0)
#include "hal_timer4e_f_01_00_00.h"
#else
#error "define CONFIG_TIMER4E_VER_MINOR of F-type TIMER4E at config_xxx.h"
#endif

#else
#error "define CONFIG_TIMER4E_VER_EXT of F-type TIMER4E at config_xxx.h"
#endif

static __inline HAL_ERR_e TIMER4E_SetScuEnable(P_TIMER4E_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_TIMER4E_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_TIMER4E_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_TIMER4E_PCER(ptScu, (uint32_t)eId, un32Enable);

    return HAL_ERR_OK;
}

static __inline uint32_t TIMER4E_GetRegOffset(void)
{
    return TIMER4E_REG_OFFSET_CNT;
}

static __inline TIMER4E_Type *TIMER4E_GetReg(uint32_t un32Id)
{
    return (TIMER4E_Type *)(TIMER4E_REG_BASE + (TIMER4E_REG_OFFSET * un32Id));
}

static __inline IRQn_Type TIMER4E_GetIRQNum(P_TIMER4E_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(TIMER4E_0_IRQ)
        case P_TIMER4E_ID_0:
            eIrq = TIMER4E_0_IRQ;
            break;
#endif
#if defined(TIMER4E_1_IRQ)
        case P_TIMER4E_ID_1:
            eIrq = TIMER4E_1_IRQ;
            break;
#endif
#if defined(TIMER4E_2_IRQ)
        case P_TIMER4E_ID_2:
            eIrq = TIMER4E_2_IRQ;
            break;
#endif
#if defined(TIMER4E_3_IRQ)
        case P_TIMER4E_ID_3:
            eIrq = TIMER4E_3_IRQ;
            break;
#endif
#if defined(TIMER4E_4_IRQ)
        case P_TIMER4E_ID_4:
            eIrq = TIMER4E_4_IRQ;
            break;
#endif
#if defined(TIMER4E_5_IRQ)
        case P_TIMER4E_ID_5:
            eIrq = TIMER4E_5_IRQ;
            break;
#endif
#if defined(TIMER4E_6_IRQ)
        case P_TIMER4E_ID_6:
            eIrq = TIMER4E_6_IRQ;
            break;
#endif
#if defined(TIMER4E_7_IRQ)
        case P_TIMER4E_ID_7:
            eIrq = TIMER4E_7_IRQ;
            break;
#endif
#if defined(TIMER4E_8_IRQ)
        case P_TIMER4E_ID_8:
            eIrq = TIMER4E_8_IRQ;
            break;
#endif
#if defined(TIMER4E_9_IRQ)
        case P_TIMER4E_ID_9:
            eIrq = TIMER4E_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __INLINE HAL_ERR_e TIMER4E_SetExtClk(P_TIMER4E_ID_e eId, TIMER4E_Type *ptTimer, P_TIMER4E_EXTCLK_EDGE_e eExtClkEdge)
{
    (void)eId;

    /* external clock */
    SET_TIMER4E_CR_CLK(ptTimer, true);

    /* external clock edge */
    if(eExtClkEdge < P_TIMER4E_EXTCLK_EDGE_MAX)
    {
        SET_TIMER4E_CR_EXTCLK_EDGE(ptTimer, (uint32_t)eExtClkEdge);
    }
    else
    {
        return HAL_ERR_PARAMETER;
    }

    return HAL_ERR_OK;
}

static __INLINE HAL_ERR_e TIMER4E_SetPClk(P_TIMER4E_ID_e eId, TIMER4E_Type *ptTimer, P_TIMER4E_PCLK_DIV_e ePClkDiv)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    (void)ePClkDiv;

    /* peri clock */
    SET_SCU_TIMER4E_PPCLKSR_CLK0(ptScu, true);

    /* internal pre-scaler clock */
    SET_TIMER4E_CR_CLK(ptTimer, false);

    return HAL_ERR_OK;
}

#if defined(TIMER4E_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void TIMER4E_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, (uint8_t)eIrq, bEnable);
}
#endif

#endif /* _HAL_TIMER4E_F1X_H_ */
