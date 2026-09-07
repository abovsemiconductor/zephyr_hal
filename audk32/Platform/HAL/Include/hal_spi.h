/**
 *******************************************************************************
 * @file        hal_spi.h
 * @author      ABOV R&D Division
 * @brief       SPI communication
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
 * @defgroup    HAL_SPI SPI
 * @{
 * @brief       Serial Peripheral Interface (SPI)
 */

#ifndef _HAL_SPI_H_
#define _HAL_SPI_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"
#include "type/spi_type.h"

/**
 * @brief SPI Mode configuration
 */
typedef struct
{
    SPI_MODE_e            eMode;
    SPI_DATA_e            eData;
    SPI_CLK_MODE_e        eClkMode;
    SPI_BIT_ORDER_e       eBitOrder;
    SPI_SS_POL_e          eSSPol;
    bool                  bSSManual;
    uint16_t              un16BaudRate; 
    uint8_t               un8DelayStart;    /**< Sart Delay Length (Minimum 1) */
    uint8_t               un8DelayStop;     /**< Stop Delay Length (Minimum 1) */
    uint8_t               un8DelayBurst;    /**< Burst Delay Length (Minimum 1) */
} SPI_CFG_t;

/**
 * @brief SPI IRQ handler context
 */
typedef struct
{
    SPI_ID_e eId;    /**< SPI Instance Id */
} SPI_Context_t;

/**
 *******************************************************************************
 * @brief       SPI Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::SPI_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnSPI_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize SPI.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SPI_Init(SPI_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize SPI.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SPI_Uninit(SPI_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration SPI.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : SPI Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SPI_SetConfig(SPI_ID_e eId, SPI_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ SPI.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SPI_SetIRQ(SPI_ID_e eId, SPI_OPS_e eOps, pfnSPI_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Transmit Data SPI.
 * @param[in]   eId : Instance Id.
 * @param[in]   *pun8Out : Transmit Data.
 * @param[in]   un32Len : Data Length.
 * @param[in]   bEnForcePoll : En-force polling Operation (Ignored IO Operation by SetIRQ).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SPI_Transmit(SPI_ID_e eId, uint8_t *pun8Out, uint32_t un32Len, bool bEnForcePoll);

/**
 *******************************************************************************
 * @brief       Receive Data SPI.
 * @param[in]   eId : Instance Id.
 * @param[in]   *pun8In : Receive Data.
 * @param[in]   un32Len : Data Length.
 * @param[in]   bEnForcePoll : En-force polling Operation (Ignored IO Operation by SetIRQ).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SPI_Receive(SPI_ID_e eId, uint8_t *pun8In, uint32_t un32Len, bool bEnForcePoll);

/**
 *******************************************************************************
 * @brief       Exchange MOSIn/MISOn Pin SPI.
 * @param[in]   eId : Instance Id.
 * @param[in]   bSwap : true (Swap) / false (Non-Swap)
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SPI_SetSwapPort(SPI_ID_e eId, bool bSwap);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_SPI_H_ */

/** @} */
/** @} */

