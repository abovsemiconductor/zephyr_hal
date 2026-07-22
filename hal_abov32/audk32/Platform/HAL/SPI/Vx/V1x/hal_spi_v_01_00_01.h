/**
 *******************************************************************************
 * @file        hal_spi_v_01_00_01.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.01 typed SPI
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_SPI_V_01_00_01_H_
#define _HAL_SPI_V_01_00_01_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#if (CONFIG_SPI_REG_NAME == 0)
typedef SPI20_Type                                    SPI_Type;
#elif (CONFIG_SPI_REG_NAME == 1)
#endif
#define SPI_REG_BASE                                  SPI20_BASE
#define SPI_REG_OFFSET                                0x100

/* Bit/Register Macro */
#define SET_SPI_CR_MODE(Peri,Data)                    SET_BIT(Peri,Data,SPI20,CR,MS)
#define SET_SPI_CR_BIT_ORDER(Peri,Data)               SET_BIT(Peri,Data,SPI20,CR,MSBF)
#define SET_SPI_CR_CPOL(Peri,Data)                    SET_BIT(Peri,Data,SPI20,CR,CPOL)
#define SET_SPI_CR_CPHA(Peri,Data)                    SET_BIT(Peri,Data,SPI20,CR,CPHA)
#define SET_SPI_CR_CPHA(Peri,Data)                    SET_BIT(Peri,Data,SPI20,CR,CPHA)
#define SET_SPI_CR_SS_MASK(Peri,Data)                 SET_BIT(Peri,Data,SPI20,CR,SSMASK)
#define SET_SPI_CR_SS_EN(Peri,Data)                   SET_BIT(Peri,Data,SPI20,CR,SSMO)
#define SET_SPI_CR_TXBUF_CLEAR(Peri)                  SET_BIT(Peri,0x1,SPI20,CR,TXBC)
#define SET_SPI_CR_RXBUF_CLEAR(Peri)                  SET_BIT(Peri,0x1,SPI20,CR,RXBC)
#define SET_SPI_SR_SS_DETECT(Peri,Data)               SET_BIT(Peri,Data,SPI20,SR,SSDET)
#define SET_SPI_CR_BAUDRATE(Peri,Data)                SET_BIT(Peri,Data,SPI20,BR,BR)
#define SET_SPI_CR_DELAY_START(Peri,Data)             SET_BIT(Peri,Data,SPI20,LR,STL)
#define SET_SPI_CR_DELAY_BURST(Peri,Data)             SET_BIT(Peri,Data,SPI20,LR,BTL)
#define SET_SPI_CR_DELAY_STOP(Peri,Data)              SET_BIT(Peri,Data,SPI20,LR,SPL)
#define SET_SPI_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,SPI20,EN,ENABLE)
#define SET_SPI_CR_DATA_BIT(Peri,Data)                SET_BIT(Peri,Data,SPI20,CR,BITSZ)
#define GET_SPI_CR_DATA_BIT(Peri)                     GET_BIT(Peri,SPI20,CR,BITSZ)
#define SET_SPI_CR_SS_MANUAL(Peri,Data)               SET_BIT(Peri,Data,SPI20,CR,SSMOD)
#define GET_SPI_CR_SS_MANUAL(Peri)                    GET_BIT(Peri,SPI20,CR,SSMOD)
#define GET_SPI_SR_TX_IDLE(Peri)                      GET_BIT(Peri,SPI20,SR,TXIDLE)
#define GET_SPI_SR_TX_RDY(Peri)                       GET_BIT(Peri,SPI20,SR,TRDY)
#define GET_SPI_SR_TX_UDR(Peri)                       GET_BIT(Peri,SPI20,SR,UDRF)
#define GET_SPI_SR_RX_RDY(Peri)                       GET_BIT(Peri,SPI20,SR,RRDY)
#define GET_SPI_SR_RX_OVR(Peri)                       GET_BIT(Peri,SPI20,SR,OVRF)
#define GET_SPI_SR_SS_DETECT(Peri)                    GET_BIT(Peri,SPI20,SR,SSDET)
#define SET_SPI_DR_TX(Peri,Data)                      SET_BIT(Peri,Data,SPI20,TDR,TDR)
#define SET_SPI_DR_RX(Peri,Data)                      SET_BIT(Peri,Data,SPI20,RDR,RDR)
#define GET_SPI_DR_RX(Peri)                           GET_BIT(Peri,SPI20,RDR,RDR)
#define GET_SPI_SR_BUSY(Peri)                         1
#define SET_SPI_CR_SS_POL(Peri,Data)                  SET_BIT(Peri,Data,SPI20,CR,SSPOL)

/* Interrupt Macro */
#define SET_SPI_IER_TX_EN(Peri,Data)                  SET_BIT(Peri,Data,SPI20,CR,TXIE)
#define SET_SPI_IER_RX_EN(Peri,Data)                  SET_BIT(Peri,Data,SPI20,CR,RXIE)
#define SET_SPI_IER_DMATX_EN(Peri,Data)               SET_BIT(Peri,Data,SPI20,CR,TXDIE)
#define SET_SPI_IER_DMARX_EN(Peri,Data)               SET_BIT(Peri,Data,SPI20,CR,RXDIE)
#define GET_SPI_SR_DMATX_DONE(Peri)                   GET_BIT(Peri,SPI20,SR,TXDMAF)
#define GET_SPI_SR_DMARX_DONE(Peri)                   GET_BIT(Peri,SPI20,SR,RXDMAF)
#define SET_SPI_SR_DMATX_DONE(Peri,Data)              SET_BIT(Peri,Data,SPI20,SR,TXDMAF)
#define SET_SPI_SR_DMARX_DONE(Peri,Data)              SET_BIT(Peri,Data,SPI20,SR,RXDMAF)

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_SPI_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PER2,SPI20)
#define SET_SCU_SPI_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PCER2,SPI20)

#endif /* _HAL_SPI_V_01_00_01_H_ */
