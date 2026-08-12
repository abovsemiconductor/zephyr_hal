/**
 *******************************************************************************
 * @file        hal_cmp_v_01_00_01.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.01 typed CMP
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_CMP_V_01_00_01_H_
#define _HAL_CMP_V_01_00_01_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#define CMP_REG_BASE                                  CMP_BASE
#define CMP_REG_OFFSET                                0x100
#define CMP_CR_REG_OFFSET                             0x04
#define CMP_HYSS_ENABLE(x)                            (x == 0 ? 0 : 1)
#define CMP_HYSS_MODE(x)                              (x > 2 ? 1 : 0)
#define CMP_INTR_ASSERTED_C0                          (1UL << 0)
#define CMP_INTR_ASSERTED_C1                          (1UL << 1)

/* Bit/Register Macro */
#define SET_CMP_CR_INPUT(Peri,Id,Data)                SET_BIT_ADDR_OFFSET(Peri,(Id*CMP_CR_REG_OFFSET),Data,CMP,CMP0CR,C0INPSEL)
#define SET_CMP_CR_REF(Peri,Id,Data)                  SET_BIT_ADDR_OFFSET(Peri,(Id*CMP_CR_REG_OFFSET),Data,CMP,CMP0CR,C0INNSEL)
#define SET_CMP_CR_INTR_TRG(Peri,Id,Data)             SET_BIT_OFFSET(Peri,(Id*2),Data,CMP,ICON,C0IMODE)
#define SET_CMP_DR_DBNC_SHIFT(Peri,Id,Data)           SET_BIT_OFFSET(Peri,(Id*4),Data,CMP,DBNC,C0DBNC)
#define GET_CMP_DR_DBNC_SHIFT(Peri,Id)                GET_BIT_OFFSET(Peri,(Id*4),CMP,DBNC,C0DBNC)
#define SET_CMP_CR_EN(Peri,Id,Data)                   SET_BIT_ADDR_OFFSET(Peri,(Id*CMP_CR_REG_OFFSET),Data,CMP,CMP0CR,C0EN)
#define SET_CMP_CR_HYSS_EN(Peri,Id,Data)              SET_BIT_ADDR_OFFSET(Peri,(Id*CMP_CR_REG_OFFSET),Data,CMP,CMP0CR,C0HYSEN)
#define SET_CMP_CR_HYSS_MODE(Peri,Id,Data)            SET_BIT_ADDR_OFFSET(Peri,(Id*CMP_CR_REG_OFFSET),Data,CMP,CMP0CR,C0HYSSEL)
#define SET_CMP_CR_HYSS(Peri,Id,Data) \
                                                      SET_CMP_CR_HYSS_EN(Peri,Id,CMP_HYSS_ENABLE(Data)); \
                                                      SET_CMP_CR_HYSS_MODE(Peri,Id,CMP_HYSS_MODE(Data))
#define SET_CMP_CR_INTR_POL(Peri,Id,Data)             SET_BIT_OFFSET(Peri,(Id*1),Data,CMP,ICON,C0IPOL)
#define SET_CMP_CR_TRG_POL(Peri,Id,Data)              SET_BIT_OFFSET(Peri,(Id*1),Data,CMP,ICON,C0TPOL)
#define SET_CMP_DR_DBNC_CLK_DIV(Peri,Data)            SET_BIT(Peri,Data,CMP,DBNC,DBNCTB)

/* Interrupt Macro */
#define GET_CMP_IER_FLAG(Peri,Id)                     GET_BIT_OFFSET(Peri,(Id*1),CMP,IST,C0IRQ)
#define SET_CMP_IER_FLAG_CLR(Peri,Id,Data)            SET_BIT_OFFSET(Peri,(Id*1),Data,CMP,ICLR,C0ICLR)
#define SET_CMP_IER_EN(Peri,Id,Data)                  SET_BIT_OFFSET(Peri,(Id*1),Data,CMP,IEN,C0IEN)
#define GET_CMP_IER(Peri)                             GET_REG(Peri,IST)

/* Unused Macro */
#define SET_CMP_CR_WINDOW_EN(Peri,Data)               (void)Peri
#define SET_CMP_CR_INTREF_EN(Peri,Data)               (void)Peri
#define SET_CMP_CR_DBNC_CLK(Peri,Data)                (void)Peri
#define SET_CMP_CR_PWR(Peri,Id,Data)                  (void)Peri

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_CMP_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,0,Data,SCU,PER2,CMP)
#define SET_SCU_CMP_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,0,Data,SCU,PCER2,CMP)

#endif /* _HAL_CMP_V_01_00_01_H_ */
