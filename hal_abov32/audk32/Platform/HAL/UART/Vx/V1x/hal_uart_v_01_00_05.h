/**
 *******************************************************************************
 * @file        hal_uart_v_01_00_05.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.05 typed UART
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_UART_V_01_00_05_H_
#define _HAL_UART_V_01_00_05_H_

/* Feature(Function) Configuration Define */
#define UART_FEATURE_IRQ_UNMASK_ENABLE
#if (CONFIG_UART_REG_NAME == 1)
#define UART_FEATURE_NO_DIV_BAUDRATE
#endif
#if defined (_DMAC)
#define UART_FEATURE_DMA_INTERNAL_INTERRUPT
#endif

/* Internal Macro */
typedef UARTn_Type                                    UART_Type;
#define UART_REG_BASE                                 UART0_BASE
#define UART_REG_OFFSET                               0x100

#define UART_RX_TIMEOUT                               10000

/* Bit/Register Macro */
#define SET_UART_IER(Peri,Data)                       SET_REG(Peri,Data,IER)
#define SET_UART_LCR(Peri,Data)                       SET_REG(Peri,Data,LCR)
#define SET_UART_BFR(Peri,Data)                       SET_REG(Peri,Data,BFR)
#define SET_UART_BDR(Peri,Data)                       SET_REG(Peri,Data,BDR)
#define SET_UART_DCR(Peri,Data)                       SET_REG(Peri,Data,DCR)
#define GET_UART_LSR(Peri)                            GET_REG(Peri,LSR)
#define GET_UART_IIR(Peri)                            GET_REG(Peri,IIR)
#define SET_UART_LCR_BREAK(Peri,Data)                 SET_BIT(Peri,Data,UARTn,LCR,BREAK)
#define GET_UART_LCR_BREAK(Peri)                      GET_BIT(Peri,UARTn,LCR,BREAK)
#define SET_UART_LCR_STICKP(Peri,Data)                SET_BIT(Peri,Data,UARTn,LCR,STICKP)
#define GET_UART_LCR_STICKP(Peri)                     GET_BIT(Peri,UARTn,LCR,STICKP)
#define SET_UART_LCR_PARITY(Peri,Data)                SET_BIT(Peri,Data,UARTn,LCR,PARITY)
#define GET_UART_LCR_PARITY(Peri)                     GET_BIT(Peri,UARTn,LCR,PARITY)
#define SET_UART_LCR_PEN(Peri,Data)                   SET_BIT(Peri,Data,UARTn,LCR,PEN)
#define GET_UART_LCR_PEN(Peri)                        GET_BIT(Peri,UARTn,LCR,PEN)
#define GET_UART_LSR_PE(Peri)                         GET_BIT(Peri,UARTn,LSR,PE)
#define SET_UART_LCR_STOPBIT(Peri,Data)               SET_BIT(Peri,Data,UARTn,LCR,STOPBIT)
#define GET_UART_LCR_STOPBIT(Peri)                    GET_BIT(Peri,UARTn,LCR,STOPBIT)
#define SET_UART_LCR_DLEN(Peri,Data)                  SET_BIT(Peri,Data,UARTn,LCR,DLEN)
#define SET_UART_LCR_DLEN(Peri,Data)                  SET_BIT(Peri,Data,UARTn,LCR,DLEN)
#define GET_UART_LCR_DLEN(Peri)                       GET_BIT(Peri,UARTn,LCR,DLEN)
#define SET_UART_DCR_LBON(Peri,Data)                  SET_BIT(Peri,Data,UARTn,DCR,LBON)
#define GET_UART_DCR_LBON(Peri)                       GET_BIT(Peri,UARTn,DCR,LBON)
#define SET_UART_DCR_RXINV(Peri,Data)                 SET_BIT(Peri,Data,UARTn,DCR,RXINV)
#define GET_UART_DCR_RXINV(Peri)                      GET_BIT(Peri,UARTn,DCR,RXINV)
#define SET_UART_DCR_TXINV(Peri,Data)                 SET_BIT(Peri,Data,UARTn,DCR,TXINV)
#define GET_UART_DCR_TXINV(Peri)                      GET_BIT(Peri,UARTn,DCR,TXINV)
#define GET_UART_LSR_TEMT(Peri)                       GET_BIT(Peri,UARTn,LSR,TEMT)
#define GET_UART_LSR_THRE(Peri)                       GET_BIT(Peri,UARTn,LSR,THRE)
#define GET_UART_LSR_BI(Peri)                         GET_BIT(Peri,UARTn,LSR,BI)
#define GET_UART_LSR_FE(Peri)                         GET_BIT(Peri,UARTn,LSR,FE)
#define GET_UART_LSR_OE(Peri)                         GET_BIT(Peri,UARTn,LSR,OE)
#define GET_UART_LSR_DR(Peri)                         GET_BIT(Peri,UARTn,LSR,DR)
#define GET_UART_BDR_BDR(Peri)                        GET_BIT(Peri,UARTn,BDR,BDR)
#define SET_UART_BFR_BFR(Peri,Data)                   SET_BIT(Peri,Data,UARTn,BFR,BFR)
#define GET_UART_BFR_BFR(Peri)                        GET_BIT(Peri,UARTn,BFR,BFR)
#define SET_UART_PARITY(Peri,Data)                    SET_UART_LCR_PEN(Peri,1); \
                                                      SET_UART_LCR_PARITY(Peri,Data)
#define SET_UART_RBR_DATA(Peri,Data)                  SET_BIT(Peri,Data,UARTn,RBR,RBR)
#define GET_UART_RBR_DATA(Peri)                       GET_BIT(Peri,UARTn,RBR,RBR)
#define SET_UART_THR_DATA(Peri,Data)                  SET_BIT(Peri,Data,UARTn,THR,THR)
#define GET_UART_THR_DATA(Peri)                       GET_BIT(Peri,UARTn,THR,THR)
#define SET_UART_BDR_BDR(Peri,Data)                   SET_BIT(Peri,Data,UARTn,BDR,BDR)
#define SET_UART_IDTR_SMS(Peri,Data)                  SET_BIT(Peri,Data,UARTn,IDTR,SMS)
#define GET_UART_IDTR_SMS(Peri)                       GET_BIT(Peri,UARTn,IDTR,SMS)
#define SET_UART_IDTR_DMS(Peri,Data)                  SET_BIT(Peri,Data,UARTn,IDTR,DMS)
#define GET_UART_IDTR_DMS(Peri)                       GET_BIT(Peri,UARTn,IDTR,DMS)
#define SET_UART_IDTR_WAITVAL(Peri,Data)              SET_BIT(Peri,Data,UARTn,IDTR,WAITVAL)
#define GET_UART_IDTR_WAITVAL(Peri)                   GET_BIT(Peri,UARTn,IDTR,WAITVAL)

#define GET_UART_TDR_ADDR(Peri)                       GET_REG_ADDR(Peri,THR)
#define GET_UART_RDR_ADDR(Peri)                       GET_REG_ADDR(Peri,RBR)

/* Interrupt Macro */
#define GET_UART_IIR_TXE(Peri)                        GET_BIT(Peri,UARTn,IIR,TXE)
#define GET_UART_IIR_IID(Peri)                        GET_BIT(Peri,UARTn,IIR,IID)
#define GET_UART_IIR_IPEN(Peri)                       GET_BIT(Peri,UARTn,IIR,IPEN)
#define SET_UART_IER_RLSIE(Peri,Data)                 SET_BIT(Peri,Data,UARTn,IER,RLSIE)
#define GET_UART_IER_RLSIE(Peri)                      GET_BIT(Peri,UARTn,IER,RLSIE)
#define SET_UART_IER_THREIE(Peri,Data)                SET_BIT(Peri,Data,UARTn,IER,THREIE)
#define GET_UART_IER_THREIE(Peri)                     GET_BIT(Peri,UARTn,IER,THREIE)
#define SET_UART_IER_TXEIE(Peri,Data)                 SET_BIT(Peri,Data,UARTn,IER,TXEIE)
#define GET_UART_IER_TXEIE(Peri)                      GET_BIT(Peri,UARTn,IER,TXEIE)
#define SET_UART_IER_DRIE(Peri,Data)                  SET_BIT(Peri,Data,UARTn,IER,DRIE)
#define GET_UART_IER_DRIE(Peri)                       GET_BIT(Peri,UARTn,IER,DRIE)

/* Unused Macro */
#define GET_UART_IIR_DMAF(Peri)                       (void)Peri
#define SET_UART_IER_DTXIEN(Peri,Data)                (void)Peri
#define GET_UART_IER_DTXIEN(Peri)                     (void)Peri
#define SET_UART_IER_DRXIEN(Peri,Data)                (void)Peri
#define GET_UART_IER_DRXIEN(Peri)                     (void)Peri

/* SCU Macro */
typedef SCUCG_Type                                    SCU_Type;
#define SCU_ADDR                                      SCUCG_BASE
#define INTC_REG_BASE                                 INTC_BASE;
#define SET_SCU_UART_PER(Peri,Id,Data)                (void)Peri
#define SET_SCU_UART_PCER(Peri,Id,Data)               SET_BIT_ID(Peri,Id,Data,SCUCG,PPCLKEN2,UT0CLKE)
#define SET_INTC_IRQ_UNMASK_EN(Peri,Irq,Data)         SET_BIT_ID(Peri,Irq,Data,INTC,MSK,IMSK0_LVI)

#endif /* _HAL_UART_V_01_00_00_H_ */
