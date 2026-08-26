/**
 *******************************************************************************
 * @file        crc_type.h
 * @author      ABOV R&D Division
 * @brief       Cyclic Redundancy Check (Common)
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
 * @defgroup    TYPE_CRC CRC
 * @{
 * @brief       Cyclic Redundancy Check
 */

#ifndef _CRC_TYPE_H_
#define _CRC_TYPE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief CRC Instance Id
 */
typedef enum
{
    CRC_ID_0,
    CRC_ID_1,
    CRC_ID_2,
    CRC_ID_3,
    CRC_ID_4,
    CRC_ID_5,
    CRC_ID_6,
    CRC_ID_7,
    CRC_ID_8,
    CRC_ID_9,
    CRC_ID_MAX
} CRC_ID_e;

/**
 * @brief CRC Mode
 */
typedef enum
{
    CRC_MODE_CRC,
    CRC_MODE_CHKSUM,
    CRC_MODE_MAX
} CRC_MODE_e;

/**
 * @brief CRC Polynomial Type
 */
typedef enum
{
    CRC_POLY_32,          /**< CRC-32 */
    CRC_POLY_16,          /**< CRC-16 */
    CRC_POLY_8,           /**< CRC-8 */
    CRC_POLY_7,           /**< CRC-7 */
    CRC_POLY_16_CCITT,    /**< CRC-16 CCITT */
    CRC_POLY_MAX
} CRC_POLY_e;

/**
 * @brief CRC First-In Bit.
 */
typedef enum
{
    CRC_INP_LSB,     /**< LSB First-In */
    CRC_INP_MSB,     /**< MSB First-In */
    CRC_INP_MAX
} CRC_INP_e;

/**
 * @brief CRC First-Out Bit.
 */
typedef enum
{
    CRC_OUTP_LSB,    /**< LSB First-Out */
    CRC_OUTP_MSB,    /**< MSB First-Out */
    CRC_OUTP_MAX
} CRC_OUTP_e;

/**
 * @brief CRC Output Bit Inversion
 */
typedef enum
{
    CRC_OUTP_INV_OFF,
    CRC_OUTP_INV_ON,
    CRC_OUTP_INV_MAX
} CRC_OUTP_INV_e;

/**
 * @brief CRC Input Data size
 */
typedef enum
{
    CRC_INP_DATA_32,
    CRC_INP_DATA_16,
    CRC_INP_DATA_8,
    CRC_INP_DATA_MAX
} CRC_INP_DATA_e;

/**
 * @brief CRC Operation
 */
typedef enum
{
    CRC_OPS_POLL,        /**< Operation Polling */
    CRC_OPS_INTR_DMA,    /**< Operation Interrupt with DMA */
    CRC_OPS_NMI_DMA,     /**< Operation NMI with DMA */
    CRC_OPS_MAX
} CRC_OPS_e;

#ifdef __cplusplus
}
#endif

#endif /* _CRC_TYPE_H_ */

/** @} */
/** @} */
