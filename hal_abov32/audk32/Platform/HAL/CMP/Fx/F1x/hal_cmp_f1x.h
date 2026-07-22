/**
 *******************************************************************************
 * @file        hal_cmp_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed CMP
 *
 * Copyright 2025 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_CMP_F1X_H_
#define _HAL_CMP_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define CMP_CH_NUM                                    CONFIG_CMP_MAX_COUNT

#if (CONFIG_CMP_VER_EXT == 0)

#if (CONFIG_CMP_VER_MINOR == 0)
#include "hal_cmp_f_01_00_00.h"
#elif (CONFIG_CMP_VER_MINOR == 1)
#include "hal_cmp_f_01_00_01.h"
#else
#error "define CONFIG_CMP_VER_MINOR of F-type CMP at config_xxx.h"
#endif

#else
#error "define CONFIG_CMP_VER_EXT of F-type CMP at config_xxx.h"
#endif

static __inline CMP_Type *CMP_GetCRReg(P_CMP_ID_e eId)
{
    return (CMP_Type *)(CMP_REG_BASE + CMP_CR_REG_OFFSET);
}

static __inline CMP_Type *CMP_GetReg(P_CMP_ID_e eId)
{
    return (CMP_Type *)(CMP_REG_BASE);
}

static __inline IRQn_Type CMP_GetIRQNum(P_CMP_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(CMP_0_IRQ)
        case P_CMP_ID_0:
            eIrq = CMP_0_IRQ;
            break;
#endif
#if defined(CMP_1_IRQ)
        case P_CMP_ID_1:
            eIrq = CMP_1_IRQ;
            break;
#endif
#if defined(CMP_2_IRQ)
        case P_CMP_ID_2:
            eIrq = CMP_2_IRQ;
            break;
#endif
#if defined(CMP_3_IRQ)
        case P_CMP_ID_3:
            eIrq = CMP_3_IRQ;
            break;
#endif
#if defined(CMP_4_IRQ)
        case P_CMP_ID_4:
            eIrq = CMP_4_IRQ;
            break;
#endif
#if defined(CMP_5_IRQ)
        case P_CMP_ID_5:
            eIrq = CMP_5_IRQ;
            break;
#endif
#if defined(CMP_6_IRQ)
        case P_CMP_ID_6:
            eIrq = CMP_6_IRQ;
            break;
#endif
#if defined(CMP_7_IRQ)
        case P_CMP_ID_7:
            eIrq = CMP_7_IRQ;
            break;
#endif
#if defined(CMP_8_IRQ)
        case P_CMP_ID_8:
            eIrq = CMP_8_IRQ;
            break;
#endif
#if defined(CMP_9_IRQ)
        case P_CMP_ID_9:
            eIrq = CMP_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline HAL_ERR_e CMP_SetScuEnable(P_CMP_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_CMP_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_CMP_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_CMP_PCER(ptScu, (uint32_t)eId, un32Enable);

    return HAL_ERR_OK;
}

static __inline void CMP_SetWkupSrc(bool bEnable)
{
#if defined(CMP_FEATURE_WAKEUP)
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    SET_SCU_CMP_WKUP_EN(ptScu, bEnable);
#else
    (void)bEnable;
#endif
}

static __inline void CMP_GetWkupEvent(bool *bEvent)
{
#if defined(CMP_FEATURE_WAKEUP)
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    uint8_t un8Prev = GET_SCU_CMP_PREVMODE(ptScu);

    if(GET_SCU_CMP_WKUP_EN(ptScu))
    {
        if(un8Prev == 0x01 || un8Prev == 0x07)
        {
            *bEvent = GET_SCU_CMP_WKUP_FLAG(ptScu);
        }
    }
#else
    *bEvent = false;
#endif
}

#if defined(CMP_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void CMP_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, (uint8_t)eIrq, bEnable);
}
#endif

#endif /* _HAL_CMP_F1X_H_ */
