/**
 *******************************************************************************
 * @file        hll_i2c.c
 * @author      ABOV R&D Division
 * @brief       Inter-Integrated Circuit (Low Level)
 *
 * Copyright 2026 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#include "abov_config.h"

/*
 * This file is picked up unconditionally by the audk32 HAL library's
 * file(GLOB_RECURSE ...) over every .c file under Platform/HAL/ (see
 * modules/hal/abov32/audk32/CMakeLists.txt) regardless of whether any app
 * actually uses the I2C driver. hll_i2c.h pulls in hal_i2c_prv.h's I2C-IP-
 * version dispatch, which #errors unless _MODULE_I2C (and thus
 * CONFIG_I2C_VER_VENDOR etc.) is defined -- so, like hal_i2c.c, this whole
 * file must stay inert unless _I2C is actually set, instead of only
 * compiling correctly by accident whenever some other translation unit
 * happens to already need CONFIG_HAL_I2C == 1.
 */
#if defined(_I2C)
#include "hll_i2c.h"

void HLL_I2C_CalcSclPeriod(uint32_t un32Freq, uint16_t *pun16Scll, uint16_t *pun16Sclh)
{
    uint16_t un16Scll = (uint16_t)(((SystemPeriClock / un32Freq) / 2U) - 2U);

    *pun16Scll = un16Scll;
    *pun16Sclh = (uint16_t)(un16Scll - 1U);
}

#endif /* _I2C */
