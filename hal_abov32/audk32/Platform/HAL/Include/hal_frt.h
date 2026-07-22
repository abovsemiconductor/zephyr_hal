/**
 *******************************************************************************
 * @file        hal_frt.h
 * @author      ABOV R&D Division
 * @brief       Free Run Timer
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
 * @defgroup    HAL_FRT FRT
 * @{
 * @brief       Free Run Timer
 */

#ifndef _HAL_FRT_H_
#define _HAL_FRT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

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

/**
 * @brief FRT Clock Configuration
 */
typedef struct
{
    FRT_CLK_e            eClk;
    FRT_CLK_MCCR_e       eMccr;         /**< When selecting MCCR at eClk */
    uint8_t              un8MccrDiv;    /**< When selecting MCCR at eClk */
    FRT_CLK_PREDIV_e     ePreDiv;       /**< Post-divider after eClk selection */
} FRT_CLK_CFG_t;

/**
 * @brief FRT Mode Configuration
 */
typedef struct
{
    FRT_MODE_e    eMode;
    FRT_INTR_e    eIntr;
    uint32_t      un32MatchCnt;    /**< Match Counter value */
} FRT_CFG_t;

/**
 * @brief FRT IRQ Hander Context
 */
typedef struct
{
    FRT_ID_e eId;    /**< FRT Instance Id */
} FRT_Context_t;

/**
 *******************************************************************************
 * @brief       FRT Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::FRT_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnFRT_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize FRT.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_FRT_Init(FRT_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize FRT.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_FRT_Uninit(FRT_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration FRT.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClkCfg : FRT Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_FRT_SetClkConfig(FRT_ID_e eId, FRT_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration FRT.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : FRT Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_FRT_SetConfig(FRT_ID_e eId, FRT_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ FRT.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_FRT_SetIRQ(FRT_ID_e eId, FRT_OPS_e eOps, pfnFRT_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Start FRT.
 * @param[in]   eId : Instance Id.
 * @param[in]   bResume : true : not clear counter, false : clear counter
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_FRT_Start(FRT_ID_e eId, bool bResume);

/**
 *******************************************************************************
 * @brief       Stop FRT.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_FRT_Stop(FRT_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set waiting interrupt FRT.
 * @param[in]   eId : Instance Id.
 * @param[in]   un32Timeout : Timeout of waiting interrupt FRT.
 * @param[out]  *pun8Event return FRT event ::FRT_EVENT_e
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_FRT_SetWaitComplete(FRT_ID_e eId, uint32_t un32Timeout, uint8_t *pun8Event);

/**
 *******************************************************************************
 * @brief       Set waiting interrupt FRT.
 * @param[in]   eId : Instance Id.
 * @param[in]   bMatch : false : Count value, true : Match Count value
 * @param[out]  *pun32Count return FRT Count data
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_FRT_ReadCount(FRT_ID_e eId, bool bMatch ,uint32_t *pun32Count);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_FRT_H_ */

/** @} */
/** @} */
