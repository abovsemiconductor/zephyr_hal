/**
 *******************************************************************************
 * @file        hal_wdt_v_01_00_01.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.01 typed WDT
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_WDT_V_01_00_01_H_
#define _HAL_WDT_V_01_00_01_H_

/* Feature(Function) Configuration Define */
#define WDT_FEATURE_USE_MCCR_CLOCK
#define WDT_FEATURE_NMI

/* Internal Macro */
#define WDT_REG_BASE                                  WDT_BASE
#define WDT_REG_OFFSET                                0x100
#define WDT_CNT_STOP                                  0x00
#define WDT_RST_STOP                                  0x00
#define WDT_CLK_MODE(x)                               (x == 1 ? x : 0)
#define WDT_CLK_PREDIV_MODE(x)                        (x)
#define WDT_WRITE_ACCESS_EN                           0xA55A
#define WDT_WRITE_ACCESS_DIS                          0
#define WDT_RELOAD_BITS                               0x555A

/* Bit/Register Macro */
#define SET_WDT_CR_RST_EN(Peri,Data)                  SET_BIT(Peri,Data,WDT,CON,WRE)
#define SET_WDT_CR_CNT_EN(Peri,Data)                  SET_BIT(Peri,Data,WDT,CON,WEN)
#define SET_WDT_CR_CLK_SEL(Peri,Data)                 SET_BIT(Peri,Data,WDT,CON,WEC)
#define SET_WDT_CR_CLK_PREDIV(Peri,Data)              SET_BIT(Peri,Data,WDT,CON,WPRS)
#define SET_WDT_DR_LOAD(Peri,Data)                    SET_REG(Peri,Data,LR)
#define GET_WDT_DR_CNT(Peri)                          GET_REG(Peri,CVR)
#define SET_WDT_DR_RELOAD(Peri,Data)                  (void)Peri

/* Interrupt Macro */
#define SET_WDT_IER_UDF_EN(Peri,Data)                 SET_BIT(Peri,Data,WDT,CON,WIE)
#define SET_WDT_IER_UDF_FLAG(Peri,Data)               SET_WDT_DR_LOAD(Peri,0xFFFFFFFF)
#define GET_WDT_IER_MATCH_FLAG(Peri)                  0
#define GET_WDT_IER_UDF_FLAG(Peri)                    GET_BIT(Peri,WDT,CON,WOF)

/* Unused Macro */
#define SET_WDT_IER_MATCH_EN(Peri,Data)               (void)Peri
#define SET_WDT_IER_MATCH_FLAG(Peri,Data)             (void)Peri
#define SET_WDT_DR_MATCH(Peri,Data)                   (void)Peri
#define GET_WDT_DR_MATCH(Peri)                        0
#define SET_WDT_ACCESS_EN(Peri,Data)                  (void)Peri
#define SET_WDT_ACCESS_KEY(Peri,Data)                 (void)Peri

/* SCU Macro */
typedef PMU_Type                                      SCU_Type;
#define SCU_ADDR                                      PMU_BASE
#define SCU_WDT_MCCR_MODE(x)                          (x == 4 ? 0x00 : x == 3 ? 0x01 : x == 1 ? 0x02 : x == 0 ? 0x03 : 0x00)
#define SET_SCU_WDT_MCCR_SEL0(Peri,Data)              SET_BIT(Peri,Data,PMU,PCSR,WDTCS)
#define SET_SCU_WDT_MCCR_DIV0(Peri,Data)              (void)Peri
#define SET_SCU_WDT_RST_CLR(Peri,Data)                SET_BIT(Peri,Data,PMU,RSSR,WDTRST)
#define SET_SCU_WDT_RST_EN(Peri,Data)                 SET_BIT(Peri,Data,PMU,RSER,WDTRSTE)

#endif /* _HAL_WDT_V_01_00_01_H_ */
