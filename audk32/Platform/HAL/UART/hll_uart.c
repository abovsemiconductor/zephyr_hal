/**
 *******************************************************************************
 * @file        hll_uart.c
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

#include "abov_config.h"

#if defined(_UART)
#include "hll_uart.h"

void HLL_UART_CalcUartBaud(uint32_t un32BaudRate, uint32_t *pun32Bdr, uint32_t *pun32Bfr)
{
    uint32_t un32Numer = UART_GetNumer();
    uint32_t un32Denom = 16U * un32BaudRate;
    uint32_t un32Bdr = un32Numer / un32Denom;
    uint32_t un32Fd = un32Numer - (un32Bdr * un32Denom);

    *pun32Bdr = un32Bdr;
    *pun32Bfr = (un32Fd * 256U) / un32Denom;
}

#endif /* _UART */
