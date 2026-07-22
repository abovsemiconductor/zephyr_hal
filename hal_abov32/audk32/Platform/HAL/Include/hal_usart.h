/**
 *******************************************************************************
 * @file        hal_usart.h
 * @author      ABOV R&D Division
 * @brief       USART communication
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
 * @defgroup    HAL_USART USART
 * @{
 * @brief       Universal Synchronous/Asynchronous Receiver/Transmitter (USART)
 */

#ifndef _HAL_USART_H_
#define _HAL_USART_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief USART Instance Id
 */
typedef enum
{
    USART_ID_0,
    USART_ID_1,
    USART_ID_2,
    USART_ID_3,
    USART_ID_4,
    USART_ID_5,
    USART_ID_MAX
} USART_ID_e;

/**
 * @brief USART Mode 
 */
typedef enum
{
    USART_MODE_UART,    /**< Asynchronous Mode */
    USART_MODE_USRT,    /**< Synchronous Mode */
    USART_MODE_SPI,     /**< SPI Mode */
    USART_MODE_MAX
} USART_MODE_e;

/**
 * @brief USART Data Bit
 */
typedef enum
{
    USART_DATA_5,    /**< 5bit Mode */
    USART_DATA_6,    /**< 6bit Mode */
    USART_DATA_7,    /**< 7bit Mode */
    USART_DATA_8,    /**< 8bit Mode */
    USART_DATA_9,    /**< 9bit Mode */
    USART_DATA_MAX
} USART_DATA_e;

/**
 * @brief USART Parity Bit
 */
typedef enum
{
    USART_PARITY_NONE,    /**< Parity not used */
    USART_PARITY_EVEN,    /**< Even Parity used */
    USART_PARITY_ODD,     /**< Odd Parity used */
    USART_PARITY_MAX
} USART_PARITY_e;

/**
 * @brief USART Stop Bit
 */
typedef enum
{
    USART_STOP_1,    /**< 1bit Stop */
    USART_STOP_2,    /**< 2bit Stop */
    USART_STOP_MAX
} USART_STOP_e;

/**
 * @brief USART Order Bit for only SPI Mode
 */
typedef enum
{
    USART_BIT_ORDER_LSB,    /**< LSB First */
    USART_BIT_ORDER_MSB,    /**< MSB First */
    USART_BIT_ORDER_MAX
} USART_BIT_ORDER_e;

/**
 * @brief USART Clock Polarity Bit
 */
typedef enum
{
    USART_CLKPOL_TXD_RISE_RXD_FALL,
    USART_CLKPOL_TXD_FALL_RXD_RISE,
    USART_CLKPOL_MAX
} USART_CLKPOL_e;

/**
 * @brief USART Clock Phase Bit
 */
typedef enum
{
    USART_CLKPHA_SAMPLE,
    USART_CLKPHA_SETUP,
    USART_CLKPHA_MAX
} USART_CLKPHA_e;

/**
 * @brief USART Master/Slave for SPI or Sync
 */
typedef enum
{
    USART_MS_SLAVE,     /**< Slave */
    USART_MS_MASTER,    /**< Master */
    USART_MS_MAX
} USART_MS_e;

/**
 * @brief USART Operation
 */
typedef enum
{
    USART_OPS_POLL,        /**< Operation Polling */
    USART_OPS_INTR,        /**< Operation Interrupt */
    USART_OPS_INTR_DMA,    /**< Operation Interrupt with DMA */
    USART_OPS_MAX
} USART_OPS_e;

/**
 * @brief USART Event
 */
typedef enum
{
    USART_EVENT_TX_DONE           = BIT(0),   /**< Transmission is completed */
    USART_EVENT_RX_DONE           = BIT(1),   /**< Reception is completed */
    USART_EVENT_RX_TIMEOUT        = BIT(2),   /**< Receive Timeout */
    USART_EVENT_WAKE_UP           = BIT(3),   /**< Wake-up occurred */
    USART_EVENT_FRAME_ERROR       = BIT(4),   /**< Frame error */
    USART_EVENT_PARITY_ERROR      = BIT(5),   /**< Parity error */
    USART_EVENT_OVERFLOW_ERROR    = BIT(6),   /**< Overflow error */
} USART_EVENT_e;

/**
 * @brief USART Busy Status
 */
typedef enum USART_BUSY
{
    USART_BUSY_NONE,
    USART_BUSY_TX,
    USART_BUSY_RX,
    USART_BUSY_MAX
} USART_BUSY_e;

/**
 * @brief USART Receive Time Out (RTO) Configuration
 */
typedef struct
{
    bool        bEnable;         /** <Function Enable */
    uint32_t    un32RTOCount;    /** < Time-out count value */
} USART_RTO_t;

/**
 * @brief USART Mode Configuration
 */
typedef struct
{
    USART_MODE_e                 eMode;
    uint32_t                     un32BaudRate;    /**< baud rate */
    union 
    {
        struct
        {
            USART_DATA_e         eData; 
            USART_PARITY_e       eParity; 
            USART_STOP_e         eStop; 
            bool                 bDoubleSpeed;    /**< Double Speed */
        } tUart;

        struct
        {
            USART_MS_e           eMs;
            USART_DATA_e         eData;
            USART_PARITY_e       eParity;
            USART_STOP_e         eStop;
            USART_CLKPOL_e       eClkPol;
        } tUsrt;

        struct
        {
            USART_MS_e           eMs;
            USART_BIT_ORDER_e    eBitOrder;
            USART_CLKPOL_e       eClkPol;
            USART_CLKPHA_e       eClkPha;
            bool                 bSwapMSPort;     /**< Swap MOSI and MISO Port */
            bool                 bSSGenDisable;   /**< Disable SS pin auto control */
            bool                 bRxSCKGen;       /**< SCK generation when receive data */
            bool                 bSlvRecvDisable; /**< Disable Receiver when Slave mode */
        } tSpi;
    } tCfg;
    USART_RTO_t                  tRTO;
} USART_CFG_t;

/**
 * @brief USART IRQ handler context
 */
typedef struct
{
    USART_ID_e eId;       /**< SPI Instance Id */
    bool       bWakeup;   /**< Wake-up flag */
} USART_Context_t;

/**
 *******************************************************************************
 * @brief       USART Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::USART_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnUSART_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize USART.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USART_Init(USART_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize USART.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USART_Uninit(USART_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration USART.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : USART Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USART_SetConfig(USART_ID_e eId, USART_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ USART.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USART_SetIRQ(USART_ID_e eId, USART_OPS_e eOps, pfnUSART_IRQ_Handler_t pfnHandler,
                           void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Transmit Data USART.
 * @param[in]   eId : Instance Id.
 * @param[in]   *pun8Out : Transmit Data.
 * @param[in]   un32Len : Data Length.
 * @param[in]   bEnForcePoll : En-force polling Operation (Ignored IO Operation by SetIRQ).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USART_Transmit(USART_ID_e eId, uint8_t *pun8Out, uint32_t un32Len,
                             bool bEnForcePoll);

/**
 *******************************************************************************
 * @brief       Receive Data USART.
 * @param[in]   eId : Instance Id.
 * @param[in]   *pun8In : Receive Data.
 * @param[in]   un32Len : Data Length.
 * @param[in]   bEnForcePoll : En-force polling Operation (Ignored IO Operation by SetIRQ).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USART_Receive(USART_ID_e eId, uint8_t *pun8In, uint32_t un32Len,
                            bool bEnForcePoll);

/**
 *******************************************************************************
 * @brief       Abort Transmission or Reception USART.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USART_Abort(USART_ID_e eId);

/**
 *******************************************************************************
 * @brief       Abort Reception USART.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USART_AbortRx(USART_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Wake-up source USART.
 * @param[in]   eId : Instance Id.
 * @param[in]   bEnable : Enable Wake-up source.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USART_SetWakeupSrc(USART_ID_e eId, bool bEnable);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_USART_H_ */

/** @} */
/** @} */
