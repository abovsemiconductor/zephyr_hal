/**
 *******************************************************************************
 * @file        hpl_dma_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed DMA
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HPL_DMA_V1X_H_
#define _HPL_DMA_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define DMA_CH_NUM                                    CONFIG_DMA_MAX_COUNT

#if (CONFIG_DMA_VER_EXT == 0)

#if (CONFIG_DMA_VER_MINOR == 0)
#include "hpl_dma_v_01_00_00.h"
#elif (CONFIG_DMA_VER_MINOR == 1)
#include "hpl_dma_v_01_00_01.h"
#else
#error "define CONFIG_DMA_VER_MINOR of V-type DMA at config_xxx.h"
#endif

#else
#error "define CONFIG_DMA_VER_EXT of V-type DMA at config_xxx.h"
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

#endif /* _HPL_DMA_PRV_H_ */
