/**
 *******************************************************************************
 * @file        hal_rng.h
 * @author      ABOV R&D Division
 * @brief       Random Number Generator
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
 * @defgroup    HAL_RNG RNG 
 * @{
 * @brief       Random Number Generator
 */

#ifndef _HAL_RNG_H_
#define _HAL_RNG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief RNG Instance Id
 */
typedef enum
{
    RNG_ID_0,
    RNG_ID_1,
    RNG_ID_2,
    RNG_ID_3,
    RNG_ID_4,
    RNG_ID_5,
    RNG_ID_6,
    RNG_ID_7,
    RNG_ID_8,
    RNG_ID_9,
    RNG_ID_MAX
} RNG_ID_e;

/**
 * @brief LFS Clock (Linear Feedback Shift)
 */
typedef enum
{
    RNG_CLK_LFS_OSC,          /**< Internal LFS Oscillator */
    RNG_CLK_LFS_LSI,          /**< Low Speed Internal Clock */
    RNG_CLK_LFS_MAX
} RNG_CLK_LFS_e;

/**
 * @brief CAS Clock (Cellular Automata Shift) 
 */
typedef enum
{
    RNG_CLK_CAS_OSC,          /**< Internal CAS Oscillator */
    RNG_CLK_CAS_HSI,          /**< High Speed Internal Clock */
    RNG_CLK_CAS_MAX
} RNG_CLK_CAS_e;

/**
 * @brief RNG Interrupt
 */
typedef enum
{
    RNG_INTR_NONE     = 0,         /**< Disable Interrupt */
    RNG_INTR_READY    = BIT(0),    /**< Ready Interrupt */
    RNG_INTR_ERROR    = BIT(1),    /**< Error Interrupt */
    RNG_INTR_MAX
} RNG_INTR_e;

/**
 * @brief RNG Event
 */
typedef enum
{
    RNG_EVENT_READY    = BIT(0),    /**< Ready Event */
    RNG_EVENT_ERROR    = BIT(1),    /**< Error Event */
    RNG_EVENT_MAX
} RNG_EVENT_e;

/**
 * @brief RNG Operation
 */
typedef enum
{
    RNG_OPS_POLL,        /**< Operation Polling */
    RNG_OPS_INTR,        /**< Operation Interrupt */
    RNG_OPS_NMI,        /**< Operation NMI */
    RNG_OPS_MAX
} RNG_OPS_e;

/**
 * @brief RNG Mode Configuration
 */
typedef struct
{
    RNG_CLK_LFS_e    eClkLFS;
    RNG_CLK_CAS_e    eClkCAS;
    uint8_t          un8IntrEnable;    /**< Interrupt Enable ::RNG_INTR_e (Bit Order) */
    uint16_t         un16GenTime;      /**< LFSR and CASR generation Time */
} RNG_CFG_t;

/**
 *******************************************************************************
 * @brief       RNG Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::RNG_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnRNG_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize RNG.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RNG_Init(RNG_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize RNG.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RNG_Uninit(RNG_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration RNG.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : RNG Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RNG_SetConfig(RNG_ID_e eId, RNG_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ RNG.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RNG_SetIRQ(RNG_ID_e eId, RNG_OPS_e eOps, pfnRNG_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Set seed RNG.
 * @param[in]   eId : Instance Id.
 * @param[out]  un32Seed : seed.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RNG_SetSeed(RNG_ID_e eId, uint32_t un32Seed);

/**
 *******************************************************************************
 * @brief       Set to generate random number RNG.
 * @param[in]   eId : Instance Id.
 * @param[in]   bEnable : Enable / Disable generation RNG.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RNG_SetGenerate(RNG_ID_e eId, bool bEnable);

/**
 *******************************************************************************
 * @brief       Get Result of generation RNG.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun32Out : Result of generation RNG.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RNG_GetResult(RNG_ID_e eId, uint32_t *pun32Out);

/**
 *******************************************************************************
 * @brief       Set waiting to complete generation random number RNG.
 * @param[in]   eId : Instance Id.
 * @param[in]   un32Timeout : Timeout of waiting of generation RNG.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_RNG_SetWaitComplete(RNG_ID_e eId, uint32_t un32Timeout);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_RNG_H_ */

/** @} */
/** @} */
