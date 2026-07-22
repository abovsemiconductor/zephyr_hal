/**
 *******************************************************************************
 * @file        config_a33m11x.h
 * @author      ABOV R&D Division
 * @brief       A33M11x config file
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


/** @addtogroup A33M11X
  * @{
  */

#ifndef _CONFIG_A33M11X_H_
#define _CONFIG_A33M11X_H_


/* Platform Specific module config */
#define CONFIG_MODULE_FMC_UNIFIED        0

#include "a33m11x.h"
#include "abov_module.h"

/* Mapping ISR function */
/* Adding all of ISR function defines */
/* There is no error when compiling them */

/* SCU IP version */
#define CONFIG_SCU_VER_VENDOR           'V'
#define CONFIG_SCU_VER_MAJOR             2
#define CONFIG_SCU_VER_EXT               0
#define CONFIG_SCU_VER_MINOR             1
#define CONFIG_SCU_REG_NAME              0

#define CONFIG_SCU_NMI_MAX_COUNT         6
#define CONFIG_SCU_CLK_MON_MAX_COUNT     2

/* SCU Configuration */
#define CONFIG_SCU_CLK_LSE_NO_FEATURE

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
#define CONFIG_PCU_VER_MINOR             1
#define CONFIG_PCU_REG_NAME              1
#define CONFIG_PCU_MAX_COUNT             6

/* PCU Interrupt Handler */
#define PCU0_IRQHandler                  Interrupt36_Handler
#define PCU1_IRQHandler                  Interrupt37_Handler
#define PCU2_IRQHandler                  Interrupt38_Handler
#define PCU3_IRQHandler                  Interrupt39_Handler
#define PCU5_IRQHandler                  Interrupt41_Handler
#define PCU6_IRQHandler                  Interrupt42_Handler

/* PCU Interrupt Number */
#define PCU_0_IRQ                        GPIOA_IRQn
#define PCU_1_IRQ                        GPIOB_IRQn
#define PCU_2_IRQ                        GPIOC_IRQn
#define PCU_3_IRQ                        GPIOD_IRQn
#define PCU_5_IRQ                        GPIOF_IRQn
#define PCU_6_IRQ                        GPIOG_IRQn

#if defined(_MODULE_TIMER1)

#define _TIMER1                          1

/* TIMER1 IP version */
#define CONFIG_TIMER1_VER_VENDOR        'V'
#define CONFIG_TIMER1_VER_MAJOR          1
#define CONFIG_TIMER1_VER_EXT            2
#define CONFIG_TIMER1_VER_MINOR          0
#define CONFIG_TIMER1_REG_NAME           0

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

/* TIMER1 Config */
#define CONFIG_TIMER1_MCCR_TYPE          1

#endif /* _MODULE_TIMER1 */

#if defined(_MODULE_UART)

#define _UART                            1

/* UART IP version */
#define CONFIG_UART_VER_VENDOR          'V'
#define CONFIG_UART_VER_MAJOR            1
#define CONFIG_UART_VER_EXT              0
#define CONFIG_UART_VER_MINOR            3
#define CONFIG_UART_REG_NAME             1

/* UART Maximum IP Count */
#define CONFIG_UART_MAX_COUNT            4

/* UART Interrupt Handler */
#define UART0_IRQHandler                 Interrupt63_Handler
#define UART1_IRQHandler                 Interrupt64_Handler
#define UART2_IRQHandler                 Interrupt65_Handler
#define UART3_IRQHandler                 Interrupt66_Handler

/* UART Interrupt Number */
#define UART_0_IRQ                       UART0_IRQn
#define UART_1_IRQ                       UART1_IRQn
#define UART_2_IRQ                       UART2_IRQn
#define UART_3_IRQ                       UART3_IRQn

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
#define CONFIG_CRC_VER_MINOR             0
#define CONFIG_CRC_REG_NAME              1

/* CRC Maximum IP Count */
#define CONFIG_CRC_MAX_COUNT             1

/* CRC Config */
#define CONFIG_CRC_INPUT_DATA_4BYTES     1

/* CRC Interrupt Handler */
#define CRC0_IRQHandler                  Interrupt85_Handler

/* CRC Interrupt Number */
#define CRC_0_IRQ                        CRC_IRQn

/* CRC DMA Config */
#define CONFIG_CRC_DMA_START_NUM         15
#define DMA_CRC_NUM(x)                   (CONFIG_CRC_DMA_START_NUM)

#endif /* _MODULE_CRC */

#if defined(_MODULE_DMAC)

#define _DMAC                            1

/* DMA Maximum Channel Count */
#define CONFIG_DMA_MAX_COUNT             8

/* DMA IP version */
#define CONFIG_DMA_VER_VENDOR           'V'
#define CONFIG_DMA_VER_MAJOR             1
#define CONFIG_DMA_VER_EXT               0
#define CONFIG_DMA_VER_MINOR             1
#define CONFIG_DMA_REG_NAME              1

#endif /* _MODULE_DMAC */

#if defined(_MODULE_FRT)

#define _FRT                             1

/* FRT IP version */
#define CONFIG_FRT_VER_VENDOR           'V'
#define CONFIG_FRT_VER_MAJOR             1
#define CONFIG_FRT_VER_EXT               0
#define CONFIG_FRT_VER_MINOR             0
#define CONFIG_FRT_REG_NAME              1

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
#define CONFIG_WDT_REG_NAME              0

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
#define CONFIG_I2C_VER_MINOR             0
#define CONFIG_I2C_REG_NAME              1

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

/* SPI Interrupt Handler */
#define SPI0_IRQHandler                  Interrupt55_Handler
#define SPI1_IRQHandler                  Interrupt56_Handler

/* SPI Interrupt Number */
#define SPI_0_IRQ                        SPI0_IRQn
#define SPI_1_IRQ                        SPI1_IRQn

/* SPI DMA Config */
#define CONFIG_SPI_DMA_START_NUM         9
#define DMA_SPI_NUM(x,y)                 (CONFIG_SPI_DMA_START_NUM + (x*2) + y)

#endif /* _MODULE_SPI */

#if defined(_MODULE_ADC)

#define _ADC                             1

/* ADC IP version */
#define CONFIG_ADC_VER_VENDOR           'V'
#define CONFIG_ADC_VER_MAJOR             1
#define CONFIG_ADC_VER_EXT               1
#define CONFIG_ADC_VER_MINOR             0
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
#define CONFIG_ADC_DMA_START_NUM         13
#define DMA_ADC_NUM(x)                   (CONFIG_ADC_DMA_START_NUM + x)

#endif /* _MODULE_ADC */

#if defined(_MODULE_CFMC)
#define _CFMC                            1

#define CONFIG_FMC_VER_VENDOR           'V'
#define CONFIG_FMC_VER_MAJOR             3
#define CONFIG_FMC_VER_EXT               0
#define CONFIG_FMC_VER_MINOR             0
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

#if defined(_MODULE_MPWM)

#define _MPWM                             1

/* MPWM IP version */
#define CONFIG_MPWM_VER_VENDOR           'V'
#define CONFIG_MPWM_VER_MAJOR             1
#define CONFIG_MPWM_VER_EXT               0
#define CONFIG_MPWM_VER_MINOR             0
#define CONFIG_MPWM_REG_NAME              1

/* MPWM Maximum IP Count */
#define CONFIG_MPWM_MAX_COUNT             2

/* MPWM Interrupt Handler */
#define MPWM0_PROTIRQHandler              Interrupt45_Handler
#define MPWM0_OVIRQHandler                Interrupt46_Handler
#define MPWM0_PWMUIRQHandler              Interrupt47_Handler
#define MPWM0_PVIRQHandler                Interrupt48_Handler
#define MPWM0_PWIRQHandler                Interrupt49_Handler
#define MPWM1_PROTIRQHandler              Interrupt50_Handler
#define MPWM1_OVIRQHandler                Interrupt51_Handler
#define MPWM1_PWMUIRQHandler              Interrupt52_Handler
#define MPWM1_PVIRQHandler                Interrupt53_Handler
#define MPWM1_PWIRQHandler                Interrupt54_Handler

/* MPWM Interrupt Number */
#define MPWM_START_PROT_IRQ               MPWM0PROT_IRQn
#define MPWM_START_OV_IRQ                 MPWM0OVV_IRQn
#define MPWM_START_SIG_U_IRQ              MPWM0U_IRQn
#define MPWM_START_SIG_V_IRQ              MPWM0V_IRQn
#define MPWM_START_SIG_W_IRQ              MPWM0W_IRQn

#endif /* _MODULE_MPWM */

#if defined(_MODULE_QEI)

#define _QEI                              1

/* QEI IP version */
#define CONFIG_QEI_VER_VENDOR            'V'
#define CONFIG_QEI_VER_MAJOR              1
#define CONFIG_QEI_VER_EXT                0
#define CONFIG_QEI_VER_MINOR              0
#define CONFIG_QEI_REG_NAME               0

/* QEI Maximum IP Count */
#define CONFIG_QEI_MAX_COUNT              2

/* QEI Interrupt Handler */
#define QEI0_IRQHandler                   Interrupt31_Handler
#define QEI1_IRQHandler                   Interrupt32_Handler

/* QEI Interrupt Number */
#define QEI_0_IRQ                         QEI0_IRQn
#define QEI_1_IRQ                         QEI1_IRQn

#endif /* _MODULE_QEI */

#if defined(_MODULE_AFE)

#define _AFE                              1

/* AFE IP version */
#define CONFIG_AFE_VER_VENDOR            'V'
#define CONFIG_AFE_VER_MAJOR              1
#define CONFIG_AFE_VER_EXT                0
#define CONFIG_AFE_VER_MINOR              0
#define CONFIG_AFE_REG_NAME               0

/* AFE Maximum IP Count */
#define CONFIG_AFE_MAX_COUNT              4

/* AFE Interrupt Handler */
#define AFE0_IRQHandler                   Interrupt79_Handler
#define AFE1_IRQHandler                   Interrupt80_Handler
#define AFE2_IRQHandler                   Interrupt81_Handler
#define AFE3_IRQHandler                   Interrupt82_Handler

/* AFE Interrupt Number */
#define AFE_0_IRQ                         AFE0_IRQn
#define AFE_1_IRQ                         AFE1_IRQn
#define AFE_2_IRQ                         AFE2_IRQn
#define AFE_3_IRQ                         AFE3_IRQn

#endif /* _MODULE_AFE */


/* Just in case of no register to give debugger connection */
#define CONFIG_EMUL_JTAG_CONNECTION      0
#if defined (EXTRN_FPA_CFMC) || defined (EXTRN_FPA_DFMC)
#undef CONFIG_EMUL_JTAG_CONNECTION
#endif


/* Put handling unsupported modules which are enabled by A33xxxx SVD (abov_module.h) */


#endif /* _CONFIG_A33M11X_H_ */

/** @} */ /* End of group A33M11X */

/** @} */ /* End of group VENDOR ABOV Semiconductor Co., Ltd. */
