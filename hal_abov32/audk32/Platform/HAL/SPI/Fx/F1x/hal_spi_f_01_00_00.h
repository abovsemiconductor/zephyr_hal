/**
 *******************************************************************************
 * @file        hal_spi_f_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed SPI
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_SPI_F_01_00_00_H_
#define _HAL_SPI_F_01_00_00_H_

/* Feature(Function) Configuration Define */
#define SPI_FEATURE_IRQ_UNMASK_ENABLE
#define SPI_FEATURE_ONLY_8BIT_DATA_TX_RX
#define SPI_FEATURE_SWAP_PORT
#define SPI_FEATURE_NOT_SUPPORTED_UNDERRUN_FLAG
#define SPI_FEATURE_NOT_SUPPORTED_OVERRUN_FLAG
#define SPI_FEATURE_NOT_SUPPORTED_SS_DETECT_FLAG
#define SPI_FEATURE_MASTER_SS_PIN_BY_GPIO
#define SPI_FEATURE_DMA_INTERNAL_INTERRUPT
#if (CONFIG_SPI_REG_NAME == 1)
#else
#define SPI_FEATURE_SUPPORT_MULTI_IRQ
#endif

/* Internal Macro */
typedef SPI0_Type                                     SPI_Type;
#define SPI_REG_BASE                                  SPI0_BASE
#define SPI_REG_OFFSET                                0x80
#define SPI_BIT_ORDER(x)                              (x == 1 ? 0 : 1)

/* Bit/Register Macro */
#define SET_SPI_CR_MODE(Peri,Data)                    SET_BIT(Peri,Data,SPI0,CR,SPInMS)
#define SET_SPI_CR_BIT_ORDER(Peri,Data)               SET_BIT(Peri,SPI_BIT_ORDER(Data),SPI0,CR,FLSBn)
#define SET_SPI_CR_CPOL(Peri,Data)                    SET_BIT(Peri,Data,SPI0,CR,CPOLn)
#define SET_SPI_CR_CPHA(Peri,Data)                    SET_BIT(Peri,Data,SPI0,CR,CPHAn)
#define SET_SPI_CR_SS_EN(Peri,Data)                   SET_BIT(Peri,Data,SPI0,SR,SSnEN)
#define SET_SPI_DR_TX(Peri,Data)                      SET_BIT(Peri,Data,SPI0,TDR,TDATA)
#define SET_SPI_DR_RX(Peri,Data)                      SET_BIT(Peri,Data,SPI0,RDR,RDATA)
#define GET_SPI_DR_RX(Peri)                           GET_BIT(Peri,SPI0,RDR,RDATA)
#define SET_SPI_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,SPI0,CR,SPInEN)
#define SET_SPI_CR_BAUDRATE(Peri,Data)                SET_BIT(Peri,Data,SPI0,PREDR,PRED)
#define GET_SPI_SR_TX_IDLE(Peri)                      GET_BIT(Peri,SPI0,SR,SSnHIGH)
#define GET_SPI_SR_TX_RDY(Peri)                       GET_BIT(Peri,SPI0,SR,SSnHIGH)
#define GET_SPI_SR_RX_RDY(Peri)                       GET_BIT(Peri,SPI0,SR,SSnHIGH)
#define GET_SPI_SR_BUSY(Peri)                         1
#define GET_SPI_CR_DATA_BIT(Peri)                     0
#define SET_SPI_CR_SWAP_PORT(Peri,Data)               SET_BIT(Peri,Data,SPI0,SR,FXCHn)
#define GET_SPI_DR_TX_ADDR(Peri)                      GET_REG_ADDR(Peri,TDR)
#define GET_SPI_DR_RX_ADDR(Peri)                      GET_REG_ADDR(Peri,RDR)

/* Interrupt Macro */
#define SET_SPI_IER_TX_EN(Peri,Data)                  SET_BIT(Peri,Data,SPI0,CR,SPInIEN)
#define SET_SPI_IER_RX_EN(Peri,Data)                  SET_BIT(Peri,Data,SPI0,CR,SPInIEN)
#define GET_SPI_IER_FLAG(Peri)                        GET_BIT(Peri,SPI0,SR,SPInIFLAG)
#define SET_SPI_IER_FLAG(Peri,Data)                   SET_BIT(Peri,Data,SPI0,SR,SPInIFLAG)

/* Unused Macro */
#define SET_SPI_CR_TXBUF_CLEAR(Peri)                  (void)0
#define SET_SPI_CR_RXBUF_CLEAR(Peri)                  (void)0
#define SET_SPI_SR_SS_DETECT(Peri,Data)               (void)0
#define SET_SPI_CR_DATA_BIT(Peri,Data)                (void)0 
#define SET_SPI_CR_SS_MANUAL(Peri,Data)               (void)0
#define GET_SPI_SR_TX_UDR(Peri)                       (void)0
#define GET_SPI_SR_RX_OVR(Peri)                       (void)0
#define GET_SPI_SR_SS_DETECT(Peri)                    (void)0
#define SET_SPI_CR_SS_POL(Peri,Data)                  (void)0
#define SET_SPI_CR_DELAY_START(Peri,Data)             (void)0
#define SET_SPI_CR_DELAY_BURST(Peri,Data)             (void)0
#define SET_SPI_CR_DELAY_STOP(Peri,Data)              (void)0
#define GET_SPI_SR_DMATX_DONE(Peri)                   (void)0
#define GET_SPI_SR_DMARX_DONE(Peri)                   (void)0
#define SET_SPI_SR_DMATX_DONE(Peri,Data)              (void)0
#define SET_SPI_SR_DMARX_DONE(Peri,Data)              (void)0
#define SET_SPI_IER_DMATX_EN(Peri,Data)               (void)0
#define SET_SPI_IER_DMARX_EN(Peri,Data)               (void)0

/* PCU Macro */
typedef PA_Type                                       PORT_Type;
#define SET_PCU_SPI_SS_PIN(Peri,Id,Data)              SET_BIT_ID(Peri,Id,Data,PA,OUTDR,OUTDR0)

/* SCU Macro */
typedef SCUCG_Type                                    SCU_Type;
#define SCU_ADDR                                      SCUCG_BASE
#define SET_SCU_SPI_PER(Peri,Id,Data)                 (void)Peri
#define SET_SCU_SPI_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCUCG,PPCLKEN2,SPI0CLKE)
#define SET_INTC_IRQ_UNMASK_EN(Peri,Irq,Data)         SET_BIT_ID(Peri,Irq,Data,INTC,MSK,IMSK0_LVI)
#endif /* _HAL_SPI_F_01_00_00_H_ */
