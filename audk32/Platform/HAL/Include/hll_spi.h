/**
 *******************************************************************************
 * @file        hll_spi.h
 * @author      ABOV R&D Division
 * @brief       Serial Peripheral Interface (Low Level)
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
 * @defgroup    HLL_SPI SPI
 * @{
 * @brief       Serial Peripheral Interface (SPI), Low Level
 *
 * Unlike HAL_SPI, this layer does not own a control block or interrupt
 * vector: it only wraps direct register access. Callers are expected to
 * connect the IRQ returned by HLL_SPI_GetIRQNum() to their own handler and
 * drive TX/RX byte-by-byte from HLL_SPI_GetTxReady()/HLL_SPI_GetRxReady(),
 * the same way HAL_SPI's own ISR does.
 *
 * There is no clock-source select for this IP (unlike UART/WDT/FRT, and
 * like I2C): HLL_SPI_SetBaudRate() divides the peripheral clock
 * (SystemPeriClock) directly via a 16-bit BR.BR divider. HAL_SPI itself
 * never derives this divider from a target bit rate -- it just clamps the
 * caller-supplied SPI_CFG_t::un16BaudRate to a minimum of 2 and writes it
 * straight through -- so there is no HLL_SPI_CalcBaudDivider() here either;
 * compute BR.BR the same way HAL_SPI's caller is expected to.
 *
 * Every register this file wraps is real on the IP version this SoC series
 * uses (hal_spi_v_01_01_00.h) -- verified against a31c15x.h's SPI_CR_x,
 * SPI_SR_x, SPI_BR_x, SPI_LR_x, SPI_EN_x bitfields, unlike I2C's
 * SET_I2C_CR_MS trap. The one no-op in that version file, GET_SPI_SR_TX_UDR
 * (this IP has no underrun status bit at all), is deliberately not wrapped
 * here: nothing in HAL_SPI ever calls it either, since the version also defines
 * SPI_FEATURE_NOT_SUPPORTED_UNDERRUN_FLAG. DMA-related registers
 * (SET_SPI_IER_DMATX_EN/DMARX_EN, the SR DMA-done flags) are likewise left
 * unwrapped, matching how I2C's DMA/NMI-only raw macros were left
 * unconverted -- dead code on this SoC, not worth speculative HLL coverage.
 */

#ifndef _HLL_SPI_H_
#define _HLL_SPI_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"
#include "type/spi_type.h"
#include "../SPI/hal_spi_prv.h"

#define HLL_SPI_REG(eId)    SPI_GetReg((P_SPI_ID_e)(eId))

/**
 * @brief Enable or disable the peripheral clock for an SPI instance.
 */
__STATIC_INLINE HAL_ERR_e HLL_SPI_SetClockEnable(SPI_ID_e eId, bool bEnable)
{
    return SPI_SetScuEnable((P_SPI_ID_e)eId, bEnable);
}

/**
 * @brief Get the NVIC IRQ number for an SPI instance.
 *
 * The caller owns the vector: connect this IRQ number to its own handler
 * instead of relying on a fixed-name weak handler. Note this vector is
 * shared with a comparator peripheral on this SoC (CMPn_SPIn_IRQn).
 */
__STATIC_INLINE IRQn_Type HLL_SPI_GetIRQNum(SPI_ID_e eId)
{
    return SPI_GetIRQNum((P_SPI_ID_e)eId);
}

/**
 * @brief Enable or disable the SPI block (EN.ENABLE).
 */
__STATIC_INLINE void HLL_SPI_SetEnable(SPI_ID_e eId, bool bEnable)
{
    SET_SPI_CR_EN(HLL_SPI_REG(eId), bEnable);
}

/**
 * @brief Select master (true) or slave (false) mode (CR.MS).
 */
__STATIC_INLINE void HLL_SPI_SetMasterMode(SPI_ID_e eId, bool bMaster)
{
    SET_SPI_CR_MODE(HLL_SPI_REG(eId), bMaster);
}

/**
 * @brief Select MSB-first (true) or LSB-first (false) bit order (CR.MSBF).
 */
__STATIC_INLINE void HLL_SPI_SetBitOrder(SPI_ID_e eId, bool bMsbFirst)
{
    SET_SPI_CR_BIT_ORDER(HLL_SPI_REG(eId), bMsbFirst);
}

/**
 * @brief Select clock idle-high (true) or idle-low (false) polarity (CR.CPOL).
 */
__STATIC_INLINE void HLL_SPI_SetClockPolarity(SPI_ID_e eId, bool bIdleHigh)
{
    SET_SPI_CR_CPOL(HLL_SPI_REG(eId), bIdleHigh);
}

/**
 * @brief Select clock phase: sample on the second edge (true) or first edge
 *        (false) of each bit cell (CR.CPHA).
 */
__STATIC_INLINE void HLL_SPI_SetClockPhase(SPI_ID_e eId, bool bSecondEdge)
{
    SET_SPI_CR_CPHA(HLL_SPI_REG(eId), bSecondEdge);
}

/**
 * @brief Select the data width per transfer (CR.BITSZ).
 */
__STATIC_INLINE void HLL_SPI_SetDataBit(SPI_ID_e eId, SPI_DATA_e eData)
{
    SET_SPI_CR_DATA_BIT(HLL_SPI_REG(eId), eData);
}

/**
 * @brief Get the currently configured data width (CR.BITSZ).
 */
__STATIC_INLINE SPI_DATA_e HLL_SPI_GetDataBit(SPI_ID_e eId)
{
    return (SPI_DATA_e)GET_SPI_CR_DATA_BIT(HLL_SPI_REG(eId));
}

/**
 * @brief Select the SS output polarity (CR.SSPOL).
 */
__STATIC_INLINE void HLL_SPI_SetSSPolarity(SPI_ID_e eId, bool bActiveHigh)
{
    SET_SPI_CR_SS_POL(HLL_SPI_REG(eId), bActiveHigh);
}

/**
 * @brief Enable or disable the SS input mask, if applicable (CR.SSMASK).
 */
__STATIC_INLINE void HLL_SPI_SetSSMask(SPI_ID_e eId, bool bEnable)
{
    SET_SPI_CR_SS_MASK(HLL_SPI_REG(eId), bEnable);
}

/**
 * @brief Enable or disable the SS output driver in master mode (CR.SSMO).
 */
__STATIC_INLINE void HLL_SPI_SetSSOutputEnable(SPI_ID_e eId, bool bEnable)
{
    SET_SPI_CR_SS_EN(HLL_SPI_REG(eId), bEnable);
}

/**
 * @brief Select manual (software-driven, true) or automatic (false) SS
 *        control (CR.SSMOD).
 */
__STATIC_INLINE void HLL_SPI_SetSSManual(SPI_ID_e eId, bool bManual)
{
    SET_SPI_CR_SS_MANUAL(HLL_SPI_REG(eId), bManual);
}

/**
 * @brief Get whether SS is under manual (software-driven) control (CR.SSMOD).
 */
__STATIC_INLINE bool HLL_SPI_GetSSManual(SPI_ID_e eId)
{
    return (bool)GET_SPI_CR_SS_MANUAL(HLL_SPI_REG(eId));
}

/**
 * @brief Clear the TX buffer (CR.TXBC) -- a fixed, self-clearing trigger,
 *        not a level, so there is no bool parameter.
 */
__STATIC_INLINE void HLL_SPI_ClearTxBuf(SPI_ID_e eId)
{
    SET_SPI_CR_TXBUF_CLEAR(HLL_SPI_REG(eId));
}

/**
 * @brief Clear the RX buffer (CR.RXBC) -- a fixed, self-clearing trigger,
 *        not a level, so there is no bool parameter.
 */
__STATIC_INLINE void HLL_SPI_ClearRxBuf(SPI_ID_e eId)
{
    SET_SPI_CR_RXBUF_CLEAR(HLL_SPI_REG(eId));
}

/**
 * @brief Write the SS-detect status flag (SR.SSDET) -- write false to clear
 *        it once observed via HLL_SPI_GetSSDetect(), matching HAL_SPI's own
 *        slave SS-detect handling in its ISR.
 */
__STATIC_INLINE void HLL_SPI_SetSSDetect(SPI_ID_e eId, bool bEnable)
{
    SET_SPI_SR_SS_DETECT(HLL_SPI_REG(eId), bEnable);
}

/**
 * @brief Get the SS-detect status flag (SR.SSDET).
 */
__STATIC_INLINE bool HLL_SPI_GetSSDetect(SPI_ID_e eId)
{
    return (bool)GET_SPI_SR_SS_DETECT(HLL_SPI_REG(eId));
}

/**
 * @brief Get whether the transmit shifter/buffer is idle (SR.TXIDLE).
 */
__STATIC_INLINE bool HLL_SPI_GetTxIdle(SPI_ID_e eId)
{
    return (bool)GET_SPI_SR_TX_IDLE(HLL_SPI_REG(eId));
}

/**
 * @brief Get whether the transmit buffer is ready for a new byte (SR.TRDY).
 */
__STATIC_INLINE bool HLL_SPI_GetTxReady(SPI_ID_e eId)
{
    return (bool)GET_SPI_SR_TX_RDY(HLL_SPI_REG(eId));
}

/**
 * @brief Get whether the receive buffer holds an unread byte (SR.RRDY).
 */
__STATIC_INLINE bool HLL_SPI_GetRxReady(SPI_ID_e eId)
{
    return (bool)GET_SPI_SR_RX_RDY(HLL_SPI_REG(eId));
}

/**
 * @brief Get the receive overrun flag (SR.OVRF).
 */
__STATIC_INLINE bool HLL_SPI_GetRxOverrun(SPI_ID_e eId)
{
    return (bool)GET_SPI_SR_RX_OVR(HLL_SPI_REG(eId));
}

/**
 * @brief Get whether the bus is currently busy (SR.SBUSY).
 */
__STATIC_INLINE bool HLL_SPI_GetBusy(SPI_ID_e eId)
{
    return (bool)GET_SPI_SR_BUSY(HLL_SPI_REG(eId));
}

/**
 * @brief Write one data word to the transmit register (TDR.TDR).
 *
 * Widened to 32 bits (not 8) since CR.BITSZ can select up to 17-bit data;
 * callers using 8-bit mode can pass a plain uint8_t.
 */
__STATIC_INLINE void HLL_SPI_TransmitData(SPI_ID_e eId, uint32_t un32Data)
{
    SET_SPI_DR_TX(HLL_SPI_REG(eId), un32Data);
}

/**
 * @brief Read one data word from the receive register (RDR.RDR).
 */
__STATIC_INLINE uint32_t HLL_SPI_ReceiveData(SPI_ID_e eId)
{
    return (uint32_t)GET_SPI_DR_RX(HLL_SPI_REG(eId));
}

/**
 * @brief Write the baud-rate divider register directly (BR.BR).
 *
 * See this file's header note: HAL_SPI never derives this from a target bit
 * rate either, so there is no HLL_SPI_CalcBaudDivider() to pair with it.
 */
__STATIC_INLINE void HLL_SPI_SetBaudRate(SPI_ID_e eId, uint16_t un16BaudRate)
{
    SET_SPI_CR_BAUDRATE(HLL_SPI_REG(eId), un16BaudRate);
}

/**
 * @brief Write the start-delay length (LR.STL).
 */
__STATIC_INLINE void HLL_SPI_SetDelayStart(SPI_ID_e eId, uint8_t un8Delay)
{
    SET_SPI_CR_DELAY_START(HLL_SPI_REG(eId), un8Delay);
}

/**
 * @brief Write the inter-byte (burst) delay length (LR.BTL).
 */
__STATIC_INLINE void HLL_SPI_SetDelayBurst(SPI_ID_e eId, uint8_t un8Delay)
{
    SET_SPI_CR_DELAY_BURST(HLL_SPI_REG(eId), un8Delay);
}

/**
 * @brief Write the stop-delay length (LR.SPL).
 */
__STATIC_INLINE void HLL_SPI_SetDelayStop(SPI_ID_e eId, uint8_t un8Delay)
{
    SET_SPI_CR_DELAY_STOP(HLL_SPI_REG(eId), un8Delay);
}

/**
 * @brief Enable or disable the transmit-ready interrupt (CR.TXIE).
 */
__STATIC_INLINE void HLL_SPI_SetTxIntrEnable(SPI_ID_e eId, bool bEnable)
{
    SET_SPI_IER_TX_EN(HLL_SPI_REG(eId), bEnable);
}

/**
 * @brief Enable or disable the receive-ready interrupt (CR.RXIE).
 */
__STATIC_INLINE void HLL_SPI_SetRxIntrEnable(SPI_ID_e eId, bool bEnable)
{
    SET_SPI_IER_RX_EN(HLL_SPI_REG(eId), bEnable);
}

#ifdef __cplusplus
}
#endif

#endif /* _HLL_SPI_H_ */

/** @} */
/** @} */
