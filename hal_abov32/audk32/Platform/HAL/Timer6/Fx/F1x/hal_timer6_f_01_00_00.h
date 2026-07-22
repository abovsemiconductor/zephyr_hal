/**
 *******************************************************************************
 * @file        hal_timer6_f_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed Timer6
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER6_F_01_00_00_H_
#define _HAL_TIMER6_F_01_00_00_H_

/* Feature(Function) Configuration Define */
#define TIMER6_FEATURE_IRQ_UNMASK_ENABLE

/* Configuration Define from config_xxx.h */

/* Internal Macro */
typedef TIMER6n_Type                                  TIMER6_Type;
#define TIMER6_REG_BASE                               TIMER60_BASE
#define TIMER6_REG_OFFSET                             0x100
#define TIMER6_REG_TIMER_OFFSET                       0x300
#define TIMER6_REG_OFFSET_CNT                         11
#define TIMER6_ID_SKIP_CNT                            3

/* Bit/Register Macro */
#define SET_TIMER6_DR(Peri,Data)                      SET_REG(Peri,Data,DR)
#define GET_TIMER6_DR(Peri)                           GET_REG(Peri,DR)
#define SET_TIMER6_CR(Peri,Data)                      SET_REG(Peri,Data,CR)
#define GET_TIMER6_CNT(Peri)                          GET_REG(Peri,CNT)

#define SET_TIMER6_CR_EN(Peri,Data)                   SET_BIT(Peri,Data,TIMER6n,CR,T6nEN)
#define GET_TIMER6_CR_EN(Peri)                        GET_BIT(Peri,TIMER6n,CR,T6nEN)
#define SET_TIMER6_CR_CLR(Peri,Data)                  SET_BIT(Peri,Data,TIMER6n,CR,T6nCLR)
#define GET_TIMER6_CR_CLR(Peri)                       GET_BIT(Peri,TIMER6n,CR,T6nCLR)

/* Interrupt Macro */
#define SET_TIMER6_IER_MATCH_FLAG(Peri,Data)          SET_BIT(Peri,Data,TIMER6n,CR,T6nMIFLAG)
#define GET_TIMER6_IER_MATCH_FLAG(Peri)               GET_BIT(Peri,TIMER6n,CR,T6nMIFLAG)
#define SET_TIMER6_IER_MATCH_EN(Peri,Data)            SET_BIT(Peri,Data,TIMER6n,CR,T6nMIEN)
#define GET_TIMER6_IER_MATCH_EN(Peri)                 GET_BIT(Peri,TIMER6n,CR,T6nMIEN)

/* Unused Macro */

/* SCU Macro */
typedef SCUCG_Type                                    SCU_Type;
#define SCU_ADDR                                      SCUCG_BASE
#define SET_SCU_TIMER6_PER(Peri,Id,Data)              (void)Peri
#define SET_SCU_TIMER6_PCER(Peri,Id,Data)             SET_BIT_ID(Peri,Id,Data,SCUCG,PPCLKEN1,T60CLKE)
#define SET_INTC_IRQ_UNMASK_EN(Peri,Irq,Data)         SET_BIT_ID(Peri,Irq,Data,INTC,MSK,IMSK0_LVI)

#endif /* _HAL_TIMER6_F_01_00_00_H_ */
