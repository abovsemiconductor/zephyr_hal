/**
 *******************************************************************************
 * @file        hal_rtc_v_01_00_01.h
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

#ifndef _HAL_RTC_V_01_00_01_H_
#define _HAL_RTC_V_01_00_01_H_

/* Feature(Function) Configuration Define */
#define RTC_FEATURE_SUBSECOND_COUNTER
#define RTC_FEATURE_TIMESTAMP
#define RTC_FEATURE_READ_OPERATION
#define RTC_FEATURE_UNSUPPORT_PIN_FUNCTION
#define RTC_FEATURE_UNSUPPORT_LSI40KHZ

/* Internal Macro */
#define RTC_REG_BASE                                  RTC_BASE
#define RTC_IO_INTR_SUPPORT                           1
#define RTC_DELAY_MARGIN                              200
#define RTC_INTR_CLEAR                                0
#define RTC_CLK_SEL(x)                                ((x) >= P_RTC_CLK_MCCR_MCLK ? (x+2) : x)


/* Bit/Register Macro */
#define SET_RTC_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,RTC,CR,RTCEN)
#define SET_RTC_CR_START(Peri,Data)                   SET_BIT(Peri,Data,RTC,CR,RTCE)
#define GET_RTC_CR_START(Peri)                        GET_BIT(Peri,RTC,CR,RTCE)
#define SET_RTC_CR_RWMODE(Peri,Data)                  SET_BIT(Peri,Data,RTC,CR,RWAIT)
#define GET_RTC_SR_RWMODE(Peri)                       GET_BIT(Peri,RTC,CR,RWST)
#define SET_RTC_DR_SUBSEC(Peri,Data)                  SET_BIT(Peri,Data,RTC,SUBDR,SUBDR)
#define SET_RTC_CR_PORT_MODE(Peri,Data)               (void)Peri
#define SET_RTC_WKUP_EN(Peri,Data)                    (void)Peri
#define SET_RTC_WKUP_PIN_EN(Peri,Data)                (void)Peri
#define SET_RTC_CR_ERRCOR_EN(Peri,Data)               SET_BIT(Peri,Data,RTC,ERRCOR,COREN)
#define SET_RTC_CR_ERRCOR_DIR(Peri,Data)              SET_BIT(Peri,Data,RTC,ERRCOR,DIR)
#define SET_RTC_CR_ERRCOR_TIME(Peri,Data)             SET_BIT(Peri,Data,RTC,ERRCOR,DEV)
#define SET_RTC_DR_ERRCOR(Peri,Data)                  SET_BIT(Peri,Data,RTC,ERRCOR,CORDATA)
#define SET_RTC_CR_24HOUR(Peri,Data)                  SET_BIT(Peri,Data,RTC,CR,AMPM)
#define SET_RTC_DR_SEC(Peri,Data)                     SET_BIT(Peri,Data,RTC,SEC,SEC)
#define SET_RTC_DR_MIN(Peri,Data)                     SET_BIT(Peri,Data,RTC,MIN,MIN)
#define SET_RTC_DR_HOUR(Peri,Data)                    SET_BIT(Peri,Data,RTC,HOUR,HOUR)
#define SET_RTC_DR_DAY(Peri,Data)                     SET_BIT(Peri,Data,RTC,DAY,DAY)
#define SET_RTC_DR_WEEK(Peri,Data)                    SET_BIT(Peri,Data,RTC,WEEK,WEEK)
#define SET_RTC_DR_MONTH(Peri,Data)                   SET_BIT(Peri,Data,RTC,MONTH,MONTH)
#define SET_RTC_DR_YEAR(Peri,Data)                    SET_BIT(Peri,Data,RTC,YEAR,YEAR)
#define GET_RTC_DR_SEC(Peri)                          GET_BIT(Peri,RTC,SEC,SEC)
#define GET_RTC_DR_MIN(Peri)                          GET_BIT(Peri,RTC,MIN,MIN)
#define GET_RTC_DR_HOUR(Peri)                         GET_BIT(Peri,RTC,HOUR,HOUR)
#define GET_RTC_DR_DAY(Peri)                          GET_BIT(Peri,RTC,DAY,DAY)
#define GET_RTC_DR_WEEK(Peri)                         GET_BIT(Peri,RTC,WEEK,WEEK)
#define GET_RTC_DR_MONTH(Peri)                        GET_BIT(Peri,RTC,MONTH,MONTH)
#define GET_RTC_DR_YEAR(Peri)                         GET_BIT(Peri,RTC,YEAR,YEAR)
#define SET_RTC_DR_ALARM_MIN(Peri,Data)               SET_BIT(Peri,Data,RTC,ALARMWM,ALARMWM)
#define SET_RTC_DR_ALARM_HOUR(Peri,Data)              SET_BIT(Peri,Data,RTC,ALARMWM,ALARMWH)
#define SET_RTC_DR_ALARM_WEEK(Peri,Data)              SET_BIT(Peri,Data,RTC,ALARMWM,ALARMWW)
#define SET_RTC_CR_TIMESTAMP_EDGE(Peri,Data)          SET_BIT(Peri,Data,RTC,CR,TS_EDGE_SEL)
#define GET_RTC_DR_TIMESTAMP_SEC(Peri)                GET_BIT(Peri,RTC,TIME_TS,SEC_TS)
#define GET_RTC_DR_TIMESTAMP_MIN(Peri)                GET_BIT(Peri,RTC,TIME_TS,MIN_TS)
#define GET_RTC_DR_TIMESTAMP_HOUR(Peri)               GET_BIT(Peri,RTC,TIME_TS,HOUR_TS)
#define GET_RTC_DR_TIMESTAMP_DAY(Peri)                GET_BIT(Peri,RTC,DATE_TS,DAY_TS)
#define GET_RTC_DR_TIMESTAMP_WEEK(Peri)               GET_BIT(Peri,RTC,DATE_TS,WEEK_TS)
#define GET_RTC_DR_TIMESTAMP_MONTH(Peri)              GET_BIT(Peri,RTC,DATE_TS,MONTH_TS)
#define GET_RTC_DR_TIMESTAMP_YEAR(Peri)               GET_BIT(Peri,RTC,DATE_TS,YEAR_TS)

/* Interrupt Macro */
#define SET_RTC_IER_CONST_PERIOD_EN(Peri,Data)        SET_BIT(Peri,Data,RTC,CR,CT)
#define SET_RTC_IER_CONST_PERIOD_FLAG(Peri,Data)      SET_BIT(Peri,Data,RTC,CR,RIFG)
#define GET_RTC_IER_CONST_PERIOD_FLAG(Peri)           GET_BIT(Peri,RTC,CR,RIFG)
#define SET_RTC_IER_ALARM_EN(Peri,Data)               SET_BIT(Peri,Data,RTC,CR,WAIE)
#define SET_RTC_IER_ALARM_FLAG(Peri,Data)             SET_BIT(Peri,Data,RTC,CR,WAFG)
#define GET_RTC_IER_ALARM_FLAG(Peri)                  GET_BIT(Peri,RTC,CR,WAFG)
#define SET_RTC_IER_TIMESTAMP_EN(Peri,Data)           SET_BIT(Peri,Data,RTC,CR,TSEN)
#define SET_RTC_IER_TIMESTAMP_FLAG(Peri,Data)         SET_BIT(Peri,Data,RTC,CR,TSFG)
#define GET_RTC_IER_TIMESTAMP_FLAG(Peri)              GET_BIT(Peri,RTC,CR,TSFG)

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_RTC_PER(Peri,Data)                    SET_BIT(Peri,Data,SCU,PER1,RTC)
#define SET_SCU_RTC_PCER(Peri,Data)                   SET_BIT(Peri,Data,SCU,PCER1,RTC)
#define SET_SCU_RTC_PPCLKSR_CLK(Peri,Data)            (void)Peri
#define SET_SCU_RTC_MCCR_SEL(Peri,Data)               SET_BIT(Peri,RTC_CLK_SEL(Data),SCU,MCCR2,RTCCSEL)
#define SET_SCU_RTC_MCCR_DIV(Peri,Data)               SET_BIT(Peri,Data,SCU,MCCR2,RTCCDIV)
#define SET_SCU_RTC_MCCR_LSI40KHZ(Peri,Data)          (void)Peri

#define SET_SCU_RTC_WKUP_EN(Peri,Data)                SET_BIT(Peri,Data,SCU,WUER,RTCWUE)
#define GET_SCU_RTC_WKUP_EN(Peri)                     GET_BIT(Peri,SCU,WUER,RTCWUE)
#define GET_SCU_RTC_WKUP_FLAG(Peri)                   GET_BIT(Peri,SCU,WUSR,RTCCWU)
#define GET_SCU_RTC_PREVMODE(Peri)                    GET_BIT(Peri,SCU,SMR,PREVMODE)

#endif /* _HAL_RTC_V_01_00_01_H_ */
