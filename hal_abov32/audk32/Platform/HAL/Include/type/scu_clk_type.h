/**
 *******************************************************************************
 * @file        scu_clk_type.h
 * @author      ABOV R&D Division
 * @brief       Clock sub system in System Control Unit (Common)
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
 * @addtogroup  TYPE TYPE (Common Type)
 * @{
 * @defgroup    TYPE_SCU_CLK SCU_CLK
 * @{
 * @brief       Core sub system in System Control Unit (SCU)
 */

#ifndef _SCU_CLK_TYPE_H_
#define _SCU_CLK_TYPE_H_

#ifdef __cplusplus
extern "C"
{
#endif


#ifdef __cplusplus
}
#endif

/**
 * @brief SCUCLK Clock Source
 */
typedef enum
{
    SCUCLK_SRC_HSE,                     /**< High Speed External Clock Source */
    SCUCLK_SRC_HSI,                     /**< High Speed Internal Clock Source */
    SCUCLK_SRC_LSI,                     /**< Low Speed Internal Clock Source */
    SCUCLK_SRC_WDT = SCUCLK_SRC_LSI,    /**< Watchdog Timer Clock Source */
    SCUCLK_SRC_LSE,                     /**< Low Speed External Clock Source */
    SCUCLK_SRC_PLL,                     /**< Phase-Locked Loop (PLL) Clock Source */ 
    SCUCLK_SRC_PLL_HSI,                 /**< PLL from HSI Clock */
    SCUCLK_SRC_PLL_HSE,                 /**< PLL from HSE Clock */
    SCUCLK_SRC_MCLK,                    /**< Main Clock Source */
    SCUCLK_SRC_HCLK,                    /**< System Clock Source */
    SCUCLK_SRC_PCLK,                    /**< Peripheral Clock Source */
    SCUCLK_SRC_MAX
} SCUCLK_SRC_e;

/**
 * @brief SCUCLK Clock Divide
 */
typedef enum
{
    SCUCLK_DIV_NONE,
    SCUCLK_DIV_2,
    SCUCLK_DIV_4,
    SCUCLK_DIV_8,
    SCUCLK_DIV_16,
    SCUCLK_DIV_32,
    SCUCLK_DIV_64,
    SCUCLK_DIV_128,
    SCUCLK_DIV_256,
    SCUCLK_DIV_512,
    SCUCLK_DIV_MAX
} SCUCLK_DIV_e;

/**
 * @brief SCUCLK Phase-Locked Loop (PLL) Clock Source
 */
typedef enum
{
    SCUCLK_PLL_SRC_HSI,       /* High Speed Internal Clock Source */
    SCUCLK_PLL_SRC_HSE,       /* High Speed External Clock Source */
    SCUCLK_PLL_SRC_MAX
} SCUCLK_PLL_SRC_e;

/**
 * @brief SCUCLK Phase-Locked Loop (PLL) Lock State
 */
typedef enum
{
    SCUCLK_PLL_LOCK_ON,
    SCUCLK_PLL_LOCK_OFF,
    SCUCLK_PLL_LOCK_MAX
} SCUCLK_PLL_LOCK_e;

/**
 * @brief SCUCLK Phase-Locked Loop (PLL) Reset
 */
typedef enum
{
    SCUCLK_PLL_RESET_ON,
    SCUCLK_PLL_RESET_OFF,
    SCUCLK_PLL_RESET_MAX
} SCUCLK_PLL_RESET_e;

/**
 * @brief SCUCLK Phase-Locked Loop (PLL) Bypass 
 */
typedef enum
{
    SCUCLK_PLL_BYPASS_ON,     /**< FOUT is Bypassed as PLLINCLK */
    SCUCLK_PLL_BYPASS_OFF,    /**< FOUT is PLL Output */
    SCUCLK_PLL_BYPASS_MAX
} SCUCLK_PLL_BYPASS_e;

/**
 * @brief SCUCLK Phase-Locked Loop (PLL) VCO 
 */
typedef enum
{
    SCUCLK_PLL_MODE_VCO,      /**< VCO Frequency is the same with FOUT */
    SCUCLK_PLL_MODE_VCO2X,    /**< VCO Frequency is double of FOUT */
    SCUCLK_PLL_MODE_MAX
} SCUCLK_PLL_MODE_e;

/**
 * @brief SCUCLK Phase-Locked Loop (PLL) Current Option
 */
typedef enum
{
    SCUCLK_PLL_CTRLOPT_5UA,
    SCUCLK_PLL_CTRLOPT_10UA,
    SCUCLK_PLL_CTRLOPT_15UA,
    SCUCLK_PLL_CTRLOPT_20UA,
    SCUCLK_PLL_CTRLOPT_MAX
} SCUCLK_PLL_CTRLOPT_e;

/**
 * @brief SCUCLK Phase-Locked Loop (PLL) VCO Bias
 */
typedef enum
{
    SCUCLK_PLL_VCOBIAS_DIV_4,    /**< 1/4 */
    SCUCLK_PLL_VCOBIAS_DIV_2,    /**< 1/2 */
    SCUCLK_PLL_VCOBIAS_NONE,     /**< x1 */
    SCUCLK_PLL_VCOBIAS_MULTI_2,  /**< x2 */
    SCUCLK_PLL_VCOBIAS_MAX
} SCUCLK_PLL_VCOBIAS_e;

/**
 * @brief SCUCLK Clock Monitor Event
 */
typedef enum
{
    SCUCLK_MON_EVENT_MCLKFAIL             = BIT(0),    /**< Main Clock Source failed by Monitor and Maskable event occurred */
    SCUCLK_MON_EVENT_HSEFAIL              = BIT(1),    /**< HSE Clock failed by Monitor */
    SCUCLK_MON_EVENT_LSEFAIL              = BIT(2),    /**< LSE clock failed by Monitor */
    SCUCLK_MON_EVENT_MAX
} SCUCLK_MON_EVENT_e;

/**
 * @brief SCUCLK HSE Frequency for Noise Cancel
 */
typedef enum
{
    SCUCLK_HSE_FREQ_4M,     /**< HSE 1MHz < f <= 4MHz */
    SCUCLK_HSE_FREQ_8M,     /**< HSE 4MHz < f <= 8MHz */
    SCUCLK_HSE_FREQ_12M,    /**< HSE 8MHz < f <= 12MHz */
    SCUCLK_HSE_FREQ_16M,    /**< HSE 12MHz < f <= 16MHz */
    SCUCLK_HSE_FREQ_MAX
} SCUCLK_HSE_FREQ_e;

/**
 * @brief SCUCLK LSE current for Noise Cancel
 */
typedef enum
{
    SCUCLK_LSE_CURR_1,    /**< LSE current 1.57uA */
    SCUCLK_LSE_CURR_2,    /**< LSE current 1.79uA */
    SCUCLK_LSE_CURR_3,    /**< LSE current 1.93uA */
    SCUCLK_LSE_CURR_4,    /**< LSE current 2.04uA */
    SCUCLK_LSE_CURR_MAX
} SCUCLK_LSE_CURR_e;

#endif /* _SCU_CLK_TYPE_H_ */

/** @} */
/** @} */
