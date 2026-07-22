/**
 *******************************************************************************
 * @file        hal_usart_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed USART
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_USART_F1X_H_
#define _HAL_USART_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define USART_CH_NUM                                  CONFIG_USART_MAX_COUNT

#define USART_STATUS_PE                               (1UL << 0)
#define USART_STATUS_FE                               (1UL << 1)
#define USART_STATUS_DOR                              (1UL << 2)
#define USART_STATUS_RTO                              (1UL << 3)
#define USART_STATUS_WAKE                             (1UL << 4)
#define USART_STATUS_RXC                              (1UL << 5)
#define USART_STATUS_TXC                              (1UL << 6)
#define USART_STATUS_DRE                              (1UL << 7)
#define USART_STATUS_DMARX                            (1UL << 8)
#define USART_STATUS_DMATX                            (1UL << 9)

#if (CONFIG_USART_VER_EXT == 0)

#if (CONFIG_USART_VER_MINOR == 0)
#include "hal_usart_f_01_00_00.h"
#elif (CONFIG_USART_VER_MINOR == 1)
#include "hal_usart_f_01_00_01.h"
#else
#error "define CONFIG_USART_VER_MINOR of F-type USART at config_xxx.h"
#endif

#elif (CONFIG_USART_VER_EXT == 1)

#if (CONFIG_USART_VER_MINOR == 0)
#include "hal_usart_f_01_01_00.h"
#else
#error "define CONFIG_USART_VER_MINOR of F-type USART at config_xxx.h"
#endif

#elif (CONFIG_USART_VER_EXT == 2)

#if (CONFIG_USART_VER_MINOR == 0)
#include "hal_usart_f_01_02_00.h"
#elif (CONFIG_USART_VER_MINOR == 1)
#include "hal_usart_f_01_02_01.h"
#elif (CONFIG_USART_VER_MINOR == 2)
#include "hal_usart_f_01_02_02.h"
#else
#error "define CONFIG_USART_VER_MINOR of F-type USART at config_xxx.h"
#endif

#elif (CONFIG_USART_VER_EXT == 3)

#if (CONFIG_USART_VER_MINOR == 0)
#include "hal_usart_f_01_03_00.h"
#elif (CONFIG_USART_VER_MINOR == 1)
#include "hal_usart_f_01_03_01.h"
#else
#error "define CONFIG_USART_VER_MINOR of F-type USART at config_xxx.h"
#endif

#else
#error "define CONFIG_USART_VER_EXT of F-type USART at config_xxx.h"
#endif

static __inline HAL_ERR_e USART_SetScuEnable(P_USART_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_USART_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_USART_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_USART_PCER(ptScu, (uint32_t)eId, un32Enable);

    return HAL_ERR_OK;
}

static __inline USART_Type *USART_GetReg(uint32_t uiId)
{
    return (USART_Type *)(USART_REG_BASE + (USART_REG_OFFSET * uiId));
}

static __inline IRQn_Type USART_GetIRQNum(P_USART_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(USART_0_IRQ)
        case P_USART_ID_0:
            eIrq = USART_0_IRQ;
            break;
#endif
#if defined(USART_1_IRQ)
        case P_USART_ID_1:
            eIrq = USART_1_IRQ;
            break;
#endif
#if defined(USART_2_IRQ)
        case P_USART_ID_2:
            eIrq = USART_2_IRQ;
            break;
#endif
#if defined(USART_3_IRQ)
        case P_USART_ID_3:
            eIrq = USART_3_IRQ;
            break;
#endif
#if defined(USART_4_IRQ)
        case P_USART_ID_4:
            eIrq = USART_4_IRQ;
            break;
#endif
#if defined(USART_5_IRQ)
        case P_USART_ID_5:
            eIrq = USART_5_IRQ;
            break;
#endif
#if defined(USART_6_IRQ)
        case P_USART_ID_6:
            eIrq = USART_6_IRQ;
            break;
#endif
#if defined(USART_7_IRQ)
        case P_USART_ID_7:
            eIrq = USART_7_IRQ;
            break;
#endif
#if defined(USART_8_IRQ)
        case P_USART_ID_8:
            eIrq = USART_8_IRQ;
            break;
#endif
#if defined(USART_9_IRQ)
        case P_USART_ID_9:
            eIrq = USART_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline uint32_t PRV_USART_GetNumer(void)
{
    return SystemPeriClock;
}

static __inline void USART_SetWkupSrc(P_USART_ID_e eId, bool bEnable)
{
#if defined(USART_FEATURE_WAKEUP)
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    uint32_t un32Data = 0;

    if(eId > P_USART_ID_1)
    {
        un32Data = USART_WKUP_OFFSET;
    }
    
    SET_SCU_USART_WKUP_EN(ptScu, (uint32_t)(eId + (P_USART_ID_e)un32Data), bEnable);
#else
    (void)bEnable;
#endif
}

static __inline void USART_GetWkupEvent(P_USART_ID_e eId, bool *bEvent)
{
#if defined(USART_FEATURE_WAKEUP)
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    uint32_t un32Data = 0;
#if defined(USART_FEATURE_NOT_SUPPORT_PREVMODE)
    if(eId > P_USART_ID_1)
    {
        un32Data = USART_WKUP_OFFSET;
    }

    if(GET_SCU_USART_WKUP_EN(ptScu, (uint32_t)(eId + (P_USART_ID_e)un32Data)))
    {
        *bEvent = GET_SCU_USART_WKUP_FLAG(ptScu, (uint32_t)(eId + (P_USART_ID_e)un32Data));
    }
    else
    {
        *bEvent = false;
    }
#else
    uint8_t un8Prev = GET_SCU_USART_PREVMODE(ptScu);

    if(eId > P_USART_ID_1)
    {
        un32Data = USART_WKUP_OFFSET;
    }

    if(GET_SCU_USART_WKUP_EN(ptScu, (uint32_t)(eId + (P_USART_ID_e)un32Data)))
    {
        if(un8Prev == 0x01 || un8Prev == 0x07)
        {
            *bEvent = GET_SCU_USART_WKUP_FLAG(ptScu, (uint32_t)(eId + (P_USART_ID_e)un32Data));
        }
    }
    else
    {
        *bEvent = false;
    }
#endif
#else
    *bEvent = false;
#endif
}

#if defined(USART_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void PRV_USART_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, (uint8_t)eIrq, bEnable);
}
#endif

#if defined(USART_FEATURE_MASTER_SS_PIN_BY_GPIO)
static __inline void USART_SetSSPort(P_USART_ID_e eId, bool bLevel)
{
    PORT_Type *ptPcu;
    uint8_t un8PortNum = 0;

    switch(eId)
    {
#if (CONFIG_USART_MAX_COUNT > 0)
        case P_USART_ID_0:
            ptPcu = (PORT_Type *)USART_0_SS_PORT;
            un8PortNum = USART_0_SS_PIN;
            break; 
#endif
#if (CONFIG_USART_MAX_COUNT > 1)
        case P_USART_ID_1:
            ptPcu = (PORT_Type *)USART_1_SS_PORT;
            un8PortNum = USART_1_SS_PIN;
            break; 
#endif
#if (CONFIG_USART_MAX_COUNT > 2)
        case P_USART_ID_2:
            ptPcu = (PORT_Type *)USART_2_SS_PORT;
            un8PortNum = USART_2_SS_PIN;
            break; 
#endif
#if (CONFIG_USART_MAX_COUNT > 3)
        case P_USART_ID_3:
            ptPcu = (PORT_Type *)USART_3_SS_PORT;
            un8PortNum = USART_3_SS_PIN;
            break; 
#endif
        default:
            return;
    }

    SET_PCU_USART_SS_PIN(ptPcu, un8PortNum, bLevel);
}
#endif

#endif /* _HAL_USART_F1X_H_ */
