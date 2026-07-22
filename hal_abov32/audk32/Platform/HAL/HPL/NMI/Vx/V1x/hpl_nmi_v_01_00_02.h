/**
 *******************************************************************************
 * @file        hpl_nmi_v_01_00_02.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.02 typed SCU NMI 
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HPL_NMI_V_01_00_02_H_
#define _HPL_NMI_V_01_00_02_H_

/* Feature(Function) Configuration Define */
#define SCUNMI_FEATURE_TIMER3_BLNK
#define SCUNMI_FEATURE_CMP
#define SCUNMI_FEATURE_FLASH_SWAP

/* Internal Define */
#define SCU_REG_BASE                                  SCU_BASE

/* Bit/Register Macro */
#define SET_SCU_NMI_LVD_IER_EN(Peri,Data)             SET_BIT_KEY_BITNAME(Peri,0xA32C,ACCESSCODE,Data,SCU,NMIR,LVDEN)
#define SET_SCU_NMI_MCLK_IER_EN(Peri,Data)            SET_BIT_KEY_BITNAME(Peri,0xA32C,ACCESSCODE,Data,SCU,NMIR,MCLKFAILEN)
#define SET_SCU_NMI_WDT_IER_EN(Peri,Data)             SET_BIT_KEY_BITNAME(Peri,0xA32C,ACCESSCODE,Data,SCU,NMIR,WDTINTEN)
#define GET_SCU_NMI_MCLK_IER_FLAG(Peri)               GET_BIT(Peri,SCU,NMIR,MCLKFAILSTS)
#define GET_SCU_NMI_WDT_IER_FLAG(Peri)                GET_BIT(Peri,SCU,NMIR,WDTINTSTS)
#define GET_SCU_NMI_STATUS(Peri)                      GET_REG(Peri,NMIR)
#define SET_SCU_NMI_TIMER3_BLNK_IER_EN(Peri,Data)     SET_BIT_KEY_BITNAME(Peri,0xA32C,ACCESSCODE,Data,SCU,NMIR,T30IEN)
#define SET_SCU_NMI_CMP_IER_EN(Peri,Data)             SET_BIT_KEY_BITNAME(Peri,0xA32C,ACCESSCODE,Data,SCU,NMIR,CMPINTEN)
#define SET_SCU_NMI_FLASH_SWAP_IER_EN(Peri,Data)      SET_BIT_KEY_BITNAME(Peri,0xA32C,ACCESSCODE,Data,SCU,NMIR,SWAPERRIEN)
#define GET_SCU_NMI_LVD_IER_FLAG(Peri)                GET_BIT(Peri,SCU,NMIR,LVRSTS)
#define GET_SCU_NMI_TIMER3_BLNK_IER_FLAG(Peri)        GET_BIT(Peri,SCU,NMIR,T30INTSTS)
#define GET_SCU_NMI_CMP_IER_FLAG(Peri)                GET_BIT(Peri,SCU,NMIR,CMPINTSTS)
#define GET_SCU_NMI_FLASH_SWAP_IER_FLAG(Peri)         GET_BIT(Peri,SCU,NMIR,SWAPFAILSTS)

#endif /* _HPL_NMI_V_01_00_02_H_ */
