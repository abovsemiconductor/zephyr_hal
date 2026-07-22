/**
 *******************************************************************************
 * @file        hal_rtc.h
 * @author      ABOV R&D Division
 * @brief       Real Time Clock
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/**
 * @addtogroup  HAL HAL (Hardware Abstraction Layer)
 * @{
 * @defgroup    HAL_RTC RTC
 * @{
 * @brief       Real-time Clock
 */

#ifndef _HAL_RTC_H_
#define _HAL_RTC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief RTC Instance Id
 */
typedef enum
{
    RTC_ID_0,
    RTC_ID_1,
    RTC_ID_2,
    RTC_ID_3,
    RTC_ID_4,
    RTC_ID_5,
    RTC_ID_6,
    RTC_ID_7,
    RTC_ID_8,
    RTC_ID_9,
    RTC_ID_MAX
} RTC_ID_e;

/**
 * @brief RTC Clock Source
 */
typedef enum
{
    RTC_CLK_LSI40KHZ,    /**< Low Speed Internal Clock Source (40KHz) */
    RTC_CLK_WDTRC,       /**< Watch Dog Timer Ring Osillator Clock source */
    RTC_CLK_MCCR,        /**< Misc Clock source ::RTC_CLK_MCCR_e */
    RTC_CLK_MAX
} RTC_CLK_e;

/**
 * @brief RTC MCCR (Misc Clock) Source
 */
typedef enum
{
    RTC_CLK_MCCR_LSI,    /**< Low Speed Internal Clock source */
    RTC_CLK_MCCR_LSE,    /**< Low Speed External Clock source */
    RTC_CLK_MCCR_MCLK,   /**< Master Clock source */
    RTC_CLK_MCCR_HSI,    /**< High Speed Internal Clock source */
    RTC_CLK_MCCR_HSE,    /**< High Speed External Clock source */
    RTC_CLK_MCCR_PLL,    /**< Phase-Locked Loop (PLL) Clock source */
    RTC_CLK_MCCR_MAX
} RTC_CLK_MCCR_e;

/**
 * @brief RTC Error Correction Direction
 */
typedef enum
{
    RTC_ERRCOR_DIR_DEC,    /**< Decrease by Error Correction Data */
    RTC_ERRCOR_DIR_INC,    /**< Increase by Error Correction Data */
    RTC_ERRCOR_DIR_MAX
} RTC_ERRCOR_DIR_e;

/**
 * @brief RTC Error Correction Duration
 */
typedef enum
{
    RTC_ERRCOR_TIME_20SEC,    /**< Correct Watch Error at Every 20 second */
    RTC_ERRCOR_TIME_60SEC,    /**< Correct Watch Error at Every 60 second */
    RTC_ERRCOR_TIME_MAX
} RTC_ERRCOR_TIME_e;

/**
 * @brief RTC Constant Interrupt Period
 */
typedef enum
{
    RTC_CONST_PERIOD_NONE,           /**< Matching disabled */
    RTC_CONST_PERIOD_HALFSEC,        /**< Once per 0.5 sec */
    RTC_CONST_PERIOD_ONESEC,         /**< Once per 1 sec */
    RTC_CONST_PERIOD_ONEMIN,         /**< Once per 1 min */
    RTC_CONST_PERIOD_ONEHOUR,        /**< Once per 1 hour */
    RTC_CONST_PERIOD_ONEDAY,         /**< Once per 1 day */
    RTC_CONST_PERIOD_ONEMONTH,       /**< Once per 1 month */
    RTC_CONST_PERIOD_MAX
} RTC_CONST_PERIOD_e;

/**
 * @brief RTC Alarm Week
 */
typedef enum
{
    RTC_ALARM_WEEK_NONE = 0,
    RTC_ALARM_WEEK_SUN = BIT(0),       /**< Sunday */
    RTC_ALARM_WEEK_MON = BIT(1),       /**< Monday */
    RTC_ALARM_WEEK_TUE = BIT(2),       /**< Tuesday */
    RTC_ALARM_WEEK_WED = BIT(3),       /**< Wedensday */
    RTC_ALARM_WEEK_THU = BIT(4),       /**< Thurday */
    RTC_ALARM_WEEK_FRI = BIT(5),       /**< Friday */
    RTC_ALARM_WEEK_SAT = BIT(6),       /**< Saturday */
    RTC_ALARM_WEEK_MAX
} RTC_ALARM_WEEK_e;

/**
 * @brief RTC Timestamp Active Event Edge
 */
typedef enum
{
    RTC_TS_EVT_FALLING,    /**< Falling Edge */
    RTC_TS_EVT_RISING,     /**< Rising Edge */
    RTC_TS_EVT_BOTH,       /**< Both Edge */
    RTC_TS_EVT_MAX
} RTC_TS_EVT_e;

/**
 * @brief RTC Event
 */
typedef enum
{
    RTC_EVENT_PERIOD       = BIT(0),    /**< Period Matching ::RTC_CONST_PERIOD_e */
    RTC_EVENT_ALARM        = BIT(1),    /**< Alarm Matching */
    RTC_EVENT_TIMESTAMP    = BIT(2),    /**< Time-stamp Event ::RTC_TS_EVT_e */
    RTC_EVENT_MAX
} RTC_EVENT_e;

/**
 * @brief RTC Operation
 */
typedef enum
{
    RTC_OPS_POLL,        /**< Operation Polling */
    RTC_OPS_INTR,        /**< Operation Interrupt */
    RTC_OPS_MAX
} RTC_OPS_e;

/**
 * @brief RTC Clock Configuration
 */
typedef struct
{
    RTC_CLK_e         eClk;
    RTC_CLK_MCCR_e    eMccr;         /**< When selecting MCCR at eClk */
    uint8_t           un8MccrDiv;    /**< When selecting MCCR at eClk */
} RTC_CLK_CFG_t;

/**
 * @brief RTC Mode Configuration
 */
typedef struct
{
    bool                 bErrCorEn;
    uint32_t             un32ErrCorData;    /**< Error Correction Value */
    RTC_ERRCOR_DIR_e     eErrCorDir;
    RTC_ERRCOR_TIME_e    eErrCorTime;

    bool                 bRTCClkOut;        /**< Enable RTC Clock output or 32KHz(true) / 1Hz(false) Select*/
} RTC_CFG_t;

/**
 * @brief RTC Time
 */
typedef struct
{
    uint8_t    un8Sec;    /**< Second */
    uint8_t    un8Min;    /**< Minute */
    uint8_t    un8Hour;   /**< Hour */
} RTC_TIME_t;

/**
 * @brief RTC Date
 */
typedef struct
{
    uint8_t    un8Day;      /**< Day */
    uint8_t    un8Week;     /**< Week */
    uint8_t    un8Month;    /**< Month */
    uint8_t    un8Year;     /**< Year since 1900 */
} RTC_DATE_t;

/**
 * @brief RTC Clock(Time/Date) Configuration
 */
typedef struct
{
    bool                  b24Hour;    /**< true = 24-hour, false = 12-hour clock */
    RTC_CONST_PERIOD_e    ePeriod;
    RTC_TIME_t            tTime;      /**< Time */
    RTC_DATE_t            tDate;      /**< Date */
} RTC_CLOCK_t;

/**
 * @brief RTC Alarm Configuration
 */
typedef struct
{
    bool       bAlarmEn;
    uint8_t    un8Min;     /**< Minute */
    uint8_t    un8Hour;    /**< Hour */
    uint8_t    un8Week;    /**< Week */
} RTC_ALARM_t;

/**
 * @brief RTC IRQ handler context
 */
typedef struct
{
    RTC_ID_e    eId;        /**< RTC Instance Id */
    bool        b24Hour;    /**< 24/12-hour clock */
    bool        bWakeup;    /**< Wake-up flag */
} RTC_Context_t;

/**
 *******************************************************************************
 * @brief       RTC Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::RTC_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnRTC_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize RTC.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RTC_Init(RTC_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize RTC.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RTC_Uninit(RTC_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration RTC.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClkCfg : RTC Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RTC_SetClkConfig(RTC_ID_e eId, RTC_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration RTC.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : RTC Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RTC_SetConfig(RTC_ID_e eId, RTC_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ RTC.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RTC_SetIRQ(RTC_ID_e eId, RTC_OPS_e eOps, pfnRTC_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Start RTC.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RTC_Start(RTC_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop RTC.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RTC_Stop(RTC_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Clock(Time/Data) Configuration RTC.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClock : RTC Clock(Time/Data) Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RTC_SetClock(RTC_ID_e eId, RTC_CLOCK_t *ptClock);

/**
 *******************************************************************************
 * @brief       Get Clock(Time/Data) RTC.
 * @param[in]   eId : Instance Id.
 * @param[out]  *ptTime : Current Time.
 * @param[out]  *ptDate : Current Date.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RTC_GetClock(RTC_ID_e eId, RTC_TIME_t *ptTime, RTC_DATE_t *ptDate);

/**
 *******************************************************************************
 * @brief       Set Alarm Configuration RTC.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptAlarm : RTC Alarm Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RTC_SetAlarm(RTC_ID_e eId, RTC_ALARM_t *ptAlarm);

/**
 *******************************************************************************
 * @brief       Set Timestamp RTC.
 * @param[in]   eId : Instance Id.
 * @param[in]   bTimestampEn : Timestamp Enable.
 * @param[in]   eTsEvt : Timestamp Active Event Edge.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RTC_SetTimestamp(RTC_ID_e eId, bool bTimestampEn, RTC_TS_EVT_e eTsEvt);

/**
 *******************************************************************************
 * @brief       Get Timestamp(Time/Data) RTC.
 * @param[in]   eId : Instance Id.
 * @param[out]  *ptTime : Current Timestamp Time.
 * @param[out]  *ptDate : Current Timestamp Date.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RTC_GetTimestamp(RTC_ID_e eId, RTC_TIME_t *ptTime, RTC_DATE_t *ptDate);

/**
 *******************************************************************************
 * @brief       Set Wake-up source RTC.
 * @param[in]   eId : Instance Id.
 * @param[in]   bEnable : Enable Wake-up source.
 * @param[in]   bExtPinEnable : Enable external pin as a Wake-up.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RTC_SetWakeupSrc(RTC_ID_e eId, bool bEnable, bool bExtPinEnable);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_RTC_H_ */

/** @} */
/** @} */
