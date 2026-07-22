/**
 *******************************************************************************
 * @file        hal_timer5_f_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed Timer5
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER5_F_01_00_00_H_
#define _HAL_TIMER5_F_01_00_00_H_

/* Feature(Function) Configuration Define */
#define TIMER5_FEATURE_ONLY_LSE_CLOCK
#define TIMER5_FEATURE_UNSUPPORT_MCCR_TIMER51
#define TIMER5_FEATURE_IRQ_UNMASK_ENABLE

/* Internal Macro */
typedef TIMER5n_Type                                  TIMER5_Type;
#define TIMER5_REG_BASE                               TIMER50_BASE
#define TIMER5_REG_OFFSET                             0x100
#define TIMER5_REG_OFFSET_CNT                         0
#define TIMER5_CLK_SRC_INT                            0x00
#define TIMER5_CLK_SRC_EXT                            0x01
#define TIMER5_CLK_MCCR_SRC_LSE                       0x03
#define TIMER5_CLK_MCCR_SRC_HSI                       0x02
#define TIMER5_POLARITY_LOW                           0x01
#define TIMER5_POLARITY_HIGH                          0x00
#define TIMER5_ONLY_PWM_PERIOD                        1
#define TIMER5_PRESCALE_MAX                           4096
#define TIMER5_CAPTURE_SEL_POS                        9
#define TIMER5_CAPTURE_SEL_MSK                        (0x3UL << TIMER5_CAPTURE_SEL_POS)

/* Bit/Register Macro */
#define SET_TIMER5_PREDR(Peri,Data)                   SET_REG(Peri,Data,PREDR)
#define GET_TIMER5_PREDR(Peri)                        GET_REG(Peri,PREDR)
#define SET_TIMER5_DR_A(Peri,Data)                    SET_REG(Peri,Data,ADR)
#define GET_TIMER5_DR_A(Peri)                         GET_REG(Peri,ADR)
#define SET_TIMER5_DR_B(Peri,Data)                    SET_REG(Peri,Data,BDR)
#define GET_TIMER5_DR_B(Peri)                         GET_REG(Peri,BDR)
#define GET_TIMER5_DR_CAPA(Peri)                      GET_REG(Peri,CAPDR)
#define GET_TIMER5_DR_CAPB(Peri)                      GET_REG(Peri,CAPDR)
#define SET_TIMER5_DR_DUTY(Peri,Data)                 SET_TIMER5_DR_B(Peri,Data)
#define SET_TIMER5_DR_PERIOD(Peri,Data)               SET_TIMER5_DR_A(Peri,Data)
#define SET_TIMER5_CR(Peri,Data)                      SET_REG(Peri,Data,CR)
#define SET_TIMER5_CR_MODE(Peri,Data)                 SET_BIT(Peri,Data,TIMER5n,CR,T5nMS)
#define GET_TIMER5_CR_MODE(Peri)                      GET_BIT(Peri,TIMER5n,CR,T5nMS)
#define SET_TIMER5_CR_EN(Peri,Data)                   SET_BIT(Peri,Data,TIMER5n,CR,T5nEN)
#define GET_TIMER5_CR_EN(Peri)                        GET_BIT(Peri,TIMER5n,CR,T5nEN)
#define SET_TIMER5_CR_OUTPORT_POL(Peri,Data)          SET_BIT(Peri,Data,TIMER5n,CR,T5nOPOL)
#define GET_TIMER5_CR_OUTPORT_POL(Peri)               GET_BIT(Peri,TIMER5n,CR,T5nOPOL)
#define SET_TIMER5_CR_CAPPORT_POL(Peri,Data)          SET_BIT(Peri,Data,TIMER5n,CR,T5nINPOL)
#define GET_TIMER5_CR_CAPPORT_POL(Peri)               GET_BIT(Peri,TIMER5n,CR,T5nCPOL)
#define SET_TIMER5_CR_CLK(Peri,Data)                  SET_BIT(Peri,Data,TIMER5n,CR,T5nCLK)
#define GET_TIMER5_CR_CLK(Peri)                       GET_BIT(Peri,TIMER5n,CR,T5nCLK)
#define SET_TIMER5_CR_CLR(Peri,Data)                  SET_BIT(Peri,Data,TIMER5n,CR,T5nCLR)
#define GET_TIMER5_CR_CLR(Peri)                       GET_BIT(Peri,TIMER5n,CR,T5nCLR)
#define SET_TIMER5_CR_PAUSE(Peri,Data)                SET_BIT(Peri,Data,TIMER5n,CR,T5nPAU)
#define SET_TIMER5_CR_EXTCLK_EDGE(Peri,Data)          SET_BIT(Peri,Data,TIMER5n,CR,T5nECE)
#define SET_TIMER5_CR_CAP_SIG(Peri,Data)              SET_BIT(Peri,Data,TIMER5n,CR,T5nINSEL)
#define SET_TIMER5_CR_CAP_KEEPCNT(Peri,Data)          SET_BIT(Peri,Data,TIMER5n,CR,T5nCLEN)
#define CLEAR_TIMER5_CR(Peri)                         SET_REG(Peri,0,CR)

/* Interrup Bit Macro */
#define SET_TIMER5_IER_MATCH_EN(Peri,Data)            SET_BIT(Peri,Data,TIMER5n,CR,T5nMIEN)
#define GET_TIMER5_IER_MATCH_EN(Peri)                 GET_BIT(Peri,TIMER5n,CR,T5nMIEN)
#define SET_TIMER5_IER_CAP_EN(Peri,Data)              SET_BIT(Peri,Data,TIMER5n,CR,T5nCIEN)
#define GET_TIMER5_IER_CAP_EN(Peri)                   GET_BIT(Peri,TIMER5n,CR,T5nCIEN)
#define SET_TIMER5_IER_MATCH_FLAG(Peri,Data)          SET_BIT(Peri,Data,TIMER5n,CR,T5nMIFLAG)
#define GET_TIMER5_IER_MATCH_FLAG(Peri)               GET_BIT(Peri,TIMER5n,CR,T5nMIFLAG)
#define SET_TIMER5_IER_CAP_FLAG(Peri,Data)            SET_BIT(Peri,Data,TIMER5n,CR,T5nCIFLAG)
#define GET_TIMER5_IER_CAP_FLAG(Peri)                 GET_BIT(Peri,TIMER5n,CR,T5nCIFLAG)
#define SET_TIMER5_IER_CLR(Peri) \
                                                      SET_TIMER5_IER_MATCH_FLAG(Peri,0x01); \
                                                      SET_TIMER5_IER_CAP_FLAG(Peri,0x01)

/* Unused Macro */

/* SCU Define */
typedef SCUCG_Type                                    SCU_Type;
#define SCU_ADDR                                      SCUCG_BASE
#define SET_SCU_TIMER5_PER(Peri,Id,Data)              (void)Peri
#define SET_SCU_TIMER5_PCER(Peri,Id,Data)             SET_BIT_ID(Peri,Id,Data,SCUCG,PPCLKEN1,T50CLKE)
#define SET_SCU_TIMER5_PPCLKSR_CLK(Peri,Data)         SET_BIT(Peri,Data,SCUCG,PPCLKSR,T50CLK)
#define SET_INTC_IRQ_UNMASK_EN(Peri,Irq,Data)         SET_BIT_ID(Peri,Irq,Data,INTC,MSK,IMSK0_LVI)

#endif /* _HAL_TIMER5_F_01_00_00_H_ */
