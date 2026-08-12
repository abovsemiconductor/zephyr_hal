/**
 *******************************************************************************
 * @file        hal_pwm_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed PWM
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_PWM_V_01_00_00_H_
#define _HAL_PWM_V_01_00_00_H_

/* Feature(Function) Configuration Define */

/* Configuration Define from config_xxx.h */

/* Internal Macro */
typedef PWM0_Type                                     PWM_Type;
typedef PWMPRS0_Type                                  PWMPRS_Type;
#define PWM_REG_BASE                                  PWM0_BASE
#define PWM_REG_OFFSET                                0x20
#define PWM_PRS_REG_BASE                              PWMPRS0_BASE
#define PWM_PRS_REG_OFFSET                            0x80

#define PWM_PRS_ID(x)                                 (x < 4 ? 0 : 1)

/* Bit/Register Macro */
#define SET_PWM_DR_PERIOD(Peri,Data)                  SET_REG(Peri,Data,PER)
#define SET_PWM_DR_DUTY(Peri,Data)                    SET_REG(Peri,Data,CMP)

#define SET_PWM_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,PWM0,CTRL,STRT)
#define SET_PWM_CR_SYNC(Peri,Data)                    SET_BIT(Peri,Data,PWM0,CTRL,SYNC)
#define SET_PWM_CR_PORTA_INV(Peri,Data)               SET_BIT(Peri,Data,PWM0,CTRL,INVA)
#define SET_PWM_CR_CLK_DIV(Peri,Data)                 SET_BIT(Peri,Data,PWM0,CTRL,CKSEL)
#define GET_PWM_CR_CLK_DIV(Peri)                      GET_BIT(Peri,PWM0,CTRL,CKSEL)

#if (CONFIG_PWM_REG_NAME == 1)
#define SET_PWMPRS_PRE_SCALE_EN(Peri,Data)            SET_BIT(Peri,Data,PWMPRS0,PRSn,CLKEN)
#define SET_PWMPRS_PRE_SCALE(Peri,Data)               SET_BIT(Peri,Data,PWMPRS0,PRSn,PRESCALER)
#else
#define SET_PWMPRS_PRE_SCALE_EN(Peri,Data)            SET_BIT(Peri,Data,PWMPRS0,PWMPRSn,CLKEN)
#define SET_PWMPRS_PRE_SCALE(Peri,Data)               SET_BIT(Peri,Data,PWMPRS0,PWMPRSn,PRESCALER)
#endif

/* Interrupt Macro */
#define SET_PWM_IER_MATCH_FLAG(Peri,Data)             SET_BIT(Peri,Data,PWM0,CTRL,PRF)
#define GET_PWM_IER_MATCH_FLAG(Peri)                  GET_BIT(Peri,PWM0,CTRL,PRF)
#define SET_PWM_IER_MATCH_EN(Peri,Data)               SET_BIT(Peri,Data,PWM0,CTRL,PRIE)

/* Unused Macro */

/* SCU Macro */
typedef PMU_Type                                      SCU_Type;
#define SCU_ADDR                                      PMU_BASE
#define SCU_ENABLE(x)                                 (x < 4 ? 0 : 1)
#define SET_SCU_PWM_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,PMU,PER,PWM03)
#define SET_SCU_PWM_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,PMU,PCCR,PWM03)

#endif /* _HAL_PWM_V_01_00_00_H_ */
