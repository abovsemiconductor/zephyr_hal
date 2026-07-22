/**
 *******************************************************************************
 * @file        hal_timer1_v_01_00_00.h
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

#ifndef _HAL_TIMER1_V_01_00_00_H_
#define _HAL_TIMER1_V_01_00_00_H_

/* Feature(Function) Configuration Define */
#define TIMER1_FEATURE_UNSUPPORT_MCCR_PLL
#define TIMER1_FEATURE_UNSUPPORT_MCCR_MCLK
#define TIMER1_FEATURE_OVERFLOW_INTERRUPT

/* Configuration Define from config_xxx.h */
#define TIMER1_MCCR_NUM                               CONFIG_TIMER1_MCCR_NUM
#define TIMER1_MCCR_REG_COUNT                         CONFIG_TIMER1_MCCR_GROUP_COUNT
#define TIMER1_MCCR_COUNT_PER_REG                     CONFIG_TIMER1_MCCR_COUNT_PER_GROUP

/* Internal Macro */
typedef T0_Type                                       TIMER1_Type;
#define TIMER1_REG_BASE                               T0_BASE
#define TIMER1_REG_OFFSET                             0x20
#define TIMER1_REG_OFFSET_CNT                         0
#define TIMER1_CLK_SRC_PDIV_2                         0x00
#define TIMER1_CLK_SRC_PDIV_4                         0x01
#define TIMER1_CLK_SRC_PDIV_16                        0x02
#define TIMER1_CLK_SRC_PDIV_64                        0x03
#define TIMER1_CLK_SRC_EXT                            0x07         /* External Input through IO pin */
#define TIMER1_CLK_MCCR_SRC_HSE                       0x00
#define TIMER1_CLK_MCCR_SRC_HSI                       0x01
#define TIMER1_CLK_MCCR_SRC_LSE                       0x02
#define TIMER1_CLK_MCCR_SRC_LSI                       0x03
#define TIMER1_CLK_SRC_MCCR                           0x05         /* MCCR Clock Source like HSI/HSE/LSI/LSE/PLL/MCLK */
#define TIMER1_MD_COUNTER                             0x0
#define TIMER1_MD_PWM                                 0x1
#define TIMER1_MD_ONESHOT                             0x2
#define TIMER1_MD_CAPTURE                             0x3
#define TIMER1_ONLY_PWM_PERIOD                        0
#define TIMER1_PRESCALE_MAX                           1024

/* Bit/Register Macro */
#define SET_TIMER1_PREDR(Peri,Data)                   SET_REG(Peri,Data,PRS)
#define GET_TIMER1_PREDR(Peri)                        GET_REG(Peri,PRS)
#define SET_TIMER1_DR_A(Peri,Data)                    SET_REG(Peri,Data,GRA)
#define GET_TIMER1_DR_A(Peri)                         GET_REG(Peri,GRA)
#define GET_TIMER1_DR_CAPA(Peri)                      GET_REG(Peri,GRA)
#if (CONFIG_TIMER1_REG_NAME == 1)
#define SET_TIMER1_DR_B(Peri,Data)                    SET_REG(Peri,Data,GRB)
#define GET_TIMER1_DR_B(Peri)                         GET_REG(Peri,GRB)
#define GET_TIMER1_DR_CAPB(Peri)                      GET_REG(Peri,GRB)
#else
#define SET_TIMER1_DR_B(Peri,Data)                    SET_REG(Peri,Data,TnGRB)
#define GET_TIMER1_DR_B(Peri)                         GET_REG(Peri,TnGRB)
#define GET_TIMER1_DR_CAPB(Peri)                      GET_REG(Peri,TnGRB)
#endif
#define SET_TIMER1_DR_DUTY(Peri,Data)                 SET_TIMER1_DR_A(Peri,Data)
#define SET_TIMER1_DR_PERIOD(Peri,Data)               SET_TIMER1_DR_B(Peri,Data)
#define GET_TIMER1_CNT(Peri)                          GET_REG(Peri,CNT)
#define SET_TIMER1_CR(Peri,Data) \
                                                      SET_REG(Peri,Data,CON); \
                                                      SET_REG(Peri,Data,CMD);
#define SET_TIMER1_CR_MODE(Peri,Data)                 SET_BIT(Peri,Data,T0,CON,TMODE)
#define GET_TIMER1_CR_MODE(Peri)                      GET_BIT(Peri,T0,CON,TMODE)
#define SET_TIMER1_CR_EN(Peri,Data)                   SET_BIT(Peri,Data,T0,CMD,TEN)
#define GET_TIMER1_CR_EN(Peri)                        GET_BIT(Peri,T0,CMD,TEN)
#define SET_TIMER1_CR_OUTPORT_POL(Peri,Data)          SET_BIT(Peri,Data,T0,CON,TSTRT)
#define GET_TIMER1_CR_OUTPORT_POL(Peri)               GET_BIT(Peri,T0,CON,TSTRT)
#define SET_TIMER1_CR_CAPPORT_POL(Peri,Data)          SET_BIT(Peri,(Data&0x01),T0,CON,CAPM)
#define GET_TIMER1_CR_CAPPORT_POL(Peri)               GET_BIT(Peri,T0,CON,CAPM)
#define SET_TIMER1_CR_CLK(Peri,Data)                  SET_BIT(Peri,Data,T0,CON,TCS)
#define GET_TIMER1_CR_CLK(Peri)                       GET_BIT(Peri,T0,CON,TCS)
#define SET_TIMER1_CR_CLR(Peri,Data)                  SET_BIT(Peri,Data,T0,CMD,TCLR)
#define GET_TIMER1_CR_CLR(Peri)                       GET_BIT(Peri,T0,CMD,TCLR)

/* Interrupt Macro */
#define SET_TIMER1_CR_OVF(Peri,Data)                  SET_BIT(Peri,Data,T0,CON,TOVF)
#define GET_TIMER1_CR_OVF(Peri)                       GET_BIT(Peri,T0,CON,TOVF)
#define SET_TIMER1_CR_MFA(Peri,Data)                  SET_BIT(Peri,Data,T0,CON,TIF0)
#define GET_TIMER1_CR_MFA(Peri)                       GET_BIT(Peri,T0,CON,TIF0)
#define SET_TIMER1_CR_MFB(Peri,Data)                  SET_BIT(Peri,Data,T0,CON,TIF1)
#define GET_TIMER1_CR_MFB(Peri)                       GET_BIT(Peri,T0,CON,TIF1)
#define SET_TIMER1_CR_OVIE(Peri,Data)                 SET_BIT(Peri,Data,T0,CON,TOVE)
#define GET_TIMER1_CR_OVIE(Peri)                      GET_BIT(Peri,T0,CON,TOVE)
#define SET_TIMER1_CR_MAIE(Peri,Data)                 SET_BIT(Peri,Data,T0,CON,TIE0)
#define GET_TIMER1_CR_MAIE(Peri)                      GET_BIT(Peri,T0,CON,TIE0)
#define SET_TIMER1_CR_MBIE(Peri,Data)                 SET_BIT(Peri,Data,T0,CON,TIE1)
#define GET_TIMER1_CR_MBIE(Peri)                      GET_BIT(Peri,T0,CON,TIE1)
#define SET_TIMER1_IER_MATCH_FLAG(Peri,Data) \
                                                      SET_TIMER1_CR_MFA(Peri,Data); \
                                                      SET_TIMER1_CR_MFB(Peri,Data);
#define SET_TIMER1_IER_CAP_FLAG(Peri,Data)            SET_TIMER1_IER_MATCH_FLAG(Peri,Data)
#define SET_TIMER1_IER_OVF_FLAG(Peri,Data)            SET_TIMER1_CR_OVF(Peri,Data)
#define SET_TIMER1_IER_MATCH_EN(Peri,Data) \
                                                      SET_TIMER1_CR_MAIE(Peri,Data); \
                                                      SET_TIMER1_CR_MBIE(Peri,Data);
#define SET_TIMER1_IER_CAP_EN(Peri,Data)              SET_TIMER1_IER_MATCH_EN(Peri,Data)
#define SET_TIMER1_IER_OVF_EN(Peri,Data)              SET_TIMER1_CR_OVIE(Peri,Data)

/* Unused Macro */
#define SET_TIMER1_IER_CLR(Peri)                      (void)Peri
#define SET_TIMER1_CR_IOPORT_SEL(Peri,Data)           (void)Peri
#define GET_TIMER1_CR_IOPORT_SEL(Peri)                0
#define SET_TIMER1_CR_OUTPORT_INV(Peri,Data)          (void)Peri
#define GET_TIMER1_CR_OUTPORT_INV(Peri)               0
#define SET_TIMER1_CR_PAUSE(Peri,Data)                (void)Peri
#define SET_TIMER1_CR_EXTCLK_EDGE(Peri,Data)          (void)Peri

/* SCU Macro */
typedef PMU_Type                                      SCU_Type;
#define SCU_ADDR                                      PMU_BASE
#define SCU_ENABLE(x)                                 (x < 2 ? 0 : (x > 5) ? 2 : 1)
#define SET_SCU_TIMER1_PER(Peri,Id,Data)              SET_BIT_ID(Peri,Id,Data,PMU,PER,TIMER01)
#define SET_SCU_TIMER1_PCER(Peri,Id,Data)             SET_BIT_ID(Peri,Id,Data,PMU,PCCR,TIMER01)

#define GET_SCU_MCCR_BASE_ADDR(Peri)                  GET_REG_ADDR(Peri,PCSR)
#define SET_SCU_TIMER1_MCCR_SEL(Addr,AOffset,DOffset,DMask,Data) \
                                                      SET_BIT_ADDR_DATA_MASK_OFFSET(Addr,AOffset,DOffset,DMask,Data)
#define SET_SCU_TIMER1_MCCR_DIV(Addr,AOffset,DOffset,DMask,Data) \
                                                      (void)Addr

#define SCU_TIMER1_MCCR_BIT_OFFSET                    2
#define SCU_TIMER1_MCCR_SEL_START_POS                 4 

#define SCU_TIMER1_MCCR_SEL_MSK                       0x07

#define SCU_TIMER1_MCCR_OFFSET                        ((TIMER1_MCCR_NUM-1)*4)
#define SCU_TIMER1_MCCR_GROUP_ID(x)                   (x < 2 ? 0 : (x > 5) ? 2 : 1)
#define SCU_TIMER1_MCCR_SEL_OFFSET(x)                 (SCU_TIMER1_MCCR_GROUP_ID(x)*SCU_TIMER1_MCCR_BIT_OFFSET \
                                                      + SCU_TIMER1_MCCR_SEL_START_POS)
#define SCU_TIMER1_MCCR_DIV_OFFSET(x)                 0

#endif /* _HAL_TIMER1_V_01_00_00_H_ */
