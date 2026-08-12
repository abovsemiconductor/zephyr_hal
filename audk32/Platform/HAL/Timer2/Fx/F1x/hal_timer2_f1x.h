/**
 *******************************************************************************
 * @file        hal_timer2_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed Timer2
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER2_F1X_H_
#define _HAL_TIMER2_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define TIMER2_CH_NUM                                 CONFIG_TIMER2_MAX_COUNT

#if (CONFIG_TIMER2_VER_EXT == 0)

#if (CONFIG_TIMER2_VER_MINOR == 0)
#include "hal_timer2_f_01_00_00.h"
#elif (CONFIG_TIMER2_VER_MINOR == 1)
#include "hal_timer2_f_01_00_01.h"
#elif (CONFIG_TIMER2_VER_MINOR == 2)
#include "hal_timer2_f_01_00_02.h"
#elif (CONFIG_TIMER2_VER_MINOR == 3)
#include "hal_timer2_f_01_00_03.h"
#elif (CONFIG_TIMER2_VER_MINOR == 4)
#include "hal_timer2_f_01_00_04.h"
#else
#error "define CONFIG_TIMER2_VER_MINOR of F-type TIMER2 at config_xxx.h"
#endif

#else
#error "define CONFIG_TIMER2_VER_EXT of F-type TIMER2 at config_xxx.h"
#endif

static __inline HAL_ERR_e TIMER2_SetScuEnable(P_TIMER2_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_TIMER2_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_TIMER2_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_TIMER2_PCER(ptScu, (uint32_t)eId, un32Enable);

    return HAL_ERR_OK;
}

static __inline uint32_t TIMER2_GetRegOffset(void)
{
    return TIMER2_REG_OFFSET_CNT;
}

static __inline TIMER2_Type *TIMER2_GetReg(uint32_t un32Id)
{
    return (TIMER2_Type *)(TIMER2_REG_BASE + (TIMER2_REG_OFFSET * un32Id));
}

static __inline IRQn_Type TIMER2_GetIRQNum(P_TIMER2_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(TIMER2_0_IRQ)
        case P_TIMER2_ID_0:
            eIrq = TIMER2_0_IRQ;
            break;
#endif
#if defined(TIMER2_1_IRQ)
        case P_TIMER2_ID_1:
            eIrq = TIMER2_1_IRQ;
            break;
#endif
#if defined(TIMER2_2_IRQ)
        case P_TIMER2_ID_2:
            eIrq = TIMER2_2_IRQ;
            break;
#endif
#if defined(TIMER2_3_IRQ)
        case P_TIMER2_ID_3:
            eIrq = TIMER2_3_IRQ;
            break;
#endif
#if defined(TIMER2_4_IRQ)
        case P_TIMER2_ID_4:
            eIrq = TIMER2_4_IRQ;
            break;
#endif
#if defined(TIMER2_5_IRQ)
        case P_TIMER2_ID_5:
            eIrq = TIMER2_5_IRQ;
            break;
#endif
#if defined(TIMER2_6_IRQ)
        case P_TIMER2_ID_6:
            eIrq = TIMER2_6_IRQ;
            break;
#endif
#if defined(TIMER2_7_IRQ)
        case P_TIMER2_ID_7:
            eIrq = TIMER2_7_IRQ;
            break;
#endif
#if defined(TIMER2_8_IRQ)
        case P_TIMER2_ID_8:
            eIrq = TIMER2_8_IRQ;
            break;
#endif
#if defined(TIMER2_9_IRQ)
        case P_TIMER2_ID_9:
            eIrq = TIMER2_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline P_TIMER2_MODE_e TIMER2_ConvMode(P_TIMER2_MODE_e eMode)
{
    return eMode;
}

static __inline uint32_t TIMER2_ConvPol(P_TIMER2_POL_e ePol)
{
    switch(ePol)
    {
        case P_TIMER2_POL_HIGH:
             return TIMER2_POLARITY_HIGH;
        case P_TIMER2_POL_LOW:
             return TIMER2_POLARITY_LOW;
        default:
             return P_TIMER2_POL_MAX;
    }
}

static __inline uint32_t TIMER2_GetIntFlag(TIMER2_Type *ptPeri)
{
    uint32_t uiFlg=0;
    uint32_t uiIntFlg=0;

    uiFlg=GET_TIMER2_IER_MATCH_FLAG(ptPeri);
    if(uiFlg)
    {
        uiIntFlg |= P_TIMER2_INTR_FLAG_MATCH;
    }
    uiFlg=GET_TIMER2_IER_CAP_FLAG(ptPeri);
    if(uiFlg)
    {
        uiIntFlg |= P_TIMER2_INTR_FLAG_CAP;
    }
    return uiIntFlg;
}

static __INLINE HAL_ERR_e TIMER2_SetMccrClk(P_TIMER2_ID_e eId, TIMER2_Type *ptTimer, P_TIMER2_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
#if defined(TIMER2_FEATURE_ONLY_LSE_CLOCK)
#else
    uint8_t un8MccrSel;
#endif

#if defined(TIMER2_FEATURE_UNSUPPORT_MCCR_TIMER21)
    /* timer21 only peri and external clock */
    if(eId == P_TIMER2_ID_1)
    {
        return HAL_ERR_NOT_SUPPORTED;
    }
#endif

#if defined(TIMER2_FEATURE_ONLY_LSE_CLOCK)

    SET_SCU_TIMER2_PPCLKSR_CLK0(ptScu, false);

#else

#if defined(TIMER2_FEATURE_SEPARATED_MCCR_TIMER21)
    if(eId == P_TIMER2_ID_1)
    {
        SET_SCU_TIMER2_PPCLKSR_CLK1(ptScu, false);
    }
    else
    {
        SET_SCU_TIMER2_PPCLKSR_CLK0(ptScu, false);
    }
#else
    SET_SCU_TIMER2_PPCLKSR_CLK0(ptScu, false);

    /* internal pre-scaler clock */
    SET_TIMER2_CR_CLK(ptTimer, false);
#endif

    switch(eMccr)
    {
        case P_TIMER2_CLK_MCCR_LSI:
            un8MccrSel = TIMER2_CLK_MCCR_SRC_LSI;
            break;
        case P_TIMER2_CLK_MCCR_LSE:
            un8MccrSel = TIMER2_CLK_MCCR_SRC_LSE;
            break;
        case P_TIMER2_CLK_MCCR_MCLK:
            un8MccrSel = TIMER2_CLK_MCCR_SRC_MCLK;
            break;
        case P_TIMER2_CLK_MCCR_HSI:
            un8MccrSel = TIMER2_CLK_MCCR_SRC_HSI;
            break;
        case P_TIMER2_CLK_MCCR_HSE:
            un8MccrSel = TIMER2_CLK_MCCR_SRC_HSE;
            break;
        case P_TIMER2_CLK_MCCR_PLL:
            un8MccrSel = TIMER2_CLK_MCCR_SRC_PLL;
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

#if defined(TIMER2_FEATURE_SEPARATED_MCCR_TIMER21)
    if(eId == P_TIMER2_ID_1)
    {
        SET_SCU_TIMER2_MCCR_SEL1(ptScu, un8MccrSel);
        SET_SCU_TIMER2_MCCR_DIV1(ptScu, un8MccrDiv);
    }
    else
    {
        SET_SCU_TIMER2_MCCR_SEL0(ptScu, un8MccrSel);
        SET_SCU_TIMER2_MCCR_DIV0(ptScu, un8MccrDiv);
    }
#else
    SET_SCU_TIMER2_MCCR_SEL0(ptScu, un8MccrSel);
    SET_SCU_TIMER2_MCCR_DIV0(ptScu, un8MccrDiv);
#endif

#endif /* TIMER2_FEATURE_ONLY_LSE_CLOCK */
    return eErr;
}

static __INLINE HAL_ERR_e TIMER2_SetExtClk(P_TIMER2_ID_e eId, TIMER2_Type *ptTimer, P_TIMER2_EXTCLK_EDGE_e eExtClkEdge)
{
    (void)eId;

    /* external clock */
    SET_TIMER2_CR_CLK(ptTimer, true);

    /* external clock edge */
    if(eExtClkEdge < P_TIMER2_EXTCLK_EDGE_MAX)
    {
        SET_TIMER2_CR_EXTCLK_EDGE(ptTimer, (uint32_t)eExtClkEdge);
    }
    else
    {
        return HAL_ERR_PARAMETER;
    }

    return HAL_ERR_OK;
}

static __INLINE HAL_ERR_e TIMER2_SetPClk(P_TIMER2_ID_e eId, TIMER2_Type *ptTimer, P_TIMER2_PCLK_DIV_e ePClkDiv)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    (void)ePClkDiv;

    /* peri clock */
#if defined(TIMER2_FEATURE_SEPARATED_MCCR_TIMER21)
    if(eId == P_TIMER2_ID_1)
    {
        SET_SCU_TIMER2_PPCLKSR_CLK1(ptScu, true);
    }
    else
    {
        SET_SCU_TIMER2_PPCLKSR_CLK0(ptScu, true);
    }
#else
    SET_SCU_TIMER2_PPCLKSR_CLK0(ptScu, true);
#endif

    /* internal pre-scaler clock */
    SET_TIMER2_CR_CLK(ptTimer, false);

    return HAL_ERR_OK;
}

#if defined(TIMER2_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void TIMER2_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, (uint8_t)eIrq, bEnable);
}
#endif

#endif /* _HAL_TIMER2_F1X_H_ */
