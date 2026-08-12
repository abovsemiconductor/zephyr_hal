/**
 *******************************************************************************
 * @file        hal_timer4_f1x.h
 * @author      ABOV R&D Division 
 * @brief       Private APIs for F1x typed timer4
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER4_F1X_H_
#define _HAL_TIMER4_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define TIMER4_CH_NUM                                 CONFIG_TIMER4_MAX_COUNT

#if (CONFIG_TIMER4_VER_EXT == 0)

#if (CONFIG_TIMER4_VER_MINOR == 0)
#include "hal_timer4_f_01_00_00.h"
#else
#error "define CONFIG_TIMER4_VER_MINOR of F-type TIMER4 at config_xxx.h"
#endif

#else
#error "define CONFIG_TIMER4_VER_EXT of F-type TIMER4 at config_xxx.h"
#endif

static __inline HAL_ERR_e TIMER4_SetScuEnable(P_TIMER4_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= CONFIG_TIMER4_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_TIMER4_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_TIMER4_PCER(ptScu, (uint32_t)eId, un32Enable);
    
    return eErr;
}

static __inline uint32_t TIMER4_GetRegOffset(void)
{
    return TIMER4_REG_OFFSET_CNT;
}

static __inline TIMER4_Type *TIMER4_GetReg(uint32_t un32Id)
{
    return (TIMER4_Type *)(TIMER4_REG_BASE + (TIMER4_REG_OFFSET * un32Id));
}

static __inline IRQn_Type TIMER4_GetIRQNum(P_TIMER4_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(TIMER4_0_IRQ)
        case P_TIMER4_ID_0:
            eIrq = TIMER4_0_IRQ;
            break;
#endif
#if defined(TIMER4_1_IRQ)
        case P_TIMER4_ID_1:
            eIrq = TIMER4_1_IRQ;
            break;
#endif
#if defined(TIMER4_2_IRQ)
        case P_TIMER4_ID_2:
            eIrq = TIMER4_2_IRQ;
            break;
#endif
#if defined(TIMER4_3_IRQ)
        case P_TIMER4_ID_3:
            eIrq = TIMER4_3_IRQ;
            break;
#endif
#if defined(TIMER4_4_IRQ)
        case P_TIMER4_ID_4:
            eIrq = TIMER4_4_IRQ;
            break;
#endif
#if defined(TIMER4_5_IRQ)
        case P_TIMER4_ID_5:
            eIrq = TIMER4_5_IRQ;
            break;
#endif
#if defined(TIMER4_6_IRQ)
        case P_TIMER4_ID_6:
            eIrq = TIMER4_6_IRQ;
            break;
#endif
#if defined(TIMER4_7_IRQ)
        case P_TIMER4_ID_7:
            eIrq = TIMER4_7_IRQ;
            break;
#endif
#if defined(TIMER4_8_IRQ)
        case P_TIMER4_ID_8:
            eIrq = TIMER4_8_IRQ;
            break;
#endif
#if defined(TIMER4_9_IRQ)
        case P_TIMER4_ID_9:
            eIrq = TIMER4_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline P_TIMER4_MODE_e TIMER4_ConvMode(P_TIMER4_MODE_e eMode)
{
    return eMode;
}

static __inline uint32_t TIMER4_ConvPol(P_TIMER4_POL_e ePol)
{
    switch(ePol)
    {
        case P_TIMER4_POL_HIGH:
             return TIMER4_POLARITY_HIGH;
        case P_TIMER4_POL_LOW:
             return TIMER4_POLARITY_LOW;
        default:
             return P_TIMER4_POL_MAX;
    }
}

static __inline uint32_t TIMER4_GetIntFlag(TIMER4_Type *ptPeri)
{
    uint32_t uiFlg=0;
    uint32_t uiIntFlg=0;
  	
    uiFlg=GET_TIMER4_IER_MATCH_FLAG(ptPeri);
    if(uiFlg)
    {
        uiIntFlg |= P_TIMER4_INTR_FLAG_MATCH;
    }
    uiFlg=GET_TIMER4_IER_CAP_FLAG(ptPeri);
    if(uiFlg)
    {
        uiIntFlg |= P_TIMER4_INTR_FLAG_CAP;
    }
    return uiIntFlg;
}

static __INLINE HAL_ERR_e TIMER4_SetMccrClk(P_TIMER4_ID_e eId, TIMER4_Type *ptTimer, P_TIMER4_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    uint8_t un8MccrSel;

    SET_SCU_TIMER4_PPCLKSR_CLK(ptScu, false);

    switch(eMccr)
    {
        case P_TIMER4_CLK_MCCR_LSI:
            un8MccrSel = TIMER4_CLK_MCCR_SRC_LSI;
            break;
        case P_TIMER4_CLK_MCCR_LSE:
            un8MccrSel = TIMER4_CLK_MCCR_SRC_LSE;
            break;
        case P_TIMER4_CLK_MCCR_MCLK:
            un8MccrSel = TIMER4_CLK_MCCR_SRC_MCLK;
            break;
        case P_TIMER4_CLK_MCCR_HSI:
            un8MccrSel = TIMER4_CLK_MCCR_SRC_HSI;
            break;
        case P_TIMER4_CLK_MCCR_HSE:
            un8MccrSel = TIMER4_CLK_MCCR_SRC_HSE;
            break;
        case P_TIMER4_CLK_MCCR_PLL:
            un8MccrSel = TIMER4_CLK_MCCR_SRC_PLL;
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    SET_SCU_TIMER4_MCCR_SEL(ptScu, un8MccrSel);
    SET_SCU_TIMER4_MCCR_DIV(ptScu, un8MccrDiv);

    return eErr;
}

static __INLINE HAL_ERR_e TIMER4_SetExtClk(P_TIMER4_ID_e eId, TIMER4_Type *ptTimer, P_TIMER4_EXTCLK_EDGE_e eExtClkEdge)
{
    (void)eId;

    /* external clock */
    SET_TIMER4_CR_CLK(ptTimer, true);

    /* external clock edge */
    if(eExtClkEdge < P_TIMER4_EXTCLK_EDGE_MAX)
    {
        SET_TIMER4_CR_EXTCLK_EDGE(ptTimer, (uint32_t)eExtClkEdge);
    }
    else
    {
        return HAL_ERR_PARAMETER;
    }

    return HAL_ERR_OK;
}

static __INLINE HAL_ERR_e TIMER4_SetPClk(P_TIMER4_ID_e eId, TIMER4_Type *ptTimer, P_TIMER4_PCLK_DIV_e ePClkDiv)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    (void)ePClkDiv;

    /* peri clock */
    SET_SCU_TIMER4_PPCLKSR_CLK(ptScu, true);
    /* internal pre-scaler clock */
    SET_TIMER4_CR_CLK(ptTimer, false);

    return HAL_ERR_OK;
}

#endif /* _HAL_TIMER4_F1X_H_ */
