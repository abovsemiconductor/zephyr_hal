/**
 *******************************************************************************
 * @file        hal_timer2.h
 * @author      ABOV R&D Division
 * @brief       2N typed timer
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
 * @defgroup    HAL_TIMER2 TIMER2
 * @{
 * @brief       32-bit General Purpose Timer
 */

#ifndef _HAL_TIMER2_H_
#define _HAL_TIMER2_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief TIMER2 Instance Id
 */
typedef enum
{
    TIMER2_ID_0,
    TIMER2_ID_1,
    TIMER2_ID_2,
    TIMER2_ID_3,
    TIMER2_ID_4,
    TIMER2_ID_5,
    TIMER2_ID_6,
    TIMER2_ID_7,
    TIMER2_ID_8,
    TIMER2_ID_9,
    TIMER2_ID_MAX
} TIMER2_ID_e;

/**
 * @brief TIMER2 Mode
 */
typedef enum
{
    TIMER2_MODE_PERIODIC,    /**< Periodic, Timer/Counter Mode */
    TIMER2_MODE_CAPTURE,     /**< Capture Mode */
    TIMER2_MODE_ONESHOT,     /**< One-Shot (PPG : Programmable Pulse Generation) */
    TIMER2_MODE_PWM,         /**< Pulse Width Modulation Mode (PPG : Programmable Pulse Generation)  */
    TIMER2_MODE_MAX
} TIMER2_MODE_e;

/**
 * @brief TIMER2 Clock Source
 */
typedef enum
{
    TIMER2_CLK_MCCR,    /**< Misc Clock source ::TIMER2_CLK_MCCR_e */
    TIMER2_CLK_EXT,     /**< External Clock source input */
    TIMER2_CLK_PCLK,    /**< Peripheral Clock source */
    TIMER2_CLK_MAX
} TIMER2_CLK_e;

/**
 * @brief TIMER2 MCCR (Misc Clock) Source
 */
typedef enum
{
    TIMER2_CLK_MCCR_LSI,    /**< Low Speed Internal Clock source */
    TIMER2_CLK_MCCR_LSE,    /**< Low Speed External Clock source */
    TIMER2_CLK_MCCR_MCLK,   /**< Master Clock source */
    TIMER2_CLK_MCCR_HSI,    /**< High Speed Internal Clock source */
    TIMER2_CLK_MCCR_HSE,    /**< High Speed External Clock source */
    TIMER2_CLK_MCCR_PLL,    /**< Phase-Locked Loop (PLL) Clock source */
    TIMER2_CLK_MCCR_NONE,
    TIMER2_CLK_MCCR_MAX
} TIMER2_CLK_MCCR_e;

/**
 * @brief TIMER2 External Clock Input Edge
 */
typedef enum
{
    TIMER2_EXTCLK_EDGE_FALLING,
    TIMER2_EXTCLK_EDGE_RISING,
    TIMER2_EXTCLK_EDGE_MAX
} TIMER2_EXTCLK_EDGE_e;

/**
 * @brief TIMER2 Output Port Polarity
 */
typedef enum
{
    TIMER2_POL_LOW,
    TIMER2_POL_HIGH,
    TIMER2_POL_MAX
} TIMER2_POL_e;

/**
 * @brief TIMER2 Output Port Inversion
 */
typedef enum
{
    TIMER2_INV_OFF,
    TIMER2_INV_ON,
    TIMER2_INV_MAX
} TIMER2_INV_e;

/**
 * @brief TIMER2 Data Type
 */
typedef enum
{
    TIMER2_DATA_A,       /**< A Data / General A Data */
    TIMER2_DATA_B,       /**< B Data / General B Data */
    TIMER2_DATA_CAP_A,   /**< Capture A Data */
    TIMER2_DATA_CAP_B,   /**< Capture B Data */
    TIMER2_DATA_MAX
} TIMER2_DATA_e;

/**
 * @brief TIMER2 Port IN/OUT Mode (Only Single Port)
 */
typedef enum
{
    TIMER2_PORT_IN,
    TIMER2_PORT_OUT,
    TIMER2_PORT_MAX
} TIMER2_PORT_e;

/**
 * @brief TIMER2 Capture Counter Edge
 */
typedef enum
{
    TIMER2_CAP_EDGE_FALLING,
    TIMER2_CAP_EDGE_RISING,
    TIMER2_CAP_EDGE_BOTH,
    TIMER2_CAP_EDGE_NONE,
    TIMER2_CAP_MAX
} TIMER2_CAP_EDGE_e;

/**
 * @brief TIMER2 Update Comparation buffer
 */
typedef enum
{
    TIMER2_UPDATE_AFTER,    /**< Update Data after current period */
    TIMER2_UPDATE_IN,       /**< Update Data in current period */
    TIMER2_UPDATE_MAX
} TIMER2_UPDATE_e;

/**
 * @brief TIMER2 Capture Signal Mode
 */
typedef enum
{
    TIMER2_CAP_SIG_EXT,      /**< External Input Signal */
    TIMER2_CAP_SIG_LSE,      /**< External Low Speed Clock source */
    TIMER2_CAP_SIG_WDTRC,    /**< Watch Dog Timer Ring Osillator Clock source */
    TIMER2_CAP_SIG_LSI = TIMER2_CAP_SIG_WDTRC,  /**< Internal Low Speed Clock source */
    TIMER2_CAP_SIG_MAX
} TIMER2_CAP_SIG_e;

/**
 * @brief TIMER2 Interrupt Status
 */
typedef enum
{
    TIMER2_INTR_FLAG_NONE,
    TIMER2_INTR_FLAG_CAP      = BIT(0),                   /**< Capture occurred */
    TIMER2_INTR_FLAG_MATCH    = BIT(1),                   /**< Match occurred */
    TIMER2_INTR_FLAG_A        = TIMER2_INTR_FLAG_MATCH,   /**< A Data Match occurred */
    TIMER2_INTR_FLAG_B        = BIT(2),                   /**< B Data Match occurred */
    TIMER2_INTR_FLAG_OVF      = BIT(3),                   /**< Overflow occurred */
    TIMER2_INTR_FLAG_MAX
} TIMER2_INTR_FLAG_e;

/**
 * @brief TIMER2 Event
 */
typedef enum
{
    TIMER2_EVENT_PERIODIC_MATCH    = BIT(0),
    TIMER2_EVENT_PWM_DUTY          = BIT(1),
    TIMER2_EVENT_PWM_PERIOD        = BIT(2),
    TIMER2_EVENT_CAPTURE           = BIT(3),
    TIMER2_EVENT_CAPTURE_A         = TIMER2_EVENT_CAPTURE,
    TIMER2_EVENT_CAPTURE_B         = BIT(4),
    TIMER2_EVENT_OVERFLOW          = BIT(5),
    TIMER2_EVENT_MAX,
} TIMER2_EVENT_e;

/**
 * @brief TIMER2 Operation
 */
typedef enum
{
    TIMER2_OPS_POLL,        /**< Operation Polling */
    TIMER2_OPS_INTR,        /**< Operation Interrupt */
    TIMER2_OPS_MAX
} TIMER2_OPS_e;

/**
 * @brief TIMER2 Clock Configuration
 */
typedef struct
{
    TIMER2_CLK_e    eClk;
    union 
    {
        TIMER2_EXTCLK_EDGE_e    eExtClkEdge;     /**< When selecting External Clock Souce Input at eClk */
        TIMER2_CLK_MCCR_e       eMccr;           /**< When selecting MCCR at eClk */
    } uSubClk;
    uint8_t         un8MccrDiv;                  /**< When selecting MCCR at eClk */
    uint16_t        un16PreScale;                /**< Pre-scaler (Post-Divider) after eClk selection */
} TIMER2_CLK_CFG_t;

/**
 * @brief TIMER2 Capture Configuration
 */
typedef struct
{
    TIMER2_CAP_EDGE_e   eEdge;         /**< Capture Edge Mode */
    TIMER2_CAP_SIG_e    eSig;          /**< Capture Signal Mode */
    bool                bKeepCount;    /**< Keep count Enable after Capture */
} TIMER2_CAP_CFG_t;

/**
 * @brief TIMER2 Mode Configuration
 */
typedef struct
{
    TIMER2_MODE_e       eMode;
    TIMER2_POL_e        ePol;
    TIMER2_CAP_CFG_t    tCapCfg;        /**< Capture Mode Configuration */
    bool                bIntrEnable;    /**< Interrupt Enable */
    union
    {
        struct
        {
            uint32_t    un32DataA;      /* A Data or General A Data */
            uint32_t    un32DataB;      /* B Data or General B Data */
        } tGRD;
        struct
        {
            uint32_t    un32Duty;       /* PWM Duty when TIMER2_MODE_PWM mode */
            uint32_t    un32Period;     /* PWM Period when TIMER2_MODE_PWM mode */
        } tPWM;
    } utData;
} TIMER2_CFG_t;

/**
 * @brief TIMER2 IRQ handler context
 */
typedef struct
{
    TIMER2_ID_e eId;    /**< TIMER2 Instance Id */
} TIMER2_Context_t;

/**
 *******************************************************************************
 * @brief       TIMER2 Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::TIMER2_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnTIMER2_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize TIMER2.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER2_Init(TIMER2_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize TIMER2.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER2_Uninit(TIMER2_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration TIMER2.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClkCfg : TIMER2 Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER2_SetClkConfig(TIMER2_ID_e eId, TIMER2_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration TIMER2.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : TIMER2 Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER2_SetConfig(TIMER2_ID_e eId, TIMER2_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ TIMER2.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER2_SetIRQ(TIMER2_ID_e eId, TIMER2_OPS_e eOps, pfnTIMER2_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Start TIMER2.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER2_Start(TIMER2_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop TIMER2.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER2_Stop(TIMER2_ID_e eId);

/**
 *******************************************************************************
 * @brief       Get Interrupt Status TIMER2.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun32Status : ::TIMER2_INTR_FLAG_e (Bit Order).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER2_GetStatus(TIMER2_ID_e eId, uint32_t *pun32Status);

/**
 *******************************************************************************
 * @brief       Set Data TIMER2.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSel : Specific Data Type.
 * @param[in]   un32Data : Set Data to Specific Buffer by eSel.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER2_SetData(TIMER2_ID_e eId, TIMER2_DATA_e eSel, uint32_t un32Data);

/**
 *******************************************************************************
 * @brief       Get Data TIMER2.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSel : Specific Data Type.
 * @param[out]  *pun32Data : Get Data from Specific Buffer by eSel.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER2_GetData(TIMER2_ID_e eId, TIMER2_DATA_e eSel, uint32_t *pun32Data);

/**
 *******************************************************************************
 * @brief       Set to Pause TIMER2.
 * @param[in]   eId : Instance Id.
 * @param[in]   bPause : true = pause, false = continue.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER2_SetPause(TIMER2_ID_e eId, bool bPause);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_TIMER2_H_ */

/** @} */
/** @} */

