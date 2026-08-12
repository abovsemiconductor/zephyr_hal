/**
 *******************************************************************************
 * @file        hal_pga.h
 * @author      ABOV R&D Division
 * @brief       Programmable Gain Amplifier (PGA)
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
 * @defgroup    HAL_PGA PGA
 * @{
 * @brief       Programmable Gain Amplifier (PGA) 
 */

#ifndef _HAL_PGA_H_
#define _HAL_PGA_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief PGA Instance Id
 */
typedef enum
{
    PGA_ID_0,
    PGA_ID_1,
    PGA_ID_2,
    PGA_ID_3,
    PGA_ID_4,
    PGA_ID_5,
    PGA_ID_6,
    PGA_ID_7,
    PGA_ID_8,
    PGA_ID_9,
    PGA_ID_MAX
} PGA_ID_e;

/**
 * @brief PGA Output Driving Current
 */
typedef enum
{
    PGA_OUT_CURR_0,    /**< Output Driving Current 0 */
    PGA_OUT_CURR_1,    /**< Output Driving Current 1 */
    PGA_OUT_CURR_2,    /**< Output Driving Current 2 */
    PGA_OUT_CURR_3,    /**< Output Driving Current 3 */
    PGA_OUT_CURR_MAX
} PGA_OUT_CURR_e;

/**
 * @brief PGA Gain Selection
 */
typedef enum
{
    PGA_GAIN_0,    /**< Lowest Gain */
    PGA_GAIN_1,
    PGA_GAIN_2,
    PGA_GAIN_3,
    PGA_GAIN_4,
    PGA_GAIN_5,
    PGA_GAIN_6,
    PGA_GAIN_7,
    PGA_GAIN_8,
    PGA_GAIN_9,
    PGA_GAIN_10,
    PGA_GAIN_11,
    PGA_GAIN_12,
    PGA_GAIN_13,
    PGA_GAIN_14,
    PGA_GAIN_15,
    PGA_GAIN_16,
    PGA_GAIN_17,
    PGA_GAIN_18,    /**< Highest Gain */
    PGA_GAIN_MAX
} PGA_GAIN_e;

/**
 *******************************************************************************
 * @brief       Initialize PGA.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PGA_Init(PGA_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize PGA.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PGA_Uninit(PGA_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Amplifier PGA.
 * @param[in]   eId : Instance Id.
 * @param[in]   eGain : Gain selection.
 * @param[in]   bEnable : Enable PGA (AMP) 
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PGA_SetAmp(PGA_ID_e eId, PGA_OUT_CURR_e eCurr, bool bEnable);

/**
 *******************************************************************************
 * @brief       Set Gain PGA.
 * @param[in]   eId : Instance Id.
 * @param[in]   eGain : Gain selection.
 * @param[in]   bFollow : Enable Voltage Follow (true : Follow Mode, false : Gain Mode)
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PGA_SetGain(PGA_ID_e eId, PGA_GAIN_e eGain, bool bFollow);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_PGA_H_ */

/** @} */
/** @} */
