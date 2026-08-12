/**
 *******************************************************************************
 * @file        hal_adc.h
 * @author      ABOV R&D Division
 * @brief       N-bits Analog to Digital Converter
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
 * @defgroup    HAL_ADC ADC
 * @{
 * @brief       N-bits Analog to Digital Converter
 */

#ifndef _HAL_ADC_H_
#define _HAL_ADC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief ADC Instance Id
 */
typedef enum
{
    ADC_ID_0,
    ADC_ID_1,
    ADC_ID_2,
    ADC_ID_3,
    ADC_ID_4,
    ADC_ID_5,
    ADC_ID_6,
    ADC_ID_7,
    ADC_ID_8,
    ADC_ID_9,
    ADC_ID_MAX
} ADC_ID_e;

/**
 * @brief ADC Mode
 */
typedef enum
{
    ADC_MODE_SINGLE,      /**< Single Mode */
    ADC_MODE_SEQ,         /**< Sequence Mode */
    ADC_MODE_BURST,       /**< Burst Mode */
    ADC_MODE_MULTIPLE,    /**< Multiple Mode */
    ADC_MODE_CONTINUOUS,  /**< Continuous Mode */
    ADC_MODE_MAX
} ADC_MODE_e;

/**
 * @brief ADC Clock Source
 */
typedef enum
{
    ADC_CLK_PCLK,    /**< Peripheral Clock source */
    ADC_CLK_MCCR,    /**< Misc Clock source ::ADC_CLK_MCCR_e */
    ADC_CLK_HCLK,    /**< System Clock source */
    ADC_CLK_MAX
} ADC_CLK_e;

/**
 * @brief ADC MCCR (Misc Clock) Source
 */
typedef enum
{
    ADC_CLK_MCCR_LSI,    /**< Low Speed Internal Clock source */
    ADC_CLK_MCCR_LSE,    /**< Low Speed External Clock source */
    ADC_CLK_MCCR_MCLK,   /**< Master Clock source */
    ADC_CLK_MCCR_HSI,    /**< High Speed Internal Clock source */
    ADC_CLK_MCCR_HSE,    /**< High Speed External Clock source */
    ADC_CLK_MCCR_PLL,    /**< Phase-Locked Loop (PLL) Clock source */
    ADC_CLK_MCCR_MAX
} ADC_CLK_MCCR_e;

/**
 * @brief ADC Reference Source
 */
typedef enum
{
    ADC_REF_INT,    /**< Internal AVDD */
    ADC_REF_EXT,    /**< External Reference */
    ADC_REF_MAX
} ADC_REF_e;

/**
 * @brief ADC Trigger Type
 */
typedef enum
{
    ADC_TRG_TYPE_SINGLE,
    ADC_TRG_TYPE_SHARE,
    ADC_TRG_TYPE_INDEPENDENT,
    ADC_TRG_TYPE_MAX
} ADC_TRG_TYPE_e;

/**
 * @brief ADC Start Trigger Source
 */
typedef enum
{
    ADC_TRG_SRC_ADST,     /**< A/DC Conversion Start bit */
    ADC_TRG_SRC_TIMER1,   /**< Timer1 Trigger signal */
    ADC_TRG_SRC_TIMER2,   /**< Timer2 Trigger signal */
    ADC_TRG_SRC_TIMER3,   /**< Timer3 Trigger signal */
    ADC_TRG_SRC_TIMER4,   /**< Timer4 Trigger signal */
    ADC_TRG_SRC_TIMER4E = ADC_TRG_SRC_TIMER4, /**< Timer4E Trigger signal */
    ADC_TRG_SRC_MPWM0,    /**< MPWM0 Trigger signal */
    ADC_TRG_SRC_MPWM1,    /**< MPWM1 Trigger signal */
    ADC_TRG_SRC_EXT,      /**< External Trigger signal */
    ADC_TRG_SRC_NONE,     /**< Disable Trigger source */
    ADC_TRG_SRC_MAX
} ADC_TRG_SRC_e;

/**
 * @brief ADC External Trigger Edge
 */
typedef enum
{
    ADC_EXT_TRG_EDGE_NONE,    /**< Disable External Trigger */
    ADC_EXT_TRG_EDGE_FALL,    /**< Falling Edge Trigger */
    ADC_EXT_TRG_EDGE_RISE,    /**< Rising Edge Trigger */
    ADC_EXT_TRG_EDGE_BOTH,    /**< Falling and Rising Edge Trigger */
    ADC_EXT_TRG_EDGE_MAX
} ADC_EXT_TRG_EDGE_e;

/**
 * @brief ADC Channel Input Number (bit)
 */
typedef enum
{
    ADC_CH_IN_NONE = 0,
    ADC_CH_IN_0 = BIT(0),
    ADC_CH_IN_1 = BIT(1),
    ADC_CH_IN_2 = BIT(2),
    ADC_CH_IN_3 = BIT(3),
    ADC_CH_IN_4 = BIT(4),
    ADC_CH_IN_5 = BIT(5),
    ADC_CH_IN_6 = BIT(6),
    ADC_CH_IN_7 = BIT(7),
    ADC_CH_IN_8 = BIT(8),
    ADC_CH_IN_9 = BIT(9),
    ADC_CH_IN_10 = BIT(10),
    ADC_CH_IN_11 = BIT(11),
    ADC_CH_IN_12 = BIT(12),
    ADC_CH_IN_13 = BIT(13),
    ADC_CH_IN_14 = BIT(14),
    ADC_CH_IN_15 = BIT(15),
    ADC_CH_IN_16 = BIT(16),
    ADC_CH_IN_17 = BIT(17),
    ADC_CH_IN_18 = BIT(18),
    ADC_CH_IN_19 = BIT(19),
    ADC_CH_IN_20 = BIT(20),
    ADC_CH_IN_21 = BIT(21),
    ADC_CH_IN_22 = BIT(22),
    ADC_CH_IN_23 = BIT(23),
    ADC_CH_IN_24 = BIT(24),
    ADC_CH_IN_25 = BIT(25),
    ADC_CH_IN_26 = BIT(26),
    ADC_CH_IN_27 = BIT(27),
    ADC_CH_IN_28 = BIT(28),
    ADC_CH_IN_29 = BIT(29),
    ADC_CH_IN_30 = BIT(30),
    ADC_CH_IN_MAX,
} ADC_CH_IN_e;

/**
 * @brief ADC Operation
 */
typedef enum
{
    ADC_OPS_POLL,        /**< Operation Polling */
    ADC_OPS_INTR,        /**< Operation Interrupt */
    ADC_OPS_INTR_DMA,    /**< Operation Interrupt with DMA */
    ADC_OPS_NMI,         /**< Operation NMI */
    ADC_OPS_NMI_DMA,     /**< Operation NMI with DMA */
    ADC_OPS_MAX
} ADC_OPS_e;

/**
 * @brief ADC Event
 */
typedef enum
{
    ADC_EVENT_SINGLE_CAPTURED       = BIT(0),    /**< Single/Sequence captured */
    ADC_EVENT_BURST_CAPTURED        = BIT(1),    /**< Burst captured */
    ADC_EVENT_CONVERSION_TRIGGER    = BIT(2),    /**< Conversion triggered */
    ADC_EVENT_COMPARE_MATCHED       = BIT(3),    /**< Compare matched */
    ADC_EVENT_OVERRUN_TRIGGER       = BIT(4),    /**< Overrun triggered */
    ADC_EVENT_MAX
} ADC_EVENT_e;

/**
 * @brief ADC Clock Configuration
 */
typedef struct
{
    ADC_CLK_e            eClk;     
    ADC_CLK_MCCR_e       eMccr;         /**< When selecting MCCR at eClk */
    uint8_t              un8MccrDiv;    /**< When selecting MCCR at eClk */
    uint8_t              un8PClkDiv;    /**< 0 = Bypass, 1 = Stop, others = Divided value */
    bool                 bPClkInv;      /**< PCLK Inversion */
} ADC_CLK_CFG_t;

/**
 * @brief ADC Trigger Configuration
 */
typedef struct {
    ADC_TRG_TYPE_e      eType;          /**< Trigger Type */
    ADC_TRG_SRC_e       eTrgSrc;        /**< Trigger Source */
    uint8_t             un8TrgNum;      /**< One of Trigger source Channel Number (ex. Timer1x, Timer2x) */
    union {
        struct {
            uint8_t     un8ChNum;       /**< Channel Number */
        } tSgl;                         /**< Trigger Single Type */
        struct {
            uint32_t           un32ChNum;    /**< Channel Number ::ADC_CH_IN_e (bit-order) */
            ADC_EXT_TRG_EDGE_e eExtTrg;      /**< Trigger Edge when ADC_TRG_EXT */ 
        } tShe;                         /**< Trigger Share Type */
        struct {
            uint8_t     un8ChNum;       /**< Channel Number */
            uint8_t     un8SeqNum;      /**< Sequence Number */
            uint8_t     un8SamplingTime;/**< Channel Sampling Time */
        } tInd;                         /**< Trigger Independent Type */
    } utCfg;
} ADC_SEQ_TRG_CFG_t;

/**
 * @brief ADC Conversion Result Data
 */
typedef struct
{
    bool         bReadDDR;      /**< Read DMA Data if true */
    uint16_t     un16Result;    /**< Conversion data */
    uint8_t      un8ChInfo;     /**< Input Channel Number if bChInfo is enable */
    uint8_t      un8TrgInfo;    /**< Triggered but pending Conversion info if bTrgInfo is enable */
} ADC_SEQ_DATA_t;

/**
 * @brief ADC Compare Configuration
 */
typedef struct
{
    bool        bEnable;
    uint8_t     un8ChNum;       /**< Channel 0 ~ N */
    uint16_t    un16Data;       /**< Comparation Data */
    bool        bIntrEnable;    /**< comparation Interrupt Enable */
    bool        bIntrTrg;       /**< Interrupt trigger (false = ADC > CVAL, true = ADC <= CVAL) */
} ADC_CMP_CFG_t;

/**
 * @brief ADC Buffer Delay Configuration
 */
typedef struct
{
    bool    bEnable;             /**< Buffer Delay Enable */
    uint8_t un8Delay;            /**< 0 ~ N * MCLK Delay */
    bool    bBypass;             
} ADC_BUF_DLY_CFG_t;

/**
 * @brief ADC Over-sampling Configuration
 */
typedef struct
{
    bool       bEnable;           /**< Over-sampling Enable */
    uint8_t    un8Ratio;          /**< Ratio 2^(un8Ratio+1) */
    uint8_t    un8DataShift;      /**< Data Shift right 0 ~ 8 bit */
} ADC_OVS_CFG_t;

/**
 * @brief ADC Mode Configuration
 */
typedef struct
{
    ADC_MODE_e    eMode;
    ADC_TRG_SRC_e eBaseTrgSrc;
    ADC_REF_e     eRef;

    uint8_t       un8SeqCnt;          /**< Sequence Buffer Count ::ADC_SEQ_CFG_t */
    uint8_t       un8SamplingTime;    /**< (2 + value) MCLK Sampling Time */

    bool          bAutoRestart;       /**< AUTO Restart after Sequence mode finished */

    bool          bChInfo;            /**< Input Channel Information option ::ADC_SEQ_DATA_t */
    bool          bTrgInfo;           /**< Trigger Information option (ex. Timer1, MPWM etc) ::ADC_SEQ_DATA_t */
    bool          bSleep;             /**< Operation at Sleep mode */
} ADC_CFG_t;

/**
 * @brief ADC IRQ handler context
 */
typedef struct
{
    ADC_ID_e eId;    /**< ADC Instance Id */
} ADC_Context_t;

/**
 *******************************************************************************
 * @brief       ADC Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::ADC_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnADC_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize ADC.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_ADC_Init(ADC_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize ADC.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_ADC_Uninit(ADC_ID_e eId);

/**
 *******************************************************************************
 * @brief       Get MAX Resolution ADC.
 * @return      uint32_t : Max Resolution Value.
 ******************************************************************************/
uint32_t HAL_ADC_GetMaxResolution(void);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration ADC.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClkCfg : ADC Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_ADC_SetClkConfig(ADC_ID_e eId, ADC_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration ADC.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : ADC Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_ADC_SetConfig(ADC_ID_e eId, ADC_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ ADC.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_ADC_SetIRQ(ADC_ID_e eId, ADC_OPS_e eOps, pfnADC_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Set DMA ADC if eIo is ADC_IO_INTR_DMA.
 * @param[in]   eId : Instance Id.
 * @param[in]   un32Addr : Memory Address.
 * @param[in]   un32Len : Data Length.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_ADC_SetDMA(ADC_ID_e eId, uint32_t un32Addr, uint32_t un32Len);

/**
 *******************************************************************************
 * @brief       Set Sequence Configuration ADC.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : Sequence Control Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_ADC_SetSeqConfig(ADC_ID_e eId, ADC_SEQ_TRG_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set Compare Configuration ADC.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : Compare Configuration.
 * @return      HAL ERR code ::HAL_ERR_e
 ******************************************************************************/
HAL_ERR_e HAL_ADC_SetCmpConfig(ADC_ID_e eId, ADC_CMP_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set Buffer Delay Configuration ADC.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : Buffer Delay Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_ADC_SetBufDlyConfig(ADC_ID_e eId, ADC_BUF_DLY_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set Over-sampling Configuration ADC.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : Over-sampling Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_ADC_SetOVSConfig(ADC_ID_e eId, ADC_OVS_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Start convertion ADC.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_ADC_Start(ADC_ID_e eId);

/**
 *******************************************************************************
 * @brief       stop convertion ADC.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_ADC_Stop(ADC_ID_e eId);

/**
 *******************************************************************************
 * @brief       Get Data(Buffer) ADC.
 * @param[in]   eId : Instance Id.
 * @param[in]   un8SeqNum : Sequence Number.
 * @param[out]  *ptData : the current Data(Buffer) indicated by un8SeqNum.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_ADC_GetData(ADC_ID_e eId, uint8_t un8SeqNum, ADC_SEQ_DATA_t *ptData);

/**
 *******************************************************************************
 * @brief       Set waiting to complete convertion ADC.
 * @param[in]   eId : Instance Id.
 * @param[in]   un32Timeout : Timeout of waiting of convertion ADC.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_ADC_SetWaitComplete(ADC_ID_e eId, uint32_t un32Timeout);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_ADC_H_ */

/** @} */
/** @} */
