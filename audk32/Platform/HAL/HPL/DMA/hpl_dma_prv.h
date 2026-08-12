/**
 *******************************************************************************
 * @file        hpl_dma_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for DMA
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HPL_DMA_PRV_H_
#define _HPL_DMA_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_DMA_ID_0,
    P_DMA_ID_1,
    P_DMA_ID_2,
    P_DMA_ID_3,
    P_DMA_ID_4,
    P_DMA_ID_5,
    P_DMA_ID_6,
    P_DMA_ID_7,
    P_DMA_ID_8,
    P_DMA_ID_9,
    P_DMA_ID_10,
    P_DMA_ID_11,
    P_DMA_ID_12,
    P_DMA_ID_13,
    P_DMA_ID_14,
    P_DMA_ID_15,
    P_DMA_ID_MAX
} P_DMA_ID_e;

typedef enum
{
    P_DMA_IRQ_ID_0,
    P_DMA_IRQ_ID_1,
    P_DMA_IRQ_ID_2,
    P_DMA_IRQ_ID_3,
    P_DMA_IRQ_ID_4,
    P_DMA_IRQ_ID_5,
    P_DMA_IRQ_ID_6,
    P_DMA_IRQ_ID_7,
    P_DMA_IRQ_ID_8,
    P_DMA_IRQ_ID_9,
    P_DMA_IRQ_ID_MAX
} P_DMA_IRQ_ID_e;

#if (CONFIG_DMA_VER_VENDOR == 'V')

#if (CONFIG_DMA_VER_MAJOR == 1)
#include "Vx/V1x/hpl_dma_v1x.h"
#else
#error "define CONFIG_DMA_VER_MAJOR of V-type DMA at config_xxx.h"
#endif

#elif (CONFIG_DMA_VER_VENDOR == 'F')

#if (CONFIG_DMA_VER_MAJOR == 1)
#include "Fx/F1x/hpl_dma_f1x.h"
#else
#error "define CONFIG_DMA_VER_MAJOR of F-type DMA at config_xxx.h"
#endif

#else
#error "define CONFIG_DMA_VER_VENDOR of DMA at config_xxx.h"
#endif

#endif /* _HPL_DMA_PRV_H_ */
