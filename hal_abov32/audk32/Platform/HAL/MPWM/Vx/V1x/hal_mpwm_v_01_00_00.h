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
#define MPWM_REG_BASE                                 MPWM0_BASE
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
#define SET_MPWM_CR_MODE_POS(Data)                    SET_POS(Data,MPWM0,CR,T30MS)
#define SET_MPWM_CR_FORCA_POS(Data)                   SET_POS(Data,MPWM0,CR,FORCA)
#define SET_MPWM_CR_DLYEN_POS(Data)                   SET_POS(Data,MPWM0,CR,DLYEN)
#define SET_MPWM_CR_DLYPOS_POS(Data)                  SET_POS(Data,MPWM0,CR,DLYPOS)
#define SET_MPWM_CR_CAPPORT_POS(Data)                 SET_POS(Data,MPWM0,CR,T30CPOL)
#define SET_MPWM_CR_RELOAD_POS(Data)                  SET_POS(Data,MPWM0,CR,UPDT)
#define SET_MPWM_CR_PMOC_POS(Data)                    SET_POS(Data,MPWM0,CR,PMOC)
#define MPWM_CR_MODE_MSK                              BIT_NAME_MSK(MPWM0_,CR_,T30MS_)
#define MPWM_CR_FORCA_MSK                             BIT_NAME_MSK(MPWM0_,CR_,FORCA_)
#define MPWM_CR_DLYEN_MSK                             BIT_NAME_MSK(MPWM0_,CR_,DLYEN_)
#define MPWM_CR_DLYPOS_MSK                            BIT_NAME_MSK(MPWM0_,CR_,DLYPOS_)
#define MPWM_CR_CAPPORT_MSK                           BIT_NAME_MSK(MPWM0_,CR_,CPOL_)
#define MPWM_CR_RELOAD_MSK                            BIT_NAME_MSK(MPWM0_,CR_,UPDT_)
#define MPWM_CR_PMOC_MSK                              BIT_NAME_MSK(MPWM0_,CR_,PMOC_)

/* Bit/Register Macro */
#define SET_MPWM_CR_EN(Peri,Data)                     SET_BIT(Peri,Data,MPWM,CR1,PWMEN)
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

#define SET_MPWM_CR_WH_OUTPUT_LVL(Peri,Data)          SET_BIT(Peri,Data,MPWM,OLR,DOLWH)
#define SET_MPWM_CR_VH_OUTPUT_LVL(Peri,Data)          SET_BIT(Peri,Data,MPWM,OLR,DOLVH)
#define SET_MPWM_CR_UH_OUTPUT_LVL(Peri,Data)          SET_BIT(Peri,Data,MPWM,OLR,DOLUH)
#define SET_MPWM_CR_WL_OUTPUT_LVL(Peri,Data)          SET_BIT(Peri,Data,MPWM,OLR,DOLWL)
#define SET_MPWM_CR_VL_OUTPUT_LVL(Peri,Data)          SET_BIT(Peri,Data,MPWM,OLR,DOLVL)
#define SET_MPWM_CR_UL_OUTPUT_LVL(Peri,Data)          SET_BIT(Peri,Data,MPWM,OLR,DOLUL)

#define SET_MPWM_CR_WH_INV_START_LVL(Peri,Data)       SET_BIT(Peri,Data,MPWM,OLR,WHL)
#define SET_MPWM_CR_VH_INV_START_LVL(Peri,Data)       SET_BIT(Peri,Data,MPWM,OLR,VHL)
#define SET_MPWM_CR_UH_INV_START_LVL(Peri,Data)       SET_BIT(Peri,Data,MPWM,OLR,UHL)
#define SET_MPWM_CR_WL_INV_START_LVL(Peri,Data)       SET_BIT(Peri,Data,MPWM,OLR,WLL)
#define SET_MPWM_CR_VL_INV_START_LVL(Peri,Data)       SET_BIT(Peri,Data,MPWM,OLR,VLL)
#define SET_MPWM_CR_UL_INV_START_LVL(Peri,Data)       SET_BIT(Peri,Data,MPWM,OLR,ULL)

#define SET_MPWM_CR_WH_FORCE_LVL(Peri,Data)           SET_BIT(Peri,Data,MPWM,FOLR,WHFL)
#define SET_MPWM_CR_VH_FORCE_LVL(Peri,Data)           SET_BIT(Peri,Data,MPWM,FOLR,VHFL)
#define SET_MPWM_CR_UH_FORCE_LVL(Peri,Data)           SET_BIT(Peri,Data,MPWM,FOLR,UHFL)
#define SET_MPWM_CR_WL_FORCE_LVL(Peri,Data)           SET_BIT(Peri,Data,MPWM,FOLR,WLFL)
#define SET_MPWM_CR_VL_FORCE_LVL(Peri,Data)           SET_BIT(Peri,Data,MPWM,FOLR,VLFL)
#define SET_MPWM_CR_UL_FORCE_LVL(Peri,Data)           SET_BIT(Peri,Data,MPWM,FOLR,ULFL)

#define SET_MPWM_CR_PWM_U_EN(Peri,Data)               SET_BIT(Peri,Data,MPWM,CR3,UEN)
#define SET_MPWM_CR_PWM_U_START(Peri,Data)            SET_BIT(Peri,Data,MPWM,CR3,USTART)
#define SET_MPWM_CR_PWM_U_HALT(Peri,Data)             SET_BIT(Peri,Data,MPWM,CR3,UHALT)
#define SET_MPWM_CR_PWM_U_INTR_INTV_VAL(Peri,Data)    SET_BIT(Peri,Data,MPWM,CR3,UIRQN)
#define SET_MPWM_CR_V_EN(Peri,Data)                   SET_BIT(Peri,Data,MPWM,CR3,VEN)
#define SET_MPWM_CR_V_START(Peri,Data)                SET_BIT(Peri,Data,MPWM,CR3,VSTART)
#define SET_MPWM_CR_V_HALT(Peri,Data)                 SET_BIT(Peri,Data,MPWM,CR3,VHALT)
#define SET_MPWM_CR_V_INTR_INTV_VAL(Peri,Data)        SET_BIT(Peri,Data,MPWM,CR3,VIRQN)
#define SET_MPWM_CR_W_EN(Peri,Data)                   SET_BIT(Peri,Data,MPWM,CR3,WEN)
#define SET_MPWM_CR_W_START(Peri,Data)                SET_BIT(Peri,Data,MPWM,CR3,WSTART)
#define SET_MPWM_CR_W_HALT(Peri,Data)                 SET_BIT(Peri,Data,MPWM,CR3,WHALT)
#define SET_MPWM_CR_W_INTR_INTV_VAL(Peri,Data)        SET_BIT(Peri,Data,MPWM,CR3,WIRQN)
#define SET_MPWM_CR_PWM_U_DIS(Peri,Data)              SET_BIT(Peri,Data,MPWM,CR4,UDIS)
#define SET_MPWM_CR_PWM_U_STOP(Peri,Data)             SET_BIT(Peri,Data,MPWM,CR4,USTOP)
#define SET_MPWM_CR_PWM_U_CONTI(Peri,Data)            SET_BIT(Peri,Data,MPWM,CR4,UCONTI)
#define SET_MPWM_CR_V_DIS(Peri,Data)                  SET_BIT(Peri,Data,MPWM,CR4,VDIS)
#define SET_MPWM_CR_V_STOP(Peri,Data)                 SET_BIT(Peri,Data,MPWM,CR4,VSTOP)
#define SET_MPWM_CR_V_CONTI(Peri,Data)                SET_BIT(Peri,Data,MPWM,CR4,VCONTI)
#define SET_MPWM_CR_W_DIS(Peri,Data)                  SET_BIT(Peri,Data,MPWM,CR4,WDIS)
#define SET_MPWM_CR_W_STOP(Peri,Data)                 SET_BIT(Peri,Data,MPWM,CR4,WSTOP)
#define SET_MPWM_CR_W_CONTI(Peri,Data)                SET_BIT(Peri,Data,MPWM,CR4,WCONTI)

#define SET_MPWM_DEADTIME_EN(Peri,Data)               SET_BIT(Peri,Data,MPWM,DTR,DTEN)
#define SET_MPWM_DEADTIME_SCPROT_DIS(Peri,Data)       SET_BIT(Peri,Data,MPWM,DTR,PSHRT)
#define SET_MPWM_DEADTIME_MODE_SEL(Peri,Data)         SET_BIT(Peri,Data,MPWM,DTR,DTMDSEL)
#define SET_MPWM_DEADTIME_PRESCALE(Peri,Data)         SET_BIT(Peri,Data,MPWM,DTR,DTCLK)
#define SET_MPWM_DEADTIME_VAL(Peri,Data)              SET_BIT(Peri,Data,MPWM,DTR,DT)

#define SET_MPWM_DEADTIME_U_EN(Peri,Data)             SET_BIT(Peri,Data,MPWM,DTRU,UDTEN)
#define SET_MPWM_DEADTIME_U_SCPROT_DIS(Peri,Data)     SET_BIT(Peri,Data,MPWM,DTRU,UPSHRT)
#define SET_MPWM_DEADTIME_U_MODE_SEL(Peri,Data)       SET_BIT(Peri,Data,MPWM,DTRU,DTMDSEL)
#define SET_MPWM_DEADTIME_U_PRESCALE(Peri,Data)       SET_BIT(Peri,Data,MPWM,DTRU,UDTCLK)

#if (CONFIG_MPWM_REG_NAME == 0)
#define SET_MPWM_DEADTIME_U_VAL(Peri,Data)            SET_BIT(Peri,Data,MPWM,DTRU,UDT)
#elif (CONFIG_MPWM_REG_NAME == 1)
#define SET_MPWM_DEADTIME_U_VAL(Peri,Data) \
                                                      SET_BIT(Peri,(Data & 0xFF),MPWM,DTRU,ULDT); \
                                                      SET_BIT(Peri,((Data >> 8) & 0xFF),MPWM,DTRU,UHDT)
#elif (CONFIG_MPWM_REG_NAME == 2)
#define SET_MPWM_DEADTIME_U_VAL(Peri,Data)            SET_BIT(Peri,Data,MPWM,DTRU,ULDT)
#endif

#define SET_MPWM_DEADTIME_V_EN(Peri,Data)             SET_BIT(Peri,Data,MPWM,DTRV,VDTEN)
#define SET_MPWM_DEADTIME_V_SCPROT_DIS(Peri,Data)     SET_BIT(Peri,Data,MPWM,DTRV,VPSHRT)
#define SET_MPWM_DEADTIME_V_MODE_SEL(Peri,Data)       SET_BIT(Peri,Data,MPWM,DTRV,DTMDSEL)
#define SET_MPWM_DEADTIME_V_PRESCALE(Peri,Data)       SET_BIT(Peri,Data,MPWM,DTRV,VDTCLK)

#if (CONFIG_MPWM_REG_NAME == 0)
#define SET_MPWM_DEADTIME_V_VAL(Peri,Data)            SET_BIT(Peri,Data,MPWM,DTRV,VDT)
#elif (CONFIG_MPWM_REG_NAME == 1)
#define SET_MPWM_DEADTIME_V_VAL(Peri,Data) \
                                                      SET_BIT(Peri,(Data & 0xFF),MPWM,DTRV,VLDT); \
                                                      SET_BIT(Peri,((Data >> 8) & 0xFF),MPWM,DTRV,VHDT)
#elif (CONFIG_MPWM_REG_NAME == 2)
#define SET_MPWM_DEADTIME_V_VAL(Peri,Data)            SET_BIT(Peri,Data,MPWM,DTRV,VLDT)
#endif

#define SET_MPWM_DEADTIME_W_EN(Peri,Data)             SET_BIT(Peri,Data,MPWM,DTRW,WDTEN)
#define SET_MPWM_DEADTIME_W_SCPROT_DIS(Peri,Data)     SET_BIT(Peri,Data,MPWM,DTRW,WPSHRT)
#define SET_MPWM_DEADTIME_W_MODE_SEL(Peri,Data)       SET_BIT(Peri,Data,MPWM,DTRW,DTMDSEL)
#define SET_MPWM_DEADTIME_W_PRESCALE(Peri,Data)       SET_BIT(Peri,Data,MPWM,DTRW,WDTCLK)

#if (CONFIG_MPWM_REG_NAME == 0)
#define SET_MPWM_DEADTIME_W_VAL(Peri,Data)            SET_BIT(Peri,Data,MPWM,DTRW,WDT)
#elif (CONFIG_MPWM_REG_NAME == 1)
#define SET_MPWM_DEADTIME_W_VAL(Peri,Data) \
                                                      SET_BIT(Peri,(Data & 0xFF),MPWM,DTRW,WLDT); \
                                                      SET_BIT(Peri,((Data >> 8) & 0xFF),MPWM,DTRW,WHDT)
#elif (CONFIG_MPWM_REG_NAME == 2)
#define SET_MPWM_DEADTIME_W_VAL(Peri,Data)            SET_BIT(Peri,Data,MPWM,DTRW,WLDT)
#endif

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

#define SET_MPWM_PROT_UL_OUTPUT(Peri,Data)            SET_BIT(Peri,Data,MPWM,PCR,ULPROTM)
#define SET_MPWM_PROT_VL_OUTPUT(Peri,Data)            SET_BIT(Peri,Data,MPWM,PCR,VLPROTM)
#define SET_MPWM_PROT_WL_OUTPUT(Peri,Data)            SET_BIT(Peri,Data,MPWM,PCR,WLPROTM)
#define SET_MPWM_PROT_UH_OUTPUT(Peri,Data)            SET_BIT(Peri,Data,MPWM,PCR,UHPROTM)
#define SET_MPWM_PROT_VH_OUTPUT(Peri,Data)            SET_BIT(Peri,Data,MPWM,PCR,VHPROTM)
#define SET_MPWM_PROT_WH_OUTPUT(Peri,Data)            SET_BIT(Peri,Data,MPWM,PCR,WHPROTM)
#define SET_MPWM_PROT_PWM_U_DEBOUNCE(Peri,Data)       SET_BIT(Peri,Data,MPWM,PCR,PROTD)
#define SET_MPWM_PROT_PWM_U_POL(Peri,Data)            SET_BIT(Peri,Data,MPWM,PCR,PROTPOL)
#define SET_MPWM_PROT_PWM_U_EN(Peri,Data)             SET_BIT(Peri,Data,MPWM,PCR,PROTEN)
#define SET_MPWM_PROT_V_DEBOUNCE(Peri,Data)           SET_BIT(Peri,Data,MPWM,PCR,VPROTD)
#define SET_MPWM_PROT_V_POL(Peri,Data)                SET_BIT(Peri,Data,MPWM,PCR,VPROTPOL)
#define SET_MPWM_PROT_V_EN(Peri,Data)                 SET_BIT(Peri,Data,MPWM,PCR,VPROTEN)
#define SET_MPWM_PROT_W_DEBOUNCE(Peri,Data)           SET_BIT(Peri,Data,MPWM,PCR,WPROTD)
#define SET_MPWM_PROT_W_POL(Peri,Data)                SET_BIT(Peri,Data,MPWM,PCR,WPROTPOL)
#define SET_MPWM_PROT_W_EN(Peri,Data)                 SET_BIT(Peri,Data,MPWM,PCR,WPROTEN)

#define GET_MPWM_PROT_UL_FLAG(Peri)                   GET_BIT(Peri,MPWM,PSR,ULPROT)
#define SET_MPWM_PROT_UL_FLAG(Peri,Data)              SET_BIT_KEY_BITNAME(Peri,MPWM_PROTECTION_ACCESS_KEY,PROTKEY,Data,MPWM,PSR,ULPROT)
#define GET_MPWM_PROT_VL_FLAG(Peri)                   GET_BIT(Peri,Data,MPWM,PSR,VLPROT)
#define SET_MPWM_PROT_VL_FLAG(Peri,Data)              SET_BIT_KEY_BITNAME(Peri,MPWM_PROTECTION_ACCESS_KEY,PROTKEY,Data,MPWM,PSR,VLPROT)
#define GET_MPWM_PROT_WL_FLAG(Peri)                   GET_BIT(Peri,Data,MPWM,PSR,WLPROT)
#define SET_MPWM_PROT_WL_FLAG(Peri,Data)              SET_BIT_KEY_BITNAME(Peri,MPWM_PROTECTION_ACCESS_KEY,PROTKEY,Data,MPWM,PSR,WLPROT)
#define GET_MPWM_PROT_UH_FLAG(Peri)                   GET_BIT(Peri,Data,MPWM,PSR,UHPROT)
#define SET_MPWM_PROT_UH_FLAG(Peri,Data)              SET_BIT_KEY_BITNAME(Peri,MPWM_PROTECTION_ACCESS_KEY,PROTKEY,Data,MPWM,PSR,UHPROT)
#define GET_MPWM_PROT_VH_FLAG(Peri)                   GET_BIT(Peri,Data,MPWM,PSR,VHPROT)
#define SET_MPWM_PROT_VH_FLAG(Peri,Data)              SET_BIT_KEY_BITNAME(Peri,MPWM_PROTECTION_ACCESS_KEY,PROTKEY,Data,MPWM,PSR,VHPROT)
#define GET_MPWM_PROT_WH_FLAG(Peri)                   GET_BIT(Peri,Data,MPWM,PSR,WHPROT)
#define SET_MPWM_PROT_WH_FLAG(Peri,Data)              SET_BIT_KEY_BITNAME(Peri,MPWM_PROTECTION_ACCESS_KEY,PROTKEY,Data,MPWM,PSR,WHPROT)
#define GET_MPWM_PROT_SR(Peri)                        GET_REG(Peri,PSR)
#define SET_MPWM_PROT_SR(Peri,Data)                   SET_REG(Peri,Data,PSR)

#define SET_MPWM_OV_UL_OUTPUT(Peri,Data)              SET_BIT(Peri,Data,MPWM,OCR,ULOVINM)
#define SET_MPWM_OV_VL_OUTPUT(Peri,Data)              SET_BIT(Peri,Data,MPWM,OCR,VLOVINM)
#define SET_MPWM_OV_WL_OUTPUT(Peri,Data)              SET_BIT(Peri,Data,MPWM,OCR,WLOVINM)
#define SET_MPWM_OV_UH_OUTPUT(Peri,Data)              SET_BIT(Peri,Data,MPWM,OCR,UHOVINM)
#define SET_MPWM_OV_VH_OUTPUT(Peri,Data)              SET_BIT(Peri,Data,MPWM,OCR,VHOVINM)
#define SET_MPWM_OV_WH_OUTPUT(Peri,Data)              SET_BIT(Peri,Data,MPWM,OCR,WHOVINM)
#define SET_MPWM_OV_PWM_U_DEBOUNCE(Peri,Data)         SET_BIT(Peri,Data,MPWM,OCR,OVIND)
#define SET_MPWM_OV_PWM_U_POL(Peri,Data)              SET_BIT(Peri,Data,MPWM,OCR,OVINPOL)
#define SET_MPWM_OV_PWM_U_EN(Peri,Data)               SET_BIT(Peri,Data,MPWM,OCR,OVINEN)
#define SET_MPWM_OV_V_DEBOUNCE(Peri,Data)             SET_BIT(Peri,Data,MPWM,OCR,VOVIND)
#define SET_MPWM_OV_V_POL(Peri,Data)                  SET_BIT(Peri,Data,MPWM,OCR,VOVINPOL)
#define SET_MPWM_OV_V_EN(Peri,Data)                   SET_BIT(Peri,Data,MPWM,OCR,VOVINEN)
#define SET_MPWM_OV_W_DEBOUNCE(Peri,Data)             SET_BIT(Peri,Data,MPWM,OCR,WOVIND)
#define SET_MPWM_OV_W_POL(Peri,Data)                  SET_BIT(Peri,Data,MPWM,OCR,WOVINPOL)
#define SET_MPWM_OV_W_EN(Peri,Data)                   SET_BIT(Peri,Data,MPWM,OCR,WOVINEN)

#define GET_MPWM_OV_UL_FLAG(Peri)                     GET_BIT(Peri,Data,MPWM,OSR,ULOVIN)
#define SET_MPWM_OV_UL_FLAG(Peri,Data)                SET_BIT_KEY_BITNAME(Peri,MPWM_OVERVOLTAGE_ACCESS_KEY,OVINKEY,Data,MPWM,OSR,ULOVIN)
#define GET_MPWM_OV_VL_FLAG(Peri)                     GET_BIT(Peri,Data,MPWM,OSR,VLOVIN)
#define SET_MPWM_OV_VL_FLAG(Peri,Data)                SET_BIT_KEY_BITNAME(Peri,MPWM_OVERVOLTAGE_ACCESS_KEY,OVINKEY,Data,MPWM,OSR,VLOVIN)
#define GET_MPWM_OV_WL_FLAG(Peri)                     GET_BIT(Peri,Data,MPWM,OSR,WLOVIN)
#define SET_MPWM_OV_WL_FLAG(Peri,Data)                SET_BIT_KEY_BITNAME(Peri,MPWM_OVERVOLTAGE_ACCESS_KEY,OVINKEY,Data,MPWM,OSR,WLOVIN)
#define GET_MPWM_OV_UH_FLAG(Peri)                     GET_BIT(Peri,Data,MPWM,OSR,UHOVIN)
#define SET_MPWM_OV_UH_FLAG(Peri,Data)                SET_BIT_KEY_BITNAME(Peri,MPWM_OVERVOLTAGE_ACCESS_KEY,OVINKEY,Data,MPWM,OSR,UHOVIN)
#define GET_MPWM_OV_VH_FLAG(Peri)                     GET_BIT(Peri,Data,MPWM,OSR,VHOVIN)
#define SET_MPWM_OV_VH_FLAG(Peri,Data)                SET_BIT_KEY_BITNAME(Peri,MPWM_OVERVOLTAGE_ACCESS_KEY,OVINKEY,Data,MPWM,OSR,VHOVIN)
#define GET_MPWM_OV_WH_FLAG(Peri)                     GET_BIT(Peri,Data,MPWM,OSR,WHOVIN)
#define SET_MPWM_OV_WH_FLAG(Peri,Data)                SET_BIT_KEY_BITNAME(Peri,MPWM_OVERVOLTAGE_ACCESS_KEY,OVINKEY,Data,MPWM,OSR,WHOVIN)
#define GET_MPWM_OV_SR(Peri)                          GET_REG(Peri,OSR)
#define SET_MPWM_OV_SR(Peri,Data)                     SET_REG(Peri,Data,OSR)

#define GET_MPWM_ADCTRG_BASE_ADDR(Peri)               GET_REG_ADDR(Peri,ATR1)
#define SET_MPWM_ADCTRG_CNT(Addr,Data,Offset)         SET_BIT_ADDR_OFFSET(Addr,Offset,Data,MPWM,ATR1,ATCNT)
#define SET_MPWM_ADCTRG_MODE(Addr,Data,Offset)        SET_BIT_ADDR_OFFSET(Addr,Offset,Data,MPWM,ATR1,ATMOD)
#define SET_MPWM_ADCTRG_UPDATE(Addr,Data,Offset)      SET_BIT_ADDR_OFFSET(Addr,Offset,Data,MPWM,ATR1,ATUDT)
#define SET_MPWM_ADCTRG_SRC(Addr,Data,Offset)         SET_BIT_ADDR_OFFSET(Addr,Offset,Data,MPWM,ATR1,ATSRC)

#define SET_MPWM_DR_PERIOD_VAL(Peri,Data)             SET_REG(Peri,Data,PRD)
#define SET_MPWM_DR_DUTY_UH_VAL(Peri,Data)            SET_REG(Peri,Data,DUH)
#define SET_MPWM_DR_DUTY_VH_VAL(Peri,Data)            SET_REG(Peri,Data,DVH)
#define SET_MPWM_DR_DUTY_WH_VAL(Peri,Data)            SET_REG(Peri,Data,DWH)
#define SET_MPWM_DR_DUTY_UL_VAL(Peri,Data)            SET_REG(Peri,Data,DUL)
#define SET_MPWM_DR_DUTY_VL_VAL(Peri,Data)            SET_REG(Peri,Data,DVL)
#define SET_MPWM_DR_DUTY_WL_VAL(Peri,Data)            SET_REG(Peri,Data,DWL)
#define SET_MPWM_DR_PERIOD_U_VAL(Peri,Data)           SET_REG(Peri,Data,PRDU)
#define SET_MPWM_DR_PERIOD_V_VAL(Peri,Data)           SET_REG(Peri,Data,PRDV)
#define SET_MPWM_DR_PERIOD_W_VAL(Peri,Data)           SET_REG(Peri,Data,PRDW)
#define GET_MPWM_DR_COUNTER(Peri,Data)                GET_REG(Peri,CNT)
#define GET_MPWM_DR_COUNTER_U(Peri,Data)              GET_REG(Peri,CNTU)
#define GET_MPWM_DR_COUNTER_V(Peri,Data)              GET_REG(Peri,CNTV)
#define GET_MPWM_DR_COUNTER_W(Peri,Data)              GET_REG(Peri,CNTW)

#define GET_MPWM_SR_SIG_W_CNT_MODE(Peri)              GET_BIT(Peri,Data,MPWM,SR,WDOWN)
#define GET_MPWM_SR_SIG_W_PERIOD_MATCH_CNT(Peri)      GET_BIT(Peri,Data,MPWM,SR,IRQWCNT)
#define GET_MPWM_SR_SIG_V_CNT_MODE(Peri)              GET_BIT(Peri,Data,MPWM,SR,VDOWN)
#define GET_MPWM_SR_SIG_V_PERIOD_MATCH_CNT(Peri)      GET_BIT(Peri,Data,MPWM,SR,IRQVCNT)
#define GET_MPWM_SR_SIG_U_CNT_MODE(Peri)              GET_BIT(Peri,Data,MPWM,SR,UDOWN)
#define GET_MPWM_SR_SIG_U_PERIOD_MATCH_CNT(Peri)      GET_BIT(Peri,Data,MPWM,SR,IRQUCNT)

/* Interrup Bit Macro */
#define SET_MPWM_IER_UL_ATR1_EN(Peri,Data)            SET_BIT(Peri,Data,MPWM,IER,ULIE_ATR1IE)
#define SET_MPWM_IER_VL_ATR2_EN(Peri,Data)            SET_BIT(Peri,Data,MPWM,IER,VLIE_ATR2IE)
#define SET_MPWM_IER_WL_ATR3_EN(Peri,Data)            SET_BIT(Peri,Data,MPWM,IER,WLIE_ATR3IE)
#define SET_MPWM_IER_UH_ATR4_EN(Peri,Data)            SET_BIT(Peri,Data,MPWM,IER,UHIE_ATR4IE)
#define SET_MPWM_IER_VH_ATR5_EN(Peri,Data)            SET_BIT(Peri,Data,MPWM,IER,VHIE_ATR5IE)
#define SET_MPWM_IER_WH_ATR6_EN(Peri,Data)            SET_BIT(Peri,Data,MPWM,IER,WHIE_ATR6IE)
#define SET_MPWM_IER_PROT_EN(Peri,Data)               SET_BIT(Peri,Data,MPWM,PCR,PROTIE)
#define SET_MPWM_IER_OV_EN(Peri,Data)                 SET_BIT(Peri,Data,MPWM,OCR,OVINIE)
#define SET_MPWM_IER_BOTTOM_U_EN(Peri,Data)           SET_BIT(Peri,Data,MPWM,IER,BOTUIE)
#define SET_MPWM_IER_PERIOD_U_EN(Peri,Data)           SET_BIT(Peri,Data,MPWM,IER,PRDUIE)
#define SET_MPWM_IER_BOTTOM_V_EN(Peri,Data)           SET_BIT(Peri,Data,MPWM,IER,BOTVIE)
#define SET_MPWM_IER_PERIOD_V_EN(Peri,Data)           SET_BIT(Peri,Data,MPWM,IER,PRDVIE)
#define SET_MPWM_IER_BOTTOM_W_EN(Peri,Data)           SET_BIT(Peri,Data,MPWM,IER,BOTWIE)
#define SET_MPWM_IER_PERIOD_W_EN(Peri,Data)           SET_BIT(Peri,Data,MPWM,IER,PRDWIE)
#define SET_MPWM_IER_SIG_ATR(Peri,Data)               SET_REG(Peri,Data,IER)
#define SET_MPWM_IER_SIG_ATR_MSK(Peri,Data,Mask)      SET_REG_MASK(Peri,Data,Mask,IER)
#define GET_MPWM_IER_SIG_ATR(Peri)                    GET_REG(Peri,IER)
#define GET_MPWM_IER_PERIOD_U_FLAG(Peri)              GET_BIT(Peri,MPWM,SR,PRDUIF)
#define SET_MPWM_IER_PERIOD_U_FLAG(Peri,Data)         SET_BIT(Peri,Data,MPWM,SR,PRDUIF)
#define GET_MPWM_IER_BOTTOM_U_FLAG(Peri)              GET_BIT(Peri,MPWM,SR,BOTUIF)
#define SET_MPWM_IER_BOTTOM_U_FLAG(Peri,Data)         SET_BIT(Peri,Data,MPWM,SR,BOTUIF)
#define GET_MPWM_IER_PERIOD_V_FLAG(Peri)              GET_BIT(Peri,MPWM,SR,PRDVIF)
#define SET_MPWM_IER_PERIOD_V_FLAG(Peri,Data)         SET_BIT(Peri,Data,MPWM,SR,PRDVIF)
#define GET_MPWM_IER_BOTTOM_V_FLAG(Peri)              GET_BIT(Peri,MPWM,SR,BOTVIF)
#define SET_MPWM_IER_BOTTOM_V_FLAG(Peri,Data)         SET_BIT(Peri,Data,MPWM,SR,BOTVIF)
#define GET_MPWM_IER_PERIOD_W_FLAG(Peri)              GET_BIT(Peri,MPWM,SR,PRDWIF)
#define SET_MPWM_IER_PERIOD_W_FLAG(Peri,Data)         SET_BIT(Peri,Data,MPWM,SR,PRDWIF)
#define GET_MPWM_IER_BOTTOM_W_FLAG(Peri)              GET_BIT(Peri,MPWM,SR,BOTWIF)
#define SET_MPWM_IER_BOTTOM_W_FLAG(Peri,Data)         SET_BIT(Peri,Data,MPWM,SR,BOTWIF)
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
#define SET_SCU_MPWM_MCCR_SEL(Peri,Id,Data)           SET_BIT_OFFSET(Peri,(Id*MPWM_MCCR_BIT_OFFSET),Data,SCU,MCCR2,MPWM0CSEL)
#define SET_SCU_MPWM_MCCR_DIV(Peri,Id,Data)           SET_BIT_OFFSET(Peri,(Id*MPWM_MCCR_BIT_OFFSET),Data,SCU,MCCR2,MPWM0CDIV)
#define SET_SCU_MPWM_PER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PER2,MPWM0)
#define SET_SCU_MPWM_PCER(Peri,Id,Data)               SET_BIT_ID(Peri,Id,Data,SCU,PCER2,MPWM0)

#endif /* _HAL_MPWM_V_01_00_00_H_ */
