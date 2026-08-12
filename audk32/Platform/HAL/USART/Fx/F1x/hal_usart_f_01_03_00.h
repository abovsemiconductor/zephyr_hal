/**
 *******************************************************************************
 * @file        hal_usart_f_01_03_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed USART
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_USART_F_01_03_00_H_
#define _HAL_USART_F_01_03_00_H_

/* Feature(Function) Configuration Define */
#define USART_FEATURE_IRQ_UNMASK_ENABLE
#define USART_FEATURE_MASTER_SS_PIN_BY_GPIO
#define USART_FEATURE_NO_NINTH_BIT_REG
#define USART_FEATURE_SUPPORT_MULTI_IRQ
#define USART_FEATURE_DMA_INTERNAL_INTERRUPT

/* Internal Macro */
typedef USART1n_Type                                  USART_Type;
#define USART_REG_BASE                                USART10_BASE
#define USART_REG_OFFSET                              0x100
#define USART_MODE(x)                                 ((x < 2) ? x : 0x3)
#define USART_DATA(x)                                 ((x < 4) ? x : 0x7)
#define USART_PARITY(x)                               ((x == 0) ? x : (x + 1))
#define USART_STATUS_MASK_BITS                        0xFF

#define USART_RX_TIMEOUT                              10000

/* Bit/Register Macro */
#define SET_USART_CR(Peri,Data)                       SET_REG(Peri,Data,CR1)
#define SET_USART_CR2(Peri,Data)                      SET_REG(Peri,Data,CR2)
#define GET_USART_SR(Peri)                            GET_REG(Peri,ST)
#define SET_USART_SR(Peri,Data)                       SET_REG(Peri,Data,ST)
#define GET_USART_DR_TX_ADDR(Peri)                    GET_REG_ADDR(Peri,TDR)
#define GET_USART_DR_RX_ADDR(Peri)                    GET_REG_ADDR(Peri,RDR)
#define SET_USART_CR_BDR(Peri,Data)                   SET_BIT(Peri,Data,USART1n,BDR,BDATA)
#define SET_USART_CR_MODE(Peri,Data)                  SET_BIT(Peri,Data,USART1n,CR1,USTnMS)
#define SET_USART_CR_DLEN(Peri,Data)                  SET_BIT(Peri,Data,USART1n,CR1,USTnS)
#define SET_USART_CR_PARITY(Peri,Data)                SET_BIT(Peri,Data,USART1n,CR1,USTnP)
#define SET_USART_CR_STOPBIT(Peri,Data)               SET_BIT(Peri,Data,USART1n,CR2,USTnSB)
#define SET_USART_CR_EN(Peri,Data)                    SET_BIT(Peri,Data,USART1n,CR2,USTnEN)
#define SET_USART_CR_CPACK(Peri,Data)                 SET_BIT(Peri,Data,USART1n,CR1,CPOLn)
#define SET_USART_CR_CPSCK(Peri,Data)                 SET_BIT(Peri,Data,USART1n,CR1,CPHAn)
#define SET_USART_CR_TXEN(Peri,Data)                  SET_BIT(Peri,Data,USART1n,CR1,TXEn)
#define SET_USART_CR_RXEN(Peri,Data)                  SET_BIT(Peri,Data,USART1n,CR1,RXEn)
#define SET_USART_CR_MS(Peri,Data)                    SET_BIT(Peri,Data,USART1n,CR2,MASTERn)
#define SET_USART_CR_SWAP_MS_PORT(Peri,Data)          SET_BIT(Peri,Data,USART1n,CR2,FXCHn)
#define SET_USART_CR_SSEN(Peri,Data)                  SET_BIT(Peri,Data,USART1n,CR2,USTnSSEN)
#define SET_USART_CR_BIT_ORDER(Peri,Data)             SET_BIT(Peri,Data,USART1n,CR1,ORDn)
#define SET_USART_CR_DISSCK(Peri,Data)                SET_BIT(Peri,Data,USART1n,CR2,DISSCKn)
#define SET_USART_CR_DBLS(Peri,Data)                  SET_BIT(Peri,Data,USART1n,CR2,DBLSn)
#define SET_USART_DR(Peri,Data)                       SET_BIT(Peri,Data,USART1n,TDR,TDATA)
#define GET_USART_DR(Peri)                            GET_BIT(Peri,USART1n,RDR,RDATA)

/* Interrupt Macro */
#define SET_USART_IER_WAKE_EN(Peri,Data)              SET_BIT(Peri,Data,USART1n,CR1,WAKEIEn)
#define SET_USART_IER_TXC_EN(Peri,Data)               SET_BIT(Peri,Data,USART1n,CR1,TXCIEn)
#define GET_USART_IER_TXC_EN(Peri)                    GET_BIT(Peri,USART1n,CR1,TXCIEn)
#define SET_USART_IER_RXC_EN(Peri,Data)               SET_BIT(Peri,Data,USART1n,CR1,RXCIEn)
#define SET_USART_IER_DR_FLAG(Peri,Data)              SET_BIT(Peri,Data,USART1n,ST,DREn)
#define GET_USART_IER_DR_FLAG(Peri)                   GET_BIT(Peri,USART1n,ST,DREn)
#define GET_USART_IER_RXC_FLAG(Peri)                  GET_BIT(Peri,USART1n,ST,RXCn)
#define SET_USART_IER_TXC_FLAG(Peri,Data)             SET_BIT(Peri,Data,USART1n,ST,TXCn)

/* Unused Macro */
#define SET_USART_IER_RTO_EN(Peri,Data)               (void)Peri
#define SET_USART_CR_FPCR(Peri,Data)                  (void)Peri; (void)Data
#define SET_USART_CR_FPCREN(Peri,Data)                (void)Peri; (void)Data
#define SET_USART_IER_DMATXC_EN(Peri,Data)            (void)0
#define SET_USART_IER_DMARXC_EN(Peri,Data)            (void)0
#define SET_USART_CR_TXBIT_NINTH(Peri,Data)           (void)Peri; (void)Data
#define SET_USART_CR_RXBIT_NINTH(Peri,Data)           (void)Peri; (void)Data
#define GET_USART_CR_RXBIT_NINTH(Peri)                (void)0

/* SCU Macro */
typedef SCUCG_Type                                    SCU_Type;
#define SCU_ADDR                                      SCUCG_BASE
#define INTC_REG_BASE                                 INTC_BASE;
#define SCU_USART_PCER(x)                             (x < 2 ? x : x + 2)
#define SET_SCU_USART_PER(Peri,Id,Data)               (void)Peri
#define SET_SCU_USART_PCER(Peri,Id,Data)              SET_BIT_ID(Peri,(SCU_USART_PCER(Id)),Data,SCUCG,PPCLKEN2,UST10CLKE)
#define SET_INTC_IRQ_UNMASK_EN(Peri,Irq,Data)         SET_BIT_ID(Peri,Irq,Data,INTC,MSK,IMSK0_LVI)

/* PCU Macro */
typedef PA_Type                                       PORT_Type;
#define SET_PCU_USART_SS_PIN(Peri,Id,Data)            SET_BIT_ID(Peri,Id,Data,PA,OUTDR,OUTDR0)

#endif /* _HAL_USART_F_01_00_01_H_ */
