/**
 *******************************************************************************
 * @file        hal_tempsens_f_01_00_01.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.01 typed TempSens
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TEMPSENS_F_01_00_01_H_
#define _HAL_TEMPSENS_F_01_00_01_H_

/* Feature(Function) Configuration Define */
#define TEMPSENS_FEATURE_IRQ_UNMASK_ENABLE
#define TEMPSENS_FEATURE_READ_REF_DATA_FX

/* Internal Macro */
typedef TS_Type                                             TEMPSENS_Type;
#define TEMPSENS_REG_BASE                                   TS_BASE
#define TEMPSENS_OPS_INTR_SUPPORT                           1
#define TEMPSENS_REF_HIGH_TEMP_ADDR                         0x1FFF204C
#define TEMPSENS_REF_HIGH_TEMP                              85
#define TEMPSENS_REF_LOW_TEMP_ADDR                          0x1FFF2048
#define TEMPSENS_REF_LOW_TEMP                               30
#define TEMPSENS_REF_CLK_DIV                                1023

/* Bit/Register Macro */
#define SET_TEMPSENS_CR_EN(Peri,Data)                       SET_BIT(Peri,Data,TS,CR,TSEN)
#define SET_TEMPSENS_CR_START(Peri,Data)                    SET_BIT(Peri,Data,TS,CR,CNTST)
#define SET_TEMPSENS_DR_PERIOD(Peri,Data)                   SET_BIT(Peri,Data,TS,IDR,IDATA)
#define GET_TEMPSENS_DR_SENSE(Peri)                         GET_BIT(Peri,TS,OUTDR,OUTDATA)
#define GET_TEMPSENS_SR_FLAG(Peri)                          GET_BIT(Peri,TS,CR,TSIFLAG)
#define SET_TEMPSENS_SR_FLAG(Peri,Data)                     SET_BIT(Peri,Data,TS,CR,TSIFLAG)

/* Interrupt Macro */
#define SET_TEMPSENS_IER_EN(Peri,Data)                      SET_BIT(Peri,Data,TS,CR,TSIEN)

/* SCU Macro */
typedef SCUCG_Type                                          SCU_Type;
#define SCU_ADDR                                            SCUCG_BASE
#define INTC_REG_BASE                                       INTC_BASE;
#define SET_SCU_TEMPSENS_PER(Peri,Data)                     (void)Peri
#define SET_SCU_TEMPSENS_PCER(Peri,Data)                    SET_BIT(Peri,Data,SCUCG,PPCLKEN1,TSCLKE)
#if (CONFIG_TEMPSENS_REG_NAME == 1)
#define SET_INTC_IRQ_UNMASK_EN(Peri,Data)                   SET_BIT_ID(Peri,20,Data,INTC,MSK,IMSK0_LVI)
#else
#define SET_INTC_IRQ_UNMASK_EN(Peri,Data)                   SET_BIT_ID(Peri,20,Data,INTC,MSK,IMSK0_LVI_ECCC)
#endif

#endif /* _HAL_TEMPSENS_F_01_00_01_H_ */
