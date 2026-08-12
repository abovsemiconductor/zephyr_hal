/**
 *******************************************************************************
 * @file        hpl_nmi.h
 * @author      ABOV R&D Division
 * @brief       Non-maskable Interrupt
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
 * @defgroup    HPL_NMI NMI
 * @{
 * @brief       Non-maskable Interrupt 
 */

#ifndef _HPL_NMI_H_
#define _HPL_NMI_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief NMI Non-maskable Interrupt Source
 */
typedef enum
{
    NMI_INTR_LVD,
    NMI_INTR_MCLK,
    NMI_INTR_WDT,
    NMI_INTR_OVP0,
    NMI_INTR_TIMER3_BLNK = NMI_INTR_OVP0,
    NMI_INTR_PROT0,
    NMI_INTR_CMP = NMI_INTR_PROT0,
    NMI_INTR_OVP1,
    NMI_INTR_FLASH_SWAP = NMI_INTR_OVP1,
    NMI_INTR_PROT1,
    NMI_INTR_SOURCE,
    NMI_INTR_MAX
} NMI_INTR_e;

/**
 *******************************************************************************
 * @brief       NMI Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type (always 0x1).
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnNMI_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Set IRQ NMI.
 * @param[in]   eNmi : Non-maskable Interrupt Source.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   bEnable : Enable NMI.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HPL_NMI_SetIRQ(NMI_INTR_e eNmi, pfnNMI_IRQ_Handler_t pfnHandler, void *pContext, bool bEnable);

/**
 *******************************************************************************
 * @brief       Set Enable NMI.
 * @param[in]   eNmi : Non-maskable Interrupt Source.
 * @param[in]   bEnable : Enable NMI.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HPL_NMI_SetEnable(NMI_INTR_e eNmi, bool bEnable);

/**
 *******************************************************************************
 * @brief       Set NMI Source NMI.
 * @param[in]   un32Irq : IRQ Number.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   bEnable : Enable NMI Source.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HPL_NMI_SetSource(IRQn_Type eIrq, pfnNMI_IRQ_Handler_t pfnHandler, 
                            void *pContext, bool bEnable);

#ifdef __cplusplus
}
#endif

#endif /* _HPL_NMI_H_ */

/** @} */
/** @} */

