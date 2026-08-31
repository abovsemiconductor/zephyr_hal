/**
 *******************************************************************************
 * @file        hll_frt.h
 * @author      ABOV R&D Division
 * @brief       Free Run Timer (Low Level)
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
 * @defgroup    HLL_FRT FRT
 * @{
 * @brief       Free Run Timer, Low Level
 *
 * Unlike HAL_FRT, this layer does not own a control block or interrupt
 * vector: it only wraps direct register access. Callers are expected to
 * connect the IRQ returned by HLL_FRT_GetIRQNum() to their own handler.
 *
 * On the IP version this SoC series uses (hal_frt_v_01_00_00.h),
 * SET_FRT_CR_CLK_SEL()/SET_FRT_CR_CLK_PREDIV() are both no-ops -- there is
 * no FRT-block-level clock select or pre-divider register at all. The
 * counter's actual clock comes entirely from the SCU MCCR mux
 * (FRT_SetMccrClk(), wrapped by HLL_FRT_SetClkSource() below): selecting
 * FRT_CLK_PCLK is accepted but configures nothing, so HLL_FRT_SetClkSource()
 * must be called with FRT_CLK_MCCR to get a running counter.
 */

#ifndef _HLL_FRT_H_
#define _HLL_FRT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"
#include "type/frt_type.h"
#include "../FRT/hal_frt_prv.h"

#define HLL_FRT_REG(eId)    FRT_GetReg((P_FRT_ID_e)(eId))

/**
 * @brief Enable or disable the peripheral clock for an FRT instance.
 */
__STATIC_INLINE HAL_ERR_e HLL_FRT_SetClockEnable(FRT_ID_e eId, bool bEnable)
{
    return FRT_SetScuEnable((P_FRT_ID_e)eId, bEnable);
}

/**
 * @brief Get the NVIC IRQ number for an FRT instance.
 *
 * The caller owns the vector: connect this IRQ number to its own handler
 * (e.g. via the host RTOS's IRQ_CONNECT-equivalent) instead of relying on
 * a fixed-name weak handler.
 */
__STATIC_INLINE IRQn_Type HLL_FRT_GetIRQNum(FRT_ID_e eId)
{
    return FRT_GetIRQNum((P_FRT_ID_e)eId);
}

/**
 * @brief Select the counter clock source (and MCCR mux/divider, if
 *        eClk == FRT_CLK_MCCR -- see the file-level note on why that's the
 *        only source that actually configures anything on this IP version).
 */
__STATIC_INLINE HAL_ERR_e HLL_FRT_SetClkSource(FRT_ID_e eId, FRT_CLK_e eClk, FRT_CLK_MCCR_e eMccr,
                                                uint8_t un8Div)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    switch (eClk)
    {
    case FRT_CLK_MCCR:
        SET_FRT_CR_CLK_SEL(HLL_FRT_REG(eId), (uint8_t)FRT_CLK_MCCR);
        eErr = FRT_SetMccrClk((P_FRT_ID_e)eId, (P_FRT_CLK_MCCR_e)eMccr, un8Div);
        break;
    case FRT_CLK_PCLK:
        SET_FRT_CR_CLK_SEL(HLL_FRT_REG(eId), (uint8_t)FRT_CLK_PCLK);
        break;
    default:
        eErr = HAL_ERR_PARAMETER;
        break;
    }

    return eErr;
}

/**
 * @brief Set the pre-divider applied after the selected clock source, if
 *        supported (see the file-level note -- a no-op on this IP version).
 */
__STATIC_INLINE void HLL_FRT_SetClkPreDiv(FRT_ID_e eId, FRT_CLK_PREDIV_e ePreDiv)
{
    SET_FRT_CR_CLK_PREDIV(HLL_FRT_REG(eId), (uint32_t)ePreDiv);
}

/**
 * @brief Select free-run vs. match mode (CTRL.MODE).
 */
__STATIC_INLINE void HLL_FRT_SetMode(FRT_ID_e eId, FRT_MODE_e eMode)
{
    SET_FRT_CR_MODE(HLL_FRT_REG(eId), (uint32_t)eMode);
}

/**
 * @brief Start (true) or stop (false) the counter (CTRL.EN).
 */
__STATIC_INLINE void HLL_FRT_SetEnable(FRT_ID_e eId, bool bEnable)
{
    SET_FRT_CR_EN(HLL_FRT_REG(eId), bEnable);
}

/**
 * @brief Write the counter register directly.
 *
 * The counter must be running to accept a write on this IP (see
 * HAL_FRT_Start()'s "To clear counter, FRT must be running" note) -- call
 * HLL_FRT_SetEnable(eId, true) first.
 */
__STATIC_INLINE void HLL_FRT_SetCount(FRT_ID_e eId, uint32_t un32Data)
{
    SET_FRT_DR_CNT(HLL_FRT_REG(eId), un32Data);
}

/**
 * @brief Read the current counter value.
 */
__STATIC_INLINE uint32_t HLL_FRT_GetCount(FRT_ID_e eId)
{
    return GET_FRT_DR_CNT(HLL_FRT_REG(eId));
}

/**
 * @brief Write the match counter value (match mode).
 */
__STATIC_INLINE void HLL_FRT_SetMatchValue(FRT_ID_e eId, uint32_t un32Data)
{
    SET_FRT_DR_MATCH_CNT(HLL_FRT_REG(eId), un32Data);
}

/**
 * @brief Read the match counter value (match mode).
 */
__STATIC_INLINE uint32_t HLL_FRT_GetMatchValue(FRT_ID_e eId)
{
    return GET_FRT_DR_MATCH_CNT(HLL_FRT_REG(eId));
}

/**
 * @brief Enable or disable the count-match interrupt.
 */
__STATIC_INLINE void HLL_FRT_SetMatchIntrEnable(FRT_ID_e eId, bool bEnable)
{
    SET_FRT_IER_MATCH_EN(HLL_FRT_REG(eId), bEnable);
}

/**
 * @brief Enable or disable the overflow interrupt.
 */
__STATIC_INLINE void HLL_FRT_SetOverflowIntrEnable(FRT_ID_e eId, bool bEnable)
{
    SET_FRT_IER_OVF_EN(HLL_FRT_REG(eId), bEnable);
}

/**
 * @brief Get the latched count-match flag.
 */
__STATIC_INLINE bool HLL_FRT_GetMatchFlag(FRT_ID_e eId)
{
    return (bool)GET_FRT_IER_MATCH_FLAG(HLL_FRT_REG(eId));
}

/**
 * @brief Clear the latched count-match flag.
 */
__STATIC_INLINE void HLL_FRT_ClearMatchFlag(FRT_ID_e eId)
{
    SET_FRT_IER_MATCH_FLAG(HLL_FRT_REG(eId), true);
}

/**
 * @brief Get the latched overflow flag.
 */
__STATIC_INLINE bool HLL_FRT_GetOverflowFlag(FRT_ID_e eId)
{
    return (bool)GET_FRT_IER_OVF_FLAG(HLL_FRT_REG(eId));
}

/**
 * @brief Clear the latched overflow flag.
 */
__STATIC_INLINE void HLL_FRT_ClearOverflowFlag(FRT_ID_e eId)
{
    SET_FRT_IER_OVF_FLAG(HLL_FRT_REG(eId), true);
}

#ifdef __cplusplus
}
#endif

#endif /* _HLL_FRT_H_ */

/** @} */
/** @} */
