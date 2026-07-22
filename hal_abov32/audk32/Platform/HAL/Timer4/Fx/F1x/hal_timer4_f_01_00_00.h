/**
 *******************************************************************************
 * @file        hal_timer4_f_01_00_00.h
 * @author      ABOV R&D Division 
 * @brief       Private APIs for ver 01.00.00 typed timer4
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER4_F_01_00_00_H_
#define _HAL_TIMER4_F_01_00_00_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
typedef TIMER40_Type                                  TIMER4_Type;
#define TIMER4_REG_BASE                               TIMER40_BASE
#define TIMER4_REG_OFFSET                             0x100
#define TIMER4_REG_OFFSET_CNT                         0
#define TIMER4_CLK_SRC_INT                            0x00
#define TIMER4_CLK_SRC_EXT                            0x01
#define TIMER4_CLK_MCCR_SRC_LSI                       0x00
#define TIMER4_CLK_MCCR_SRC_LSE                       0x03
#define TIMER4_CLK_MCCR_SRC_MCLK                      0x04
#define TIMER4_CLK_MCCR_SRC_HSI                       0x05
#define TIMER4_CLK_MCCR_SRC_HSE                       0x06
#define TIMER4_CLK_MCCR_SRC_PLL                       0x07
#define TIMER4_POLARITY_LOW                           0x01
#define TIMER4_POLARITY_HIGH                          0x00
#define TIMER4_ONLY_PWM_PERIOD                        1
#define TIMER4_PRESCALE_MAX                           4096

/* Bit/Register Macro */
#define SET_TIMER4_PREDR(Peri,Data)                   SET_REG(Peri,Data,PREDR)
#define GET_TIMER4_PREDR(Peri)                        GET_REG(Peri,PREDR)
#define SET_TIMER4_CAP_PREDR(Peri,Data)               SET_REG(Peri,Data,PREDR2)
#define GET_TIMER4_CAP_PREDR(Peri)                    GET_REG(Peri,PREDR2)
#define SET_TIMER4_DR_A(Peri,Data)                    SET_REG(Peri,Data,ADR)
#define GET_TIMER4_DR_A(Peri)                         GET_REG(Peri,ADR)
#define SET_TIMER4_DR_B(Peri,Data)                    SET_REG(Peri,Data,BDR)
#define GET_TIMER4_DR_B(Peri)                         GET_REG(Peri,BDR)
#define GET_TIMER4_DR_CAPA(Peri)                      GET_REG(Peri,CAPDR)
#define GET_TIMER4_DR_CAPB(Peri)                      GET_REG(Peri,CAPDR)
#define SET_TIMER4_DR_DUTY(Peri,Data)                 SET_TIMER4_DR_B(Peri,Data)
#define SET_TIMER4_DR_PERIOD(Peri,Data)               SET_TIMER4_DR_A(Peri,Data)
#define SET_TIMER4_CR(Peri,Data)                      SET_REG(Peri,Data,CR)
#define SET_TIMER4_CR_MODE(Peri,Data)                 SET_BIT(Peri,Data,TIMER40,CR,T40MS)
#define GET_TIMER4_CR_MODE(Peri)                      GET_BIT(Peri,TIMER40,CR,T40MS)
#define SET_TIMER4_CR_EN(Peri,Data)                   SET_BIT(Peri,Data,TIMER40,CR,T40EN)
#define GET_TIMER4_CR_EN(Peri)                        GET_BIT(Peri,TIMER40,CR,T40EN)
#define SET_TIMER4_CR_OUTPORT_POL(Peri,Data)          SET_BIT(Peri,Data,TIMER40,CR,T40OPOL)
#define GET_TIMER4_CR_OUTPORT_POL(Peri)               GET_BIT(Peri,TIMER40,CR,T40OPOL)
#define SET_TIMER4_CR_CAPPORT_POL(Peri,Data)          SET_BIT(Peri,Data,TIMER40,CR,T40CPOL)
#define GET_TIMER4_CR_CAPPORT_POL(Peri)               GET_BIT(Peri,TIMER40,CR,T40CPOL)
#define SET_TIMER4_CR_CLK(Peri,Data)                  SET_BIT(Peri,Data,TIMER40,CR,T40CLK)
#define GET_TIMER4_CR_CLK(Peri)                       GET_BIT(Peri,TIMER40,CR,T40CLK)
#define SET_TIMER4_CR_CLR(Peri,Data)                  SET_BIT(Peri,Data,TIMER40,CR,T40CLR)
#define GET_TIMER4_CR_CLR(Peri)                       GET_BIT(Peri,TIMER40,CR,T40CLR)
#define SET_TIMER4_CR_PAUSE(Peri,Data)                SET_BIT(Peri,Data,TIMER40,CR,T40PAU)
#define SET_TIMER4_CR_EXTCLK_EDGE(Peri,Data)          SET_BIT(Peri,Data,TIMER40,CR,T40ECE)
#define SET_TIMER4_CR_CAP_CH(Peri,Data)               SET_BIT(Peri,Data,TIMER40,CR,T40CAPCHSEL)
#define CLEAR_TIMER4_CR(Peri)                         SET_REG(Peri,0,CR)

/* Interrupt Macro */
#define SET_TIMER4_IER_MATCH_EN(Peri,Data)            SET_BIT(Peri,Data,TIMER40,CR,T40MIEN)
#define GET_TIMER4_IER_MATCH_EN(Peri)                 GET_BIT(Peri,TIMER40,CR,T40MIEN)
#define SET_TIMER4_IER_CAP_EN(Peri,Data)              SET_BIT(Peri,Data,TIMER40,CR,T40CIEN)
#define GET_TIMER4_IER_CAP_EN(Peri)                   GET_BIT(Peri,TIMER40,CR,T40CIEN)
#define SET_TIMER4_IER_MATCH_FLAG(Peri,Data)          SET_BIT(Peri,Data,TIMER40,CR,T40MIFLAG)
#define GET_TIMER4_IER_MATCH_FLAG(Peri)               GET_BIT(Peri,TIMER40,CR,T40MIFLAG)
#define SET_TIMER4_IER_CAP_FLAG(Peri,Data)            SET_BIT(Peri,Data,TIMER40,CR,T40CIFLAG)
#define GET_TIMER4_IER_CAP_FLAG(Peri)                 GET_BIT(Peri,TIMER40,CR,T40CIFLAG)
#define SET_TIMER4_IER_CLR(Peri) \
                                                      SET_TIMER4_IER_MATCH_FLAG(Peri,0x01); \
                                                      SET_TIMER4_IER_CAP_FLAG(Peri,0x01)

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_TIMER4_MCCR_SEL(Peri,Data)            SET_BIT(Peri,Data,SCU,MCCR6,TEXT4CSEL)
#define SET_SCU_TIMER4_MCCR_DIV(Peri,Data)            SET_BIT(Peri,Data,SCU,MCCR6,TEXT4DIV)
#define SET_SCU_TIMER4_PPCLKSR_CLK(Peri,Data)         SET_BIT(Peri,Data,SCU,PPCLKSR,T40CLK)
#define SET_SCU_TIMER4_PER(Peri,Id,Data)              SET_BIT_ID(Peri,Id,Data,SCU,PER1,TIMER40)
#define SET_SCU_TIMER4_PCER(Peri,Id,Data)             SET_BIT_ID(Peri,Id,Data,SCU,PCER1,TIMER40)

#endif /* _HAL_TIMER4_F_01_00_00_H_ */
