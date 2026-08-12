/**
 *******************************************************************************
 * @file        hal_mpwm_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed MPWM
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_MPWM_V_01_00_00_H_
#define _HAL_MPWM_V_01_00_00_H_

/* Feature(Function) Configuration Define */
#define MPWM_FEATURE_NMI

/* Internal Macro */
#define MPWM_REG_BASE                                 MPWM_BASE
#define MPWM_REG_OFFSET                               0x100
#define MPWM_REG_OFFSET_CNT                           0
#define MPWM_ADCTRG_REG_OFFSET                        4
#define MPWM_IRQ_OFFSET                               5

#define MPWM_CLK_SRC_INT                              0x00
#define MPWM_CLK_SRC_EXT                              0x01
#define MPWM_CLK_MCCR_SRC_LSI                         0x00
#define MPWM_CLK_MCCR_SRC_LSE                         0x03
#define MPWM_CLK_MCCR_SRC_MCLK                        0x04
#define MPWM_CLK_MCCR_SRC_HSI                         0x05
#define MPWM_CLK_MCCR_SRC_HSE                         0x06
#define MPWM_CLK_MCCR_SRC_PLL                         0x07

#define MPWM_PROTECTION_ACCESS_KEY                    0xCA
#define MPWM_PROTECTION_ACCESS_KEY_OFFSET             8
#define MPWM_OVERVOLTAGE_ACCESS_KEY                   0xAC
#define MPWM_OVERVOLTAGE_ACCESS_KEY_OFFSET            8
#define MPWM_MCCR_BIT_OFFSET                          16

#define MPWM_INTR_SIG_UL_MSK                          0x0001
#define MPWM_INTR_SIG_UH_MSK                          0x0008
#define MPWM_INTR_SIG_U_BOTTOM_MSK                    0x0040
#define MPWM_INTR_SIG_U_PERIOD_MSK                    0x0080

#define MPWM_INTR_SIG_VL_MSK                          0x0002
#define MPWM_INTR_SIG_VH_MSK                          0x0010
#define MPWM_INTR_SIG_V_BOTTOM_MSK                    0x0100
#define MPWM_INTR_SIG_V_PERIOD_MSK                    0x0200

#define MPWM_INTR_SIG_WL_MSK                          0x0004
#define MPWM_INTR_SIG_WH_MSK                          0x0020
#define MPWM_INTR_SIG_W_BOTTOM_MSK                    0x0400
#define MPWM_INTR_SIG_W_PERIOD_MSK                    0x0800

#define MPWM_INTR_ATR1_MSK                            0x0001
#define MPWM_INTR_ATR2_MSK                            0x0002
#define MPWM_INTR_ATR3_MSK                            0x0004
#define MPWM_INTR_ATR4_MSK                            0x0008
#define MPWM_INTR_ATR5_MSK                            0x0010
#define MPWM_INTR_ATR6_MSK                            0x0020

#define MPWM_INTR_PROT_SIG_UL_MSK                     0x0001
#define MPWM_INTR_PROT_SIG_VL_MSK                     0x0002
#define MPWM_INTR_PROT_SIG_WL_MSK                     0x0004
#define MPWM_INTR_PROT_SIG_UH_MSK                     0x0008
#define MPWM_INTR_PROT_SIG_VH_MSK                     0x0010
#define MPWM_INTR_PROT_SIG_WH_MSK                     0x0020
#define MPWM_INTR_PROT_BASE_MSK                       0x0080

#define MPWM_INTR_OV_SIG_UL_MSK                       0x0001
#define MPWM_INTR_OV_SIG_VL_MSK                       0x0002
#define MPWM_INTR_OV_SIG_WL_MSK                       0x0004
#define MPWM_INTR_OV_SIG_UH_MSK                       0x0008
#define MPWM_INTR_OV_SIG_VH_MSK                       0x0010
#define MPWM_INTR_OV_SIG_WH_MSK                       0x0020
#define MPWM_INTR_OV_BASE_MSK                         0x0080

#define MPWM_INTR_SIG_U_MSK                           (MPWM_INTR_SIG_UL_MSK | MPWM_INTR_SIG_UH_MSK | MPWM_INTR_SIG_U_PERIOD_MSK | MPWM_INTR_SIG_U_BOTTOM_MSK)
#define MPWM_INTR_SIG_V_MSK                           (MPWM_INTR_SIG_VL_MSK | MPWM_INTR_SIG_VH_MSK | MPWM_INTR_SIG_V_PERIOD_MSK | MPWM_INTR_SIG_V_BOTTOM_MSK)
#define MPWM_INTR_SIG_W_MSK                           (MPWM_INTR_SIG_WL_MSK | MPWM_INTR_SIG_WH_MSK | MPWM_INTR_SIG_W_PERIOD_MSK | MPWM_INTR_SIG_W_BOTTOM_MSK)

#define MPWM_INTR_PWM_MSK                               (MPWM_INTR_SIG_UL_MSK | MPWM_INTR_SIG_UH_MSK | MPWM_INTR_SIG_VL_MSK | MPWM_INTR_SIG_VH_MSK \
                                                        | MPWM_INTR_SIG_WL_MSK | MPWM_INTR_SIG_WH_MSK | MPWM_INTR_SIG_U_PERIOD_MSK | MPWM_INTR_SIG_U_BOTTOM_MSK)

#define MPWM_INTR_ADC_ATR_MSK                           (MPWM_INTR_ATR1_MSK | MPWM_INTR_ATR2_MSK | MPWM_INTR_ATR3_MSK \
                                                        | MPWM_INTR_ATR4_MSK | MPWM_INTR_ATR5_MSK | MPWM_INTR_ATR6_MSK)

#define MPWM_INTR_PROT_MSK                              (MPWM_INTR_PROT_SIG_UL_MSK | MPWM_INTR_PROT_SIG_VL_MSK | MPWM_INTR_PROT_SIG_WL_MSK \
                                                        | MPWM_INTR_PROT_SIG_UH_MSK | MPWM_INTR_PROT_SIG_VH_MSK | MPWM_INTR_PROT_SIG_WH_MSK \
                                                        | MPWM_INTR_PROT_BASE_MSK)

#define MPWM_INTR_OV_MSK                                (MPWM_INTR_OV_SIG_UL_MSK | MPWM_INTR_OV_SIG_VL_MSK | MPWM_INTR_OV_SIG_WL_MSK \
                                                        | MPWM_INTR_OV_SIG_UH_MSK | MPWM_INTR_OV_SIG_VH_MSK | MPWM_INTR_OV_SIG_WH_MSK \
                                                        | MPWM_INTR_OV_BASE_MSK)
#define MPWM_MODE(x)                                  (x == 2 ? 3 : x)

/* Position & Mask Macro */
#define SET_MPWM_CR_MODE_POS(Data)                    SET_POS(Data,MPWM,CR,T30MS)
#define SET_MPWM_CR_FORCA_POS(Data)                   SET_POS(Data,MPWM,CR,FORCA)
#define SET_MPWM_CR_DLYEN_POS(Data)                   SET_POS(Data,MPWM,CR,DLYEN)
#define SET_MPWM_CR_DLYPOS_POS(Data)                  SET_POS(Data,MPWM,CR,DLYPOS)
#define SET_MPWM_CR_CAPPORT_POS(Data)                 SET_POS(Data,MPWM,CR,T30CPOL)
#define SET_MPWM_CR_RELOAD_POS(Data)                  SET_POS(Data,MPWM,CR,UPDT)
#define SET_MPWM_CR_PMOC_POS(Data)                    SET_POS(Data,MPWM,CR,PMOC)
#define MPWM_CR_MODE_MSK                              BIT_NAME_MSK(MPWM_,CR_,T30MS_)
#define MPWM_CR_FORCA_MSK                             BIT_NAME_MSK(MPWM_,CR_,FORCA_)
#define MPWM_CR_DLYEN_MSK                             BIT_NAME_MSK(MPWM_,CR_,DLYEN_)
#define MPWM_CR_DLYPOS_MSK                            BIT_NAME_MSK(MPWM_,CR_,DLYPOS_)
#define MPWM_CR_CAPPORT_MSK                           BIT_NAME_MSK(MPWM_,CR_,CPOL_)
#define MPWM_CR_RELOAD_MSK                            BIT_NAME_MSK(MPWM_,CR_,UPDT_)
#define MPWM_CR_PMOC_MSK                              BIT_NAME_MSK(MPWM_,CR_,PMOC_)

/* Bit/Register Macro */
#define SET_MPWM_CR_EN(Peri,Data)                     SET_BIT(Peri,Data,MPWM,CR1,PWMEN)
#define SET_MPWM_CR_TFM(Peri,Data)                    SET_BIT(Peri,Data,MPWM,MR,TFM)
#define SET_MPWM_CR_BFM(Peri,Data)                    SET_BIT(Peri,Data,MPWM,MR,BFM)
#define SET_MPWM_CR_DIV(Peri,Data)                    SET_BIT(Peri,Data,MPWM,MR,CLKDIV)
#define SET_MPWM_CR_MODE(Peri,Data)                   SET_BIT(Peri,Data,MPWM,MR,MOTORB)
#define GET_MPWM_CR_MODE(Peri)                        GET_BIT(Peri,MPWM,MR,MOTORB)
#define SET_MPWM_CR_UPDATE_TIME(Peri,Data)            SET_BIT(Peri,Data,MPWM,MR,UAO)
#define SET_MPWM_CR_UPDATE_DUTY_PERIOD(Peri,Data)     SET_BIT(Peri,Data,MPWM,MR,TUP)
#define SET_MPWM_CR_UPDATE_DUTY_BOTTOM(Peri,Data)     SET_BIT(Peri,Data,MPWM,MR,BUP)
#define SET_MPWM_CR_CHANNEL_MODE(Peri,Data)           SET_BIT(Peri,Data,MPWM,MR,MCHMOD)
#define SET_MPWM_CR_COUNTER_MODE(Peri,Data)           SET_BIT(Peri,Data,MPWM,MR,UPDOWN)
#define SET_MPWM_CR_INTR_INTV_VAL(Peri,Data)          SET_BIT(Peri,Data,MPWM,CR1,IRQN)
#define SET_MPWM_CR_START(Peri,Data)                  SET_BIT(Peri,Data,MPWM,CR2,PSTART)
#define SET_MPWM_CR_HALT(Peri,Data)                   SET_BIT(Peri,Data,MPWM,CR2,HALT)

#define SET_MPWM_CR_FORCE_OUTPUT_EN(Peri,Data)        SET_BIT(Peri,Data,MPWM,OLR,FORCEU)

#define SET_MPWM_CR_WH_OUTPUT_EN(Peri,Data)           SET_BIT(Peri,Data,MPWM,OLR,POCWH)
#define SET_MPWM_CR_VH_OUTPUT_EN(Peri,Data)           SET_BIT(Peri,Data,MPWM,OLR,POCVH)
#define SET_MPWM_CR_UH_OUTPUT_EN(Peri,Data)           SET_BIT(Peri,Data,MPWM,OLR,POCUH)
#define SET_MPWM_CR_WL_OUTPUT_EN(Peri,Data)           SET_BIT(Peri,Data,MPWM,OLR,POCWL)
#define SET_MPWM_CR_VL_OUTPUT_EN(Peri,Data)           SET_BIT(Peri,Data,MPWM,OLR,POCVL)
#define SET_MPWM_CR_UL_OUTPUT_EN(Peri,Data)           SET_BIT(Peri,Data,MPWM,OLR,POCUL)

#define SET_MPWM_CR_WH_OUTPUT_LVL(Peri,Data)          SET_BIT(Peri,Data,MPWM,OLR,DOLWH)
#define SET_MPWM_CR_VH_OUTPUT_LVL(Peri,Data)          SET_BIT(Peri,Data,MPWM,OLR,DOLVH)
#define SET_MPWM_CR_UH_OUTPUT_LVL(Peri,Data)          SET_BIT(Peri,Data,MPWM,OLR,DOLUH)
#define SET_MPWM_CR_WL_OUTPUT_LVL(Peri,Data)          SET_BIT(Peri,Data,MPWM,OLR,DOLWL)
#define SET_MPWM_CR_VL_OUTPUT_LVL(Peri,Data)          SET_BIT(Peri,Data,MPWM,OLR,DOLVL)
#define SET_MPWM_CR_UL_OUTPUT_LVL(Peri,Data)          SET_BIT(Peri,Data,MPWM,OLR,DOLUL)

#define SET_MPWM_CR_WH_INV_START_LVL(Peri,Data)       SET_BIT(Peri,Data,MPWM,OLR,SLWH)
#define SET_MPWM_CR_VH_INV_START_LVL(Peri,Data)       SET_BIT(Peri,Data,MPWM,OLR,SLVH)
#define SET_MPWM_CR_UH_INV_START_LVL(Peri,Data)       SET_BIT(Peri,Data,MPWM,OLR,SLUH)
#define SET_MPWM_CR_WL_INV_START_LVL(Peri,Data)       SET_BIT(Peri,Data,MPWM,OLR,SLWL)
#define SET_MPWM_CR_VL_INV_START_LVL(Peri,Data)       SET_BIT(Peri,Data,MPWM,OLR,SLVL)
#define SET_MPWM_CR_UL_INV_START_LVL(Peri,Data)       SET_BIT(Peri,Data,MPWM,OLR,SLUL)

#define SET_MPWM_CR_WH_FORCE_SW(Peri,Data)            SET_BIT_KEY_BITNAME(Peri,MPWM_FORCE_ACCESS_KEY,FOLKEY,Data,MPWM,FOLR,SWFO)
#define SET_MPWM_CR_VH_FORCE_PRT(Peri,Data)           SET_BIT_KEY_BITNAME(Peri,MPWM_FORCE_ACCESS_KEY,FOLKEY,Data,MPWM,FOLR,PRTFO)
#define SET_MPWM_CR_UH_FORCE_OC(Peri,Data)            SET_BIT_KEY_BITNAME(Peri,MPWM_FORCE_ACCESS_KEY,FOLKEY,Data,MPWM,FOLR,OCFO)

#define SET_MPWM_CR_WH_FORCE_LVL(Peri,Data)           SET_BIT_KEY_BITNAME(Peri,MPWM_FORCE_ACCESS_KEY,FOLKEY,Data,MPWM,FOLR,FLWH)
#define SET_MPWM_CR_VH_FORCE_LVL(Peri,Data)           SET_BIT_KEY_BITNAME(Peri,MPWM_FORCE_ACCESS_KEY,FOLKEY,Data,MPWM,FOLR,FLVH)
#define SET_MPWM_CR_UH_FORCE_LVL(Peri,Data)           SET_BIT_KEY_BITNAME(Peri,MPWM_FORCE_ACCESS_KEY,FOLKEY,Data,MPWM,FOLR,FLUH)
#define SET_MPWM_CR_WL_FORCE_LVL(Peri,Data)           SET_BIT_KEY_BITNAME(Peri,MPWM_FORCE_ACCESS_KEY,FOLKEY,Data,MPWM,FOLR,FLWL)
#define SET_MPWM_CR_VL_FORCE_LVL(Peri,Data)           SET_BIT_KEY_BITNAME(Peri,MPWM_FORCE_ACCESS_KEY,FOLKEY,Data,MPWM,FOLR,FLVL)
#define SET_MPWM_CR_UL_FORCE_LVL(Peri,Data)           SET_BIT_KEY_BITNAME(Peri,MPWM_FORCE_ACCESS_KEY,FOLKEY,Data,MPWM,FOLR,FLUL)

#define SET_MPWM_DEADTIME_EN(Peri,Data)               SET_BIT(Peri,Data,MPWM,DTR,DTEN)
#define SET_MPWM_DEADTIME_SCPROT_DIS(Peri,Data)       SET_BIT(Peri,Data,MPWM,DTR,PSHRT)
#define SET_MPWM_DEADTIME_H_OUTPUT_LVL(Peri,Data)     SET_BIT(Peri,Data,MPWM,DTR,HDTOL)
#define SET_MPWM_DEADTIME_L_OUTPUT_LVL(Peri,Data)     SET_BIT(Peri,Data,MPWM,DTR,LDTOL)
#define SET_MPWM_DEADTIME_PRESCALE(Peri,Data)         SET_BIT(Peri,Data,MPWM,DTR,DTCLK)
#define SET_MPWM_DEADTIME_H_VAL(Peri,Data)            SET_BIT(Peri,Data,MPWM,DTR,HDT)
#define SET_MPWM_DEADTIME_L_VAL(Peri,Data)            SET_BIT(Peri,Data,MPWM,DTR,LDT)

#define SET_MPWM_CAP_U_CLEAR_CNT(Peri,Data)           SET_BIT(Peri,Data,MPWM,CAPCNTU,CNTCLEAR)
#define SET_MPWM_CAP_U_EN(Peri,Data)                  SET_BIT(Peri,Data,MPWM,CAPCNTU,CAPEN)
#define GET_MPWM_CAP_U_COUNTER(Peri)                  GET_BIT(Peri,MPWM,CAPCNTU,CAPCNTx)
#define SET_MPWM_CAP_V_CLEAR_CNT(Peri,Data)           SET_BIT(Peri,Data,MPWM,CAPCNTV,CNTCLEAR)
#define SET_MPWM_CAP_V_EN(Peri,Data)                  SET_BIT(Peri,Data,MPWM,CAPCNTV,CAPEN)
#define GET_MPWM_CAP_V_COUNTER(Peri)                  GET_BIT(Peri,MPWM,CAPCNTV,CAPCNTx)
#define SET_MPWM_CAP_W_CLEAR_CNT(Peri,Data)           SET_BIT(Peri,Data,MPWM,CAPCNTW,CNTCLEAR)
#define SET_MPWM_CAP_W_EN(Peri,Data)                  SET_BIT(Peri,Data,MPWM,CAPCNTW,CAPEN)
#define GET_MPWM_CAP_W_COUNTER(Peri)                  GET_BIT(Peri,MPWM,CAPCNTW,CAPCNTx)

#define SET_MPWM_CAP_U_RISING_FLAG(Peri,Data)         SET_BIT(Peri,Data,MPWM,RCAPU,RCAPFLAG)
#define GET_MPWM_CAP_U_RISING_FLAG(Peri)              GET_BIT(Peri,MPWM,RCAPU,RCAPFLAG)
#define GET_MPWM_CAP_U_RISING_COUNTER(Peri)           GET_BIT(Peri,MPWM,RCAPU,RCAPx)
#define SET_MPWM_CAP_V_RISING_FLAG(Peri,Data)         SET_BIT(Peri,Data,MPWM,RCAPV,RCAPFLAG)
#define GET_MPWM_CAP_V_RISING_FLAG(Peri)              GET_BIT(Peri,MPWM,RCAPV,RCAPFLAG)
#define GET_MPWM_CAP_V_RISING_COUNTER(Peri)           GET_BIT(Peri,MPWM,RCAPV,RCAPx)
#define SET_MPWM_CAP_W_RISING_FLAG(Peri,Data)         SET_BIT(Peri,Data,MPWM,RCAPW,RCAPFLAG)
#define GET_MPWM_CAP_W_RISING_FLAG(Peri)              GET_BIT(Peri,MPWM,RCAPW,RCAPFLAG)
#define GET_MPWM_CAP_W_RISING_COUNTER(Peri)           GET_BIT(Peri,MPWM,RCAPW,RCAPx)

#define SET_MPWM_CAP_U_FALLING_FLAG(Peri,Data)        SET_BIT(Peri,Data,MPWM,FCAPU,FCAPFLAG)
#define GET_MPWM_CAP_U_FALLING_FLAG(Peri)             GET_BIT(Peri,MPWM,FCAPU,FCAPFLAG)
#define GET_MPWM_CAP_U_FALLING_COUNTER(Peri)          GET_BIT(Peri,MPWM,FCAPU,FCAPx)
#define SET_MPWM_CAP_V_FALLING_FLAG(Peri,Data)        SET_BIT(Peri,Data,MPWM,FCAPV,FCAPFLAG)
#define GET_MPWM_CAP_V_FALLING_FLAG(Peri)             GET_BIT(Peri,MPWM,FCAPV,FCAPFLAG)
#define GET_MPWM_CAP_V_FALLING_COUNTER(Peri)          GET_BIT(Peri,MPWM,FCAPV,FCAPx)
#define SET_MPWM_CAP_W_FALLING_FLAG(Peri,Data)        SET_BIT(Peri,Data,MPWM,FCAPW,FCAPFLAG)
#define GET_MPWM_CAP_W_FALLING_FLAG(Peri)             GET_BIT(Peri,MPWM,FCAPW,FCAPFLAG)
#define GET_MPWM_CAP_W_FALLING_COUNTER(Peri)          GET_BIT(Peri,MPWM,FCAPW,FCAPx)

#define SET_MPWM_SUBCAP_U_FLAG(Peri,Data)             SET_BIT(Peri,Data,MPWM,SCAPU,SCAPFLAG)
#define GET_MPWM_SUBCAP_U_FLAG(Peri)                  GET_BIT(Peri,MPWM,SCAPU,SCAPFLAG)
#define SET_MPWM_SUBCAP_U_EDGE(Peri,Data)             SET_BIT(Peri,Data,MPWM,SCAPU,EDGESEL)
#define GET_MPWM_SUBCAP_U_COUNTER(Peri)               GET_BIT(Peri,MPWM,SCAPU,SCAPx)
#define SET_MPWM_SUBCAP_V_FLAG(Peri,Data)             SET_BIT(Peri,Data,MPWM,SCAPV,SCAPFLAG)
#define GET_MPWM_SUBCAP_V_FLAG(Peri)                  GET_BIT(Peri,MPWM,SCAPV,SCAPFLAG)
#define SET_MPWM_SUBCAP_V_EDGE(Peri,Data)             SET_BIT(Peri,Data,MPWM,SCAPU,EDGESEL)
#define GET_MPWM_SUBCAP_V_COUNTER(Peri)               GET_BIT(Peri,MPWM,SCAPV,SCAPx)
#define SET_MPWM_SUBCAP_W_FLAG(Peri,Data)             SET_BIT(Peri,Data,MPWM,SCAPW,SCAPFLAG)
#define GET_MPWM_SUBCAP_W_FLAG(Peri)                  GET_BIT(Peri,MPWM,SCAPW,SCAPFLAG)
#define SET_MPWM_SUBCAP_W_EDGE(Peri,Data)             SET_BIT(Peri,Data,MPWM,SCAPU,EDGESEL)
#define GET_MPWM_SUBCAP_W_COUNTER(Peri)               GET_BIT(Peri,MPWM,SCAPW,SCAPx)

#define SET_MPWM_PROT_POL(Peri,Data)                  SET_BIT(Peri,Data,MPWM,PCR,PROTPOL)
#define SET_MPWM_PROT_DIV(Peri,Data)                  SET_BIT(Peri,Data,MPWM,PCR,PROTDIV)
#define SET_MPWM_PROT_DEBOUNCE(Peri,Data)             SET_BIT(Peri,Data,MPWM,PCR,PROTD)
#define SET_MPWM_PROT3_EN(Peri,Data)                  SET_BIT(Peri,Data,MPWM,PCR,PROT3EN)
#define SET_MPWM_PROT2_EN(Peri,Data)                  SET_BIT(Peri,Data,MPWM,PCR,PROT2EN)
#define SET_MPWM_PROT1_EN(Peri,Data)                  SET_BIT(Peri,Data,MPWM,PCR,PROT1EN)
#define SET_MPWM_PROT0_EN(Peri,Data)                  SET_BIT(Peri,Data,MPWM,PCR,PROT0EN)

#define GET_MPWM_PROT3_FLAG(Peri)                     GET_BIT(Peri,Data,MPWM,PSR,PROT3IF)
#define SET_MPWM_PROT3_FLAG(Peri,Data)                SET_BIT(Peri,Data,MPWM,PSR,PROT3IF)
#define GET_MPWM_PROT2_FLAG(Peri)                     GET_BIT(Peri,Data,MPWM,PSR,PROT2IF)
#define SET_MPWM_PROT2_FLAG(Peri,Data)                SET_BIT(Peri,Data,MPWM,PSR,PROT2IF)
#define GET_MPWM_PROT1_FLAG(Peri)                     GET_BIT(Peri,Data,MPWM,PSR,PROT1IF)
#define SET_MPWM_PROT1_FLAG(Peri,Data)                SET_BIT(Peri,Data,MPWM,PSR,PROT1IF)
#define GET_MPWM_PROT0_FLAG(Peri)                     GET_BIT(Peri,Data,MPWM,PSR,PROT0IF)
#define SET_MPWM_PROT0_FLAG(Peri,Data)                SET_BIT(Peri,Data,MPWM,PSR,PROT0IF)
#define GET_MPWM_PROT_SR(Peri)                        GET_REG(Peri,PSR)
#define SET_MPWM_PROT_SR(Peri,Data)                   SET_REG(Peri,Data,PSR)

#define SET_MPWM_OV_POL(Peri,Data)                    SET_BIT(Peri,Data,MPWM,OCR,OVINPOL)
#define SET_MPWM_OV_DIV(Peri,Data)                    SET_BIT(Peri,Data,MPWM,OCR,OVINDIV)
#define SET_MPWM_OV_DEBOUNCE(Peri,Data)               SET_BIT(Peri,Data,MPWM,OCR,OVIND)
#define SET_MPWM_OV0_EN(Peri,Data)                    SET_BIT(Peri,Data,MPWM,OCR,OVIN0EN)
#define SET_MPWM_OV1_EN(Peri,Data)                    SET_BIT(Peri,Data,MPWM,OCR,OVIN1EN)
#define SET_MPWM_OV2_EN(Peri,Data)                    SET_BIT(Peri,Data,MPWM,OCR,OVIN2EN)
#define SET_MPWM_OV3_EN(Peri,Data)                    SET_BIT(Peri,Data,MPWM,OCR,OVIN3EN)

#define GET_MPWM_OV3_FLAG(Peri)                       GET_BIT(Peri,Data,MPWM,OSR,OVIN3IF)
#define SET_MPWM_OV3_FLAG(Peri,Data)                  SET_BIT(Peri,Data,MPWM,OSR,OVIN3IF)
#define GET_MPWM_OV2_FLAG(Peri)                       GET_BIT(Peri,Data,MPWM,OSR,OVIN2IF)
#define SET_MPWM_OV2_FLAG(Peri,Data)                  SET_BIT(Peri,Data,MPWM,OSR,OVIN2IF)
#define GET_MPWM_OV1_FLAG(Peri)                       GET_BIT(Peri,Data,MPWM,OSR,OVIN1IF)
#define SET_MPWM_OV1_FLAG(Peri,Data)                  SET_BIT(Peri,Data,MPWM,OSR,OVIN1IF)
#define GET_MPWM_OV0_FLAG(Peri)                       GET_BIT(Peri,Data,MPWM,OSR,OVIN0IF)
#define SET_MPWM_OV0_FLAG(Peri,Data)                  SET_BIT(Peri,Data,MPWM,OSR,OVIN0IF)
#define GET_MPWM_OV_SR(Peri)                          GET_REG(Peri,OSR)
#define SET_MPWM_OV_SR(Peri,Data)                     SET_REG(Peri,Data,OSR)

#define GET_MPWM_ADCTRG_BASE_ADDR(Peri)               GET_REG_ADDR(Peri,ATR1)
#define SET_MPWM_ADCTRG_CNT(Addr,Data,Offset)         SET_BIT_ADDR_OFFSET(Addr,Offset,Data,MPWM,ATR1,ATCNT)
#define SET_MPWM_ADCTRG_MODE(Addr,Data,Offset)        SET_BIT_ADDR_OFFSET(Addr,Offset,Data,MPWM,ATR1,ATMOD)
#define SET_MPWM_ADCTRG_UPDATE(Addr,Data,Offset)      SET_BIT_ADDR_OFFSET(Addr,Offset,Data,MPWM,ATR1,ATUDT)

#define SET_MPWM_DR_PERIOD_VAL(Peri,Data)             SET_REG(Peri,Data,PRD)
#define SET_MPWM_DR_DUTY_UH_VAL(Peri,Data)            SET_REG(Peri,Data,DUH)
#define SET_MPWM_DR_DUTY_VH_VAL(Peri,Data)            SET_REG(Peri,Data,DVH)
#define SET_MPWM_DR_DUTY_WH_VAL(Peri,Data)            SET_REG(Peri,Data,DWH)
#define SET_MPWM_DR_DUTY_UL_VAL(Peri,Data)            SET_REG(Peri,Data,DUL)
#define SET_MPWM_DR_DUTY_VL_VAL(Peri,Data)            SET_REG(Peri,Data,DVL)
#define SET_MPWM_DR_DUTY_WL_VAL(Peri,Data)            SET_REG(Peri,Data,DWL)

#define GET_MPWM_DR_COUNTER(Peri,Data)                GET_REG(Peri,CNT)


#define GET_MPWM_SR_SIG_CNT_MODE(Peri)                GET_BIT(Peri,Data,MPWM,SR,DOWN)
#define GET_MPWM_SR_SIG_PERIOD_MATCH_CNT(Peri)        GET_BIT(Peri,Data,MPWM,SR,IRQCNT)

/* Interrup Bit Macro */
#define SET_MPWM_IER_UL_ATR1_EN(Peri,Data)            SET_BIT(Peri,Data,MPWM,IER,ULIE_ATR1IE)
#define SET_MPWM_IER_VL_ATR2_EN(Peri,Data)            SET_BIT(Peri,Data,MPWM,IER,VLIE_ATR2IE)
#define SET_MPWM_IER_WL_ATR3_EN(Peri,Data)            SET_BIT(Peri,Data,MPWM,IER,WLIE_ATR3IE)
#define SET_MPWM_IER_UH_ATR4_EN(Peri,Data)            SET_BIT(Peri,Data,MPWM,IER,UHIE_ATR4IE)
#define SET_MPWM_IER_VH_ATR5_EN(Peri,Data)            SET_BIT(Peri,Data,MPWM,IER,VHIE_ATR5IE)
#define SET_MPWM_IER_WH_ATR6_EN(Peri,Data)            SET_BIT(Peri,Data,MPWM,IER,WHIE_ATR6IE)
#define SET_MPWM_IER_PROT_EN(Peri,Data)               SET_BIT(Peri,Data,MPWM,PCR,PROTIE)
#define SET_MPWM_IER_OV_EN(Peri,Data)                 SET_BIT(Peri,Data,MPWM,OCR,OVINIE)
#define SET_MPWM_IER_BOTTOM_EN(Peri,Data)             SET_BIT(Peri,Data,MPWM,IER,BOTIE)
#define SET_MPWM_IER_PERIOD_EN(Peri,Data)             SET_BIT(Peri,Data,MPWM,IER,PRDIE)
#define SET_MPWM_IER_SIG_ATR(Peri,Data)               SET_REG(Peri,Data,IER)
#define SET_MPWM_IER_SIG_ATR_MSK(Peri,Data,Mask)      SET_REG_MASK(Peri,Data,Mask,IER)
#define GET_MPWM_IER_SIG_ATR(Peri)                    GET_REG(Peri,IER)
#define GET_MPWM_IER_PERIOD_FLAG(Peri)                GET_BIT(Peri,MPWM,SR,PRDIF)
#define SET_MPWM_IER_PERIOD_FLAG(Peri,Data)           SET_BIT(Peri,Data,MPWM,SR,PRDIF)
#define GET_MPWM_IER_BOTTOM_FLAG(Peri)                GET_BIT(Peri,MPWM,SR,BOTIF)
#define SET_MPWM_IER_BOTTOM_FLAG(Peri,Data)           SET_BIT(Peri,Data,MPWM,SR,BOTIF)
#define GET_MPWM_IER_UL_ATR1_FLAG(Peri)               GET_BIT(Peri,MPWM,SR,DULIF_ATR1F)
#define SET_MPWM_IER_UL_ATR1_FLAG(Peri,Data)          SET_BIT(Peri,Data,MPWM,SR,DULIF_ATR1F)
#define GET_MPWM_IER_VL_ATR2_FLAG(Peri)               GET_BIT(Peri,MPWM,SR,DVLIF_ATR2F)
#define SET_MPWM_IER_VL_ATR2_FLAG(Peri,Data)          SET_BIT(Peri,Data,MPWM,SR,DVLIF_ATR2F)
#define GET_MPWM_IER_WL_ATR3_FLAG(Peri)               GET_BIT(Peri,MPWM,SR,DWLIF_ATR3F)
#define SET_MPWM_IER_WL_ATR3_FLAG(Peri,Data)          SET_BIT(Peri,Data,MPWM,SR,DWLIF_ATR3F)
#define GET_MPWM_IER_UH_ATR4_FLAG(Peri)               GET_BIT(Peri,MPWM,SR,DUHIF_ATR4F)
#define SET_MPWM_IER_UH_ATR4_FLAG(Peri,Data)          SET_BIT(Peri,Data,MPWM,SR,DUHIF_ATR4F)
#define GET_MPWM_IER_VH_ATR5_FLAG(Peri)               GET_BIT(Peri,MPWM,SR,DVHIF_ATR5F)
#define SET_MPWM_IER_VH_ATR5_FLAG(Peri,Data)          SET_BIT(Peri,Data,MPWM,SR,DVHIF_ATR5F)
#define GET_MPWM_IER_WH_ATR6_FLAG(Peri)               GET_BIT(Peri,MPWM,SR,DWHIF_ATR6F)
#define SET_MPWM_IER_WH_ATR6_FLAG(Peri,Data)          SET_BIT(Peri,Data,MPWM,SR,DWHIF_ATR6F)
#define SET_MPWM_IER_SR_SIG_ATR(Peri,Data)            SET_REG(Peri,Data,SR)
#define GET_MPWM_IER_SR_SIG_ATR(Peri)                 GET_REG(Peri,SR)
#define GET_MPWM_IER_PROT_FLAG(Peri)                  GET_BIT(Peri,MPWM,PSR,PROTIF)
#define SET_MPWM_IER_PROT_FLAG(Peri,Data)             SET_BIT_KEY_BITNAME(Peri,MPWM_PROTECTION_ACCESS_KEY,PROTKEY,Data,MPWM,OSR,PROTIF)
#define GET_MPWM_IER_OV_FLAG(Peri)                    GET_BIT(Peri,MPWM,OSR,OVINIF)
#define SET_MPWM_IER_OV_FLAG(Peri,Data)               SET_BIT_KEY_BITNAME(Peri,MPWM_OVERVOLTAGE_ACCESS_KEY,OVINKEY,Data,MPWM,OSR,OVINIF)

/* Unused Macro */
               
/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_MPWM_MCCR_SEL(Peri,Id,Data)           SET_BIT_OFFSET(Peri,(Id*MPWM_MCCR_BIT_OFFSET),Data,SCU,MCCR2,MPWMCSEL)
#define SET_SCU_MPWM_MCCR_DIV(Peri,Id,Data)           SET_BIT_OFFSET(Peri,(Id*MPWM_MCCR_BIT_OFFSET),Data,SCU,MCCR2,MPWMCDIV)
#define SET_SCU_MPWM_PER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PER2,MPWM)
#define SET_SCU_MPWM_PCER(Peri,Id,Data)               SET_BIT_ID(Peri,Id,Data,SCU,PCER2,MPWM)

#endif /* _HAL_MPWM_V_01_00_00_H_ */
