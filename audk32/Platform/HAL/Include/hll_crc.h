/**
 *******************************************************************************
 * @file        hll_crc.h
 * @author      ABOV R&D Division
 * @brief       Cyclic Redundancy Check (Low Level)
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
 * @defgroup    HLL_CRC CRC
 * @{
 * @brief       Cyclic Redundancy Check, Low Level
 *
 * Unlike HAL_CRC, this layer does not own an interrupt vector, a control
 * block, or DMA state: it only wraps direct register access. Callers are
 * expected to connect the IRQ returned by HLL_CRC_GetIRQNum() to their own
 * handler and drive data feed / result readout / DMA setup themselves.
 */

#ifndef _HLL_CRC_H_
#define _HLL_CRC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"
#include "type/crc_type.h"
#include "../CRC/hal_crc_prv.h"

#define HLL_CRC_REG(eId)    CRC_GetReg((P_CRC_ID_e)(eId))

/* __inline function */

/**
 * @brief Enable or disable the peripheral clock for a CRC instance.
 */
__STATIC_INLINE HAL_ERR_e HLL_CRC_SetClockEnable(CRC_ID_e eId, bool bEnable)
{
    return CRC_SetScuEnable((P_CRC_ID_e)eId, bEnable);
}

/**
 * @brief Get the NVIC IRQ number for a CRC instance.
 *
 * The caller owns the vector: connect this IRQ number to its own handler
 * (e.g. via the host RTOS's IRQ_CONNECT-equivalent) instead of relying on
 * a fixed-name weak handler.
 */
__STATIC_INLINE IRQn_Type HLL_CRC_GetIRQNum(CRC_ID_e eId)
{
    return CRC_GetIRQNum((P_CRC_ID_e)eId);
}

/**
 * @brief Check whether a polynomial is supported on this CRC IP variant.
 */
__STATIC_INLINE HAL_ERR_e HLL_CRC_GetSupportPoly(CRC_POLY_e ePoly)
{
    return CRC_GetSupportPoly((P_CRC_POLY_e)ePoly);
}

/**
 * @brief Select CRC or Checksum mode (if supported by this IP variant).
 */
__STATIC_INLINE void HLL_CRC_SetMode(CRC_ID_e eId, CRC_MODE_e eMode)
{
    SET_CRC_CR_MODE(HLL_CRC_REG(eId), (uint32_t)eMode);
}

/**
 * @brief Select the CRC polynomial.
 */
__STATIC_INLINE void HLL_CRC_SetPoly(CRC_ID_e eId, CRC_POLY_e ePoly)
{
    SET_CRC_CR_POLY(HLL_CRC_REG(eId), CRC_INT_POLY((uint32_t)ePoly));
}

/**
 * @brief Select the first-in bit order (LSB/MSB).
 */
__STATIC_INLINE void HLL_CRC_SetFirstIn(CRC_ID_e eId, CRC_INP_e eFirstIn)
{
    SET_CRC_CR_INP(HLL_CRC_REG(eId), CRC_INT_INP((uint32_t)eFirstIn));
}

/**
 * @brief Configure the output bit order and inversion (if supported by
 *        this IP variant).
 */
__STATIC_INLINE void HLL_CRC_SetOutputConfig(CRC_ID_e eId, CRC_OUTP_e eFirstOut,
                                              CRC_OUTP_INV_e eInv)
{
    CRC_Type *ptCrc = HLL_CRC_REG(eId);

    SET_CRC_CR_OUTP(ptCrc, (uint32_t)eFirstOut);
    SET_CRC_CR_OUTP_INV(ptCrc, (uint32_t)eInv);
}

/**
 * @brief Clear the output (result) register (if supported by this IP variant).
 */
__STATIC_INLINE void HLL_CRC_ClearOutput(CRC_ID_e eId)
{
    SET_CRC_CR_OUT_CLR(HLL_CRC_REG(eId), true);
}

/**
 * @brief Enable or disable the Auto/DMA-done operating mode bit.
 *
 * @note The bit backing this field differs by IP version: it selects Auto
 *       CRC mode on some variants and the DMA-done interrupt enable on
 *       others. See SET_CRC_CR_OP_MODE() in the active version-specific
 *       private header for the exact meaning on the target in use.
 */
__STATIC_INLINE void HLL_CRC_SetOpMode(CRC_ID_e eId, bool bEnable)
{
    SET_CRC_CR_OP_MODE(HLL_CRC_REG(eId), bEnable);
}

/**
 * @brief Set the initial seed value for the next computation.
 */
__STATIC_INLINE void HLL_CRC_SetInitValue(CRC_ID_e eId, uint32_t un32Init)
{
    SET_CRC_DR_INIT(HLL_CRC_REG(eId), un32Init);
}

/**
 * @brief Enable or disable the CRC block.
 *
 * Must be called after Poly/FirstIn/Output/Init are configured, and before
 * feeding data (see HAL_CRC_SetCompute() for the expected sequence).
 */
__STATIC_INLINE void HLL_CRC_SetEnable(CRC_ID_e eId, bool bEnable)
{
    SET_CRC_CR_EN(HLL_CRC_REG(eId), bEnable);
}

/**
 * @brief Write one word directly to the input data register.
 *
 * @note No byte-alignment or packing is performed; the caller is
 *       responsible for matching the register's expected word layout.
 *       Use HLL_CRC_SetData() to feed a raw byte buffer instead.
 */
__STATIC_INLINE void HLL_CRC_WriteInputData(CRC_ID_e eId, uint32_t un32Data)
{
    SET_CRC_DR_IN(HLL_CRC_REG(eId), un32Data);
}

/**
 * @brief Feed a byte buffer to the CRC input register, packed per this IP
 *        variant's native input word size and byte order.
 */
__STATIC_INLINE void HLL_CRC_SetData(CRC_ID_e eId, uint8_t *pun8Data, uint32_t un32Len)
{
    CRC_SetData(HLL_CRC_REG(eId), pun8Data, un32Len);
}

/**
 * @brief Read the current computation result.
 */
__STATIC_INLINE uint32_t HLL_CRC_GetResult(CRC_ID_e eId)
{
    return GET_CRC_DR_OUT(HLL_CRC_REG(eId));
}

/**
 * @brief Get the address of the input data register (e.g. for DMA transfer setup).
 */
__STATIC_INLINE uint32_t HLL_CRC_GetInputAddr(CRC_ID_e eId)
{
    return (uint32_t)GET_CRC_IN_ADDR(HLL_CRC_REG(eId));
}

/* end of __inline function */

/**
 * @brief Configure the input data size and complement.
 *
 * No-op on IP variants that do not implement configurable input data size
 * (i.e. CRC_FEATURE_INPUT_CONF_MODE is not defined for the active version).
 */
void HLL_CRC_SetInputConfig(CRC_ID_e eId, CRC_INP_DATA_e eInDataSize, bool bComplement);

/**
 * @brief Enable or disable the DMA-done interrupt.
 *
 * No-op on IP variants that do not implement a CRC interrupt (i.e.
 * CRC_FEATURE_UNSUPPORT_IRQ is defined for the active version).
 */
void HLL_CRC_SetDmaIntrEnable(CRC_ID_e eId, bool bEnable);

/**
 * @brief Clear the latched DMA-done interrupt flag.
 *
 * No-op on IP variants that do not implement a CRC interrupt (i.e.
 * CRC_FEATURE_UNSUPPORT_IRQ is defined for the active version).
 */
void HLL_CRC_ClearDmaFlag(CRC_ID_e eId);

/**
 * @brief Get the latched DMA-done interrupt flag.
 *
 * Always returns false on IP variants that do not implement a CRC
 * interrupt (i.e. CRC_FEATURE_UNSUPPORT_IRQ is defined for the active version).
 */
bool HLL_CRC_GetDmaFlag(CRC_ID_e eId);

#ifdef __cplusplus
}
#endif

#endif /* _HLL_CRC_H_ */

/** @} */
/** @} */
