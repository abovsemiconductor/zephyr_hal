/**
 *******************************************************************************
 * @file        config_a31t51x.h
 * @author      ABOV R&D Division
 * @brief       A31T51x config file
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


/** @addtogroup A31T51x
  * @{
  */

#ifndef CONFIG_A31T51X_H
#define CONFIG_A31T51X_H


/* Platform Specific module config */
#define CONFIG_MODULE_FMC_UNIFIED        0

#include "a31t51x.h"
#include "abov_module.h"

/* Mapping ISR function */
/* Adding all of ISR function defines */
/* There is no error when compiling them */

/* One Interrupt number to N-th IP */
#define CONFIG_IRQ_0                    0    /* 0 : LVI, 1 : TOUCH0 */
#define CONFIG_IRQ_1                    0    /* 0 : SYSCLKFAIL, 1 : TOUCH1 */
#define CONFIG_IRQ_2                    0    /* 0 : HSEFAIL, 1 : DFMC */
#define CONFIG_IRQ_3                    0    /* 0 : LSEFAIL, 1 : RTCC */
#define CONFIG_IRQ_5                    0    /* 0 : FRT, 1 : TIMER10 */
#define CONFIG_IRQ_6                    0    /* 0 : CFMC, 1 : TIMER11 */
#define CONFIG_IRQ_23                   0    /* 0 : CRC, 1 : UART2 */
#define CONFIG_IRQ_24                   0    /* 0 : CMP0, 1 : SPI0 */
#define CONFIG_IRQ_30                   0    /* 0 : TIMER8, 1 : UART3 */
#define CONFIG_IRQ_31                   0    /* 0 : TIMER9, 1 : UART4 */

/* SCU IP version */
#define CONFIG_SCU_VER_VENDOR           'V'
#define CONFIG_SCU_VER_MAJOR             4
#define CONFIG_SCU_VER_EXT               0
#define CONFIG_SCU_VER_MINOR             3
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
#if (CONFIG_IRQ_1 == 0)
#define SCUCLK_SysClkIRQHandler          Interrupt1_Handler
#endif
#endif

#if (CONFIG_IRQ_2 == 0)
#define SCUCLK_HSEIRQHandler             Interrupt2_Handler
#endif

#if (CONFIG_IRQ_3 == 0)
#define SCUCLK_LSEIRQHandler             Interrupt3_Handler
#endif

/* SCU CLK Interrupt Number */
#define SCUCLK_0_IRQ                     SYSCLKFAIL_TOUCH1_IRQn
#define SCUCLK_1_IRQ                     HSEFAIL_DFMC_IRQn
#define SCUCLK_2_IRQ                     LSEFAIL_RTCC_IRQn

#if defined(_MODULE_SCU_LVD)

#define _SCU_LVD                         1

/* SCU LVD Interrupt Handler */
#if (CONFIG_IRQ_0 == 0)
#define SCULVD_IRQHandler                Interrupt0_Handler
#endif

/* SCU LVD Interrupt Number */
#define SCULVD_0_IRQ                     LVI_TOUCH0_IRQn

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
#define CONFIG_PCU_MAX_COUNT             5

/* PCU Interrupt Handler */
#define PCU0_IRQHandler                  Interrupt11_Handler
#define PCU1_IRQHandler                  Interrupt12_Handler
#define PCU2_IRQHandler                  Interrupt13_Handler

/* PCU Interrupt Number */
#define PCU_0_IRQ                        GPIOAB_IRQn
#define PCU_1_IRQ                        GPIOCD_IRQn
#define PCU_2_IRQ                        GPIOE_IRQn

#if defined(_MODULE_UART)

#define _UART                            1

/* UART IP version */
#define CONFIG_UART_VER_VENDOR          'V'
#define CONFIG_UART_VER_MAJOR            1
#define CONFIG_UART_VER_EXT              0
#define CONFIG_UART_VER_MINOR            8
#define CONFIG_UART_REG_NAME             0

/* UART Maximum IP Count */
#define CONFIG_UART_MAX_COUNT            5

/* UART Interrupt Handler */
#define UART0_IRQHandler                 Interrupt20_Handler
#define UART1_IRQHandler                 Interrupt21_Handler
#if (CONFIG_IRQ_23 == 1)
#define UART2_IRQHandler                 Interrupt23_Handler
#endif
#if (CONFIG_IRQ_30 == 1)
#define UART3_IRQHandler                 Interrupt30_Handler
#endif
#if (CONFIG_IRQ_31 == 1)
#define UART4_IRQHandler                 Interrupt31_Handler
#endif

/* UART Interrupt Number */
#define UART_0_IRQ                       UART0_IRQn
#define UART_1_IRQ                       UART1_IRQn
#define UART_2_IRQ                       CRC_UART2_IRQn
#define UART_3_IRQ                       TIMER8_UART3_IRQn
#define UART_4_IRQ                       TIMER9_UART4_IRQn

/* UART Config */
#define CONFIG_UART_REG_MCCR             1

/* UART DMA Config */
#define CONFIG_UART_DMA_START_NUM        1
#define DMA_UART_NUM(x,y)                (CONFIG_UART_DMA_START_NUM + ((x>2) ? 18 : (x>1) ? 12 : 0) + (x*2) + y)

#endif /* _MODULE_UART */

#if defined(_MODULE_TIMER1)

#define _TIMER1                          1

/* TIMER1 IP version */
#define CONFIG_TIMER1_VER_VENDOR        'V'
#define CONFIG_TIMER1_VER_MAJOR          1
#define CONFIG_TIMER1_VER_EXT            2
#define CONFIG_TIMER1_VER_MINOR          0
#define CONFIG_TIMER1_REG_NAME           1

/* TIMER1 Maximum IP Count */
#define CONFIG_TIMER1_MAX_COUNT          12

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
#define TIMER17_IRQHandler               Interrupt29_Handler
#if (CONFIG_IRQ_30 == 0)
#define TIMER18_IRQHandler               Interrupt30_Handler
#endif
#if (CONFIG_IRQ_31 == 0)
#define TIMER19_IRQHandler               Interrupt31_Handler
#endif
#if (CONFIG_IRQ_5 == 1)
#define TIMER110_IRQHandler              Interrupt31_Handler
#endif
#if (CONFIG_IRQ_6 == 1)
#define TIMER111_IRQHandler              Interrupt31_Handler
#endif

/* TIMER1 Interrupt Number */
#define TIMER1_0_IRQ                     TIMER0_IRQn
#define TIMER1_1_IRQ                     TIMER1_IRQn
#define TIMER1_2_IRQ                     TIMER2_IRQn
#define TIMER1_3_IRQ                     TIMER3_IRQn
#define TIMER1_4_IRQ                     TIMER4_IRQn
#define TIMER1_5_IRQ                     TIMER5_IRQn
#define TIMER1_6_IRQ                     TIMER6_IRQn
#define TIMER1_7_IRQ                     TIMER7_IRQn
#define TIMER1_8_IRQ                     TIMER8_UART3_IRQn
#define TIMER1_9_IRQ                     TIMER9_UART4_IRQn
#define TIMER1_10_IRQ                    FRT_TIMER10_IRQn
#define TIMER1_11_IRQ                    CFMC_TIMER11_IRQn

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
#define CONFIG_USART_MAX_COUNT           3

/* USART Interrupt Handler */
#define USART0_IRQHandler                Interrupt16_Handler
#define USART1_IRQHandler                Interrupt17_Handler
#define USART2_IRQHandler                Interrupt18_Handler

/* USART Interrupt Number */
#define USART_0_IRQ                      USART10_IRQn
#define USART_1_IRQ                      USART11_IRQn
#define USART_2_IRQ                      USART12_IRQn

/* USART DMA Config */
#define CONFIG_USART_DMA_START_NUM       5
#define DMA_USART_NUM(x,y)               (CONFIG_USART_DMA_START_NUM + (x*2) + y)

#endif /* _MODULE_USART */

#if defined(_MODULE_SPI)

#define _SPI                             1

/* SPI IP version */
#define CONFIG_SPI_VER_VENDOR           'V'
#define CONFIG_SPI_VER_MAJOR             1
#define CONFIG_SPI_VER_EXT               1
#define CONFIG_SPI_VER_MINOR             0
#define CONFIG_SPI_REG_NAME              3

/* SPI Maximum IP Count */
#define CONFIG_SPI_MAX_COUNT             1

/* SPI Config */
#define CONFIG_SPI_TYPE_V0X              1

/* SPI Interrupt Handler */
#if (CONFIG_IRQ_24 == 1)
#define SPI0_IRQHandler                  Interrupt24_Handler
#endif

/* SPI Interrupt Number */
#define SPI_0_IRQ                        CMP0_SPI0_IRQn

/* SPI DMA Config */
#define CONFIG_SPI_DMA_START_NUM         15
#define DMA_SPI_NUM(x,y)                 (CONFIG_SPI_DMA_START_NUM + (x*2) + y)

#endif /* _MODULE_SPI */

#if defined(_MODULE_I2C)

#define _I2C                             1

/* I2C IP version */
#define CONFIG_I2C_VER_VENDOR           'V'
#define CONFIG_I2C_VER_MAJOR             1
#define CONFIG_I2C_VER_EXT               0
#define CONFIG_I2C_VER_MINOR             0
#define CONFIG_I2C_REG_NAME              0

/* I2C Maximum IP Count */
#define CONFIG_I2C_MAX_COUNT             3

/* I2C Interrupt Handler */
#define I2C0_IRQHandler                  Interrupt19_Handler
#define I2C1_IRQHandler                  Interrupt26_Handler
#define I2C2_IRQHandler                  Interrupt27_Handler

/* I2C Interrupt Number */
#define I2C_0_IRQ                        I2C0_IRQn
#define I2C_1_IRQ                        I2C1_IRQn
#define I2C_2_IRQ                        I2C2_IRQn

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
#if (CONFIG_IRQ_23 == 0)
#define CRC0_IRQHandler                   Interrupt23_Handler
#endif

/* CRC Interrupt Number */
#define CRC_0_IRQ                        CRC_UART2_IRQn

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
#if (CONFIG_IRQ_5 == 0)
#define FRT0_IRQHandler                  Interrupt5_Handler
#endif

/* FRT Interrupt Number */
#define FRT_0_IRQ                        FRT_TIMER10_IRQn

#endif /* _MODULE_FRT */

#if defined(_MODULE_RTC)

#define _RTC                             1

/* RTC IP version */
#define CONFIG_RTC_VER_VENDOR           'V'
#define CONFIG_RTC_VER_MAJOR             1
#define CONFIG_RTC_VER_EXT               1
#define CONFIG_RTC_VER_MINOR             0
#define CONFIG_RTC_REG_NAME              0

/* RTC Maximum IP Count */
#define CONFIG_RTC_MAX_COUNT             1

/* RTC Interrupt Handler */
#if (CONFIG_IRQ_3 == 1)
#define RTC0_IRQHandler                  Interrupt3_Handler
#endif

/* RTC Interrupt Number */
#define RTC_0_IRQ                        LSEFAIL_RTCC_IRQn

#endif /* _MODULE_RTC */

#if defined(_MODULE_CFMC)
#define _CFMC                            1

#define CONFIG_FMC_VER_VENDOR           'V'
#define CONFIG_FMC_VER_MAJOR             3
#define CONFIG_FMC_VER_EXT               0
#define CONFIG_FMC_VER_MINOR             2
#define CONFIG_FMC_REG_NAME              0

/* FMC IRQ */
#if (CONFIG_IRQ_6 == 0)
#define CFMC_IRQ_Handler                 Interrupt6_Handler
#endif

/* FMC Interrupt Number */
#define CFMC_IRQn                        CFMC_TIMER11_IRQn

/* Bank switching */
#define CONFIG_CFMC_BANK_SWITCH          0

/* Passwork Lock */
#define CONFIG_CFMC_PASSWD_LOCK          1

/* CRC */
#define CONFIG_FMC_CRC                   0

#endif /* _MODULE_CFMC */

#if defined(_MODULE_DFMC)
#define _DFMC                            1
#endif

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

#if defined(_MODULE_CMP)

#define _CMP                              1

/* CMP IP version */
#define CONFIG_CMP_VER_VENDOR            'V'
#define CONFIG_CMP_VER_MAJOR              2
#define CONFIG_CMP_VER_EXT                0
#define CONFIG_CMP_VER_MINOR              2
#define CONFIG_CMP_REG_NAME               0

/* CMP Maximum IP Count */
#define CONFIG_CMP_MAX_COUNT              2

/* CMP Interrupt Handler */
#if (CONFIG_IRQ_24 == 0)
#define CMP0_IRQHandler                  Interrupt24_Handler
#endif
#define CMP1_IRQHandler                  Interrupt25_Handler

/* CMP Interrupt Number */
#define CMP_0_IRQ                        CMP0_SPI0_IRQn
#define CMP_1_IRQ                        CMP1_IRQn

/* CMP Config */
#define CONFIG_CMP_OPS_INTERRUPT          1

#endif /* _MODULE_CMP */

#if defined(_MODULE_DMAC)

#define _DMAC                            1

/* DMA Maximum Channel Count */
#define CONFIG_DMA_MAX_COUNT             16

/* DMA IP version */
#define CONFIG_DMA_VER_VENDOR           'V'
#define CONFIG_DMA_VER_MAJOR             1
#define CONFIG_DMA_VER_EXT               0
#define CONFIG_DMA_VER_MINOR             1
#define CONFIG_DMA_REG_NAME              1

#endif /* _MODULE_DMAC */

#if defined(_MODULE_HSICMU)

#define _HSICMU                          1

/* DMA Maximum Channel Count */
#define CONFIG_HSICMU_MAX_COUNT          1

/* DMA IP version */
#define CONFIG_HSICMU_VER_VENDOR        'V'
#define CONFIG_HSICMU_VER_MAJOR          1
#define CONFIG_HSICMU_VER_EXT            0
#define CONFIG_HSICMU_VER_MINOR          0
#define CONFIG_HSICMU_REG_NAME           0

#endif /* _MODULE_HSICMU */

/* Just in case of no register to give debugger connection */
#define CONFIG_EMUL_JTAG_CONNECTION      0
#if defined (EXTRN_FPA_CFMC) || defined (EXTRN_FPA_DFMC)
#undef CONFIG_EMUL_JTAG_CONNECTION
#endif


/* Put handling unsupported modules which are enabled by A31xxxx SVD (abov_module.h) */


#endif /* CONFIG_A31T51X_H */

/** @} */ /* End of group A31T51x */

/** @} */ /* End of group VENDOR ABOV Semiconductor Co., Ltd. */
