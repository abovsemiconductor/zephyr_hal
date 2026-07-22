/**
 *******************************************************************************
 * @file        hal_wt.h
 * @author      ABOV R&D Division
 * @brief       Watch Timer
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
 * @defgroup    HAL_WT WT
 * @{
 * @brief       Watch Timer
 */

#ifndef _HAL_WT_H_
#define _HAL_WT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief WT Instance Id
 */
typedef enum
{
    WT_ID_0,
    WT_ID_1,
    WT_ID_2,
    WT_ID_3,
    WT_ID_4,
    WT_ID_5,
    WT_ID_6,
    WT_ID_7,
    WT_ID_8,
    WT_ID_9,
    WT_ID_MAX
} WT_ID_e;

/**
 * @brief WT clock source
 */
typedef enum
{
    WT_CLK_MCCR,    /**< Misc Clock source ::WT_CLK_MCCR_e */
    WT_CLK_LSE,     /**< Low Speed External Clock source */
    WT_CLK_WDTRC,   /**< Watch Dog Timer Ring Osillator Clock source */
    WT_CLK_MAX
} WT_CLK_e;

/**
 * @brief WT MCCR (Misc Clock) Source
 */
typedef enum
{
    WT_CLK_MCCR_LSI,    /**< Low Speed Internal Clock source */
    WT_CLK_MCCR_LSE,    /**< Low Speed External Clock source */
    WT_CLK_MCCR_MCLK,   /**< Master Clock source */
    WT_CLK_MCCR_HSI,    /**< High Speed Internal Clock source */
    WT_CLK_MCCR_HSE,    /**< High Speed External Clock source */
    WT_CLK_MCCR_PLL,    /**< Phase-Locked Loop (PLL) Clock source */
    WT_CLK_MCCR_MAX
} WT_CLK_MCCR_e;

/**
 * @brief WT Interval Mode
 */
typedef enum
{
    WT_INTV_2_7,                   /**< fWT/2^7 */
    WT_INTV_2_13,                  /**< fWT/2^13 */
    WT_INTV_2_14,                  /**< fWT/2^14 */
    WT_INTV_2_14_MULY_DATA_REG,    /**< fWT/(2^14 x (un16MatchCnt + 1)) ::WT_CFG_t */
    WT_INTV_MAX,
} WT_INTV_e;

/**
 * @brief WT Operation
 */
typedef enum
{
    WT_OPS_POLL,        /**< Operation Polling */
    WT_OPS_INTR,        /**< Operation Interrupt */
    WT_OPS_MAX
} WT_OPS_e;

/**
 * @brief WT Event
 */
typedef enum
{
    WT_EVENT_MATCH    = BIT(0),    /**< Match occurred */
    WT_EVENT_MAX,
} WT_EVENT_e;

/**
 * @brief WT Clock Configuration
 */
typedef struct
{
    WT_CLK_e       eClk;
    WT_CLK_MCCR_e  eMccr;         /**< When selecting MCCR at eClk */
    uint8_t        un8MccrDiv;    /**< When selecting MCCR at eClk */
} WT_CLK_CFG_t;

/**
 * @brief WT Mode Configuration
 */
typedef struct
{
    WT_INTV_e    eIntv;
    bool         bIntrEnable;     /**< Interrupt Enable */
    uint16_t     un16MatchCnt;    /**< Match Data value */
} WT_CFG_t;

/**
 * @brief WT IRQ handler context
 */
typedef struct
{
    WT_ID_e eId;        /**< WT Instance Id */
    bool    bWakeup;    /**< Wake-up flag */
} WT_Context_t;

/**
 *******************************************************************************
 * @brief       WT Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::WT_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnWT_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize WT.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WT_Init(WT_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize WT.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WT_Uninit(WT_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration WT.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClkCfg : WT Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WT_SetClkConfig(WT_ID_e eId, WT_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration WT.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : WT Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WT_SetConfig(WT_ID_e eId, WT_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ WT.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WT_SetIRQ(WT_ID_e eId, WT_OPS_e eOps, pfnWT_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Start WT.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WT_Start(WT_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop WT.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WT_Stop(WT_ID_e eId);

/**
 *******************************************************************************
 * @brief       Get Event Flag WT.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pbEvt : Event Flag (true = matched, false = not matched).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WT_GetEvent(WT_ID_e eId, bool *pbEvt);

/**
 *******************************************************************************
 * @brief       Set Wake-up source WT.
 * @param[in]   eId : Instance Id.
 * @param[in]   bEnable : Enable Wake-up source.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WT_SetWakeupSrc(WT_ID_e eId, bool bEnable);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_WT_H_ */

/** @} */
/** @} */
