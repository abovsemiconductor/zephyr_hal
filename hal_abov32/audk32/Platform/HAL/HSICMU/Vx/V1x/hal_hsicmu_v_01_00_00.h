/**
 *******************************************************************************
 * @file        hal_hsicmu_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed HSICMU
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_HSICMU_V_01_00_00_H_
#define _HAL_HSICMU_V_01_00_00_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#define HSICMU_REG_BASE                                 HSICMU_BASE
#define HSICMU_REG_OFFSET                               0x0

/* Bit/Register Macro */
#define SET_HSICMU_CR_EN(Peri,Data)                     SET_BIT(Peri,Data,HSICMU,CR,HSICMU_EN)
#define SET_HSICMU_CR_AUTOTRIM_EN(Peri,Data)            SET_BIT(Peri,Data,HSICMU,CR,AUTOTRIM_EN)
#define SET_HSICMU_CR_SW_SYNC(Peri,Data)                SET_BIT(Peri,Data,HSICMU,CR,SW_SYNC)
#define SET_HSICMU_CR_TIMER(Peri,Data)                  SET_BIT(Peri,Data,HSICMU,CR,SET_TIMER)
#define SET_HSICMU_CR_SYNC_START(Peri,Data)             SET_BIT(Peri,Data,HSICMU,CR,SYNC_START)
#define SET_HSICMU_CR_TRIMVALUE(Peri,Data)              SET_BIT(Peri,Data,HSICMU,CR,SET_TRIMVALUE)

/* Interrupt Macro */


/* Unused Macro */


/* SCU Macro */
#define SCU_ADDR                                        SCU_BASE
#define SET_SCU_HSICMU_PER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PER1,HSICMU)
#define SET_SCU_HSICMU_PCER(Peri,Id,Data)               SET_BIT_ID(Peri,Id,Data,SCU,PCER1,HSICMU)

#endif /* _HAL_HSICMU_V_01_00_00_H_ */
