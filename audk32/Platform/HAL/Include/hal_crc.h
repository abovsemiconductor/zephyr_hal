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
#include "type/crc_type.h"

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
