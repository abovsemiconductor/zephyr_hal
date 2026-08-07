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
#include "type/usart_type.h"

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
