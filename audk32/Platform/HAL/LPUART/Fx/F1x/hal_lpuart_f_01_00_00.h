/**
 *******************************************************************************
 * @file        hal_lpuart_f_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed LPUART
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_LPUART_F_01_00_00_H_
#define _HAL_LPUART_F_01_00_00_H_

/* Feature(Function) Configuration Define */
#define LPUART_FEATURE_IRQ_UNMASK_ENABLE
#define LPUART_FEATURE_SUPPORT_MULTI_IRQ
#define LPUART_FEATURE_DMA_INTERNAL_INTERRUPT

/* Internal Macro */
#if (CONFIG_LPUART_REG_NAME == 1)
#define LPUART_REG_BASE                                 LPUART_BASE
#define LPUART_SET_BIT(A, B, C, D)                      SET_BIT(A, B, LPUART, C, D)
#define LPUART_GET_BIT(A, B, C)                         GET_BIT(A, LPUART, B, C)
#else
typedef LPUARTn_Type                                    LPUART_Type;
#define LPUART_REG_BASE                                 LPUART0_BASE
#define LPUART_SET_BIT(A, B, C, D)                      SET_BIT(A, B, LPUARTn, C, D)
#define LPUART_GET_BIT(A, B, C)                         GET_BIT(A, LPUARTn, B, C)
#endif
#define LPUART_REG_OFFSET                               0x80

#define LPUART_CLK_PCLK                                 0
#define LPUART_CLK_HSI                                  1
#define LPUART_CLK_LSE                                  2
#define LPUART_PPCLKSR(x)                               (x == 1 ? x+1 : 0)
#define LPUART_TX_MASK_BIT                              BIT(2)
#define LPUART_RX_MASK_BIT                              BIT(0)

#define LPUART_RX_TIMEOUT                               10000

/* Bit/Register Macro */
#define SET_LPUART_IER(Peri,Data)                       SET_REG(Peri,Data,IER)
#define SET_LPUART_BDR(Peri,Data)                       SET_REG(Peri,Data,BDR)
#define SET_LPUART_IFSR(Peri,Data)                      SET_REG(Peri,Data,IFSR)
#define GET_LPUART_IFSR(Peri)                           GET_REG(Peri,IFSR)

#define SET_LPUART_CR_EN(Peri,Data)                     LPUART_SET_BIT(Peri,Data,CR1,LPUEN)
#define SET_LPUART_CR_TXEN(Peri,Data)                   LPUART_SET_BIT(Peri,Data,CR1,TXE);
#define SET_LPUART_CR_RXEN(Peri,Data)                   LPUART_SET_BIT(Peri,Data,CR1,RXE);
#define SET_LPUART_CR_DLEN(Peri,Data)                   LPUART_SET_BIT(Peri,Data,CR1,DLEN)
#define SET_LPUART_CR_PARITY_EN(Peri,Data)              LPUART_SET_BIT(Peri,Data,CR1,PEN)
#define SET_LPUART_CR_STICK_PARITY_EN(Peri,Data)        LPUART_SET_BIT(Peri,Data,CR1,STKPEN)
#define SET_LPUART_CR_PARITY(Peri,Data)                 LPUART_SET_BIT(Peri,Data,CR1,PSEL)
#define SET_LPUART_CR_STOPBIT(Peri,Data)                LPUART_SET_BIT(Peri,Data,CR1,STOPB)
#define SET_LPUART_CR_OVS(Peri,Data)                    LPUART_SET_BIT(Peri,Data,CR1,OVRS)
#define SET_LPUART_CR_RTO_EN(Peri,Data)                 LPUART_SET_BIT(Peri,Data,CR2,RTOEN)
#define SET_LPUART_CR_RTO_CNT(Peri,Data)                LPUART_SET_BIT(Peri,Data,RTODR,RTOD)
#define SET_LPUART_CR_DE_STIME(Peri,Data)               LPUART_SET_BIT(Peri,Data,CR2,DEALST)
#define SET_LPUART_CR_DE_FTIME(Peri,Data)               LPUART_SET_BIT(Peri,Data,CR2,DEALFT)
#define SET_LPUART_CR_DE_POL(Peri,Data)                 LPUART_SET_BIT(Peri,Data,CR2,DEPOL)
#define SET_LPUART_CR_DE_EN(Peri,Data)                  LPUART_SET_BIT(Peri,Data,CR2,DEPEN)
#define SET_LPUART_CR_RCD_EN(Peri,Data)                 LPUART_SET_BIT(Peri,Data,CR2,RCDEN)

#define SET_LPUART_BDR_BDR(Peri,Data)                   LPUART_SET_BIT(Peri,Data,BDR,BDATA)
#define GET_LPUART_BDR_BDR(Peri)                        LPUART_GET_BIT(Peri,BDR,BDATA)

#define SET_LPUART_TDR_DATA(Peri,Data)                  LPUART_SET_BIT(Peri,Data,TDR,TDATA)
#define GET_LPUART_TDR_DATA(Peri)                       LPUART_GET_BIT(Peri,TDR,TDATA)
#define SET_LPUART_RDR_DATA(Peri,Data)                  LPUART_SET_BIT(Peri,Data,RDR,RDATA)
#define GET_LPUART_RDR_DATA(Peri)                       LPUART_GET_BIT(Peri,RDR,RDATA)
#define GET_LPUART_TDR_ADDR(Peri)                       GET_REG_ADDR(Peri,TDR)
#define GET_LPUART_RDR_ADDR(Peri)                       GET_REG_ADDR(Peri,RDR)

#define SET_LPUART_IFSR_TXC(Peri,Data)                  LPUART_SET_BIT(Peri,Data,IFSR,TXCIFLAG)
#define GET_LPUART_IFSR_TXC(Peri)                       LPUART_GET_BIT(Peri,IFSR,TXCIFLAG)

#define SET_LPUART_IFSR_RXC(Peri,Data)                  LPUART_SET_BIT(Peri,Data,IFSR,RXCIFLAG)
#define GET_LPUART_IFSR_RXC(Peri)                       LPUART_GET_BIT(Peri,IFSR,RXCIFLAG)

#define GET_LPUART_IFSR_FE(Peri)                        LPUART_GET_BIT(Peri,IFSR,FE)
#define GET_LPUART_IFSR_OE(Peri)                        LPUART_GET_BIT(Peri,IFSR,DOR)

#define GET_LPUART_IFSR_RTO(Peri)                       LPUART_GET_BIT(Peri,IFSR,RTOIFLAG)
#define GET_LPUART_IFSR_RDC(Peri)                       LPUART_GET_BIT(Peri,IFSR,RCDIFLAG)

#if (CONFIG_LPUART_REG_NAME == 1)
#define GET_LPUART_IFSR_PE(Peri)                        GET_BIT(Peri,LPUART,IFSR,PE)
#else
#define GET_LPUART_IFSR_PE(Peri)                        GET_BIT(Peri,LPUARTn,IFSR,PE)
#endif

#define GET_LPUART_IFSR_RXBUSY(Peri)                    LPUART_GET_BIT(Peri,IFSR,RXBUSY)

#define SET_LPUART_LCR_STICKP(Peri,Data)                LPUART_SET_BIT(Peri,Data,LCR,STICKP)
#define GET_LPUART_LCR_STICKP(Peri)                     LPUART_GET_BIT(Peri,LCR,STICKP)
#define GET_LPUART_LCR_PARITY(Peri)                     LPUART_GET_BIT(Peri,LCR,PARITY)
#define SET_LPUART_LCR_PEN(Peri,Data)                   LPUART_SET_BIT(Peri,Data,LCR,PEN)
#define GET_LPUART_LCR_PEN(Peri)                        LPUART_GET_BIT(Peri,LCR,PEN)
#define GET_LPUART_LSR_PE(Peri)                         LPUART_GET_BIT(Peri,LSR,PE)
#define GET_LPUART_LCR_DLEN(Peri)                       LPUART_GET_BIT(Peri,LCR,DLEN)
#define GET_LPUART_LSR_TEMT(Peri)                       LPUART_GET_BIT(Peri,LSR,TEMT)
#define GET_LPUART_LSR_THRE(Peri)                       LPUART_GET_BIT(Peri,LSR,THRE)
#define GET_LPUART_LSR_BI(Peri)                         LPUART_GET_BIT(Peri,LSR,BI)
#define SET_LPUART_BFR_BFR(Peri,Data)                   LPUART_SET_BIT(Peri,Data,BFR,BFR)
#define GET_LPUART_BFR_BFR(Peri)                        LPUART_GET_BIT(Peri,BFR,BFR)
#define SET_LPUART_PARITY(Peri,Data)                    SET_LPUART_LCR_PEN(Peri,1); \
                                                        SET_LPUART_LCR_PARITY(Peri,Data)
#define SET_LPUART_IDTR_SMS(Peri,Data)                  LPUART_SET_BIT(Peri,Data,IDTR,SMS)
#define GET_LPUART_IDTR_SMS(Peri)                       LPUART_GET_BIT(Peri,IDTR,SMS)
#define SET_LPUART_IDTR_DMS(Peri,Data)                  LPUART_SET_BIT(Peri,Data,IDTR,DMS)
#define GET_LPUART_IDTR_DMS(Peri)                       LPUART_GET_BIT(Peri,IDTR,DMS)
#define SET_LPUART_IDTR_WAITVAL(Peri,Data)              LPUART_SET_BIT(Peri,Data,IDTR,WAITVAL)
#define GET_LPUART_IDTR_WAITVAL(Peri)                   LPUART_GET_BIT(Peri,IDTR,WAITVAL)

#define SET_LPUART_BCMP_SIGN(Peri,Data)                 LPUART_SET_BIT(Peri,Data,BCMP,BCMPS)
#define SET_LPUART_BCMP_BIT(Peri,Data)                  LPUART_SET_BIT(Peri,(Data & 0x1FFF),BCMP,BCMP0)

#define SET_LPUART_RCDR_DATA(Peri,Data)                 LPUART_SET_BIT(Peri,Data,RCDR,RCDD)

#define SET_LPUART_DLYDR_DATA(Peri,Data)                LPUART_SET_BIT(Peri,Data,DLYDR,DLYD)

/* Interrupt Macro */
#define SET_LPUART_IER_TXC(Peri,Data)                   LPUART_SET_BIT(Peri,Data,IER,TXCIEN)
#define GET_LPUART_IER_TXC(Peri)                        LPUART_GET_BIT(Peri,IER,TXCIEN)
#define SET_LPUART_IER_RXC(Peri,Data)                   LPUART_SET_BIT(Peri,Data,IER,RXCIEN)
#define GET_LPUART_IER_RXC(Peri)                        LPUART_GET_BIT(Peri,IER,RXCIEN)

#define SET_LPUART_IER_DRIE(Peri,Data)                  LPUART_SET_BIT(Peri,Data,IER,DRIE)
#define GET_LPUART_IER_DRIE(Peri)                       LPUART_GET_BIT(Peri,IER,DRIE)

#define SET_LPUART_IER_RTO_EN(Peri,Data)                LPUART_SET_BIT(Peri,Data,IER,RTOIEN)

#define SET_LPUART_IER_RCD_EN(Peri,Data)                LPUART_SET_BIT(Peri,Data,IER,RCDIEN)

/* Unused Macro */
#define GET_LPUART_IIR_DMAF(Peri)                       (void)Peri
#define GET_LPUART_LSR(Peri)                            (void)Peri
#define SET_LPUART_LCR(Peri,Data)                       (void)0
#define SET_LPUART_BFR(Peri,Data)                       (void)0
#define SET_LPUART_DCR(Peri,Data)                       (void)0
#define SET_LPUART_IER_DTXIEN(Peri,Data)                (void)Peri
#define GET_LPUART_IER_DTXIEN(Peri)                     (void)Peri
#define SET_LPUART_IER_DRXIEN(Peri,Data)                (void)Peri
#define GET_LPUART_IER_DRXIEN(Peri)                     (void)Peri

/* SCU Macro */
typedef SCUCG_Type                                      SCU_Type;
#define SCU_ADDR                                        SCUCG_BASE
#define INTC_REG_BASE                                   INTC_BASE;
#define SET_SCU_LPUART_PER(Peri,Id,Data)                (void)Peri
#define SET_INTC_IRQ_UNMASK_EN(Peri,Data)               SET_BIT_ID(Peri,25,Data,INTC,MSK,IMSK0_LVI)
#define GET_SCU_HSI_CLK_SEL(Peri)                       GET_BIT(Peri,SCUCG,CLKSRCR,HIRCSEL)

#if (CONFIG_LPUART_REG_NAME == 1)
#define SET_SCU_LPUART_PCER(Peri,Id,Data)               SET_BIT_ID(Peri,Id,Data,SCUCG,PPCLKEN2,LPUTCLKE)
#define SET_SCU_LPUART_CLK_SEL(Peri,Id,Data)            SET_BIT_ID(Peri,LPUART_PPCLKSR(Id),Data,SCUCG,PPCLKSR,LPUTCLK)
#define GET_SCU_LPUART_CLK_SEL(Peri,Id)                 GET_BIT_OFFSET(Peri,LPUART_PPCLKSR(Id),SCUCG,PPCLKSR,LPUTCLK)
#define SET_SCU_LPUART_RST(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCUCG,PPRST2,LPUTRST)
#else
#define SET_SCU_LPUART_PCER(Peri,Id,Data)               SET_BIT_ID(Peri,Id,Data,SCUCG,PPCLKEN2,LPUT0CLKE)
#define SET_SCU_LPUART_CLK_SEL(Peri,Id,Data)            SET_BIT_ID(Peri,LPUART_PPCLKSR(Id),Data,SCUCG,PPCLKSR,LPUT0CLK)
#define GET_SCU_LPUART_CLK_SEL(Peri,Id)                 GET_BIT_OFFSET(Peri,LPUART_PPCLKSR(Id),SCUCG,PPCLKSR,LPUT0CLK)
#define SET_SCU_LPUART_RST(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCUCG,PPRST2,LPUT0RST)
#endif

#endif /* _HAL_LPUART_F_01_00_00_H_ */
