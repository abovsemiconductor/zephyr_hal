/**
 *******************************************************************************
 * @file        hal_wdt.h
 * @author      ABOV R&D Division
 * @brief       Watch Dog Timer
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
 * @defgroup    HAL_WDT WDT
 * @{
 * @brief       Watch Dog Timer
 */

#ifndef _HAL_WDT_H_
#define _HAL_WDT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief WDT Instance Id
 */
typedef enum
{
    WDT_ID_0,
    WDT_ID_1,
    WDT_ID_2,
    WDT_ID_3,
    WDT_ID_4,
    WDT_ID_5,
    WDT_ID_6,
    WDT_ID_7,
    WDT_ID_8,
    WDT_ID_9,
    WDT_ID_MAX
} WDT_ID_e;

/**
 * @brief WDT Mode
 */
typedef enum
{
    WDT_MODE_NONE         = 0,
    WDT_MODE_CNT          = BIT(0),    /**< Count Match Mode */
    WDT_MODE_RST          = BIT(1),    /**< Reset Mode */
    WDT_MODE_UNDERFLOW    = BIT(2),    /**< Underflow Mode */
    WDT_MODE_MAX
} WDT_MODE_e;

/**
 * @brief WDT Clock Source
 */
typedef enum
{
    WDT_CLK_WDTRC,    /**< Watch Dog Timer Ring Osillator Clock source */
    WDT_CLK_MCCR,     /**< Misc Clock source ::WDT_CLK_MCCR_e */
    WDT_CLK_PCLK,     /**< Peripheral Clock source */
    WDT_CLK_MAX
} WDT_CLK_e;

/**
 * @brief WDT MCCR (Misc Clock) Source
 */
typedef enum
{
    WDT_CLK_MCCR_LSI,    /**< Low Speed Internal Clock source */
    WDT_CLK_MCCR_LSE,    /**< Low Speed External Clock source */
    WDT_CLK_MCCR_MCLK,   /**< Master Clock source */
    WDT_CLK_MCCR_HSI,    /**< High Speed Internal Clock source */
    WDT_CLK_MCCR_HSE,    /**< High Speed External Clock source */
    WDT_CLK_MCCR_PLL,    /**< Phase-Locked Loop (PLL) Clock source */
    WDT_CLK_MCCR_MAX
} WDT_CLK_MCCR_e;

/**
 * @brief WDT Clock Pre-divide
 */
typedef enum
{
    WDT_CLK_PREDIV_1,      /**< fWDT */
    WDT_CLK_PREDIV_4,      /**< fWDT/4 */
    WDT_CLK_PREDIV_8,      /**< fWDT/8 */
    WDT_CLK_PREDIV_16,     /**< fWDT/16 */
    WDT_CLK_PREDIV_32,     /**< fWDT/32 */
    WDT_CLK_PREDIV_64,     /**< fWDT/64 */
    WDT_CLK_PREDIV_128,    /**< fWDT/128 */
    WDT_CLK_PREDIV_256,    /**< fWDT/256 */
    WDT_CLK_PREDIV_MAX
} WDT_CLK_PREDIV_e;

/**
 * @brief WDT Interrupt Mode
 */
typedef enum
{
    WDT_INTR_NONE          = 0,
    WDT_INTR_MATCH         = BIT(0),
    WDT_INTR_UNDERFLOW     = BIT(1),
    WDT_INTR_MAX
} WDT_INTR_e;

/**
 * @brief WDT Event
 */
typedef enum
{
    WDT_EVENT_MATCH        = BIT(0),
    WDT_EVENT_UNDERFLOW    = BIT(1),
    WDT_EVENT_MAX
} WDT_EVENT_e;

/**
 * @brief WDT Operation
 */
typedef enum
{
    WDT_OPS_POLL,        /**< Operation Polling */
    WDT_OPS_INTR,        /**< Operation Interrupt */
    WDT_OPS_MAX
} WDT_OPS_e;

/**
 * @brief WDT Clock Configuration
 */
typedef struct
{
    WDT_CLK_e           eClk;
    WDT_CLK_MCCR_e      eMccr;         /**< When selecting MCCR at eClk */
    uint8_t             un8MccrDiv;    /**< When selecting MCCR at eClk */
    WDT_CLK_PREDIV_e    ePreDiv;       /**< Post-divider after eClk selection */
} WDT_CLK_CFG_t;

/**
 * @brief WDT Mode Configuration
 */
typedef struct
{
    uint8_t             un8Mode;          /**< ::WDT_MODE_e (Bit Order) */
    uint8_t             un8IntrEnable;    /**< ::WDT_INTR_e (Bit Order) */
    uint32_t            un32InitCnt;      /**< Initial counter value */
    uint32_t            un32MatchCnt;     /**< Match counter value (Only some chipsets supported) */
} WDT_CFG_t;

/**
 * @brief WDT IRQ handler context
 */
typedef struct
{
    WDT_ID_e        eId;        /**< WDT Instance Id */
    uint8_t         un8Mode;    /**< ::WDT_MODE_e (Bit Order) */
    bool            bWakeup;    /**< Wake-up flag */
} WDT_Context_t;

/**
 *******************************************************************************
 * @brief       WDT Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::WDT_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnWDT_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize WDT.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WDT_Init(WDT_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize WDT.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WDT_Uninit(WDT_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration WDT.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClkCfg : WDT Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WDT_SetClkConfig(WDT_ID_e eId, WDT_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration WDT.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : WDT Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WDT_SetConfig(WDT_ID_e eId, WDT_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ WDT.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @param[in]   bNonMask : Enable non-maskable Interrupt.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WDT_SetIRQ(WDT_ID_e eId, WDT_OPS_e eOps, pfnWDT_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio, bool bNonMask);

/**
 *******************************************************************************
 * @brief       Start WDT.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WDT_Start(WDT_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop WDT.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WDT_Stop(WDT_ID_e eId);

/**
 *******************************************************************************
 * @brief       Get Current Count value WDT.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun32Count : Current Count value.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WDT_GetCount(WDT_ID_e eId, uint32_t *pun32Count);

/**
 *******************************************************************************
 * @brief       Set Re-load WDT.
 * @param[in]   eId : Instance Id.
 * @param[in]   un32Data : Re-load value (some of chipset support).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WDT_SetReload(WDT_ID_e eId, uint32_t un32Data);

/**
 *******************************************************************************
 * @brief       Set Wake-up source WDT.
 * @param[in]   eId : Instance Id.
 * @param[in]   bEnable : Enable Wake-up source.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_WDT_SetWakeupSrc(WDT_ID_e eId, bool bEnable);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_WDT_H_ */

/** @} */
/** @} */
