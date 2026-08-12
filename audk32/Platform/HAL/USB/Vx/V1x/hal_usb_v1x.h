/**
 *******************************************************************************
 * @file        hal_usb_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed USB
 *
 * Copyright 2026 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_USB_V1X_H_
#define _HAL_USB_V1X_H_

/* Configuration Define from config_xxx.h */
#define USB_CH_NUM                                    CONFIG_USB_MAX_COUNT

#if (CONFIG_USB_VER_EXT == 0)

#if (CONFIG_USB_VER_MINOR == 0)
#include "hal_usb_v_01_00_00.h"
#elif (CONFIG_USB_VER_MINOR == 1)
#include "hal_usb_v_01_00_01.h"
#elif (CONFIG_USB_VER_MINOR == 2)
#include "hal_usb_v_01_00_02.h"
#else
#error "define CONFIG_USB_VER_MINOR of V-type USB at config_xxx.h"
#endif

#else
#error "define CONFIG_USB_VER_EXT of V-type USB at config_xxx.h"
#endif

static __inline USB_Type *USB_GetReg(P_USB_ID_e eId)
{
    return (USB_Type *)(USB_REG_BASE + (USB_REG_OFFSET * (uint32_t)eId));
}

static __inline HAL_ERR_e USB_SetScuEnable(P_USB_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= CONFIG_USB_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_USB_PER(ptScu, (uint32_t)eId, un32Enable);
    //SET_SCU_USB_PCER(ptScu, (uint32_t)eId, un32Enable);

    return eErr;
}

static __inline IRQn_Type USB_GetIRQNum(P_USB_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(USB_0_IRQ)
        case P_USB_ID_0:
            eIrq = USB_0_IRQ;
            break;
#endif
#if defined(USB_1_IRQ)
        case P_USB_ID_1:
            eIrq = USB_1_IRQ;
            break;
#endif
#if defined(USB_2_IRQ)
        case P_USB_ID_2:
            eIrq = USB_2_IRQ;
            break;
#endif
#if defined(USB_3_IRQ)
        case P_USB_ID_3:
            eIrq = USB_3_IRQ;
            break;
#endif
#if defined(USB_4_IRQ)
        case P_USB_ID_4:
            eIrq = USB_4_IRQ;
            break;
#endif
#if defined(USB_5_IRQ)
        case P_USB_ID_5:
            eIrq = USB_5_IRQ;
            break;
#endif
#if defined(USB_6_IRQ)
        case P_USB_ID_6:
            eIrq = USB_6_IRQ;
            break;
#endif
#if defined(USB_7_IRQ)
        case P_USB_ID_7:
            eIrq = USB_7_IRQ;
            break;
#endif
#if defined(USB_8_IRQ)
        case P_USB_ID_8:
            eIrq = USB_8_IRQ;
            break;
#endif
#if defined(USB_9_IRQ)
        case P_USB_ID_9:
            eIrq = USB_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline HAL_ERR_e USB_SetClk(P_USB_ID_e eId, P_USB_CLK_e eClk, P_USB_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    USB_Type *ptUsb = USB_GetReg(eId);

#if defined(USB_FEATURE_POWER_ENABLE)
    ptScu->VUSB33CR = 0xA3690011;
#endif

    if(eClk == P_USB_CLK_MCCR)
    {
	switch(eId)
	{
#if (CONFIG_USB_MAX_COUNT > 0)
	    case P_USB_ID_0:
	        SET_SCU_USB_MCCR_SEL0(ptScu, SCU_USB_MCCR_MODE(eMccr));
	        SET_SCU_USB_MCCR_DIV0(ptScu, un8MccrDiv);
	        break;
#endif
#if (CONFIG_USB_MAX_COUNT > 1)
	    case P_USB_ID_1:
	        SET_SCU_USB_MCCR_SEL1(ptScu, SCU_USB_MCCR_MODE(eMccr));
	        SET_SCU_USB_MCCR_DIV1(ptScu, un8MccrDiv);
	        break;
#endif
	    case P_USB_ID_2:
	    case P_USB_ID_3:
	    case P_USB_ID_4:
	    case P_USB_ID_5:
	    case P_USB_ID_6:
	    case P_USB_ID_7:
	    case P_USB_ID_8:
	    case P_USB_ID_9:
	    default:
                eErr = HAL_ERR_PARAMETER;
	        break;
        }
    }

    SET_SCU_USB_PCER(ptScu, (uint32_t)eId, true);
		
    return eErr;
}

static __inline void USB_SetResetEnable(uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    SET_SCU_USB_RST_CLR(ptScu, true);
    SET_SCU_USB_RST_EN(ptScu, un32Enable);
}

static __inline void USB_SetWkupSrc(bool bEnable)
{
    (void)bEnable;
}

static __inline void USB_GetWkupEvent(bool *bEvent)
{
    (void)*bEvent;
}

#if defined(USB_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void USB_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, (uint8_t)eIrq, bEnable);
}
#endif

#endif /* _HAL_USB_V1X_H_ */
