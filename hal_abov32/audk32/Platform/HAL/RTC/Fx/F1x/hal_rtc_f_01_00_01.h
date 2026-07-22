/**
 *******************************************************************************
 * @file        hal_rtc_f_01_00_01.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.01 typed RTC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_RTC_F_01_00_01_H_
#define _HAL_RTC_F_01_00_01_H_

/* Feature(Function) Configuration Define */
#define RTC_FEATURE_IRQ_UNMASK_ENABLE

/* Internal Macro */
typedef RTCC_Type                                     RTC_Type;
#define RTC_REG_BASE                                  RTCC_BASE
#define RTC_IO_INTR_SUPPORT                           1
#define RTC_DELAY_MARGIN                              200
#define RTC_CLKOUT_1HZ                                0x00
#define RTC_CLKOUT_32KHZ                              0x01
#define RTC_INTR_CLEAR                                1

#define RTC_CLK_SRC_LSE                               0x01
#define RTC_CLK_SRC_WDTRC                             0x02
#define RTC_CLK_SRC_LSI                               0x02
#define RTC_CLK_SRC_MCLK                              0x03

/* Bit/Register Macro */
#define SET_RTC_CR_START(Peri,Data)                   SET_BIT(Peri,Data,RTCC,CR,RTEN)
#define GET_RTC_CR_START(Peri)                        GET_BIT(Peri,RTCC,CR,RTEN)
#define SET_RTC_CR_RWMODE(Peri,Data)                  SET_BIT(Peri,Data,RTCC,CR,RTWAIT)
#define GET_RTC_SR_RWMODE(Peri)                       GET_BIT(Peri,RTCC,CR,RTWST)

#define SET_RTC_CR_ERRCOR_DIR(Peri,Data)              SET_BIT(Peri,Data,RTCC,ECR,ECSIGN)
#define SET_RTC_CR_ERRCOR_TIME(Peri,Data)             SET_BIT(Peri,Data,RTCC,ECR,ECTM)
#define SET_RTC_DR_ERRCOR(Peri,Data)                  SET_BIT(Peri,Data,RTCC,ECR,ECV)

#define SET_RTC_CR_PORT_MODE(Peri,Data)               SET_BIT(Peri,Data,RTCC,CR,OUTSEL)
#define SET_RTC_CR_24HOUR(Peri,Data)                  SET_BIT(Peri,Data,RTCC,CR,HS24)

#define SET_RTC_DR_SEC(Peri,Data)                     SET_BIT(Peri,Data,RTCC,SEC,RSEC)
#define SET_RTC_DR_MIN(Peri,Data)                     SET_BIT(Peri,Data,RTCC,MIN,RMIN)
#define SET_RTC_DR_HOUR(Peri,Data)                    SET_BIT(Peri,Data,RTCC,HOUR,RHOUR)
#define SET_RTC_DR_DAY(Peri,Data)                     SET_BIT(Peri,Data,RTCC,DAY,RDAY)
#define SET_RTC_DR_WEEK(Peri,Data)                    SET_BIT(Peri,Data,RTCC,WEEK,RWEEK)
#define SET_RTC_DR_MONTH(Peri,Data)                   SET_BIT(Peri,Data,RTCC,MONTH,RMONTH)
#define SET_RTC_DR_YEAR(Peri,Data)                    SET_BIT(Peri,Data,RTCC,YEAR,RYEAR)
#define GET_RTC_DR_SEC(Peri)                          GET_BIT(Peri,RTCC,SEC,RSEC)
#define GET_RTC_DR_MIN(Peri)                          GET_BIT(Peri,RTCC,MIN,RMIN)
#define GET_RTC_DR_HOUR(Peri)                         GET_BIT(Peri,RTCC,HOUR,RHOUR)
#define GET_RTC_DR_DAY(Peri)                          GET_BIT(Peri,RTCC,DAY,RDAY)
#define GET_RTC_DR_WEEK(Peri)                         GET_BIT(Peri,RTCC,WEEK,RWEEK)
#define GET_RTC_DR_MONTH(Peri)                        GET_BIT(Peri,RTCC,MONTH,RMONTH)
#define GET_RTC_DR_YEAR(Peri)                         GET_BIT(Peri,RTCC,YEAR,RYEAR)
#define SET_RTC_DR_ALARM_MIN(Peri,Data)               SET_BIT(Peri,Data,RTCC,ALMIN,AMIN)
#define SET_RTC_DR_ALARM_HOUR(Peri,Data)              SET_BIT(Peri,Data,RTCC,ALHOUR,AHOUR)
#define SET_RTC_DR_ALARM_WEEK(Peri,Data)              SET_REG(Peri,Data,ALWEEK)


/* Interrupt Macro */
#define SET_RTC_IER_CONST_PERIOD_EN(Peri,Data)        SET_BIT(Peri,Data,RTCC,CR,RTIN)
#define SET_RTC_IER_CONST_PERIOD_FLAG(Peri,Data)      SET_BIT(Peri,Data,RTCC,CR,RTIFLAG)
#define GET_RTC_IER_CONST_PERIOD_FLAG(Peri)           GET_BIT(Peri,RTCC,CR,RTIFLAG)
#define SET_RTC_IER_ALARM_EN(Peri,Data)               SET_BIT(Peri,Data,RTCC,CR,ALIEN);\
                                                      SET_BIT(Peri,Data,RTCC,CR,ALEN)
#define SET_RTC_IER_ALARM_FLAG(Peri,Data)             SET_BIT(Peri,Data,RTCC,CR,ALIFLAG)
#define GET_RTC_IER_ALARM_FLAG(Peri)                  GET_BIT(Peri,RTCC,CR,ALIFLAG)

/* Unused Macro */
#define SET_RTC_CR_EN(Peri,Data)                      (void)Peri
#define SET_RTC_CR_ERRCOR_EN(Peri,Data)               (void)0
#define SET_RTC_DR_SUBSEC(Peri,Data)                  (void)0
#define SET_RTC_CR_TIMESTAMP_EDGE(Peri,Data)          (void)0
#define GET_RTC_DR_TIMESTAMP_SEC(Peri)                (void)Peri
#define GET_RTC_DR_TIMESTAMP_MIN(Peri)                (void)Peri
#define GET_RTC_DR_TIMESTAMP_HOUR(Peri)               (void)Peri
#define GET_RTC_DR_TIMESTAMP_DAY(Peri)                (void)Peri
#define GET_RTC_DR_TIMESTAMP_WEEK(Peri)               (void)Peri
#define GET_RTC_DR_TIMESTAMP_MONTH(Peri)              (void)Peri
#define GET_RTC_DR_TIMESTAMP_YEAR(Peri)               (void)Peri
#define SET_RTC_IER_TIMESTAMP_EN(Peri,Data)           (void)0
#define SET_RTC_IER_TIMESTAMPLAG(Peri,Data)           (void)0
#define GET_RTC_IER_TIMESTAMPLAG(Peri)                (void)Peri
#define SET_RTC_WKUP_EN(Peri,Data)                    (void)0
#define SET_RTC_WKUP_PIN_EN(Peri,Data)                (void)Peri

/* SCU Macro */
typedef SCUCG_Type                                    SCU_Type;
#define SCU_ADDR                                      SCUCG_BASE
#define INTC_REG_BASE                                 INTC_BASE;
#define SET_SCU_RTC_PER(Peri,Id,Data)                 (void)Peri
#define SET_SCU_RTC_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCUCG,PPCLKEN2,RTCCLKE)
#define SET_INTC_IRQ_UNMASK_EN(Peri,Irq,Data)         SET_BIT_ID(Peri,Irq,Data,INTC,MSK,IMSK0_LVI_ECCC)
#define SET_SCU_RTC_CLK_SEL(Peri,Data)                SET_BIT(Peri,Data,SCUCG,PPCLKSR,RTCCLK)
#define GET_SCU_RTC_CLK_SEL(Peri)                     GET_BIT(Peri,SCUCG,PPCLKSR,RTCCLK)
#define GET_SCU_HSI_CLK_SEL(Peri)                     GET_BIT(Peri,SCUCG,CLKSRCR,HIRCSEL)

#define SET_SCU_RTC_WKUP_EN(Peri,Data)                (void)0
#define GET_SCU_RTC_WKUP_EN(Peri)                     (void)Peri
#define GET_SCU_RTC_WKUPLAG(Peri)                     (void)Peri
#define GET_SCU_RTC_PREVMODE(Peri)                    (void)Peri

#endif /* _HAL_RTC_F_01_00_01_H_ */
