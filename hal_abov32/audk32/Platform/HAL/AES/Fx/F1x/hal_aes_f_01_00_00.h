/**
 *******************************************************************************
 * @file        hal_aes_f_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed AES
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_AES_F_01_00_00_H_
#define _HAL_AES_F_01_00_00_H_

/* Feature(Function) Configuration Define */
#define AES_FEATURE_READ_SINGLE_BUFFER
#define AES_FEATURE_IRQ_UNMASK_ENABLE
#define AES_FEATURE_DESC_KEY_EXPANSION
#define AES_FEATURE_INIT_VECTOR
#define AES_FEATURE_DMA_INTERNAL_INTERRUPT

/* Internal Macro */
#define AES_REG_BASE                                  AES_BASE
#define AES_REG_OFFSET                                0x0
#define AES_CIPHER_MODE(x)                            (x)
#define AES_TEXT_ALIGN(x)                             (x == 3 ? 4 : x)
#define AES_KEY_REG_COUNT                             4
#define AES_BYTE_LENGTH                               4
#define AES_ENC_MODE                                  0
#define AES_DESC_MODE                                 1
#define AES_KEY_EXPANSION_MODE                        2
#define AES_DESC_KEY_EXPANSION_TIMEOUT                1000000

/* Bit/Register Macro */
#define SET_AES_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,AES,CR,AESEN)
#define SET_AES_CR_CIPHER_MODE(Peri,Data)             SET_BIT(Peri,Data,AES,CR,MDSEL)
#define SET_AES_CR_TEXT_OUT_SEL(Peri,Data)            SET_BIT(Peri,Data,AES,CR,SWAPTYP)
#define SET_AES_CR_CHAIN_MODE(Peri,Data)              SET_BIT(Peri,Data,AES,CR,CHMDS)
#define SET_AES_DR_INFIFO_VAL(Peri,Data)              SET_REG(Peri,Data,INDR)
#define GET_AES_DR_OUTFIFO_VAL(Peri)                  GET_REG(Peri,OUTDR)
#define GET_AES_DR_KEY_BASE_ADDR(Peri)                GET_REG_ADDR(Peri,KEYDR1)
#define GET_AES_DR_KEY_OUT_BASE_ADDR(Peri)            GET_REG_ADDR(Peri,KEYOUTDR1)
#define GET_AES_DR_INFIFO_ADDR(Peri)                  GET_REG_ADDR(Peri,INDR)
#define GET_AES_DR_OUTFIFO_ADDR(Peri)                 GET_REG_ADDR(Peri,OUTDR)
#define GET_AES_DR_TEXT_OUT_ADDR(Peri)                GET_REG_ADDR(Peri,OUTDR)
#define GET_AES_DR_IV_BASE_ADDR(Peri)                 GET_REG_ADDR(Peri,IVDR1)

/* Interrupt Macro */
#define SET_AES_IER_ENC_DONE_EN(Peri,Data)            SET_BIT(Peri,Data,AES,CR,AESIEN)
#define SET_AES_IER_DEC_DONE_EN(Peri,Data)            SET_BIT(Peri,Data,AES,CR,AESIEN)
#define SET_AES_IER_ENC_DONE_FLAG(Peri,Data)          SET_BIT(Peri,Data,AES,CR,AESIFLAG)
#define GET_AES_IER_ENC_DONE_FLAG(Peri)               GET_BIT(Peri,AES,CR,AESIFLAG)
#define SET_AES_IER_DEC_DONE_FLAG(Peri,Data)          SET_BIT(Peri,Data,AES,CR,AESIFLAG)
#define GET_AES_IER_DEC_DONE_FLAG(Peri)               GET_BIT(Peri,AES,CR,AESIFLAG)

/* Unused Macro */
#define SET_AES_CR_TEXT_IN_SEL(Peri,Data)             (void)0
#define SET_AES_CR_IN_FIFO_FLUSH(Peri,Data)           (void)0
#define SET_AES_CR_OUT_FIFO_FLUSH(Peri,Data)          (void)0
#define SET_AES_IER_IN_DMA_EN(Peri,Data)              (void)0
#define SET_AES_IER_OUT_DMA_EN(Peri,Data)             (void)0
#define SET_AES_IER_IN_DMA_FLAG(Peri,Data)            (void)0
#define GET_AES_IER_IN_DMA_FLAG(Peri)                 (void)0
#define SET_AES_IER_OUT_DMA_FLAG(Peri,Data)           (void)0
#define GET_AES_IER_OUT_DMA_FLAG(Peri)                (void)0

/* SCU Macro */
typedef SCUCG_Type                                    SCU_Type;
#define SCU_ADDR                                      SCUCG_BASE
#define INTC_REG_BASE                                 INTC_BASE;
#define SET_SCU_AES_PER(Peri,Data)                    (void)Peri
#define SET_SCU_AES_PCER(Peri,Data)                   SET_BIT(Peri,Data,SCUCG,PPCLKEN1,AESCLKE)
#define SET_INTC_IRQ_UNMASK_EN(Peri,Data)             SET_BIT_ID(Peri,30,Data,INTC,MSK,IMSK0_LVI)

#endif /* _HAL_AES_F_01_00_00_H_ */
