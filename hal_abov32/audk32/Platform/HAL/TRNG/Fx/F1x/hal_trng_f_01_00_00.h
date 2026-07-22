/**
 *******************************************************************************
 * @file        hal_trng_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed TRNG
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TRNG_F_01_00_00_H_
#define _HAL_TRNG_F_01_00_00_H_

/* Feature(Function) Configuration Define */
#define TRNG_FEATURE_IRQ_UNMASK_ENABLE

/* Internal Macro */
typedef RNG_Type                                       TRNG_Type;
#define TRNG_REG_BASE                                  RNG_BASE
#define TRNG_REG_OFFSET                                0x0

/* Bit/Register Macro */
#define SET_TRNG_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,RNG,CR,RNGEN)
#define GET_TRNG_DR_TRNGD_VAL(Peri)                    GET_REG(Peri,OUTDR)
#define GET_TRNG_SR_RDY_FLAG(Peri)                     GET_BIT(Peri,RNG,CR,RNGIFLAG)
#define SET_TRNG_SR_RDY_FLAG(Peri,Data)                SET_BIT(Peri,Data,RNG,CR,RNGIFLAG)
#define GET_TRNG_SR_ERR_FLAG(Peri)                     GET_BIT(Peri,RNG,CR,ERRIFLAG)
#define SET_TRNG_SR_ERR_FLAG(Peri,Data)                SET_BIT(Peri,Data,RNG,CR,ERRIFLAG)

/* Interrupt Macro */
#define SET_TRNG_IER_RDY_EN(Peri,Data)                 SET_BIT(Peri,Data,RNG,CR,RNGIEN)
#define SET_TRNG_IER_RDY_FLAG(Peri,Data)               SET_BIT(Peri,Data,RNG,CR,RNGIFLAG)
#define GET_TRNG_IER_RDY_FLAG(Peri)                    GET_BIT(Peri,RNG,CR,RNGIFLAG)
#define SET_TRNG_IER_ERR_EN(Peri,Data)                 SET_BIT(Peri,Data,RNG,CR,ERRIEN)
#define SET_TRNG_IER_ERR_FLAG(Peri,Data)               SET_BIT(Peri,Data,RNG,CR,ERRIFLAG)
#define GET_TRNG_IER_ERR_FLAG(Peri)                    GET_BIT(Peri,RNG,CR,ERRIFLAG)

/* Unused Macro */

/* SCU Macro */
typedef SCUCG_Type                                    SCU_Type;
#define SCU_ADDR                                      SCUCG_BASE
#define INTC_REG_BASE                                 INTC_BASE;
#define SET_SCU_TRNG_PER(Peri,Data)                   (void)Peri
#define SET_SCU_TRNG_PCER(Peri,Data)                  SET_BIT(Peri,Data,SCUCG,PPCLKEN1,RNGCLKE)
#define SET_INTC_IRQ_UNMASK_EN(Peri,Data)             SET_BIT_ID(Peri,31,Data,INTC,MSK,IMSK0_LVI)

#endif /* _HAL_TRNG_F_01_00_00_H_ */
