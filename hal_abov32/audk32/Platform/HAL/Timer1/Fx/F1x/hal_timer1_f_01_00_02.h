/**
 *******************************************************************************
 * @file        hal_timer1_f_01_00_02.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.02 typed Timer1
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER1_F_01_00_02_H_
#define _HAL_TIMER1_F_01_00_02_H_

/* Feature(Function) Configuration Define */
#define TIMER1_FEATURE_PAUSE
#define TIMER1_FEATURE_IRQ_UNMASK_ENABLE
#if (CONFIG_TIMER1_REG_NAME == 1)
#define TIMER1_FEATURE_SUPPORT_MULTI_IRQ
#endif

/* Configuration Define from config_xxx.h */

/* Internal Macro */
typedef TIMER1n_Type                                  TIMER1_Type;
#define TIMER1_REG_BASE                               TIMER10_BASE
#if (CONFIG_TIMER1_REG_NAME == 1)
#define TIMER1_REG_OFFSET                             0x80
#define TIMER1_ID_SKIP_CNT                            4
#else
#define TIMER1_REG_OFFSET                             0x100
#define TIMER1_ID_SKIP_CNT                            3
#endif
#define TIMER1_REG_TIMER_OFFSET                       0x300
#define TIMER1_REG_OFFSET_CNT                         11
#define TIMER1_CLK_SRC_INT                            0x00
#define TIMER1_CLK_SRC_EXT                            0x01
#define TIMER1_POLARITY_LOW                           0x01
#define TIMER1_POLARITY_HIGH                          0x00
#define TIMER1_ONLY_PWM_PERIOD                        1          
#define TIMER1_PRESCALE_MAX                           4096

/* Bit/Register Macro */
#define SET_TIMER1_PREDR(Peri,Data)                   SET_REG(Peri,Data,PREDR)
#define GET_TIMER1_PREDR(Peri)                        GET_REG(Peri,PREDR)
#define SET_TIMER1_DR_A(Peri,Data)                    SET_REG(Peri,Data,ADR)
#define GET_TIMER1_DR_A(Peri)                         GET_REG(Peri,ADR)
#define SET_TIMER1_DR_B(Peri,Data)                    SET_REG(Peri,Data,BDR)
#define GET_TIMER1_DR_B(Peri)                         GET_REG(Peri,BDR)
#define GET_TIMER1_DR_CAPA(Peri)                      GET_REG(Peri,CAPDR)
#define GET_TIMER1_DR_CAPB(Peri)                      GET_REG(Peri,CAPDR)
#define SET_TIMER1_DR_DUTY(Peri,Data)                 SET_TIMER1_DR_B(Peri,Data)
#define SET_TIMER1_DR_PERIOD(Peri,Data)               SET_TIMER1_DR_A(Peri,Data)
#define SET_TIMER1_CR(Peri,Data)                      SET_REG(Peri,Data,CR)
#define GET_TIMER1_CNT(Peri)                          GET_REG(Peri,CNT)

#define SET_TIMER1_CR_MODE(Peri,Data)                 SET_BIT(Peri,Data,TIMER1n,CR,T1nMS)
#define GET_TIMER1_CR_MODE(Peri)                      GET_BIT(Peri,TIMER1n,CR,T1nMS)
#define SET_TIMER1_CR_EN(Peri,Data)                   SET_BIT(Peri,Data,TIMER1n,CR,T1nEN)
#define GET_TIMER1_CR_EN(Peri)                        GET_BIT(Peri,TIMER1n,CR,T1nEN)
#define SET_TIMER1_CR_OUTPORT_POL(Peri,Data)          SET_BIT(Peri,Data,TIMER1n,CR,T1nOPOL)
#define GET_TIMER1_CR_OUTPORT_POL(Peri)               GET_BIT(Peri,TIMER1n,CR,T1nOPOL)
#define SET_TIMER1_CR_CAPPORT_POL(Peri,Data)          SET_BIT(Peri,Data,TIMER1n,CR,T1nCPOL)
#define GET_TIMER1_CR_CAPPORT_POL(Peri)               GET_BIT(Peri,TIMER1n,CR,T1nCPOL)
#define SET_TIMER1_CR_CLK(Peri,Data)                  SET_BIT(Peri,Data,TIMER1n,CR,T1nCLK)
#define GET_TIMER1_CR_CLK(Peri)                       GET_BIT(Peri,TIMER1n,CR,T1nCLK)
#define SET_TIMER1_CR_CLR(Peri,Data)                  SET_BIT(Peri,Data,TIMER1n,CR,T1nCLR)
#define GET_TIMER1_CR_CLR(Peri)                       GET_BIT(Peri,TIMER1n,CR,T1nCLR)
#define SET_TIMER1_CR_PAUSE(Peri,Data)                SET_BIT(Peri,Data,TIMER1n,CR,T1nPAU)
#define SET_TIMER1_CR_EXTCLK_EDGE(Peri,Data)          SET_BIT(Peri,Data,TIMER1n,CR,T1nECE)

/* Interrupt Macro */
#define SET_TIMER1_IER_MATCH_FLAG(Peri,Data)          SET_BIT(Peri,Data,TIMER1n,CR,T1nMIFLAG)
#define GET_TIMER1_IER_MATCH_FLAG(Peri)               GET_BIT(Peri,TIMER1n,CR,T1nMIFLAG)
#define SET_TIMER1_IER_CAP_FLAG(Peri,Data)            SET_BIT(Peri,Data,TIMER1n,CR,T1nCIFLAG)
#define GET_TIMER1_IER_CAP_FLAG(Peri)                 GET_BIT(Peri,TIMER1n,CR,T1nCIFLAG)
#define SET_TIMER1_IER_MATCH_EN(Peri,Data)            SET_BIT(Peri,Data,TIMER1n,CR,T1nMIEN)
#define SET_TIMER1_IER_CAP_EN(Peri,Data)              SET_BIT(Peri,Data,TIMER1n,CR,T1nCIEN)
#define GET_TIMER1_IER_MATCH_EN(Peri)                 GET_BIT(Peri,TIMER1n,CR,T1nMIEN)
#define GET_TIMER1_IER_CAP_EN(Peri)                   GET_BIT(Peri,TIMER1n,CR,T1nCIEN)
#define SET_TIMER1_IER_CLR(Peri) \
                                                      (Peri->CR = (Peri->CR & ~(BIT_NAME_MSK(TIMER1n_,CR_,T1nMIEN_) \
                                                      | BIT_NAME_MSK(TIMER1n_,CR_,T1nCIEN_))))

/* Unused Macro */
#define SET_TIMER1_CR_IOPORT_SEL(Peri,Data)           (void)Peri
#define GET_TIMER1_CR_IOPORT_SEL(Peri)                0
#define SET_TIMER1_CR_OUTPORT_INV(Peri,Data)          (void)Peri
#define GET_TIMER1_CR_OUTPORT_INV(Peri)               0
#define SET_TIMER1_CR_T30_SSYNC(Peri,Data)            (void)Peri
#define SET_TIMER1_CR_T30_CSYNC(Peri,Data)            (void)Peri

/* SCU Macro */
typedef SCUCG_Type                                    SCU_Type;
#define SCU_ADDR                                      SCUCG_BASE
#define TIMER1_PCER(x)                                (x < 3 ? x + 16 : x + 5)
#define SET_SCU_TIMER1_PER(Peri,Id,Data)              (void)Peri
#define SET_SCU_TIMER1_PCER(Peri,Id,Data)             SET_BIT_ID(Peri,TIMER1_PCER(Id),Data,SCUCG,PPCLKEN1,PACLKE)
#define SET_SCU_PPCLKSR_T1XCLK(Peri,Data)             (void)Peri
#define SET_INTC_IRQ_UNMASK_EN(Peri,Irq,Data)         SET_BIT_ID(Peri,Irq,Data,INTC,MSK,IMSK0_LVI_ECCC)

#endif /* _HAL_TIMER1_F_01_00_02_H_ */
