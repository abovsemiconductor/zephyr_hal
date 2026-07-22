/**
 *******************************************************************************
 * @file        hal_timer5_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed Timer5
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER5_F1X_H_
#define _HAL_TIMER5_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define TIMER5_CH_NUM                                 CONFIG_TIMER5_MAX_COUNT

#if (CONFIG_TIMER5_VER_EXT == 0)

#if (CONFIG_TIMER5_VER_MINOR == 0)
#include "hal_timer5_f_01_00_00.h"
#else
#error "define CONFIG_TIMER5_VER_MINOR of F-type TIMER5 at config_xxx.h"
#endif

#else
#error "define CONFIG_TIMER5_VER_EXT of F-type TIMER5 at config_xxx.h"
#endif

static __inline HAL_ERR_e TIMER5_SetScuEnable(P_TIMER5_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_TIMER5_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_TIMER5_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_TIMER5_PCER(ptScu, (uint32_t)eId, un32Enable);

    return HAL_ERR_OK;
}

static __inline uint32_t TIMER5_GetRegOffset(void)
{
    return TIMER5_REG_OFFSET_CNT;
}

static __inline TIMER5_Type *TIMER5_GetReg(uint32_t un32Id)
{
    return (TIMER5_Type *)(TIMER5_REG_BASE + (TIMER5_REG_OFFSET * un32Id));
}

static __inline IRQn_Type TIMER5_GetIRQNum(P_TIMER5_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(TIMER5_0_IRQ)
        case P_TIMER5_ID_0:
            eIrq = TIMER5_0_IRQ;
            break;
#endif
#if defined(TIMER5_1_IRQ)
        case P_TIMER5_ID_1:
            eIrq = TIMER5_1_IRQ;
            break;
#endif
#if defined(TIMER5_2_IRQ)
        case P_TIMER5_ID_2:
            eIrq = TIMER5_2_IRQ;
            break;
#endif
#if defined(TIMER5_3_IRQ)
        case P_TIMER5_ID_3:
            eIrq = TIMER5_3_IRQ;
            break;
#endif
#if defined(TIMER5_4_IRQ)
        case P_TIMER5_ID_4:
            eIrq = TIMER5_4_IRQ;
            break;
#endif
#if defined(TIMER5_5_IRQ)
        case P_TIMER5_ID_5:
            eIrq = TIMER5_5_IRQ;
            break;
#endif
#if defined(TIMER5_6_IRQ)
        case P_TIMER5_ID_6:
            eIrq = TIMER5_6_IRQ;
            break;
#endif
#if defined(TIMER5_7_IRQ)
        case P_TIMER5_ID_7:
            eIrq = TIMER5_7_IRQ;
            break;
#endif
#if defined(TIMER5_8_IRQ)
        case P_TIMER5_ID_8:
            eIrq = TIMER5_8_IRQ;
            break;
#endif
#if defined(TIMER5_9_IRQ)
        case P_TIMER5_ID_9:
            eIrq = TIMER5_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline P_TIMER5_MODE_e TIMER5_ConvMode(P_TIMER5_MODE_e eMode)
{
    return eMode;
}

static __inline uint32_t TIMER5_ConvPol(P_TIMER5_POL_e ePol)
{
    switch(ePol)
    {
        case P_TIMER5_POL_HIGH:
             return TIMER5_POLARITY_HIGH;
        case P_TIMER5_POL_LOW:
             return TIMER5_POLARITY_LOW;
        default:
             return P_TIMER5_POL_MAX;
    }
}

static __inline uint32_t TIMER5_GetIntFlag(TIMER5_Type *ptPeri)
{
    uint32_t uiFlg=0;
    uint32_t uiIntFlg=0;

    uiFlg=GET_TIMER5_IER_MATCH_FLAG(ptPeri);
    if(uiFlg)
    {
        uiIntFlg |= P_TIMER5_INTR_FLAG_MATCH;
    }
    uiFlg=GET_TIMER5_IER_CAP_FLAG(ptPeri);
    if(uiFlg)
    {
        uiIntFlg |= P_TIMER5_INTR_FLAG_CAP;
    }
    return uiIntFlg;
}

static __INLINE HAL_ERR_e TIMER5_SetMccrClk(P_TIMER5_ID_e eId, TIMER5_Type *ptTimer, P_TIMER5_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    uint8_t un8MccrSel;

    (void)un8MccrDiv;

    /* internal pre-scaler clock */
    SET_TIMER5_CR_CLK(ptTimer, false);

    switch(eMccr)
    {
        case P_TIMER5_CLK_MCCR_LSE:
            un8MccrSel = TIMER5_CLK_MCCR_SRC_LSE;
            break;
        case P_TIMER5_CLK_MCCR_HSI:
            un8MccrSel = TIMER5_CLK_MCCR_SRC_HSI;
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    SET_SCU_TIMER5_PPCLKSR_CLK(ptScu, un8MccrSel);

    return eErr;
}

static __INLINE HAL_ERR_e TIMER5_SetExtClk(P_TIMER5_ID_e eId, TIMER5_Type *ptTimer, P_TIMER5_EXTCLK_EDGE_e eExtClkEdge)
{
    (void)eId;

    /* external clock */
    SET_TIMER5_CR_CLK(ptTimer, true);

    /* external clock edge */
    if(eExtClkEdge < P_TIMER5_EXTCLK_EDGE_MAX)
    {
        SET_TIMER5_CR_EXTCLK_EDGE(ptTimer, (uint32_t)eExtClkEdge);
    }
    else
    {
        return HAL_ERR_PARAMETER;
    }

    return HAL_ERR_OK;
}

static __INLINE HAL_ERR_e TIMER5_SetPClk(P_TIMER5_ID_e eId, TIMER5_Type *ptTimer, P_TIMER5_PCLK_DIV_e ePClkDiv)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    (void)ePClkDiv;

    /* internal pre-scaler clock */
    SET_TIMER5_CR_CLK(ptTimer, false);

    /* peri clock */
    SET_SCU_TIMER5_PPCLKSR_CLK(ptScu, 0x0);

    return HAL_ERR_OK;
}

static __INLINE HAL_ERR_e TIMER5_SetWDTRC(P_TIMER5_ID_e eId, TIMER5_Type *ptTimer)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    /* internal pre-scaler clock */
    SET_TIMER5_CR_CLK(ptTimer, false);

    /* peri clock */
    SET_SCU_TIMER5_PPCLKSR_CLK(ptScu, 0x01);

    return HAL_ERR_OK;
}

#if defined(TIMER5_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void TIMER5_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, (uint8_t)eIrq, bEnable);
}
#endif

#endif /* _HAL_TIMER5_F1X_H_ */
