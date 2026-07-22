/**
 *******************************************************************************
 * @file        hal_timer2_f_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed Timer2
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER2_F_01_00_00_H_
#define _HAL_TIMER2_F_01_00_00_H_

/* Feature(Function) Configuration Define */
#define TIMER2_FEATURE_UNSUPPORT_MCCR_TIMER21

/* Internal Macro */
typedef TIMER20_Type                                  TIMER2_Type;
#define TIMER2_REG_BASE                               TIMER20_BASE
#define TIMER2_REG_OFFSET                             0x100
#define TIMER2_REG_OFFSET_CNT                         0

#define TIMER2_CLK_SRC_INT                            0x00
#define TIMER2_CLK_SRC_EXT                            0x01
#define TIMER2_CLK_MCCR_SRC_LSI                       0x00
#define TIMER2_CLK_MCCR_SRC_LSE                       0x03
#define TIMER2_CLK_MCCR_SRC_MCLK                      0x04
#define TIMER2_CLK_MCCR_SRC_HSI                       0x05
#define TIMER2_CLK_MCCR_SRC_HSE                       0x06
#define TIMER2_CLK_MCCR_SRC_PLL                       0x07
#define TIMER2_POLARITY_LOW                           0x01
#define TIMER2_POLARITY_HIGH                          0x00
#define TIMER2_ONLY_PWM_PERIOD                        1
#define TIMER2_PRESCALE_MAX                           4096
#define TIMER2_CAPTURE_SEL_POS                        9
#define TIMER2_CAPTURE_SEL_MSK                        (0x3UL << TIMER2_CAPTURE_SEL_POS)

/* Bit/Register Macro */
#define SET_TIMER2_PREDR(Peri,Data)                   SET_REG(Peri,Data,PREDR)
#define GET_TIMER2_PREDR(Peri)                        GET_REG(Peri,PREDR)
#define SET_TIMER2_DR_A(Peri,Data)                    SET_REG(Peri,Data,ADR)
#define GET_TIMER2_DR_A(Peri)                         GET_REG(Peri,ADR)
#define SET_TIMER2_DR_B(Peri,Data)                    SET_REG(Peri,Data,BDR)
#define GET_TIMER2_DR_B(Peri)                         GET_REG(Peri,BDR)
#define GET_TIMER2_DR_CAPA(Peri)                      GET_REG(Peri,CAPDR)
#define GET_TIMER2_DR_CAPB(Peri)                      GET_REG(Peri,CAPDR)
#define SET_TIMER2_DR_DUTY(Peri,Data)                 SET_TIMER2_DR_B(Peri,Data)
#define SET_TIMER2_DR_PERIOD(Peri,Data)               SET_TIMER2_DR_A(Peri,Data)
#define SET_TIMER2_CR(Peri,Data)                      SET_REG(Peri,Data,CR)
#define SET_TIMER2_CR_MODE(Peri,Data)                 SET_BIT(Peri,Data,TIMER20,CR,TnMS)
#define GET_TIMER2_CR_MODE(Peri)                      GET_BIT(Peri,TIMER20,CR,TnMS)
#define SET_TIMER2_CR_EN(Peri,Data)                   SET_BIT(Peri,Data,TIMER20,CR,TnEN)
#define GET_TIMER2_CR_EN(Peri)                        GET_BIT(Peri,TIMER20,CR,TnEN)
#define SET_TIMER2_CR_OUTPORT_POL(Peri,Data)          SET_BIT(Peri,Data,TIMER20,CR,TnOPOL)
#define GET_TIMER2_CR_OUTPORT_POL(Peri)               GET_BIT(Peri,TIMER20,CR,TnOPOL)
#define SET_TIMER2_CR_CAPPORT_POL(Peri,Data)          SET_BIT(Peri,Data,TIMER20,CR,TnCPOL)
#define GET_TIMER2_CR_CAPPORT_POL(Peri)               GET_BIT(Peri,TIMER20,CR,TnCPOL)
#define SET_TIMER2_CR_CLK(Peri,Data)                  SET_BIT(Peri,Data,TIMER20,CR,TnCLK)
#define GET_TIMER2_CR_CLK(Peri)                       GET_BIT(Peri,TIMER20,CR,TnCLK)
#define SET_TIMER2_CR_CLR(Peri,Data)                  SET_BIT(Peri,Data,TIMER20,CR,TnCLR)
#define GET_TIMER2_CR_CLR(Peri)                       GET_BIT(Peri,TIMER20,CR,TnCLR)
#define SET_TIMER2_CR_PAUSE(Peri,Data)                SET_BIT(Peri,Data,TIMER20,CR,TnPAU)
#define SET_TIMER2_CR_EXTCLK_EDGE(Peri,Data)          SET_BIT(Peri,Data,TIMER20,CR,TnECE)
#define SET_TIMER2_CR_CAP_SIG(Peri,Data)              (Peri->CR = ((Peri->CR & ~(TIMER2_CAPTURE_SEL_MSK)) \
                                                      | (Data << TIMER2_CAPTURE_SEL_POS)))
#define CLEAR_TIMER2_CR(Peri)                         SET_REG(Peri,0,CR)

/* Interrup Macro */
#define SET_TIMER2_IER_MATCH_EN(Peri,Data)            SET_BIT(Peri,Data,TIMER20,CR,TnMIEN)
#define GET_TIMER2_IER_MATCH_EN(Peri)                 GET_BIT(Peri,TIMER20,CR,TnMIEN)
#define SET_TIMER2_IER_CAP_EN(Peri,Data)              SET_BIT(Peri,Data,TIMER20,CR,TnCIEN)
#define GET_TIMER2_IER_CAP_EN(Peri)                   GET_BIT(Peri,TIMER20,CR,TnCIEN)
#define SET_TIMER2_IER_MATCH_FLAG(Peri,Data)          SET_BIT(Peri,Data,TIMER20,CR,TnMIFLAG)
#define GET_TIMER2_IER_MATCH_FLAG(Peri)               GET_BIT(Peri,TIMER20,CR,TnMIFLAG)
#define SET_TIMER2_IER_CAP_FLAG(Peri,Data)            SET_BIT(Peri,Data,TIMER20,CR,TnCIFLAG)
#define GET_TIMER2_IER_CAP_FLAG(Peri)                 GET_BIT(Peri,TIMER20,CR,TnCIFLAG)
#define SET_TIMER2_IER_CLR(Peri) \
                                                      SET_TIMER2_IER_MATCH_FLAG(Peri,0x01); \
                                                      SET_TIMER2_IER_CAP_FLAG(Peri,0x01)

/* Unused Macro */
#define SET_TIMER2_CR_CAP_KEEPCNT(Peri,Data)          (void)Peri

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_TIMER2_MCCR_SEL0(Peri,Data)           SET_BIT(Peri,Data,SCU,MCCR2,TEXT2CSEL)
#define SET_SCU_TIMER2_MCCR_DIV0(Peri,Data)           SET_BIT(Peri,Data,SCU,MCCR2,TEXT2DIV)
#define SET_SCU_TIMER2_PPCLKSR_CLK0(Peri,Data)        SET_BIT(Peri,Data,SCU,PPCLKSR,T20CLK)
#define SET_SCU_TIMER2_PER(Peri,Id,Data)              SET_BIT_ID(Peri,Id,Data,SCU,PER1,TIMER20)
#define SET_SCU_TIMER2_PCER(Peri,Id,Data)             SET_BIT_ID(Peri,Id,Data,SCU,PCER1,TIMER20)

#endif /* _HAL_TIMER2_F_01_00_00_H_ */
