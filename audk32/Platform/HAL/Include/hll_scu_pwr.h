/**
 *******************************************************************************
 * @file        hll_scu_pwr.h
 * @author      ABOV R&D Division
 * @brief       Power sub system in System Control Unit (Low Level)
 *
 * Copyright 2026 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/**
 * @addtogroup  HLL HLL (Hardware Low Level)
 * @{
 * @defgroup    HLL_SCU_PWR SCU_PWR
 * @{
 * @brief       Power sub system in System Control Unit (SCU), Low Level
 *
 * SCU_PWR has no wake-up IRQ on this SoC, so most of HAL_SCU_PWR's surface
 * (deep-sleep sub modes, wake-up IRQ, backup data, flash power extension,
 * port pull-up/down) is a stub here. Deep-sleep depth (STOP1 vs STOP2) is
 * selected via SCU.SMR's LSIAON/LSEAON bits (HLL_SCU_PWR_SetAlwaysOnMask()),
 * not by HAL_SCU_PWR_SetMode()'s DEEPSLEEP/DEEPSLEEP2 split, which is a
 * no-op distinction on this IP version.
 */

#ifndef _HLL_SCU_PWR_H_
#define _HLL_SCU_PWR_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"
#include "type/scu_pwr_type.h"
#include "../SCU/hal_scu_prv.h"

#define HLL_SCU_PWR_REG    ((SCU_Type *)SCU_REG_BASE)

/**
 * @brief Raw SCU.SMR bit positions for each Always-on source real on this
 *        IP version (LSE/HSI/HSE exist here but aren't used by HAL_SCU_PWR).
 */
#define HLL_SCU_PWR_AON_VDC_POS    BIT_SCU_SMR_VDC_POS
#define HLL_SCU_PWR_AON_LSI_POS    BIT_SCU_SMR_LSI_POS
#define HLL_SCU_PWR_AON_LSE_POS    BIT_SCU_SMR_LSE_POS
#define HLL_SCU_PWR_AON_HSI_POS    BIT_SCU_SMR_HSI_POS
#define HLL_SCU_PWR_AON_HSE_POS    BIT_SCU_SMR_HSE_POS

/**
 * @brief Enter Sleep mode: CPU clock stops, peripherals keep running, any
 *        enabled interrupt wakes the CPU back up.
 */
__STATIC_INLINE void HLL_SCU_PWR_EnterSleep(void)
{
    SCB->SCR = 0;
    __WFI();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
}

/**
 * @brief Enter Deep-sleep mode. Call HLL_SCU_PWR_SetAlwaysOnMask() first:
 *        LSIAON and/or LSEAON set selects STOP1 (WDT/FRT stay powered),
 *        both clear selects STOP2 (nothing does). Also arm the needed
 *        wake source in SCU.WUER (HLL_SCU_PWR_SetWakeUpEnableMask()) first.
 */
__STATIC_INLINE void HLL_SCU_PWR_EnterDeepSleep(void)
{
    SCB->SCR = 0x04;
    __WFI();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
}

/**
 * @brief Set which blocks stay powered after Deep-sleep (LSIAON/LSEAON also
 *        select STOP1 vs STOP2). Whole-register: OR together
 *        `1UL << HLL_SCU_PWR_AON_xxx_POS` bits -- SCUPWR_AON_e's own bit
 *        values use a different layout.
 */
__STATIC_INLINE void HLL_SCU_PWR_SetAlwaysOnMask(uint32_t un32Mask)
{
    SET_SCU_SMR(HLL_SCU_PWR_REG, un32Mask);
}

/**
 * @brief Read back the current Always-on/STOP1-vs-STOP2 mask.
 */
__STATIC_INLINE uint32_t HLL_SCU_PWR_GetAlwaysOnMask(void)
{
    return GET_REG(HLL_SCU_PWR_REG, SMR);
}

/**
 * @brief Raw SCU.WUER/WUSR bit positions for each wake-up source this IP
 *        defines. WUSR (status) mirrors WUER (enable) at the same bit
 *        positions, so these constants serve both registers.
 */
#define HLL_SCU_PWR_WKUP_LVI_POS        SCU_WUER_LVIWUE_Pos
#define HLL_SCU_PWR_WKUP_WDT_POS        SCU_WUER_WDTWUE_Pos
#define HLL_SCU_PWR_WKUP_FRT_POS        SCU_WUER_FRTWUE_Pos
#define HLL_SCU_PWR_WKUP_RTCC_POS       SCU_WUER_RTCCWUE_Pos
#define HLL_SCU_PWR_WKUP_USART10_POS    SCU_WUER_USART10WUE_Pos
#define HLL_SCU_PWR_WKUP_USART11_POS    SCU_WUER_USART11WUE_Pos
#define HLL_SCU_PWR_WKUP_USART12_POS    SCU_WUER_USART12WUE_Pos
#define HLL_SCU_PWR_WKUP_GPIOA_POS      SCU_WUER_GPIOAWUE_Pos
#define HLL_SCU_PWR_WKUP_GPIOB_POS      SCU_WUER_GPIOBWUE_Pos
#define HLL_SCU_PWR_WKUP_GPIOC_POS      SCU_WUER_GPIOCWUE_Pos
#define HLL_SCU_PWR_WKUP_GPIOD_POS      SCU_WUER_GPIODWUE_Pos
#define HLL_SCU_PWR_WKUP_GPIOE_POS      SCU_WUER_GPIOEWUE_Pos
#define HLL_SCU_PWR_WKUP_GPIOF_POS      SCU_WUER_GPIOFWUE_Pos

/**
 * @brief Arm which events can wake the CPU from Deep-sleep. Whole-register:
 *        OR together `1UL << HLL_SCU_PWR_WKUP_xxx_POS` bits. Reset value is
 *        0 (nothing armed); plain Sleep mode wakes on any enabled NVIC
 *        interrupt regardless of this register.
 */
__STATIC_INLINE void HLL_SCU_PWR_SetWakeUpEnableMask(uint32_t un32Mask)
{
    SET_REG(HLL_SCU_PWR_REG, un32Mask, WUER);
}

/**
 * @brief Read back the current wake-up-source enable mask (SCU.WUER).
 */
__STATIC_INLINE uint32_t HLL_SCU_PWR_GetWakeUpEnableMask(void)
{
    return GET_REG(HLL_SCU_PWR_REG, WUER);
}

/**
 * @brief Read which wake-up source(s) actually fired (SCU.WUSR), using the
 *        same HLL_SCU_PWR_WKUP_*_POS positions as WUER. Read-only; unlike
 *        WUER this reflects hardware status, not something you set.
 */
__STATIC_INLINE uint32_t HLL_SCU_PWR_GetWakeUpStatusMask(void)
{
    return GET_REG(HLL_SCU_PWR_REG, WUSR);
}

/**
 * @brief Set the VDC (core regulator) wake-up delay count.
 */
__STATIC_INLINE void HLL_SCU_PWR_SetVdcDelay(uint8_t un8Delay)
{
    SET_SCU_DATA_VDC_DELAY(HLL_SCU_PWR_REG, un8Delay);
}

/**
 * @brief Drive the power-down indicator pin level.
 */
__STATIC_INLINE void HLL_SCU_PWR_SetPDIndicator(bool bLevel)
{
    SET_SCU_PD_IND_LVL(HLL_SCU_PWR_REG, bLevel);
}

#ifdef __cplusplus
}
#endif

#endif /* _HLL_SCU_PWR_H_ */

/** @} */
/** @} */
