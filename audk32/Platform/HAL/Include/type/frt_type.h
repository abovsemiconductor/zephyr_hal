/**
 *******************************************************************************
 * @file        frt_type.h
 * @author      ABOV R&D Division
 * @brief       Free Run Timer (Common)
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
 * @defgroup    TYPE_FRT FRT
 * @{
 * @brief       Free Run Timer
 */

#ifndef _FRT_TYPE_H_
#define _FRT_TYPE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief FRT Instance Id
 */
typedef enum
{
    FRT_ID_0,
    FRT_ID_1,
    FRT_ID_2,
    FRT_ID_3,
    FRT_ID_4,
    FRT_ID_5,
    FRT_ID_6,
    FRT_ID_7,
    FRT_ID_8,
    FRT_ID_9,
    FRT_ID_MAX
} FRT_ID_e;

/**
 * @brief FRT Mode
 */
typedef enum
{
    FRT_MODE_FREERUN,
    FRT_MODE_MATCH,
    FRT_MODE_MAX
} FRT_MODE_e;

/**
 * @brief FRT Clock Source
 */
typedef enum
{
    FRT_CLK_PCLK,    /**< Peripheral Clock source */
    FRT_CLK_MCCR,    /**< Misc Clock source ::FRT_CLK_MCCR_e */
    FRT_CLK_MAX
} FRT_CLK_e;

/**
 * @brief FRT MCCR (Misc Clock) Source
 */
typedef enum
{
    FRT_CLK_MCCR_LSI,     /**< Low Speed Internal Clock source */
    FRT_CLK_MCCR_LSE,     /**< Low Speed External Clock source */
    FRT_CLK_MCCR_MCLK,    /**< Main Clock source */
    FRT_CLK_MCCR_HSI,     /**< High Speed Internal Clock source */
    FRT_CLK_MCCR_HSE,     /**< High Speed External Clock source */
    FRT_CLK_MCCR_PLL,     /**< Phase-Locked Loop (PLL) Clock source */
    FRT_CLK_MCCR_MAX
} FRT_CLK_MCCR_e;

/**
 * @brief FRT Clock Pre-divide
 */
typedef enum
{
    FRT_CLK_PREDIV_1,      /**< fFRT */
    FRT_CLK_PREDIV_4,      /**< fFRT/4 */
    FRT_CLK_PREDIV_8,      /**< fFRT/8 */
    FRT_CLK_PREDIV_16,     /**< fFRT/16 */
    FRT_CLK_PREDIV_32,     /**< fFRT/32 */
    FRT_CLK_PREDIV_64,     /**< fFRT/64 */
    FRT_CLK_PREDIV_128,    /**< fFRT/128 */
    FRT_CLK_PREDIV_256,    /**< fFRT/256 */
    FRT_CLK_PREDIV_MAX
} FRT_CLK_PREDIV_e;

/**
 * FRT Interrupt Mode
 */
typedef enum
{
    FRT_INTR_MATCH,
    FRT_INTR_OVERFLOW,
    FRT_INTR_MAX
} FRT_INTR_e;

/**
 * @brief FRT Operation
 */
typedef enum
{
    FRT_OPS_POLL,        /**< Operation Polling */
    FRT_OPS_INTR,        /**< Operation Interrupt */
    FRT_OPS_NMI,         /**< Operation NMI */
    FRT_OPS_MAX
} FRT_OPS_e;

/**
 * @brief FRT Event
 */
typedef enum
{
    FRT_EVENT_MATCH       = BIT(0),
    FRT_EVENT_OVERFLOW    = BIT(1),
    FRT_EVENT_MAX
} FRT_EVENT_e;

#ifdef __cplusplus
}
#endif

#endif /* _FRT_TYPE_H_ */

/** @} */
/** @} */
