/**
 *******************************************************************************
 * @file        hal_crc_v_01_00_01.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.01 typed CRC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_CRC_V_01_00_01_H_
#define _HAL_CRC_V_01_00_01_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#define CRC_REG_BASE                                  CRC_BASE
#define CRC_REG_OFFSET                                0x100
#define CRC_CH_NUM                                    CONFIG_CRC_MAX_COUNT
#define CRC_IN_BUF_MASK                               0xFFFFFFFF
#define CRC_INT_INP(x)                                ((~x) & 0x1)
#define CRC_INT_POLY(x)                               (x == 4 ? 0 : x)
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
#define GET_CRC_IN_ADDR(Peri)                         GET_REG_ADDR(Peri,IN)

/* Interrupt Macro */
#define SET_CRC_IER_DMA_EN(Peri,Data)                 SET_BIT(Peri,Data,CRC,CR,CRCINTEN)
#define SET_CRC_IER_DMA_FLAG(Peri,Data)               SET_BIT(Peri,Data,CRC,CR,CRCINTF)
#define GET_CRC_IER_DMA_FLAG(Peri)                    GET_BIT(Peri,CRC,CR,CRCINTF)

/* Unused Macro */
#define SET_CRC_CR_OP_MODE(Peri,Data)                 (void)0
#define SET_CRC_CR_OUTP(Peri,Data)                    (void)0
#define SET_CRC_CR_OUTP_INV(Peri,Data)                (void)0

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_CRC_PER(Peri,Data)                    SET_BIT(Peri,Data,SCU,PER2,CRC)
#define SET_SCU_CRC_PCER(Peri,Data)                   SET_BIT(Peri,Data,SCU,PCER2,CRC)

#endif /* _HAL_CRC_V_01_00_01_H_ */
