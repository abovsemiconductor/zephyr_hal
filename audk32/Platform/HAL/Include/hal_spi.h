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

/**
 * @brief SPI Instance Id
 */
typedef enum
{
    SPI_ID_0,
    SPI_ID_1,
    SPI_ID_2,
    SPI_ID_3,
    SPI_ID_4,
    SPI_ID_5,
    SPI_ID_6,
    SPI_ID_7,
    SPI_ID_8,
    SPI_ID_9,
    SPI_ID_10,
    SPI_ID_11,
    SPI_ID_MAX
} SPI_ID_e;

/**
 * @brief SPI Mode
 */
typedef enum
{
    SPI_MODE_SLAVE,     /**< Slave */
    SPI_MODE_MASTER,    /**< Master */
    SPI_MODE_MAX,                  
} SPI_MODE_e;

/**
 * @brief SPI Data Bit
 */
typedef enum
{
    SPI_DATA_8,     /**< 8bit mode */
    SPI_DATA_9,     /**< 9bit mode */
    SPI_DATA_16,    /**< 16bit mode */
    SPI_DATA_17,    /**< 17bit mode */
    SPI_DATA_MAX
} SPI_DATA_e;

/**
 * @brief SPI Order Bit
 */
typedef enum
{
    SPI_BIT_ORDER_LSB,    /**< LSB First */
    SPI_BIT_ORDER_MSB,    /**< MSB First */
    SPI_BIT_ORDER_MAX
} SPI_BIT_ORDER_e;

/**
 * @brief SPI Clock Polarity and Phase Mode
 */
typedef enum
{
    SPI_CLK_MODE_CPOL_0_CPHA_0,    /**< Polarity 0, Phase 0 */
    SPI_CLK_MODE_CPOL_0_CPHA_1,    /**< Polarity 0, Phase 1 */
    SPI_CLK_MODE_CPOL_1_CPHA_0,    /**< Polarity 1, Phase 0 */
    SPI_CLK_MODE_CPOL_1_CPHA_1,    /**< Polarity 1, Phase 1 */
    SPI_CLK_MODE_MAX
} SPI_CLK_MODE_e;

/**
 * @brief SPI Slave Selection Polarity
 */
typedef enum
{
    SPI_SS_POL_LOW,     /**< Polarity Low */
    SPI_SS_POL_HIGH,    /**< Polarity High */
    SPI_SS_POL_MAX
} SPI_SS_POL_e;

/**
 * @brief SPI Event
 */
typedef enum
{
    SPI_EVENT_TX_DONE     = BIT(0),    /**< Transmit completed */
    SPI_EVENT_RX_DONE     = BIT(1),    /**< Receive completed */
    SPI_EVENT_OVERRUN     = BIT(2),    /**< Overrun occurred */
    SPI_EVENT_UNDERRUN    = BIT(3),    /**< Underrun occurred */
    SPI_EVENT_MAX
} SPI_EVENT_e;

/**
 * @brief SPI Operation
 */
typedef enum
{
    SPI_OPS_POLL,        /**< Operation Polling */
    SPI_OPS_INTR,        /**< Operation Interrupt */
    SPI_OPS_INTR_DMA,    /**< Operation Interrupt with DMA */
    SPI_OPS_NMI,         /**< Operation NMI */
    SPI_OPS_NMI_DMA,     /**< Operation NMI with DMA */
    SPI_OPS_MAX
} SPI_OPS_e;

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

