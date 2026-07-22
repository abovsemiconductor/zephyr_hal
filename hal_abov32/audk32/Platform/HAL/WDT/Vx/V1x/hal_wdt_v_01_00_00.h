/**
 *******************************************************************************
 * @file        hal_wdt_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed WDT
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_WDT_V_01_00_00_H_
#define _HAL_WDT_V_01_00_00_H_

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
#define SET_WDT_CR_RST_EN(Peri,Data)                  SET_BIT(Peri,Data,WDT,CON,WDTRE)
#define SET_WDT_CR_CNT_EN(Peri,Data)                  SET_BIT(Peri,Data,WDT,CON,WDTEN)
#define SET_WDT_CR_CLK_SEL(Peri,Data)                 SET_BIT(Peri,Data,WDT,CON,CKSEL)
#define SET_WDT_CR_CLK_PREDIV(Peri,Data)              SET_BIT(Peri,Data,WDT,CON,WPRS)
#if (CONFIG_WDT_REG_NAME == 1)
#define SET_WDT_DR_LOAD(Peri,Data)                    SET_BIT(Peri,Data,WDT,LR,LR)
#define GET_WDT_DR_CNT(Peri)                          GET_BIT(Peri,WDT,CNT,CNT)
#else
#define SET_WDT_DR_LOAD(Peri,Data)                    SET_BIT(Peri,Data,WDT,LR,WDTLR)
#define GET_WDT_DR_CNT(Peri)                          GET_BIT(Peri,WDT,CNT,WDTCNT)
#endif
#define SET_WDT_DR_RELOAD(Peri,Data) \
                                                      SET_WDT_ACCESS_KEY(Peri,WDT_WRITE_ACCESS_EN); \
                                                      SET_WDT_DR_LOAD(Peri,Data); \
                                                      SET_WDT_ACCESS_KEY(Peri,WDT_WRITE_ACCESS_DIS); \
                                                      SET_WDT_ACCESS_KEY(Peri,WDT_RELOAD_BITS)
#define SET_WDT_ACCESS_EN(Peri,Data)                  SET_BIT(Peri,Data,WDT,AEN,ENS)
#define SET_WDT_ACCESS_KEY(Peri,Data)                 SET_BIT(Peri,Data,WDT,AEN,AEN)

/* Interrupt Macro */
#define SET_WDT_IER_UDF_EN(Peri,Data)                 SET_BIT(Peri,Data,WDT,CON,WDTIE)
#define SET_WDT_IER_UDF_FLAG(Peri,Data)               SET_WDT_DR_LOAD(Peri,0xFFFFFFFF)
#define GET_WDT_IER_MATCH_FLAG(Peri)                  0
#define GET_WDT_IER_UDF_FLAG(Peri)                    GET_BIT(Peri,WDT,CON,WUF)

/* Unused Macro */
#define SET_WDT_DR_MATCH(Peri,Data)                   (void)Peri
#define GET_WDT_DR_MATCH(Peri)                        0
#define SET_WDT_IER_MATCH_EN(Peri,Data)               (void)Peri
#define SET_WDT_IER_MATCH_FLAG(Peri,Data)             (void)Peri

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SCU_WDT_MCCR_MODE(x)                          (x == 0 ? x : x + 2)
#define SET_SCU_WDT_MCCR_SEL0(Peri,Data)              SET_BIT(Peri,Data,SCU,MCCR1,WDTCSEL)
#define SET_SCU_WDT_MCCR_DIV0(Peri,Data)              SET_BIT(Peri,Data,SCU,MCCR1,WDTCDIV)
#define SET_SCU_WDT_RST_CLR(Peri,Data)                SET_BIT(Peri,Data,SCU,RSSR,WDTRST)
#define SET_SCU_WDT_RST_EN(Peri,Data)                 SET_BIT(Peri,Data,SCU,RSER,WDTRST)

#endif /* _HAL_WDT_V_01_00_00_H_ */
