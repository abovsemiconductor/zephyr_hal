/**
 *******************************************************************************
 * @file        hal_cmp.h
 * @author      ABOV R&D Division
 * @brief       Comparator
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
 * @defgroup    HAL_CMP CMP
 * @{
 * @brief       N-channel Comparator
 */

#ifndef _HAL_CMP_H_
#define _HAL_CMP_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief CMP Instance Id
 */
typedef enum
{
    CMP_ID_0,
    CMP_ID_1,
    CMP_ID_2,
    CMP_ID_3,
    CMP_ID_4,
    CMP_ID_5,
    CMP_ID_6,
    CMP_ID_7,
    CMP_ID_8,
    CMP_ID_9,
    CMP_ID_MAX
} CMP_ID_e;

/**
 * @brief CMP Power Mode
 */
typedef enum
{
    CMP_PWR_ULTRALOW,    /**< Ultra Low */
    CMP_PWR_LOW,         /**< Low */
    CMP_PWR_MEDIUM,      /**< Medium */
    CMP_PWR_HIGH,        /**< High */
    CMP_PWR_MAX
} CMP_PWR_e;

/**
 * @brief CMP Input and Reference source
 */
typedef enum
{
    CMP_SRC_0,    /**< Input/Reference 0 */
    CMP_SRC_1,    /**< Input/Reference 1 */
    CMP_SRC_2,    /**< Input/Reference 2 */
    CMP_SRC_3,    /**< Input/Reference 3 */
    CMP_SRC_4,    /**< Input/Reference 4 */
    CMP_SRC_5,    /**< Input/Reference 5 */
    CMP_SRC_6,    /**< Input/Reference 6 */
    CMP_SRC_7,    /**< Input/Reference 7 */
    CMP_SRC_MAX
} CMP_SRC_e;

/**
 * @brief CMP Hysteresis Mode
 */
typedef enum
{
    CMP_HYSS_OFF,
    CMP_HYSS_LOW,           /**< Low or 5mV or 40mV Hysteresis */
    CMP_HYSS_MEDIUM,        /**< Medium or 5mV or 80mV Hysteresis */
    CMP_HYSS_HIGH,          /**< High or 20mV or 120mV Hysteresis */
    CMP_HYSS_ULTRA_HIGH,    /**< Ultra High or 160mV Hysteresis */
    CMP_HYSS_MAX
} CMP_HYSS_e;

/**
 * @brief CMP Interrupt Trigger Mode
 */
typedef enum
{
    CMP_INTR_TRG_LEVEL,        /**< Level */
    CMP_INTR_TRG_RISING,       /**< Rising Edge */
    CMP_INTR_TRG_FALLING,      /**< Falling Edge */
    CMP_INTR_TRG_BOTH_EDGE,    /**< Both Edge */
    CMP_INTR_TRG_DISABLE,      /**< Disable */
    CMP_INTR_TRG_MAX
} CMP_INTR_TRG_e;

/**
 * @brief CMP Operation
 */
typedef enum
{
    CMP_OPS_POLL,        /**< Operation Polling */
    CMP_OPS_INTR,        /**< Operation Interrupt */
    CMP_OPS_NMI,         /**< Operation NMI */
    CMP_OPS_MAX
} CMP_OPS_e;

/**
 * @brief CMP Event
 */
typedef enum
{
    CMP_EVENT_LEVEL        = BIT(0),    /**< Level triggered */
    CMP_EVENT_RISING       = BIT(1),    /**< Rising Egde triggered */
    CMP_EVENT_FALLING      = BIT(2),    /**< Falling Egde triggered */
    CMP_EVENT_BOTH_EDGE    = BIT(3),    /**< Both Egde triggered */
    CMP_EVENT_MAX
} CMP_EVENT_e;

/**
 * @brief CMP Extend Configuration
 */
typedef struct
{
    CMP_PWR_e    ePwr;        
    bool         bWindowEn;         /**< Window Enable (CMP Input 1 is connected to CMP Input 0) */
    bool         bIntRefEn;         /**< Internal Reference Enable */
    uint8_t      un8IntRefVLvl;    /**< Internal Reference Voltage Level */
} CMP_EXT_CFG_t;

/**
 * @brief CMP Debounce Configuration
 */
typedef struct
{
    bool        bEnable;
    uint16_t    un16ClkDiv;    /** < Debounce clock divider (0 : system clock) */
    uint8_t     un8Shift;      /** < Debounce shift number (0 : disable) */
    bool        bLSIClk;       /** < Use LSI Clock source instead of System Clock */
} CMP_DBC_CFG_t;

/**
 * @brief CMP Mode Configuration
 */
typedef struct
{
    CMP_SRC_e         eInSrc;
    CMP_SRC_e         eRefSrc;
    CMP_HYSS_e        eHyss;
    CMP_INTR_TRG_e    eIntrTrg;
    bool              bIntrPol;        /**< true : low, false : high */
    bool              bTrgOutPol;      /**< true : inverted, false : normal */

    CMP_DBC_CFG_t     tDbc;
    CMP_EXT_CFG_t     tExt;
} CMP_CFG_t;

/**
 * @brief CMP IRQ handler context
 */
typedef struct
{
    CMP_ID_e eId;        /**< CMP Instance Id */
    bool     bWakeup;    /**< Wake-up flag */
} CMP_Context_t;

/**
 *******************************************************************************
 * @brief       CMP Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::CMP_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnCMP_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize CMP.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CMP_Init(CMP_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize CMP.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CMP_Uninit(CMP_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration CMP.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : CMP Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CMP_SetConfig(CMP_ID_e eId, CMP_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ CMP.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @param[in]   bNonMask : Enable non-maskable Interrupt.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CMP_SetIRQ(CMP_ID_e eId, CMP_OPS_e eOps, pfnCMP_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio, bool bNonMask);

/**
 *******************************************************************************
 * @brief       Start comparation CMP.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CMP_Start(CMP_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop comparation CMP.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CMP_Stop(CMP_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set waiting to complete comparation CMP.
 * @param[in]   eId : Instance Id
 * @param[in]   un32Timeout : Timeout of waiting of comparation CMP.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CMP_SetWaitComplete(CMP_ID_e eId, uint32_t un32Timeout);

/**
 *******************************************************************************
 * @brief       Set Wake-up source CMP.
 * @param[in]   eId : Instance Id.
 * @param[in]   bEnable : Enable Wake-up source.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CMP_SetWakeupSrc(CMP_ID_e eId, bool bEnable);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_CMP_H_ */

/** @} */
/** @} */
