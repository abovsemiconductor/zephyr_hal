/**
 *******************************************************************************
 * @file        hll_pcu.h
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

/**
 * @addtogroup  HLL HLL (Hardware Low Level)
 * @{
 * @defgroup    HLL_PCU PCU
 * @{
 * @brief       Port/GPIO Control Unit
 */

#ifndef _HLL_PCU_H_
#define _HLL_PCU_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"
#include "type/pcu_type.h"
#include "../PCU/hal_pcu_prv.h"

/**
 * @brief PCU Clock Configuration for Port Debounce
 */

/**
 * @brief PCU IRQ handler context
 */

#define HLL_PCU_GET_REG(Id) ((PORT_Type *)(PCU_REG_BASE + (PCU_REG_OFFSET*(uint32_t)(Id))))
#define HLL_PCU_GET_GPIO_REG(Id) ((PORT_Type *)(PCU_GPIO_REG_BASE + (PCU_GPIO_REG_OFFSET*(uint32_t)(Id))))

/**
 *******************************************************************************
 * @brief       PCU Interrupt Callback Function Type.
 * @param[in]   un32Event Event type (NONE).
 * @param[in]   *pContext Context provided during SetIntrPort.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnPCU_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/* __inline function */

/**
 * @brief Enable PCU protected register write access.
 */
__STATIC_INLINE void HLL_PCU_SetWriteEnable(void)
{
    SET_PCU_ACCESS_EN();
}

/**
 * @brief Disable PCU protected register write access.
 */
__STATIC_INLINE void HLL_PCU_SetWriteDisable(void)
{
    SET_PCU_ACCESS_DIS();
}

/**
 * @brief Set PCU pin to digital input mode.
 *
 * @note This function does not enable/disable PCU write access.
 *       Caller must control PCU write access.
 */
__STATIC_INLINE void HLL_PCU_SetInputMode(PCU_ID_e eId, uint32_t un32Pin)
{
    SET_PCU_MODE(HLL_PCU_GET_REG(eId), PCU_INPUTMODE, (un32Pin * 2UL));
}

/**
 * @brief Set PCU pin output mode field.
 *
 * @note This function sets the pin mode field only.
 *       Output type must be configured separately by HLL_PCU_SetOutputType().
 */
__STATIC_INLINE void HLL_PCU_SetAnalogInputMode(PCU_ID_e eId, uint32_t un32Pin)
{
    SET_PCU_MODE(HLL_PCU_GET_REG(eId), PCU_INPUTMODE_ANG, (un32Pin * 2UL));
}

/**
 * @brief Set PCU pin output mode field.
 *
 * @note This function sets the pin mode field only.
 *       Output type must be configured separately by HLL_PCU_SetOutputType().
 */
__STATIC_INLINE void HLL_PCU_SetOutputMode(PCU_ID_e eId, uint32_t un32Pin, uint8_t un8InOut)
{
    SET_PCU_MODE(HLL_PCU_GET_REG(eId), PCU_OUTPUTMODE(un8InOut), (un32Pin * 2UL));
}

/**
 * @brief Set PCU pin output type field.
 *
 * @note This function selects push-pull or open-drain type according to
 *       the existing PCU_OUTPUTMODE_TYP() macro.
 */
__STATIC_INLINE void HLL_PCU_SetOutputType(PCU_ID_e eId, uint32_t un32Pin, uint8_t un8InOut)
{
    SET_PCU_MODE_TYPE(HLL_PCU_GET_REG(eId), PCU_OUTPUTMODE_TYP(un8InOut), un32Pin);
}

/**
 * @brief Set PCU pin to alternate-function mode.
 *
 * @note This function does not enable/disable PCU write access.
 *       Caller must control PCU write access.
 */
__STATIC_INLINE void HLL_PCU_SetAltMode(PCU_ID_e eId, uint32_t un32Pin)
{
    SET_PCU_MODE_ALT(HLL_PCU_GET_REG(eId), PCU_ALTMODE, PCU_ALTMODE_BIT(un32Pin));
}

/**
 * @brief Set alternate-function type for pin 0 to pin 7.
 *
 * @note This function does not check pin range.
 *       Caller must call this function only for pin 0 to pin 7.
 */
__STATIC_INLINE void HLL_PCU_SetAlt1Type(PCU_ID_e eId, uint32_t un32Pin, uint8_t un8Alt)
{
    SET_PCU_ALT1(HLL_PCU_GET_REG(eId), PCU_ALTMODE_TYPE(un8Alt), PCU_ALTTYPE_BIT(un32Pin));
}

/**
 * @brief Set alternate-function type for pin 8 to pin 15.
 *
 * @note This function does not check pin range.
 *       Caller must call this function only for pin 8 to pin 15.
 */
__STATIC_INLINE void HLL_PCU_SetAlt2Type(PCU_ID_e eId, uint32_t un32Pin, uint8_t un8Alt)
{
    SET_PCU_ALT2(HLL_PCU_GET_REG(eId), PCU_ALTMODE_TYPE(un8Alt), PCU_ALT2TYPE_BIT(un32Pin));
}

/**
 * @brief Set PCU pin pull-up / pull-down mode.
 *
 * @note This function does not enable/disable PCU write access.
 *       Caller must control PCU write access.
 */
__STATIC_INLINE void HLL_PCU_SetPullUpDown(PCU_ID_e eId, uint32_t un32Pin, uint8_t un8Pupd)
{
    SET_PCU_PULL_MODE(HLL_PCU_GET_REG(eId), PCU_PULLMODE_TYPE(un8Pupd), PCU_PULLMODE_BIT(un32Pin));
}

/**
 * @brief Get PCU GPIO input value.
 */
__STATIC_INLINE uint32_t HLL_PCU_GetInputValue(PCU_ID_e eId, uint32_t un32Pin)
{
    return GET_PCU_INPUT_DATA(HLL_PCU_GET_GPIO_REG(eId), (uint8_t)un32Pin);
}

/**
 * @brief Set PCU GPIO output value.
 */
__STATIC_INLINE void HLL_PCU_SetOutputValue(PCU_ID_e eId, uint32_t un32Pin, uint8_t un8Output)
{
    SET_PCU_OUTPUT_DATA(HLL_PCU_GET_GPIO_REG(eId), un8Output, un32Pin);
}

/**
 * @brief Enable or disable PCU GPIO output sustain.
 */
__STATIC_INLINE void HLL_PCU_SetOutputSustain(PCU_ID_e eId, uint32_t un32Pin, bool bEnable)
{
    SET_PCU_OUTPUT_SUSTAIN(HLL_PCU_GET_GPIO_REG(eId), bEnable, un32Pin);
}

/**
 * @brief Set PCU GPIO output bit.
 */
__STATIC_INLINE void HLL_PCU_SetOutputBit(PCU_ID_e eId, uint32_t un32Pin)
{
    SET_PCU_OUTPUT_BIT(HLL_PCU_GET_GPIO_REG(eId), true, un32Pin);
}

/**
 * @brief Clear PCU GPIO output bit.
 */
__STATIC_INLINE void HLL_PCU_ClearOutputBit(PCU_ID_e eId, uint32_t un32Pin)
{
    SET_PCU_OUTPUT_CLEAR_BIT(HLL_PCU_GET_GPIO_REG(eId), true, un32Pin);
}

/**
 * @brief Set PCU interrupt trigger type for a pin.
 *
 * @note This function does not enable/disable PCU write access.
 *       Caller must control PCU write access if the target register is protected.
 *
 * @param eId       PCU port ID.
 * @param un32Pin   Pin number.
 * @param un32Trg   Interrupt trigger value.
 */
__STATIC_INLINE void HLL_PCU_SetInterruptTrigger(PCU_ID_e eId, uint32_t un32Pin, uint32_t un32Trg)
{
    SET_PCU_ICR_EN(HLL_PCU_GET_REG(eId), un32Trg, PCU_INTR_BIT(un32Pin));
}

/**
 * @brief Set PCU interrupt mode for a pin.
 *
 * @note This function does not enable/disable PCU write access.
 *       Caller must control PCU write access if the target register is protected.
 *
 * @param eId        PCU port ID.
 * @param un32Pin    Pin number.
 * @param un32Mode   Interrupt mode value.
 */
__STATIC_INLINE void HLL_PCU_SetInterruptMode(PCU_ID_e eId, uint32_t un32Pin, uint32_t un32Mode)
{
    SET_PCU_IER_EN(HLL_PCU_GET_REG(eId), un32Mode, PCU_INTR_BIT(un32Pin));
}

/**
 * @brief Get PCU interrupt status for a pin.
 *
 * @note This function does not clear the interrupt status flag.
 */
__STATIC_INLINE uint32_t HLL_PCU_GetInterruptStatus(PCU_ID_e eId, uint32_t un32Pin)
{
    return GET_PCU_IER_ST(HLL_PCU_GET_REG(eId), PCU_INTR_BIT(un32Pin));
}

/**
 * @brief Clear PCU interrupt status for a pin.
 *
 * @note This function does not enable/disable PCU write access.
 *       Caller must control PCU write access.
 */
__STATIC_INLINE void HLL_PCU_ClearInterruptStatus(PCU_ID_e eId, uint32_t un32Pin)
{
    SET_PCU_IER_ST(HLL_PCU_GET_REG(eId), 0x3UL, PCU_INTR_BIT(un32Pin));
}

/**
 * @brief Clear PCU interrupt status by interrupt bit mask.
 *
 * @note This function is useful when the caller already has PCU_INTR_BIT().
 */
__STATIC_INLINE void HLL_PCU_ClearInterruptStatusByMask(PCU_ID_e eId, uint32_t un32IntrMask)
{
    SET_PCU_IER_ST(HLL_PCU_GET_REG(eId), 0x3UL, un32IntrMask);
}

/**
 * @brief Enable or disable PCU pin debounce.
 *
 * @note This function does not enable/disable PCU write access.
 *       Caller must control PCU write access.
 */
__STATIC_INLINE void HLL_PCU_SetPortDebounce(PCU_ID_e eId, uint32_t un32Pin, bool bEnable)
{
    SET_PCU_DEBOUNCE_EN(HLL_PCU_GET_REG(eId), bEnable, un32Pin);
}

/* end of __inline function */

/**
 * @brief Set RTC port in/out mode if RTC port feature exists.
 */
void HLL_PCU_SetRTCPortInOutMode(PCU_ID_e eId, PCU_PIN_ID_e ePinId, PCU_INOUT_e eInOut);

/**
 * @brief PCU IRQ Configuration
 */

#ifdef __cplusplus
}
#endif

#endif /* _HLL_PCU_H_ */

/** @} */
/** @} */
