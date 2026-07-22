/**
 *******************************************************************************
 * @file        hal_cmp_f_01_00_01.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.01 typed CMP
 *
 * Copyright 2025 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_CMP_F_01_00_01_H_
#define _HAL_CMP_F_01_00_01_H_

/* Feature(Function) Configuration Define */
#define CMP_FEATURE_IRQ_UNMASK_ENABLE

/* Internal Macro */
typedef CMPn_Type                                     CMP_Type;
#define CMP_REG_BASE                                  CMP0_BASE
#define CMP_REG_OFFSET                                0x80
#define CMP_CR_REG_OFFSET                             0x04
#define CMP_HYSS_ENABLE(x)                            (x != 0 ? 1 : 0)
#define CMP_INTR_ASSERTED_C0                          (1UL << 0)
#define CMP_INTR_ASSERTED_C1                          (1UL << 1)
#define CMP_TRG_INTR_MODE(x)                          (x == 4 ? 0 : \
                                                      (x == 1 ? 2 : \
                                                      (x == 2 ? 1 : x \
                                                      )))

/* Bit/Register Macro */
#define SET_CMP_CR_EN(Peri,Id,Data)                   SET_BIT_ID(Peri,0,Data,CMPn,CR,CMPnEN)
#define SET_CMP_CR_HYSS(Peri,Id,Data)                 SET_BIT_ID(Peri,0,CMP_HYSS_ENABLE(Data),CMPn,CR,HYSnSEL)
#define SET_CMP_CR_INPUT(Peri,Id,Data)                SET_BIT_ID(Peri,0,Data,CMPn,CR,CMPnPOS)
#define SET_CMP_CR_REF(Peri,Id,Data)                  SET_BIT_ID(Peri,0,Data,CMPn,CR,CMPnNEG)
#define SET_CMP_CR_INTR_TRG(Peri,Id,Data)             SET_BIT_ID(Peri,0,CMP_TRG_INTR_MODE(Data),CMPn,CR,CMPnPOL)
#define SET_CMP_DR_DBNC_CLK_DIV(Peri,Data)            SET_BIT(Peri,Data,CMPn,CR,NFCKn)
#define SET_CMP_CR_INTREF_EN(Peri,Data)               SET_BIT(Peri,Data,CMPn,CR,REFnEN)
#define SET_CMP_CR_INTREF_VOL_LVL(Peri,Data)          (void)Peri//SET_BIT(Peri,Data,CMPn,RCR,CMPnREF)

/* Interrupt Macro */
#define GET_CMP_IER_FLAG(Peri,Id)                     GET_BIT_OFFSET(Peri,0,CMPn,SR,CMPnIFLAG)
#define SET_CMP_IER_FLAG_CLR(Peri,Id,Data)            SET_BIT_ID(Peri,0,Data,CMPn,SR,CMPnIFLAG)
#define GET_CMP_IER(Peri)                             GET_REG(Peri,SR)

/* Unused Macro */
#define SET_CMP_CR_WINDOW_EN(Peri,Data)               (void)Peri
#define SET_CMP_DR_DBNC_SHIFT(Peri,Id,Data)           (void)Peri
#define GET_CMP_DR_DBNC_SHIFT(Peri,Id)                (void)Peri
#define SET_CMP_CR_DBNC_CLK(Peri,Data)                (void)Peri
#define SET_CMP_CR_PWR(Peri,Id,Data)                  (void)Peri
#define SET_CMP_IER_EN(Peri,Id,Data)                  (void)Peri
#define SET_CMP_CR_INTR_POL(Peri,Id,Data)             (void)Peri
#define SET_CMP_CR_TRG_POL(Peri,Id,Data)              (void)Peri

/* SCU Macro */
typedef SCUCG_Type                                    SCU_Type;
#define SCU_ADDR                                      SCUCG_BASE
#define SET_SCU_CMP_PER(Peri,Id,Data)                 (void)Peri
#define SET_SCU_CMP_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCUCG,PPCLKEN2,CMP0CLKE)
#define SET_INTC_IRQ_UNMASK_EN(Peri,Irq,Data)         SET_BIT_ID(Peri,Irq,Data,INTC,MSK,IMSK0_LVI_ECCC)

#endif /* _HAL_CMP_F_01_00_01_H_ */
