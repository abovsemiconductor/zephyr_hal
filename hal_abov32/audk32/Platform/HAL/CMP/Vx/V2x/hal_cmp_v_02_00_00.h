/**
 *******************************************************************************
 * @file        hal_cmp_v_02_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 02.00.00 typed CMP
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_CMP_V_02_00_00_H_
#define _HAL_CMP_V_02_00_00_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
typedef COMP_Type                                     CMP_Type;
#define CMP_REG_BASE                                  COMP0_BASE
#define CMP_REG_OFFSET                                0x0C
#define CMP_CR_REG_OFFSET                             0x04
#define CMP_HYSS_ENABLE(x)                            (x == 0 ? 0 : 1)
#define CMP_HYSS_MODE(x)                              (x > 2 ? 1 : 0)
#define CMP_INTR_ASSERTED_C0                          (1UL << 8)
#define CMP_INTR_ASSERTED_C1                          (1UL << 1)
#define CMP_TRG_MODE(x)                               (x == 0 ? 1 : \
                                                      (x == 1 || x == 2 ? 2 : \
                                                      (x == 4 ? 0 : x )))
#define CMP_TRG_POL(x,y)                              (x == 0 ? y : \
                                                      (x == 1 ? 1 : \
                                                      (x == 2 ? 0 : y )))
/* Bit/Register Macro */
#define SET_CMP_CR_INPUT(Peri,Id,Data)                SET_BIT(Peri,Data,COMP,CONF,CINPSEL)
#define SET_CMP_CR_REF(Peri,Id,Data)                  SET_BIT(Peri,Data,COMP,CONF,CINNSEL)

#define SET_CMP_CR_EN(Peri,Id,Data)                   SET_BIT(Peri,Data,COMP,CTRL,COMPEN)
#define SET_CMP_CR_HYSS_EN(Peri,Id,Data)              SET_BIT(Peri,Data,COMP,CONF,HYSEN)
#define SET_CMP_CR_HYSS_MODE(Peri,Id,Data)            SET_BIT(Peri,Data,COMP,CONF,HYSSEL)
#define SET_CMP_CR_HYSS(Peri,Id,Data) \
                                                      SET_CMP_CR_HYSS_EN(Peri,Id,CMP_HYSS_ENABLE(Data)); \
                                                      SET_CMP_CR_HYSS_MODE(Peri,Id,CMP_HYSS_MODE(Data))

#define SET_CMP_CR_INTR_TYPE(Peri,Data)               SET_BIT(Peri,Data,COMP,CONF,INTTYPE)
#define SET_CMP_CR_INTR_POLA(Peri,Data)               SET_BIT(Peri,Data,COMP,CONF,INTPOL)
#define SET_CMP_CR_INTR_TRG(Peri,Id,Data1,Data2) \
                                                      SET_CMP_CR_INTR_TYPE(Peri,CMP_TRG_MODE(Data1)); \
                                                      SET_CMP_CR_INTR_POLA(Peri,CMP_TRG_POL(Data1,Data2))

#define SET_CMP_DR_DBNC_SHIFT(Peri,Id,Data)           SET_BIT(Peri,Data,COMP,CONF,FLTSEL)
#define GET_CMP_DR_DBNC_SHIFT(Peri,Id)                GET_BIT(Peri,COMP,CONF,FLTSEL)

/* Interrupt Macro */
#define GET_CMP_IER_FLAG(Peri,Id)                     GET_BIT(Peri,COMP,STAT,COMPINTF)
#define SET_CMP_IER_FLAG_CLR(Peri,Id,Data)            SET_BIT(Peri,Data,COMP,STAT,COMPINTF)
#define SET_CMP_IER_EN(Peri,Id,Data)                  SET_BIT(Peri,Data,COMP,CTRL,COMPINTEN)
#define GET_CMP_IER(Peri,Id)                          GET_REG(Peri,STAT)

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
#define SET_SCU_CMP_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,0,Data,SCU,PER2,COMPARATOR)
#define SET_SCU_CMP_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,0,Data,SCU,PCER2,COMPARATOR)

#endif /* _HAL_CMP_V_02_00_00_H_ */
