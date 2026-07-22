/**
 *******************************************************************************
 * @file        hal_vrefbuf_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed VREFBUF
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_VREFBUF_V_01_00_00_H_
#define _HAL_VREFBUF_V_01_00_00_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#define VREFBUF_REG_BASE                                  VREFBUF_BASE
#define VREFBUF_REG_OFFSET                                0x100

#define VREF_MODE(x)                                      (x > P_VREFBUF_MODE_VDDEXT ?  (x + 1) : x)

/* Bit/Register Macro */
#define SET_VREFBUF_CR_MODE(Peri,Data)                    SET_BIT(Peri,VREF_MODE(Data),VREFBUF,CR,MODE_SEL)
#define SET_VREFBUF_CR_VREF_VOLT(Peri,Data)               SET_BIT(Peri,Data,VREFBUF,CR,VREFP_SEL)
#define SET_VREFBUF_SR_STABLE(Peri,Data)                  SET_BIT(Peri,Data,VREFBUF,SR,VREF_ACT)
#define GET_VREFBUF_SR_STABLE(Peri)                       GET_BIT(Peri,VREFBUF,SR,VREF_ACT)
#define SET_VREFBUF_TCR_STABLE_TIME(Peri,Data)            SET_BIT(Peri,Data,VREFBUF,TCR,VREF_STIME)

/* Interrupt Macro */
#define SET_VREFBUF_IER_EN(Peri,Data)                     SET_BIT(Peri,Data,VREFBUF,CR,INTEN)
#define GET_VREFBUF_IER_EN(Peri)                          GET_BIT(Peri,VREFBUF,CR,INTEN)

/* Unused Macro */

/* SCU Macro */
#define SCU_ADDR                                          SCU_BASE
#define SET_SCU_VREFBUF_PER(Peri,Data)                    SET_BIT(Peri,Data,SCU,PER1,VREFBUF)
#define SET_SCU_VREFBUF_PCER(Peri,Data)                   SET_BIT(Peri,Data,SCU,PCER1,VREFBUF)

#endif /* _HAL_VREFBUF_V_01_00_00_H_ */
