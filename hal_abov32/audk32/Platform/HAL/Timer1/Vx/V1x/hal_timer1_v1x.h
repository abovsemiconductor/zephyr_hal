/**
 *******************************************************************************
 * @file        hal_timer1_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed Timer1
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER1_V1X_H_
#define _HAL_TIMER1_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define TIMER1_CH_NUM                                 CONFIG_TIMER1_MAX_COUNT

#if (CONFIG_TIMER1_VER_EXT == 0)

#if (CONFIG_TIMER1_VER_MINOR == 0)
#include "hal_timer1_v_01_00_00.h"
#else
#error "define CONFIG_TIMER1_VER_MINOR of V-type TIMER1 at config_xxx.h"
#endif

#elif (CONFIG_TIMER1_VER_EXT == 1)

#if (CONFIG_TIMER1_VER_MINOR == 0)
#include "hal_timer1_v_01_01_00.h"
#else
#error "define CONFIG_TIMER1_VER_MINOR of V-type TIMER1 at config_xxx.h"
#endif

#elif (CONFIG_TIMER1_VER_EXT == 2)

#if (CONFIG_TIMER1_VER_MINOR == 0)
#include "hal_timer1_v_01_02_00.h"
#else
#error "define CONFIG_TIMER1_VER_MINOR of V-type TIMER1 at config_xxx.h"
#endif

#else
#error "define CONFIG_TIMER1_VER_EXT of V-type TIMER1 at config_xxx.h"
#endif

static __inline HAL_ERR_e TIMER1_SetScuEnable(P_TIMER1_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= CONFIG_TIMER1_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_TIMER1_PER(ptScu, SCU_ENABLE((uint32_t)eId), un32Enable);
    SET_SCU_TIMER1_PCER(ptScu, SCU_ENABLE((uint32_t)eId), un32Enable);

    return eErr;
}

static __INLINE TIMER1_Type *TIMER1_GetReg(uint32_t un32Id)
{
    return (TIMER1_Type *)(TIMER1_REG_BASE + (TIMER1_REG_OFFSET * un32Id));
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

static __inline uint32_t TIMER1_ConvMode(P_TIMER1_MODE_e eMode)
{
        switch(eMode)
        {
            case P_TIMER1_MODE_COUNTER:
                 return TIMER1_MD_COUNTER;
            case P_TIMER1_MODE_PWM:
                 return TIMER1_MD_PWM;
            case P_TIMER1_MODE_ONESHOT:
                 return TIMER1_MD_ONESHOT;
            case P_TIMER1_MODE_CAPTURE:
                 return TIMER1_MD_CAPTURE;
            default:
                 return P_TIMER1_MODE_MAX;
         }
}

static __inline uint32_t TIMER1_ConvPol(P_TIMER1_POL_e ePol)
{
    return ePol;
}

static __inline uint32_t TIMER1_GetIntFlag(TIMER1_Type *ptPeri)
{
    uint32_t un32Flg=0;
    uint32_t un32IntFlg=0;

    un32Flg = GET_TIMER1_CR_MFA(ptPeri);
    if(un32Flg)
    {
        un32IntFlg |= P_TIMER1_INTR_FLAG_A;
    }
    un32Flg = GET_TIMER1_CR_MFB(ptPeri);
    if(un32Flg)
    {
        un32IntFlg |= P_TIMER1_INTR_FLAG_B;
    }
    un32Flg = GET_TIMER1_CR_OVF(ptPeri);
    if(un32Flg)
    {
        un32IntFlg |= P_TIMER1_INTR_FLAG_OVF;
    }
    return un32IntFlg;
}

static __INLINE HAL_ERR_e TIMER1_SetMccrClk(P_TIMER1_ID_e eId, TIMER1_Type *ptTimer, P_TIMER1_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    uint8_t un8MccrSel;
    uint32_t un32AddrReg = 0;

    SET_TIMER1_CR_CLK(ptTimer, TIMER1_CLK_SRC_MCCR);

    switch(eMccr)
    {
        case P_TIMER1_CLK_MCCR_LSI:
            un8MccrSel = TIMER1_CLK_MCCR_SRC_LSI;
            break;
#if defined(TIMER1_FEATURE_UNSUPPORT_MCCR_LSE)
#else
        case P_TIMER1_CLK_MCCR_LSE:
            un8MccrSel = TIMER1_CLK_MCCR_SRC_LSE;
            break;
#endif
        case P_TIMER1_CLK_MCCR_HSI:
            un8MccrSel = TIMER1_CLK_MCCR_SRC_HSI;
            break;
        case P_TIMER1_CLK_MCCR_HSE:
            un8MccrSel = TIMER1_CLK_MCCR_SRC_HSE;
            break;
#if defined(TIMER1_FEATURE_UNSUPPORT_MCCR_PLL)
#else
        case P_TIMER1_CLK_MCCR_PLL:
            un8MccrSel = TIMER1_CLK_MCCR_SRC_PLL;
            break;
#endif
#if defined(TIMER1_FEATURE_UNSUPPORT_MCCR_MCLK)
#else
        case P_TIMER1_CLK_MCCR_MCLK:
            un8MccrSel = TIMER1_CLK_MCCR_SRC_MCLK;
            break;
#endif
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    if (eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    if(eErr == HAL_ERR_OK)
    {
        un32AddrReg = (uint32_t)(GET_SCU_MCCR_BASE_ADDR(ptScu));
        SET_SCU_TIMER1_MCCR_SEL(un32AddrReg, SCU_TIMER1_MCCR_OFFSET, SCU_TIMER1_MCCR_SEL_OFFSET((uint8_t)eId), SCU_TIMER1_MCCR_SEL_MSK, un8MccrSel);
        SET_SCU_TIMER1_MCCR_DIV(un32AddrReg, SCU_TIMER1_MCCR_OFFSET, SCU_TIMER1_MCCR_DIV_OFFSET((uint8_t)eId), SCU_TIMER1_MCCR_DIV_MSK, un8MccrDiv);
    }

    return HAL_ERR_OK;
}

static __INLINE HAL_ERR_e TIMER1_SetExtClk(P_TIMER1_ID_e eId, TIMER1_Type *ptTimer, P_TIMER1_EXTCLK_EDGE_e eExtClkEdge)
{
    (void)eId;
    (void)eExtClkEdge;
    SET_TIMER1_CR_CLK(ptTimer, TIMER1_CLK_SRC_EXT);

    return HAL_ERR_OK;
}

static __INLINE HAL_ERR_e TIMER1_SetPClk(P_TIMER1_ID_e eId, TIMER1_Type *ptTimer, P_TIMER1_PCLK_DIV_e ePClkDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    uint8_t un8Clk = 0;

    switch(ePClkDiv)
    {
        case P_TIMER1_PCLK_DIV_2:
            un8Clk = TIMER1_CLK_SRC_PDIV_2;
            break;
        case P_TIMER1_PCLK_DIV_4:
            un8Clk = TIMER1_CLK_SRC_PDIV_4;
            break;
        case P_TIMER1_PCLK_DIV_16:
            un8Clk = TIMER1_CLK_SRC_PDIV_16;
            break;
        case P_TIMER1_PCLK_DIV_64:
            un8Clk = TIMER1_CLK_SRC_PDIV_64;
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    SET_TIMER1_CR_CLK(ptTimer, un8Clk);

    return eErr;
}

#endif /* _HAL_TIMER1_V1X_H_ */
