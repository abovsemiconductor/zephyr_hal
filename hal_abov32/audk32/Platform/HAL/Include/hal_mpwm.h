/**
 *******************************************************************************
 * @file        hal_mpwm.h
 * @author      ABOV R&D Division
 * @brief       Motor Pulse Width Modulation (MPWM)
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
 * @defgroup    HAL_MPWM MPWM
 * @{
 * @brief       Motor Pulse Width Modulation (MPWM)
 */

#ifndef _HAL_MPWM_H_
#define _HAL_MPWM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief MPWM Instance Id
 */
typedef enum
{
    MPWM_ID_0,
    MPWM_ID_1,
    MPWM_ID_2,
    MPWM_ID_3,
    MPWM_ID_4,
    MPWM_ID_5,
    MPWM_ID_6,
    MPWM_ID_7,
    MPWM_ID_8,
    MPWM_ID_9,
    MPWM_ID_MAX
} MPWM_ID_e;

/**
 * @brief MPWM Signal
 */
typedef enum
{
    MPWM_SIG_PWM = BIT(0),     /**< Signal-U/V/W */
    MPWM_SIG_U   = BIT(1),     /**< Signal-U */
    MPWM_SIG_V   = BIT(2),     /**< Signal-V */
    MPWM_SIG_W   = BIT(3),     /**< Signal-W */
    MPWM_SIG_MAX
} MPWM_SIG_e;

/**
 * @brief MPWM Mode
 */
typedef enum
{
    MPWM_MODE_MOTOR,         /**< Motor Mode */
    MPWM_MODE_NORMAL,        /**< Normal Mode */
    MPWM_MODE_INDIVIDUAL,    /**< Individual Mode */
    MPWM_MODE_MAX
} MPWM_MODE_e;

/**
 * @brief MPWM Channel Mode
 */
typedef enum
{
    MPWM_CHANNEL_MODE_TWO_SYM,     /**< Two-channel symmetric Mode */
    MPWM_CHANNEL_MODE_ONE_ASYM,    /**< One-channel asymmetric Mode */
    MPWM_CHANNEL_MODE_ONE_SYM,     /**< One-channel symmetric Mode */
    MPWM_CHANNEL_MODE_MAX
} MPWM_CHANNEL_MODE_e;

/**
 * @brief MPWM Counter Mode
 */
typedef enum
{
    MPWM_COUNTER_MODE_UP,         /**< Up Counter Mode (only Normal Mode) */
    MPWM_COUNTER_MODE_UP_DOWN,    /**< Up-down Counder Mode */
    MPWM_COUNTER_MODE_MAX
} MPWM_COUNTER_MODE_e;

/**
 * @brief MPWM Stop Mode
 */
typedef enum
{
    MPWM_START_MODE_RECOUNT,    /**< Start and Re-counter from beginning */
    MPWM_START_MODE_RESUME,     /**< Start and Resume counter */
    MPWM_START_MODE_MAX
} MPWM_START_MODE_e;

/**
 * @brief MPWM Stop Mode
 */
typedef enum
{
    MPWM_STOP_MODE_CLEAR,      /**< Stop and clear counter */
    MPWM_STOP_MODE_REMAIN,     /**< Stop and remain counter */
    MPWM_STOP_MODE_RESET,      /**< Stop and reset counter */
    MPWM_STOP_MODE_DISABLE,    /**< Stop and disable */
    MPWM_STOP_MODE_MAX
} MPWM_STOP_MODE_e;

/**
 * @brief MPWM Clock Source
 */
typedef enum
{
    MPWM_CLK_MCCR,    /**< Misc Clock source ::MPWM_CLK_MCCR_e */
    MPWM_CLK_MAX
} MPWM_CLK_e;

/**
 * @brief MPWM MCCR (Misc Clock) Source
 */
typedef enum
{
    MPWM_CLK_MCCR_LSI,    /**< Low Speed Internal Clock source */
    MPWM_CLK_MCCR_LSE,    /**< Low Speed External Clock source */
    MPWM_CLK_MCCR_MCLK,   /**< Master Clock source */
    MPWM_CLK_MCCR_HSI,    /**< High Speed Internal Clock source */
    MPWM_CLK_MCCR_HSE,    /**< High Speed External Clock source */
    MPWM_CLK_MCCR_PLL,    /**< Phase-Locked Loop (PLL) Clock source */
    MPWM_CLK_MCCR_NONE,
    MPWM_CLK_MCCR_MAX
} MPWM_CLK_MCCR_e;

/**
 * @brief MPWM Output Port Polarity
 */
typedef enum
{
    MPWM_POL_LOW,
    MPWM_POL_HIGH,
    MPWM_POL_MAX
} MPWM_POL_e;

/**
 * @brief MPWM ADC Trigger Source
 */
typedef enum
{
    MPWM_ADCTRG_SRC_U,       /**< Adc Trigger Source U Counter */
    MPWM_ADCTRG_SRC_V,       /**< Adc Trigger Source V Counter */
    MPWM_ADCTRG_SRC_W,       /**< Adc Trigger Source W Counter */
    MPWM_ADCTRG_SRC_NONE,    /**< Adc Trigger Source Disable */
    MPWM_ADCTRG_SRC_MAX
} MPWM_ADCTRG_SRC_e;

/**
 * @brief MPWM ADC Trigger Mode
 */
typedef enum
{
    MPWM_ADCTRG_MODE_NONE,             /**< Adc Trigger Disable */
    MPWM_ADCTRG_MODE_MATCH_UP,         /**< Adc Triggered when Matched Up Count */
    MPWM_ADCTRG_MODE_MATCH_DOWN,       /**< Adc Triggered when Matched Down Count */
    MPWM_ADCTRG_MODE_MATCH_UP_DOWN,    /**< Adc Triggered when Matched Up-Down Count */
    MPWM_ADCTRG_MODE_MAX
} MPWM_ADCTRG_MODE_e;

/**
 * @brief MPWM Dead Time Mode
 */
typedef enum
{
    MPWM_DT_MODE_LEAD_H,    /**< Insert dead time at leading edge of PWMxH and trailling edge of PWMxL*/
    MPWM_DT_MODE_LEAD_L,    /**< Insert dead time at leading edge of PWMxL and trailling edge of PWMxH*/
    MPWM_DT_MODE_MAX
} MPWM_DT_MODE_e;

/**
 * @brief MPWM Dead Time Prescaler
 */
typedef enum
{
    MPWM_DT_PRESCALE_2,     /**< PWM CLK / 2 */
    MPWM_DT_PRESCALE_4,     /**< PWM CLK / 4 */
    MPWM_DT_PRESCALE_8,     /**< PWM CLK / 8 */
    MPWM_DT_PRESCALE_16,    /**< PWM CLK / 16 */
    MPWM_DT_PRESCALE_MAX
} MPWM_DT_PRESCALE_e;

/**
 * @brief MPWM Sub-capture edge mode
 */
typedef enum
{
    MPWM_SUBCAP_EDGE_MODE_RISING,     /**< Sub-capture rising edge */
    MPWM_SUBCAP_EDGE_MODE_FALLING,    /**< Sub-capture falling edge */
    MPWM_SUBCAP_EDGE_MODE_MAX,
} MPWM_SUBCAP_EDGE_MODE_e;

/**
 * @brief MPWM Interrupt Handler Type
 */
typedef enum
{
    MPWM_INTR_HDLR_PROTECTION,     /**< Protection Input handler */
    MPWM_INTR_HDLR_OVERVOLTAGE,    /**< Over Voltage Input handler */
    MPWM_INTR_HDLR_SIG_U,          /**< Signal U handler */
    MPWM_INTR_HDLR_SIG_V,          /**< Signal V handler */
    MPWM_INTR_HDLR_SIG_W,          /**< Signal W handler */
    MPWM_INTR_HDLR_PWM,            /**< PWM handler */
    MPWM_INTR_HDLR_MAX
} MPWM_INTR_HDLR_e;

/**
 * @brief MPWM Interrupt Type
 */
typedef enum
{
    MPWM_INTR_DUTY_UL_ATR1    = BIT(0),     /**< Matched Duty UL or ADC Trigger 1 */
    MPWM_INTR_DUTY_VL_ATR2    = BIT(1),     /**< Matched Duty VL or ADC Trigger 2 */
    MPWM_INTR_DUTY_WL_ATR3    = BIT(2),     /**< Matched Duty WL or ADC Trigger 3 */
    MPWM_INTR_DUTY_UH_ATR4    = BIT(3),     /**< Matched Duty UH or ADC Trigger 4 */
    MPWM_INTR_DUTY_VH_ATR5    = BIT(4),     /**< Matched Duty VH or ADC Trigger 5 */
    MPWM_INTR_DUTY_WH_ATR6    = BIT(5),     /**< Matched Duty WH or ADC Trigger 6 */
    MPWM_INTR_BOTTOM_PWM_U    = BIT(6),     /**< Matched Bottom U or Bottom(Motor/Normal PWM Mode) */
    MPWM_INTR_PERIOD_PWM_U    = BIT(7),     /**< Matched Period U or Period(Motor/Normal PWM Mode) */
    MPWM_INTR_BOTTOM_V        = BIT(8),     /**< Matched Bottom V */
    MPWM_INTR_PERIOD_V        = BIT(9),     /**< Matched Period V */
    MPWM_INTR_BOTTOM_W        = BIT(10),    /**< Matched Bottom W */
    MPWM_INTR_PERIOD_W        = BIT(11),    /**< Matched Period W */
    MPWM_INTR_MAX
} MPWM_INTR_e;

/**
 * @brief MPWM Event Type
 */
typedef enum
{
    MPWM_EVENT_DUTY_UL_ATR1    = BIT(0),     /**< Matched Duty UL or ADC Trigger 1 */
    MPWM_EVENT_DUTY_VL_ATR2    = BIT(1),     /**< Matched Duty VL or ADC Trigger 2 */
    MPWM_EVENT_DUTY_WL_ATR3    = BIT(2),     /**< Matched Duty WL or ADC Trigger 3 */
    MPWM_EVENT_DUTY_UH_ATR4    = BIT(3),     /**< Matched Duty UH or ADC Trigger 4 */
    MPWM_EVENT_DUTY_VH_ATR5    = BIT(4),     /**< Matched Duty VH or ADC Trigger 5 */
    MPWM_EVENT_DUTY_WH_ATR6    = BIT(5),     /**< Matched Duty WH or ADC Trigger 6 */
    MPWM_EVENT_BOTTOM_U        = BIT(6),     /**< Matched Bottom U */
    MPWM_EVENT_PERIOD_U        = BIT(7),     /**< Matched Period U */
    MPWM_EVENT_BOTTOM_V        = BIT(8),     /**< Matched Bottom V */
    MPWM_EVENT_PERIOD_V        = BIT(9),     /**< Matched Period V */
    MPWM_EVENT_BOTTOM_W        = BIT(10),    /**< Matched Bottom W */
    MPWM_EVENT_PERIOD_W        = BIT(11),    /**< Matched Period W */
    MPWM_EVENT_MAX
} MPWM_EVENT_e;

/**
 * @brief MPWM Protection Event Type
 */
typedef enum
{
    MPWM_EVENT_PROT_UL    = BIT(0),     /**< Protection U's L-side */
    MPWM_EVENT_PROT_VL    = BIT(1),     /**< Protection V's L-side */
    MPWM_EVENT_PROT_WL    = BIT(2),     /**< Protection W's L-side */
    MPWM_EVENT_PROT_UH    = BIT(3),     /**< Protection U's H-side */
    MPWM_EVENT_PROT_VH    = BIT(4),     /**< Protection V's H-side */
    MPWM_EVENT_PROT_WH    = BIT(5),     /**< Protection W's H-side */
    MPWM_EVENT_PROT_MAX
} MPWM_EVENT_PROT_e;

/**
 * @brief MPWM Over Voltage Event Type
 */
typedef enum
{
    MPWM_EVENT_OV_UL    = BIT(0),     /**< Over Voltage U's L-side */
    MPWM_EVENT_OV_VL    = BIT(1),     /**< Over Voltage V's L-side */
    MPWM_EVENT_OV_WL    = BIT(2),     /**< Over Voltage W's L-side */
    MPWM_EVENT_OV_UH    = BIT(3),     /**< Over Voltage U's H-side */
    MPWM_EVENT_OV_VH    = BIT(4),     /**< Over Voltage V's H-side */
    MPWM_EVENT_OV_WH    = BIT(5),     /**< Over Voltage W's H-side */
    MPWM_EVENT_OV_MAX
} MPWM_EVENT_OV_e;

/**
 * @brief MPWM Operation
 */
typedef enum
{
    MPWM_OPS_POLL,    /**< Operation Polling */
    MPWM_OPS_INTR,    /**< Operation Interrupt */
    MPWM_OPS_NMI,     /**< Operation NMI */
    MPWM_OPS_MAX
} MPWM_OPS_e;

/**
 * @brief MPWM Clock Configuration
 */
typedef struct
{
    MPWM_CLK_e         eClk;
    MPWM_CLK_MCCR_e    eMccr;         /**< When selecting MCCR at eClk */
    uint8_t            un8MccrDiv;    /**< When selecting MCCR at eClk */
} MPWM_CLK_CFG_t;

/**
 * @brief MPWM Port Level Configuration
 */
typedef struct
{
    MPWM_POL_e    eOutLevel;      /**< Output Level when PWMx is set disabled */
    MPWM_POL_e    eStartLevel;    /**< Output Level at the start of PWMx */
    MPWM_POL_e    eForceLevel;    /**< Forcibly Output Level */
} MPWM_PORT_CFG_t;

/**
 * @brief MPWM Alert Configuration
 */
typedef struct
{
    bool          bEnable;             /**< Protection / Overvoltage Detection Enable */
    MPWM_POL_e    eInPolarity;         /**< Protection / Overvoltage input Polarity */
    uint8_t       un8Debounce;         /**< Debounce Time (MPWMCLK * un8Debounce) */
    bool          bIntrEnable;         /**< Interrupt Enable */
    bool          bHLevelOutEnable;    /**< Enable H-side Preset Level Output forcibly when event is occurred */
    bool          bLLevelOutEnable;    /**< Enable L-side Preset Level Output forcibly when event is occurred */
} MPWM_ALERT_CFG_t;

/**
 * @brief MPWM Signal Port
 */
typedef struct
{
    MPWM_PORT_CFG_t    tHPort;    /**< H-Port */
    MPWM_PORT_CFG_t    tLPort;    /**< L-Port */
} MPWM_SP_CFG_t;

/**
 * @brief MPWM Signal Duty
 */
typedef struct
{
    uint16_t    un16HDuty;    /**< H-Duty */
    uint16_t    un16LDuty;    /**< L-Duty */
} MPWM_SD_CFG_t;

/**
 * @brief MPWM Signal Duty and Port
 */
typedef struct
{
    MPWM_SP_CFG_t    tSPCfg;    /**< High/Low Port */
    MPWM_SD_CFG_t    tSDCfg;    /**< High/Low Duty */
} MPWM_SDP_CFG_t;

/**
 * @brief MPWM Dead Time Configuration
 */
typedef struct
{
    bool                  bEnable;           /**< Enable Dead Time */
    MPWM_DT_MODE_e        eMode;             /**< Mode ::MPWM_DT_MODE_e */
    bool                  bSCPDisable;       /**< Disable short-circuit protection */
    MPWM_DT_PRESCALE_e    ePreScale;         /**< Prescale ::MPWM_DT_PRESCALE_e */
    uint8_t               un8EdgeDTValue;    /**< Falling or Rising Dead Time value */
} MPWM_DT_CFG_t;

/**
 * @brief MPWM Capture Counter Configuration
 */
typedef struct
{
    bool                       bEnable;      /**< Enable Capture Counter */
    MPWM_SUBCAP_EDGE_MODE_e    eEdgeMode;    /**< Sub-Capture Edge Mode */
} MPWM_CAP_CFG_t;

/**
 * @brief MPWM ADC Trigger Configuration
 **/
typedef struct
{
    uint8_t               un8Idx;         /**< ADC Trigger Block Number */
    MPWM_ADCTRG_SRC_e     eSrc;           /**< ADC Trigger Source */
    MPWM_ADCTRG_MODE_e    eMode;          /**< ADC Trigger Mode */
    bool                  bIntrEnable;    /**< ADC Trigger Interrupt Enable */
    bool                  bTrgUpdate;     /**< ADC Trigger Update Mode (false : after update match event, true : after two PWM clock) */
    uint16_t              un16GenData;    /**< ADC Trigger Generation Counter */
} MPWM_ADCTRG_CFG_t;

/**
 * @brief MPWM Individual Signal Configuration
 */
typedef struct
{
    uint16_t            un16Period;        /**< Signal Period */
    uint32_t            un32IntrEnable;    /**< Interrupt Enable ::MPWM_INTR_e */
    MPWM_SDP_CFG_t      tSDPCfg;           /**< Signal High/Low Duty and Port */
    MPWM_DT_CFG_t       tDTCfg;            /**< Signal Dead Time Configuration */
    MPWM_ALERT_CFG_t    tProtCfg;          /**< Signal Protection Input Configuration */
    MPWM_ALERT_CFG_t    tOVCfg;            /**< Signal Overvoltage Input Configuration */
    MPWM_CAP_CFG_t      tCapCfg;           /**< Signal Capture Configuration */
} MPWM_INDIV_SIG_CFG_t;

/**
 * @brief MPWM General Mode Configuration
 */
typedef struct
{
    MPWM_MODE_e            eMode;
    MPWM_CHANNEL_MODE_e    eChannelMode;
    MPWM_COUNTER_MODE_e    eCounterMode;
    bool                   bPeriodMatch;    /**< Update Period and Duty at every period match */
    bool                   bBottomMatch;    /**< Update Period and Duty at every bottom match */
} MPWM_CFG_t;

/**
 * @brief MPWM Motor/Normal PWM Mode Configuration
 */
typedef struct
{
    uint16_t           un16Period;        /**< Period */
    uint32_t           un32IntrEnable;    /**< Interrupt Enable ::MPWM_INTR_e */
    MPWM_SDP_CFG_t     tUSDPCfg;          /**< Signal U High/Low Duty and Port */
    MPWM_SDP_CFG_t     tVSDPCfg;          /**< Signal V High/Low Duty and Port */
    MPWM_SDP_CFG_t     tWSDPCfg;          /**< Signal W High/Low Duty and Port */
    MPWM_DT_CFG_t      tDTCfg;            /**< Dead Time Configuration */
    MPWM_ALERT_CFG_t   tProtCfg;          /**< Protection Input Configuration */
    MPWM_ALERT_CFG_t   tOVCfg;            /**< Overvoltage Input Configuration */
} MPWM_PWM_CFG_t;

/**
 * @brief MPWM Individual PWM Mode Configuration
 */
typedef struct
{
    MPWM_INDIV_SIG_CFG_t    tUCfg;    /**< Signal-U Configuration */
    MPWM_INDIV_SIG_CFG_t    tVCfg;    /**< Signal-V Configuration */
    MPWM_INDIV_SIG_CFG_t    tWCfg;    /**< Signal-W Configuration */
} MPWM_INDIV_CFG_t;

/**
 * @brief MPWM IRQ handler context
 */
typedef struct
{
    MPWM_ID_e eId;    /**< MPWM Instance Id */
} MPWM_Context_t;

/**
 *******************************************************************************
 * @brief       MPWM Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::MPWM_EVENT_e ::MPWM_EVENT_PROT_e ::MPWM_EVENT_OV_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnMPWM_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize MPWM.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_Init(MPWM_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize MPWM.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_Uninit(MPWM_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration MPWM.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClkCfg : MPWM Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_SetClkConfig(MPWM_ID_e eId, MPWM_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration MPWM.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : MPWM Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_SetConfig(MPWM_ID_e eId, MPWM_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set Motor/Normal or Individual Mode Configuration MPWM.
 * @param[in]   eId : Instance Id.
 * @param[in]   eMode : Motor/Normal/Individual Mode.
 * @param[in]   *ptCfg : MPWM Motor/Normal (::MPWM_PWM_CFG_t) or Individual (::MPWM_INDIV_CFG_t)
 *                       Mode Configuration by eMode.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_SetModeConfig(MPWM_ID_e eId, MPWM_MODE_e eMode, void *ptCfg);

/**
 *******************************************************************************
 * @brief       Set Dead Time Configuration MPWM.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSig : Signal U or V or W or ALL(Motor/Normal PWM)
 * @param[in]   *ptCfg : MPWM Dead Time Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_SetDTConfig(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_DT_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set Protection Input Configuration MPWM.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSig : Signal U or V or W or ALL(Motor/Normal PWM)
 * @param[in]   *ptCfg : MPWM Protection Input Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_SetProtConfig(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_ALERT_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set Over Voltage Input Configuration MPWM.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSig : Signal U or V or W or ALL(Motor/Normal PWM)
 * @param[in]   *ptCfg : MPWM Over Voltage Input Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_SetOVConfig(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_ALERT_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set Capture Configuration MPWM.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSig : Signal U or V or W or ALL(Motor/Normal PWM)
 * @param[out]  *ptCfg : Capture Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_SetCapConfig(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_CAP_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set ADC Trigger Configuration MPWM.
 * @param[in]   eId : Instance Id.
 * @param[out]  *ptCfg : ADC Trigger Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_SetAdcTrgConfig(MPWM_ID_e eId, MPWM_ADCTRG_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ MPWM.
 * @param[in]   eId : Instance Id.
 * @param[in]   eHdlr : Interrupt Handler Type
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_SetIRQ(MPWM_ID_e eId, MPWM_INTR_HDLR_e eHdlr, MPWM_OPS_e eOps, pfnMPWM_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio);
/**
 *******************************************************************************
 * @brief       Start MPWM.
 * @param[in]   eId : Instance Id.
 * @param[in]   eMode : Motor/Normal/Individual Mode.
 * @param[in]   eStartMode : Start Mode ::MPWM_START_MODE_e
 * @param[in]   un8Sig : Signal U and V and W or ALL(Motor/Normal PWM) ::MPWM_SIG_e (bit-Order)
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_Start(MPWM_ID_e eId, MPWM_MODE_e eMode, MPWM_START_MODE_e eStartMode, uint8_t un8Sig);

/**
 *******************************************************************************
 * @brief       Stop MPWM.
 * @param[in]   eId : Instance Id.
 * @param[in]   eMode : Motor/Normal/Individual Mode.
 * @param[in]   eStopMode : Stop Mode ::MPWM_STOP_MODE_e
 * @param[in]   un8Sig : Signal U and V and W or ALL(Motor/Normal PWM) ::MPWM_SIG_e (bit-Order)
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_Stop(MPWM_ID_e eId, MPWM_MODE_e eMode, MPWM_STOP_MODE_e eStopMode, uint8_t un8Sig);

/**
 *******************************************************************************
 * @brief       Set Duty MPWM.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSig : Signal U or V or W
 * @param[in]   *ptCfg : High / Low Duty configuration
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_SetDuty(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_SD_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set Port Output MPWM.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSig : Signal U or V or W
 * @param[in]   *ptCfg : High / Low Port Output configuration
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_SetPort(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_SP_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set Period MPWM.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSig : Signal U or V or W or ALL(Motor/Normal PWM)
 * @param[in]   un16Period : Period value.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_SetPeriod(MPWM_ID_e eId, MPWM_SIG_e eSig, uint16_t un16Period);

/**
 *******************************************************************************
 * @brief       Set Interrupt Interval MPWM.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSig : Signal U or V or W or ALL(Motor/Normal PWM)
 * @param[in]   un8Interval : Interval value.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_SetInterval(MPWM_ID_e eId, MPWM_SIG_e eSig, uint8_t un8Interval);

/**
 *******************************************************************************
 * @brief       Get Interrupt Status MPWM.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun32Status : ::MPWM_INTR_e (Bit Order).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_GetStatus(MPWM_ID_e eId, uint32_t *pun32Status);

/**
 *******************************************************************************
 * @brief       Get Count MPWM.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun32Count : current counter value.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_GetCount(MPWM_ID_e eId, uint32_t *pun32Count);

/**
 *******************************************************************************
 * @brief       Get Capture Count MPWM.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSig : Signal U or V or W or ALL(Motor/Normal PWM)
 * @param[out]  *pun32Count : current counter value.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_MPWM_GetCaptureCount(MPWM_ID_e eId, MPWM_SIG_e eSig, uint32_t *pun32Count);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_MPWM_H_ */

/** @} */
/** @} */

