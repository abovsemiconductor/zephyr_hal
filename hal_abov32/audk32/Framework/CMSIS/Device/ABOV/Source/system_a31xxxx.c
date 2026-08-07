/**
 *******************************************************************************
 * @file        system_a31xxxx.c
 * @author      ABOV R&D Division
 * @brief       CMSIS Cortex-M0+ Device Peripheral Access Layer for A31xxxx
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#include <stdint.h>
#include "abov_config.h"

#if !defined (EXTRN_FPA)
extern const VECTOR_TABLE_Type __VECTOR_TABLE[48];
#endif

/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/

void SystemInit (void)
{
    __disable_irq();

#if !defined (EXTRN_FPA_CFMC) && !defined (EXTRN_FPA_DFMC)
    SCB->VTOR = (uint32_t)(&__VECTOR_TABLE[0]);
#endif

    PRV_CHIPSET_Init();

    __enable_irq();
}

void SystemDelayMS(uint32_t ms)
{
    uint32_t i;
    uint32_t Delay = (SystemDelayMSCount) * ms;
    for (i=0; i < Delay; i++)
    {
        __NOP();
    }
}

void SystemDelayUS(uint32_t us)
{
    uint32_t i;
    uint32_t Delay = (SystemDelayUSCount) * us;
    for (i=0; i < Delay; i++)
    {
        __NOP();
    }
}
