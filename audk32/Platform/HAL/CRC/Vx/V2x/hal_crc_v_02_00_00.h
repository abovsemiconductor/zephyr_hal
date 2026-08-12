/**
 *******************************************************************************
 * @file        hal_crc_v_02_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 02.00.00 typed CRC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_CRC_V_02_00_00_H_
#define _HAL_CRC_V_02_00_00_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#define CRC_REG_BASE                                  CRC_BASE
#define CRC_REG_OFFSET                                0x100
#define CRC_IN_BUF_MASK                               0xFFFFFFFF
#define CRC_INT_INP(x)                                (x)
#define CRC_INT_POLY(x)                               (x)
#define CRC_INTR_NOT_AVAIL                            0
#define CRC_CHKSUM_NOT_AVAIL                          1
#define CRC_BYTE_ALIGN                                4

/* Bit/Register Macro */
#if (CONFIG_CRC_REG_NAME == 0)
#define SET_CRC_CR_OP_MODE(Peri,Data)                 SET_BIT(Peri,Data,CRC,CTRL,DMADINTEN)
#elif (CONFIG_CRC_REG_NAME == 1)
#define SET_CRC_CR_OP_MODE(Peri,Data)                 SET_BIT(Peri,Data,CRC,CTRL,DMADINT)
#endif

#define SET_CRC_CR_POLY(Peri,Data)                    SET_BIT(Peri,Data,CRC,CTRL,POLY)
#define SET_CRC_CR_INP(Peri,Data)                     SET_BIT(Peri,Data,CRC,CTRL,IN_REV)
#define SET_CRC_CR_OUTP(Peri,Data)                    SET_BIT(Peri,Data,CRC,CTRL,OUT_REV)
#define SET_CRC_CR_OUTP_INV(Peri,Data)                SET_BIT(Peri,Data,CRC,CTRL,OUT_INV)
#define SET_CRC_CR_EN(Peri,Data) \
                                                      SET_BIT(Peri,Data,CRC,CTRL,INIT_EN); \
                                                      __NOP(); \
                                                      __NOP(); \
                                                      __NOP(); \
                                                      __NOP()
#define SET_CRC_DR_IN(Peri,Data)                      SET_REG(Peri,Data,IDR)
#define SET_CRC_DR_INIT(Peri,Data)                    SET_REG(Peri,Data,INIT)
#if (CONFIG_CRC_REG_NAME == 0)
#define GET_CRC_DR_OUT(Peri)                          GET_BIT(Peri,CRC,ODR,ODR)
#elif (CONFIG_CRC_REG_NAME == 1)
#define GET_CRC_DR_OUT(Peri)                          GET_BIT(Peri,CRC,ODR,OUTPUT)
#endif
#define SET_CRC_CR(Peri,Data)                         SET_REG(Peri,Data,CTRL)
#define GET_CRC_IN_ADDR(Peri)                         GET_REG_ADDR(Peri,IDR)

/* Interrupt Macro */
#if (CONFIG_CRC_REG_NAME == 0)
#define SET_CRC_IER_DMA_EN(Peri,Data)                 SET_BIT(Peri,Data,CRC,CTRL,DMADINTEN)
#elif (CONFIG_CRC_REG_NAME == 1)
#define SET_CRC_IER_DMA_EN(Peri,Data)                 SET_BIT(Peri,Data,CRC,CTRL,DMADINT)
#endif
#define SET_CRC_IER_DMA_FLAG(Peri,Data)               SET_BIT(Peri,Data,CRC,STAT,DMADINT)
#define GET_CRC_IER_DMA_FLAG(Peri)                    GET_BIT(Peri,CRC,STAT,DMADINT)

/* Unused Macro */
#define SET_CRC_CR_MODE(Peri,Data)                    (void)0
#define SET_CRC_CR_OUT_CLR(Peri,Data)                 (void)0

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_CRC_PER(Peri,Data)                    SET_BIT(Peri,Data,SCU,PER2,CRC)
#define SET_SCU_CRC_PCER(Peri,Data)                   SET_BIT(Peri,Data,SCU,PCER2,CRC)

#endif /* _HAL_CRC_V_02_00_00_H_ */
