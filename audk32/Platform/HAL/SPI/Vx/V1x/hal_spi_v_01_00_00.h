/**
 *******************************************************************************
 * @file        hal_spi_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed SPI
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_SPI_V_01_00_00_H_
#define _HAL_SPI_V_01_00_00_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#if (CONFIG_SPI_REG_NAME == 0)
typedef SPI20_Type                                    SPI_Type;
#define SPI_REG_BASE                                  SPI20_BASE
#elif (CONFIG_SPI_REG_NAME == 1)

#if (SPI_CH_NUM == 1)
#define SPI_REG_BASE                                  SPI_BASE
#else
#define SPI_REG_BASE                                  SPI0_BASE
#endif

#elif (CONFIG_SPI_REG_NAME == 2)
#define SPI_REG_BASE                                  SPI_BASE

#elif (CONFIG_SPI_REG_NAME == 3)
#define SPI_REG_BASE                                  SPI0_BASE

#endif
#define SPI_REG_OFFSET                                0x100

/* Bit/Register Macro */
#if (CONFIG_SPI_REG_NAME == 0)
#define SET_SPI_BIT(Peri,Data,RegName,BitName)        SET_BIT(Peri,Data,SPI20,RegName,BitName)
#define GET_SPI_BIT(Peri,RegName,BitName)             GET_BIT(Peri,SPI20,RegName,BitName)
#elif (CONFIG_SPI_REG_NAME == 1) || (CONFIG_SPI_REG_NAME == 2) || (CONFIG_SPI_REG_NAME == 3)
#define SET_SPI_BIT(Peri,Data,RegName,BitName)        SET_BIT(Peri,Data,SPI,RegName,BitName)
#define GET_SPI_BIT(Peri,RegName,BitName)             GET_BIT(Peri,SPI,RegName,BitName)
#endif

#define SET_SPI_CR_MODE(Peri,Data)                    SET_SPI_BIT(Peri,Data,CR,MS)
#define SET_SPI_CR_BIT_ORDER(Peri,Data)               SET_SPI_BIT(Peri,Data,CR,MSBF)
#define SET_SPI_CR_CPOL(Peri,Data)                    SET_SPI_BIT(Peri,Data,CR,CPOL)
#define SET_SPI_CR_CPHA(Peri,Data)                    SET_SPI_BIT(Peri,Data,CR,CPHA)
#define SET_SPI_CR_CPHA(Peri,Data)                    SET_SPI_BIT(Peri,Data,CR,CPHA)
#define SET_SPI_CR_SS_MASK(Peri,Data)                 SET_SPI_BIT(Peri,Data,CR,SSMASK)
#define SET_SPI_CR_SS_EN(Peri,Data)                   SET_SPI_BIT(Peri,Data,CR,SSMO)
#define SET_SPI_CR_TXBUF_CLEAR(Peri)                  SET_SPI_BIT(Peri,0x1,CR,TXBC)
#define SET_SPI_CR_RXBUF_CLEAR(Peri)                  SET_SPI_BIT(Peri,0x1,CR,RXBC)
#define SET_SPI_SR_SS_DETECT(Peri,Data)               SET_SPI_BIT(Peri,Data,SR,SSDET)
#define SET_SPI_CR_DATA_BIT(Peri,Data)                SET_SPI_BIT(Peri,Data,CR,BITSZ)
#define GET_SPI_CR_DATA_BIT(Peri)                     GET_SPI_BIT(Peri,CR,BITSZ)
#define SET_SPI_CR_SS_MANUAL(Peri,Data)               SET_SPI_BIT(Peri,Data,CR,SSMOD)
#define GET_SPI_CR_SS_MANUAL(Peri)                    GET_SPI_BIT(Peri,CR,SSMOD)

#define GET_SPI_SR_TX_IDLE(Peri)                      GET_SPI_BIT(Peri,SR,TXIDLE)
#define GET_SPI_SR_TX_RDY(Peri)                       GET_SPI_BIT(Peri,SR,TRDY)
#define GET_SPI_SR_TX_UDR(Peri)                       GET_SPI_BIT(Peri,SR,UDRF)
#define GET_SPI_SR_RX_RDY(Peri)                       GET_SPI_BIT(Peri,SR,RRDY)
#define GET_SPI_SR_RX_OVR(Peri)                       GET_SPI_BIT(Peri,SR,OVRF)
#define GET_SPI_SR_SS_DETECT(Peri)                    GET_SPI_BIT(Peri,SR,SSDET)
#define GET_SPI_SR_BUSY(Peri)                         GET_SPI_BIT(Peri,SR,SBUSY)
#define SET_SPI_DR_TX(Peri,Data)                      SET_SPI_BIT(Peri,Data,TDR,TDR)
#define SET_SPI_DR_RX(Peri,Data)                      SET_SPI_BIT(Peri,Data,RDR,RDR)
#define GET_SPI_DR_RX(Peri)                           GET_SPI_BIT(Peri,RDR,RDR)
#define SET_SPI_CR_SS_POL(Peri,Data)                  SET_SPI_BIT(Peri,Data,CR,SSPOL)

#if (CONFIG_SPI_REG_NAME == 0) || (CONFIG_SPI_REG_NAME == 1) || (CONFIG_SPI_REG_NAME == 3)
#define SET_SPI_CR_BAUDRATE(Peri,Data)                SET_SPI_BIT(Peri,Data,BR,BR)
#define SET_SPI_CR_DELAY_START(Peri,Data)             SET_SPI_BIT(Peri,Data,LR,STL)
#define SET_SPI_CR_DELAY_BURST(Peri,Data)             SET_SPI_BIT(Peri,Data,LR,BTL)
#define SET_SPI_CR_DELAY_STOP(Peri,Data)              SET_SPI_BIT(Peri,Data,LR,SPL)
#define SET_SPI_CR_EN(Peri,Data)                      SET_SPI_BIT(Peri,Data,EN,ENABLE)
#elif (CONFIG_SPI_REG_NAME == 2)
#define SET_SPI_CR_BAUDRATE(Peri,Data)                SET_SPI_BIT(Peri,Data,BDR,BDR)
#define SET_SPI_CR_DELAY_START(Peri,Data)             SET_SPI_BIT(Peri,Data,DTR,STL)
#define SET_SPI_CR_DELAY_BURST(Peri,Data)             SET_SPI_BIT(Peri,Data,DTR,BTL)
#define SET_SPI_CR_DELAY_STOP(Peri,Data)              SET_SPI_BIT(Peri,Data,DTR,SPL)
#define SET_SPI_CR_EN(Peri,Data)                      SET_SPI_BIT(Peri,Data,ER,ENABLE)
#endif

/* Interrupt Macro */
#define SET_SPI_IER_TX_EN(Peri,Data)                  SET_SPI_BIT(Peri,Data,CR,TXIE)
#define SET_SPI_IER_RX_EN(Peri,Data)                  SET_SPI_BIT(Peri,Data,CR,RXIE)
#define GET_SPI_SR_DMATX_DONE(Peri)                   GET_SPI_BIT(Peri,SR,TXDMAF)
#define GET_SPI_SR_DMARX_DONE(Peri)                   GET_SPI_BIT(Peri,SR,RXDMAF)
#define SET_SPI_SR_DMATX_DONE(Peri,Data)              SET_SPI_BIT(Peri,Data,SR,TXDMAF)
#define SET_SPI_SR_DMARX_DONE(Peri,Data)              SET_SPI_BIT(Peri,Data,SR,RXDMAF)

#if (CONFIG_SPI_REG_NAME == 0) || (CONFIG_SPI_REG_NAME == 3)
#define SET_SPI_IER_DMATX_EN(Peri,Data)               SET_SPI_BIT(Peri,Data,CR,TXDIE)
#define SET_SPI_IER_DMARX_EN(Peri,Data)               SET_SPI_BIT(Peri,Data,CR,RXDIE)
#elif (CONFIG_SPI_REG_NAME == 1) || (CONFIG_SPI_REG_NAME == 2)
#define SET_SPI_IER_DMATX_EN(Peri,Data)               SET_SPI_BIT(Peri,Data,CR,DTXIE)
#define SET_SPI_IER_DMARX_EN(Peri,Data)               SET_SPI_BIT(Peri,Data,CR,DRXIE)
#endif

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#if (CONFIG_SPI_REG_NAME == 0)
#define SET_SCU_SPI_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PER2,SPI20)
#define SET_SCU_SPI_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PCER2,SPI20)
#elif (CONFIG_SPI_REG_NAME == 1) || (CONFIG_SPI_REG_NAME == 3)

#if (SPI_CH_NUM == 1)
#define SET_SCU_SPI_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PER2,SPI)
#define SET_SCU_SPI_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PCER2,SPI)
#else
#define SET_SCU_SPI_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PER2,SPI0)
#define SET_SCU_SPI_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PCER2,SPI0)
#endif

#elif (CONFIG_SPI_REG_NAME == 2)
#define SET_SCU_SPI_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PER2,SPI)
#define SET_SCU_SPI_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PCER2,SPI)
#endif

#endif /* _HAL_SPI_V_01_00_00_H_ */
