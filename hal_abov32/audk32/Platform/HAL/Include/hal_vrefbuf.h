/**
 *******************************************************************************
 * @file        hal_vrefbuf.h
 * @author      ABOV R&D Division
 * @brief       Cyclic Redundancy Check
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
 * @defgroup    HAL_VREFBUF VREFBUF
 * @{
 * @brief       Cyclic Redundancy Check
 */

#ifndef _HAL_VREFBUF_H_
#define _HAL_VREFBUF_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief VREFBUF Instance Id
 */
typedef enum
{
    VREFBUF_ID_0,
    VREFBUF_ID_1,
    VREFBUF_ID_2,
    VREFBUF_ID_3,
    VREFBUF_ID_4,
    VREFBUF_ID_5,
    VREFBUF_ID_6,
    VREFBUF_ID_7,
    VREFBUF_ID_8,
    VREFBUF_ID_9,
    VREFBUF_ID_MAX
} VREFBUF_ID_e;

/**
 * @brief VREFBUF Mode
 */
typedef enum
{
    VREFBUF_MODE_NONE,        /**< Operation Interrupt with DMA */
    VREFBUF_MODE_EXTERNAL,    /**< External source */
    VREFBUF_MODE_VDDEXT,      /**< Bypass mode */
    VREFBUF_MODE_INTERNAL,    /**< internal source (2.0V / 2.5V) */
    VREFBUF_MODE_MAX
} VREFBUF_MODE_e;

typedef enum
{
    VREFBUF_VOLTAGE_INT20V,
    VREFBUF_VOLTAGE_INT25V,
    VREFBUF_VOLTAGE_MAX
} VREFBUF_VOLTAGE_e;

/**
 * @brief CRC Operation
 */
typedef enum
{
    VREFBUF_OPS_POLL,        /**< Operation Polling */
    VREFBUF_OPS_INTR,        /**< Operation Interrupt with DMA */
    VREFBUF_OPS_NMI,
    VREFBUF_OPS_MAX
} VREFBUF_OPS_e;

/**
 * @brief VREFBUF Mode Configuration
 */
typedef struct
{
    VREFBUF_MODE_e          eMode;
    VREFBUF_VOLTAGE_e       eVoltage;
    uint32_t                un32StlTime;
} VREFBUF_CFG_t;

/**
 *******************************************************************************
 * @brief       VREFBUF Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type (NONE).
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnVREFBUF_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize VREFBUF.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_VREFBUF_Init(VREFBUF_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize VREFBUF.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_VREFBUF_Uninit(VREFBUF_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration VREFBUF.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : VREFBUF Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_VREFBUF_SetConfig(VREFBUF_ID_e eId, VREFBUF_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ VREFBUF.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_VREFBUF_SetIRQ(VREFBUF_ID_e eId, VREFBUF_OPS_e eOps, pfnVREFBUF_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Set waiting to stable VREFBUF.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_VREFBUF_SetWaitStable(VREFBUF_ID_e eId, uint32_t un32Timeout);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_VREFBUF_H_ */

/** @} */
/** @} */
