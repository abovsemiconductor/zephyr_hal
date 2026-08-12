/**
 *******************************************************************************
 * @file        hal_uart_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed UART
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_UART_V_01_00_00_H_
#define _HAL_UART_V_01_00_00_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
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
#define SET_UART_LCR_BREAK(Peri,Data)                 SET_BIT(Peri,Data,UART,LCR,BREAK)
#define GET_UART_LCR_BREAK(Peri)                      GET_BIT(Peri,UART,LCR,BREAK)
#define SET_UART_LCR_STICKP(Peri,Data)                SET_BIT(Peri,Data,UART,LCR,STICKP)
#define GET_UART_LCR_STICKP(Peri)                     GET_BIT(Peri,UART,LCR,STICKP)
#define SET_UART_LCR_PARITY(Peri,Data)                SET_BIT(Peri,Data,UART,LCR,PARITY)
#define GET_UART_LCR_PARITY(Peri)                     GET_BIT(Peri,UART,LCR,PARITY)
#define SET_UART_LCR_PEN(Peri,Data)                   SET_BIT(Peri,Data,UART,LCR,PEN)
#define GET_UART_LCR_PEN(Peri)                        GET_BIT(Peri,UART,LCR,PEN)
#define GET_UART_LSR_PE(Peri)                         GET_BIT(Peri,UART,LSR,PE)
#define SET_UART_LCR_STOPBIT(Peri,Data)               SET_BIT(Peri,Data,UART,LCR,STOPBIT)
#define GET_UART_LCR_STOPBIT(Peri)                    GET_BIT(Peri,UART,LCR,STOPBIT)
#define SET_UART_LCR_DLEN(Peri,Data)                  SET_BIT(Peri,Data,UART,LCR,DLEN)
#define SET_UART_LCR_DLEN(Peri,Data)                  SET_BIT(Peri,Data,UART,LCR,DLEN)
#define GET_UART_LCR_DLEN(Peri)                       GET_BIT(Peri,UART,LCR,DLEN)
#define SET_UART_DCR_LBON(Peri,Data)                  SET_BIT(Peri,Data,UART,DCR,LBON)
#define GET_UART_DCR_LBON(Peri)                       GET_BIT(Peri,UART,DCR,LBON)
#define SET_UART_DCR_RXINV(Peri,Data)                 SET_BIT(Peri,Data,UART,DCR,RXINV)
#define GET_UART_DCR_RXINV(Peri)                      GET_BIT(Peri,UART,DCR,RXINV)
#define SET_UART_DCR_TXINV(Peri,Data)                 SET_BIT(Peri,Data,UART,DCR,TXINV)
#define GET_UART_DCR_TXINV(Peri)                      GET_BIT(Peri,UART,DCR,TXINV)
#define GET_UART_LSR_TEMT(Peri)                       GET_BIT(Peri,UART,LSR,TEMT)
#define GET_UART_LSR_THRE(Peri)                       GET_BIT(Peri,UART,LSR,THRE)
#define GET_UART_LSR_BI(Peri)                         GET_BIT(Peri,UART,LSR,BI)
#define GET_UART_LSR_FE(Peri)                         GET_BIT(Peri,UART,LSR,FE)
#define GET_UART_LSR_OE(Peri)                         GET_BIT(Peri,UART,LSR,OE)
#define GET_UART_LSR_DR(Peri)                         GET_BIT(Peri,UART,LSR,DR)
#define GET_UART_BDR_BDR(Peri)                        GET_BIT(Peri,UART,BDR,BDR)
#define SET_UART_BFR_BFR(Peri,Data)                   SET_BIT(Peri,Data,UART,BFR,BFR)
#define GET_UART_BFR_BFR(Peri)                        GET_BIT(Peri,UART,BFR,BFR)
#define SET_UART_PARITY(Peri,Data)                    SET_UART_LCR_PEN(Peri,1); \
                                                      SET_UART_LCR_PARITY(Peri,Data)
#define SET_UART_RBR_DATA(Peri,Data)                  SET_BIT(Peri,Data,UART,RBR,RBR)
#define GET_UART_RBR_DATA(Peri)                       GET_BIT(Peri,UART,RBR,RBR)
#define SET_UART_THR_DATA(Peri,Data)                  SET_BIT(Peri,Data,UART,THR,THR)
#define GET_UART_THR_DATA(Peri)                       GET_BIT(Peri,UART,THR,THR)
#define SET_UART_BDR_BDR(Peri,Data)                   SET_BIT(Peri,Data,UART,BDR,BDR)
#define SET_UART_IDTR_SMS(Peri,Data)                  SET_BIT(Peri,Data,UART,IDTR,SMS)
#define GET_UART_IDTR_SMS(Peri)                       GET_BIT(Peri,UART,IDTR,SMS)
#define SET_UART_IDTR_DMS(Peri,Data)                  SET_BIT(Peri,Data,UART,IDTR,DMS)
#define GET_UART_IDTR_DMS(Peri)                       GET_BIT(Peri,UART,IDTR,DMS)
#define SET_UART_IDTR_WAITVAL(Peri,Data)              SET_BIT(Peri,Data,UART,IDTR,WAITVAL)
#define GET_UART_IDTR_WAITVAL(Peri)                   GET_BIT(Peri,UART,IDTR,WAITVAL)

/* Interrupt Macro */
#define GET_UART_IIR_TXE(Peri)                        GET_BIT(Peri,UART,IIR,TXE)
#define GET_UART_IIR_IID(Peri)                        GET_BIT(Peri,UART,IIR,IID)
#define GET_UART_IIR_IPEN(Peri)                       GET_BIT(Peri,UART,IIR,IPEN)
#define SET_UART_IER_RLSIE(Peri,Data)                 SET_BIT(Peri,Data,UART,IER,RLSIE)
#define GET_UART_IER_RLSIE(Peri)                      GET_BIT(Peri,UART,IER,RLSIE)
#define SET_UART_IER_THREIE(Peri,Data)                SET_BIT(Peri,Data,UART,IER,THREIE)
#define GET_UART_IER_THREIE(Peri)                     GET_BIT(Peri,UART,IER,THREIE)
#define SET_UART_IER_DRIE(Peri,Data)                  SET_BIT(Peri,Data,UART,IER,DRIE)
#define GET_UART_IER_DRIE(Peri)                       GET_BIT(Peri,UART,IER,DRIE)
#define SET_UART_IER_TXEIE(Peri,Data)                 SET_BIT(Peri,Data,UART,IER,TXEIE)
#define GET_UART_IER_TXEIE(Peri)                      GET_BIT(Peri,UART,IER,TXEIE)
#define SET_UART_IER_DTXIEN(Peri,Data)                SET_BIT(Peri,Data,UART,IER,DTXIEN)
#define GET_UART_IER_DTXIEN(Peri)                     GET_BIT(Peri,UART,IER,DTXIEN)
#define SET_UART_IER_DRXIEN(Peri,Data)                SET_BIT(Peri,Data,UART,IER,DRXIEN)
#define GET_UART_IER_DRXIEN(Peri)                     GET_BIT(Peri,UART,IER,DRXIEN)

/* Unused Macro */
#define GET_UART_IIR_DMAF(Peri)                       (void)Peri

/* SCU Macro */
#define SCU_ADDR                                       SCU_BASE
#define SET_SCU_UART_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PER2,UART0)
#define SET_SCU_UART_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PCER2,UART0)

#endif /* _HAL_UART_V_01_00_00_H_ */
