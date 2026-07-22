/**
 *******************************************************************************
 * @file        hal_ebi.h
 * @author      ABOV R&D Division
 * @brief       EBI Driver
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
 * @defgroup    HAL_EBI EBI
 * @{
 * @brief       External Bus Interface (Static Memory Controller)
 */

#ifndef _HAL_EBI_H_
#define _HAL_EBI_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief EBI Instance Id
 */
typedef enum
{
    EBI_ID_0,
    EBI_ID_1,
    EBI_ID_2,
    EBI_ID_3,
    EBI_ID_4,
    EBI_ID_5,
    EBI_ID_6,
    EBI_ID_7,
    EBI_ID_8,
    EBI_ID_9,
    EBI_ID_MAX
} EBI_ID_e;

/**
 * @brief EBI Memory Bus Width Size
 */
typedef enum
{
    EBI_BUS_WIDTH_8BIT,
    EBI_BUS_WIDTH_16BIT,
    EBI_BUS_WIDTH_MAX
} EBI_BUS_WIDTH_e;

/**
 * @brief EBI Addressing Clock Cycle (AH + 1) HCLK Cycle
 */
typedef enum
{
    EBI_CLK_CYCLE_1,
    EBI_CLK_CYCLE_2,
    EBI_CLK_CYCLE_3,
    EBI_CLK_CYCLE_4,
    EBI_CLK_CYCLE_MAX
} EBI_CLK_CYCLE_e;

/**
 * @brief EBI Byte Lane
 */
typedef enum
{
    EBI_BLEN_DISABLE,
    EBI_BLEN_ENABLE,
    EBI_BLEN_MAX
} EBI_BYTE_LANE_SEL_e;

/**
 * @brief EBI Byte Lane Mode
 */
typedef enum
{
    EBI_ADDRESS_SEPARATED,    /**< Separated Address/Data Access */
    EBI_ADDRESS_MUXED,        /**< Muxed Address/Data Access */
    EBI_ADDRESS_MAX
} EBI_ADDRESS_TYPE_e;

/**
 * @brief EBI nWAIT Polarity
 */
typedef enum
{
    EBI_POLARITY_ACTIVE_LOW,
    EBI_POLARITY_ACTIVE_HIGH,
    EBI_POLATIRY_MAX
} EBI_POLARITY_e;

/**
 * @brief EBI Changing Falling Time of RD/nUWR/nLWR
 */
typedef enum
{
    EBI_EXTEND_CYCLE_NONE,
    EBI_EXTEND_CYCLE_1,
    EBI_EXTEND_CYCLE_2,
    EBI_EXTEND_CYCLE_3,
    EBI_EXTEND_CYCLE_MAX
} EBI_EXTEND_CYCLE_e;

/**
 * @brief EBI Insert Idle Cycle at Memory Access Time
 */
typedef enum
{
    EBI_IDLE_CYCLE_NONE,
    EBI_IDLE_CYCLE_1,
    EBI_IDLE_CYCLE_2,
    EBI_IDLE_CYCLE_3,
    EBI_IDLE_CYCLE_MAX
} EBI_IDLE_CYCLE_e;

/**
 * @brief EBI External Input nWait Configuration
 */
typedef struct
{
    bool              bEnable;
    EBI_POLARITY_e    eWaitPolarity;    /**< External nWait Polarity */
} EBI_EXT_REQ_t;

/**
 * @brief EBI  Extend Cycle Configuration
 */
typedef struct
{
    EBI_EXTEND_CYCLE_e    eFallCycle;    /**< Changing Falling Timing */
    EBI_IDLE_CYCLE_e      eIdleCycle;    /**< Insert IDLE Cycle at Memory Access Time */
} EBI_EXT_CYCLE_t;

/**
 * @brief EBI Mode Configuration
 */
typedef struct
{
    EBI_ADDRESS_TYPE_e     eAddressType;
    EBI_BUS_WIDTH_e        eMemBusWidth;
    EBI_BYTE_LANE_SEL_e    eByteLaneSel;    /**< Enable byte lane selection in case of 8bit memory organization */
    EBI_CLK_CYCLE_e        eKeepCycle;      /**< Address keeps the value for AH + 1 clock (HCLK) cycle. */
    uint8_t                un8NormWait;     /**< It represents wait value to be used for memory read/write operation. (NORMWAIT+1)*/

    EBI_EXT_REQ_t          tExtReq;
    EBI_EXT_CYCLE_t        tExtCycle;
} EBI_CFG_t;

/**
 *******************************************************************************
 * @brief       Initialize EBI.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_EBI_Init(EBI_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize EBI.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_EBI_Uninit(EBI_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration EBI.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : EBI Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_EBI_SetConfig(EBI_ID_e eId, EBI_CFG_t *ptCfg);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_EBI_H_ */

/** @} */
/** @} */
