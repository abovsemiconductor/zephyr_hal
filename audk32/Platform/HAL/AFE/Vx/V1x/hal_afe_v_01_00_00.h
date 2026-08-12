/**
 *******************************************************************************
 * @file        hal_afe_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed AFE
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_AFE_V_01_00_00_H_
#define _HAL_AFE_V_01_00_00_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#define AFE_REG_BASE                                  AFE_BASE
#define AFE_REG_OFFSET                                0x100
#define AFE_CR_REG_OFFSET                             0x04
#define AFE_HYSS_ENABLE(x)                            (x == 0 ? 0 : 1)
#define AFE_HYSS_MODE(x)                              (x > 2 ? 1 : 0)
#define AFE_INTR_ASSERTED(x)                          (1UL << (1 + (x*4)))

/* Bit/Register Macro */
#define SET_AFE_CR_OPAMP_EN(Peri,Id,Data)             SET_BIT_ADDR_OFFSET(Peri,(Id*AFE_CR_REG_OFFSET),Data,AFE,AFE0_CR,OPAEN)
#define SET_AFE_CR_UGAIN_EN(Peri,Id,Data)             SET_BIT_ADDR_OFFSET(Peri,(Id*AFE_CR_REG_OFFSET),Data,AFE,AFE0_CR,UGAINEN)
#define SET_AFE_CR_CMP_EN(Peri,Id,Data)               SET_BIT_ADDR_OFFSET(Peri,(Id*AFE_CR_REG_OFFSET),Data,AFE,AFE0_CR,CMPEN)
#define SET_AFE_CR_CMP_OUTPUT_POL(Peri,Id,Data)           SET_BIT_ADDR_OFFSET(Peri,(Id*AFE_CR_REG_OFFSET),Data,AFE,AFE0_CR,CMPOSEL)
#define SET_AFE_CR_CMP_INTR_TRG(Peri,Id,Data)             SET_BIT_OFFSET(Peri,(Id*4),Data,AFE,CMP_ICR,INTTYPE0)
#define SET_AFE_CR_CMP_INTR_POL(Peri,Id,Data)             SET_BIT_OFFSET(Peri,(Id*4),Data,AFE,CMP_ICR,INTPOL0)

#define SET_AFE_DR_CMP_DBNC_SHIFT(Peri,Id,Data)           SET_BIT_OFFSET(Peri,(Id*4),Data,AFE,CMP_DBR,C0FLTSEL)
#define GET_AFE_DR_CMP_DBNC_SHIFT(Peri,Id)                GET_BIT_OFFSET(Peri,(Id*4),AFE,CMP_DBR,C0FLTSEL)

#define GET_AFE_SR_OUTPUT_FLAG(Peri,Id)               GET_BIT_OFFSET(Peri,(Id*4),AFE,CMP_SR,CMP0FLAG)
#define GET_AFE_SR_RAW_FLAG(Peri,Id)                  GET_BIT_OFFSET(Peri,(Id*4),AFE,CMP_SR,CMP0RFLAG)
#define GET_AFE_SR_EDGE_POL_FLAG(Peri,Id)             GET_BIT_OFFSET(Peri,(Id*4),AFE,CMP_SR,CMP0EPOL)

/* Interrupt Macro */
#define SET_AFE_IER_CMP_EN(Peri,Id,Data)              SET_BIT_ADDR_OFFSET(Peri,(Id*AFE_CR_REG_OFFSET),Data,AFE,AFE0_CR,CMPIEN)
#define GET_AFE_IER_CMP_FLAG(Peri,Id)                 GET_BIT_OFFSET(Peri,(Id*4),AFE,CMP_SR,CMP0INTF)
#define SET_AFE_IER_CMP_FLAG_CLR(Peri,Id,Data)        SET_BIT_OFFSET(Peri,(Id*4),Data,AFE,CMP_SR,CMP0INTF)
#define GET_AFE_IER_SR(Peri)                          GET_REG(Peri,CMP_SR)

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_AFE_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,0,Data,SCU,PER2,AFE)
#define SET_SCU_AFE_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,0,Data,SCU,PCER2,AFE)

#endif /* _HAL_AFE_V_01_00_00_H_ */
