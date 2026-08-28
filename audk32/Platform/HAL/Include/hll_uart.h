/**
 *******************************************************************************
 * @file        hll_uart.h
 * @author      ABOV R&D Division
 * @brief       Universal Asynchronous Receiver Transmitter (Low Level)
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
 * @defgroup    HLL_UART UART
 * @{
 * @brief       Universal Asynchronous Receiver Transmitter (UART), Low Level
 *
 * Unlike HAL_UART, this layer does not own an interrupt vector, a control
 * block, or DMA state: it only wraps direct register access. Callers are
 * expected to connect the IRQ returned by HLL_UART_GetIRQNum() to their own
 * handler and drive TX/RX byte-by-byte from it.
 *
 * This IP is a classic 16550-style UART: ELSR (line status) and IIR
 * (interrupt id) are read-to-clear -- reading them acknowledges whatever
 * condition they report, there is no separate write-1-to-clear step like
 * HLL_USART's status register.
 */

#ifndef _HLL_UART_H_
#define _HLL_UART_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"
#include "type/uart_type.h"
#include "../UART/hal_uart_prv.h"

#define HLL_UART_REG(eId)    UART_GetReg((uint32_t)(eId))

/* __inline function */

/**
 * @brief Enable or disable the peripheral clock for a UART instance.
 */
__STATIC_INLINE HAL_ERR_e HLL_UART_SetClockEnable(UART_ID_e eId, bool bEnable)
{
    return UART_SetScuEnable((P_UART_ID_e)eId, bEnable);
}

/**
 * @brief Get the NVIC IRQ number for a UART instance.
 *
 * The caller owns the vector: connect this IRQ number to its own handler
 * (e.g. via the host RTOS's IRQ_CONNECT-equivalent) instead of relying on
 * a fixed-name weak handler.
 */
__STATIC_INLINE IRQn_Type HLL_UART_GetIRQNum(UART_ID_e eId)
{
    return UART_GetIRQNum((P_UART_ID_e)eId);
}

/**
 * @brief Select the bit-rate clock source (MCCR mux + divider) feeding this
 *        UART's baud-rate generator.
 *
 * On IP variants without MCCR support this is a no-op (the divider always
 * runs from PCLK); see UART_FEATURE_MCCR in the active version header.
 */
__STATIC_INLINE HAL_ERR_e HLL_UART_SetClkSource(UART_ID_e eId, UART_CLK_MCCR_e eMccr,
                                                 uint8_t un8Div)
{
    return UART_SetClk((P_UART_ID_e)eId, (P_UART_CLK_MCCR_e)eMccr, un8Div);
}

/**
 * @brief Clear IER/LCR/DCR to their reset state.
 */
__STATIC_INLINE void HLL_UART_ClearControl(UART_ID_e eId)
{
    UART_Type *ptUart = HLL_UART_REG(eId);

    SET_UART_IER(ptUart, 0);
    SET_UART_LCR(ptUart, 0);
    SET_UART_DCR(ptUart, 0);
}

/**
 * @brief Configure the data/parity/stop frame format.
 *
 * UART_PARITY_NONE clears the parity-enable bit instead of writing the
 * 2-bit PARITY field (which has no code point for "none").
 */
__STATIC_INLINE void HLL_UART_SetFormat(UART_ID_e eId, UART_PARITY_e eParity, UART_DATA_e eData,
                                         UART_STOP_e eStop)
{
    UART_Type *ptUart = HLL_UART_REG(eId);

    SET_UART_LCR_DLEN(ptUart, (uint32_t)eData);

    if (eParity == UART_PARITY_NONE)
    {
        SET_UART_LCR_PEN(ptUart, false);
    }
    else
    {
        SET_UART_LCR_PEN(ptUart, true);
        SET_UART_LCR_PARITY(ptUart, (uint32_t)eParity);
    }

    SET_UART_LCR_STOPBIT(ptUart, (uint32_t)eStop);
}

/**
 * @brief Program the baud-rate divider with fractional correction.
 *
 * @param[in] un32Bdr Integer divider value (see HLL_UART_CalcUartBaud()).
 * @param[in] un32Bfr Fractional correction value (8-bit).
 */
__STATIC_INLINE void HLL_UART_SetBaudRate(UART_ID_e eId, uint32_t un32Bdr, uint32_t un32Bfr)
{
    UART_Type *ptUart = HLL_UART_REG(eId);

    SET_UART_BDR_BDR(ptUart, un32Bdr & 0xFFFFU);
    SET_UART_BFR_BFR(ptUart, un32Bfr & 0xFFU);
}

/**
 * @brief Write one byte to the transmit holding register.
 */
__STATIC_INLINE void HLL_UART_TransmitByte(UART_ID_e eId, uint8_t un8Data)
{
    SET_UART_THR_DATA(HLL_UART_REG(eId), un8Data);
}

/**
 * @brief Read one byte from the receive buffer register.
 */
__STATIC_INLINE uint8_t HLL_UART_ReceiveByte(UART_ID_e eId)
{
    return (uint8_t)GET_UART_RBR_DATA(HLL_UART_REG(eId));
}

/**
 * @brief Get Transmit-Holding-Register-Empty status (true = ready to accept
 *        a new TX byte).
 */
__STATIC_INLINE bool HLL_UART_GetTxReady(UART_ID_e eId)
{
    return (bool)GET_UART_LSR_THRE(HLL_UART_REG(eId));
}

/**
 * @brief Get Transmitter-Empty status (true = shift register and holding
 *        register are both empty -- transmission fully complete).
 */
__STATIC_INLINE bool HLL_UART_GetTxComplete(UART_ID_e eId)
{
    return (bool)GET_UART_LSR_TEMT(HLL_UART_REG(eId));
}

/**
 * @brief Get Data-Ready status (true = a received byte is available in RBR).
 */
__STATIC_INLINE bool HLL_UART_GetRxReady(UART_ID_e eId)
{
    return (bool)GET_UART_LSR_DR(HLL_UART_REG(eId));
}

/**
 * @brief Get the raw Extended Line Status Register.
 *
 * Reading this register clears its latched bits (see UART_LINE_STATUS_e in
 * hal_uart.h for the bit layout -- RX_DONE/OVERRUN/PARITY/FRAME/BREAK are
 * only meaningful once, at the moment of the read that surfaced them).
 */
__STATIC_INLINE uint32_t HLL_UART_GetLineStatus(UART_ID_e eId)
{
    return GET_UART_LSR(HLL_UART_REG(eId)) & 0x7FU;
}

/**
 * @brief Get the raw Interrupt Identification Register.
 *
 * Reading this register acknowledges/identifies the currently latched
 * interrupt cause (see the UART_IIR_* bit masks in the active version
 * header, e.g. UART_IIR_RX_DATA_AVAIL, UART_IIR_TX_HOLD_EMPTY).
 */
__STATIC_INLINE uint32_t HLL_UART_GetIntrStatus(UART_ID_e eId)
{
    return GET_UART_IIR(HLL_UART_REG(eId));
}

/**
 * @brief Enable or disable the Receiver Line Status interrupt.
 */
__STATIC_INLINE void HLL_UART_SetLineIntrEnable(UART_ID_e eId, bool bEnable)
{
    SET_UART_IER_RLSIE(HLL_UART_REG(eId), bEnable);
}

/**
 * @brief Enable or disable the Transmit-Holding-Register-Empty interrupt
 *        (fires when HLL_UART_GetTxReady() would return true).
 */
__STATIC_INLINE void HLL_UART_SetTxReadyIntrEnable(UART_ID_e eId, bool bEnable)
{
    SET_UART_IER_THREIE(HLL_UART_REG(eId), bEnable);
}

/**
 * @brief Enable or disable the Transmitter-Empty interrupt (fires when
 *        HLL_UART_GetTxComplete() would return true).
 */
__STATIC_INLINE void HLL_UART_SetTxCompleteIntrEnable(UART_ID_e eId, bool bEnable)
{
    SET_UART_IER_TXEIE(HLL_UART_REG(eId), bEnable);
}

/**
 * @brief Enable or disable the Data-Ready (RX) interrupt.
 */
__STATIC_INLINE void HLL_UART_SetRxIntrEnable(UART_ID_e eId, bool bEnable)
{
    SET_UART_IER_DRIE(HLL_UART_REG(eId), bEnable);
}

/**
 * @brief Enable or disable the DMA-TX-done interrupt.
 *
 * Distinct from HLL_UART_SetTxReadyIntrEnable(): this gates the DMA
 * completion interrupt (IER.DTXIEN), not the byte-at-a-time THRE interrupt.
 */
__STATIC_INLINE void HLL_UART_SetTxDmaIntrEnable(UART_ID_e eId, bool bEnable)
{
    SET_UART_IER_DTXIEN(HLL_UART_REG(eId), bEnable);
}

/**
 * @brief Enable or disable the DMA-RX-done interrupt.
 *
 * Distinct from HLL_UART_SetRxIntrEnable(): this gates the DMA completion
 * interrupt (IER.DRXIEN), not the byte-at-a-time data-ready interrupt.
 */
__STATIC_INLINE void HLL_UART_SetRxDmaIntrEnable(UART_ID_e eId, bool bEnable)
{
    SET_UART_IER_DRXIEN(HLL_UART_REG(eId), bEnable);
}

/**
 * @brief Force the TX line to the BREAK (space) condition, or release it.
 */
__STATIC_INLINE void HLL_UART_SetBreak(UART_ID_e eId, bool bEnable)
{
    SET_UART_LCR_BREAK(HLL_UART_REG(eId), bEnable);
}

/**
 * @brief Set the inter-frame delay (delay inserted between frames, 0 - 7).
 */
__STATIC_INLINE void HLL_UART_SetIFDelay(UART_ID_e eId, uint8_t un8Delay)
{
    SET_UART_IDTR_WAITVAL(HLL_UART_REG(eId), un8Delay);
}

/* end of __inline function */

/**
 *******************************************************************************
 * @brief       Calculate the UART baud-rate divider and fractional
 *              correction for a target baud rate.
 * @param[in]   un32BaudRate : Target baud rate, in bps.
 * @param[out]  *pun32Bdr : Integer divider, ready for HLL_UART_SetBaudRate().
 * @param[out]  *pun32Bfr : Fractional correction value (8-bit), ready for
 *                          HLL_UART_SetBaudRate().
 * @return      void : None
 ******************************************************************************/
void HLL_UART_CalcUartBaud(uint32_t un32BaudRate, uint32_t *pun32Bdr, uint32_t *pun32Bfr);

#ifdef __cplusplus
}
#endif

#endif /* _HLL_UART_H_ */

/** @} */
/** @} */
