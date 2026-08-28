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

/*
 * This file is picked up unconditionally by the audk32 HAL library's
 * file(GLOB_RECURSE ... Platform/HAL/*.c) (see modules/hal/abov32/audk32/
 * CMakeLists.txt) regardless of whether any app actually uses the UART
 * driver. hll_uart.h pulls in hal_uart_prv.h's UART-IP-version dispatch,
 * which #errors unless _MODULE_UART (and thus CONFIG_UART_VER_VENDOR etc.)
 * is defined -- so, like hal_uart.c, this whole file must stay inert unless
 * _UART is actually set, instead of only compiling correctly by accident
 * whenever some other translation unit happens to already need
 * CONFIG_HAL_UART == 1.
 */
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
