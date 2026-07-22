/**
 *******************************************************************************
 * @file        hal_aes.h
 * @author      ABOV R&D Division
 * @brief       Advanced Encryption Standard (AES)
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
 * @defgroup    HAL_AES AES
 * @{
 * @brief       Advanced Encryption Standard (AES)
 */

#ifndef _HAL_AES_H_
#define _HAL_AES_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief AES Instance Id
 */
typedef enum
{
    AES_ID_0,
    AES_ID_1,
    AES_ID_2,
    AES_ID_3,
    AES_ID_4,
    AES_ID_5,
    AES_ID_6,
    AES_ID_7,
    AES_ID_8,
    AES_ID_9,
    AES_ID_MAX
} AES_ID_e;

/**
 * @brief AES Chain Mode
 */
typedef enum
{
    AES_CHAIN_MODE_ECB,
    AES_CHAIN_MODE_CBC,
    AES_CHAIN_MODE_CTR,
    AES_CHAIN_MODE_MAX
} AES_CHAIN_MODE_e;

/**
 * @brief AES Cipher Mode
 */
typedef enum
{
    AES_CIPHER_MODE_ENC,    /**<* Encryption */
    AES_CIPHER_MODE_DEC,    /**<* Decryption */
    AES_CIPHER_MODE_MAX
} AES_CIPHER_MODE_e;

/**
 * @brief Alignment Mode (Text in/Out)
 */
typedef enum
{
    AES_ALIGN_MODE_WORD,                                   /**< No Swap */
    AES_ALIGN_MODE_NONE = AES_ALIGN_MODE_WORD,             /**< No Swap */
    AES_ALIGN_MODE_WORD_INV,                               /**< Swap Word */
    AES_ALIGN_MODE_HALF_WORD = AES_ALIGN_MODE_WORD_INV,    /**< Swap Half Word */
    AES_ALIGN_MODE_BYTE_INV_WORD,                          /**< Swap Byte in Word */
    AES_ALIGN_MODE_BYTE = AES_ALIGN_MODE_BYTE_INV_WORD,    /**< Swap Byte */
    AES_ALIGN_MODE_BYTE_INV,                               /**< Swap Byte Inv */
    AES_ALIGN_MODE_BIT = AES_ALIGN_MODE_BYTE_INV,          /**< Swap Bit */
    AES_ALIGN_MODE_MAX
} AES_ALIGN_MODE_e;

/**
 * @brief AES Interrupt
 */
typedef enum
{
    AES_INTR_NONE     = 0,
    AES_INTR_ENC_DONE = BIT(0),    /**< Complete Encryption */
    AES_INTR_DEC_DONE = BIT(1),    /**< Complete Decryption */
    AES_INTR_MAX
} AES_INTR_e;

/**
 * @brief AES Event
 */
typedef enum
{
    AES_EVENT_ENC_DONE = BIT(0),    /**< Complete Encryption Event */
    AES_EVENT_DEC_DONE = BIT(1),    /**< Complete Decryption Event */
    AES_EVENT_MAX
} AES_EVENT_e;

/**
 * @brief AES Operation
 */
typedef enum
{
    AES_OPS_POLL,       /**< Operation Polling */
    AES_OPS_INTR,       /**< Operation Interrupt */
    AES_OPS_INTR_DMA,   /**< Operation Interrupt DMA */
    AES_OPS_NMI,        /**< Operation NMI */
    AES_OPS_MAX
} AES_OPS_e;

/**
 * @brief AES Mode Configuration
 */
typedef struct
{
    AES_CHAIN_MODE_e     eChainMode;
    AES_CIPHER_MODE_e    eCipherMode;

    AES_ALIGN_MODE_e     eTextInAlign;     /**< In Align(Swap) */
    AES_ALIGN_MODE_e     eTextOutAlign;    /**< Out Align(Swap) */

    uint8_t              un8IntrEnable;    /**< Interrupt Enable ::AES_INTR_e (Bit Order) */
} AES_CFG_t;

/**
 * @brief AES Data
 */
typedef struct
{
    uint8_t     un8Num;       /**< Data Index */
    uint32_t    un32Data;    /**< 32bit Data */ 
} AES_DATA_t;

/**
 *******************************************************************************
 * @brief       AES Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::AES_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnAES_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize AES.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_AES_Init(AES_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize AES.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_AES_Uninit(AES_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration AES.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : AES Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_AES_SetConfig(AES_ID_e eId, AES_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ AES.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_AES_SetIRQ(AES_ID_e eId, AES_OPS_e eOps, pfnAES_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Set key data AES.
 * @param[in]   eId : Instance Id.
 * @param[in]   *pun32Key : Key data.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_AES_SetKey(AES_ID_e eId, uint32_t *pun32Key);

/**
 *******************************************************************************
 * @brief       Set Initial Vector key data AES.
 * @param[in]   eId : Instance Id.
 * @param[in]   *pun32Key : Key data.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_AES_SetIVKey(AES_ID_e eId, uint32_t *pun32Key);

/**
 *******************************************************************************
 * @brief       Set computation AES.
 * @param[in]   eId : Instance Id.
 * @param[in]   *pun32Data : Data Address.
 * @param[in]   un32Len : Data Length.
 * @param[out]  *pun32Out : Result of computation AES.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_AES_SetCompute(AES_ID_e eId, uint32_t *pun32Data, uint32_t un32Len, uint32_t *pun32Out);

/**
 *******************************************************************************
 * @brief       Get Result of computation AES.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun32Out : Result of computation AES.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_AES_GetResult(AES_ID_e eId, uint32_t *pun32Out);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_AES_H_ */

/** @} */
/** @} */
