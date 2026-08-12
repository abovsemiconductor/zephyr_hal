/**
 *******************************************************************************
 * @file        hal_lcd_f_01_00_01.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.01 typed LCD
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_LCD_F_01_00_01_H_
#define _HAL_LCD_F_01_00_01_H_

/* Feature(Function) Configuration Define */
#define LCD_FEATURE_EXT_BIAS

/* Internal Macro */
#define LCD_REG_BASE                                  LCD_BASE
#define LCD_UNUSE_SEG_CH_NUM                          CONFIG_LCD_UNUSE_SEG_CH_NUM
#define LCD_UNUSE_SEG_CH_0                            CONFIG_LCD_UNUSE_SEG_CH_0
#define LCD_UNUSE_SEG_CH_1                            CONFIG_LCD_UNUSE_SEG_CH_1

/* Bit/Register Macro */
#define SET_LCD_CR_DISPLAY(Peri,Data)                 SET_BIT(Peri,Data,LCD,CR,DISP)
#define SET_LCD_CR_INTBIASR(Peri,Data)                SET_BIT(Peri,Data,LCD,CR,IRSEL)
#define SET_LCD_CR_LCLKDIV(Peri,Data)                 SET_BIT(Peri,Data,LCD,CR,LCLK)
#define SET_LCD_CR_DUTYBIAS(Peri,Data)                SET_BIT(Peri,Data,LCD,CR,DBS)
#define SET_LCD_BCCR_AUTOBIAS(Peri,Data)              SET_BIT(Peri,Data,LCD,BCCR,LCDABC)
#define SET_LCD_BCCR_CONTRAST(Peri,Data)              SET_BIT(Peri,Data,LCD,BCCR,LCTEN)
#define SET_LCD_BCCR_VLC0VOLT(Peri,Data)              SET_BIT(Peri,Data,LCD,BCCR,VLCD)
#define SET_LCD_BCCR_BMASEL(Peri,Data)                SET_BIT(Peri,Data,LCD,BCCR,BMSEL)
#define SET_LCD_BSSR_DRVBIAS(Peri,Data)               SET_BIT(Peri,Data,LCD,BSSR,LCDDR)
#define SET_LCD_BSSR_EXTBIASEN(Peri,Data)             SET_BIT(Peri,Data,LCD,BSSR,VLE_EN)
#define SET_LCD_BSSR_EXTPATH(Peri,Data)               SET_BIT(Peri,Data,LCD,BSSR,LCDEPEN)
#define SET_LCD_BSSR_VLC3EN(Peri,Data)                SET_BIT(Peri,Data,LCD,BSSR,VLC3EN)
#define SET_LCD_BSSR_VLC2EN(Peri,Data)                SET_BIT(Peri,Data,LCD,BSSR,VLC2EN)
#define SET_LCD_BSSR_VLC1EN(Peri,Data)                SET_BIT(Peri,Data,LCD,BSSR,VLC1EN)
#define SET_LCD_BSSR_VLC0EN(Peri,Data)                SET_BIT(Peri,Data,LCD,BSSR,VLC0EN)
#define GET_LCD_DATA_BASE_ADDR(Peri)                  GET_REG_ADDR(Peri,LCDDR0)

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SCU_MCCR_MODE(x)                              (x == 0 ? x : x + 2)
#define SET_SCU_LCD_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PER2,LCD)
#define SET_SCU_LCD_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PCER2,LCD)
#define SET_SCU_LCD_PPCLKSR(Peri,Data)                SET_BIT(Peri,Data,SCU,PPCLKSR,LCDCLK)
#define SET_SCU_LCD_MCCR_SEL(Peri,Data)               SET_BIT(Peri,Data,SCU,MCCR5,LCDCSEL)
#define SET_SCU_LCD_MCCR_DIV(Peri,Data)               SET_BIT(Peri,Data,SCU,MCCR5,LCDDIV)

#endif /* _HAL_LCD_F_01_00_01_H_ */
