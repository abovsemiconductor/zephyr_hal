/**
 *******************************************************************************
 * @file        hal_timer1_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed Timer1
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER1_F1X_H_
#define _HAL_TIMER1_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define TIMER1_CH_NUM                                 CONFIG_TIMER1_MAX_COUNT

#if (CONFIG_TIMER1_VER_EXT == 0)

#if (CONFIG_TIMER1_VER_MINOR == 0)
#include "hal_timer1_f_01_00_00.h"
#elif (CONFIG_TIMER1_VER_MINOR == 1)
#include "hal_timer1_f_01_00_01.h"
#elif (CONFIG_TIMER1_VER_MINOR == 2)
#include "hal_timer1_f_01_00_02.h"
#else
#error "define CONFIG_TIMER1_VER_MINOR of F-type TIMER1 at config_xxx.h"
#endif

#elif (CONFIG_TIMER1_VER_EXT == 1)

#if (CONFIG_TIMER1_VER_MINOR == 0)
#include "hal_timer1_f_01_01_00.h"
#else
#error "define CONFIG_TIMER1_VER_MINOR of F-type TIMER1 at config_xxx.h"
#endif

#else
#error "define CONFIG_TIMER1_VER_EXT of F-type TIMER1 at config_xxx.h"
#endif

static __inline HAL_ERR_e TIMER1_SetScuEnable(P_TIMER1_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= CONFIG_TIMER1_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_TIMER1_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_TIMER1_PCER(ptScu, (uint32_t)eId, un32Enable);

    return eErr;
}

static __inline uint32_t TIMER1_GetRegOffset(void)
{
    return TIMER1_REG_OFFSET_CNT;
}

static __inline TIMER1_Type *TIMER1_GetReg(uint32_t un32Id)
{
    if(un32Id < TIMER1_ID_SKIP_CNT)
        return (TIMER1_Type *)(TIMER1_REG_BASE + (TIMER1_REG_OFFSET * un32Id));
    else
        return (TIMER1_Type *)(TIMER1_REG_BASE + TIMER1_REG_TIMER_OFFSET + (TIMER1_REG_OFFSET * un32Id));
}

static __inline IRQn_Type TIMER1_GetIRQNum(P_TIMER1_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(TIMER1_0_IRQ)
        case P_TIMER1_ID_0:
            eIrq = TIMER1_0_IRQ;
            break;
#endif
#if defined(TIMER1_1_IRQ)
        case P_TIMER1_ID_1:
            eIrq = TIMER1_1_IRQ;
            break;
#endif
#if defined(TIMER1_2_IRQ)
        case P_TIMER1_ID_2:
            eIrq = TIMER1_2_IRQ;
            break;
#endif
#if defined(TIMER1_3_IRQ)
        case P_TIMER1_ID_3:
            eIrq = TIMER1_3_IRQ;
            break;
#endif
#if defined(TIMER1_4_IRQ)
        case P_TIMER1_ID_4:
            eIrq = TIMER1_4_IRQ;
            break;
#endif
#if defined(TIMER1_5_IRQ)
        case P_TIMER1_ID_5:
            eIrq = TIMER1_5_IRQ;
            break;
#endif
#if defined(TIMER1_6_IRQ)
        case P_TIMER1_ID_6:
            eIrq = TIMER1_6_IRQ;
            break;
#endif
#if defined(TIMER1_7_IRQ)
        case P_TIMER1_ID_7:
            eIrq = TIMER1_7_IRQ;
            break;
#endif
#if defined(TIMER1_8_IRQ)
        case P_TIMER1_ID_8:
            eIrq = TIMER1_8_IRQ;
            break;
#endif
#if defined(TIMER1_9_IRQ)
        case P_TIMER1_ID_9:
            eIrq = TIMER1_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline P_TIMER1_MODE_e TIMER1_ConvMode(P_TIMER1_MODE_e eMode)
{
    return eMode;
}

static __inline uint32_t TIMER1_ConvPol(P_TIMER1_POL_e ePol)
{
    switch(ePol)
    {
        case P_TIMER1_POL_HIGH:
             return TIMER1_POLARITY_HIGH;
        case P_TIMER1_POL_LOW:
             return TIMER1_POLARITY_LOW;
        default:
             return P_TIMER1_POL_MAX;
    }
}

static __inline uint32_t TIMER1_GetIntFlag(TIMER1_Type *ptPeri)
{
    uint32_t uiFlg=0;
    uint32_t uiIntFlg=0;

    uiFlg = GET_TIMER1_IER_MATCH_FLAG(ptPeri);
    if(uiFlg)
    {
        uiIntFlg |= P_TIMER1_INTR_FLAG_MATCH;
    }
    uiFlg = GET_TIMER1_IER_CAP_FLAG(ptPeri);
    if(uiFlg)
    {
        uiIntFlg |= P_TIMER1_INTR_FLAG_CAP;
    }
    return uiIntFlg;
}

static __INLINE HAL_ERR_e TIMER1_SetMccrClk(P_TIMER1_ID_e eId, TIMER1_Type *ptTimer, P_TIMER1_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
#if defined(TIMER1_FEATURE_USE_MCCR_CLOCK)
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    uint8_t un8MccrSel;
    uint32_t un32AddrReg = 0;

    (void)eId;

    /* mccr clock */
    SET_SCU_PPCLKSR_T1XCLK(ptScu, false);

    /* internal pre-scaler clock */
    SET_TIMER1_CR_CLK(ptTimer, false);

    switch(eMccr)
    {
        case P_TIMER1_CLK_MCCR_LSI:
            un8MccrSel = TIMER1_CLK_MCCR_SRC_LSI;
            break;
        case P_TIMER1_CLK_MCCR_LSE:
            un8MccrSel = TIMER1_CLK_MCCR_SRC_LSE;
            break;
        case P_TIMER1_CLK_MCCR_MCLK:
            un8MccrSel = TIMER1_CLK_MCCR_SRC_MCLK;
            break;
        case P_TIMER1_CLK_MCCR_HSI:
            un8MccrSel = TIMER1_CLK_MCCR_SRC_HSI;
            break;
        case P_TIMER1_CLK_MCCR_HSE:
            un8MccrSel = TIMER1_CLK_MCCR_SRC_HSE;
            break;
        case P_TIMER1_CLK_MCCR_PLL:
            un8MccrSel = TIMER1_CLK_MCCR_SRC_PLL;
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    if(eErr == HAL_ERR_OK)
    {
        un32AddrReg = (uint32_t)(GET_SCU_MCCR_BASE_ADDR(ptScu));
        SET_SCU_TIMER1_MCCR_SEL(un32AddrReg, SCU_TIMER1_MCCR_OFFSET, SCU_TIMER1_MCCR_SEL_OFFSET((uint8_t)eId), SCU_TIMER1_MCCR_SEL_MSK, un8MccrSel);
        SET_SCU_TIMER1_MCCR_DIV(un32AddrReg, SCU_TIMER1_MCCR_OFFSET, SCU_TIMER1_MCCR_DIV_OFFSET((uint8_t)eId), SCU_TIMER1_MCCR_DIV_MSK, un8MccrDiv);
    }

    return eErr;
#else
    (void)eId;
    (void)ptTimer;
    (void)eMccr;
    (void)un8MccrDiv;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

static __INLINE HAL_ERR_e TIMER1_SetExtClk(P_TIMER1_ID_e eId, TIMER1_Type *ptTimer, P_TIMER1_EXTCLK_EDGE_e eExtClkEdge)
{

    (void)eId;

    /* external clock */
    SET_TIMER1_CR_CLK(ptTimer, true);

    /* external clock edge */
    if(eExtClkEdge < P_TIMER1_EXTCLK_EDGE_MAX)
    {
        SET_TIMER1_CR_EXTCLK_EDGE(ptTimer, (uint32_t)eExtClkEdge);
    }
    else
    {
        return HAL_ERR_PARAMETER;
    }

    return HAL_ERR_OK;
}

static __INLINE HAL_ERR_e TIMER1_SetPClk(P_TIMER1_ID_e eId, TIMER1_Type *ptTimer, P_TIMER1_PCLK_DIV_e ePClkDiv)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    (void)eId;
    (void)ePClkDiv;

    /* peri clock */
    SET_SCU_PPCLKSR_T1XCLK(ptScu, true);

    /* internal pre-scaler clock */
    SET_TIMER1_CR_CLK(ptTimer, false);

    return HAL_ERR_OK;
}

#if defined(TIMER1_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void TIMER1_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, (uint8_t)eIrq, bEnable);
}
#endif

#endif /* _HAL_TIMER1_F1X_H_ */
