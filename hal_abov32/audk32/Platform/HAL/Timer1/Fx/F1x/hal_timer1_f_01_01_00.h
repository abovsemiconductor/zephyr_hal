/**
 *******************************************************************************
 * @file        hal_timer1_f_01_01_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed Timer1
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER1_F_01_01_00_H_
#define _HAL_TIMER1_F_01_01_00_H_

/* Feature(Function) Configuration Define */
#define TIMER1_FEATURE_PAUSE
#define TIMER1_FEATURE_SYNC_TIMER3
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
#define GET_TIMER1_CNT(Peri)                          GET_REG(Peri,CNT)
#define SET_TIMER1_CR(Peri,Data)                      SET_REG(Peri,Data,CR)
#define SET_TIMER1_CR_MODE(Peri,Data)                 SET_BIT(Peri,Data,TIMER1n,CR,MS)
#define GET_TIMER1_CR_MODE(Peri)                      GET_BIT(Peri,TIMER1n,CR,MS)
#define SET_TIMER1_CR_EN(Peri,Data)                   SET_BIT(Peri,Data,TIMER1n,CR,EN)
#define GET_TIMER1_CR_EN(Peri)                        GET_BIT(Peri,TIMER1n,CR,EN)
#define SET_TIMER1_CR_OUTPORT_POL(Peri,Data)          SET_BIT(Peri,Data,TIMER1n,CR,OPOL)
#define GET_TIMER1_CR_OUTPORT_POL(Peri)               GET_BIT(Peri,TIMER1n,CR,OPOL)
#define SET_TIMER1_CR_CAPPORT_POL(Peri,Data)          SET_BIT(Peri,Data,TIMER1n,CR,CPOL)
#define GET_TIMER1_CR_CAPPORT_POL(Peri)               GET_BIT(Peri,TIMER1n,CR,CPOL)
#define SET_TIMER1_CR_CLK(Peri,Data)                  SET_BIT(Peri,Data,TIMER1n,CR,CLK)
#define GET_TIMER1_CR_CLK(Peri)                       GET_BIT(Peri,TIMER1n,CR,CLK)
#define SET_TIMER1_CR_CLR(Peri,Data)                  SET_BIT(Peri,Data,TIMER1n,CR,CLR)
#define GET_TIMER1_CR_CLR(Peri)                       GET_BIT(Peri,TIMER1n,CR,CLR)
#define SET_TIMER1_CR_PAUSE(Peri,Data)                SET_BIT(Peri,Data,TIMER1n,CR,PAU)
#define SET_TIMER1_CR_EXTCLK_EDGE(Peri,Data)          SET_BIT(Peri,Data,TIMER1n,CR,ECE)
#define SET_TIMER1_CR_T30_SSYNC(Peri,Data)            SET_BIT(Peri,Data,TIMER1n,CR,SSYNC)
#define SET_TIMER1_CR_T30_CSYNC(Peri,Data)            SET_BIT(Peri,Data,TIMER1n,CR,CSYNC)

/* Interrupt Macro */
#define SET_TIMER1_IER_MATCH_FLAG(Peri,Data)          SET_BIT(Peri,Data,TIMER1n,CR,MIFLAG)
#define GET_TIMER1_IER_MATCH_FLAG(Peri)               GET_BIT(Peri,TIMER1n,CR,MIFLAG)
#define SET_TIMER1_IER_CAP_FLAG(Peri,Data)            SET_BIT(Peri,Data,TIMER1n,CR,CIFLAG)
#define GET_TIMER1_IER_CAP_FLAG(Peri)                 GET_BIT(Peri,TIMER1n,CR,CIFLAG)
#define SET_TIMER1_IER_MATCH_EN(Peri,Data)            SET_BIT(Peri,Data,TIMER1n,CR,MIEN)
#define SET_TIMER1_IER_CAP_EN(Peri,Data)              SET_BIT(Peri,Data,TIMER1n,CR,CIEN)
#define GET_TIMER1_IER_MATCH_EN(Peri)                 GET_BIT(Peri,TIMER1n,CR,MIEN)
#define GET_TIMER1_IER_CAP_EN(Peri)                   GET_BIT(Peri,TIMER1n,CR,CIEN)
#define SET_TIMER1_IER_CLR(Peri) \
                                                      (Peri->CR = (Peri->CR & ~(BIT_NAME_MSK(TIMER1n_,CR_,MIEN_) \
                                                      | BIT_NAME_MSK(TIMER1n_,CR_,CIEN_))))

/* Unused Macro */
#define SET_TIMER1_CR_IOPORT_SEL(Peri,Data)           (void)Peri
#define GET_TIMER1_CR_IOPORT_SEL(Peri)                0
#define SET_TIMER1_CR_OUTPORT_INV(Peri,Data)          (void)Peri
#define GET_TIMER1_CR_OUTPORT_INV(Peri)               0

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

#endif /* _HAL_TIMER1_F_01_01_00_H_ */
