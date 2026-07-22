/**
 *******************************************************************************
 * @file        hal_timer6.h
 * @author      ABOV R&D Division
 * @brief       6N typed timer
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
 * @defgroup    HAL_TIMER6 TIMER6
 * @{
 * @brief       16-bit 100Hz General Purpose Timer
 */

#ifndef _HAL_TIMER6_H_
#define _HAL_TIMER6_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief TIMER6 Instance Id
 */
typedef enum
{
    TIMER6_ID_0,
    TIMER6_ID_1,
    TIMER6_ID_2,
    TIMER6_ID_3,
    TIMER6_ID_4,
    TIMER6_ID_5,
    TIMER6_ID_6,
    TIMER6_ID_7,
    TIMER6_ID_8,
    TIMER6_ID_9,
    TIMER6_ID_MAX
} TIMER6_ID_e;

/**
 * @brief TIMER6 Interrupt Status
 */
typedef enum
{
    TIMER6_INTR_FLAG_MATCH,   /**< Match occurred */
    TIMER6_INTR_FLAG_MAX
} TIMER6_INTR_FLAG_e;

/**
 * @brief TIMER6 Event
 */
typedef enum
{
    TIMER6_EVENT_PERIODIC_MATCH = BIT(0),
    TIMER6_EVENT_MAX,
} TIMER6_EVENT_e;

/**
 * @brief TIMER6 Operation
 */
typedef enum
{
    TIMER6_OPS_POLL,        /**< Operation Polling */
    TIMER6_OPS_INTR,        /**< Operation Interrupt */
    TIMER6_OPS_NMI,         /**< Operation Non-maskable Interrupt */
    TIMER6_OPS_MAX
} TIMER6_OPS_e;

/**
 * @brief TIMER6 Mode Configuration
 */
typedef struct
{
    bool        bIntrEnable;    /**< Interrupt Enable */
    uint16_t    un16Data;       /**< Data or General Data */
} TIMER6_CFG_t;

/**
 * @brief TIMER6 IRQ handler context
 */
typedef struct
{
    TIMER6_ID_e eId;    /**< TIMER6 Instance Id */
} TIMER6_Context_t;

/**
 *******************************************************************************
 * @brief       TIMER6 Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::TIMER6_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnTIMER6_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize TIMER6.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER6_Init(TIMER6_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize TIMER6.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER6_Uninit(TIMER6_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration TIMER6.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : TIMER6 Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER6_SetConfig(TIMER6_ID_e eId, TIMER6_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ TIMER6.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER6_SetIRQ(TIMER6_ID_e eId, TIMER6_OPS_e eOps, pfnTIMER6_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Start TIMER6.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER6_Start(TIMER6_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop TIMER6.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER6_Stop(TIMER6_ID_e eId);

/**
 *******************************************************************************
 * @brief       Get Interrupt Status TIMER6.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun32Status : ::TIMER6_INTR_FLAG_e (Bit Order).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER6_GetStatus(TIMER6_ID_e eId, uint32_t *pun32Status);

/**
 *******************************************************************************
 * @brief       Get Data TIMER6.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun32Data : Get Data from Specific Buffer by eSel.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER6_GetData(TIMER6_ID_e eId, uint32_t *pun32Data);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_TIMER6_H_ */

/** @} */
/** @} */
