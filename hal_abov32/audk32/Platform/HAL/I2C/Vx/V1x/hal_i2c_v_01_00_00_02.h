/**
 *******************************************************************************
 * @file        hal_i2c_v_01_00_00_02.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00-02 typed I2C
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_I2C_V_01_00_00_02_H_
#define _HAL_I2C_V_01_00_00_02_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
typedef I2C0_Type                                     I2C_Type;
#define I2C_REG_BASE                                  I2C0_BASE
#define I2C_REG_OFFSET                                0x80

/* Bit/Register Macro */
#define SET_I2C_BIT(Peri,Data,RegName,BitName)        SET_BIT(Peri,Data,I2C0,RegName,BitName)
#define GET_I2C_BIT(Peri,RegName,BitName)             GET_BIT(Peri,I2C0,RegName,BitName)
#define SET_I2C_CR_DELAY(Peri,Data)                   SET_BIT(Peri,Data,I2C0,CR,INTDEL)
#define SET_I2C_CR_ACK(Peri,Data)                     SET_BIT(Peri,Data,I2C0,CR,ACKEN)
#define SET_I2C_CR_START(Peri,Data)                   SET_BIT(Peri,Data,I2C0,CR,START)
#define SET_I2C_CR_STOP(Peri,Data)                    SET_BIT(Peri,Data,I2C0,CR,STOP)
#define SET_I2C_DR_TX(Peri,Data)                      SET_BIT(Peri,Data,I2C0,DR,ICDR)
#define GET_I2C_DR_RX(Peri)                           GET_BIT(Peri,I2C0,DR,ICDR)
#define SET_I2C_CR_MS(Peri,Data)                      SET_BIT(Peri,Data,I2C0,CR,IMASTERn)
#define SET_I2C_CR_SLAVEADDR(Peri,Data)               SET_BIT(Peri,Data,I2C0,SAR,SVAD)
#define SET_I2C_CR_GNRLADDR(Peri,Data)                SET_BIT(Peri,Data,I2C0,SAR,GCALL)
#define SET_I2C_CR_SCLL(Peri,Data)                    SET_BIT(Peri,Data,I2C0,SCLL,SCLL)
#define SET_I2C_CR_SCLH(Peri,Data)                    SET_BIT(Peri,Data,I2C0,SCLH,SCLH)
#define SET_I2C_CR_SDA_HOLD(Peri,Data)                SET_BIT(Peri,Data,I2C0,SDH,SDH)
#define SET_I2C_SR_CLEAR(Peri)                        SET_REG(Peri,0xFF,SR)
#define GET_I2C_SR(Peri)                              GET_REG(Peri,SR)

/* Interrupt Macro */
#define GET_I2C_IER_FLAG(Peri)                        GET_BIT(Peri,I2C0,CR,IIF)
#define SET_I2C_IER_EN(Peri,Data)                     SET_BIT(Peri,Data,I2C0,CR,IINTEN)

/* Unused Macro */
#define SET_I2C_CR_EN(Peri,Data)                      (void)Peri
#define SET_I2C_CR_SLAVEADDR2(Peri,Data)              (void)Peri
#define SET_I2C_CR_GNRLADDR2(Peri,Data)               (void)Peri
#define SET_I2C_CR_SDA_HOLD_EN(Peri,Data)             (void)Peri

/* SCU Macro */
typedef PMU_Type                                      SCU_Type;
#define SCU_ADDR                                      PMU_BASE
#define SET_SCU_I2C_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,PMU,PER,I2C0)
#define SET_SCU_I2C_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,PMU,PCCR,I2C0)

#endif /* _HAL_I2C_V_01_00_00_02_H_ */
