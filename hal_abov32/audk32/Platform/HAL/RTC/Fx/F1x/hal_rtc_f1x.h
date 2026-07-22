/**
 *******************************************************************************
 * @file        hal_rtc_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for f1x typed RTC
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_RTC_F1X_H_
#define _HAL_RTC_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define RTC_CH_NUM                                    CONFIG_RTC_MAX_COUNT

#if (CONFIG_RTC_VER_EXT == 0)

#if (CONFIG_RTC_VER_MINOR == 0)
#include "hal_rtc_f_01_00_00.h"
#elif (CONFIG_RTC_VER_MINOR == 1)
#include "hal_rtc_f_01_00_01.h"
#elif (CONFIG_RTC_VER_MINOR == 2)
#include "hal_rtc_f_01_00_02.h"
#else
#error "define CONFIG_RTC_VER_MINOR of F-type RTC at config_xxx.h"
#endif

#else
#error "define CONFIG_RTC_VER_EXT of F-type RTC at config_xxx.h"
#endif

static __inline RTC_Type *RTC_GetReg(P_RTC_ID_e eId)
{
    return (RTC_Type *)(RTC_REG_BASE);
}

static __inline IRQn_Type RTC_GetIRQNum(P_RTC_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(RTC_0_IRQ)
        case P_RTC_ID_0:
            eIrq = RTC_0_IRQ;
            break;
#endif
#if defined(RTC_1_IRQ)
        case P_RTC_ID_1:
            eIrq = RTC_1_IRQ;
            break;
#endif
#if defined(RTC_2_IRQ)
        case P_RTC_ID_2:
            eIrq = RTC_2_IRQ;
            break;
#endif
#if defined(RTC_3_IRQ)
        case P_RTC_ID_3:
            eIrq = RTC_3_IRQ;
            break;
#endif
#if defined(RTC_4_IRQ)
        case P_RTC_ID_4:
            eIrq = RTC_4_IRQ;
            break;
#endif
#if defined(RTC_5_IRQ)
        case P_RTC_ID_5:
            eIrq = RTC_5_IRQ;
            break;
#endif
#if defined(RTC_6_IRQ)
        case P_RTC_ID_6:
            eIrq = RTC_6_IRQ;
            break;
#endif
#if defined(RTC_7_IRQ)
        case P_RTC_ID_7:
            eIrq = RTC_7_IRQ;
            break;
#endif
#if defined(RTC_8_IRQ)
        case P_RTC_ID_8:
            eIrq = RTC_8_IRQ;
            break;
#endif
#if defined(RTC_9_IRQ)
        case P_RTC_ID_9:
            eIrq = RTC_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline HAL_ERR_e RTC_SetScuEnable(P_RTC_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_RTC_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_RTC_PER(ptScu, eId, un32Enable);
    SET_SCU_RTC_PCER(ptScu, eId, un32Enable);

    return HAL_ERR_OK;
}

static __inline HAL_ERR_e RTC_SetClk(P_RTC_ID_e eId, P_RTC_CLK_e eClk, P_RTC_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    (void)un8MccrDiv;

    if((uint32_t)eId >= CONFIG_RTC_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    switch(eClk)
    {
        case P_RTC_CLK_WDTRC:
            SET_SCU_RTC_CLK_SEL(ptScu, RTC_CLK_SRC_WDTRC);
            break;
        case P_RTC_CLK_MCCR:
            if (eMccr == P_RTC_CLK_MCCR_MCLK)
            {
                SET_SCU_RTC_CLK_SEL(ptScu, RTC_CLK_SRC_MCLK);
            }
            else if (eMccr == P_RTC_CLK_MCCR_LSE)
            {
                SET_SCU_RTC_CLK_SEL(ptScu, RTC_CLK_SRC_LSE);
            }
            else if (eMccr == P_RTC_CLK_MCCR_LSI)
            {
                SET_SCU_RTC_CLK_SEL(ptScu, RTC_CLK_SRC_LSI);
            }
            else
            {
                eErr = HAL_ERR_PARAMETER;
            }
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    return eErr;
}

static __inline void RTC_SetPortMode(P_RTC_ID_e eId, bool bPortMode, bool bTimeStamp)
{
    RTC_Type *ptRtc = (RTC_Type *)RTC_REG_BASE;

    (void)bTimeStamp;

    if (bPortMode == true)
    {
        SET_RTC_CR_PORT_MODE(ptRtc, RTC_CLKOUT_32KHZ);
    }
    else
    {
        SET_RTC_CR_PORT_MODE(ptRtc, RTC_CLKOUT_1HZ);
    }
}

#if defined (RTC_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void RTC_SetIntrUnMask(IRQn_Type eIrq, bool bEnable, P_RTC_FUNC_e eFunc)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE;
    RTC_Type *ptRtc = (RTC_Type*)RTC_REG_BASE;

    SET_INTC_IRQ_UNMASK_EN(ptIntc, eIrq, bEnable);
    switch(eFunc)
    {
        case P_RTC_FUNC_WATCH:
            if (GET_RTC_IER_CONST_PERIOD_FLAG(ptRtc))
            {
                SET_RTC_IER_CONST_PERIOD_FLAG(ptRtc, true);
            }
            break;
        case P_RTC_FUNC_ALARM:
            if (GET_RTC_IER_ALARM_FLAG(ptRtc))
            {
                SET_RTC_IER_ALARM_FLAG(ptRtc, true);
            }
            break;
        default:
            break;
    }
}
#endif

#endif /* _HAL_RTC_F1X_H_ */
