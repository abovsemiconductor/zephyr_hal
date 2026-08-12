/**
 *******************************************************************************
 * @file        hal_crc_f_01_00_01.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.01 typed CRC
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_CRC_F_01_00_01_H_
#define _HAL_CRC_F_01_00_01_H_

/* Feature(Function) Configuration Define */
#define CRC_FEATURE_INPUT_CONF_MODE   

/* Internal Macro */
#define CRC_REG_BASE                                  CRC_BASE
#define CRC_REG_OFFSET                                0x100
#define CRC_IN_BUF_MASK                               0xFFFFFFFF
#define CRC_INT_INP(x)                                ((~x) & 0x1)
#define CRC_INT_POLY(x)                               (x == 4 || x == 3 ? 0 : \
                                                      (x == 0 ? 3 : x))
#define CRC_CHKSUM_NOT_AVAIL                          0
#define CRC_BYTE_ALIGN                                4

/* Bit/Register Macro */
#define SET_CRC_CR_MODE(Peri,Data)                    SET_BIT(Peri,Data,CRC,CR,MDSEL)
#define SET_CRC_CR_POLY(Peri,Data)                    SET_BIT(Peri,Data,CRC,CR,POLYS)
#define SET_CRC_CR_INP(Peri,Data)                     SET_BIT(Peri,Data,CRC,CR,FIRSTBS)
#define SET_CRC_CR_OUT_CLR(Peri,Data)                 SET_BIT(Peri,Data,CRC,CR,RLTCLR)
#define SET_CRC_DR_IN(Peri,Data)                      SET_REG(Peri,Data,IN)
#define SET_CRC_DR_INIT(Peri,Data)                    SET_REG(Peri,Data,INIT)
#define GET_CRC_DR_OUT(Peri)                          GET_REG(Peri,RLT)
#define SET_CRC_CR_EN(Peri,Data) \
                                                      SET_BIT(Peri,Data,CRC,CR,CRCRUN); \
                                                      __NOP(); \
                                                      __NOP(); \
                                                      __NOP(); \
                                                      __NOP()
#define SET_CRC_CR_OP_MODE(Peri,Data)                 SET_BIT(Peri,Data,CRC,CR,MODS)
#define GET_CRC_IN_ADDR(Peri)                         GET_REG_ADDR(Peri,IN)
#define SET_CRC_CR_START_ADDR(Peri,Data)              SET_BIT(Peri,Data,CRC,SADR,SADR)
#define SET_CRC_CR_END_ADDR(Peri,Data)                SET_BIT(Peri,Data,CRC,EADR,EADR)
#define SET_CRC_CR_INDATA_SIZE(Peri,Data)             SET_BIT(Peri,Data,CRC,CR,INSIZE)
#define GET_CRC_CR_INDATA_SIZE(Peri)                  GET_BIT(Peri,CRC,CR,INSIZE)
#define SET_CRC_CR_INDATA_COMPLE(Peri,Data)           SET_BIT(Peri,Data,CRC,CR,INCOMP)
#define GET_CRC_CR_INDATA_COMPLE(Peri)                GET_BIT(Peri,CRC,CR,INCOMP)

/* Interrupt Macro */
#define SET_CRC_IER_DMA_EN(Peri,Data)                 (void)Peri
#define SET_CRC_IER_DMA_FLAG(Peri,Data)               (void)Peri
#define GET_CRC_IER_DMA_FLAG(Peri)                    0

/* Unused Macro */
#define SET_CRC_CR_OUTP(Peri,Data)                    (void)0
#define SET_CRC_CR_OUTP_INV(Peri,Data)                (void)0

/* SCU Macro */
typedef SCUCG_Type                                    SCU_Type;
#define SCU_ADDR                                      SCUCG_BASE
#define SET_SCU_CRC_PER(Peri,Data)                    (void)Peri
#define SET_SCU_CRC_PCER(Peri,Data)                   SET_BIT(Peri,Data,SCUCG,PPCLKEN2,CRCLKE)

#endif /* _HAL_CRC_F_01_00_01_H_ */
