/**
 *******************************************************************************
 * @file        hpl_nmi_v_02_00_05.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 02.00.05 typed SCU NMI 
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HPL_NMI_V_02_00_05_H_
#define _HPL_NMI_V_02_00_05_H_

/* Feature(Function) Configuration Define */
#define SCUNMI_FEATURE_CLEAR_STATUS

/* Internal Define */
#define SCU_REG_BASE                                  SCU_BASE
#define SCU_NMI_SR_WTIDKY                             0x8C000000
#define SCU_NMI_SRC_SR_BIT                            0x00008000

/* Bit/Register Macro */
#define SET_SCU_NMI_EN(Peri,Data)                     SET_BIT(Peri,Data,SCU,NMICR,NMIINEN)

#define SET_SCU_NMI_LVD_IER_EN(Peri,Data)             SET_BIT(Peri,Data,SCU,NMICR,LVIEN)
#define GET_SCU_NMI_LVD_IER_FLAG(Peri)                GET_BIT(Peri,SCU,NMISR,LVISTS)
#define SET_SCU_NMI_MCLK_IER_EN(Peri,Data)            SET_BIT(Peri,Data,SCU,NMICR,MCLKFAILEN)
#define SET_SCU_NMI_WDT_IER_EN(Peri,Data)             SET_BIT(Peri,Data,SCU,NMICR,WDTINTEN)
#define GET_SCU_NMI_MCLK_IER_FLAG(Peri)               GET_BIT(Peri,SCU,NMISR,MCLKFAILSTS)
#define GET_SCU_NMI_WDT_IER_FLAG(Peri)                GET_BIT(Peri,SCU,NMISR,WDTINTSTS)
#define SET_SCU_NMI_WDT_IER_FLAG(Peri,Data)           SET_BIT(Peri,Data,SCU,NMISR,WDTINTSTS)
#define GET_SCU_NMI_STATUS(Peri)                      GET_REG(Peri,NMISR)
#define SET_SCU_NMI_STATUS(Peri,Data)                 SET_REG(Peri,(Data|SCU_NMI_SR_WTIDKY),NMISR)

#define SET_SCU_NMI_SRC(Peri,Data)                    SET_BIT(Peri,Data,SCU,NMICR,NMISRC)

#endif /* _HPL_NMI_V_02_00_05_H_ */
