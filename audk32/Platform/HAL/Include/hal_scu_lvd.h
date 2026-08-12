/**
 *******************************************************************************
 * @file        hal_scu_lvd.h
 * @author      ABOV R&D Division 
 * @brief       Low Voltage Detector sub system in System Control Unit
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
 * @defgroup    HAL_SCU_LVD SCU_LVD
 * @{
 * @brief       Low Voltage Detector sub system in System Control Unit (SCU)
 */

#ifndef _HAL_SCU_LVD_H_
#define _HAL_SCU_LVD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief SCULVD Indicator Level
 */
typedef enum {
    SCULVD_IND_LVL_0,    /**< Lowest Voltage Level */
    SCULVD_IND_LVL_1,    
    SCULVD_IND_LVL_2,   
    SCULVD_IND_LVL_3,    
    SCULVD_IND_LVL_4,    
    SCULVD_IND_LVL_5,    
    SCULVD_IND_LVL_6,     
    SCULVD_IND_LVL_7,
    SCULVD_IND_LVL_8,
    SCULVD_IND_LVL_9,
    SCULVD_IND_LVL_10,
    SCULVD_IND_LVL_11,
    SCULVD_IND_LVL_12,
    SCULVD_IND_LVL_13,
    SCULVD_IND_LVL_14,
    SCULVD_IND_LVL_15,    /**< Highest Voltage Level */
    SCULVD_IND_LVL_MAX
} SCULVD_IND_LVL_e;

/**
 * @brief SCULVD Reset Level
 */

typedef enum {
    SCULVD_RST_LVL_0,    /**< Highest Voltage Level */
    SCULVD_RST_LVL_1,    
    SCULVD_RST_LVL_2,   
    SCULVD_RST_LVL_3,    
    SCULVD_RST_LVL_4,    
    SCULVD_RST_LVL_5,    
    SCULVD_RST_LVL_6,     
    SCULVD_RST_LVL_7,
    SCULVD_RST_LVL_8,
    SCULVD_RST_LVL_9,
    SCULVD_RST_LVL_10,
    SCULVD_RST_LVL_11,
    SCULVD_RST_LVL_12,
    SCULVD_RST_LVL_13,
    SCULVD_RST_LVL_14,
    SCULVD_RST_LVL_15,    /**< Lowest Voltage Level */
    SCULVD_RST_LVL_MAX
} SCULVD_RST_LVL_e;

/**
 * @brief SCULVD Indicator Interrupt 
 */

typedef enum {
    SCULVD_IND_INTR_NONE,        /**< None Interrupt */
    SCULVD_IND_INTR_MASK,        /**< Maskable Interrupt */
    SCULVD_IND_INTR_NON_MASK,    /**< Non-maskable Interrupt */
    SCULVD_IND_INTR_MAX
} SCULVD_IND_INTR_e;

/**
 * @brief SCULVD Indicator Event
 */

typedef enum {
    SCULVD_IND_EVENT_NON_MASK    = BIT(0),    /**< Non-maskable Interrupt occurred */
    SCULVD_IND_EVENT_MASK        = BIT(1),    /**< Maskable Interrupt occurred */
    SCULVD_IND_EVENT_MAX
} SCULVD_IND_EVENT_e;

/**
 * @brief SCULVD IRQ handler context
 */
typedef struct
{
    SCULVD_IND_LVL_e    eLevel;
    bool                bWakeup;    /**< Wake-up flag */
} SCULVD_Context_t;

/**
 *******************************************************************************
 * @brief       SCULVD Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::SCULVD_IND_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQIndicator.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnSCULVD_IND_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Set IRQ SCU LVD Indicator SCULVD.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @param[in]   eIntr : Interrupt Operation Mode.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_LVD_SetIRQIndicator(pfnSCULVD_IND_IRQ_Handler_t pfnHandler, 
                                      void *pContext, uint32_t un32IRQPrio, 
                                      SCULVD_IND_INTR_e eIntr);

/**
 *******************************************************************************
 * @brief       Set SCU LVD Indicator Enable SCULVD.
 * @param[in]   eLevel : Indicator Voltage Level.
 * @param[in]   bEnable : Enable Indicator.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_LVD_SetIndicatorEnable(SCULVD_IND_LVL_e eLevel, bool bEnable);

/**
 *******************************************************************************
 * @brief       Set SCU LVD Indicator Always-on SCULVD.
 * @param[in]   bEnable : Enable Always-on Indicator.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_LVD_SetIndicatorAlwalysOn(bool bEnable);

/**
 *******************************************************************************
 * @brief       Set SCU LVD Reset Enable SCULVD.
 * @param[in]   eLevel : Reset Voltage Level.
 * @param[in]   bEnable : Enable Reset.
 * @param[in]   bPowerDown : Enable Auto-off when Deep-sleep Mode.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_LVD_SetResetEnable(SCULVD_RST_LVL_e eLevel, bool bEnable, bool bPowerDown);

/**
 *******************************************************************************
 * @brief       Set SCU LVD Reset Always-on SCULVD.
 * @param[in]   bEnable : Enable Always-on Reset.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_LVD_SetResetAlwaysOn(bool bEnable);

/**
 *******************************************************************************
 * @brief       Set Wake-up Source Indicator SCULVD.
 * @param[in]   bEnable : Enable Wake-up Source.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_LVD_SetWakeupSrc(bool bEnable);

/**
 *******************************************************************************
 * @brief       Set Reset Source SCULVD.
 * @param[in]   bEnable : Enable Reset Source.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_LVD_SetResetSrc(bool bEnable);

/**
 *******************************************************************************
 * @brief       Get Reset Source Event SCULVD.
 * @param[out]  *pbEnable : Reset Source Event.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_LVD_GetResetSrcEvent(bool *pbEvent);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_SCU_LVD_H_ */

/** @} */
/** @} */
