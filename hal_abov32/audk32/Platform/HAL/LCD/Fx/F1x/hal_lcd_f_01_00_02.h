/**
 *******************************************************************************
 * @file        hal_lcd_f_01_00_02.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.02 typed LCD
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_LCD_F_01_00_02_H_
#define _HAL_LCD_F_01_00_02_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#define LCD_REG_BASE                                  LCD_BASE

/* Bit/Register Macro */
#define SET_LCD_CR_DISPLAY(Peri,Data)                 SET_BIT(Peri,Data,LCD,CR,DISP)
#define SET_LCD_CR_INTBIASR(Peri,Data)                SET_BIT(Peri,Data,LCD,CR,IRSEL)
#define SET_LCD_CR_LCLKDIV(Peri,Data)                 SET_BIT(Peri,Data,LCD,CR,LCLK)
#define SET_LCD_CR_DUTYBIAS(Peri,Data)                SET_BIT(Peri,Data,LCD,CR,DBS)
#define SET_LCD_BCCR_AUTOBIAS(Peri,Data)              SET_BIT(Peri,Data,LCD,BCCR,LCDABC)
#define SET_LCD_BCCR_CONTRAST(Peri,Data)              SET_BIT(Peri,Data,LCD,BCCR,LCTEN)
#define SET_LCD_BCCR_VLC0VOLT(Peri,Data)              SET_BIT(Peri,Data,LCD,BCCR,VLCD)
#define SET_LCD_BCCR_BMASEL(Peri,Data)                SET_BIT(Peri,Data,LCD,BCCR,BMSEL)
#define GET_LCD_DATA_BASE_ADDR(Peri)                  GET_REG_ADDR(Peri,DR0)

/* Unused Macro */
#define SET_LCD_BSSR_DRVBIAS(Peri,Data)               (void)Peri
#define SET_LCD_BSSR_EXTBIASEN(Peri,Data)             (void)Peri
#define SET_LCD_BSSR_EXTPATH(Peri,Data)               (void)Peri
#define SET_LCD_BSSR_VLC3EN(Peri,Data)                (void)Peri
#define SET_LCD_BSSR_VLC2EN(Peri,Data)                (void)Peri
#define SET_LCD_BSSR_VLC1EN(Peri,Data)                (void)Peri
#define SET_LCD_BSSR_VLC0EN(Peri,Data)                (void)Peri

/* SCU Macro */
typedef SCUCG_Type                                    SCU_Type;
#define SCU_ADDR                                      SCUCG_BASE
#define SET_SCU_LCD_PER(Peri,Id,Data)                 (void)Peri
#define SET_SCU_LCD_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCUCG,PPCLKEN2,LCDCLKE)
#define SET_SCU_LCD_PPCLKSR(Peri,Data)                SET_BIT(Peri,Data,SCUCG,PPCLKSR,LCDCLK)
#define SET_SCU_LCD_MCCR_SEL(Peri,Data)               (void)Peri
#define SET_SCU_LCD_MCCR_DIV(Peri,Data)               SET_BIT(Peri,Data,SCUCG,SCDIVR1,WLDIV)

#endif /* _HAL_LCD_F_01_00_02_H_ */
