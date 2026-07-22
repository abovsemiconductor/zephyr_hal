/**
 *******************************************************************************
 * @file        hal_rtc_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed RTC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_RTC_V1X_H_
#define _HAL_RTC_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define RTC_CH_NUM                                    CONFIG_RTC_MAX_COUNT

#if (CONFIG_RTC_VER_EXT == 0)

#if (CONFIG_RTC_VER_MINOR == 0)
#include "hal_rtc_v_01_00_00.h"
#elif (CONFIG_RTC_VER_MINOR == 1)
#include "hal_rtc_v_01_00_01.h"
#else
#error "define CONFIG_RTC_VER_MINOR of V-type RTC at config_xxx.h"
#endif
#elif (CONFIG_RTC_VER_EXT == 1)
#if (CONFIG_RTC_VER_MINOR == 0)
#include "hal_rtc_v_01_01_00.h"
#else
#error "define CONFIG_RTC_VER_MINOR of V-type RTC at config_xxx.h"
#endif
#else
#error "define CONFIG_RTC_VER_EXT of V-type RTC at config_xxx.h"
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

    SET_SCU_RTC_PER(ptScu, un32Enable);
    SET_SCU_RTC_PCER(ptScu, un32Enable);

    return HAL_ERR_OK;
}

static __inline HAL_ERR_e RTC_SetClk(P_RTC_ID_e eId, P_RTC_CLK_e eClk, P_RTC_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_RTC_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(eClk == P_RTC_CLK_LSI40KHZ)
    {
#if defined(RTC_FEATURE_UNSUPPORT_LSI40KHZ)
        return HAL_ERR_NOT_SUPPORTED;
#else
        SET_SCU_RTC_PPCLKSR_CLK(ptScu, false);
        SET_SCU_RTC_MCCR_LSI40KHZ(ptScu, true);
#endif
    }
    else
    {
        SET_SCU_RTC_MCCR_LSI40KHZ(ptScu, false);
        SET_SCU_RTC_PPCLKSR_CLK(ptScu, true);
        SET_SCU_RTC_MCCR_SEL(ptScu, (uint8_t)eMccr);
        SET_SCU_RTC_MCCR_DIV(ptScu, (uint8_t)un8MccrDiv);
    }

    return HAL_ERR_OK;
}

static __inline void RTC_SetPortMode(P_RTC_ID_e eId, bool bPortMode, bool bTimeStamp)
{
#if defined(RTC_FEATURE_UNSUPPORT_PIN_FUNCTION)
    (void)eId;
    (void)bPortMode;
    (void)bTimeStamp;
#else
    RTC_Type *ptRtc = (RTC_Type *)RTC_REG_BASE;

    if (bPortMode == true)
    {
        if (bTimeStamp == true)
        {
            SET_RTC_CR_PORT_MODE(ptRtc, RTC_PC13_TSIN_MODE);
        }
        else
        {
            /* For measuring real clock frequency through PC13 port */
            SET_RTC_DR_SUBSEC(ptRtc, 0x01);
            SET_RTC_CR_PORT_MODE(ptRtc, RTC_PC13_CLKOUT_MODE);
        }
    }
    else
    {
        SET_RTC_CR_PORT_MODE(ptRtc, RTC_PC13_FLOATING);
    }
#endif
}

static __inline void RTC_SetWkupSrc(bool bEnable, bool bExtPinEnable)
{
#if defined(RTC_FEATURE_WAKEUP_SOURCE)
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    RTC_Type *ptRtc = (RTC_Type *)RTC_REG_BASE;
    uint8_t un8Data = 0;
    SET_SCU_RTC_WKUP_EN(ptScu, bEnable);

    if(bExtPinEnable == true)
    {
        un8Data = 0x3;
    }
    SET_RTC_WKUP_EN(ptRtc, un8Data);
    SET_RTC_WKUP_PIN_EN(ptRtc, bExtPinEnable);
#else
    (void)bEnable;
#endif
}

static __inline void RTC_GetWkupEvent(bool *bEvent)
{
#if defined(RTC_FEATURE_WAKEUP_SOURCE)
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    uint8_t un8Prev = GET_SCU_RTC_PREVMODE(ptScu);

    if(GET_SCU_RTC_WKUP_EN(ptScu))
    {
        if(un8Prev == 0x01 || un8Prev == 0x07)
        {
            *bEvent = GET_SCU_RTC_WKUP_FLAG(ptScu);
        }
    }
#else
    (void)*bEvent;
#endif
}


#endif /* _HAL_RTC_V1X_H_ */
