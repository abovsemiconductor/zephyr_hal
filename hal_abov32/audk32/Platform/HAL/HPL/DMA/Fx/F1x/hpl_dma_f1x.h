/**
 *******************************************************************************
 * @file        hpl_dma_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed DMA
 *
 * Copyright 2025 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HPL_DMA_F1X_H_
#define _HPL_DMA_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define DMA_CH_NUM                                    CONFIG_DMA_MAX_COUNT

#if (CONFIG_DMA_VER_EXT == 0)

#if (CONFIG_DMA_VER_MINOR == 0)
#include "hpl_dma_f_01_00_00.h"
#elif (CONFIG_DMA_VER_MINOR == 1)
#include "hpl_dma_f_01_00_01.h"
#elif (CONFIG_DMA_VER_MINOR == 2)
#include "hpl_dma_f_01_00_02.h"
#else
#error "define CONFIG_DMA_VER_MINOR of F-type DMA at config_xxx.h"
#endif

#else
#error "define CONFIG_DMA_VER_EXT of F-type DMA at config_xxx.h"
#endif

static __inline HAL_ERR_e DMA_SetScuEnable(uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    SET_SCU_DMA_PER(ptScu, un32Enable);
    SET_SCU_DMA_PCER(ptScu, un32Enable);

    return HAL_ERR_OK;
}

static __inline DMA_Type *DMA_GetReg(P_DMA_ID_e eId)
{
    return (DMA_Type *)(DMA_REG_BASE + (DMA_REG_OFFSET * (uint32_t)eId));
}

static __inline IRQn_Type DMA_GetIRQNum(uint8_t un8Idx)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(un8Idx)
    {
#if defined(DMA_0_IRQ)
        case 0:
            eIrq = DMA_0_IRQ;
            break;
#endif
#if defined(DMA_1_IRQ)
        case 1:
            eIrq = DMA_1_IRQ;
            break;
#endif
#if defined(DMA_2_IRQ)
        case 2:
            eIrq = DMA_2_IRQ;
            break;
#endif
#if defined(DMA_3_IRQ)
        case 3:
            eIrq = DMA_3_IRQ;
            break;
#endif
#if defined(DMA_4_IRQ)
        case 4:
            eIrq = DMA_4_IRQ;
            break;
#endif
#if defined(DMA_5_IRQ)
        case 5:
            eIrq = DMA_5_IRQ;
            break;
#endif
#if defined(DMA_6_IRQ)
        case 6:
            eIrq = DMA_6_IRQ;
            break;
#endif
#if defined(DMA_7_IRQ)
        case 7:
            eIrq = DMA_7_IRQ;
            break;
#endif
#if defined(DMA_8_IRQ)
        case 8:
            eIrq = DMA_8_IRQ;
            break;
#endif
#if defined(DMA_9_IRQ)
        case 9:
            eIrq = DMA_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

#if defined(DMA_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void DMA_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, (uint8_t)eIrq, bEnable);
}
#endif

#endif /* _HPL_DMA_F1X_H_ */
