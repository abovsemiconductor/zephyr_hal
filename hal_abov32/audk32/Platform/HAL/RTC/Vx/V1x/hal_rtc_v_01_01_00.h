/**
 *******************************************************************************
 * @file        hal_rtc_v_01_01_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.01.00 typed RTC
 *
 * Copyright 2026 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_RTC_V_01_01_00_H_
#define _HAL_RTC_V_01_01_00_H_

/* Feature(Function) Configuration Define */
#define RTC_FEATURE_SUBSECOND_COUNTER
#define RTC_FEATURE_TIMESTAMP
#define RTC_FEATURE_READ_OPERATION
#define RTC_FEATURE_UNSUPPORT_PIN_FUNCTION
#define RTC_FEATURE_UNSUPPORT_LSI40KHZ
#define RTC_FEATURE_TIME_REG_UNIFIED
#define RTC_FEATURE_DATE_REG_UNIFIED

/* Internal Macro */
typedef RTCC_Type                                     RTC_Type;
#define RTC_REG_BASE                                  RTCC_BASE
#define RTC_IO_INTR_SUPPORT                           1
#define RTC_DELAY_MARGIN                              200
#define RTC_INTR_CLEAR                                0
#define RTC_CLK_SEL(x)                                ((x) >= P_RTC_CLK_MCCR_MCLK ? (x+2) : x)

/* Bit/Register Macro */
#if (CONFIG_RTC_VER_EXT == 1)
#define SET_RTC_BIT(Peri,Data,RegName,BitName)        SET_BIT(Peri,Data,RTCC,RegName,BitName)
#define GET_RTC_BIT(Peri,RegName,BitName)             GET_BIT(Peri,RTCC,RegName,BitName)
#else
#define SET_RTC_BIT(Peri,Data,RegName,BitName)        SET_BIT(Peri,Data,RTC,RegName,BitName)
#define GET_RTC_BIT(Peri,RegName,BitName)             GET_BIT(Peri,RTC,RegName,BitName)
#endif

#define SET_RTC_CR_EN(Peri,Data)                      SET_RTC_BIT(Peri,Data,CR,RTCCEN)
#define SET_RTC_CR_START(Peri,Data)                   SET_RTC_BIT(Peri,Data,CR,RTCCE)
#define GET_RTC_CR_START(Peri)                        GET_RTC_BIT(Peri,CR,RTCCE)
#define SET_RTC_CR_RWMODE(Peri,Data)                  SET_RTC_BIT(Peri,Data,CR,RWAIT)
#define GET_RTC_SR_RWMODE(Peri)                       GET_RTC_BIT(Peri,CR,RWST)
#define SET_RTC_DR_SUBSEC(Peri,Data)                  SET_RTC_BIT(Peri,Data,SUBDR,SUBDR)
#define SET_RTC_CR_PORT_MODE(Peri,Data)               (void)Peri
#define SET_RTC_WKUP_EN(Peri,Data)                    (void)Peri
#define SET_RTC_WKUP_PIN_EN(Peri,Data)                (void)Peri
#define SET_RTC_CR_ERRCOR_EN(Peri,Data)               SET_RTC_BIT(Peri,Data,ERRCOR,COREN)
#define SET_RTC_CR_ERRCOR_DIR(Peri,Data)              SET_RTC_BIT(Peri,Data,ERRCOR,DIR)
#define SET_RTC_CR_ERRCOR_TIME(Peri,Data)             SET_RTC_BIT(Peri,Data,ERRCOR,DEV)
#define SET_RTC_DR_ERRCOR(Peri,Data)                  SET_RTC_BIT(Peri,Data,ERRCOR,CORDATA)
#define SET_RTC_CR_24HOUR(Peri,Data)                  SET_RTC_BIT(Peri,Data,CR,AMPM)
#define SET_RTC_DR_TIME(Peri,Data)                    SET_REG(Peri,Data,TIME_CNT)
#define SET_RTC_DR_DATE(Peri,Data)                    SET_REG(Peri,Data,DATE_CNT)
#define GET_RTC_DR_TIME(Peri)                         GET_REG(Peri,TIME_CNT)
#define GET_RTC_DR_DATE(Peri)                         GET_REG(Peri,DATE_CNT)
#define SET_RTC_DR_ALARM_MIN(Peri,Data)               SET_RTC_BIT(Peri,Data,ALARMWM,ALARMWM)
#define SET_RTC_DR_ALARM_HOUR(Peri,Data)              SET_RTC_BIT(Peri,Data,ALARMWM,ALARMWH)
#define SET_RTC_DR_ALARM_WEEK(Peri,Data)              SET_RTC_BIT(Peri,Data,ALARMWM,ALARMWW)
#define SET_RTC_CR_TIMESTAMP_EDGE(Peri,Data)          SET_RTC_BIT(Peri,Data,CR,TS_EDGE_SEL)
#define GET_RTC_DR_TIMESTAMP_SEC(Peri)                GET_RTC_BIT(Peri,TIME_TS,SEC_TS)
#define GET_RTC_DR_TIMESTAMP_MIN(Peri)                GET_RTC_BIT(Peri,TIME_TS,MIN_TS)
#define GET_RTC_DR_TIMESTAMP_HOUR(Peri)               GET_RTC_BIT(Peri,TIME_TS,HOUR_TS)
#define GET_RTC_DR_TIMESTAMP_DAY(Peri)                GET_RTC_BIT(Peri,DATE_TS,DAY_TS)
#define GET_RTC_DR_TIMESTAMP_WEEK(Peri)               GET_RTC_BIT(Peri,DATE_TS,WEEK_TS)
#define GET_RTC_DR_TIMESTAMP_MONTH(Peri)              GET_RTC_BIT(Peri,DATE_TS,MONTH_TS)
#define GET_RTC_DR_TIMESTAMP_YEAR(Peri)               GET_RTC_BIT(Peri,DATE_TS,YEAR_TS)

/* Interrupt Macro */
#define SET_RTC_IER_CONST_PERIOD_EN(Peri,Data)        SET_RTC_BIT(Peri,Data,CR,CT)
#define SET_RTC_IER_CONST_PERIOD_FLAG(Peri,Data)      SET_RTC_BIT(Peri,Data,CR,RIFG)
#define GET_RTC_IER_CONST_PERIOD_FLAG(Peri)           GET_RTC_BIT(Peri,CR,RIFG)
#define SET_RTC_IER_ALARM_EN(Peri,Data)               SET_RTC_BIT(Peri,Data,CR,WAIE)
#define SET_RTC_IER_ALARM_FLAG(Peri,Data)             SET_RTC_BIT(Peri,Data,CR,WAFG)
#define GET_RTC_IER_ALARM_FLAG(Peri)                  GET_RTC_BIT(Peri,CR,WAFG)
#define SET_RTC_IER_TIMESTAMP_EN(Peri,Data)           SET_RTC_BIT(Peri,Data,CR,TSEN)
#define SET_RTC_IER_TIMESTAMP_FLAG(Peri,Data)         SET_RTC_BIT(Peri,Data,CR,TSFG)
#define GET_RTC_IER_TIMESTAMP_FLAG(Peri)              GET_RTC_BIT(Peri,CR,TSFG)

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_RTC_PER(Peri,Data)                    SET_BIT(Peri,Data,SCU,PER2,RTCC)
#define SET_SCU_RTC_PCER(Peri,Data)                   SET_BIT(Peri,Data,SCU,PCER2,RTCC)
#define SET_SCU_RTC_PPCLKSR_CLK(Peri,Data)            (void)Peri
#define SET_SCU_RTC_MCCR_SEL(Peri,Data)               SET_BIT(Peri,RTC_CLK_SEL(Data),SCU,MCCR2,RTCCCSEL)
#define SET_SCU_RTC_MCCR_DIV(Peri,Data)               SET_BIT(Peri,Data,SCU,MCCR2,RTCCCDIV)
#define SET_SCU_RTC_MCCR_LSI40KHZ(Peri,Data)          (void)Peri

#define SET_SCU_RTC_WKUP_EN(Peri,Data)                SET_BIT(Peri,Data,SCU,WUER,RTCCWUE)
#define GET_SCU_RTC_WKUP_EN(Peri)                     GET_BIT(Peri,SCU,WUER,RTCCWUE)
#define GET_SCU_RTC_WKUP_FLAG(Peri)                   GET_BIT(Peri,SCU,WUSR,RTCCWU)
#define GET_SCU_RTC_PREVMODE(Peri)                    GET_BIT(Peri,SCU,SMR,PREVMODE)

#endif /* _HAL_RTC_V_01_01_00_H_ */
