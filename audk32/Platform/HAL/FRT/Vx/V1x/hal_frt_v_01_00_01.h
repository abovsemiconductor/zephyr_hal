/**
 *******************************************************************************
 * @file        hal_frt_v_01_00_01.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.01 typed FRT
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_FRT_V_01_00_01_H_
#define _HAL_FRT_V_01_00_01_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#define FRT_REG_BASE                                  FRT_BASE
#define FRT_REG_OFFSET                                0x100
#define FRT_CLEAR                                     false

/* Bit/Register Macro */
#define SET_FRT_CR_MODE(Peri,Data)                    SET_BIT(Peri,Data,FRT,CON,FAC)
#define SET_FRT_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,FRT,CON,FEN)
#define SET_FRT_DR_CNT(Peri,Data)                     SET_REG(Peri,Data,CNT)
#define SET_FRT_DR_MATCH_CNT(Peri,Data)               SET_REG(Peri,Data,PRD)
#define SET_FRT_CR_CLK_SEL(Peri,Data)                 SET_BIT(Peri,Data,FRT,CON,FEC)
#define SET_FRT_CR_CLK_PREDIV(Peri,Data)              SET_BIT(Peri,Data,FRT,CON,FPRS)
#define GET_FRT_DR_CNT(Peri)                          GET_REG(Peri,CNT)
#define GET_FRT_DR_MATCH_CNT(Peri)                    GET_REG(Peri,PRD)

/* Interrupt Macro */
#define SET_FRT_IER_MATCH_EN(Peri,Data)               SET_BIT(Peri,Data,FRT,CON,FMIE)
#define SET_FRT_IER_OVF_EN(Peri,Data)                 SET_BIT(Peri,Data,FRT,CON,FOIE)
#define SET_FRT_IER_MATCH_FLAG(Peri,Data)             SET_BIT(Peri,Data,FRT,CON,FMF)
#define SET_FRT_IER_OVF_FLAG(Peri,Data)               SET_BIT(Peri,Data,FRT,CON,FOF)
#define GET_FRT_IER_MATCH_FLAG(Peri)                  GET_BIT(Peri,FRT,CON,FMF)
#define GET_FRT_IER_OVF_FLAG(Peri)                    GET_BIT(Peri,FRT,CON,FOF)

/* SCU Macro */
typedef PMU_Type                                      SCU_Type;
#define SCU_ADDR                                      PMU_BASE
#define SCU_MCCR_MODE(x)                              (x == 4 ? 0x00 : x == 3 ? 0x01 : x == 1 ? 0x02 : x == 0 ? 0x03 : 0x00)

#define SET_SCU_FRT_PER0(Peri,Data)                   SET_BIT(Peri,Data,PMU,PER,FRT)
#define SET_SCU_FRT_PCER0(Peri,Data)                  SET_BIT(Peri,Data,PMU,PCCR,FRT)
#define SET_SCU_FRT_MCCR_SEL0(Peri,Data)              SET_BIT(Peri,Data,PMU,PCSR,FRTCS)

/* Unused SCU Macro */
#define SET_SCU_FRT_MCCR_DIV0(Peri,Data)              (void)Peri

#endif /* _HAL_FRT_V_01_00_01_H_ */
