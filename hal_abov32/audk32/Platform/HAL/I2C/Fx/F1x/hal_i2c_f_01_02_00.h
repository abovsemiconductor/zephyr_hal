/**
 *******************************************************************************
 * @file        hal_i2c_f_01_02_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.02.00 typed I2C
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_I2C_F_01_02_00_H_
#define _HAL_I2C_F_01_02_00_H_

/* Feature(Function) Configuration Define */
#define I2C_FEATURE_LOW_TIMEOUT_PERIOD
#define I2C_FEATURE_MANUAL_BUS_CONTROL

/* Internal Macro */
#define I2C_REG_BASE                                  I2C0_BASE
#define I2C_REG_OFFSET                                0x100
#define I2C_MANUAL_TIMEOUT                            10

#if (CONFIG_I2C_REG_NAME == 1)

/* Bit/Register Macro */
#define SET_I2C_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,I2C0,CR,I2CnEN)
#define SET_I2C_CR_ACK(Peri,Data)                     SET_BIT(Peri,Data,I2C0,CR,ACKnEN)
#define SET_I2C_CR_START(Peri,Data)                   SET_BIT(Peri,Data,I2C0,CR,STARTCn)
#define SET_I2C_CR_STOP(Peri,Data)                    SET_BIT(Peri,Data,I2C0,CR,STOPCn)
#define SET_I2C_CR_SLAVEADDR(Peri,Data)               SET_BIT(Peri,Data,I2C0,SAR1,SLAn)
#define SET_I2C_CR_SLAVEADDR2(Peri,Data)              SET_BIT(Peri,Data,I2C0,SAR2,SLAn)
#define SET_I2C_CR_GNRLADDR(Peri,Data)                SET_BIT(Peri,Data,I2C0,SAR1,GCALLnEN)
#define SET_I2C_CR_GNRLADDR2(Peri,Data)               SET_BIT(Peri,Data,I2C0,SAR2,GCALLnEN)
#define SET_I2C_CR_MS(Peri,Data)                      SET_BIT(Peri,Data,I2C0,CR,IMASTERn)
#define SET_I2C_CR_SDA_HOLD_EN(Peri,Data)             SET_BIT(Peri,(Data == 0 ? 0x01 : 0x00),I2C0,CR,TXDLYENBn)
#define SET_I2C_SR_CLEAR(Peri)                        SET_REG(Peri,0xFF,ST)
#define GET_I2C_SR(Peri)                              GET_REG(Peri,ST)

/* Interrupt Macro */
#define SET_I2C_IER_EN(Peri,Data)                     SET_BIT(Peri,Data,I2C0,CR,I2CnIEN)
#define GET_I2C_IER_FLAG(Peri)                        GET_BIT(Peri,I2C0,CR,I2CnIFLAG)

#else

/* Bit/Register Macro */
#define SET_I2C_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,I2C0,CR,EN)
#define SET_I2C_CR_ACK(Peri,Data)                     SET_BIT(Peri,Data,I2C0,CR,ACKEN)
#define SET_I2C_CR_START(Peri,Data)                   SET_BIT(Peri,Data,I2C0,CR,STARTC)
#define SET_I2C_CR_STOP(Peri,Data)                    SET_BIT(Peri,Data,I2C0,CR,STOPC)
#define SET_I2C_CR_SLAVEADDR(Peri,Data)               SET_BIT(Peri,Data,I2C0,SAR1,SLA)
#define SET_I2C_CR_SLAVEADDR2(Peri,Data)              SET_BIT(Peri,Data,I2C0,SAR2,SLA)
#define SET_I2C_CR_GNRLADDR(Peri,Data)                SET_BIT(Peri,Data,I2C0,SAR1,GCALLEN)
#define SET_I2C_CR_GNRLADDR2(Peri,Data)               SET_BIT(Peri,Data,I2C0,SAR2,GCALLEN)
#define GET_I2C_DR_RX(Peri)                           GET_BIT(Peri,I2C0,DR,DATA)
#define SET_I2C_CR_MS(Peri,Data)                      SET_BIT(Peri,Data,I2C0,CR,IMASTER)
#define SET_I2C_CR_SDA_HOLD_EN(Peri,Data)             SET_BIT(Peri,(Data == 0 ? 0x01 : 0x00),I2C0,CR,TXDLYENB)
#define SET_I2C_SR_CLEAR(Peri)                        SET_REG(Peri,0xFF,ST)
#define GET_I2C_SR(Peri)                              GET_REG(Peri,ST)

/* Interrupt Macro */
#define SET_I2C_IER_EN(Peri,Data)                     SET_BIT(Peri,Data,I2C0,CR,IEN)
#define GET_I2C_IER_FLAG(Peri)                        GET_BIT(Peri,I2C0,CR,IFLAG)

#endif

/* Bit/Register Macro */
#define SET_I2C_DR_TX(Peri,Data)                      SET_BIT(Peri,Data,I2C0,DR,DATA)
#define GET_I2C_DR_RX(Peri)                           GET_BIT(Peri,I2C0,DR,DATA)
#define SET_I2C_CR_SDA_HOLD(Peri,Data)                SET_BIT(Peri,Data,I2C0,SDHR,HLDT)
#define SET_I2C_CR_SCLL(Peri,Data)                    SET_BIT(Peri,Data,I2C0,SCLR,SCLL)
#define SET_I2C_CR_SCLH(Peri,Data)                    SET_BIT(Peri,Data,I2C0,SCHR,SCLH)
#define SET_I2C_CR_SCL_LOW_TO_EN(Peri,Data)           SET_BIT(Peri,Data,I2C0,SLTCR,SLTEN)
#define SET_I2C_DR_SCL_LOW_TO(Peri,Data)              SET_BIT(Peri,Data,I2C0,SLTPDR,PDATA)
#define SET_I2C_CR_SCL_MAUL_EN(Peri,Data)             SET_BIT(Peri,Data,I2C0,MBCR,SCLMCE)
#define SET_I2C_CR_SDA_MAUL_EN(Peri,Data)             SET_BIT(Peri,Data,I2C0,MBCR,SDAMCE)
#define GET_I2C_SR_SCL_MAUL_STA(Peri)                 GET_BIT(Peri,I2C0,MBCR,SCLS)
#define GET_I2C_SR_SDA_MAUL_STA(Peri)                 GET_BIT(Peri,I2C0,MBCR,SDAS)
#define SET_I2C_CR_SCL_MAUL_OUT(Peri,Data)            SET_BIT(Peri,Data,I2C0,MBCR,SCLO)
#define SET_I2C_CR_SDA_MAUL_OUT(Peri,Data)            SET_BIT(Peri,Data,I2C0,MBCR,SDAO)

/* Interrupt Macro */
#define SET_I2C_IER_SCL_LOW_TO_EN(Peri,Data)          SET_BIT(Peri,Data,I2C0,SLTCR,SLTINT)

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_I2C_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PER2,I2C0)
#define SET_SCU_I2C_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PCER2,I2C0)

#endif /* _HAL_I2C_F_01_02_00_H_ */
