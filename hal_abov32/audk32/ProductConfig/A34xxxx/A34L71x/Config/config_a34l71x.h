/**
 *******************************************************************************
 * @file        config_a34l71x.h
 * @author      ABOV R&D Division
 * @brief       A34L71x config file
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
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


/** @addtogroup A34L71x
  * @{
  */

#ifndef CONFIG_A34L71X_H
#define CONFIG_A34L71X_H


/* Platform Specific module config */
#define CONFIG_MODULE_FMC_UNIFIED        0

#include "a34l71x.h"
#include "abov_module.h"

/* Mapping ISR function */
/* Adding all of ISR function defines */
/* There is no error when compiling them */

/* SCU IP version */
#define CONFIG_SCU_VER_VENDOR           'V'
#define CONFIG_SCU_VER_MAJOR             2
#define CONFIG_SCU_VER_EXT               0
#define CONFIG_SCU_VER_MINOR             5
#define CONFIG_SCU_REG_NAME              0

#define CONFIG_SCU_NMI_MAX_COUNT         8
#define CONFIG_SCU_CLK_MON_MAX_COUNT     3

/* SCU NMI Interrupt Handler */
#if defined (EXTRN_FPA_CFMC) || defined (EXTRN_FPA_DFMC)
#else
#define _NMI                             1
#define CONFIG_NMI_ANY_INTERRUPT         1
#define NMI_IRQHandler                   NMI_Handler
#endif

/* SCU CLK Interrupt Handler */
#if defined (EXTRN_FPA_CFMC) || defined (EXTRN_FPA_DFMC)
#else
#define SCUCLK_SysClkIRQHandler          Interrupt1_Handler
#define SCUCLK_HSEIRQHandler             Interrupt2_Handler
#define SCUCLK_LSEIRQHandler             Interrupt3_Handler
#endif

/* SCU CLK Interrupt Number */
#define SCUCLK_0_IRQ                     SYSCLKFAIL_IRQn
#define SCUCLK_1_IRQ                     HSEFAIL_IRQn
#define SCUCLK_2_IRQ                     LSEFAIL_IRQn

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
#define CONFIG_PCU_VER_MINOR             4
#define CONFIG_PCU_REG_NAME              0

/* PCU Maximum IP Count */
#define CONFIG_PCU_MAX_COUNT             6

/* PCU Interrupt Handler */
#define PCU0_IRQHandler                  Interrupt36_Handler
#define PCU1_IRQHandler                  Interrupt37_Handler
#define PCU2_IRQHandler                  Interrupt38_Handler
#define PCU3_IRQHandler                  Interrupt39_Handler
#define PCU4_IRQHandler                  Interrupt40_Handler
#define PCU5_IRQHandler                  Interrupt41_Handler

/* PCU Interrupt Number */
#define PCU_0_IRQ                        GPIOA_IRQn
#define PCU_1_IRQ                        GPIOB_IRQn
#define PCU_2_IRQ                        GPIOC_IRQn
#define PCU_3_IRQ                        GPIOD_IRQn
#define PCU_4_IRQ                        GPIOE_IRQn
#define PCU_5_IRQ                        GPIOF_IRQn

#if defined(_MODULE_TIMER1)

#define _TIMER1                          1

/* TIMER1 IP version */
#define CONFIG_TIMER1_VER_VENDOR        'V'
#define CONFIG_TIMER1_VER_MAJOR          1
#define CONFIG_TIMER1_VER_EXT            2
#define CONFIG_TIMER1_VER_MINOR          0
#define CONFIG_TIMER1_REG_NAME           1

/* TIMER1 Maximum IP Count */
#define CONFIG_TIMER1_MAX_COUNT          8

/* TIMER1 MCCR Config */
#define CONFIG_TIMER1_MCCR_NUM                3
#define CONFIG_TIMER1_MCCR_GROUP_COUNT        2
#define CONFIG_TIMER1_MCCR_COUNT_PER_GROUP    4

/* TIMER1 Interrupt Handler */
#define TIMER10_IRQHandler               Interrupt15_Handler
#define TIMER11_IRQHandler               Interrupt16_Handler
#define TIMER12_IRQHandler               Interrupt17_Handler
#define TIMER13_IRQHandler               Interrupt18_Handler
#define TIMER14_IRQHandler               Interrupt19_Handler
#define TIMER15_IRQHandler               Interrupt20_Handler
#define TIMER16_IRQHandler               Interrupt21_Handler
#define TIMER17_IRQHandler               Interrupt22_Handler

/* TIMER1 Interrupt Number */
#define TIMER1_0_IRQ                     TIMER0_IRQn
#define TIMER1_1_IRQ                     TIMER1_IRQn
#define TIMER1_2_IRQ                     TIMER2_IRQn
#define TIMER1_3_IRQ                     TIMER3_IRQn
#define TIMER1_4_IRQ                     TIMER4_IRQn
#define TIMER1_5_IRQ                     TIMER5_IRQn
#define TIMER1_6_IRQ                     TIMER6_IRQn
#define TIMER1_7_IRQ                     TIMER7_IRQn

#endif /* _MODULE_TIMER1 */

#if defined(_MODULE_UART)

#define _UART                            1

/* UART IP version */
#define CONFIG_UART_VER_VENDOR          'V'
#define CONFIG_UART_VER_MAJOR            1
#define CONFIG_UART_VER_EXT              0
#define CONFIG_UART_VER_MINOR            7
#define CONFIG_UART_REG_NAME             0

/* UART Maximum IP Count */
#define CONFIG_UART_MAX_COUNT            1

/* UART Interrupt Handler */
#define UART0_IRQHandler                 Interrupt63_Handler

/* UART Interrupt Number */
#define UART_0_IRQ                       UART_IRQn

/* UART Config */
#define CONFIG_UART_REG_MCCR             1

/* UART DMA Config */
#define CONFIG_UART_DMA_START_NUM        1
#define DMA_UART_NUM(x,y)                (CONFIG_UART_DMA_START_NUM + (x*2) + y)

#endif /* _MODULE_UART */

#if defined(_MODULE_CRC)

#define _CRC                             1

/* CRC IP version */
#define CONFIG_CRC_VER_VENDOR           'V'
#define CONFIG_CRC_VER_MAJOR             2
#define CONFIG_CRC_VER_EXT               0
#define CONFIG_CRC_VER_MINOR             3
#define CONFIG_CRC_REG_NAME              0

/* CRC Maximum IP Count */
#define CONFIG_CRC_MAX_COUNT             1

/* CRC Interrupt Handler */
#define CRC0_IRQHandler                  Interrupt85_Handler

/* CRC Interrupt Number */
#define CRC_0_IRQ                        CRC_IRQn

/* CRC DMA Config */
#define CONFIG_CRC_DMA_START_NUM         17
#define DMA_CRC_NUM(x)                   (CONFIG_CRC_DMA_START_NUM)

#endif /* _MODULE_CRC */

#if defined(_MODULE_DMAC)

#define _DMAC                            1

/* DMA Maximum Channel Count */
#define CONFIG_DMA_MAX_COUNT             7

/* DMA IP version */
#define CONFIG_DMA_VER_VENDOR           'V'
#define CONFIG_DMA_VER_MAJOR             1
#define CONFIG_DMA_VER_EXT               0
#define CONFIG_DMA_VER_MINOR             0
#define CONFIG_DMA_REG_NAME              2

#endif /* _MODULE_DMAC */

#if defined(_MODULE_FRT)

#define _FRT                             1

/* FRT IP version */
#define CONFIG_FRT_VER_VENDOR           'V'
#define CONFIG_FRT_VER_MAJOR             1
#define CONFIG_FRT_VER_EXT               0
#define CONFIG_FRT_VER_MINOR             0
#define CONFIG_FRT_REG_NAME              0

/* FRT Maximum IP Count */
#define CONFIG_FRT_MAX_COUNT             1

/* FRT Interrupt Handler */
#define FRT0_IRQHandler                  Interrupt8_Handler

/* FRT Interrupt Number */
#define FRT_0_IRQ                        FRT_IRQn

#endif /* _MODULE_FRT */

#if defined(_MODULE_WDT)

#define _WDT                             1

/* WDT IP version */
#define CONFIG_WDT_VER_VENDOR           'V'
#define CONFIG_WDT_VER_MAJOR             1
#define CONFIG_WDT_VER_EXT               0
#define CONFIG_WDT_VER_MINOR             0
#define CONFIG_WDT_REG_NAME              1

/* WDT Maximum IP Count */
#define CONFIG_WDT_MAX_COUNT             1

/* WDT Interrupt Handler */
#define WDT0_IRQHandler                  Interrupt6_Handler

/* WDT Interrupt Number */
#define WDT_0_IRQ                        WDT_IRQn

#endif /* _MODULE_WDT */

#if defined(_MODULE_I2C)

#define _I2C                             1

/* I2C IP version */
#define CONFIG_I2C_VER_VENDOR           'V'
#define CONFIG_I2C_VER_MAJOR             1
#define CONFIG_I2C_VER_EXT               0
#define CONFIG_I2C_VER_MINOR             1
#define CONFIG_I2C_REG_NAME              0

/* I2C Maximum IP Count */
#define CONFIG_I2C_MAX_COUNT             2

/* I2C Interrupt Handler */
#define I2C0_IRQHandler                  Interrupt60_Handler
#define I2C1_IRQHandler                  Interrupt61_Handler

/* I2C Interrupt Number */
#define I2C_0_IRQ                        I2C0_IRQn
#define I2C_1_IRQ                        I2C1_IRQn

#endif /* _MODULE_I2C */

#if defined(_MODULE_SPI)

#define _SPI                             1

/* SPI IP version */
#define CONFIG_SPI_VER_VENDOR           'V'
#define CONFIG_SPI_VER_MAJOR             1
#define CONFIG_SPI_VER_EXT               0
#define CONFIG_SPI_VER_MINOR             0
#define CONFIG_SPI_REG_NAME              1

/* SPI Maximum IP Count */
#define CONFIG_SPI_MAX_COUNT             2

/* SPI Config */
#define CONFIG_SPI_TYPE_V0X              1

/* SPI Interrupt Handler */
#define SPI0_IRQHandler                  Interrupt55_Handler
#define SPI1_IRQHandler                  Interrupt56_Handler

/* SPI Interrupt Number */
#define SPI_0_IRQ                        SPI0_IRQn
#define SPI_1_IRQ                        SPI1_IRQn

/* SPI DMA Config */
#define CONFIG_SPI_DMA_START_NUM         11
#define DMA_SPI_NUM(x,y)                 (CONFIG_SPI_DMA_START_NUM + (x*2) + y)

#endif /* _MODULE_SPI */

#if defined(_MODULE_ADC)

#define _ADC                             1

/* ADC IP version */
#define CONFIG_ADC_VER_VENDOR           'V'
#define CONFIG_ADC_VER_MAJOR             1
#define CONFIG_ADC_VER_EXT               0
#define CONFIG_ADC_VER_MINOR             4
#define CONFIG_ADC_REG_NAME              0

/* ADC Maximum IP Count */
#define CONFIG_ADC_MAX_COUNT             2

/* ADC IRQ */
#define ADC0_IRQHandler                  Interrupt74_Handler
#define ADC1_IRQHandler                  Interrupt75_Handler

/* ADC IRQ Number */
#define ADC_0_IRQ                        ADC0_IRQn
#define ADC_1_IRQ                        ADC1_IRQn

/* ADC DMA Config */
#define CONFIG_ADC_DMA_START_NUM         15
#define DMA_ADC_NUM(x)                   (CONFIG_ADC_DMA_START_NUM + x)

#endif /* _MODULE_ADC */

#if defined(_MODULE_CFMC)
#define _CFMC                            1

#define CONFIG_FMC_VER_VENDOR           'V'
#define CONFIG_FMC_VER_MAJOR             3
#define CONFIG_FMC_VER_EXT               0
#define CONFIG_FMC_VER_MINOR             2
#define CONFIG_FMC_REG_NAME              0

/* FMC IRQ */
#define CFMC_IRQ_Handler                 Interrupt11_Handler
#define DFMC_IRQ_Handler                 Interrupt12_Handler

/* Bank switching */
#define CONFIG_CFMC_BANK_SWITCH          0

/* Passwork Lock */
#define CONFIG_FMC_PASSWD_LOCK           1

/* CRC */
#define CONFIG_FMC_CRC                   0

#endif /* _MODULE_CFMC */

#if defined(_MODULE_DFMC)
#define _DFMC                            1
#endif /* _MODULE_DFMC */

#if defined(_MODULE_USART)

#define _USART                           1

/* USART IP version */
#define CONFIG_USART_VER_VENDOR         'F'
#define CONFIG_USART_VER_MAJOR           1
#define CONFIG_USART_VER_EXT             2
#define CONFIG_USART_VER_MINOR           2
#define CONFIG_USART_REG_NAME            0

/* USART Maximum IP Count */
#define CONFIG_USART_MAX_COUNT           2

/* USART Interrupt Handler */
#define USART0_IRQHandler                Interrupt69_Handler
#define USART1_IRQHandler                Interrupt70_Handler

/* USART Interrupt Number */
#define USART_0_IRQ                      USART10_IRQn
#define USART_1_IRQ                      USART11_IRQn

/* USART DMA Config */
#define CONFIG_USART_DMA_START_NUM       3
#define DMA_USART_NUM(x,y)               (CONFIG_USART_DMA_START_NUM + (x*2) + y)

#endif /* _MODULE_USART */

#if defined(_MODULE_LPUART)

#define _LPUART                          1

/* LPUART IP version */
#define CONFIG_LPUART_VER_VENDOR        'F'
#define CONFIG_LPUART_VER_MAJOR          1
#define CONFIG_LPUART_VER_EXT            0
#define CONFIG_LPUART_VER_MINOR          1
#define CONFIG_LPUART_REG_NAME           0

/* LPUART Maximum IP Count */
#define CONFIG_LPUART_MAX_COUNT          2

/* LPUART Interrupt Handler */
#define LPUART0_IRQHandler               Interrupt50_Handler
#define LPUART1_IRQHandler               Interrupt51_Handler

/* LPUART Interrupt Number */
#define LPUART_0_IRQ                     LPUART0_IRQn
#define LPUART_1_IRQ                     LPUART1_IRQn

/* LPUART DMA Config */
#define CONFIG_LPUART_DMA_START_NUM      7
#define DMA_LPUART_NUM(x,y)              (CONFIG_LPUART_DMA_START_NUM + (x*2) + y)

#endif /* _MODULE_LPUART */

#if defined(_MODULE_LCD)

#define _LCD                             1

/* LCD IP version */
#define CONFIG_LCD_VER_VENDOR           'F'
#define CONFIG_LCD_VER_MAJOR             1
#define CONFIG_LCD_VER_EXT               0
#define CONFIG_LCD_VER_MINOR             4
#define CONFIG_LCD_REG_NAME              0

/* LCD Maximum IP Count */
#define CONFIG_LCD_MAX_COUNT             1

#define CONFIG_LCD_MAX_COM_CH_NUM        8
#define CONFIG_LCD_MAX_SEG_CH_NUM        44

#endif /* _LCD */

#if defined(_MODULE_RTC)

#define _RTC                             1

/* RTC IP version */
#define CONFIG_RTC_VER_VENDOR           'V'
#define CONFIG_RTC_VER_MAJOR             1
#define CONFIG_RTC_VER_EXT               0
#define CONFIG_RTC_VER_MINOR             1
#define CONFIG_RTC_REG_NAME              0

/* RTC Maximum IP Count */
#define CONFIG_RTC_MAX_COUNT             1

/* RTC Interrupt Handler */
#define RTC0_IRQHandler                  Interrupt29_Handler

/* RTC Interrupt Number */
#define RTC_0_IRQ                        RTC_IRQn

#endif /* _MODULE_RTC */


#if defined(_MODULE_DAC)

#define _DAC                             1

/* DAC IP version */
#define CONFIG_DAC_VER_VENDOR           'V'
#define CONFIG_DAC_VER_MAJOR             3
#define CONFIG_DAC_VER_EXT               0
#define CONFIG_DAC_VER_MINOR             0
#define CONFIG_DAC_REG_NAME              0

/* DAC Maximum IP Count */
#define CONFIG_DAC_MAX_COUNT             2

/* DAC Interrupt Handler */

/* DAC Interrupt Number */

/* DAC Config */
#define CONFIG_DAC_OPS_INTERRUPT         0
#define CONFIG_DAC_OPS_INTERRUPT_DMA     0

/* DAC DMA Config */

#endif /* _MODULE_DAC */


#if defined(_MODULE_VREFBUF)

#define _VREFBUF                         1

/* VREFBUF IP version */
#define CONFIG_VREFBUF_VER_VENDOR       'V'
#define CONFIG_VREFBUF_VER_MAJOR         1
#define CONFIG_VREFBUF_VER_EXT           0
#define CONFIG_VREFBUF_VER_MINOR         0
#define CONFIG_VREFBUF_REG_NAME          0

/* VREFBUF Maximum IP Count */
#define CONFIG_VREFBUF_MAX_COUNT         1

/* VREFBUF Interrupt Handler */
#define VREFBUF0_IRQHandler               Interrupt30_Handler

/* VREFBUF Interrupt Number */
#define VREFBUF_0_IRQ                     VREFBUF_IRQn

/* VREFBUF Config */

/* VREFBUF DMA Config */

#endif /* _MODULE_DAC */

#if defined(_MODULE_USB)

#define _USB                             1

/* USB IP version */
#define CONFIG_USB_VER_VENDOR           'V'
#define CONFIG_USB_VER_MAJOR             1
#define CONFIG_USB_VER_EXT               0
#define CONFIG_USB_VER_MINOR             0
#define CONFIG_USB_REG_NAME              0

/* USB Maximum IP Count */
#define CONFIG_USB_MAX_COUNT             1

/* USB Interrupt Handler */
#define USB0_IRQHandler                  Interrupt44_Handler

/* USB Interrupt Number */
#define USB_0_IRQ                        USB_IRQn

/* USB Config */

/* USB DMA Config */

#endif /* _MODULE_USB */


/* Just in case of no register to give debugger connection */
#define CONFIG_EMUL_JTAG_CONNECTION      0
#if defined (EXTRN_FPA_CFMC) || defined (EXTRN_FPA_DFMC)
#undef CONFIG_EMUL_JTAG_CONNECTION
#endif


/* Put handling unsupported modules which are enabled by A34xxxx SVD (abov_module.h) */


#endif /* CONFIG_A34L71X_H */

/** @} */ /* End of group A34L71x */

/** @} */ /* End of group VENDOR ABOV Semiconductor Co., Ltd. */
