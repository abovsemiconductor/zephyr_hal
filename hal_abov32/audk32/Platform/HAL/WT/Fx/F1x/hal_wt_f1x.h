/**
 *******************************************************************************
 * @file        hal_wt_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed WT
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_WT_F1X_H_
#define _HAL_WT_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define WT_CH_NUM                                     CONFIG_WT_MAX_COUNT

#if (CONFIG_WT_VER_EXT == 0)

#if (CONFIG_WT_VER_MINOR == 0)
#include "hal_wt_f_01_00_00.h"
#elif (CONFIG_WT_VER_MINOR == 1)
#include "hal_wt_f_01_00_01.h"
#else
#error "define CONFIG_WT_VER_MINOR of F-type WT at config_xxx.h"
#endif

#else
#error "define CONFIG_WT_VER_EXT of F-type WT at config_xxx.h"
#endif

static __inline HAL_ERR_e WT_SetScuEnable(P_WT_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    HAL_ERR_e eErr = HAL_ERR_OK;

    switch(eId)
    {
#if (CONFIG_WT_MAX_COUNT > 0)
        case P_WT_ID_0:
             SET_SCU_WT_PER0(ptScu,un32Enable);
             SET_SCU_WT_PCER0(ptScu,un32Enable);
             break;
#endif
#if (CONFIG_WT_MAX_COUNT > 1)
        case P_WT_ID_1:
             SET_SCU_WT_PER1(ptScu,un32Enable);
             SET_SCU_WT_PCER1(ptScu,un32Enable);
             break;
#endif
        default:
             eErr = HAL_ERR_PARAMETER;
             break;
    }

    return eErr;

}

static __inline WT_Type *WT_GetReg(P_WT_ID_e eId)
{
    return (WT_Type *)(WT_BASE + (WT_REG_OFFSET * (uint32_t)eId));
}

static __inline IRQn_Type WT_GetIRQNum(P_WT_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(WT_0_IRQ)
        case P_WT_ID_0:
            eIrq = WT_0_IRQ;
            break;
#endif
#if defined(WT_1_IRQ)
        case P_WT_ID_1:
            eIrq = WT_1_IRQ;
            break;
#endif
#if defined(WT_2_IRQ)
        case P_WT_ID_2:
            eIrq = WT_2_IRQ;
            break;
#endif
#if defined(WT_3_IRQ)
        case P_WT_ID_3:
            eIrq = WT_3_IRQ;
            break;
#endif
#if defined(WT_4_IRQ)
        case P_WT_ID_4:
            eIrq = WT_4_IRQ;
            break;
#endif
#if defined(WT_5_IRQ)
        case P_WT_ID_5:
            eIrq = WT_5_IRQ;
            break;
#endif
#if defined(WT_6_IRQ)
        case P_WT_ID_6:
            eIrq = WT_6_IRQ;
            break;
#endif
#if defined(WT_7_IRQ)
        case P_WT_ID_7:
            eIrq = WT_7_IRQ;
            break;
#endif
#if defined(WT_8_IRQ)
        case P_WT_ID_8:
            eIrq = WT_8_IRQ;
            break;
#endif
#if defined(WT_9_IRQ)
        case P_WT_ID_9:
            eIrq = WT_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline HAL_ERR_e WT_SetClk(P_WT_ID_e eId, P_WT_CLK_e eClk, P_WT_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    SET_SCU_WT_PPCLKSR_CLK(ptScu, eClk);

    if(eClk == P_WT_CLK_MCCR)
    {
	switch(eId)
	{
#if (CONFIG_WT_MAX_COUNT > 0)
	    case P_WT_ID_0:
	        SET_SCU_WT_MCCR_SEL0(ptScu,SCU_WT_MCCR_MODE(eMccr));
	        SET_SCU_WT_MCCR_DIV0(ptScu,un8MccrDiv);
                break;
#endif
#if (CONFIG_WT_MAX_COUNT > 1)
	    case P_WT_ID_1:
	        SET_SCU_WT_MCCR_SEL1(ptScu,SCU_WT_MCCR_MODE(eMccr));
	        SET_SCU_WT_MCCR_DIV1(ptScu,un8MccrDiv);
                break;
#endif
	    case P_WT_ID_2:
	    case P_WT_ID_3:
	    case P_WT_ID_4:
	    case P_WT_ID_5:
	    case P_WT_ID_6:
	    case P_WT_ID_7:
	    case P_WT_ID_8:
	    case P_WT_ID_9:
	    default:
                eErr = HAL_ERR_PARAMETER;
                break;
        }
    }

    return eErr;
}

static __inline void WT_SetWkupSrc(bool bEnable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    SET_SCU_WT_WKUP_EN(ptScu, bEnable);
}

static __inline void WT_GetWkupEvent(bool *bEvent)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    uint8_t un8Prev = GET_SCU_WT_PREVMODE(ptScu);

    if(GET_SCU_WT_WKUP_EN(ptScu))
    {
        if(un8Prev == 0x01 || un8Prev == 0x02)
        {
            *bEvent = GET_SCU_WT_WKUP_FLAG(ptScu);
        }
    }
}

#if defined(WT_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void PRV_WT_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, (uint8_t)eIrq, bEnable);
}
#endif

#endif /* _HAL_WT_F1X_H_ */
