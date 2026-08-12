/**
 *******************************************************************************
 * @file        hal_tempsens_v_01_00_01.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.01 typed TempSens
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TEMPSENS_V_01_00_01_H_
#define _HAL_TEMPSENS_V_01_00_01_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
typedef TS_Type                                             TEMPSENS_Type;
#define TEMPSENS_REG_BASE                                   TS_BASE
#define TEMPSENS_OPS_INTR_SUPPORT                           1
#define TEMPSENS_REF_CLK_DIV                                1000

/* Bit/Register Macro */
#define SET_TEMPSENS_CR_START(Peri,Data)                    SET_BIT(Peri,Data,TS,CR,START)
#define SET_TEMPSENS_DR_PERIOD(Peri,Data)                   SET_BIT(Peri,Data,TS,RCCNT,RCCV)
#define GET_TEMPSENS_DR_SENSE(Peri)                         GET_BIT(Peri,TS,SCCNT,SCCV)
#define GET_TEMPSENS_SR_FLAG(Peri)                          GET_BIT(Peri,TS,SR,DONE)
#define SET_TEMPSENS_SR_FLAG(Peri,Data)                     SET_BIT(Peri,Data,TS,SR,DONE)

/* Interrupt Macro */
#define SET_TEMPSENS_IER_EN(Peri,Data)                      SET_BIT(Peri,Data,TS,CR,INTEN)

/* Unused Macro */
#define SET_TEMPSENS_CR_EN(Peri,Data)                       (void)Peri

/* SCU Macro */
#define SCU_ADDR                                            SCU_BASE
#define SCU_MCCR_LSITS(x)                                   (x == 0 ? 1 : 0)
#define SET_SCU_TEMPSENS_PER(Peri,Id,Data)                  SET_BIT_ID(Peri,0,Data,SCU,PER2,TS)
#define SET_SCU_TEMPSENS_PCER(Peri,Id,Data)                 SET_BIT_ID(Peri,0,Data,SCU,PCER2,TS)
#define SET_SCU_TEMPSENS_MCCR_LSITS_EN(Peri,id,Data) \
                                                            SET_BIT_OFFSET(Peri,0,Data,SCU,MCCR5,TSSLSITSEN)
#define SET_SCU_TEMPSENS_MCCR_SEN(Peri,Id,Data) \
                                                            SET_SCU_TEMPSENS_MCCR_LSITS_EN(Peri,Id,SCU_MCCR_LSITS(Data)); \
                                                            SET_BIT_OFFSET(Peri,0,Data,SCU,MCCR5,TSSCSEL)
#define SET_SCU_TEMPSENS_MCCR_REF(Peri,Id,Data)             SET_BIT_OFFSET(Peri,0,Data,SCU,MCCR5,TSRCSEL)

#endif /* _HAL_TEMPSENS_V_01_00_01_H_ */
