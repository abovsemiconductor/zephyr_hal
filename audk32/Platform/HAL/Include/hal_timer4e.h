/**
 *******************************************************************************
 * @file        hal_timer4e.h
 * @author      ABOV R&D Division
 * @brief       two output typed timer
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
 * @defgroup    HAL_TIMER4E TIMER4E
 * @{
 * @brief       16-bit Two-Output PWM channel Timer
 */

#ifndef _HAL_TIMER4E_H_
#define _HAL_TIMER4E_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief TIMER4E Instance Id
 */
typedef enum
{
    TIMER4E_ID_0,
    TIMER4E_ID_1,
    TIMER4E_ID_2,
    TIMER4E_ID_3,
    TIMER4E_ID_4,
    TIMER4E_ID_5,
    TIMER4E_ID_6,
    TIMER4E_ID_7,
    TIMER4E_ID_8,
    TIMER4E_ID_9,
    TIMER4E_ID_MAX
} TIMER4E_ID_e;

/**
 * @brief TIMER4E Mode
 */
typedef enum
{
    TIMER4E_MODE_INTERVAL,           /**< Interval Mode */
    TIMER4E_MODE_CAPTURE,            /**< Capture Mode */
    TIMER4E_MODE_BACK2BACK,          /**< Back to Back Mode */
    TIMER4E_MODE_ONESHOT_INTERVAL,   /**< One-Shot Interval Mode */
    TIMER4E_MODE_MAX
} TIMER4E_MODE_e;

/**
 * @brief TIMER4E Clock Source
 */
typedef enum
{
    TIMER4E_CLK_EXT,     /**< External Clock source */
    TIMER4E_CLK_PCLK,    /**< Peripheral Clock source */
    TIMER4E_CLK_MAX
} TIMER4E_CLK_e;

/**
 * @brief TIMER4E External Clock Input Edge
 */
typedef enum
{
    TIMER4E_EXTCLK_EDGE_FALLING,
    TIMER4E_EXTCLK_EDGE_RISING,
    TIMER4E_EXTCLK_EDGE_MAX
} TIMER4E_EXTCLK_EDGE_e;

/**
 * @brief TIMER4E Output Port Polarity
 */
typedef enum
{
    TIMER4E_POL_LOW,
    TIMER4E_POL_HIGH,
    TIMER4E_POL_MAX
} TIMER4E_POL_e;

/**
 * @brief TIMER4E Data Type
 */
typedef enum
{
    TIMER4E_DATA_P,       /**< Period Data */
    TIMER4E_DATA_A,       /**< A Data */
    TIMER4E_DATA_B,       /**< B Data */
    TIMER4E_DATA_CAP,     /**< Capture Data */
    TIMER4E_DATA_MAX
} TIMER4E_DATA_e;

/**
 * @brief TIMER4E Capture Counter Clear Edge
 */
typedef enum
{
    TIMER4E_CAP_CLR_RISING,     /**< Clear counter when rising edge detected */
    TIMER4E_CAP_CLR_FALLING,    /**< Clear counter when falling edge detected */
    TIMER4E_CAP_CLR_BOTH,       /**< Clear counter when both edge detected */
    TIMER4E_CAP_CLR_NONE,
    TIMER4E_CAP_CLR_MAX
} TIMER4E_CAP_CLR_e;

/**
 * @brief TIMER4E Delay Insertion Position Mode
 */
typedef enum
{
    TIMER4E_DLY_POS_AB,    /**< Front of A and Back of B */
    TIMER4E_DLY_POS_BA,    /**< Front of B and Back of A */
    TIMER4E_DLY_POS_MAX
} TIMER4E_DLY_POS_e;

/**
 * @brief TIMER4E Data Reload Mode
 */
typedef enum
{
    TIMER4E_RELOAD_INSTANT,         /**< Instantly Reload Buffer */
    TIMER4E_RELOAD_PERIOD_MATCH,    /**< After Period Match, Reload Buffer */
    TIMER4E_RELOAD_BOTTOM,          /**< After Bottom Reach, Reload Buffer */
    TIMER4E_RELOAD_MAX
} TIMER4E_RELOAD_e;

/**
 * @brief TIMER4E Interrupt Type
 */
typedef enum
{
    TIMER4E_INTR_NONE               = 0,
    TIMER4E_INTR_MATCH_CH_A_UP      = BIT(0),                /**< Match A up counting */
    TIMER4E_INTR_MATCH_CH_A_DOWN    = BIT(1),                /**< Match A down counting */
    TIMER4E_INTR_MATCH_CH_A_UP_DOWN = BIT(0) | BIT(1),       /**< Match A up/down counting */
    TIMER4E_INTR_MATCH_CH_B_UP      = BIT(2),                /**< Match B up counting */
    TIMER4E_INTR_MATCH_CH_B_DOWN    = BIT(3),                /**< Match B down counting */
    TIMER4E_INTR_MATCH_CH_B_UP_DOWN = BIT(2) | BIT(3),       /**< Match B up/down counting */
    TIMER4E_INTR_PERIOD_MATCH       = BIT(8),                /**< Period Match */
    TIMER4E_INTR_BOTTOM             = BIT(9),                /**< Reached Bottom */
    TIMER4E_INTR_CAPTURE            = BIT(10),               /**< Capture */
    TIMER4E_INTR_OUTPUT_FORCE       = BIT(11),               /**< Output Force */
    TIMER4E_INTR_MAX
} TIMER4E_INTR_e;

/**
 * @brief TIMER4E ADC Trigger Type
 */
typedef enum
{
    TIMER4E_ADCTRG_NONE               = 0,                     /**< Trigger Type None */
    TIMER4E_ADCTRG_MATCH_CH_A_UP      = BIT(0),                /**< Match A up counting */
    TIMER4E_ADCTRG_MATCH_CH_A_DOWN    = BIT(1),                /**< Match A down counting */
    TIMER4E_ADCTRG_MATCH_CH_A_UP_DOWN = BIT(0) | BIT(1),       /**< Match A up/down counting */
    TIMER4E_ADCTRG_MATCH_CH_B_UP      = BIT(2),                /**< Match B up counting */
    TIMER4E_ADCTRG_MATCH_CH_B_DOWN    = BIT(3),                /**< Match B down counting */
    TIMER4E_ADCTRG_MATCH_CH_B_UP_DOWN = BIT(2) | BIT(3),       /**< Match B up/down counting */
    TIMER4E_ADCTRG_PERIOD_MATCH       = BIT(8),                /**< Period Match */
    TIMER4E_ADCTRG_BOTTOM             = BIT(9),                /**< Reached Bottom */
    TIMER4E_ADCTRG_MAX
} TIMER4E_ADCTRG_e;

/**
 * @brief TIMER4E Event
 */
typedef enum
{
    TIMER4E_EVENT_NONE              = 0,
    TIMER4E_EVENT_MATCH_CH_A        = BIT(0),
    TIMER4E_EVENT_MATCH_CH_B        = BIT(1),
    TIMER4E_EVENT_PERIOD_MATCH      = BIT(2),
    TIMER4E_EVENT_BOTTOM            = BIT(3),
    TIMER4E_EVENT_CAPTURE           = BIT(4),
    TIMER4E_EVENT_OUTPUT_FORCE      = BIT(5),
    TIMER4E_EVENT_MAX,
} TIMER4E_EVENT_e;

/**
 * @brief TIMER4E Operation
 */
typedef enum
{
    TIMER4E_OPS_POLL,        /**< Operation Polling */
    TIMER4E_OPS_INTR,        /**< Operation Interrupt */
    TIMER4E_OPS_MAX
} TIMER4E_OPS_e;

/**
 * @brief TIMER4E Clock Configuration
 */
typedef struct
{
    TIMER4E_CLK_e                eClk;
    union 
    {
        TIMER4E_EXTCLK_EDGE_e    eExtClkEdge;    /**< When selecting External Clock Souce Input at eClk */
    } uSubClk;
    uint16_t                     un16PreScale;    /**< Pre-scaler (Post-Divider) after eClk selection */
} TIMER4E_CLK_CFG_t;

/**
 * @brief TIMER4E Output Delay Configuration
 */
typedef struct
{
    bool                 bEnable; 
    TIMER4E_DLY_POS_e    ePos;         /**< Delay Position */
    uint16_t             un16Value;    /**< Delay Value */
} TIMER4E_DELAY_CFG_t;

/**
 * @brief TIMER4E Output Port Configuration
 */
typedef struct
{
    bool             bEnable;          /**< Output Port Enable */
    TIMER4E_POL_e    eEnPol;           /**< Start Ouput Port Level when enabled */
    TIMER4E_POL_e    eDisPol;          /**< Output Port Level when disabled */
} TIMER4E_OUTPUT_CFG_t;

/**
 * @brief TIMER4E Outputs Port Configuration
 */
typedef struct
{
    TIMER4E_OUTPUT_CFG_t    tAPortCfg;    /**< Output Port A Configuration */
    TIMER4E_OUTPUT_CFG_t    tBPortCfg;    /**< Output Port B Configuration */
} TIMER4E_OUTPUTS_CFG_t;

/**
 * @brief TIMER4E ADC Trigger Configuration
 **/
typedef struct
{
    uint16_t                 un16Enable;     /**< ADC Trigger Signal Generator ::TIMER4E_ADCTRG_e (Bit Order) */
} TIMER4E_ADCTRG_CFG_t;

/**
 * @brief TIMER4E Counter synchronized with T4E others Configuration
 **/
typedef struct
{
    bool                 bEnable;
    TIMER4E_ID_e         eId;
} TIMER4E_SYNCNT_CFG_t;

/**
 * @brief TIMER4E Force Input Configuration
 **/
typedef struct
{
    bool                 bEnable;
    TIMER4E_ID_e         eId;
} TIMER4E_FRCINP_CFG_t;

/**
 * @brief TIMER4E Mode Configuration
 */
typedef struct
{
    TIMER4E_MODE_e            eMode;
    TIMER4E_CAP_CLR_e         eCapClr;           
    uint16_t                  un16IntrEnable;       /**< Interrupt Enable ::TIMER4E_INTR_e (Bit Order) */
    union
    {
        struct
        {
            uint16_t          un16DataP;            /**< Period Data */
            uint16_t          un16DataA;            /**< A Data */
            uint16_t          un16DataB;            /**< B Data */
        } tGRD;
    } utData;

    TIMER4E_RELOAD_e          eReload;
    TIMER4E_OUTPUTS_CFG_t     tOutputsCfg;
    TIMER4E_DELAY_CFG_t       tDlyCfg;
    TIMER4E_FRCINP_CFG_t      tFrcInpCfg;
    TIMER4E_SYNCNT_CFG_t      tSyncCnt;
} TIMER4E_CFG_t;

/**
 * @brief TIMER4E IRQ handler context
 */
typedef struct
{
    TIMER4E_ID_e eId;    /**< TIMER4E Instance Id */
} TIMER4E_Context_t;

/**
 *******************************************************************************
 * @brief       TIMER4E Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::TIMER4E_INTR_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnTIMER4E_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize TIMER4E.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4E_Init(TIMER4E_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize TIMER4E.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4E_Uninit(TIMER4E_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration TIMER4E.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClkCfg : TIMER4E Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4E_SetClkConfig(TIMER4E_ID_e eId, TIMER4E_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration TIMER4E.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : TIMER4E Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4E_SetConfig(TIMER4E_ID_e eId, TIMER4E_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set ADC Trigger Configuration TIMER4E.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : TIMER4E ADC Trigger Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4E_SetAdcTrgConfig(TIMER4E_ID_e eId, TIMER4E_ADCTRG_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ TIMER4E.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @param[in]   bNonMask : Enable non-maskable Interrupt.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4E_SetIRQ(TIMER4E_ID_e eId, TIMER4E_OPS_e eOps, pfnTIMER4E_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio, bool bNonMask);

/**
 *******************************************************************************
 * @brief       Set Output Port Enable TIMER4E.
 * @param[in]   eId : Instance Id.
 * @param[in]   TIMER4E_OUTPUTS_CFG_t : TIMER4E Output Port Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4E_SetOutputPort(TIMER4E_ID_e eId, TIMER4E_OUTPUTS_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Start TIMER4E.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4E_Start(TIMER4E_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop TIMER4E.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4E_Stop(TIMER4E_ID_e eId);

/**
 *******************************************************************************
 * @brief       Get Interrupt Status TIMER4E.
 * @param[in]   eId : Instance Id.
 * @param[out]  *pun32Status : ::TIMER4E_INTR_e (Bit Order).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4E_GetStatus(TIMER4E_ID_e eId, uint32_t *pun32Status);

/**
 *******************************************************************************
 * @brief       Set Data TIMER4E.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSel : Specific Data Type.
 * @param[in]   un32Data : Set Data to Specific Buffer by eSel.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4E_SetData(TIMER4E_ID_e eId, TIMER4E_DATA_e eSel, uint32_t un32Data);

/**
 *******************************************************************************
 * @brief       Get Data TIMER4E.
 * @param[in]   eId : Instance Id.
 * @param[in]   eSel : Specific Data Type.
 * @param[out]  *pun32Data : Get Data from Specific Buffer by eSel.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_TIMER4E_GetData(TIMER4E_ID_e eId, TIMER4E_DATA_e eSel, uint32_t *pun32Data);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_TIMER4E_H_ */

/** @} */
/** @} */

