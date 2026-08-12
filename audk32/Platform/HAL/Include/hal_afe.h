/**
 *******************************************************************************
 * @file        hal_afe.h
 * @author      ABOV R&D Division
 * @brief       Analog Front End (AFE)
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
 * @defgroup    HAL_AFE AFE
 * @{
 * @brief       N-channel Analog Front End (AFE)
 */

#ifndef _HAL_AFE_H_
#define _HAL_AFE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief AFE Instance Id
 */
typedef enum
{
    AFE_ID_0,
    AFE_ID_1,
    AFE_ID_2,
    AFE_ID_3,
    AFE_ID_4,
    AFE_ID_5,
    AFE_ID_6,
    AFE_ID_7,
    AFE_ID_8,
    AFE_ID_9,
    AFE_ID_MAX
} AFE_ID_e;

/**
 * @brief AFE Mode
 */
typedef enum
{
    AFE_MODE_CMP,          /**< OP-Amp and Comparator */
    AFE_MODE_OPAMP,        /**< Only OP-Amp */
    AFE_MODE_UNITY_GAIN,   /**< Unity Gain Buffer (Gain = 1) */
    AFE_MODE_MAX
} AFE_MODE_e;

/**
 * @brief AFE Comparator Interrupt Trigger
 */
typedef enum
{
    AFE_CMP_INTR_TRG_DISABLE,      /**< Comparator Trigger Disable */
    AFE_CMP_INTR_TRG_LEVEL,        /**< Comparator Trigger Level */
    AFE_CMP_INTR_TRG_SINGLE_EDGE,  /**< Comparator Trigger Rising or Falling Edge */
    AFE_CMP_INTR_TRG_BOTH_EDGE,    /**< Comparator Trigger Both Edge */
    AFE_CMP_INTR_TRG_MAX
} AFE_CMP_INTR_TRG_e;

/**
 * @brief AFE Comparator Interrupt Trigger Polarity
 */
typedef enum
{
    AFE_CMP_INTR_TRG_POL_LOW_FALLING,    /**< Low Level or Falling Edge */
    AFE_CMP_INTR_TRG_POL_HIGH_RISING,    /**< High Level or Rising Edge */
    AFE_CMP_INTR_TRG_POL_MAX
} AFE_CMP_INTR_TRG_POL_e;

/**
 * @brief AFE Operation
 */
typedef enum
{
    AFE_OPS_POLL,        /**< Operation Polling */
    AFE_OPS_INTR,        /**< Operation Interrupt */
    AFE_OPS_NMI,         /**< Operation NMI */
    AFE_OPS_MAX
} AFE_OPS_e;

/**
 * @brief AFE Event
 */
typedef enum
{
    AFE_CMP_EVENT_LOW          = BIT(0),    /**< Level triggered */
    AFE_CMP_EVENT_HIGH         = BIT(1),    /**< Level triggered */
    AFE_CMP_EVENT_RISING       = BIT(2),    /**< Rising Egde triggered */
    AFE_CMP_EVENT_FALLING      = BIT(3),    /**< Falling Egde triggered */
    AFE_CMP_EVENT_MAX
} AFE_CMP_EVENT_e;

/**
 * @brief AFE Comparator Configuration
 */
typedef struct
{
    AFE_CMP_INTR_TRG_e        eIntrTrg;
    AFE_CMP_INTR_TRG_POL_e    eIntrTrgPol;
    bool                      bTrgOutPol;    /**< true : inverted, false : normal */
    uint8_t                   un8DebCnt;     /** < Debounce Filter Counter (0 : disable) */
} AFE_CMP_CFG_t;

/**
 * @brief AFE Mode Configuration
 */
typedef struct
{
    AFE_MODE_e            eMode;
    AFE_CMP_CFG_t         tCmp;
} AFE_CFG_t;

/**
 * @brief AFE IRQ handler context
 */
typedef struct
{
    AFE_ID_e eId;        /**< AFE Instance Id */
} AFE_Context_t;

/**
 *******************************************************************************
 * @brief       AFE Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::AFE_CMP_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnAFE_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize AFE.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_AFE_Init(AFE_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize AFE.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_AFE_Uninit(AFE_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration AFE.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : AFE Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_AFE_SetConfig(AFE_ID_e eId, AFE_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ AFE.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @param[in]   bNonMask : Enable non-maskable Interrupt.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_AFE_SetIRQ(AFE_ID_e eId, AFE_OPS_e eOps, pfnAFE_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio, bool bNonMask);

/**
 *******************************************************************************
 * @brief       Start comparation AFE.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_AFE_Start(AFE_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop comparation AFE.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_AFE_Stop(AFE_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set waiting to complete comparation AFE.
 * @param[in]   eId : Instance Id
 * @param[in]   un32Timeout : Timeout of waiting of comparation AFE.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_AFE_SetWaitComplete(AFE_ID_e eId, uint32_t un32Timeout);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_AFE_H_ */

/** @} */
/** @} */
