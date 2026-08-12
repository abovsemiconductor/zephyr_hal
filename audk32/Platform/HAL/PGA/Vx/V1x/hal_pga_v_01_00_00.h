/**
 *******************************************************************************
 * @file        hal_pga_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed PGA
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_PGA_V_01_00_00_H_
#define _HAL_PGA_V_01_00_00_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#define PGA_REG_BASE                                  PGA0_BASE
#define PGA_REG_OFFSET                                0x4

/* Bit/Register Macro */
#define SET_PGA_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,PGA,CR,AMPEN)
#define SET_PGA_CR_GAIN_EN(Peri,Data)                 SET_BIT(Peri,Data,PGA,CR,UGAINEN)
#define SET_PGA_CR_GAIN_SEL(Peri,Data)                SET_BIT(Peri,Data,PGA,CR,GAINSEL)
#define SET_PGA_CR_AMP_CURR_SEL(Peri,Data)            SET_BIT(Peri,Data,PGA,CR,AMPISEL)

/* Unused Macro */

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_PGA_PER(Peri,Data)                    SET_BIT(Peri,Data,SCU,PER2,PGA)
#define SET_SCU_PGA_PCER(Peri,Data)                   SET_BIT(Peri,Data,SCU,PCER2,PGA)

#endif /* _HAL_PGA_V_01_00_00_H_ */
