/**
 *******************************************************************************
 * @file        config_a31l21x.h
 * @author      ABOV R&D Division
 * @brief       A31L21x config file
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
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


/** @addtogroup A31L21x
  * @{
  */

#ifndef _CONFIG_A31L21X_H_
#define _CONFIG_A31L21X_H_


/* Platform Specific module config */
#define CONFIG_MODULE_FMC_UNIFIED        0
#define CONFIG_MODULE_COA                1

#include "a31l21x.h"
#include "abov_module.h"

/* Mapping ISR function */
/* Adding all of ISR function defines */
/* There is no error when compiling them */

/* One Interrupt number to N-th IP */
#define CONFIG_IRQ_28                    0    /* 0 : Timer6, 1 : RTC */

/* SCU IP version */
#define CONFIG_SCU_VER_VENDOR           'F'
#define CONFIG_SCU_VER_MAJOR             1
#define CONFIG_SCU_VER_EXT               1
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
#define CONFIG_SCU_PWR_BACKUP_DATA_COUNT 32
#define SCUPWR_WkUpIRQHandler            Interrupt17_Handler

#endif /* _MODULE_SCU_PWR */

/* PCU IP version */
#define CONFIG_PCU_VER_VENDOR           'F'
#define CONFIG_PCU_VER_MAJOR             1
#define CONFIG_PCU_VER_EXT               0
#define CONFIG_PCU_VER_MINOR             0
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
#define CONFIG_USART_VER_EXT             3
#define CONFIG_USART_VER_MINOR           0
#define CONFIG_USART_REG_NAME            0

/* USART Maximum IP Count */
#define CONFIG_USART_MAX_COUNT           2

/* USART Interrupt Handler */
#define USART0_IRQHandler                Interrupt11_Handler

/* USART Interrupt Number */
#define USART_0_IRQ                      USART1n_IRQn

/* USART DMA Config */
#define CONFIG_USART_DMA_START_NUM       6
#define DMA_USART_NUM(x,y)               ((CONFIG_USART_DMA_START_NUM + (x == 1 ? ((x+9)*2) : x)) + y)

/* USART Configuration */
#define USART_0_SS_PORT                  PA_BASE
#define USART_0_SS_PIN                   1
#define USART_1_SS_PORT                  PA_BASE
#define USART_1_SS_PIN                   11

#endif /* _MODULE_USART */

#if defined(_MODULE_UART)

#define _UART                            1

/* UART IP version */
#define CONFIG_UART_VER_VENDOR          'V'
#define CONFIG_UART_VER_MAJOR            1
#define CONFIG_UART_VER_EXT              0
#define CONFIG_UART_VER_MINOR            5
#define CONFIG_UART_REG_NAME             1

/* UART Maximum IP Count */
#define CONFIG_UART_MAX_COUNT            1

/* UART Interrupt Handler */
#define UART0_IRQHandler                 Interrupt19_Handler

/* UART Interrupt Number */
#define UART_0_IRQ                       UART0_IRQn

/* UART DMA Config */
#define CONFIG_UART_DMA_START_NUM       12
#define DMA_UART_NUM(x,y)               ((CONFIG_UART_DMA_START_NUM + (x*2)) + y)

#endif /* _MODULE_UART */

#if defined(_MODULE_LPUART)

#define _LPUART                          1

/* LPUART IP version */
#define CONFIG_LPUART_VER_VENDOR        'F'
#define CONFIG_LPUART_VER_MAJOR          1
#define CONFIG_LPUART_VER_EXT            0
#define CONFIG_LPUART_VER_MINOR          0
#define CONFIG_LPUART_REG_NAME           0

/* LPUART Maximum IP Count */
#define CONFIG_LPUART_MAX_COUNT          2

/* LPUART Interrupt Handler */
#define LPUART0_IRQHandler               Interrupt25_Handler

/* LPUART Interrupt Number */
#define LPUART_0_IRQ                     LPUARTn_IRQn
#define LPUART_1_IRQ                     LPUARTn_IRQn

/* LPUART DMA Config */
#define CONFIG_LPUART_DMA_START_NUM      16
#define DMA_LPUART_NUM(x,y)              ((CONFIG_LPUART_DMA_START_NUM + (x == 1 ? ((x+7)*2) : x)) + y)

#endif /* _MODULE_LPUART */

#if defined(_MODULE_WDT)

#define _WDT                             1

/* WDT IP version */
#define CONFIG_WDT_VER_VENDOR           'F'
#define CONFIG_WDT_VER_MAJOR             1
#define CONFIG_WDT_VER_EXT               0
#define CONFIG_WDT_VER_MINOR             1
#define CONFIG_WDT_REG_NAME              0

/* WDT Maximum IP Count */
#define CONFIG_WDT_MAX_COUNT             1

/* WDT Interrupt Handler */
#define WDT0_IRQHandler                  Interrupt2_Handler

/* WDT Interrupt Number */
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
#define CONFIG_I2C_MAX_COUNT             3

/* I2C Interrupt Handler */
#define I2C0_IRQHandler                  Interrupt10_Handler
#define I2C1_IRQHandler                  Interrupt14_Handler
#define I2C2_IRQHandler                  Interrupt29_Handler

/* I2C Interrupt Number */
#define I2C_0_IRQ                        I2C0_IRQn
#define I2C_1_IRQ                        I2C1_IRQn
#define I2C_2_IRQ                        I2C2_IRQn

/* I2C DMA Config */
#define CONFIG_I2C_DMA_START_NUM         8
#define DMA_I2C_NUM(x,y)                 ((CONFIG_I2C_DMA_START_NUM + (x == 2 ? ((x+8)*2) : x*2)) + y)

#endif /* _MODULE_I2C */

#if defined(_MODULE_SPI)

#define _SPI                             1

/* SPI IP version */
#define CONFIG_SPI_VER_VENDOR           'F'
#define CONFIG_SPI_VER_MAJOR             1
#define CONFIG_SPI_VER_EXT               0
#define CONFIG_SPI_VER_MINOR             0
#define CONFIG_SPI_REG_NAME              0

/* SPI Maximum IP Count */
#define CONFIG_SPI_MAX_COUNT             4

/* SPI Interrupt Handler */
#define SPI0_IRQHandler                  Interrupt12_Handler
#define SPI1_IRQHandler                  Interrupt13_Handler

/* SPI Interrupt Number */
#define SPI_0_IRQ                        SPI0_1_IRQn
#define SPI_1_IRQ                        SPI0_1_IRQn
#define SPI_2_IRQ                        SPI2_3_IRQn
#define SPI_3_IRQ                        SPI2_3_IRQn

/* SPI Configuration */
#define SPI_0_SS_PORT                  PB_BASE
#define SPI_0_SS_PIN                   5
#define SPI_1_SS_PORT                  PC_BASE
#define SPI_1_SS_PIN                   7
#define SPI_2_SS_PORT                  PE_BASE
#define SPI_2_SS_PIN                   15
#define SPI_3_SS_PORT                  PE_BASE
#define SPI_3_SS_PIN                   11

/* SPI DMA Config */
#define CONFIG_SPI_DMA_START_NUM         2
#define DMA_SPI_NUM(x,y)                 ((CONFIG_SPI_DMA_START_NUM + ((x > 1) ? ((x+8)*2) : x*2)) + y)

#endif /* _MODULE_SPI */

#if defined(_MODULE_CRC)

#define _CRC                             1

/* CRC IP version */
#define CONFIG_CRC_VER_VENDOR           'F'
#define CONFIG_CRC_VER_MAJOR             1
#define CONFIG_CRC_VER_EXT               0
#define CONFIG_CRC_VER_MINOR             1
#define CONFIG_CRC_REG_NAME              0

/* CRC Maximum IP Count */
#define CONFIG_CRC_MAX_COUNT             1

#endif /* _MODULE_CRC */

#if defined(_MODULE_AES)

#define _AES                             1

/* AES IP version */
#define CONFIG_AES_VER_VENDOR           'F'
#define CONFIG_AES_VER_MAJOR             1
#define CONFIG_AES_VER_EXT               0
#define CONFIG_AES_VER_MINOR             0
#define CONFIG_AES_REG_NAME              0

/* AES Maximum IP Count */
#define CONFIG_AES_MAX_COUNT             1

/* AES Interrupt Handler */
#define AES0_IRQHandler                  Interrupt30_Handler

/* AES Interrupt Number */
#define AES_0_IRQ                        AES_IRQn

/* AES DMA Config */
#define CONFIG_AES_DMA_START_NUM         30
#define DMA_AES_NUM(x,y)                 (CONFIG_AES_DMA_START_NUM + (x*2) + y)

#endif /* _MODULE_AES */

#if defined(_MODULE_TRNG)

#define _TRNG                            1

/* TRNG IP version */
#define CONFIG_TRNG_VER_VENDOR          'F'
#define CONFIG_TRNG_VER_MAJOR            1
#define CONFIG_TRNG_VER_EXT              0
#define CONFIG_TRNG_VER_MINOR            0
#define CONFIG_TRNG_REG_NAME             0

/* TRNG Maximum IP Count */
#define CONFIG_TRNG_MAX_COUNT            1

/* TRNG Interrupt Handler */
#define TRNG0_IRQHandler                 Interrupt31_Handler

/* TRNG Interrupt Number */
#define TRNG_0_IRQ                       RNG_IRQn

#endif /* _MODULE_TRNG */

#if defined(_MODULE_TIMER1)

#define _TIMER1                          1

/* TIMER1 IP version */
#define CONFIG_TIMER1_VER_VENDOR        'F'
#define CONFIG_TIMER1_VER_MAJOR          1
#define CONFIG_TIMER1_VER_EXT            0
#define CONFIG_TIMER1_VER_MINOR          1
#define CONFIG_TIMER1_REG_NAME           1

/* TIMER1 Maximum IP Count */
#define CONFIG_TIMER1_MAX_COUNT          4

/* TIMER1 Interrupt Handler */
#define TIMER10_IRQHandler               Interrupt26_Handler
#define TIMER12_IRQHandler               Interrupt27_Handler

/* TIMER1 Interrupt Number */
#define TIMER1_0_IRQ                     TIMER10_11_IRQn
#define TIMER1_1_IRQ                     TIMER10_11_IRQn
#define TIMER1_2_IRQ                     TIMER12_13_IRQn
#define TIMER1_3_IRQ                     TIMER12_13_IRQn

#endif /* _MODULE_TIMER1 */

#if defined(_MODULE_TIMER4E)

#define _TIMER4E                         1

/* TIMER4E IP version */
#define CONFIG_TIMER4E_VER_VENDOR       'F'
#define CONFIG_TIMER4E_VER_MAJOR         1
#define CONFIG_TIMER4E_VER_EXT           0
#define CONFIG_TIMER4E_VER_MINOR         0
#define CONFIG_TIMER4E_REG_NAME          0

/* TIMER4E Maximum IP Count */
#define CONFIG_TIMER4E_MAX_COUNT         4

/* TIMER4E Interrupt Handler */
#define TIMER4E0_IRQHandler              Interrupt7_Handler
#define TIMER4E1_IRQHandler              Interrupt8_Handler
#define TIMER4E2_IRQHandler              Interrupt9_Handler
#define TIMER4E3_IRQHandler              Interrupt21_Handler

/* TIMER4E Interrupt Number */
#define TIMER4E_0_IRQ                    TIMER40_IRQn
#define TIMER4E_1_IRQ                    TIMER41_IRQn
#define TIMER4E_2_IRQ                    TIMER42_IRQn
#define TIMER4E_3_IRQ                    TIMER43_IRQn

#endif /* _MODULE_TIMER4E */

#if defined(_MODULE_TIMER5)

#define _TIMER5                          1

/* TIMER5 IP version */
#define CONFIG_TIMER5_VER_VENDOR        'F'
#define CONFIG_TIMER5_VER_MAJOR          1
#define CONFIG_TIMER5_VER_EXT            0
#define CONFIG_TIMER5_VER_MINOR          0
#define CONFIG_TIMER5_REG_NAME           0

/* TIMER5 Maximum IP Count */
#define CONFIG_TIMER5_MAX_COUNT          1

/* TIMER5 Interrupt Handler */
#define TIMER50_IRQHandler               Interrupt15_Handler

/* TIMER5 Interrupt Number */
#define TIMER5_0_IRQ                     TIMER50_IRQn

#endif /* _MODULE_TIMER5 */

#if defined(_MODULE_TIMER6)

#define _TIMER6                          1

/* TIMER6 IP version */
#define CONFIG_TIMER6_VER_VENDOR        'F'
#define CONFIG_TIMER6_VER_MAJOR          1
#define CONFIG_TIMER6_VER_EXT            0
#define CONFIG_TIMER6_VER_MINOR          0
#define CONFIG_TIMER6_REG_NAME           0

/* TIMER6 Maximum IP Count */
#define CONFIG_TIMER6_MAX_COUNT          1

/* TIMER6 Interrupt Handler */
#if (CONFIG_IRQ_28 == 0)
#define TIMER60_IRQHandler               Interrupt28_Handler
#endif

/* TIMER6 Interrupt Number */
#define TIMER6_0_IRQ                     RTCC_TIMER60_IRQn

#endif /* _MODULE_TIMER6 */

#if defined(_MODULE_RTC)

#define _RTC                             1

/* RTC IP version */
#define CONFIG_RTC_VER_VENDOR           'F'
#define CONFIG_RTC_VER_MAJOR             1
#define CONFIG_RTC_VER_EXT               0
#define CONFIG_RTC_VER_MINOR             0
#define CONFIG_RTC_REG_NAME              0

/* RTC Maximum IP Count */
#define CONFIG_RTC_MAX_COUNT             1

/* RTC Interrupt Handler */
#if (CONFIG_IRQ_28 == 1)
#define RTC0_IRQHandler                  Interrupt28_Handler
#endif

/* RTC Interrupt Number */
#define RTC_0_IRQ                        RTCC_TIMER60_IRQn

#endif /* _MODULE_RTC */

#if defined(_MODULE_LCD)

#define _LCD                             1

/* LCD IP version */
#define CONFIG_LCD_VER_VENDOR           'F'
#define CONFIG_LCD_VER_MAJOR             1
#define CONFIG_LCD_VER_EXT               0
#define CONFIG_LCD_VER_MINOR             3
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
#define CONFIG_ADC_VER_MAJOR             2
#define CONFIG_ADC_VER_EXT               0
#define CONFIG_ADC_VER_MINOR             0
#define CONFIG_ADC_REG_NAME              0

/* ADC Maximum IP Count */
#define CONFIG_ADC_MAX_COUNT             1

/* ADC Interrupt Handler */
#define ADC0_IRQHandler                  Interrupt18_Handler

/* ADC Interrupt Number */
#define ADC_0_IRQ                        ADC_IRQn

/* ADC DMA Config */
#define CONFIG_ADC_DMA_START_NUM         1
#define DMA_ADC_NUM(x)                   (CONFIG_ADC_DMA_START_NUM)

#endif /* _MODULE_ADC */

#if defined(_MODULE_CMP)

#define _CMP                             1

/* CMP IP version */
#define CONFIG_CMP_VER_VENDOR           'F'
#define CONFIG_CMP_VER_MAJOR             1
#define CONFIG_CMP_VER_EXT               0
#define CONFIG_CMP_VER_MINOR             0
#define CONFIG_CMP_REG_NAME              0

/* CMP Maximum IP Count */
#define CONFIG_CMP_MAX_COUNT             2

/* CMP Interrupt Handler */
#define CMP0_IRQHandler                  Interrupt22_Handler
/* CMP Interrupt Number */
#define CMP_0_IRQ                        CMPn_IRQn

/* CMP Config */
#define CONFIG_CMP_OPS_INTERRUPT         1
#define CONFIG_CMP_NMI_INTERRUPT         1

#endif /* _MODULE_CMP */

#if defined(_MODULE_TEMPSENS)

#define _TEMPSENS                        1

/* TEMPSENS IP version */
#define CONFIG_TEMPSENS_VER_VENDOR      'F'
#define CONFIG_TEMPSENS_VER_MAJOR        1
#define CONFIG_TEMPSENS_VER_EXT          0
#define CONFIG_TEMPSENS_VER_MINOR        0
#define CONFIG_TEMPSENS_REG_NAME         0

/* TEMPSENS Maximum IP Count */
#define CONFIG_TEMPSENS_MAX_COUNT        1

/* TEMPSENS Interrupt Handler */
#define TEMPSENS0_IRQHandler             Interrupt20_Handler

/* TEMPSENS Interrupt Number */
#define TEMPSENS_0_IRQ                   TS_IRQn

#endif /* _MODULE_TEMPSENS */

#if defined(_MODULE_CFMC)

#define _CFMC                            1

#define CONFIG_FMC_VER_VENDOR           'F'
#define CONFIG_FMC_VER_MAJOR             1
#define CONFIG_FMC_VER_EXT               0
#define CONFIG_FMC_VER_MINOR             0
#define CONFIG_FMC_REG_NAME              0

/* FMC Config */
#define CONFIG_FMC_TYPE_F1X              1

/* FMC Interrupt : None */

/* Bank switching */
#define CONFIG_CFMC_BANK_SWITCH          0

/* Passwork Lock */
#define CONFIG_FMC_PASSWD_LOCK           0

/* CRC */
#define CONFIG_FMC_CRC                   0

#endif /* _MODULE_CFMC */

#if defined(_MODULE_DFMC)
#define _DFMC                            1
#endif

#if defined(_MODULE_DMAC)

#define _DMAC                            1

/* DMA Maximum Channel Count */
#define CONFIG_DMA_MAX_COUNT             7

/* DMA IP version */
#define CONFIG_DMA_VER_VENDOR           'F'
#define CONFIG_DMA_VER_MAJOR             1
#define CONFIG_DMA_VER_EXT               0
#define CONFIG_DMA_VER_MINOR             0
#define CONFIG_DMA_REG_NAME              0

/* DMA Interrupt Handler */
#define DMA0_IRQHandler                  Interrupt23_Handler
#define DMA1_IRQHandler                  Interrupt24_Handler

/* DMA Interrupt Number */
#define DMA_0_IRQ                        DMAC0_1_2_3_IRQn
#define DMA_1_IRQ                        DMAC4_5_6_IRQn

#endif /* _MODULE_DMAC */

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


#endif /* _CONFIG_A31L21X_H_ */

/** @} */ /* End of group A31L21X */

/** @} */ /* End of group VENDOR ABOV Semiconductor Co., Ltd. */
