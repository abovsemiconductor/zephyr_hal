/**
 *******************************************************************************
 * @file        hal_led.h
 * @author      ABOV R&D Division
 * @brief       LED Driver
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
 * @defgroup    HAL_LED LED
 * @{
 * @brief       Light Emitting Diode (LED) Controller
 */

#ifndef _HAL_LED_H_
#define _HAL_LED_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief LED Instance Id
 */
typedef enum
{
    LED_ID_0,
    LED_ID_1,
    LED_ID_2,
    LED_ID_3,
    LED_ID_4,
    LED_ID_5,
    LED_ID_7,
    LED_ID_8,
    LED_ID_9,
    LED_ID_MAX
} LED_ID_e;

/**
 * @brief LED Clock Source
 */
typedef enum
{
    LED_CLK_MCCR,    /**< Misc Clock source ::LED_CLK_MCCR_e */
    LED_CLK_PCLK,    /**< Peripheral Clock source */
    LED_CLK_MAX
} LED_CLK_e;

/**
 * @brief LED MCCR (Misc Clock) Source
 */
typedef enum
{
    LED_CLK_MCCR_LSI,    /**< Low Speed Internal Clock source */
    LED_CLK_MCCR_LSE,    /**< Low Speed External Clock source */
    LED_CLK_MCCR_MCLK,   /**< Master Clock source */
    LED_CLK_MCCR_HSI,    /**< High Speed Internal Clock source */
    LED_CLK_MCCR_HSE,    /**< High Speed External Clock source */
    LED_CLK_MCCR_PLL,    /**< Phase-Locked Loop (PLL) Clock source */
    LED_CLK_MCCR_MAX
} LED_CLK_MCCR_e;

/**
 * @brief LED Overlap Time
 */
typedef enum
{
    LED_OVERLAP_TIME_DIV_1024,
    LED_OVERLAP_TIME_DIV_512,
    LED_OVERLAP_TIME_DIV_256,
    LED_OVERLAP_TIME_DIV_128,
    LED_OVERLAP_TIME_DIV_64,
    LED_OVERLAP_TIME_DIV_32,
    LED_OVERLAP_TIME_DIV_16,
    LED_OVERLAP_TIME_DIV_8,
    LED_OVERLAP_TIME_DIV_MAX
} LED_OVERLAP_TIME_e;

/**
 * @brief LED ICOM and ISEG Share Pin
 *
 */
typedef enum
{
    LED_SHARE_PIN_ISEG0_ISEG1,
    LED_SHARE_PIN_ISEG0_ICOM26,
    LED_SHARE_PIN_ICOM25_ISEG1,
    LED_SHARE_PIN_ICOM25_ICOM26,
    LED_SHARE_PIN_MAX
} LED_SHARE_PIN_e;

/**
 * @brief LED Mode
 *
 */
typedef enum
{
    LED_MODE_ALONE,        /**< LED alone */
    LED_MODE_HANDSHAKE,    /**< Hand-shake with Touch */
    LED_MODE_STOPCOUNT,    /**< LED Stop Count */
    LED_MODE_SMARTSHARE,   /**< Smart Share with Touch */
    LED_MODE_AUTO,         /**< LED Auto Mode */
    LED_MODE_MAX
} LED_MODE_e;

/**
 * @brief LED ISEG Bit
 *
 */
typedef enum
{
    LED_ISEG_0    = BIT(0),
    LED_ISEG_1    = BIT(1),
    LED_ISEG_2    = BIT(2),
    LED_ISEG_3    = BIT(3),
    LED_ISEG_4    = BIT(4),
    LED_ISEG_5    = BIT(5),
    LED_ISEG_6    = BIT(6),
    LED_ISEG_7    = BIT(7),
    LED_ISEG_8    = BIT(8),
    LED_ISEG_9    = BIT(9),
    LED_ISEG_10   = BIT(10),
    LED_ISEG_11   = BIT(11),
    LED_ISEG_12   = BIT(12),
    LED_ISEG_13   = BIT(13),
    LED_ISEG_14   = BIT(14),
    LED_ISEG_15   = BIT(15),
    LED_ISEG_MAX
} LED_ISEG_e;

/**
 * @brief LED ICOM Bit
 *
 */
typedef enum
{
    LED_ICOM_0    = BIT(0),
    LED_ICOM_1    = BIT(1),
    LED_ICOM_2    = BIT(2),
    LED_ICOM_3    = BIT(3),
    LED_ICOM_4    = BIT(4),
    LED_ICOM_5    = BIT(5),
    LED_ICOM_6    = BIT(6),
    LED_ICOM_7    = BIT(7),
    LED_ICOM_8    = BIT(8),
    LED_ICOM_9    = BIT(9),
    LED_ICOM_10   = BIT(10),
    LED_ICOM_11   = BIT(11),
    LED_ICOM_12   = BIT(12),
    LED_ICOM_13   = BIT(13),
    LED_ICOM_14   = BIT(14),
    LED_ICOM_15   = BIT(15),
    LED_ICOM_16   = BIT(16),
    LED_ICOM_17   = BIT(17),
    LED_ICOM_18   = BIT(18),
    LED_ICOM_19   = BIT(19),
    LED_ICOM_20   = BIT(20),
    LED_ICOM_21   = BIT(21),
    LED_ICOM_22   = BIT(22),
    LED_ICOM_23   = BIT(23),
    LED_ICOM_24   = BIT(24),
    LED_ICOM_25   = BIT(25),
    LED_ICOM_26   = BIT(26),
    LED_ICOM_27   = BIT(27),
    LED_ICOM_28   = BIT(28),
    LED_ICOM_29   = BIT(29),
    LED_ICOM_30   = BIT(30),
    LED_ICOM_MAX
} LED_ICOM_e;

/**
 * @brief LED Operation
 */
typedef enum
{
    LED_OPS_POLL,        /**< Operation Polling */
    LED_OPS_INTR,        /**< Operation Interrupt */
    LED_OPS_MAX
} LED_OPS_e;

/**
 * @brief LED Event
 */
typedef enum
{
    LED_EVENT_MATCH    = BIT(0),    /**< When mode is LED_MODE_STOPCOUNT */
    LED_EVENT_INTR     = BIT(1),
    LED_EVENT_END      = BIT(2),    /**< End of LED Operation */
    LED_EVENT_MAX
} LED_EVENT_e;

/**
 * @brief LED Clock Configuration
 */
typedef struct
{
    LED_CLK_e            eClk;     
    LED_CLK_MCCR_e       eMccr;          /**< When selecting MCCR at eClk */
    uint8_t              un8MccrDiv;     /**< When selecting MCCR at eClk */
    uint16_t             un16Prescale;
} LED_CLK_CFG_t;

/**
 * @brief LED Overlap Time Configuration
 */
typedef struct
{
    bool                  bEnable;
    LED_OVERLAP_TIME_e    eTime;
} LED_OVLAP_CFG_t;

/**
 * @brief LED Mode configuration
 */
typedef struct
{
    LED_MODE_e         eLedMode;
    LED_SHARE_PIN_e    eSharePin;
    uint8_t            un8IcomPulse;    /**< ICOM Pulse width (LED CLK/(un8IcomPulse + 1) */
    uint32_t           un32Duration;    /**< Led Stop Count Duration value */

    LED_OVLAP_CFG_t    tOverlap;
} LED_CFG_t;

/**
 * @brief LED Control Data Buffer
 */
typedef struct
{
    bool       bEnable;
    uint8_t    un8Num;
    uint32_t   un32Data;
} LED_DATA_t;

/**
 * @brief LED IRQ handler context
 */
typedef struct
{
    LED_ID_e        eId;
    uint32_t        un32Mode;
} LED_Context_t;

/**
 *******************************************************************************
 * @brief       LED Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::LED_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnLED_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize LED.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LED_Init(LED_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize LED.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LED_Uninit(LED_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration LED.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClkCfg : LED Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LED_SetClkConfig(LED_ID_e eId, LED_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration LED.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : LED Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LED_SetConfig(LED_ID_e eId, LED_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Start to display LED.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LED_Start(LED_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop to display LED.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LED_Stop(LED_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Icom Dimming Data LED.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptDimm : Dimming Data.
 * @param[in]   un8Num : Number of Dimming Data.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LED_SetDimming(LED_ID_e eId, LED_DATA_t *ptDimm, uint8_t un8Num);

/**
 *******************************************************************************
 * @brief       Set Icom Display Data LED.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptRam : Display RAM Data.
 * @param[in]   un8Num : Number of Display RAM Data.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LED_SetDispData(LED_ID_e eId, LED_DATA_t *ptRam, uint8_t un8Num);

/**
 *******************************************************************************
 * @brief       Get Icom Display Data LED.
 * @param[in]   eId : Instance Id.
 * @param[in]   un8IcomNum : Icom Channel Number.
 * @param[in]   pun32data : ICOM Data by un8IcomNum.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LED_GetDispData(LED_ID_e eId, uint8_t un8IcomNum, uint32_t *pun32Data);

/**
 *******************************************************************************
 * @brief       Set IRQ LED.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LED_SetIRQ(LED_ID_e eId, LED_OPS_e eOps, pfnLED_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Set Icom Enable LED.
 * @param[in]   eId : Instance Id.
 * @param[in]   un32Enable : Icom Enable Bit (Bit Order).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LED_SetIcomEnable(LED_ID_e eId, uint32_t un32Enable);

/**
 *******************************************************************************
 * @brief       Set Icom Output Port Enable LED.
 * @param[in]   eId : Instance Id.
 * @param[in]   un32Enable : Icom Enable Bit (Bit Order).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LED_SetIcomOutput(LED_ID_e eId, uint32_t un32Enable);

/**
 *******************************************************************************
 * @brief       Set Iseg Output Port Enable LED.
 * @param[in]   eId : Instance Id.
 * @param[in]   un32Enable : Iseg Enable Bit (Bit Order).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LED_SetIsegOutput(LED_ID_e eId, uint32_t un32Enable);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_LED_H_ */

/** @} */
/** @} */
