/**
 *******************************************************************************
 * @file        hal_trng.h
 * @author      ABOV R&D Division
 * @brief       True Random Number Generator
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
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
 * @defgroup    HAL_TRNG TRNG 
 * @{
 * @brief       True Random Number Generator
 */

#ifndef _HAL_TRNG_H_
#define _HAL_TRNG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief TRNG Instance Id
 */
typedef enum
{
    TRNG_ID_0,
    TRNG_ID_1,
    TRNG_ID_2,
    TRNG_ID_3,
    TRNG_ID_4,
    TRNG_ID_5,
    TRNG_ID_6,
    TRNG_ID_7,
    TRNG_ID_8,
    TRNG_ID_9,
    TRNG_ID_MAX
} TRNG_ID_e;

/**
 * @brief TRNG Interrupt
 */
typedef enum
{
    TRNG_INTR_NONE     = 0,         /**< Disable Interrupt */
    TRNG_INTR_READY    = BIT(0),    /**< Ready Interrupt */
    TRNG_INTR_ERROR    = BIT(1),    /**< Error Interrupt */
    TRNG_INTR_MAX
} TRNG_INTR_e;

/**
 * @brief TRNG Event
 */
typedef enum
{
    TRNG_EVENT_READY    = BIT(0),    /**< Ready Event */
    TRNG_EVENT_ERROR    = BIT(1),    /**< Error Event */
    TRNG_EVENT_MAX
} TRNG_EVENT_e;

/**
 * @brief TRNG Operation
 */
typedef enum
{
    TRNG_OPS_POLL,        /**< Operation Polling */
    TRNG_OPS_INTR,        /**< Operation Interrupt */
    TRNG_OPS_NMI,        /**< Operation NMI */
    TRNG_OPS_MAX
} TRNG_OPS_e;

/**
 * @brief TRNG Mode Configuration
 */
typedef struct
{
    uint8_t          un8IntrEnable;    /**< Interrupt Enable ::TRNG_INTR_e (Bit Order) */
} TRNG_CFG_t;

/**
 *******************************************************************************
 * @brief       TRNG Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::TRNG_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnTRNG_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize TRNG.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TRNG_Init(TRNG_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize TRNG.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TRNG_Uninit(TRNG_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration TRNG.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : TRNG Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TRNG_SetConfig(TRNG_ID_e eId, TRNG_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ TRNG.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TRNG_SetIRQ(TRNG_ID_e eId, TRNG_OPS_e eOps, pfnTRNG_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Set to generate random number TRNG.
 * @param[in]   eId : Instance Id.
 * @param[in]   bEnable : Enable / Disable generation TRNG.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TRNG_SetGenerate(TRNG_ID_e eId, bool bEnable);

/**
 *******************************************************************************
 * @brief       Get Result of generation TRNG.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun32Out : Result of generation TRNG.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TRNG_GetResult(TRNG_ID_e eId, uint32_t *pun32Out);

/**
 *******************************************************************************
 * @brief       Set waiting to complete generation random number TRNG.
 * @param[in]   eId : Instance Id.
 * @param[in]   un32Timeout : Timeout of waiting of generation TRNG.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TRNG_SetWaitComplete(TRNG_ID_e eId, uint32_t un32Timeout);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_TRNG_H_ */

/** @} */
/** @} */
