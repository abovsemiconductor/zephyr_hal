/**
 *******************************************************************************
 * @file        abov_module.h
 * @author      ABOV R&D Division
 * @brief       Import modules to target into device
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _ABOV_MODULES_H_
#define _ABOV_MODULES_H_

/* for abov example source */
#if defined(EXTRN_ABOV_EXAMPLE_CONFIG)
#undef _EXAMPLE_CONFIG_H_
#include "abov_example_config.h"
#endif

/* for abov module config */
#if defined(EXTRN_ABOV_MODULE_CONFIG)
#undef ABOV_MODULE_CONFIG_H
#include "abov_module_config.h"
#endif

/*
 * Module Enable/Disable Control
 * XXX_BASE defines Chipset header file (a34xxxx.h) created by SVD file.
 */

/* SCU LVD */
#if (CONFIG_HAL_SCU_LVD == 1)
#define _MODULE_SCU_LVD
#endif

/* SCU PWRW */
#if (CONFIG_HAL_SCU_PWR == 1)
#define _MODULE_SCU_PWR
#endif

/* Port */
#if defined(PA_BASE)
#define _MODULE_GPIO
#endif

/* TIMER1n Module */
#if (CONFIG_HAL_TIMER1 == 1) && (defined(TIMER10_BASE) || defined(TIMER0_BASE))
#define _MODULE_TIMER1
#endif

/* Uart Module */
#if (CONFIG_HAL_UART == 1) && (defined(UART0_BASE) || defined(UART_BASE))
#define _MODULE_UART
#endif

/* LPUart Module */
#if (CONFIG_HAL_LPUART == 1) && (defined(LPUART0_BASE) || defined(LPUART_BASE))
#define _MODULE_LPUART
#endif

/* Usart Module */
#if (CONFIG_HAL_USART == 1) && defined(USART10_BASE)
#define _MODULE_USART
#endif

#if (CONFIG_HAL_CRC == 1) && defined(CRC_BASE)
#define _MODULE_CRC
#endif

/* DMAC Module */
#if (CONFIG_HAL_DMAC == 1) && (defined(DMA0_BASE) || defined(DMAC0_BASE))
#define _MODULE_DMAC
#endif

/* FRT Module */
#if (CONFIG_HAL_FRT == 1) && (defined(FRT0_BASE) || defined(FRT_BASE))
#define _MODULE_FRT
#endif

/* WDT Module */
#if (CONFIG_HAL_WDT == 1) && defined(WDT_BASE)
#define _MODULE_WDT
#endif

/* I2C Module */
#if (CONFIG_HAL_I2C == 1) && defined(I2C0_BASE)
#define _MODULE_I2C
#endif

/* SPI Module */
#if (CONFIG_HAL_SPI == 1) && (defined(SPI20_BASE) || defined(SPI0_BASE))
#define _MODULE_SPI
#endif

/* ADC Module */
#if (CONFIG_HAL_ADC == 1) && (defined(ADC_BASE) || defined(ADC0_BASE))
#define _MODULE_ADC
#endif

/* DAC Module */
#if (CONFIG_HAL_DAC == 1) && (defined(DAC_BASE) || defined(DAC0_BASE))
#define _MODULE_DAC
#endif

/* FMC Module */
#if (CONFIG_MODULE_FMC_UNIFIED)
#if ((CONFIG_HAL_FMC == 1) || defined (EXTRN_CONFIG_HAL_FMC))
#define _MODULE_CFMC
#define _MODULE_DFMC
#endif
#else
#if ((CONFIG_HAL_FMC == 1) || defined (EXTRN_CONFIG_HAL_FMC)) && (defined(FMC_BASE) || defined (CFMC_BASE))
#define _MODULE_CFMC
#endif
#if ((CONFIG_HAL_FMC == 1) || defined (EXTRN_CONFIG_HAL_FMC)) && defined(DFMC_BASE)
#define _MODULE_DFMC
#endif
#endif /* CONFIG_MODULE_FMC_UNIFIED */

#if (CONFIG_HAL_RNG == 1) && defined(RNG_BASE)
#define _MODULE_RNG
#endif

#if (CONFIG_HAL_AES == 1) && defined(AES128_BASE)
#define _MODULE_AES
#endif

#if (CONFIG_HAL_MPWM == 1) && defined(MPWM0_BASE)
#define _MODULE_MPWM
#endif

#if (CONFIG_HAL_QEI == 1) && defined(QEI0_BASE)
#define _MODULE_QEI
#endif

#if (CONFIG_HAL_CMP == 1) && (defined(COMP0_BASE) || defined(CMP0_BASE))
#define _MODULE_CMP
#endif

#if (CONFIG_HAL_PGA == 1) && defined(PGA0_BASE)
#define _MODULE_PGA
#endif

#if (CONFIG_HAL_RTC == 1) && (defined(RTC_BASE) || defined(RTCC_BASE))
#define _MODULE_RTC
#endif

#if (CONFIG_HAL_LCD == 1) && defined(LCD_BASE)
#define _MODULE_LCD
#endif

#if (CONFIG_HAL_USB == 1) && defined(USB_BASE)
#define _MODULE_USB
#endif

#if (CONFIG_HAL_VREFBUF == 1) && defined(VREFBUF_BASE)
#define _MODULE_VREFBUF
#endif

#if (CONFIG_HAL_PWM == 1) && defined(PWM0_BASE)
#define _MODULE_PWM
#endif

#if (CONFIG_HAL_QSPI == 1) && defined(QSPI_BASE)
#define _MODULE_QSPI
#endif

#endif /* _ABOV_MODEULS_H_*/
