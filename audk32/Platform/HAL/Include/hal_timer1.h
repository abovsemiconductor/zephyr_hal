/**
 *******************************************************************************
 * @file        hal_timer1.h
 * @author      ABOV R&D Division
 * @brief       1N typed timer
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
 * @defgroup    HAL_TIMER1 TIMER1
 * @{
 * @brief       16-bit General Purpose Timer
 */

#ifndef _HAL_TIMER1_H_
#define _HAL_TIMER1_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief TIMER1 Instance Id
 */
typedef enum
{
    TIMER1_ID_0,
    TIMER1_ID_1,
    TIMER1_ID_2,
    TIMER1_ID_3,
    TIMER1_ID_4,
    TIMER1_ID_5,
    TIMER1_ID_6,
    TIMER1_ID_7,
    TIMER1_ID_8,
    TIMER1_ID_9,
    TIMER1_ID_10,
    TIMER1_ID_11,
    TIMER1_ID_MAX
} TIMER1_ID_e;

/**
 * @brief TIMER1 Mode
 */
typedef enum
{
    TIMER1_MODE_PERIODIC,    /**< Periodic, Timer/Counter Mode */
    TIMER1_MODE_CAPTURE,     /**< Capture Mode */
    TIMER1_MODE_ONESHOT,     /**< One-Shot (PPG : Programmable Pulse Generation) */
    TIMER1_MODE_PWM,         /**< Pulse Width Modulation Mode (PPG : Programmable Pulse Generation)  */
    TIMER1_MODE_MAX
} TIMER1_MODE_e;

/**
 * @brief TIMER1 Clock Source
 */
typedef enum
{
    TIMER1_CLK_MCCR,    /**< Misc Clock source ::TIMER1_CLK_MCCR_e */
    TIMER1_CLK_EXT,     /**< External Clock source input */
    TIMER1_CLK_PCLK,    /**< Peripheral Clock source */
    TIMER1_CLK_MAX
} TIMER1_CLK_e;

/**
 * @brief TIMER1 MCCR (Misc Clock) Source
 */
typedef enum
{
    TIMER1_CLK_MCCR_LSI,    /**< Low Speed Internal Clock source */
    TIMER1_CLK_MCCR_LSE,    /**< Low Speed External Clock source */
    TIMER1_CLK_MCCR_MCLK,   /**< Master Clock source */
    TIMER1_CLK_MCCR_HSI,    /**< High Speed Internal Clock source */
    TIMER1_CLK_MCCR_HSE,    /**< High Speed External Clock source */
    TIMER1_CLK_MCCR_PLL,    /**< Phase-Locked Loop (PLL) Clock source */
    TIMER1_CLK_MCCR_NONE,
    TIMER1_CLK_MCCR_MAX
} TIMER1_CLK_MCCR_e;

/**
 * @brief TIMER1 Peripheral Clock Divide
 */
typedef enum
{
    TIMER1_PCLK_DIV_2,     /**< PCLK/2 */
    TIMER1_PCLK_DIV_4,     /**< PCLK/4 */
    TIMER1_PCLK_DIV_16,    /**< PCLK/16 */
    TIMER1_PCLK_DIV_64,    /**< PCLK/64 */
    TIMER1_PCLK_DIV_MAX
} TIMER1_PCLK_DIV_e;

/**
 * @brief TIMER1 External Clock Input Edge
 */
typedef enum
{
    TIMER1_EXTCLK_EDGE_FALLING,
    TIMER1_EXTCLK_EDGE_RISING,
    TIMER1_EXTCLK_EDGE_MAX
} TIMER1_EXTCLK_EDGE_e;

/**
 * @brief TIMER1 Output Port Polarity
 */
typedef enum
{
    TIMER1_POL_LOW,
    TIMER1_POL_HIGH,
    TIMER1_POL_MAX
} TIMER1_POL_e;

/**
 * @brief TIMER1 Output Port Inversion
 */
typedef enum
{
    TIMER1_INV_OFF,
    TIMER1_INV_ON,
    TIMER1_INV_MAX
} TIMER1_INV_e;

/**
 * @brief TIMER1 Data Type
 */
typedef enum
{
    TIMER1_DATA_A,       /**< A Data / General A Data */
    TIMER1_DATA_B,       /**< B Data / General B Data */
    TIMER1_DATA_CAP_A,   /**< Capture A Data */
    TIMER1_DATA_CAP_B,   /**< Capture B Data */
    TIMER1_DATA_CNT,     /**< Counter */
    TIMER1_DATA_MAX
} TIMER1_DATA_e;

/**
 * @brief TIMER1 Port IN/OUT Mode (Only Single Port)
 */
typedef enum
{
    TIMER1_PORT_IN,
    TIMER1_PORT_OUT,
    TIMER1_PORT_MAX
} TIMER1_PORT_e;

/**
 * @brief TIMER1 Capture Counter Clear Edge
 */
typedef enum
{
    TIMER1_CAP_CLR_RISING,     /**< Clear counter when rising edge detected */
    TIMER1_CAP_CLR_FALLING,    /**< Clear counter when falling edge detected */
    TIMER1_CAP_CLR_BOTH,       /**< Clear counter when both edge detected */
    TIMER1_CAP_CLR_NONE,
    TIMER1_CAP_CLR_MAX
} TIMER1_CAP_CLR_e;

/**
 * @brief TIMER1 Update Comparation buffer
 */
typedef enum
{
    TIMER1_UPDATE_AFTER,    /**< Update Data after current period */
    TIMER1_UPDATE_IN,       /**< Update Data in current period */
    TIMER1_UPDATE_MAX
} TIMER1_UPDATE_e;

/**
 * @brief TIMER1 ADC Trigger Mode
 */
typedef enum
{
    TIMER1_ADCTRG_MODE_NORMAL,    /**< ADC Triggered by reached GRA value */
    TIMER1_ADCTRG_MODE_POINT,     /**< ADC Triggered by trigger point value */
    TIMER1_ADCTRG_MODE_BOTH,      /**< ADC Triggered by both of NORMAL and POINT */
    TIMER1_ADCTRG_MODE_MAX
} TIMER1_ADCTRG_MODE_e;


/**
 * @brief TIMER1 Interrupt Status
 */
typedef enum
{
    TIMER1_INTR_FLAG_NONE,
    TIMER1_INTR_FLAG_CAP      = BIT(0),                   /**< Capture occurred */
    TIMER1_INTR_FLAG_MATCH    = BIT(1),                   /**< Match occurred */
    TIMER1_INTR_FLAG_A        = TIMER1_INTR_FLAG_MATCH,   /**< A Data Match occurred */
    TIMER1_INTR_FLAG_B        = BIT(2),                   /**< B Data Match occurred */
    TIMER1_INTR_FLAG_OVF      = BIT(3),                   /**< Overflow occurred */
    TIMER1_INTR_FLAG_MAX
} TIMER1_INTR_FLAG_e;

/**
 * @brief TIMER1 Event
 */
typedef enum
{
    TIMER1_EVENT_PERIODIC_MATCH    = BIT(0),
    TIMER1_EVENT_PWM_DUTY          = BIT(1),
    TIMER1_EVENT_PWM_PERIOD        = BIT(2),
    TIMER1_EVENT_CAPTURE           = BIT(3),
    TIMER1_EVENT_CAPTURE_A         = TIMER1_EVENT_CAPTURE,
    TIMER1_EVENT_CAPTURE_B         = BIT(4),
    TIMER1_EVENT_OVERFLOW          = BIT(5),
    TIMER1_EVENT_MAX,
} TIMER1_EVENT_e;

/**
 * @brief TIMER1 Operation
 */
typedef enum
{
    TIMER1_OPS_POLL,        /**< Operation Polling */
    TIMER1_OPS_INTR,        /**< Operation Interrupt */
    TIMER1_OPS_NMI,         /**< Operation NMI */
    TIMER1_OPS_MAX
} TIMER1_OPS_e;

/**
 * @brief TIMER1 Clock Configuration
 */
typedef struct
{
    TIMER1_CLK_e    eClk;
    union 
    {
        TIMER1_PCLK_DIV_e       ePClkDiv;        /**< When selecting PCLK at eClk */
        TIMER1_EXTCLK_EDGE_e    eExtClkEdge;     /**< When selecting External Clock Souce Input at eClk */
        TIMER1_CLK_MCCR_e       eMccr;           /**< When selecting MCCR at eClk */
    } uSubClk;
    uint8_t         un8MccrDiv;                  /**< When selecting MCCR at eClk */
    uint16_t        un16PreScale;                /**< Pre-scaler (Post-Divider) after eClk selection */
} TIMER1_CLK_CFG_t;

/**
 * @brief TIMER1 TIMER3 Synchro Configuration
 */
typedef struct
{
    bool bSsync;    /**< Start counter synchronized by TIMER3 */
    bool bCsync;    /**< Clear counter Synchronized by TIMER3 */
} TIMER1_T30SYNC_CFG_t;

/**
 * @brief TIMER1 ADC Trigger Configuration
 */
typedef struct
{
    bool                    bEnable;       /**< Enable Adc Trigger */
    TIMER1_ADCTRG_MODE_e    eMode;
    uint16_t                un16TrgPnt;    /**< Trigger Point Value when selecting POINT and BOTH mode ::TIMER1_ADCTRG_MODE_e */
} TIMER1_ADCTRG_CFG_t;

/**
 * @brief TIMER1 Mode Configuration
 */
typedef struct
{
    TIMER1_MODE_e       eMode;
    TIMER1_POL_e        ePol;
    TIMER1_CAP_CLR_e    eCapClr;
    bool                bIntrEnable;       /**< Interrupt Enable */
    bool                bOVFIntrEnable;    /**< Additional Overflow Interrupt Enable */
    union
    {
        struct
        {
            uint16_t    un16DataA;          /**< A Data or General A Data */
            uint16_t    un16DataB;          /**< B Data or General B Data */
        } tGRD;
        struct
        {
            uint16_t    un16Duty;            /**< PWM Duty when TIMER1_MODE_PWM mode */
            uint16_t    un16Period;          /**< PWM Period when TIMER1_MODE_PWM mode */
        } tPWM;
    } utData;
} TIMER1_CFG_t;

/**
 * @brief TIMER1 IRQ handler context
 */
typedef struct
{
    TIMER1_ID_e eId;    /**< TIMER1 Instance Id */
} TIMER1_Context_t;

/**
 *******************************************************************************
 * @brief       TIMER1 Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::TIMER1_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnTIMER1_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize TIMER1.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER1_Init(TIMER1_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize TIMER1.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER1_Uninit(TIMER1_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration TIMER1.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClkCfg : TIMER1 Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER1_SetClkConfig(TIMER1_ID_e eId, TIMER1_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration TIMER1.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : TIMER1 Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER1_SetConfig(TIMER1_ID_e eId, TIMER1_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set Adc Trigger Configuration TIMER1.
 *              some of ABOV chipsets are only supported.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : TIMER1 ADC Trigger Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER1_SetAdcTrgConfig(TIMER1_ID_e eId, TIMER1_ADCTRG_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ TIMER1.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER1_SetIRQ(TIMER1_ID_e eId, TIMER1_OPS_e eOps, pfnTIMER1_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Start TIMER1.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER1_Start(TIMER1_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop TIMER1.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER1_Stop(TIMER1_ID_e eId);

/**
 *******************************************************************************
 * @brief       Get Interrupt Status TIMER1.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun32Status : ::TIMER1_INTR_FLAG_e (Bit Order).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER1_GetStatus(TIMER1_ID_e eId, uint32_t *pun32Status);

/**
 *******************************************************************************
 * @brief       Set Data TIMER1.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSel : Specific Data Type.
 * @param[in]   un32Data : Set Data to Specific Buffer by eSel.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER1_SetData(TIMER1_ID_e eId, TIMER1_DATA_e eSel, uint32_t un32Data);

/**
 *******************************************************************************
 * @brief       Get Data TIMER1.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSel : Specific Data Type.
 * @param[out]  *pun32Data : Get Data from Specific Buffer by eSel.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER1_GetData(TIMER1_ID_e eId, TIMER1_DATA_e eSel, uint32_t *pun32Data);

/* Only Support Fx series */
/**
 *******************************************************************************
 * @brief       Set to Pause TIMER1.
 *              some of ABOV chipsets are only supported.
 * @param[in]   eId : Instance Id.
 * @param[in]   bPause : true = pause, false = continue
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER1_SetPause(TIMER1_ID_e eId, bool bPause);

/**
 *******************************************************************************
 * @brief       Set to Synchro with TIMER3 TIMER1.
 *              some of ABOV chipsets are only supported.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : TIMER1 Synchro configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER1_SetT30Sync(TIMER1_ID_e eId, TIMER1_T30SYNC_CFG_t *ptCfg);

/* Only Support Vx series */
/**
 *******************************************************************************
 * @brief       Set Update Mode TIMER1.
 *              some of ABOV chipsets are only supported.
 * @param[in]   eId : Instance Id.
 * @param[in]   eUpdate : Update Mode.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER1_SetDataUpdateMode(TIMER1_ID_e eId, TIMER1_UPDATE_e eUpdate);

/**
 *******************************************************************************
 * @brief       Set Output Port Inversion TIMER1.
 *              some of ABOV chipsets are only supported.
 * @param[in]   eId : Instance Id.
 * @param[in]   eInv : Output Port Inversion.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER1_SetInversionPort(TIMER1_ID_e eId, TIMER1_INV_e eInv);

/**
 *******************************************************************************
 * @brief       Set Port IN/OUT TIMER1.
 *              some of ABOV chipsets are only supported.
 * @param[in]   eId : Instance Id.
 * @param[in]   ePort : Port IN/OUT.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER1_SetInOutPort(TIMER1_ID_e eId, TIMER1_PORT_e ePort);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_TIMER1_H_ */

/** @} */
/** @} */

