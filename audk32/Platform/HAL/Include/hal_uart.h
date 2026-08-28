/**
 *******************************************************************************
 * @file        hal_uart.h
 * @author      ABOV R&D Division
 * @brief       UART communication
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
 * @defgroup    HAL_UART UART
 * @{
 * @brief       Universal Asynchronous Receiver Transmitter (UART)
 */

#ifndef _HAL_UART_H_
#define _HAL_UART_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"
#include "type/uart_type.h"

/**
 * @brief UART Clock Configuration
 **/
typedef struct
{
    UART_CLK_e         eClk;
    UART_CLK_MCCR_e    eMccr;         /**< When selecting MCCR at eClk */
    uint8_t            un8MccrDiv;    /**< When selecting MCCR at eClk */
} UART_CLK_CFG_t;

/**
 * @brief UART Mode Configuration
 */
typedef struct
{
    uint32_t         un32BaudRate;     /**< Baud Rate */
    UART_DATA_e      eData;            
    UART_PARITY_e    eParity;          
    UART_STOP_e      eStop;            
    bool             bIntrLSEnable;    /**< Line Status Interrupt Enable */
} UART_CFG_t;

/**
 * @brief UART IRQ handler context
 */
typedef struct
{
    UART_ID_e eId;
} UART_Context_t;

/**
 *******************************************************************************
 * @brief       UART Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::UART_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnUART_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize UART.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_UART_Init(UART_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize UART.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_UART_Uninit(UART_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration UART.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClkCfg : UART Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_UART_SetClkConfig(UART_ID_e eId, UART_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration UART.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : UART Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_UART_SetConfig(UART_ID_e eId, UART_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ UART.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_UART_SetIRQ(UART_ID_e eId, UART_OPS_e eOps, pfnUART_IRQ_Handler_t pfnHandler,
                          void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Transmit Data UART.
 * @param[in]   eId : Instance Id.
 * @param[in]   *pun8Out : Transmit Data.
 * @param[in]   un32Len : Data Length.
 * @param[in]   bEnForcePoll : En-force polling Operation (Ignored IO Operation by SetIRQ).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_UART_Transmit(UART_ID_e eId, uint8_t *pun8Out, uint32_t un32Len, 
                            bool bEnForcePoll);

/**
 *******************************************************************************
 * @brief       Receive Data UART.
 * @param[in]   eId : Instance Id.
 * @param[in]   *pun8In : Receive Data.
 * @param[in]   un32Len : Data Length.
 * @param[in]   bEnForcePoll : En-force polling Operation (Ignored IO Operation by SetIRQ).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_UART_Receive(UART_ID_e eId, uint8_t *pun8In, uint32_t un32Len, 
                           bool bEnForcePoll);

/**
 *******************************************************************************
 * @brief       Abort Transmission or Receiption UART.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_UART_Abort(UART_ID_e eId);

/**
 *******************************************************************************
 * @brief       Get Busy Status UART.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun8Busy : Busy Status (true = busy, false = not busy).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_UART_GetBusyStatus(UART_ID_e eId, bool *pbBusy);

/**
 *******************************************************************************
 * @brief       Get Line Status UART.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun8Status : Line Status ::UART_LINE_STATUS_e.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_UART_GetLineStatus(UART_ID_e eId, uint8_t *pun8Status);

/**
 *******************************************************************************
 * @brief       Set Inter Frame Delay UART.
 * @param[in]   eId : Instance Id.
 * @param[in]   un8Delay : Delay between each frame (0 ~ 7).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_UART_SetIFDelay(UART_ID_e eId, uint8_t un8Delay);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_UART_H_ */

/** @} */
/** @} */

