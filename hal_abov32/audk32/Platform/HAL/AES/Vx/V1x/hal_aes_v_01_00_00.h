/**
 *******************************************************************************
 * @file        hal_aes_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed AES
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_AES_V_01_00_00_H_
#define _HAL_AES_V_01_00_00_H_

/* Feature(Function) Configuration Define */
#define AES_FEATURE_CHAIN_ONLY_ECB

/* Internal Macro */
typedef AES128_Type                                   AES_Type;
#define AES_REG_BASE                                  AES128_BASE
#define AES_REG_OFFSET                                0x0
#define AES_CIPHER_MODE(x)                            (x + 1)
#define AES_TEXT_ALIGN(x)                             (x == 3 ? 4 : x)
#define AES_KEY_REG_COUNT                             4
#define AES_BYTE_LENGTH                               4

/* Bit/Register Macro */
#define SET_AES_CR_CIPHER_MODE(Peri,Data)             SET_BIT(Peri,Data,AES128,CTRL,MODE)
#define SET_AES_CR_TEXT_IN_SEL(Peri,Data)             SET_BIT(Peri,Data,AES128,CTRL,TIINVMD)
#define SET_AES_CR_TEXT_OUT_SEL(Peri,Data)            SET_BIT(Peri,Data,AES128,CTRL,TOINVMD)
#define SET_AES_CR_IN_FIFO_FLUSH(Peri,Data)           SET_BIT(Peri,Data,AES128,CTRL,INFIFOFLUSH)
#define SET_AES_CR_OUT_FIFO_FLUSH(Peri,Data)          SET_BIT(Peri,Data,AES128,CTRL,OUTFIFOFLUSH)
#define SET_AES_DR_INFIFO_VAL(Peri,Data)              SET_REG(Peri,Data,INFIFO)
#define GET_AES_DR_OUTFIFO_VAL(Peri)                  GET_REG(Peri,OUTFIFO)
#define GET_AES_DR_KEY_BASE_ADDR(Peri)                GET_REG_ADDR(Peri,KEYIN0)
#define GET_AES_DR_INFIFO_ADDR(Peri)                  GET_REG_ADDR(Peri,INFIFO)
#define GET_AES_DR_OUTFIFO_ADDR(Peri)                 GET_REG_ADDR(Peri,OUTFIFO)
#define GET_AES_DR_TEXT_OUT_ADDR(Peri)                GET_REG_ADDR(Peri,TEXTOUT0)

/* Interrupt Macro */
#define SET_AES_IER_ENC_DONE_EN(Peri,Data)            SET_BIT(Peri,Data,AES128,CTRL,CIPHERIE)
#define SET_AES_IER_DEC_DONE_EN(Peri,Data)            SET_BIT(Peri,Data,AES128,CTRL,INVCIPHERIE)
#define SET_AES_IER_ENC_DONE_FLAG(Peri,Data)          SET_BIT(Peri,Data,AES128,STAT,CIPDONE)
#define GET_AES_IER_ENC_DONE_FLAG(Peri)               GET_BIT(Peri,AES128,STAT,CIPDRS)
#define SET_AES_IER_DEC_DONE_FLAG(Peri,Data)          SET_BIT(Peri,Data,AES128,STAT,INVCIPDONE)
#define GET_AES_IER_DEC_DONE_FLAG(Peri)               GET_BIT(Peri,AES128,STAT,INVCIPDRS)
#define SET_AES_IER_IN_DMA_EN(Peri,Data)              SET_BIT(Peri,Data,AES128,CTRL,DMAINIE)
#define SET_AES_IER_OUT_DMA_EN(Peri,Data)             SET_BIT(Peri,Data,AES128,CTRL,DMAOUTIE)
#define SET_AES_IER_IN_DMA_FLAG(Peri,Data)            SET_BIT(Peri,Data,AES128,STAT,DMAIN)
#define GET_AES_IER_IN_DMA_FLAG(Peri)                 GET_BIT(Peri,AES128,STAT,DMAINRS)
#define SET_AES_IER_OUT_DMA_FLAG(Peri,Data)           SET_BIT(Peri,Data,AES128,STAT,DMAOUT)
#define GET_AES_IER_OUT_DMA_FLAG(Peri)                GET_BIT(Peri,AES128,STAT,DMAOUTRS)

/* Unused Macro */
#define SET_AES_CR_EN(Peri,Data)                      (void)0
#define SET_AES_CR_CHAIN_MODE(Peri,Data)              (void)0

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_AES_PER(Peri,Data)                    SET_BIT(Peri,Data,SCU,PER2,AES)
#define SET_SCU_AES_PCER(Peri,Data)                   SET_BIT(Peri,Data,SCU,PCER2,AES)

#endif /* _HAL_AES_V_01_00_00_H_ */
