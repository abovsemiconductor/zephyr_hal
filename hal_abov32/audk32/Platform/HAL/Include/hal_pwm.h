/**
 *******************************************************************************
 * @file        hal_pwm.h
 * @author      ABOV R&D Division
 * @brief       Pulse Width Modulation (PWM)
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
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
 * @defgroup    HAL_PWM PWM
 * @{
 * @brief       Pulse Width Modulation (PWM)
 */

#ifndef _HAL_PWM_H_
#define _HAL_PWM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief PWM Instance Id
 */
typedef enum
{
    PWM_ID_0,
    PWM_ID_1,
    PWM_ID_2,
    PWM_ID_3,
    PWM_ID_4,
    PWM_ID_5,
    PWM_ID_6,
    PWM_ID_7,
    PWM_ID_8,
    PWM_ID_9,
    PWM_ID_MAX
} PWM_ID_e;

/**
 * @brief PWM Clock Source
 */
typedef enum
{
    PWM_CLK_PCLK,    /**< Peripheral Clock source */
    PWM_CLK_MAX
} PWM_CLK_e;

/**
 * @brief PWM Clock Divider
 */
typedef enum
{
    PWM_CLK_DIV_2,          /**< In-clock/2 */
    PWM_CLK_DIV_4,          /**< In-clock/4 */
    PWM_CLK_DIV_8,          /**< In-clock/8 */
    PWM_CLK_DIV_16,         /**< In-clock/16 */
    PWM_CLK_DIV_DISABLE,
    PWM_CLK_DIV_MAX
} PWM_CLK_DIV_e;

/**
 * @brief PWM Output Port A Inversion
 */
typedef enum
{
    PWM_PORTA_INV_OFF,
    PWM_PORTA_INV_ON,
    PWM_PORTA_INV_MAX
} PWM_PORTA_INV_e;

/**
 * @brief PWM Event
 */
typedef enum
{
    PWM_EVENT_MATCH     = BIT(0),    /**< Match event */
    PWM_EVENT_MAX,
} PWM_EVENT_e;

/**
 * @brief PWM Operation
 */
typedef enum
{
    PWM_OPS_POLL,        /**< Operation Polling */
    PWM_OPS_INTR,        /**< Operation Interrupt */
    PWM_OPS_MAX
} PWM_OPS_e;

/**
 * @brief PWM Clock Configuration
 */
typedef struct
{
    PWM_CLK_e        eClk;           /**< Clock Source **/
    PWM_CLK_DIV_e    eClkDiv;        /**< eClk Divider before Pre-scaler */
    bool             bPreScaleEn;    /**< Enable Pre-scaler function */
    uint8_t          un8PreScale;    /**< Pre-scaler after eClk selection (un8PreScale + 1) */
} PWM_CLK_CFG_t;

/**
 * @brief PWM Mode Configuration
 */
typedef struct
{
    bool               bSyncEn;       /**< Synchronize this channel to the other channels */
    PWM_PORTA_INV_e    ePAInv;        /**< Channel Port A Output Signal Invert */

    uint16_t           un16Period;    /**< The period value of PWM channel N (un16Period + 1)*/
    uint16_t           un16Duty;      /**< The comparator value (duty) of PWM channel N (un16Duty + 1)*/
} PWM_CFG_t;

/**
 * @brief PWM IRQ handler context
 */
typedef struct
{
    PWM_ID_e eId;    /**< PWM Instance Id */
} PWM_Context_t;

/**
 *******************************************************************************
 * @brief       PWM Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::PWM_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnPWM_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize PWM.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PWM_Init(PWM_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize PWM.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PWM_Uninit(PWM_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration PWM.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClkCfg : PWM Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PWM_SetClkConfig(PWM_ID_e eId, PWM_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration PWM.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : PWM Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PWM_SetConfig(PWM_ID_e eId, PWM_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ PWM.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PWM_SetIRQ(PWM_ID_e eId, PWM_OPS_e eOps, pfnPWM_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Start PWM.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PWM_Start(PWM_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop PWM.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PWM_Stop(PWM_ID_e eId);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_PWM_H_ */

/** @} */
/** @} */

