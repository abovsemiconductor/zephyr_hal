/**
 *******************************************************************************
 * @file        config_a31c12x.h
 * @author      ABOV R&D Division
 * @brief       A31C12x config file
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


/** @addtogroup A31C12x
  * @{
  */

#ifndef CONFIG_A31C12X_H
#define CONFIG_A31C12X_H


/* Platform Specific module config */
#define CONFIG_MODULE_FMC_UNIFIED        0

#include "a31c12x.h"
#include "abov_module.h"

/* Mapping ISR function */
/* Adding all of ISR function defines */
/* There is no error when compiling them */

/* SCU IP version */
#define CONFIG_SCU_VER_VENDOR           'V'
#define CONFIG_SCU_VER_MAJOR             4
#define CONFIG_SCU_VER_EXT               0
#define CONFIG_SCU_VER_MINOR             0
#define CONFIG_SCU_REG_NAME              0

#define CONFIG_SCU_NMI_MAX_COUNT         6
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
#endif

#define SCUCLK_HSEIRQHandler             Interrupt2_Handler
#define SCUCLK_LSEIRQHandler             Interrupt3_Handler

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
#define CONFIG_PCU_VER_MINOR             3
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

/* UART DMA Config */
#define CONFIG_UART_DMA_START_NUM        1
#define DMA_UART_NUM(x,y)                (CONFIG_UART_DMA_START_NUM + (x*2) + y)

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
#define CONFIG_TIMER1_MAX_COUNT          7

/* TIMER1 MCCR Config */
#define CONFIG_TIMER1_MCCR_NUM                3
#define CONFIG_TIMER1_MCCR_GROUP_COUNT        1
#define CONFIG_TIMER1_MCCR_COUNT_PER_GROUP    5

/* TIMER1 Interrupt Handler */
#define TIMER10_IRQHandler               Interrupt7_Handler
#define TIMER11_IRQHandler               Interrupt8_Handler
#define TIMER12_IRQHandler               Interrupt9_Handler
#define TIMER13_IRQHandler               Interrupt10_Handler
#define TIMER14_IRQHandler               Interrupt14_Handler
#define TIMER15_IRQHandler               Interrupt15_Handler
#define TIMER16_IRQHandler               Interrupt28_Handler

/* TIMER1 Interrupt Number */
#define TIMER1_0_IRQ                     TIMER0_IRQn
#define TIMER1_1_IRQ                     TIMER1_IRQn
#define TIMER1_2_IRQ                     TIMER2_IRQn
#define TIMER1_3_IRQ                     TIMER3_IRQn
#define TIMER1_4_IRQ                     TIMER4_IRQn
#define TIMER1_5_IRQ                     TIMER5_IRQn
#define TIMER1_6_IRQ                     TIMER6_IRQn

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

/* ADC DMA Config */
#define CONFIG_ADC_DMA_START_NUM         11
#define DMA_ADC_NUM(x)                   (CONFIG_ADC_DMA_START_NUM + x)

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
#define CONFIG_USART_MAX_COUNT           2

/* USART Interrupt Handler */
#define USART0_IRQHandler                Interrupt16_Handler
#define USART1_IRQHandler                Interrupt17_Handler

/* USART Interrupt Number */
#define USART_0_IRQ                      USART10_IRQn
#define USART_1_IRQ                      USART11_IRQn

/* USART DMA Config */
#define CONFIG_USART_DMA_START_NUM       5
#define DMA_USART_NUM(x,y)               (CONFIG_USART_DMA_START_NUM + (x*2) + y)

#endif /* _MODULE_USART */


#if defined(_MODULE_I2C)

#define _I2C                             1

/* I2C IP version */
#define CONFIG_I2C_VER_VENDOR           'V'
#define CONFIG_I2C_VER_MAJOR             1
#define CONFIG_I2C_VER_EXT               0
#define CONFIG_I2C_VER_MINOR             0
#define CONFIG_I2C_REG_NAME              0

/* I2C Maximum IP Count */
#define CONFIG_I2C_MAX_COUNT             2

/* I2C Interrupt Handler */
#define I2C0_IRQHandler                  Interrupt19_Handler
#define I2C1_IRQHandler                  Interrupt26_Handler

/* I2C Interrupt Number */
#define I2C_0_IRQ                        I2C0_IRQn
#define I2C_1_IRQ                        I2C1_IRQn

#endif /* _MODULE_I2C */

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
#define CRC0_IRQHandler                   Interrupt23_Handler

/* CRC Interrupt Number */
#define CRC_0_IRQ                        CRC_IRQn

/* CRC DMA Config */
#define CONFIG_CRC_DMA_START_NUM         12
#define DMA_CRC_NUM(x)                   (CONFIG_CRC_DMA_START_NUM)

#endif /* _MODULE_CRC */

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
#define FRT0_IRQHandler                  Interrupt5_Handler

/* FRT Interrupt Number */
#define FRT_0_IRQ                        FRT_IRQn

#endif /* _MODULE_FRT */

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

#if defined(_MODULE_DMAC)

#define _DMAC                            1

/* DMA Maximum Channel Count */
#define CONFIG_DMA_MAX_COUNT             4

/* DMA IP version */
#define CONFIG_DMA_VER_VENDOR           'V'
#define CONFIG_DMA_VER_MAJOR             1
#define CONFIG_DMA_VER_EXT               0
#define CONFIG_DMA_VER_MINOR             1
#define CONFIG_DMA_REG_NAME              1

#endif /* _MODULE_DMAC */

/* Just in case of no register to give debugger connection */
#define CONFIG_EMUL_JTAG_CONNECTION      0
#if defined (EXTRN_FPA_CFMC) || defined (EXTRN_FPA_DFMC)
#undef CONFIG_EMUL_JTAG_CONNECTION
#endif


/* Put handling unsupported modules which are enabled by A31xxxx SVD (abov_module.h) */


#endif /* CONFIG_A31C12X_H */

/** @} */ /* End of group A31C12x */

/** @} */ /* End of group VENDOR ABOV Semiconductor Co., Ltd. */
