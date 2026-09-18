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

#if defined(_I2C)
#include "hll_i2c.h"

void HLL_I2C_CalcSclPeriod(uint32_t un32Freq, uint16_t *pun16Scll, uint16_t *pun16Sclh)
{
    uint16_t un16Scll = (uint16_t)(((SystemPeriClock / un32Freq) / 2U) - 2U);

    *pun16Scll = un16Scll;
    *pun16Sclh = (uint16_t)(un16Scll - 1U);
}

#endif /* _I2C */
