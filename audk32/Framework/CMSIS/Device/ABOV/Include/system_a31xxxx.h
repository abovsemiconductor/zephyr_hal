/**
 *******************************************************************************
 * @file        system_a31xxxx.h
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


#ifndef SYSTEM_A31XXXX_H
#define SYSTEM_A31XXXX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef void(*VECTOR_TABLE_Type)(void);

/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */
extern uint32_t SystemPeriClock;     /*!< System Clock Frequency (Peri Clock)  */
extern uint32_t SystemDelayMSCount;  /*!< System Delay Milli-second Count */
extern uint32_t SystemDelayUSCount;  /*!< System Delay Micro-second Count */


/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit(void);

///**
// * Initialize the system
// *
// * @param  none
// * @return none
// *
// * @brief  Setup the microcontroller system.
// *         Initialize the System and update the SystemCoreClock variable.
// */
//extern void SystemCoreClockUpdate(void);

extern void SystemDelayMS(uint32_t ms);
extern void SystemDelayUS(uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_A31XXXX_H */
