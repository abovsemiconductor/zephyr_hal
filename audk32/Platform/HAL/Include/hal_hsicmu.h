/**
 *******************************************************************************
 * @file        hal_hsicmu.h
 * @author      ABOV R&D Division
 * @brief       High-Speed Internal OSC Clock Management Unit
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
 * @defgroup    HAL_HSICMU HSICMU
 * @{
 * @brief       High-Speed Internal OSC Clock Management Unit
 */

#ifndef _HAL_HSICMU_H_
#define _HAL_HSICMU_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief HSICMU Instance Id
 */
typedef enum
{
    HSICMU_ID_0,
    HSICMU_ID_1,
    HSICMU_ID_2,
    HSICMU_ID_3,
    HSICMU_ID_4,
    HSICMU_ID_5,
    HSICMU_ID_6,
    HSICMU_ID_7,
    HSICMU_ID_8,
    HSICMU_ID_9,
    HSICMU_ID_MAX
} HSICMU_ID_e;

/**
 * @brief HSICMU Synchronization Source
 */
typedef enum
{
    HSICMU_SRC_RESERVED,    /**< High Speed External Clock Source */
    HSICMU_SRC_HSE,         /**< High Speed External Clock Source */
    HSICMU_SRC_LSE,         /**< Low Speed External Clock Source */
    HSICMU_SRC_GPIO,        /**< External SYNC pin */
    HSICMU_SRC_MAX
} HSICMU_SRC_e;

/**
 * @brief HSICMU Sync Divide
 */
typedef enum
{
    HSICMU_DIV_NONE,
    HSICMU_DIV_2,
    HSICMU_DIV_4,
    HSICMU_DIV_8,
    HSICMU_DIV_16,
    HSICMU_DIV_32,
    HSICMU_DIV_64,
    HSICMU_DIV_128,
    HSICMU_DIV_256,
    HSICMU_DIV_512,
    HSICMU_DIV_MAX
} HSICMU_DIV_e;

/**
 * @brief HSICMU Sync Signal Polarity
 */
typedef enum
{
    HSICMU_POL_BOTH_EDGE,
    HSICMU_POL_RISING_EDGE,
    HSICMU_POL_FALLING_EDGE,
    HSICMU_POL_MAX
} HSICMU_POL_e;

/**
 * @brief HSICMU Operation
 */
typedef enum
{
    HSICMU_OPS_POLL,        /**< Operation Polling */
    HSICMU_OPS_INTR,        /**< Operation Interrupt */
    HSICMU_OPS_NMI,         /**< Operation NMI */
    HSICMU_OPS_MAX
} HSICMU_OPS_e;

/**
 * @brief HSICMU Configuration
 */
typedef struct
{
    HSICMU_SRC_e    eSyncSrc;       /**< Sync Signal Source */
    HSICMU_DIV_e    eSyncDiv;       /**< Sync divider */
    HSICMU_DIV_e    ePreDiv;        /**< Sync Pre divider */
    HSICMU_POL_e    eSyncPol;       /**< Sync Signal Polarity */
    uint32_t        un32Reload;     /**< TIMER counter value */
    uint16_t        un16ErrRate;    /**< Frequency Error Rate Threshold */
} HSICMU_CFG_t;

/**
 *******************************************************************************
 * @brief       HSICMU Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type (NONE).
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnHSICMU_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize HSICMU.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_HSICMU_Init(HSICMU_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize HSICMU.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_HSICMU_Uninit(HSICMU_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration HSICMU.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : HSICMU Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_HSICMU_SetConfig(HSICMU_ID_e eId, HSICMU_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Start HSICMU.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_HSICMU_Start(HSICMU_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop HSICMU.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_HSICMU_Stop(HSICMU_ID_e eId);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_HSICMU_H_ */

/** @} */
/** @} */
