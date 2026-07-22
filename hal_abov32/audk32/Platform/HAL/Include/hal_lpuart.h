/**
 *******************************************************************************
 * @file        hal_lpuart.h
 * @author      ABOV R&D Division
 * @brief       LPUART communication
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
 * @defgroup    HAL_LPUART LPUART
 * @{
 * @brief       Low Power Universal Asynchronous Receiver Transmitter (LPUART)
 */

#ifndef _HAL_LPUART_H_
#define _HAL_LPUART_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief LPUART Instance Id
 */
typedef enum
{
    LPUART_ID_0   = 0,
    LPUART_ID_1   = 1,
    LPUART_ID_2   = 2,
    LPUART_ID_3   = 3,
    LPUART_ID_4   = 4,
    LPUART_ID_5   = 5,
    LPUART_ID_MAX
} LPUART_ID_e;

/**
 * @brief LPUART Clock Source
 */
typedef enum
{
    LPUART_CLK_PCLK,    /**< Peripheral Clock source */
    LPUART_CLK_MCCR,    /**< Misc Clock source ::LPUART_CLK_MCCR_e */
    LPUART_CLK_MAX
} LPUART_CLK_e;

/**
 * @brief LPUART MCCR (Misc Clock) Source
 */
typedef enum
{
    LPUART_CLK_MCCR_LSI,    /**< Low Speed Internal Clock source */
    LPUART_CLK_MCCR_LSE,    /**< Low Speed External Clock source */
    LPUART_CLK_MCCR_MCLK,   /**< Master Clock source */
    LPUART_CLK_MCCR_HSI,    /**< High Speed Internal Clock source */
    LPUART_CLK_MCCR_HSE,    /**< High Speed External Clock source */
    LPUART_CLK_MCCR_PLL,    /**< Phase-Locked Loop (PLL) Clock source */
    LPUART_CLK_MCCR_MAX
} LPUART_CLK_MCCR_e;

/**
 * @brief LPUART Data Bit
 */
typedef enum
{
    LPUART_DATA_5,    /**< 5bit mode */
    LPUART_DATA_6,    /**< 6bit mode */
    LPUART_DATA_7,    /**< 7bit mode */
    LPUART_DATA_8,    /**< 8bit mode */
    LPUART_DATA_MAX
} LPUART_DATA_e;

/**
 * @brief LPUART Parity Bit
 */
typedef enum
{
    LPUART_PARITY_ODD,     /**< Odd Parity used */
    LPUART_PARITY_EVEN,    /**< Even Parity used */
    LPUART_PARITY_NONE,    /**< Parity not used */
    LPUART_PARITY_MAX
} LPUART_PARITY_e;

/**
 * @brief LPUART Stop Bit
 */
typedef enum
{
    LPUART_STOP_1,    /**< 1bit Stop */
    LPUART_STOP_2,    /**< 2bit Stop */
    LPUART_STOP_MAX
} LPUART_STOP_e;

/**
 * @brief LPUART Oversampling
 */
typedef enum
{
    LPUART_OVS_16,         /**< 16 oversampling */
    LPUART_OVS_8,          /**< 8 oversampling */
    LPUART_OVS_NONE,       /**< No oversamping (Only 1 sampling and LSE 32.768KHz) */
    LPUART_OVS_MAX
} LPUART_OVS_e;

/**
 * @brief LPUART BaudRate Compensation
 */
typedef enum
{
    LPUART_BC_PLUS,        /**< Plus 1 clock compensation */
    LPUART_BC_MINUS,       /**< Minus 1 clock compensation */
    LPUART_BC_MAX
} LPUART_BC_e;

/** 
 * @brief LPUART BaudRate Compensation Bit
 */
typedef enum
{
    LPUART_BC_BIT_NONE  = 0,
    LPUART_BC_BIT_0     = BIT(0),    /**< 1 clock compensation */
    LPUART_BC_BIT_1     = BIT(1),
    LPUART_BC_BIT_2     = BIT(2),
    LPUART_BC_BIT_3     = BIT(3),
    LPUART_BC_BIT_4     = BIT(4),
    LPUART_BC_BIT_5     = BIT(5),
    LPUART_BC_BIT_6     = BIT(6),
    LPUART_BC_BIT_7     = BIT(7),
    LPUART_BC_PARITY    = BIT(8)
} LPUART_BC_BIT_e;

/**
 * @brief LPUART Line Status
 */
typedef enum
{
    LPUART_LINE_STATUS_RX_LINE_BUSY     = BIT(0),    /**< Rx Line Busy */
    LPUART_LINE_STATUS_OVERRUN_ERROR    = BIT(1),    /**< Overrun error */
    LPUART_LINE_STATUS_PARITY_ERROR     = BIT(2),    /**< Parity error */
    LPUART_LINE_STATUS_FRAME_ERROR      = BIT(3),    /**< Frame error */
} LPUART_LINE_STATUS_e;

/**
 * @brief LPUART Event
 */
typedef enum
{
    LPUART_EVENT_TX_DONE           = BIT(0),    /**< Transmission is completed */
    LPUART_EVENT_RX_DONE           = BIT(1),    /**< Reception is completed */
    LPUART_EVENT_SB_DEELSLEEP      = BIT(2),    /**< Start Bit Detect in Deep Sleep */
    LPUART_EVENT_RCD               = BIT(3),    /**< Receive Charactor Detect */
    LPUART_EVENT_RTO               = BIT(4),    /**< Receive Time Out */
    LPUART_EVENT_LINE_ERROR        = BIT(5),    /**< Line error */
    LPUART_EVENT_FRAME_ERROR       = BIT(6),    /**< Frame error */
    LPUART_EVENT_PARITY_ERROR      = BIT(7),    /**< Parity error */
    LPUART_EVENT_OVERFLOW_ERROR    = BIT(8),    /**< Overflow error */
} LPUART_EVENT_e;

/**
 * @brief LPUART Busy Status
 */
typedef enum
{
    LPUART_BUSY_NONE,
    LPUART_BUSY_TX,
    LPUART_BUSY_RX,
    LPUART_BUSY_MAX
} LPUART_BUSY_e;

/**
 * @brief LPUART Operation
 */
typedef enum
{
    LPUART_OPS_POLL,        /**< Operation Polling */
    LPUART_OPS_INTR,        /**< Operation Interrupt */
    LPUART_OPS_INTR_DMA,    /**< Operation Interrupt with DMA */
    LPUART_OPS_NMI,         /**< Operation NMI */
    LPUART_OPS_NMI_DMA,     /**< Operation NMI with DMA */
    LPUART_OPS_MAX
} LPUART_OPS_e;

/**
 * @brief LPUART Clock Configuration
 **/
typedef struct
{
    LPUART_CLK_e         eClk;
    LPUART_CLK_MCCR_e    eMccr;         /**< When selecting MCCR at eClk */
    uint8_t              un8MccrDiv;    /**< When selecting MCCR at eClk */
} LPUART_CLK_CFG_t;

/**
 * @brief LPUART Data Enable Configuration
 **/
typedef struct
{
    bool               bEnable;
    bool               bPolarity;        /**< true: Active High, false: Active Low */
    uint8_t            un8StartTime;     /**< Active Level Start Time */
    uint8_t            un8FinishTime;    /**< Active Level Finish Time */
} LPUART_DE_CFG_t;

/**
 * @brief LPUART Receive Character Detect Configuration
 **/
typedef struct
{
    bool               bEnable;
    bool               bIntrEnable;      /**< Interrupt Enable */
    uint8_t            un8RCDData;       /**< Detection Charactor */
} LPUART_RCD_CFG_t;

/**
 * @brief LPUART Receive Time Out Configuration
 **/
typedef struct
{
    bool               bEnable;
    bool               bIntrEnable;      /**< Interrupt Enable */
    uint32_t           un32TimeOut;      /**< Time Out */
} LPUART_RTO_CFG_t;

/**
 * @brief LPUART Transmit Delay Configuration
 **/
typedef struct
{
    bool               bEnable;
    uint8_t            un8Delay;         /**< Transmit Delay */
} LPUART_TXDLY_CFG_t;

/**
 * @brief LPUART BaudRate Compensation Configuration
 **/
typedef struct
{
    bool               bEnable;
    LPUART_BC_e        eBC;              /**< Plus 1 or Minus 1 compensation */
    uint16_t           un16BC;           /**< 9 Bit (Data 0 Bit to Parity Bit) */
} LPUART_BC_CFG_t;

/**
 * @brief LPUART Mode Configuration
 */
typedef struct
{
    uint32_t           un32BaudRate;     /**< Baud Rate */
    LPUART_DATA_e      eData;            
    LPUART_PARITY_e    eParity;          
    LPUART_STOP_e      eStop;            
    LPUART_OVS_e       eOVS;             /**< Over Sampling */

    LPUART_RTO_CFG_t   tRtoCfg;          /**< Receive Time Out Configuration */
} LPUART_CFG_t;

/**
 * @brief LPUART IRQ handler context
 */
typedef struct
{
    LPUART_ID_e eId;
} LPUART_Context_t;

/**
 *******************************************************************************
 * @brief       LPUART Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::LPUART_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnLPUART_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize LPUART.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LPUART_Init(LPUART_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize LPUART.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LPUART_Uninit(LPUART_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration LPUART.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClkCfg : LPUART Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LPUART_SetClkConfig(LPUART_ID_e eId, LPUART_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration LPUART.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : LPUART Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LPUART_SetConfig(LPUART_ID_e eId, LPUART_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ LPUART.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LPUART_SetIRQ(LPUART_ID_e eId, LPUART_OPS_e eOps, pfnLPUART_IRQ_Handler_t pfnHandler,
                          void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Transmit Data LPUART.
 * @param[in]   eId : Instance Id.
 * @param[in]   *pun8Out : Transmit Data.
 * @param[in]   un32Len : Data Length.
 * @param[in]   bEnForcePoll : En-force polling Operation (Ignored IO Operation by SetIRQ).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LPUART_Transmit(LPUART_ID_e eId, uint8_t *pun8Out, uint32_t un32Len, 
                            bool bEnForcePoll);

/**
 *******************************************************************************
 * @brief       Receive Data LPUART.
 * @param[in]   eId : Instance Id.
 * @param[in]   *pun8In : Receive Data.
 * @param[in]   un32Len : Data Length.
 * @param[in]   bEnForcePoll : En-force polling Operation (Ignored IO Operation by SetIRQ).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LPUART_Receive(LPUART_ID_e eId, uint8_t *pun8In, uint32_t un32Len, 
                           bool bEnForcePoll);

/**
 *******************************************************************************
 * @brief       Abort Transmission or Receiption LPUART.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LPUART_Abort(LPUART_ID_e eId);

/**
 *******************************************************************************
 * @brief       Get Busy Status LPUART.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun8Busy : Busy Status (true = busy, false = not busy).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LPUART_GetBusyStatus(LPUART_ID_e eId, bool *pbBusy);

/**
 *******************************************************************************
 * @brief       Get Line Status LPUART.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun8Status : Line Status ::LPUART_LINE_STATUS_e.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LPUART_GetLineStatus(LPUART_ID_e eId, uint8_t *pun8Status);

/**
 *******************************************************************************
 * @brief       Set Inter Frame Delay LPUART.
 * @param[in]   eId : Instance Id.
 * @param[in]   un8Delay : Delay between each frame (0 ~ 7).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LPUART_SetIFDelay(LPUART_ID_e eId, uint8_t un8Delay);

/**
 *******************************************************************************
 * @brief       Set BaudRate Compensation LPUART.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptBcCfg : BaudRate Compensation Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LPUART_SetBaudRateCompensation(LPUART_ID_e eId, LPUART_BC_CFG_t *ptBcCfg);

/**
 *******************************************************************************
 * @brief       Set Receive Character Detect LPUART.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptRcdCfg : Receive Character Detection Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LPUART_SetReceiveCharDetect(LPUART_ID_e eId, LPUART_RCD_CFG_t *ptRcdCfg);

/**
 *******************************************************************************
 * @brief       Set Transmit Delay LPUART.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptTxDlyCfg : Transmit Delay Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LPUART_SetTransmitDelay(LPUART_ID_e eId, LPUART_TXDLY_CFG_t *ptTxDlyCfg);

/**
 *******************************************************************************
 * @brief       Set Data Enable LPUART.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptDeCfg : Data Enable Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LPUART_SetDataEnable(LPUART_ID_e eId, LPUART_DE_CFG_t *ptDeCfg);

/**
 *******************************************************************************
 * @brief       Set Receive Timeout LPUART.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptDeCfg : Receive Timeout Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LPUART_SetReceiveTimeout(LPUART_ID_e eId, LPUART_RTO_CFG_t *ptRtoCfg);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_LPUART_H_ */

/** @} */
/** @} */

