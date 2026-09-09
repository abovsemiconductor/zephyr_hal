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
 * Unlike HAL_SCU_PWR, this layer does not own a control block: SCU_PWR has
 * no wake-up interrupt at all on this SoC series (SCUPMU_WKUP_IRQ, along
 * with the whole SCUPMU_Type/SCUPMU_REG_BASE register block it lives on, is
 * only defined for other ABOV chip families' version files, not this one's
 * -- config_a31c15x.h's `_MODULE_SCU_PWR` block, unlike the `_SCU_LVD` block
 * right above it, defines no IRQ handler/number).
 *
 * Consequently most of HAL_SCU_PWR's surface is a stub on this chip (deep-
 * sleep sub modes, wake-up IRQ, backup data, flash power extension, and
 * port pull-up/down all compile to HAL_ERR_NOT_SUPPORTED here). But that
 * HAL surface was written against a *different* ABOV chip family's power
 * architecture (SCUPMU_Type registers) that A31C15x doesn't have -- it is
 * NOT the real story for this chip. Per the A31C15x user's manual (section
 * 4.7, Operating Modes), the real mode set is RUN / SLEEP / DEEP-SLEEP, and
 * DEEP-SLEEP itself has two real depths, STOP1 and STOP2, both reachable
 * through registers this file already had reason to touch:
 *
 * - SLEEP: SCB.SCR.SLEEPDEEP = 0, then WFI.
 * - DEEP-SLEEP: SCB.SCR.SLEEPDEEP = 1, then WFI. Which depth you get is
 *   decided beforehand by SCU.SMR's LSIAON (bit 9) and LSEAON (bit 13) --
 *   the exact same Always-on mask HLL_SCU_PWR_SetAlwaysOnMask() below
 *   already writes for a completely different-sounding reason. If either
 *   is set: STOP1 (every VDC-domain peripheral except WDT and FRT loses
 *   power). If both are clear (the reset default): STOP2 (everything in
 *   the VDC domain stops, no exceptions). HAL_SCU_PWR_SetMode()'s
 *   SCUPWR_MODE_DEEPSLEEP vs SCUPWR_MODE_DEEPSLEEP2 split is a red
 *   herring: it tries to distinguish them via SET_SCU_VDC_DEEPSLEEP(),
 *   which is `(void)Peri` on this chip's IP version (a genuine no-op) --
 *   that HAL function cannot actually select STOP1 vs STOP2 here at all.
 *   So there's a single HLL_SCU_PWR_EnterDeepSleep() below, not two: call
 *   HLL_SCU_PWR_SetAlwaysOnMask() first with LSIAON/LSEAON set (or clear)
 *   as needed, exactly as you would to pick an Always-on source.
 * - Waking back up from either Sleep or Deep-sleep needs the relevant
 *   source armed in SCU.WUER (Wake-up Source Enable Register) beforehand
 *   -- WFI alone only blocks until *some* interrupt is pending, but on
 *   this chip DEEP-SLEEP additionally gates which events even reach the
 *   core through WUER, and its reset value is 0 (no source armed) for
 *   both STOP1 and STOP2. See HLL_SCU_PWR_SetWakeUpEnableMask() below.
 *
 * What this header wraps, all real on this SoC series' SCU IP version
 * (hal_scu_v_04_00_00.h / a31c15x.h, both verified directly):
 *
 * - Sleep and deep-sleep entry (SCB.SCR + WFI, with the vendor HAL's own
 *   post-WFI NOP padding kept).
 * - The Always-on/STOP1-vs-STOP2 mask (SCU.SMR). Unlike HAL_SCU_PWR_SetAlwaysOn()
 *   (which builds this value one bit at a time from a caller-supplied
 *   SCUPWR_AON_e bitmask, but only ever does a plain write, and only ever
 *   acts on 2 of its 8 bits -- no SCUPWR_AON_LSE_EN/_HSI_EN/_HSE_EN
 *   feature flag is defined for this IP version even though those bit
 *   positions are real), HLL_SCU_PWR_SetAlwaysOnMask()/GetAlwaysOnMask()
 *   below expose the real register directly (SMR is `__IO`, genuinely
 *   readable, just never given a named GET_ macro upstream) with position
 *   constants for all 5 bits this IP version's register map actually
 *   defines (VDC/LSI/LSE/HSI/HSE; there is no BGR/PLL/EXTCLK bit at all
 *   on this chip despite SCUPWR_AON_e implying 8 sources).
 * - The wake-up-source enable/status registers (SCU.WUER/WUSR) -- not
 *   wrapped by HAL_SCU_PWR at all (its wake-up-IRQ path is entirely
 *   SCUPMU_Type-gated and compiles out on this chip), even though the
 *   real WUER/WUSR registers and their per-source bit positions are
 *   already in a31c15x.h. Of those, only LVIWUE/RTCCWUE have existing
 *   vendor-wrapped SET_SCU_LVD_WKUP_EN()/SET_SCU_RTC_WKUP_EN()-style
 *   macros elsewhere (for the LVI/RTC peripherals' own use) -- WDT/FRT/
 *   USART10-12/GPIOA-F have none, so this file accesses SCU.WUER/WUSR as
 *   plain whole registers via hal_common.h's generic SET_REG()/GET_REG(),
 *   with position constants sourced directly from a31c15x.h's own
 *   SCU_WUER_*_Pos defines (no IP-version dispatch needed for these; the
 *   register layout comes straight from the chip header, not a version
 *   file).
 * - VDC delay (SCU.VDCCON.VDCWDLY) and the power-down pin level indicator
 *   (SCU.SRCR.STBYO, gated by SCU_FEATURE_POWER_DOWN_PIN_LEVEL, which *is*
 *   defined for this IP version) -- both plain, always-real register bits,
 *   independent of the Sleep/Deep-sleep mechanics above.
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
 * @brief Raw SCU.SMR bit positions for each Always-on source that's real on
 *        this IP version. See the file-level comment: LSE/HSI/HSE exist in
 *        the register map but aren't exercised by HAL_SCU_PWR on this chip.
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
 * @brief Enter Deep-sleep mode (STOP1 or STOP2). Call
 *        HLL_SCU_PWR_SetAlwaysOnMask() first to pick which: LSIAON and/or
 *        LSEAON set selects STOP1 (WDT/FRT stay powered), both clear
 *        selects STOP2 (nothing does) -- see the file-level comment, this
 *        is not what SCUPWR_MODE_DEEPSLEEP vs SCUPWR_MODE_DEEPSLEEP2
 *        would suggest. Also make sure the wake source you need is armed
 *        in SCU.WUER (HLL_SCU_PWR_SetWakeUpEnableMask()) beforehand.
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
 * @brief Set which blocks stay powered (Always-on) after Deep-sleep, and
 *        (LSIAON/LSEAON specifically) select STOP1 vs STOP2 -- see the
 *        file-level comment. Whole-register: OR together
 *        `1UL << HLL_SCU_PWR_AON_xxx_POS` bits yourself rather than
 *        passing SCUPWR_AON_e's own bit values directly -- the two bit
 *        layouts are not the same.
 */
__STATIC_INLINE void HLL_SCU_PWR_SetAlwaysOnMask(uint32_t un32Mask)
{
    SET_SCU_SMR(HLL_SCU_PWR_REG, un32Mask);
}

/**
 * @brief Read back the current Always-on/STOP1-vs-STOP2 mask (SCU.SMR is
 *        `__IO`, genuinely readable in hardware -- see the file comment).
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
 * @brief Arm which events can wake the CPU from Sleep/Deep-sleep. Whole-
 *        register: OR together `1UL << HLL_SCU_PWR_WKUP_xxx_POS` bits.
 *        Reset value is 0 (nothing armed) -- required even for Sleep
 *        mode's ordinary interrupt-driven wake-up on this chip's
 *        DEEP-SLEEP path, per the user's manual; for plain Sleep mode any
 *        enabled NVIC interrupt already wakes the core regardless of
 *        WUER, so this mainly matters before HLL_SCU_PWR_EnterDeepSleep().
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
