/**
 *******************************************************************************
 * @file        hal_i2c_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed I2C
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_I2C_V_01_00_00_H_
#define _HAL_I2C_V_01_00_00_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#if (I2C_CH_NUM == 1)
#else
#define I2C_REG_BASE                                  I2C0_BASE
#endif
#define I2C_REG_OFFSET                                0x100

/* Bit/Register Macro */
#define SET_I2C_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,I2C,CR,I2CEN)
#define SET_I2C_CR_DELAY(Peri,Data)                   SET_BIT(Peri,Data,I2C,CR,INTDEL)
#define SET_I2C_CR_ACK(Peri,Data)                     SET_BIT(Peri,Data,I2C,CR,ACKEN)
#define SET_I2C_CR_START(Peri,Data)                   SET_BIT(Peri,Data,I2C,CR,START)
#define SET_I2C_CR_STOP(Peri,Data)                    SET_BIT(Peri,Data,I2C,CR,STOP)
#define SET_I2C_DR_TX(Peri,Data)                      SET_BIT(Peri,Data,I2C,DR,ICDR)
#define GET_I2C_DR_RX(Peri)                           GET_BIT(Peri,I2C,DR,ICDR)
#define SET_I2C_CR_MS(Peri,Data)                      SET_BIT(Peri,Data,I2C,CR,IMASTERn)
#define SET_I2C_IER_EN(Peri,Data)                     SET_BIT(Peri,Data,I2C,CR,INTEN)
#define SET_I2C_CR_SLAVEADDR(Peri,Data)               SET_BIT(Peri,Data,I2C,SAR0,SVAD0)
#define SET_I2C_CR_GNRLADDR(Peri,Data)                SET_BIT(Peri,Data,I2C,SAR0,GCEN)
#define SET_I2C_CR_SLAVEADDR2(Peri,Data)              SET_BIT(Peri,Data,I2C,SAR1,SLVAD)
#define SET_I2C_CR_GNRLADDR2(Peri,Data)               SET_BIT(Peri,Data,I2C,SAR1,GCEN)
#define SET_I2C_SR_CLEAR(Peri)                        SET_REG(Peri,0x79,SR)
#define GET_I2C_SR(Peri)                              GET_REG(Peri,SR)

#if (CONFIG_I2C_REG_NAME == 1)
#define SET_I2C_CR_SCLL(Peri,Data)                    SET_BIT(Peri,Data,I2C,SCLLLR,SCLL)
#define SET_I2C_CR_SCLH(Peri,Data)                    SET_BIT(Peri,Data,I2C,SCLHR,SCLH)
#define SET_I2C_CR_SDA_HOLD(Peri,Data)                SET_BIT(Peri,Data,I2C,SDAHR,SDH)
#else
#define SET_I2C_CR_SCLL(Peri,Data)                    SET_BIT(Peri,Data,I2C,SCLL,SCLL)
#define SET_I2C_CR_SCLH(Peri,Data)                    SET_BIT(Peri,Data,I2C,SCLH,SCLH)
#define SET_I2C_CR_SDA_HOLD(Peri,Data)                SET_BIT(Peri,Data,I2C,SDH,SDH)
#endif

/* Interrupt Register */
#define SET_I2C_IER_EN(Peri,Data)                     SET_BIT(Peri,Data,I2C,CR,INTEN)
#define GET_I2C_IER_FLAG(Peri)                        GET_BIT(Peri,I2C,CR,IIF)

/* Unused Macro */
#define SET_I2C_CR_SDA_HOLD_EN(Peri,Data)             (void)Peri

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#if (I2C_CH_NUM == 1)
#define SET_SCU_I2C_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PER2,I2C)
#define SET_SCU_I2C_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PCER2,I2C)
#else
#define SET_SCU_I2C_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PER2,I2C0)
#define SET_SCU_I2C_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PCER2,I2C0)
#endif

#endif /* _HAL_I2C_V_01_00_00_H_ */
