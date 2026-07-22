/**
 *******************************************************************************
 * @file        hal_tempsens_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed TempSens
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TEMPSENS_V_01_00_00_H_
#define _HAL_TEMPSENS_V_01_00_00_H_

/* Feature(Function) Configuration Define */
#define TEMPSENS_FEATURE_READ_REF_DATA_VX

/* Internal Macro */
typedef TEMP_Type                                           TEMPSENS_Type;
#define TEMPSENS_REG_BASE                                   TEMP_BASE
#define TEMPSENS_OPS_INTR_SUPPORT                           1
#define TEMPSENS_REF_HIGH_TEMP_ADDR                         0x3F0103F8
#define TEMPSENS_REF_HIGH_TEMP                              85
#define TEMPSENS_REF_LOW_TEMP_ADDR                          0x3F0103F4
#define TEMPSENS_REF_LOW_TEMP                               30
#define TEMPSENS_REF_CLK_DIV                                1000

/* Bit/Register Macro */
#define SET_TEMPSENS_CR_EN(Peri,Data)                       SET_BIT(Peri,Data,TEMP,TSENSECON,TSSEN)
#define SET_TEMPSENS_CR_START(Peri,Data)                    SET_BIT(Peri,Data,TEMP,TSENSECON,TSSTART)
#define SET_TEMPSENS_DR_PERIOD(Peri,Data)                   SET_BIT(Peri,Data,TEMP,TSREFPEROID,TSREFPERIOD)
#define GET_TEMPSENS_DR_SENSE(Peri)                         GET_BIT(Peri,TEMP,TSSENSECNT,TSSENSECNT)
#define GET_TEMPSENS_SR_FLAG(Peri)                          GET_BIT(Peri,TEMP,TSENSECON,TSSFLAG)
#define SET_TEMPSENS_SR_FLAG(Peri,Data)                     SET_BIT(Peri,Data,TEMP,TSENSECON,TSSFLAG)

/* Interrupt Macro */
#define SET_TEMPSENS_IER_EN(Peri,Data)                      SET_BIT(Peri,Data,TEMP,TSENSECON,TSSINTEN)

/* SCU Macro */
#define SCU_ADDR                                            SCU_BASE
#define SCU_MCCR_LSITS(x)                                   (x == 0 ? 1 : 0)
#define SET_SCU_TEMPSENS_PER(Peri,Id,Data)                  SET_BIT_ID(Peri,0,Data,SCU,PER2,TSENSE)
#define SET_SCU_TEMPSENS_PCER(Peri,Id,Data)                 SET_BIT_ID(Peri,0,Data,SCU,PCER2,TSENSE)
#define SET_SCU_TEMPSENS_MCCR_LSITS_EN(Peri,id,Data) \
                                                            SET_BIT_OFFSET(Peri,0,Data,SCU,MCCR5,LSITS_EN)
#define SET_SCU_TEMPSENS_MCCR_SEN(Peri,Id,Data) \
                                                            SET_SCU_TEMPSENS_MCCR_LSITS_EN(Peri,Id,SCU_MCCR_LSITS(Data)); \
                                                            SET_BIT_OFFSET(Peri,0,Data,SCU,MCCR5,TSSENSECLK_SEL)
#define SET_SCU_TEMPSENS_MCCR_REF(Peri,Id,Data)             SET_BIT_OFFSET(Peri,0,Data,SCU,MCCR5,TSREFCLK_SEL)

#endif /* _HAL_TEMPSENS_V_01_00_00_H_ */
