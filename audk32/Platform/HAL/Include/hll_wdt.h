/**
 *******************************************************************************
 * @file        hll_wdt.h
 * @author      ABOV R&D Division
 * @brief       Watch Dog Timer (Low Level)
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
 * @defgroup    HLL_WDT WDT
 * @{
 * @brief       Watch Dog Timer, Low Level
 *
 * Unlike HAL_WDT, this layer does not own a control block or interrupt
 * vector: it only wraps direct register access. Callers are expected to
 * connect the IRQ returned by HLL_WDT_GetIRQNum() to their own handler.
 *
 * Match-counter (window) mode is not implemented on every WDT IP version --
 * HLL_WDT_SetMatchValue()/GetMatchValue()/SetMatchIntrEnable()/
 * GetMatchFlag()/ClearMatchFlag() are no-ops (and GetMatchValue()/
 * GetMatchFlag() read back 0) wherever the active version header doesn't
 * back them with real bits (see e.g. hal_wdt_v_01_00_02.h's "Unused Macro"
 * section) -- check WDT_MODE_CNT support before relying on them.
 */

#ifndef _HLL_WDT_H_
#define _HLL_WDT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"
#include "type/wdt_type.h"
#include "../WDT/hal_wdt_prv.h"

#define HLL_WDT_REG(eId)    WDT_GetReg((P_WDT_ID_e)(eId))

/**
 * @brief Get the NVIC IRQ number for a WDT instance.
 *
 * The caller owns the vector: connect this IRQ number to its own handler
 * (e.g. via the host RTOS's IRQ_CONNECT-equivalent) instead of relying on
 * a fixed-name weak handler.
 */
__STATIC_INLINE IRQn_Type HLL_WDT_GetIRQNum(WDT_ID_e eId)
{
    return WDT_GetIRQNum((P_WDT_ID_e)eId);
}

/**
 * @brief Select the WDT count clock source (and MCCR mux/divider, if
 *        eClk == WDT_CLK_MCCR).
 *
 * @retval HAL_ERR_NOT_SUPPORTED if eClk == WDT_CLK_WDTRC on this IP version.
 */
__STATIC_INLINE HAL_ERR_e HLL_WDT_SetClkSource(WDT_ID_e eId, WDT_CLK_e eClk, WDT_CLK_MCCR_e eMccr,
                                                uint8_t un8Div)
{
    return WDT_SetClk((P_WDT_ID_e)eId, (P_WDT_CLK_e)eClk, (P_WDT_CLK_MCCR_e)eMccr, un8Div);
}

/**
 * @brief Set the pre-divider applied after the selected clock source.
 */
__STATIC_INLINE void HLL_WDT_SetClkPreDiv(WDT_ID_e eId, WDT_CLK_PREDIV_e ePreDiv)
{
    SET_WDT_CR_CLK_PREDIV(HLL_WDT_REG(eId), WDT_CLK_PREDIV_MODE((uint32_t)ePreDiv));
}

/**
 * @brief Enable or disable a system-level reset when the WDT underflows.
 *
 * This is an SCU-level bit shared by the whole WDT block, not per-instance
 * (see WDT_SetResetEnable() in the active version header) -- also clears
 * any latched WDT reset-cause flag as a side effect, matching HAL_WDT's own
 * usage.
 */
__STATIC_INLINE void HLL_WDT_SetResetEnable(bool bEnable)
{
    WDT_SetResetEnable(bEnable);
}

/**
 * @brief Enable or disable register write access for a WDT instance.
 *
 * This is the persistent access-enable bit (AEN.ENS), set once at init --
 * distinct from HLL_WDT_SetWriteEnable()/SetWriteDisable(), which unlock
 * individual protected-register writes.
 */
__STATIC_INLINE void HLL_WDT_SetAccessEnable(WDT_ID_e eId, bool bEnable)
{
    SET_WDT_ACCESS_EN(HLL_WDT_REG(eId), bEnable);
}

/**
 * @brief Unlock protected WDT registers (CON/LR/...) for the next write.
 *
 * Must be paired with HLL_WDT_SetWriteDisable() once the write is done.
 */
__STATIC_INLINE void HLL_WDT_SetWriteEnable(WDT_ID_e eId)
{
    SET_WDT_ACCESS_KEY(HLL_WDT_REG(eId), WDT_WRITE_ACCESS_EN);
}

/**
 * @brief Re-lock protected WDT registers after a write.
 */
__STATIC_INLINE void HLL_WDT_SetWriteDisable(WDT_ID_e eId)
{
    SET_WDT_ACCESS_KEY(HLL_WDT_REG(eId), WDT_WRITE_ACCESS_DIS);
}

/**
 * @brief Enable or disable the block-level reset-on-underflow bit (CON.WDTRE).
 *
 * Requires HLL_WDT_SetWriteEnable() first.
 */
__STATIC_INLINE void HLL_WDT_SetRstEnable(WDT_ID_e eId, bool bEnable)
{
    SET_WDT_CR_RST_EN(HLL_WDT_REG(eId), bEnable);
}

/**
 * @brief Start (true) or stop (false) the down-counter (CON.WDTEN).
 *
 * Requires HLL_WDT_SetWriteEnable() first.
 */
__STATIC_INLINE void HLL_WDT_SetCountEnable(WDT_ID_e eId, bool bEnable)
{
    SET_WDT_CR_CNT_EN(HLL_WDT_REG(eId), bEnable);
}

/**
 * @brief Write the load (initial count) register directly.
 *
 * Requires HLL_WDT_SetWriteEnable() first. Unlike HLL_WDT_Reload(), this
 * does not also trigger the counter to reload from it -- it just sets what
 * the next reload will load.
 */
__STATIC_INLINE void HLL_WDT_SetLoadValue(WDT_ID_e eId, uint32_t un32Data)
{
    SET_WDT_DR_LOAD(HLL_WDT_REG(eId), un32Data);
}

/**
 * @brief Feed (kick) the watchdog: load the down-counter with un32Data and
 *        restart counting from it.
 *
 * This is the one operation that owns its own unlock/write/re-lock/trigger
 * key sequence (see SET_WDT_DR_RELOAD() in the active version header) --
 * unlike the other setters here, do not bracket this with
 * HLL_WDT_SetWriteEnable()/SetWriteDisable() yourself.
 */
__STATIC_INLINE void HLL_WDT_Reload(WDT_ID_e eId, uint32_t un32Data)
{
    SET_WDT_DR_RELOAD(HLL_WDT_REG(eId), un32Data);
}

/**
 * @brief Read the current down-counter value.
 *
 * Requires HLL_WDT_SetWriteEnable() first (this IP gates counter reads
 * behind the same access key as writes).
 */
__STATIC_INLINE uint32_t HLL_WDT_GetCount(WDT_ID_e eId)
{
    return GET_WDT_DR_CNT(HLL_WDT_REG(eId));
}

/**
 * @brief Write the match (window) counter value, if supported.
 */
__STATIC_INLINE void HLL_WDT_SetMatchValue(WDT_ID_e eId, uint32_t un32Data)
{
    SET_WDT_DR_MATCH(HLL_WDT_REG(eId), un32Data);
}

/**
 * @brief Read the match (window) counter value, if supported.
 */
__STATIC_INLINE uint32_t HLL_WDT_GetMatchValue(WDT_ID_e eId)
{
    return GET_WDT_DR_MATCH(HLL_WDT_REG(eId));
}

/**
 * @brief Enable or disable the count-match interrupt, if supported.
 */
__STATIC_INLINE void HLL_WDT_SetMatchIntrEnable(WDT_ID_e eId, bool bEnable)
{
    SET_WDT_IER_MATCH_EN(HLL_WDT_REG(eId), bEnable);
}

/**
 * @brief Enable or disable the underflow interrupt (CON.WDTIE).
 */
__STATIC_INLINE void HLL_WDT_SetUnderflowIntrEnable(WDT_ID_e eId, bool bEnable)
{
    SET_WDT_IER_UDF_EN(HLL_WDT_REG(eId), bEnable);
}

/**
 * @brief Get the latched count-match flag, if supported.
 */
__STATIC_INLINE bool HLL_WDT_GetMatchFlag(WDT_ID_e eId)
{
    return (bool)GET_WDT_IER_MATCH_FLAG(HLL_WDT_REG(eId));
}

/**
 * @brief Clear the latched count-match flag, if supported.
 */
__STATIC_INLINE void HLL_WDT_ClearMatchFlag(WDT_ID_e eId)
{
    SET_WDT_IER_MATCH_FLAG(HLL_WDT_REG(eId), true);
}

/**
 * @brief Get the latched underflow flag (CON.WUF).
 */
__STATIC_INLINE bool HLL_WDT_GetUnderflowFlag(WDT_ID_e eId)
{
    return (bool)GET_WDT_IER_UDF_FLAG(HLL_WDT_REG(eId));
}

/**
 * @brief Clear the latched underflow flag.
 *
 * On some IP versions this is implemented as a full load-register write
 * rather than a dedicated clear bit (see SET_WDT_IER_UDF_FLAG() in the
 * active version header) -- already accounted for here.
 */
__STATIC_INLINE void HLL_WDT_ClearUnderflowFlag(WDT_ID_e eId)
{
    SET_WDT_IER_UDF_FLAG(HLL_WDT_REG(eId), true);
}

/**
 * @brief Enable or disable the WDT as a wake-up source, if supported.
 *
 * Global, not per-instance (see WDT_SetWkupSrc() in the active version
 * header) -- a no-op on IP versions without wake-up support.
 */
__STATIC_INLINE void HLL_WDT_SetWakeupSrc(bool bEnable)
{
    WDT_SetWkupSrc(bEnable);
}

/**
 * @brief Get and clear the latched wake-up event, if supported.
 *
 * Global, not per-instance (see WDT_GetWkupEvent() in the active version
 * header) -- always reports false on IP versions without wake-up support.
 */
__STATIC_INLINE void HLL_WDT_GetWakeupEvent(bool *pbEvent)
{
    WDT_GetWkupEvent(pbEvent);
}

#ifdef __cplusplus
}
#endif

#endif /* _HLL_WDT_H_ */

/** @} */
/** @} */
