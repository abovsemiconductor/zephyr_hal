/**
 *******************************************************************************
 * @file        config_a33g53x.h
 * @author      ABOV R&D Division
 * @brief       A33G53x config file
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


/** @addtogroup A33G53x
  * @{
  */

#ifndef _CONFIG_A33G53X_H_
#define _CONFIG_A33G53X_H_


/* Platform Specific module config */
#define CONFIG_MODULE_FMC_UNIFIED        1

#include "a33g53x.h"
#include "abov_module.h"

/* Mapping ISR function */
/* Adding all of ISR function defines */
/* There is no error when compiling them */

/* SCU IP version */
#define CONFIG_SCU_VER_VENDOR           'V'
#define CONFIG_SCU_VER_MAJOR             3
#define CONFIG_SCU_VER_EXT               0
#define CONFIG_SCU_VER_MINOR             0
#define CONFIG_SCU_REG_NAME              0

#define CONFIG_SCU_CLK_MON_MAX_COUNT     2

/* SCU CLK Interrupt Number */
#define SCUCLK_0_IRQ                     MCKFAIL_IRQn
#define SCUCLK_1_IRQ                     SCLKFAIL_IRQn
#define SCUCLK_2_IRQ                     MXOSCFAIL_IRQn

/* SCU CLK Interrupt Handler */
#if defined (EXTRN_FPA_CFMC) || defined (EXTRN_FPA_DFMC)
#else
#define SCUCLK_SysClkIRQHandler          Interrupt15_Handler
#define SCUCLK_HSEIRQHandler             Interrupt1_Handler
#endif

#if defined(_MODULE_SCU_LVD)

#define _SCU_LVD                         1

/* SCU LVD Interrupt Handler */
#define SCULVD_IRQHandler                Interrupt0_Handler

/* SCU LVD Interrupt Number */
#define SCULVD_0_IRQ                     LVDDETECT_IRQn

#endif /* _MODULE_SCU_LVD */

#if defined(_MODULE_SCU_PWR)

#define _SCU_PWR                         1

#endif /* _MODULE_SCU_PWR */

/* PCU IP version */
#define CONFIG_PCU_VER_VENDOR           'V'
#define CONFIG_PCU_VER_MAJOR             3
#define CONFIG_PCU_VER_EXT               0
#define CONFIG_PCU_VER_MINOR             0
#define CONFIG_PCU_REG_NAME              0
#define CONFIG_PCU_MAX_COUNT             6

/* PCU Interrupt Handler */
#define PCU0_IRQHandler                  Interrupt16_Handler
#define PCU1_IRQHandler                  Interrupt17_Handler
#define PCU2_IRQHandler                  Interrupt18_Handler
#define PCU3_IRQHandler                  Interrupt19_Handler
#define PCU4_IRQHandler                  Interrupt20_Handler
#define PCU5_IRQHandler                  Interrupt21_Handler

/* PCU Interrupt Number */
#define PCU_0_IRQ                        GPIOA_IRQn
#define PCU_1_IRQ                        GPIOB_IRQn
#define PCU_2_IRQ                        GPIOC_IRQn
#define PCU_3_IRQ                        GPIOD_IRQn
#define PCU_4_IRQ                        GPIOE_IRQn
#define PCU_5_IRQ                        GPIOF_IRQn

#if defined(_MODULE_UART)

#define _UART                            1

/* UART IP version */
#define CONFIG_UART_VER_VENDOR          'V'
#define CONFIG_UART_VER_MAJOR            1
#define CONFIG_UART_VER_EXT              0
#define CONFIG_UART_VER_MINOR            4
#define CONFIG_UART_REG_NAME             0

/* UART Maximum IP Count */
#define CONFIG_UART_MAX_COUNT            4

/* UART Interrupt Handler */
#define UART0_IRQHandler                 Interrupt38_Handler
#define UART1_IRQHandler                 Interrupt39_Handler
#define UART2_IRQHandler                 Interrupt40_Handler
#define UART3_IRQHandler                 Interrupt41_Handler

/* UART Interrupt Number */
#define UART_0_IRQ                       UART0_IRQn
#define UART_1_IRQ                       UART1_IRQn
#define UART_2_IRQ                       UART2_IRQn
#define UART_3_IRQ                       UART3_IRQn

#endif /* _MODULE_UART */

#if defined(_MODULE_TIMER1)

#define _TIMER1                          1

/* TIMER1 IP version */
#define CONFIG_TIMER1_VER_VENDOR        'V'
#define CONFIG_TIMER1_VER_MAJOR          1
#define CONFIG_TIMER1_VER_EXT            0
#define CONFIG_TIMER1_VER_MINOR          0
#define CONFIG_TIMER1_REG_NAME           1

/* TIMER1 Maximum IP Count */
#define CONFIG_TIMER1_MAX_COUNT          10

/* TIMER1 MCCR Config */
#define CONFIG_TIMER1_MCCR_NUM                1
#define CONFIG_TIMER1_MCCR_GROUP_COUNT        3
#define CONFIG_TIMER1_MCCR_COUNT_PER_GROUP    4

/* TIMER1N Interrupt Handler */
#define TIMER10_IRQHandler               Interrupt5_Handler
#define TIMER11_IRQHandler               Interrupt6_Handler
#define TIMER12_IRQHandler               Interrupt7_Handler
#define TIMER13_IRQHandler               Interrupt8_Handler
#define TIMER14_IRQHandler               Interrupt9_Handler
#define TIMER15_IRQHandler               Interrupt10_Handler
#define TIMER16_IRQHandler               Interrupt11_Handler
#define TIMER17_IRQHandler               Interrupt12_Handler
#define TIMER18_IRQHandler               Interrupt13_Handler
#define TIMER19_IRQHandler               Interrupt14_Handler

/* TIMER1 Interrupt Number */
#define TIMER1_0_IRQ                     TIMER0_IRQn
#define TIMER1_1_IRQ                     TIMER1_IRQn
#define TIMER1_2_IRQ                     TIMER2_IRQn
#define TIMER1_3_IRQ                     TIMER3_IRQn
#define TIMER1_4_IRQ                     TIMER4_IRQn
#define TIMER1_5_IRQ                     TIMER5_IRQn
#define TIMER1_6_IRQ                     TIMER6_IRQn
#define TIMER1_7_IRQ                     TIMER7_IRQn
#define TIMER1_8_IRQ                     TIMER8_IRQn
#define TIMER1_9_IRQ                     TIMER9_IRQn

#endif /* _TIMER1N */

#if defined(_MODULE_WDT)

#define _WDT                             1

/* WDT IP version */
#define CONFIG_WDT_VER_VENDOR           'V'
#define CONFIG_WDT_VER_MAJOR             1
#define CONFIG_WDT_VER_EXT               0
#define CONFIG_WDT_VER_MINOR             1
#define CONFIG_WDT_REG_NAME              0

/* WDT Maximum IP Count */
#define CONFIG_WDT_MAX_COUNT             1

/* WDT Interrupt Handler */
#define WDT0_IRQHandler                  Interrupt3_Handler

/* WDT Interrupt Number */
#define WDT_0_IRQ                        WDT_IRQn

#endif /* _MODULE_WDT */

#if defined(_MODULE_SPI)

#define _SPI                             1

/* SPI IP version */
#define CONFIG_SPI_VER_VENDOR           'V'
#define CONFIG_SPI_VER_MAJOR             1
#define CONFIG_SPI_VER_EXT               0
#define CONFIG_SPI_VER_MINOR             2
#define CONFIG_SPI_REG_NAME              0

/* SPI Maximum IP Count */
#define CONFIG_SPI_MAX_COUNT             2

/* SPI Config */
#define CONFIG_SPI_TYPE_V0X              1

/* SPI Interrupt Handler */
#define SPI0_IRQHandler                  Interrupt32_Handler
#define SPI1_IRQHandler                  Interrupt33_Handler

/* SPI Interrupt Number */
#define SPI_0_IRQ                        SPI0_IRQn
#define SPI_1_IRQ                        SPI1_IRQn

#endif /* _MODULE_SPI */

#if defined(_MODULE_FRT)

#define _FRT                             1

/* FRT IP version */
#define CONFIG_FRT_VER_VENDOR           'V'
#define CONFIG_FRT_VER_MAJOR             1
#define CONFIG_FRT_VER_EXT               0
#define CONFIG_FRT_VER_MINOR             1
#define CONFIG_FRT_REG_NAME              0

/* FRT Maximum IP Count */
#define CONFIG_FRT_MAX_COUNT             1

/* FRT Interrupt Handler */
#define FRT0_IRQHandler                  Interrupt4_Handler

/* FRT Interrupt Number */
#define FRT_0_IRQ                        FRT_IRQn

#endif /* _MODULE_FRT */

#if defined(_MODULE_I2C)

#define _I2C                             1

/* I2C IP version */
#define CONFIG_I2C_VER_VENDOR           'V'
#define CONFIG_I2C_VER_MAJOR             1
#define CONFIG_I2C_VER_EXT               0
#define CONFIG_I2C_VER_MINOR             0
#define CONFIG_I2C_REG_NAME              2

/* I2C Maximum IP Count */
#define CONFIG_I2C_MAX_COUNT             2

/* I2C Interrupt Handler */
#define I2C0_IRQHandler                  Interrupt36_Handler
#define I2C1_IRQHandler                  Interrupt37_Handler

/* I2C Interrupt Number */
#define I2C_0_IRQ                        I2C0_IRQn
#define I2C_1_IRQ                        I2C1_IRQn

#endif /* _MODULE_I2C */

#if defined(_MODULE_ADC)

#define _ADC                             1

/* ADC IP version */
#define CONFIG_ADC_VER_VENDOR           'F'
#define CONFIG_ADC_VER_MAJOR             1
#define CONFIG_ADC_VER_EXT               0
#define CONFIG_ADC_VER_MINOR             1
#define CONFIG_ADC_REG_NAME              0

/* ADC Maximum IP Count */
#define CONFIG_ADC_MAX_COUNT             1

/* ADC Interrupt Handler */
#define ADC0_IRQHandler                  Interrupt43_Handler

/* ADC Interrupt Number */
#define ADC_0_IRQ                        ADC_IRQn

#endif /* _MODULE_ADC */

#if defined(_MODULE_PWM)

#define _PWM                             1

/* PWM IP version */
#define CONFIG_PWM_VER_VENDOR           'V'
#define CONFIG_PWM_VER_MAJOR             1
#define CONFIG_PWM_VER_EXT               0
#define CONFIG_PWM_VER_MINOR             0
#define CONFIG_PWM_REG_NAME              1

/* PWM Maximum IP Count */
#define CONFIG_PWM_MAX_COUNT             8

/* PWM Interrupt Handler */
#define PWM0_IRQHandler                  Interrupt24_Handler
#define PWM1_IRQHandler                  Interrupt25_Handler
#define PWM2_IRQHandler                  Interrupt26_Handler
#define PWM3_IRQHandler                  Interrupt27_Handler
#define PWM4_IRQHandler                  Interrupt28_Handler
#define PWM5_IRQHandler                  Interrupt29_Handler
#define PWM6_IRQHandler                  Interrupt30_Handler
#define PWM7_IRQHandler                  Interrupt31_Handler

/* PWM Interrupt Number */
#define PWM_0_IRQ                        PWM0_IRQn
#define PWM_1_IRQ                        PWM1_IRQn
#define PWM_2_IRQ                        PWM2_IRQn
#define PWM_3_IRQ                        PWM3_IRQn
#define PWM_4_IRQ                        PWM4_IRQn
#define PWM_5_IRQ                        PWM5_IRQn
#define PWM_6_IRQ                        PWM6_IRQn
#define PWM_7_IRQ                        PWM7_IRQn

#endif /* _MODULE_PWM */

#if defined(_MODULE_CFMC)
#define _CFMC                            1

#define CONFIG_FMC_VER_VENDOR           'V'
#define CONFIG_FMC_VER_MAJOR             1
#define CONFIG_FMC_VER_EXT               1
#define CONFIG_FMC_VER_MINOR             0
#define CONFIG_FMC_REG_NAME              0

/* FMC IRQ */
#define CFMC_IRQ_Handler                 NULL
#define DFMC_IRQ_Handler                 NULL

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


/* Just in case of no register to give debugger connection */
#define CONFIG_EMUL_JTAG_CONNECTION      1
#if defined (EXTRN_FPA_CFMC) || defined (EXTRN_FPA_DFMC)
#undef CONFIG_EMUL_JTAG_CONNECTION
#endif


/* Put handling unsupported modules which are enabled by A33xxxx SVD (abov_module.h) */

#endif /* _CONFIG_A33G53X_H_ */

/** @} */ /* End of group A33G53x */

/** @} */ /* End of group VENDOR ABOV Semiconductor Co., Ltd. */
