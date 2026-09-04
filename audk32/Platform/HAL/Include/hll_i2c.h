/**
 *******************************************************************************
 * @file        hll_i2c.h
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

/**
 * @addtogroup  HLL HLL (Hardware Low Level)
 * @{
 * @defgroup    HLL_I2C I2C
 * @{
 * @brief       Inter-Integrated Circuit (I2C), Low Level
 *
 * Unlike HAL_I2C, this layer does not own a control block or interrupt
 * vector: it only wraps direct register access. Callers are expected to
 * connect the IRQ returned by HLL_I2C_GetIRQNum() to their own handler and
 * drive the transfer state machine from it using the I2C_STATUS_,
 * I2C_MASTER_ and I2C_SLAVE_ prefixed status-word constants (transitively
 * visible here via hal_i2c_prv.h -> hal_i2c_v1x.h -- see HLL_I2C_GetStatus()).
 *
 * There is no clock-source select for this IP (unlike UART/WDT/FRT): SCLL/
 * SCLH divide the peripheral clock (SystemPeriClock) directly, see
 * HLL_I2C_CalcSclPeriod().
 *
 * There is no HLL_I2C_SetMasterMode(): SET_I2C_CR_MS references a CR bit
 * (IMASTERn) that hal_i2c_v_01_00_00.h's own "Bit/Register Macro" section
 * assumes exists, but this chip's actual I2C_CR/I2C0_CR bitfields
 * (a31c15x.h) have no such bit -- SET_I2C_CR_MS doesn't build on this SoC.
 * HAL_I2C never called it either way: master vs. slave behavior in
 * HAL_I2C_Transmit()/Receive()/the ISR is driven entirely by the
 * caller-supplied I2C_MODE_e in software, not by a hardware mode bit.
 *
 * HLL_I2C_SetSclLowTimeout*() and the HLL_I2C_Set{Scl,Sda}Manual*() /
 * HLL_I2C_Get{Scl,Sda}ManualStatus() functions only exist when this IP version defines
 * I2C_FEATURE_LOW_TIMEOUT_PERIOD / I2C_FEATURE_MANUAL_BUS_CONTROL
 * respectively (see the active version header) -- on the version this SoC
 * series uses (hal_i2c_v_01_00_00.h), neither is defined, so none of those
 * functions are compiled in at all. Callers that need to build against both
 * cases should guard call sites with the same #if.
 */

#ifndef _HLL_I2C_H_
#define _HLL_I2C_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"
#include "type/i2c_type.h"
#include "../I2C/hal_i2c_prv.h"

#define HLL_I2C_REG(eId)    I2C_GetReg((P_I2C_ID_e)(eId))

/**
 * @brief Enable or disable the peripheral clock for an I2C instance.
 */
__STATIC_INLINE HAL_ERR_e HLL_I2C_SetClockEnable(I2C_ID_e eId, bool bEnable)
{
    return I2C_SetScuEnable((P_I2C_ID_e)eId, bEnable);
}

/**
 * @brief Get the NVIC IRQ number for an I2C instance.
 *
 * The caller owns the vector: connect this IRQ number to its own handler
 * (e.g. via the host RTOS's IRQ_CONNECT-equivalent) instead of relying on
 * a fixed-name weak handler.
 */
__STATIC_INLINE IRQn_Type HLL_I2C_GetIRQNum(I2C_ID_e eId)
{
    return I2C_GetIRQNum((P_I2C_ID_e)eId);
}

/**
 * @brief Enable or disable this instance as a wake-up source, if supported.
 *
 * A no-op on the IP version this SoC series uses.
 */
__STATIC_INLINE void HLL_I2C_SetWakeupSrc(I2C_ID_e eId, bool bEnable)
{
    I2C_SetWkupSrc((P_I2C_ID_e)eId, bEnable);
}

/**
 * @brief Get and clear the latched wake-up event, if supported.
 *
 * Always reports false on the IP version this SoC series uses.
 */
__STATIC_INLINE void HLL_I2C_GetWakeupEvent(I2C_ID_e eId, bool *pbEvent)
{
    I2C_GetWkupEvent((P_I2C_ID_e)eId, pbEvent);
}

/**
 * @brief Enable or disable the I2C block, if this IP version has a block
 *        enable bit (see the file-level note -- a no-op otherwise).
 */
__STATIC_INLINE void HLL_I2C_SetEnable(I2C_ID_e eId, bool bEnable)
{
    SET_I2C_CR_EN(HLL_I2C_REG(eId), bEnable);
}

/**
 * @brief Set this instance's own slave address (7-bit, un-shifted).
 */
__STATIC_INLINE void HLL_I2C_SetOwnSlaveAddr(I2C_ID_e eId, uint8_t un8Addr)
{
    SET_I2C_CR_SLAVEADDR(HLL_I2C_REG(eId), un8Addr);
}

/**
 * @brief Set this instance's second own slave address, if supported (a
 *        no-op on the IP version this SoC series uses -- see HAL_I2C's
 *        un8OwnSlvAddr2, which is likewise inert here).
 */
__STATIC_INLINE void HLL_I2C_SetOwnSlaveAddr2(I2C_ID_e eId, uint8_t un8Addr)
{
    SET_I2C_CR_SLAVEADDR2(HLL_I2C_REG(eId), un8Addr);
}

/**
 * @brief Enable or disable general-call address recognition for the first
 *        own slave address.
 */
__STATIC_INLINE void HLL_I2C_SetGeneralCallEnable(I2C_ID_e eId, bool bEnable)
{
    SET_I2C_CR_GNRLADDR(HLL_I2C_REG(eId), bEnable);
}

/**
 * @brief Enable or disable general-call address recognition for the second
 *        own slave address, if supported (a no-op on the IP version this
 *        SoC series uses).
 */
__STATIC_INLINE void HLL_I2C_SetGeneralCallEnable2(I2C_ID_e eId, bool bEnable)
{
    SET_I2C_CR_GNRLADDR2(HLL_I2C_REG(eId), bEnable);
}

/**
 * @brief Write the SCL low-period divider register directly.
 *
 * See HLL_I2C_CalcSclPeriod() to derive this (and the high-period value)
 * from a target bus frequency.
 */
__STATIC_INLINE void HLL_I2C_SetSclLow(I2C_ID_e eId, uint16_t un16Scll)
{
    SET_I2C_CR_SCLL(HLL_I2C_REG(eId), un16Scll);
}

/**
 * @brief Write the SCL high-period divider register directly.
 */
__STATIC_INLINE void HLL_I2C_SetSclHigh(I2C_ID_e eId, uint16_t un16Sclh)
{
    SET_I2C_CR_SCLH(HLL_I2C_REG(eId), un16Sclh);
}

/**
 * @brief Enable or disable programmable SDA hold time, if this IP version
 *        has a dedicated enable bit (a no-op on the IP version this SoC
 *        series uses -- writing 0 via HLL_I2C_SetSdaHold() is this
 *        version's way of disabling it instead, matching HAL_I2C_SetConfig).
 */
__STATIC_INLINE void HLL_I2C_SetSdaHoldEnable(I2C_ID_e eId, bool bEnable)
{
    SET_I2C_CR_SDA_HOLD_EN(HLL_I2C_REG(eId), bEnable);
}

/**
 * @brief Write the SDA hold time register directly (0 to disable).
 */
__STATIC_INLINE void HLL_I2C_SetSdaHold(I2C_ID_e eId, uint16_t un16Hold)
{
    SET_I2C_CR_SDA_HOLD(HLL_I2C_REG(eId), un16Hold);
}

/**
 * @brief Enable or disable the transfer-event interrupt (CR.INTEN).
 */
__STATIC_INLINE void HLL_I2C_SetIntrEnable(I2C_ID_e eId, bool bEnable)
{
    SET_I2C_IER_EN(HLL_I2C_REG(eId), bEnable);
}

/**
 * @brief Get the latched transfer-event interrupt flag (CR.IIF).
 */
__STATIC_INLINE bool HLL_I2C_GetIntrFlag(I2C_ID_e eId)
{
    return (bool)GET_I2C_IER_FLAG(HLL_I2C_REG(eId));
}

/**
 * @brief Write one byte to the data register (address+R/W byte or data,
 *        the caller composes either).
 */
__STATIC_INLINE void HLL_I2C_TransmitByte(I2C_ID_e eId, uint8_t un8Data)
{
    SET_I2C_DR_TX(HLL_I2C_REG(eId), un8Data);
}

/**
 * @brief Read one byte from the data register.
 */
__STATIC_INLINE uint8_t HLL_I2C_ReceiveByte(I2C_ID_e eId)
{
    return (uint8_t)GET_I2C_DR_RX(HLL_I2C_REG(eId));
}

/**
 * @brief Enable or disable ACK generation for the next byte.
 */
__STATIC_INLINE void HLL_I2C_SetAck(I2C_ID_e eId, bool bEnable)
{
    SET_I2C_CR_ACK(HLL_I2C_REG(eId), bEnable);
}

/**
 * @brief Request (true) or release (false) a START condition.
 */
__STATIC_INLINE void HLL_I2C_SetStart(I2C_ID_e eId, bool bEnable)
{
    SET_I2C_CR_START(HLL_I2C_REG(eId), bEnable);
}

/**
 * @brief Request (true) or release (false) a STOP condition.
 */
__STATIC_INLINE void HLL_I2C_SetStop(I2C_ID_e eId, bool bEnable)
{
    SET_I2C_CR_STOP(HLL_I2C_REG(eId), bEnable);
}

/**
 * @brief Acknowledge the current transfer event so the state machine
 *        advances to the next byte/condition.
 *
 * This writes a fixed vendor magic value (see SET_I2C_SR_CLEAR() in the
 * active version header), not a caller-supplied bitmask -- there is nothing
 * to select, hence no bool/mask parameter.
 */
__STATIC_INLINE void HLL_I2C_ClearStatus(I2C_ID_e eId)
{
    SET_I2C_SR_CLEAR(HLL_I2C_REG(eId));
}

/**
 * @brief Get the raw status register.
 *
 * Compare against the I2C_STATUS_, I2C_MASTER_ and I2C_SLAVE_ prefixed
 * combinations defined in hal_i2c_v1x.h (visible here transitively via hal_i2c_prv.h) to
 * decode the current transfer state, e.g. I2C_MASTER_TX_ADDR_ACK,
 * I2C_SLAVE_RX_DONE.
 */
__STATIC_INLINE uint32_t HLL_I2C_GetStatus(I2C_ID_e eId)
{
    return GET_I2C_SR(HLL_I2C_REG(eId));
}

#if defined(I2C_FEATURE_LOW_TIMEOUT_PERIOD)
/**
 * @brief Enable or disable the SCL-low-timeout detector.
 */
__STATIC_INLINE void HLL_I2C_SetSclLowTimeoutEnable(I2C_ID_e eId, bool bEnable)
{
    SET_I2C_CR_SCL_LOW_TO_EN(HLL_I2C_REG(eId), bEnable);
}

/**
 * @brief Enable or disable the SCL-low-timeout interrupt.
 */
__STATIC_INLINE void HLL_I2C_SetSclLowTimeoutIntrEnable(I2C_ID_e eId, bool bEnable)
{
    SET_I2C_IER_SCL_LOW_TO_EN(HLL_I2C_REG(eId), bEnable);
}

/**
 * @brief Write the SCL-low-timeout threshold.
 */
__STATIC_INLINE void HLL_I2C_SetSclLowTimeoutValue(I2C_ID_e eId, uint32_t un32Timeout)
{
    SET_I2C_DR_SCL_LOW_TO(HLL_I2C_REG(eId), un32Timeout);
}
#endif /* I2C_FEATURE_LOW_TIMEOUT_PERIOD */

#if defined(I2C_FEATURE_MANUAL_BUS_CONTROL)
/**
 * @brief Enable or disable manual (software-driven) SCL control.
 */
__STATIC_INLINE void HLL_I2C_SetSclManualEnable(I2C_ID_e eId, bool bEnable)
{
    SET_I2C_CR_SCL_MAUL_EN(HLL_I2C_REG(eId), bEnable);
}

/**
 * @brief Enable or disable manual (software-driven) SDA control.
 */
__STATIC_INLINE void HLL_I2C_SetSdaManualEnable(I2C_ID_e eId, bool bEnable)
{
    SET_I2C_CR_SDA_MAUL_EN(HLL_I2C_REG(eId), bEnable);
}

/**
 * @brief Drive the SCL line level under manual control.
 */
__STATIC_INLINE void HLL_I2C_SetSclManualOut(I2C_ID_e eId, bool bLevel)
{
    SET_I2C_CR_SCL_MAUL_OUT(HLL_I2C_REG(eId), bLevel);
}

/**
 * @brief Read the actual SCL line level while under manual control.
 */
__STATIC_INLINE bool HLL_I2C_GetSclManualStatus(I2C_ID_e eId)
{
    return (bool)GET_I2C_SR_SCL_MAUL_STA(HLL_I2C_REG(eId));
}

/**
 * @brief Drive the SDA line level under manual control.
 */
__STATIC_INLINE void HLL_I2C_SetSdaManualOut(I2C_ID_e eId, bool bLevel)
{
    SET_I2C_CR_SDA_MAUL_OUT(HLL_I2C_REG(eId), bLevel);
}

/**
 * @brief Read the actual SDA line level while under manual control.
 */
__STATIC_INLINE bool HLL_I2C_GetSdaManualStatus(I2C_ID_e eId)
{
    return (bool)GET_I2C_SR_SDA_MAUL_STA(HLL_I2C_REG(eId));
}
#endif /* I2C_FEATURE_MANUAL_BUS_CONTROL */

/**
 *******************************************************************************
 * @brief       Calculate the SCL low/high divider values for a target I2C
 *              bus frequency.
 * @param[in]   un32Freq : Target bus frequency, in Hz.
 * @param[out]  *pun16Scll : SCL low-period divider, ready for
 *                           HLL_I2C_SetSclLow().
 * @param[out]  *pun16Sclh : SCL high-period divider, ready for
 *                           HLL_I2C_SetSclHigh().
 * @return      void : None
 ******************************************************************************/
void HLL_I2C_CalcSclPeriod(uint32_t un32Freq, uint16_t *pun16Scll, uint16_t *pun16Sclh);

#ifdef __cplusplus
}
#endif

#endif /* _HLL_I2C_H_ */

/** @} */
/** @} */
