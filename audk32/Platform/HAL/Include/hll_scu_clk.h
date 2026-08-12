/**
 *******************************************************************************
 * @file        hll_scu_clk.h
 * @author      ABOV R&D Division
 * @brief       Clock sub system in System Control Unit (Low Level)
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
 * @addtogroup  HLL HLL (Hardware Abstraction Layer)
 * @{
 * @defgroup    HLL_SCU_CLK SCU_CLK
 * @{
 * @brief       Clock sub system in System Control Unit (SCU)
 */

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"
#include "type/scu_clk_type.h"
#include "../SCU/hal_scu_prv.h"

#ifndef _HLL_SCU_CLK_H_
#define _HLL_SCU_CLK_H_

#define HLL_SCUCLK_REG    ((SCUCLK_Type *)SCUCLK_REG_BASE)

/**
 * @brief Enable or disable the HSE clock source.
 */
__STATIC_INLINE void HLL_SCU_CLK_SetHSEEnable(bool bEnable)
{
    HLL_SCU_CLK_SET_HSE_ENABLE(bEnable);
}

/**
 * @brief Enable or disable the HSI clock source.
 */
__STATIC_INLINE void HLL_SCU_CLK_SetHSIEnable(bool bEnable)
{
    HLL_SCU_CLK_SET_HSI_ENABLE(bEnable);
}

/**
 * @brief Enable or disable the LSI clock source.
 */
__STATIC_INLINE void HLL_SCU_CLK_SetLSIEnable(bool bEnable)
{
    HLL_SCU_CLK_SET_LSI_ENABLE(bEnable);
}

/**
 * @brief Enable or disable the LSE clock source.
 */
__STATIC_INLINE void HLL_SCU_CLK_SetLSEEnable(bool bEnable)
{
    HLL_SCU_CLK_SET_LSE_ENABLE(bEnable);
}

/**
 * @brief Set the HSE source divider.
 */
__STATIC_INLINE void HLL_SCU_CLK_SetHSEDivider(SCUCLK_DIV_e eDiv)
{
    HLL_SCU_CLK_SET_HSE_DIVIDER(eDiv);
}

/**
 * @brief Set the HSI source divider.
 */
__STATIC_INLINE void HLL_SCU_CLK_SetHSIDivider(SCUCLK_DIV_e eDiv)
{
    HLL_SCU_CLK_SET_HSI_DIVIDER(eDiv);
}

/**
 * @brief Set the LSI source divider.
 */
__STATIC_INLINE void HLL_SCU_CLK_SetLSIDivider(SCUCLK_DIV_e eDiv)
{
    HLL_SCU_CLK_SET_LSI_DIVIDER(eDiv);
}

/**
 * @brief Set the LSE source divider.
 */
__STATIC_INLINE void HLL_SCU_CLK_SetLSEDivider(SCUCLK_DIV_e eDiv)
{
    HLL_SCU_CLK_SET_LSE_DIVIDER(eDiv);
}

/**
 * @brief Set the HCLK divider.
 */
__STATIC_INLINE void HLL_SCU_CLK_SetHClkDivider(SCUCLK_DIV_e eDiv)
{
    HLL_SCU_CLK_SET_HCLK_DIVIDER(eDiv);
}

/**
 * @brief Get the peripheral clock divider.
 */
__STATIC_INLINE uint8_t HLL_SCU_CLK_GetPClkDivider(void)
{
    return (uint8_t)HLL_SCU_CLK_GET_PCLK_DIVIDER();
}

/**
 * @brief Select the main clock source.
 *
 * @param[in] un32Source MCLKSEL register field value.
 */
__STATIC_INLINE void HLL_SCU_CLK_SetMClkSource(uint32_t un32Source)
{
    HLL_SCU_CLK_SET_MCLK_SOURCE(un32Source);
}

/**
 * @brief Apply the default Flash latency before switching MCLK.
 */
__STATIC_INLINE void HLL_SCU_CLK_SetFlashLatencyDefault(void)
{
    HLL_SCU_CLK_SET_FLASH_LATENCY_DEFAULT();
}

/**
 * @brief Enable or disable the main clock auto-recovery function.
 *
 * @param[in] bEnable
 *            - true  : Enable main clock auto-recovery
 *            - false : Disable main clock auto-recovery
 */
__STATIC_INLINE void HLL_SCU_CLK_SetAutoRecovery(bool bEnable)
{
    SET_SCU_CMR_MCLKREC(HLL_SCUCLK_REG, bEnable ? SCUCLK_AUTO_RECOVERY_ON : SCUCLK_AUTO_RECOVERY_OFF);
}

/**
 * @brief Enable or disable the clock output.
 *
 * @param[in] bEnable
 *            - true  : Enable clock output
 *            - false : Disable clock output
 */
__STATIC_INLINE void HLL_SCU_CLK_SetOutputEnable(bool bEnable)
{
    SET_SCU_COR_CLKOEN(HLL_SCUCLK_REG, bEnable);
}

/**
 * @brief Set the clock output divider.
 *
 * @param[in] un8Divider Clock output divider value.
 */
__STATIC_INLINE void HLL_SCU_CLK_SetOutputDivider(uint8_t un8Divider)
{
    HLL_SCU_CLK_SET_OUTPUT_DIVIDER(un8Divider);
}

/**
 * @brief Select the clock output source.
 *
 * @param[in] un32Source Clock output source register value.
 */
__STATIC_INLINE void HLL_SCU_CLK_SetOutputSource(uint32_t un32Source)
{
    HLL_SCU_CLK_SET_OUTPUT_SOURCE(un32Source);
}

/**
 * @brief Convert a clock source to the clock output source value.
 *
 * @param[in]  eSrc            Clock source.
 * @param[out] pun32OutputSrc  Clock output source register value.
 *
 * @return
 *        - HAL_ERR_OK        : Supported source
 *        - HAL_ERR_PARAMETER : Unsupported source
 */
__STATIC_INLINE HAL_ERR_e HLL_SCU_CLK_GetOutputSourceValue(SCUCLK_SRC_e eSrc, uint32_t *pun32OutputSrc)
{
    return HLL_SCU_CLK_GET_OUTPUT_SOURCE_VALUE(eSrc, pun32OutputSrc);
}

/**
 * @brief Enable or disable HSE as a clock reset source.
 *
 * @param[in] bEnable
 *            - true  : Enable HSE reset source
 *            - false : Disable HSE reset source
 */
__STATIC_INLINE void HLL_SCU_CLK_SetResetSrcHSEEnable(bool bEnable)
{
    HLL_SCU_CLK_SET_RESET_SRC_HSE_ENABLE(bEnable);
}

/**
 * @brief Enable or disable MCLK as a clock reset source.
 *
 * @param[in] bEnable
 *            - true  : Enable MCLK reset source
 *            - false : Disable MCLK reset source
 */
__STATIC_INLINE void HLL_SCU_CLK_SetResetSrcMClkEnable(bool bEnable)
{
    HLL_SCU_CLK_SET_RESET_SRC_MCLK_ENABLE(bEnable);
}

/**
 * @brief Enable or disable LSE as a clock reset source.
 *
 * @param[in] bEnable
 *            - true  : Enable LSE reset source
 *            - false : Disable LSE reset source
 */
__STATIC_INLINE void HLL_SCU_CLK_SetResetSrcLSEEnable(bool bEnable)
{
    HLL_SCU_CLK_SET_RESET_SRC_LSE_ENABLE(bEnable);
}

/**
 * @brief Get the HSE clock reset source enable state.
 *
 * @return
 *        - true  : HSE reset source is enabled
 *        - false : HSE reset source is disabled
 */
__STATIC_INLINE bool HLL_SCU_CLK_GetResetSrcHSEEnable(void)
{
    return (bool)HLL_SCU_CLK_GET_RESET_SRC_HSE_ENABLE();
}

/**
 * @brief Get the HSE clock reset source event flag.
 *
 * @return HSE reset source event flag.
 */
__STATIC_INLINE bool HLL_SCU_CLK_GetResetSrcHSEEvent(void)
{
    return (bool)HLL_SCU_CLK_GET_RESET_SRC_HSE_EVENT();
}

/**
 * @brief Clear the HSE clock reset source event flag.
 */
__STATIC_INLINE void HLL_SCU_CLK_ClearResetSrcHSEEvent(void)
{
    HLL_SCU_CLK_CLEAR_RESET_SRC_HSE_EVENT();
}

/**
 * @brief Get the MCLK reset source enable state.
 */
__STATIC_INLINE bool HLL_SCU_CLK_GetResetSrcMClkEnable(void)
{
    return (bool)HLL_SCU_CLK_GET_RESET_SRC_MCLK_ENABLE();
}

/**
 * @brief Get the MCLK reset source event flag.
 */
__STATIC_INLINE bool HLL_SCU_CLK_GetResetSrcMClkEvent(void)
{
    return (bool)HLL_SCU_CLK_GET_RESET_SRC_MCLK_EVENT();
}

/**
 * @brief Clear the MCLK reset source event flag.
 */
__STATIC_INLINE void HLL_SCU_CLK_ClearResetSrcMClkEvent(void)
{
    HLL_SCU_CLK_CLEAR_RESET_SRC_MCLK_EVENT();
}


/**
 * @brief Get the LSE clock reset source enable state.
 */
__STATIC_INLINE bool HLL_SCU_CLK_GetResetSrcLSEEnable(void)
{
    return (bool)HLL_SCU_CLK_GET_RESET_SRC_LSE_ENABLE();
}

/**
 * @brief Get the LSE clock reset source event flag.
 */
__STATIC_INLINE bool HLL_SCU_CLK_GetResetSrcLSEEvent(void)
{
    return (bool)HLL_SCU_CLK_GET_RESET_SRC_LSE_EVENT();
}

/**
 * @brief Clear the LSE clock reset source event flag.
 */
__STATIC_INLINE void HLL_SCU_CLK_ClearResetSrcLSEEvent(void)
{
    HLL_SCU_CLK_CLEAR_RESET_SRC_LSE_EVENT();
}

/**
 * @brief Enable or disable PLL.
 *
 * @param[in] bEnable
 *            - true  : Enable PLL
 *            - false : Disable PLL
 */
__STATIC_INLINE void HLL_SCU_CLK_SetPLLEnable(bool bEnable)
{
    HLL_SCU_CLK_SET_PLL_ENABLE(bEnable);
}

/**
 * @brief Select HSE or HSI as PLL input clock.
 *
 * @param[in] bUseHSE
 *            - true  : Select HSE
 *            - false : Select HSI
 */
__STATIC_INLINE void HLL_SCU_CLK_SetPLLSourceHSE(bool bUseHSE)
{
    HLL_SCU_CLK_SET_PLL_SOURCE_HSE(bUseHSE);
}

/**
 * @brief Set PLL input clock pre-divider.
 *
 * @param[in] eDiv PLL input clock divider.
 */
__STATIC_INLINE void HLL_SCU_CLK_SetPLLSourceDivider(SCUCLK_DIV_e eDiv)
{
    HLL_SCU_CLK_SET_PLL_SOURCE_DIVIDER(eDiv);
}

/**
 * @brief Configure and enable HSE for PLL input.
 *
 * @param[in] eDiv HSE divider.
 */
__STATIC_INLINE void HLL_SCU_CLK_SetPLLHSESource(SCUCLK_DIV_e eDiv)
{
    HLL_SCU_CLK_SET_PLL_HSE_SOURCE(eDiv);
}

/**
 * @brief Configure and enable HSI for PLL input.
 *
 * @param[in] eDiv HSI divider.
 */
__STATIC_INLINE void HLL_SCU_CLK_SetPLLHSISource(SCUCLK_DIV_e eDiv)
{
    HLL_SCU_CLK_SET_PLL_HSI_SOURCE(eDiv);
}

/**
 * @brief Write PLL control register.
 *
 * @param[in] un32Value PLL control register value.
 */
__STATIC_INLINE void HLL_SCU_CLK_SetPLLControl(uint32_t un32Value)
{
    HLL_SCU_CLK_SET_PLL_CONTROL(un32Value);
}

/**
 * @brief Write PLL control key value.
 */
__STATIC_INLINE void HLL_SCU_CLK_SetPLLControlKey(void)
{
    HLL_SCU_CLK_SET_PLL_CONTROL_KEY();
}

/**
 * @brief Get PLL lock state.
 *
 * @return
 *        - true  : PLL is locked
 *        - false : PLL is not locked
 */
__STATIC_INLINE bool HLL_SCU_CLK_GetPLLLock(void)
{
    return (bool)HLL_SCU_CLK_GET_PLL_LOCK();
}

/**
 * @brief Get PLL ready state.
 *
 * @return
 *        - true  : PLL is ready
 *        - false : PLL is not ready
 */
__STATIC_INLINE bool HLL_SCU_CLK_GetPLLReady(void)
{
    return (bool)HLL_SCU_CLK_GET_PLL_READY();
}


#ifdef __cplusplus
}
#endif

#endif /* _HLL_SCU_CLK_H_ */

/** @} */
/** @} */
