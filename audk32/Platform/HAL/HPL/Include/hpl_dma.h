/**
 *******************************************************************************
 * @file        hpl_dma.h
 * @author      ABOV R&D Division
 * @brief       Direct Memory Access
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
 * @addtogroup  HPL HPL (Hardware Private Layer)
 * @{
 * @brief       HPL (Hardware Private Layer) works as adaptation between HAL and device specfic driver.
 * @defgroup    HPL_DMA DMA
 * @{
 * @brief       Direct Memory Access
 */

#ifndef _HPL_DMA_H_
#define _HPL_DMA_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief DMA Instance Id
 */
typedef enum
{
    DMA_ID_0,
    DMA_ID_1,
    DMA_ID_2,
    DMA_ID_3,
    DMA_ID_4,
    DMA_ID_5,
    DMA_ID_6,
    DMA_ID_7,
    DMA_ID_8,
    DMA_ID_9,
    DMA_ID_10,
    DMA_ID_11,
    DMA_ID_12,
    DMA_ID_13,
    DMA_ID_14,
    DMA_ID_15,
    DMA_ID_MAX
} DMA_ID_e;

/**
 * @brief DMA Peripheral Id
 */
typedef enum
{
    DMA_PERI_IDLE,
    DMA_PERI_UART,
    DMA_PERI_USART,
    DMA_PERI_SPI,
    DMA_PERI_CRC,
    DMA_PERI_ADC,
    DMA_PERI_DAC,
    DMA_PERI_AES,
    DMA_PERI_I2C,
    DMA_PERI_LPUART,
    DMA_PERI_MAX
} DMA_PERI_e;

/**
 * @brief DMA Peripheral Channel Id
 */
typedef enum
{
    DMA_PERI_ID_0,
    DMA_PERI_ID_1,
    DMA_PERI_ID_2,
    DMA_PERI_ID_3,
    DMA_PERI_ID_4,
    DMA_PERI_ID_5,
    DMA_PERI_ID_6,
    DMA_PERI_ID_7,
    DMA_PERI_ID_8,
    DMA_PERI_ID_9,
    DMA_PERI_ID_10,
    DMA_PERI_ID_11,
    DMA_PERI_ID_12,
    DMA_PERI_ID_MAX
} DMA_PERI_ID_e;

/**
 * @brief DMA Peripheral Transfer Mode 
 */
typedef enum
{
    DMA_PERI_COM_RX,    /**< Peripheral Reception */ 
    DMA_PERI_COM_TX,    /**< Peripheral Transmission */
    DMA_PERI_COM_MAX
} DMA_PERI_COM_e;

/**
 * @brief DMA Source/Destination Transfer Width
 */
typedef enum
{
    DMA_BUS_SIZE_BYTE        = (0UL),    /**< size = 1 byte */
    DMA_BUS_SIZE_HALFWORD    = (1UL),    /**< size = 2 bytes */
    DMA_BUS_SIZE_WORD        = (2UL),    /**< size = 4 bytes */
} DMA_BUS_SIZE_e;

/**
 * @brief DMA Direction Mode
 */
typedef enum
{
    DMA_DIR_MEM_TO_PERI,    /**< Memory to Peripheral */
    DMA_DIR_PERI_TO_MEM,    /**< Peripheral to Memory */
} DMA_DIR_e;

/**
 * @brief DMA Event
 */
typedef enum
{
    DMA_EVENT_DONE,    /**< Generation completed */
    DMA_EVENT_ERROR,   /**< Generation error */
} DMA_EVENT_e;

/**
 * @brief DMA Mode Configuration
 */
typedef struct
{
    DMA_PERI_e        ePeri;
    DMA_PERI_ID_e     ePeriId;
    uint32_t          un32PeriNum;    /**< Peripheral Id (see: UserManual DMAC Table) */
    DMA_BUS_SIZE_e    eSize;          /**< Bus Size */
    DMA_DIR_e         eDir;           /**< Direction */
} DMA_CFG_t;

/**
 *******************************************************************************
 * @brief       DMA Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnDMA_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize DMA.
 * @param[in]   ePeri : Peripheral Id.
 * @param[in]   un8ChNum : Peripheral Channel Number.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HPL_DMA_Init(DMA_PERI_e ePeri, uint8_t un8ChNum);

/**
 *******************************************************************************
 * @brief       Uninitialize DMA.
 * @param[in]   ePeri : Peripheral Id.
 * @param[in]   un8ChNum : Peripheral Channel Number.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HPL_DMA_Uninit(DMA_PERI_e ePeri, uint8_t un8ChNum);

/**
 *******************************************************************************
 * @brief       Set IRQ DMA.
 * @param[in]   eNmi : Non-maskable Interrupt Source.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   bEnable : Enable NMI.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HPL_DMA_SetIRQ(DMA_PERI_e ePeri, pfnDMA_IRQ_Handler_t pfnHandler, void *pContext, bool bEnable);

/**
 *******************************************************************************
 * @brief       Get Available Channel DMA.
 * @param[in]   eId : DMA Channel Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HPL_DMA_GetAvailChannel(DMA_ID_e *peId);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration DMA.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : DMA Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HPL_DMA_SetConfig(DMA_ID_e eId, DMA_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set DMA Channel Clear.
 * @param[in]   eId : DMA Channel Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HPL_DMA_SetClear(DMA_ID_e eId);

/**
 *******************************************************************************
 * @brief       Start DMA.
 * @param[in]   eId : DMA Channel Id.
 * @param[in]   un32Src : Source Address for the DMA Transfer.
 * @param[in]   un32Dst : Destination Address for the DMA Transfer.
 * @param[in]   un32Len : Length of the DMA Transfer, should be less than 0xFFF.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HPL_DMA_Start(DMA_ID_e eId, uint32_t un32Src, uint32_t un32Dst, uint32_t un32Len);

/**
 *******************************************************************************
 * @brief       Stop DMA.
 * @param[in]   eId DMA Channel Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HPL_DMA_Stop(DMA_ID_e eId);

/**
 *******************************************************************************
 * @brief       Get complete DMA.
 * @param[in]   eId DMA Channel Id.
 * @param[out]  *pbComplete : true (Complete) / false (Incomplete).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HPL_DMA_GetComplete(DMA_ID_e eId, bool *pbComplete);

/**
 *******************************************************************************
 * @brief       Get Peripheral Selection Number DMA.
 * @param[in]   eId : DMA Channel Id.
 * @param[in]   ePeriId : Peripherial Id.
 * @param[in]   eCom : Peripheral Transfer Mode (Rx or Tx).
 * @param[out]  *pun32SelNum : Peripheral Selection Number.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HPL_DMA_GetPeriSelectNumber(DMA_PERI_e ePeri, DMA_PERI_ID_e ePeriId, DMA_PERI_COM_e eCom, uint32_t *pun32SelNum);

/**
 *******************************************************************************
 * @brief       Set waiting to complete convertion DMA.
 * @param[in]   eId : Instance Id.
 * @param[in]   un32Timeout : Timeout of waiting of completed transfer DMA.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HPL_DMA_SetWaitComplete(DMA_ID_e eId, uint32_t un32Timeout);

#ifdef __cplusplus
}
#endif

#endif /* _HPL_DMA_H_ */

/** @} */
/** @} */


