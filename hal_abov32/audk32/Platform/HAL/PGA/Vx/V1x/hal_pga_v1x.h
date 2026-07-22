/**
 *******************************************************************************
 * @file        hal_pga_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed PGA
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_PGA_V1X_H_
#define _HAL_PGA_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define PGA_CH_NUM                                    CONFIG_PGA_MAX_COUNT

#if (CONFIG_PGA_VER_EXT == 0)

#if (CONFIG_PGA_VER_MINOR == 0)
#include "hal_pga_v_01_00_00.h"
#else
#error "define CONFIG_PGA_VER_MINOR of V-type PGA at config_xxx.h"
#endif

#else
#error "define CONFIG_PGA_VER_EXT of V-type PGA at config_xxx.h"
#endif

static __inline PGA_Type *PGA_GetReg(P_PGA_ID_e eId)
{
    return (PGA_Type *)(PGA_REG_BASE + (PGA_REG_OFFSET * (uint32_t)eId));
}

static __inline HAL_ERR_e PGA_SetScuEnable(P_PGA_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_PGA_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_PGA_PER(ptScu, un32Enable);
    SET_SCU_PGA_PCER(ptScu, un32Enable);

    return HAL_ERR_OK;
}

#endif /* _HAL_PGA_V1X_H_ */
