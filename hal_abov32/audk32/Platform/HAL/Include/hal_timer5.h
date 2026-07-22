/**
 *******************************************************************************
 * @file        hal_timer5.h
 * @author      ABOV R&D Division
 * @brief       5N typed timer
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
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
 * @defgroup    HAL_TIMER5 TIMER5
 * @{
 * @brief       16-bit General Purpose Timer
 */

#ifndef _HAL_TIMER5_H_
#define _HAL_TIMER5_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief TIMER5 Instance Id
 */
typedef enum
{
    TIMER5_ID_0,
    TIMER5_ID_1,
    TIMER5_ID_2,
    TIMER5_ID_3,
    TIMER5_ID_4,
    TIMER5_ID_5,
    TIMER5_ID_6,
    TIMER5_ID_7,
    TIMER5_ID_8,
    TIMER5_ID_9,
    TIMER5_ID_MAX
} TIMER5_ID_e;

/**
 * @brief TIMER5 Mode
 */
typedef enum
{
    TIMER5_MODE_PERIODIC,    /**< Periodic, Timer/Counter Mode */
    TIMER5_MODE_CAPTURE,     /**< Capture Mode */
    TIMER5_MODE_ONESHOT,     /**< One-Shot (PPG : Programmable Pulse Generation) */
    TIMER5_MODE_PWM,         /**< Pulse Width Modulation Mode (PPG : Programmable Pulse Generation)  */
    TIMER5_MODE_MAX
} TIMER5_MODE_e;

/**
 * @brief TIMER5 Clock Source
 */
typedef enum
{
    TIMER5_CLK_MCCR,    /**< Misc Clock source ::TIMER5_CLK_MCCR_e */
    TIMER5_CLK_EXT,     /**< External Clock source input */
    TIMER5_CLK_PCLK,    /**< Peripheral Clock source */
    TIMER5_CLK_WDTRC,   /**< Watch Dog Timer Ring Osillator Clock source */
    TIMER5_CLK_MAX
} TIMER5_CLK_e;

/**
 * @brief TIMER5 MCCR (Misc Clock) Source
 */
typedef enum
{
    TIMER5_CLK_MCCR_LSI,    /**< Low Speed Internal Clock source */
    TIMER5_CLK_MCCR_LSE,    /**< Low Speed External Clock source */
    TIMER5_CLK_MCCR_MCLK,   /**< Master Clock source */
    TIMER5_CLK_MCCR_HSI,    /**< High Speed Internal Clock source */
    TIMER5_CLK_MCCR_HSE,    /**< High Speed External Clock source */
    TIMER5_CLK_MCCR_PLL,    /**< Phase-Locked Loop (PLL) Clock source */
    TIMER5_CLK_MCCR_NONE,
    TIMER5_CLK_MCCR_MAX
} TIMER5_CLK_MCCR_e;

/**
 * @brief TIMER5 External Clock Input Edge
 */
typedef enum
{
    TIMER5_EXTCLK_EDGE_FALLING,
    TIMER5_EXTCLK_EDGE_RISING,
    TIMER5_EXTCLK_EDGE_MAX
} TIMER5_EXTCLK_EDGE_e;

/**
 * @brief TIMER5 Output Port Polarity
 */
typedef enum
{
    TIMER5_POL_LOW,
    TIMER5_POL_HIGH,
    TIMER5_POL_MAX
} TIMER5_POL_e;

/**
 * @brief TIMER5 Data Type
 */
typedef enum
{
    TIMER5_DATA_A,       /**< A Data / General A Data */
    TIMER5_DATA_B,       /**< B Data / General B Data */
    TIMER5_DATA_CAP_A,   /**< Capture A Data */
    TIMER5_DATA_CAP_B,   /**< Capture B Data */
    TIMER5_DATA_MAX
} TIMER5_DATA_e;

/**
 * @brief TIMER5 Capture Counter Edge
 */
typedef enum
{
    TIMER5_CAP_EDGE_FALLING,
    TIMER5_CAP_EDGE_RISING,
    TIMER5_CAP_EDGE_BOTH,
    TIMER5_CAP_EDGE_NONE,
    TIMER5_CAP_MAX
} TIMER5_CAP_EDGE_e;

/**
 * @brief TIMER5 Capture Signal Mode
 */
typedef enum
{
    TIMER5_CAP_SIG_EXT,      /**< External Input Signal */
    TIMER5_CAP_SIG_LSE,      /**< External Low Speed Clock source */
    TIMER5_CAP_SIG_WDTRC,    /**< Watch Dog Timer Ring Osillator Clock source */
    TIMER5_CAP_SIG_MAX
} TIMER5_CAP_SIG_e;

/**
 * @brief TIMER5 Interrupt Status
 */
typedef enum
{
    TIMER5_INTR_FLAG_NONE,
    TIMER5_INTR_FLAG_CAP      = BIT(0),                   /**< Capture occurred */
    TIMER5_INTR_FLAG_MATCH    = BIT(1),                   /**< Match occurred */
    TIMER5_INTR_FLAG_A        = TIMER5_INTR_FLAG_MATCH,   /**< A Data Match occurred */
    TIMER5_INTR_FLAG_B        = BIT(2),                   /**< B Data Match occurred */
    TIMER5_INTR_FLAG_OVF      = BIT(3),                   /**< Overflow occurred */
    TIMER5_INTR_FLAG_MAX
} TIMER5_INTR_FLAG_e;

/**
 * @brief TIMER5 Event
 */
typedef enum
{
    TIMER5_EVENT_PERIODIC_MATCH    = BIT(0),
    TIMER5_EVENT_PWM_DUTY          = BIT(1),
    TIMER5_EVENT_PWM_PERIOD        = BIT(2),
    TIMER5_EVENT_CAPTURE           = BIT(3),
    TIMER5_EVENT_CAPTURE_A         = TIMER5_EVENT_CAPTURE,
    TIMER5_EVENT_CAPTURE_B         = BIT(4),
    TIMER5_EVENT_OVERFLOW          = BIT(5),
    TIMER5_EVENT_MAX,
} TIMER5_EVENT_e;

/**
 * @brief TIMER5 Operation
 */
typedef enum
{
    TIMER5_OPS_POLL,        /**< Operation Polling */
    TIMER5_OPS_INTR,        /**< Operation Interrupt */
    TIMER5_OPS_MAX
} TIMER5_OPS_e;

/**
 * @brief TIMER5 Clock Configuration
 */
typedef struct
{
    TIMER5_CLK_e    eClk;
    union 
    {
        TIMER5_EXTCLK_EDGE_e    eExtClkEdge;     /**< When selecting External Clock Souce Input at eClk */
        TIMER5_CLK_MCCR_e       eMccr;           /**< When selecting MCCR at eClk */
    } uSubClk;
    uint16_t        un16PreScale;                /**< Pre-scaler (Post-Divider) after eClk selection */
} TIMER5_CLK_CFG_t;

/**
 * @brief TIMER5 Capture Configuration
 */
typedef struct
{
    TIMER5_CAP_EDGE_e   eEdge;         /**< Capture Edge Mode */
    TIMER5_CAP_SIG_e    eSig;          /**< Capture Signal Mode */
    bool                bKeepCount;    /**< Keep count Enable after Capture */
} TIMER5_CAP_CFG_t;

/**
 * @brief TIMER5 Mode Configuration
 */
typedef struct
{
    TIMER5_MODE_e       eMode;
    TIMER5_POL_e        ePol;
    TIMER5_CAP_CFG_t    tCapCfg;        /**< Capture Mode Configuration */
    bool                bIntrEnable;    /**< Interrupt Enable */
    union
    {
        struct
        {
            uint16_t    un16DataA;      /* A Data or General A Data */
            uint16_t    un16DataB;      /* B Data or General B Data */
        } tGRD;
        struct
        {
            uint16_t    un16Duty;       /* PWM Duty when TIMER5_MODE_PWM mode */
            uint16_t    un16Period;     /* PWM Period when TIMER5_MODE_PWM mode */
        } tPWM;
    } utData;
} TIMER5_CFG_t;

/**
 * @brief TIMER5 IRQ handler context
 */
typedef struct
{
    TIMER5_ID_e eId;    /**< TIMER5 Instance Id */
} TIMER5_Context_t;

/**
 *******************************************************************************
 * @brief       TIMER5 Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::TIMER5_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnTIMER5_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize TIMER5.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER5_Init(TIMER5_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize TIMER5.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER5_Uninit(TIMER5_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration TIMER5.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClkCfg : TIMER5 Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER5_SetClkConfig(TIMER5_ID_e eId, TIMER5_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration TIMER5.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : TIMER5 Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER5_SetConfig(TIMER5_ID_e eId, TIMER5_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ TIMER5.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER5_SetIRQ(TIMER5_ID_e eId, TIMER5_OPS_e eOps, pfnTIMER5_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Start TIMER5.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER5_Start(TIMER5_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop TIMER5.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER5_Stop(TIMER5_ID_e eId);

/**
 *******************************************************************************
 * @brief       Get Interrupt Status TIMER5.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun32Status : ::TIMER5_INTR_FLAG_e (Bit Order).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER5_GetStatus(TIMER5_ID_e eId, uint32_t *pun32Status);

/**
 *******************************************************************************
 * @brief       Set Data TIMER5.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSel : Specific Data Type.
 * @param[in]   un32Data : Set Data to Specific Buffer by eSel.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER5_SetData(TIMER5_ID_e eId, TIMER5_DATA_e eSel, uint32_t un32Data);

/**
 *******************************************************************************
 * @brief       Get Data TIMER5.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSel : Specific Data Type.
 * @param[out]  *pun32Data : Get Data from Specific Buffer by eSel.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER5_GetData(TIMER5_ID_e eId, TIMER5_DATA_e eSel, uint32_t *pun32Data);

/**
 *******************************************************************************
 * @brief       Set to Pause TIMER5.
 * @param[in]   eId : Instance Id.
 * @param[in]   bPause : true = pause, false = continue.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER5_SetPause(TIMER5_ID_e eId, bool bPause);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_TIMER5_H_ */

/** @} */
/** @} */

