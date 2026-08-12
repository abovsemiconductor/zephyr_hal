/**
 *******************************************************************************
 * @file        hal_frt_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed FRT
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_FRT_V_01_00_00_H_
#define _HAL_FRT_V_01_00_00_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#if (CONFIG_FRT_MAX_COUNT == 1)
#define FRT_REG_BASE                                  FRT_BASE
#else
#define FRT_REG_BASE                                  FRT0_BASE
#endif
#define FRT_REG_OFFSET                                0x100
#define FRT_CLEAR                                     true

/* Bit/Register Macro */
#define SET_FRT_CR_MODE(Peri,Data)                    SET_BIT(Peri,Data,FRT,CTRL,MODE)
#define SET_FRT_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,FRT,CTRL,EN)
#define SET_FRT_DR_CNT(Peri,Data)                     SET_BIT(Peri,Data,FRT,CNT,CNT)
#define SET_FRT_DR_MATCH_CNT(Peri,Data)               SET_BIT(Peri,Data,FRT,MCNT,MCNT)
#define GET_FRT_DR_CNT(Peri)                          GET_BIT(Peri,FRT,CNT,CNT)
#define GET_FRT_DR_MATCH_CNT(Peri)                    GET_BIT(Peri,FRT,MCNT,MCNT)

/* Interrupt Macro */
#define SET_FRT_IER_MATCH_EN(Peri,Data)               SET_BIT(Peri,Data,FRT,CTRL,MATCHIE)
#define SET_FRT_IER_OVF_EN(Peri,Data)                 SET_BIT(Peri,Data,FRT,CTRL,OVFIE)
#if (CONFIG_FRT_REG_NAME == 0)
#define SET_FRT_IER_MATCH_FLAG(Peri,Data)             SET_BIT(Peri,Data,FRT,STAT,MATCHIF)
#define SET_FRT_IER_OVF_FLAG(Peri,Data)               SET_BIT(Peri,Data,FRT,STAT,OVFIF)
#define GET_FRT_IER_MATCH_FLAG(Peri)                  GET_BIT(Peri,FRT,STAT,MATCHIF)
#define GET_FRT_IER_OVF_FLAG(Peri)                    GET_BIT(Peri,FRT,STAT,OVFIF)
#elif (CONFIG_FRT_REG_NAME == 1)
#define SET_FRT_IER_MATCH_FLAG(Peri,Data)             SET_BIT(Peri,Data,FRT,STAT,MATCHI)
#define SET_FRT_IER_OVF_FLAG(Peri,Data)               SET_BIT(Peri,Data,FRT,STAT,OVFI)
#define GET_FRT_IER_MATCH_FLAG(Peri)                  GET_BIT(Peri,FRT,STAT,MATCHI)
#define GET_FRT_IER_OVF_FLAG(Peri)                    GET_BIT(Peri,FRT,STAT,OVFI)
#endif

/* Unused Macro */
#define SET_FRT_CR_CLK_SEL(Peri,Data)                 (void)Peri
#define SET_FRT_CR_CLK_PREDIV(Peri,Data)              (void)Peri

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SCU_MCCR_MODE(x)                              (x < 2 ? x : x + 2)

#if (CONFIG_FRT_MAX_COUNT == 1)
#define SET_SCU_FRT_PER0(Peri,Data)                   SET_BIT(Peri,Data,SCU,PER1,FRT)
#define SET_SCU_FRT_PCER0(Peri,Data)                  SET_BIT(Peri,Data,SCU,PCER1,FRT)
#define SET_SCU_FRT_MCCR_SEL0(Peri,Data)              SET_BIT(Peri,Data,SCU,MCCR6,FRTCSEL)
#define SET_SCU_FRT_MCCR_DIV0(Peri,Data)              SET_BIT(Peri,Data,SCU,MCCR6,FRTCDIV)
#else
#define SET_SCU_FRT_PER0(Peri,Data)                   SET_BIT(Peri,Data,SCU,PER1,FRT0)
#define SET_SCU_FRT_PCER0(Peri,Data)                  SET_BIT(Peri,Data,SCU,PCER1,FRT0)
#define SET_SCU_FRT_PER1(Peri,Data)                   SET_BIT(Peri,Data,SCU,PER1,FRT1)
#define SET_SCU_FRT_PCER1(Peri,Data)                  SET_BIT(Peri,Data,SCU,PCER1,FRT1)
#define SET_SCU_FRT_MCCR_SEL0(Peri,Data)              SET_BIT(Peri,Data,SCU,MCCR6,FRT0CSEL)
#define SET_SCU_FRT_MCCR_DIV0(Peri,Data)              SET_BIT(Peri,Data,SCU,MCCR6,FRT0CDIV)
#define SET_SCU_FRT_MCCR_SEL1(Peri,Data)              SET_BIT(Peri,Data,SCU,MCCR6,FRT1CSEL)
#define SET_SCU_FRT_MCCR_DIV1(Peri,Data)              SET_BIT(Peri,Data,SCU,MCCR6,FRT1CDIV)
#endif

#endif /* _HAL_FRT_V_01_00_00_H_ */
