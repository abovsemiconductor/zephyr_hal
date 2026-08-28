/**
 *******************************************************************************
 * @file        wdt_type.h
 * @author      ABOV R&D Division
 * @brief       Watch Dog Timer (Common)
 *
 * Copyright 2026 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/**
 * @addtogroup  TYPE TYPE (Common type)
 * @{
 * @defgroup    TYPE_WDT WDT
 * @{
 * @brief       Watch Dog Timer
 */

#ifndef _WDT_TYPE_H_
#define _WDT_TYPE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief WDT Instance Id
 */
typedef enum
{
    WDT_ID_0,
    WDT_ID_1,
    WDT_ID_2,
    WDT_ID_3,
    WDT_ID_4,
    WDT_ID_5,
    WDT_ID_6,
    WDT_ID_7,
    WDT_ID_8,
    WDT_ID_9,
    WDT_ID_MAX
} WDT_ID_e;

/**
 * @brief WDT Mode
 */
typedef enum
{
    WDT_MODE_NONE         = 0,
    WDT_MODE_CNT          = BIT(0),    /**< Count Match Mode */
    WDT_MODE_RST          = BIT(1),    /**< Reset Mode */
    WDT_MODE_UNDERFLOW    = BIT(2),    /**< Underflow Mode */
    WDT_MODE_MAX
} WDT_MODE_e;

/**
 * @brief WDT Clock Source
 */
typedef enum
{
    WDT_CLK_WDTRC,    /**< Watch Dog Timer Ring Osillator Clock source */
    WDT_CLK_MCCR,     /**< Misc Clock source ::WDT_CLK_MCCR_e */
    WDT_CLK_PCLK,     /**< Peripheral Clock source */
    WDT_CLK_MAX
} WDT_CLK_e;

/**
 * @brief WDT MCCR (Misc Clock) Source
 */
typedef enum
{
    WDT_CLK_MCCR_LSI,    /**< Low Speed Internal Clock source */
    WDT_CLK_MCCR_LSE,    /**< Low Speed External Clock source */
    WDT_CLK_MCCR_MCLK,   /**< Master Clock source */
    WDT_CLK_MCCR_HSI,    /**< High Speed Internal Clock source */
    WDT_CLK_MCCR_HSE,    /**< High Speed External Clock source */
    WDT_CLK_MCCR_PLL,    /**< Phase-Locked Loop (PLL) Clock source */
    WDT_CLK_MCCR_MAX
} WDT_CLK_MCCR_e;

/**
 * @brief WDT Clock Pre-divide
 */
typedef enum
{
    WDT_CLK_PREDIV_1,      /**< fWDT */
    WDT_CLK_PREDIV_4,      /**< fWDT/4 */
    WDT_CLK_PREDIV_8,      /**< fWDT/8 */
    WDT_CLK_PREDIV_16,     /**< fWDT/16 */
    WDT_CLK_PREDIV_32,     /**< fWDT/32 */
    WDT_CLK_PREDIV_64,     /**< fWDT/64 */
    WDT_CLK_PREDIV_128,    /**< fWDT/128 */
    WDT_CLK_PREDIV_256,    /**< fWDT/256 */
    WDT_CLK_PREDIV_MAX
} WDT_CLK_PREDIV_e;

/**
 * @brief WDT Interrupt Mode
 */
typedef enum
{
    WDT_INTR_NONE          = 0,
    WDT_INTR_MATCH         = BIT(0),
    WDT_INTR_UNDERFLOW     = BIT(1),
    WDT_INTR_MAX
} WDT_INTR_e;

/**
 * @brief WDT Event
 */
typedef enum
{
    WDT_EVENT_MATCH        = BIT(0),
    WDT_EVENT_UNDERFLOW    = BIT(1),
    WDT_EVENT_MAX
} WDT_EVENT_e;

/**
 * @brief WDT Operation
 */
typedef enum
{
    WDT_OPS_POLL,        /**< Operation Polling */
    WDT_OPS_INTR,        /**< Operation Interrupt */
    WDT_OPS_MAX
} WDT_OPS_e;

#ifdef __cplusplus
}
#endif

#endif /* _WDT_TYPE_H_ */

/** @} */
/** @} */
