/**
 *******************************************************************************
 * @file        hal_wdt_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed WDT
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_WDT_F1X_H_
#define _HAL_WDT_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define WDT_CH_NUM                                    CONFIG_WDT_MAX_COUNT

#if (CONFIG_WDT_VER_EXT == 0)

#if (CONFIG_WDT_VER_MINOR == 0)
#include "hal_wdt_f_01_00_00.h"
#elif (CONFIG_WDT_VER_MINOR == 1)
#include "hal_wdt_f_01_00_01.h"
#elif (CONFIG_WDT_VER_MINOR == 2)
#include "hal_wdt_f_01_00_02.h"
#else
#error "define CONFIG_WDT_VER_MINOR of F-type WDT at config_xxx.h"
#endif

#else
#error "define CONFIG_WDT_VER_EXT of F-type WDT at config_xxx.h"
#endif

static __inline WDT_Type *WDT_GetReg(P_WDT_ID_e eId)
{
    return (WDT_Type *)(WDT_REG_BASE + (WDT_REG_OFFSET * (uint32_t)eId));
}

static __inline IRQn_Type WDT_GetIRQNum(P_WDT_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(WDT_0_IRQ)
        case P_WDT_ID_0:
            eIrq = WDT_0_IRQ;
            break;
#endif
#if defined(WDT_1_IRQ)
        case P_WDT_ID_1:
            eIrq = WDT_1_IRQ;
            break;
#endif
#if defined(WDT_2_IRQ)
        case P_WDT_ID_2:
            eIrq = WDT_2_IRQ;
            break;
#endif
#if defined(WDT_3_IRQ)
        case P_WDT_ID_3:
            eIrq = WDT_3_IRQ;
            break;
#endif
#if defined(WDT_4_IRQ)
        case P_WDT_ID_4:
            eIrq = WDT_4_IRQ;
            break;
#endif
#if defined(WDT_5_IRQ)
        case P_WDT_ID_5:
            eIrq = WDT_5_IRQ;
            break;
#endif
#if defined(WDT_6_IRQ)
        case P_WDT_ID_6:
            eIrq = WDT_6_IRQ;
            break;
#endif
#if defined(WDT_7_IRQ)
        case P_WDT_ID_7:
            eIrq = WDT_7_IRQ;
            break;
#endif
#if defined(WDT_8_IRQ)
        case P_WDT_ID_8:
            eIrq = WDT_8_IRQ;
            break;
#endif
#if defined(WDT_9_IRQ)
        case P_WDT_ID_9:
            eIrq = WDT_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}


static __inline HAL_ERR_e WDT_SetClk(P_WDT_ID_e eId, P_WDT_CLK_e eClk, P_WDT_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

#if defined(WDT_FEATURE_USE_PCLK)
#else
    if(eClk == P_WDT_CLK_PCLK)
    {
        return HAL_ERR_NOT_SUPPORTED;
    }
#endif

    SET_SCU_WDT_PPCLKSR_CLK(ptScu, WDT_PPCLKSR(eClk));

#if defined(WDT_FEATURE_USE_MCCR_CLOCK)
    if(eClk == P_WDT_CLK_MCCR)
    {
	switch(eId)
	{
#if (CONFIG_WDT_MAX_COUNT > 0)
	    case P_WDT_ID_0:
	         SET_SCU_WDT_MCCR_SEL0(ptScu, SCU_WDT_MCCR_MODE(eMccr));
	         SET_SCU_WDT_MCCR_DIV0(ptScu, un8MccrDiv);
	         break;
#endif
#if (CONFIG_WDT_MAX_COUNT > 1)
	    case P_WDT_ID_1:
	         SET_SCU_WDT_MCCR_SEL1(ptScu, SCU_WDT_MCCR_MODE(eMccr));
	         SET_SCU_WDT_MCCR_DIV1(ptScu, un8MccrDiv);
	         break;
#endif
	    case P_WDT_ID_2:
	    case P_WDT_ID_3:
	    case P_WDT_ID_4:
	    case P_WDT_ID_5:
	    case P_WDT_ID_6:
	    case P_WDT_ID_7:
	    case P_WDT_ID_8:
	    case P_WDT_ID_9:
	    default:
                 eErr = HAL_ERR_PARAMETER;
	         break;
        }
    }
#else
    if(eClk == P_WDT_CLK_MCCR)
    {
        return HAL_ERR_NOT_SUPPORTED;
    }
#endif

    return eErr;
}

static __inline void WDT_SetResetEnable(uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    SET_SCU_WDT_RST_CLR(ptScu, true);
    SET_SCU_WDT_RST_EN(ptScu, un32Enable);
}

static __inline void WDT_SetWkupSrc(bool bEnable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    SET_SCU_WDT_WKUP_EN(ptScu, bEnable);
}

static __inline void WDT_GetWkupEvent(bool *bEvent)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    uint8_t un8Prev = GET_SCU_WDT_PREVMODE(ptScu);

    if(GET_SCU_WDT_WKUP_EN(ptScu))
    {
        if(un8Prev == 0x01 || un8Prev == 0x02)
        {
            *bEvent = GET_SCU_WDT_WKUP_FLAG(ptScu);
        }
    }
}

#if defined(WDT_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void PRV_WDT_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, (uint8_t)eIrq, bEnable);
}
#endif

#endif /* _HAL_WDT_F1X_H_ */
