/**
 *******************************************************************************
 * @file        hal_crc.h
 * @author      ABOV R&D Division
 * @brief       Cyclic Redundancy Check
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
 * @defgroup    HAL_CRC CRC
 * @{
 * @brief       Cyclic Redundancy Check
 */

#ifndef _HAL_CRC_H_
#define _HAL_CRC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

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
    CRC_OPS_NMI_DMA,    /**< Operation NMI with DMA */
    CRC_OPS_MAX
} CRC_OPS_e;

/**
 * @brief CRC Output Configuration 
 */
typedef struct
{
    CRC_OUTP_e        eFirstOut;
    CRC_OUTP_INV_e    eInv;
} CRC_OUTPUT_CFG_t;

/**
 * @brief CRC Input Configuration 
 */
typedef struct
{
    bool              bComplement;
    CRC_INP_DATA_e    eInDataSize;
} CRC_INPUT_CFG_t;

/**
 * @brief CRC Mode Configuration
 */
typedef struct
{
    CRC_MODE_e          eMode;
    CRC_POLY_e          ePoly;
    CRC_INP_e           eFirstIn;
    bool                bIntrEnable;
    CRC_OUTPUT_CFG_t    tOutputCfg;
    CRC_INPUT_CFG_t     tInputCfg;
} CRC_CFG_t;

/**
 *******************************************************************************
 * @brief       CRC Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type (NONE).
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnCRC_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize CRC.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CRC_Init(CRC_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize CRC.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CRC_Uninit(CRC_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration CRC.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : CRC Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CRC_SetConfig(CRC_ID_e eId, CRC_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ CRC.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CRC_SetIRQ(CRC_ID_e eId, CRC_OPS_e eOps, pfnCRC_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio);
/**
 *******************************************************************************
 * @brief       Set computation CRC.
 * @param[in]   un32Init : Initial Value.
 * @param[in]   *pun8Data : Data Address.
 * @param[in]   un32Len : Data Length.
 * @param[out]  *pun32Out : Result of computation CRC.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CRC_SetCompute(CRC_ID_e eId, uint32_t un32Init, uint8_t *pun8Data, uint32_t un32Len, uint32_t *pun32Out);

/**
 *******************************************************************************
 * @brief       Get Result of computation CRC.
 * @param[out]  *pun32Out : Result of computation CRC.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CRC_GetResult(CRC_ID_e eId, uint32_t *pun32Out);

/**
 *******************************************************************************
 * @brief       Set waiting to complete convertion CRC.
 * @param[in]   eId : Instance Id.
 * @param[in]   un32Timeout : Timeout of waiting of computation CRC.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CRC_SetWaitComplete(CRC_ID_e eId, uint32_t un32Timeout);

/**
 *******************************************************************************
 * @brief       Set Interrupt Clear with DMA CRC.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CRC_SetIRQClear(CRC_ID_e eId);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_CRC_H_ */

/** @} */
/** @} */
