/**
 *******************************************************************************
 * @file        hal_pcu.h
 * @author      ABOV R&D Division
 * @brief       Port Control Unit
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
 * @defgroup    HAL_PCU PCU
 * @{
 * @brief       Port/GPIO Control Unit
 */

#ifndef _HAL_PCU_H_
#define _HAL_PCU_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief PCU Port Group Id
 */
typedef enum
{
    PCU_ID_A,
    PCU_ID_B,
    PCU_ID_C,
    PCU_ID_D,
    PCU_ID_E,
    PCU_ID_F,
    PCU_ID_G,
    PCU_ID_MAX
} PCU_ID_e;

/**
 * @brief PCU MCCR (Misc Clock) Source for Port Debounce
 */
typedef enum
{
    PCU_CLK_MCCR_LSI,    /**< Low Speed Internal Clock source */
    PCU_CLK_MCCR_LSE,    /**< Low Speed External Clock source */
    PCU_CLK_MCCR_MCLK,   /**< Master Clock source */
    PCU_CLK_MCCR_HSI,    /**< High Speed Internal Clock source */
    PCU_CLK_MCCR_HSE,    /**< High Speed External Clock source */
    PCU_CLK_MCCR_PLL,    /**< Phase-Locked Loop (PLL) Clock source */
    PCU_CLK_MCCR_HCLK,   /**< System Clock source */
    PCU_CLK_MCCR_MAX
} PCU_CLK_MCCR_e;

/**
 * @brief PCU IN/OUT Mode
 */
typedef enum
{
    PCU_INOUT_INPUT,                /**< Input Mode */
    PCU_INOUT_ANG_INPUT,            /**< Input Mode with Analog Port */
    PCU_INOUT_OUTPUT_PUSH_PULL,     /**< Output Mode with Push-Pull */
    PCU_INOUT_OUTPUT_OPEN_DRAIN,    /**< Output Mode with Open-Drain */
    PCU_INOUT_MAX
} PCU_INOUT_e;

/**
 * @brief PCU Port Number Id
 */
typedef enum
{
    PCU_PIN_ID_0,
    PCU_PIN_ID_1,
    PCU_PIN_ID_2,
    PCU_PIN_ID_3,
    PCU_PIN_ID_4,
    PCU_PIN_ID_5,
    PCU_PIN_ID_6,
    PCU_PIN_ID_7,
    PCU_PIN_ID_8,
    PCU_PIN_ID_9,
    PCU_PIN_ID_10,
    PCU_PIN_ID_11,
    PCU_PIN_ID_12,
    PCU_PIN_ID_13,
    PCU_PIN_ID_14,
    PCU_PIN_ID_15,
    PCU_PIN_ID_MAX
} PCU_PIN_ID_e;

/**
 * @brief PCU Alternative Id
 */
typedef enum
{
    PCU_ALT_0,
    PCU_ALT_1,
    PCU_ALT_2,
    PCU_ALT_3,
    PCU_ALT_4,
    PCU_ALT_5,
    PCU_ALT_6,
    PCU_ALT_7,
    PCU_ALT_8,
    PCU_ALT_9,
    PCU_ALT_10,
    PCU_ALT_MAX
} PCU_ALT_e;

/**
 * @brief PCU Port Pull-up/down Mode 
 */
typedef enum
{
    PCU_PUPD_DISABLED,    /**< Port Pull-up/down disable */
    PCU_PUPD_UP,          /**< Port Pull-up */
    PCU_PUPD_DOWN,        /**< Port Pull-down */
    PCU_PUPD_MAX
} PCU_PUPD_e;

/**
 * @brief PCU Port Debounce Enable
 */
typedef enum
{
    PCU_DEBOUNCE_DISABLE,
    PCU_DEBOUNCE_ENABLE,
    PCU_DEBOUNCE_MAX
} PCU_DEBOUNCE_e;

/**
 * @brief PCU Port Interrupt Mode
 */
typedef enum
{
    PCU_INTR_MODE_DISABLE,
    PCU_INTR_MODE_LEVEL_NONPEND,    /**< Clear Automatically Interrupt Flag */ 
    PCU_INTR_MODE_LEVEL_PEND,       /**< Not Clear Interrupt Flag */
    PCU_INTR_MODE_EDGE,             /**< Rising or Falling or Both Edge */
    PCU_INTR_MODE_MAX
} PCU_INTR_MODE_e;

/**
 * @brief PCU Port Interrupt Trigger Mode
 */
typedef enum
{
    PCU_INTR_TRG_DISABLE,          
    PCU_INTR_TRG_LOW_FALLING,        /**< Low Level or Falling Edge Trigger */
    PCU_INTR_TRG_HIGH_RISING,        /**< High Level or Rising Edge Trigger */
    PCU_INTR_TRG_BOTH_LEVEL_EDGE,    /**< Both Level or Edge Trigger */
    PCU_INTR_TRG_MAX
} PCU_INTR_TRG_e;

/**
 * @brief PCU Port Interrupt Status
 */
typedef enum
{
    PCU_INTR_STATUS_NONE,
    PCU_INTR_STATUS_LOW_FALL,     /**< Low Level or Falling Edge detected */
    PCU_INTR_STATUS_HIGH_RISE,    /**< High Level or Rising Edge detected */
    PCU_INTR_STATUS_BOTH,         /**< Both Level or Edge detected */
    PCU_INTR_STATUS_MAX
} PCU_INTR_STATUS_e;

/**
 * @brief PCU Port Level
 */
typedef enum
{
    PCU_PORT_LOW,
    PCU_PORT_HIGH,
    PCU_PORT_MAX
} PCU_PORT_e;

/**
 * @brief PCU Output Port Bit
 */
typedef enum
{
    PCU_OUTPUT_BIT_SET,
    PCU_OUTPUT_BIT_CLEAR,
    PCU_OUTPUT_BIT_MAX
} PCU_OUTPUT_BIT_e;

/**
 * @brief PCU Operation
 */
typedef enum
{
    PCU_OPS_POLL,        /**< Operation Polling */
    PCU_OPS_INTR,        /**< Operation Interrupt */
    PCU_OPS_NMI,         /**< Operation NMI */
    PCU_OPS_MAX
} PCU_OPS_e;

/**
 * @brief PCU Clock Configuration for Port Debounce
 */
typedef struct
{
    PCU_CLK_MCCR_e    eMccr;
    uint8_t           un8MccrDiv;
} PCU_DEBOUNCE_CLK_CFG_t;

/**
 * @brief PCU IRQ handler context
 */
typedef struct
{
    PCU_ID_e eId;    /**< PCU Port Group Id */
} PCU_Context_t;

/**
 *******************************************************************************
 * @brief       PCU Interrupt Callback Function Type.
 * @param[in]   un32Event Event type (NONE).
 * @param[in]   *pContext Context provided during SetIntrPort.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnPCU_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 * @brief PCU IRQ Configuration
 */
typedef struct
{
    PCU_ID_e                eId;
    PCU_OPS_e               eOps;
    pfnPCU_IRQ_Handler_t    pfnHandler;
    void                    *pContext;
    uint32_t                un32IRQPrio;
    uint8_t                 un8IntNum;
} PCU_IRQ_CFG_t;

/**
 *******************************************************************************
 * @brief       Set Alternative Function of Specific Port Group and Port's pin PCU.
 * @param[in]   eId : Port Group Id.
 * @param[in]   ePinId : Pin Id of Port Group Id.
 * @param[in]   eAlt : Alternative Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PCU_SetAltMode(PCU_ID_e eId, PCU_PIN_ID_e ePinId, PCU_ALT_e eAlt);

/**
 *******************************************************************************
 * @brief       Set Input or Output Mode of Specific Port Group and Port's Pin PCU.
 * @param[in]   eId : Port Group Id.
 * @param[in]   ePinId : Pin Id of Port Group Id.
 * @param[in]   eInOut : Port IN/OUT Mode.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PCU_SetInOutMode(PCU_ID_e eId, PCU_PIN_ID_e ePinId, PCU_INOUT_e eInOut);

/**
 *******************************************************************************
 * @brief       Set Pull-up/down Mode of Specific Port Group and Port's Pin PCU.
 * @param[in]   eId : Port Group Id.
 * @param[in]   ePinId : Pin Id of Port Group Id.
 * @param[in]   ePupd : Pull-up/down Mode.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PCU_SetPullUpDown(PCU_ID_e eId, PCU_PIN_ID_e ePinId, PCU_PUPD_e ePupd);

/**
 *******************************************************************************
 * @brief       Set Input Port Value (Level) of Specific Port Group and Port's Pin PCU.
 * @param[in]   eId : Port Group Id.
 * @param[in]   ePinId : Pin Id of Port Group Id.
 * @param[in]   *peInput : Input Port Value (Level).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PCU_GetInputValue(PCU_ID_e eId, PCU_PIN_ID_e ePinId, PCU_PORT_e *peInput);

/**
 *******************************************************************************
 * @brief       Set Output Port Value (Level) of Specific Port Group and Port's Pin PCU.
 * @param[in]   eId : Port Group Id.
 * @param[in]   ePinId : Pin Id of Port Group Id.
 * @param[in]   eOutput : Output Port Value (Level).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PCU_SetOutputValue(PCU_ID_e eId, PCU_PIN_ID_e ePinId, PCU_PORT_e eOutput);

/**
 *******************************************************************************
 * @brief       Set Output Port Bit of Specific Port Group and Port's Pin PCU.
 * @param[in]   eId : Port Group Id.
 * @param[in]   ePinId : Pin Id of Port Group Id.
 * @param[in]   eBit : Output Port Bit.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PCU_SetOutputBit(PCU_ID_e eId, PCU_PIN_ID_e ePinId, PCU_OUTPUT_BIT_e eBit);

/**
 *******************************************************************************
 * @brief       Set to sustain Current Output Port Value (Level).
 * @param[in]   eId : Port Group Id.
 * @param[in]   ePinId : Pin Id of Port Group Id.
 * @param[in]   bEnable : Enable to sustain Output Port Value (Level).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PCU_SetOutputSustain(PCU_ID_e eId, PCU_PIN_ID_e ePinId, bool bEnable);

/**
 *******************************************************************************
 * @brief       Set Interrupt and Trigger Mode of Specific Port Group and Port's Pin PCU.
 * @param[in]   eId : Port Group Id.
 * @param[in]   ePinId : Pin Id of Port Group Id.
 * @param[in]   eMode : Interrupt Mode.
 * @param[in]   eTrg : Interrupt Trigger Mode.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PCU_SetIntrPort(PCU_ID_e eId, PCU_PIN_ID_e ePinId, PCU_INTR_MODE_e eMode, PCU_INTR_TRG_e eTrg, uint8_t un8IntNum);

/**
 *******************************************************************************
 * @brief       Get Interrupt Status of Specific Port Group and Port's Pin PCU.
 * @param[in]   eId : Port Group Id.
 * @param[in]   ePinId : Pin Id of Port Group Id.
 * @param[in]   *peStatus : Interrupt Status ::PCU_INTR_STATUS_e.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PCU_GetIntrStatus(PCU_ID_e eId, PCU_PIN_ID_e ePinId, PCU_INTR_STATUS_e *peStatus);

/**
 *******************************************************************************
 * @brief       Set Port Debounce Enable PCU.
 * @param[in]   eId : Port Group Id.
 * @param[in]   ePinId : Pin Id of Port Group Id.
 * @param[in]   bEnable : Enable Port Debounce.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PCU_SetPortDebounce(PCU_ID_e eId, PCU_PIN_ID_e ePinId, bool bEnable);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration for Port Debounce PCU.
 * @param[in]   eId : Port Group Id.
 * @param[in]   *ptClkCfg : Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PCU_SetClkDebounce(PCU_ID_e eId, PCU_DEBOUNCE_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set F Port 5 to 7 Input Level PCU.
 * @param[in]   eId : Port Group Id.
 * @param[in]   ePinId : Pin Id of Port Group Id.
 * @param[in]   bLevel : true = 1.8V, false = VDD.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PCU_SetPortFInputLevel(PCU_ID_e eId, PCU_PIN_ID_e ePinId, bool bLevel);

/**
 *******************************************************************************
 * @brief       Set Port Strength Enable PCU.
 * @param[in]   eId : Port Group Id.
 * @param[in]   ePinId : Pin Id of Port Group Id.
 * @param[in]   bEnable : Enable Port Strength.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PCU_SetPortStrength(PCU_ID_e eId, PCU_PIN_ID_e ePinId, bool bEnable);

/**
 *******************************************************************************
 * @brief       Set Port Low Voltage Input Enable PCU.
 * @param[in]   eId : Port Group Id.
 * @param[in]   ePinId : Pin Id of Port Group Id.
 * @param[in]   bEnable : Enable Port Low Voltage Input.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PCU_SetPortLowVoltageInput(PCU_ID_e eId, PCU_PIN_ID_e ePinId, bool bEnable);

/**
 *******************************************************************************
 * @brief       Set Port Alternate Function Open-Drain Enable PCU.
 * @param[in]   eId : Port Group Id.
 * @param[in]   ePinId : Pin Id of Port Group Id.
 * @param[in]   bEnable : Enable Port Alternate Function Open-Drain.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PCU_SetPortAltOpenDrain(PCU_ID_e eId, PCU_PIN_ID_e ePinId, bool bEnable);

/**
 *******************************************************************************
 * @brief       Set IRQ PCU.
 * @param[in]   *ptIRQCfg : PCU IRQ Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_PCU_SetIRQ(PCU_IRQ_CFG_t *ptIRQCfg);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_PCU_H_ */

/** @} */
/** @} */
