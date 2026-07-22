/**
 *******************************************************************************
 * @file        hal_rng_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed RNG
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_RNG_V_01_00_00_H_
#define _HAL_RNG_V_01_00_00_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#define RNG_REG_BASE                                  RNG_BASE
#define RNG_REG_OFFSET                                0x0

/* Bit/Register Macro */
#define SET_RNG_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,RNG,CTRL,EN)
#define SET_RNG_CR_LFS_SEL(Peri,Data)                 SET_BIT(Peri,Data,RNG,CTRL,LCS)
#define SET_RNG_CR_CAS_SEL(Peri,Data)                 SET_BIT(Peri,Data,RNG,CTRL,CCS)
#define SET_RNG_CR_GCP_VAL(Peri,Data)                 SET_BIT(Peri,Data,RNG,CTRL,GCP)
#define SET_RNG_DR_SEED_VAL(Peri,Data)                SET_REG(Peri,Data,SEED)
#define GET_RNG_DR_RNGD_VAL(Peri)                     GET_REG(Peri,RNGD)
#define GET_RNG_SR_RDY_FLAG(Peri)                     GET_BIT(Peri,RNG,STAT,RDY)
#define SET_RNG_SR_RDY_FLAG(Peri,Data)                SET_BIT(Peri,Data,RNG,STAT,RDY)
#define GET_RNG_SR_ERR_FLAG(Peri)                     GET_BIT(Peri,RNG,STAT,ERR)
#define SET_RNG_SR_ERR_FLAG(Peri,Data)                SET_BIT(Peri,Data,RNG,STAT,ERR)

/* Interrupt Macro */
#define SET_RNG_IER_RDY_EN(Peri,Data)                 SET_BIT(Peri,Data,RNG,CTRL,RDYIE)
#define SET_RNG_IER_RDY_FLAG(Peri,Data)               SET_BIT(Peri,Data,RNG,STAT,RDYI)
#define GET_RNG_IER_RDY_FLAG(Peri)                    GET_BIT(Peri,RNG,STAT,RDYI)
#define SET_RNG_IER_ERR_EN(Peri,Data)                 SET_BIT(Peri,Data,RNG,CTRL,ERRIE)
#define SET_RNG_IER_ERR_FLAG(Peri,Data)               SET_BIT(Peri,Data,RNG,STAT,ERRI)
#define GET_RNG_IER_ERR_FLAG(Peri)                    GET_BIT(Peri,RNG,STAT,ERRI)

/* Unused Macro */

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_RNG_PER(Peri,Data)                    SET_BIT(Peri,Data,SCU,PER2,RNG)
#define SET_SCU_RNG_PCER(Peri,Data)                   SET_BIT(Peri,Data,SCU,PCER2,RNG)

#endif /* _HAL_RNG_V_01_00_00_H_ */
