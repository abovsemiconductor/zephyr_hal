/**
 *******************************************************************************
 * @file        hll_pcu.c
 * @author      ABOV R&D Division
 * @brief       Port Control Unit (Low Level)
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

#include "hll_pcu.h"
#include "hal_pcu_prv.h"

void HLL_PCU_SetRTCPortInOutMode(PCU_ID_e eId, PCU_PIN_ID_e ePinId, PCU_INOUT_e eInOut)
{
#if defined(PCU_FEATURE_RTC_PORT)
    PCU_SetRTCPortInOutMode((P_PCU_ID_e)eId, (P_PCU_PIN_ID_e)ePinId, (P_PCU_INOUT_e)eInOut);
#else
    (void)eId;
    (void)ePinId;
    (void)eInOut;
#endif
}
