/**
 *******************************************************************************
 * @file        spi_type.h
 * @author      ABOV R&D Division
 * @brief       Serial Peripheral Interface (Common)
 *
 * Copyright 2026 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/**
 * @addtogroup  TYPE TYPE (Common type)
 * @{
 * @defgroup    TYPE_SPI SPI
 * @{
 * @brief       Serial Peripheral Interface (SPI)
 */

#ifndef _SPI_TYPE_H_
#define _SPI_TYPE_H_

#ifdef __cplusplus
extern "C"
{
#endif

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

#ifdef __cplusplus
}
#endif

#endif /* _SPI_TYPE_H_ */

/** @} */
/** @} */
