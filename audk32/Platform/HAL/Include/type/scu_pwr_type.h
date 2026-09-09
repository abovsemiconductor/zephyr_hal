/**
 *******************************************************************************
 * @file        scu_pwr_type.h
 * @author      ABOV R&D Division
 * @brief       Power sub system in System Control Unit (Common)
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
 * @defgroup    TYPE_SCU_PWR SCU_PWR
 * @{
 * @brief       Power sub system in System Control Unit (SCU)
 */

#ifndef _SCU_PWR_TYPE_H_
#define _SCU_PWR_TYPE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief SCUPWR Mode
 */
typedef enum {
    SCUPWR_MODE_INIT,          /**< Init Mode */
    SCUPWR_MODE_RUN,           /**< Running Mode */
    SCUPWR_MODE_SLEEP,         /**< Sleep Mode */
    SCUPWR_MODE_DEEPSLEEP,     /**< Deep-sleep Mode */
    SCUPWR_MODE_DEEPSLEEP2,    /**< Deep-sleep 2 Mode */
    SCUPWR_MODE_MAX
} SCUPWR_MODE_e;

/**
 * @brief SCUPWR Deep-sleep Mode
 */
typedef enum {
    SCUPWR_DS_MODE_0,     /**< Deep-sleep Mode 0 */
    SCUPWR_DS_MODE_1,     /**< Deep-sleep Mode 1 */
    SCUPWR_DS_MODE_2,     /**< Deep-sleep Mode 2 */
    SCUPWR_DS_MODE_3,     /**< Deep-sleep Mode 3 */
    SCUPWR_DS_MODE_MAX
} SCUPWR_DS_MODE_e;

/**
 * @brief SCUPWR Wake-up Pin bit
 */
typedef enum {
    SCUPWR_WKUP_PIN_0 = BIT(0),     /**< Wake-up Pin 0 */
    SCUPWR_WKUP_PIN_1 = BIT(1),     /**< Wake-up Pin 1 */
    SCUPWR_WKUP_PIN_2 = BIT(2),     /**< Wake-up Pin 2 */
    SCUPWR_WKUP_PIN_3 = BIT(3),     /**< Wake-up Pin 3 */
    SCUPWR_WKUP_PIN_MAX
} SCUPWR_WKUP_PIN_e;

/**
 * @brief SCUPWR Deep-sleep Wake-up reason
 */
typedef enum {
    SCUPWR_DS_WKUP_REASON_1,       /**< Wake-up reason Deep-sleep 1 */
    SCUPWR_DS_WKUP_REASON_2,       /**< Wake-up reason Deep-sleep 2 */
    SCUPWR_DS_WKUP_REASON_3,       /**< Wake-up reason Deep-sleep 3 */
    SCUPWR_DS_WKUP_REASON_MAX
} SCUPWR_DS_WKUP_REASON_e;

/**
 * @brief SCUPWR Always On in Deep-sleep Mode
 */
typedef enum {
    SCUPWR_AON_VDC     = BIT(0),    /**< VDC Block */
    SCUPWR_AON_BGR     = BIT(1),    /**< BGR Block */
    SCUPWR_AON_LSI     = BIT(2),    /**< Low Speed Internal Clock Block */
    SCUPWR_AON_LSE     = BIT(3),    /**< Low Speed External Clock Block */
    SCUPWR_AON_HSI     = BIT(4),    /**< High Speed Internal Clock Block */
    SCUPWR_AON_HSE     = BIT(5),    /**< High Speed External Clock Block */
    SCUPWR_AON_PLL     = BIT(6),    /**< Phase-Locked Loop (PLL) Clock Block */
    SCUPWR_AON_EXTCLK  = BIT(7),    /**< High and Low Speed External Clock Block */
    SCUPWR_AON_MAX
} SCUPWR_AON_e;

/**
 * @brief SCUPWR Wake-up Interrupt
 */
typedef enum {
    SCUPWR_WKUP_INTR_NONE,        /**< None Interrupt */
    SCUPWR_WKUP_INTR_MASK,        /**< Maskable Interrupt */
    SCUPWR_WKUP_INTR_NON_MASK,    /**< Non-maskable Interrupt */
    SCUPWR_WKUP_INTR_MAX
} SCUPWR_WKUP_INTR_e;

/**
 * @brief SCUPWR Port Id
 */
typedef enum {
    SCUPWR_PORT_ID_A,              /**< Port Id A */
    SCUPWR_PORT_ID_B,              /**< Port Id B */
    SCUPWR_PORT_ID_C,              /**< Port Id C */
    SCUPWR_PORT_ID_D,              /**< Port Id D */
    SCUPWR_PORT_ID_E,              /**< Port Id E */
    SCUPWR_PORT_ID_F,              /**< Port Id F */
    SCUPWR_PORT_ID_MAX
} SCUPWR_PORT_ID_e;

/**
 * @brief SCUPWR Port Pull Up/Down
 */
typedef enum {
    SCUPWR_PORT_PUPD_DISABLE,      /**< Disable Port Pull-up/down */
    SCUPWR_PORT_PUPD_UP,           /**< Port Pull-up */
    SCUPWR_PORT_PUPD_DOWN,         /**< Port Pull-down */
    SCUPWR_PORT_PUPD_MAX
} SCUPWR_PORT_PUPD_e;

#ifdef __cplusplus
}
#endif

#endif /* _SCU_PWR_TYPE_H_ */

/** @} */
/** @} */
