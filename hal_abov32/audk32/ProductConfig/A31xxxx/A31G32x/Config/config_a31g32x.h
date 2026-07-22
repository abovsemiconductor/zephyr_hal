/**
 *******************************************************************************
 * @file        config_a31g32x.h
 * @author      ABOV R&D Division
 * @brief       A31G32x config file
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


/** @addtogroup A31G32x
  * @{
  */

#ifndef _CONFIG_A31G32X_H_
#define _CONFIG_A31G32X_H_


/* Platform Specific module config */
#define CONFIG_MODULE_FMC_UNIFIED        0

#include "a31g32x.h"
#include "abov_module.h"

/* Mapping ISR function */
/* Adding all of ISR function defines */
/* There is no error when compiling them */

/* SCU IP version */
#define CONFIG_SCU_VER_VENDOR           'V'
#define CONFIG_SCU_VER_MAJOR             1
#define CONFIG_SCU_VER_EXT               0
#define CONFIG_SCU_VER_MINOR             3
#define CONFIG_SCU_REG_NAME              0

#define CONFIG_SCU_NMI_MAX_COUNT         3
#define CONFIG_SCU_CLK_MON_MAX_COUNT     3

/* SCU NMI Interrupt Handler */
#if defined (EXTRN_FPA_CFMC) || defined (EXTRN_FPA_DFMC)
#else
#define _NMI                             1
#define NMI_IRQHandler                   NMI_Handler
#endif

/* SCU CLK Interrupt Handler */
#if defined (EXTRN_FPA_CFMC) || defined (EXTRN_FPA_DFMC)
#else
#define SCUCLK_SysClkIRQHandler          Interrupt1_Handler
#endif

/* SCU CLK Interrupt Number */
#define SCUCLK_0_IRQ                     SYSCLKFAIL_IRQn

#if defined(_MODULE_SCU_LVD)

#define _SCU_LVD                         1

/* SCU LVD Interrupt Handler */
#define SCULVD_IRQHandler                Interrupt0_Handler

/* SCU LVD Interrupt Number */
#define SCULVD_0_IRQ                     LVI_IRQn

#endif /* _MODULE_SCU_LVD */

#if defined(_MODULE_SCU_PWR)

#define _SCU_PWR                         1
#define CONFIG_SCU_PWR_BACKUP_DATA_COUNT 4

#endif /* _MODULE_SCU_PWR */

/* PCU IP version */
#define CONFIG_PCU_VER_VENDOR           'V'
#define CONFIG_PCU_VER_MAJOR             1
#define CONFIG_PCU_VER_EXT               0
#define CONFIG_PCU_VER_MINOR             2
#define CONFIG_PCU_REG_NAME              0
#define CONFIG_PCU_MAX_COUNT             4

/* PCU Interrupt Handler */
#define PCU0_IRQHandler                  Interrupt3_Handler
#define PCU1_IRQHandler                  Interrupt4_Handler

/* PCU Interrupt Number */
#define PCU_0_IRQ                        GPIOAB_IRQn
#define PCU_1_IRQ                        GPIOCF_IRQn

#if defined(_MODULE_TIMER1)

#define _TIMER1                          1

/* TIMER1 IP version */
#define CONFIG_TIMER1_VER_VENDOR        'F'
#define CONFIG_TIMER1_VER_MAJOR          1
#define CONFIG_TIMER1_VER_EXT            0
#define CONFIG_TIMER1_VER_MINOR          0
#define CONFIG_TIMER1_REG_NAME           1

/* TIMER1 Maximum IP Count */
#define CONFIG_TIMER1_MAX_COUNT          4

/* TIMER1 MCCR Config */
#define CONFIG_TIMER1_MCCR_NUM                1
#define CONFIG_TIMER1_MCCR_GROUP_COUNT        1
#define CONFIG_TIMER1_MCCR_COUNT_PER_GROUP    0

/* TIMER1 Interrupt Handler */
#define TIMER10_IRQHandler               Interrupt7_Handler
#define TIMER11_IRQHandler               Interrupt8_Handler
#define TIMER12_IRQHandler               Interrupt9_Handler
#define TIMER13_IRQHandler               Interrupt21_Handler

/* TIMER1 Interrupt Number */
#define TIMER1_0_IRQ                     TIMER10_IRQn
#define TIMER1_1_IRQ                     TIMER11_IRQn
#define TIMER1_2_IRQ                     TIMER12_IRQn
#define TIMER1_3_IRQ                     TIMER13_IRQn

#endif /* _MODULE_TIMER1 */

#if defined(_MODULE_TIMER2)

#define _TIMER2                          1

/* TIMER2 IP version */
#define CONFIG_TIMER2_VER_VENDOR        'F'
#define CONFIG_TIMER2_VER_MAJOR          1
#define CONFIG_TIMER2_VER_EXT            0
#define CONFIG_TIMER2_VER_MINOR          2
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
#define CONFIG_TIMER3_VER_MINOR          2
#define CONFIG_TIMER3_REG_NAME           0

/* TIMER3 Maximum IP Count */
#define CONFIG_TIMER3_MAX_COUNT          1

/* TIMER3 Interrupt Handler */
#define TIMER30_IRQHandler               Interrupt13_Handler

/* TIMER3 Interrupt Number */
#define TIMER3_0_IRQ                     TIMER30_IRQn

#endif /* _MODULE_TIMER3 */

#if defined(_MODULE_TIMER4)

#define _TIMER4                          1

/* TIMER4 IP version */
#define CONFIG_TIMER4_VER_VENDOR        'F'
#define CONFIG_TIMER4_VER_MAJOR          1
#define CONFIG_TIMER4_VER_EXT            0
#define CONFIG_TIMER4_VER_MINOR          0
#define CONFIG_TIMER4_REG_NAME           0

/* TIMER4 Maximum IP Count */
#define CONFIG_TIMER4_MAX_COUNT          1

/* TIMER4 Interrupt Handler */
#define TIMER40_IRQHandler               Interrupt22_Handler

/* TIMER4 Interrupt Number */
#define TIMER4_0_IRQ                     TIMER40_IRQn

#endif /* _MODULE_TIMER4 */

#if defined(_MODULE_USART)

#define _USART                           1

/* USART IP version */
#define CONFIG_USART_VER_VENDOR         'F'
#define CONFIG_USART_VER_MAJOR           1
#define CONFIG_USART_VER_EXT             1
#define CONFIG_USART_VER_MINOR           0
#define CONFIG_USART_REG_NAME            0

/* USART Maximum IP Count */
#define CONFIG_USART_MAX_COUNT           4

/* USART Interrupt Handler */
#define USART0_IRQHandler                Interrupt11_Handler
#define USART1_IRQHandler                Interrupt17_Handler
#define USART2_IRQHandler                Interrupt26_Handler
#define USART3_IRQHandler                Interrupt27_Handler

/* USART Interrupt Number */
#define USART_0_IRQ                      USART10_IRQn
#define USART_1_IRQ                      USART11_IRQn
#define USART_2_IRQ                      USART12_IRQn
#define USART_3_IRQ                      USART13_IRQn

/* USART DMA Config */
#define CONFIG_USART_DMA_START_NUM       5
#define DMA_USART_NUM(x,y)               (CONFIG_USART_DMA_START_NUM + (x*2) + y)

#endif /* _MODULE_USART */

#if defined(_MODULE_CRC)

#define _CRC                             1

/* CRC IP version */
#define CONFIG_CRC_VER_VENDOR           'V'
#define CONFIG_CRC_VER_MAJOR             1
#define CONFIG_CRC_VER_EXT               0
#define CONFIG_CRC_VER_MINOR             1
#define CONFIG_CRC_REG_NAME              0

/* CRC Maximum IP Count */
#define CONFIG_CRC_MAX_COUNT             1

/* CRC Interrupt Handler */
#define CRC0_IRQHandler                  Interrupt31_Handler

/* CRC Interrupt Number */
#define CRC_0_IRQ                        CRC_IRQn

/* CRC DMA Config */
#define CONFIG_CRC_DMA_START_NUM         13
#define DMA_CRC_NUM(x)                   (CONFIG_CRC_DMA_START_NUM)

#endif /* _MODULE_CRC */

#if defined(_MODULE_DMAC)

#define _DMAC                            1

/* DMA Maximum Channel Count */
#define CONFIG_DMA_MAX_COUNT             4

/* DMA IP version */
#define CONFIG_DMA_VER_VENDOR           'V'
#define CONFIG_DMA_VER_MAJOR             1
#define CONFIG_DMA_VER_EXT               0
#define CONFIG_DMA_VER_MINOR             0
#define CONFIG_DMA_REG_NAME              1

#endif /* _MODULE_DMAC */

#if defined(_MODULE_WT)

#define _WT                              1

/* WT IP version */
#define CONFIG_WT_VER_VENDOR            'F'
#define CONFIG_WT_VER_MAJOR              1
#define CONFIG_WT_VER_EXT                0
#define CONFIG_WT_VER_MINOR              0
#define CONFIG_WT_REG_NAME               0

/* WT Maximum IP Count */
#define CONFIG_WT_MAX_COUNT              1

/* WT Interrupt Handler */
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
#define CONFIG_WDT_VER_MINOR             0
#define CONFIG_WDT_REG_NAME              0

/* WDT Maximum IP Count */
#define CONFIG_WDT_MAX_COUNT             1

/* WDT Config */
#define CONFIG_WDT_TYPE_V0X              1
#define CONFIG_WDT_REG_PPCLKSR           1

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
#define CONFIG_I2C_VER_EXT               1
#define CONFIG_I2C_VER_MINOR             0
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

#if defined(_MODULE_SPI)

#define _SPI                             1

/* SPI IP version */
#define CONFIG_SPI_VER_VENDOR           'V'
#define CONFIG_SPI_VER_MAJOR             1
#define CONFIG_SPI_VER_EXT               0
#define CONFIG_SPI_VER_MINOR             1
#define CONFIG_SPI_REG_NAME              0

/* SPI Maximum IP Count */
#define CONFIG_SPI_MAX_COUNT             2

/* SPI Config */
#define CONFIG_SPI_TYPE_V0X              1

/* SPI Interrupt Handler */
#define SPI0_IRQHandler                  Interrupt19_Handler
#define SPI1_IRQHandler                  Interrupt20_Handler

/* SPI Interrupt Number */
#define SPI_0_IRQ                        SPI20_IRQn
#define SPI_1_IRQ                        SPI21_IRQn

/* SPI DMA Config */
#define CONFIG_SPI_DMA_START_NUM         1
#define DMA_SPI_NUM(x,y)                 (CONFIG_SPI_DMA_START_NUM + (x*2) + y)

#endif /* _MODULE_SPI */

#if defined(_MODULE_DAC)

#define _DAC                             1

/* DAC IP version */
#define CONFIG_DAC_VER_VENDOR           'V'
#define CONFIG_DAC_VER_MAJOR             2
#define CONFIG_DAC_VER_EXT               0
#define CONFIG_DAC_VER_MINOR             1
#define CONFIG_DAC_REG_NAME              1

/* DAC Maximum IP Count */
#define CONFIG_DAC_MAX_COUNT             1

#endif /* _MODULE_DAC */

#if defined(_MODULE_CFMC)

#define _CFMC                            1

#define CONFIG_CFMC_VER_VENDOR          'V'
#define CONFIG_CFMC_VER_MAJOR            2
#define CONFIG_CFMC_VER_EXT              0
#define CONFIG_CFMC_VER_MINOR            0
#define CONFIG_CFMC_REG_NAME             0

/* FMC Interrupt : None */

#endif /* _MODULE_CFMC */

#if defined(_MODULE_ADC)

#define _ADC                             1

/* ADC IP version */
#define CONFIG_ADC_VER_VENDOR           'V'
#define CONFIG_ADC_VER_MAJOR             1
#define CONFIG_ADC_VER_EXT               0
#define CONFIG_ADC_VER_MINOR             1
#define CONFIG_ADC_REG_NAME              0

/* ADC Maximum IP Count */
#define CONFIG_ADC_MAX_COUNT             1

/* ADC Interrupt Handler */
#define ADC0_IRQHandler                  Interrupt18_Handler

/* ADC Interrupt Number */
#define ADC_0_IRQ                        ADC_IRQn

/* ADC DMA Config */
#define CONFIG_ADC_DMA_START_NUM         14
#define DMA_ADC_NUM(x)                   (CONFIG_ADC_DMA_START_NUM)

#endif /* _MODULE_ADC */

#if defined(_MODULE_CMP)

#define _CMP                             1

/* CMP IP version */
#define CONFIG_CMP_VER_VENDOR           'V'
#define CONFIG_CMP_VER_MAJOR             1
#define CONFIG_CMP_VER_EXT               1
#define CONFIG_CMP_VER_MINOR             0
#define CONFIG_CMP_REG_NAME              0

/* CMP Maximum IP Count */
#define CONFIG_CMP_MAX_COUNT             2

/* CMP Interrupt Handler */
#define CMP0_IRQHandler                  Interrupt29_Handler

/* CMP Interrupt Number */
#define CMP_0_IRQ                        COMP_IRQn

/* CMP Config */
#define CONFIG_CMP_OPS_INTERRUPT         1

#endif /* _MODULE_CMP */

#if defined(_MODULE_TEMPSENS)

#define _TEMPSENS                        1

/* TS IP version */
#define CONFIG_TEMPSENS_VER_VENDOR      'V'
#define CONFIG_TEMPSENS_VER_MAJOR        1
#define CONFIG_TEMPSENS_VER_EXT          0
#define CONFIG_TEMPSENS_VER_MINOR        0
#define CONFIG_TEMPSENS_REG_NAME         0

/* TS Maximum IP Count */
#define CONFIG_TEMPSENS_MAX_COUNT        1

/* TS Interrupt Handler */
#define TEMPSENS0_IRQHandler             Interrupt28_Handler

/* TS Interrupt Number */
#define TEMPSENS_0_IRQ                   TEMPERATURE_IRQn

#endif /* _MODULE_TEMPSENS */

#if defined(_MODULE_RTC)

#define _RTC                             1

/* RTC IP version */
#define CONFIG_RTC_VER_VENDOR           'V'
#define CONFIG_RTC_VER_MAJOR             1
#define CONFIG_RTC_VER_EXT               0
#define CONFIG_RTC_VER_MINOR             0
#define CONFIG_RTC_REG_NAME              0

/* RTC Maximum IP Count */
#define CONFIG_RTC_MAX_COUNT             1

/* RTC Interrupt Handler */
#define RTC0_IRQHandler                  Interrupt23_Handler

/* RTC Interrupt Number */
#define RTC_0_IRQ                        RTC_IRQn

#endif /* _MODULE_RTC */

#if defined(_MODULE_EBI)

#define _EBI                             1

/* EBI IP version */
#define CONFIG_EBI_VER_VENDOR           'V'
#define CONFIG_EBI_VER_MAJOR             1
#define CONFIG_EBI_VER_EXT               0
#define CONFIG_EBI_VER_MINOR             0
#define CONFIG_EBI_REG_NAME              0

/* EBI Maximum IP Count */
#define CONFIG_EBI_MAX_COUNT             1
#define CONFIG_EBI_CS_MAX_COUNT          4

#define CONFIG_EBI_EXT_MEMORY0_ADDR      (0x60000000UL)
#define CONFIG_EBI_EXT_MEMORY1_ADDR      (0x61000000UL)
#define CONFIG_EBI_EXT_MEMORY2_ADDR      (0x62000000UL)
#define CONFIG_EBI_EXT_MEMORY3_ADDR      (0x63000000UL)
#define EBI_EXT_MEMORY_SIZE              (0x100000UL)

/* EBI Interrupt Handler None */

/* EBI Interrupt Number None */

#endif /* _MODULE_EBI */


/* Just in case of no register to give debugger connection */
#define CONFIG_EMUL_JTAG_CONNECTION      1
#if defined (EXTRN_FPA_CFMC) || defined (EXTRN_FPA_DFMC)
#undef CONFIG_EMUL_JTAG_CONNECTION
#endif


/* Put handling unsupported modules which are enabled by A31xxxx SVD (abov_module.h) */


#endif /* _CONFIG_A31G32X_H_ */

/** @} */ /* End of group A31G32x */

/** @} */ /* End of group VENDOR ABOV Semiconductor Co., Ltd. */
