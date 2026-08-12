/**
 *******************************************************************************
 * @file        hal_cmp_v_02_00_01.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 02.00.01 typed CMP
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_CMP_V_02_00_01_H_
#define _HAL_CMP_V_02_00_01_H_

/* Feature(Function) Configuration Define */
#define CMP_FEATURE_POST_ENABLE_INTERRUPT

/* Internal Macro */
#define CMP_REG_BASE                                  CMP_BASE
#define CMP_REG_OFFSET                                0x10
#define CMP_CR_REG_OFFSET                             0x04
#define CMP_HYSS_ENABLE(x)                            (x == 0 ? 0 : 1)
#define CMP_HYSS_MODE(x)                              (x > 0 ? x-1 : 0)
#define CMP_INTR_ASSERTED_C0                          (1UL << 8)
#define CMP_INTR_ASSERTED_C1                          (1UL << 1)
#define CMP_TRG_MODE(x)                               (x == 0 ? 1 : \
                                                      (x == 1 || x == 2 ? 2 : \
                                                      (x == 4 ? 0 : x )))
#define CMP_TRG_POL(x,y)                              (x == 0 ? y : \
                                                      (x == 1 ? 1 : \
                                                      (x == 2 ? 0 : y )))
/* Bit/Register Macro */
#define SET_CMP_CR_INPUT(Peri,Id,Data)                SET_BIT(Peri,Data,CMP,CMP0_CONF,CINPSEL)
#define SET_CMP_CR_REF(Peri,Id,Data)                  SET_BIT(Peri,Data,CMP,CMP0_CONF,CINNSEL)

#define SET_CMP_CR_EN(Peri,Id,Data)                   SET_BIT(Peri,Data,CMP,CMP0_CTRL,CMPEN)
#define SET_CMP_CR_HYSS_EN(Peri,Id,Data)              SET_BIT(Peri,Data,CMP,CMP0_CONF,HYSEN)
#define SET_CMP_CR_HYSS_MODE(Peri,Id,Data)            SET_BIT(Peri,Data,CMP,CMP0_CONF,HYSSEL)
#define SET_CMP_CR_HYSS(Peri,Id,Data) \
                                                      SET_CMP_CR_HYSS_EN(Peri,Id,CMP_HYSS_ENABLE(Data)); \
                                                      SET_CMP_CR_HYSS_MODE(Peri,Id,CMP_HYSS_MODE(Data))

#define SET_CMP_CR_INTR_TYPE(Peri,Id,Data)            SET_BIT(Peri,Data,CMP,CMP0_CONF,INTTYPE)
#define SET_CMP_CR_INTR_POLA(Peri,Id,Data)            SET_BIT(Peri,Data,CMP,CMP0_CONF,INTPOL)
#define SET_CMP_CR_INTR_TRG(Peri,Id,Data1,Data2) \
                                                      SET_CMP_CR_INTR_TYPE(Peri,Id,CMP_TRG_MODE(Data1)); \
                                                      SET_CMP_CR_INTR_POLA(Peri,Id,CMP_TRG_POL(Data1,Data2))

#define SET_CMP_DR_DBNC_SHIFT(Peri,Id,Data)           SET_BIT(Peri,Data,CMP,CMP0_CONF,FLTSEL)
#define GET_CMP_DR_DBNC_SHIFT(Peri,Id)                GET_BIT(Peri,CMP,CMP0_CONF,FLTSEL)

/* Interrupt Macro */
#define GET_CMP_IER_FLAG(Peri,Id)                     GET_BIT(Peri,CMP,CMP0_STAT,CMPINTF)
#define SET_CMP_IER_FLAG_CLR(Peri,Id,Data)            SET_BIT(Peri,Data,CMP,CMP0_STAT,CMPINTF)
#define SET_CMP_IER_EN(Peri,Id,Data)                  SET_BIT(Peri,Data,CMP,CMP0_CTRL,CMPINTEN)
#define GET_CMP_IER(Peri,Id)                          GET_REG(Peri,CMP0_STAT)

/* Unused Macro */
#define SET_CMP_CR_WINDOW_EN(Peri,Data)               (void)Peri
#define SET_CMP_CR_INTREF_EN(Peri,Data)               (void)Peri
#define SET_CMP_CR_DBNC_CLK(Peri,Data)                (void)Peri
#define SET_CMP_CR_PWR(Peri,Id,Data)                  (void)Peri
#define SET_CMP_DR_DBNC_CLK_DIV(Peri,Data)            (void)Peri
#define SET_CMP_CR_INTR_POL(Peri,Id,Data)             (void)Peri
#define SET_CMP_CR_TRG_POL(Peri,Id,Data)              (void)Peri

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_CMP_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,0,Data,SCU,PER2,CMP)
#define SET_SCU_CMP_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,0,Data,SCU,PCER2,CMP)

#endif /* _HAL_CMP_V_02_00_01_H_ */
