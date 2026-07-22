/**
 *******************************************************************************
 * @file        hal_tempsens.h
 * @author      ABOV R&D Division
 * @brief       Temperature Sensor
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
 * @defgroup    HAL_TEMPSENS TempSens
 * @{
 * @brief       Temperature Sensor
 */

#ifndef _HAL_TEMPSENS_H_
#define _HAL_TEMPSENS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief TEMPSENS Instance Id
 */
typedef enum
{
    TEMPSENS_ID_0,
    TEMPSENS_ID_1,
    TEMPSENS_ID_2,
    TEMPSENS_ID_3,
    TEMPSENS_ID_4,
    TEMPSENS_ID_5,
    TEMPSENS_ID_6,
    TEMPSENS_ID_7,
    TEMPSENS_ID_8,
    TEMPSENS_ID_9,
    TEMPSENS_ID_MAX
} TEMPSENS_ID_e;

/**
 * @brief TEMPSENS Reference Clock
 */
typedef enum
{
    TEMPSENS_REF_CLK_HSI,     /**< High Speed Internal Clock Source */
    TEMPSENS_REF_CLK_MCLK,    /**< Master Clock Source */
    TEMPSENS_REF_CLK_HSE,     /**< High Speed External Clock Source */
    TEMPSENS_REF_CLK_LSE,     /**< Low Speed External Clock Source */
    TEMPSENS_REF_CLK_PCLK,    /**< Peripheral Clock Source */
    TEMPSENS_REF_CLK_MAX
} TEMPSENS_REF_CLK_e;

/**
 * @brief TEMPSENS Sense Clock
 */
typedef enum
{
    TEMPSENS_SEN_CLK_LSITS,                              /**< Low Speed Internal Temperature Sensing Oscillator Source */
    TEMPSENS_SEN_CLK_MAX
} TEMPSENS_SEN_CLK_e;

/**
 * @brief TEMPSENS Operation
 */
typedef enum
{
    TEMPSENS_OPS_POLL,        /**< Operation Polling */
    TEMPSENS_OPS_INTR,        /**< Operation Interrupt */
    TEMPSENS_OPS_MAX
} TEMPSENS_OPS_e;

/**
 * @brief TEMPSENS Event
 */
typedef enum
{
    TEMPSENS_EVENT_MATCHED    = BIT(0),    /**< Match or Done occurred */
    TEMPSENS_EVENT_MAX
} TEMPSENS_EVENT_e;

/**
 * @brief TEMPSENS Mode Configuration
 */
typedef struct
{
    TEMPSENS_REF_CLK_e  eRefClk; 
    TEMPSENS_SEN_CLK_e  eSenClk;
} TEMPSENS_CFG_t;

/**
 * @brief TEMPSENS IRQ handler context
 */
typedef struct
{
    TEMPSENS_ID_e eId;    /**< TEMPSENS Instance Id */
} TEMPSENS_Context_t;

/**
 *******************************************************************************
 * @brief       TEMPSENS Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::TEMPSENS_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnTEMPSENS_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize TEMPSENS.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TEMPSENS_Init(TEMPSENS_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize TEMPSENS.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TEMPSENS_Uninit(TEMPSENS_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration TEMPSENS.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : TEMPSENS Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TEMPSENS_SetConfig(TEMPSENS_ID_e eId, TEMPSENS_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ TEMPSENS.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TEMPSENS_SetIRQ(TEMPSENS_ID_e eId, TEMPSENS_OPS_e eOps, pfnTEMPSENS_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Start TEMPSENS.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TEMPSENS_Start(TEMPSENS_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop TEMPSENS.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TEMPSENS_Stop(TEMPSENS_ID_e eId);

/**
 *******************************************************************************
 * @brief       Get Data TEMPSENS.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun32Data : Current Sense Data.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TEMPSENS_GetData(TEMPSENS_ID_e eId, uint32_t *pun32Data);

/**
 *******************************************************************************
 * @brief       Get Temperature TEMPSENS.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pn8Temp : Current temperature.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TEMPSENS_GetTemp(TEMPSENS_ID_e eId, int8_t *pn8Temp);

/**
 *******************************************************************************
 * @brief       Set waiting to complete matched count TEMPSENS.
 * @param[in]   eId : Instance Id.
 * @param[in]   un32Timeout : Timeout of waiting of matched count TEMPSENS.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TEMPSENS_SetWaitComplete(TEMPSENS_ID_e eId, uint32_t un32Timeout);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_TEMPSENS_H_ */

/** @} */
/** @} */
