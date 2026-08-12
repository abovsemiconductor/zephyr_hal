/**
 *******************************************************************************
 * @file        hal_dac_v_02_00_01.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 02.00.01 typed DAC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_DAC_V_02_00_01_H_
#define _HAL_DAC_V_02_00_01_H_

/* Feature(Function) Configuration Define */
#define DAC_FEATURE_OUTPUT_PORT                       3
#define DAC_FEATURE_BUFFER_OFFSET

/* Internal Macro */
#define DAC_REG_BASE                                  DAC_BASE
#define DAC_DR_SHIFT                                  4
#define DAC_RELOAD(x)                                 (x > 0 ? x+1 : x)
#define DAC_RESOLUTION                                1023

/* Bit/Register Macro */
#define SET_DAC_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,DAC,CR,DACEN)
#define SET_DAC_CR_RELOAD(Peri,Data)                  SET_BIT(Peri,Data,DAC,CR,DACRLDS)
#define SET_DAC_CR_BF_CLEAR(Peri,Data)                SET_BIT(Peri,Data,DAC,CR,DACBC)
#define SET_DAC_DR_IN(Peri,Data)                      SET_BIT(Peri,Data,DAC,DR,DACDR)
#define GET_DAC_DR_OUT(Peri)                          GET_BIT(Peri,DAC,BR,DACBR)
#define SET_DAC_CR_REF(Peri,Data)                     SET_BIT(Peri,Data,DAC,CR,REFSEL)
#define SET_DAC_CR_PORT_EN(Peri,Data)                 SET_BIT(Peri,Data,DAC,CR,DAC_OUT1_EN)
#define SET_DAC_CR_PORT1_EN(Peri,Data)                SET_BIT(Peri,Data,DAC,CR,DAC_OUT2_EN)
#define SET_DAC_CR_PORT2_EN(Peri,Data)                SET_BIT(Peri,Data,DAC,CR,DAC_OUT3_EN)
#define SET_DAC_CR_PG(Peri,Data)                      SET_BIT(Peri,Data,DAC,PGSR,DACPGSR)
#define SET_DAC_CR_OFS_EN(Peri,Data)                  SET_BIT(Peri,Data,DAC,OFSCR,OFSEN)
#define SET_DAC_CR_OFS_DIR(Peri,Data)                 SET_BIT(Peri,Data,DAC,OFSCR,OFSDIR)
#define SET_DAC_DR_OFS(Peri,Data)                     SET_BIT(Peri,Data,DAC,OFSCR,OFS)
#define SET_DAC_CR_AUTO(Peri,Data)                    SET_BIT(Peri,Data,DAC,CR,ADATID)

/* Interrupt Macro */
#define SET_DAC_IER_FLAG(Peri,Data)                   SET_BIT(Peri,Data,DAC,CR,DACIFR)
#define GET_DAC_IER_FLAG(Peri)                        GET_BIT(Peri,DAC,CR,DACIFR)
#define SET_DAC_IER_EN(Peri,Data)                     SET_BIT(Peri,Data,DAC,CR,DACIE)

/* Unused Macro */
#define GET_DAC_DR_ADDR(Peri)                         0
#define SET_DAC_IER_DMA_EN(Peri,Data)                 (void)Peri
#define SET_DAC_IER_DMA_FLAG(Peri,Data)               (void)Peri
#define GET_DAC_IER_DMA_FLAG(Peri)                    (void)0
#define SET_DAC_IER_DMA_UNDER_EN(Peri,Data)           (void)Peri
#define GET_DAC_IER_DMA_UNDER_EN(Peri)                (void)0
#define SET_DAC_IER_DMA_UNDER_FLAG(Peri,Data)         (void)Peri
#define GET_DAC_IER_DMA_UNDER_FLAG(Peri)              (void)0

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_DAC_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PER2,DAC)
#define SET_SCU_DAC_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PCER2,DAC)

#endif /* _HAL_DAC_V_02_00_01_H_ */
