/**
 *******************************************************************************
 * @file        hal_scu_pwr.h
 * @author      ABOV R&D Division 
 * @brief       Power sub system in System Control Unit
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
 * @defgroup    HAL_SCU_PWR SCU_PWR
 * @{
 * @brief       Power sub system in System Control Unit (SCU)
 */

#ifndef _HAL_SCU_PWR_H_
#define _HAL_SCU_PWR_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief SCUPWR Mode
 */
typedef enum {
    SCUPWR_MODE_INIT,          /**< Init Mode */
    SCUPWR_MODE_RUN,           /**< Running Mode */
    SCUPWR_MODE_SLEEP,         /**< Sleep Mode */
    SCUPWR_MODE_DEEPSLEEP,     /**< Deep-sleep Mode */
    SCUPWR_MODE_DEEPSLEEP2,    /**< Deep-sleep 2 Mode */
    SCUPWR_MODE_MAX
} SCUPWR_MODE_e;

/**
 * @brief SCUPWR Deep-sleep Mode
 */
typedef enum {
    SCUPWR_DS_MODE_0,     /**< Deep-sleep Mode 0 */
    SCUPWR_DS_MODE_1,     /**< Deep-sleep Mode 1 */
    SCUPWR_DS_MODE_2,     /**< Deep-sleep Mode 2 */
    SCUPWR_DS_MODE_3,     /**< Deep-sleep Mode 3 */
    SCUPWR_DS_MODE_MAX
} SCUPWR_DS_MODE_e;

/**
 * @brief SCUPWR Wake-up Pin bit 
 */
typedef enum {
    SCUPWR_WKUP_PIN_0 = BIT(0),     /**< Wake-up Pin 0 */
    SCUPWR_WKUP_PIN_1 = BIT(1),     /**< Wake-up Pin 1 */
    SCUPWR_WKUP_PIN_2 = BIT(2),     /**< Wake-up Pin 2 */
    SCUPWR_WKUP_PIN_3 = BIT(3),     /**< Wake-up Pin 3 */
    SCUPWR_WKUP_PIN_MAX
} SCUPWR_WKUP_PIN_e;

/**
 * @brief SCUPWR Deep-sleep Wake-up reason
 */
typedef enum {
    SCUPWR_DS_WKUP_REASON_1,       /**< Wake-up reason Deep-sleep 1 */
    SCUPWR_DS_WKUP_REASON_2,       /**< Wake-up reason Deep-sleep 2 */
    SCUPWR_DS_WKUP_REASON_3,       /**< Wake-up reason Deep-sleep 3 */
    SCUPWR_DS_WKUP_REASON_MAX
} SCUPWR_DS_WKUP_REASON_e;

/**
 * @brief SCUPWR Always On in Deep-sleep Mode
 */
typedef enum {
    SCUPWR_AON_VDC     = BIT(0),    /**< VDC Block */
    SCUPWR_AON_BGR     = BIT(1),    /**< BGR Block */
    SCUPWR_AON_LSI     = BIT(2),    /**< Low Speed Internal Clock Block */
    SCUPWR_AON_LSE     = BIT(3),    /**< Low Speed External Clock Block */
    SCUPWR_AON_HSI     = BIT(4),    /**< High Speed Internal Clock Block */
    SCUPWR_AON_HSE     = BIT(5),    /**< High Speed External Clock Block */
    SCUPWR_AON_PLL     = BIT(6),    /**< Phase-Locked Loop (PLL) Clock Block */
    SCUPWR_AON_EXTCLK  = BIT(7),    /**< High and Low Speed External Clock Block */
    SCUPWR_AON_MAX
} SCUPWR_AON_e;

/**
 * @brief SCUPWR Wake-up Interrupt 
 */
typedef enum {
    SCUPWR_WKUP_INTR_NONE,        /**< None Interrupt */
    SCUPWR_WKUP_INTR_MASK,        /**< Maskable Interrupt */
    SCUPWR_WKUP_INTR_NON_MASK,    /**< Non-maskable Interrupt */
    SCUPWR_WKUP_INTR_MAX
} SCUPWR_WKUP_INTR_e;

/**
 * @brief SCUPWR Port Id 
 */
typedef enum {
    SCUPWR_PORT_ID_A,              /**< Port Id A */
    SCUPWR_PORT_ID_B,              /**< Port Id B */
    SCUPWR_PORT_ID_C,              /**< Port Id C */
    SCUPWR_PORT_ID_D,              /**< Port Id D */
    SCUPWR_PORT_ID_E,              /**< Port Id E */
    SCUPWR_PORT_ID_F,              /**< Port Id F */
    SCUPWR_PORT_ID_MAX
} SCUPWR_PORT_ID_e;

/**
 * @brief SCUPWR Port Pull Up/Down  
 */
typedef enum {
    SCUPWR_PORT_PUPD_DISABLE,      /**< Disable Port Pull-up/down */
    SCUPWR_PORT_PUPD_UP,           /**< Port Pull-up */
    SCUPWR_PORT_PUPD_DOWN,         /**< Port Pull-down */
    SCUPWR_PORT_PUPD_MAX
} SCUPWR_PORT_PUPD_e;

/**
 * @brief SCUPWR Deep-sleep configuration
 */
typedef struct
{
    SCUPWR_DS_MODE_e    eDsMode;            /**< Deep-sleep sub mode */
    uint8_t             un8WkUpPinEnable;   /**< Wake-Up Enable :: SCUPWR_WKUP_e (Bit Order) */
} SCUPWR_DS_CFG_t;

/**
 * @brief SCUPWR Extension Power Control configuration
 */
typedef struct
{
    bool    bFlashPwrOff;    /**< Flash Power On/Off normally, Code Flash */
    bool    bDFlashPwrOff;   /**< Data Flash Power On/Off */
} SCUPWR_EPC_CFG_t;

/**
 * @brief SCUPWR Backup Data Buffer
 */
typedef struct
{
    uint8_t    un8Num;              /**< Backup Data Number */
    uint32_t   un32Data;            /**< Backup Data */
} SCUPWR_BAK_DATA_t;

/**
 *******************************************************************************
 * @brief       SCUPWR WakeUp Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::SCUPWR_WKUP_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQIndicator.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnSCUPWR_WKUP_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Set IRQ SCU PWR Wake-up SCUPWR.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @param[in]   eIntr : Interrupt Operation Mode.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_PWR_SetIRQWakeUp(pfnSCUPWR_WKUP_IRQ_Handler_t pfnHandler, 
                                      void *pContext, uint32_t un32IRQPrio, 
                                      SCUPWR_WKUP_INTR_e eIntr);

/**
 *******************************************************************************
 * @brief       Set Power Mode SCU PWR.
 * @param[in]   eMode : Power Mode.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_PWR_SetMode(SCUPWR_MODE_e eMode);

/**
 *******************************************************************************
 * @brief       Set Deep-sleep Sub Mode SCU PWR.
 *              some of ABOV chipsets are only supported.
 * @param[in]   *ptEpc : Deep-Sleep Sub Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_PWR_SetDeepSleepMode(SCUPWR_DS_CFG_t *ptDs);

/**
 *******************************************************************************
 * @brief       Set Alway-on Block after Deep-sleep SCU PWR.
 * @param[in]   un32Aon : Always-on Block ::SCUPWR_AON_e (Bit Order).
 * @param[in]   un32Enable : Enable Bit ::SCUPWR_AON_e (Bit Order).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_PWR_SetAlwaysOn(uint32_t un32Aon, uint32_t un32Enable);

/**
 *******************************************************************************
 * @brief       Set VDC Delay SCU PWR.
 * @param[in]   un8VdcDelay : VDC Delay Value.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_PWR_SetVdcDelay(uint8_t un8VdcDelay);

/**
 *******************************************************************************
 * @brief       Set Power-down Indicator (Specific Port) Level SCU PWR.
 *              some of ABOV chipsets are only supported.
 * @param[in]   bLevel : true = High, false = Low.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_PWR_SetPDIndicator(bool bLevel);

/**
 *******************************************************************************
 * @brief       Set Backup Power Mode.
 *              some of ABOV chipsets are only supported.
 * @param[in]   bEnable : true = enable, false = disable.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_PWR_SetBackupMode(bool bEnable);

/**
 *******************************************************************************
 * @brief       Set Backup Data.
 *              some of ABOV chipsets are only supported.
 * @param[in]   *ptBak : Backup Data 
 * @param[in]   un8Len : Backup Data length
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_PWR_SetBackupData(SCUPWR_BAK_DATA_t *ptBak, uint8_t un8Len);

/**
 *******************************************************************************
 * @brief       Get Backup Data.
 *              some of ABOV chipsets are only supported.
 * @param[in]   *ptBak : Backup Data 
 * @param[in]   un8Len : Backup Data length
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_PWR_GetBackupData(SCUPWR_BAK_DATA_t *ptBak, uint8_t un8Len);

/**
 *******************************************************************************
 * @brief       Set Extension SCU PWR.
 *              some of ABOV chipsets are only supported.
 * @param[in]   *ptEpc : Power Control Extension Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_PWR_SetExtension(SCUPWR_EPC_CFG_t *ptEpc);

/**
 *******************************************************************************
 * @brief       Set Port Pull-up/down SCU PWR.
 *              some of ABOV chipsets are only supported.
 * @param[in]   ePortId : Pull-up/down Port Id.
 * @param[in[   un32Pupd : Pull-up/down value ::SCUPWR_PORT_PUPD_e (2Bit Order)
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_PWR_SetPortPupd(SCUPWR_PORT_ID_e ePortId, uint32_t un32Pupd);

/**
 *******************************************************************************
 * @brief       Set Wake-up Reason SCU PWR.
 *              some of ABOV chipsets are only supported.
 * @param[in]   *peWkUpReason : Wake-up Reason ::SCUPWR_DS_WKUP_REASON_e.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_PWR_GetDsWkUpReason(SCUPWR_DS_WKUP_REASON_e *peWkUpReason);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_SCU_PWR_H_ */

/** @} */
/** @} */
