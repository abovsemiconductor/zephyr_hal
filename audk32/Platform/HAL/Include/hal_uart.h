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

/**
 * @brief UART Instance Id
 */
typedef enum
{
    UART_ID_0   = 0,
    UART_ID_1   = 1,
    UART_ID_2   = 2,
    UART_ID_3   = 3,
    UART_ID_4   = 4,
    UART_ID_5   = 5,
    UART_ID_6   = 6,
    UART_ID_7   = 7,
    UART_ID_8   = 8,
    UART_ID_9   = 9,
    UART_ID_10  = 10,
    UART_ID_11  = 11,
    UART_ID_12  = 12,
    UART_ID_MAX
} UART_ID_e;

/**
 * @brief UART Clock Source
 */
typedef enum
{
    UART_CLK_PCLK,    /**< Peripheral Clock source */
    UART_CLK_MCCR,    /**< Misc Clock source ::UART_CLK_MCCR_e */
    UART_CLK_MAX
} UART_CLK_e;

/**
 * @brief UART MCCR (Misc Clock) Source
 */
typedef enum
{
    UART_CLK_MCCR_LSI,    /**< Low Speed Internal Clock source */
    UART_CLK_MCCR_LSE,    /**< Low Speed External Clock source */
    UART_CLK_MCCR_MCLK,   /**< Master Clock source */
    UART_CLK_MCCR_HSI,    /**< High Speed Internal Clock source */
    UART_CLK_MCCR_HSE,    /**< High Speed External Clock source */
    UART_CLK_MCCR_PLL,    /**< Phase-Locked Loop (PLL) Clock source */
    UART_CLK_MCCR_MAX
} UART_CLK_MCCR_e;

/**
 * @brief UART Data Bit
 */
typedef enum
{
    UART_DATA_5,    /**< 5bit mode */
    UART_DATA_6,    /**< 6bit mode */
    UART_DATA_7,    /**< 7bit mode */
    UART_DATA_8,    /**< 8bit mode */
    UART_DATA_MAX
} UART_DATA_e;

/**
 * @brief UART Parity Bit
 */
typedef enum
{
    UART_PARITY_ODD,     /**< Odd Parity used */
    UART_PARITY_EVEN,    /**< Even Parity used */
    UART_PARITY_SP_1,    /**< Force "1" sticky Parity */
    UART_PARITY_SP_0,    /**< Force "0" sticky Parity */
    UART_PARITY_NONE,    /**< Parity not used */
    UART_PARITY_MAX
} UART_PARITY_e;

/**
 * @brief UART Stop Bit
 */
typedef enum
{
    UART_STOP_1,    /**< 1bit Stop */
    UART_STOP_2,    /**< 2bit Stop */
    UART_STOP_MAX
} UART_STOP_e;

/**
 * @brief UART Line Status
 */
typedef enum
{
    UART_LINE_STATUS_RX_DONE          = BIT(0),    /**< Data received */
    UART_LINE_STATUS_OVERRUN_ERROR    = BIT(1),    /**< Overrun error */
    UART_LINE_STATUS_PARITY_ERROR     = BIT(2),    /**< Parity error */
    UART_LINE_STATUS_FRAME_ERROR      = BIT(3),    /**< Frame error */
    UART_LINE_STATUS_BREAK            = BIT(4),    /**< Break Condition detected */
    UART_LINE_STATUS_TX_READY         = BIT(5),    /**< Ready for Transmit */
    UART_LINE_STATUS_TX_EMPTY         = BIT(6),    /**< Transmit Data not set */
} UART_LINE_STATUS_e;

/**
 * @brief UART Event
 */
typedef enum
{
    UART_EVENT_TX_DONE           = BIT(0),    /**< Transmission is completed */
    UART_EVENT_RX_DONE           = BIT(1),    /**< Reception is completed */
    UART_EVENT_LINE_ERROR        = BIT(2),    /**< Line error */
    UART_EVENT_BREAK_ERROR       = BIT(3),    /**< Break error */
    UART_EVENT_FRAME_ERROR       = BIT(4),    /**< Frame error */
    UART_EVENT_PARITY_ERROR      = BIT(5),    /**< Parity error */
    UART_EVENT_OVERFLOW_ERROR    = BIT(6),    /**< Overflow error */
} UART_EVENT_e;

/**
 * @brief UART Busy Status
 */
typedef enum
{
    UART_BUSY_NONE,
    UART_BUSY_TX,
    UART_BUSY_RX,
    UART_BUSY_MAX
} UART_BUSY_e;

/**
 * @brief UART Operation
 */
typedef enum
{
    UART_OPS_POLL,        /**< Operation Polling */
    UART_OPS_INTR,        /**< Operation Interrupt */
    UART_OPS_INTR_DMA,    /**< Operation Interrupt with DMA */
    UART_OPS_NMI,         /**< Operation NMI */
    UART_OPS_NMI_DMA,     /**< Operation NMI with DMA */
    UART_OPS_MAX
} UART_OPS_e;

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

