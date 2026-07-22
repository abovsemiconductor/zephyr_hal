/**
 *******************************************************************************
 * @file        config_a31c11x.h
 * @author      ABOV R&D Division
 * @brief       A31C11x config file
 *
 * Copyright 2026 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/** @addtogroup VENDOR ABOV Semiconductor Co., Ltd.
  * @{
  */


/** @addtogroup A31C11x
  * @{
  */

#ifndef CONFIG_A31C11X_H
#define CONFIG_A31C11X_H


/* Platform Specific module config */
#define CONFIG_MODULE_FMC_UNIFIED        0

#include "a31c11x.h"
#include "abov_module.h"

/* Mapping ISR function */
/* Adding all of ISR function defines */
/* There is no error when compiling them */

/* SCU IP version */
#define CONFIG_SCU_VER_VENDOR           'V'
#define CONFIG_SCU_VER_MAJOR             4
#define CONFIG_SCU_VER_EXT               0
#define CONFIG_SCU_VER_MINOR             2
#define CONFIG_SCU_REG_NAME              0

#define CONFIG_SCU_NMI_MAX_COUNT         8
#define CONFIG_SCU_CLK_MON_MAX_COUNT     1
#define CONFIG_SCU_CLK_LSE_NO_FEATURE
#define CONFIG_SCU_CLK_HSE_NO_FEATURE

/* SCU NMI Interrupt Handler */
#if defined (EXTRN_FPA_CFMC) || defined (EXTRN_FPA_DFMC)
#else
#define _NMI                             1
#define CONFIG_NMI_ANY_INTERRUPT         1
#define NMI_IRQHandler                   NMI_Handler
#endif

#if defined(_MODULE_SCU_LVD)

#define _SCU_LVD                         1

/* SCU LVD Interrupt Handler */
#define SCULVD_IRQHandler                Interrupt0_Handler

/* SCU LVD Interrupt Number */
#define SCULVD_0_IRQ                     LVI_IRQn

#endif /* _MODULE_SCU_LVD */

#if defined(_MODULE_SCU_PWR)

#define _SCU_PWR                         1

#endif /* _MODULE_SCU_PWR */

/* PCU IP version */
#define CONFIG_PCU_VER_VENDOR           'V'
#define CONFIG_PCU_VER_MAJOR             2
#define CONFIG_PCU_VER_EXT               0
#define CONFIG_PCU_VER_MINOR             6
#define CONFIG_PCU_REG_NAME              0
#define CONFIG_PCU_MAX_COUNT             6

/* PCU Interrupt Handler */
#define PCU0_IRQHandler                  Interrupt11_Handler
#define PCU1_IRQHandler                  Interrupt12_Handler
#define PCU2_IRQHandler                  Interrupt13_Handler

/* PCU Interrupt Number */
#define PCU_0_IRQ                        GPIOAB_IRQn
#define PCU_1_IRQ                        GPIOCD_IRQn
#define PCU_2_IRQ                        GPIOEF_IRQn

#if defined(_MODULE_UART)

#define _UART                            1

/* UART IP version */
#define CONFIG_UART_VER_VENDOR          'V'
#define CONFIG_UART_VER_MAJOR            1
#define CONFIG_UART_VER_EXT              0
#define CONFIG_UART_VER_MINOR            8
#define CONFIG_UART_REG_NAME             0

/* UART Maximum IP Count */
#define CONFIG_UART_MAX_COUNT            1

/* UART Interrupt Handler */
#define UART0_IRQHandler                 Interrupt20_Handler

/* UART Interrupt Number */
#define UART_0_IRQ                       UART0_IRQn

/* UART Config */
#define CONFIG_UART_REG_MCCR             1

#endif /* _MODULE_UART */

#if defined(_MODULE_TIMER1)

#define _TIMER1                          1

/* TIMER1 IP version */
#define CONFIG_TIMER1_VER_VENDOR        'V'
#define CONFIG_TIMER1_VER_MAJOR          1
#define CONFIG_TIMER1_VER_EXT            2
#define CONFIG_TIMER1_VER_MINOR          0
#define CONFIG_TIMER1_REG_NAME           0

/* TIMER1 Maximum IP Count */
#define CONFIG_TIMER1_MAX_COUNT          4

/* TIMER1 MCCR Config */
#define CONFIG_TIMER1_MCCR_NUM                3
#define CONFIG_TIMER1_MCCR_GROUP_COUNT        1
#define CONFIG_TIMER1_MCCR_COUNT_PER_GROUP    3

/* TIMER1 Interrupt Handler */
#define TIMER10_IRQHandler               Interrupt7_Handler
#define TIMER11_IRQHandler               Interrupt8_Handler
#define TIMER12_IRQHandler               Interrupt9_Handler
#define TIMER13_IRQHandler               Interrupt10_Handler

/* TIMER1 Interrupt Number */
#define TIMER1_0_IRQ                     TIMER0_IRQn
#define TIMER1_1_IRQ                     TIMER1_IRQn
#define TIMER1_2_IRQ                     TIMER2_IRQn
#define TIMER1_3_IRQ                     TIMER3_IRQn

#endif /* _MODULE_TIMER1 */

#if defined(_MODULE_ADC)

#define _ADC                             1

/* ADC IP version */
#define CONFIG_ADC_VER_VENDOR           'V'
#define CONFIG_ADC_VER_MAJOR             1
#define CONFIG_ADC_VER_EXT               0
#define CONFIG_ADC_VER_MINOR             2
#define CONFIG_ADC_REG_NAME              0

/* ADC Maximum IP Count */
#define CONFIG_ADC_MAX_COUNT             1

/* ADC IRQ */
#define ADC0_IRQHandler                  Interrupt22_Handler

/* ADC IRQ Number */
#define ADC_0_IRQ                        ADC_IRQn

#endif /* _MODULE_ADC */

#if defined(_MODULE_USART) || (TARGET_BOARD_DEBUG_ENABLE == 1)

#define _USART                           1

/* USART IP version */
#define CONFIG_USART_VER_VENDOR         'F'
#define CONFIG_USART_VER_MAJOR           1
#define CONFIG_USART_VER_EXT             2
#define CONFIG_USART_VER_MINOR           1
#define CONFIG_USART_REG_NAME            0

/* USART Maximum IP Count */
#define CONFIG_USART_MAX_COUNT           1

/* USART Interrupt Handler */
#define USART0_IRQHandler                Interrupt16_Handler

/* USART Interrupt Number */
#define USART_0_IRQ                      USART10_IRQn

#endif /* _MODULE_USART */

#if defined(_MODULE_I2C)

#define _I2C                             1

/* I2C IP version */
#define CONFIG_I2C_VER_VENDOR           'V'
#define CONFIG_I2C_VER_MAJOR             1
#define CONFIG_I2C_VER_EXT               0
#define CONFIG_I2C_VER_MINOR             0
#define CONFIG_I2C_REG_NAME              3

/* I2C Maximum IP Count */
#define CONFIG_I2C_MAX_COUNT             1

/* I2C Interrupt Handler */
#define I2C0_IRQHandler                  Interrupt19_Handler

/* I2C Interrupt Number */
#define I2C_0_IRQ                        I2C0_IRQn

#endif /* _MODULE_I2C */

#if defined(_MODULE_CRC)

#define _CRC                             1

/* CRC IP version */
#define CONFIG_CRC_VER_VENDOR           'V'
#define CONFIG_CRC_VER_MAJOR             2
#define CONFIG_CRC_VER_EXT               0
#define CONFIG_CRC_VER_MINOR             4
#define CONFIG_CRC_REG_NAME              0

/* CRC Maximum IP Count */
#define CONFIG_CRC_MAX_COUNT             1

#endif /* _MODULE_CRC */

#if defined(_MODULE_CFMC)
#define _CFMC                            1

#define CONFIG_CFMC_VER_VENDOR          'V'
#define CONFIG_CFMC_VER_MAJOR            3
#define CONFIG_CFMC_VER_EXT              1
#define CONFIG_CFMC_VER_MINOR            1
#define CONFIG_CFMC_REG_NAME             0

/* FMC IRQ */
#define CFMC_IRQ_Handler                 Interrupt6_Handler

/* Bank switching */
#define CONFIG_CFMC_BANK_SWITCH          0

/* Passwork Lock */
#define CONFIG_CFMC_PASSWD_LOCK          1

/* CRC */
#define CONFIG_FMC_CRC                   0

#endif /* _MODULE_CFMC */

#if defined(_MODULE_WDT)

#define _WDT                             1

/* WDT IP version */
#define CONFIG_WDT_VER_VENDOR           'V'
#define CONFIG_WDT_VER_MAJOR             1
#define CONFIG_WDT_VER_EXT               0
#define CONFIG_WDT_VER_MINOR             2
#define CONFIG_WDT_REG_NAME              0

/* WT Maximum IP Count */
#define CONFIG_WDT_MAX_COUNT             1

/* WT Interrupt Handler */
#define WDT0_IRQHandler                  Interrupt4_Handler

/* WT Interrupt Number */
#define WDT_0_IRQ                        WDT_IRQn

#endif /* _MODULE_WDT */


/* Just in case of no register to give debugger connection */
#define CONFIG_EMUL_JTAG_CONNECTION      0
#if defined (EXTRN_FPA_CFMC) || defined (EXTRN_FPA_DFMC)
#undef CONFIG_EMUL_JTAG_CONNECTION
#endif


/* Put handling unsupported modules which are enabled by A31xxxx SVD (abov_module.h) */


#endif /* CONFIG_A31C11X_H */

/** @} */ /* End of group A31C11x */

/** @} */ /* End of group VENDOR ABOV Semiconductor Co., Ltd. */
