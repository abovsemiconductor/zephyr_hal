/**
 *******************************************************************************
 * @file        hal_timer4.h
 * @author      ABOV R&D Division
 * @brief       4N typed timer
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
 * @defgroup    HAL_TIMER4 TIMER4
 * @{
 * @brief       16-bit Multi-Input Capture Timer
 */

#ifndef _HAL_TIMER4_H_
#define _HAL_TIMER4_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief TIMER4 Instance Id
 */
typedef enum
{
    TIMER4_ID_0,
    TIMER4_ID_1,
    TIMER4_ID_2,
    TIMER4_ID_3,
    TIMER4_ID_4,
    TIMER4_ID_5,
    TIMER4_ID_6,
    TIMER4_ID_7,
    TIMER4_ID_8,
    TIMER4_ID_9,
    TIMER4_ID_MAX
} TIMER4_ID_e;

/**
 * @brief TIMER4 Mode
 */
typedef enum
{
    TIMER4_MODE_PERIODIC,    /**< Periodic, Timer/Counter Mode */
    TIMER4_MODE_CAPTURE,     /**< Capture Mode */
    TIMER4_MODE_ONESHOT,     /**< One-Shot (PPG : Programmable Pulse Generation) */
    TIMER4_MODE_PWM,         /**< Pulse Width Modulation Mode (PPG : Programmable Pulse Generation)  */
    TIMER4_MODE_MAX
} TIMER4_MODE_e;

/**
 * @brief TIMER4 Clock Source
 */
typedef enum
{
    TIMER4_CLK_MCCR,    /**< Misc Clock source ::TIMER4_CLK_MCCR_e */
    TIMER4_CLK_EXT,     /**< External Clock source input */
    TIMER4_CLK_PCLK,    /**< Peripheral Clock source */
    TIMER4_CLK_MAX
} TIMER4_CLK_e;

/**
 * @brief TIMER4 MCCR (Misc Clock) Source
 */
typedef enum
{
    TIMER4_CLK_MCCR_LSI,    /**< Low Speed Internal Clock source */
    TIMER4_CLK_MCCR_LSE,    /**< Low Speed External Clock source */
    TIMER4_CLK_MCCR_MCLK,   /**< Master Clock source */
    TIMER4_CLK_MCCR_HSI,    /**< High Speed Internal Clock source */
    TIMER4_CLK_MCCR_HSE,    /**< High Speed External Clock source */
    TIMER4_CLK_MCCR_PLL,    /**< Phase-Locked Loop (PLL) Clock source */
    TIMER4_CLK_MCCR_NONE,
    TIMER4_CLK_MCCR_MAX
} TIMER4_CLK_MCCR_e;

/**
 * @brief TIMER4 External Clock Input Edge
 */
typedef enum
{
    TIMER4_EXTCLK_EDGE_FALLING,
    TIMER4_EXTCLK_EDGE_RISING,
    TIMER4_EXTCLK_EDGE_MAX
} TIMER4_EXTCLK_EDGE_e;

/**
 * @brief TIMER4 Output Port Polarity
 */
typedef enum
{
    TIMER4_POL_LOW,
    TIMER4_POL_HIGH,
    TIMER4_POL_MAX
} TIMER4_POL_e;

/**
 * @brief TIMER4 Output Port Inversion
 */
typedef enum
{
    TIMER4_INV_OFF,
    TIMER4_INV_ON,
    TIMER4_INV_MAX
} TIMER4_INV_e;

/**
 * @brief TIMER4 Data Type
 */
typedef enum
{
    TIMER4_DATA_A,       /**< A Data / General A Data */
    TIMER4_DATA_B,       /**< B Data / General B Data */
    TIMER4_DATA_CAP_A,   /**< Capture A Data */
    TIMER4_DATA_CAP_B,   /**< Capture B Data */
    TIMER4_DATA_MAX
} TIMER4_DATA_e;

/**
 * @brief TIMER4 Port IN/OUT Mode (Only Single Port)
 */
typedef enum
{
    TIMER4_PORT_IN,
    TIMER4_PORT_OUT,
    TIMER4_PORT_MAX
} TIMER4_PORT_e;

/**
 * @brief TIMER4 Capture Input Channel
 */
typedef enum
{
    TIMER4_CAP_CH_1,    /**< Capture Input Channel 1 */
    TIMER4_CAP_CH_2,    /**< Capture Input Channel 2 */
    TIMER4_CAP_CH_3,    /**< Capture Input Channel 3 */
    TIMER4_CAP_CH_XOR,  /**< Capture Input Channel 1,2,3 XOR */
    TIMER4_CAP_CH_MAX
} TIMER4_CAP_CH_e;

/**
 * @brief TIMER4 Capture Counter Edge
 */
typedef enum
{
    TIMER4_CAP_EDGE_FALLING,
    TIMER4_CAP_EDGE_RISING,
    TIMER4_CAP_EDGE_BOTH,
    TIMER4_CAP_EDGE_NONE,
    TIMER4_CAP_MAX
} TIMER4_CAP_EDGE_e;

/**
 * @brief TIMER4 Interrupt Status
 */
typedef enum
{
    TIMER4_INTR_FLAG_NONE,
    TIMER4_INTR_FLAG_CAP      = BIT(0),                   /**< Capture occurred */
    TIMER4_INTR_FLAG_MATCH    = BIT(1),                   /**< Match occurred */
    TIMER4_INTR_FLAG_A        = TIMER4_INTR_FLAG_MATCH,   /**< A Data Match occurred */
    TIMER4_INTR_FLAG_B        = BIT(2),                   /**< B Data Match occurred */
    TIMER4_INTR_FLAG_OVF      = BIT(3),                   /**< Overflow occurred */
    TIMER4_INTR_FLAG_MAX
} TIMER4_INTR_FLAG_e;

/**
 * @brief TIMER4 Event
 */
typedef enum
{
    TIMER4_EVENT_PERIODIC_MATCH    = BIT(0),
    TIMER4_EVENT_PWM_DUTY          = BIT(1),
    TIMER4_EVENT_PWM_PERIOD        = BIT(2),
    TIMER4_EVENT_CAPTURE           = BIT(3),
    TIMER4_EVENT_CAPTURE_A         = TIMER4_EVENT_CAPTURE,
    TIMER4_EVENT_CAPTURE_B         = BIT(4),
    TIMER4_EVENT_MAX
} TIMER4_EVENT_e;

/**
 * @brief TIMER4 Operation
 */
typedef enum
{
    TIMER4_OPS_POLL,        /**< Operation Polling */
    TIMER4_OPS_INTR,        /**< Operation Interrupt */
    TIMER4_OPS_MAX
} TIMER4_OPS_e;

/**
 * @brief TIMER4 Clock Configuration
 */
typedef struct
{
    TIMER4_CLK_e    eClk;
    union 
    {
        TIMER4_EXTCLK_EDGE_e    eExtClkEdge;    /**< When selecting External Clock Souce Input at eClk */
        TIMER4_CLK_MCCR_e       eMccr;          /**< When selecting MCCR at eClk */
    } uSubClk;
    uint8_t         un8MccrDiv;                 /**< When selecting MCCR at eClk */
    uint16_t        un16PreScale;               /**< Pre-scaler (Post-Divider) after eClk selection */
} TIMER4_CLK_CFG_t;

/**
 * @brief TIMER4 Capture Configuration
 */
typedef struct
{
    TIMER4_CAP_EDGE_e   eEdge;            /* Capture Edge Mode */
    TIMER4_CAP_CH_e     eCh;              /* Capture Input Channel */
    uint16_t            un16EdgeCount;    /* Capture Edge Count Value */
} TIMER4_CAP_CFG_t;

/**
 * @brief TIMER4 Mode Configuration
 */
typedef struct
{
    TIMER4_MODE_e       eMode;
    TIMER4_POL_e        ePol;
    TIMER4_CAP_CFG_t    tCapCfg;        /* Capture Mode Configuration */
    bool                bIntrEnable;    /* Interrupt Enable */
    union
    {
        struct
        {
            uint16_t    un16DataA;      /* A Data or General A Data */
            uint16_t    un16DataB;      /* B Data or General B Data */
        } tGRD;
        struct
        {
            uint16_t    un16Duty;       /* PWM Duty when TIMER4_MODE_PWM mode */
            uint16_t    un16Period;     /* PWM Period when TIMER2_MODE_PWM mode */
        } tPWM;
    } utData;
} TIMER4_CFG_t;

/**
 * @brief TIMER4 IRQ handler context
 */
typedef struct
{
    TIMER4_ID_e eId;    /**< TIMER4 Instance Id */
} TIMER4_Context_t;

/**
 *******************************************************************************
 * @brief       TIMER4 Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::TIMER4_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnTIMER4_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize TIMER4.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4_Init(TIMER4_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize TIMER4.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4_Uninit(TIMER4_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration TIMER4.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClkCfg : TIMER4 Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4_SetClkConfig(TIMER4_ID_e eId, TIMER4_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration TIMER4.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : TIMER4 Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4_SetConfig(TIMER4_ID_e eId, TIMER4_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ TIMER4.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4_SetIRQ(TIMER4_ID_e eId, TIMER4_OPS_e eOps, pfnTIMER4_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Start TIMER4.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4_Start(TIMER4_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop TIMER4.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4_Stop(TIMER4_ID_e eId);

/**
 *******************************************************************************
 * @brief       Get Interrupt Status TIMER4.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun32Status : ::TIMER4_INTR_FLAG_e (Bit Order).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4_GetStatus(TIMER4_ID_e eId, uint32_t *pun32Status);

/**
 *******************************************************************************
 * @brief       Set Data TIMER4.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSel : Specific Data Type.
 * @param[in]   un32Data : Set Data to Specific Buffer by eSel.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4_SetData(TIMER4_ID_e eId, TIMER4_DATA_e eSel, uint32_t un32Data);

/**
 *******************************************************************************
 * @brief       Get Data TIMER4.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSel : Specific Data Type.
 * @param[out]  *pun32Data : Get Data from Specific Buffer by eSel.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4_GetData(TIMER4_ID_e eId, TIMER4_DATA_e eSel, uint32_t *pun32Data);

/**
 *******************************************************************************
 * @brief       Set to Pause TIMER4.
 * @param[in]   eId : Instance Id.
 * @param[in]   bPause : true = pause, false = continue.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4_SetPause(TIMER4_ID_e eId, bool bPause);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_TIMER4_H_ */

/** @} */
/** @} */

