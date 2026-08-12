/**
 *******************************************************************************
 * @file        hal_timer3.h
 * @author      ABOV R&D Division
 * @brief       3N typed timer
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
 * @defgroup    HAL_TIMER3 TIMER3
 * @{
 * @brief       16-bit Multi-PWM channel Timer
 */

#ifndef _HAL_TIMER3_H_
#define _HAL_TIMER3_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief TIMER3 Instance Id
 */
typedef enum
{
    TIMER3_ID_0,
    TIMER3_ID_1,
    TIMER3_ID_2,
    TIMER3_ID_3,
    TIMER3_ID_4,
    TIMER3_ID_5,
    TIMER3_ID_6,
    TIMER3_ID_7,
    TIMER3_ID_8,
    TIMER3_ID_9,
    TIMER3_ID_MAX
} TIMER3_ID_e;

/**
 * @brief TIMER3 Mode
 */
typedef enum
{
    TIMER3_MODE_INTERVAL,    /**< Interval Mode */
    TIMER3_MODE_CAPTURE,     /**< Capture Mode */
    TIMER3_MODE_BACK2BACK,   /**< Back to Back Mode */
    TIMER3_MODE_MAX
} TIMER3_MODE_e;

/**
 * @brief TIMER3 Clock Source
 */
typedef enum
{
    TIMER3_CLK_MCCR,    /**< Misc Clock source ::TIMER3_CLK_MCCR_e */
    TIMER3_CLK_EXT,     /**< External Clock source input */
    TIMER3_CLK_PCLK,    /**< Peripheral Clock source */
    TIMER3_CLK_MAX
} TIMER3_CLK_e;

/**
 * @brief TIMER3 MCCR (Misc Clock) Source
 */
typedef enum
{
    TIMER3_CLK_MCCR_LSI,    /**< Low Speed Internal Clock source */
    TIMER3_CLK_MCCR_LSE,    /**< Low Speed External Clock source */
    TIMER3_CLK_MCCR_MCLK,   /**< Master Clock source */
    TIMER3_CLK_MCCR_HSI,    /**< High Speed Internal Clock source */
    TIMER3_CLK_MCCR_HSE,    /**< High Speed External Clock source */
    TIMER3_CLK_MCCR_PLL,    /**< Phase-Locked Loop (PLL) Clock source */
    TIMER3_CLK_MCCR_NONE,
    TIMER3_CLK_MCCR_MAX
} TIMER3_CLK_MCCR_e;

/**
 * @brief TIMER3 External Clock Input Edge
 */
typedef enum
{
    TIMER3_EXTCLK_EDGE_FALLING,
    TIMER3_EXTCLK_EDGE_RISING,
    TIMER3_EXTCLK_EDGE_MAX
} TIMER3_EXTCLK_EDGE_e;

/**
 * @brief TIMER3 Output Port Polarity
 */
typedef enum
{
    TIMER3_POL_LOW,
    TIMER3_POL_HIGH,
    TIMER3_POL_MAX
} TIMER3_POL_e;

/**
 * @brief TIMER3 Data Type
 */
typedef enum
{
    TIMER3_DATA_P,       /**< Period Data */
    TIMER3_DATA_A,       /**< A Data */
    TIMER3_DATA_B,       /**< B Data */
    TIMER3_DATA_C,       /**< C Data */
    TIMER3_DATA_CAP,     /**< Capture Data */
    TIMER3_DATA_ADC,     /**< ADC Trigger Generator Data */
    TIMER3_DATA_MAX
} TIMER3_DATA_e;

/**
 * @brief TIMER3 Capture Counter Clear Edge
 */
typedef enum
{
    TIMER3_CAP_CLR_RISING,     /**< Clear counter when rising edge detected */
    TIMER3_CAP_CLR_FALLING,    /**< Clear counter when falling edge detected */
    TIMER3_CAP_CLR_BOTH,       /**< Clear counter when both edge detected */
    TIMER3_CAP_CLR_NONE,
    TIMER3_CAP_CLR_MAX
} TIMER3_CAP_CLR_e;

/**
 * @brief TIMER3 Output Port
 */ 
typedef enum
{
    TIMER3_PORT_OUT_NONE  = 0, 
    TIMER3_PORT_OUT_CA    = BIT(0),    /**< C Data A Port */
    TIMER3_PORT_OUT_BA    = BIT(1),    /**< B Data A Port */
    TIMER3_PORT_OUT_AA    = BIT(2),    /**< A Data A Port */
    TIMER3_PORT_OUT_CB    = BIT(3),    /**< C Data B Port */
    TIMER3_PORT_OUT_BB    = BIT(4),    /**< B Data B Port */
    TIMER3_PORT_OUT_AB    = BIT(5),    /**< A Data B Port */
    TIMER3_PORT_OUT_MAX
} TIMER3_PORT_OUT_e;

/**
 * @brief TIMER3 Delay Insertion Position Mode
 */
typedef enum
{
    TIMER3_DLY_POS_XAXB,    /**< Front of xA and Back of xB */
    TIMER3_DLY_POS_XBXA,    /**< Front of xB and Back of xA */
    TIMER3_DLY_POS_MAX
} TIMER3_DLY_POS_e;

/**
 * @brief TIMER3 Ouput Mode 
 */
typedef enum
{
    TIMER3_OUT_MODE_6CH,    /**< 6-channel Output from xDR */
    TIMER3_OUT_MODE_ACH,    /**< A-channel Output from ADR */
    TIMER3_OUT_MODE_MAX
} TIMER3_OUT_MODE_e;

/**
 * @brief TIMER3 Data Reload Mode
 */
typedef enum
{
    TIMER3_RELOAD_INSTANT,         /**< Instantly Reload Buffer */
    TIMER3_RELOAD_PERIOD_MATCH,    /**< After Period Match, Reload Buffer */
    TIMER3_RELOAD_BOTTOM,          /**< After Bottom Reach, Reload Buffer */
    TIMER3_RELOAD_MAX
} TIMER3_RELOAD_e;

/**
 * @brief TIMER3 High-Impedance Edge Mode
 */
typedef enum
{
    TIMER3_HIZ_EDGE_FALLING,    /**< Falling Edge of BLNK pin */
    TIMER3_HIZ_EDGE_RISING,     /**< Rising Edge of BLNK pin */
    TIMER3_HIZ_EDGE_MAX,
} TIMER3_HIZ_EDGE_e;

/**
 * @brief TIMER3 High-Impedance Input Source
 */
typedef enum
{
    TIMER3_HIZ_SRC_EXT,        /**< External Sync Signal Input (BLNK pin) */
    TIMER3_HIZ_SRC_TIMER40,    /**< Internal Timer40 Output */
    TIMER3_HIZ_SRC_MAX,
} TIMER3_HIZ_SRC_e;

/**
 * @brief TIMER3 Interrupt Type
 */
typedef enum
{
    TIMER3_INTR_NONE            = 0,
    TIMER3_INTR_MATCH_CH_C      = BIT(0),    /**< Matched Data C */
    TIMER3_INTR_MATCH_CH_B      = BIT(1),    /**< Matched Data B */
    TIMER3_INTR_MATCH_CH_A      = BIT(2),    /**< Matched Data A */
    TIMER3_INTR_PERIOD_MATCH    = BIT(3),    /**< Period Match */
    TIMER3_INTR_BOTTOM          = BIT(4),    /**< Reached Bottom */
    TIMER3_INTR_CAPTURE         = BIT(5),    /**< Capture */
    TIMER3_INTR_HIZ             = BIT(6),    /**< High-Impedence */
    TIMER3_INTR_MAX
} TIMER3_INTR_e;

/**
 * @brief TIMER3 ADC Trigger Type
 */
typedef enum
{
    TIMER3_ADCTRG_NONE            = 0,
    TIMER3_ADCTRG_MATCH_CH_C      = BIT(0),    /**< Adc Triggered when Matched Data C */
    TIMER3_ADCTRG_MATCH_CH_B      = BIT(1),    /**< Adc Triggered when Matched Data B */
    TIMER3_ADCTRG_MATCH_CH_A      = BIT(2),    /**< Adc Triggered when Matched Data A */
    TIMER3_ADCTRG_PERIOD_MATCH    = BIT(3),    /**< Adc Triggered when Period Match */
    TIMER3_ADCTRG_BOTTOM          = BIT(4),    /**< Adc Triggered when Reached Bottom */
    TIMER3_ADCTRG_MAX
} TIMER3_ADCTRG_e;

/**
 * @brief TIMER3 Operation
 */
typedef enum
{
    TIMER3_OPS_POLL,        /**< Operation Polling */
    TIMER3_OPS_INTR,        /**< Operation Interrupt */
    TIMER3_OPS_MAX
} TIMER3_OPS_e;

/**
 * @brief TIMER3 Clock Configuration
 */
typedef struct
{
    TIMER3_CLK_e                eClk;
    union 
    {
        TIMER3_EXTCLK_EDGE_e    eExtClkEdge;    /**< When selecting External Clock Souce Input at eClk */
        TIMER3_CLK_MCCR_e       eMccr;          /**< When selecting MCCR at eClk */
    } uSubClk;
    uint8_t                     un8MccrDiv;      /**< When selecting MCCR at eClk */
    uint16_t                    un16PreScale;    /**< Pre-scaler (Post-Divider) after eClk selection */
} TIMER3_CLK_CFG_t;

/**
 * @brief TIMER3 Output Delay Configuration
 */
typedef struct
{
    bool                 bEnable; 
    TIMER3_DLY_POS_e     ePos;         /**< Delay Position */
    uint16_t             un16Value;    /**< Delay Value */
} TIMER3_DELAY_CFG_t;

/**
 * @brief TIMER3 Output Port Configuration
 */
typedef struct
{
    TIMER3_POL_e         eXAPol;            /**< xA Output Port Polarity */
    TIMER3_POL_e         eXBPol;            /**< xB Output Port Polarity */
    TIMER3_OUT_MODE_e    eOutputMode;

    bool                 bHizEnable;        /**< High Impedance Enable */
    TIMER3_HIZ_EDGE_e    eHizEdge;          /**< High Impedance Edge pin */
    TIMER3_HIZ_SRC_e     eHizSrc;           /**< High Impedance Input Source */
} TIMER3_OUTPUT_CFG_t;

/**
 * @brief TIMER3 ADC Trigger Configuration
 **/
typedef struct
{
    uint16_t                 un16GenData;   /**< ADC Trigger Generation Counter */
    uint8_t                  un8Enable;     /**< ADC Trigger Signal Generator ::TIMER3_ADCTRG_e (Bit Order) */
} TIMER3_ADCTRG_CFG_t;

/**
 * @brief TIMER3 Mode Configuration
 */
typedef struct
{
    TIMER3_MODE_e            eMode;
    TIMER3_CAP_CLR_e         eCapClr;           
    uint8_t                  un8IntrEnable;       /**< Interrupt Enable ::TIMER3_INTR_e (Bit Order) */
    union
    {
        struct
        {
            uint16_t         un16DataP;            /**< Period Data */
            uint16_t         un16DataA;            /**< A Data */
            uint16_t         un16DataB;            /**< B Data */
            uint16_t         un16DataC;            /**< C Data */
        } tGRD;
    } utData;
    TIMER3_RELOAD_e          eReload;
    uint8_t                  un8PeriodMatchCnt;    /**< Period Match Count Value */
    TIMER3_OUTPUT_CFG_t      tOutputCfg;
    TIMER3_DELAY_CFG_t       tDlyCfg;
} TIMER3_CFG_t;

/**
 * @brief TIMER3 IRQ handler context
 */
typedef struct
{
    TIMER3_ID_e eId;    /**< TIMER3 Instance Id */
} TIMER3_Context_t;

/**
 *******************************************************************************
 * @brief       TIMER3 Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::TIMER3_INTR_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnTIMER3_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize TIMER3.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER3_Init(TIMER3_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize TIMER3.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER3_Uninit(TIMER3_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration TIMER3.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClkCfg : TIMER3 Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER3_SetClkConfig(TIMER3_ID_e eId, TIMER3_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration TIMER3.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : TIMER3 Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER3_SetConfig(TIMER3_ID_e eId, TIMER3_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set ADC Trigger Configuration TIMER3.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : TIMER3 ADC Trigger Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER3_SetAdcTrgConfig(TIMER3_ID_e eId, TIMER3_ADCTRG_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ TIMER3.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @param[in]   bNonMask : Enable non-maskable Interrupt.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER3_SetIRQ(TIMER3_ID_e eId, TIMER3_OPS_e eOps, pfnTIMER3_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio, bool bNonMask);

/**
 *******************************************************************************
 * @brief       Set Output Port Enable TIMER3.
 * @param[in]   eId : Instance Id.
 * @param[in]   un8PortEnable : Enabled by ::TIMER3_PORT_OUT_e (Bit Order).
 * @param[in]   un8PortLevel : When disabled x Port Output, Set x Port Level by ::TIMER3_PORT_OUT_e \n
 *              (Bit Order : 0 = Low, 1 = High).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER3_SetOutputPort(TIMER3_ID_e eId, uint8_t un8PortEnable, uint8_t un8PortLevel);

/**
 *******************************************************************************
 * @brief       Start TIMER3.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER3_Start(TIMER3_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop TIMER3.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER3_Stop(TIMER3_ID_e eId);

/**
 *******************************************************************************
 * @brief       Get Interrupt Status TIMER3.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun32Status : ::TIMER3_INTR_e (Bit Order).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER3_GetStatus(TIMER3_ID_e eId, uint32_t *pun32Status);

/**
 *******************************************************************************
 * @brief       Set Data TIMER3.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSel : Specific Data Type.
 * @param[in]   un32Data : Set Data to Specific Buffer by eSel.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER3_SetData(TIMER3_ID_e eId, TIMER3_DATA_e eSel, uint32_t un32Data);

/**
 *******************************************************************************
 * @brief       Get Data TIMER3.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSel : Specific Data Type.
 * @param[out]  *pun32Data : Get Data from Specific Buffer by eSel.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER3_GetData(TIMER3_ID_e eId, TIMER3_DATA_e eSel, uint32_t *pun32Data);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_TIMER3_H_ */

/** @} */
/** @} */

