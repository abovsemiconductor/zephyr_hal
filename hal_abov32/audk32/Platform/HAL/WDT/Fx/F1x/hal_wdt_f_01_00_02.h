/**
 *******************************************************************************
 * @file        hal_wdt_f_01_00_02.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.02 typed WDT
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_WDT_F_01_00_02_H_
#define _HAL_WDT_F_01_00_02_H_

/* Feature(Function) Configuration Define */
#define WDT_FEATURE_USE_PCLK
#define WDT_FEATURE_IRQ_UNMASK_ENABLE
#define WDT_FEATURE_RELOAD_COUNT_WITH_WINDR

/* Internal Macro */
#define WDT_REG_BASE                                  WDT_BASE
#define WDT_REG_OFFSET                                0x100
#define WDT_CNT_STOP                                  0x1A
#define WDT_RST_STOP                                  0x25
#define WDT_CLK_PREDIV_MODE(x)                        (x >> 1)
#define WDT_WRITE_ACCESS_EN                           0
#define WDT_WRITE_ACCESS_DIS                          0
#define WDT_WRITE_IDENT_KEY                           0x5A69
#define WDT_RELOAD_BITS                               0x6A
#define WDT_PPCLKSR(x)                                (x > 0 ? 1 : 0)

/* Bit/Register Macro */
#define SET_WDT_CR_RST_EN(Peri,Data)                  SET_BIT_KEY(Peri,WDT_WRITE_IDENT_KEY,Data,WDT,CR,RSTEN)
#define SET_WDT_CR_CNT_EN(Peri,Data)                  SET_BIT_KEY(Peri,WDT_WRITE_IDENT_KEY,Data,WDT,CR,CNTEN)
#define SET_WDT_CR_CLK_PREDIV(Peri,Data)              SET_BIT_KEY(Peri,WDT_WRITE_IDENT_KEY,Data,WDT,CR,CLKDIV)
#define SET_WDT_DR_RELOAD(Peri,Data)                  SET_BIT(Peri,WDT_RELOAD_BITS,WDT,CNTR,CNTR)
#define SET_WDT_DR_LOAD(Peri,Data)                    SET_BIT(Peri,Data,WDT,DR,DATA)
#define SET_WDT_DR_MATCH(Peri,Data)                   SET_BIT(Peri,Data,WDT,WINDR,WDATA)
#define GET_WDT_DR_MATCH(Peri)                        GET_BIT(Peri,WDT,WINDR,WDATA)
#define GET_WDT_DR_CNT(Peri)                          GET_BIT(Peri,WDT,CNT,CNT)

/* Interrupt Macro */
#define SET_WDT_IER_MATCH_EN(Peri,Data)               SET_BIT_KEY(Peri,WDT_WRITE_IDENT_KEY,Data,WDT,CR,WINMIEN)
#define SET_WDT_IER_UDF_EN(Peri,Data)                 SET_BIT_KEY(Peri,WDT_WRITE_IDENT_KEY,Data,WDT,CR,UNFIEN)
#define SET_WDT_IER_MATCH_FLAG(Peri,Data)             SET_BIT(Peri,Data,WDT,SR,WINMIFLAG)
#define GET_WDT_IER_MATCH_FLAG(Peri)                  GET_BIT(Peri,WDT,SR,WINMIFLAG)
#define SET_WDT_IER_UDF_FLAG(Peri,Data)               SET_BIT(Peri,Data,WDT,SR,UNFIFLAG)
#define GET_WDT_IER_UDF_FLAG(Peri)                    GET_BIT(Peri,WDT,SR,UNFIFLAG)

#define SET_WDT_ACCESS_EN(Peri,Data)                  (void)Peri
#define SET_WDT_ACCESS_KEY(Peri,Data)                 (void)Peri

/* SCU Macro */
typedef SCUCG_Type                                    SCU_Type;
#define SCU_ADDR                                      SCUCG_BASE
#define SCU_WDT_MCCR_MODE(x)                          (x) 
#define SET_SCU_WDT_PER0(Peri,Data)                   (void)Peri
#define SET_SCU_WDT_PCER0(Peri,Data)                  SET_BIT(Peri,Data,SCUCG,PPCLKEN2,WDTCLKE)
#define SET_SCU_WDT_PPCLKSR_CLK(Peri,Data)            SET_BIT(Peri,Data,SCUCG,PPCLKSR,WDTCLK)
#define SET_INTC_IRQ_UNMASK_EN(Peri,Irq,Data)         SET_BIT_ID(Peri,Irq,Data,INTC,MSK,IMSK0_LVI_ECCC)

#define SET_SCU_WDT_MCCR_SEL0(Peri,Data)              (void)Peri
#define SET_SCU_WDT_MCCR_DIV0(Peri,Data)              (void)Peri
#define SET_SCU_WDT_RST_CLR(Peri,Data)                (void)Peri
#define SET_SCU_WDT_RST_EN(Peri,Data)                 (void)Peri
#define SET_SCU_WDT_WKUP_EN(Peri,Data)                (void)Peri
#define GET_SCU_WDT_WKUP_EN(Peri)                     0
#define GET_SCU_WDT_WKUP_FLAG(Peri)                   0
#define GET_SCU_WDT_PREVMODE(Peri)                    0; (void)Peri

#endif /* _HAL_WDT_F_01_00_02_H_ */
