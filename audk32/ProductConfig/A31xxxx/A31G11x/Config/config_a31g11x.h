/**
 *******************************************************************************
 * @file        config_a31g11x.h
 * @author      ABOV R&D Division
 * @brief       A31G11x config file
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
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


/** @addtogroup A31G11x
  * @{
  */

#ifndef _CONFIG_A31G11X_H_
#define _CONFIG_A31G11X_H_


/* Platform Specific module config */
#define CONFIG_MODULE_FMC_UNIFIED        0
#define CONFIG_MODULE_COA                1

#include "a31g11x.h"
#include "abov_module.h"

/* Mapping ISR function */
/* Adding all of ISR function defines */
/* There is no error when compiling them */

/* SCU IP version */
#define CONFIG_SCU_VER_VENDOR           'F'
#define CONFIG_SCU_VER_MAJOR             1
#define CONFIG_SCU_VER_EXT               0
#define CONFIG_SCU_VER_MINOR             0
#define CONFIG_SCU_REG_NAME              0

#define CONFIG_SCU_NMI_MAX_COUNT         1
#define CONFIG_SCU_CLK_MON_MAX_COUNT     1

/* SCU NMI Interrupt Handler */
#if defined (EXTRN_FPA_CFMC) || defined (EXTRN_FPA_DFMC)
#else
#define _NMI                             1
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
#define CONFIG_PCU_VER_VENDOR           'F'
#define CONFIG_PCU_VER_MAJOR             1
#define CONFIG_PCU_VER_EXT               0
#define CONFIG_PCU_VER_MINOR             1
#define CONFIG_PCU_REG_NAME              0
#define CONFIG_PCU_MAX_COUNT             6

/* PCU Interrupt Handler */
#define PCU0_IRQHandler                  Interrupt3_Handler
#define PCU1_IRQHandler                  Interrupt4_Handler
#define PCU2_IRQHandler                  Interrupt5_Handler
#define PCU3_IRQHandler                  Interrupt6_Handler

/* PCU Interrupt Number */
#define PCU_0_IRQ                        EINT0_IRQn
#define PCU_1_IRQ                        EINT1_IRQn
#define PCU_2_IRQ                        EINT2_IRQn
#define PCU_3_IRQ                        EINT3_IRQn

#if defined(_MODULE_USART)

#define _USART                           1

/* USART IP version */
#define CONFIG_USART_VER_VENDOR         'F'
#define CONFIG_USART_VER_MAJOR           1
#define CONFIG_USART_VER_EXT             0
#define CONFIG_USART_VER_MINOR           1
#define CONFIG_USART_REG_NAME            0

/* USART Maximum IP Count */
#define CONFIG_USART_MAX_COUNT           2

/* USART Interrupt Handler */
#define USART0_IRQHandler                Interrupt11_Handler
#define USART1_IRQHandler                Interrupt17_Handler

/* USART Interrupt Number */
#define USART_0_IRQ                      USART10_IRQn
#define USART_1_IRQ                      USART11_IRQn

/* USART Configuration */
#define USART_0_SS_PORT                  PB_BASE
#define USART_0_SS_PIN                   3
#define USART_1_SS_PORT                  PD_BASE
#define USART_1_SS_PIN                   5

#endif /* _MODULE_USART */

#if defined(_MODULE_UART)

#define _UART                            1

/* UART IP version */
#define CONFIG_UART_VER_VENDOR          'V'
#define CONFIG_UART_VER_MAJOR            1
#define CONFIG_UART_VER_EXT              0
#define CONFIG_UART_VER_MINOR            5
#define CONFIG_UART_REG_NAME             0

/* UART Maximum IP Count */
#define CONFIG_UART_MAX_COUNT            2

/* UART Interrupt Handler */
#define UART0_IRQHandler                 Interrupt19_Handler
#define UART1_IRQHandler                 Interrupt20_Handler

/* UART Interrupt Number */
#define UART_0_IRQ                       UART0_IRQn
#define UART_1_IRQ                       UART1_IRQn

#endif /* _MODULE_UART */

#if defined(_MODULE_WT)

#define _WT                              1

/* WT IP version */
#define CONFIG_WT_VER_VENDOR            'F'
#define CONFIG_WT_VER_MAJOR              1
#define CONFIG_WT_VER_EXT                0
#define CONFIG_WT_VER_MINOR              1
#define CONFIG_WT_REG_NAME               0

/* WT Maximum IP Count */
#define CONFIG_WT_MAX_COUNT              1

/* WT Interrupt Hander */
#define WT0_IRQHandler                   Interrupt12_Handler

/* WT Interrupt Handler */
#define WT_0_IRQ                         WT_IRQn

#endif /* _MODULE_WT */

#if defined(_MODULE_WDT)

#define _WDT                             1

/* WDT IP version */
#define CONFIG_WDT_VER_VENDOR           'F'
#define CONFIG_WDT_VER_MAJOR             1
#define CONFIG_WDT_VER_EXT               0
#define CONFIG_WDT_VER_MINOR             1
#define CONFIG_WDT_REG_NAME              0

/* WT Maximum IP Count */
#define CONFIG_WDT_MAX_COUNT             1

/* WT Interrupt Handler */
#define WDT0_IRQHandler                  Interrupt2_Handler

/* WT Interrupt Number */
#define WDT_0_IRQ                        WDT_IRQn

#endif /* _MODULE_WDT */

#if defined(_MODULE_I2C)

#define _I2C                             1

/* I2C IP version */
#define CONFIG_I2C_VER_VENDOR           'F'
#define CONFIG_I2C_VER_MAJOR             1
#define CONFIG_I2C_VER_EXT               0
#define CONFIG_I2C_VER_MINOR             1
#define CONFIG_I2C_REG_NAME              0

/* I2C Maximum IP Count */
#define CONFIG_I2C_MAX_COUNT             2

/* I2C Interrupt Handler */
#define I2C0_IRQHandler                  Interrupt10_Handler
#define I2C1_IRQHandler                  Interrupt14_Handler

/* I2C Interrupt Number */
#define I2C_0_IRQ                        I2C0_IRQn
#define I2C_1_IRQ                        I2C1_IRQn

#endif /* _MODULE_I2C */

#if defined(_MODULE_CRC)

#define _CRC                             1

/* CRC IP version */
#define CONFIG_CRC_VER_VENDOR           'F'
#define CONFIG_CRC_VER_MAJOR             1
#define CONFIG_CRC_VER_EXT               0
#define CONFIG_CRC_VER_MINOR             0
#define CONFIG_CRC_REG_NAME              0

/* CRC Maximum IP Count */
#define CONFIG_CRC_MAX_COUNT             1

#endif /* _MODULE_CRC */

#if defined(_MODULE_TIMER1)

#define _TIMER1                          1

/* TIMER1 IP version */
#define CONFIG_TIMER1_VER_VENDOR        'F'
#define CONFIG_TIMER1_VER_MAJOR          1
#define CONFIG_TIMER1_VER_EXT            0
#define CONFIG_TIMER1_VER_MINOR          1
#define CONFIG_TIMER1_REG_NAME           0

/* TIMER1 Maximum IP Count */
#define CONFIG_TIMER1_MAX_COUNT          3

/* TIMER1 Interrupt Handler */
#define TIMER10_IRQHandler               Interrupt7_Handler
#define TIMER11_IRQHandler               Interrupt8_Handler
#define TIMER12_IRQHandler               Interrupt9_Handler

/* TIMER1 Interrupt Number */
#define TIMER1_0_IRQ                     TIMER10_IRQn
#define TIMER1_1_IRQ                     TIMER11_IRQn
#define TIMER1_2_IRQ                     TIMER12_IRQn

#endif /* _MODULE_TIMER1 */

#if defined(_MODULE_TIMER2)

#define _TIMER2                          1

/* TIMER2 IP version */
#define CONFIG_TIMER2_VER_VENDOR        'F'
#define CONFIG_TIMER2_VER_MAJOR          1
#define CONFIG_TIMER2_VER_EXT            0
#define CONFIG_TIMER2_VER_MINOR          3
#define CONFIG_TIMER2_REG_NAME           0

/* TIMER2 Maximum IP Count */
#define CONFIG_TIMER2_MAX_COUNT          2

/* TIMER2 Interrupt Handler */
#define TIMER20_IRQHandler               Interrupt15_Handler
#define TIMER21_IRQHandler               Interrupt16_Handler

/* TIMER2 Interrupt Number */
#define TIMER2_0_IRQ                     TIMER20_IRQn
#define TIMER2_1_IRQ                     TIMER21_IRQn

#endif /* _MODULE_TIMER2 */

#if defined(_MODULE_TIMER3)

#define _TIMER3                          1

/* TIMER3 IP version */
#define CONFIG_TIMER3_VER_VENDOR        'F'
#define CONFIG_TIMER3_VER_MAJOR          1
#define CONFIG_TIMER3_VER_EXT            0
#define CONFIG_TIMER3_VER_MINOR          3
#define CONFIG_TIMER3_REG_NAME           0

/* TIMER3 Maximum IP Count */
#define CONFIG_TIMER3_MAX_COUNT          1

/* TIMER3 Interrupt Handler */
#define TIMER30_IRQHandler               Interrupt13_Handler

/* TIMER3 Interrupt Number */
#define TIMER3_0_IRQ                     TIMER30_IRQn

#endif /* _MODULE_TIMER3 */

#if defined(_MODULE_LCD)

#define _LCD                             1

/* LCD IP version */
#define CONFIG_LCD_VER_VENDOR           'F'
#define CONFIG_LCD_VER_MAJOR             1
#define CONFIG_LCD_VER_EXT               0
#define CONFIG_LCD_VER_MINOR             2
#define CONFIG_LCD_REG_NAME              0

/* LCD Maximum IP Count */
#define CONFIG_LCD_MAX_COUNT             1

#define CONFIG_LCD_MAX_COM_CH_NUM        8
#define CONFIG_LCD_MAX_SEG_CH_NUM        44

#endif /* _LCD */

#if defined(_MODULE_ADC)

#define _ADC                             1

/* ADC IP version */
#define CONFIG_ADC_VER_VENDOR           'F'
#define CONFIG_ADC_VER_MAJOR             1
#define CONFIG_ADC_VER_EXT               0
#define CONFIG_ADC_VER_MINOR             2
#define CONFIG_ADC_REG_NAME              0

/* ADC Maximum IP Count */
#define CONFIG_ADC_MAX_COUNT             1

/* ADC Interrupt Handler */
#define ADC0_IRQHandler                  Interrupt18_Handler

/* ADC Interrupt Number */
#define ADC_0_IRQ                        ADC_IRQn

#endif /* _MODULE_ADC */


#if defined(_MODULE_CFMC)

#define _CFMC                            1

#define CONFIG_CFMC_VER_VENDOR          'F'
#define CONFIG_CFMC_VER_MAJOR            1
#define CONFIG_CFMC_VER_EXT              0
#define CONFIG_CFMC_VER_MINOR            0
#define CONFIG_CFMC_REG_NAME             0

/* FMC Interrupt : None */

#endif /* _MODULE_CFMC */

#if defined(_MODULE_COA)

/* Only WDT and LVR Configuration */
#define _COA                             1

/* COA Configuration */
#define CONFIG_COA_PAGE1_ADDR            0x1FFFF200
#define CONFIG_COA_WDT_ADDR              0x1FFFF20C
#define CONFIG_COA_LVR_ADDR              0x1FFFF210

#define CONFIG_WDT_DEFAULT               0xFFFF96D3

#endif /* _MODULE_COA */


/* Just in case of no register to give debugger connection */
#define CONFIG_EMUL_JTAG_CONNECTION      1
#if defined (EXTRN_FPA_CFMC) || defined (EXTRN_FPA_DFMC)
#undef CONFIG_EMUL_JTAG_CONNECTION
#endif


/* Put handling unsupported modules which are enabled by A31xxxx SVD (abov_module.h) */


#endif /* _CONFIG_A31G11X_H_ */

/** @} */ /* End of group A31G11X */

/** @} */ /* End of group VENDOR ABOV Semiconductor Co., Ltd. */
