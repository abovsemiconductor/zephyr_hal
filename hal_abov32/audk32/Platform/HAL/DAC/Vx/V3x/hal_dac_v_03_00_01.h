/**
 *******************************************************************************
 * @file        hal_dac_v_03_00_01.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 03.00.00 typed DAC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_DAC_V_03_00_01_H_
#define _HAL_DAC_V_03_00_01_H_

/* Feature(Function) Configuration Define */
#define DAC_FEATURE_BUFFER_ENABLE_WITH_DELAY

/* Internal Macro */
#define DAC_REG_BASE                                  DAC0_BASE
#define DAC_REG_OFFSET                                0x100
#define DAC_DR_SHIFT                                  0
#define DAC_RESOLUTION                                4095

/* Bit/Register Macro */
#define SET_DAC_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,DAC,CR,DACEN)
#define SET_DAC_DR_IN(Peri,Data)                      SET_BIT(Peri,Data,DAC,DR,DACD)
#define GET_DAC_DR_OUT(Peri)                          GET_BIT(Peri,DAC,DR,DACD)
#define SET_DAC_CR_PG(Peri,Data)                      (void)Peri

#define SET_DAC_CR_BIAS_EN(Peri,Data)                 (void)Peri
#define SET_DAC_CR_BUF_EN(Peri,Data)                  SET_BIT(Peri,Data,DAC,CR,BUFEN)
#define SET_DAC_CR_BUF_MODE_EN(Peri,Data)             (void)Peri
#define SET_DAC_CR_BYPASS_MODE_EN(Peri,Data)          (void)Peri

/* Unused Macro */
#define SET_DAC_CR_PORT_EN(Peri,Data)                 (void)Peri
#define SET_DAC_CR_RELOAD(Peri,Data)                  (void)Peri
#define SET_DAC_CR_BF_CLEAR(Peri,Data)                (void)Peri
#define SET_DAC_CR_AUTO(Peri,Data)                    (void)Peri
#define SET_DAC_CR_REF(Peri,Data)                     (void)Peri
#define SET_DAC_CR_OFS_EN(Peri,Data)                  (void)Peri
#define SET_DAC_CR_OFS_DIR(Peri,Data)                 (void)Peri
#define SET_DAC_CR_OFS_DATA(Peri,Data)                (void)Peri
#define GET_DAC_DR_ADDR(Peri)                         0
#define SET_DAC_IER_FLAG(Peri,Data)                   (void)Peri
#define GET_DAC_IER_FLAG(Peri)                        0
#define SET_DAC_IER_EN(Peri,Data)                     (void)Peri
#define SET_DAC_IER_DMA_EN(Peri,Data)                 (void)Peri
#define SET_DAC_IER_DMA_FLAG(Peri,Data)               (void)Peri
#define GET_DAC_IER_DMA_FLAG(Peri)                    0
#define SET_DAC_IER_DMA_UNDER_EN(Peri,Data)           (void)Peri
#define GET_DAC_IER_DMA_UNDER_EN(Peri)                0
#define SET_DAC_IER_DMA_UNDER_FLAG(Peri,Data)         (void)Peri
#define GET_DAC_IER_DMA_UNDER_FLAG(Peri)              0

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_DAC_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PER2,DAC0)
#define SET_SCU_DAC_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PCER2,DAC0)

#endif /* _HAL_DAC_V_03_00_01_H_ */
