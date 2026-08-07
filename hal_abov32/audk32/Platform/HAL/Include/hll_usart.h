/**
 *******************************************************************************
 * @file        hll_usart.h
 * @author      ABOV R&D Division
 * @brief       USART communication (Low Level)
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
 * @defgroup    HLL_USART USART
 * @{
 * @brief       Universal Synchronous/Asynchronous Receiver/Transmitter (USART), Low Level
 *
 * Unlike HAL_USART, this layer does not own an interrupt vector, a control
 * block, or DMA state: it only wraps direct register access. Callers are
 * expected to connect the IRQ returned by HLL_USART_GetIRQNum() to their own
 * handler and drive TX/RX byte-by-byte from it.
 */

#ifndef _HLL_USART_H_
#define _HLL_USART_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"
#include "type/usart_type.h"
#include "../USART/hal_usart_prv.h"

#define HLL_USART_REG(eId)    USART_GetReg((uint32_t)(eId))

/**
 * @brief Enable or disable the peripheral clock for a USART instance.
 */
__STATIC_INLINE HAL_ERR_e HLL_USART_SetClockEnable(USART_ID_e eId, bool bEnable)
{
    return USART_SetScuEnable((P_USART_ID_e)eId, bEnable);
}

/**
 * @brief Get the NVIC IRQ number for a USART instance.
 *
 * The caller owns the vector: connect this IRQ number to its own handler
 * (e.g. via the host RTOS's IRQ_CONNECT-equivalent) instead of relying on
 * a fixed-name weak handler.
 */
__STATIC_INLINE IRQn_Type HLL_USART_GetIRQNum(USART_ID_e eId)
{
    return USART_GetIRQNum((P_USART_ID_e)eId);
}

/**
 * @brief Clear both control registers (CR1/CR2) to their reset state.
 */
__STATIC_INLINE void HLL_USART_ClearControl(USART_ID_e eId)
{
    USART_Type *ptUsart = HLL_USART_REG(eId);

    SET_USART_CR(ptUsart, 0x00);
    SET_USART_CR2(ptUsart, 0x00);
}

/**
 * @brief Select the USART mode (UART / USRT / SPI).
 */
__STATIC_INLINE void HLL_USART_SetMode(USART_ID_e eId, USART_MODE_e eMode)
{
    SET_USART_CR_MODE(HLL_USART_REG(eId), USART_MODE((uint8_t)eMode));
}

/**
 * @brief Configure UART (asynchronous) frame format.
 */
__STATIC_INLINE void HLL_USART_SetUartFormat(USART_ID_e eId, USART_PARITY_e eParity,
                                              USART_DATA_e eData, USART_STOP_e eStop,
                                              bool bDoubleSpeed)
{
    USART_Type *ptUsart = HLL_USART_REG(eId);

    SET_USART_CR_PARITY(ptUsart, USART_PARITY((uint8_t)eParity));
    SET_USART_CR_DLEN(ptUsart, USART_DATA((uint8_t)eData));
    SET_USART_CR_STOPBIT(ptUsart, (uint32_t)eStop);
    SET_USART_CR_DBLS(ptUsart, bDoubleSpeed);
}

/**
 * @brief Configure USRT (synchronous) frame format.
 */
__STATIC_INLINE void HLL_USART_SetUsrtFormat(USART_ID_e eId, USART_MS_e eMs,
                                              USART_PARITY_e eParity, USART_DATA_e eData,
                                              USART_STOP_e eStop, USART_CLKPOL_e eClkPol)
{
    USART_Type *ptUsart = HLL_USART_REG(eId);

    SET_USART_CR_MS(ptUsart, (uint8_t)eMs);
    SET_USART_CR_PARITY(ptUsart, USART_PARITY((uint8_t)eParity));
    SET_USART_CR_DLEN(ptUsart, USART_DATA((uint8_t)eData));
    SET_USART_CR_STOPBIT(ptUsart, (uint32_t)eStop);
    SET_USART_CR_CPACK(ptUsart, (uint8_t)eClkPol);
}

/**
 * @brief Configure SPI frame format.
 */
__STATIC_INLINE void HLL_USART_SetSpiFormat(USART_ID_e eId, USART_MS_e eMs,
                                             USART_BIT_ORDER_e eBitOrder,
                                             USART_CLKPOL_e eClkPol, USART_CLKPHA_e eClkPha,
                                             bool bSwapMSPort)
{
    USART_Type *ptUsart = HLL_USART_REG(eId);

    SET_USART_CR_MS(ptUsart, (uint8_t)eMs);
    SET_USART_CR_BIT_ORDER(ptUsart, (uint8_t)eBitOrder);
    SET_USART_CR_CPACK(ptUsart, (uint8_t)eClkPol);
    SET_USART_CR_CPSCK(ptUsart, (uint8_t)eClkPha);
    SET_USART_CR_SWAP_MS_PORT(ptUsart, bSwapMSPort);
}

/**
 * @brief Enable or disable the receiver while in SPI slave mode.
 */
__STATIC_INLINE void HLL_USART_SetSpiSlaveRxEnable(USART_ID_e eId, bool bEnable)
{
    SET_USART_CR_SREN(HLL_USART_REG(eId), bEnable);
}

/**
 * @brief Set the Receive Time-Out (RTO) count.
 */
__STATIC_INLINE void HLL_USART_SetRtoCount(USART_ID_e eId, uint32_t un32Count)
{
    SET_USART_CR_RTO_CNT(HLL_USART_REG(eId), un32Count);
}

/**
 * @brief Enable or disable the Receive Time-Out (RTO) counter itself (CR2.RTOEN).
 */
__STATIC_INLINE void HLL_USART_SetRtoEnable(USART_ID_e eId, bool bEnable)
{
    SET_USART_CR_RTO_EN(HLL_USART_REG(eId), bEnable);
}

/**
 * @brief Enable or disable the Receive Time-Out (RTO) interrupt (CR2.RTOIE).
 */
__STATIC_INLINE void HLL_USART_SetRtoIntrEnable(USART_ID_e eId, bool bEnable)
{
    SET_USART_IER_RTO_EN(HLL_USART_REG(eId), bEnable);
}

/**
 * @brief Clear the latched Receive Time-Out (RTO) status flag.
 */
__STATIC_INLINE void HLL_USART_ClearRtoFlag(USART_ID_e eId)
{
    SET_USART_IER_RTO_FLAG(HLL_USART_REG(eId), true);
}

/**
 * @brief Write the raw baud-divider register directly (SPI mode).
 */
__STATIC_INLINE void HLL_USART_SetSpiBaudRaw(USART_ID_e eId, uint16_t un16Bdr)
{
    SET_USART_CR_BDR(HLL_USART_REG(eId), un16Bdr);
}

/**
 * @brief Enable or disable hardware SS generation (SPI mode).
 */
__STATIC_INLINE void HLL_USART_SetSpiSSEnable(USART_ID_e eId, bool bEnable)
{
    SET_USART_CR_SSEN(HLL_USART_REG(eId), bEnable);
}

/**
 * @brief Program the baud-rate divider with fractional correction (UART/USRT modes).
 *
 * @param[in] un32Bdr Integer divider value, already decremented by 1 by the caller.
 * @param[in] un32Bfr Fractional correction value (8-bit).
 */
__STATIC_INLINE void HLL_USART_SetBaudRate(USART_ID_e eId, uint32_t un32Bdr, uint32_t un32Bfr)
{
    USART_Type *ptUsart = HLL_USART_REG(eId);

    SET_USART_CR_BDR(ptUsart, un32Bdr & 0xFFFFU);
    SET_USART_CR_FPCR(ptUsart, un32Bfr & 0xFFU);
    SET_USART_CR_FPCREN(ptUsart, true);
}

/**
 * @brief Enable or disable the transmitter.
 */
__STATIC_INLINE void HLL_USART_SetTxEnable(USART_ID_e eId, bool bEnable)
{
    SET_USART_CR_TXEN(HLL_USART_REG(eId), bEnable);
}

/**
 * @brief Enable or disable the receiver.
 */
__STATIC_INLINE void HLL_USART_SetRxEnable(USART_ID_e eId, bool bEnable)
{
    SET_USART_CR_RXEN(HLL_USART_REG(eId), bEnable);
}

/**
 * @brief Enable or disable the USART block.
 *
 * Must be called after master/polarity/phase are configured in SPI mode.
 */
__STATIC_INLINE void HLL_USART_SetEnable(USART_ID_e eId, bool bEnable)
{
    SET_USART_CR_EN(HLL_USART_REG(eId), bEnable);
}

/**
 * @brief Set the 9th transmit data bit (9-bit UART/USRT modes).
 */
__STATIC_INLINE void HLL_USART_SetTxNinthBit(USART_ID_e eId, bool bBit)
{
    SET_USART_CR_TXBIT_NINTH(HLL_USART_REG(eId), bBit);
}

/**
 * @brief Get the 9th receive data bit (9-bit UART/USRT modes).
 */
__STATIC_INLINE bool HLL_USART_GetRxNinthBit(USART_ID_e eId)
{
    return (bool)GET_USART_CR_RXBIT_NINTH(HLL_USART_REG(eId));
}

#if defined(USART_FEATURE_MASTER_SS_PIN_BY_GPIO)
/**
 * @brief Drive the SPI slave-select pin level (master mode, GPIO-controlled SS).
 */
__STATIC_INLINE void HLL_USART_SetSpiSlaveSelect(USART_ID_e eId, bool bLevel)
{
    USART_SetSSPort((P_USART_ID_e)eId, bLevel);
}
#endif

/**
 * @brief Enable or disable a USART instance as a wake-up source.
 */
__STATIC_INLINE void HLL_USART_SetWakeupSrc(USART_ID_e eId, bool bEnable)
{
    USART_SetWkupSrc((P_USART_ID_e)eId, bEnable);
    SET_USART_IER_WAKE_EN(HLL_USART_REG(eId), bEnable);
}

/**
 * @brief Write one data word to the transmit data register.
 *
 * Also arms the Data-Register-Empty status flag, matching the sequence
 * required by hardware before writing DR (see HAL_USART_Transmit()).
 */
__STATIC_INLINE void HLL_USART_TransmitByte(USART_ID_e eId, uint32_t un32Data)
{
    USART_Type *ptUsart = HLL_USART_REG(eId);

    SET_USART_IER_DR_FLAG(ptUsart, true);
    SET_USART_DR(ptUsart, un32Data);
}

/**
 * @brief Read one data word from the receive data register.
 */
__STATIC_INLINE uint32_t HLL_USART_ReceiveByte(USART_ID_e eId)
{
    return GET_USART_DR(HLL_USART_REG(eId));
}

/**
 * @brief Get Data-Register-Empty status (true = ready to accept a new TX byte).
 */
__STATIC_INLINE bool HLL_USART_GetTxReady(USART_ID_e eId)
{
    return (bool)GET_USART_IER_DR_FLAG(HLL_USART_REG(eId));
}

/**
 * @brief Get Receive-Complete status (true = a byte is available to read).
 */
__STATIC_INLINE bool HLL_USART_GetRxReady(USART_ID_e eId)
{
    return (bool)GET_USART_IER_RXC_FLAG(HLL_USART_REG(eId));
}

/**
 * @brief Enable or disable the Transmit-Complete interrupt.
 *
 * This is the only maskable TX interrupt source on this IP: there is no
 * separate Data-Register-Empty interrupt enable, so TX-ready polling
 * (HLL_USART_GetTxReady()) is combined with this to drive interrupt mode.
 */
__STATIC_INLINE void HLL_USART_SetTxIntrEnable(USART_ID_e eId, bool bEnable)
{
    SET_USART_IER_TXC_EN(HLL_USART_REG(eId), bEnable);
}

/**
 * @brief Get Transmit-Complete interrupt enable state.
 */
__STATIC_INLINE bool HLL_USART_GetTxIntrEnable(USART_ID_e eId)
{
    return (bool)GET_USART_IER_TXC_EN(HLL_USART_REG(eId));
}

/**
 * @brief Enable or disable the Receive-Complete interrupt.
 */
__STATIC_INLINE void HLL_USART_SetRxIntrEnable(USART_ID_e eId, bool bEnable)
{
    SET_USART_IER_RXC_EN(HLL_USART_REG(eId), bEnable);
}

/**
 * @brief Get the raw status register (see USART_STATUS_* bit masks).
 */
__STATIC_INLINE uint32_t HLL_USART_GetStatus(USART_ID_e eId)
{
    return GET_USART_SR(HLL_USART_REG(eId));
}

/**
 * @brief Clear latched error/event status bits (PE/FE/DOR/RTO/WAKE).
 *
 * @param[in] un32Status Bits to clear, as read from HLL_USART_GetStatus().
 *                        Only bits covered by USART_STATUS_MASK_BITS apply;
 *                        RXC/TXC/DRE are not write-1-to-clear on this IP.
 */
__STATIC_INLINE void HLL_USART_ClearStatus(USART_ID_e eId, uint32_t un32Status)
{
    SET_USART_SR(HLL_USART_REG(eId), un32Status & USART_STATUS_MASK_BITS);
}

/* end of inline function */

/**
 *******************************************************************************
 * @brief       Calculate the UART/USRT baud-rate divider and fractional
 *              correction for a target baud rate.
 * @param[in]   un32BaudRate : Target baud rate, in bps.
 * @param[in]   bDoubleSpeed : Double-speed (BCV=8) vs normal (BCV=16) sampling.
 * @param[out]  *pun32Bdr : Integer divider, already decremented by 1, ready
 *                          for HLL_USART_SetBaudRate().
 * @param[out]  *pun32Bfr : Fractional correction value (8-bit), ready for
 *                          HLL_USART_SetBaudRate().
 * @return      void : None
 ******************************************************************************/
void HLL_USART_CalcUartBaud(uint32_t un32BaudRate, bool bDoubleSpeed, uint32_t *pun32Bdr,
                             uint32_t *pun32Bfr);

#endif /* _HLL_USART_H_ */

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */
