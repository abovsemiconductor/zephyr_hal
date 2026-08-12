/**
 *******************************************************************************
 * @file        hal_QSPI_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed QSPI
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_QSPI_V_01_00_00_H_
#define _HAL_QSPI_V_01_00_00_H_

/* Feature(Function) Configuration Define */
/* Internal Macro */
#define QSPI_REG_BASE                                   QSPI_BASE
#define QSPI_REG_OFFSET                                 0x0
#define QSPI_PHASE_BITWIDTH(x)                          (x * 8)

/* Bit/Register Macro */
#define SET_QSPI_BIT(Peri,Data,RegName,BitName)         SET_BIT(Peri,Data,QSPI,RegName,BitName)
#define GET_QSPI_BIT(Peri,RegName,BitName)              GET_BIT(Peri,QSPI,RegName,BitName)

#define SET_QSPI_GCR_SW_RESET(Peri,Data)                SET_QSPI_BIT(Peri,Data,GCR,SWRST)
#define SET_QSPI_GCR_DMA_EN(Peri,Data)                  SET_QSPI_BIT(Peri,Data,GCR,DMAEN)

#define SET_QSPI_CLKCFGR_PRD(Peri,Data)                 SET_QSPI_BIT(Peri,Data,CLKCFGR,PRD)
#define SET_QSPI_CLKCFGR_MINCSL(Peri,Data)              SET_QSPI_BIT(Peri,Data,CLKCFGR,MINCSL)
#define SET_QSPI_CLKCFGR_SP(Peri,Data)                  SET_QSPI_BIT(Peri,Data,CLKCFGR,SP)
#define SET_QSPI_CLKCFGR_TRANS(Peri,Data)               SET_QSPI_BIT(Peri,Data,CLKCFGR,TRANS)
#define SET_QSPI_CLKCFGR_CPOL(Peri,Data)                SET_QSPI_BIT(Peri,Data,CLKCFGR,CPOL)
#define SET_QSPI_MINCSHR_MINCSH(Peri,Data)              SET_QSPI_BIT(Peri,Data,MINCSHR,MINCSHR)
#define SET_QSPI_CSR_CS(Peri,Data)                      SET_QSPI_BIT(Peri,Data,CSR,CS)
#define SET_QSPI_HTR_TIME(Peri,Data)                    SET_QSPI_BIT(Peri,Data,HTR,TIME)

#define GET_QSPI_FSR_EMPTY(Peri)                        GET_QSPI_BIT(Peri,FSR,EMPTY)

#define GET_QSPI_SR_RDY(Peri)                           GET_QSPI_BIT(Peri,SR,RDY)
#define GET_QSPI_SR_BUSY(Peri)                          GET_QSPI_BIT(Peri,SR,BUSY)
#define GET_QSPI_SR_RX_RDY(Peri)                        GET_QSPI_BIT(Peri,SR,FRER)
#define GET_QSPI_SR_TX_RDY(Peri)                        GET_QSPI_BIT(Peri,SR,FWER)
#define GET_QSPI_SR_RX_ERR(Peri)                        GET_QSPI_BIT(Peri,SR,FRERR)
#define GET_QSPI_SR_TX_ERR(Peri)                        GET_QSPI_BIT(Peri,SR,FWERR)
#define SET_QSPI_SR_RX_ERR(Peri,Data)                   SET_QSPI_BIT(Peri,Data,SR,FRERR)
#define SET_QSPI_SR_TX_ERR(Peri,Data)                   SET_QSPI_BIT(Peri,Data,SR,FWERR)

#define SET_QSPI_IER_NOT_BUSY_EN(Peri,Data)             SET_QSPI_BIT(Peri,Data,ICR,NBUSYIE)
#define SET_QSPI_IER_RX_EN(Peri,Data)                   SET_QSPI_BIT(Peri,Data,ICR,FRFILLIE)
#define SET_QSPI_IER_TX_EN(Peri,Data)                   SET_QSPI_BIT(Peri,Data,ICR,FWFILLIE)
#define SET_QSPI_IER_RX_ERR_EN(Peri,Data)               SET_QSPI_BIT(Peri,Data,ICR,FRERRIE)
#define SET_QSPI_IER_TX_ERR_EN(Peri,Data)               SET_QSPI_BIT(Peri,Data,ICR,FWERRIE)
#define SET_QSPI_IER_DMA_IDLE_EN(Peri,Data)             SET_QSPI_BIT(Peri,Data,ICR,DIDLEIE)
#define SET_QSPI_IER_DMA_EN(Peri,Data)                  SET_QSPI_BIT(Peri,Data,ICR,DIE)
#define SET_QSPI_IER_DMA_ERR_EN(Peri,Data)              SET_QSPI_BIT(Peri,Data,ICR,DERRIE)

#define SET_QSPI_CMD_COMMAND(Peri,Data)                 SET_QSPI_BIT(Peri,Data,CMDR,CMD)
#define SET_QSPI_CMD_DURATION(Peri,Data)                SET_QSPI_BIT(Peri,Data,CMDATR,DUR)
#define SET_QSPI_CMD_MODE(Peri,Data)                    SET_QSPI_BIT(Peri,Data,CMDATR,MODE)
#define SET_QSPI_CMD_DDR(Peri,Data)                     SET_QSPI_BIT(Peri,Data,CMDATR,DDR)
#define SET_QSPI_CMD_SKIP(Peri,Data)                    SET_QSPI_BIT(Peri,Data,CMDATR,SKIP)
#define SET_QSPI_ADDR_ADDRESS(Peri,Data)                SET_QSPI_BIT(Peri,Data,AR,ADDR)
#define SET_QSPI_ADDR_DURATION(Peri,Data)               SET_QSPI_BIT(Peri,Data,AATR,DUR)
#define SET_QSPI_ADDR_MODE(Peri,Data)                   SET_QSPI_BIT(Peri,Data,AATR,MODE)
#define SET_QSPI_ADDR_DDR(Peri,Data)                    SET_QSPI_BIT(Peri,Data,AATR,DDR)
#define SET_QSPI_ADDR_SKIP(Peri,Data)                   SET_QSPI_BIT(Peri,Data,AATR,SKIP)
#define SET_QSPI_ADDR_MASK(Peri,Data)                   SET_QSPI_BIT(Peri,Data,AATR,MSK)
#define SET_QSPI_MBR_MODE(Peri,Data)                    SET_QSPI_BIT(Peri,Data,MBR,MODE)
#define SET_QSPI_MBITS_DURATION(Peri,Data)              SET_QSPI_BIT(Peri,Data,MBATR,DUR)
#define SET_QSPI_MBITS_MODE(Peri,Data)                  SET_QSPI_BIT(Peri,Data,MBATR,MODE)
#define SET_QSPI_MBITS_DDR(Peri,Data)                   SET_QSPI_BIT(Peri,Data,MBATR,DDR)
#define SET_QSPI_MBITS_SKIP(Peri,Data)                  SET_QSPI_BIT(Peri,Data,MBATR,SKIP)
#define SET_QSPI_DMY_DURATION(Peri,Data)                SET_QSPI_BIT(Peri,Data,DMYATR,DUR)
#define SET_QSPI_DMY_SKIP(Peri,Data)                    SET_QSPI_BIT(Peri,Data,DMYATR,SKIP)
#define SET_QSPI_DMY_NO_W_LATENCY(Peri,Data)            SET_QSPI_BIT(Peri,Data,DMYATR,NO_WRLAT)
#define SET_QSPI_DATA_SIZE(Peri,Data)                   SET_QSPI_BIT(Peri,Data,DSZR,SIZE)
#define SET_QSPI_DATA_MODE(Peri,Data)                   SET_QSPI_BIT(Peri,Data,DATR,MODE)
#define SET_QSPI_DATA_DDR(Peri,Data)                    SET_QSPI_BIT(Peri,Data,DATR,DDR)
#define SET_QSPI_DATA_FLIP(Peri,Data)                   SET_QSPI_BIT(Peri,Data,DATR,FLIP)
#define SET_QSPI_DATA_SKIP(Peri,Data)                   SET_QSPI_BIT(Peri,Data,DATR,SKIP)
#define SET_QSPI_DATA_DIRECTION(Peri,Data)              SET_QSPI_BIT(Peri,Data,DATR,DIR)

#define SET_QSPI_DATA_TX(Peri,Data)                     SET_QSPI_BIT(Peri,Data,TDR,TDR)
#define GET_QSPI_DATA_RX(Peri)                          GET_QSPI_BIT(Peri,RDR,RDR)

#define GET_QSPI_DATA_RX_ADDR(Peri)                     GET_REG_ADDR(Peri,RDR)

#define SET_QSPI_XIPCMD_COMMAND(Peri,Data)              SET_QSPI_BIT(Peri,Data,XIPCMDR,RCMD)
#define SET_QSPI_XIPCMD_DURATION(Peri,Data)             SET_QSPI_BIT(Peri,Data,XIPCMDATR,DUR)
#define SET_QSPI_XIPCMD_MODE(Peri,Data)                 SET_QSPI_BIT(Peri,Data,XIPCMDATR,MODE)
#define SET_QSPI_XIPCMD_DDR(Peri,Data)                  SET_QSPI_BIT(Peri,Data,XIPCMDATR,DDR)
#define SET_QSPI_XIPCMD_SKIP(Peri,Data)                 SET_QSPI_BIT(Peri,Data,XIPCMDATR,SKIP)
#define SET_QSPI_XIPADDR_ADDRESS(Peri,Data)             SET_QSPI_BIT(Peri,Data,XIPBAR,ADDR)
#define SET_QSPI_XIPADDR_DURATION(Peri,Data)            SET_QSPI_BIT(Peri,Data,XIPAATR,DUR)
#define SET_QSPI_XIPADDR_MODE(Peri,Data)                SET_QSPI_BIT(Peri,Data,XIPAATR,MODE)
#define SET_QSPI_XIPADDR_DDR(Peri,Data)                 SET_QSPI_BIT(Peri,Data,XIPAATR,DDR)
#define SET_QSPI_XIPADDR_SKIP(Peri,Data)                SET_QSPI_BIT(Peri,Data,XIPAATR,SKIP)
#define SET_QSPI_XIPADDR_MASK(Peri,Data)                SET_QSPI_BIT(Peri,Data,XIPAATR,MSK)
#define SET_QSPI_XIPMBR_MODE(Peri,Data)                 SET_QSPI_BIT(Peri,Data,XIPMBR,MODE)
#define SET_QSPI_XIPMBITS_DURATION(Peri,Data)           SET_QSPI_BIT(Peri,Data,XIPMBATR,DUR)
#define SET_QSPI_XIPMBITS_MODE(Peri,Data)               SET_QSPI_BIT(Peri,Data,XIPMBATR,MODE)
#define SET_QSPI_XIPMBITS_DDR(Peri,Data)                SET_QSPI_BIT(Peri,Data,XIPMBATR,DDR)
#define SET_QSPI_XIPMBITS_SKIP(Peri,Data)               SET_QSPI_BIT(Peri,Data,XIPMBATR,SKIP)
#define SET_QSPI_XIPDMY_DURATION(Peri,Data)             SET_QSPI_BIT(Peri,Data,XIPDMYATR,DUR)
#define SET_QSPI_XIPDMY_SKIP(Peri,Data)                 SET_QSPI_BIT(Peri,Data,XIPDMYATR,SKIP)
#define SET_QSPI_XIPDMY_NO_W_LATENCY(Peri,Data)         SET_QSPI_BIT(Peri,Data,XIPDMYATR,NO_WRLAT)
#define SET_QSPI_XIPDATA_MODE(Peri,Data)                SET_QSPI_BIT(Peri,Data,XIPDATR,MODE)
#define SET_QSPI_XIPDATA_DDR(Peri,Data)                 SET_QSPI_BIT(Peri,Data,XIPDATR,DDR)
#define SET_QSPI_XIPDATA_FLIP(Peri,Data)                SET_QSPI_BIT(Peri,Data,XIPDATR,FLIP)

#define SET_QSPI_DMASTAR_ADDR(Peri,Data)                SET_QSPI_BIT(Peri,Data,DMASTAR,ADDR)
#define SET_QSPI_DMAFBLSR(Peri,Data)                    SET_QSPI_BIT(Peri,Data,DMAFBLSR,LEN)
#define GET_QSPI_DMASR_IDLE(Peri)                       GET_QSPI_BIT(Peri,DMASR,IDLE)
#define SET_QSPI_DMASR_IRQ(Peri,Data)                   SET_QSPI_BIT(Peri,Data,DMASR,DIRQ)
#define GET_QSPI_DMASR_IRQ(Peri)                        GET_QSPI_BIT(Peri,DMASR,DIRQ)
#define SET_QSPI_DMASR_ERR(Peri,Data)                   SET_QSPI_BIT(Peri,Data,DMASR,DERR)
#define GET_QSPI_DMASR_ERR(Peri)                        GET_QSPI_BIT(Peri,DMASR,DERR)
#define GET_QSPI_DMABDCNTR_CNT(Peri)                    GET_QSPI_BIT(Peri,DMABDCNTR,CNT)

/* Interrupt Macro */

/* SCU Macro */
#define SCU_ADDR                                        SCU_BASE
#define SET_SCU_QSPI_PER(Peri,Id,Data)                  SET_BIT_ID(Peri,Id,Data,SCU,PER3,QSPI)
#define SET_SCU_QSPI_PCER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PCER3,QSPI)
#define SET_SCU_QSPI_PRER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PRER3,QSPI)

#endif /* _HAL_QSPI_V_01_00_00_H_ */
