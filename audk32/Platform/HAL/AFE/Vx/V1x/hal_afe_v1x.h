/**
 *******************************************************************************
 * @file        hal_afe_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed AFE
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_AFE_V1X_H_
#define _HAL_AFE_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define AFE_CH_NUM                                    CONFIG_AFE_MAX_COUNT

#if (CONFIG_AFE_VER_EXT == 0)

#if (CONFIG_AFE_VER_MINOR == 0)
#include "hal_afe_v_01_00_00.h"
#else
#error "define CONFIG_AFE_VER_MINOR of V-type AFE at config_xxx.h"
#endif

#else
#error "define CONFIG_AFE_VER_EXT of V-type AFE at config_xxx.h"
#endif

static __inline AFE_Type *AFE_GetCRReg(P_AFE_ID_e eId)
{
    if(eId == P_AFE_ID_1)
    {
        return (AFE_Type *)(AFE_REG_BASE + AFE_CR_REG_OFFSET);
    }
    else
    {
        return (AFE_Type *)(AFE_REG_BASE);
    }
}

static __inline AFE_Type *AFE_GetReg(P_AFE_ID_e eId)
{
    return (AFE_Type *)(AFE_REG_BASE);
}

static __inline IRQn_Type AFE_GetIRQNum(P_AFE_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(AFE_0_IRQ)
        case P_AFE_ID_0:
            eIrq = AFE_0_IRQ;
            break;
#endif
#if defined(AFE_1_IRQ)
        case P_AFE_ID_1:
            eIrq = AFE_1_IRQ;
            break;
#endif
#if defined(AFE_2_IRQ)
        case P_AFE_ID_2:
            eIrq = AFE_2_IRQ;
            break;
#endif
#if defined(AFE_3_IRQ)
        case P_AFE_ID_3:
            eIrq = AFE_3_IRQ;
            break;
#endif
#if defined(AFE_4_IRQ)
        case P_AFE_ID_4:
            eIrq = AFE_4_IRQ;
            break;
#endif
#if defined(AFE_5_IRQ)
        case P_AFE_ID_5:
            eIrq = AFE_5_IRQ;
            break;
#endif
#if defined(AFE_6_IRQ)
        case P_AFE_ID_6:
            eIrq = AFE_6_IRQ;
            break;
#endif
#if defined(AFE_7_IRQ)
        case P_AFE_ID_7:
            eIrq = AFE_7_IRQ;
            break;
#endif
#if defined(AFE_8_IRQ)
        case P_AFE_ID_8:
            eIrq = AFE_8_IRQ;
            break;
#endif
#if defined(AFE_9_IRQ)
        case P_AFE_ID_9:
            eIrq = AFE_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline HAL_ERR_e AFE_SetScuEnable(P_AFE_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_AFE_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_AFE_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_AFE_PCER(ptScu, (uint32_t)eId, un32Enable);

    return HAL_ERR_OK;
}

static __inline void AFE_SetWkupSrc(bool bEnable)
{
#if defined(AFE_FEATURE_WAKEUP)
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    SET_SCU_AFE_WKUP_EN(ptScu, bEnable);
#else
    (void)bEnable;
#endif
}

static __inline void AFE_GetWkupEvent(bool *bEvent)
{
#if defined(AFE_FEATURE_WAKEUP)
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    uint8_t un8Prev = GET_SCU_AFE_PREVMODE(ptScu);

    if(GET_SCU_AFE_WKUP_EN(ptScu))
    {
        if(un8Prev == 0x01 || un8Prev == 0x07)
        {
            *bEvent = GET_SCU_AFE_WKUP_FLAG(ptScu);
        }
    }
#else
    *bEvent = false;
#endif
}

#endif /* _HAL_AFE_V1X_H_ */
