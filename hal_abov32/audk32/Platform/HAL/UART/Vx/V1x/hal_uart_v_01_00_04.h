/**
 *******************************************************************************
 * @file        hal_uart_v_01_00_04.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.04 typed UART
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_UART_V_01_00_04_H_
#define _HAL_UART_V_01_00_04_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
typedef UART0_Type                                    UART_Type;
#define UART_REG_BASE                                 UART0_BASE
#define UART_REG_OFFSET                               0x40

#define UART_RX_TIMEOUT                               10000

/* Bit/Register Macro */
#define SET_UART_IER(Peri,Data)                       SET_REG(Peri,Data,IER)
#define SET_UART_LCR(Peri,Data)                       SET_REG(Peri,Data,LCR)
#define SET_UART_BFR(Peri,Data)                       SET_REG(Peri,Data,BFR)
#define SET_UART_BDR(Peri,Data)                       SET_BIT(Peri,0x1,UART0,LCR,DLAB); \
                                                      SET_BIT(Peri,(Data & 0xFF),UART0,DLL,DLL); \
                                                      SET_BIT(Peri,((Data>>8) & 0xFF),UART0,DLM,DLM); \
                                                      SET_BIT(Peri,0x0,UART0,LCR,DLAB)
#define GET_UART_LSR(Peri)                            GET_REG(Peri,LSR)
#define GET_UART_IIR(Peri)                            GET_REG(Peri,IIR)
#define SET_UART_LCR_BREAK(Peri,Data)                 SET_BIT(Peri,Data,UART0,LCR,BREAK)
#define GET_UART_LCR_BREAK(Peri)                      GET_BIT(Peri,UART0,LCR,BREAK)
#define SET_UART_LCR_STICKP(Peri,Data)                SET_BIT(Peri,Data,UART0,LCR,STICKP)
#define GET_UART_LCR_STICKP(Peri)                     GET_BIT(Peri,UART0,LCR,STICKP)
#define SET_UART_LCR_PARITY(Peri,Data)                SET_BIT(Peri,Data,UART0,LCR,PARITY)
#define GET_UART_LCR_PARITY(Peri)                     GET_BIT(Peri,UART0,LCR,PARITY)
#define SET_UART_LCR_PEN(Peri,Data)                   SET_BIT(Peri,Data,UART0,LCR,PEN)
#define GET_UART_LCR_PEN(Peri)                        GET_BIT(Peri,UART0,LCR,PEN)
#define GET_UART_LSR_PE(Peri)                         GET_BIT(Peri,UART0,LSR,PE)
#define SET_UART_LCR_STOPBIT(Peri,Data)               SET_BIT(Peri,Data,UART0,LCR,STOPBIT)
#define GET_UART_LCR_STOPBIT(Peri)                    GET_BIT(Peri,UART0,LCR,STOPBIT)
#define SET_UART_LCR_DLEN(Peri,Data)                  SET_BIT(Peri,Data,UART0,LCR,DLEN)
#define SET_UART_LCR_DLEN(Peri,Data)                  SET_BIT(Peri,Data,UART0,LCR,DLEN)
#define GET_UART_LCR_DLEN(Peri)                       GET_BIT(Peri,UART0,LCR,DLEN)
#define SET_UART_DCR_LBON(Peri,Data)                  (void)Peri
#define GET_UART_DCR_LBON(Peri)                       (void)Peri
#define SET_UART_DCR_RXINV(Peri,Data)                 SET_BIT(Peri,Data,UART0,DTR,RXINV)
#define GET_UART_DCR_RXINV(Peri)                      GET_BIT(Peri,UART0,DTR,RXINV)
#define SET_UART_DCR_TXINV(Peri,Data)                 SET_BIT(Peri,Data,UART0,DTR,TXINV)
#define GET_UART_DCR_TXINV(Peri)                      GET_BIT(Peri,UART0,DTR,TXINV)
#define GET_UART_LSR_TEMT(Peri)                       GET_BIT(Peri,UART0,LSR,TEMT)
#define GET_UART_LSR_THRE(Peri)                       GET_BIT(Peri,UART0,LSR,THRE)
#define GET_UART_LSR_BI(Peri)                         GET_BIT(Peri,UART0,LSR,BI)
#define GET_UART_LSR_FE(Peri)                         GET_BIT(Peri,UART0,LSR,FE)
#define GET_UART_LSR_OE(Peri)                         GET_BIT(Peri,UART0,LSR,OE)
#define GET_UART_LSR_DR(Peri)                         GET_BIT(Peri,UART0,LSR,DR)
#define GET_UART_BDR_BDR(Peri)                        GET_BIT(Peri,UART0,BDR,BDR)
#define SET_UART_BFR_BFR(Peri,Data)                   SET_BIT(Peri,Data,UART0,BFR,BFR)
#define GET_UART_BFR_BFR(Peri)                        GET_BIT(Peri,UART0,BFR,BFR)
#define SET_UART_PARITY(Peri,Data)                    SET_UART_LCR_PEN(Peri,1); \
                                                      SET_UART_LCR_PARITY(Peri,Data)
#define SET_UART_RBR_DATA(Peri,Data)                  SET_BIT(Peri,Data,UART0,RBR,RBR)
#define GET_UART_RBR_DATA(Peri)                       GET_BIT(Peri,UART0,RBR,RBR)
#define SET_UART_THR_DATA(Peri,Data)                  SET_BIT(Peri,Data,UART0,THR,THR)
#define GET_UART_THR_DATA(Peri)                       GET_BIT(Peri,UART0,THR,THR)
#define SET_UART_BDR_BDR(Peri,Data)                   SET_BIT(Peri,0x1,UART0,LCR,DLAB); \
                                                      SET_BIT(Peri,(Data & 0xFF),UART0,DLL,DLL); \
                                                      SET_BIT(Peri,((Data>>8) & 0xFF),UART0,DLM,DLM); \
                                                      SET_BIT(Peri,0x0,UART0,LCR,DLAB)
#define SET_UART_IDTR_SMS(Peri,Data)                  SET_BIT(Peri,Data,UART0,DTR,SMS)
#define GET_UART_IDTR_SMS(Peri)                       GET_BIT(Peri,UART0,DTR,SMS)
#define SET_UART_IDTR_DMS(Peri,Data)                  SET_BIT(Peri,Data,UART0,DTR,DMS)
#define GET_UART_IDTR_DMS(Peri)                       GET_BIT(Peri,UART0,DTR,DMS)
#define SET_UART_IDTR_WAITVAL(Peri,Data)              SET_BIT(Peri,Data,UART0,DTR,WAITVAL)
#define GET_UART_IDTR_WAITVAL(Peri)                   GET_BIT(Peri,UART0,DTR,WAITVAL)

/* Interrupt Macro */
#define GET_UART_IIR_TXE(Peri)                        GET_BIT(Peri,UART0,IIR,TXE)
#define GET_UART_IIR_IID(Peri)                        GET_BIT(Peri,UART0,IIR,IID)
#define GET_UART_IIR_IPEN(Peri)                       GET_BIT(Peri,UART0,IIR,IPEN)
#define SET_UART_IER_RLSIE(Peri,Data)                 SET_BIT(Peri,Data,UART0,IER,RLSIE)
#define GET_UART_IER_RLSIE(Peri)                      GET_BIT(Peri,UART0,IER,RLSIE)
#define SET_UART_IER_THREIE(Peri,Data)                SET_BIT(Peri,Data,UART0,IER,THREIE)
#define GET_UART_IER_THREIE(Peri)                     GET_BIT(Peri,UART0,IER,THREIE)
#define SET_UART_IER_DRIE(Peri,Data)                  SET_BIT(Peri,Data,UART0,IER,DRIE)
#define GET_UART_IER_DRIE(Peri)                       GET_BIT(Peri,UART0,IER,DRIE)
#define SET_UART_IER_TXEIE(Peri,Data)                 SET_BIT(Peri,Data,UART0,IER,TXEIE)
#define GET_UART_IER_TXEIE(Peri)                      GET_BIT(Peri,UART0,IER,TXEIE)

/* Unused Macro */
#define SET_UART_DCR(Peri,Data)                       (void)Peri
#define SET_UART_IER_DTXIEN(Peri,Data)                (void)Peri
#define GET_UART_IER_DTXIEN(Peri)                     (void)Peri
#define SET_UART_IER_DRXIEN(Peri,Data)                (void)Peri
#define GET_UART_IER_DRXIEN(Peri)                     (void)Peri
#define GET_UART_IIR_DMAF(Peri)                       (void)Peri

/* SCU Macro */
typedef PMU_Type                                      SCU_Type;
#define SCU_ADDR                                      PMU_BASE
#define SET_SCU_UART_PER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,PMU,PER,UART0)
#define SET_SCU_UART_PCER(Peri,Id,Data)               SET_BIT_ID(Peri,Id,Data,PMU,PCCR,UART0)

#endif /* _HAL_UART_V_01_00_04_H_ */
