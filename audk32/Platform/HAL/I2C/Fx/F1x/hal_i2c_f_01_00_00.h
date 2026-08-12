/**
 *******************************************************************************
 * @file        hal_i2c_f_01_00_00.h
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

#ifndef _HAL_I2C_F_01_00_00_H_
#define _HAL_I2C_F_01_00_00_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
typedef I2C0_Type                                     I2C_Type;
#define I2C_REG_BASE                                  I2C0_BASE
#define I2C_REG_OFFSET                                0x100
#define I2C_MANUAL_TIMEOUT                            10

/* Bit/Register Macro */
#define SET_I2C_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,I2C0,CR,I2CnEN)
#define SET_I2C_CR_ACK(Peri,Data)                     SET_BIT(Peri,Data,I2C0,CR,ACKnEN)
#define SET_I2C_CR_START(Peri,Data)                   SET_BIT(Peri,Data,I2C0,CR,STARTCn)
#define SET_I2C_CR_STOP(Peri,Data)                    SET_BIT(Peri,Data,I2C0,CR,STOPCn)
#define SET_I2C_CR_SLAVEADDR(Peri,Data)               SET_BIT(Peri,Data,I2C0,SAR1,SLAn)
#define SET_I2C_CR_SLAVEADDR2(Peri,Data)              SET_BIT(Peri,Data,I2C0,SAR2,SLAn)
#define SET_I2C_CR_GNRLADDR(Peri,Data)                SET_BIT(Peri,Data,I2C0,SAR1,GCALLnEN)
#define SET_I2C_CR_GNRLADDR2(Peri,Data)               SET_BIT(Peri,Data,I2C0,SAR2,GCALLnEN)
#define SET_I2C_DR_TX(Peri,Data)                      SET_BIT(Peri,Data,I2C0,DR,DATA)
#define GET_I2C_DR_RX(Peri)                           GET_BIT(Peri,I2C0,DR,DATA)
#define SET_I2C_CR_MS(Peri,Data)                      SET_BIT(Peri,Data,I2C0,CR,IMASTERn)
#define SET_I2C_CR_SCLL(Peri,Data)                    SET_BIT(Peri,Data,I2C0,SCLR,SCLL)
#define SET_I2C_CR_SCLH(Peri,Data)                    SET_BIT(Peri,Data,I2C0,SCHR,SCLH)
#define SET_I2C_CR_SDA_HOLD_EN(Peri,Data)             SET_BIT(Peri,(Data == 0 ? 0x01 : 0x00),I2C0,CR,TXDLYENBn)
#define SET_I2C_CR_SDA_HOLD(Peri,Data)                SET_BIT(Peri,Data,I2C0,SDHR,HLDT)
#define SET_I2C_SR_CLEAR(Peri)                        SET_REG(Peri,0xFF,ST)
#define GET_I2C_SR(Peri)                              GET_REG(Peri,ST)

/* Interrupt Macro */
#define SET_I2C_IER_EN(Peri,Data)                     SET_BIT(Peri,Data,I2C0,CR,I2CnIEN)
#define GET_I2C_IER_FLAG(Peri)                        GET_BIT(Peri,I2C0,CR,I2CnIFLAG)

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_I2C_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PER2,I2C0)
#define SET_SCU_I2C_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PCER2,I2C0)

#endif /* _HAL_I2C_F_01_00_00_H_ */
