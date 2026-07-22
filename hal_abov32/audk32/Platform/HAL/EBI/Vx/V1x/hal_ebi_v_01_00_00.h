/**
 *******************************************************************************
 * @file        hal_ebi_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed EBI
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_EBI_V_01_00_00_H_
#define _HAL_EBI_V_01_00_00_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#define EBI_REG_BASE                                  EBI_BASE
#define EBI_REG_OFFSET                                4
#define EBI_CS_REG_OFFSET                             4

/* Bit/Register Macro */
#define SET_EBI_CR0_REG(Peri,Data)                    SET_REG(Peri,Data,SMIBCR0)
#define SET_EBI_CR1_REG(Peri,Data)                    SET_REG(Peri,Data,SMIBCR1)
#define SET_EBI_CR2_REG(Peri,Data)                    SET_REG(Peri,Data,SMIBCR2)
#define SET_EBI_CR3_REG(Peri,Data)                    SET_REG(Peri,Data,SMIBCR3)
#define SET_EBI_CR_REG(Addr,Data)                     SET_REG_ADDR(Addr,Data) 
#define GET_EBI_CR_BASE_ADDR(Peri)                    GET_REG_ADDR(Peri,SMIBCR0)
#define SET_EBI_CR_NORMWAIT_POS(Data)                 SET_POS(Data,EBI,SMIBCR0,NORMWAIT)
#define SET_EBI_CR_MWIDTH_POS(Data)                   SET_POS(Data,EBI,SMIBCR0,MWIDTH)
#define SET_EBI_CR_AH_POS(Data)                       SET_POS(Data,EBI,SMIBCR0,AH)
#define SET_EBI_CR_BLEN_POS(Data)                     SET_POS(Data,EBI,SMIBCR0,BLEN)
#define SET_EBI_CR_IOE_POS(Data)                      SET_POS(Data,EBI,SMIBCR0,IOE)
#define SET_EBI_CR_EWP_POS(Data)                      SET_POS(Data,EBI,SMIBCR0,EWP)
#define SET_EBI_CR_EWEN_POS(Data)                     SET_POS(Data,EBI,SMIBCR0,EWEN)
#define SET_EBI_CR_PREIDL_POS(Data)                   SET_POS(Data,EBI,SMIBCR0,PREIDL)
#define SET_EBI_CR_IDLE_POS(Data)                     SET_POS(Data,EBI,SMIBCR0,IDLE)

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_PER_EBI(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PER1,EBI)
#define SET_SCU_PCER_EBI(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PCER1,EBI)

#endif /* _HAL_EBI_V_01_00_00_H_ */
