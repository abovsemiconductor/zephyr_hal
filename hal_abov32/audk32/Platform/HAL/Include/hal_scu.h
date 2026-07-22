/**
 *******************************************************************************
 * @file        hal_scu.h
 * @author      ABOV R&D Division
 * @brief       System Control Unit
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
 * @defgroup    HAL_SCU SCU
 * @{
 * @brief       Core sub system in System Control Unit (SCU)
 */

#ifndef _HAL_SCU_H_
#define _HAL_SCU_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/*
 * @brief SCU Reset Source
 */
typedef enum
{
    SCU_RST_SW,            /**< Software Reset */
    SCU_RST_CPU,           /**< CPU Request Reset */
    SCU_RST_CPU_LOCKUP,    /**< CPU Lock-up Reset */
    SCU_RST_EXT_PIN,       /**< External Pin Reset */
    SCU_RST_POR,           /**< Power-on Reset */
    SCU_RST_MAX
} SCU_RST_e;

/**
 *******************************************************************************
 * @brief       Set Software Reset SCU.
 * @return      void : None
 ******************************************************************************/
void HAL_SCU_SetSWReset(void);

/**
 *******************************************************************************
 * @brief       Set Reset Source SCU.
 * @param[in]   eRst : Reset Source.
 * @param[in]   bEnable : Enable Reset Source.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_SetReset(SCU_RST_e eRst, bool bEnable);

/**
 *******************************************************************************
 * @brief       Get Reset Source Event SCU.
 * @param[in]   eRst : Reset Source.
 * @param[out]  *pbEvent : Reset Source Event.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_GetResetEvent(SCU_RST_e eRst, bool *pbEvent);

/**
 *******************************************************************************
 * @brief       Get Boot Pin Level SCU.
 *              some of ABOV chipsets are only supported.
 * @param[out]  *pbLevel : Boot Pin Level (true = High, false = Low).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_GetBootPinLevel(bool *pbLevel);

/**
 *******************************************************************************
 * @brief       Set Reset Pin Debounce SCU.
 *              some of ABOV chipsets are only supported.
 * @param[in]   un8Count : Clock Count for Reset Pin Debounce.
 * @param[in]   bEnable : Enable Reset Pin Debounce.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_SetResetPinDebounce(uint8_t un8Count, bool bEnable);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_SCU_H_ */

/** @} */
/** @} */
