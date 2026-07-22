/**
 *******************************************************************************
 * @file        hal_timer1_v_01_02_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.02.00 typed timer1
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER1_V_01_02_00_H_
#define _HAL_TIMER1_V_01_02_00_H_

/* Feature(Function) Configuration Define */
#if defined(CONFIG_SCU_CLK_LSE_NO_FEATURE)
#define TIMER1_FEATURE_UNSUPPORT_MCCR_LSE
#endif
#define TIMER1_FEATURE_OVERFLOW_INTERRUPT
#define TIMER1_FEATURE_CLEAR_CAPTURE_DATA
#define TIMER1_FEATURE_ADC_TRIGGER_CONFIG

/* Configuration Define from config_xxx.h */
#define TIMER1_MCCR_NUM                               CONFIG_TIMER1_MCCR_NUM
#define TIMER1_MCCR_REG_COUNT                         CONFIG_TIMER1_MCCR_GROUP_COUNT
#define TIMER1_MCCR_COUNT_PER_REG                     CONFIG_TIMER1_MCCR_COUNT_PER_GROUP

/* Internal Macro */
#if (CONFIG_TIMER1_REG_NAME == 1)
#else
typedef TIMER_Type                                    TIMER1_Type;
#endif
#define TIMER1_REG_BASE                               TIMER0_BASE
#define TIMER1_REG_OFFSET                             0x40
#define TIMER1_CLK_SRC_PDIV_2                         0x00
#define TIMER1_CLK_SRC_PDIV_4                         0x01
#define TIMER1_CLK_SRC_PDIV_16                        0x02
#define TIMER1_CLK_SRC_PDIV_64                        0x03
#define TIMER1_CLK_SRC_EXT                            0x07         /* External Input through IO pin */
#define TIMER1_CLK_SRC_MCCR                           0x04         /* MCCR Clock Source like HSI/HSE/LSI/LSE/PLL/MCLK */
#define TIMER1_CLK_MCCR_SRC_LSI                       0x00
#define TIMER1_CLK_MCCR_SRC_LSE                       0x01
#define TIMER1_CLK_MCCR_SRC_MCLK                      0x04
#define TIMER1_CLK_MCCR_SRC_HSI                       0x05
#define TIMER1_CLK_MCCR_SRC_HSE                       0x06
#define TIMER1_CLK_MCCR_SRC_PLL                       0x07
#define TIMER1_MD_COUNTER                             0x00
#define TIMER1_MD_PWM                                 0x01
#define TIMER1_MD_ONESHOT                             0x02
#define TIMER1_MD_CAPTURE                             0x03
#define TIMER1_ONLY_PWM_PERIOD                        0
#define TIMER1_PRESCALE_MAX                           1024

/* Bit/Register Macro */
#define SET_TIMER1_PREDR(Peri,Data)                   SET_REG(Peri,Data,PRS)
#define GET_TIMER1_PREDR(Peri)                        GET_REG(Peri,PRS)
#define SET_TIMER1_DR_A(Peri,Data)                    SET_REG(Peri,Data,GRA)
#define GET_TIMER1_DR_A(Peri)                         GET_REG(Peri,GRA)
#define SET_TIMER1_DR_B(Peri,Data)                    SET_REG(Peri,Data,GRB)
#define GET_TIMER1_DR_B(Peri)                         GET_REG(Peri,GRB)
#define GET_TIMER1_DR_CAPA(Peri)                      GET_REG(Peri,GRA)
#define GET_TIMER1_DR_CAPB(Peri)                      GET_REG(Peri,GRB)
#define SET_TIMER1_DR_DUTY(Peri,Data)                 SET_TIMER1_DR_A(Peri,Data)
#define SET_TIMER1_DR_PERIOD(Peri,Data)               SET_TIMER1_DR_B(Peri,Data)
#define GET_TIMER1_CNT(Peri)                          GET_REG(Peri,CNT)
#define SET_TIMER1_CR(Peri,Data) \
                                                      SET_REG(Peri,Data,CR1); \
                                                      SET_REG(Peri,Data,CR2)
#define SET_TIMER1_CR_MODE(Peri,Data)                 SET_BIT(Peri,Data,TIMER,CR1,MODE)
#define GET_TIMER1_CR_MODE(Peri)                      GET_BIT(Peri,TIMER,CR1,MODE)
#define SET_TIMER1_CR_EN(Peri,Data)                   SET_BIT(Peri,Data,TIMER,CR2,TEN)
#define GET_TIMER1_CR_EN(Peri)                        GET_BIT(Peri,TIMER,CR2,TEN)
#define SET_TIMER1_CR_OUTPORT_POL(Peri,Data)          SET_BIT(Peri,Data,TIMER,CR1,STARTLVL)
#define GET_TIMER1_CR_OUTPORT_OPOL(Peri)              GET_BIT(Peri,TIMER,CR1,STARTLVL)
#define SET_TIMER1_CR_CAPPORT_POL(Peri,Data)          SET_BIT(Peri,Data,TIMER,CR1,CLRMOD)
#define GET_TIMER1_CR_CAPPORT_POL(Peri)               GET_BIT(Peri,TIMER,CR1,CLRMOD)
#define SET_TIMER1_CR_CLK(Peri,Data)                  SET_BIT(Peri,Data,TIMER,CR1,CKSEL)
#define GET_TIMER1_CR_CLK(Peri)                       GET_BIT(Peri,TIMER,CR1,CKSEL)
#define SET_TIMER1_CR_CLR(Peri,Data)                  SET_BIT(Peri,Data,TIMER,CR2,TCLR)
#define GET_TIMER1_CR_CLR(Peri)                       GET_BIT(Peri,TIMER,CR2,TCLR)
#define SET_TIMER1_CR_IOPORT_SEL(Peri,Data)           SET_BIT(Peri,Data,TIMER,CR1,IOSEL)
#define GET_TIMER1_CR_IOPORT_SEL(Peri)                GET_BIT(Peri,TIMER,CR1,IOSEL)
#define SET_TIMER1_CR_OUTPORT_INV(Peri,Data)          SET_BIT(Peri,Data,TIMER,CR1,OUTPOL)
#define GET_TIMER1_CR_OUTPORT_INV(Peri)               GET_BIT(Peri,TIMER,CR1,OUTPOL)

#define SET_TIMER1_CR_ADCTRG_MODE(Peri,Data)          SET_BIT(Peri,Data,TIMER,CR1,TRGMOD)
#define SET_TIMER1_CR_ADCTRG_EN(Peri,Data)            SET_BIT(Peri,Data,TIMER,CR1,ADCTRGEN)
#define SET_TIMER1_DR_ADCTRG_PNT(Peri,Data)           SET_BIT(Peri,Data,TIMER,TRGPNT,TRGPNT)

/* Interrupt Macro */
#define SET_TIMER1_CR_OVF(Peri,Data)                  SET_BIT(Peri,Data,TIMER,SR,OVF)
#define GET_TIMER1_CR_OVF(Peri)                       GET_BIT(Peri,TIMER,SR,OVF)
#define SET_TIMER1_CR_MFA(Peri,Data)                  SET_BIT(Peri,Data,TIMER,SR,MFA)
#define GET_TIMER1_CR_MFA(Peri)                       GET_BIT(Peri,TIMER,SR,MFA)
#define SET_TIMER1_CR_MFB(Peri,Data)                  SET_BIT(Peri,Data,TIMER,SR,MFB)
#define GET_TIMER1_CR_MFB(Peri)                       GET_BIT(Peri,TIMER,SR,MFB)
#define SET_TIMER1_CR_OVIE(Peri,Data)                 SET_BIT(Peri,Data,TIMER,IER,OVIE)
#define GET_TIMER1_CR_OVIE(Peri)                      GET_BIT(Peri,TIMER,IER,OVIE)
#define SET_TIMER1_CR_MAIE(Peri,Data)                 SET_BIT(Peri,Data,TIMER,IER,MAIE)
#define GET_TIMER1_CR_MAIE(Peri)                      GET_BIT(Peri,TIMER,IER,MAIE)
#define SET_TIMER1_CR_MBIE(Peri,Data)                 SET_BIT(Peri,Data,TIMER,IER,MBIE)
#define GET_TIMER1_CR_MBIE(Peri)                      GET_BIT(Peri,TIMER,IER,MBIE)
#define SET_TIMER1_IER_MATCH_FLAG(Peri,Data) \
                                                      SET_TIMER1_CR_MFA(Peri,Data); \
                                                      SET_TIMER1_CR_MFB(Peri,Data)
#define SET_TIMER1_IER_CAP_FLAG(Peri,Data)            SET_TIMER1_IER_MATCH_FLAG(Peri,Data)
#define SET_TIMER1_IER_OVF_FLAG(Peri,Data)            SET_TIMER1_CR_OVF(Peri,Data)
#define SET_TIMER1_IER_MATCH_EN(Peri,Data) \
                                                      SET_TIMER1_CR_MAIE(Peri,Data); \
                                                      SET_TIMER1_CR_MBIE(Peri,Data)
#define SET_TIMER1_IER_CAP_EN(Peri,Data)              SET_TIMER1_IER_MATCH_EN(Peri,Data)
#define SET_TIMER1_IER_OVF_EN(Peri,Data)              SET_TIMER1_CR_OVIE(Peri,Data)

/* Unused Macro */
#define SET_TIMER1_CR_PAUSE(Peri,Data)                (void)Peri
#define SET_TIMER1_CR_EXTCLK_EDGE(Peri,Data)          (void)Peri
#define SET_TIMER1_IER_CLR(Peri)                      (void)Peri

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SCU_ENABLE(x)                                 (x)
#define SET_SCU_TIMER1_PER(Peri,Id,Data)              SET_BIT_ID(Peri,Id,Data,SCU,PER1,TIMER0)
#define SET_SCU_TIMER1_PCER(Peri,Id,Data)             SET_BIT_ID(Peri,Id,Data,SCU,PCER1,TIMER0)

#define GET_SCU_MCCR_BASE_ADDR(Peri)                  GET_REG_ADDR(Peri,MCCR1)
#define SET_SCU_TIMER1_MCCR_SEL(Addr,AOffset,DOffset,DMask,Data) \
                                                      SET_BIT_ADDR_DATA_MASK_OFFSET(Addr,AOffset,DOffset,DMask,Data)
#define SET_SCU_TIMER1_MCCR_DIV(Addr,AOffset,DOffset,DMask,Data) \
                                                      SET_BIT_ADDR_DATA_MASK_OFFSET(Addr,AOffset,DOffset,DMask,Data)
#define SCU_TIMER1_MCCR_BIT_OFFSET                    16
#define SCU_TIMER1_MCCR_DIV_START_POS                 0 
#define SCU_TIMER1_MCCR_SEL_START_POS                 8 

#define SCU_TIMER1_MCCR_SEL_MSK                       0x07
#define SCU_TIMER1_MCCR_DIV_MSK                       0xFF

#define SCU_TIMER1_MCCR_OFFSET                        ((TIMER1_MCCR_NUM-1)*4)
#define SCU_TIMER1_MCCR_GROUP_ID(x)                   (x < TIMER1_MCCR_COUNT_PER_REG ? 0 : 1)
#define SCU_TIMER1_MCCR_SEL_OFFSET(x)                 (SCU_TIMER1_MCCR_GROUP_ID(x)*SCU_TIMER1_MCCR_BIT_OFFSET \
                                                      + SCU_TIMER1_MCCR_SEL_START_POS)
#define SCU_TIMER1_MCCR_DIV_OFFSET(x)                 (SCU_TIMER1_MCCR_GROUP_ID(x)*SCU_TIMER1_MCCR_BIT_OFFSET \
                                                      + SCU_TIMER1_MCCR_DIV_START_POS)

#endif /* _HAL_TIMER1_V_01_02_00_H_ */
