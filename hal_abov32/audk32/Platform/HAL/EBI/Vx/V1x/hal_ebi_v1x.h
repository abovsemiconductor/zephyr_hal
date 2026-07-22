/**
 *******************************************************************************
 * @file        hal_ebi_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed EBI
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_EBI_V1X_H_
#define _HAL_EBI_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define EBI_CH_NUM                                    CONFIG_EBI_MAX_COUNT
#define EBI_CS_NUM                                    CONFIG_EBI_CS_MAX_COUNT

#if (CONFIG_EBI_VER_EXT == 0)

#if (CONFIG_EBI_VER_MINOR == 0)
#include "hal_ebi_v_01_00_00.h"
#else
#error "define CONFIG_EBI_VER_MINOR of V-type EBI at config_xxx.h"
#endif

#else
#error "define CONFIG_EBI_VER_EXT of V-type EBI at config_xxx.h"
#endif

static __inline EBI_Type *EBI_GetReg(P_EBI_ID_e eId)
{
        return (EBI_Type *)(EBI_REG_BASE);
}

static __inline HAL_ERR_e EBI_SetScuEnable(P_EBI_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_EBI_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_PER_EBI(ptScu,(uint32_t)eId,un32Enable);
    SET_SCU_PCER_EBI(ptScu,(uint32_t)eId,un32Enable);

    return HAL_ERR_OK;
}

#endif /* _HAL_EBI_V1X_H_ */
