/**
 *******************************************************************************
 * @file        i2c_type.h
 * @author      ABOV R&D Division
 * @brief       Inter-Integrated Circuit (Common)
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
 * @defgroup    TYPE_I2C I2C
 * @{
 * @brief       Inter-Integrated Circuit (I2C)
 */

#ifndef _I2C_TYPE_H_
#define _I2C_TYPE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief I2C Instance Id
 */
typedef enum
{
    I2C_ID_0,
    I2C_ID_1,
    I2C_ID_2,
    I2C_ID_3,
    I2C_ID_4,
    I2C_ID_5,
    I2C_ID_6,
    I2C_ID_7,
    I2C_ID_8,
    I2C_ID_9,
    I2C_ID_MAX
} I2C_ID_e;

/**
 * @brief I2C Mode
 */
typedef enum
{
    I2C_MODE_MASTER,    /**< Master */
    I2C_MODE_SLAVE,     /**< Slave */
    I2C_MODE_MAX
} I2C_MODE_e;

/**
 * @brief I2C Event
 */
typedef enum
{
    I2C_EVENT_TX_DONE            = BIT(0),    /**< Transmit complete */
    I2C_EVENT_RX_DONE            = BIT(1),    /**< Receive complete */
    I2C_EVENT_MASTERSHIP_LOSS    = BIT(2),    /**< Mastership lose */
    I2C_EVENT_RX_NO_ACK          = BIT(3),    /**< Receive No Ack */
    I2C_EVENT_SCL_LOW_TIMEOUT    = BIT(4),    /**< SCL low timeout */
    I2C_EVENT_MAX
} I2C_EVENT_e;

/**
 * @brief I2C Operation
 */
typedef enum
{
    I2C_OPS_POLL,        /**< Operation Polling */
    I2C_OPS_INTR,        /**< Operation Interrupt */
    I2C_OPS_INTR_DMA,    /**< Operation Interrupt with DMA */
    I2C_OPS_NMI,         /**< Operation NMI */
    I2C_OPS_NMI_DMA,     /**< Operation NMI with DMA */
    I2C_OPS_MAX
} I2C_OPS_e;

#ifdef __cplusplus
}
#endif

#endif /* _I2C_TYPE_H_ */

/** @} */
/** @} */
