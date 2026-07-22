/**
 *******************************************************************************
 * @file        hal_qei_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed QEI
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_QEI_V_01_00_00_H_
#define _HAL_QEI_V_01_00_00_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#define QEI_REG_BASE                                  QEI0_BASE
#define QEI_REG_OFFSET                                0x100
#define QEI_POS_CNTER_COMPARE_CNT                     3
#define QEI_POS_COMPARE_REG_OFFSET                    0x04
#define QEI_POS_COMPARE_REG_START                     0x14
#define QEI_COUNTER_CLEAR_MASK                        0x07
#define QEI_VELOCITY_TIMER_CLEAR                      0xFFFF
#define QEI_INTR_BASE_MASK                            0x018F
#define QEI_IDX_GATING(x)                             (x < 4 ? 0x1UL << x : 0x0F)

/* Bit/Register Macro */
#define SET_QEI_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,QEI,MR,QDMOD)
#define SET_QEI_CR_PHA_PHB_SWAP(Peri,Data)            SET_BIT(Peri,Data,QEI,MR,QDSWAP)
#define SET_QEI_CR_SIG_MODE(Peri,Data)                SET_BIT(Peri,Data,QEI,MR,QDSIG)
#define SET_QEI_CR_CAP_CNT_EDGE(Peri,Data)            SET_BIT(Peri,Data,QEI,MR,QDCAP)
#define SET_QEI_CR_POS_CNTER_RST(Peri,Data)           SET_BIT(Peri,Data,QEI,MR,QDRST)
#define SET_QEI_CR_POS_CHANGE_DIR(Peri,Data)          SET_BIT(Peri,Data,QEI,MR,DIRPC)
#define SET_QEI_CR_IDX_CHANGE_DIR(Peri,Data)          SET_BIT(Peri,Data,QEI,MR,DIRI)
#define SET_QEI_CR_VELOCITY_EN(Peri,Data)             SET_BIT(Peri,Data,QEI,MR,QDVEL)
#define SET_QEI_CR_IDX_GATING(Peri,Data)              SET_BIT(Peri,Data,QEI,MR,INXGATE)

#define SET_QEI_CR_IDX_SIG_INVERT(Peri,Data)          SET_BIT(Peri,Data,QEI,CON,INVI)
#define SET_QEI_CR_POS_CNTER_CLEAR(Peri,Data)         SET_BIT(Peri,Data,QEI,CON,RESP)
#define SET_QEI_CR_IDX_CNTER_CLEAR(Peri,Data)         SET_BIT(Peri,Data,QEI,CON,RESI)
#define SET_QEI_CR_VEL_CNTER_CLEAR(Peri,Data)         SET_BIT(Peri,Data,QEI,CON,RESV)
#define GET_QEI_CR_CNTER_CLEAR(Peri)                  GET_REG(Peri,CON)
#define SET_QEI_CR_CNTER_CLEAR(Peri,Data,Mask)        SET_REG_MASK(Peri,Data,Mask,CON)

#define GET_QEI_SR_ERROR(Peri)                        GET_BIT(Peri,QEI,SR,Error)
#define GET_QEI_SR_DIRECTION(Peri)                    GET_BIT(Peri,QEI,SR,Direction)

#define SET_QEI_DR_POS_CNTER(Peri,Data)               SET_REG(Peri,Data,POS)
#define GET_QEI_DR_POS_CNTER(Peri)                    GET_REG(Peri,POS)
#define SET_QEI_DR_POS_MAX(Peri,Data)                 SET_REG(Peri,Data,MAX)
#define GET_QEI_DR_POS_MAX(Peri)                      GET_REG(Peri,MAX)
#define SET_QEI_DR_POS_CMP0(Peri,Data)                SET_REG(Peri,Data,CMP0)
#define GET_QEI_DR_POS_CMP0(Peri)                     GET_REG(Peri,CMP0)
#define SET_QEI_DR_POS_CMP1(Peri,Data)                SET_REG(Peri,Data,CMP1)
#define GET_QEI_DR_POS_CMP1(Peri)                     GET_REG(Peri,CMP1)
#define SET_QEI_DR_POS_CMP2(Peri,Data)                SET_REG(Peri,Data,CMP2)
#define GET_QEI_DR_POS_CMP2(Peri)                     GET_REG(Peri,CMP2)
#define SET_QEI_DR_POS_CMPX(Peri,Id,Data)             SET_BIT_ADDR_OFFSET(Peri,(QEI_POS_COMPARE_REG_START + (Id * QEI_POS_COMPARE_REG_OFFSET)), \
                                                      Data,QEI,CMP0,QEICMP0)

#define SET_QEI_DR_IDX_CNTER(Peri,Data)               SET_REG(Peri,Data,IDX)
#define GET_QEI_DR_IDX_CNTER(Peri)                    GET_REG(Peri,IDX)
#define SET_QEI_DR_IDX_CMP(Peri,Data)                 SET_REG(Peri,Data,CMPI)
#define GET_QEI_DR_IDX_CMP(Peri)                      GET_REG(Peri,CMPI)

#define SET_QEI_DR_VEL_RELOAD(Peri,Data)              SET_REG(Peri,Data,VLR)
#define GET_QEI_DR_VEL_RELOAD(Peri)                   GET_REG(Peri,VLR)
#define SET_QEI_DR_VEL_TIMER(Peri,Data)               SET_REG(Peri,Data,VLT)
#define GET_QEI_DR_VEL_TIMER(Peri)                    GET_REG(Peri,VLT)
#define SET_QEI_DR_VEL_PULSE_CNTER(Peri,Data)         SET_REG(Peri,Data,VLP)
#define GET_QEI_DR_VEL_PULSE_CNTER(Peri)              GET_REG(Peri,VLP)
#define SET_QEI_DR_VEL_CAP(Peri,Data)                 SET_REG(Peri,Data,VLC)
#define GET_QEI_DR_VEL_CAP(Peri)                      GET_REG(Peri,VLC)
#define SET_QEI_DR_VEL_CMP(Peri,Data)                 SET_REG(Peri,Data,VLCOM)
#define GET_QEI_DR_VEL_CMP(Peri)                      GET_REG(Peri,VLCOM)

/* Interrup Bit Macro */
#define SET_QEI_IER_IDX_EN(Peri,Data)                 SET_BIT(Peri,Data,QEI,IER,INXEN)
#define SET_QEI_IER_DIR_EN(Peri,Data)                 SET_BIT(Peri,Data,QEI,IER,DIREN)
#define SET_QEI_IER_ERR_EN(Peri,Data)                 SET_BIT(Peri,Data,QEI,IER,ERREN)
#define SET_QEI_IER_CLK_PULSE_EN(Peri,Data)           SET_BIT(Peri,Data,QEI,IER,ENCLKEN)
#define SET_QEI_IER_POS_CMP0_EN(Peri,Data)            SET_BIT(Peri,Data,QEI,IER,POS0EN)
#define SET_QEI_IER_POS_CMP1_EN(Peri,Data)            SET_BIT(Peri,Data,QEI,IER,POS1EN)
#define SET_QEI_IER_POS_CMP2_EN(Peri,Data)            SET_BIT(Peri,Data,QEI,IER,POS2EN)
#define SET_QEI_IER_POS_CMPX_EN(Peri,Id,Data)         SET_BIT_OFFSET(Peri,Id,Data,QEI,IER,POS0EN)
#define SET_QEI_IER_POS_MAX_EN(Peri,Data)             SET_BIT(Peri,Data,QEI,IER,MAXEN)
#define SET_QEI_IER_IDX_CMP_EN(Peri,Data)             SET_BIT(Peri,Data,QEI,IER,IDXEN)
#define SET_QEI_IER_VEL_TIMER_EN(Peri,Data)           SET_BIT(Peri,Data,QEI,IER,VELTEN)
#define SET_QEI_IER_VEL_CMP_EN(Peri,Data)             SET_BIT(Peri,Data,QEI,IER,VELCEN)
#define SET_QEI_IER(Peri,Data,Mask)                   SET_REG_MASK(Peri,Data,Mask,IER)
#define GET_QEI_IER(Peri)                             GET_REG(Peri,IER)

#define GET_QEI_IER_IDX_FLAG(Peri)                    GET_BIT(Peri,QEI,ISR,INX)
#define GET_QEI_IER_DIR_FLAG(Peri)                    GET_BIT(Peri,QEI,ISR,DIR)
#define GET_QEI_IER_ERR_FLAG(Peri)                    GET_BIT(Peri,QEI,ISR,ERR)
#define GET_QEI_IER_CLK_PULSE_FLAG(Peri,Data)         GET_BIT(Peri,QEI,ISR,ENCLK)
#define GET_QEI_IER_POS_CMP0_FLAG(Peri)               GET_BIT(Peri,QEI,ISR,POS0)
#define GET_QEI_IER_POS_CMP1_FLAG(Peri,Data)          GET_BIT(Peri,QEI,ISR,POS1)
#define GET_QEI_IER_POS_CMP2_FLAG(Peri)               GET_BIT(Peri,QEI,ISR,POS2)
#define GET_QEI_IER_POS_MAX_FLAG(Peri,Data)           GET_BIT(Peri,QEI,ISR,MAX)
#define GET_QEI_IER_IDX_CMP_FLAG(Peri)                GET_BIT(Peri,QEI,ISR,IDX)
#define GET_QEI_IER_VEL_TIMER_FLAG(Peri,Data)         GET_BIT(Peri,QEI,ISR,VELT)
#define GET_QEI_IER_VEL_CMP_FLAG(Peri)                GET_BIT(Peri,QEI,ISR,VELC)
#define GET_QEI_IER_FLAG(Peri)                        GET_REG(Peri,ISR)

#define SET_QEI_IER_IDX_CLEAR(Peri,Data)              SET_BIT(Peri,Data,QEI,ISCR,INX)
#define SET_QEI_IER_DIR_CLEAR(Peri,Data)              SET_BIT(Peri,Data,QEI,ISCR,DIR)
#define SET_QEI_IER_ERR_CLEAR(Peri,Data)              SET_BIT(Peri,Data,QEI,ISCR,ERR)
#define SET_QEI_IER_CLK_PULSE_CLEAR(Peri,Data)        SET_BIT(Peri,Data,QEI,ISCR,ENCLK)
#define SET_QEI_IER_POS_CMP0_CLEAR(Peri,Data)         SET_BIT(Peri,Data,QEI,ISCR,POS0)
#define SET_QEI_IER_POS_CMP1_CLEAR(Peri,Data)         SET_BIT(Peri,Data,QEI,ISCR,POS1)
#define SET_QEI_IER_POS_CMP2_CLEAR(Peri,Data)         SET_BIT(Peri,Data,QEI,ISCR,POS2)
#define SET_QEI_IER_POS_MAX_CLEAR(Peri,Data)          SET_BIT(Peri,Data,QEI,ISCR,MAX)
#define SET_QEI_IER_IDX_CMP_CLEAR(Peri,Data)          SET_BIT(Peri,Data,QEI,ISCR,IDX)
#define SET_QEI_IER_VEL_TIMER_CLEAR(Peri,Data)        SET_BIT(Peri,Data,QEI,ISCR,VELT)
#define SET_QEI_IER_VEL_CMP_CLEAR(Peri,Data)          SET_BIT(Peri,Data,QEI,ISCR,VELC)
#define SET_QEI_IER_CLEAR(Peri,Data)                  SET_REG(Peri,Data,ISCR)
#define GET_QEI_IER_CLEAR(Peri)                       GET_REG(Peri,ISCR)

/* Unused Macro */
               
/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_QEI_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PER1,QEI0)
#define SET_SCU_QEI_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PCER1,QEI0)

#endif /* _HAL_MPWM_V_01_00_00_H_ */
