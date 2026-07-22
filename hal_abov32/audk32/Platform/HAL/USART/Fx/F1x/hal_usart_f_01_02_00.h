/**
 *******************************************************************************
 * @file        hal_usart_f_01_02_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.02.00 typed USART
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_USART_F_01_02_00_H_
#define _HAL_USART_F_01_02_00_H_

/* Feature(Function) Configuration Define */
#define USART_FEATURE_RX_TIME_OUT                     

/* Internal Macro */
#define USART_REG_BASE                                USART10_BASE
#define USART_REG_OFFSET                              0x100
#define USART_MODE(x)                                 ((x < 2) ? x : 0x3)
#define USART_DATA(x)                                 ((x < 4) ? x : 0x7)
#define USART_PARITY(x)                               ((x == 0) ? x : (x + 1))
#define USART_STATUS_MASK_BITS                        0x1F

#define USART_RX_TIMEOUT                              10000

/* Bit/Register Macro */
#define SET_USART_CR(Peri,Data)                       SET_REG(Peri,Data,CR1)
#define SET_USART_CR2(Peri,Data)                      SET_REG(Peri,Data,CR2)
#define GET_USART_SR(Peri)                            GET_REG(Peri,ST)
#define SET_USART_SR(Peri,Data)                       SET_REG(Peri,Data,ST)
#define GET_USART_DR_TX_ADDR(Peri)                    GET_REG_ADDR(Peri,DR)
#define GET_USART_DR_RX_ADDR(Peri)                    GET_REG_ADDR(Peri,DR)
#define SET_USART_CR_BDR(Peri,Data)                   SET_BIT(Peri,Data,USART,BDR,BDATA)
#define SET_USART_CR_MODE(Peri,Data)                  SET_BIT(Peri,Data,USART,CR1,MS)
#define SET_USART_CR_DLEN(Peri,Data)                  SET_BIT(Peri,Data,USART,CR1,DLEN)
#define SET_USART_CR_PARITY(Peri,Data)                SET_BIT(Peri,Data,USART,CR1,PG)
#define SET_USART_CR_STOPBIT(Peri,Data)               SET_BIT(Peri,Data,USART,CR2,SB)
#define SET_USART_CR_EN(Peri,Data)                    SET_BIT(Peri,Data,USART,CR2,EN)
#define SET_USART_CR_CPACK(Peri,Data)                 SET_BIT(Peri,Data,USART,CR1,CPOL)
#define SET_USART_CR_CPSCK(Peri,Data)                 SET_BIT(Peri,Data,USART,CR1,CPHA)
#define SET_USART_CR_TXEN(Peri,Data)                  SET_BIT(Peri,Data,USART,CR1,TXE)
#define SET_USART_CR_RXEN(Peri,Data)                  SET_BIT(Peri,Data,USART,CR1,RXE)
#define SET_USART_CR_MS(Peri,Data)                    SET_BIT(Peri,Data,USART,CR2,MASTER)
#define SET_USART_CR_SWAP_MS_PORT(Peri,Data)          SET_BIT(Peri,Data,USART,CR2,FXCH)
#define SET_USART_CR_SSEN(Peri,Data)                  SET_BIT(Peri,Data,USART,CR2,SSEN)
#define SET_USART_CR_BIT_ORDER(Peri,Data)             SET_BIT(Peri,Data,USART,CR1,ORD)
#define SET_USART_CR_DISSCK(Peri,Data)                SET_BIT(Peri,Data,USART,CR2,DISSCK)
#define SET_USART_CR_TXBIT_NINTH(Peri,Data)           SET_BIT(Peri,Data,USART,CR2,TX8)
#define SET_USART_CR_RXBIT_NINTH(Peri,Data)           SET_BIT(Peri,Data,USART,CR2,RX8)
#define GET_USART_CR_RXBIT_NINTH(Peri)                GET_BIT(Peri,USART,CR2,RX8)
#define SET_USART_CR_DBLS(Peri,Data)                  SET_BIT(Peri,Data,USART,CR2,DBLS)
#define SET_USART_CR_FPCR(Peri,Data)                  SET_BIT(Peri,Data,USART,BFR,BFC)
#define SET_USART_CR_FPCREN(Peri,Data)                SET_BIT(Peri,Data,USART,CR2,BFREN)
#define SET_USART_DR(Peri,Data)                       SET_BIT(Peri,Data,USART,DR,DATA)
#define GET_USART_DR(Peri)                            GET_BIT(Peri,USART,DR,DATA)
#define SET_USART_CR_RTO_EN(Peri,Data)                SET_BIT(Peri,Data,USART,CR2,RTOEN)
#define SET_USART_CR_RTO_CNT(Peri,Data)               SET_BIT(Peri,Data,USART,RTO,RTO)

/* Interrupt Macro */
#define SET_USART_IER_RTO_EN(Peri,Data)               SET_BIT(Peri,Data,USART,CR2,RTOIE)
#define SET_USART_IER_TXC_EN(Peri,Data)               SET_BIT(Peri,Data,USART,CR1,TXCIE)
#define GET_USART_IER_TXC_EN(Peri)                    GET_BIT(Peri,USART,CR1,TXCIE)
#define SET_USART_IER_RXC_EN(Peri,Data)               SET_BIT(Peri,Data,USART,CR1,RXCIE)
#define SET_USART_IER_DR_FLAG(Peri,Data)              SET_BIT(Peri,Data,USART,ST,DRE)
#define GET_USART_IER_DR_FLAG(Peri)                   GET_BIT(Peri,USART,ST,DRE)
#define GET_USART_IER_RXC_FLAG(Peri)                  GET_BIT(Peri,USART,ST,RXC)
#define SET_USART_IER_TXC_FLAG(Peri,Data)             SET_BIT(Peri,Data,USART,ST,TXC)
#define SET_USART_IER_RTO_FLAG(Peri,Data)             SET_BIT(Peri,Data,USART,ST,RTOF)
#define SET_USART_IER_DMATXC_EN(Peri,Data)            SET_BIT(Peri,Data,USART,CR2,DMATXIE)
#define SET_USART_IER_DMARXC_EN(Peri,Data)            SET_BIT(Peri,Data,USART,CR2,DMARXIE)

/* Unused Macro */
#define SET_USART_IER_WAKE_EN(Peri,Data)              (void)Peri

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_USART_PER(Peri,Id,Data)               SET_BIT_ID(Peri,Id,Data,SCU,PER2,USART10)
#define SET_SCU_USART_PCER(Peri,Id,Data)              SET_BIT_ID(Peri,Id,Data,SCU,PCER2,USART10)

#endif /* _HAL_USART_F_01_02_00_H_ */
