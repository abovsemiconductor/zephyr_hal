/**
 *******************************************************************************
 * @file        hal_timer1_f_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed Timer1
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER1_F_01_00_00_H_
#define _HAL_TIMER1_F_01_00_00_H_

/* Feature(Function) Configuration Define */
#define TIMER1_FEATURE_PAUSE
#define TIMER1_FEATURE_USE_MCCR_CLOCK

/* Configuration Define from config_xxx.h */
#define TIMER1_MCCR_NUM                               CONFIG_TIMER1_MCCR_NUM
#define TIMER1_MCCR_REG_COUNT                         CONFIG_TIMER1_MCCR_GROUP_COUNT

/* Internal Macro */
typedef TIMER1n_Type                                  TIMER1_Type;
#define TIMER1_REG_BASE                               TIMER10_BASE
#define TIMER1_REG_OFFSET                             0x100
#define TIMER1_REG_TIMER_OFFSET                       0x300
#define TIMER1_REG_OFFSET_CNT                         11
#define TIMER1_ID_SKIP_CNT                            3
#define TIMER1_CLK_SRC_INT                            0x00
#define TIMER1_CLK_SRC_EXT                            0x01
#define TIMER1_CLK_MCCR_SRC_LSI                       0x00
#define TIMER1_CLK_MCCR_SRC_LSE                       0x03
#define TIMER1_CLK_MCCR_SRC_MCLK                      0x04
#define TIMER1_CLK_MCCR_SRC_HSI                       0x05
#define TIMER1_CLK_MCCR_SRC_HSE                       0x06
#define TIMER1_CLK_MCCR_SRC_PLL                       0x07
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

#define SET_TIMER1_CR_MODE(Peri,Data)                 SET_BIT(Peri,Data,TIMER1n,CR,TnMS)
#define GET_TIMER1_CR_MODE(Peri)                      GET_BIT(Peri,TIMER1n,CR,TnMS)
#define SET_TIMER1_CR_EN(Peri,Data)                   SET_BIT(Peri,Data,TIMER1n,CR,TnEN)
#define GET_TIMER1_CR_EN(Peri)                        GET_BIT(Peri,TIMER1n,CR,TnEN)
#define SET_TIMER1_CR_OUTPORT_POL(Peri,Data)          SET_BIT(Peri,Data,TIMER1n,CR,TnOPOL)
#define GET_TIMER1_CR_OUTPORT_POL(Peri)               GET_BIT(Peri,TIMER1n,CR,TnOPOL)
#define SET_TIMER1_CR_CAPPORT_POL(Peri,Data)          SET_BIT(Peri,Data,TIMER1n,CR,TnCPOL)
#define GET_TIMER1_CR_CAPPORT_POL(Peri)               GET_BIT(Peri,TIMER1n,CR,TnCPOL)
#define SET_TIMER1_CR_CLK(Peri,Data)                  SET_BIT(Peri,Data,TIMER1n,CR,TnCLK)
#define GET_TIMER1_CR_CLK(Peri)                       GET_BIT(Peri,TIMER1n,CR,TnCLK)
#define SET_TIMER1_CR_CLR(Peri,Data)                  SET_BIT(Peri,Data,TIMER1n,CR,TnCLR)
#define GET_TIMER1_CR_CLR(Peri)                       GET_BIT(Peri,TIMER1n,CR,TnCLR)
#define SET_TIMER1_CR_PAUSE(Peri,Data)                SET_BIT(Peri,Data,TIMER1n,CR,TnPAU)
#define SET_TIMER1_CR_EXTCLK_EDGE(Peri,Data)          SET_BIT(Peri,Data,TIMER1n,CR,TnECE)

/* Interrupt Macro */
#define SET_TIMER1_IER_MATCH_FLAG(Peri,Data)          SET_BIT(Peri,Data,TIMER1n,CR,TnMIFLAG)
#define GET_TIMER1_IER_MATCH_FLAG(Peri)               GET_BIT(Peri,TIMER1n,CR,TnMIFLAG)
#define SET_TIMER1_IER_CAP_FLAG(Peri,Data)            SET_BIT(Peri,Data,TIMER1n,CR,TnCIFLAG)
#define GET_TIMER1_IER_CAP_FLAG(Peri)                 GET_BIT(Peri,TIMER1n,CR,TnCIFLAG)
#define SET_TIMER1_IER_MATCH_EN(Peri,Data)            SET_BIT(Peri,Data,TIMER1n,CR,TnMIEN)
#define SET_TIMER1_IER_CAP_EN(Peri,Data)              SET_BIT(Peri,Data,TIMER1n,CR,TnCIEN)
#define GET_TIMER1_IER_MATCH_EN(Peri)                 GET_BIT(Peri,TIMER1n,CR,TnMIEN)
#define GET_TIMER1_IER_CAP_EN(Peri)                   GET_BIT(Peri,TIMER1n,CR,TnCIEN)
#define SET_TIMER1_IER_CLR(Peri) \
                                                      (Peri->CR = (Peri->CR & ~(BIT_NAME_MSK(TIMER1n_,CR_,TnMIEN_) \
                                                      | BIT_NAME_MSK(TIMER1n_,CR_,TnCIEN_))))

/* Unused Macro */
#define SET_TIMER1_CR_IOPORT_SEL(Peri,Data)           (void)Peri
#define GET_TIMER1_CR_IOPORT_SEL(Peri)                0
#define SET_TIMER1_CR_OUTPORT_INV(Peri,Data)          (void)Peri
#define GET_TIMER1_CR_OUTPORT_INV(Peri)               0
#define SET_TIMER1_CR_T30_SSYNC(Peri,Data)            (void)Peri
#define SET_TIMER1_CR_T30_CSYNC(Peri,Data)            (void)Peri

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define GET_SCU_MCCR_BASE_ADDR(Peri)                  GET_REG_ADDR(Peri,MCCR1)
#define SET_SCU_TIMER1_MCCR_SEL(Addr,AOffset,DOffset,DMask,Data) \
                                                      SET_BIT_ADDR_DATA_MASK_OFFSET(Addr,AOffset,DOffset,DMask,Data)
#define SET_SCU_TIMER1_MCCR_DIV(Addr,AOffset,DOffset,DMask,Data) \
                                                      SET_BIT_ADDR_DATA_MASK_OFFSET(Addr,AOffset,DOffset,DMask,Data)
#if (TIMER1_MCCR_REG_COUNT > 0)
#define SCU_TIMER1_MCCR_0_DIV_POS                     16
#define SCU_TIMER1_MCCR_0_SEL_POS                     24
#endif

#define SCU_TIMER1_MCCR_SEL_MSK                       0x07
#define SCU_TIMER1_MCCR_DIV_MSK                       0xFF

#define SCU_TIMER1_MCCR_OFFSET                        ((TIMER1_MCCR_NUM-1)*4)
#define SCU_TIMER1_MCCR_GROUP_ID(x)                   (0)
#define SCU_TIMER1_MCCR_SEL_OFFSET(x)                 (SCU_TIMER1_MCCR_0_SEL_POS)
#define SCU_TIMER1_MCCR_DIV_OFFSET(x)                 (SCU_TIMER1_MCCR_0_DIV_POS)

#define SET_SCU_TIMER1_PER(Peri,Id,Data)              SET_BIT_ID(Peri,Id,Data,SCU,PER1,TIMER10)
#define SET_SCU_TIMER1_PCER(Peri,Id,Data)             SET_BIT_ID(Peri,Id,Data,SCU,PCER1,TIMER10)
#define SET_SCU_PPCLKSR_T1XCLK(Peri,Data)             SET_BIT(Peri,Data,SCU,PPCLKSR,T1xCLK)

#endif /* _HAL_TIMER1_F_01_00_00_H_ */
