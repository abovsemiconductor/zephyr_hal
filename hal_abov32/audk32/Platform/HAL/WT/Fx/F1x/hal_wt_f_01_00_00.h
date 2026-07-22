/**
 *******************************************************************************
 * @file        hal_wt_f_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed WT
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_WT_F_01_00_00_H_
#define _HAL_WT_F_01_00_00_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#define WT_REG_OFFSET                                 0x100
#define WT_CH_NUM                                     CONFIG_WT_MAX_COUNT

/* Bit/Register Macro */
#define SET_WT_CR_EN(Peri,Data)                       SET_BIT(Peri,Data,WT,CR,WTEN)
#define SET_WT_CR_INTV(Peri,Data)                     SET_BIT(Peri,Data,WT,CR,WTINTV)
#define SET_WT_DR_MATCH_CNT(Peri,Data)                SET_BIT(Peri,Data,WT,DR,WTDATA)

/* Interrupt Macro */
#define SET_WT_IER_EN(Peri,Data)                      SET_BIT(Peri,Data,WT,CR,WTIEN)
#define SET_WT_IER_CLR(Peri,Data)                     SET_BIT(Peri,Data,WT,CR,WTCLR)
#define SET_WT_IER_FLAG(Peri,Data)                    SET_BIT(Peri,Data,WT,CR,WTIFLAG)
#define GET_WT_IER_FLAG(Peri)                         GET_BIT(Peri,WT,CR,WTIFLAG)

/* SCU Macro */
#define SCU_ADDR SCU_BASE
#define SCU_WT_MCCR_MODE(x)                           (x == 0 ? x : x + 2)
#define SET_SCU_WT_PER0(Peri,Data)                    SET_BIT(Peri,Data,SCU,PER1,WT)
#define SET_SCU_WT_PCER0(Peri,Data)                   SET_BIT(Peri,Data,SCU,PCER1,WT)
#define SET_SCU_WT_MCCR_SEL0(Peri,Data)               SET_BIT(Peri,Data,SCU,MCCR3,WTEXTCSEL)
#define SET_SCU_WT_MCCR_DIV0(Peri,Data)               SET_BIT(Peri,Data,SCU,MCCR3,WTEXTCDIV)
#define SET_SCU_WT_PPCLKSR_CLK(Peri,Data)             SET_BIT(Peri,Data,SCU,PPCLKSR,WTCLK)
#define SET_SCU_WT_WKUP_EN(Peri,Data)                 SET_BIT(Peri,Data,SCU,WUER,WTWUE)
#define GET_SCU_WT_WKUP_EN(Peri)                      GET_BIT(Peri,SCU,WUER,WTWUE)
#define GET_SCU_WT_WKUP_FLAG(Peri)                    GET_BIT(Peri,SCU,WUSR,WTWU)
#define GET_SCU_WT_PREVMODE(Peri)                     GET_BIT(Peri,SCU,SMR,PREVMODE)

#endif /* _HAL_WT_F_01_00_00_H_ */
