/**
 *******************************************************************************
 * @file        hal_scu.c
 * @author      ABOV R&D Division
 * @brief       System Control Unit
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#include "abov_config.h"
#include "hll_scu.h"
#include "hpl_nmi.h"

HAL_ERR_e HLL_SCU_SetReset(SCU_RST_e eRst, bool bEnable)
{
#if defined(SCU_FEATURE_VX_RESET_ENABLE)
    switch (eRst)
    {
        case SCU_RST_SW:
            SET_SCU_RSER_SW_EN(HLL_SCU_REG, bEnable);
            break;

        case SCU_RST_CPU:
            SET_SCU_RSER_CPU_EN(HLL_SCU_REG, bEnable);
            break;

        case SCU_RST_EXT_PIN:
            SET_SCU_RSER_EXTPIN_EN(HLL_SCU_REG, bEnable);
            break;

#if defined(SCU_FEATURE_RST_CPU_LOCKUP)
        case SCU_RST_CPU_LOCKUP:
            SET_SCU_RSER_CPU_LOCKUP_EN(HLL_SCU_REG, bEnable);
            break;
#endif

        default:
            return HAL_ERR_PARAMETER;
    }

    return HAL_ERR_OK;

#elif defined(SCU_FEATURE_FX_RESET_ENABLE)

    (void)eRst;
    (void)bEnable;

    return HAL_ERR_OK;

#else

    (void)eRst;
    (void)bEnable;

    return HAL_ERR_NOT_SUPPORTED;
#endif
}
