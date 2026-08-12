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

/* for abov simpleapp config */
#if defined(EXTRN_ABOV_SIMPLEAPP_CONFIG)
#undef ABOV_SIMPLEAPP_CONFIG_H
#include "abov_simpleapp_config.h"
#endif

/*
 * Module Enable/Disable Control
 * XXX_BASE defines Chipset header file (a31xxxx.h) created by SVD file.
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

/* TIMER2n Module */
#if (CONFIG_HAL_TIMER2 == 1) && defined(TIMER20_BASE)
#define _MODULE_TIMER2
#endif

/* TIMER3n Module */
#if (CONFIG_HAL_TIMER3 == 1) && defined(TIMER30_BASE)
#define _MODULE_TIMER3
#endif

/* TIMER4n Module */
#if (CONFIG_HAL_TIMER4 == 1) && defined(TIMER40_BASE)
#define _MODULE_TIMER4
#endif

/* TIMER4En Module */
#if (CONFIG_HAL_TIMER4E == 1) && defined(TIMER40_BASE)
#define _MODULE_TIMER4E
#endif

/* TIMER5 Module */
#if (CONFIG_HAL_TIMER5 == 1) && defined(TIMER50_BASE)
#define _MODULE_TIMER5
#endif

/* TIMER6 Module */
#if (CONFIG_HAL_TIMER6 == 1) && defined(TIMER60_BASE)
#define _MODULE_TIMER6
#endif

/* Uart Module */
#if (CONFIG_HAL_UART == 1) && defined(UART0_BASE)
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

/* CRC Module */
#if (CONFIG_HAL_CRC == 1) && defined(CRC_BASE)
#define _MODULE_CRC
#endif

#if defined(CONFIG_HAL_AES) && defined(AES_BASE)
#define _MODULE_AES
#endif

#if defined(CONFIG_HAL_TRNG) && defined(RNG_BASE)
#define _MODULE_TRNG
#endif

/* DMAC Module */
#if (CONFIG_HAL_DMAC == 1) && (defined(DMA0_BASE) || defined(DMAC0_BASE))
#define _MODULE_DMAC
#endif

/* WT Module */
#if (CONFIG_HAL_WT == 1) && defined(WT_BASE)
#define _MODULE_WT
#endif

/* WDT Module */
#if (CONFIG_HAL_WDT == 1) && defined(WDT_BASE)
#define _MODULE_WDT
#endif

/* MPWM Module */
#if (CONFIG_HAL_MPWM == 1) && defined(MPWM_BASE)
#define _MODULE_MPWM
#endif

/* I2C Module */
#if (CONFIG_HAL_I2C == 1) && (defined(I2C0_BASE) || defined(I2C_BASE))
#define _MODULE_I2C
#endif

/* SPI Module */
#if (CONFIG_HAL_SPI == 1) && (defined(SPI20_BASE) || defined(SPI_BASE) || defined(SPI0_BASE) || defined(SPI1_BASE))
#define _MODULE_SPI
#endif

/* DAC Module */
#if (CONFIG_HAL_DAC == 1) && defined(DAC_BASE)
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

/* LCD Module */
#if (CONFIG_HAL_LCD == 1) && defined(LCD_BASE)
#define _MODULE_LCD
#endif

#if (CONFIG_HAL_USB == 1) && defined(USB_BASE)
#define _MODULE_USB
#endif

/* ADC Module */
#if (CONFIG_HAL_ADC == 1) && defined(ADC_BASE)
#define _MODULE_ADC
#endif

/* CMP Module */
#if (CONFIG_HAL_CMP == 1) && (defined(CMP_BASE) || defined(COMP_BASE) || defined(CMP0_BASE))
#define _MODULE_CMP
#endif

/* TS Module */
#if (CONFIG_HAL_TEMPSENS == 1) && (defined(TEMP_BASE) || defined(TS_BASE))
#define _MODULE_TEMPSENS
#endif

/* LED Module */
#if (CONFIG_HAL_LED == 1) && defined(LED_BASE)
#define _MODULE_LED
#endif

/* RTC Module */
#if (CONFIG_HAL_RTC == 1) && (defined(RTC_BASE) || defined(RTCC_BASE))
#define _MODULE_RTC
#endif

/* EBI Module */
#if (CONFIG_HAL_EBI == 1) && defined(EBI_BASE)
#define _MODULE_EBI
#endif

/* FRT Module */
#if (CONFIG_HAL_FRT == 1) && (defined(FRT0_BASE) || defined(FRT_BASE))
#define _MODULE_FRT
#endif

/* HSICMU Module */
#if (CONFIG_HAL_HSICMU == 1) && defined(HSICMU_BASE)
#define _MODULE_HSICMU
#endif

/* COA Module */
#if defined(COA1_BASE)
#define _MODULE_COA
#endif

#endif /* _ABOV_MODULES_H_*/
