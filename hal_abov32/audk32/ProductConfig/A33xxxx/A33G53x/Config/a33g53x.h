
/****************************************************************************************************//**
 * @file     A33G53x.h
 *
 * @brief    CMSIS Cortex-M3 Peripheral Access Layer Header File for
 *           A33G53x from ABOV Semiconductor Co., Ltd..
 *
 * @version  V0.1
 * @date     19. June 2024
 *
 * @note     Generated with SVDConv V2.85b 
 *           from CMSIS SVD File 'A33G53x.svd' Version 0.1,
 *
 * @par      ARM Limited (ARM) is supplying this software for use with Cortex-M
 *           processor based microcontroller, but can be equally used for other
 *           suitable processor architectures. This file can be freely distributed.
 *           Modifications to this file shall be clearly marked.
 *           
 *           THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 *           OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 *           MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 *           ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 *           CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER. 
 *
 *******************************************************************************************************/



/** @addtogroup ABOV Semiconductor Co., Ltd.
  * @{
  */

/** @addtogroup A33G53x
  * @{
  */

#ifndef A33G53X_H
#define A33G53X_H

#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum {
/* -------------------  Cortex-M3 Processor Exceptions Numbers  ------------------- */
  Reset_IRQn                    = -15,              /*!<   1  Reset Vector, invoked on Power up and warm reset                 */
  NonMaskableInt_IRQn           = -14,              /*!<   2  Non maskable Interrupt, cannot be stopped or preempted           */
  HardFault_IRQn                = -13,              /*!<   3  Hard Fault, all classes of Fault                                 */
  MemoryManagement_IRQn         = -12,              /*!<   4  Memory Management, MPU mismatch, including Access Violation
                                                         and No Match                                                          */
  BusFault_IRQn                 = -11,              /*!<   5  Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory
                                                         related Fault                                                         */
  UsageFault_IRQn               = -10,              /*!<   6  Usage Fault, i.e. Undef Instruction, Illegal State Transition    */
  SVCall_IRQn                   =  -5,              /*!<  11  System Service Call via SVC instruction                          */
  DebugMonitor_IRQn             =  -4,              /*!<  12  Debug Monitor                                                    */
  PendSV_IRQn                   =  -2,              /*!<  14  Pendable request for system service                              */
  SysTick_IRQn                  =  -1,              /*!<  15  System Tick Timer                                                */
/* ---------------------  A33G53x Specific Interrupt Numbers  --------------------- */
  LVDDETECT_IRQn                =   0,              /*!<   0  LVDDETECT                                                        */
  SCLKFAIL_IRQn                 =   1,              /*!<   1  SCLKFAIL                                                         */
  MXOSCFAIL_IRQn                =   2,              /*!<   2  MXOSCFAIL                                                        */
  WDT_IRQn                      =   3,              /*!<   3  WDT                                                              */
  FRT_IRQn                      =   4,              /*!<   4  FRT                                                              */
  TIMER0_IRQn                   =   5,              /*!<   5  TIMER0                                                           */
  TIMER1_IRQn                   =   6,              /*!<   6  TIMER1                                                           */
  TIMER2_IRQn                   =   7,              /*!<   7  TIMER2                                                           */
  TIMER3_IRQn                   =   8,              /*!<   8  TIMER3                                                           */
  TIMER4_IRQn                   =   9,              /*!<   9  TIMER4                                                           */
  TIMER5_IRQn                   =  10,              /*!<  10  TIMER5                                                           */
  TIMER6_IRQn                   =  11,              /*!<  11  TIMER6                                                           */
  TIMER7_IRQn                   =  12,              /*!<  12  TIMER7                                                           */
  TIMER8_IRQn                   =  13,              /*!<  13  TIMER8                                                           */
  TIMER9_IRQn                   =  14,              /*!<  14  TIMER9                                                           */
  MCKFAIL_IRQn                  =  15,              /*!<  15  MCKFAIL                                                          */
  GPIOA_IRQn                    =  16,              /*!<  16  GPIOA                                                            */
  GPIOB_IRQn                    =  17,              /*!<  17  GPIOB                                                            */
  GPIOC_IRQn                    =  18,              /*!<  18  GPIOC                                                            */
  GPIOD_IRQn                    =  19,              /*!<  19  GPIOD                                                            */
  GPIOE_IRQn                    =  20,              /*!<  20  GPIOE                                                            */
  GPIOF_IRQn                    =  21,              /*!<  21  GPIOF                                                            */
  PWM0_IRQn                     =  24,              /*!<  24  PWM0                                                             */
  PWM1_IRQn                     =  25,              /*!<  25  PWM1                                                             */
  PWM2_IRQn                     =  26,              /*!<  26  PWM2                                                             */
  PWM3_IRQn                     =  27,              /*!<  27  PWM3                                                             */
  PWM4_IRQn                     =  28,              /*!<  28  PWM4                                                             */
  PWM5_IRQn                     =  29,              /*!<  29  PWM5                                                             */
  PWM6_IRQn                     =  30,              /*!<  30  PWM6                                                             */
  PWM7_IRQn                     =  31,              /*!<  31  PWM7                                                             */
  SPI0_IRQn                     =  32,              /*!<  32  SPI0                                                             */
  SPI1_IRQn                     =  33,              /*!<  33  SPI1                                                             */
  I2C0_IRQn                     =  36,              /*!<  36  I2C0                                                             */
  I2C1_IRQn                     =  37,              /*!<  37  I2C1                                                             */
  UART0_IRQn                    =  38,              /*!<  38  UART0                                                            */
  UART1_IRQn                    =  39,              /*!<  39  UART1                                                            */
  UART2_IRQn                    =  40,              /*!<  40  UART2                                                            */
  UART3_IRQn                    =  41,              /*!<  41  UART3                                                            */
  ADC_IRQn                      =  43,              /*!<  43  ADC                                                              */
  FMC_IRQn                      =  44               /*!<  44  FMC                                                              */
} IRQn_Type;


/** @addtogroup Configuration_of_CMSIS
  * @{
  */


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* ----------------Configuration of the Cortex-M3 Processor and Core Peripherals---------------- */
#define __CM3_REV                 0x0100            /*!< Cortex-M3 Core Revision                                               */
#define __MPU_PRESENT                  0            /*!< MPU present or not                                                    */
#define __NVIC_PRIO_BITS               3            /*!< Number of Bits used for Priority Levels                               */
#define __Vendor_SysTickConfig         0            /*!< Set to 1 if different SysTick Config is used                          */
/** @} */ /* End of group Configuration_of_CMSIS */

#include "core_cm3.h"                               /*!< Cortex-M3 processor and core peripherals                              */
#include "system_a33xxxx.h"                         /*!< A33xxxx System                                                        */


/* ================================================================================ */
/* ================       Device Specific Peripheral Section       ================ */
/* ================================================================================ */


/** @addtogroup Device_Peripheral_Registers
  * @{
  */


/* -------------------  Start of section using anonymous unions  ------------------ */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
/* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler type
#endif



/* ================================================================================ */
/* ================                   CHIP_CONFIG                  ================ */
/* ================================================================================ */


/**
  * @brief POWER MANAGEMENT UNIT Configuraiton (CHIP_CONFIG)
  */

typedef struct {                                    /*!< CHIP_CONFIG Structure                                                 */
  __I  uint32_t  VENDDIR;                           /*!< Vendor ID Register                                                    */
  __I  uint32_t  CHIPIDR;                           /*!< Chip ID Register                                                      */
  __I  uint32_t  REVIDR;                            /*!< Revision Number Register                                              */
} CHIP_CONFIG_Type;


/* ================================================================================ */
/* ================                       PMU                      ================ */
/* ================================================================================ */


/**
  * @brief POWER MANAGEMENT UNIT (PMU)
  */

typedef struct {                                    /*!< PMU Structure                                                         */
  __I  uint32_t  IDR;                               /*!< Chip ID Register                                                      */
  __IO uint32_t  MR;                                /*!< PMU Mode Register                                                     */
  __IO uint32_t  CFG;                               /*!< PMU CONFIGURATION REGISTER                                            */
  __I  uint32_t  RESERVED;
  __IO uint32_t  WSER;                              /*!< PMU Wake-up Source Enable Register                                    */
  __I  uint32_t  WSSR;                              /*!< PMU Wak-up Source Status Register                                     */
  __IO uint32_t  RSER;                              /*!< Reset Source Enable Register                                          */
  __IO uint32_t  RSSR;                              /*!< Reset Source Status Register                                          */
  __IO uint32_t  PRER;                              /*!< PMU Peripheral Event Reset Register                                   */
  __IO uint32_t  PER;                               /*!< PMU Perpheral Enable Register                                         */
  __IO uint32_t  PCCR;                              /*!< PMU Peripheral Clock Control Register                                 */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  CCR;                               /*!< PMU Clock Control Register                                            */
  __IO uint32_t  CMR;                               /*!< PMU Clock Monitoring Register                                         */
  __IO uint32_t  MCMR;                              /*!< PMU Main Clock Monitoring Register                                    */
  __IO uint32_t  BCCR;                              /*!< PMU BUS Clock Control Register                                        */
  __IO uint32_t  PCSR;                              /*!< PMU Peripheral Clock Select Register                                  */
  __IO uint32_t  COR;                               /*!< PMU Clock Output Register                                             */
  __I  uint32_t  RESERVED2[2];
  __IO uint32_t  PLLCON;                            /*!< PLL Control Register                                                  */
  __IO uint32_t  LVDCON;                            /*!< LVD Control Register                                                  */
  __IO uint32_t  VDCCON;                            /*!< VDC Control Register                                                  */
  __IO uint32_t  IOSC16TRIM;                        /*!< IOS16 Trimming Register                                               */
  __IO uint32_t  EOSCCON;                           /*!< External Oscillator Control Register                                  */
  __I  uint32_t  RESERVED3[3];
  __IO uint32_t  EXTMODER;                          /*!< External Mode Read Register                                           */
} PMU_Type;


/* ================================================================================ */
/* ================                       PCA                      ================ */
/* ================================================================================ */


/**
  * @brief PORT MAP CONTROLLER (PCA)
  */

typedef struct {                                    /*!< PCA Structure                                                         */
  __IO uint32_t  MR;                                /*!< PORT x Pin MUX Register                                               */
  __IO uint32_t  CR;                                /*!< PORT n Pin Control Register                                           */
  __IO uint32_t  PCR;                               /*!< PORT n Pull-up/Pull-down Resistor Control Register                    */
  __IO uint32_t  DER;                               /*!< PORT n Debounce Enable Register                                       */
  __IO uint32_t  IER;                               /*!< PORT n Interrupt Enable Register                                      */
  __IO uint32_t  ISR;                               /*!< PORT n Interrupt Status Register                                      */
  __IO uint32_t  ICR;                               /*!< PORT n Interrupt Control Register                                     */
  __IO uint32_t  DPR;                               /*!< PORT n Debounce Prescaler Register                                    */
} PCA_Type;


/* ================================================================================ */
/* ================                       PA                       ================ */
/* ================================================================================ */


/**
  * @brief GENERAL PURPOSE I/O (PA)
  */

typedef struct {                                    /*!< PA Structure                                                          */
  __IO uint32_t  ODR;                               /*!< PORT n Output Data Register                                           */
  __I  uint32_t  IDR;                               /*!< PORT n Input Data Register                                            */
  __IO uint32_t  SRR;                               /*!< Port n Set/Reset Register                                             */
} PA_Type;


/* ================================================================================ */
/* ================                       WDT                      ================ */
/* ================================================================================ */


/**
  * @brief WATCH-DOG TIMER (WDT)
  */

typedef struct {                                    /*!< WDT Structure                                                         */
  __IO uint32_t  LR;                                /*!< Watchdog Timer Load Register                                          */
  __I  uint32_t  CVR;                               /*!< WDT Counter Value Register                                            */
  __IO uint32_t  CON;                               /*!< WDT Control Register                                                  */
} WDT_Type;


/* ================================================================================ */
/* ================                       FRT                      ================ */
/* ================================================================================ */


/**
  * @brief Free-Run Timer (FRT)
  */

typedef struct {                                    /*!< FRT Structure                                                         */
  __IO uint32_t  PRD;                               /*!< FRT Period Register                                                   */
  __IO uint32_t  CNT;                               /*!< FRT Count Register                                                    */
  __IO uint32_t  CON;                               /*!< FRT Control Register                                                  */
} FRT_Type;


/* ================================================================================ */
/* ================                       T0                       ================ */
/* ================================================================================ */


/**
  * @brief 16-BIT TIMER (T0)
  */

typedef struct {                                    /*!< T0 Structure                                                          */
  __IO uint32_t  CON;                               /*!< Timer n Control Register                                              */
  __IO uint32_t  CMD;                               /*!< Timer n Command Register                                              */
  __IO uint32_t  GRA;                               /*!< Timer n General Purpose Register A                                    */
  __IO uint32_t  GRB;                               /*!< Timer n General Register B                                            */
  __IO uint32_t  PRS;                               /*!< Timer n Prescaler Register                                            */
  __IO uint32_t  CNT;                               /*!< Timer n Count Register                                                */
} T0_Type;


/* ================================================================================ */
/* ================                      PWM0                      ================ */
/* ================================================================================ */


/**
  * @brief PWM Generator (PWM0)
  */

typedef struct {                                    /*!< PWM0 Structure                                                        */
  __IO uint32_t  CTRL;                              /*!< PWM n Control Register                                                */
  __IO uint32_t  CNT;                               /*!< PWM n Counter Register                                                */
  __IO uint32_t  PER;                               /*!< PWM n Counter Period Register                                         */
  __IO uint32_t  CMP;                               /*!< PWM n Compare Register                                                */
} PWM0_Type;


/* ================================================================================ */
/* ================                     PWMPRS0                    ================ */
/* ================================================================================ */


/**
  * @brief PWMPRS0 (PWMPRS0)
  */

typedef struct {                                    /*!< PWMPRS0 Structure                                                     */
  __IO uint32_t  PRSn;                              /*!< PWM Prescaler Register n                                              */
} PWMPRS0_Type;


/* ================================================================================ */
/* ================                      I2C0                      ================ */
/* ================================================================================ */


/**
  * @brief I2C Interface (I2C0)
  */

typedef struct {                                    /*!< I2C0 Structure                                                        */
  __IO uint32_t  DR;                                /*!< I2C Data Register                                                     */
  __I  uint32_t  RESERVED;
  __IO uint32_t  SR;                                /*!< Status register                                                       */
  __IO uint32_t  SAR;                               /*!< I2C Slave Address Register                                            */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  CR;                                /*!< I2C Control Register                                                  */
  __IO uint32_t  SCLL;                              /*!< I2C SCL LOW duration Register                                         */
  __IO uint32_t  SCLH;                              /*!< I2C SCL HIGH duration Register                                        */
  __IO uint32_t  SDH;                               /*!< I2C SDA Hold Register                                                 */
} I2C0_Type;


/* ================================================================================ */
/* ================                      UART0                     ================ */
/* ================================================================================ */


/**
  * @brief UNIVERSAL ASYNCHRONOUS RECEIVER/TRANSMITTER (UART0)
  */

typedef struct {                                    /*!< UART0 Structure                                                       */
  
  union {
    __IO uint32_t  DLL;                             /*!< UART n Divisor Latch Register LSB                                     */
    __IO uint32_t  THR;                             /*!< Tx Buffer REGISTER                                                    */
    __IO uint32_t  RBR;                             /*!< Rx Buffer REGISTER                                                    */
  };
  
  union {
    __IO uint32_t  IER;                             /*!< UART Interrupt Enable Register                                        */
    __IO uint32_t  DLM;                             /*!< UART n Divisor Latch Register MSB                                     */
  };
  
  union {
    __O  uint32_t  FCR;                             /*!< FIFO Control Register                                                 */
    __I  uint32_t  IIR;                             /*!< UART Interrupt ID Register                                            */
  };
  __IO uint32_t  LCR;                               /*!< UART Line Control Register                                            */
  __I  uint32_t  RESERVED;
  __IO uint32_t  LSR;                               /*!< UART Line Status Register                                             */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  SCR;                               /*!< UART Scratch Register                                                 */
  __I  uint32_t  RESERVED2;
  __IO uint32_t  BFR;                               /*!< UART BaudRate Fraction Counter Register                               */
  __IO uint32_t  DTR;                               /*!< UART Inter-frame Delay Time Register                                  */
} UART0_Type;


/* ================================================================================ */
/* ================                      SPI0                      ================ */
/* ================================================================================ */


/**
  * @brief SERIAL PERIPHERAL INTERFACE (SPI0)
  */

typedef struct {                                    /*!< SPI0 Structure                                                        */
  
  union {
    __IO uint32_t  RDR;                             /*!< SPI n Receive Data Register                                           */
    __IO uint32_t  TDR;                             /*!< SPI n Transmit Data Register                                          */
  };
  __IO uint32_t  CR;                                /*!< SPI n Control Register                                                */
  __IO uint32_t  SR;                                /*!< SPI n Status Register                                                 */
  __IO uint32_t  BR;                                /*!< SPI n Baud Rate Register                                              */
  __IO uint32_t  EN;                                /*!< SPI n Enable register                                                 */
  __IO uint32_t  LR;                                /*!< SPI n Timing register                                                 */
} SPI0_Type;


/* ================================================================================ */
/* ================                       ADC                      ================ */
/* ================================================================================ */


/**
  * @brief 12-BIT A/D CONVERTER (ADC)
  */

typedef struct {                                    /*!< ADC Structure                                                         */
  __IO uint32_t  CR;                                /*!< ADC Control Register                                                  */
  __IO uint32_t  MR;                                /*!< ADC Mode Register                                                     */
  __I  uint32_t  DR;                                /*!< A/D Data Register                                                     */
} ADC_Type;


/* ================================================================================ */
/* ================                       FMC                      ================ */
/* ================================================================================ */


/**
  * @brief INTERNAL FLASH MEMORY (FMC)
  */

typedef struct {                                    /*!< FMC Structure                                                         */
  __IO uint32_t  CFG;                               /*!< Flash Memory Configuration Register                                   */
  __IO uint32_t  CON;                               /*!< Flash Memory Control Register                                         */
  __IO uint32_t  ODR;                               /*!< Flash Memory Output Data Register                                     */
  __I  uint32_t  IDR;                               /*!< Flash Memory Input Data Register                                      */
  __IO uint32_t  AR;                                /*!< Flash Memory Address Register                                         */
  __IO uint32_t  TEST;                              /*!< Flash Memory Extended Mode Control Register                           */
  __IO uint32_t  CRC;                               /*!< Flash Memory CRC Register                                             */
  __IO uint32_t  PROTECT;                           /*!< Flash Memory Protection Register                                      */
  __IO uint32_t  RPROT;                             /*!< Flash Memory Read Protection Register                                 */
  __I  uint32_t  RESERVED[9];
  __IO uint32_t  ECCTLSBER;                         /*!< Flash Memory ECC Test LSB Error Register                              */
  __IO uint32_t  ECCTMSBER;                         /*!< Flash Memory ECC Test MSB Error Register                              */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  BCR;                               /*!< Flash Memory Bank Control Register                                    */
  __IO uint32_t  BSR;                               /*!< Flash Memory Bank Status Register                                     */
  __I  uint32_t  RESERVED2;
  __IO uint32_t  ECCMR;                             /*!< Flash Memory ECC Mode Register                                        */
  __IO uint32_t  CECCEAR;                           /*!< Code Flash Memroy ECC Error Address Register                          */
  __IO uint32_t  CECCELSBDR;                        /*!< Code Flash Memory ECC Error LSB Data Register                         */
  __IO uint32_t  CECCEMSBDR;                        /*!< Code Flash Memory ECC Error MSB Data Register                         */
  __IO uint32_t  DECCEAR;                           /*!< Data Flash Memory ECC Error Address Register                          */
  __IO uint32_t  DECCELSBDR;                        /*!< Data Flash Memory ECC Error LSB Data Register                         */
  __IO uint32_t  DECCEMSBDR;                        /*!< Data Flash Memory ECC Error MSB Data Register                         */
  __I  uint32_t  RESERVED3;
  __IO uint32_t  FMC_IER;                           /*!< Flash Memory Interrupt Enable Register                                */
  __IO uint32_t  FMC_ISR;                           /*!< Flash Memory Interrupt Status Register                                */
} FMC_Type;


/* ================================================================================ */
/* ================                      MEMCR                     ================ */
/* ================================================================================ */


/**
  * @brief Memory Control Register (MEMCR)
  */

typedef struct {                                    /*!< MEMCR Structure                                                       */
  __IO uint32_t  CR;                                /*!< Memory Control Register                                               */
} MEMCR_Type;


/* ================================================================================ */
/* ================                     LEGACY                     ================ */
/* ================================================================================ */


/**
  * @brief PMULEGACY A33G53x Extended Mode Register (LEGACY)
  */

typedef struct {                                    /*!< LEGACY Structure                                                      */
  __IO uint32_t  PMULEGACY;                         /*!< PMULEGACY A33G53x Extended Mode Register                              */
} LEGACY_Type;


/* --------------------  End of section using anonymous unions  ------------------- */
#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
  /* leave anonymous unions enabled */
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler type
#endif



/* ================================================================================ */
/* ================          struct 'PMU' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  PMU_MR  ----------------------------------- */
#define PMU_MR_PMUMODE_Pos                    0                                                       /*!< PMU MR: PMUMODE Position                */
#define PMU_MR_PMUMODE_Msk                    (0x03UL << PMU_MR_PMUMODE_Pos)                          /*!< PMU MR: PMUMODE Mask                    */
#define PMU_MR_VDCLP_Pos                      2                                                       /*!< PMU MR: VDCLP Position                  */
#define PMU_MR_VDCLP_Msk                      (0x01UL << PMU_MR_VDCLP_Pos)                            /*!< PMU MR: VDCLP Mask                      */
#define PMU_MR_ECLKMD_Pos                     3                                                       /*!< PMU MR: ECLKMD Position                 */
#define PMU_MR_ECLKMD_Msk                     (0x01UL << PMU_MR_ECLKMD_Pos)                           /*!< PMU MR: ECLKMD Mask                     */
#define PMU_MR_PREVMODE_Pos                   4                                                       /*!< PMU MR: PREVMODE Position               */
#define PMU_MR_PREVMODE_Msk                   (0x03UL << PMU_MR_PREVMODE_Pos)                         /*!< PMU MR: PREVMODE Mask                   */
#define PMU_MR_PVDCLP_Pos                     6                                                       /*!< PMU MR: PVDCLP Position                 */
#define PMU_MR_PVDCLP_Msk                     (0x01UL << PMU_MR_PVDCLP_Pos)                           /*!< PMU MR: PVDCLP Mask                     */

/* -----------------------------------  PMU_CFG  ---------------------------------- */
#define PMU_CFG_SOFTRST_Pos                   0                                                       /*!< PMU CFG: SOFTRST Position               */
#define PMU_CFG_SOFTRST_Msk                   (0x01UL << PMU_CFG_SOFTRST_Pos)                         /*!< PMU CFG: SOFTRST Mask                   */
#define PMU_CFG_STBYOP_Pos                    4                                                       /*!< PMU CFG: STBYOP Position                */
#define PMU_CFG_STBYOP_Msk                    (0x01UL << PMU_CFG_STBYOP_Pos)                          /*!< PMU CFG: STBYOP Mask                    */

/* ----------------------------------  PMU_WSER  ---------------------------------- */
#define PMU_WSER_LVDE_Pos                     0                                                       /*!< PMU WSER: LVDE Position                 */
#define PMU_WSER_LVDE_Msk                     (0x01UL << PMU_WSER_LVDE_Pos)                           /*!< PMU WSER: LVDE Mask                     */
#define PMU_WSER_MXFAILE_Pos                  1                                                       /*!< PMU WSER: MXFAILE Position              */
#define PMU_WSER_MXFAILE_Msk                  (0x01UL << PMU_WSER_MXFAILE_Pos)                        /*!< PMU WSER: MXFAILE Mask                  */
#define PMU_WSER_SXFAILE_Pos                  2                                                       /*!< PMU WSER: SXFAILE Position              */
#define PMU_WSER_SXFAILE_Msk                  (0x01UL << PMU_WSER_SXFAILE_Pos)                        /*!< PMU WSER: SXFAILE Mask                  */
#define PMU_WSER_WDTE_Pos                     3                                                       /*!< PMU WSER: WDTE Position                 */
#define PMU_WSER_WDTE_Msk                     (0x01UL << PMU_WSER_WDTE_Pos)                           /*!< PMU WSER: WDTE Mask                     */
#define PMU_WSER_FRTE_Pos                     4                                                       /*!< PMU WSER: FRTE Position                 */
#define PMU_WSER_FRTE_Msk                     (0x01UL << PMU_WSER_FRTE_Pos)                           /*!< PMU WSER: FRTE Mask                     */
#define PMU_WSER_GPIOAE_Pos                   5                                                       /*!< PMU WSER: GPIOAE Position               */
#define PMU_WSER_GPIOAE_Msk                   (0x01UL << PMU_WSER_GPIOAE_Pos)                         /*!< PMU WSER: GPIOAE Mask                   */
#define PMU_WSER_GPIOBE_Pos                   6                                                       /*!< PMU WSER: GPIOBE Position               */
#define PMU_WSER_GPIOBE_Msk                   (0x01UL << PMU_WSER_GPIOBE_Pos)                         /*!< PMU WSER: GPIOBE Mask                   */
#define PMU_WSER_GPIOCE_Pos                   7                                                       /*!< PMU WSER: GPIOCE Position               */
#define PMU_WSER_GPIOCE_Msk                   (0x01UL << PMU_WSER_GPIOCE_Pos)                         /*!< PMU WSER: GPIOCE Mask                   */
#define PMU_WSER_GPIODE_Pos                   8                                                       /*!< PMU WSER: GPIODE Position               */
#define PMU_WSER_GPIODE_Msk                   (0x01UL << PMU_WSER_GPIODE_Pos)                         /*!< PMU WSER: GPIODE Mask                   */
#define PMU_WSER_GPIOEE_Pos                   9                                                       /*!< PMU WSER: GPIOEE Position               */
#define PMU_WSER_GPIOEE_Msk                   (0x01UL << PMU_WSER_GPIOEE_Pos)                         /*!< PMU WSER: GPIOEE Mask                   */
#define PMU_WSER_GPIOFE_Pos                   10                                                      /*!< PMU WSER: GPIOFE Position               */
#define PMU_WSER_GPIOFE_Msk                   (0x01UL << PMU_WSER_GPIOFE_Pos)                         /*!< PMU WSER: GPIOFE Mask                   */

/* ----------------------------------  PMU_WSSR  ---------------------------------- */
#define PMU_WSSR_LVD_Pos                      0                                                       /*!< PMU WSSR: LVD Position                  */
#define PMU_WSSR_LVD_Msk                      (0x01UL << PMU_WSSR_LVD_Pos)                            /*!< PMU WSSR: LVD Mask                      */
#define PMU_WSSR_MXFAIL_Pos                   1                                                       /*!< PMU WSSR: MXFAIL Position               */
#define PMU_WSSR_MXFAIL_Msk                   (0x01UL << PMU_WSSR_MXFAIL_Pos)                         /*!< PMU WSSR: MXFAIL Mask                   */
#define PMU_WSSR_SXFAIL_Pos                   2                                                       /*!< PMU WSSR: SXFAIL Position               */
#define PMU_WSSR_SXFAIL_Msk                   (0x01UL << PMU_WSSR_SXFAIL_Pos)                         /*!< PMU WSSR: SXFAIL Mask                   */
#define PMU_WSSR_WDT_Pos                      3                                                       /*!< PMU WSSR: WDT Position                  */
#define PMU_WSSR_WDT_Msk                      (0x01UL << PMU_WSSR_WDT_Pos)                            /*!< PMU WSSR: WDT Mask                      */
#define PMU_WSSR_FRT_Pos                      4                                                       /*!< PMU WSSR: FRT Position                  */
#define PMU_WSSR_FRT_Msk                      (0x01UL << PMU_WSSR_FRT_Pos)                            /*!< PMU WSSR: FRT Mask                      */
#define PMU_WSSR_GPIOA_Pos                    5                                                       /*!< PMU WSSR: GPIOA Position                */
#define PMU_WSSR_GPIOA_Msk                    (0x01UL << PMU_WSSR_GPIOA_Pos)                          /*!< PMU WSSR: GPIOA Mask                    */
#define PMU_WSSR_GPIOB_Pos                    6                                                       /*!< PMU WSSR: GPIOB Position                */
#define PMU_WSSR_GPIOB_Msk                    (0x01UL << PMU_WSSR_GPIOB_Pos)                          /*!< PMU WSSR: GPIOB Mask                    */
#define PMU_WSSR_GPIOC_Pos                    7                                                       /*!< PMU WSSR: GPIOC Position                */
#define PMU_WSSR_GPIOC_Msk                    (0x01UL << PMU_WSSR_GPIOC_Pos)                          /*!< PMU WSSR: GPIOC Mask                    */
#define PMU_WSSR_GPIOD_Pos                    8                                                       /*!< PMU WSSR: GPIOD Position                */
#define PMU_WSSR_GPIOD_Msk                    (0x01UL << PMU_WSSR_GPIOD_Pos)                          /*!< PMU WSSR: GPIOD Mask                    */
#define PMU_WSSR_GPIOE_Pos                    9                                                       /*!< PMU WSSR: GPIOE Position                */
#define PMU_WSSR_GPIOE_Msk                    (0x01UL << PMU_WSSR_GPIOE_Pos)                          /*!< PMU WSSR: GPIOE Mask                    */
#define PMU_WSSR_GPIOF_Pos                    10                                                      /*!< PMU WSSR: GPIOF Position                */
#define PMU_WSSR_GPIOF_Msk                    (0x01UL << PMU_WSSR_GPIOF_Pos)                          /*!< PMU WSSR: GPIOF Mask                    */

/* ----------------------------------  PMU_RSER  ---------------------------------- */
#define PMU_RSER_LVDRSTE_Pos                  0                                                       /*!< PMU RSER: LVDRSTE Position              */
#define PMU_RSER_LVDRSTE_Msk                  (0x01UL << PMU_RSER_LVDRSTE_Pos)                        /*!< PMU RSER: LVDRSTE Mask                  */
#define PMU_RSER_MXFAILRSTE_Pos               1                                                       /*!< PMU RSER: MXFAILRSTE Position           */
#define PMU_RSER_MXFAILRSTE_Msk               (0x01UL << PMU_RSER_MXFAILRSTE_Pos)                     /*!< PMU RSER: MXFAILRSTE Mask               */
#define PMU_RSER_SXFAILRSTE_Pos               2                                                       /*!< PMU RSER: SXFAILRSTE Position           */
#define PMU_RSER_SXFAILRSTE_Msk               (0x01UL << PMU_RSER_SXFAILRSTE_Pos)                     /*!< PMU RSER: SXFAILRSTE Mask               */
#define PMU_RSER_WDTRSTE_Pos                  3                                                       /*!< PMU RSER: WDTRSTE Position              */
#define PMU_RSER_WDTRSTE_Msk                  (0x01UL << PMU_RSER_WDTRSTE_Pos)                        /*!< PMU RSER: WDTRSTE Mask                  */
#define PMU_RSER_SWRSTE_Pos                   4                                                       /*!< PMU RSER: SWRSTE Position               */
#define PMU_RSER_SWRSTE_Msk                   (0x01UL << PMU_RSER_SWRSTE_Pos)                         /*!< PMU RSER: SWRSTE Mask                   */
#define PMU_RSER_SYSRSTE_Pos                  5                                                       /*!< PMU RSER: SYSRSTE Position              */
#define PMU_RSER_SYSRSTE_Msk                  (0x01UL << PMU_RSER_SYSRSTE_Pos)                        /*!< PMU RSER: SYSRSTE Mask                  */
#define PMU_RSER_RSTRSTE_Pos                  6                                                       /*!< PMU RSER: RSTRSTE Position              */
#define PMU_RSER_RSTRSTE_Msk                  (0x01UL << PMU_RSER_RSTRSTE_Pos)                        /*!< PMU RSER: RSTRSTE Mask                  */
#define PMU_RSER_MCLKFAILRSTE_Pos             7                                                       /*!< PMU RSER: MCLKFAILRSTE Position         */
#define PMU_RSER_MCLKFAILRSTE_Msk             (0x01UL << PMU_RSER_MCLKFAILRSTE_Pos)                   /*!< PMU RSER: MCLKFAILRSTE Mask             */

/* ----------------------------------  PMU_RSSR  ---------------------------------- */
#define PMU_RSSR_LVDRST_Pos                   0                                                       /*!< PMU RSSR: LVDRST Position               */
#define PMU_RSSR_LVDRST_Msk                   (0x01UL << PMU_RSSR_LVDRST_Pos)                         /*!< PMU RSSR: LVDRST Mask                   */
#define PMU_RSSR_MXFAILRST_Pos                1                                                       /*!< PMU RSSR: MXFAILRST Position            */
#define PMU_RSSR_MXFAILRST_Msk                (0x01UL << PMU_RSSR_MXFAILRST_Pos)                      /*!< PMU RSSR: MXFAILRST Mask                */
#define PMU_RSSR_SXFAILRST_Pos                2                                                       /*!< PMU RSSR: SXFAILRST Position            */
#define PMU_RSSR_SXFAILRST_Msk                (0x01UL << PMU_RSSR_SXFAILRST_Pos)                      /*!< PMU RSSR: SXFAILRST Mask                */
#define PMU_RSSR_WDTRST_Pos                   3                                                       /*!< PMU RSSR: WDTRST Position               */
#define PMU_RSSR_WDTRST_Msk                   (0x01UL << PMU_RSSR_WDTRST_Pos)                         /*!< PMU RSSR: WDTRST Mask                   */
#define PMU_RSSR_SWRST_Pos                    4                                                       /*!< PMU RSSR: SWRST Position                */
#define PMU_RSSR_SWRST_Msk                    (0x01UL << PMU_RSSR_SWRST_Pos)                          /*!< PMU RSSR: SWRST Mask                    */
#define PMU_RSSR_SYSRST_Pos                   5                                                       /*!< PMU RSSR: SYSRST Position               */
#define PMU_RSSR_SYSRST_Msk                   (0x01UL << PMU_RSSR_SYSRST_Pos)                         /*!< PMU RSSR: SYSRST Mask                   */
#define PMU_RSSR_RSTRST_Pos                   6                                                       /*!< PMU RSSR: RSTRST Position               */
#define PMU_RSSR_RSTRST_Msk                   (0x01UL << PMU_RSSR_RSTRST_Pos)                         /*!< PMU RSSR: RSTRST Mask                   */
#define PMU_RSSR_MCLKFAILRST_Pos              7                                                       /*!< PMU RSSR: MCLKFAILRST Position          */
#define PMU_RSSR_MCLKFAILRST_Msk              (0x01UL << PMU_RSSR_MCLKFAILRST_Pos)                    /*!< PMU RSSR: MCLKFAILRST Mask              */

/* ----------------------------------  PMU_PRER  ---------------------------------- */
#define PMU_PRER_WDT_Pos                      3                                                       /*!< PMU PRER: WDT Position                  */
#define PMU_PRER_WDT_Msk                      (0x01UL << PMU_PRER_WDT_Pos)                            /*!< PMU PRER: WDT Mask                      */
#define PMU_PRER_FRT_Pos                      4                                                       /*!< PMU PRER: FRT Position                  */
#define PMU_PRER_FRT_Msk                      (0x01UL << PMU_PRER_FRT_Pos)                            /*!< PMU PRER: FRT Mask                      */
#define PMU_PRER_TIMER01_Pos                  5                                                       /*!< PMU PRER: TIMER01 Position              */
#define PMU_PRER_TIMER01_Msk                  (0x01UL << PMU_PRER_TIMER01_Pos)                        /*!< PMU PRER: TIMER01 Mask                  */
#define PMU_PRER_TIMER25_Pos                  6                                                       /*!< PMU PRER: TIMER25 Position              */
#define PMU_PRER_TIMER25_Msk                  (0x01UL << PMU_PRER_TIMER25_Pos)                        /*!< PMU PRER: TIMER25 Mask                  */
#define PMU_PRER_TIMER69_Pos                  7                                                       /*!< PMU PRER: TIMER69 Position              */
#define PMU_PRER_TIMER69_Msk                  (0x01UL << PMU_PRER_TIMER69_Pos)                        /*!< PMU PRER: TIMER69 Mask                  */
#define PMU_PRER_GPIOA_Pos                    8                                                       /*!< PMU PRER: GPIOA Position                */
#define PMU_PRER_GPIOA_Msk                    (0x01UL << PMU_PRER_GPIOA_Pos)                          /*!< PMU PRER: GPIOA Mask                    */
#define PMU_PRER_GPIOB_Pos                    9                                                       /*!< PMU PRER: GPIOB Position                */
#define PMU_PRER_GPIOB_Msk                    (0x01UL << PMU_PRER_GPIOB_Pos)                          /*!< PMU PRER: GPIOB Mask                    */
#define PMU_PRER_GPIOC_Pos                    10                                                      /*!< PMU PRER: GPIOC Position                */
#define PMU_PRER_GPIOC_Msk                    (0x01UL << PMU_PRER_GPIOC_Pos)                          /*!< PMU PRER: GPIOC Mask                    */
#define PMU_PRER_GPIOD_Pos                    11                                                      /*!< PMU PRER: GPIOD Position                */
#define PMU_PRER_GPIOD_Msk                    (0x01UL << PMU_PRER_GPIOD_Pos)                          /*!< PMU PRER: GPIOD Mask                    */
#define PMU_PRER_GPIOE_Pos                    12                                                      /*!< PMU PRER: GPIOE Position                */
#define PMU_PRER_GPIOE_Msk                    (0x01UL << PMU_PRER_GPIOE_Pos)                          /*!< PMU PRER: GPIOE Mask                    */
#define PMU_PRER_GPIOF_Pos                    13                                                      /*!< PMU PRER: GPIOF Position                */
#define PMU_PRER_GPIOF_Msk                    (0x01UL << PMU_PRER_GPIOF_Pos)                          /*!< PMU PRER: GPIOF Mask                    */
#define PMU_PRER_CRC16_Pos                    14                                                      /*!< PMU PRER: CRC16 Position                */
#define PMU_PRER_CRC16_Msk                    (0x01UL << PMU_PRER_CRC16_Pos)                          /*!< PMU PRER: CRC16 Mask                    */
#define PMU_PRER_SPI0_Pos                     16                                                      /*!< PMU PRER: SPI0 Position                 */
#define PMU_PRER_SPI0_Msk                     (0x01UL << PMU_PRER_SPI0_Pos)                           /*!< PMU PRER: SPI0 Mask                     */
#define PMU_PRER_SPI1_Pos                     17                                                      /*!< PMU PRER: SPI1 Position                 */
#define PMU_PRER_SPI1_Msk                     (0x01UL << PMU_PRER_SPI1_Pos)                           /*!< PMU PRER: SPI1 Mask                     */
#define PMU_PRER_I2C0_Pos                     18                                                      /*!< PMU PRER: I2C0 Position                 */
#define PMU_PRER_I2C0_Msk                     (0x01UL << PMU_PRER_I2C0_Pos)                           /*!< PMU PRER: I2C0 Mask                     */
#define PMU_PRER_I2C1_Pos                     19                                                      /*!< PMU PRER: I2C1 Position                 */
#define PMU_PRER_I2C1_Msk                     (0x01UL << PMU_PRER_I2C1_Pos)                           /*!< PMU PRER: I2C1 Mask                     */
#define PMU_PRER_UART0_Pos                    20                                                      /*!< PMU PRER: UART0 Position                */
#define PMU_PRER_UART0_Msk                    (0x01UL << PMU_PRER_UART0_Pos)                          /*!< PMU PRER: UART0 Mask                    */
#define PMU_PRER_UART1_Pos                    21                                                      /*!< PMU PRER: UART1 Position                */
#define PMU_PRER_UART1_Msk                    (0x01UL << PMU_PRER_UART1_Pos)                          /*!< PMU PRER: UART1 Mask                    */
#define PMU_PRER_UART2_Pos                    22                                                      /*!< PMU PRER: UART2 Position                */
#define PMU_PRER_UART2_Msk                    (0x01UL << PMU_PRER_UART2_Pos)                          /*!< PMU PRER: UART2 Mask                    */
#define PMU_PRER_UART3_Pos                    23                                                      /*!< PMU PRER: UART3 Position                */
#define PMU_PRER_UART3_Msk                    (0x01UL << PMU_PRER_UART3_Pos)                          /*!< PMU PRER: UART3 Mask                    */
#define PMU_PRER_PWM03_Pos                    24                                                      /*!< PMU PRER: PWM03 Position                */
#define PMU_PRER_PWM03_Msk                    (0x01UL << PMU_PRER_PWM03_Pos)                          /*!< PMU PRER: PWM03 Mask                    */
#define PMU_PRER_PWM47_Pos                    25                                                      /*!< PMU PRER: PWM47 Position                */
#define PMU_PRER_PWM47_Msk                    (0x01UL << PMU_PRER_PWM47_Pos)                          /*!< PMU PRER: PWM47 Mask                    */
#define PMU_PRER_ADC_Pos                      28                                                      /*!< PMU PRER: ADC Position                  */
#define PMU_PRER_ADC_Msk                      (0x01UL << PMU_PRER_ADC_Pos)                            /*!< PMU PRER: ADC Mask                      */
#define PMU_PRER_PMC_Pos                      29                                                      /*!< PMU PRER: PMC Position                  */
#define PMU_PRER_PMC_Msk                      (0x01UL << PMU_PRER_PMC_Pos)                            /*!< PMU PRER: PMC Mask                      */
#define PMU_PRER_JTAGEN_Pos                   31                                                      /*!< PMU PRER: JTAGEN Position               */
#define PMU_PRER_JTAGEN_Msk                   (0x01UL << PMU_PRER_JTAGEN_Pos)                         /*!< PMU PRER: JTAGEN Mask                   */

/* -----------------------------------  PMU_PER  ---------------------------------- */
#define PMU_PER_WDT_Pos                       3                                                       /*!< PMU PER: WDT Position                   */
#define PMU_PER_WDT_Msk                       (0x01UL << PMU_PER_WDT_Pos)                             /*!< PMU PER: WDT Mask                       */
#define PMU_PER_FRT_Pos                       4                                                       /*!< PMU PER: FRT Position                   */
#define PMU_PER_FRT_Msk                       (0x01UL << PMU_PER_FRT_Pos)                             /*!< PMU PER: FRT Mask                       */
#define PMU_PER_TIMER01_Pos                   5                                                       /*!< PMU PER: TIMER01 Position               */
#define PMU_PER_TIMER01_Msk                   (0x01UL << PMU_PER_TIMER01_Pos)                         /*!< PMU PER: TIMER01 Mask                   */
#define PMU_PER_TIMER25_Pos                   6                                                       /*!< PMU PER: TIMER25 Position               */
#define PMU_PER_TIMER25_Msk                   (0x01UL << PMU_PER_TIMER25_Pos)                         /*!< PMU PER: TIMER25 Mask                   */
#define PMU_PER_TIMER69_Pos                   7                                                       /*!< PMU PER: TIMER69 Position               */
#define PMU_PER_TIMER69_Msk                   (0x01UL << PMU_PER_TIMER69_Pos)                         /*!< PMU PER: TIMER69 Mask                   */
#define PMU_PER_GPIOA_Pos                     8                                                       /*!< PMU PER: GPIOA Position                 */
#define PMU_PER_GPIOA_Msk                     (0x01UL << PMU_PER_GPIOA_Pos)                           /*!< PMU PER: GPIOA Mask                     */
#define PMU_PER_GPIOB_Pos                     9                                                       /*!< PMU PER: GPIOB Position                 */
#define PMU_PER_GPIOB_Msk                     (0x01UL << PMU_PER_GPIOB_Pos)                           /*!< PMU PER: GPIOB Mask                     */
#define PMU_PER_GPIOC_Pos                     10                                                      /*!< PMU PER: GPIOC Position                 */
#define PMU_PER_GPIOC_Msk                     (0x01UL << PMU_PER_GPIOC_Pos)                           /*!< PMU PER: GPIOC Mask                     */
#define PMU_PER_GPIOD_Pos                     11                                                      /*!< PMU PER: GPIOD Position                 */
#define PMU_PER_GPIOD_Msk                     (0x01UL << PMU_PER_GPIOD_Pos)                           /*!< PMU PER: GPIOD Mask                     */
#define PMU_PER_GPIOE_Pos                     12                                                      /*!< PMU PER: GPIOE Position                 */
#define PMU_PER_GPIOE_Msk                     (0x01UL << PMU_PER_GPIOE_Pos)                           /*!< PMU PER: GPIOE Mask                     */
#define PMU_PER_GPIOF_Pos                     13                                                      /*!< PMU PER: GPIOF Position                 */
#define PMU_PER_GPIOF_Msk                     (0x01UL << PMU_PER_GPIOF_Pos)                           /*!< PMU PER: GPIOF Mask                     */
#define PMU_PER_CRC16_Pos                     14                                                      /*!< PMU PER: CRC16 Position                 */
#define PMU_PER_CRC16_Msk                     (0x01UL << PMU_PER_CRC16_Pos)                           /*!< PMU PER: CRC16 Mask                     */
#define PMU_PER_SPI0_Pos                      16                                                      /*!< PMU PER: SPI0 Position                  */
#define PMU_PER_SPI0_Msk                      (0x01UL << PMU_PER_SPI0_Pos)                            /*!< PMU PER: SPI0 Mask                      */
#define PMU_PER_SPI1_Pos                      17                                                      /*!< PMU PER: SPI1 Position                  */
#define PMU_PER_SPI1_Msk                      (0x01UL << PMU_PER_SPI1_Pos)                            /*!< PMU PER: SPI1 Mask                      */
#define PMU_PER_I2C0_Pos                      18                                                      /*!< PMU PER: I2C0 Position                  */
#define PMU_PER_I2C0_Msk                      (0x01UL << PMU_PER_I2C0_Pos)                            /*!< PMU PER: I2C0 Mask                      */
#define PMU_PER_I2C1_Pos                      19                                                      /*!< PMU PER: I2C1 Position                  */
#define PMU_PER_I2C1_Msk                      (0x01UL << PMU_PER_I2C1_Pos)                            /*!< PMU PER: I2C1 Mask                      */
#define PMU_PER_UART0_Pos                     20                                                      /*!< PMU PER: UART0 Position                 */
#define PMU_PER_UART0_Msk                     (0x01UL << PMU_PER_UART0_Pos)                           /*!< PMU PER: UART0 Mask                     */
#define PMU_PER_UART1_Pos                     21                                                      /*!< PMU PER: UART1 Position                 */
#define PMU_PER_UART1_Msk                     (0x01UL << PMU_PER_UART1_Pos)                           /*!< PMU PER: UART1 Mask                     */
#define PMU_PER_UART2_Pos                     22                                                      /*!< PMU PER: UART2 Position                 */
#define PMU_PER_UART2_Msk                     (0x01UL << PMU_PER_UART2_Pos)                           /*!< PMU PER: UART2 Mask                     */
#define PMU_PER_UART3_Pos                     23                                                      /*!< PMU PER: UART3 Position                 */
#define PMU_PER_UART3_Msk                     (0x01UL << PMU_PER_UART3_Pos)                           /*!< PMU PER: UART3 Mask                     */
#define PMU_PER_PWM03_Pos                     24                                                      /*!< PMU PER: PWM03 Position                 */
#define PMU_PER_PWM03_Msk                     (0x01UL << PMU_PER_PWM03_Pos)                           /*!< PMU PER: PWM03 Mask                     */
#define PMU_PER_PWM47_Pos                     25                                                      /*!< PMU PER: PWM47 Position                 */
#define PMU_PER_PWM47_Msk                     (0x01UL << PMU_PER_PWM47_Pos)                           /*!< PMU PER: PWM47 Mask                     */
#define PMU_PER_ADC_Pos                       28                                                      /*!< PMU PER: ADC Position                   */
#define PMU_PER_ADC_Msk                       (0x01UL << PMU_PER_ADC_Pos)                             /*!< PMU PER: ADC Mask                       */
#define PMU_PER_PMC_Pos                       29                                                      /*!< PMU PER: PMC Position                   */
#define PMU_PER_PMC_Msk                       (0x01UL << PMU_PER_PMC_Pos)                             /*!< PMU PER: PMC Mask                       */
#define PMU_PER_JTAGEN_Pos                    31                                                      /*!< PMU PER: JTAGEN Position                */
#define PMU_PER_JTAGEN_Msk                    (0x01UL << PMU_PER_JTAGEN_Pos)                          /*!< PMU PER: JTAGEN Mask                    */

/* ----------------------------------  PMU_PCCR  ---------------------------------- */
#define PMU_PCCR_WDT_Pos                      3                                                       /*!< PMU PCCR: WDT Position                  */
#define PMU_PCCR_WDT_Msk                      (0x01UL << PMU_PCCR_WDT_Pos)                            /*!< PMU PCCR: WDT Mask                      */
#define PMU_PCCR_FRT_Pos                      4                                                       /*!< PMU PCCR: FRT Position                  */
#define PMU_PCCR_FRT_Msk                      (0x01UL << PMU_PCCR_FRT_Pos)                            /*!< PMU PCCR: FRT Mask                      */
#define PMU_PCCR_TIMER01_Pos                  5                                                       /*!< PMU PCCR: TIMER01 Position              */
#define PMU_PCCR_TIMER01_Msk                  (0x01UL << PMU_PCCR_TIMER01_Pos)                        /*!< PMU PCCR: TIMER01 Mask                  */
#define PMU_PCCR_TIMER25_Pos                  6                                                       /*!< PMU PCCR: TIMER25 Position              */
#define PMU_PCCR_TIMER25_Msk                  (0x01UL << PMU_PCCR_TIMER25_Pos)                        /*!< PMU PCCR: TIMER25 Mask                  */
#define PMU_PCCR_TIMER69_Pos                  7                                                       /*!< PMU PCCR: TIMER69 Position              */
#define PMU_PCCR_TIMER69_Msk                  (0x01UL << PMU_PCCR_TIMER69_Pos)                        /*!< PMU PCCR: TIMER69 Mask                  */
#define PMU_PCCR_GPIO_Pos                     8                                                       /*!< PMU PCCR: GPIO Position                 */
#define PMU_PCCR_GPIO_Msk                     (0x01UL << PMU_PCCR_GPIO_Pos)                           /*!< PMU PCCR: GPIO Mask                     */
#define PMU_PCCR_CRC16_Pos                    14                                                      /*!< PMU PCCR: CRC16 Position                */
#define PMU_PCCR_CRC16_Msk                    (0x01UL << PMU_PCCR_CRC16_Pos)                          /*!< PMU PCCR: CRC16 Mask                    */
#define PMU_PCCR_SPI0_Pos                     16                                                      /*!< PMU PCCR: SPI0 Position                 */
#define PMU_PCCR_SPI0_Msk                     (0x01UL << PMU_PCCR_SPI0_Pos)                           /*!< PMU PCCR: SPI0 Mask                     */
#define PMU_PCCR_SPI1_Pos                     17                                                      /*!< PMU PCCR: SPI1 Position                 */
#define PMU_PCCR_SPI1_Msk                     (0x01UL << PMU_PCCR_SPI1_Pos)                           /*!< PMU PCCR: SPI1 Mask                     */
#define PMU_PCCR_I2C0_Pos                     18                                                      /*!< PMU PCCR: I2C0 Position                 */
#define PMU_PCCR_I2C0_Msk                     (0x01UL << PMU_PCCR_I2C0_Pos)                           /*!< PMU PCCR: I2C0 Mask                     */
#define PMU_PCCR_I2C1_Pos                     19                                                      /*!< PMU PCCR: I2C1 Position                 */
#define PMU_PCCR_I2C1_Msk                     (0x01UL << PMU_PCCR_I2C1_Pos)                           /*!< PMU PCCR: I2C1 Mask                     */
#define PMU_PCCR_UART0_Pos                    20                                                      /*!< PMU PCCR: UART0 Position                */
#define PMU_PCCR_UART0_Msk                    (0x01UL << PMU_PCCR_UART0_Pos)                          /*!< PMU PCCR: UART0 Mask                    */
#define PMU_PCCR_UART1_Pos                    21                                                      /*!< PMU PCCR: UART1 Position                */
#define PMU_PCCR_UART1_Msk                    (0x01UL << PMU_PCCR_UART1_Pos)                          /*!< PMU PCCR: UART1 Mask                    */
#define PMU_PCCR_UART2_Pos                    22                                                      /*!< PMU PCCR: UART2 Position                */
#define PMU_PCCR_UART2_Msk                    (0x01UL << PMU_PCCR_UART2_Pos)                          /*!< PMU PCCR: UART2 Mask                    */
#define PMU_PCCR_UART3_Pos                    23                                                      /*!< PMU PCCR: UART3 Position                */
#define PMU_PCCR_UART3_Msk                    (0x01UL << PMU_PCCR_UART3_Pos)                          /*!< PMU PCCR: UART3 Mask                    */
#define PMU_PCCR_PWM03_Pos                    24                                                      /*!< PMU PCCR: PWM03 Position                */
#define PMU_PCCR_PWM03_Msk                    (0x01UL << PMU_PCCR_PWM03_Pos)                          /*!< PMU PCCR: PWM03 Mask                    */
#define PMU_PCCR_PWM47_Pos                    25                                                      /*!< PMU PCCR: PWM47 Position                */
#define PMU_PCCR_PWM47_Msk                    (0x01UL << PMU_PCCR_PWM47_Pos)                          /*!< PMU PCCR: PWM47 Mask                    */
#define PMU_PCCR_ADC_Pos                      28                                                      /*!< PMU PCCR: ADC Position                  */
#define PMU_PCCR_ADC_Msk                      (0x01UL << PMU_PCCR_ADC_Pos)                            /*!< PMU PCCR: ADC Mask                      */

/* -----------------------------------  PMU_CCR  ---------------------------------- */
#define PMU_CCR_MXOSCEN_Pos                   0                                                       /*!< PMU CCR: MXOSCEN Position               */
#define PMU_CCR_MXOSCEN_Msk                   (0x03UL << PMU_CCR_MXOSCEN_Pos)                         /*!< PMU CCR: MXOSCEN Mask                   */
#define PMU_CCR_SXOSCEN_Pos                   2                                                       /*!< PMU CCR: SXOSCEN Position               */
#define PMU_CCR_SXOSCEN_Msk                   (0x03UL << PMU_CCR_SXOSCEN_Pos)                         /*!< PMU CCR: SXOSCEN Mask                   */
#define PMU_CCR_IOSC16EN_Pos                  4                                                       /*!< PMU CCR: IOSC16EN Position              */
#define PMU_CCR_IOSC16EN_Msk                  (0x03UL << PMU_CCR_IOSC16EN_Pos)                        /*!< PMU CCR: IOSC16EN Mask                  */
#define PMU_CCR_ROSCEN_Pos                    6                                                       /*!< PMU CCR: ROSCEN Position                */
#define PMU_CCR_ROSCEN_Msk                    (0x03UL << PMU_CCR_ROSCEN_Pos)                          /*!< PMU CCR: ROSCEN Mask                    */

/* -----------------------------------  PMU_CMR  ---------------------------------- */
#define PMU_CMR_MXOSCSTS_Pos                  0                                                       /*!< PMU CMR: MXOSCSTS Position              */
#define PMU_CMR_MXOSCSTS_Msk                  (0x01UL << PMU_CMR_MXOSCSTS_Pos)                        /*!< PMU CMR: MXOSCSTS Mask                  */
#define PMU_CMR_MXOSCIF_Pos                   6                                                       /*!< PMU CMR: MXOSCIF Position               */
#define PMU_CMR_MXOSCIF_Msk                   (0x01UL << PMU_CMR_MXOSCIF_Pos)                         /*!< PMU CMR: MXOSCIF Mask                   */
#define PMU_CMR_MXOSCMNT_Pos                  8                                                       /*!< PMU CMR: MXOSCMNT Position              */
#define PMU_CMR_MXOSCMNT_Msk                  (0x01UL << PMU_CMR_MXOSCMNT_Pos)                        /*!< PMU CMR: MXOSCMNT Mask                  */
#define PMU_CMR_MXOSCIE_Pos                   14                                                      /*!< PMU CMR: MXOSCIE Position               */
#define PMU_CMR_MXOSCIE_Msk                   (0x01UL << PMU_CMR_MXOSCIE_Pos)                         /*!< PMU CMR: MXOSCIE Mask                   */

/* ----------------------------------  PMU_MCMR  ---------------------------------- */
#define PMU_MCMR_MCKSTS_Pos                   0                                                       /*!< PMU MCMR: MCKSTS Position               */
#define PMU_MCMR_MCKSTS_Msk                   (0x01UL << PMU_MCMR_MCKSTS_Pos)                         /*!< PMU MCMR: MCKSTS Mask                   */
#define PMU_MCMR_MCKIF_Pos                    6                                                       /*!< PMU MCMR: MCKIF Position                */
#define PMU_MCMR_MCKIF_Msk                    (0x01UL << PMU_MCMR_MCKIF_Pos)                          /*!< PMU MCMR: MCKIF Mask                    */
#define PMU_MCMR_MCKMNT_Pos                   8                                                       /*!< PMU MCMR: MCKMNT Position               */
#define PMU_MCMR_MCKMNT_Msk                   (0x01UL << PMU_MCMR_MCKMNT_Pos)                         /*!< PMU MCMR: MCKMNT Mask                   */
#define PMU_MCMR_MCKIE_Pos                    14                                                      /*!< PMU MCMR: MCKIE Position                */
#define PMU_MCMR_MCKIE_Msk                    (0x01UL << PMU_MCMR_MCKIE_Pos)                          /*!< PMU MCMR: MCKIE Mask                    */
#define PMU_MCMR_RECOVER_Pos                  15                                                      /*!< PMU MCMR: RECOVER Position              */
#define PMU_MCMR_RECOVER_Msk                  (0x01UL << PMU_MCMR_RECOVER_Pos)                        /*!< PMU MCMR: RECOVER Mask                  */

/* ----------------------------------  PMU_BCCR  ---------------------------------- */
#define PMU_BCCR_MCLKSEL_Pos                  0                                                       /*!< PMU BCCR: MCLKSEL Position              */
#define PMU_BCCR_MCLKSEL_Msk                  (0x03UL << PMU_BCCR_MCLKSEL_Pos)                        /*!< PMU BCCR: MCLKSEL Mask                  */
#define PMU_BCCR_PLLCLKSEL_Pos                4                                                       /*!< PMU BCCR: PLLCLKSEL Position            */
#define PMU_BCCR_PLLCLKSEL_Msk                (0x01UL << PMU_BCCR_PLLCLKSEL_Pos)                      /*!< PMU BCCR: PLLCLKSEL Mask                */
#define PMU_BCCR_PLLCLKDIV_Pos                5                                                       /*!< PMU BCCR: PLLCLKDIV Position            */
#define PMU_BCCR_PLLCLKDIV_Msk                (0x01UL << PMU_BCCR_PLLCLKDIV_Pos)                      /*!< PMU BCCR: PLLCLKDIV Mask                */
#define PMU_BCCR_HCLKDIV_Pos                  8                                                       /*!< PMU BCCR: HCLKDIV Position              */
#define PMU_BCCR_HCLKDIV_Msk                  (0x03UL << PMU_BCCR_HCLKDIV_Pos)                        /*!< PMU BCCR: HCLKDIV Mask                  */
#define PMU_BCCR_PCLKDIV_Pos                  10                                                      /*!< PMU BCCR: PCLKDIV Position              */
#define PMU_BCCR_PCLKDIV_Msk                  (0x01UL << PMU_BCCR_PCLKDIV_Pos)                        /*!< PMU BCCR: PCLKDIV Mask                  */

/* ----------------------------------  PMU_PCSR  ---------------------------------- */
#define PMU_PCSR_WDTCS_Pos                    0                                                       /*!< PMU PCSR: WDTCS Position                */
#define PMU_PCSR_WDTCS_Msk                    (0x03UL << PMU_PCSR_WDTCS_Pos)                          /*!< PMU PCSR: WDTCS Mask                    */
#define PMU_PCSR_FRTCS_Pos                    2                                                       /*!< PMU PCSR: FRTCS Position                */
#define PMU_PCSR_FRTCS_Msk                    (0x03UL << PMU_PCSR_FRTCS_Pos)                          /*!< PMU PCSR: FRTCS Mask                    */
#define PMU_PCSR_T01CS_Pos                    4                                                       /*!< PMU PCSR: T01CS Position                */
#define PMU_PCSR_T01CS_Msk                    (0x03UL << PMU_PCSR_T01CS_Pos)                          /*!< PMU PCSR: T01CS Mask                    */
#define PMU_PCSR_T25CS_Pos                    6                                                       /*!< PMU PCSR: T25CS Position                */
#define PMU_PCSR_T25CS_Msk                    (0x03UL << PMU_PCSR_T25CS_Pos)                          /*!< PMU PCSR: T25CS Mask                    */
#define PMU_PCSR_T69CS_Pos                    8                                                       /*!< PMU PCSR: T69CS Position                */
#define PMU_PCSR_T69CS_Msk                    (0x03UL << PMU_PCSR_T69CS_Pos)                          /*!< PMU PCSR: T69CS Mask                    */

/* -----------------------------------  PMU_COR  ---------------------------------- */
#define PMU_COR_CLKODIV_Pos                   0                                                       /*!< PMU COR: CLKODIV Position               */
#define PMU_COR_CLKODIV_Msk                   (0x0fUL << PMU_COR_CLKODIV_Pos)                         /*!< PMU COR: CLKODIV Mask                   */
#define PMU_COR_CLKOEN_Pos                    4                                                       /*!< PMU COR: CLKOEN Position                */
#define PMU_COR_CLKOEN_Msk                    (0x01UL << PMU_COR_CLKOEN_Pos)                          /*!< PMU COR: CLKOEN Mask                    */
#define PMU_COR_CLKOSEL_Pos                   5                                                       /*!< PMU COR: CLKOSEL Position               */
#define PMU_COR_CLKOSEL_Msk                   (0x01UL << PMU_COR_CLKOSEL_Pos)                         /*!< PMU COR: CLKOSEL Mask                   */
#define PMU_COR_TRACEDATADELAY_Pos            6                                                       /*!< PMU COR: TRACEDATADELAY Position        */
#define PMU_COR_TRACEDATADELAY_Msk            (0x01UL << PMU_COR_TRACEDATADELAY_Pos)                  /*!< PMU COR: TRACEDATADELAY Mask            */
#define PMU_COR_TRACECLKINV_Pos               7                                                       /*!< PMU COR: TRACECLKINV Position           */
#define PMU_COR_TRACECLKINV_Msk               (0x01UL << PMU_COR_TRACECLKINV_Pos)                     /*!< PMU COR: TRACECLKINV Mask               */
#define PMU_COR_TRACEDIV_Pos                  8                                                       /*!< PMU COR: TRACEDIV Position              */
#define PMU_COR_TRACEDIV_Msk                  (0x07UL << PMU_COR_TRACEDIV_Pos)                        /*!< PMU COR: TRACEDIV Mask                  */
#define PMU_COR_TRACEDIVKEY_Pos               12                                                      /*!< PMU COR: TRACEDIVKEY Position           */
#define PMU_COR_TRACEDIVKEY_Msk               (0x0fUL << PMU_COR_TRACEDIVKEY_Pos)                     /*!< PMU COR: TRACEDIVKEY Mask               */

/* ---------------------------------  PMU_PLLCON  --------------------------------- */
#define PMU_PLLCON_POSTDIV_Pos                0                                                       /*!< PMU PLLCON: POSTDIV Position            */
#define PMU_PLLCON_POSTDIV_Msk                (0x0fUL << PMU_PLLCON_POSTDIV_Pos)                      /*!< PMU PLLCON: POSTDIV Mask                */
#define PMU_PLLCON_PREDIV_Pos                 8                                                       /*!< PMU PLLCON: PREDIV Position             */
#define PMU_PLLCON_PREDIV_Msk                 (0x07UL << PMU_PLLCON_PREDIV_Pos)                       /*!< PMU PLLCON: PREDIV Mask                 */
#define PMU_PLLCON_LOCKSTS_Pos                12                                                      /*!< PMU PLLCON: LOCKSTS Position            */
#define PMU_PLLCON_LOCKSTS_Msk                (0x01UL << PMU_PLLCON_LOCKSTS_Pos)                      /*!< PMU PLLCON: LOCKSTS Mask                */
#define PMU_PLLCON_BYPASS_Pos                 13                                                      /*!< PMU PLLCON: BYPASS Position             */
#define PMU_PLLCON_BYPASS_Msk                 (0x01UL << PMU_PLLCON_BYPASS_Pos)                       /*!< PMU PLLCON: BYPASS Mask                 */
#define PMU_PLLCON_PLLEN_Pos                  14                                                      /*!< PMU PLLCON: PLLEN Position              */
#define PMU_PLLCON_PLLEN_Msk                  (0x01UL << PMU_PLLCON_PLLEN_Pos)                        /*!< PMU PLLCON: PLLEN Mask                  */
#define PMU_PLLCON_PLLRESB_Pos                15                                                      /*!< PMU PLLCON: PLLRESB Position            */
#define PMU_PLLCON_PLLRESB_Msk                (0x01UL << PMU_PLLCON_PLLRESB_Pos)                      /*!< PMU PLLCON: PLLRESB Mask                */
#define PMU_PLLCON_DIV_Pos                    16                                                      /*!< PMU PLLCON: DIV Position                */
#define PMU_PLLCON_DIV_Msk                    (0x0fUL << PMU_PLLCON_DIV_Pos)                          /*!< PMU PLLCON: DIV Mask                    */
#define PMU_PLLCON_MULT_Pos                   20                                                      /*!< PMU PLLCON: MULT Position               */
#define PMU_PLLCON_MULT_Msk                   (0x000000ffUL << PMU_PLLCON_MULT_Pos)                   /*!< PMU PLLCON: MULT Mask                   */
#define PMU_PLLCON_VCOMODE_Pos                28                                                      /*!< PMU PLLCON: VCOMODE Position            */
#define PMU_PLLCON_VCOMODE_Msk                (0x01UL << PMU_PLLCON_VCOMODE_Pos)                      /*!< PMU PLLCON: VCOMODE Mask                */

/* ---------------------------------  PMU_LVDCON  --------------------------------- */
#define PMU_LVDCON_LVDIL_Pos                  0                                                       /*!< PMU LVDCON: LVDIL Position              */
#define PMU_LVDCON_LVDIL_Msk                  (0x07UL << PMU_LVDCON_LVDIL_Pos)                        /*!< PMU LVDCON: LVDIL Mask                  */
#define PMU_LVDCON_LVDIEN_Pos                 3                                                       /*!< PMU LVDCON: LVDIEN Position             */
#define PMU_LVDCON_LVDIEN_Msk                 (0x01UL << PMU_LVDCON_LVDIEN_Pos)                       /*!< PMU LVDCON: LVDIEN Mask                 */
#define PMU_LVDCON_LVDICS_Pos                 5                                                       /*!< PMU LVDCON: LVDICS Position             */
#define PMU_LVDCON_LVDICS_Msk                 (0x01UL << PMU_LVDCON_LVDICS_Pos)                       /*!< PMU LVDCON: LVDICS Mask                 */
#define PMU_LVDCON_LVDIF_Pos                  6                                                       /*!< PMU LVDCON: LVDIF Position              */
#define PMU_LVDCON_LVDIF_Msk                  (0x01UL << PMU_LVDCON_LVDIF_Pos)                        /*!< PMU LVDCON: LVDIF Mask                  */
#define PMU_LVDCON_LVDRL_Pos                  8                                                       /*!< PMU LVDCON: LVDRL Position              */
#define PMU_LVDCON_LVDRL_Msk                  (0x07UL << PMU_LVDCON_LVDRL_Pos)                        /*!< PMU LVDCON: LVDRL Mask                  */
#define PMU_LVDCON_LVDREN_Pos                 11                                                      /*!< PMU LVDCON: LVDREN Position             */
#define PMU_LVDCON_LVDREN_Msk                 (0x01UL << PMU_LVDCON_LVDREN_Pos)                       /*!< PMU LVDCON: LVDREN Mask                 */
#define PMU_LVDCON_LVDRF_Pos                  14                                                      /*!< PMU LVDCON: LVDRF Position              */
#define PMU_LVDCON_LVDRF_Msk                  (0x01UL << PMU_LVDCON_LVDRF_Pos)                        /*!< PMU LVDCON: LVDRF Mask                  */
#define PMU_LVDCON_LVDEN_Pos                  15                                                      /*!< PMU LVDCON: LVDEN Position              */
#define PMU_LVDCON_LVDEN_Msk                  (0x01UL << PMU_LVDCON_LVDEN_Pos)                        /*!< PMU LVDCON: LVDEN Mask                  */

/* ---------------------------------  PMU_VDCCON  --------------------------------- */
#define PMU_VDCCON_VDCDELAY_Pos               0                                                       /*!< PMU VDCCON: VDCDELAY Position           */
#define PMU_VDCCON_VDCDELAY_Msk               (0x000000ffUL << PMU_VDCCON_VDCDELAY_Pos)               /*!< PMU VDCCON: VDCDELAY Mask               */
#define PMU_VDCCON_VDCTRIM_Pos                8                                                       /*!< PMU VDCCON: VDCTRIM Position            */
#define PMU_VDCCON_VDCTRIM_Msk                (0x0fUL << PMU_VDCCON_VDCTRIM_Pos)                      /*!< PMU VDCCON: VDCTRIM Mask                */
#define PMU_VDCCON_LVDTRIM_Pos                12                                                      /*!< PMU VDCCON: LVDTRIM Position            */
#define PMU_VDCCON_LVDTRIM_Msk                (0x0fUL << PMU_VDCCON_LVDTRIM_Pos)                      /*!< PMU VDCCON: LVDTRIM Mask                */
#define PMU_VDCCON_VDCD_EN_Pos                16                                                      /*!< PMU VDCCON: VDCD_EN Position            */
#define PMU_VDCCON_VDCD_EN_Msk                (0x01UL << PMU_VDCCON_VDCD_EN_Pos)                      /*!< PMU VDCCON: VDCD_EN Mask                */
#define PMU_VDCCON_VDCT_EN_Pos                17                                                      /*!< PMU VDCCON: VDCT_EN Position            */
#define PMU_VDCCON_VDCT_EN_Msk                (0x01UL << PMU_VDCCON_VDCT_EN_Pos)                      /*!< PMU VDCCON: VDCT_EN Mask                */
#define PMU_VDCCON_LVDT_EN_Pos                18                                                      /*!< PMU VDCCON: LVDT_EN Position            */
#define PMU_VDCCON_LVDT_EN_Msk                (0x01UL << PMU_VDCCON_LVDT_EN_Pos)                      /*!< PMU VDCCON: LVDT_EN Mask                */
#define PMU_VDCCON_BMRT_EN_Pos                19                                                      /*!< PMU VDCCON: BMRT_EN Position            */
#define PMU_VDCCON_BMRT_EN_Msk                (0x01UL << PMU_VDCCON_BMRT_EN_Pos)                      /*!< PMU VDCCON: BMRT_EN Mask                */
#define PMU_VDCCON_VDROP_EN_Pos               20                                                      /*!< PMU VDCCON: VDROP_EN Position           */
#define PMU_VDCCON_VDROP_EN_Msk               (0x03UL << PMU_VDCCON_VDROP_EN_Pos)                     /*!< PMU VDCCON: VDROP_EN Mask               */
#define PMU_VDCCON_DFLVL_EN_Pos               22                                                      /*!< PMU VDCCON: DFLVL_EN Position           */
#define PMU_VDCCON_DFLVL_EN_Msk               (0x03UL << PMU_VDCCON_DFLVL_EN_Pos)                     /*!< PMU VDCCON: DFLVL_EN Mask               */
#define PMU_VDCCON_VDROP_Pos                  24                                                      /*!< PMU VDCCON: VDROP Position              */
#define PMU_VDCCON_VDROP_Msk                  (0x01UL << PMU_VDCCON_VDROP_Pos)                        /*!< PMU VDCCON: VDROP Mask                  */
#define PMU_VDCCON_BOPENB_Pos                 26                                                      /*!< PMU VDCCON: BOPENB Position             */
#define PMU_VDCCON_BOPENB_Msk                 (0x01UL << PMU_VDCCON_BOPENB_Pos)                       /*!< PMU VDCCON: BOPENB Mask                 */
#define PMU_VDCCON_BMRTRIM_Pos                28                                                      /*!< PMU VDCCON: BMRTRIM Position            */
#define PMU_VDCCON_BMRTRIM_Msk                (0x03UL << PMU_VDCCON_BMRTRIM_Pos)                      /*!< PMU VDCCON: BMRTRIM Mask                */
#define PMU_VDCCON_DFLVL_Pos                  31                                                      /*!< PMU VDCCON: DFLVL Position              */
#define PMU_VDCCON_DFLVL_Msk                  (0x01UL << PMU_VDCCON_DFLVL_Pos)                        /*!< PMU VDCCON: DFLVL Mask                  */

/* -------------------------------  PMU_IOSC16TRIM  ------------------------------- */
#define PMU_IOSC16TRIM_TCAL1_Pos              0                                                       /*!< PMU IOSC16TRIM: TCAL1 Position          */
#define PMU_IOSC16TRIM_TCAL1_Msk              (0x07UL << PMU_IOSC16TRIM_TCAL1_Pos)                    /*!< PMU IOSC16TRIM: TCAL1 Mask              */
#define PMU_IOSC16TRIM_UDCH_Pos               3                                                       /*!< PMU IOSC16TRIM: UDCH Position           */
#define PMU_IOSC16TRIM_UDCH_Msk               (0x03UL << PMU_IOSC16TRIM_UDCH_Pos)                     /*!< PMU IOSC16TRIM: UDCH Mask               */
#define PMU_IOSC16TRIM_TSL_Pos                5                                                       /*!< PMU IOSC16TRIM: TSL Position            */
#define PMU_IOSC16TRIM_TSL_Msk                (0x07UL << PMU_IOSC16TRIM_TSL_Pos)                      /*!< PMU IOSC16TRIM: TSL Mask                */
#define PMU_IOSC16TRIM_LTM_Pos                8                                                       /*!< PMU IOSC16TRIM: LTM Position            */
#define PMU_IOSC16TRIM_LTM_Msk                (0x03UL << PMU_IOSC16TRIM_LTM_Pos)                      /*!< PMU IOSC16TRIM: LTM Mask                */
#define PMU_IOSC16TRIM_LT_Pos                 10                                                      /*!< PMU IOSC16TRIM: LT Position             */
#define PMU_IOSC16TRIM_LT_Msk                 (0x0fUL << PMU_IOSC16TRIM_LT_Pos)                       /*!< PMU IOSC16TRIM: LT Mask                 */
#define PMU_IOSC16TRIM_TCAL_EN_Pos            16                                                      /*!< PMU IOSC16TRIM: TCAL_EN Position        */
#define PMU_IOSC16TRIM_TCAL_EN_Msk            (0x01UL << PMU_IOSC16TRIM_TCAL_EN_Pos)                  /*!< PMU IOSC16TRIM: TCAL_EN Mask            */
#define PMU_IOSC16TRIM_UDCH_EN_Pos            17                                                      /*!< PMU IOSC16TRIM: UDCH_EN Position        */
#define PMU_IOSC16TRIM_UDCH_EN_Msk            (0x01UL << PMU_IOSC16TRIM_UDCH_EN_Pos)                  /*!< PMU IOSC16TRIM: UDCH_EN Mask            */
#define PMU_IOSC16TRIM_TSL_EN_Pos             18                                                      /*!< PMU IOSC16TRIM: TSL_EN Position         */
#define PMU_IOSC16TRIM_TSL_EN_Msk             (0x01UL << PMU_IOSC16TRIM_TSL_EN_Pos)                   /*!< PMU IOSC16TRIM: TSL_EN Mask             */
#define PMU_IOSC16TRIM_LTM_EN_Pos             19                                                      /*!< PMU IOSC16TRIM: LTM_EN Position         */
#define PMU_IOSC16TRIM_LTM_EN_Msk             (0x01UL << PMU_IOSC16TRIM_LTM_EN_Pos)                   /*!< PMU IOSC16TRIM: LTM_EN Mask             */
#define PMU_IOSC16TRIM_LT_EN_Pos              20                                                      /*!< PMU IOSC16TRIM: LT_EN Position          */
#define PMU_IOSC16TRIM_LT_EN_Msk              (0x01UL << PMU_IOSC16TRIM_LT_EN_Pos)                    /*!< PMU IOSC16TRIM: LT_EN Mask              */

/* ---------------------------------  PMU_EOSCCON  -------------------------------- */
#define PMU_EOSCCON_MOSCISEL_Pos              0                                                       /*!< PMU EOSCCON: MOSCISEL Position          */
#define PMU_EOSCCON_MOSCISEL_Msk              (0x03UL << PMU_EOSCCON_MOSCISEL_Pos)                    /*!< PMU EOSCCON: MOSCISEL Mask              */
#define PMU_EOSCCON_MOSCNFSEL_Pos             4                                                       /*!< PMU EOSCCON: MOSCNFSEL Position         */
#define PMU_EOSCCON_MOSCNFSEL_Msk             (0x03UL << PMU_EOSCCON_MOSCNFSEL_Pos)                   /*!< PMU EOSCCON: MOSCNFSEL Mask             */
#define PMU_EOSCCON_MOSCNFOFF_Pos             7                                                       /*!< PMU EOSCCON: MOSCNFOFF Position         */
#define PMU_EOSCCON_MOSCNFOFF_Msk             (0x01UL << PMU_EOSCCON_MOSCNFOFF_Pos)                   /*!< PMU EOSCCON: MOSCNFOFF Mask             */
#define PMU_EOSCCON_SOSCISEL_Pos              12                                                      /*!< PMU EOSCCON: SOSCISEL Position          */
#define PMU_EOSCCON_SOSCISEL_Msk              (0x03UL << PMU_EOSCCON_SOSCISEL_Pos)                    /*!< PMU EOSCCON: SOSCISEL Mask              */
#define PMU_EOSCCON_SOSCNFOFF_Pos             15                                                      /*!< PMU EOSCCON: SOSCNFOFF Position         */
#define PMU_EOSCCON_SOSCNFOFF_Msk             (0x01UL << PMU_EOSCCON_SOSCNFOFF_Pos)                   /*!< PMU EOSCCON: SOSCNFOFF Mask             */

/* --------------------------------  PMU_EXTMODER  -------------------------------- */
#define PMU_EXTMODER_BOOT_Pos                 0                                                       /*!< PMU EXTMODER: BOOT Position             */
#define PMU_EXTMODER_BOOT_Msk                 (0x01UL << PMU_EXTMODER_BOOT_Pos)                       /*!< PMU EXTMODER: BOOT Mask                 */
#define PMU_EXTMODER_TEST_Pos                 1                                                       /*!< PMU EXTMODER: TEST Position             */
#define PMU_EXTMODER_TEST_Msk                 (0x01UL << PMU_EXTMODER_TEST_Pos)                       /*!< PMU EXTMODER: TEST Mask                 */
#define PMU_EXTMODER_SCANMD_Pos               2                                                       /*!< PMU EXTMODER: SCANMD Position           */
#define PMU_EXTMODER_SCANMD_Msk               (0x01UL << PMU_EXTMODER_SCANMD_Pos)                     /*!< PMU EXTMODER: SCANMD Mask               */
#define PMU_EXTMODER_ROSCAON_Pos              3                                                       /*!< PMU EXTMODER: ROSCAON Position          */
#define PMU_EXTMODER_ROSCAON_Msk              (0x01UL << PMU_EXTMODER_ROSCAON_Pos)                    /*!< PMU EXTMODER: ROSCAON Mask              */
#define PMU_EXTMODER_XRSTON_Pos               4                                                       /*!< PMU EXTMODER: XRSTON Position           */
#define PMU_EXTMODER_XRSTON_Msk               (0x01UL << PMU_EXTMODER_XRSTON_Pos)                     /*!< PMU EXTMODER: XRSTON Mask               */
#define PMU_EXTMODER_PDON_Pos                 5                                                       /*!< PMU EXTMODER: PDON Position             */
#define PMU_EXTMODER_PDON_Msk                 (0x01UL << PMU_EXTMODER_PDON_Pos)                       /*!< PMU EXTMODER: PDON Mask                 */
#define PMU_EXTMODER_FMTEST_Pos               8                                                       /*!< PMU EXTMODER: FMTEST Position           */
#define PMU_EXTMODER_FMTEST_Msk               (0x01UL << PMU_EXTMODER_FMTEST_Pos)                     /*!< PMU EXTMODER: FMTEST Mask               */


/* ================================================================================ */
/* ================          struct 'PCA' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  PCA_MR  ----------------------------------- */
#define PCA_MR_P0_Pos                         0                                                       /*!< PCA MR: P0 Position                     */
#define PCA_MR_P0_Msk                         (0x03UL << PCA_MR_P0_Pos)                               /*!< PCA MR: P0 Mask                         */
#define PCA_MR_P1_Pos                         2                                                       /*!< PCA MR: P1 Position                     */
#define PCA_MR_P1_Msk                         (0x03UL << PCA_MR_P1_Pos)                               /*!< PCA MR: P1 Mask                         */
#define PCA_MR_P2_Pos                         4                                                       /*!< PCA MR: P2 Position                     */
#define PCA_MR_P2_Msk                         (0x03UL << PCA_MR_P2_Pos)                               /*!< PCA MR: P2 Mask                         */
#define PCA_MR_P3_Pos                         6                                                       /*!< PCA MR: P3 Position                     */
#define PCA_MR_P3_Msk                         (0x03UL << PCA_MR_P3_Pos)                               /*!< PCA MR: P3 Mask                         */
#define PCA_MR_P4_Pos                         8                                                       /*!< PCA MR: P4 Position                     */
#define PCA_MR_P4_Msk                         (0x03UL << PCA_MR_P4_Pos)                               /*!< PCA MR: P4 Mask                         */
#define PCA_MR_P5_Pos                         10                                                      /*!< PCA MR: P5 Position                     */
#define PCA_MR_P5_Msk                         (0x03UL << PCA_MR_P5_Pos)                               /*!< PCA MR: P5 Mask                         */
#define PCA_MR_P6_Pos                         12                                                      /*!< PCA MR: P6 Position                     */
#define PCA_MR_P6_Msk                         (0x03UL << PCA_MR_P6_Pos)                               /*!< PCA MR: P6 Mask                         */
#define PCA_MR_P7_Pos                         14                                                      /*!< PCA MR: P7 Position                     */
#define PCA_MR_P7_Msk                         (0x03UL << PCA_MR_P7_Pos)                               /*!< PCA MR: P7 Mask                         */
#define PCA_MR_P8_Pos                         16                                                      /*!< PCA MR: P8 Position                     */
#define PCA_MR_P8_Msk                         (0x03UL << PCA_MR_P8_Pos)                               /*!< PCA MR: P8 Mask                         */
#define PCA_MR_P9_Pos                         18                                                      /*!< PCA MR: P9 Position                     */
#define PCA_MR_P9_Msk                         (0x03UL << PCA_MR_P9_Pos)                               /*!< PCA MR: P9 Mask                         */
#define PCA_MR_P10_Pos                        20                                                      /*!< PCA MR: P10 Position                    */
#define PCA_MR_P10_Msk                        (0x03UL << PCA_MR_P10_Pos)                              /*!< PCA MR: P10 Mask                        */
#define PCA_MR_P11_Pos                        22                                                      /*!< PCA MR: P11 Position                    */
#define PCA_MR_P11_Msk                        (0x03UL << PCA_MR_P11_Pos)                              /*!< PCA MR: P11 Mask                        */
#define PCA_MR_P12_Pos                        24                                                      /*!< PCA MR: P12 Position                    */
#define PCA_MR_P12_Msk                        (0x03UL << PCA_MR_P12_Pos)                              /*!< PCA MR: P12 Mask                        */
#define PCA_MR_P13_Pos                        26                                                      /*!< PCA MR: P13 Position                    */
#define PCA_MR_P13_Msk                        (0x03UL << PCA_MR_P13_Pos)                              /*!< PCA MR: P13 Mask                        */
#define PCA_MR_P14_Pos                        28                                                      /*!< PCA MR: P14 Position                    */
#define PCA_MR_P14_Msk                        (0x03UL << PCA_MR_P14_Pos)                              /*!< PCA MR: P14 Mask                        */
#define PCA_MR_P15_Pos                        30                                                      /*!< PCA MR: P15 Position                    */
#define PCA_MR_P15_Msk                        (0x03UL << PCA_MR_P15_Pos)                              /*!< PCA MR: P15 Mask                        */

/* -----------------------------------  PCA_CR  ----------------------------------- */
#define PCA_CR_P0_Pos                         0                                                       /*!< PCA CR: P0 Position                     */
#define PCA_CR_P0_Msk                         (0x03UL << PCA_CR_P0_Pos)                               /*!< PCA CR: P0 Mask                         */
#define PCA_CR_P1_Pos                         2                                                       /*!< PCA CR: P1 Position                     */
#define PCA_CR_P1_Msk                         (0x03UL << PCA_CR_P1_Pos)                               /*!< PCA CR: P1 Mask                         */
#define PCA_CR_P2_Pos                         4                                                       /*!< PCA CR: P2 Position                     */
#define PCA_CR_P2_Msk                         (0x03UL << PCA_CR_P2_Pos)                               /*!< PCA CR: P2 Mask                         */
#define PCA_CR_P3_Pos                         6                                                       /*!< PCA CR: P3 Position                     */
#define PCA_CR_P3_Msk                         (0x03UL << PCA_CR_P3_Pos)                               /*!< PCA CR: P3 Mask                         */
#define PCA_CR_P4_Pos                         8                                                       /*!< PCA CR: P4 Position                     */
#define PCA_CR_P4_Msk                         (0x03UL << PCA_CR_P4_Pos)                               /*!< PCA CR: P4 Mask                         */
#define PCA_CR_P5_Pos                         10                                                      /*!< PCA CR: P5 Position                     */
#define PCA_CR_P5_Msk                         (0x03UL << PCA_CR_P5_Pos)                               /*!< PCA CR: P5 Mask                         */
#define PCA_CR_P6_Pos                         12                                                      /*!< PCA CR: P6 Position                     */
#define PCA_CR_P6_Msk                         (0x03UL << PCA_CR_P6_Pos)                               /*!< PCA CR: P6 Mask                         */
#define PCA_CR_P7_Pos                         14                                                      /*!< PCA CR: P7 Position                     */
#define PCA_CR_P7_Msk                         (0x03UL << PCA_CR_P7_Pos)                               /*!< PCA CR: P7 Mask                         */
#define PCA_CR_P8_Pos                         16                                                      /*!< PCA CR: P8 Position                     */
#define PCA_CR_P8_Msk                         (0x03UL << PCA_CR_P8_Pos)                               /*!< PCA CR: P8 Mask                         */
#define PCA_CR_P9_Pos                         18                                                      /*!< PCA CR: P9 Position                     */
#define PCA_CR_P9_Msk                         (0x03UL << PCA_CR_P9_Pos)                               /*!< PCA CR: P9 Mask                         */
#define PCA_CR_P10_Pos                        20                                                      /*!< PCA CR: P10 Position                    */
#define PCA_CR_P10_Msk                        (0x03UL << PCA_CR_P10_Pos)                              /*!< PCA CR: P10 Mask                        */
#define PCA_CR_P11_Pos                        22                                                      /*!< PCA CR: P11 Position                    */
#define PCA_CR_P11_Msk                        (0x03UL << PCA_CR_P11_Pos)                              /*!< PCA CR: P11 Mask                        */
#define PCA_CR_P12_Pos                        24                                                      /*!< PCA CR: P12 Position                    */
#define PCA_CR_P12_Msk                        (0x03UL << PCA_CR_P12_Pos)                              /*!< PCA CR: P12 Mask                        */
#define PCA_CR_P13_Pos                        26                                                      /*!< PCA CR: P13 Position                    */
#define PCA_CR_P13_Msk                        (0x03UL << PCA_CR_P13_Pos)                              /*!< PCA CR: P13 Mask                        */
#define PCA_CR_P14_Pos                        28                                                      /*!< PCA CR: P14 Position                    */
#define PCA_CR_P14_Msk                        (0x03UL << PCA_CR_P14_Pos)                              /*!< PCA CR: P14 Mask                        */
#define PCA_CR_P15_Pos                        30                                                      /*!< PCA CR: P15 Position                    */
#define PCA_CR_P15_Msk                        (0x03UL << PCA_CR_P15_Pos)                              /*!< PCA CR: P15 Mask                        */

/* -----------------------------------  PCA_PCR  ---------------------------------- */
#define PCA_PCR_P0_Pos                        0                                                       /*!< PCA PCR: P0 Position                    */
#define PCA_PCR_P0_Msk                        (0x01UL << PCA_PCR_P0_Pos)                              /*!< PCA PCR: P0 Mask                        */
#define PCA_PCR_P1_Pos                        1                                                       /*!< PCA PCR: P1 Position                    */
#define PCA_PCR_P1_Msk                        (0x01UL << PCA_PCR_P1_Pos)                              /*!< PCA PCR: P1 Mask                        */
#define PCA_PCR_P2_Pos                        2                                                       /*!< PCA PCR: P2 Position                    */
#define PCA_PCR_P2_Msk                        (0x01UL << PCA_PCR_P2_Pos)                              /*!< PCA PCR: P2 Mask                        */
#define PCA_PCR_P3_Pos                        3                                                       /*!< PCA PCR: P3 Position                    */
#define PCA_PCR_P3_Msk                        (0x01UL << PCA_PCR_P3_Pos)                              /*!< PCA PCR: P3 Mask                        */
#define PCA_PCR_P4_Pos                        4                                                       /*!< PCA PCR: P4 Position                    */
#define PCA_PCR_P4_Msk                        (0x01UL << PCA_PCR_P4_Pos)                              /*!< PCA PCR: P4 Mask                        */
#define PCA_PCR_P5_Pos                        5                                                       /*!< PCA PCR: P5 Position                    */
#define PCA_PCR_P5_Msk                        (0x01UL << PCA_PCR_P5_Pos)                              /*!< PCA PCR: P5 Mask                        */
#define PCA_PCR_P6_Pos                        6                                                       /*!< PCA PCR: P6 Position                    */
#define PCA_PCR_P6_Msk                        (0x01UL << PCA_PCR_P6_Pos)                              /*!< PCA PCR: P6 Mask                        */
#define PCA_PCR_P7_Pos                        7                                                       /*!< PCA PCR: P7 Position                    */
#define PCA_PCR_P7_Msk                        (0x01UL << PCA_PCR_P7_Pos)                              /*!< PCA PCR: P7 Mask                        */
#define PCA_PCR_P8_Pos                        8                                                       /*!< PCA PCR: P8 Position                    */
#define PCA_PCR_P8_Msk                        (0x01UL << PCA_PCR_P8_Pos)                              /*!< PCA PCR: P8 Mask                        */
#define PCA_PCR_P9_Pos                        9                                                       /*!< PCA PCR: P9 Position                    */
#define PCA_PCR_P9_Msk                        (0x01UL << PCA_PCR_P9_Pos)                              /*!< PCA PCR: P9 Mask                        */
#define PCA_PCR_P10_Pos                       10                                                      /*!< PCA PCR: P10 Position                   */
#define PCA_PCR_P10_Msk                       (0x01UL << PCA_PCR_P10_Pos)                             /*!< PCA PCR: P10 Mask                       */
#define PCA_PCR_P11_Pos                       11                                                      /*!< PCA PCR: P11 Position                   */
#define PCA_PCR_P11_Msk                       (0x01UL << PCA_PCR_P11_Pos)                             /*!< PCA PCR: P11 Mask                       */
#define PCA_PCR_P12_Pos                       12                                                      /*!< PCA PCR: P12 Position                   */
#define PCA_PCR_P12_Msk                       (0x01UL << PCA_PCR_P12_Pos)                             /*!< PCA PCR: P12 Mask                       */
#define PCA_PCR_P13_Pos                       13                                                      /*!< PCA PCR: P13 Position                   */
#define PCA_PCR_P13_Msk                       (0x01UL << PCA_PCR_P13_Pos)                             /*!< PCA PCR: P13 Mask                       */
#define PCA_PCR_P14_Pos                       14                                                      /*!< PCA PCR: P14 Position                   */
#define PCA_PCR_P14_Msk                       (0x01UL << PCA_PCR_P14_Pos)                             /*!< PCA PCR: P14 Mask                       */
#define PCA_PCR_P15_Pos                       15                                                      /*!< PCA PCR: P15 Position                   */
#define PCA_PCR_P15_Msk                       (0x01UL << PCA_PCR_P15_Pos)                             /*!< PCA PCR: P15 Mask                       */
#define PCA_PCR_D0_Pos                        16                                                      /*!< PCA PCR: D0 Position                    */
#define PCA_PCR_D0_Msk                        (0x01UL << PCA_PCR_D0_Pos)                              /*!< PCA PCR: D0 Mask                        */
#define PCA_PCR_D1_Pos                        17                                                      /*!< PCA PCR: D1 Position                    */
#define PCA_PCR_D1_Msk                        (0x01UL << PCA_PCR_D1_Pos)                              /*!< PCA PCR: D1 Mask                        */
#define PCA_PCR_D2_Pos                        18                                                      /*!< PCA PCR: D2 Position                    */
#define PCA_PCR_D2_Msk                        (0x01UL << PCA_PCR_D2_Pos)                              /*!< PCA PCR: D2 Mask                        */
#define PCA_PCR_D3_Pos                        19                                                      /*!< PCA PCR: D3 Position                    */
#define PCA_PCR_D3_Msk                        (0x01UL << PCA_PCR_D3_Pos)                              /*!< PCA PCR: D3 Mask                        */
#define PCA_PCR_D4_Pos                        20                                                      /*!< PCA PCR: D4 Position                    */
#define PCA_PCR_D4_Msk                        (0x01UL << PCA_PCR_D4_Pos)                              /*!< PCA PCR: D4 Mask                        */
#define PCA_PCR_D5_Pos                        21                                                      /*!< PCA PCR: D5 Position                    */
#define PCA_PCR_D5_Msk                        (0x01UL << PCA_PCR_D5_Pos)                              /*!< PCA PCR: D5 Mask                        */
#define PCA_PCR_D6_Pos                        22                                                      /*!< PCA PCR: D6 Position                    */
#define PCA_PCR_D6_Msk                        (0x01UL << PCA_PCR_D6_Pos)                              /*!< PCA PCR: D6 Mask                        */
#define PCA_PCR_D7_Pos                        23                                                      /*!< PCA PCR: D7 Position                    */
#define PCA_PCR_D7_Msk                        (0x01UL << PCA_PCR_D7_Pos)                              /*!< PCA PCR: D7 Mask                        */
#define PCA_PCR_D8_Pos                        24                                                      /*!< PCA PCR: D8 Position                    */
#define PCA_PCR_D8_Msk                        (0x01UL << PCA_PCR_D8_Pos)                              /*!< PCA PCR: D8 Mask                        */
#define PCA_PCR_D9_Pos                        25                                                      /*!< PCA PCR: D9 Position                    */
#define PCA_PCR_D9_Msk                        (0x01UL << PCA_PCR_D9_Pos)                              /*!< PCA PCR: D9 Mask                        */
#define PCA_PCR_D10_Pos                       26                                                      /*!< PCA PCR: D10 Position                   */
#define PCA_PCR_D10_Msk                       (0x01UL << PCA_PCR_D10_Pos)                             /*!< PCA PCR: D10 Mask                       */
#define PCA_PCR_D11_Pos                       27                                                      /*!< PCA PCR: D11 Position                   */
#define PCA_PCR_D11_Msk                       (0x01UL << PCA_PCR_D11_Pos)                             /*!< PCA PCR: D11 Mask                       */
#define PCA_PCR_D12_Pos                       28                                                      /*!< PCA PCR: D12 Position                   */
#define PCA_PCR_D12_Msk                       (0x01UL << PCA_PCR_D12_Pos)                             /*!< PCA PCR: D12 Mask                       */
#define PCA_PCR_D13_Pos                       29                                                      /*!< PCA PCR: D13 Position                   */
#define PCA_PCR_D13_Msk                       (0x01UL << PCA_PCR_D13_Pos)                             /*!< PCA PCR: D13 Mask                       */
#define PCA_PCR_D14_Pos                       30                                                      /*!< PCA PCR: D14 Position                   */
#define PCA_PCR_D14_Msk                       (0x01UL << PCA_PCR_D14_Pos)                             /*!< PCA PCR: D14 Mask                       */
#define PCA_PCR_D15_Pos                       31                                                      /*!< PCA PCR: D15 Position                   */
#define PCA_PCR_D15_Msk                       (0x01UL << PCA_PCR_D15_Pos)                             /*!< PCA PCR: D15 Mask                       */

/* -----------------------------------  PCA_DER  ---------------------------------- */
#define PCA_DER_P0_Pos                        0                                                       /*!< PCA DER: P0 Position                    */
#define PCA_DER_P0_Msk                        (0x01UL << PCA_DER_P0_Pos)                              /*!< PCA DER: P0 Mask                        */
#define PCA_DER_P1_Pos                        1                                                       /*!< PCA DER: P1 Position                    */
#define PCA_DER_P1_Msk                        (0x01UL << PCA_DER_P1_Pos)                              /*!< PCA DER: P1 Mask                        */
#define PCA_DER_P2_Pos                        2                                                       /*!< PCA DER: P2 Position                    */
#define PCA_DER_P2_Msk                        (0x01UL << PCA_DER_P2_Pos)                              /*!< PCA DER: P2 Mask                        */
#define PCA_DER_P3_Pos                        3                                                       /*!< PCA DER: P3 Position                    */
#define PCA_DER_P3_Msk                        (0x01UL << PCA_DER_P3_Pos)                              /*!< PCA DER: P3 Mask                        */
#define PCA_DER_P4_Pos                        4                                                       /*!< PCA DER: P4 Position                    */
#define PCA_DER_P4_Msk                        (0x01UL << PCA_DER_P4_Pos)                              /*!< PCA DER: P4 Mask                        */
#define PCA_DER_P5_Pos                        5                                                       /*!< PCA DER: P5 Position                    */
#define PCA_DER_P5_Msk                        (0x01UL << PCA_DER_P5_Pos)                              /*!< PCA DER: P5 Mask                        */
#define PCA_DER_P6_Pos                        6                                                       /*!< PCA DER: P6 Position                    */
#define PCA_DER_P6_Msk                        (0x01UL << PCA_DER_P6_Pos)                              /*!< PCA DER: P6 Mask                        */
#define PCA_DER_P7_Pos                        7                                                       /*!< PCA DER: P7 Position                    */
#define PCA_DER_P7_Msk                        (0x01UL << PCA_DER_P7_Pos)                              /*!< PCA DER: P7 Mask                        */
#define PCA_DER_P8_Pos                        8                                                       /*!< PCA DER: P8 Position                    */
#define PCA_DER_P8_Msk                        (0x01UL << PCA_DER_P8_Pos)                              /*!< PCA DER: P8 Mask                        */
#define PCA_DER_P9_Pos                        9                                                       /*!< PCA DER: P9 Position                    */
#define PCA_DER_P9_Msk                        (0x01UL << PCA_DER_P9_Pos)                              /*!< PCA DER: P9 Mask                        */
#define PCA_DER_P10_Pos                       10                                                      /*!< PCA DER: P10 Position                   */
#define PCA_DER_P10_Msk                       (0x01UL << PCA_DER_P10_Pos)                             /*!< PCA DER: P10 Mask                       */
#define PCA_DER_P11_Pos                       11                                                      /*!< PCA DER: P11 Position                   */
#define PCA_DER_P11_Msk                       (0x01UL << PCA_DER_P11_Pos)                             /*!< PCA DER: P11 Mask                       */
#define PCA_DER_P12_Pos                       12                                                      /*!< PCA DER: P12 Position                   */
#define PCA_DER_P12_Msk                       (0x01UL << PCA_DER_P12_Pos)                             /*!< PCA DER: P12 Mask                       */
#define PCA_DER_P13_Pos                       13                                                      /*!< PCA DER: P13 Position                   */
#define PCA_DER_P13_Msk                       (0x01UL << PCA_DER_P13_Pos)                             /*!< PCA DER: P13 Mask                       */
#define PCA_DER_P14_Pos                       14                                                      /*!< PCA DER: P14 Position                   */
#define PCA_DER_P14_Msk                       (0x01UL << PCA_DER_P14_Pos)                             /*!< PCA DER: P14 Mask                       */
#define PCA_DER_P15_Pos                       15                                                      /*!< PCA DER: P15 Position                   */
#define PCA_DER_P15_Msk                       (0x01UL << PCA_DER_P15_Pos)                             /*!< PCA DER: P15 Mask                       */

/* -----------------------------------  PCA_IER  ---------------------------------- */
#define PCA_IER_P0_Pos                        0                                                       /*!< PCA IER: P0 Position                    */
#define PCA_IER_P0_Msk                        (0x03UL << PCA_IER_P0_Pos)                              /*!< PCA IER: P0 Mask                        */
#define PCA_IER_P1_Pos                        2                                                       /*!< PCA IER: P1 Position                    */
#define PCA_IER_P1_Msk                        (0x03UL << PCA_IER_P1_Pos)                              /*!< PCA IER: P1 Mask                        */
#define PCA_IER_P2_Pos                        4                                                       /*!< PCA IER: P2 Position                    */
#define PCA_IER_P2_Msk                        (0x03UL << PCA_IER_P2_Pos)                              /*!< PCA IER: P2 Mask                        */
#define PCA_IER_P3_Pos                        6                                                       /*!< PCA IER: P3 Position                    */
#define PCA_IER_P3_Msk                        (0x03UL << PCA_IER_P3_Pos)                              /*!< PCA IER: P3 Mask                        */
#define PCA_IER_P4_Pos                        8                                                       /*!< PCA IER: P4 Position                    */
#define PCA_IER_P4_Msk                        (0x03UL << PCA_IER_P4_Pos)                              /*!< PCA IER: P4 Mask                        */
#define PCA_IER_P5_Pos                        10                                                      /*!< PCA IER: P5 Position                    */
#define PCA_IER_P5_Msk                        (0x03UL << PCA_IER_P5_Pos)                              /*!< PCA IER: P5 Mask                        */
#define PCA_IER_P6_Pos                        12                                                      /*!< PCA IER: P6 Position                    */
#define PCA_IER_P6_Msk                        (0x03UL << PCA_IER_P6_Pos)                              /*!< PCA IER: P6 Mask                        */
#define PCA_IER_P7_Pos                        14                                                      /*!< PCA IER: P7 Position                    */
#define PCA_IER_P7_Msk                        (0x03UL << PCA_IER_P7_Pos)                              /*!< PCA IER: P7 Mask                        */
#define PCA_IER_P8_Pos                        16                                                      /*!< PCA IER: P8 Position                    */
#define PCA_IER_P8_Msk                        (0x03UL << PCA_IER_P8_Pos)                              /*!< PCA IER: P8 Mask                        */
#define PCA_IER_P9_Pos                        18                                                      /*!< PCA IER: P9 Position                    */
#define PCA_IER_P9_Msk                        (0x03UL << PCA_IER_P9_Pos)                              /*!< PCA IER: P9 Mask                        */
#define PCA_IER_P10_Pos                       20                                                      /*!< PCA IER: P10 Position                   */
#define PCA_IER_P10_Msk                       (0x03UL << PCA_IER_P10_Pos)                             /*!< PCA IER: P10 Mask                       */
#define PCA_IER_P11_Pos                       22                                                      /*!< PCA IER: P11 Position                   */
#define PCA_IER_P11_Msk                       (0x03UL << PCA_IER_P11_Pos)                             /*!< PCA IER: P11 Mask                       */
#define PCA_IER_P12_Pos                       24                                                      /*!< PCA IER: P12 Position                   */
#define PCA_IER_P12_Msk                       (0x03UL << PCA_IER_P12_Pos)                             /*!< PCA IER: P12 Mask                       */
#define PCA_IER_P13_Pos                       26                                                      /*!< PCA IER: P13 Position                   */
#define PCA_IER_P13_Msk                       (0x03UL << PCA_IER_P13_Pos)                             /*!< PCA IER: P13 Mask                       */
#define PCA_IER_P14_Pos                       28                                                      /*!< PCA IER: P14 Position                   */
#define PCA_IER_P14_Msk                       (0x03UL << PCA_IER_P14_Pos)                             /*!< PCA IER: P14 Mask                       */
#define PCA_IER_P15_Pos                       30                                                      /*!< PCA IER: P15 Position                   */
#define PCA_IER_P15_Msk                       (0x03UL << PCA_IER_P15_Pos)                             /*!< PCA IER: P15 Mask                       */

/* -----------------------------------  PCA_ISR  ---------------------------------- */
#define PCA_ISR_P0_Pos                        0                                                       /*!< PCA ISR: P0 Position                    */
#define PCA_ISR_P0_Msk                        (0x03UL << PCA_ISR_P0_Pos)                              /*!< PCA ISR: P0 Mask                        */
#define PCA_ISR_P1_Pos                        2                                                       /*!< PCA ISR: P1 Position                    */
#define PCA_ISR_P1_Msk                        (0x03UL << PCA_ISR_P1_Pos)                              /*!< PCA ISR: P1 Mask                        */
#define PCA_ISR_P2_Pos                        4                                                       /*!< PCA ISR: P2 Position                    */
#define PCA_ISR_P2_Msk                        (0x03UL << PCA_ISR_P2_Pos)                              /*!< PCA ISR: P2 Mask                        */
#define PCA_ISR_P3_Pos                        6                                                       /*!< PCA ISR: P3 Position                    */
#define PCA_ISR_P3_Msk                        (0x03UL << PCA_ISR_P3_Pos)                              /*!< PCA ISR: P3 Mask                        */
#define PCA_ISR_P4_Pos                        8                                                       /*!< PCA ISR: P4 Position                    */
#define PCA_ISR_P4_Msk                        (0x03UL << PCA_ISR_P4_Pos)                              /*!< PCA ISR: P4 Mask                        */
#define PCA_ISR_P5_Pos                        10                                                      /*!< PCA ISR: P5 Position                    */
#define PCA_ISR_P5_Msk                        (0x03UL << PCA_ISR_P5_Pos)                              /*!< PCA ISR: P5 Mask                        */
#define PCA_ISR_P6_Pos                        12                                                      /*!< PCA ISR: P6 Position                    */
#define PCA_ISR_P6_Msk                        (0x03UL << PCA_ISR_P6_Pos)                              /*!< PCA ISR: P6 Mask                        */
#define PCA_ISR_P7_Pos                        14                                                      /*!< PCA ISR: P7 Position                    */
#define PCA_ISR_P7_Msk                        (0x03UL << PCA_ISR_P7_Pos)                              /*!< PCA ISR: P7 Mask                        */
#define PCA_ISR_P8_Pos                        16                                                      /*!< PCA ISR: P8 Position                    */
#define PCA_ISR_P8_Msk                        (0x03UL << PCA_ISR_P8_Pos)                              /*!< PCA ISR: P8 Mask                        */
#define PCA_ISR_P9_Pos                        18                                                      /*!< PCA ISR: P9 Position                    */
#define PCA_ISR_P9_Msk                        (0x03UL << PCA_ISR_P9_Pos)                              /*!< PCA ISR: P9 Mask                        */
#define PCA_ISR_P10_Pos                       20                                                      /*!< PCA ISR: P10 Position                   */
#define PCA_ISR_P10_Msk                       (0x03UL << PCA_ISR_P10_Pos)                             /*!< PCA ISR: P10 Mask                       */
#define PCA_ISR_P11_Pos                       22                                                      /*!< PCA ISR: P11 Position                   */
#define PCA_ISR_P11_Msk                       (0x03UL << PCA_ISR_P11_Pos)                             /*!< PCA ISR: P11 Mask                       */
#define PCA_ISR_P12_Pos                       24                                                      /*!< PCA ISR: P12 Position                   */
#define PCA_ISR_P12_Msk                       (0x03UL << PCA_ISR_P12_Pos)                             /*!< PCA ISR: P12 Mask                       */
#define PCA_ISR_P13_Pos                       26                                                      /*!< PCA ISR: P13 Position                   */
#define PCA_ISR_P13_Msk                       (0x03UL << PCA_ISR_P13_Pos)                             /*!< PCA ISR: P13 Mask                       */
#define PCA_ISR_P14_Pos                       28                                                      /*!< PCA ISR: P14 Position                   */
#define PCA_ISR_P14_Msk                       (0x03UL << PCA_ISR_P14_Pos)                             /*!< PCA ISR: P14 Mask                       */
#define PCA_ISR_P15_Pos                       30                                                      /*!< PCA ISR: P15 Position                   */
#define PCA_ISR_P15_Msk                       (0x03UL << PCA_ISR_P15_Pos)                             /*!< PCA ISR: P15 Mask                       */

/* -----------------------------------  PCA_ICR  ---------------------------------- */
#define PCA_ICR_P0_Pos                        0                                                       /*!< PCA ICR: P0 Position                    */
#define PCA_ICR_P0_Msk                        (0x03UL << PCA_ICR_P0_Pos)                              /*!< PCA ICR: P0 Mask                        */
#define PCA_ICR_P1_Pos                        2                                                       /*!< PCA ICR: P1 Position                    */
#define PCA_ICR_P1_Msk                        (0x03UL << PCA_ICR_P1_Pos)                              /*!< PCA ICR: P1 Mask                        */
#define PCA_ICR_P2_Pos                        4                                                       /*!< PCA ICR: P2 Position                    */
#define PCA_ICR_P2_Msk                        (0x03UL << PCA_ICR_P2_Pos)                              /*!< PCA ICR: P2 Mask                        */
#define PCA_ICR_P3_Pos                        6                                                       /*!< PCA ICR: P3 Position                    */
#define PCA_ICR_P3_Msk                        (0x03UL << PCA_ICR_P3_Pos)                              /*!< PCA ICR: P3 Mask                        */
#define PCA_ICR_P4_Pos                        8                                                       /*!< PCA ICR: P4 Position                    */
#define PCA_ICR_P4_Msk                        (0x03UL << PCA_ICR_P4_Pos)                              /*!< PCA ICR: P4 Mask                        */
#define PCA_ICR_P5_Pos                        10                                                      /*!< PCA ICR: P5 Position                    */
#define PCA_ICR_P5_Msk                        (0x03UL << PCA_ICR_P5_Pos)                              /*!< PCA ICR: P5 Mask                        */
#define PCA_ICR_P6_Pos                        12                                                      /*!< PCA ICR: P6 Position                    */
#define PCA_ICR_P6_Msk                        (0x03UL << PCA_ICR_P6_Pos)                              /*!< PCA ICR: P6 Mask                        */
#define PCA_ICR_P7_Pos                        14                                                      /*!< PCA ICR: P7 Position                    */
#define PCA_ICR_P7_Msk                        (0x03UL << PCA_ICR_P7_Pos)                              /*!< PCA ICR: P7 Mask                        */
#define PCA_ICR_P8_Pos                        16                                                      /*!< PCA ICR: P8 Position                    */
#define PCA_ICR_P8_Msk                        (0x03UL << PCA_ICR_P8_Pos)                              /*!< PCA ICR: P8 Mask                        */
#define PCA_ICR_P9_Pos                        18                                                      /*!< PCA ICR: P9 Position                    */
#define PCA_ICR_P9_Msk                        (0x03UL << PCA_ICR_P9_Pos)                              /*!< PCA ICR: P9 Mask                        */
#define PCA_ICR_P10_Pos                       20                                                      /*!< PCA ICR: P10 Position                   */
#define PCA_ICR_P10_Msk                       (0x03UL << PCA_ICR_P10_Pos)                             /*!< PCA ICR: P10 Mask                       */
#define PCA_ICR_P11_Pos                       22                                                      /*!< PCA ICR: P11 Position                   */
#define PCA_ICR_P11_Msk                       (0x03UL << PCA_ICR_P11_Pos)                             /*!< PCA ICR: P11 Mask                       */
#define PCA_ICR_P12_Pos                       24                                                      /*!< PCA ICR: P12 Position                   */
#define PCA_ICR_P12_Msk                       (0x03UL << PCA_ICR_P12_Pos)                             /*!< PCA ICR: P12 Mask                       */
#define PCA_ICR_P13_Pos                       26                                                      /*!< PCA ICR: P13 Position                   */
#define PCA_ICR_P13_Msk                       (0x03UL << PCA_ICR_P13_Pos)                             /*!< PCA ICR: P13 Mask                       */
#define PCA_ICR_P14_Pos                       28                                                      /*!< PCA ICR: P14 Position                   */
#define PCA_ICR_P14_Msk                       (0x03UL << PCA_ICR_P14_Pos)                             /*!< PCA ICR: P14 Mask                       */
#define PCA_ICR_P15_Pos                       30                                                      /*!< PCA ICR: P15 Position                   */
#define PCA_ICR_P15_Msk                       (0x03UL << PCA_ICR_P15_Pos)                             /*!< PCA ICR: P15 Mask                       */

/* -----------------------------------  PCA_DPR  ---------------------------------- */
#define PCA_DPR_DPR_Pos                       0                                                       /*!< PCA DPR: DPR Position                   */
#define PCA_DPR_DPR_Msk                       (0x1fUL << PCA_DPR_DPR_Pos)                             /*!< PCA DPR: DPR Mask                       */


/* ================================================================================ */
/* ================          struct 'PCB' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  PCB_MR  ----------------------------------- */
#define PCB_MR_P0_Pos                         0                                                       /*!< PCB MR: P0 Position                     */
#define PCB_MR_P0_Msk                         (0x03UL << PCB_MR_P0_Pos)                               /*!< PCB MR: P0 Mask                         */
#define PCB_MR_P1_Pos                         2                                                       /*!< PCB MR: P1 Position                     */
#define PCB_MR_P1_Msk                         (0x03UL << PCB_MR_P1_Pos)                               /*!< PCB MR: P1 Mask                         */
#define PCB_MR_P2_Pos                         4                                                       /*!< PCB MR: P2 Position                     */
#define PCB_MR_P2_Msk                         (0x03UL << PCB_MR_P2_Pos)                               /*!< PCB MR: P2 Mask                         */
#define PCB_MR_P3_Pos                         6                                                       /*!< PCB MR: P3 Position                     */
#define PCB_MR_P3_Msk                         (0x03UL << PCB_MR_P3_Pos)                               /*!< PCB MR: P3 Mask                         */
#define PCB_MR_P4_Pos                         8                                                       /*!< PCB MR: P4 Position                     */
#define PCB_MR_P4_Msk                         (0x03UL << PCB_MR_P4_Pos)                               /*!< PCB MR: P4 Mask                         */
#define PCB_MR_P5_Pos                         10                                                      /*!< PCB MR: P5 Position                     */
#define PCB_MR_P5_Msk                         (0x03UL << PCB_MR_P5_Pos)                               /*!< PCB MR: P5 Mask                         */
#define PCB_MR_P6_Pos                         12                                                      /*!< PCB MR: P6 Position                     */
#define PCB_MR_P6_Msk                         (0x03UL << PCB_MR_P6_Pos)                               /*!< PCB MR: P6 Mask                         */
#define PCB_MR_P7_Pos                         14                                                      /*!< PCB MR: P7 Position                     */
#define PCB_MR_P7_Msk                         (0x03UL << PCB_MR_P7_Pos)                               /*!< PCB MR: P7 Mask                         */
#define PCB_MR_P8_Pos                         16                                                      /*!< PCB MR: P8 Position                     */
#define PCB_MR_P8_Msk                         (0x03UL << PCB_MR_P8_Pos)                               /*!< PCB MR: P8 Mask                         */
#define PCB_MR_P9_Pos                         18                                                      /*!< PCB MR: P9 Position                     */
#define PCB_MR_P9_Msk                         (0x03UL << PCB_MR_P9_Pos)                               /*!< PCB MR: P9 Mask                         */
#define PCB_MR_P10_Pos                        20                                                      /*!< PCB MR: P10 Position                    */
#define PCB_MR_P10_Msk                        (0x03UL << PCB_MR_P10_Pos)                              /*!< PCB MR: P10 Mask                        */
#define PCB_MR_P11_Pos                        22                                                      /*!< PCB MR: P11 Position                    */
#define PCB_MR_P11_Msk                        (0x03UL << PCB_MR_P11_Pos)                              /*!< PCB MR: P11 Mask                        */
#define PCB_MR_P12_Pos                        24                                                      /*!< PCB MR: P12 Position                    */
#define PCB_MR_P12_Msk                        (0x03UL << PCB_MR_P12_Pos)                              /*!< PCB MR: P12 Mask                        */
#define PCB_MR_P13_Pos                        26                                                      /*!< PCB MR: P13 Position                    */
#define PCB_MR_P13_Msk                        (0x03UL << PCB_MR_P13_Pos)                              /*!< PCB MR: P13 Mask                        */
#define PCB_MR_P14_Pos                        28                                                      /*!< PCB MR: P14 Position                    */
#define PCB_MR_P14_Msk                        (0x03UL << PCB_MR_P14_Pos)                              /*!< PCB MR: P14 Mask                        */
#define PCB_MR_P15_Pos                        30                                                      /*!< PCB MR: P15 Position                    */
#define PCB_MR_P15_Msk                        (0x03UL << PCB_MR_P15_Pos)                              /*!< PCB MR: P15 Mask                        */

/* -----------------------------------  PCB_CR  ----------------------------------- */
#define PCB_CR_P0_Pos                         0                                                       /*!< PCB CR: P0 Position                     */
#define PCB_CR_P0_Msk                         (0x03UL << PCB_CR_P0_Pos)                               /*!< PCB CR: P0 Mask                         */
#define PCB_CR_P1_Pos                         2                                                       /*!< PCB CR: P1 Position                     */
#define PCB_CR_P1_Msk                         (0x03UL << PCB_CR_P1_Pos)                               /*!< PCB CR: P1 Mask                         */
#define PCB_CR_P2_Pos                         4                                                       /*!< PCB CR: P2 Position                     */
#define PCB_CR_P2_Msk                         (0x03UL << PCB_CR_P2_Pos)                               /*!< PCB CR: P2 Mask                         */
#define PCB_CR_P3_Pos                         6                                                       /*!< PCB CR: P3 Position                     */
#define PCB_CR_P3_Msk                         (0x03UL << PCB_CR_P3_Pos)                               /*!< PCB CR: P3 Mask                         */
#define PCB_CR_P4_Pos                         8                                                       /*!< PCB CR: P4 Position                     */
#define PCB_CR_P4_Msk                         (0x03UL << PCB_CR_P4_Pos)                               /*!< PCB CR: P4 Mask                         */
#define PCB_CR_P5_Pos                         10                                                      /*!< PCB CR: P5 Position                     */
#define PCB_CR_P5_Msk                         (0x03UL << PCB_CR_P5_Pos)                               /*!< PCB CR: P5 Mask                         */
#define PCB_CR_P6_Pos                         12                                                      /*!< PCB CR: P6 Position                     */
#define PCB_CR_P6_Msk                         (0x03UL << PCB_CR_P6_Pos)                               /*!< PCB CR: P6 Mask                         */
#define PCB_CR_P7_Pos                         14                                                      /*!< PCB CR: P7 Position                     */
#define PCB_CR_P7_Msk                         (0x03UL << PCB_CR_P7_Pos)                               /*!< PCB CR: P7 Mask                         */
#define PCB_CR_P8_Pos                         16                                                      /*!< PCB CR: P8 Position                     */
#define PCB_CR_P8_Msk                         (0x03UL << PCB_CR_P8_Pos)                               /*!< PCB CR: P8 Mask                         */
#define PCB_CR_P9_Pos                         18                                                      /*!< PCB CR: P9 Position                     */
#define PCB_CR_P9_Msk                         (0x03UL << PCB_CR_P9_Pos)                               /*!< PCB CR: P9 Mask                         */
#define PCB_CR_P10_Pos                        20                                                      /*!< PCB CR: P10 Position                    */
#define PCB_CR_P10_Msk                        (0x03UL << PCB_CR_P10_Pos)                              /*!< PCB CR: P10 Mask                        */
#define PCB_CR_P11_Pos                        22                                                      /*!< PCB CR: P11 Position                    */
#define PCB_CR_P11_Msk                        (0x03UL << PCB_CR_P11_Pos)                              /*!< PCB CR: P11 Mask                        */
#define PCB_CR_P12_Pos                        24                                                      /*!< PCB CR: P12 Position                    */
#define PCB_CR_P12_Msk                        (0x03UL << PCB_CR_P12_Pos)                              /*!< PCB CR: P12 Mask                        */
#define PCB_CR_P13_Pos                        26                                                      /*!< PCB CR: P13 Position                    */
#define PCB_CR_P13_Msk                        (0x03UL << PCB_CR_P13_Pos)                              /*!< PCB CR: P13 Mask                        */
#define PCB_CR_P14_Pos                        28                                                      /*!< PCB CR: P14 Position                    */
#define PCB_CR_P14_Msk                        (0x03UL << PCB_CR_P14_Pos)                              /*!< PCB CR: P14 Mask                        */
#define PCB_CR_P15_Pos                        30                                                      /*!< PCB CR: P15 Position                    */
#define PCB_CR_P15_Msk                        (0x03UL << PCB_CR_P15_Pos)                              /*!< PCB CR: P15 Mask                        */

/* -----------------------------------  PCB_PCR  ---------------------------------- */
#define PCB_PCR_P0_Pos                        0                                                       /*!< PCB PCR: P0 Position                    */
#define PCB_PCR_P0_Msk                        (0x01UL << PCB_PCR_P0_Pos)                              /*!< PCB PCR: P0 Mask                        */
#define PCB_PCR_P1_Pos                        1                                                       /*!< PCB PCR: P1 Position                    */
#define PCB_PCR_P1_Msk                        (0x01UL << PCB_PCR_P1_Pos)                              /*!< PCB PCR: P1 Mask                        */
#define PCB_PCR_P2_Pos                        2                                                       /*!< PCB PCR: P2 Position                    */
#define PCB_PCR_P2_Msk                        (0x01UL << PCB_PCR_P2_Pos)                              /*!< PCB PCR: P2 Mask                        */
#define PCB_PCR_P3_Pos                        3                                                       /*!< PCB PCR: P3 Position                    */
#define PCB_PCR_P3_Msk                        (0x01UL << PCB_PCR_P3_Pos)                              /*!< PCB PCR: P3 Mask                        */
#define PCB_PCR_P4_Pos                        4                                                       /*!< PCB PCR: P4 Position                    */
#define PCB_PCR_P4_Msk                        (0x01UL << PCB_PCR_P4_Pos)                              /*!< PCB PCR: P4 Mask                        */
#define PCB_PCR_P5_Pos                        5                                                       /*!< PCB PCR: P5 Position                    */
#define PCB_PCR_P5_Msk                        (0x01UL << PCB_PCR_P5_Pos)                              /*!< PCB PCR: P5 Mask                        */
#define PCB_PCR_P6_Pos                        6                                                       /*!< PCB PCR: P6 Position                    */
#define PCB_PCR_P6_Msk                        (0x01UL << PCB_PCR_P6_Pos)                              /*!< PCB PCR: P6 Mask                        */
#define PCB_PCR_P7_Pos                        7                                                       /*!< PCB PCR: P7 Position                    */
#define PCB_PCR_P7_Msk                        (0x01UL << PCB_PCR_P7_Pos)                              /*!< PCB PCR: P7 Mask                        */
#define PCB_PCR_P8_Pos                        8                                                       /*!< PCB PCR: P8 Position                    */
#define PCB_PCR_P8_Msk                        (0x01UL << PCB_PCR_P8_Pos)                              /*!< PCB PCR: P8 Mask                        */
#define PCB_PCR_P9_Pos                        9                                                       /*!< PCB PCR: P9 Position                    */
#define PCB_PCR_P9_Msk                        (0x01UL << PCB_PCR_P9_Pos)                              /*!< PCB PCR: P9 Mask                        */
#define PCB_PCR_P10_Pos                       10                                                      /*!< PCB PCR: P10 Position                   */
#define PCB_PCR_P10_Msk                       (0x01UL << PCB_PCR_P10_Pos)                             /*!< PCB PCR: P10 Mask                       */
#define PCB_PCR_P11_Pos                       11                                                      /*!< PCB PCR: P11 Position                   */
#define PCB_PCR_P11_Msk                       (0x01UL << PCB_PCR_P11_Pos)                             /*!< PCB PCR: P11 Mask                       */
#define PCB_PCR_P12_Pos                       12                                                      /*!< PCB PCR: P12 Position                   */
#define PCB_PCR_P12_Msk                       (0x01UL << PCB_PCR_P12_Pos)                             /*!< PCB PCR: P12 Mask                       */
#define PCB_PCR_P13_Pos                       13                                                      /*!< PCB PCR: P13 Position                   */
#define PCB_PCR_P13_Msk                       (0x01UL << PCB_PCR_P13_Pos)                             /*!< PCB PCR: P13 Mask                       */
#define PCB_PCR_P14_Pos                       14                                                      /*!< PCB PCR: P14 Position                   */
#define PCB_PCR_P14_Msk                       (0x01UL << PCB_PCR_P14_Pos)                             /*!< PCB PCR: P14 Mask                       */
#define PCB_PCR_P15_Pos                       15                                                      /*!< PCB PCR: P15 Position                   */
#define PCB_PCR_P15_Msk                       (0x01UL << PCB_PCR_P15_Pos)                             /*!< PCB PCR: P15 Mask                       */
#define PCB_PCR_D0_Pos                        16                                                      /*!< PCB PCR: D0 Position                    */
#define PCB_PCR_D0_Msk                        (0x01UL << PCB_PCR_D0_Pos)                              /*!< PCB PCR: D0 Mask                        */
#define PCB_PCR_D1_Pos                        17                                                      /*!< PCB PCR: D1 Position                    */
#define PCB_PCR_D1_Msk                        (0x01UL << PCB_PCR_D1_Pos)                              /*!< PCB PCR: D1 Mask                        */
#define PCB_PCR_D2_Pos                        18                                                      /*!< PCB PCR: D2 Position                    */
#define PCB_PCR_D2_Msk                        (0x01UL << PCB_PCR_D2_Pos)                              /*!< PCB PCR: D2 Mask                        */
#define PCB_PCR_D3_Pos                        19                                                      /*!< PCB PCR: D3 Position                    */
#define PCB_PCR_D3_Msk                        (0x01UL << PCB_PCR_D3_Pos)                              /*!< PCB PCR: D3 Mask                        */
#define PCB_PCR_D4_Pos                        20                                                      /*!< PCB PCR: D4 Position                    */
#define PCB_PCR_D4_Msk                        (0x01UL << PCB_PCR_D4_Pos)                              /*!< PCB PCR: D4 Mask                        */
#define PCB_PCR_D5_Pos                        21                                                      /*!< PCB PCR: D5 Position                    */
#define PCB_PCR_D5_Msk                        (0x01UL << PCB_PCR_D5_Pos)                              /*!< PCB PCR: D5 Mask                        */
#define PCB_PCR_D6_Pos                        22                                                      /*!< PCB PCR: D6 Position                    */
#define PCB_PCR_D6_Msk                        (0x01UL << PCB_PCR_D6_Pos)                              /*!< PCB PCR: D6 Mask                        */
#define PCB_PCR_D7_Pos                        23                                                      /*!< PCB PCR: D7 Position                    */
#define PCB_PCR_D7_Msk                        (0x01UL << PCB_PCR_D7_Pos)                              /*!< PCB PCR: D7 Mask                        */
#define PCB_PCR_D8_Pos                        24                                                      /*!< PCB PCR: D8 Position                    */
#define PCB_PCR_D8_Msk                        (0x01UL << PCB_PCR_D8_Pos)                              /*!< PCB PCR: D8 Mask                        */
#define PCB_PCR_D9_Pos                        25                                                      /*!< PCB PCR: D9 Position                    */
#define PCB_PCR_D9_Msk                        (0x01UL << PCB_PCR_D9_Pos)                              /*!< PCB PCR: D9 Mask                        */
#define PCB_PCR_D10_Pos                       26                                                      /*!< PCB PCR: D10 Position                   */
#define PCB_PCR_D10_Msk                       (0x01UL << PCB_PCR_D10_Pos)                             /*!< PCB PCR: D10 Mask                       */
#define PCB_PCR_D11_Pos                       27                                                      /*!< PCB PCR: D11 Position                   */
#define PCB_PCR_D11_Msk                       (0x01UL << PCB_PCR_D11_Pos)                             /*!< PCB PCR: D11 Mask                       */
#define PCB_PCR_D12_Pos                       28                                                      /*!< PCB PCR: D12 Position                   */
#define PCB_PCR_D12_Msk                       (0x01UL << PCB_PCR_D12_Pos)                             /*!< PCB PCR: D12 Mask                       */
#define PCB_PCR_D13_Pos                       29                                                      /*!< PCB PCR: D13 Position                   */
#define PCB_PCR_D13_Msk                       (0x01UL << PCB_PCR_D13_Pos)                             /*!< PCB PCR: D13 Mask                       */
#define PCB_PCR_D14_Pos                       30                                                      /*!< PCB PCR: D14 Position                   */
#define PCB_PCR_D14_Msk                       (0x01UL << PCB_PCR_D14_Pos)                             /*!< PCB PCR: D14 Mask                       */
#define PCB_PCR_D15_Pos                       31                                                      /*!< PCB PCR: D15 Position                   */
#define PCB_PCR_D15_Msk                       (0x01UL << PCB_PCR_D15_Pos)                             /*!< PCB PCR: D15 Mask                       */

/* -----------------------------------  PCB_DER  ---------------------------------- */
#define PCB_DER_P0_Pos                        0                                                       /*!< PCB DER: P0 Position                    */
#define PCB_DER_P0_Msk                        (0x01UL << PCB_DER_P0_Pos)                              /*!< PCB DER: P0 Mask                        */
#define PCB_DER_P1_Pos                        1                                                       /*!< PCB DER: P1 Position                    */
#define PCB_DER_P1_Msk                        (0x01UL << PCB_DER_P1_Pos)                              /*!< PCB DER: P1 Mask                        */
#define PCB_DER_P2_Pos                        2                                                       /*!< PCB DER: P2 Position                    */
#define PCB_DER_P2_Msk                        (0x01UL << PCB_DER_P2_Pos)                              /*!< PCB DER: P2 Mask                        */
#define PCB_DER_P3_Pos                        3                                                       /*!< PCB DER: P3 Position                    */
#define PCB_DER_P3_Msk                        (0x01UL << PCB_DER_P3_Pos)                              /*!< PCB DER: P3 Mask                        */
#define PCB_DER_P4_Pos                        4                                                       /*!< PCB DER: P4 Position                    */
#define PCB_DER_P4_Msk                        (0x01UL << PCB_DER_P4_Pos)                              /*!< PCB DER: P4 Mask                        */
#define PCB_DER_P5_Pos                        5                                                       /*!< PCB DER: P5 Position                    */
#define PCB_DER_P5_Msk                        (0x01UL << PCB_DER_P5_Pos)                              /*!< PCB DER: P5 Mask                        */
#define PCB_DER_P6_Pos                        6                                                       /*!< PCB DER: P6 Position                    */
#define PCB_DER_P6_Msk                        (0x01UL << PCB_DER_P6_Pos)                              /*!< PCB DER: P6 Mask                        */
#define PCB_DER_P7_Pos                        7                                                       /*!< PCB DER: P7 Position                    */
#define PCB_DER_P7_Msk                        (0x01UL << PCB_DER_P7_Pos)                              /*!< PCB DER: P7 Mask                        */
#define PCB_DER_P8_Pos                        8                                                       /*!< PCB DER: P8 Position                    */
#define PCB_DER_P8_Msk                        (0x01UL << PCB_DER_P8_Pos)                              /*!< PCB DER: P8 Mask                        */
#define PCB_DER_P9_Pos                        9                                                       /*!< PCB DER: P9 Position                    */
#define PCB_DER_P9_Msk                        (0x01UL << PCB_DER_P9_Pos)                              /*!< PCB DER: P9 Mask                        */
#define PCB_DER_P10_Pos                       10                                                      /*!< PCB DER: P10 Position                   */
#define PCB_DER_P10_Msk                       (0x01UL << PCB_DER_P10_Pos)                             /*!< PCB DER: P10 Mask                       */
#define PCB_DER_P11_Pos                       11                                                      /*!< PCB DER: P11 Position                   */
#define PCB_DER_P11_Msk                       (0x01UL << PCB_DER_P11_Pos)                             /*!< PCB DER: P11 Mask                       */
#define PCB_DER_P12_Pos                       12                                                      /*!< PCB DER: P12 Position                   */
#define PCB_DER_P12_Msk                       (0x01UL << PCB_DER_P12_Pos)                             /*!< PCB DER: P12 Mask                       */
#define PCB_DER_P13_Pos                       13                                                      /*!< PCB DER: P13 Position                   */
#define PCB_DER_P13_Msk                       (0x01UL << PCB_DER_P13_Pos)                             /*!< PCB DER: P13 Mask                       */
#define PCB_DER_P14_Pos                       14                                                      /*!< PCB DER: P14 Position                   */
#define PCB_DER_P14_Msk                       (0x01UL << PCB_DER_P14_Pos)                             /*!< PCB DER: P14 Mask                       */
#define PCB_DER_P15_Pos                       15                                                      /*!< PCB DER: P15 Position                   */
#define PCB_DER_P15_Msk                       (0x01UL << PCB_DER_P15_Pos)                             /*!< PCB DER: P15 Mask                       */

/* -----------------------------------  PCB_IER  ---------------------------------- */
#define PCB_IER_P0_Pos                        0                                                       /*!< PCB IER: P0 Position                    */
#define PCB_IER_P0_Msk                        (0x03UL << PCB_IER_P0_Pos)                              /*!< PCB IER: P0 Mask                        */
#define PCB_IER_P1_Pos                        2                                                       /*!< PCB IER: P1 Position                    */
#define PCB_IER_P1_Msk                        (0x03UL << PCB_IER_P1_Pos)                              /*!< PCB IER: P1 Mask                        */
#define PCB_IER_P2_Pos                        4                                                       /*!< PCB IER: P2 Position                    */
#define PCB_IER_P2_Msk                        (0x03UL << PCB_IER_P2_Pos)                              /*!< PCB IER: P2 Mask                        */
#define PCB_IER_P3_Pos                        6                                                       /*!< PCB IER: P3 Position                    */
#define PCB_IER_P3_Msk                        (0x03UL << PCB_IER_P3_Pos)                              /*!< PCB IER: P3 Mask                        */
#define PCB_IER_P4_Pos                        8                                                       /*!< PCB IER: P4 Position                    */
#define PCB_IER_P4_Msk                        (0x03UL << PCB_IER_P4_Pos)                              /*!< PCB IER: P4 Mask                        */
#define PCB_IER_P5_Pos                        10                                                      /*!< PCB IER: P5 Position                    */
#define PCB_IER_P5_Msk                        (0x03UL << PCB_IER_P5_Pos)                              /*!< PCB IER: P5 Mask                        */
#define PCB_IER_P6_Pos                        12                                                      /*!< PCB IER: P6 Position                    */
#define PCB_IER_P6_Msk                        (0x03UL << PCB_IER_P6_Pos)                              /*!< PCB IER: P6 Mask                        */
#define PCB_IER_P7_Pos                        14                                                      /*!< PCB IER: P7 Position                    */
#define PCB_IER_P7_Msk                        (0x03UL << PCB_IER_P7_Pos)                              /*!< PCB IER: P7 Mask                        */
#define PCB_IER_P8_Pos                        16                                                      /*!< PCB IER: P8 Position                    */
#define PCB_IER_P8_Msk                        (0x03UL << PCB_IER_P8_Pos)                              /*!< PCB IER: P8 Mask                        */
#define PCB_IER_P9_Pos                        18                                                      /*!< PCB IER: P9 Position                    */
#define PCB_IER_P9_Msk                        (0x03UL << PCB_IER_P9_Pos)                              /*!< PCB IER: P9 Mask                        */
#define PCB_IER_P10_Pos                       20                                                      /*!< PCB IER: P10 Position                   */
#define PCB_IER_P10_Msk                       (0x03UL << PCB_IER_P10_Pos)                             /*!< PCB IER: P10 Mask                       */
#define PCB_IER_P11_Pos                       22                                                      /*!< PCB IER: P11 Position                   */
#define PCB_IER_P11_Msk                       (0x03UL << PCB_IER_P11_Pos)                             /*!< PCB IER: P11 Mask                       */
#define PCB_IER_P12_Pos                       24                                                      /*!< PCB IER: P12 Position                   */
#define PCB_IER_P12_Msk                       (0x03UL << PCB_IER_P12_Pos)                             /*!< PCB IER: P12 Mask                       */
#define PCB_IER_P13_Pos                       26                                                      /*!< PCB IER: P13 Position                   */
#define PCB_IER_P13_Msk                       (0x03UL << PCB_IER_P13_Pos)                             /*!< PCB IER: P13 Mask                       */
#define PCB_IER_P14_Pos                       28                                                      /*!< PCB IER: P14 Position                   */
#define PCB_IER_P14_Msk                       (0x03UL << PCB_IER_P14_Pos)                             /*!< PCB IER: P14 Mask                       */
#define PCB_IER_P15_Pos                       30                                                      /*!< PCB IER: P15 Position                   */
#define PCB_IER_P15_Msk                       (0x03UL << PCB_IER_P15_Pos)                             /*!< PCB IER: P15 Mask                       */

/* -----------------------------------  PCB_ISR  ---------------------------------- */
#define PCB_ISR_P0_Pos                        0                                                       /*!< PCB ISR: P0 Position                    */
#define PCB_ISR_P0_Msk                        (0x03UL << PCB_ISR_P0_Pos)                              /*!< PCB ISR: P0 Mask                        */
#define PCB_ISR_P1_Pos                        2                                                       /*!< PCB ISR: P1 Position                    */
#define PCB_ISR_P1_Msk                        (0x03UL << PCB_ISR_P1_Pos)                              /*!< PCB ISR: P1 Mask                        */
#define PCB_ISR_P2_Pos                        4                                                       /*!< PCB ISR: P2 Position                    */
#define PCB_ISR_P2_Msk                        (0x03UL << PCB_ISR_P2_Pos)                              /*!< PCB ISR: P2 Mask                        */
#define PCB_ISR_P3_Pos                        6                                                       /*!< PCB ISR: P3 Position                    */
#define PCB_ISR_P3_Msk                        (0x03UL << PCB_ISR_P3_Pos)                              /*!< PCB ISR: P3 Mask                        */
#define PCB_ISR_P4_Pos                        8                                                       /*!< PCB ISR: P4 Position                    */
#define PCB_ISR_P4_Msk                        (0x03UL << PCB_ISR_P4_Pos)                              /*!< PCB ISR: P4 Mask                        */
#define PCB_ISR_P5_Pos                        10                                                      /*!< PCB ISR: P5 Position                    */
#define PCB_ISR_P5_Msk                        (0x03UL << PCB_ISR_P5_Pos)                              /*!< PCB ISR: P5 Mask                        */
#define PCB_ISR_P6_Pos                        12                                                      /*!< PCB ISR: P6 Position                    */
#define PCB_ISR_P6_Msk                        (0x03UL << PCB_ISR_P6_Pos)                              /*!< PCB ISR: P6 Mask                        */
#define PCB_ISR_P7_Pos                        14                                                      /*!< PCB ISR: P7 Position                    */
#define PCB_ISR_P7_Msk                        (0x03UL << PCB_ISR_P7_Pos)                              /*!< PCB ISR: P7 Mask                        */
#define PCB_ISR_P8_Pos                        16                                                      /*!< PCB ISR: P8 Position                    */
#define PCB_ISR_P8_Msk                        (0x03UL << PCB_ISR_P8_Pos)                              /*!< PCB ISR: P8 Mask                        */
#define PCB_ISR_P9_Pos                        18                                                      /*!< PCB ISR: P9 Position                    */
#define PCB_ISR_P9_Msk                        (0x03UL << PCB_ISR_P9_Pos)                              /*!< PCB ISR: P9 Mask                        */
#define PCB_ISR_P10_Pos                       20                                                      /*!< PCB ISR: P10 Position                   */
#define PCB_ISR_P10_Msk                       (0x03UL << PCB_ISR_P10_Pos)                             /*!< PCB ISR: P10 Mask                       */
#define PCB_ISR_P11_Pos                       22                                                      /*!< PCB ISR: P11 Position                   */
#define PCB_ISR_P11_Msk                       (0x03UL << PCB_ISR_P11_Pos)                             /*!< PCB ISR: P11 Mask                       */
#define PCB_ISR_P12_Pos                       24                                                      /*!< PCB ISR: P12 Position                   */
#define PCB_ISR_P12_Msk                       (0x03UL << PCB_ISR_P12_Pos)                             /*!< PCB ISR: P12 Mask                       */
#define PCB_ISR_P13_Pos                       26                                                      /*!< PCB ISR: P13 Position                   */
#define PCB_ISR_P13_Msk                       (0x03UL << PCB_ISR_P13_Pos)                             /*!< PCB ISR: P13 Mask                       */
#define PCB_ISR_P14_Pos                       28                                                      /*!< PCB ISR: P14 Position                   */
#define PCB_ISR_P14_Msk                       (0x03UL << PCB_ISR_P14_Pos)                             /*!< PCB ISR: P14 Mask                       */
#define PCB_ISR_P15_Pos                       30                                                      /*!< PCB ISR: P15 Position                   */
#define PCB_ISR_P15_Msk                       (0x03UL << PCB_ISR_P15_Pos)                             /*!< PCB ISR: P15 Mask                       */

/* -----------------------------------  PCB_ICR  ---------------------------------- */
#define PCB_ICR_P0_Pos                        0                                                       /*!< PCB ICR: P0 Position                    */
#define PCB_ICR_P0_Msk                        (0x03UL << PCB_ICR_P0_Pos)                              /*!< PCB ICR: P0 Mask                        */
#define PCB_ICR_P1_Pos                        2                                                       /*!< PCB ICR: P1 Position                    */
#define PCB_ICR_P1_Msk                        (0x03UL << PCB_ICR_P1_Pos)                              /*!< PCB ICR: P1 Mask                        */
#define PCB_ICR_P2_Pos                        4                                                       /*!< PCB ICR: P2 Position                    */
#define PCB_ICR_P2_Msk                        (0x03UL << PCB_ICR_P2_Pos)                              /*!< PCB ICR: P2 Mask                        */
#define PCB_ICR_P3_Pos                        6                                                       /*!< PCB ICR: P3 Position                    */
#define PCB_ICR_P3_Msk                        (0x03UL << PCB_ICR_P3_Pos)                              /*!< PCB ICR: P3 Mask                        */
#define PCB_ICR_P4_Pos                        8                                                       /*!< PCB ICR: P4 Position                    */
#define PCB_ICR_P4_Msk                        (0x03UL << PCB_ICR_P4_Pos)                              /*!< PCB ICR: P4 Mask                        */
#define PCB_ICR_P5_Pos                        10                                                      /*!< PCB ICR: P5 Position                    */
#define PCB_ICR_P5_Msk                        (0x03UL << PCB_ICR_P5_Pos)                              /*!< PCB ICR: P5 Mask                        */
#define PCB_ICR_P6_Pos                        12                                                      /*!< PCB ICR: P6 Position                    */
#define PCB_ICR_P6_Msk                        (0x03UL << PCB_ICR_P6_Pos)                              /*!< PCB ICR: P6 Mask                        */
#define PCB_ICR_P7_Pos                        14                                                      /*!< PCB ICR: P7 Position                    */
#define PCB_ICR_P7_Msk                        (0x03UL << PCB_ICR_P7_Pos)                              /*!< PCB ICR: P7 Mask                        */
#define PCB_ICR_P8_Pos                        16                                                      /*!< PCB ICR: P8 Position                    */
#define PCB_ICR_P8_Msk                        (0x03UL << PCB_ICR_P8_Pos)                              /*!< PCB ICR: P8 Mask                        */
#define PCB_ICR_P9_Pos                        18                                                      /*!< PCB ICR: P9 Position                    */
#define PCB_ICR_P9_Msk                        (0x03UL << PCB_ICR_P9_Pos)                              /*!< PCB ICR: P9 Mask                        */
#define PCB_ICR_P10_Pos                       20                                                      /*!< PCB ICR: P10 Position                   */
#define PCB_ICR_P10_Msk                       (0x03UL << PCB_ICR_P10_Pos)                             /*!< PCB ICR: P10 Mask                       */
#define PCB_ICR_P11_Pos                       22                                                      /*!< PCB ICR: P11 Position                   */
#define PCB_ICR_P11_Msk                       (0x03UL << PCB_ICR_P11_Pos)                             /*!< PCB ICR: P11 Mask                       */
#define PCB_ICR_P12_Pos                       24                                                      /*!< PCB ICR: P12 Position                   */
#define PCB_ICR_P12_Msk                       (0x03UL << PCB_ICR_P12_Pos)                             /*!< PCB ICR: P12 Mask                       */
#define PCB_ICR_P13_Pos                       26                                                      /*!< PCB ICR: P13 Position                   */
#define PCB_ICR_P13_Msk                       (0x03UL << PCB_ICR_P13_Pos)                             /*!< PCB ICR: P13 Mask                       */
#define PCB_ICR_P14_Pos                       28                                                      /*!< PCB ICR: P14 Position                   */
#define PCB_ICR_P14_Msk                       (0x03UL << PCB_ICR_P14_Pos)                             /*!< PCB ICR: P14 Mask                       */
#define PCB_ICR_P15_Pos                       30                                                      /*!< PCB ICR: P15 Position                   */
#define PCB_ICR_P15_Msk                       (0x03UL << PCB_ICR_P15_Pos)                             /*!< PCB ICR: P15 Mask                       */

/* -----------------------------------  PCB_DPR  ---------------------------------- */
#define PCB_DPR_DPR_Pos                       0                                                       /*!< PCB DPR: DPR Position                   */
#define PCB_DPR_DPR_Msk                       (0x1fUL << PCB_DPR_DPR_Pos)                             /*!< PCB DPR: DPR Mask                       */


/* ================================================================================ */
/* ================          struct 'PCC' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  PCC_MR  ----------------------------------- */
#define PCC_MR_P0_Pos                         0                                                       /*!< PCC MR: P0 Position                     */
#define PCC_MR_P0_Msk                         (0x03UL << PCC_MR_P0_Pos)                               /*!< PCC MR: P0 Mask                         */
#define PCC_MR_P1_Pos                         2                                                       /*!< PCC MR: P1 Position                     */
#define PCC_MR_P1_Msk                         (0x03UL << PCC_MR_P1_Pos)                               /*!< PCC MR: P1 Mask                         */
#define PCC_MR_P2_Pos                         4                                                       /*!< PCC MR: P2 Position                     */
#define PCC_MR_P2_Msk                         (0x03UL << PCC_MR_P2_Pos)                               /*!< PCC MR: P2 Mask                         */
#define PCC_MR_P3_Pos                         6                                                       /*!< PCC MR: P3 Position                     */
#define PCC_MR_P3_Msk                         (0x03UL << PCC_MR_P3_Pos)                               /*!< PCC MR: P3 Mask                         */
#define PCC_MR_P4_Pos                         8                                                       /*!< PCC MR: P4 Position                     */
#define PCC_MR_P4_Msk                         (0x03UL << PCC_MR_P4_Pos)                               /*!< PCC MR: P4 Mask                         */
#define PCC_MR_P5_Pos                         10                                                      /*!< PCC MR: P5 Position                     */
#define PCC_MR_P5_Msk                         (0x03UL << PCC_MR_P5_Pos)                               /*!< PCC MR: P5 Mask                         */
#define PCC_MR_P6_Pos                         12                                                      /*!< PCC MR: P6 Position                     */
#define PCC_MR_P6_Msk                         (0x03UL << PCC_MR_P6_Pos)                               /*!< PCC MR: P6 Mask                         */
#define PCC_MR_P7_Pos                         14                                                      /*!< PCC MR: P7 Position                     */
#define PCC_MR_P7_Msk                         (0x03UL << PCC_MR_P7_Pos)                               /*!< PCC MR: P7 Mask                         */
#define PCC_MR_P8_Pos                         16                                                      /*!< PCC MR: P8 Position                     */
#define PCC_MR_P8_Msk                         (0x03UL << PCC_MR_P8_Pos)                               /*!< PCC MR: P8 Mask                         */
#define PCC_MR_P9_Pos                         18                                                      /*!< PCC MR: P9 Position                     */
#define PCC_MR_P9_Msk                         (0x03UL << PCC_MR_P9_Pos)                               /*!< PCC MR: P9 Mask                         */
#define PCC_MR_P10_Pos                        20                                                      /*!< PCC MR: P10 Position                    */
#define PCC_MR_P10_Msk                        (0x03UL << PCC_MR_P10_Pos)                              /*!< PCC MR: P10 Mask                        */
#define PCC_MR_P11_Pos                        22                                                      /*!< PCC MR: P11 Position                    */
#define PCC_MR_P11_Msk                        (0x03UL << PCC_MR_P11_Pos)                              /*!< PCC MR: P11 Mask                        */
#define PCC_MR_P12_Pos                        24                                                      /*!< PCC MR: P12 Position                    */
#define PCC_MR_P12_Msk                        (0x03UL << PCC_MR_P12_Pos)                              /*!< PCC MR: P12 Mask                        */
#define PCC_MR_P13_Pos                        26                                                      /*!< PCC MR: P13 Position                    */
#define PCC_MR_P13_Msk                        (0x03UL << PCC_MR_P13_Pos)                              /*!< PCC MR: P13 Mask                        */
#define PCC_MR_P14_Pos                        28                                                      /*!< PCC MR: P14 Position                    */
#define PCC_MR_P14_Msk                        (0x03UL << PCC_MR_P14_Pos)                              /*!< PCC MR: P14 Mask                        */
#define PCC_MR_P15_Pos                        30                                                      /*!< PCC MR: P15 Position                    */
#define PCC_MR_P15_Msk                        (0x03UL << PCC_MR_P15_Pos)                              /*!< PCC MR: P15 Mask                        */

/* -----------------------------------  PCC_CR  ----------------------------------- */
#define PCC_CR_P0_Pos                         0                                                       /*!< PCC CR: P0 Position                     */
#define PCC_CR_P0_Msk                         (0x03UL << PCC_CR_P0_Pos)                               /*!< PCC CR: P0 Mask                         */
#define PCC_CR_P1_Pos                         2                                                       /*!< PCC CR: P1 Position                     */
#define PCC_CR_P1_Msk                         (0x03UL << PCC_CR_P1_Pos)                               /*!< PCC CR: P1 Mask                         */
#define PCC_CR_P2_Pos                         4                                                       /*!< PCC CR: P2 Position                     */
#define PCC_CR_P2_Msk                         (0x03UL << PCC_CR_P2_Pos)                               /*!< PCC CR: P2 Mask                         */
#define PCC_CR_P3_Pos                         6                                                       /*!< PCC CR: P3 Position                     */
#define PCC_CR_P3_Msk                         (0x03UL << PCC_CR_P3_Pos)                               /*!< PCC CR: P3 Mask                         */
#define PCC_CR_P4_Pos                         8                                                       /*!< PCC CR: P4 Position                     */
#define PCC_CR_P4_Msk                         (0x03UL << PCC_CR_P4_Pos)                               /*!< PCC CR: P4 Mask                         */
#define PCC_CR_P5_Pos                         10                                                      /*!< PCC CR: P5 Position                     */
#define PCC_CR_P5_Msk                         (0x03UL << PCC_CR_P5_Pos)                               /*!< PCC CR: P5 Mask                         */
#define PCC_CR_P6_Pos                         12                                                      /*!< PCC CR: P6 Position                     */
#define PCC_CR_P6_Msk                         (0x03UL << PCC_CR_P6_Pos)                               /*!< PCC CR: P6 Mask                         */
#define PCC_CR_P7_Pos                         14                                                      /*!< PCC CR: P7 Position                     */
#define PCC_CR_P7_Msk                         (0x03UL << PCC_CR_P7_Pos)                               /*!< PCC CR: P7 Mask                         */
#define PCC_CR_P8_Pos                         16                                                      /*!< PCC CR: P8 Position                     */
#define PCC_CR_P8_Msk                         (0x03UL << PCC_CR_P8_Pos)                               /*!< PCC CR: P8 Mask                         */
#define PCC_CR_P9_Pos                         18                                                      /*!< PCC CR: P9 Position                     */
#define PCC_CR_P9_Msk                         (0x03UL << PCC_CR_P9_Pos)                               /*!< PCC CR: P9 Mask                         */
#define PCC_CR_P10_Pos                        20                                                      /*!< PCC CR: P10 Position                    */
#define PCC_CR_P10_Msk                        (0x03UL << PCC_CR_P10_Pos)                              /*!< PCC CR: P10 Mask                        */
#define PCC_CR_P11_Pos                        22                                                      /*!< PCC CR: P11 Position                    */
#define PCC_CR_P11_Msk                        (0x03UL << PCC_CR_P11_Pos)                              /*!< PCC CR: P11 Mask                        */
#define PCC_CR_P12_Pos                        24                                                      /*!< PCC CR: P12 Position                    */
#define PCC_CR_P12_Msk                        (0x03UL << PCC_CR_P12_Pos)                              /*!< PCC CR: P12 Mask                        */
#define PCC_CR_P13_Pos                        26                                                      /*!< PCC CR: P13 Position                    */
#define PCC_CR_P13_Msk                        (0x03UL << PCC_CR_P13_Pos)                              /*!< PCC CR: P13 Mask                        */
#define PCC_CR_P14_Pos                        28                                                      /*!< PCC CR: P14 Position                    */
#define PCC_CR_P14_Msk                        (0x03UL << PCC_CR_P14_Pos)                              /*!< PCC CR: P14 Mask                        */
#define PCC_CR_P15_Pos                        30                                                      /*!< PCC CR: P15 Position                    */
#define PCC_CR_P15_Msk                        (0x03UL << PCC_CR_P15_Pos)                              /*!< PCC CR: P15 Mask                        */

/* -----------------------------------  PCC_PCR  ---------------------------------- */
#define PCC_PCR_P0_Pos                        0                                                       /*!< PCC PCR: P0 Position                    */
#define PCC_PCR_P0_Msk                        (0x01UL << PCC_PCR_P0_Pos)                              /*!< PCC PCR: P0 Mask                        */
#define PCC_PCR_P1_Pos                        1                                                       /*!< PCC PCR: P1 Position                    */
#define PCC_PCR_P1_Msk                        (0x01UL << PCC_PCR_P1_Pos)                              /*!< PCC PCR: P1 Mask                        */
#define PCC_PCR_P2_Pos                        2                                                       /*!< PCC PCR: P2 Position                    */
#define PCC_PCR_P2_Msk                        (0x01UL << PCC_PCR_P2_Pos)                              /*!< PCC PCR: P2 Mask                        */
#define PCC_PCR_P3_Pos                        3                                                       /*!< PCC PCR: P3 Position                    */
#define PCC_PCR_P3_Msk                        (0x01UL << PCC_PCR_P3_Pos)                              /*!< PCC PCR: P3 Mask                        */
#define PCC_PCR_P4_Pos                        4                                                       /*!< PCC PCR: P4 Position                    */
#define PCC_PCR_P4_Msk                        (0x01UL << PCC_PCR_P4_Pos)                              /*!< PCC PCR: P4 Mask                        */
#define PCC_PCR_P5_Pos                        5                                                       /*!< PCC PCR: P5 Position                    */
#define PCC_PCR_P5_Msk                        (0x01UL << PCC_PCR_P5_Pos)                              /*!< PCC PCR: P5 Mask                        */
#define PCC_PCR_P6_Pos                        6                                                       /*!< PCC PCR: P6 Position                    */
#define PCC_PCR_P6_Msk                        (0x01UL << PCC_PCR_P6_Pos)                              /*!< PCC PCR: P6 Mask                        */
#define PCC_PCR_P7_Pos                        7                                                       /*!< PCC PCR: P7 Position                    */
#define PCC_PCR_P7_Msk                        (0x01UL << PCC_PCR_P7_Pos)                              /*!< PCC PCR: P7 Mask                        */
#define PCC_PCR_P8_Pos                        8                                                       /*!< PCC PCR: P8 Position                    */
#define PCC_PCR_P8_Msk                        (0x01UL << PCC_PCR_P8_Pos)                              /*!< PCC PCR: P8 Mask                        */
#define PCC_PCR_P9_Pos                        9                                                       /*!< PCC PCR: P9 Position                    */
#define PCC_PCR_P9_Msk                        (0x01UL << PCC_PCR_P9_Pos)                              /*!< PCC PCR: P9 Mask                        */
#define PCC_PCR_P10_Pos                       10                                                      /*!< PCC PCR: P10 Position                   */
#define PCC_PCR_P10_Msk                       (0x01UL << PCC_PCR_P10_Pos)                             /*!< PCC PCR: P10 Mask                       */
#define PCC_PCR_P11_Pos                       11                                                      /*!< PCC PCR: P11 Position                   */
#define PCC_PCR_P11_Msk                       (0x01UL << PCC_PCR_P11_Pos)                             /*!< PCC PCR: P11 Mask                       */
#define PCC_PCR_P12_Pos                       12                                                      /*!< PCC PCR: P12 Position                   */
#define PCC_PCR_P12_Msk                       (0x01UL << PCC_PCR_P12_Pos)                             /*!< PCC PCR: P12 Mask                       */
#define PCC_PCR_P13_Pos                       13                                                      /*!< PCC PCR: P13 Position                   */
#define PCC_PCR_P13_Msk                       (0x01UL << PCC_PCR_P13_Pos)                             /*!< PCC PCR: P13 Mask                       */
#define PCC_PCR_P14_Pos                       14                                                      /*!< PCC PCR: P14 Position                   */
#define PCC_PCR_P14_Msk                       (0x01UL << PCC_PCR_P14_Pos)                             /*!< PCC PCR: P14 Mask                       */
#define PCC_PCR_P15_Pos                       15                                                      /*!< PCC PCR: P15 Position                   */
#define PCC_PCR_P15_Msk                       (0x01UL << PCC_PCR_P15_Pos)                             /*!< PCC PCR: P15 Mask                       */
#define PCC_PCR_D0_Pos                        16                                                      /*!< PCC PCR: D0 Position                    */
#define PCC_PCR_D0_Msk                        (0x01UL << PCC_PCR_D0_Pos)                              /*!< PCC PCR: D0 Mask                        */
#define PCC_PCR_D1_Pos                        17                                                      /*!< PCC PCR: D1 Position                    */
#define PCC_PCR_D1_Msk                        (0x01UL << PCC_PCR_D1_Pos)                              /*!< PCC PCR: D1 Mask                        */
#define PCC_PCR_D2_Pos                        18                                                      /*!< PCC PCR: D2 Position                    */
#define PCC_PCR_D2_Msk                        (0x01UL << PCC_PCR_D2_Pos)                              /*!< PCC PCR: D2 Mask                        */
#define PCC_PCR_D3_Pos                        19                                                      /*!< PCC PCR: D3 Position                    */
#define PCC_PCR_D3_Msk                        (0x01UL << PCC_PCR_D3_Pos)                              /*!< PCC PCR: D3 Mask                        */
#define PCC_PCR_D4_Pos                        20                                                      /*!< PCC PCR: D4 Position                    */
#define PCC_PCR_D4_Msk                        (0x01UL << PCC_PCR_D4_Pos)                              /*!< PCC PCR: D4 Mask                        */
#define PCC_PCR_D5_Pos                        21                                                      /*!< PCC PCR: D5 Position                    */
#define PCC_PCR_D5_Msk                        (0x01UL << PCC_PCR_D5_Pos)                              /*!< PCC PCR: D5 Mask                        */
#define PCC_PCR_D6_Pos                        22                                                      /*!< PCC PCR: D6 Position                    */
#define PCC_PCR_D6_Msk                        (0x01UL << PCC_PCR_D6_Pos)                              /*!< PCC PCR: D6 Mask                        */
#define PCC_PCR_D7_Pos                        23                                                      /*!< PCC PCR: D7 Position                    */
#define PCC_PCR_D7_Msk                        (0x01UL << PCC_PCR_D7_Pos)                              /*!< PCC PCR: D7 Mask                        */
#define PCC_PCR_D8_Pos                        24                                                      /*!< PCC PCR: D8 Position                    */
#define PCC_PCR_D8_Msk                        (0x01UL << PCC_PCR_D8_Pos)                              /*!< PCC PCR: D8 Mask                        */
#define PCC_PCR_D9_Pos                        25                                                      /*!< PCC PCR: D9 Position                    */
#define PCC_PCR_D9_Msk                        (0x01UL << PCC_PCR_D9_Pos)                              /*!< PCC PCR: D9 Mask                        */
#define PCC_PCR_D10_Pos                       26                                                      /*!< PCC PCR: D10 Position                   */
#define PCC_PCR_D10_Msk                       (0x01UL << PCC_PCR_D10_Pos)                             /*!< PCC PCR: D10 Mask                       */
#define PCC_PCR_D11_Pos                       27                                                      /*!< PCC PCR: D11 Position                   */
#define PCC_PCR_D11_Msk                       (0x01UL << PCC_PCR_D11_Pos)                             /*!< PCC PCR: D11 Mask                       */
#define PCC_PCR_D12_Pos                       28                                                      /*!< PCC PCR: D12 Position                   */
#define PCC_PCR_D12_Msk                       (0x01UL << PCC_PCR_D12_Pos)                             /*!< PCC PCR: D12 Mask                       */
#define PCC_PCR_D13_Pos                       29                                                      /*!< PCC PCR: D13 Position                   */
#define PCC_PCR_D13_Msk                       (0x01UL << PCC_PCR_D13_Pos)                             /*!< PCC PCR: D13 Mask                       */
#define PCC_PCR_D14_Pos                       30                                                      /*!< PCC PCR: D14 Position                   */
#define PCC_PCR_D14_Msk                       (0x01UL << PCC_PCR_D14_Pos)                             /*!< PCC PCR: D14 Mask                       */
#define PCC_PCR_D15_Pos                       31                                                      /*!< PCC PCR: D15 Position                   */
#define PCC_PCR_D15_Msk                       (0x01UL << PCC_PCR_D15_Pos)                             /*!< PCC PCR: D15 Mask                       */

/* -----------------------------------  PCC_DER  ---------------------------------- */
#define PCC_DER_P0_Pos                        0                                                       /*!< PCC DER: P0 Position                    */
#define PCC_DER_P0_Msk                        (0x01UL << PCC_DER_P0_Pos)                              /*!< PCC DER: P0 Mask                        */
#define PCC_DER_P1_Pos                        1                                                       /*!< PCC DER: P1 Position                    */
#define PCC_DER_P1_Msk                        (0x01UL << PCC_DER_P1_Pos)                              /*!< PCC DER: P1 Mask                        */
#define PCC_DER_P2_Pos                        2                                                       /*!< PCC DER: P2 Position                    */
#define PCC_DER_P2_Msk                        (0x01UL << PCC_DER_P2_Pos)                              /*!< PCC DER: P2 Mask                        */
#define PCC_DER_P3_Pos                        3                                                       /*!< PCC DER: P3 Position                    */
#define PCC_DER_P3_Msk                        (0x01UL << PCC_DER_P3_Pos)                              /*!< PCC DER: P3 Mask                        */
#define PCC_DER_P4_Pos                        4                                                       /*!< PCC DER: P4 Position                    */
#define PCC_DER_P4_Msk                        (0x01UL << PCC_DER_P4_Pos)                              /*!< PCC DER: P4 Mask                        */
#define PCC_DER_P5_Pos                        5                                                       /*!< PCC DER: P5 Position                    */
#define PCC_DER_P5_Msk                        (0x01UL << PCC_DER_P5_Pos)                              /*!< PCC DER: P5 Mask                        */
#define PCC_DER_P6_Pos                        6                                                       /*!< PCC DER: P6 Position                    */
#define PCC_DER_P6_Msk                        (0x01UL << PCC_DER_P6_Pos)                              /*!< PCC DER: P6 Mask                        */
#define PCC_DER_P7_Pos                        7                                                       /*!< PCC DER: P7 Position                    */
#define PCC_DER_P7_Msk                        (0x01UL << PCC_DER_P7_Pos)                              /*!< PCC DER: P7 Mask                        */
#define PCC_DER_P8_Pos                        8                                                       /*!< PCC DER: P8 Position                    */
#define PCC_DER_P8_Msk                        (0x01UL << PCC_DER_P8_Pos)                              /*!< PCC DER: P8 Mask                        */
#define PCC_DER_P9_Pos                        9                                                       /*!< PCC DER: P9 Position                    */
#define PCC_DER_P9_Msk                        (0x01UL << PCC_DER_P9_Pos)                              /*!< PCC DER: P9 Mask                        */
#define PCC_DER_P10_Pos                       10                                                      /*!< PCC DER: P10 Position                   */
#define PCC_DER_P10_Msk                       (0x01UL << PCC_DER_P10_Pos)                             /*!< PCC DER: P10 Mask                       */
#define PCC_DER_P11_Pos                       11                                                      /*!< PCC DER: P11 Position                   */
#define PCC_DER_P11_Msk                       (0x01UL << PCC_DER_P11_Pos)                             /*!< PCC DER: P11 Mask                       */
#define PCC_DER_P12_Pos                       12                                                      /*!< PCC DER: P12 Position                   */
#define PCC_DER_P12_Msk                       (0x01UL << PCC_DER_P12_Pos)                             /*!< PCC DER: P12 Mask                       */
#define PCC_DER_P13_Pos                       13                                                      /*!< PCC DER: P13 Position                   */
#define PCC_DER_P13_Msk                       (0x01UL << PCC_DER_P13_Pos)                             /*!< PCC DER: P13 Mask                       */
#define PCC_DER_P14_Pos                       14                                                      /*!< PCC DER: P14 Position                   */
#define PCC_DER_P14_Msk                       (0x01UL << PCC_DER_P14_Pos)                             /*!< PCC DER: P14 Mask                       */
#define PCC_DER_P15_Pos                       15                                                      /*!< PCC DER: P15 Position                   */
#define PCC_DER_P15_Msk                       (0x01UL << PCC_DER_P15_Pos)                             /*!< PCC DER: P15 Mask                       */

/* -----------------------------------  PCC_IER  ---------------------------------- */
#define PCC_IER_P0_Pos                        0                                                       /*!< PCC IER: P0 Position                    */
#define PCC_IER_P0_Msk                        (0x03UL << PCC_IER_P0_Pos)                              /*!< PCC IER: P0 Mask                        */
#define PCC_IER_P1_Pos                        2                                                       /*!< PCC IER: P1 Position                    */
#define PCC_IER_P1_Msk                        (0x03UL << PCC_IER_P1_Pos)                              /*!< PCC IER: P1 Mask                        */
#define PCC_IER_P2_Pos                        4                                                       /*!< PCC IER: P2 Position                    */
#define PCC_IER_P2_Msk                        (0x03UL << PCC_IER_P2_Pos)                              /*!< PCC IER: P2 Mask                        */
#define PCC_IER_P3_Pos                        6                                                       /*!< PCC IER: P3 Position                    */
#define PCC_IER_P3_Msk                        (0x03UL << PCC_IER_P3_Pos)                              /*!< PCC IER: P3 Mask                        */
#define PCC_IER_P4_Pos                        8                                                       /*!< PCC IER: P4 Position                    */
#define PCC_IER_P4_Msk                        (0x03UL << PCC_IER_P4_Pos)                              /*!< PCC IER: P4 Mask                        */
#define PCC_IER_P5_Pos                        10                                                      /*!< PCC IER: P5 Position                    */
#define PCC_IER_P5_Msk                        (0x03UL << PCC_IER_P5_Pos)                              /*!< PCC IER: P5 Mask                        */
#define PCC_IER_P6_Pos                        12                                                      /*!< PCC IER: P6 Position                    */
#define PCC_IER_P6_Msk                        (0x03UL << PCC_IER_P6_Pos)                              /*!< PCC IER: P6 Mask                        */
#define PCC_IER_P7_Pos                        14                                                      /*!< PCC IER: P7 Position                    */
#define PCC_IER_P7_Msk                        (0x03UL << PCC_IER_P7_Pos)                              /*!< PCC IER: P7 Mask                        */
#define PCC_IER_P8_Pos                        16                                                      /*!< PCC IER: P8 Position                    */
#define PCC_IER_P8_Msk                        (0x03UL << PCC_IER_P8_Pos)                              /*!< PCC IER: P8 Mask                        */
#define PCC_IER_P9_Pos                        18                                                      /*!< PCC IER: P9 Position                    */
#define PCC_IER_P9_Msk                        (0x03UL << PCC_IER_P9_Pos)                              /*!< PCC IER: P9 Mask                        */
#define PCC_IER_P10_Pos                       20                                                      /*!< PCC IER: P10 Position                   */
#define PCC_IER_P10_Msk                       (0x03UL << PCC_IER_P10_Pos)                             /*!< PCC IER: P10 Mask                       */
#define PCC_IER_P11_Pos                       22                                                      /*!< PCC IER: P11 Position                   */
#define PCC_IER_P11_Msk                       (0x03UL << PCC_IER_P11_Pos)                             /*!< PCC IER: P11 Mask                       */
#define PCC_IER_P12_Pos                       24                                                      /*!< PCC IER: P12 Position                   */
#define PCC_IER_P12_Msk                       (0x03UL << PCC_IER_P12_Pos)                             /*!< PCC IER: P12 Mask                       */
#define PCC_IER_P13_Pos                       26                                                      /*!< PCC IER: P13 Position                   */
#define PCC_IER_P13_Msk                       (0x03UL << PCC_IER_P13_Pos)                             /*!< PCC IER: P13 Mask                       */
#define PCC_IER_P14_Pos                       28                                                      /*!< PCC IER: P14 Position                   */
#define PCC_IER_P14_Msk                       (0x03UL << PCC_IER_P14_Pos)                             /*!< PCC IER: P14 Mask                       */
#define PCC_IER_P15_Pos                       30                                                      /*!< PCC IER: P15 Position                   */
#define PCC_IER_P15_Msk                       (0x03UL << PCC_IER_P15_Pos)                             /*!< PCC IER: P15 Mask                       */

/* -----------------------------------  PCC_ISR  ---------------------------------- */
#define PCC_ISR_P0_Pos                        0                                                       /*!< PCC ISR: P0 Position                    */
#define PCC_ISR_P0_Msk                        (0x03UL << PCC_ISR_P0_Pos)                              /*!< PCC ISR: P0 Mask                        */
#define PCC_ISR_P1_Pos                        2                                                       /*!< PCC ISR: P1 Position                    */
#define PCC_ISR_P1_Msk                        (0x03UL << PCC_ISR_P1_Pos)                              /*!< PCC ISR: P1 Mask                        */
#define PCC_ISR_P2_Pos                        4                                                       /*!< PCC ISR: P2 Position                    */
#define PCC_ISR_P2_Msk                        (0x03UL << PCC_ISR_P2_Pos)                              /*!< PCC ISR: P2 Mask                        */
#define PCC_ISR_P3_Pos                        6                                                       /*!< PCC ISR: P3 Position                    */
#define PCC_ISR_P3_Msk                        (0x03UL << PCC_ISR_P3_Pos)                              /*!< PCC ISR: P3 Mask                        */
#define PCC_ISR_P4_Pos                        8                                                       /*!< PCC ISR: P4 Position                    */
#define PCC_ISR_P4_Msk                        (0x03UL << PCC_ISR_P4_Pos)                              /*!< PCC ISR: P4 Mask                        */
#define PCC_ISR_P5_Pos                        10                                                      /*!< PCC ISR: P5 Position                    */
#define PCC_ISR_P5_Msk                        (0x03UL << PCC_ISR_P5_Pos)                              /*!< PCC ISR: P5 Mask                        */
#define PCC_ISR_P6_Pos                        12                                                      /*!< PCC ISR: P6 Position                    */
#define PCC_ISR_P6_Msk                        (0x03UL << PCC_ISR_P6_Pos)                              /*!< PCC ISR: P6 Mask                        */
#define PCC_ISR_P7_Pos                        14                                                      /*!< PCC ISR: P7 Position                    */
#define PCC_ISR_P7_Msk                        (0x03UL << PCC_ISR_P7_Pos)                              /*!< PCC ISR: P7 Mask                        */
#define PCC_ISR_P8_Pos                        16                                                      /*!< PCC ISR: P8 Position                    */
#define PCC_ISR_P8_Msk                        (0x03UL << PCC_ISR_P8_Pos)                              /*!< PCC ISR: P8 Mask                        */
#define PCC_ISR_P9_Pos                        18                                                      /*!< PCC ISR: P9 Position                    */
#define PCC_ISR_P9_Msk                        (0x03UL << PCC_ISR_P9_Pos)                              /*!< PCC ISR: P9 Mask                        */
#define PCC_ISR_P10_Pos                       20                                                      /*!< PCC ISR: P10 Position                   */
#define PCC_ISR_P10_Msk                       (0x03UL << PCC_ISR_P10_Pos)                             /*!< PCC ISR: P10 Mask                       */
#define PCC_ISR_P11_Pos                       22                                                      /*!< PCC ISR: P11 Position                   */
#define PCC_ISR_P11_Msk                       (0x03UL << PCC_ISR_P11_Pos)                             /*!< PCC ISR: P11 Mask                       */
#define PCC_ISR_P12_Pos                       24                                                      /*!< PCC ISR: P12 Position                   */
#define PCC_ISR_P12_Msk                       (0x03UL << PCC_ISR_P12_Pos)                             /*!< PCC ISR: P12 Mask                       */
#define PCC_ISR_P13_Pos                       26                                                      /*!< PCC ISR: P13 Position                   */
#define PCC_ISR_P13_Msk                       (0x03UL << PCC_ISR_P13_Pos)                             /*!< PCC ISR: P13 Mask                       */
#define PCC_ISR_P14_Pos                       28                                                      /*!< PCC ISR: P14 Position                   */
#define PCC_ISR_P14_Msk                       (0x03UL << PCC_ISR_P14_Pos)                             /*!< PCC ISR: P14 Mask                       */
#define PCC_ISR_P15_Pos                       30                                                      /*!< PCC ISR: P15 Position                   */
#define PCC_ISR_P15_Msk                       (0x03UL << PCC_ISR_P15_Pos)                             /*!< PCC ISR: P15 Mask                       */

/* -----------------------------------  PCC_ICR  ---------------------------------- */
#define PCC_ICR_P0_Pos                        0                                                       /*!< PCC ICR: P0 Position                    */
#define PCC_ICR_P0_Msk                        (0x03UL << PCC_ICR_P0_Pos)                              /*!< PCC ICR: P0 Mask                        */
#define PCC_ICR_P1_Pos                        2                                                       /*!< PCC ICR: P1 Position                    */
#define PCC_ICR_P1_Msk                        (0x03UL << PCC_ICR_P1_Pos)                              /*!< PCC ICR: P1 Mask                        */
#define PCC_ICR_P2_Pos                        4                                                       /*!< PCC ICR: P2 Position                    */
#define PCC_ICR_P2_Msk                        (0x03UL << PCC_ICR_P2_Pos)                              /*!< PCC ICR: P2 Mask                        */
#define PCC_ICR_P3_Pos                        6                                                       /*!< PCC ICR: P3 Position                    */
#define PCC_ICR_P3_Msk                        (0x03UL << PCC_ICR_P3_Pos)                              /*!< PCC ICR: P3 Mask                        */
#define PCC_ICR_P4_Pos                        8                                                       /*!< PCC ICR: P4 Position                    */
#define PCC_ICR_P4_Msk                        (0x03UL << PCC_ICR_P4_Pos)                              /*!< PCC ICR: P4 Mask                        */
#define PCC_ICR_P5_Pos                        10                                                      /*!< PCC ICR: P5 Position                    */
#define PCC_ICR_P5_Msk                        (0x03UL << PCC_ICR_P5_Pos)                              /*!< PCC ICR: P5 Mask                        */
#define PCC_ICR_P6_Pos                        12                                                      /*!< PCC ICR: P6 Position                    */
#define PCC_ICR_P6_Msk                        (0x03UL << PCC_ICR_P6_Pos)                              /*!< PCC ICR: P6 Mask                        */
#define PCC_ICR_P7_Pos                        14                                                      /*!< PCC ICR: P7 Position                    */
#define PCC_ICR_P7_Msk                        (0x03UL << PCC_ICR_P7_Pos)                              /*!< PCC ICR: P7 Mask                        */
#define PCC_ICR_P8_Pos                        16                                                      /*!< PCC ICR: P8 Position                    */
#define PCC_ICR_P8_Msk                        (0x03UL << PCC_ICR_P8_Pos)                              /*!< PCC ICR: P8 Mask                        */
#define PCC_ICR_P9_Pos                        18                                                      /*!< PCC ICR: P9 Position                    */
#define PCC_ICR_P9_Msk                        (0x03UL << PCC_ICR_P9_Pos)                              /*!< PCC ICR: P9 Mask                        */
#define PCC_ICR_P10_Pos                       20                                                      /*!< PCC ICR: P10 Position                   */
#define PCC_ICR_P10_Msk                       (0x03UL << PCC_ICR_P10_Pos)                             /*!< PCC ICR: P10 Mask                       */
#define PCC_ICR_P11_Pos                       22                                                      /*!< PCC ICR: P11 Position                   */
#define PCC_ICR_P11_Msk                       (0x03UL << PCC_ICR_P11_Pos)                             /*!< PCC ICR: P11 Mask                       */
#define PCC_ICR_P12_Pos                       24                                                      /*!< PCC ICR: P12 Position                   */
#define PCC_ICR_P12_Msk                       (0x03UL << PCC_ICR_P12_Pos)                             /*!< PCC ICR: P12 Mask                       */
#define PCC_ICR_P13_Pos                       26                                                      /*!< PCC ICR: P13 Position                   */
#define PCC_ICR_P13_Msk                       (0x03UL << PCC_ICR_P13_Pos)                             /*!< PCC ICR: P13 Mask                       */
#define PCC_ICR_P14_Pos                       28                                                      /*!< PCC ICR: P14 Position                   */
#define PCC_ICR_P14_Msk                       (0x03UL << PCC_ICR_P14_Pos)                             /*!< PCC ICR: P14 Mask                       */
#define PCC_ICR_P15_Pos                       30                                                      /*!< PCC ICR: P15 Position                   */
#define PCC_ICR_P15_Msk                       (0x03UL << PCC_ICR_P15_Pos)                             /*!< PCC ICR: P15 Mask                       */

/* -----------------------------------  PCC_DPR  ---------------------------------- */
#define PCC_DPR_DPR_Pos                       0                                                       /*!< PCC DPR: DPR Position                   */
#define PCC_DPR_DPR_Msk                       (0x1fUL << PCC_DPR_DPR_Pos)                             /*!< PCC DPR: DPR Mask                       */


/* ================================================================================ */
/* ================          struct 'PCD' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  PCD_MR  ----------------------------------- */
#define PCD_MR_P0_Pos                         0                                                       /*!< PCD MR: P0 Position                     */
#define PCD_MR_P0_Msk                         (0x03UL << PCD_MR_P0_Pos)                               /*!< PCD MR: P0 Mask                         */
#define PCD_MR_P1_Pos                         2                                                       /*!< PCD MR: P1 Position                     */
#define PCD_MR_P1_Msk                         (0x03UL << PCD_MR_P1_Pos)                               /*!< PCD MR: P1 Mask                         */
#define PCD_MR_P2_Pos                         4                                                       /*!< PCD MR: P2 Position                     */
#define PCD_MR_P2_Msk                         (0x03UL << PCD_MR_P2_Pos)                               /*!< PCD MR: P2 Mask                         */
#define PCD_MR_P3_Pos                         6                                                       /*!< PCD MR: P3 Position                     */
#define PCD_MR_P3_Msk                         (0x03UL << PCD_MR_P3_Pos)                               /*!< PCD MR: P3 Mask                         */
#define PCD_MR_P4_Pos                         8                                                       /*!< PCD MR: P4 Position                     */
#define PCD_MR_P4_Msk                         (0x03UL << PCD_MR_P4_Pos)                               /*!< PCD MR: P4 Mask                         */
#define PCD_MR_P5_Pos                         10                                                      /*!< PCD MR: P5 Position                     */
#define PCD_MR_P5_Msk                         (0x03UL << PCD_MR_P5_Pos)                               /*!< PCD MR: P5 Mask                         */
#define PCD_MR_P6_Pos                         12                                                      /*!< PCD MR: P6 Position                     */
#define PCD_MR_P6_Msk                         (0x03UL << PCD_MR_P6_Pos)                               /*!< PCD MR: P6 Mask                         */
#define PCD_MR_P7_Pos                         14                                                      /*!< PCD MR: P7 Position                     */
#define PCD_MR_P7_Msk                         (0x03UL << PCD_MR_P7_Pos)                               /*!< PCD MR: P7 Mask                         */
#define PCD_MR_P8_Pos                         16                                                      /*!< PCD MR: P8 Position                     */
#define PCD_MR_P8_Msk                         (0x03UL << PCD_MR_P8_Pos)                               /*!< PCD MR: P8 Mask                         */
#define PCD_MR_P9_Pos                         18                                                      /*!< PCD MR: P9 Position                     */
#define PCD_MR_P9_Msk                         (0x03UL << PCD_MR_P9_Pos)                               /*!< PCD MR: P9 Mask                         */
#define PCD_MR_P10_Pos                        20                                                      /*!< PCD MR: P10 Position                    */
#define PCD_MR_P10_Msk                        (0x03UL << PCD_MR_P10_Pos)                              /*!< PCD MR: P10 Mask                        */
#define PCD_MR_P11_Pos                        22                                                      /*!< PCD MR: P11 Position                    */
#define PCD_MR_P11_Msk                        (0x03UL << PCD_MR_P11_Pos)                              /*!< PCD MR: P11 Mask                        */
#define PCD_MR_P12_Pos                        24                                                      /*!< PCD MR: P12 Position                    */
#define PCD_MR_P12_Msk                        (0x03UL << PCD_MR_P12_Pos)                              /*!< PCD MR: P12 Mask                        */
#define PCD_MR_P13_Pos                        26                                                      /*!< PCD MR: P13 Position                    */
#define PCD_MR_P13_Msk                        (0x03UL << PCD_MR_P13_Pos)                              /*!< PCD MR: P13 Mask                        */
#define PCD_MR_P14_Pos                        28                                                      /*!< PCD MR: P14 Position                    */
#define PCD_MR_P14_Msk                        (0x03UL << PCD_MR_P14_Pos)                              /*!< PCD MR: P14 Mask                        */
#define PCD_MR_P15_Pos                        30                                                      /*!< PCD MR: P15 Position                    */
#define PCD_MR_P15_Msk                        (0x03UL << PCD_MR_P15_Pos)                              /*!< PCD MR: P15 Mask                        */

/* -----------------------------------  PCD_CR  ----------------------------------- */
#define PCD_CR_P0_Pos                         0                                                       /*!< PCD CR: P0 Position                     */
#define PCD_CR_P0_Msk                         (0x03UL << PCD_CR_P0_Pos)                               /*!< PCD CR: P0 Mask                         */
#define PCD_CR_P1_Pos                         2                                                       /*!< PCD CR: P1 Position                     */
#define PCD_CR_P1_Msk                         (0x03UL << PCD_CR_P1_Pos)                               /*!< PCD CR: P1 Mask                         */
#define PCD_CR_P2_Pos                         4                                                       /*!< PCD CR: P2 Position                     */
#define PCD_CR_P2_Msk                         (0x03UL << PCD_CR_P2_Pos)                               /*!< PCD CR: P2 Mask                         */
#define PCD_CR_P3_Pos                         6                                                       /*!< PCD CR: P3 Position                     */
#define PCD_CR_P3_Msk                         (0x03UL << PCD_CR_P3_Pos)                               /*!< PCD CR: P3 Mask                         */
#define PCD_CR_P4_Pos                         8                                                       /*!< PCD CR: P4 Position                     */
#define PCD_CR_P4_Msk                         (0x03UL << PCD_CR_P4_Pos)                               /*!< PCD CR: P4 Mask                         */
#define PCD_CR_P5_Pos                         10                                                      /*!< PCD CR: P5 Position                     */
#define PCD_CR_P5_Msk                         (0x03UL << PCD_CR_P5_Pos)                               /*!< PCD CR: P5 Mask                         */
#define PCD_CR_P6_Pos                         12                                                      /*!< PCD CR: P6 Position                     */
#define PCD_CR_P6_Msk                         (0x03UL << PCD_CR_P6_Pos)                               /*!< PCD CR: P6 Mask                         */
#define PCD_CR_P7_Pos                         14                                                      /*!< PCD CR: P7 Position                     */
#define PCD_CR_P7_Msk                         (0x03UL << PCD_CR_P7_Pos)                               /*!< PCD CR: P7 Mask                         */
#define PCD_CR_P8_Pos                         16                                                      /*!< PCD CR: P8 Position                     */
#define PCD_CR_P8_Msk                         (0x03UL << PCD_CR_P8_Pos)                               /*!< PCD CR: P8 Mask                         */
#define PCD_CR_P9_Pos                         18                                                      /*!< PCD CR: P9 Position                     */
#define PCD_CR_P9_Msk                         (0x03UL << PCD_CR_P9_Pos)                               /*!< PCD CR: P9 Mask                         */
#define PCD_CR_P10_Pos                        20                                                      /*!< PCD CR: P10 Position                    */
#define PCD_CR_P10_Msk                        (0x03UL << PCD_CR_P10_Pos)                              /*!< PCD CR: P10 Mask                        */
#define PCD_CR_P11_Pos                        22                                                      /*!< PCD CR: P11 Position                    */
#define PCD_CR_P11_Msk                        (0x03UL << PCD_CR_P11_Pos)                              /*!< PCD CR: P11 Mask                        */
#define PCD_CR_P12_Pos                        24                                                      /*!< PCD CR: P12 Position                    */
#define PCD_CR_P12_Msk                        (0x03UL << PCD_CR_P12_Pos)                              /*!< PCD CR: P12 Mask                        */
#define PCD_CR_P13_Pos                        26                                                      /*!< PCD CR: P13 Position                    */
#define PCD_CR_P13_Msk                        (0x03UL << PCD_CR_P13_Pos)                              /*!< PCD CR: P13 Mask                        */
#define PCD_CR_P14_Pos                        28                                                      /*!< PCD CR: P14 Position                    */
#define PCD_CR_P14_Msk                        (0x03UL << PCD_CR_P14_Pos)                              /*!< PCD CR: P14 Mask                        */
#define PCD_CR_P15_Pos                        30                                                      /*!< PCD CR: P15 Position                    */
#define PCD_CR_P15_Msk                        (0x03UL << PCD_CR_P15_Pos)                              /*!< PCD CR: P15 Mask                        */

/* -----------------------------------  PCD_PCR  ---------------------------------- */
#define PCD_PCR_P0_Pos                        0                                                       /*!< PCD PCR: P0 Position                    */
#define PCD_PCR_P0_Msk                        (0x01UL << PCD_PCR_P0_Pos)                              /*!< PCD PCR: P0 Mask                        */
#define PCD_PCR_P1_Pos                        1                                                       /*!< PCD PCR: P1 Position                    */
#define PCD_PCR_P1_Msk                        (0x01UL << PCD_PCR_P1_Pos)                              /*!< PCD PCR: P1 Mask                        */
#define PCD_PCR_P2_Pos                        2                                                       /*!< PCD PCR: P2 Position                    */
#define PCD_PCR_P2_Msk                        (0x01UL << PCD_PCR_P2_Pos)                              /*!< PCD PCR: P2 Mask                        */
#define PCD_PCR_P3_Pos                        3                                                       /*!< PCD PCR: P3 Position                    */
#define PCD_PCR_P3_Msk                        (0x01UL << PCD_PCR_P3_Pos)                              /*!< PCD PCR: P3 Mask                        */
#define PCD_PCR_P4_Pos                        4                                                       /*!< PCD PCR: P4 Position                    */
#define PCD_PCR_P4_Msk                        (0x01UL << PCD_PCR_P4_Pos)                              /*!< PCD PCR: P4 Mask                        */
#define PCD_PCR_P5_Pos                        5                                                       /*!< PCD PCR: P5 Position                    */
#define PCD_PCR_P5_Msk                        (0x01UL << PCD_PCR_P5_Pos)                              /*!< PCD PCR: P5 Mask                        */
#define PCD_PCR_P6_Pos                        6                                                       /*!< PCD PCR: P6 Position                    */
#define PCD_PCR_P6_Msk                        (0x01UL << PCD_PCR_P6_Pos)                              /*!< PCD PCR: P6 Mask                        */
#define PCD_PCR_P7_Pos                        7                                                       /*!< PCD PCR: P7 Position                    */
#define PCD_PCR_P7_Msk                        (0x01UL << PCD_PCR_P7_Pos)                              /*!< PCD PCR: P7 Mask                        */
#define PCD_PCR_P8_Pos                        8                                                       /*!< PCD PCR: P8 Position                    */
#define PCD_PCR_P8_Msk                        (0x01UL << PCD_PCR_P8_Pos)                              /*!< PCD PCR: P8 Mask                        */
#define PCD_PCR_P9_Pos                        9                                                       /*!< PCD PCR: P9 Position                    */
#define PCD_PCR_P9_Msk                        (0x01UL << PCD_PCR_P9_Pos)                              /*!< PCD PCR: P9 Mask                        */
#define PCD_PCR_P10_Pos                       10                                                      /*!< PCD PCR: P10 Position                   */
#define PCD_PCR_P10_Msk                       (0x01UL << PCD_PCR_P10_Pos)                             /*!< PCD PCR: P10 Mask                       */
#define PCD_PCR_P11_Pos                       11                                                      /*!< PCD PCR: P11 Position                   */
#define PCD_PCR_P11_Msk                       (0x01UL << PCD_PCR_P11_Pos)                             /*!< PCD PCR: P11 Mask                       */
#define PCD_PCR_P12_Pos                       12                                                      /*!< PCD PCR: P12 Position                   */
#define PCD_PCR_P12_Msk                       (0x01UL << PCD_PCR_P12_Pos)                             /*!< PCD PCR: P12 Mask                       */
#define PCD_PCR_P13_Pos                       13                                                      /*!< PCD PCR: P13 Position                   */
#define PCD_PCR_P13_Msk                       (0x01UL << PCD_PCR_P13_Pos)                             /*!< PCD PCR: P13 Mask                       */
#define PCD_PCR_P14_Pos                       14                                                      /*!< PCD PCR: P14 Position                   */
#define PCD_PCR_P14_Msk                       (0x01UL << PCD_PCR_P14_Pos)                             /*!< PCD PCR: P14 Mask                       */
#define PCD_PCR_P15_Pos                       15                                                      /*!< PCD PCR: P15 Position                   */
#define PCD_PCR_P15_Msk                       (0x01UL << PCD_PCR_P15_Pos)                             /*!< PCD PCR: P15 Mask                       */
#define PCD_PCR_D0_Pos                        16                                                      /*!< PCD PCR: D0 Position                    */
#define PCD_PCR_D0_Msk                        (0x01UL << PCD_PCR_D0_Pos)                              /*!< PCD PCR: D0 Mask                        */
#define PCD_PCR_D1_Pos                        17                                                      /*!< PCD PCR: D1 Position                    */
#define PCD_PCR_D1_Msk                        (0x01UL << PCD_PCR_D1_Pos)                              /*!< PCD PCR: D1 Mask                        */
#define PCD_PCR_D2_Pos                        18                                                      /*!< PCD PCR: D2 Position                    */
#define PCD_PCR_D2_Msk                        (0x01UL << PCD_PCR_D2_Pos)                              /*!< PCD PCR: D2 Mask                        */
#define PCD_PCR_D3_Pos                        19                                                      /*!< PCD PCR: D3 Position                    */
#define PCD_PCR_D3_Msk                        (0x01UL << PCD_PCR_D3_Pos)                              /*!< PCD PCR: D3 Mask                        */
#define PCD_PCR_D4_Pos                        20                                                      /*!< PCD PCR: D4 Position                    */
#define PCD_PCR_D4_Msk                        (0x01UL << PCD_PCR_D4_Pos)                              /*!< PCD PCR: D4 Mask                        */
#define PCD_PCR_D5_Pos                        21                                                      /*!< PCD PCR: D5 Position                    */
#define PCD_PCR_D5_Msk                        (0x01UL << PCD_PCR_D5_Pos)                              /*!< PCD PCR: D5 Mask                        */
#define PCD_PCR_D6_Pos                        22                                                      /*!< PCD PCR: D6 Position                    */
#define PCD_PCR_D6_Msk                        (0x01UL << PCD_PCR_D6_Pos)                              /*!< PCD PCR: D6 Mask                        */
#define PCD_PCR_D7_Pos                        23                                                      /*!< PCD PCR: D7 Position                    */
#define PCD_PCR_D7_Msk                        (0x01UL << PCD_PCR_D7_Pos)                              /*!< PCD PCR: D7 Mask                        */
#define PCD_PCR_D8_Pos                        24                                                      /*!< PCD PCR: D8 Position                    */
#define PCD_PCR_D8_Msk                        (0x01UL << PCD_PCR_D8_Pos)                              /*!< PCD PCR: D8 Mask                        */
#define PCD_PCR_D9_Pos                        25                                                      /*!< PCD PCR: D9 Position                    */
#define PCD_PCR_D9_Msk                        (0x01UL << PCD_PCR_D9_Pos)                              /*!< PCD PCR: D9 Mask                        */
#define PCD_PCR_D10_Pos                       26                                                      /*!< PCD PCR: D10 Position                   */
#define PCD_PCR_D10_Msk                       (0x01UL << PCD_PCR_D10_Pos)                             /*!< PCD PCR: D10 Mask                       */
#define PCD_PCR_D11_Pos                       27                                                      /*!< PCD PCR: D11 Position                   */
#define PCD_PCR_D11_Msk                       (0x01UL << PCD_PCR_D11_Pos)                             /*!< PCD PCR: D11 Mask                       */
#define PCD_PCR_D12_Pos                       28                                                      /*!< PCD PCR: D12 Position                   */
#define PCD_PCR_D12_Msk                       (0x01UL << PCD_PCR_D12_Pos)                             /*!< PCD PCR: D12 Mask                       */
#define PCD_PCR_D13_Pos                       29                                                      /*!< PCD PCR: D13 Position                   */
#define PCD_PCR_D13_Msk                       (0x01UL << PCD_PCR_D13_Pos)                             /*!< PCD PCR: D13 Mask                       */
#define PCD_PCR_D14_Pos                       30                                                      /*!< PCD PCR: D14 Position                   */
#define PCD_PCR_D14_Msk                       (0x01UL << PCD_PCR_D14_Pos)                             /*!< PCD PCR: D14 Mask                       */
#define PCD_PCR_D15_Pos                       31                                                      /*!< PCD PCR: D15 Position                   */
#define PCD_PCR_D15_Msk                       (0x01UL << PCD_PCR_D15_Pos)                             /*!< PCD PCR: D15 Mask                       */

/* -----------------------------------  PCD_DER  ---------------------------------- */
#define PCD_DER_P0_Pos                        0                                                       /*!< PCD DER: P0 Position                    */
#define PCD_DER_P0_Msk                        (0x01UL << PCD_DER_P0_Pos)                              /*!< PCD DER: P0 Mask                        */
#define PCD_DER_P1_Pos                        1                                                       /*!< PCD DER: P1 Position                    */
#define PCD_DER_P1_Msk                        (0x01UL << PCD_DER_P1_Pos)                              /*!< PCD DER: P1 Mask                        */
#define PCD_DER_P2_Pos                        2                                                       /*!< PCD DER: P2 Position                    */
#define PCD_DER_P2_Msk                        (0x01UL << PCD_DER_P2_Pos)                              /*!< PCD DER: P2 Mask                        */
#define PCD_DER_P3_Pos                        3                                                       /*!< PCD DER: P3 Position                    */
#define PCD_DER_P3_Msk                        (0x01UL << PCD_DER_P3_Pos)                              /*!< PCD DER: P3 Mask                        */
#define PCD_DER_P4_Pos                        4                                                       /*!< PCD DER: P4 Position                    */
#define PCD_DER_P4_Msk                        (0x01UL << PCD_DER_P4_Pos)                              /*!< PCD DER: P4 Mask                        */
#define PCD_DER_P5_Pos                        5                                                       /*!< PCD DER: P5 Position                    */
#define PCD_DER_P5_Msk                        (0x01UL << PCD_DER_P5_Pos)                              /*!< PCD DER: P5 Mask                        */
#define PCD_DER_P6_Pos                        6                                                       /*!< PCD DER: P6 Position                    */
#define PCD_DER_P6_Msk                        (0x01UL << PCD_DER_P6_Pos)                              /*!< PCD DER: P6 Mask                        */
#define PCD_DER_P7_Pos                        7                                                       /*!< PCD DER: P7 Position                    */
#define PCD_DER_P7_Msk                        (0x01UL << PCD_DER_P7_Pos)                              /*!< PCD DER: P7 Mask                        */
#define PCD_DER_P8_Pos                        8                                                       /*!< PCD DER: P8 Position                    */
#define PCD_DER_P8_Msk                        (0x01UL << PCD_DER_P8_Pos)                              /*!< PCD DER: P8 Mask                        */
#define PCD_DER_P9_Pos                        9                                                       /*!< PCD DER: P9 Position                    */
#define PCD_DER_P9_Msk                        (0x01UL << PCD_DER_P9_Pos)                              /*!< PCD DER: P9 Mask                        */
#define PCD_DER_P10_Pos                       10                                                      /*!< PCD DER: P10 Position                   */
#define PCD_DER_P10_Msk                       (0x01UL << PCD_DER_P10_Pos)                             /*!< PCD DER: P10 Mask                       */
#define PCD_DER_P11_Pos                       11                                                      /*!< PCD DER: P11 Position                   */
#define PCD_DER_P11_Msk                       (0x01UL << PCD_DER_P11_Pos)                             /*!< PCD DER: P11 Mask                       */
#define PCD_DER_P12_Pos                       12                                                      /*!< PCD DER: P12 Position                   */
#define PCD_DER_P12_Msk                       (0x01UL << PCD_DER_P12_Pos)                             /*!< PCD DER: P12 Mask                       */
#define PCD_DER_P13_Pos                       13                                                      /*!< PCD DER: P13 Position                   */
#define PCD_DER_P13_Msk                       (0x01UL << PCD_DER_P13_Pos)                             /*!< PCD DER: P13 Mask                       */
#define PCD_DER_P14_Pos                       14                                                      /*!< PCD DER: P14 Position                   */
#define PCD_DER_P14_Msk                       (0x01UL << PCD_DER_P14_Pos)                             /*!< PCD DER: P14 Mask                       */
#define PCD_DER_P15_Pos                       15                                                      /*!< PCD DER: P15 Position                   */
#define PCD_DER_P15_Msk                       (0x01UL << PCD_DER_P15_Pos)                             /*!< PCD DER: P15 Mask                       */

/* -----------------------------------  PCD_IER  ---------------------------------- */
#define PCD_IER_P0_Pos                        0                                                       /*!< PCD IER: P0 Position                    */
#define PCD_IER_P0_Msk                        (0x03UL << PCD_IER_P0_Pos)                              /*!< PCD IER: P0 Mask                        */
#define PCD_IER_P1_Pos                        2                                                       /*!< PCD IER: P1 Position                    */
#define PCD_IER_P1_Msk                        (0x03UL << PCD_IER_P1_Pos)                              /*!< PCD IER: P1 Mask                        */
#define PCD_IER_P2_Pos                        4                                                       /*!< PCD IER: P2 Position                    */
#define PCD_IER_P2_Msk                        (0x03UL << PCD_IER_P2_Pos)                              /*!< PCD IER: P2 Mask                        */
#define PCD_IER_P3_Pos                        6                                                       /*!< PCD IER: P3 Position                    */
#define PCD_IER_P3_Msk                        (0x03UL << PCD_IER_P3_Pos)                              /*!< PCD IER: P3 Mask                        */
#define PCD_IER_P4_Pos                        8                                                       /*!< PCD IER: P4 Position                    */
#define PCD_IER_P4_Msk                        (0x03UL << PCD_IER_P4_Pos)                              /*!< PCD IER: P4 Mask                        */
#define PCD_IER_P5_Pos                        10                                                      /*!< PCD IER: P5 Position                    */
#define PCD_IER_P5_Msk                        (0x03UL << PCD_IER_P5_Pos)                              /*!< PCD IER: P5 Mask                        */
#define PCD_IER_P6_Pos                        12                                                      /*!< PCD IER: P6 Position                    */
#define PCD_IER_P6_Msk                        (0x03UL << PCD_IER_P6_Pos)                              /*!< PCD IER: P6 Mask                        */
#define PCD_IER_P7_Pos                        14                                                      /*!< PCD IER: P7 Position                    */
#define PCD_IER_P7_Msk                        (0x03UL << PCD_IER_P7_Pos)                              /*!< PCD IER: P7 Mask                        */
#define PCD_IER_P8_Pos                        16                                                      /*!< PCD IER: P8 Position                    */
#define PCD_IER_P8_Msk                        (0x03UL << PCD_IER_P8_Pos)                              /*!< PCD IER: P8 Mask                        */
#define PCD_IER_P9_Pos                        18                                                      /*!< PCD IER: P9 Position                    */
#define PCD_IER_P9_Msk                        (0x03UL << PCD_IER_P9_Pos)                              /*!< PCD IER: P9 Mask                        */
#define PCD_IER_P10_Pos                       20                                                      /*!< PCD IER: P10 Position                   */
#define PCD_IER_P10_Msk                       (0x03UL << PCD_IER_P10_Pos)                             /*!< PCD IER: P10 Mask                       */
#define PCD_IER_P11_Pos                       22                                                      /*!< PCD IER: P11 Position                   */
#define PCD_IER_P11_Msk                       (0x03UL << PCD_IER_P11_Pos)                             /*!< PCD IER: P11 Mask                       */
#define PCD_IER_P12_Pos                       24                                                      /*!< PCD IER: P12 Position                   */
#define PCD_IER_P12_Msk                       (0x03UL << PCD_IER_P12_Pos)                             /*!< PCD IER: P12 Mask                       */
#define PCD_IER_P13_Pos                       26                                                      /*!< PCD IER: P13 Position                   */
#define PCD_IER_P13_Msk                       (0x03UL << PCD_IER_P13_Pos)                             /*!< PCD IER: P13 Mask                       */
#define PCD_IER_P14_Pos                       28                                                      /*!< PCD IER: P14 Position                   */
#define PCD_IER_P14_Msk                       (0x03UL << PCD_IER_P14_Pos)                             /*!< PCD IER: P14 Mask                       */
#define PCD_IER_P15_Pos                       30                                                      /*!< PCD IER: P15 Position                   */
#define PCD_IER_P15_Msk                       (0x03UL << PCD_IER_P15_Pos)                             /*!< PCD IER: P15 Mask                       */

/* -----------------------------------  PCD_ISR  ---------------------------------- */
#define PCD_ISR_P0_Pos                        0                                                       /*!< PCD ISR: P0 Position                    */
#define PCD_ISR_P0_Msk                        (0x03UL << PCD_ISR_P0_Pos)                              /*!< PCD ISR: P0 Mask                        */
#define PCD_ISR_P1_Pos                        2                                                       /*!< PCD ISR: P1 Position                    */
#define PCD_ISR_P1_Msk                        (0x03UL << PCD_ISR_P1_Pos)                              /*!< PCD ISR: P1 Mask                        */
#define PCD_ISR_P2_Pos                        4                                                       /*!< PCD ISR: P2 Position                    */
#define PCD_ISR_P2_Msk                        (0x03UL << PCD_ISR_P2_Pos)                              /*!< PCD ISR: P2 Mask                        */
#define PCD_ISR_P3_Pos                        6                                                       /*!< PCD ISR: P3 Position                    */
#define PCD_ISR_P3_Msk                        (0x03UL << PCD_ISR_P3_Pos)                              /*!< PCD ISR: P3 Mask                        */
#define PCD_ISR_P4_Pos                        8                                                       /*!< PCD ISR: P4 Position                    */
#define PCD_ISR_P4_Msk                        (0x03UL << PCD_ISR_P4_Pos)                              /*!< PCD ISR: P4 Mask                        */
#define PCD_ISR_P5_Pos                        10                                                      /*!< PCD ISR: P5 Position                    */
#define PCD_ISR_P5_Msk                        (0x03UL << PCD_ISR_P5_Pos)                              /*!< PCD ISR: P5 Mask                        */
#define PCD_ISR_P6_Pos                        12                                                      /*!< PCD ISR: P6 Position                    */
#define PCD_ISR_P6_Msk                        (0x03UL << PCD_ISR_P6_Pos)                              /*!< PCD ISR: P6 Mask                        */
#define PCD_ISR_P7_Pos                        14                                                      /*!< PCD ISR: P7 Position                    */
#define PCD_ISR_P7_Msk                        (0x03UL << PCD_ISR_P7_Pos)                              /*!< PCD ISR: P7 Mask                        */
#define PCD_ISR_P8_Pos                        16                                                      /*!< PCD ISR: P8 Position                    */
#define PCD_ISR_P8_Msk                        (0x03UL << PCD_ISR_P8_Pos)                              /*!< PCD ISR: P8 Mask                        */
#define PCD_ISR_P9_Pos                        18                                                      /*!< PCD ISR: P9 Position                    */
#define PCD_ISR_P9_Msk                        (0x03UL << PCD_ISR_P9_Pos)                              /*!< PCD ISR: P9 Mask                        */
#define PCD_ISR_P10_Pos                       20                                                      /*!< PCD ISR: P10 Position                   */
#define PCD_ISR_P10_Msk                       (0x03UL << PCD_ISR_P10_Pos)                             /*!< PCD ISR: P10 Mask                       */
#define PCD_ISR_P11_Pos                       22                                                      /*!< PCD ISR: P11 Position                   */
#define PCD_ISR_P11_Msk                       (0x03UL << PCD_ISR_P11_Pos)                             /*!< PCD ISR: P11 Mask                       */
#define PCD_ISR_P12_Pos                       24                                                      /*!< PCD ISR: P12 Position                   */
#define PCD_ISR_P12_Msk                       (0x03UL << PCD_ISR_P12_Pos)                             /*!< PCD ISR: P12 Mask                       */
#define PCD_ISR_P13_Pos                       26                                                      /*!< PCD ISR: P13 Position                   */
#define PCD_ISR_P13_Msk                       (0x03UL << PCD_ISR_P13_Pos)                             /*!< PCD ISR: P13 Mask                       */
#define PCD_ISR_P14_Pos                       28                                                      /*!< PCD ISR: P14 Position                   */
#define PCD_ISR_P14_Msk                       (0x03UL << PCD_ISR_P14_Pos)                             /*!< PCD ISR: P14 Mask                       */
#define PCD_ISR_P15_Pos                       30                                                      /*!< PCD ISR: P15 Position                   */
#define PCD_ISR_P15_Msk                       (0x03UL << PCD_ISR_P15_Pos)                             /*!< PCD ISR: P15 Mask                       */

/* -----------------------------------  PCD_ICR  ---------------------------------- */
#define PCD_ICR_P0_Pos                        0                                                       /*!< PCD ICR: P0 Position                    */
#define PCD_ICR_P0_Msk                        (0x03UL << PCD_ICR_P0_Pos)                              /*!< PCD ICR: P0 Mask                        */
#define PCD_ICR_P1_Pos                        2                                                       /*!< PCD ICR: P1 Position                    */
#define PCD_ICR_P1_Msk                        (0x03UL << PCD_ICR_P1_Pos)                              /*!< PCD ICR: P1 Mask                        */
#define PCD_ICR_P2_Pos                        4                                                       /*!< PCD ICR: P2 Position                    */
#define PCD_ICR_P2_Msk                        (0x03UL << PCD_ICR_P2_Pos)                              /*!< PCD ICR: P2 Mask                        */
#define PCD_ICR_P3_Pos                        6                                                       /*!< PCD ICR: P3 Position                    */
#define PCD_ICR_P3_Msk                        (0x03UL << PCD_ICR_P3_Pos)                              /*!< PCD ICR: P3 Mask                        */
#define PCD_ICR_P4_Pos                        8                                                       /*!< PCD ICR: P4 Position                    */
#define PCD_ICR_P4_Msk                        (0x03UL << PCD_ICR_P4_Pos)                              /*!< PCD ICR: P4 Mask                        */
#define PCD_ICR_P5_Pos                        10                                                      /*!< PCD ICR: P5 Position                    */
#define PCD_ICR_P5_Msk                        (0x03UL << PCD_ICR_P5_Pos)                              /*!< PCD ICR: P5 Mask                        */
#define PCD_ICR_P6_Pos                        12                                                      /*!< PCD ICR: P6 Position                    */
#define PCD_ICR_P6_Msk                        (0x03UL << PCD_ICR_P6_Pos)                              /*!< PCD ICR: P6 Mask                        */
#define PCD_ICR_P7_Pos                        14                                                      /*!< PCD ICR: P7 Position                    */
#define PCD_ICR_P7_Msk                        (0x03UL << PCD_ICR_P7_Pos)                              /*!< PCD ICR: P7 Mask                        */
#define PCD_ICR_P8_Pos                        16                                                      /*!< PCD ICR: P8 Position                    */
#define PCD_ICR_P8_Msk                        (0x03UL << PCD_ICR_P8_Pos)                              /*!< PCD ICR: P8 Mask                        */
#define PCD_ICR_P9_Pos                        18                                                      /*!< PCD ICR: P9 Position                    */
#define PCD_ICR_P9_Msk                        (0x03UL << PCD_ICR_P9_Pos)                              /*!< PCD ICR: P9 Mask                        */
#define PCD_ICR_P10_Pos                       20                                                      /*!< PCD ICR: P10 Position                   */
#define PCD_ICR_P10_Msk                       (0x03UL << PCD_ICR_P10_Pos)                             /*!< PCD ICR: P10 Mask                       */
#define PCD_ICR_P11_Pos                       22                                                      /*!< PCD ICR: P11 Position                   */
#define PCD_ICR_P11_Msk                       (0x03UL << PCD_ICR_P11_Pos)                             /*!< PCD ICR: P11 Mask                       */
#define PCD_ICR_P12_Pos                       24                                                      /*!< PCD ICR: P12 Position                   */
#define PCD_ICR_P12_Msk                       (0x03UL << PCD_ICR_P12_Pos)                             /*!< PCD ICR: P12 Mask                       */
#define PCD_ICR_P13_Pos                       26                                                      /*!< PCD ICR: P13 Position                   */
#define PCD_ICR_P13_Msk                       (0x03UL << PCD_ICR_P13_Pos)                             /*!< PCD ICR: P13 Mask                       */
#define PCD_ICR_P14_Pos                       28                                                      /*!< PCD ICR: P14 Position                   */
#define PCD_ICR_P14_Msk                       (0x03UL << PCD_ICR_P14_Pos)                             /*!< PCD ICR: P14 Mask                       */
#define PCD_ICR_P15_Pos                       30                                                      /*!< PCD ICR: P15 Position                   */
#define PCD_ICR_P15_Msk                       (0x03UL << PCD_ICR_P15_Pos)                             /*!< PCD ICR: P15 Mask                       */

/* -----------------------------------  PCD_DPR  ---------------------------------- */
#define PCD_DPR_DPR_Pos                       0                                                       /*!< PCD DPR: DPR Position                   */
#define PCD_DPR_DPR_Msk                       (0x1fUL << PCD_DPR_DPR_Pos)                             /*!< PCD DPR: DPR Mask                       */


/* ================================================================================ */
/* ================          struct 'PCE' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  PCE_MR  ----------------------------------- */
#define PCE_MR_P0_Pos                         0                                                       /*!< PCE MR: P0 Position                     */
#define PCE_MR_P0_Msk                         (0x03UL << PCE_MR_P0_Pos)                               /*!< PCE MR: P0 Mask                         */
#define PCE_MR_P1_Pos                         2                                                       /*!< PCE MR: P1 Position                     */
#define PCE_MR_P1_Msk                         (0x03UL << PCE_MR_P1_Pos)                               /*!< PCE MR: P1 Mask                         */
#define PCE_MR_P2_Pos                         4                                                       /*!< PCE MR: P2 Position                     */
#define PCE_MR_P2_Msk                         (0x03UL << PCE_MR_P2_Pos)                               /*!< PCE MR: P2 Mask                         */
#define PCE_MR_P3_Pos                         6                                                       /*!< PCE MR: P3 Position                     */
#define PCE_MR_P3_Msk                         (0x03UL << PCE_MR_P3_Pos)                               /*!< PCE MR: P3 Mask                         */
#define PCE_MR_P4_Pos                         8                                                       /*!< PCE MR: P4 Position                     */
#define PCE_MR_P4_Msk                         (0x03UL << PCE_MR_P4_Pos)                               /*!< PCE MR: P4 Mask                         */
#define PCE_MR_P5_Pos                         10                                                      /*!< PCE MR: P5 Position                     */
#define PCE_MR_P5_Msk                         (0x03UL << PCE_MR_P5_Pos)                               /*!< PCE MR: P5 Mask                         */
#define PCE_MR_P6_Pos                         12                                                      /*!< PCE MR: P6 Position                     */
#define PCE_MR_P6_Msk                         (0x03UL << PCE_MR_P6_Pos)                               /*!< PCE MR: P6 Mask                         */
#define PCE_MR_P7_Pos                         14                                                      /*!< PCE MR: P7 Position                     */
#define PCE_MR_P7_Msk                         (0x03UL << PCE_MR_P7_Pos)                               /*!< PCE MR: P7 Mask                         */
#define PCE_MR_P8_Pos                         16                                                      /*!< PCE MR: P8 Position                     */
#define PCE_MR_P8_Msk                         (0x03UL << PCE_MR_P8_Pos)                               /*!< PCE MR: P8 Mask                         */
#define PCE_MR_P9_Pos                         18                                                      /*!< PCE MR: P9 Position                     */
#define PCE_MR_P9_Msk                         (0x03UL << PCE_MR_P9_Pos)                               /*!< PCE MR: P9 Mask                         */
#define PCE_MR_P10_Pos                        20                                                      /*!< PCE MR: P10 Position                    */
#define PCE_MR_P10_Msk                        (0x03UL << PCE_MR_P10_Pos)                              /*!< PCE MR: P10 Mask                        */
#define PCE_MR_P11_Pos                        22                                                      /*!< PCE MR: P11 Position                    */
#define PCE_MR_P11_Msk                        (0x03UL << PCE_MR_P11_Pos)                              /*!< PCE MR: P11 Mask                        */
#define PCE_MR_P12_Pos                        24                                                      /*!< PCE MR: P12 Position                    */
#define PCE_MR_P12_Msk                        (0x03UL << PCE_MR_P12_Pos)                              /*!< PCE MR: P12 Mask                        */
#define PCE_MR_P13_Pos                        26                                                      /*!< PCE MR: P13 Position                    */
#define PCE_MR_P13_Msk                        (0x03UL << PCE_MR_P13_Pos)                              /*!< PCE MR: P13 Mask                        */
#define PCE_MR_P14_Pos                        28                                                      /*!< PCE MR: P14 Position                    */
#define PCE_MR_P14_Msk                        (0x03UL << PCE_MR_P14_Pos)                              /*!< PCE MR: P14 Mask                        */
#define PCE_MR_P15_Pos                        30                                                      /*!< PCE MR: P15 Position                    */
#define PCE_MR_P15_Msk                        (0x03UL << PCE_MR_P15_Pos)                              /*!< PCE MR: P15 Mask                        */

/* -----------------------------------  PCE_CR  ----------------------------------- */
#define PCE_CR_P0_Pos                         0                                                       /*!< PCE CR: P0 Position                     */
#define PCE_CR_P0_Msk                         (0x03UL << PCE_CR_P0_Pos)                               /*!< PCE CR: P0 Mask                         */
#define PCE_CR_P1_Pos                         2                                                       /*!< PCE CR: P1 Position                     */
#define PCE_CR_P1_Msk                         (0x03UL << PCE_CR_P1_Pos)                               /*!< PCE CR: P1 Mask                         */
#define PCE_CR_P2_Pos                         4                                                       /*!< PCE CR: P2 Position                     */
#define PCE_CR_P2_Msk                         (0x03UL << PCE_CR_P2_Pos)                               /*!< PCE CR: P2 Mask                         */
#define PCE_CR_P3_Pos                         6                                                       /*!< PCE CR: P3 Position                     */
#define PCE_CR_P3_Msk                         (0x03UL << PCE_CR_P3_Pos)                               /*!< PCE CR: P3 Mask                         */
#define PCE_CR_P4_Pos                         8                                                       /*!< PCE CR: P4 Position                     */
#define PCE_CR_P4_Msk                         (0x03UL << PCE_CR_P4_Pos)                               /*!< PCE CR: P4 Mask                         */
#define PCE_CR_P5_Pos                         10                                                      /*!< PCE CR: P5 Position                     */
#define PCE_CR_P5_Msk                         (0x03UL << PCE_CR_P5_Pos)                               /*!< PCE CR: P5 Mask                         */
#define PCE_CR_P6_Pos                         12                                                      /*!< PCE CR: P6 Position                     */
#define PCE_CR_P6_Msk                         (0x03UL << PCE_CR_P6_Pos)                               /*!< PCE CR: P6 Mask                         */
#define PCE_CR_P7_Pos                         14                                                      /*!< PCE CR: P7 Position                     */
#define PCE_CR_P7_Msk                         (0x03UL << PCE_CR_P7_Pos)                               /*!< PCE CR: P7 Mask                         */
#define PCE_CR_P8_Pos                         16                                                      /*!< PCE CR: P8 Position                     */
#define PCE_CR_P8_Msk                         (0x03UL << PCE_CR_P8_Pos)                               /*!< PCE CR: P8 Mask                         */
#define PCE_CR_P9_Pos                         18                                                      /*!< PCE CR: P9 Position                     */
#define PCE_CR_P9_Msk                         (0x03UL << PCE_CR_P9_Pos)                               /*!< PCE CR: P9 Mask                         */
#define PCE_CR_P10_Pos                        20                                                      /*!< PCE CR: P10 Position                    */
#define PCE_CR_P10_Msk                        (0x03UL << PCE_CR_P10_Pos)                              /*!< PCE CR: P10 Mask                        */
#define PCE_CR_P11_Pos                        22                                                      /*!< PCE CR: P11 Position                    */
#define PCE_CR_P11_Msk                        (0x03UL << PCE_CR_P11_Pos)                              /*!< PCE CR: P11 Mask                        */
#define PCE_CR_P12_Pos                        24                                                      /*!< PCE CR: P12 Position                    */
#define PCE_CR_P12_Msk                        (0x03UL << PCE_CR_P12_Pos)                              /*!< PCE CR: P12 Mask                        */
#define PCE_CR_P13_Pos                        26                                                      /*!< PCE CR: P13 Position                    */
#define PCE_CR_P13_Msk                        (0x03UL << PCE_CR_P13_Pos)                              /*!< PCE CR: P13 Mask                        */
#define PCE_CR_P14_Pos                        28                                                      /*!< PCE CR: P14 Position                    */
#define PCE_CR_P14_Msk                        (0x03UL << PCE_CR_P14_Pos)                              /*!< PCE CR: P14 Mask                        */
#define PCE_CR_P15_Pos                        30                                                      /*!< PCE CR: P15 Position                    */
#define PCE_CR_P15_Msk                        (0x03UL << PCE_CR_P15_Pos)                              /*!< PCE CR: P15 Mask                        */

/* -----------------------------------  PCE_PCR  ---------------------------------- */
#define PCE_PCR_P0_Pos                        0                                                       /*!< PCE PCR: P0 Position                    */
#define PCE_PCR_P0_Msk                        (0x01UL << PCE_PCR_P0_Pos)                              /*!< PCE PCR: P0 Mask                        */
#define PCE_PCR_P1_Pos                        1                                                       /*!< PCE PCR: P1 Position                    */
#define PCE_PCR_P1_Msk                        (0x01UL << PCE_PCR_P1_Pos)                              /*!< PCE PCR: P1 Mask                        */
#define PCE_PCR_P2_Pos                        2                                                       /*!< PCE PCR: P2 Position                    */
#define PCE_PCR_P2_Msk                        (0x01UL << PCE_PCR_P2_Pos)                              /*!< PCE PCR: P2 Mask                        */
#define PCE_PCR_P3_Pos                        3                                                       /*!< PCE PCR: P3 Position                    */
#define PCE_PCR_P3_Msk                        (0x01UL << PCE_PCR_P3_Pos)                              /*!< PCE PCR: P3 Mask                        */
#define PCE_PCR_P4_Pos                        4                                                       /*!< PCE PCR: P4 Position                    */
#define PCE_PCR_P4_Msk                        (0x01UL << PCE_PCR_P4_Pos)                              /*!< PCE PCR: P4 Mask                        */
#define PCE_PCR_P5_Pos                        5                                                       /*!< PCE PCR: P5 Position                    */
#define PCE_PCR_P5_Msk                        (0x01UL << PCE_PCR_P5_Pos)                              /*!< PCE PCR: P5 Mask                        */
#define PCE_PCR_P6_Pos                        6                                                       /*!< PCE PCR: P6 Position                    */
#define PCE_PCR_P6_Msk                        (0x01UL << PCE_PCR_P6_Pos)                              /*!< PCE PCR: P6 Mask                        */
#define PCE_PCR_P7_Pos                        7                                                       /*!< PCE PCR: P7 Position                    */
#define PCE_PCR_P7_Msk                        (0x01UL << PCE_PCR_P7_Pos)                              /*!< PCE PCR: P7 Mask                        */
#define PCE_PCR_P8_Pos                        8                                                       /*!< PCE PCR: P8 Position                    */
#define PCE_PCR_P8_Msk                        (0x01UL << PCE_PCR_P8_Pos)                              /*!< PCE PCR: P8 Mask                        */
#define PCE_PCR_P9_Pos                        9                                                       /*!< PCE PCR: P9 Position                    */
#define PCE_PCR_P9_Msk                        (0x01UL << PCE_PCR_P9_Pos)                              /*!< PCE PCR: P9 Mask                        */
#define PCE_PCR_P10_Pos                       10                                                      /*!< PCE PCR: P10 Position                   */
#define PCE_PCR_P10_Msk                       (0x01UL << PCE_PCR_P10_Pos)                             /*!< PCE PCR: P10 Mask                       */
#define PCE_PCR_P11_Pos                       11                                                      /*!< PCE PCR: P11 Position                   */
#define PCE_PCR_P11_Msk                       (0x01UL << PCE_PCR_P11_Pos)                             /*!< PCE PCR: P11 Mask                       */
#define PCE_PCR_P12_Pos                       12                                                      /*!< PCE PCR: P12 Position                   */
#define PCE_PCR_P12_Msk                       (0x01UL << PCE_PCR_P12_Pos)                             /*!< PCE PCR: P12 Mask                       */
#define PCE_PCR_P13_Pos                       13                                                      /*!< PCE PCR: P13 Position                   */
#define PCE_PCR_P13_Msk                       (0x01UL << PCE_PCR_P13_Pos)                             /*!< PCE PCR: P13 Mask                       */
#define PCE_PCR_P14_Pos                       14                                                      /*!< PCE PCR: P14 Position                   */
#define PCE_PCR_P14_Msk                       (0x01UL << PCE_PCR_P14_Pos)                             /*!< PCE PCR: P14 Mask                       */
#define PCE_PCR_P15_Pos                       15                                                      /*!< PCE PCR: P15 Position                   */
#define PCE_PCR_P15_Msk                       (0x01UL << PCE_PCR_P15_Pos)                             /*!< PCE PCR: P15 Mask                       */
#define PCE_PCR_D0_Pos                        16                                                      /*!< PCE PCR: D0 Position                    */
#define PCE_PCR_D0_Msk                        (0x01UL << PCE_PCR_D0_Pos)                              /*!< PCE PCR: D0 Mask                        */
#define PCE_PCR_D1_Pos                        17                                                      /*!< PCE PCR: D1 Position                    */
#define PCE_PCR_D1_Msk                        (0x01UL << PCE_PCR_D1_Pos)                              /*!< PCE PCR: D1 Mask                        */
#define PCE_PCR_D2_Pos                        18                                                      /*!< PCE PCR: D2 Position                    */
#define PCE_PCR_D2_Msk                        (0x01UL << PCE_PCR_D2_Pos)                              /*!< PCE PCR: D2 Mask                        */
#define PCE_PCR_D3_Pos                        19                                                      /*!< PCE PCR: D3 Position                    */
#define PCE_PCR_D3_Msk                        (0x01UL << PCE_PCR_D3_Pos)                              /*!< PCE PCR: D3 Mask                        */
#define PCE_PCR_D4_Pos                        20                                                      /*!< PCE PCR: D4 Position                    */
#define PCE_PCR_D4_Msk                        (0x01UL << PCE_PCR_D4_Pos)                              /*!< PCE PCR: D4 Mask                        */
#define PCE_PCR_D5_Pos                        21                                                      /*!< PCE PCR: D5 Position                    */
#define PCE_PCR_D5_Msk                        (0x01UL << PCE_PCR_D5_Pos)                              /*!< PCE PCR: D5 Mask                        */
#define PCE_PCR_D6_Pos                        22                                                      /*!< PCE PCR: D6 Position                    */
#define PCE_PCR_D6_Msk                        (0x01UL << PCE_PCR_D6_Pos)                              /*!< PCE PCR: D6 Mask                        */
#define PCE_PCR_D7_Pos                        23                                                      /*!< PCE PCR: D7 Position                    */
#define PCE_PCR_D7_Msk                        (0x01UL << PCE_PCR_D7_Pos)                              /*!< PCE PCR: D7 Mask                        */
#define PCE_PCR_D8_Pos                        24                                                      /*!< PCE PCR: D8 Position                    */
#define PCE_PCR_D8_Msk                        (0x01UL << PCE_PCR_D8_Pos)                              /*!< PCE PCR: D8 Mask                        */
#define PCE_PCR_D9_Pos                        25                                                      /*!< PCE PCR: D9 Position                    */
#define PCE_PCR_D9_Msk                        (0x01UL << PCE_PCR_D9_Pos)                              /*!< PCE PCR: D9 Mask                        */
#define PCE_PCR_D10_Pos                       26                                                      /*!< PCE PCR: D10 Position                   */
#define PCE_PCR_D10_Msk                       (0x01UL << PCE_PCR_D10_Pos)                             /*!< PCE PCR: D10 Mask                       */
#define PCE_PCR_D11_Pos                       27                                                      /*!< PCE PCR: D11 Position                   */
#define PCE_PCR_D11_Msk                       (0x01UL << PCE_PCR_D11_Pos)                             /*!< PCE PCR: D11 Mask                       */
#define PCE_PCR_D12_Pos                       28                                                      /*!< PCE PCR: D12 Position                   */
#define PCE_PCR_D12_Msk                       (0x01UL << PCE_PCR_D12_Pos)                             /*!< PCE PCR: D12 Mask                       */
#define PCE_PCR_D13_Pos                       29                                                      /*!< PCE PCR: D13 Position                   */
#define PCE_PCR_D13_Msk                       (0x01UL << PCE_PCR_D13_Pos)                             /*!< PCE PCR: D13 Mask                       */
#define PCE_PCR_D14_Pos                       30                                                      /*!< PCE PCR: D14 Position                   */
#define PCE_PCR_D14_Msk                       (0x01UL << PCE_PCR_D14_Pos)                             /*!< PCE PCR: D14 Mask                       */
#define PCE_PCR_D15_Pos                       31                                                      /*!< PCE PCR: D15 Position                   */
#define PCE_PCR_D15_Msk                       (0x01UL << PCE_PCR_D15_Pos)                             /*!< PCE PCR: D15 Mask                       */

/* -----------------------------------  PCE_DER  ---------------------------------- */
#define PCE_DER_P0_Pos                        0                                                       /*!< PCE DER: P0 Position                    */
#define PCE_DER_P0_Msk                        (0x01UL << PCE_DER_P0_Pos)                              /*!< PCE DER: P0 Mask                        */
#define PCE_DER_P1_Pos                        1                                                       /*!< PCE DER: P1 Position                    */
#define PCE_DER_P1_Msk                        (0x01UL << PCE_DER_P1_Pos)                              /*!< PCE DER: P1 Mask                        */
#define PCE_DER_P2_Pos                        2                                                       /*!< PCE DER: P2 Position                    */
#define PCE_DER_P2_Msk                        (0x01UL << PCE_DER_P2_Pos)                              /*!< PCE DER: P2 Mask                        */
#define PCE_DER_P3_Pos                        3                                                       /*!< PCE DER: P3 Position                    */
#define PCE_DER_P3_Msk                        (0x01UL << PCE_DER_P3_Pos)                              /*!< PCE DER: P3 Mask                        */
#define PCE_DER_P4_Pos                        4                                                       /*!< PCE DER: P4 Position                    */
#define PCE_DER_P4_Msk                        (0x01UL << PCE_DER_P4_Pos)                              /*!< PCE DER: P4 Mask                        */
#define PCE_DER_P5_Pos                        5                                                       /*!< PCE DER: P5 Position                    */
#define PCE_DER_P5_Msk                        (0x01UL << PCE_DER_P5_Pos)                              /*!< PCE DER: P5 Mask                        */
#define PCE_DER_P6_Pos                        6                                                       /*!< PCE DER: P6 Position                    */
#define PCE_DER_P6_Msk                        (0x01UL << PCE_DER_P6_Pos)                              /*!< PCE DER: P6 Mask                        */
#define PCE_DER_P7_Pos                        7                                                       /*!< PCE DER: P7 Position                    */
#define PCE_DER_P7_Msk                        (0x01UL << PCE_DER_P7_Pos)                              /*!< PCE DER: P7 Mask                        */
#define PCE_DER_P8_Pos                        8                                                       /*!< PCE DER: P8 Position                    */
#define PCE_DER_P8_Msk                        (0x01UL << PCE_DER_P8_Pos)                              /*!< PCE DER: P8 Mask                        */
#define PCE_DER_P9_Pos                        9                                                       /*!< PCE DER: P9 Position                    */
#define PCE_DER_P9_Msk                        (0x01UL << PCE_DER_P9_Pos)                              /*!< PCE DER: P9 Mask                        */
#define PCE_DER_P10_Pos                       10                                                      /*!< PCE DER: P10 Position                   */
#define PCE_DER_P10_Msk                       (0x01UL << PCE_DER_P10_Pos)                             /*!< PCE DER: P10 Mask                       */
#define PCE_DER_P11_Pos                       11                                                      /*!< PCE DER: P11 Position                   */
#define PCE_DER_P11_Msk                       (0x01UL << PCE_DER_P11_Pos)                             /*!< PCE DER: P11 Mask                       */
#define PCE_DER_P12_Pos                       12                                                      /*!< PCE DER: P12 Position                   */
#define PCE_DER_P12_Msk                       (0x01UL << PCE_DER_P12_Pos)                             /*!< PCE DER: P12 Mask                       */
#define PCE_DER_P13_Pos                       13                                                      /*!< PCE DER: P13 Position                   */
#define PCE_DER_P13_Msk                       (0x01UL << PCE_DER_P13_Pos)                             /*!< PCE DER: P13 Mask                       */
#define PCE_DER_P14_Pos                       14                                                      /*!< PCE DER: P14 Position                   */
#define PCE_DER_P14_Msk                       (0x01UL << PCE_DER_P14_Pos)                             /*!< PCE DER: P14 Mask                       */
#define PCE_DER_P15_Pos                       15                                                      /*!< PCE DER: P15 Position                   */
#define PCE_DER_P15_Msk                       (0x01UL << PCE_DER_P15_Pos)                             /*!< PCE DER: P15 Mask                       */

/* -----------------------------------  PCE_IER  ---------------------------------- */
#define PCE_IER_P0_Pos                        0                                                       /*!< PCE IER: P0 Position                    */
#define PCE_IER_P0_Msk                        (0x03UL << PCE_IER_P0_Pos)                              /*!< PCE IER: P0 Mask                        */
#define PCE_IER_P1_Pos                        2                                                       /*!< PCE IER: P1 Position                    */
#define PCE_IER_P1_Msk                        (0x03UL << PCE_IER_P1_Pos)                              /*!< PCE IER: P1 Mask                        */
#define PCE_IER_P2_Pos                        4                                                       /*!< PCE IER: P2 Position                    */
#define PCE_IER_P2_Msk                        (0x03UL << PCE_IER_P2_Pos)                              /*!< PCE IER: P2 Mask                        */
#define PCE_IER_P3_Pos                        6                                                       /*!< PCE IER: P3 Position                    */
#define PCE_IER_P3_Msk                        (0x03UL << PCE_IER_P3_Pos)                              /*!< PCE IER: P3 Mask                        */
#define PCE_IER_P4_Pos                        8                                                       /*!< PCE IER: P4 Position                    */
#define PCE_IER_P4_Msk                        (0x03UL << PCE_IER_P4_Pos)                              /*!< PCE IER: P4 Mask                        */
#define PCE_IER_P5_Pos                        10                                                      /*!< PCE IER: P5 Position                    */
#define PCE_IER_P5_Msk                        (0x03UL << PCE_IER_P5_Pos)                              /*!< PCE IER: P5 Mask                        */
#define PCE_IER_P6_Pos                        12                                                      /*!< PCE IER: P6 Position                    */
#define PCE_IER_P6_Msk                        (0x03UL << PCE_IER_P6_Pos)                              /*!< PCE IER: P6 Mask                        */
#define PCE_IER_P7_Pos                        14                                                      /*!< PCE IER: P7 Position                    */
#define PCE_IER_P7_Msk                        (0x03UL << PCE_IER_P7_Pos)                              /*!< PCE IER: P7 Mask                        */
#define PCE_IER_P8_Pos                        16                                                      /*!< PCE IER: P8 Position                    */
#define PCE_IER_P8_Msk                        (0x03UL << PCE_IER_P8_Pos)                              /*!< PCE IER: P8 Mask                        */
#define PCE_IER_P9_Pos                        18                                                      /*!< PCE IER: P9 Position                    */
#define PCE_IER_P9_Msk                        (0x03UL << PCE_IER_P9_Pos)                              /*!< PCE IER: P9 Mask                        */
#define PCE_IER_P10_Pos                       20                                                      /*!< PCE IER: P10 Position                   */
#define PCE_IER_P10_Msk                       (0x03UL << PCE_IER_P10_Pos)                             /*!< PCE IER: P10 Mask                       */
#define PCE_IER_P11_Pos                       22                                                      /*!< PCE IER: P11 Position                   */
#define PCE_IER_P11_Msk                       (0x03UL << PCE_IER_P11_Pos)                             /*!< PCE IER: P11 Mask                       */
#define PCE_IER_P12_Pos                       24                                                      /*!< PCE IER: P12 Position                   */
#define PCE_IER_P12_Msk                       (0x03UL << PCE_IER_P12_Pos)                             /*!< PCE IER: P12 Mask                       */
#define PCE_IER_P13_Pos                       26                                                      /*!< PCE IER: P13 Position                   */
#define PCE_IER_P13_Msk                       (0x03UL << PCE_IER_P13_Pos)                             /*!< PCE IER: P13 Mask                       */
#define PCE_IER_P14_Pos                       28                                                      /*!< PCE IER: P14 Position                   */
#define PCE_IER_P14_Msk                       (0x03UL << PCE_IER_P14_Pos)                             /*!< PCE IER: P14 Mask                       */
#define PCE_IER_P15_Pos                       30                                                      /*!< PCE IER: P15 Position                   */
#define PCE_IER_P15_Msk                       (0x03UL << PCE_IER_P15_Pos)                             /*!< PCE IER: P15 Mask                       */

/* -----------------------------------  PCE_ISR  ---------------------------------- */
#define PCE_ISR_P0_Pos                        0                                                       /*!< PCE ISR: P0 Position                    */
#define PCE_ISR_P0_Msk                        (0x03UL << PCE_ISR_P0_Pos)                              /*!< PCE ISR: P0 Mask                        */
#define PCE_ISR_P1_Pos                        2                                                       /*!< PCE ISR: P1 Position                    */
#define PCE_ISR_P1_Msk                        (0x03UL << PCE_ISR_P1_Pos)                              /*!< PCE ISR: P1 Mask                        */
#define PCE_ISR_P2_Pos                        4                                                       /*!< PCE ISR: P2 Position                    */
#define PCE_ISR_P2_Msk                        (0x03UL << PCE_ISR_P2_Pos)                              /*!< PCE ISR: P2 Mask                        */
#define PCE_ISR_P3_Pos                        6                                                       /*!< PCE ISR: P3 Position                    */
#define PCE_ISR_P3_Msk                        (0x03UL << PCE_ISR_P3_Pos)                              /*!< PCE ISR: P3 Mask                        */
#define PCE_ISR_P4_Pos                        8                                                       /*!< PCE ISR: P4 Position                    */
#define PCE_ISR_P4_Msk                        (0x03UL << PCE_ISR_P4_Pos)                              /*!< PCE ISR: P4 Mask                        */
#define PCE_ISR_P5_Pos                        10                                                      /*!< PCE ISR: P5 Position                    */
#define PCE_ISR_P5_Msk                        (0x03UL << PCE_ISR_P5_Pos)                              /*!< PCE ISR: P5 Mask                        */
#define PCE_ISR_P6_Pos                        12                                                      /*!< PCE ISR: P6 Position                    */
#define PCE_ISR_P6_Msk                        (0x03UL << PCE_ISR_P6_Pos)                              /*!< PCE ISR: P6 Mask                        */
#define PCE_ISR_P7_Pos                        14                                                      /*!< PCE ISR: P7 Position                    */
#define PCE_ISR_P7_Msk                        (0x03UL << PCE_ISR_P7_Pos)                              /*!< PCE ISR: P7 Mask                        */
#define PCE_ISR_P8_Pos                        16                                                      /*!< PCE ISR: P8 Position                    */
#define PCE_ISR_P8_Msk                        (0x03UL << PCE_ISR_P8_Pos)                              /*!< PCE ISR: P8 Mask                        */
#define PCE_ISR_P9_Pos                        18                                                      /*!< PCE ISR: P9 Position                    */
#define PCE_ISR_P9_Msk                        (0x03UL << PCE_ISR_P9_Pos)                              /*!< PCE ISR: P9 Mask                        */
#define PCE_ISR_P10_Pos                       20                                                      /*!< PCE ISR: P10 Position                   */
#define PCE_ISR_P10_Msk                       (0x03UL << PCE_ISR_P10_Pos)                             /*!< PCE ISR: P10 Mask                       */
#define PCE_ISR_P11_Pos                       22                                                      /*!< PCE ISR: P11 Position                   */
#define PCE_ISR_P11_Msk                       (0x03UL << PCE_ISR_P11_Pos)                             /*!< PCE ISR: P11 Mask                       */
#define PCE_ISR_P12_Pos                       24                                                      /*!< PCE ISR: P12 Position                   */
#define PCE_ISR_P12_Msk                       (0x03UL << PCE_ISR_P12_Pos)                             /*!< PCE ISR: P12 Mask                       */
#define PCE_ISR_P13_Pos                       26                                                      /*!< PCE ISR: P13 Position                   */
#define PCE_ISR_P13_Msk                       (0x03UL << PCE_ISR_P13_Pos)                             /*!< PCE ISR: P13 Mask                       */
#define PCE_ISR_P14_Pos                       28                                                      /*!< PCE ISR: P14 Position                   */
#define PCE_ISR_P14_Msk                       (0x03UL << PCE_ISR_P14_Pos)                             /*!< PCE ISR: P14 Mask                       */
#define PCE_ISR_P15_Pos                       30                                                      /*!< PCE ISR: P15 Position                   */
#define PCE_ISR_P15_Msk                       (0x03UL << PCE_ISR_P15_Pos)                             /*!< PCE ISR: P15 Mask                       */

/* -----------------------------------  PCE_ICR  ---------------------------------- */
#define PCE_ICR_P0_Pos                        0                                                       /*!< PCE ICR: P0 Position                    */
#define PCE_ICR_P0_Msk                        (0x03UL << PCE_ICR_P0_Pos)                              /*!< PCE ICR: P0 Mask                        */
#define PCE_ICR_P1_Pos                        2                                                       /*!< PCE ICR: P1 Position                    */
#define PCE_ICR_P1_Msk                        (0x03UL << PCE_ICR_P1_Pos)                              /*!< PCE ICR: P1 Mask                        */
#define PCE_ICR_P2_Pos                        4                                                       /*!< PCE ICR: P2 Position                    */
#define PCE_ICR_P2_Msk                        (0x03UL << PCE_ICR_P2_Pos)                              /*!< PCE ICR: P2 Mask                        */
#define PCE_ICR_P3_Pos                        6                                                       /*!< PCE ICR: P3 Position                    */
#define PCE_ICR_P3_Msk                        (0x03UL << PCE_ICR_P3_Pos)                              /*!< PCE ICR: P3 Mask                        */
#define PCE_ICR_P4_Pos                        8                                                       /*!< PCE ICR: P4 Position                    */
#define PCE_ICR_P4_Msk                        (0x03UL << PCE_ICR_P4_Pos)                              /*!< PCE ICR: P4 Mask                        */
#define PCE_ICR_P5_Pos                        10                                                      /*!< PCE ICR: P5 Position                    */
#define PCE_ICR_P5_Msk                        (0x03UL << PCE_ICR_P5_Pos)                              /*!< PCE ICR: P5 Mask                        */
#define PCE_ICR_P6_Pos                        12                                                      /*!< PCE ICR: P6 Position                    */
#define PCE_ICR_P6_Msk                        (0x03UL << PCE_ICR_P6_Pos)                              /*!< PCE ICR: P6 Mask                        */
#define PCE_ICR_P7_Pos                        14                                                      /*!< PCE ICR: P7 Position                    */
#define PCE_ICR_P7_Msk                        (0x03UL << PCE_ICR_P7_Pos)                              /*!< PCE ICR: P7 Mask                        */
#define PCE_ICR_P8_Pos                        16                                                      /*!< PCE ICR: P8 Position                    */
#define PCE_ICR_P8_Msk                        (0x03UL << PCE_ICR_P8_Pos)                              /*!< PCE ICR: P8 Mask                        */
#define PCE_ICR_P9_Pos                        18                                                      /*!< PCE ICR: P9 Position                    */
#define PCE_ICR_P9_Msk                        (0x03UL << PCE_ICR_P9_Pos)                              /*!< PCE ICR: P9 Mask                        */
#define PCE_ICR_P10_Pos                       20                                                      /*!< PCE ICR: P10 Position                   */
#define PCE_ICR_P10_Msk                       (0x03UL << PCE_ICR_P10_Pos)                             /*!< PCE ICR: P10 Mask                       */
#define PCE_ICR_P11_Pos                       22                                                      /*!< PCE ICR: P11 Position                   */
#define PCE_ICR_P11_Msk                       (0x03UL << PCE_ICR_P11_Pos)                             /*!< PCE ICR: P11 Mask                       */
#define PCE_ICR_P12_Pos                       24                                                      /*!< PCE ICR: P12 Position                   */
#define PCE_ICR_P12_Msk                       (0x03UL << PCE_ICR_P12_Pos)                             /*!< PCE ICR: P12 Mask                       */
#define PCE_ICR_P13_Pos                       26                                                      /*!< PCE ICR: P13 Position                   */
#define PCE_ICR_P13_Msk                       (0x03UL << PCE_ICR_P13_Pos)                             /*!< PCE ICR: P13 Mask                       */
#define PCE_ICR_P14_Pos                       28                                                      /*!< PCE ICR: P14 Position                   */
#define PCE_ICR_P14_Msk                       (0x03UL << PCE_ICR_P14_Pos)                             /*!< PCE ICR: P14 Mask                       */
#define PCE_ICR_P15_Pos                       30                                                      /*!< PCE ICR: P15 Position                   */
#define PCE_ICR_P15_Msk                       (0x03UL << PCE_ICR_P15_Pos)                             /*!< PCE ICR: P15 Mask                       */

/* -----------------------------------  PCE_DPR  ---------------------------------- */
#define PCE_DPR_DPR_Pos                       0                                                       /*!< PCE DPR: DPR Position                   */
#define PCE_DPR_DPR_Msk                       (0x1fUL << PCE_DPR_DPR_Pos)                             /*!< PCE DPR: DPR Mask                       */


/* ================================================================================ */
/* ================          struct 'PCF' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  PCF_MR  ----------------------------------- */
#define PCF_MR_P0_Pos                         0                                                       /*!< PCF MR: P0 Position                     */
#define PCF_MR_P0_Msk                         (0x03UL << PCF_MR_P0_Pos)                               /*!< PCF MR: P0 Mask                         */
#define PCF_MR_P1_Pos                         2                                                       /*!< PCF MR: P1 Position                     */
#define PCF_MR_P1_Msk                         (0x03UL << PCF_MR_P1_Pos)                               /*!< PCF MR: P1 Mask                         */
#define PCF_MR_P2_Pos                         4                                                       /*!< PCF MR: P2 Position                     */
#define PCF_MR_P2_Msk                         (0x03UL << PCF_MR_P2_Pos)                               /*!< PCF MR: P2 Mask                         */
#define PCF_MR_P3_Pos                         6                                                       /*!< PCF MR: P3 Position                     */
#define PCF_MR_P3_Msk                         (0x03UL << PCF_MR_P3_Pos)                               /*!< PCF MR: P3 Mask                         */
#define PCF_MR_P4_Pos                         8                                                       /*!< PCF MR: P4 Position                     */
#define PCF_MR_P4_Msk                         (0x03UL << PCF_MR_P4_Pos)                               /*!< PCF MR: P4 Mask                         */
#define PCF_MR_P5_Pos                         10                                                      /*!< PCF MR: P5 Position                     */
#define PCF_MR_P5_Msk                         (0x03UL << PCF_MR_P5_Pos)                               /*!< PCF MR: P5 Mask                         */
#define PCF_MR_P6_Pos                         12                                                      /*!< PCF MR: P6 Position                     */
#define PCF_MR_P6_Msk                         (0x03UL << PCF_MR_P6_Pos)                               /*!< PCF MR: P6 Mask                         */
#define PCF_MR_P7_Pos                         14                                                      /*!< PCF MR: P7 Position                     */
#define PCF_MR_P7_Msk                         (0x03UL << PCF_MR_P7_Pos)                               /*!< PCF MR: P7 Mask                         */
#define PCF_MR_P8_Pos                         16                                                      /*!< PCF MR: P8 Position                     */
#define PCF_MR_P8_Msk                         (0x03UL << PCF_MR_P8_Pos)                               /*!< PCF MR: P8 Mask                         */
#define PCF_MR_P9_Pos                         18                                                      /*!< PCF MR: P9 Position                     */
#define PCF_MR_P9_Msk                         (0x03UL << PCF_MR_P9_Pos)                               /*!< PCF MR: P9 Mask                         */
#define PCF_MR_P10_Pos                        20                                                      /*!< PCF MR: P10 Position                    */
#define PCF_MR_P10_Msk                        (0x03UL << PCF_MR_P10_Pos)                              /*!< PCF MR: P10 Mask                        */
#define PCF_MR_P11_Pos                        22                                                      /*!< PCF MR: P11 Position                    */
#define PCF_MR_P11_Msk                        (0x03UL << PCF_MR_P11_Pos)                              /*!< PCF MR: P11 Mask                        */
#define PCF_MR_P12_Pos                        24                                                      /*!< PCF MR: P12 Position                    */
#define PCF_MR_P12_Msk                        (0x03UL << PCF_MR_P12_Pos)                              /*!< PCF MR: P12 Mask                        */
#define PCF_MR_P13_Pos                        26                                                      /*!< PCF MR: P13 Position                    */
#define PCF_MR_P13_Msk                        (0x03UL << PCF_MR_P13_Pos)                              /*!< PCF MR: P13 Mask                        */
#define PCF_MR_P14_Pos                        28                                                      /*!< PCF MR: P14 Position                    */
#define PCF_MR_P14_Msk                        (0x03UL << PCF_MR_P14_Pos)                              /*!< PCF MR: P14 Mask                        */
#define PCF_MR_P15_Pos                        30                                                      /*!< PCF MR: P15 Position                    */
#define PCF_MR_P15_Msk                        (0x03UL << PCF_MR_P15_Pos)                              /*!< PCF MR: P15 Mask                        */

/* -----------------------------------  PCF_CR  ----------------------------------- */
#define PCF_CR_P0_Pos                         0                                                       /*!< PCF CR: P0 Position                     */
#define PCF_CR_P0_Msk                         (0x03UL << PCF_CR_P0_Pos)                               /*!< PCF CR: P0 Mask                         */
#define PCF_CR_P1_Pos                         2                                                       /*!< PCF CR: P1 Position                     */
#define PCF_CR_P1_Msk                         (0x03UL << PCF_CR_P1_Pos)                               /*!< PCF CR: P1 Mask                         */
#define PCF_CR_P2_Pos                         4                                                       /*!< PCF CR: P2 Position                     */
#define PCF_CR_P2_Msk                         (0x03UL << PCF_CR_P2_Pos)                               /*!< PCF CR: P2 Mask                         */
#define PCF_CR_P3_Pos                         6                                                       /*!< PCF CR: P3 Position                     */
#define PCF_CR_P3_Msk                         (0x03UL << PCF_CR_P3_Pos)                               /*!< PCF CR: P3 Mask                         */
#define PCF_CR_P4_Pos                         8                                                       /*!< PCF CR: P4 Position                     */
#define PCF_CR_P4_Msk                         (0x03UL << PCF_CR_P4_Pos)                               /*!< PCF CR: P4 Mask                         */
#define PCF_CR_P5_Pos                         10                                                      /*!< PCF CR: P5 Position                     */
#define PCF_CR_P5_Msk                         (0x03UL << PCF_CR_P5_Pos)                               /*!< PCF CR: P5 Mask                         */
#define PCF_CR_P6_Pos                         12                                                      /*!< PCF CR: P6 Position                     */
#define PCF_CR_P6_Msk                         (0x03UL << PCF_CR_P6_Pos)                               /*!< PCF CR: P6 Mask                         */
#define PCF_CR_P7_Pos                         14                                                      /*!< PCF CR: P7 Position                     */
#define PCF_CR_P7_Msk                         (0x03UL << PCF_CR_P7_Pos)                               /*!< PCF CR: P7 Mask                         */
#define PCF_CR_P8_Pos                         16                                                      /*!< PCF CR: P8 Position                     */
#define PCF_CR_P8_Msk                         (0x03UL << PCF_CR_P8_Pos)                               /*!< PCF CR: P8 Mask                         */
#define PCF_CR_P9_Pos                         18                                                      /*!< PCF CR: P9 Position                     */
#define PCF_CR_P9_Msk                         (0x03UL << PCF_CR_P9_Pos)                               /*!< PCF CR: P9 Mask                         */
#define PCF_CR_P10_Pos                        20                                                      /*!< PCF CR: P10 Position                    */
#define PCF_CR_P10_Msk                        (0x03UL << PCF_CR_P10_Pos)                              /*!< PCF CR: P10 Mask                        */
#define PCF_CR_P11_Pos                        22                                                      /*!< PCF CR: P11 Position                    */
#define PCF_CR_P11_Msk                        (0x03UL << PCF_CR_P11_Pos)                              /*!< PCF CR: P11 Mask                        */
#define PCF_CR_P12_Pos                        24                                                      /*!< PCF CR: P12 Position                    */
#define PCF_CR_P12_Msk                        (0x03UL << PCF_CR_P12_Pos)                              /*!< PCF CR: P12 Mask                        */
#define PCF_CR_P13_Pos                        26                                                      /*!< PCF CR: P13 Position                    */
#define PCF_CR_P13_Msk                        (0x03UL << PCF_CR_P13_Pos)                              /*!< PCF CR: P13 Mask                        */
#define PCF_CR_P14_Pos                        28                                                      /*!< PCF CR: P14 Position                    */
#define PCF_CR_P14_Msk                        (0x03UL << PCF_CR_P14_Pos)                              /*!< PCF CR: P14 Mask                        */
#define PCF_CR_P15_Pos                        30                                                      /*!< PCF CR: P15 Position                    */
#define PCF_CR_P15_Msk                        (0x03UL << PCF_CR_P15_Pos)                              /*!< PCF CR: P15 Mask                        */

/* -----------------------------------  PCF_PCR  ---------------------------------- */
#define PCF_PCR_P0_Pos                        0                                                       /*!< PCF PCR: P0 Position                    */
#define PCF_PCR_P0_Msk                        (0x01UL << PCF_PCR_P0_Pos)                              /*!< PCF PCR: P0 Mask                        */
#define PCF_PCR_P1_Pos                        1                                                       /*!< PCF PCR: P1 Position                    */
#define PCF_PCR_P1_Msk                        (0x01UL << PCF_PCR_P1_Pos)                              /*!< PCF PCR: P1 Mask                        */
#define PCF_PCR_P2_Pos                        2                                                       /*!< PCF PCR: P2 Position                    */
#define PCF_PCR_P2_Msk                        (0x01UL << PCF_PCR_P2_Pos)                              /*!< PCF PCR: P2 Mask                        */
#define PCF_PCR_P3_Pos                        3                                                       /*!< PCF PCR: P3 Position                    */
#define PCF_PCR_P3_Msk                        (0x01UL << PCF_PCR_P3_Pos)                              /*!< PCF PCR: P3 Mask                        */
#define PCF_PCR_P4_Pos                        4                                                       /*!< PCF PCR: P4 Position                    */
#define PCF_PCR_P4_Msk                        (0x01UL << PCF_PCR_P4_Pos)                              /*!< PCF PCR: P4 Mask                        */
#define PCF_PCR_P5_Pos                        5                                                       /*!< PCF PCR: P5 Position                    */
#define PCF_PCR_P5_Msk                        (0x01UL << PCF_PCR_P5_Pos)                              /*!< PCF PCR: P5 Mask                        */
#define PCF_PCR_P6_Pos                        6                                                       /*!< PCF PCR: P6 Position                    */
#define PCF_PCR_P6_Msk                        (0x01UL << PCF_PCR_P6_Pos)                              /*!< PCF PCR: P6 Mask                        */
#define PCF_PCR_P7_Pos                        7                                                       /*!< PCF PCR: P7 Position                    */
#define PCF_PCR_P7_Msk                        (0x01UL << PCF_PCR_P7_Pos)                              /*!< PCF PCR: P7 Mask                        */
#define PCF_PCR_P8_Pos                        8                                                       /*!< PCF PCR: P8 Position                    */
#define PCF_PCR_P8_Msk                        (0x01UL << PCF_PCR_P8_Pos)                              /*!< PCF PCR: P8 Mask                        */
#define PCF_PCR_P9_Pos                        9                                                       /*!< PCF PCR: P9 Position                    */
#define PCF_PCR_P9_Msk                        (0x01UL << PCF_PCR_P9_Pos)                              /*!< PCF PCR: P9 Mask                        */
#define PCF_PCR_P10_Pos                       10                                                      /*!< PCF PCR: P10 Position                   */
#define PCF_PCR_P10_Msk                       (0x01UL << PCF_PCR_P10_Pos)                             /*!< PCF PCR: P10 Mask                       */
#define PCF_PCR_P11_Pos                       11                                                      /*!< PCF PCR: P11 Position                   */
#define PCF_PCR_P11_Msk                       (0x01UL << PCF_PCR_P11_Pos)                             /*!< PCF PCR: P11 Mask                       */
#define PCF_PCR_P12_Pos                       12                                                      /*!< PCF PCR: P12 Position                   */
#define PCF_PCR_P12_Msk                       (0x01UL << PCF_PCR_P12_Pos)                             /*!< PCF PCR: P12 Mask                       */
#define PCF_PCR_P13_Pos                       13                                                      /*!< PCF PCR: P13 Position                   */
#define PCF_PCR_P13_Msk                       (0x01UL << PCF_PCR_P13_Pos)                             /*!< PCF PCR: P13 Mask                       */
#define PCF_PCR_P14_Pos                       14                                                      /*!< PCF PCR: P14 Position                   */
#define PCF_PCR_P14_Msk                       (0x01UL << PCF_PCR_P14_Pos)                             /*!< PCF PCR: P14 Mask                       */
#define PCF_PCR_P15_Pos                       15                                                      /*!< PCF PCR: P15 Position                   */
#define PCF_PCR_P15_Msk                       (0x01UL << PCF_PCR_P15_Pos)                             /*!< PCF PCR: P15 Mask                       */
#define PCF_PCR_D0_Pos                        16                                                      /*!< PCF PCR: D0 Position                    */
#define PCF_PCR_D0_Msk                        (0x01UL << PCF_PCR_D0_Pos)                              /*!< PCF PCR: D0 Mask                        */
#define PCF_PCR_D1_Pos                        17                                                      /*!< PCF PCR: D1 Position                    */
#define PCF_PCR_D1_Msk                        (0x01UL << PCF_PCR_D1_Pos)                              /*!< PCF PCR: D1 Mask                        */
#define PCF_PCR_D2_Pos                        18                                                      /*!< PCF PCR: D2 Position                    */
#define PCF_PCR_D2_Msk                        (0x01UL << PCF_PCR_D2_Pos)                              /*!< PCF PCR: D2 Mask                        */
#define PCF_PCR_D3_Pos                        19                                                      /*!< PCF PCR: D3 Position                    */
#define PCF_PCR_D3_Msk                        (0x01UL << PCF_PCR_D3_Pos)                              /*!< PCF PCR: D3 Mask                        */
#define PCF_PCR_D4_Pos                        20                                                      /*!< PCF PCR: D4 Position                    */
#define PCF_PCR_D4_Msk                        (0x01UL << PCF_PCR_D4_Pos)                              /*!< PCF PCR: D4 Mask                        */
#define PCF_PCR_D5_Pos                        21                                                      /*!< PCF PCR: D5 Position                    */
#define PCF_PCR_D5_Msk                        (0x01UL << PCF_PCR_D5_Pos)                              /*!< PCF PCR: D5 Mask                        */
#define PCF_PCR_D6_Pos                        22                                                      /*!< PCF PCR: D6 Position                    */
#define PCF_PCR_D6_Msk                        (0x01UL << PCF_PCR_D6_Pos)                              /*!< PCF PCR: D6 Mask                        */
#define PCF_PCR_D7_Pos                        23                                                      /*!< PCF PCR: D7 Position                    */
#define PCF_PCR_D7_Msk                        (0x01UL << PCF_PCR_D7_Pos)                              /*!< PCF PCR: D7 Mask                        */
#define PCF_PCR_D8_Pos                        24                                                      /*!< PCF PCR: D8 Position                    */
#define PCF_PCR_D8_Msk                        (0x01UL << PCF_PCR_D8_Pos)                              /*!< PCF PCR: D8 Mask                        */
#define PCF_PCR_D9_Pos                        25                                                      /*!< PCF PCR: D9 Position                    */
#define PCF_PCR_D9_Msk                        (0x01UL << PCF_PCR_D9_Pos)                              /*!< PCF PCR: D9 Mask                        */
#define PCF_PCR_D10_Pos                       26                                                      /*!< PCF PCR: D10 Position                   */
#define PCF_PCR_D10_Msk                       (0x01UL << PCF_PCR_D10_Pos)                             /*!< PCF PCR: D10 Mask                       */
#define PCF_PCR_D11_Pos                       27                                                      /*!< PCF PCR: D11 Position                   */
#define PCF_PCR_D11_Msk                       (0x01UL << PCF_PCR_D11_Pos)                             /*!< PCF PCR: D11 Mask                       */
#define PCF_PCR_D12_Pos                       28                                                      /*!< PCF PCR: D12 Position                   */
#define PCF_PCR_D12_Msk                       (0x01UL << PCF_PCR_D12_Pos)                             /*!< PCF PCR: D12 Mask                       */
#define PCF_PCR_D13_Pos                       29                                                      /*!< PCF PCR: D13 Position                   */
#define PCF_PCR_D13_Msk                       (0x01UL << PCF_PCR_D13_Pos)                             /*!< PCF PCR: D13 Mask                       */
#define PCF_PCR_D14_Pos                       30                                                      /*!< PCF PCR: D14 Position                   */
#define PCF_PCR_D14_Msk                       (0x01UL << PCF_PCR_D14_Pos)                             /*!< PCF PCR: D14 Mask                       */
#define PCF_PCR_D15_Pos                       31                                                      /*!< PCF PCR: D15 Position                   */
#define PCF_PCR_D15_Msk                       (0x01UL << PCF_PCR_D15_Pos)                             /*!< PCF PCR: D15 Mask                       */

/* -----------------------------------  PCF_DER  ---------------------------------- */
#define PCF_DER_P0_Pos                        0                                                       /*!< PCF DER: P0 Position                    */
#define PCF_DER_P0_Msk                        (0x01UL << PCF_DER_P0_Pos)                              /*!< PCF DER: P0 Mask                        */
#define PCF_DER_P1_Pos                        1                                                       /*!< PCF DER: P1 Position                    */
#define PCF_DER_P1_Msk                        (0x01UL << PCF_DER_P1_Pos)                              /*!< PCF DER: P1 Mask                        */
#define PCF_DER_P2_Pos                        2                                                       /*!< PCF DER: P2 Position                    */
#define PCF_DER_P2_Msk                        (0x01UL << PCF_DER_P2_Pos)                              /*!< PCF DER: P2 Mask                        */
#define PCF_DER_P3_Pos                        3                                                       /*!< PCF DER: P3 Position                    */
#define PCF_DER_P3_Msk                        (0x01UL << PCF_DER_P3_Pos)                              /*!< PCF DER: P3 Mask                        */
#define PCF_DER_P4_Pos                        4                                                       /*!< PCF DER: P4 Position                    */
#define PCF_DER_P4_Msk                        (0x01UL << PCF_DER_P4_Pos)                              /*!< PCF DER: P4 Mask                        */
#define PCF_DER_P5_Pos                        5                                                       /*!< PCF DER: P5 Position                    */
#define PCF_DER_P5_Msk                        (0x01UL << PCF_DER_P5_Pos)                              /*!< PCF DER: P5 Mask                        */
#define PCF_DER_P6_Pos                        6                                                       /*!< PCF DER: P6 Position                    */
#define PCF_DER_P6_Msk                        (0x01UL << PCF_DER_P6_Pos)                              /*!< PCF DER: P6 Mask                        */
#define PCF_DER_P7_Pos                        7                                                       /*!< PCF DER: P7 Position                    */
#define PCF_DER_P7_Msk                        (0x01UL << PCF_DER_P7_Pos)                              /*!< PCF DER: P7 Mask                        */
#define PCF_DER_P8_Pos                        8                                                       /*!< PCF DER: P8 Position                    */
#define PCF_DER_P8_Msk                        (0x01UL << PCF_DER_P8_Pos)                              /*!< PCF DER: P8 Mask                        */
#define PCF_DER_P9_Pos                        9                                                       /*!< PCF DER: P9 Position                    */
#define PCF_DER_P9_Msk                        (0x01UL << PCF_DER_P9_Pos)                              /*!< PCF DER: P9 Mask                        */
#define PCF_DER_P10_Pos                       10                                                      /*!< PCF DER: P10 Position                   */
#define PCF_DER_P10_Msk                       (0x01UL << PCF_DER_P10_Pos)                             /*!< PCF DER: P10 Mask                       */
#define PCF_DER_P11_Pos                       11                                                      /*!< PCF DER: P11 Position                   */
#define PCF_DER_P11_Msk                       (0x01UL << PCF_DER_P11_Pos)                             /*!< PCF DER: P11 Mask                       */
#define PCF_DER_P12_Pos                       12                                                      /*!< PCF DER: P12 Position                   */
#define PCF_DER_P12_Msk                       (0x01UL << PCF_DER_P12_Pos)                             /*!< PCF DER: P12 Mask                       */
#define PCF_DER_P13_Pos                       13                                                      /*!< PCF DER: P13 Position                   */
#define PCF_DER_P13_Msk                       (0x01UL << PCF_DER_P13_Pos)                             /*!< PCF DER: P13 Mask                       */
#define PCF_DER_P14_Pos                       14                                                      /*!< PCF DER: P14 Position                   */
#define PCF_DER_P14_Msk                       (0x01UL << PCF_DER_P14_Pos)                             /*!< PCF DER: P14 Mask                       */
#define PCF_DER_P15_Pos                       15                                                      /*!< PCF DER: P15 Position                   */
#define PCF_DER_P15_Msk                       (0x01UL << PCF_DER_P15_Pos)                             /*!< PCF DER: P15 Mask                       */

/* -----------------------------------  PCF_IER  ---------------------------------- */
#define PCF_IER_P0_Pos                        0                                                       /*!< PCF IER: P0 Position                    */
#define PCF_IER_P0_Msk                        (0x03UL << PCF_IER_P0_Pos)                              /*!< PCF IER: P0 Mask                        */
#define PCF_IER_P1_Pos                        2                                                       /*!< PCF IER: P1 Position                    */
#define PCF_IER_P1_Msk                        (0x03UL << PCF_IER_P1_Pos)                              /*!< PCF IER: P1 Mask                        */
#define PCF_IER_P2_Pos                        4                                                       /*!< PCF IER: P2 Position                    */
#define PCF_IER_P2_Msk                        (0x03UL << PCF_IER_P2_Pos)                              /*!< PCF IER: P2 Mask                        */
#define PCF_IER_P3_Pos                        6                                                       /*!< PCF IER: P3 Position                    */
#define PCF_IER_P3_Msk                        (0x03UL << PCF_IER_P3_Pos)                              /*!< PCF IER: P3 Mask                        */
#define PCF_IER_P4_Pos                        8                                                       /*!< PCF IER: P4 Position                    */
#define PCF_IER_P4_Msk                        (0x03UL << PCF_IER_P4_Pos)                              /*!< PCF IER: P4 Mask                        */
#define PCF_IER_P5_Pos                        10                                                      /*!< PCF IER: P5 Position                    */
#define PCF_IER_P5_Msk                        (0x03UL << PCF_IER_P5_Pos)                              /*!< PCF IER: P5 Mask                        */
#define PCF_IER_P6_Pos                        12                                                      /*!< PCF IER: P6 Position                    */
#define PCF_IER_P6_Msk                        (0x03UL << PCF_IER_P6_Pos)                              /*!< PCF IER: P6 Mask                        */
#define PCF_IER_P7_Pos                        14                                                      /*!< PCF IER: P7 Position                    */
#define PCF_IER_P7_Msk                        (0x03UL << PCF_IER_P7_Pos)                              /*!< PCF IER: P7 Mask                        */
#define PCF_IER_P8_Pos                        16                                                      /*!< PCF IER: P8 Position                    */
#define PCF_IER_P8_Msk                        (0x03UL << PCF_IER_P8_Pos)                              /*!< PCF IER: P8 Mask                        */
#define PCF_IER_P9_Pos                        18                                                      /*!< PCF IER: P9 Position                    */
#define PCF_IER_P9_Msk                        (0x03UL << PCF_IER_P9_Pos)                              /*!< PCF IER: P9 Mask                        */
#define PCF_IER_P10_Pos                       20                                                      /*!< PCF IER: P10 Position                   */
#define PCF_IER_P10_Msk                       (0x03UL << PCF_IER_P10_Pos)                             /*!< PCF IER: P10 Mask                       */
#define PCF_IER_P11_Pos                       22                                                      /*!< PCF IER: P11 Position                   */
#define PCF_IER_P11_Msk                       (0x03UL << PCF_IER_P11_Pos)                             /*!< PCF IER: P11 Mask                       */
#define PCF_IER_P12_Pos                       24                                                      /*!< PCF IER: P12 Position                   */
#define PCF_IER_P12_Msk                       (0x03UL << PCF_IER_P12_Pos)                             /*!< PCF IER: P12 Mask                       */
#define PCF_IER_P13_Pos                       26                                                      /*!< PCF IER: P13 Position                   */
#define PCF_IER_P13_Msk                       (0x03UL << PCF_IER_P13_Pos)                             /*!< PCF IER: P13 Mask                       */
#define PCF_IER_P14_Pos                       28                                                      /*!< PCF IER: P14 Position                   */
#define PCF_IER_P14_Msk                       (0x03UL << PCF_IER_P14_Pos)                             /*!< PCF IER: P14 Mask                       */
#define PCF_IER_P15_Pos                       30                                                      /*!< PCF IER: P15 Position                   */
#define PCF_IER_P15_Msk                       (0x03UL << PCF_IER_P15_Pos)                             /*!< PCF IER: P15 Mask                       */

/* -----------------------------------  PCF_ISR  ---------------------------------- */
#define PCF_ISR_P0_Pos                        0                                                       /*!< PCF ISR: P0 Position                    */
#define PCF_ISR_P0_Msk                        (0x03UL << PCF_ISR_P0_Pos)                              /*!< PCF ISR: P0 Mask                        */
#define PCF_ISR_P1_Pos                        2                                                       /*!< PCF ISR: P1 Position                    */
#define PCF_ISR_P1_Msk                        (0x03UL << PCF_ISR_P1_Pos)                              /*!< PCF ISR: P1 Mask                        */
#define PCF_ISR_P2_Pos                        4                                                       /*!< PCF ISR: P2 Position                    */
#define PCF_ISR_P2_Msk                        (0x03UL << PCF_ISR_P2_Pos)                              /*!< PCF ISR: P2 Mask                        */
#define PCF_ISR_P3_Pos                        6                                                       /*!< PCF ISR: P3 Position                    */
#define PCF_ISR_P3_Msk                        (0x03UL << PCF_ISR_P3_Pos)                              /*!< PCF ISR: P3 Mask                        */
#define PCF_ISR_P4_Pos                        8                                                       /*!< PCF ISR: P4 Position                    */
#define PCF_ISR_P4_Msk                        (0x03UL << PCF_ISR_P4_Pos)                              /*!< PCF ISR: P4 Mask                        */
#define PCF_ISR_P5_Pos                        10                                                      /*!< PCF ISR: P5 Position                    */
#define PCF_ISR_P5_Msk                        (0x03UL << PCF_ISR_P5_Pos)                              /*!< PCF ISR: P5 Mask                        */
#define PCF_ISR_P6_Pos                        12                                                      /*!< PCF ISR: P6 Position                    */
#define PCF_ISR_P6_Msk                        (0x03UL << PCF_ISR_P6_Pos)                              /*!< PCF ISR: P6 Mask                        */
#define PCF_ISR_P7_Pos                        14                                                      /*!< PCF ISR: P7 Position                    */
#define PCF_ISR_P7_Msk                        (0x03UL << PCF_ISR_P7_Pos)                              /*!< PCF ISR: P7 Mask                        */
#define PCF_ISR_P8_Pos                        16                                                      /*!< PCF ISR: P8 Position                    */
#define PCF_ISR_P8_Msk                        (0x03UL << PCF_ISR_P8_Pos)                              /*!< PCF ISR: P8 Mask                        */
#define PCF_ISR_P9_Pos                        18                                                      /*!< PCF ISR: P9 Position                    */
#define PCF_ISR_P9_Msk                        (0x03UL << PCF_ISR_P9_Pos)                              /*!< PCF ISR: P9 Mask                        */
#define PCF_ISR_P10_Pos                       20                                                      /*!< PCF ISR: P10 Position                   */
#define PCF_ISR_P10_Msk                       (0x03UL << PCF_ISR_P10_Pos)                             /*!< PCF ISR: P10 Mask                       */
#define PCF_ISR_P11_Pos                       22                                                      /*!< PCF ISR: P11 Position                   */
#define PCF_ISR_P11_Msk                       (0x03UL << PCF_ISR_P11_Pos)                             /*!< PCF ISR: P11 Mask                       */
#define PCF_ISR_P12_Pos                       24                                                      /*!< PCF ISR: P12 Position                   */
#define PCF_ISR_P12_Msk                       (0x03UL << PCF_ISR_P12_Pos)                             /*!< PCF ISR: P12 Mask                       */
#define PCF_ISR_P13_Pos                       26                                                      /*!< PCF ISR: P13 Position                   */
#define PCF_ISR_P13_Msk                       (0x03UL << PCF_ISR_P13_Pos)                             /*!< PCF ISR: P13 Mask                       */
#define PCF_ISR_P14_Pos                       28                                                      /*!< PCF ISR: P14 Position                   */
#define PCF_ISR_P14_Msk                       (0x03UL << PCF_ISR_P14_Pos)                             /*!< PCF ISR: P14 Mask                       */
#define PCF_ISR_P15_Pos                       30                                                      /*!< PCF ISR: P15 Position                   */
#define PCF_ISR_P15_Msk                       (0x03UL << PCF_ISR_P15_Pos)                             /*!< PCF ISR: P15 Mask                       */

/* -----------------------------------  PCF_ICR  ---------------------------------- */
#define PCF_ICR_P0_Pos                        0                                                       /*!< PCF ICR: P0 Position                    */
#define PCF_ICR_P0_Msk                        (0x03UL << PCF_ICR_P0_Pos)                              /*!< PCF ICR: P0 Mask                        */
#define PCF_ICR_P1_Pos                        2                                                       /*!< PCF ICR: P1 Position                    */
#define PCF_ICR_P1_Msk                        (0x03UL << PCF_ICR_P1_Pos)                              /*!< PCF ICR: P1 Mask                        */
#define PCF_ICR_P2_Pos                        4                                                       /*!< PCF ICR: P2 Position                    */
#define PCF_ICR_P2_Msk                        (0x03UL << PCF_ICR_P2_Pos)                              /*!< PCF ICR: P2 Mask                        */
#define PCF_ICR_P3_Pos                        6                                                       /*!< PCF ICR: P3 Position                    */
#define PCF_ICR_P3_Msk                        (0x03UL << PCF_ICR_P3_Pos)                              /*!< PCF ICR: P3 Mask                        */
#define PCF_ICR_P4_Pos                        8                                                       /*!< PCF ICR: P4 Position                    */
#define PCF_ICR_P4_Msk                        (0x03UL << PCF_ICR_P4_Pos)                              /*!< PCF ICR: P4 Mask                        */
#define PCF_ICR_P5_Pos                        10                                                      /*!< PCF ICR: P5 Position                    */
#define PCF_ICR_P5_Msk                        (0x03UL << PCF_ICR_P5_Pos)                              /*!< PCF ICR: P5 Mask                        */
#define PCF_ICR_P6_Pos                        12                                                      /*!< PCF ICR: P6 Position                    */
#define PCF_ICR_P6_Msk                        (0x03UL << PCF_ICR_P6_Pos)                              /*!< PCF ICR: P6 Mask                        */
#define PCF_ICR_P7_Pos                        14                                                      /*!< PCF ICR: P7 Position                    */
#define PCF_ICR_P7_Msk                        (0x03UL << PCF_ICR_P7_Pos)                              /*!< PCF ICR: P7 Mask                        */
#define PCF_ICR_P8_Pos                        16                                                      /*!< PCF ICR: P8 Position                    */
#define PCF_ICR_P8_Msk                        (0x03UL << PCF_ICR_P8_Pos)                              /*!< PCF ICR: P8 Mask                        */
#define PCF_ICR_P9_Pos                        18                                                      /*!< PCF ICR: P9 Position                    */
#define PCF_ICR_P9_Msk                        (0x03UL << PCF_ICR_P9_Pos)                              /*!< PCF ICR: P9 Mask                        */
#define PCF_ICR_P10_Pos                       20                                                      /*!< PCF ICR: P10 Position                   */
#define PCF_ICR_P10_Msk                       (0x03UL << PCF_ICR_P10_Pos)                             /*!< PCF ICR: P10 Mask                       */
#define PCF_ICR_P11_Pos                       22                                                      /*!< PCF ICR: P11 Position                   */
#define PCF_ICR_P11_Msk                       (0x03UL << PCF_ICR_P11_Pos)                             /*!< PCF ICR: P11 Mask                       */
#define PCF_ICR_P12_Pos                       24                                                      /*!< PCF ICR: P12 Position                   */
#define PCF_ICR_P12_Msk                       (0x03UL << PCF_ICR_P12_Pos)                             /*!< PCF ICR: P12 Mask                       */
#define PCF_ICR_P13_Pos                       26                                                      /*!< PCF ICR: P13 Position                   */
#define PCF_ICR_P13_Msk                       (0x03UL << PCF_ICR_P13_Pos)                             /*!< PCF ICR: P13 Mask                       */
#define PCF_ICR_P14_Pos                       28                                                      /*!< PCF ICR: P14 Position                   */
#define PCF_ICR_P14_Msk                       (0x03UL << PCF_ICR_P14_Pos)                             /*!< PCF ICR: P14 Mask                       */
#define PCF_ICR_P15_Pos                       30                                                      /*!< PCF ICR: P15 Position                   */
#define PCF_ICR_P15_Msk                       (0x03UL << PCF_ICR_P15_Pos)                             /*!< PCF ICR: P15 Mask                       */

/* -----------------------------------  PCF_DPR  ---------------------------------- */
#define PCF_DPR_DPR_Pos                       0                                                       /*!< PCF DPR: DPR Position                   */
#define PCF_DPR_DPR_Msk                       (0x1fUL << PCF_DPR_DPR_Pos)                             /*!< PCF DPR: DPR Mask                       */


/* ================================================================================ */
/* ================           struct 'PA' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  PA_ODR  ----------------------------------- */
#define PA_ODR_P0_Pos                         0                                                       /*!< PA ODR: P0 Position                     */
#define PA_ODR_P0_Msk                         (0x01UL << PA_ODR_P0_Pos)                               /*!< PA ODR: P0 Mask                         */
#define PA_ODR_P1_Pos                         1                                                       /*!< PA ODR: P1 Position                     */
#define PA_ODR_P1_Msk                         (0x01UL << PA_ODR_P1_Pos)                               /*!< PA ODR: P1 Mask                         */
#define PA_ODR_P2_Pos                         2                                                       /*!< PA ODR: P2 Position                     */
#define PA_ODR_P2_Msk                         (0x01UL << PA_ODR_P2_Pos)                               /*!< PA ODR: P2 Mask                         */
#define PA_ODR_P3_Pos                         3                                                       /*!< PA ODR: P3 Position                     */
#define PA_ODR_P3_Msk                         (0x01UL << PA_ODR_P3_Pos)                               /*!< PA ODR: P3 Mask                         */
#define PA_ODR_P4_Pos                         4                                                       /*!< PA ODR: P4 Position                     */
#define PA_ODR_P4_Msk                         (0x01UL << PA_ODR_P4_Pos)                               /*!< PA ODR: P4 Mask                         */
#define PA_ODR_P5_Pos                         5                                                       /*!< PA ODR: P5 Position                     */
#define PA_ODR_P5_Msk                         (0x01UL << PA_ODR_P5_Pos)                               /*!< PA ODR: P5 Mask                         */
#define PA_ODR_P6_Pos                         6                                                       /*!< PA ODR: P6 Position                     */
#define PA_ODR_P6_Msk                         (0x01UL << PA_ODR_P6_Pos)                               /*!< PA ODR: P6 Mask                         */
#define PA_ODR_P7_Pos                         7                                                       /*!< PA ODR: P7 Position                     */
#define PA_ODR_P7_Msk                         (0x01UL << PA_ODR_P7_Pos)                               /*!< PA ODR: P7 Mask                         */
#define PA_ODR_P8_Pos                         8                                                       /*!< PA ODR: P8 Position                     */
#define PA_ODR_P8_Msk                         (0x01UL << PA_ODR_P8_Pos)                               /*!< PA ODR: P8 Mask                         */
#define PA_ODR_P9_Pos                         9                                                       /*!< PA ODR: P9 Position                     */
#define PA_ODR_P9_Msk                         (0x01UL << PA_ODR_P9_Pos)                               /*!< PA ODR: P9 Mask                         */
#define PA_ODR_P10_Pos                        10                                                      /*!< PA ODR: P10 Position                    */
#define PA_ODR_P10_Msk                        (0x01UL << PA_ODR_P10_Pos)                              /*!< PA ODR: P10 Mask                        */
#define PA_ODR_P11_Pos                        11                                                      /*!< PA ODR: P11 Position                    */
#define PA_ODR_P11_Msk                        (0x01UL << PA_ODR_P11_Pos)                              /*!< PA ODR: P11 Mask                        */
#define PA_ODR_P12_Pos                        12                                                      /*!< PA ODR: P12 Position                    */
#define PA_ODR_P12_Msk                        (0x01UL << PA_ODR_P12_Pos)                              /*!< PA ODR: P12 Mask                        */
#define PA_ODR_P13_Pos                        13                                                      /*!< PA ODR: P13 Position                    */
#define PA_ODR_P13_Msk                        (0x01UL << PA_ODR_P13_Pos)                              /*!< PA ODR: P13 Mask                        */
#define PA_ODR_P14_Pos                        14                                                      /*!< PA ODR: P14 Position                    */
#define PA_ODR_P14_Msk                        (0x01UL << PA_ODR_P14_Pos)                              /*!< PA ODR: P14 Mask                        */
#define PA_ODR_P15_Pos                        15                                                      /*!< PA ODR: P15 Position                    */
#define PA_ODR_P15_Msk                        (0x01UL << PA_ODR_P15_Pos)                              /*!< PA ODR: P15 Mask                        */

/* -----------------------------------  PA_IDR  ----------------------------------- */
#define PA_IDR_P0_Pos                         0                                                       /*!< PA IDR: P0 Position                     */
#define PA_IDR_P0_Msk                         (0x01UL << PA_IDR_P0_Pos)                               /*!< PA IDR: P0 Mask                         */
#define PA_IDR_P1_Pos                         1                                                       /*!< PA IDR: P1 Position                     */
#define PA_IDR_P1_Msk                         (0x01UL << PA_IDR_P1_Pos)                               /*!< PA IDR: P1 Mask                         */
#define PA_IDR_P2_Pos                         2                                                       /*!< PA IDR: P2 Position                     */
#define PA_IDR_P2_Msk                         (0x01UL << PA_IDR_P2_Pos)                               /*!< PA IDR: P2 Mask                         */
#define PA_IDR_P3_Pos                         3                                                       /*!< PA IDR: P3 Position                     */
#define PA_IDR_P3_Msk                         (0x01UL << PA_IDR_P3_Pos)                               /*!< PA IDR: P3 Mask                         */
#define PA_IDR_P4_Pos                         4                                                       /*!< PA IDR: P4 Position                     */
#define PA_IDR_P4_Msk                         (0x01UL << PA_IDR_P4_Pos)                               /*!< PA IDR: P4 Mask                         */
#define PA_IDR_P5_Pos                         5                                                       /*!< PA IDR: P5 Position                     */
#define PA_IDR_P5_Msk                         (0x01UL << PA_IDR_P5_Pos)                               /*!< PA IDR: P5 Mask                         */
#define PA_IDR_P6_Pos                         6                                                       /*!< PA IDR: P6 Position                     */
#define PA_IDR_P6_Msk                         (0x01UL << PA_IDR_P6_Pos)                               /*!< PA IDR: P6 Mask                         */
#define PA_IDR_P7_Pos                         7                                                       /*!< PA IDR: P7 Position                     */
#define PA_IDR_P7_Msk                         (0x01UL << PA_IDR_P7_Pos)                               /*!< PA IDR: P7 Mask                         */
#define PA_IDR_P8_Pos                         8                                                       /*!< PA IDR: P8 Position                     */
#define PA_IDR_P8_Msk                         (0x01UL << PA_IDR_P8_Pos)                               /*!< PA IDR: P8 Mask                         */
#define PA_IDR_P9_Pos                         9                                                       /*!< PA IDR: P9 Position                     */
#define PA_IDR_P9_Msk                         (0x01UL << PA_IDR_P9_Pos)                               /*!< PA IDR: P9 Mask                         */
#define PA_IDR_P10_Pos                        10                                                      /*!< PA IDR: P10 Position                    */
#define PA_IDR_P10_Msk                        (0x01UL << PA_IDR_P10_Pos)                              /*!< PA IDR: P10 Mask                        */
#define PA_IDR_P11_Pos                        11                                                      /*!< PA IDR: P11 Position                    */
#define PA_IDR_P11_Msk                        (0x01UL << PA_IDR_P11_Pos)                              /*!< PA IDR: P11 Mask                        */
#define PA_IDR_P12_Pos                        12                                                      /*!< PA IDR: P12 Position                    */
#define PA_IDR_P12_Msk                        (0x01UL << PA_IDR_P12_Pos)                              /*!< PA IDR: P12 Mask                        */
#define PA_IDR_P13_Pos                        13                                                      /*!< PA IDR: P13 Position                    */
#define PA_IDR_P13_Msk                        (0x01UL << PA_IDR_P13_Pos)                              /*!< PA IDR: P13 Mask                        */
#define PA_IDR_P14_Pos                        14                                                      /*!< PA IDR: P14 Position                    */
#define PA_IDR_P14_Msk                        (0x01UL << PA_IDR_P14_Pos)                              /*!< PA IDR: P14 Mask                        */
#define PA_IDR_P15_Pos                        15                                                      /*!< PA IDR: P15 Position                    */
#define PA_IDR_P15_Msk                        (0x01UL << PA_IDR_P15_Pos)                              /*!< PA IDR: P15 Mask                        */

/* -----------------------------------  PA_SRR  ----------------------------------- */
#define PA_SRR_P0_SET_Pos                     0                                                       /*!< PA SRR: P0_SET Position                 */
#define PA_SRR_P0_SET_Msk                     (0x01UL << PA_SRR_P0_SET_Pos)                           /*!< PA SRR: P0_SET Mask                     */
#define PA_SRR_P1_SET_Pos                     1                                                       /*!< PA SRR: P1_SET Position                 */
#define PA_SRR_P1_SET_Msk                     (0x01UL << PA_SRR_P1_SET_Pos)                           /*!< PA SRR: P1_SET Mask                     */
#define PA_SRR_P2_SET_Pos                     2                                                       /*!< PA SRR: P2_SET Position                 */
#define PA_SRR_P2_SET_Msk                     (0x01UL << PA_SRR_P2_SET_Pos)                           /*!< PA SRR: P2_SET Mask                     */
#define PA_SRR_P3_SET_Pos                     3                                                       /*!< PA SRR: P3_SET Position                 */
#define PA_SRR_P3_SET_Msk                     (0x01UL << PA_SRR_P3_SET_Pos)                           /*!< PA SRR: P3_SET Mask                     */
#define PA_SRR_P4_SET_Pos                     4                                                       /*!< PA SRR: P4_SET Position                 */
#define PA_SRR_P4_SET_Msk                     (0x01UL << PA_SRR_P4_SET_Pos)                           /*!< PA SRR: P4_SET Mask                     */
#define PA_SRR_P5_SET_Pos                     5                                                       /*!< PA SRR: P5_SET Position                 */
#define PA_SRR_P5_SET_Msk                     (0x01UL << PA_SRR_P5_SET_Pos)                           /*!< PA SRR: P5_SET Mask                     */
#define PA_SRR_P6_SET_Pos                     6                                                       /*!< PA SRR: P6_SET Position                 */
#define PA_SRR_P6_SET_Msk                     (0x01UL << PA_SRR_P6_SET_Pos)                           /*!< PA SRR: P6_SET Mask                     */
#define PA_SRR_P7_SET_Pos                     7                                                       /*!< PA SRR: P7_SET Position                 */
#define PA_SRR_P7_SET_Msk                     (0x01UL << PA_SRR_P7_SET_Pos)                           /*!< PA SRR: P7_SET Mask                     */
#define PA_SRR_P8_SET_Pos                     8                                                       /*!< PA SRR: P8_SET Position                 */
#define PA_SRR_P8_SET_Msk                     (0x01UL << PA_SRR_P8_SET_Pos)                           /*!< PA SRR: P8_SET Mask                     */
#define PA_SRR_P9_SET_Pos                     9                                                       /*!< PA SRR: P9_SET Position                 */
#define PA_SRR_P9_SET_Msk                     (0x01UL << PA_SRR_P9_SET_Pos)                           /*!< PA SRR: P9_SET Mask                     */
#define PA_SRR_P10_SET_Pos                    10                                                      /*!< PA SRR: P10_SET Position                */
#define PA_SRR_P10_SET_Msk                    (0x01UL << PA_SRR_P10_SET_Pos)                          /*!< PA SRR: P10_SET Mask                    */
#define PA_SRR_P11_SET_Pos                    11                                                      /*!< PA SRR: P11_SET Position                */
#define PA_SRR_P11_SET_Msk                    (0x01UL << PA_SRR_P11_SET_Pos)                          /*!< PA SRR: P11_SET Mask                    */
#define PA_SRR_P12_SET_Pos                    12                                                      /*!< PA SRR: P12_SET Position                */
#define PA_SRR_P12_SET_Msk                    (0x01UL << PA_SRR_P12_SET_Pos)                          /*!< PA SRR: P12_SET Mask                    */
#define PA_SRR_P13_SET_Pos                    13                                                      /*!< PA SRR: P13_SET Position                */
#define PA_SRR_P13_SET_Msk                    (0x01UL << PA_SRR_P13_SET_Pos)                          /*!< PA SRR: P13_SET Mask                    */
#define PA_SRR_P14_SET_Pos                    14                                                      /*!< PA SRR: P14_SET Position                */
#define PA_SRR_P14_SET_Msk                    (0x01UL << PA_SRR_P14_SET_Pos)                          /*!< PA SRR: P14_SET Mask                    */
#define PA_SRR_P15_SET_Pos                    15                                                      /*!< PA SRR: P15_SET Position                */
#define PA_SRR_P15_SET_Msk                    (0x01UL << PA_SRR_P15_SET_Pos)                          /*!< PA SRR: P15_SET Mask                    */
#define PA_SRR_P0_RESET_Pos                   16                                                      /*!< PA SRR: P0_RESET Position               */
#define PA_SRR_P0_RESET_Msk                   (0x01UL << PA_SRR_P0_RESET_Pos)                         /*!< PA SRR: P0_RESET Mask                   */
#define PA_SRR_P1_RESET_Pos                   17                                                      /*!< PA SRR: P1_RESET Position               */
#define PA_SRR_P1_RESET_Msk                   (0x01UL << PA_SRR_P1_RESET_Pos)                         /*!< PA SRR: P1_RESET Mask                   */
#define PA_SRR_P2_RESET_Pos                   18                                                      /*!< PA SRR: P2_RESET Position               */
#define PA_SRR_P2_RESET_Msk                   (0x01UL << PA_SRR_P2_RESET_Pos)                         /*!< PA SRR: P2_RESET Mask                   */
#define PA_SRR_P3_RESET_Pos                   19                                                      /*!< PA SRR: P3_RESET Position               */
#define PA_SRR_P3_RESET_Msk                   (0x01UL << PA_SRR_P3_RESET_Pos)                         /*!< PA SRR: P3_RESET Mask                   */
#define PA_SRR_P4_RESET_Pos                   20                                                      /*!< PA SRR: P4_RESET Position               */
#define PA_SRR_P4_RESET_Msk                   (0x01UL << PA_SRR_P4_RESET_Pos)                         /*!< PA SRR: P4_RESET Mask                   */
#define PA_SRR_P5_RESET_Pos                   21                                                      /*!< PA SRR: P5_RESET Position               */
#define PA_SRR_P5_RESET_Msk                   (0x01UL << PA_SRR_P5_RESET_Pos)                         /*!< PA SRR: P5_RESET Mask                   */
#define PA_SRR_P6_RESET_Pos                   22                                                      /*!< PA SRR: P6_RESET Position               */
#define PA_SRR_P6_RESET_Msk                   (0x01UL << PA_SRR_P6_RESET_Pos)                         /*!< PA SRR: P6_RESET Mask                   */
#define PA_SRR_P7_RESET_Pos                   23                                                      /*!< PA SRR: P7_RESET Position               */
#define PA_SRR_P7_RESET_Msk                   (0x01UL << PA_SRR_P7_RESET_Pos)                         /*!< PA SRR: P7_RESET Mask                   */
#define PA_SRR_P8_RESET_Pos                   24                                                      /*!< PA SRR: P8_RESET Position               */
#define PA_SRR_P8_RESET_Msk                   (0x01UL << PA_SRR_P8_RESET_Pos)                         /*!< PA SRR: P8_RESET Mask                   */
#define PA_SRR_P9_RESET_Pos                   25                                                      /*!< PA SRR: P9_RESET Position               */
#define PA_SRR_P9_RESET_Msk                   (0x01UL << PA_SRR_P9_RESET_Pos)                         /*!< PA SRR: P9_RESET Mask                   */
#define PA_SRR_P10_RESET_Pos                  26                                                      /*!< PA SRR: P10_RESET Position              */
#define PA_SRR_P10_RESET_Msk                  (0x01UL << PA_SRR_P10_RESET_Pos)                        /*!< PA SRR: P10_RESET Mask                  */
#define PA_SRR_P11_RESET_Pos                  27                                                      /*!< PA SRR: P11_RESET Position              */
#define PA_SRR_P11_RESET_Msk                  (0x01UL << PA_SRR_P11_RESET_Pos)                        /*!< PA SRR: P11_RESET Mask                  */
#define PA_SRR_P12_RESET_Pos                  28                                                      /*!< PA SRR: P12_RESET Position              */
#define PA_SRR_P12_RESET_Msk                  (0x01UL << PA_SRR_P12_RESET_Pos)                        /*!< PA SRR: P12_RESET Mask                  */
#define PA_SRR_P13_RESET_Pos                  29                                                      /*!< PA SRR: P13_RESET Position              */
#define PA_SRR_P13_RESET_Msk                  (0x01UL << PA_SRR_P13_RESET_Pos)                        /*!< PA SRR: P13_RESET Mask                  */
#define PA_SRR_P14_RESET_Pos                  30                                                      /*!< PA SRR: P14_RESET Position              */
#define PA_SRR_P14_RESET_Msk                  (0x01UL << PA_SRR_P14_RESET_Pos)                        /*!< PA SRR: P14_RESET Mask                  */
#define PA_SRR_P15_RESET_Pos                  31                                                      /*!< PA SRR: P15_RESET Position              */
#define PA_SRR_P15_RESET_Msk                  (0x01UL << PA_SRR_P15_RESET_Pos)                        /*!< PA SRR: P15_RESET Mask                  */


/* ================================================================================ */
/* ================           struct 'PB' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  PB_ODR  ----------------------------------- */
#define PB_ODR_P0_Pos                         0                                                       /*!< PB ODR: P0 Position                     */
#define PB_ODR_P0_Msk                         (0x01UL << PB_ODR_P0_Pos)                               /*!< PB ODR: P0 Mask                         */
#define PB_ODR_P1_Pos                         1                                                       /*!< PB ODR: P1 Position                     */
#define PB_ODR_P1_Msk                         (0x01UL << PB_ODR_P1_Pos)                               /*!< PB ODR: P1 Mask                         */
#define PB_ODR_P2_Pos                         2                                                       /*!< PB ODR: P2 Position                     */
#define PB_ODR_P2_Msk                         (0x01UL << PB_ODR_P2_Pos)                               /*!< PB ODR: P2 Mask                         */
#define PB_ODR_P3_Pos                         3                                                       /*!< PB ODR: P3 Position                     */
#define PB_ODR_P3_Msk                         (0x01UL << PB_ODR_P3_Pos)                               /*!< PB ODR: P3 Mask                         */
#define PB_ODR_P4_Pos                         4                                                       /*!< PB ODR: P4 Position                     */
#define PB_ODR_P4_Msk                         (0x01UL << PB_ODR_P4_Pos)                               /*!< PB ODR: P4 Mask                         */
#define PB_ODR_P5_Pos                         5                                                       /*!< PB ODR: P5 Position                     */
#define PB_ODR_P5_Msk                         (0x01UL << PB_ODR_P5_Pos)                               /*!< PB ODR: P5 Mask                         */
#define PB_ODR_P6_Pos                         6                                                       /*!< PB ODR: P6 Position                     */
#define PB_ODR_P6_Msk                         (0x01UL << PB_ODR_P6_Pos)                               /*!< PB ODR: P6 Mask                         */
#define PB_ODR_P7_Pos                         7                                                       /*!< PB ODR: P7 Position                     */
#define PB_ODR_P7_Msk                         (0x01UL << PB_ODR_P7_Pos)                               /*!< PB ODR: P7 Mask                         */
#define PB_ODR_P8_Pos                         8                                                       /*!< PB ODR: P8 Position                     */
#define PB_ODR_P8_Msk                         (0x01UL << PB_ODR_P8_Pos)                               /*!< PB ODR: P8 Mask                         */
#define PB_ODR_P9_Pos                         9                                                       /*!< PB ODR: P9 Position                     */
#define PB_ODR_P9_Msk                         (0x01UL << PB_ODR_P9_Pos)                               /*!< PB ODR: P9 Mask                         */
#define PB_ODR_P10_Pos                        10                                                      /*!< PB ODR: P10 Position                    */
#define PB_ODR_P10_Msk                        (0x01UL << PB_ODR_P10_Pos)                              /*!< PB ODR: P10 Mask                        */
#define PB_ODR_P11_Pos                        11                                                      /*!< PB ODR: P11 Position                    */
#define PB_ODR_P11_Msk                        (0x01UL << PB_ODR_P11_Pos)                              /*!< PB ODR: P11 Mask                        */
#define PB_ODR_P12_Pos                        12                                                      /*!< PB ODR: P12 Position                    */
#define PB_ODR_P12_Msk                        (0x01UL << PB_ODR_P12_Pos)                              /*!< PB ODR: P12 Mask                        */
#define PB_ODR_P13_Pos                        13                                                      /*!< PB ODR: P13 Position                    */
#define PB_ODR_P13_Msk                        (0x01UL << PB_ODR_P13_Pos)                              /*!< PB ODR: P13 Mask                        */
#define PB_ODR_P14_Pos                        14                                                      /*!< PB ODR: P14 Position                    */
#define PB_ODR_P14_Msk                        (0x01UL << PB_ODR_P14_Pos)                              /*!< PB ODR: P14 Mask                        */
#define PB_ODR_P15_Pos                        15                                                      /*!< PB ODR: P15 Position                    */
#define PB_ODR_P15_Msk                        (0x01UL << PB_ODR_P15_Pos)                              /*!< PB ODR: P15 Mask                        */

/* -----------------------------------  PB_IDR  ----------------------------------- */
#define PB_IDR_P0_Pos                         0                                                       /*!< PB IDR: P0 Position                     */
#define PB_IDR_P0_Msk                         (0x01UL << PB_IDR_P0_Pos)                               /*!< PB IDR: P0 Mask                         */
#define PB_IDR_P1_Pos                         1                                                       /*!< PB IDR: P1 Position                     */
#define PB_IDR_P1_Msk                         (0x01UL << PB_IDR_P1_Pos)                               /*!< PB IDR: P1 Mask                         */
#define PB_IDR_P2_Pos                         2                                                       /*!< PB IDR: P2 Position                     */
#define PB_IDR_P2_Msk                         (0x01UL << PB_IDR_P2_Pos)                               /*!< PB IDR: P2 Mask                         */
#define PB_IDR_P3_Pos                         3                                                       /*!< PB IDR: P3 Position                     */
#define PB_IDR_P3_Msk                         (0x01UL << PB_IDR_P3_Pos)                               /*!< PB IDR: P3 Mask                         */
#define PB_IDR_P4_Pos                         4                                                       /*!< PB IDR: P4 Position                     */
#define PB_IDR_P4_Msk                         (0x01UL << PB_IDR_P4_Pos)                               /*!< PB IDR: P4 Mask                         */
#define PB_IDR_P5_Pos                         5                                                       /*!< PB IDR: P5 Position                     */
#define PB_IDR_P5_Msk                         (0x01UL << PB_IDR_P5_Pos)                               /*!< PB IDR: P5 Mask                         */
#define PB_IDR_P6_Pos                         6                                                       /*!< PB IDR: P6 Position                     */
#define PB_IDR_P6_Msk                         (0x01UL << PB_IDR_P6_Pos)                               /*!< PB IDR: P6 Mask                         */
#define PB_IDR_P7_Pos                         7                                                       /*!< PB IDR: P7 Position                     */
#define PB_IDR_P7_Msk                         (0x01UL << PB_IDR_P7_Pos)                               /*!< PB IDR: P7 Mask                         */
#define PB_IDR_P8_Pos                         8                                                       /*!< PB IDR: P8 Position                     */
#define PB_IDR_P8_Msk                         (0x01UL << PB_IDR_P8_Pos)                               /*!< PB IDR: P8 Mask                         */
#define PB_IDR_P9_Pos                         9                                                       /*!< PB IDR: P9 Position                     */
#define PB_IDR_P9_Msk                         (0x01UL << PB_IDR_P9_Pos)                               /*!< PB IDR: P9 Mask                         */
#define PB_IDR_P10_Pos                        10                                                      /*!< PB IDR: P10 Position                    */
#define PB_IDR_P10_Msk                        (0x01UL << PB_IDR_P10_Pos)                              /*!< PB IDR: P10 Mask                        */
#define PB_IDR_P11_Pos                        11                                                      /*!< PB IDR: P11 Position                    */
#define PB_IDR_P11_Msk                        (0x01UL << PB_IDR_P11_Pos)                              /*!< PB IDR: P11 Mask                        */
#define PB_IDR_P12_Pos                        12                                                      /*!< PB IDR: P12 Position                    */
#define PB_IDR_P12_Msk                        (0x01UL << PB_IDR_P12_Pos)                              /*!< PB IDR: P12 Mask                        */
#define PB_IDR_P13_Pos                        13                                                      /*!< PB IDR: P13 Position                    */
#define PB_IDR_P13_Msk                        (0x01UL << PB_IDR_P13_Pos)                              /*!< PB IDR: P13 Mask                        */
#define PB_IDR_P14_Pos                        14                                                      /*!< PB IDR: P14 Position                    */
#define PB_IDR_P14_Msk                        (0x01UL << PB_IDR_P14_Pos)                              /*!< PB IDR: P14 Mask                        */
#define PB_IDR_P15_Pos                        15                                                      /*!< PB IDR: P15 Position                    */
#define PB_IDR_P15_Msk                        (0x01UL << PB_IDR_P15_Pos)                              /*!< PB IDR: P15 Mask                        */

/* -----------------------------------  PB_SRR  ----------------------------------- */
#define PB_SRR_P0_SET_Pos                     0                                                       /*!< PB SRR: P0_SET Position                 */
#define PB_SRR_P0_SET_Msk                     (0x01UL << PB_SRR_P0_SET_Pos)                           /*!< PB SRR: P0_SET Mask                     */
#define PB_SRR_P1_SET_Pos                     1                                                       /*!< PB SRR: P1_SET Position                 */
#define PB_SRR_P1_SET_Msk                     (0x01UL << PB_SRR_P1_SET_Pos)                           /*!< PB SRR: P1_SET Mask                     */
#define PB_SRR_P2_SET_Pos                     2                                                       /*!< PB SRR: P2_SET Position                 */
#define PB_SRR_P2_SET_Msk                     (0x01UL << PB_SRR_P2_SET_Pos)                           /*!< PB SRR: P2_SET Mask                     */
#define PB_SRR_P3_SET_Pos                     3                                                       /*!< PB SRR: P3_SET Position                 */
#define PB_SRR_P3_SET_Msk                     (0x01UL << PB_SRR_P3_SET_Pos)                           /*!< PB SRR: P3_SET Mask                     */
#define PB_SRR_P4_SET_Pos                     4                                                       /*!< PB SRR: P4_SET Position                 */
#define PB_SRR_P4_SET_Msk                     (0x01UL << PB_SRR_P4_SET_Pos)                           /*!< PB SRR: P4_SET Mask                     */
#define PB_SRR_P5_SET_Pos                     5                                                       /*!< PB SRR: P5_SET Position                 */
#define PB_SRR_P5_SET_Msk                     (0x01UL << PB_SRR_P5_SET_Pos)                           /*!< PB SRR: P5_SET Mask                     */
#define PB_SRR_P6_SET_Pos                     6                                                       /*!< PB SRR: P6_SET Position                 */
#define PB_SRR_P6_SET_Msk                     (0x01UL << PB_SRR_P6_SET_Pos)                           /*!< PB SRR: P6_SET Mask                     */
#define PB_SRR_P7_SET_Pos                     7                                                       /*!< PB SRR: P7_SET Position                 */
#define PB_SRR_P7_SET_Msk                     (0x01UL << PB_SRR_P7_SET_Pos)                           /*!< PB SRR: P7_SET Mask                     */
#define PB_SRR_P8_SET_Pos                     8                                                       /*!< PB SRR: P8_SET Position                 */
#define PB_SRR_P8_SET_Msk                     (0x01UL << PB_SRR_P8_SET_Pos)                           /*!< PB SRR: P8_SET Mask                     */
#define PB_SRR_P9_SET_Pos                     9                                                       /*!< PB SRR: P9_SET Position                 */
#define PB_SRR_P9_SET_Msk                     (0x01UL << PB_SRR_P9_SET_Pos)                           /*!< PB SRR: P9_SET Mask                     */
#define PB_SRR_P10_SET_Pos                    10                                                      /*!< PB SRR: P10_SET Position                */
#define PB_SRR_P10_SET_Msk                    (0x01UL << PB_SRR_P10_SET_Pos)                          /*!< PB SRR: P10_SET Mask                    */
#define PB_SRR_P11_SET_Pos                    11                                                      /*!< PB SRR: P11_SET Position                */
#define PB_SRR_P11_SET_Msk                    (0x01UL << PB_SRR_P11_SET_Pos)                          /*!< PB SRR: P11_SET Mask                    */
#define PB_SRR_P12_SET_Pos                    12                                                      /*!< PB SRR: P12_SET Position                */
#define PB_SRR_P12_SET_Msk                    (0x01UL << PB_SRR_P12_SET_Pos)                          /*!< PB SRR: P12_SET Mask                    */
#define PB_SRR_P13_SET_Pos                    13                                                      /*!< PB SRR: P13_SET Position                */
#define PB_SRR_P13_SET_Msk                    (0x01UL << PB_SRR_P13_SET_Pos)                          /*!< PB SRR: P13_SET Mask                    */
#define PB_SRR_P14_SET_Pos                    14                                                      /*!< PB SRR: P14_SET Position                */
#define PB_SRR_P14_SET_Msk                    (0x01UL << PB_SRR_P14_SET_Pos)                          /*!< PB SRR: P14_SET Mask                    */
#define PB_SRR_P15_SET_Pos                    15                                                      /*!< PB SRR: P15_SET Position                */
#define PB_SRR_P15_SET_Msk                    (0x01UL << PB_SRR_P15_SET_Pos)                          /*!< PB SRR: P15_SET Mask                    */
#define PB_SRR_P0_RESET_Pos                   16                                                      /*!< PB SRR: P0_RESET Position               */
#define PB_SRR_P0_RESET_Msk                   (0x01UL << PB_SRR_P0_RESET_Pos)                         /*!< PB SRR: P0_RESET Mask                   */
#define PB_SRR_P1_RESET_Pos                   17                                                      /*!< PB SRR: P1_RESET Position               */
#define PB_SRR_P1_RESET_Msk                   (0x01UL << PB_SRR_P1_RESET_Pos)                         /*!< PB SRR: P1_RESET Mask                   */
#define PB_SRR_P2_RESET_Pos                   18                                                      /*!< PB SRR: P2_RESET Position               */
#define PB_SRR_P2_RESET_Msk                   (0x01UL << PB_SRR_P2_RESET_Pos)                         /*!< PB SRR: P2_RESET Mask                   */
#define PB_SRR_P3_RESET_Pos                   19                                                      /*!< PB SRR: P3_RESET Position               */
#define PB_SRR_P3_RESET_Msk                   (0x01UL << PB_SRR_P3_RESET_Pos)                         /*!< PB SRR: P3_RESET Mask                   */
#define PB_SRR_P4_RESET_Pos                   20                                                      /*!< PB SRR: P4_RESET Position               */
#define PB_SRR_P4_RESET_Msk                   (0x01UL << PB_SRR_P4_RESET_Pos)                         /*!< PB SRR: P4_RESET Mask                   */
#define PB_SRR_P5_RESET_Pos                   21                                                      /*!< PB SRR: P5_RESET Position               */
#define PB_SRR_P5_RESET_Msk                   (0x01UL << PB_SRR_P5_RESET_Pos)                         /*!< PB SRR: P5_RESET Mask                   */
#define PB_SRR_P6_RESET_Pos                   22                                                      /*!< PB SRR: P6_RESET Position               */
#define PB_SRR_P6_RESET_Msk                   (0x01UL << PB_SRR_P6_RESET_Pos)                         /*!< PB SRR: P6_RESET Mask                   */
#define PB_SRR_P7_RESET_Pos                   23                                                      /*!< PB SRR: P7_RESET Position               */
#define PB_SRR_P7_RESET_Msk                   (0x01UL << PB_SRR_P7_RESET_Pos)                         /*!< PB SRR: P7_RESET Mask                   */
#define PB_SRR_P8_RESET_Pos                   24                                                      /*!< PB SRR: P8_RESET Position               */
#define PB_SRR_P8_RESET_Msk                   (0x01UL << PB_SRR_P8_RESET_Pos)                         /*!< PB SRR: P8_RESET Mask                   */
#define PB_SRR_P9_RESET_Pos                   25                                                      /*!< PB SRR: P9_RESET Position               */
#define PB_SRR_P9_RESET_Msk                   (0x01UL << PB_SRR_P9_RESET_Pos)                         /*!< PB SRR: P9_RESET Mask                   */
#define PB_SRR_P10_RESET_Pos                  26                                                      /*!< PB SRR: P10_RESET Position              */
#define PB_SRR_P10_RESET_Msk                  (0x01UL << PB_SRR_P10_RESET_Pos)                        /*!< PB SRR: P10_RESET Mask                  */
#define PB_SRR_P11_RESET_Pos                  27                                                      /*!< PB SRR: P11_RESET Position              */
#define PB_SRR_P11_RESET_Msk                  (0x01UL << PB_SRR_P11_RESET_Pos)                        /*!< PB SRR: P11_RESET Mask                  */
#define PB_SRR_P12_RESET_Pos                  28                                                      /*!< PB SRR: P12_RESET Position              */
#define PB_SRR_P12_RESET_Msk                  (0x01UL << PB_SRR_P12_RESET_Pos)                        /*!< PB SRR: P12_RESET Mask                  */
#define PB_SRR_P13_RESET_Pos                  29                                                      /*!< PB SRR: P13_RESET Position              */
#define PB_SRR_P13_RESET_Msk                  (0x01UL << PB_SRR_P13_RESET_Pos)                        /*!< PB SRR: P13_RESET Mask                  */
#define PB_SRR_P14_RESET_Pos                  30                                                      /*!< PB SRR: P14_RESET Position              */
#define PB_SRR_P14_RESET_Msk                  (0x01UL << PB_SRR_P14_RESET_Pos)                        /*!< PB SRR: P14_RESET Mask                  */
#define PB_SRR_P15_RESET_Pos                  31                                                      /*!< PB SRR: P15_RESET Position              */
#define PB_SRR_P15_RESET_Msk                  (0x01UL << PB_SRR_P15_RESET_Pos)                        /*!< PB SRR: P15_RESET Mask                  */


/* ================================================================================ */
/* ================           struct 'PC' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  PC_ODR  ----------------------------------- */
#define PC_ODR_P0_Pos                         0                                                       /*!< PC ODR: P0 Position                     */
#define PC_ODR_P0_Msk                         (0x01UL << PC_ODR_P0_Pos)                               /*!< PC ODR: P0 Mask                         */
#define PC_ODR_P1_Pos                         1                                                       /*!< PC ODR: P1 Position                     */
#define PC_ODR_P1_Msk                         (0x01UL << PC_ODR_P1_Pos)                               /*!< PC ODR: P1 Mask                         */
#define PC_ODR_P2_Pos                         2                                                       /*!< PC ODR: P2 Position                     */
#define PC_ODR_P2_Msk                         (0x01UL << PC_ODR_P2_Pos)                               /*!< PC ODR: P2 Mask                         */
#define PC_ODR_P3_Pos                         3                                                       /*!< PC ODR: P3 Position                     */
#define PC_ODR_P3_Msk                         (0x01UL << PC_ODR_P3_Pos)                               /*!< PC ODR: P3 Mask                         */
#define PC_ODR_P4_Pos                         4                                                       /*!< PC ODR: P4 Position                     */
#define PC_ODR_P4_Msk                         (0x01UL << PC_ODR_P4_Pos)                               /*!< PC ODR: P4 Mask                         */
#define PC_ODR_P5_Pos                         5                                                       /*!< PC ODR: P5 Position                     */
#define PC_ODR_P5_Msk                         (0x01UL << PC_ODR_P5_Pos)                               /*!< PC ODR: P5 Mask                         */
#define PC_ODR_P6_Pos                         6                                                       /*!< PC ODR: P6 Position                     */
#define PC_ODR_P6_Msk                         (0x01UL << PC_ODR_P6_Pos)                               /*!< PC ODR: P6 Mask                         */
#define PC_ODR_P7_Pos                         7                                                       /*!< PC ODR: P7 Position                     */
#define PC_ODR_P7_Msk                         (0x01UL << PC_ODR_P7_Pos)                               /*!< PC ODR: P7 Mask                         */
#define PC_ODR_P8_Pos                         8                                                       /*!< PC ODR: P8 Position                     */
#define PC_ODR_P8_Msk                         (0x01UL << PC_ODR_P8_Pos)                               /*!< PC ODR: P8 Mask                         */
#define PC_ODR_P9_Pos                         9                                                       /*!< PC ODR: P9 Position                     */
#define PC_ODR_P9_Msk                         (0x01UL << PC_ODR_P9_Pos)                               /*!< PC ODR: P9 Mask                         */
#define PC_ODR_P10_Pos                        10                                                      /*!< PC ODR: P10 Position                    */
#define PC_ODR_P10_Msk                        (0x01UL << PC_ODR_P10_Pos)                              /*!< PC ODR: P10 Mask                        */
#define PC_ODR_P11_Pos                        11                                                      /*!< PC ODR: P11 Position                    */
#define PC_ODR_P11_Msk                        (0x01UL << PC_ODR_P11_Pos)                              /*!< PC ODR: P11 Mask                        */
#define PC_ODR_P12_Pos                        12                                                      /*!< PC ODR: P12 Position                    */
#define PC_ODR_P12_Msk                        (0x01UL << PC_ODR_P12_Pos)                              /*!< PC ODR: P12 Mask                        */
#define PC_ODR_P13_Pos                        13                                                      /*!< PC ODR: P13 Position                    */
#define PC_ODR_P13_Msk                        (0x01UL << PC_ODR_P13_Pos)                              /*!< PC ODR: P13 Mask                        */
#define PC_ODR_P14_Pos                        14                                                      /*!< PC ODR: P14 Position                    */
#define PC_ODR_P14_Msk                        (0x01UL << PC_ODR_P14_Pos)                              /*!< PC ODR: P14 Mask                        */
#define PC_ODR_P15_Pos                        15                                                      /*!< PC ODR: P15 Position                    */
#define PC_ODR_P15_Msk                        (0x01UL << PC_ODR_P15_Pos)                              /*!< PC ODR: P15 Mask                        */

/* -----------------------------------  PC_IDR  ----------------------------------- */
#define PC_IDR_P0_Pos                         0                                                       /*!< PC IDR: P0 Position                     */
#define PC_IDR_P0_Msk                         (0x01UL << PC_IDR_P0_Pos)                               /*!< PC IDR: P0 Mask                         */
#define PC_IDR_P1_Pos                         1                                                       /*!< PC IDR: P1 Position                     */
#define PC_IDR_P1_Msk                         (0x01UL << PC_IDR_P1_Pos)                               /*!< PC IDR: P1 Mask                         */
#define PC_IDR_P2_Pos                         2                                                       /*!< PC IDR: P2 Position                     */
#define PC_IDR_P2_Msk                         (0x01UL << PC_IDR_P2_Pos)                               /*!< PC IDR: P2 Mask                         */
#define PC_IDR_P3_Pos                         3                                                       /*!< PC IDR: P3 Position                     */
#define PC_IDR_P3_Msk                         (0x01UL << PC_IDR_P3_Pos)                               /*!< PC IDR: P3 Mask                         */
#define PC_IDR_P4_Pos                         4                                                       /*!< PC IDR: P4 Position                     */
#define PC_IDR_P4_Msk                         (0x01UL << PC_IDR_P4_Pos)                               /*!< PC IDR: P4 Mask                         */
#define PC_IDR_P5_Pos                         5                                                       /*!< PC IDR: P5 Position                     */
#define PC_IDR_P5_Msk                         (0x01UL << PC_IDR_P5_Pos)                               /*!< PC IDR: P5 Mask                         */
#define PC_IDR_P6_Pos                         6                                                       /*!< PC IDR: P6 Position                     */
#define PC_IDR_P6_Msk                         (0x01UL << PC_IDR_P6_Pos)                               /*!< PC IDR: P6 Mask                         */
#define PC_IDR_P7_Pos                         7                                                       /*!< PC IDR: P7 Position                     */
#define PC_IDR_P7_Msk                         (0x01UL << PC_IDR_P7_Pos)                               /*!< PC IDR: P7 Mask                         */
#define PC_IDR_P8_Pos                         8                                                       /*!< PC IDR: P8 Position                     */
#define PC_IDR_P8_Msk                         (0x01UL << PC_IDR_P8_Pos)                               /*!< PC IDR: P8 Mask                         */
#define PC_IDR_P9_Pos                         9                                                       /*!< PC IDR: P9 Position                     */
#define PC_IDR_P9_Msk                         (0x01UL << PC_IDR_P9_Pos)                               /*!< PC IDR: P9 Mask                         */
#define PC_IDR_P10_Pos                        10                                                      /*!< PC IDR: P10 Position                    */
#define PC_IDR_P10_Msk                        (0x01UL << PC_IDR_P10_Pos)                              /*!< PC IDR: P10 Mask                        */
#define PC_IDR_P11_Pos                        11                                                      /*!< PC IDR: P11 Position                    */
#define PC_IDR_P11_Msk                        (0x01UL << PC_IDR_P11_Pos)                              /*!< PC IDR: P11 Mask                        */
#define PC_IDR_P12_Pos                        12                                                      /*!< PC IDR: P12 Position                    */
#define PC_IDR_P12_Msk                        (0x01UL << PC_IDR_P12_Pos)                              /*!< PC IDR: P12 Mask                        */
#define PC_IDR_P13_Pos                        13                                                      /*!< PC IDR: P13 Position                    */
#define PC_IDR_P13_Msk                        (0x01UL << PC_IDR_P13_Pos)                              /*!< PC IDR: P13 Mask                        */
#define PC_IDR_P14_Pos                        14                                                      /*!< PC IDR: P14 Position                    */
#define PC_IDR_P14_Msk                        (0x01UL << PC_IDR_P14_Pos)                              /*!< PC IDR: P14 Mask                        */
#define PC_IDR_P15_Pos                        15                                                      /*!< PC IDR: P15 Position                    */
#define PC_IDR_P15_Msk                        (0x01UL << PC_IDR_P15_Pos)                              /*!< PC IDR: P15 Mask                        */

/* -----------------------------------  PC_SRR  ----------------------------------- */
#define PC_SRR_P0_SET_Pos                     0                                                       /*!< PC SRR: P0_SET Position                 */
#define PC_SRR_P0_SET_Msk                     (0x01UL << PC_SRR_P0_SET_Pos)                           /*!< PC SRR: P0_SET Mask                     */
#define PC_SRR_P1_SET_Pos                     1                                                       /*!< PC SRR: P1_SET Position                 */
#define PC_SRR_P1_SET_Msk                     (0x01UL << PC_SRR_P1_SET_Pos)                           /*!< PC SRR: P1_SET Mask                     */
#define PC_SRR_P2_SET_Pos                     2                                                       /*!< PC SRR: P2_SET Position                 */
#define PC_SRR_P2_SET_Msk                     (0x01UL << PC_SRR_P2_SET_Pos)                           /*!< PC SRR: P2_SET Mask                     */
#define PC_SRR_P3_SET_Pos                     3                                                       /*!< PC SRR: P3_SET Position                 */
#define PC_SRR_P3_SET_Msk                     (0x01UL << PC_SRR_P3_SET_Pos)                           /*!< PC SRR: P3_SET Mask                     */
#define PC_SRR_P4_SET_Pos                     4                                                       /*!< PC SRR: P4_SET Position                 */
#define PC_SRR_P4_SET_Msk                     (0x01UL << PC_SRR_P4_SET_Pos)                           /*!< PC SRR: P4_SET Mask                     */
#define PC_SRR_P5_SET_Pos                     5                                                       /*!< PC SRR: P5_SET Position                 */
#define PC_SRR_P5_SET_Msk                     (0x01UL << PC_SRR_P5_SET_Pos)                           /*!< PC SRR: P5_SET Mask                     */
#define PC_SRR_P6_SET_Pos                     6                                                       /*!< PC SRR: P6_SET Position                 */
#define PC_SRR_P6_SET_Msk                     (0x01UL << PC_SRR_P6_SET_Pos)                           /*!< PC SRR: P6_SET Mask                     */
#define PC_SRR_P7_SET_Pos                     7                                                       /*!< PC SRR: P7_SET Position                 */
#define PC_SRR_P7_SET_Msk                     (0x01UL << PC_SRR_P7_SET_Pos)                           /*!< PC SRR: P7_SET Mask                     */
#define PC_SRR_P8_SET_Pos                     8                                                       /*!< PC SRR: P8_SET Position                 */
#define PC_SRR_P8_SET_Msk                     (0x01UL << PC_SRR_P8_SET_Pos)                           /*!< PC SRR: P8_SET Mask                     */
#define PC_SRR_P9_SET_Pos                     9                                                       /*!< PC SRR: P9_SET Position                 */
#define PC_SRR_P9_SET_Msk                     (0x01UL << PC_SRR_P9_SET_Pos)                           /*!< PC SRR: P9_SET Mask                     */
#define PC_SRR_P10_SET_Pos                    10                                                      /*!< PC SRR: P10_SET Position                */
#define PC_SRR_P10_SET_Msk                    (0x01UL << PC_SRR_P10_SET_Pos)                          /*!< PC SRR: P10_SET Mask                    */
#define PC_SRR_P11_SET_Pos                    11                                                      /*!< PC SRR: P11_SET Position                */
#define PC_SRR_P11_SET_Msk                    (0x01UL << PC_SRR_P11_SET_Pos)                          /*!< PC SRR: P11_SET Mask                    */
#define PC_SRR_P12_SET_Pos                    12                                                      /*!< PC SRR: P12_SET Position                */
#define PC_SRR_P12_SET_Msk                    (0x01UL << PC_SRR_P12_SET_Pos)                          /*!< PC SRR: P12_SET Mask                    */
#define PC_SRR_P13_SET_Pos                    13                                                      /*!< PC SRR: P13_SET Position                */
#define PC_SRR_P13_SET_Msk                    (0x01UL << PC_SRR_P13_SET_Pos)                          /*!< PC SRR: P13_SET Mask                    */
#define PC_SRR_P14_SET_Pos                    14                                                      /*!< PC SRR: P14_SET Position                */
#define PC_SRR_P14_SET_Msk                    (0x01UL << PC_SRR_P14_SET_Pos)                          /*!< PC SRR: P14_SET Mask                    */
#define PC_SRR_P15_SET_Pos                    15                                                      /*!< PC SRR: P15_SET Position                */
#define PC_SRR_P15_SET_Msk                    (0x01UL << PC_SRR_P15_SET_Pos)                          /*!< PC SRR: P15_SET Mask                    */
#define PC_SRR_P0_RESET_Pos                   16                                                      /*!< PC SRR: P0_RESET Position               */
#define PC_SRR_P0_RESET_Msk                   (0x01UL << PC_SRR_P0_RESET_Pos)                         /*!< PC SRR: P0_RESET Mask                   */
#define PC_SRR_P1_RESET_Pos                   17                                                      /*!< PC SRR: P1_RESET Position               */
#define PC_SRR_P1_RESET_Msk                   (0x01UL << PC_SRR_P1_RESET_Pos)                         /*!< PC SRR: P1_RESET Mask                   */
#define PC_SRR_P2_RESET_Pos                   18                                                      /*!< PC SRR: P2_RESET Position               */
#define PC_SRR_P2_RESET_Msk                   (0x01UL << PC_SRR_P2_RESET_Pos)                         /*!< PC SRR: P2_RESET Mask                   */
#define PC_SRR_P3_RESET_Pos                   19                                                      /*!< PC SRR: P3_RESET Position               */
#define PC_SRR_P3_RESET_Msk                   (0x01UL << PC_SRR_P3_RESET_Pos)                         /*!< PC SRR: P3_RESET Mask                   */
#define PC_SRR_P4_RESET_Pos                   20                                                      /*!< PC SRR: P4_RESET Position               */
#define PC_SRR_P4_RESET_Msk                   (0x01UL << PC_SRR_P4_RESET_Pos)                         /*!< PC SRR: P4_RESET Mask                   */
#define PC_SRR_P5_RESET_Pos                   21                                                      /*!< PC SRR: P5_RESET Position               */
#define PC_SRR_P5_RESET_Msk                   (0x01UL << PC_SRR_P5_RESET_Pos)                         /*!< PC SRR: P5_RESET Mask                   */
#define PC_SRR_P6_RESET_Pos                   22                                                      /*!< PC SRR: P6_RESET Position               */
#define PC_SRR_P6_RESET_Msk                   (0x01UL << PC_SRR_P6_RESET_Pos)                         /*!< PC SRR: P6_RESET Mask                   */
#define PC_SRR_P7_RESET_Pos                   23                                                      /*!< PC SRR: P7_RESET Position               */
#define PC_SRR_P7_RESET_Msk                   (0x01UL << PC_SRR_P7_RESET_Pos)                         /*!< PC SRR: P7_RESET Mask                   */
#define PC_SRR_P8_RESET_Pos                   24                                                      /*!< PC SRR: P8_RESET Position               */
#define PC_SRR_P8_RESET_Msk                   (0x01UL << PC_SRR_P8_RESET_Pos)                         /*!< PC SRR: P8_RESET Mask                   */
#define PC_SRR_P9_RESET_Pos                   25                                                      /*!< PC SRR: P9_RESET Position               */
#define PC_SRR_P9_RESET_Msk                   (0x01UL << PC_SRR_P9_RESET_Pos)                         /*!< PC SRR: P9_RESET Mask                   */
#define PC_SRR_P10_RESET_Pos                  26                                                      /*!< PC SRR: P10_RESET Position              */
#define PC_SRR_P10_RESET_Msk                  (0x01UL << PC_SRR_P10_RESET_Pos)                        /*!< PC SRR: P10_RESET Mask                  */
#define PC_SRR_P11_RESET_Pos                  27                                                      /*!< PC SRR: P11_RESET Position              */
#define PC_SRR_P11_RESET_Msk                  (0x01UL << PC_SRR_P11_RESET_Pos)                        /*!< PC SRR: P11_RESET Mask                  */
#define PC_SRR_P12_RESET_Pos                  28                                                      /*!< PC SRR: P12_RESET Position              */
#define PC_SRR_P12_RESET_Msk                  (0x01UL << PC_SRR_P12_RESET_Pos)                        /*!< PC SRR: P12_RESET Mask                  */
#define PC_SRR_P13_RESET_Pos                  29                                                      /*!< PC SRR: P13_RESET Position              */
#define PC_SRR_P13_RESET_Msk                  (0x01UL << PC_SRR_P13_RESET_Pos)                        /*!< PC SRR: P13_RESET Mask                  */
#define PC_SRR_P14_RESET_Pos                  30                                                      /*!< PC SRR: P14_RESET Position              */
#define PC_SRR_P14_RESET_Msk                  (0x01UL << PC_SRR_P14_RESET_Pos)                        /*!< PC SRR: P14_RESET Mask                  */
#define PC_SRR_P15_RESET_Pos                  31                                                      /*!< PC SRR: P15_RESET Position              */
#define PC_SRR_P15_RESET_Msk                  (0x01UL << PC_SRR_P15_RESET_Pos)                        /*!< PC SRR: P15_RESET Mask                  */


/* ================================================================================ */
/* ================           struct 'PD' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  PD_ODR  ----------------------------------- */
#define PD_ODR_P0_Pos                         0                                                       /*!< PD ODR: P0 Position                     */
#define PD_ODR_P0_Msk                         (0x01UL << PD_ODR_P0_Pos)                               /*!< PD ODR: P0 Mask                         */
#define PD_ODR_P1_Pos                         1                                                       /*!< PD ODR: P1 Position                     */
#define PD_ODR_P1_Msk                         (0x01UL << PD_ODR_P1_Pos)                               /*!< PD ODR: P1 Mask                         */
#define PD_ODR_P2_Pos                         2                                                       /*!< PD ODR: P2 Position                     */
#define PD_ODR_P2_Msk                         (0x01UL << PD_ODR_P2_Pos)                               /*!< PD ODR: P2 Mask                         */
#define PD_ODR_P3_Pos                         3                                                       /*!< PD ODR: P3 Position                     */
#define PD_ODR_P3_Msk                         (0x01UL << PD_ODR_P3_Pos)                               /*!< PD ODR: P3 Mask                         */
#define PD_ODR_P4_Pos                         4                                                       /*!< PD ODR: P4 Position                     */
#define PD_ODR_P4_Msk                         (0x01UL << PD_ODR_P4_Pos)                               /*!< PD ODR: P4 Mask                         */
#define PD_ODR_P5_Pos                         5                                                       /*!< PD ODR: P5 Position                     */
#define PD_ODR_P5_Msk                         (0x01UL << PD_ODR_P5_Pos)                               /*!< PD ODR: P5 Mask                         */
#define PD_ODR_P6_Pos                         6                                                       /*!< PD ODR: P6 Position                     */
#define PD_ODR_P6_Msk                         (0x01UL << PD_ODR_P6_Pos)                               /*!< PD ODR: P6 Mask                         */
#define PD_ODR_P7_Pos                         7                                                       /*!< PD ODR: P7 Position                     */
#define PD_ODR_P7_Msk                         (0x01UL << PD_ODR_P7_Pos)                               /*!< PD ODR: P7 Mask                         */
#define PD_ODR_P8_Pos                         8                                                       /*!< PD ODR: P8 Position                     */
#define PD_ODR_P8_Msk                         (0x01UL << PD_ODR_P8_Pos)                               /*!< PD ODR: P8 Mask                         */
#define PD_ODR_P9_Pos                         9                                                       /*!< PD ODR: P9 Position                     */
#define PD_ODR_P9_Msk                         (0x01UL << PD_ODR_P9_Pos)                               /*!< PD ODR: P9 Mask                         */
#define PD_ODR_P10_Pos                        10                                                      /*!< PD ODR: P10 Position                    */
#define PD_ODR_P10_Msk                        (0x01UL << PD_ODR_P10_Pos)                              /*!< PD ODR: P10 Mask                        */
#define PD_ODR_P11_Pos                        11                                                      /*!< PD ODR: P11 Position                    */
#define PD_ODR_P11_Msk                        (0x01UL << PD_ODR_P11_Pos)                              /*!< PD ODR: P11 Mask                        */
#define PD_ODR_P12_Pos                        12                                                      /*!< PD ODR: P12 Position                    */
#define PD_ODR_P12_Msk                        (0x01UL << PD_ODR_P12_Pos)                              /*!< PD ODR: P12 Mask                        */
#define PD_ODR_P13_Pos                        13                                                      /*!< PD ODR: P13 Position                    */
#define PD_ODR_P13_Msk                        (0x01UL << PD_ODR_P13_Pos)                              /*!< PD ODR: P13 Mask                        */
#define PD_ODR_P14_Pos                        14                                                      /*!< PD ODR: P14 Position                    */
#define PD_ODR_P14_Msk                        (0x01UL << PD_ODR_P14_Pos)                              /*!< PD ODR: P14 Mask                        */
#define PD_ODR_P15_Pos                        15                                                      /*!< PD ODR: P15 Position                    */
#define PD_ODR_P15_Msk                        (0x01UL << PD_ODR_P15_Pos)                              /*!< PD ODR: P15 Mask                        */

/* -----------------------------------  PD_IDR  ----------------------------------- */
#define PD_IDR_P0_Pos                         0                                                       /*!< PD IDR: P0 Position                     */
#define PD_IDR_P0_Msk                         (0x01UL << PD_IDR_P0_Pos)                               /*!< PD IDR: P0 Mask                         */
#define PD_IDR_P1_Pos                         1                                                       /*!< PD IDR: P1 Position                     */
#define PD_IDR_P1_Msk                         (0x01UL << PD_IDR_P1_Pos)                               /*!< PD IDR: P1 Mask                         */
#define PD_IDR_P2_Pos                         2                                                       /*!< PD IDR: P2 Position                     */
#define PD_IDR_P2_Msk                         (0x01UL << PD_IDR_P2_Pos)                               /*!< PD IDR: P2 Mask                         */
#define PD_IDR_P3_Pos                         3                                                       /*!< PD IDR: P3 Position                     */
#define PD_IDR_P3_Msk                         (0x01UL << PD_IDR_P3_Pos)                               /*!< PD IDR: P3 Mask                         */
#define PD_IDR_P4_Pos                         4                                                       /*!< PD IDR: P4 Position                     */
#define PD_IDR_P4_Msk                         (0x01UL << PD_IDR_P4_Pos)                               /*!< PD IDR: P4 Mask                         */
#define PD_IDR_P5_Pos                         5                                                       /*!< PD IDR: P5 Position                     */
#define PD_IDR_P5_Msk                         (0x01UL << PD_IDR_P5_Pos)                               /*!< PD IDR: P5 Mask                         */
#define PD_IDR_P6_Pos                         6                                                       /*!< PD IDR: P6 Position                     */
#define PD_IDR_P6_Msk                         (0x01UL << PD_IDR_P6_Pos)                               /*!< PD IDR: P6 Mask                         */
#define PD_IDR_P7_Pos                         7                                                       /*!< PD IDR: P7 Position                     */
#define PD_IDR_P7_Msk                         (0x01UL << PD_IDR_P7_Pos)                               /*!< PD IDR: P7 Mask                         */
#define PD_IDR_P8_Pos                         8                                                       /*!< PD IDR: P8 Position                     */
#define PD_IDR_P8_Msk                         (0x01UL << PD_IDR_P8_Pos)                               /*!< PD IDR: P8 Mask                         */
#define PD_IDR_P9_Pos                         9                                                       /*!< PD IDR: P9 Position                     */
#define PD_IDR_P9_Msk                         (0x01UL << PD_IDR_P9_Pos)                               /*!< PD IDR: P9 Mask                         */
#define PD_IDR_P10_Pos                        10                                                      /*!< PD IDR: P10 Position                    */
#define PD_IDR_P10_Msk                        (0x01UL << PD_IDR_P10_Pos)                              /*!< PD IDR: P10 Mask                        */
#define PD_IDR_P11_Pos                        11                                                      /*!< PD IDR: P11 Position                    */
#define PD_IDR_P11_Msk                        (0x01UL << PD_IDR_P11_Pos)                              /*!< PD IDR: P11 Mask                        */
#define PD_IDR_P12_Pos                        12                                                      /*!< PD IDR: P12 Position                    */
#define PD_IDR_P12_Msk                        (0x01UL << PD_IDR_P12_Pos)                              /*!< PD IDR: P12 Mask                        */
#define PD_IDR_P13_Pos                        13                                                      /*!< PD IDR: P13 Position                    */
#define PD_IDR_P13_Msk                        (0x01UL << PD_IDR_P13_Pos)                              /*!< PD IDR: P13 Mask                        */
#define PD_IDR_P14_Pos                        14                                                      /*!< PD IDR: P14 Position                    */
#define PD_IDR_P14_Msk                        (0x01UL << PD_IDR_P14_Pos)                              /*!< PD IDR: P14 Mask                        */
#define PD_IDR_P15_Pos                        15                                                      /*!< PD IDR: P15 Position                    */
#define PD_IDR_P15_Msk                        (0x01UL << PD_IDR_P15_Pos)                              /*!< PD IDR: P15 Mask                        */

/* -----------------------------------  PD_SRR  ----------------------------------- */
#define PD_SRR_P0_SET_Pos                     0                                                       /*!< PD SRR: P0_SET Position                 */
#define PD_SRR_P0_SET_Msk                     (0x01UL << PD_SRR_P0_SET_Pos)                           /*!< PD SRR: P0_SET Mask                     */
#define PD_SRR_P1_SET_Pos                     1                                                       /*!< PD SRR: P1_SET Position                 */
#define PD_SRR_P1_SET_Msk                     (0x01UL << PD_SRR_P1_SET_Pos)                           /*!< PD SRR: P1_SET Mask                     */
#define PD_SRR_P2_SET_Pos                     2                                                       /*!< PD SRR: P2_SET Position                 */
#define PD_SRR_P2_SET_Msk                     (0x01UL << PD_SRR_P2_SET_Pos)                           /*!< PD SRR: P2_SET Mask                     */
#define PD_SRR_P3_SET_Pos                     3                                                       /*!< PD SRR: P3_SET Position                 */
#define PD_SRR_P3_SET_Msk                     (0x01UL << PD_SRR_P3_SET_Pos)                           /*!< PD SRR: P3_SET Mask                     */
#define PD_SRR_P4_SET_Pos                     4                                                       /*!< PD SRR: P4_SET Position                 */
#define PD_SRR_P4_SET_Msk                     (0x01UL << PD_SRR_P4_SET_Pos)                           /*!< PD SRR: P4_SET Mask                     */
#define PD_SRR_P5_SET_Pos                     5                                                       /*!< PD SRR: P5_SET Position                 */
#define PD_SRR_P5_SET_Msk                     (0x01UL << PD_SRR_P5_SET_Pos)                           /*!< PD SRR: P5_SET Mask                     */
#define PD_SRR_P6_SET_Pos                     6                                                       /*!< PD SRR: P6_SET Position                 */
#define PD_SRR_P6_SET_Msk                     (0x01UL << PD_SRR_P6_SET_Pos)                           /*!< PD SRR: P6_SET Mask                     */
#define PD_SRR_P7_SET_Pos                     7                                                       /*!< PD SRR: P7_SET Position                 */
#define PD_SRR_P7_SET_Msk                     (0x01UL << PD_SRR_P7_SET_Pos)                           /*!< PD SRR: P7_SET Mask                     */
#define PD_SRR_P8_SET_Pos                     8                                                       /*!< PD SRR: P8_SET Position                 */
#define PD_SRR_P8_SET_Msk                     (0x01UL << PD_SRR_P8_SET_Pos)                           /*!< PD SRR: P8_SET Mask                     */
#define PD_SRR_P9_SET_Pos                     9                                                       /*!< PD SRR: P9_SET Position                 */
#define PD_SRR_P9_SET_Msk                     (0x01UL << PD_SRR_P9_SET_Pos)                           /*!< PD SRR: P9_SET Mask                     */
#define PD_SRR_P10_SET_Pos                    10                                                      /*!< PD SRR: P10_SET Position                */
#define PD_SRR_P10_SET_Msk                    (0x01UL << PD_SRR_P10_SET_Pos)                          /*!< PD SRR: P10_SET Mask                    */
#define PD_SRR_P11_SET_Pos                    11                                                      /*!< PD SRR: P11_SET Position                */
#define PD_SRR_P11_SET_Msk                    (0x01UL << PD_SRR_P11_SET_Pos)                          /*!< PD SRR: P11_SET Mask                    */
#define PD_SRR_P12_SET_Pos                    12                                                      /*!< PD SRR: P12_SET Position                */
#define PD_SRR_P12_SET_Msk                    (0x01UL << PD_SRR_P12_SET_Pos)                          /*!< PD SRR: P12_SET Mask                    */
#define PD_SRR_P13_SET_Pos                    13                                                      /*!< PD SRR: P13_SET Position                */
#define PD_SRR_P13_SET_Msk                    (0x01UL << PD_SRR_P13_SET_Pos)                          /*!< PD SRR: P13_SET Mask                    */
#define PD_SRR_P14_SET_Pos                    14                                                      /*!< PD SRR: P14_SET Position                */
#define PD_SRR_P14_SET_Msk                    (0x01UL << PD_SRR_P14_SET_Pos)                          /*!< PD SRR: P14_SET Mask                    */
#define PD_SRR_P15_SET_Pos                    15                                                      /*!< PD SRR: P15_SET Position                */
#define PD_SRR_P15_SET_Msk                    (0x01UL << PD_SRR_P15_SET_Pos)                          /*!< PD SRR: P15_SET Mask                    */
#define PD_SRR_P0_RESET_Pos                   16                                                      /*!< PD SRR: P0_RESET Position               */
#define PD_SRR_P0_RESET_Msk                   (0x01UL << PD_SRR_P0_RESET_Pos)                         /*!< PD SRR: P0_RESET Mask                   */
#define PD_SRR_P1_RESET_Pos                   17                                                      /*!< PD SRR: P1_RESET Position               */
#define PD_SRR_P1_RESET_Msk                   (0x01UL << PD_SRR_P1_RESET_Pos)                         /*!< PD SRR: P1_RESET Mask                   */
#define PD_SRR_P2_RESET_Pos                   18                                                      /*!< PD SRR: P2_RESET Position               */
#define PD_SRR_P2_RESET_Msk                   (0x01UL << PD_SRR_P2_RESET_Pos)                         /*!< PD SRR: P2_RESET Mask                   */
#define PD_SRR_P3_RESET_Pos                   19                                                      /*!< PD SRR: P3_RESET Position               */
#define PD_SRR_P3_RESET_Msk                   (0x01UL << PD_SRR_P3_RESET_Pos)                         /*!< PD SRR: P3_RESET Mask                   */
#define PD_SRR_P4_RESET_Pos                   20                                                      /*!< PD SRR: P4_RESET Position               */
#define PD_SRR_P4_RESET_Msk                   (0x01UL << PD_SRR_P4_RESET_Pos)                         /*!< PD SRR: P4_RESET Mask                   */
#define PD_SRR_P5_RESET_Pos                   21                                                      /*!< PD SRR: P5_RESET Position               */
#define PD_SRR_P5_RESET_Msk                   (0x01UL << PD_SRR_P5_RESET_Pos)                         /*!< PD SRR: P5_RESET Mask                   */
#define PD_SRR_P6_RESET_Pos                   22                                                      /*!< PD SRR: P6_RESET Position               */
#define PD_SRR_P6_RESET_Msk                   (0x01UL << PD_SRR_P6_RESET_Pos)                         /*!< PD SRR: P6_RESET Mask                   */
#define PD_SRR_P7_RESET_Pos                   23                                                      /*!< PD SRR: P7_RESET Position               */
#define PD_SRR_P7_RESET_Msk                   (0x01UL << PD_SRR_P7_RESET_Pos)                         /*!< PD SRR: P7_RESET Mask                   */
#define PD_SRR_P8_RESET_Pos                   24                                                      /*!< PD SRR: P8_RESET Position               */
#define PD_SRR_P8_RESET_Msk                   (0x01UL << PD_SRR_P8_RESET_Pos)                         /*!< PD SRR: P8_RESET Mask                   */
#define PD_SRR_P9_RESET_Pos                   25                                                      /*!< PD SRR: P9_RESET Position               */
#define PD_SRR_P9_RESET_Msk                   (0x01UL << PD_SRR_P9_RESET_Pos)                         /*!< PD SRR: P9_RESET Mask                   */
#define PD_SRR_P10_RESET_Pos                  26                                                      /*!< PD SRR: P10_RESET Position              */
#define PD_SRR_P10_RESET_Msk                  (0x01UL << PD_SRR_P10_RESET_Pos)                        /*!< PD SRR: P10_RESET Mask                  */
#define PD_SRR_P11_RESET_Pos                  27                                                      /*!< PD SRR: P11_RESET Position              */
#define PD_SRR_P11_RESET_Msk                  (0x01UL << PD_SRR_P11_RESET_Pos)                        /*!< PD SRR: P11_RESET Mask                  */
#define PD_SRR_P12_RESET_Pos                  28                                                      /*!< PD SRR: P12_RESET Position              */
#define PD_SRR_P12_RESET_Msk                  (0x01UL << PD_SRR_P12_RESET_Pos)                        /*!< PD SRR: P12_RESET Mask                  */
#define PD_SRR_P13_RESET_Pos                  29                                                      /*!< PD SRR: P13_RESET Position              */
#define PD_SRR_P13_RESET_Msk                  (0x01UL << PD_SRR_P13_RESET_Pos)                        /*!< PD SRR: P13_RESET Mask                  */
#define PD_SRR_P14_RESET_Pos                  30                                                      /*!< PD SRR: P14_RESET Position              */
#define PD_SRR_P14_RESET_Msk                  (0x01UL << PD_SRR_P14_RESET_Pos)                        /*!< PD SRR: P14_RESET Mask                  */
#define PD_SRR_P15_RESET_Pos                  31                                                      /*!< PD SRR: P15_RESET Position              */
#define PD_SRR_P15_RESET_Msk                  (0x01UL << PD_SRR_P15_RESET_Pos)                        /*!< PD SRR: P15_RESET Mask                  */


/* ================================================================================ */
/* ================           struct 'PE' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  PE_ODR  ----------------------------------- */
#define PE_ODR_P0_Pos                         0                                                       /*!< PE ODR: P0 Position                     */
#define PE_ODR_P0_Msk                         (0x01UL << PE_ODR_P0_Pos)                               /*!< PE ODR: P0 Mask                         */
#define PE_ODR_P1_Pos                         1                                                       /*!< PE ODR: P1 Position                     */
#define PE_ODR_P1_Msk                         (0x01UL << PE_ODR_P1_Pos)                               /*!< PE ODR: P1 Mask                         */
#define PE_ODR_P2_Pos                         2                                                       /*!< PE ODR: P2 Position                     */
#define PE_ODR_P2_Msk                         (0x01UL << PE_ODR_P2_Pos)                               /*!< PE ODR: P2 Mask                         */
#define PE_ODR_P3_Pos                         3                                                       /*!< PE ODR: P3 Position                     */
#define PE_ODR_P3_Msk                         (0x01UL << PE_ODR_P3_Pos)                               /*!< PE ODR: P3 Mask                         */
#define PE_ODR_P4_Pos                         4                                                       /*!< PE ODR: P4 Position                     */
#define PE_ODR_P4_Msk                         (0x01UL << PE_ODR_P4_Pos)                               /*!< PE ODR: P4 Mask                         */
#define PE_ODR_P5_Pos                         5                                                       /*!< PE ODR: P5 Position                     */
#define PE_ODR_P5_Msk                         (0x01UL << PE_ODR_P5_Pos)                               /*!< PE ODR: P5 Mask                         */
#define PE_ODR_P6_Pos                         6                                                       /*!< PE ODR: P6 Position                     */
#define PE_ODR_P6_Msk                         (0x01UL << PE_ODR_P6_Pos)                               /*!< PE ODR: P6 Mask                         */
#define PE_ODR_P7_Pos                         7                                                       /*!< PE ODR: P7 Position                     */
#define PE_ODR_P7_Msk                         (0x01UL << PE_ODR_P7_Pos)                               /*!< PE ODR: P7 Mask                         */
#define PE_ODR_P8_Pos                         8                                                       /*!< PE ODR: P8 Position                     */
#define PE_ODR_P8_Msk                         (0x01UL << PE_ODR_P8_Pos)                               /*!< PE ODR: P8 Mask                         */
#define PE_ODR_P9_Pos                         9                                                       /*!< PE ODR: P9 Position                     */
#define PE_ODR_P9_Msk                         (0x01UL << PE_ODR_P9_Pos)                               /*!< PE ODR: P9 Mask                         */
#define PE_ODR_P10_Pos                        10                                                      /*!< PE ODR: P10 Position                    */
#define PE_ODR_P10_Msk                        (0x01UL << PE_ODR_P10_Pos)                              /*!< PE ODR: P10 Mask                        */
#define PE_ODR_P11_Pos                        11                                                      /*!< PE ODR: P11 Position                    */
#define PE_ODR_P11_Msk                        (0x01UL << PE_ODR_P11_Pos)                              /*!< PE ODR: P11 Mask                        */
#define PE_ODR_P12_Pos                        12                                                      /*!< PE ODR: P12 Position                    */
#define PE_ODR_P12_Msk                        (0x01UL << PE_ODR_P12_Pos)                              /*!< PE ODR: P12 Mask                        */
#define PE_ODR_P13_Pos                        13                                                      /*!< PE ODR: P13 Position                    */
#define PE_ODR_P13_Msk                        (0x01UL << PE_ODR_P13_Pos)                              /*!< PE ODR: P13 Mask                        */
#define PE_ODR_P14_Pos                        14                                                      /*!< PE ODR: P14 Position                    */
#define PE_ODR_P14_Msk                        (0x01UL << PE_ODR_P14_Pos)                              /*!< PE ODR: P14 Mask                        */
#define PE_ODR_P15_Pos                        15                                                      /*!< PE ODR: P15 Position                    */
#define PE_ODR_P15_Msk                        (0x01UL << PE_ODR_P15_Pos)                              /*!< PE ODR: P15 Mask                        */

/* -----------------------------------  PE_IDR  ----------------------------------- */
#define PE_IDR_P0_Pos                         0                                                       /*!< PE IDR: P0 Position                     */
#define PE_IDR_P0_Msk                         (0x01UL << PE_IDR_P0_Pos)                               /*!< PE IDR: P0 Mask                         */
#define PE_IDR_P1_Pos                         1                                                       /*!< PE IDR: P1 Position                     */
#define PE_IDR_P1_Msk                         (0x01UL << PE_IDR_P1_Pos)                               /*!< PE IDR: P1 Mask                         */
#define PE_IDR_P2_Pos                         2                                                       /*!< PE IDR: P2 Position                     */
#define PE_IDR_P2_Msk                         (0x01UL << PE_IDR_P2_Pos)                               /*!< PE IDR: P2 Mask                         */
#define PE_IDR_P3_Pos                         3                                                       /*!< PE IDR: P3 Position                     */
#define PE_IDR_P3_Msk                         (0x01UL << PE_IDR_P3_Pos)                               /*!< PE IDR: P3 Mask                         */
#define PE_IDR_P4_Pos                         4                                                       /*!< PE IDR: P4 Position                     */
#define PE_IDR_P4_Msk                         (0x01UL << PE_IDR_P4_Pos)                               /*!< PE IDR: P4 Mask                         */
#define PE_IDR_P5_Pos                         5                                                       /*!< PE IDR: P5 Position                     */
#define PE_IDR_P5_Msk                         (0x01UL << PE_IDR_P5_Pos)                               /*!< PE IDR: P5 Mask                         */
#define PE_IDR_P6_Pos                         6                                                       /*!< PE IDR: P6 Position                     */
#define PE_IDR_P6_Msk                         (0x01UL << PE_IDR_P6_Pos)                               /*!< PE IDR: P6 Mask                         */
#define PE_IDR_P7_Pos                         7                                                       /*!< PE IDR: P7 Position                     */
#define PE_IDR_P7_Msk                         (0x01UL << PE_IDR_P7_Pos)                               /*!< PE IDR: P7 Mask                         */
#define PE_IDR_P8_Pos                         8                                                       /*!< PE IDR: P8 Position                     */
#define PE_IDR_P8_Msk                         (0x01UL << PE_IDR_P8_Pos)                               /*!< PE IDR: P8 Mask                         */
#define PE_IDR_P9_Pos                         9                                                       /*!< PE IDR: P9 Position                     */
#define PE_IDR_P9_Msk                         (0x01UL << PE_IDR_P9_Pos)                               /*!< PE IDR: P9 Mask                         */
#define PE_IDR_P10_Pos                        10                                                      /*!< PE IDR: P10 Position                    */
#define PE_IDR_P10_Msk                        (0x01UL << PE_IDR_P10_Pos)                              /*!< PE IDR: P10 Mask                        */
#define PE_IDR_P11_Pos                        11                                                      /*!< PE IDR: P11 Position                    */
#define PE_IDR_P11_Msk                        (0x01UL << PE_IDR_P11_Pos)                              /*!< PE IDR: P11 Mask                        */
#define PE_IDR_P12_Pos                        12                                                      /*!< PE IDR: P12 Position                    */
#define PE_IDR_P12_Msk                        (0x01UL << PE_IDR_P12_Pos)                              /*!< PE IDR: P12 Mask                        */
#define PE_IDR_P13_Pos                        13                                                      /*!< PE IDR: P13 Position                    */
#define PE_IDR_P13_Msk                        (0x01UL << PE_IDR_P13_Pos)                              /*!< PE IDR: P13 Mask                        */
#define PE_IDR_P14_Pos                        14                                                      /*!< PE IDR: P14 Position                    */
#define PE_IDR_P14_Msk                        (0x01UL << PE_IDR_P14_Pos)                              /*!< PE IDR: P14 Mask                        */
#define PE_IDR_P15_Pos                        15                                                      /*!< PE IDR: P15 Position                    */
#define PE_IDR_P15_Msk                        (0x01UL << PE_IDR_P15_Pos)                              /*!< PE IDR: P15 Mask                        */

/* -----------------------------------  PE_SRR  ----------------------------------- */
#define PE_SRR_P0_SET_Pos                     0                                                       /*!< PE SRR: P0_SET Position                 */
#define PE_SRR_P0_SET_Msk                     (0x01UL << PE_SRR_P0_SET_Pos)                           /*!< PE SRR: P0_SET Mask                     */
#define PE_SRR_P1_SET_Pos                     1                                                       /*!< PE SRR: P1_SET Position                 */
#define PE_SRR_P1_SET_Msk                     (0x01UL << PE_SRR_P1_SET_Pos)                           /*!< PE SRR: P1_SET Mask                     */
#define PE_SRR_P2_SET_Pos                     2                                                       /*!< PE SRR: P2_SET Position                 */
#define PE_SRR_P2_SET_Msk                     (0x01UL << PE_SRR_P2_SET_Pos)                           /*!< PE SRR: P2_SET Mask                     */
#define PE_SRR_P3_SET_Pos                     3                                                       /*!< PE SRR: P3_SET Position                 */
#define PE_SRR_P3_SET_Msk                     (0x01UL << PE_SRR_P3_SET_Pos)                           /*!< PE SRR: P3_SET Mask                     */
#define PE_SRR_P4_SET_Pos                     4                                                       /*!< PE SRR: P4_SET Position                 */
#define PE_SRR_P4_SET_Msk                     (0x01UL << PE_SRR_P4_SET_Pos)                           /*!< PE SRR: P4_SET Mask                     */
#define PE_SRR_P5_SET_Pos                     5                                                       /*!< PE SRR: P5_SET Position                 */
#define PE_SRR_P5_SET_Msk                     (0x01UL << PE_SRR_P5_SET_Pos)                           /*!< PE SRR: P5_SET Mask                     */
#define PE_SRR_P6_SET_Pos                     6                                                       /*!< PE SRR: P6_SET Position                 */
#define PE_SRR_P6_SET_Msk                     (0x01UL << PE_SRR_P6_SET_Pos)                           /*!< PE SRR: P6_SET Mask                     */
#define PE_SRR_P7_SET_Pos                     7                                                       /*!< PE SRR: P7_SET Position                 */
#define PE_SRR_P7_SET_Msk                     (0x01UL << PE_SRR_P7_SET_Pos)                           /*!< PE SRR: P7_SET Mask                     */
#define PE_SRR_P8_SET_Pos                     8                                                       /*!< PE SRR: P8_SET Position                 */
#define PE_SRR_P8_SET_Msk                     (0x01UL << PE_SRR_P8_SET_Pos)                           /*!< PE SRR: P8_SET Mask                     */
#define PE_SRR_P9_SET_Pos                     9                                                       /*!< PE SRR: P9_SET Position                 */
#define PE_SRR_P9_SET_Msk                     (0x01UL << PE_SRR_P9_SET_Pos)                           /*!< PE SRR: P9_SET Mask                     */
#define PE_SRR_P10_SET_Pos                    10                                                      /*!< PE SRR: P10_SET Position                */
#define PE_SRR_P10_SET_Msk                    (0x01UL << PE_SRR_P10_SET_Pos)                          /*!< PE SRR: P10_SET Mask                    */
#define PE_SRR_P11_SET_Pos                    11                                                      /*!< PE SRR: P11_SET Position                */
#define PE_SRR_P11_SET_Msk                    (0x01UL << PE_SRR_P11_SET_Pos)                          /*!< PE SRR: P11_SET Mask                    */
#define PE_SRR_P12_SET_Pos                    12                                                      /*!< PE SRR: P12_SET Position                */
#define PE_SRR_P12_SET_Msk                    (0x01UL << PE_SRR_P12_SET_Pos)                          /*!< PE SRR: P12_SET Mask                    */
#define PE_SRR_P13_SET_Pos                    13                                                      /*!< PE SRR: P13_SET Position                */
#define PE_SRR_P13_SET_Msk                    (0x01UL << PE_SRR_P13_SET_Pos)                          /*!< PE SRR: P13_SET Mask                    */
#define PE_SRR_P14_SET_Pos                    14                                                      /*!< PE SRR: P14_SET Position                */
#define PE_SRR_P14_SET_Msk                    (0x01UL << PE_SRR_P14_SET_Pos)                          /*!< PE SRR: P14_SET Mask                    */
#define PE_SRR_P15_SET_Pos                    15                                                      /*!< PE SRR: P15_SET Position                */
#define PE_SRR_P15_SET_Msk                    (0x01UL << PE_SRR_P15_SET_Pos)                          /*!< PE SRR: P15_SET Mask                    */
#define PE_SRR_P0_RESET_Pos                   16                                                      /*!< PE SRR: P0_RESET Position               */
#define PE_SRR_P0_RESET_Msk                   (0x01UL << PE_SRR_P0_RESET_Pos)                         /*!< PE SRR: P0_RESET Mask                   */
#define PE_SRR_P1_RESET_Pos                   17                                                      /*!< PE SRR: P1_RESET Position               */
#define PE_SRR_P1_RESET_Msk                   (0x01UL << PE_SRR_P1_RESET_Pos)                         /*!< PE SRR: P1_RESET Mask                   */
#define PE_SRR_P2_RESET_Pos                   18                                                      /*!< PE SRR: P2_RESET Position               */
#define PE_SRR_P2_RESET_Msk                   (0x01UL << PE_SRR_P2_RESET_Pos)                         /*!< PE SRR: P2_RESET Mask                   */
#define PE_SRR_P3_RESET_Pos                   19                                                      /*!< PE SRR: P3_RESET Position               */
#define PE_SRR_P3_RESET_Msk                   (0x01UL << PE_SRR_P3_RESET_Pos)                         /*!< PE SRR: P3_RESET Mask                   */
#define PE_SRR_P4_RESET_Pos                   20                                                      /*!< PE SRR: P4_RESET Position               */
#define PE_SRR_P4_RESET_Msk                   (0x01UL << PE_SRR_P4_RESET_Pos)                         /*!< PE SRR: P4_RESET Mask                   */
#define PE_SRR_P5_RESET_Pos                   21                                                      /*!< PE SRR: P5_RESET Position               */
#define PE_SRR_P5_RESET_Msk                   (0x01UL << PE_SRR_P5_RESET_Pos)                         /*!< PE SRR: P5_RESET Mask                   */
#define PE_SRR_P6_RESET_Pos                   22                                                      /*!< PE SRR: P6_RESET Position               */
#define PE_SRR_P6_RESET_Msk                   (0x01UL << PE_SRR_P6_RESET_Pos)                         /*!< PE SRR: P6_RESET Mask                   */
#define PE_SRR_P7_RESET_Pos                   23                                                      /*!< PE SRR: P7_RESET Position               */
#define PE_SRR_P7_RESET_Msk                   (0x01UL << PE_SRR_P7_RESET_Pos)                         /*!< PE SRR: P7_RESET Mask                   */
#define PE_SRR_P8_RESET_Pos                   24                                                      /*!< PE SRR: P8_RESET Position               */
#define PE_SRR_P8_RESET_Msk                   (0x01UL << PE_SRR_P8_RESET_Pos)                         /*!< PE SRR: P8_RESET Mask                   */
#define PE_SRR_P9_RESET_Pos                   25                                                      /*!< PE SRR: P9_RESET Position               */
#define PE_SRR_P9_RESET_Msk                   (0x01UL << PE_SRR_P9_RESET_Pos)                         /*!< PE SRR: P9_RESET Mask                   */
#define PE_SRR_P10_RESET_Pos                  26                                                      /*!< PE SRR: P10_RESET Position              */
#define PE_SRR_P10_RESET_Msk                  (0x01UL << PE_SRR_P10_RESET_Pos)                        /*!< PE SRR: P10_RESET Mask                  */
#define PE_SRR_P11_RESET_Pos                  27                                                      /*!< PE SRR: P11_RESET Position              */
#define PE_SRR_P11_RESET_Msk                  (0x01UL << PE_SRR_P11_RESET_Pos)                        /*!< PE SRR: P11_RESET Mask                  */
#define PE_SRR_P12_RESET_Pos                  28                                                      /*!< PE SRR: P12_RESET Position              */
#define PE_SRR_P12_RESET_Msk                  (0x01UL << PE_SRR_P12_RESET_Pos)                        /*!< PE SRR: P12_RESET Mask                  */
#define PE_SRR_P13_RESET_Pos                  29                                                      /*!< PE SRR: P13_RESET Position              */
#define PE_SRR_P13_RESET_Msk                  (0x01UL << PE_SRR_P13_RESET_Pos)                        /*!< PE SRR: P13_RESET Mask                  */
#define PE_SRR_P14_RESET_Pos                  30                                                      /*!< PE SRR: P14_RESET Position              */
#define PE_SRR_P14_RESET_Msk                  (0x01UL << PE_SRR_P14_RESET_Pos)                        /*!< PE SRR: P14_RESET Mask                  */
#define PE_SRR_P15_RESET_Pos                  31                                                      /*!< PE SRR: P15_RESET Position              */
#define PE_SRR_P15_RESET_Msk                  (0x01UL << PE_SRR_P15_RESET_Pos)                        /*!< PE SRR: P15_RESET Mask                  */


/* ================================================================================ */
/* ================           struct 'PF' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  PF_ODR  ----------------------------------- */
#define PF_ODR_P0_Pos                         0                                                       /*!< PF ODR: P0 Position                     */
#define PF_ODR_P0_Msk                         (0x01UL << PF_ODR_P0_Pos)                               /*!< PF ODR: P0 Mask                         */
#define PF_ODR_P1_Pos                         1                                                       /*!< PF ODR: P1 Position                     */
#define PF_ODR_P1_Msk                         (0x01UL << PF_ODR_P1_Pos)                               /*!< PF ODR: P1 Mask                         */
#define PF_ODR_P2_Pos                         2                                                       /*!< PF ODR: P2 Position                     */
#define PF_ODR_P2_Msk                         (0x01UL << PF_ODR_P2_Pos)                               /*!< PF ODR: P2 Mask                         */
#define PF_ODR_P3_Pos                         3                                                       /*!< PF ODR: P3 Position                     */
#define PF_ODR_P3_Msk                         (0x01UL << PF_ODR_P3_Pos)                               /*!< PF ODR: P3 Mask                         */
#define PF_ODR_P4_Pos                         4                                                       /*!< PF ODR: P4 Position                     */
#define PF_ODR_P4_Msk                         (0x01UL << PF_ODR_P4_Pos)                               /*!< PF ODR: P4 Mask                         */
#define PF_ODR_P5_Pos                         5                                                       /*!< PF ODR: P5 Position                     */
#define PF_ODR_P5_Msk                         (0x01UL << PF_ODR_P5_Pos)                               /*!< PF ODR: P5 Mask                         */
#define PF_ODR_P6_Pos                         6                                                       /*!< PF ODR: P6 Position                     */
#define PF_ODR_P6_Msk                         (0x01UL << PF_ODR_P6_Pos)                               /*!< PF ODR: P6 Mask                         */
#define PF_ODR_P7_Pos                         7                                                       /*!< PF ODR: P7 Position                     */
#define PF_ODR_P7_Msk                         (0x01UL << PF_ODR_P7_Pos)                               /*!< PF ODR: P7 Mask                         */
#define PF_ODR_P8_Pos                         8                                                       /*!< PF ODR: P8 Position                     */
#define PF_ODR_P8_Msk                         (0x01UL << PF_ODR_P8_Pos)                               /*!< PF ODR: P8 Mask                         */
#define PF_ODR_P9_Pos                         9                                                       /*!< PF ODR: P9 Position                     */
#define PF_ODR_P9_Msk                         (0x01UL << PF_ODR_P9_Pos)                               /*!< PF ODR: P9 Mask                         */
#define PF_ODR_P10_Pos                        10                                                      /*!< PF ODR: P10 Position                    */
#define PF_ODR_P10_Msk                        (0x01UL << PF_ODR_P10_Pos)                              /*!< PF ODR: P10 Mask                        */
#define PF_ODR_P11_Pos                        11                                                      /*!< PF ODR: P11 Position                    */
#define PF_ODR_P11_Msk                        (0x01UL << PF_ODR_P11_Pos)                              /*!< PF ODR: P11 Mask                        */
#define PF_ODR_P12_Pos                        12                                                      /*!< PF ODR: P12 Position                    */
#define PF_ODR_P12_Msk                        (0x01UL << PF_ODR_P12_Pos)                              /*!< PF ODR: P12 Mask                        */
#define PF_ODR_P13_Pos                        13                                                      /*!< PF ODR: P13 Position                    */
#define PF_ODR_P13_Msk                        (0x01UL << PF_ODR_P13_Pos)                              /*!< PF ODR: P13 Mask                        */
#define PF_ODR_P14_Pos                        14                                                      /*!< PF ODR: P14 Position                    */
#define PF_ODR_P14_Msk                        (0x01UL << PF_ODR_P14_Pos)                              /*!< PF ODR: P14 Mask                        */
#define PF_ODR_P15_Pos                        15                                                      /*!< PF ODR: P15 Position                    */
#define PF_ODR_P15_Msk                        (0x01UL << PF_ODR_P15_Pos)                              /*!< PF ODR: P15 Mask                        */

/* -----------------------------------  PF_IDR  ----------------------------------- */
#define PF_IDR_P0_Pos                         0                                                       /*!< PF IDR: P0 Position                     */
#define PF_IDR_P0_Msk                         (0x01UL << PF_IDR_P0_Pos)                               /*!< PF IDR: P0 Mask                         */
#define PF_IDR_P1_Pos                         1                                                       /*!< PF IDR: P1 Position                     */
#define PF_IDR_P1_Msk                         (0x01UL << PF_IDR_P1_Pos)                               /*!< PF IDR: P1 Mask                         */
#define PF_IDR_P2_Pos                         2                                                       /*!< PF IDR: P2 Position                     */
#define PF_IDR_P2_Msk                         (0x01UL << PF_IDR_P2_Pos)                               /*!< PF IDR: P2 Mask                         */
#define PF_IDR_P3_Pos                         3                                                       /*!< PF IDR: P3 Position                     */
#define PF_IDR_P3_Msk                         (0x01UL << PF_IDR_P3_Pos)                               /*!< PF IDR: P3 Mask                         */
#define PF_IDR_P4_Pos                         4                                                       /*!< PF IDR: P4 Position                     */
#define PF_IDR_P4_Msk                         (0x01UL << PF_IDR_P4_Pos)                               /*!< PF IDR: P4 Mask                         */
#define PF_IDR_P5_Pos                         5                                                       /*!< PF IDR: P5 Position                     */
#define PF_IDR_P5_Msk                         (0x01UL << PF_IDR_P5_Pos)                               /*!< PF IDR: P5 Mask                         */
#define PF_IDR_P6_Pos                         6                                                       /*!< PF IDR: P6 Position                     */
#define PF_IDR_P6_Msk                         (0x01UL << PF_IDR_P6_Pos)                               /*!< PF IDR: P6 Mask                         */
#define PF_IDR_P7_Pos                         7                                                       /*!< PF IDR: P7 Position                     */
#define PF_IDR_P7_Msk                         (0x01UL << PF_IDR_P7_Pos)                               /*!< PF IDR: P7 Mask                         */
#define PF_IDR_P8_Pos                         8                                                       /*!< PF IDR: P8 Position                     */
#define PF_IDR_P8_Msk                         (0x01UL << PF_IDR_P8_Pos)                               /*!< PF IDR: P8 Mask                         */
#define PF_IDR_P9_Pos                         9                                                       /*!< PF IDR: P9 Position                     */
#define PF_IDR_P9_Msk                         (0x01UL << PF_IDR_P9_Pos)                               /*!< PF IDR: P9 Mask                         */
#define PF_IDR_P10_Pos                        10                                                      /*!< PF IDR: P10 Position                    */
#define PF_IDR_P10_Msk                        (0x01UL << PF_IDR_P10_Pos)                              /*!< PF IDR: P10 Mask                        */
#define PF_IDR_P11_Pos                        11                                                      /*!< PF IDR: P11 Position                    */
#define PF_IDR_P11_Msk                        (0x01UL << PF_IDR_P11_Pos)                              /*!< PF IDR: P11 Mask                        */
#define PF_IDR_P12_Pos                        12                                                      /*!< PF IDR: P12 Position                    */
#define PF_IDR_P12_Msk                        (0x01UL << PF_IDR_P12_Pos)                              /*!< PF IDR: P12 Mask                        */
#define PF_IDR_P13_Pos                        13                                                      /*!< PF IDR: P13 Position                    */
#define PF_IDR_P13_Msk                        (0x01UL << PF_IDR_P13_Pos)                              /*!< PF IDR: P13 Mask                        */
#define PF_IDR_P14_Pos                        14                                                      /*!< PF IDR: P14 Position                    */
#define PF_IDR_P14_Msk                        (0x01UL << PF_IDR_P14_Pos)                              /*!< PF IDR: P14 Mask                        */
#define PF_IDR_P15_Pos                        15                                                      /*!< PF IDR: P15 Position                    */
#define PF_IDR_P15_Msk                        (0x01UL << PF_IDR_P15_Pos)                              /*!< PF IDR: P15 Mask                        */

/* -----------------------------------  PF_SRR  ----------------------------------- */
#define PF_SRR_P0_SET_Pos                     0                                                       /*!< PF SRR: P0_SET Position                 */
#define PF_SRR_P0_SET_Msk                     (0x01UL << PF_SRR_P0_SET_Pos)                           /*!< PF SRR: P0_SET Mask                     */
#define PF_SRR_P1_SET_Pos                     1                                                       /*!< PF SRR: P1_SET Position                 */
#define PF_SRR_P1_SET_Msk                     (0x01UL << PF_SRR_P1_SET_Pos)                           /*!< PF SRR: P1_SET Mask                     */
#define PF_SRR_P2_SET_Pos                     2                                                       /*!< PF SRR: P2_SET Position                 */
#define PF_SRR_P2_SET_Msk                     (0x01UL << PF_SRR_P2_SET_Pos)                           /*!< PF SRR: P2_SET Mask                     */
#define PF_SRR_P3_SET_Pos                     3                                                       /*!< PF SRR: P3_SET Position                 */
#define PF_SRR_P3_SET_Msk                     (0x01UL << PF_SRR_P3_SET_Pos)                           /*!< PF SRR: P3_SET Mask                     */
#define PF_SRR_P4_SET_Pos                     4                                                       /*!< PF SRR: P4_SET Position                 */
#define PF_SRR_P4_SET_Msk                     (0x01UL << PF_SRR_P4_SET_Pos)                           /*!< PF SRR: P4_SET Mask                     */
#define PF_SRR_P5_SET_Pos                     5                                                       /*!< PF SRR: P5_SET Position                 */
#define PF_SRR_P5_SET_Msk                     (0x01UL << PF_SRR_P5_SET_Pos)                           /*!< PF SRR: P5_SET Mask                     */
#define PF_SRR_P6_SET_Pos                     6                                                       /*!< PF SRR: P6_SET Position                 */
#define PF_SRR_P6_SET_Msk                     (0x01UL << PF_SRR_P6_SET_Pos)                           /*!< PF SRR: P6_SET Mask                     */
#define PF_SRR_P7_SET_Pos                     7                                                       /*!< PF SRR: P7_SET Position                 */
#define PF_SRR_P7_SET_Msk                     (0x01UL << PF_SRR_P7_SET_Pos)                           /*!< PF SRR: P7_SET Mask                     */
#define PF_SRR_P8_SET_Pos                     8                                                       /*!< PF SRR: P8_SET Position                 */
#define PF_SRR_P8_SET_Msk                     (0x01UL << PF_SRR_P8_SET_Pos)                           /*!< PF SRR: P8_SET Mask                     */
#define PF_SRR_P9_SET_Pos                     9                                                       /*!< PF SRR: P9_SET Position                 */
#define PF_SRR_P9_SET_Msk                     (0x01UL << PF_SRR_P9_SET_Pos)                           /*!< PF SRR: P9_SET Mask                     */
#define PF_SRR_P10_SET_Pos                    10                                                      /*!< PF SRR: P10_SET Position                */
#define PF_SRR_P10_SET_Msk                    (0x01UL << PF_SRR_P10_SET_Pos)                          /*!< PF SRR: P10_SET Mask                    */
#define PF_SRR_P11_SET_Pos                    11                                                      /*!< PF SRR: P11_SET Position                */
#define PF_SRR_P11_SET_Msk                    (0x01UL << PF_SRR_P11_SET_Pos)                          /*!< PF SRR: P11_SET Mask                    */
#define PF_SRR_P12_SET_Pos                    12                                                      /*!< PF SRR: P12_SET Position                */
#define PF_SRR_P12_SET_Msk                    (0x01UL << PF_SRR_P12_SET_Pos)                          /*!< PF SRR: P12_SET Mask                    */
#define PF_SRR_P13_SET_Pos                    13                                                      /*!< PF SRR: P13_SET Position                */
#define PF_SRR_P13_SET_Msk                    (0x01UL << PF_SRR_P13_SET_Pos)                          /*!< PF SRR: P13_SET Mask                    */
#define PF_SRR_P14_SET_Pos                    14                                                      /*!< PF SRR: P14_SET Position                */
#define PF_SRR_P14_SET_Msk                    (0x01UL << PF_SRR_P14_SET_Pos)                          /*!< PF SRR: P14_SET Mask                    */
#define PF_SRR_P15_SET_Pos                    15                                                      /*!< PF SRR: P15_SET Position                */
#define PF_SRR_P15_SET_Msk                    (0x01UL << PF_SRR_P15_SET_Pos)                          /*!< PF SRR: P15_SET Mask                    */
#define PF_SRR_P0_RESET_Pos                   16                                                      /*!< PF SRR: P0_RESET Position               */
#define PF_SRR_P0_RESET_Msk                   (0x01UL << PF_SRR_P0_RESET_Pos)                         /*!< PF SRR: P0_RESET Mask                   */
#define PF_SRR_P1_RESET_Pos                   17                                                      /*!< PF SRR: P1_RESET Position               */
#define PF_SRR_P1_RESET_Msk                   (0x01UL << PF_SRR_P1_RESET_Pos)                         /*!< PF SRR: P1_RESET Mask                   */
#define PF_SRR_P2_RESET_Pos                   18                                                      /*!< PF SRR: P2_RESET Position               */
#define PF_SRR_P2_RESET_Msk                   (0x01UL << PF_SRR_P2_RESET_Pos)                         /*!< PF SRR: P2_RESET Mask                   */
#define PF_SRR_P3_RESET_Pos                   19                                                      /*!< PF SRR: P3_RESET Position               */
#define PF_SRR_P3_RESET_Msk                   (0x01UL << PF_SRR_P3_RESET_Pos)                         /*!< PF SRR: P3_RESET Mask                   */
#define PF_SRR_P4_RESET_Pos                   20                                                      /*!< PF SRR: P4_RESET Position               */
#define PF_SRR_P4_RESET_Msk                   (0x01UL << PF_SRR_P4_RESET_Pos)                         /*!< PF SRR: P4_RESET Mask                   */
#define PF_SRR_P5_RESET_Pos                   21                                                      /*!< PF SRR: P5_RESET Position               */
#define PF_SRR_P5_RESET_Msk                   (0x01UL << PF_SRR_P5_RESET_Pos)                         /*!< PF SRR: P5_RESET Mask                   */
#define PF_SRR_P6_RESET_Pos                   22                                                      /*!< PF SRR: P6_RESET Position               */
#define PF_SRR_P6_RESET_Msk                   (0x01UL << PF_SRR_P6_RESET_Pos)                         /*!< PF SRR: P6_RESET Mask                   */
#define PF_SRR_P7_RESET_Pos                   23                                                      /*!< PF SRR: P7_RESET Position               */
#define PF_SRR_P7_RESET_Msk                   (0x01UL << PF_SRR_P7_RESET_Pos)                         /*!< PF SRR: P7_RESET Mask                   */
#define PF_SRR_P8_RESET_Pos                   24                                                      /*!< PF SRR: P8_RESET Position               */
#define PF_SRR_P8_RESET_Msk                   (0x01UL << PF_SRR_P8_RESET_Pos)                         /*!< PF SRR: P8_RESET Mask                   */
#define PF_SRR_P9_RESET_Pos                   25                                                      /*!< PF SRR: P9_RESET Position               */
#define PF_SRR_P9_RESET_Msk                   (0x01UL << PF_SRR_P9_RESET_Pos)                         /*!< PF SRR: P9_RESET Mask                   */
#define PF_SRR_P10_RESET_Pos                  26                                                      /*!< PF SRR: P10_RESET Position              */
#define PF_SRR_P10_RESET_Msk                  (0x01UL << PF_SRR_P10_RESET_Pos)                        /*!< PF SRR: P10_RESET Mask                  */
#define PF_SRR_P11_RESET_Pos                  27                                                      /*!< PF SRR: P11_RESET Position              */
#define PF_SRR_P11_RESET_Msk                  (0x01UL << PF_SRR_P11_RESET_Pos)                        /*!< PF SRR: P11_RESET Mask                  */
#define PF_SRR_P12_RESET_Pos                  28                                                      /*!< PF SRR: P12_RESET Position              */
#define PF_SRR_P12_RESET_Msk                  (0x01UL << PF_SRR_P12_RESET_Pos)                        /*!< PF SRR: P12_RESET Mask                  */
#define PF_SRR_P13_RESET_Pos                  29                                                      /*!< PF SRR: P13_RESET Position              */
#define PF_SRR_P13_RESET_Msk                  (0x01UL << PF_SRR_P13_RESET_Pos)                        /*!< PF SRR: P13_RESET Mask                  */
#define PF_SRR_P14_RESET_Pos                  30                                                      /*!< PF SRR: P14_RESET Position              */
#define PF_SRR_P14_RESET_Msk                  (0x01UL << PF_SRR_P14_RESET_Pos)                        /*!< PF SRR: P14_RESET Mask                  */
#define PF_SRR_P15_RESET_Pos                  31                                                      /*!< PF SRR: P15_RESET Position              */
#define PF_SRR_P15_RESET_Msk                  (0x01UL << PF_SRR_P15_RESET_Pos)                        /*!< PF SRR: P15_RESET Mask                  */


/* ================================================================================ */
/* ================          struct 'WDT' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  WDT_CON  ---------------------------------- */
#define WDT_CON_WPRS_Pos                      0                                                       /*!< WDT CON: WPRS Position                  */
#define WDT_CON_WPRS_Msk                      (0x07UL << WDT_CON_WPRS_Pos)                            /*!< WDT CON: WPRS Mask                      */
#define WDT_CON_WEC_Pos                       3                                                       /*!< WDT CON: WEC Position                   */
#define WDT_CON_WEC_Msk                       (0x01UL << WDT_CON_WEC_Pos)                             /*!< WDT CON: WEC Mask                       */
#define WDT_CON_WEN_Pos                       5                                                       /*!< WDT CON: WEN Position                   */
#define WDT_CON_WEN_Msk                       (0x01UL << WDT_CON_WEN_Pos)                             /*!< WDT CON: WEN Mask                       */
#define WDT_CON_WRE_Pos                       6                                                       /*!< WDT CON: WRE Position                   */
#define WDT_CON_WRE_Msk                       (0x01UL << WDT_CON_WRE_Pos)                             /*!< WDT CON: WRE Mask                       */
#define WDT_CON_WIE_Pos                       7                                                       /*!< WDT CON: WIE Position                   */
#define WDT_CON_WIE_Msk                       (0x01UL << WDT_CON_WIE_Pos)                             /*!< WDT CON: WIE Mask                       */
#define WDT_CON_WOF_Pos                       8                                                       /*!< WDT CON: WOF Position                   */
#define WDT_CON_WOF_Msk                       (0x01UL << WDT_CON_WOF_Pos)                             /*!< WDT CON: WOF Mask                       */
#define WDT_CON_WDH_Pos                       15                                                      /*!< WDT CON: WDH Position                   */
#define WDT_CON_WDH_Msk                       (0x01UL << WDT_CON_WDH_Pos)                             /*!< WDT CON: WDH Mask                       */


/* ================================================================================ */
/* ================          struct 'FRT' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  FRT_CON  ---------------------------------- */
#define FRT_CON_FEN_Pos                       0                                                       /*!< FRT CON: FEN Position                   */
#define FRT_CON_FEN_Msk                       (0x01UL << FRT_CON_FEN_Pos)                             /*!< FRT CON: FEN Mask                       */
#define FRT_CON_FAC_Pos                       1                                                       /*!< FRT CON: FAC Position                   */
#define FRT_CON_FAC_Msk                       (0x01UL << FRT_CON_FAC_Pos)                             /*!< FRT CON: FAC Mask                       */
#define FRT_CON_FOIE_Pos                      2                                                       /*!< FRT CON: FOIE Position                  */
#define FRT_CON_FOIE_Msk                      (0x01UL << FRT_CON_FOIE_Pos)                            /*!< FRT CON: FOIE Mask                      */
#define FRT_CON_FMIE_Pos                      3                                                       /*!< FRT CON: FMIE Position                  */
#define FRT_CON_FMIE_Msk                      (0x01UL << FRT_CON_FMIE_Pos)                            /*!< FRT CON: FMIE Mask                      */
#define FRT_CON_FPRS_Pos                      4                                                       /*!< FRT CON: FPRS Position                  */
#define FRT_CON_FPRS_Msk                      (0x07UL << FRT_CON_FPRS_Pos)                            /*!< FRT CON: FPRS Mask                      */
#define FRT_CON_FEC_Pos                       7                                                       /*!< FRT CON: FEC Position                   */
#define FRT_CON_FEC_Msk                       (0x01UL << FRT_CON_FEC_Pos)                             /*!< FRT CON: FEC Mask                       */
#define FRT_CON_FOF_Pos                       8                                                       /*!< FRT CON: FOF Position                   */
#define FRT_CON_FOF_Msk                       (0x01UL << FRT_CON_FOF_Pos)                             /*!< FRT CON: FOF Mask                       */
#define FRT_CON_FMF_Pos                       9                                                       /*!< FRT CON: FMF Position                   */
#define FRT_CON_FMF_Msk                       (0x01UL << FRT_CON_FMF_Pos)                             /*!< FRT CON: FMF Mask                       */


/* ================================================================================ */
/* ================           struct 'T0' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  T0_CON  ----------------------------------- */
#define T0_CON_TMODE_Pos                      0                                                       /*!< T0 CON: TMODE Position                  */
#define T0_CON_TMODE_Msk                      (0x03UL << T0_CON_TMODE_Pos)                            /*!< T0 CON: TMODE Mask                      */
#define T0_CON_CAPM_Pos                       3                                                       /*!< T0 CON: CAPM Position                   */
#define T0_CON_CAPM_Msk                       (0x01UL << T0_CON_CAPM_Pos)                             /*!< T0 CON: CAPM Mask                       */
#define T0_CON_TCS_Pos                        4                                                       /*!< T0 CON: TCS Position                    */
#define T0_CON_TCS_Msk                        (0x07UL << T0_CON_TCS_Pos)                              /*!< T0 CON: TCS Mask                        */
#define T0_CON_TSTRT_Pos                      7                                                       /*!< T0 CON: TSTRT Position                  */
#define T0_CON_TSTRT_Msk                      (0x01UL << T0_CON_TSTRT_Pos)                            /*!< T0 CON: TSTRT Mask                      */
#define T0_CON_TIE0_Pos                       8                                                       /*!< T0 CON: TIE0 Position                   */
#define T0_CON_TIE0_Msk                       (0x01UL << T0_CON_TIE0_Pos)                             /*!< T0 CON: TIE0 Mask                       */
#define T0_CON_TIE1_Pos                       9                                                       /*!< T0 CON: TIE1 Position                   */
#define T0_CON_TIE1_Msk                       (0x01UL << T0_CON_TIE1_Pos)                             /*!< T0 CON: TIE1 Mask                       */
#define T0_CON_TOVE_Pos                       10                                                      /*!< T0 CON: TOVE Position                   */
#define T0_CON_TOVE_Msk                       (0x01UL << T0_CON_TOVE_Pos)                             /*!< T0 CON: TOVE Mask                       */
#define T0_CON_TIF0_Pos                       12                                                      /*!< T0 CON: TIF0 Position                   */
#define T0_CON_TIF0_Msk                       (0x01UL << T0_CON_TIF0_Pos)                             /*!< T0 CON: TIF0 Mask                       */
#define T0_CON_TIF1_Pos                       13                                                      /*!< T0 CON: TIF1 Position                   */
#define T0_CON_TIF1_Msk                       (0x01UL << T0_CON_TIF1_Pos)                             /*!< T0 CON: TIF1 Mask                       */
#define T0_CON_TOVF_Pos                       14                                                      /*!< T0 CON: TOVF Position                   */
#define T0_CON_TOVF_Msk                       (0x01UL << T0_CON_TOVF_Pos)                             /*!< T0 CON: TOVF Mask                       */

/* -----------------------------------  T0_CMD  ----------------------------------- */
#define T0_CMD_TEN_Pos                        0                                                       /*!< T0 CMD: TEN Position                    */
#define T0_CMD_TEN_Msk                        (0x01UL << T0_CMD_TEN_Pos)                              /*!< T0 CMD: TEN Mask                        */
#define T0_CMD_TCLR_Pos                       1                                                       /*!< T0 CMD: TCLR Position                   */
#define T0_CMD_TCLR_Msk                       (0x01UL << T0_CMD_TCLR_Pos)                             /*!< T0 CMD: TCLR Mask                       */
#define T0_CMD_TOUT_Pos                       15                                                      /*!< T0 CMD: TOUT Position                   */
#define T0_CMD_TOUT_Msk                       (0x01UL << T0_CMD_TOUT_Pos)                             /*!< T0 CMD: TOUT Mask                       */

/* -----------------------------------  T0_GRA  ----------------------------------- */
#define T0_GRA_GRA_Pos                        0                                                       /*!< T0 GRA: GRA Position                    */
#define T0_GRA_GRA_Msk                        (0x0000ffffUL << T0_GRA_GRA_Pos)                        /*!< T0 GRA: GRA Mask                        */

/* -----------------------------------  T0_GRB  ----------------------------------- */
#define T0_GRB_GRB_Pos                        0                                                       /*!< T0 GRB: GRB Position                    */
#define T0_GRB_GRB_Msk                        (0x0000ffffUL << T0_GRB_GRB_Pos)                        /*!< T0 GRB: GRB Mask                        */

/* -----------------------------------  T0_PRS  ----------------------------------- */
#define T0_PRS_PRS_Pos                        0                                                       /*!< T0 PRS: PRS Position                    */
#define T0_PRS_PRS_Msk                        (0x000003ffUL << T0_PRS_PRS_Pos)                        /*!< T0 PRS: PRS Mask                        */

/* -----------------------------------  T0_CNT  ----------------------------------- */
#define T0_CNT_CNT_Pos                        0                                                       /*!< T0 CNT: CNT Position                    */
#define T0_CNT_CNT_Msk                        (0x0000ffffUL << T0_CNT_CNT_Pos)                        /*!< T0 CNT: CNT Mask                        */


/* ================================================================================ */
/* ================           struct 'T1' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  T1_CON  ----------------------------------- */
#define T1_CON_TMODE_Pos                      0                                                       /*!< T1 CON: TMODE Position                  */
#define T1_CON_TMODE_Msk                      (0x03UL << T1_CON_TMODE_Pos)                            /*!< T1 CON: TMODE Mask                      */
#define T1_CON_CAPM_Pos                       3                                                       /*!< T1 CON: CAPM Position                   */
#define T1_CON_CAPM_Msk                       (0x01UL << T1_CON_CAPM_Pos)                             /*!< T1 CON: CAPM Mask                       */
#define T1_CON_TCS_Pos                        4                                                       /*!< T1 CON: TCS Position                    */
#define T1_CON_TCS_Msk                        (0x07UL << T1_CON_TCS_Pos)                              /*!< T1 CON: TCS Mask                        */
#define T1_CON_TSTRT_Pos                      7                                                       /*!< T1 CON: TSTRT Position                  */
#define T1_CON_TSTRT_Msk                      (0x01UL << T1_CON_TSTRT_Pos)                            /*!< T1 CON: TSTRT Mask                      */
#define T1_CON_TIE0_Pos                       8                                                       /*!< T1 CON: TIE0 Position                   */
#define T1_CON_TIE0_Msk                       (0x01UL << T1_CON_TIE0_Pos)                             /*!< T1 CON: TIE0 Mask                       */
#define T1_CON_TIE1_Pos                       9                                                       /*!< T1 CON: TIE1 Position                   */
#define T1_CON_TIE1_Msk                       (0x01UL << T1_CON_TIE1_Pos)                             /*!< T1 CON: TIE1 Mask                       */
#define T1_CON_TOVE_Pos                       10                                                      /*!< T1 CON: TOVE Position                   */
#define T1_CON_TOVE_Msk                       (0x01UL << T1_CON_TOVE_Pos)                             /*!< T1 CON: TOVE Mask                       */
#define T1_CON_TIF0_Pos                       12                                                      /*!< T1 CON: TIF0 Position                   */
#define T1_CON_TIF0_Msk                       (0x01UL << T1_CON_TIF0_Pos)                             /*!< T1 CON: TIF0 Mask                       */
#define T1_CON_TIF1_Pos                       13                                                      /*!< T1 CON: TIF1 Position                   */
#define T1_CON_TIF1_Msk                       (0x01UL << T1_CON_TIF1_Pos)                             /*!< T1 CON: TIF1 Mask                       */
#define T1_CON_TOVF_Pos                       14                                                      /*!< T1 CON: TOVF Position                   */
#define T1_CON_TOVF_Msk                       (0x01UL << T1_CON_TOVF_Pos)                             /*!< T1 CON: TOVF Mask                       */

/* -----------------------------------  T1_CMD  ----------------------------------- */
#define T1_CMD_TEN_Pos                        0                                                       /*!< T1 CMD: TEN Position                    */
#define T1_CMD_TEN_Msk                        (0x01UL << T1_CMD_TEN_Pos)                              /*!< T1 CMD: TEN Mask                        */
#define T1_CMD_TCLR_Pos                       1                                                       /*!< T1 CMD: TCLR Position                   */
#define T1_CMD_TCLR_Msk                       (0x01UL << T1_CMD_TCLR_Pos)                             /*!< T1 CMD: TCLR Mask                       */
#define T1_CMD_TOUT_Pos                       15                                                      /*!< T1 CMD: TOUT Position                   */
#define T1_CMD_TOUT_Msk                       (0x01UL << T1_CMD_TOUT_Pos)                             /*!< T1 CMD: TOUT Mask                       */

/* -----------------------------------  T1_GRA  ----------------------------------- */
#define T1_GRA_GRA_Pos                        0                                                       /*!< T1 GRA: GRA Position                    */
#define T1_GRA_GRA_Msk                        (0x0000ffffUL << T1_GRA_GRA_Pos)                        /*!< T1 GRA: GRA Mask                        */

/* -----------------------------------  T1_GRB  ----------------------------------- */
#define T1_GRB_GRB_Pos                        0                                                       /*!< T1 GRB: GRB Position                    */
#define T1_GRB_GRB_Msk                        (0x0000ffffUL << T1_GRB_GRB_Pos)                        /*!< T1 GRB: GRB Mask                        */

/* -----------------------------------  T1_PRS  ----------------------------------- */
#define T1_PRS_PRS_Pos                        0                                                       /*!< T1 PRS: PRS Position                    */
#define T1_PRS_PRS_Msk                        (0x000003ffUL << T1_PRS_PRS_Pos)                        /*!< T1 PRS: PRS Mask                        */

/* -----------------------------------  T1_CNT  ----------------------------------- */
#define T1_CNT_CNT_Pos                        0                                                       /*!< T1 CNT: CNT Position                    */
#define T1_CNT_CNT_Msk                        (0x0000ffffUL << T1_CNT_CNT_Pos)                        /*!< T1 CNT: CNT Mask                        */


/* ================================================================================ */
/* ================           struct 'T2' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  T2_CON  ----------------------------------- */
#define T2_CON_TMODE_Pos                      0                                                       /*!< T2 CON: TMODE Position                  */
#define T2_CON_TMODE_Msk                      (0x03UL << T2_CON_TMODE_Pos)                            /*!< T2 CON: TMODE Mask                      */
#define T2_CON_CAPM_Pos                       3                                                       /*!< T2 CON: CAPM Position                   */
#define T2_CON_CAPM_Msk                       (0x01UL << T2_CON_CAPM_Pos)                             /*!< T2 CON: CAPM Mask                       */
#define T2_CON_TCS_Pos                        4                                                       /*!< T2 CON: TCS Position                    */
#define T2_CON_TCS_Msk                        (0x07UL << T2_CON_TCS_Pos)                              /*!< T2 CON: TCS Mask                        */
#define T2_CON_TSTRT_Pos                      7                                                       /*!< T2 CON: TSTRT Position                  */
#define T2_CON_TSTRT_Msk                      (0x01UL << T2_CON_TSTRT_Pos)                            /*!< T2 CON: TSTRT Mask                      */
#define T2_CON_TIE0_Pos                       8                                                       /*!< T2 CON: TIE0 Position                   */
#define T2_CON_TIE0_Msk                       (0x01UL << T2_CON_TIE0_Pos)                             /*!< T2 CON: TIE0 Mask                       */
#define T2_CON_TIE1_Pos                       9                                                       /*!< T2 CON: TIE1 Position                   */
#define T2_CON_TIE1_Msk                       (0x01UL << T2_CON_TIE1_Pos)                             /*!< T2 CON: TIE1 Mask                       */
#define T2_CON_TOVE_Pos                       10                                                      /*!< T2 CON: TOVE Position                   */
#define T2_CON_TOVE_Msk                       (0x01UL << T2_CON_TOVE_Pos)                             /*!< T2 CON: TOVE Mask                       */
#define T2_CON_TIF0_Pos                       12                                                      /*!< T2 CON: TIF0 Position                   */
#define T2_CON_TIF0_Msk                       (0x01UL << T2_CON_TIF0_Pos)                             /*!< T2 CON: TIF0 Mask                       */
#define T2_CON_TIF1_Pos                       13                                                      /*!< T2 CON: TIF1 Position                   */
#define T2_CON_TIF1_Msk                       (0x01UL << T2_CON_TIF1_Pos)                             /*!< T2 CON: TIF1 Mask                       */
#define T2_CON_TOVF_Pos                       14                                                      /*!< T2 CON: TOVF Position                   */
#define T2_CON_TOVF_Msk                       (0x01UL << T2_CON_TOVF_Pos)                             /*!< T2 CON: TOVF Mask                       */

/* -----------------------------------  T2_CMD  ----------------------------------- */
#define T2_CMD_TEN_Pos                        0                                                       /*!< T2 CMD: TEN Position                    */
#define T2_CMD_TEN_Msk                        (0x01UL << T2_CMD_TEN_Pos)                              /*!< T2 CMD: TEN Mask                        */
#define T2_CMD_TCLR_Pos                       1                                                       /*!< T2 CMD: TCLR Position                   */
#define T2_CMD_TCLR_Msk                       (0x01UL << T2_CMD_TCLR_Pos)                             /*!< T2 CMD: TCLR Mask                       */
#define T2_CMD_TOUT_Pos                       15                                                      /*!< T2 CMD: TOUT Position                   */
#define T2_CMD_TOUT_Msk                       (0x01UL << T2_CMD_TOUT_Pos)                             /*!< T2 CMD: TOUT Mask                       */

/* -----------------------------------  T2_GRA  ----------------------------------- */
#define T2_GRA_GRA_Pos                        0                                                       /*!< T2 GRA: GRA Position                    */
#define T2_GRA_GRA_Msk                        (0x0000ffffUL << T2_GRA_GRA_Pos)                        /*!< T2 GRA: GRA Mask                        */

/* -----------------------------------  T2_GRB  ----------------------------------- */
#define T2_GRB_GRB_Pos                        0                                                       /*!< T2 GRB: GRB Position                    */
#define T2_GRB_GRB_Msk                        (0x0000ffffUL << T2_GRB_GRB_Pos)                        /*!< T2 GRB: GRB Mask                        */

/* -----------------------------------  T2_PRS  ----------------------------------- */
#define T2_PRS_PRS_Pos                        0                                                       /*!< T2 PRS: PRS Position                    */
#define T2_PRS_PRS_Msk                        (0x000003ffUL << T2_PRS_PRS_Pos)                        /*!< T2 PRS: PRS Mask                        */

/* -----------------------------------  T2_CNT  ----------------------------------- */
#define T2_CNT_CNT_Pos                        0                                                       /*!< T2 CNT: CNT Position                    */
#define T2_CNT_CNT_Msk                        (0x0000ffffUL << T2_CNT_CNT_Pos)                        /*!< T2 CNT: CNT Mask                        */


/* ================================================================================ */
/* ================           struct 'T3' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  T3_CON  ----------------------------------- */
#define T3_CON_TMODE_Pos                      0                                                       /*!< T3 CON: TMODE Position                  */
#define T3_CON_TMODE_Msk                      (0x03UL << T3_CON_TMODE_Pos)                            /*!< T3 CON: TMODE Mask                      */
#define T3_CON_CAPM_Pos                       3                                                       /*!< T3 CON: CAPM Position                   */
#define T3_CON_CAPM_Msk                       (0x01UL << T3_CON_CAPM_Pos)                             /*!< T3 CON: CAPM Mask                       */
#define T3_CON_TCS_Pos                        4                                                       /*!< T3 CON: TCS Position                    */
#define T3_CON_TCS_Msk                        (0x07UL << T3_CON_TCS_Pos)                              /*!< T3 CON: TCS Mask                        */
#define T3_CON_TSTRT_Pos                      7                                                       /*!< T3 CON: TSTRT Position                  */
#define T3_CON_TSTRT_Msk                      (0x01UL << T3_CON_TSTRT_Pos)                            /*!< T3 CON: TSTRT Mask                      */
#define T3_CON_TIE0_Pos                       8                                                       /*!< T3 CON: TIE0 Position                   */
#define T3_CON_TIE0_Msk                       (0x01UL << T3_CON_TIE0_Pos)                             /*!< T3 CON: TIE0 Mask                       */
#define T3_CON_TIE1_Pos                       9                                                       /*!< T3 CON: TIE1 Position                   */
#define T3_CON_TIE1_Msk                       (0x01UL << T3_CON_TIE1_Pos)                             /*!< T3 CON: TIE1 Mask                       */
#define T3_CON_TOVE_Pos                       10                                                      /*!< T3 CON: TOVE Position                   */
#define T3_CON_TOVE_Msk                       (0x01UL << T3_CON_TOVE_Pos)                             /*!< T3 CON: TOVE Mask                       */
#define T3_CON_TIF0_Pos                       12                                                      /*!< T3 CON: TIF0 Position                   */
#define T3_CON_TIF0_Msk                       (0x01UL << T3_CON_TIF0_Pos)                             /*!< T3 CON: TIF0 Mask                       */
#define T3_CON_TIF1_Pos                       13                                                      /*!< T3 CON: TIF1 Position                   */
#define T3_CON_TIF1_Msk                       (0x01UL << T3_CON_TIF1_Pos)                             /*!< T3 CON: TIF1 Mask                       */
#define T3_CON_TOVF_Pos                       14                                                      /*!< T3 CON: TOVF Position                   */
#define T3_CON_TOVF_Msk                       (0x01UL << T3_CON_TOVF_Pos)                             /*!< T3 CON: TOVF Mask                       */

/* -----------------------------------  T3_CMD  ----------------------------------- */
#define T3_CMD_TEN_Pos                        0                                                       /*!< T3 CMD: TEN Position                    */
#define T3_CMD_TEN_Msk                        (0x01UL << T3_CMD_TEN_Pos)                              /*!< T3 CMD: TEN Mask                        */
#define T3_CMD_TCLR_Pos                       1                                                       /*!< T3 CMD: TCLR Position                   */
#define T3_CMD_TCLR_Msk                       (0x01UL << T3_CMD_TCLR_Pos)                             /*!< T3 CMD: TCLR Mask                       */
#define T3_CMD_TOUT_Pos                       15                                                      /*!< T3 CMD: TOUT Position                   */
#define T3_CMD_TOUT_Msk                       (0x01UL << T3_CMD_TOUT_Pos)                             /*!< T3 CMD: TOUT Mask                       */

/* -----------------------------------  T3_GRA  ----------------------------------- */
#define T3_GRA_GRA_Pos                        0                                                       /*!< T3 GRA: GRA Position                    */
#define T3_GRA_GRA_Msk                        (0x0000ffffUL << T3_GRA_GRA_Pos)                        /*!< T3 GRA: GRA Mask                        */

/* -----------------------------------  T3_GRB  ----------------------------------- */
#define T3_GRB_GRB_Pos                        0                                                       /*!< T3 GRB: GRB Position                    */
#define T3_GRB_GRB_Msk                        (0x0000ffffUL << T3_GRB_GRB_Pos)                        /*!< T3 GRB: GRB Mask                        */

/* -----------------------------------  T3_PRS  ----------------------------------- */
#define T3_PRS_PRS_Pos                        0                                                       /*!< T3 PRS: PRS Position                    */
#define T3_PRS_PRS_Msk                        (0x000003ffUL << T3_PRS_PRS_Pos)                        /*!< T3 PRS: PRS Mask                        */

/* -----------------------------------  T3_CNT  ----------------------------------- */
#define T3_CNT_CNT_Pos                        0                                                       /*!< T3 CNT: CNT Position                    */
#define T3_CNT_CNT_Msk                        (0x0000ffffUL << T3_CNT_CNT_Pos)                        /*!< T3 CNT: CNT Mask                        */


/* ================================================================================ */
/* ================           struct 'T4' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  T4_CON  ----------------------------------- */
#define T4_CON_TMODE_Pos                      0                                                       /*!< T4 CON: TMODE Position                  */
#define T4_CON_TMODE_Msk                      (0x03UL << T4_CON_TMODE_Pos)                            /*!< T4 CON: TMODE Mask                      */
#define T4_CON_CAPM_Pos                       3                                                       /*!< T4 CON: CAPM Position                   */
#define T4_CON_CAPM_Msk                       (0x01UL << T4_CON_CAPM_Pos)                             /*!< T4 CON: CAPM Mask                       */
#define T4_CON_TCS_Pos                        4                                                       /*!< T4 CON: TCS Position                    */
#define T4_CON_TCS_Msk                        (0x07UL << T4_CON_TCS_Pos)                              /*!< T4 CON: TCS Mask                        */
#define T4_CON_TSTRT_Pos                      7                                                       /*!< T4 CON: TSTRT Position                  */
#define T4_CON_TSTRT_Msk                      (0x01UL << T4_CON_TSTRT_Pos)                            /*!< T4 CON: TSTRT Mask                      */
#define T4_CON_TIE0_Pos                       8                                                       /*!< T4 CON: TIE0 Position                   */
#define T4_CON_TIE0_Msk                       (0x01UL << T4_CON_TIE0_Pos)                             /*!< T4 CON: TIE0 Mask                       */
#define T4_CON_TIE1_Pos                       9                                                       /*!< T4 CON: TIE1 Position                   */
#define T4_CON_TIE1_Msk                       (0x01UL << T4_CON_TIE1_Pos)                             /*!< T4 CON: TIE1 Mask                       */
#define T4_CON_TOVE_Pos                       10                                                      /*!< T4 CON: TOVE Position                   */
#define T4_CON_TOVE_Msk                       (0x01UL << T4_CON_TOVE_Pos)                             /*!< T4 CON: TOVE Mask                       */
#define T4_CON_TIF0_Pos                       12                                                      /*!< T4 CON: TIF0 Position                   */
#define T4_CON_TIF0_Msk                       (0x01UL << T4_CON_TIF0_Pos)                             /*!< T4 CON: TIF0 Mask                       */
#define T4_CON_TIF1_Pos                       13                                                      /*!< T4 CON: TIF1 Position                   */
#define T4_CON_TIF1_Msk                       (0x01UL << T4_CON_TIF1_Pos)                             /*!< T4 CON: TIF1 Mask                       */
#define T4_CON_TOVF_Pos                       14                                                      /*!< T4 CON: TOVF Position                   */
#define T4_CON_TOVF_Msk                       (0x01UL << T4_CON_TOVF_Pos)                             /*!< T4 CON: TOVF Mask                       */

/* -----------------------------------  T4_CMD  ----------------------------------- */
#define T4_CMD_TEN_Pos                        0                                                       /*!< T4 CMD: TEN Position                    */
#define T4_CMD_TEN_Msk                        (0x01UL << T4_CMD_TEN_Pos)                              /*!< T4 CMD: TEN Mask                        */
#define T4_CMD_TCLR_Pos                       1                                                       /*!< T4 CMD: TCLR Position                   */
#define T4_CMD_TCLR_Msk                       (0x01UL << T4_CMD_TCLR_Pos)                             /*!< T4 CMD: TCLR Mask                       */
#define T4_CMD_TOUT_Pos                       15                                                      /*!< T4 CMD: TOUT Position                   */
#define T4_CMD_TOUT_Msk                       (0x01UL << T4_CMD_TOUT_Pos)                             /*!< T4 CMD: TOUT Mask                       */

/* -----------------------------------  T4_GRA  ----------------------------------- */
#define T4_GRA_GRA_Pos                        0                                                       /*!< T4 GRA: GRA Position                    */
#define T4_GRA_GRA_Msk                        (0x0000ffffUL << T4_GRA_GRA_Pos)                        /*!< T4 GRA: GRA Mask                        */

/* -----------------------------------  T4_GRB  ----------------------------------- */
#define T4_GRB_GRB_Pos                        0                                                       /*!< T4 GRB: GRB Position                    */
#define T4_GRB_GRB_Msk                        (0x0000ffffUL << T4_GRB_GRB_Pos)                        /*!< T4 GRB: GRB Mask                        */

/* -----------------------------------  T4_PRS  ----------------------------------- */
#define T4_PRS_PRS_Pos                        0                                                       /*!< T4 PRS: PRS Position                    */
#define T4_PRS_PRS_Msk                        (0x000003ffUL << T4_PRS_PRS_Pos)                        /*!< T4 PRS: PRS Mask                        */

/* -----------------------------------  T4_CNT  ----------------------------------- */
#define T4_CNT_CNT_Pos                        0                                                       /*!< T4 CNT: CNT Position                    */
#define T4_CNT_CNT_Msk                        (0x0000ffffUL << T4_CNT_CNT_Pos)                        /*!< T4 CNT: CNT Mask                        */


/* ================================================================================ */
/* ================           struct 'T5' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  T5_CON  ----------------------------------- */
#define T5_CON_TMODE_Pos                      0                                                       /*!< T5 CON: TMODE Position                  */
#define T5_CON_TMODE_Msk                      (0x03UL << T5_CON_TMODE_Pos)                            /*!< T5 CON: TMODE Mask                      */
#define T5_CON_CAPM_Pos                       3                                                       /*!< T5 CON: CAPM Position                   */
#define T5_CON_CAPM_Msk                       (0x01UL << T5_CON_CAPM_Pos)                             /*!< T5 CON: CAPM Mask                       */
#define T5_CON_TCS_Pos                        4                                                       /*!< T5 CON: TCS Position                    */
#define T5_CON_TCS_Msk                        (0x07UL << T5_CON_TCS_Pos)                              /*!< T5 CON: TCS Mask                        */
#define T5_CON_TSTRT_Pos                      7                                                       /*!< T5 CON: TSTRT Position                  */
#define T5_CON_TSTRT_Msk                      (0x01UL << T5_CON_TSTRT_Pos)                            /*!< T5 CON: TSTRT Mask                      */
#define T5_CON_TIE0_Pos                       8                                                       /*!< T5 CON: TIE0 Position                   */
#define T5_CON_TIE0_Msk                       (0x01UL << T5_CON_TIE0_Pos)                             /*!< T5 CON: TIE0 Mask                       */
#define T5_CON_TIE1_Pos                       9                                                       /*!< T5 CON: TIE1 Position                   */
#define T5_CON_TIE1_Msk                       (0x01UL << T5_CON_TIE1_Pos)                             /*!< T5 CON: TIE1 Mask                       */
#define T5_CON_TOVE_Pos                       10                                                      /*!< T5 CON: TOVE Position                   */
#define T5_CON_TOVE_Msk                       (0x01UL << T5_CON_TOVE_Pos)                             /*!< T5 CON: TOVE Mask                       */
#define T5_CON_TIF0_Pos                       12                                                      /*!< T5 CON: TIF0 Position                   */
#define T5_CON_TIF0_Msk                       (0x01UL << T5_CON_TIF0_Pos)                             /*!< T5 CON: TIF0 Mask                       */
#define T5_CON_TIF1_Pos                       13                                                      /*!< T5 CON: TIF1 Position                   */
#define T5_CON_TIF1_Msk                       (0x01UL << T5_CON_TIF1_Pos)                             /*!< T5 CON: TIF1 Mask                       */
#define T5_CON_TOVF_Pos                       14                                                      /*!< T5 CON: TOVF Position                   */
#define T5_CON_TOVF_Msk                       (0x01UL << T5_CON_TOVF_Pos)                             /*!< T5 CON: TOVF Mask                       */

/* -----------------------------------  T5_CMD  ----------------------------------- */
#define T5_CMD_TEN_Pos                        0                                                       /*!< T5 CMD: TEN Position                    */
#define T5_CMD_TEN_Msk                        (0x01UL << T5_CMD_TEN_Pos)                              /*!< T5 CMD: TEN Mask                        */
#define T5_CMD_TCLR_Pos                       1                                                       /*!< T5 CMD: TCLR Position                   */
#define T5_CMD_TCLR_Msk                       (0x01UL << T5_CMD_TCLR_Pos)                             /*!< T5 CMD: TCLR Mask                       */
#define T5_CMD_TOUT_Pos                       15                                                      /*!< T5 CMD: TOUT Position                   */
#define T5_CMD_TOUT_Msk                       (0x01UL << T5_CMD_TOUT_Pos)                             /*!< T5 CMD: TOUT Mask                       */

/* -----------------------------------  T5_GRA  ----------------------------------- */
#define T5_GRA_GRA_Pos                        0                                                       /*!< T5 GRA: GRA Position                    */
#define T5_GRA_GRA_Msk                        (0x0000ffffUL << T5_GRA_GRA_Pos)                        /*!< T5 GRA: GRA Mask                        */

/* -----------------------------------  T5_GRB  ----------------------------------- */
#define T5_GRB_GRB_Pos                        0                                                       /*!< T5 GRB: GRB Position                    */
#define T5_GRB_GRB_Msk                        (0x0000ffffUL << T5_GRB_GRB_Pos)                        /*!< T5 GRB: GRB Mask                        */

/* -----------------------------------  T5_PRS  ----------------------------------- */
#define T5_PRS_PRS_Pos                        0                                                       /*!< T5 PRS: PRS Position                    */
#define T5_PRS_PRS_Msk                        (0x000003ffUL << T5_PRS_PRS_Pos)                        /*!< T5 PRS: PRS Mask                        */

/* -----------------------------------  T5_CNT  ----------------------------------- */
#define T5_CNT_CNT_Pos                        0                                                       /*!< T5 CNT: CNT Position                    */
#define T5_CNT_CNT_Msk                        (0x0000ffffUL << T5_CNT_CNT_Pos)                        /*!< T5 CNT: CNT Mask                        */


/* ================================================================================ */
/* ================           struct 'T6' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  T6_CON  ----------------------------------- */
#define T6_CON_TMODE_Pos                      0                                                       /*!< T6 CON: TMODE Position                  */
#define T6_CON_TMODE_Msk                      (0x03UL << T6_CON_TMODE_Pos)                            /*!< T6 CON: TMODE Mask                      */
#define T6_CON_CAPM_Pos                       3                                                       /*!< T6 CON: CAPM Position                   */
#define T6_CON_CAPM_Msk                       (0x01UL << T6_CON_CAPM_Pos)                             /*!< T6 CON: CAPM Mask                       */
#define T6_CON_TCS_Pos                        4                                                       /*!< T6 CON: TCS Position                    */
#define T6_CON_TCS_Msk                        (0x07UL << T6_CON_TCS_Pos)                              /*!< T6 CON: TCS Mask                        */
#define T6_CON_TSTRT_Pos                      7                                                       /*!< T6 CON: TSTRT Position                  */
#define T6_CON_TSTRT_Msk                      (0x01UL << T6_CON_TSTRT_Pos)                            /*!< T6 CON: TSTRT Mask                      */
#define T6_CON_TIE0_Pos                       8                                                       /*!< T6 CON: TIE0 Position                   */
#define T6_CON_TIE0_Msk                       (0x01UL << T6_CON_TIE0_Pos)                             /*!< T6 CON: TIE0 Mask                       */
#define T6_CON_TIE1_Pos                       9                                                       /*!< T6 CON: TIE1 Position                   */
#define T6_CON_TIE1_Msk                       (0x01UL << T6_CON_TIE1_Pos)                             /*!< T6 CON: TIE1 Mask                       */
#define T6_CON_TOVE_Pos                       10                                                      /*!< T6 CON: TOVE Position                   */
#define T6_CON_TOVE_Msk                       (0x01UL << T6_CON_TOVE_Pos)                             /*!< T6 CON: TOVE Mask                       */
#define T6_CON_TIF0_Pos                       12                                                      /*!< T6 CON: TIF0 Position                   */
#define T6_CON_TIF0_Msk                       (0x01UL << T6_CON_TIF0_Pos)                             /*!< T6 CON: TIF0 Mask                       */
#define T6_CON_TIF1_Pos                       13                                                      /*!< T6 CON: TIF1 Position                   */
#define T6_CON_TIF1_Msk                       (0x01UL << T6_CON_TIF1_Pos)                             /*!< T6 CON: TIF1 Mask                       */
#define T6_CON_TOVF_Pos                       14                                                      /*!< T6 CON: TOVF Position                   */
#define T6_CON_TOVF_Msk                       (0x01UL << T6_CON_TOVF_Pos)                             /*!< T6 CON: TOVF Mask                       */

/* -----------------------------------  T6_CMD  ----------------------------------- */
#define T6_CMD_TEN_Pos                        0                                                       /*!< T6 CMD: TEN Position                    */
#define T6_CMD_TEN_Msk                        (0x01UL << T6_CMD_TEN_Pos)                              /*!< T6 CMD: TEN Mask                        */
#define T6_CMD_TCLR_Pos                       1                                                       /*!< T6 CMD: TCLR Position                   */
#define T6_CMD_TCLR_Msk                       (0x01UL << T6_CMD_TCLR_Pos)                             /*!< T6 CMD: TCLR Mask                       */
#define T6_CMD_TOUT_Pos                       15                                                      /*!< T6 CMD: TOUT Position                   */
#define T6_CMD_TOUT_Msk                       (0x01UL << T6_CMD_TOUT_Pos)                             /*!< T6 CMD: TOUT Mask                       */

/* -----------------------------------  T6_GRA  ----------------------------------- */
#define T6_GRA_GRA_Pos                        0                                                       /*!< T6 GRA: GRA Position                    */
#define T6_GRA_GRA_Msk                        (0x0000ffffUL << T6_GRA_GRA_Pos)                        /*!< T6 GRA: GRA Mask                        */

/* -----------------------------------  T6_GRB  ----------------------------------- */
#define T6_GRB_GRB_Pos                        0                                                       /*!< T6 GRB: GRB Position                    */
#define T6_GRB_GRB_Msk                        (0x0000ffffUL << T6_GRB_GRB_Pos)                        /*!< T6 GRB: GRB Mask                        */

/* -----------------------------------  T6_PRS  ----------------------------------- */
#define T6_PRS_PRS_Pos                        0                                                       /*!< T6 PRS: PRS Position                    */
#define T6_PRS_PRS_Msk                        (0x000003ffUL << T6_PRS_PRS_Pos)                        /*!< T6 PRS: PRS Mask                        */

/* -----------------------------------  T6_CNT  ----------------------------------- */
#define T6_CNT_CNT_Pos                        0                                                       /*!< T6 CNT: CNT Position                    */
#define T6_CNT_CNT_Msk                        (0x0000ffffUL << T6_CNT_CNT_Pos)                        /*!< T6 CNT: CNT Mask                        */


/* ================================================================================ */
/* ================           struct 'T7' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  T7_CON  ----------------------------------- */
#define T7_CON_TMODE_Pos                      0                                                       /*!< T7 CON: TMODE Position                  */
#define T7_CON_TMODE_Msk                      (0x03UL << T7_CON_TMODE_Pos)                            /*!< T7 CON: TMODE Mask                      */
#define T7_CON_CAPM_Pos                       3                                                       /*!< T7 CON: CAPM Position                   */
#define T7_CON_CAPM_Msk                       (0x01UL << T7_CON_CAPM_Pos)                             /*!< T7 CON: CAPM Mask                       */
#define T7_CON_TCS_Pos                        4                                                       /*!< T7 CON: TCS Position                    */
#define T7_CON_TCS_Msk                        (0x07UL << T7_CON_TCS_Pos)                              /*!< T7 CON: TCS Mask                        */
#define T7_CON_TSTRT_Pos                      7                                                       /*!< T7 CON: TSTRT Position                  */
#define T7_CON_TSTRT_Msk                      (0x01UL << T7_CON_TSTRT_Pos)                            /*!< T7 CON: TSTRT Mask                      */
#define T7_CON_TIE0_Pos                       8                                                       /*!< T7 CON: TIE0 Position                   */
#define T7_CON_TIE0_Msk                       (0x01UL << T7_CON_TIE0_Pos)                             /*!< T7 CON: TIE0 Mask                       */
#define T7_CON_TIE1_Pos                       9                                                       /*!< T7 CON: TIE1 Position                   */
#define T7_CON_TIE1_Msk                       (0x01UL << T7_CON_TIE1_Pos)                             /*!< T7 CON: TIE1 Mask                       */
#define T7_CON_TOVE_Pos                       10                                                      /*!< T7 CON: TOVE Position                   */
#define T7_CON_TOVE_Msk                       (0x01UL << T7_CON_TOVE_Pos)                             /*!< T7 CON: TOVE Mask                       */
#define T7_CON_TIF0_Pos                       12                                                      /*!< T7 CON: TIF0 Position                   */
#define T7_CON_TIF0_Msk                       (0x01UL << T7_CON_TIF0_Pos)                             /*!< T7 CON: TIF0 Mask                       */
#define T7_CON_TIF1_Pos                       13                                                      /*!< T7 CON: TIF1 Position                   */
#define T7_CON_TIF1_Msk                       (0x01UL << T7_CON_TIF1_Pos)                             /*!< T7 CON: TIF1 Mask                       */
#define T7_CON_TOVF_Pos                       14                                                      /*!< T7 CON: TOVF Position                   */
#define T7_CON_TOVF_Msk                       (0x01UL << T7_CON_TOVF_Pos)                             /*!< T7 CON: TOVF Mask                       */

/* -----------------------------------  T7_CMD  ----------------------------------- */
#define T7_CMD_TEN_Pos                        0                                                       /*!< T7 CMD: TEN Position                    */
#define T7_CMD_TEN_Msk                        (0x01UL << T7_CMD_TEN_Pos)                              /*!< T7 CMD: TEN Mask                        */
#define T7_CMD_TCLR_Pos                       1                                                       /*!< T7 CMD: TCLR Position                   */
#define T7_CMD_TCLR_Msk                       (0x01UL << T7_CMD_TCLR_Pos)                             /*!< T7 CMD: TCLR Mask                       */
#define T7_CMD_TOUT_Pos                       15                                                      /*!< T7 CMD: TOUT Position                   */
#define T7_CMD_TOUT_Msk                       (0x01UL << T7_CMD_TOUT_Pos)                             /*!< T7 CMD: TOUT Mask                       */

/* -----------------------------------  T7_GRA  ----------------------------------- */
#define T7_GRA_GRA_Pos                        0                                                       /*!< T7 GRA: GRA Position                    */
#define T7_GRA_GRA_Msk                        (0x0000ffffUL << T7_GRA_GRA_Pos)                        /*!< T7 GRA: GRA Mask                        */

/* -----------------------------------  T7_GRB  ----------------------------------- */
#define T7_GRB_GRB_Pos                        0                                                       /*!< T7 GRB: GRB Position                    */
#define T7_GRB_GRB_Msk                        (0x0000ffffUL << T7_GRB_GRB_Pos)                        /*!< T7 GRB: GRB Mask                        */

/* -----------------------------------  T7_PRS  ----------------------------------- */
#define T7_PRS_PRS_Pos                        0                                                       /*!< T7 PRS: PRS Position                    */
#define T7_PRS_PRS_Msk                        (0x000003ffUL << T7_PRS_PRS_Pos)                        /*!< T7 PRS: PRS Mask                        */

/* -----------------------------------  T7_CNT  ----------------------------------- */
#define T7_CNT_CNT_Pos                        0                                                       /*!< T7 CNT: CNT Position                    */
#define T7_CNT_CNT_Msk                        (0x0000ffffUL << T7_CNT_CNT_Pos)                        /*!< T7 CNT: CNT Mask                        */


/* ================================================================================ */
/* ================           struct 'T8' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  T8_CON  ----------------------------------- */
#define T8_CON_TMODE_Pos                      0                                                       /*!< T8 CON: TMODE Position                  */
#define T8_CON_TMODE_Msk                      (0x03UL << T8_CON_TMODE_Pos)                            /*!< T8 CON: TMODE Mask                      */
#define T8_CON_CAPM_Pos                       3                                                       /*!< T8 CON: CAPM Position                   */
#define T8_CON_CAPM_Msk                       (0x01UL << T8_CON_CAPM_Pos)                             /*!< T8 CON: CAPM Mask                       */
#define T8_CON_TCS_Pos                        4                                                       /*!< T8 CON: TCS Position                    */
#define T8_CON_TCS_Msk                        (0x07UL << T8_CON_TCS_Pos)                              /*!< T8 CON: TCS Mask                        */
#define T8_CON_TSTRT_Pos                      7                                                       /*!< T8 CON: TSTRT Position                  */
#define T8_CON_TSTRT_Msk                      (0x01UL << T8_CON_TSTRT_Pos)                            /*!< T8 CON: TSTRT Mask                      */
#define T8_CON_TIE0_Pos                       8                                                       /*!< T8 CON: TIE0 Position                   */
#define T8_CON_TIE0_Msk                       (0x01UL << T8_CON_TIE0_Pos)                             /*!< T8 CON: TIE0 Mask                       */
#define T8_CON_TIE1_Pos                       9                                                       /*!< T8 CON: TIE1 Position                   */
#define T8_CON_TIE1_Msk                       (0x01UL << T8_CON_TIE1_Pos)                             /*!< T8 CON: TIE1 Mask                       */
#define T8_CON_TOVE_Pos                       10                                                      /*!< T8 CON: TOVE Position                   */
#define T8_CON_TOVE_Msk                       (0x01UL << T8_CON_TOVE_Pos)                             /*!< T8 CON: TOVE Mask                       */
#define T8_CON_TIF0_Pos                       12                                                      /*!< T8 CON: TIF0 Position                   */
#define T8_CON_TIF0_Msk                       (0x01UL << T8_CON_TIF0_Pos)                             /*!< T8 CON: TIF0 Mask                       */
#define T8_CON_TIF1_Pos                       13                                                      /*!< T8 CON: TIF1 Position                   */
#define T8_CON_TIF1_Msk                       (0x01UL << T8_CON_TIF1_Pos)                             /*!< T8 CON: TIF1 Mask                       */
#define T8_CON_TOVF_Pos                       14                                                      /*!< T8 CON: TOVF Position                   */
#define T8_CON_TOVF_Msk                       (0x01UL << T8_CON_TOVF_Pos)                             /*!< T8 CON: TOVF Mask                       */

/* -----------------------------------  T8_CMD  ----------------------------------- */
#define T8_CMD_TEN_Pos                        0                                                       /*!< T8 CMD: TEN Position                    */
#define T8_CMD_TEN_Msk                        (0x01UL << T8_CMD_TEN_Pos)                              /*!< T8 CMD: TEN Mask                        */
#define T8_CMD_TCLR_Pos                       1                                                       /*!< T8 CMD: TCLR Position                   */
#define T8_CMD_TCLR_Msk                       (0x01UL << T8_CMD_TCLR_Pos)                             /*!< T8 CMD: TCLR Mask                       */
#define T8_CMD_TOUT_Pos                       15                                                      /*!< T8 CMD: TOUT Position                   */
#define T8_CMD_TOUT_Msk                       (0x01UL << T8_CMD_TOUT_Pos)                             /*!< T8 CMD: TOUT Mask                       */

/* -----------------------------------  T8_GRA  ----------------------------------- */
#define T8_GRA_GRA_Pos                        0                                                       /*!< T8 GRA: GRA Position                    */
#define T8_GRA_GRA_Msk                        (0x0000ffffUL << T8_GRA_GRA_Pos)                        /*!< T8 GRA: GRA Mask                        */

/* -----------------------------------  T8_GRB  ----------------------------------- */
#define T8_GRB_GRB_Pos                        0                                                       /*!< T8 GRB: GRB Position                    */
#define T8_GRB_GRB_Msk                        (0x0000ffffUL << T8_GRB_GRB_Pos)                        /*!< T8 GRB: GRB Mask                        */

/* -----------------------------------  T8_PRS  ----------------------------------- */
#define T8_PRS_PRS_Pos                        0                                                       /*!< T8 PRS: PRS Position                    */
#define T8_PRS_PRS_Msk                        (0x000003ffUL << T8_PRS_PRS_Pos)                        /*!< T8 PRS: PRS Mask                        */

/* -----------------------------------  T8_CNT  ----------------------------------- */
#define T8_CNT_CNT_Pos                        0                                                       /*!< T8 CNT: CNT Position                    */
#define T8_CNT_CNT_Msk                        (0x0000ffffUL << T8_CNT_CNT_Pos)                        /*!< T8 CNT: CNT Mask                        */


/* ================================================================================ */
/* ================           struct 'T9' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  T9_CON  ----------------------------------- */
#define T9_CON_TMODE_Pos                      0                                                       /*!< T9 CON: TMODE Position                  */
#define T9_CON_TMODE_Msk                      (0x03UL << T9_CON_TMODE_Pos)                            /*!< T9 CON: TMODE Mask                      */
#define T9_CON_CAPM_Pos                       3                                                       /*!< T9 CON: CAPM Position                   */
#define T9_CON_CAPM_Msk                       (0x01UL << T9_CON_CAPM_Pos)                             /*!< T9 CON: CAPM Mask                       */
#define T9_CON_TCS_Pos                        4                                                       /*!< T9 CON: TCS Position                    */
#define T9_CON_TCS_Msk                        (0x07UL << T9_CON_TCS_Pos)                              /*!< T9 CON: TCS Mask                        */
#define T9_CON_TSTRT_Pos                      7                                                       /*!< T9 CON: TSTRT Position                  */
#define T9_CON_TSTRT_Msk                      (0x01UL << T9_CON_TSTRT_Pos)                            /*!< T9 CON: TSTRT Mask                      */
#define T9_CON_TIE0_Pos                       8                                                       /*!< T9 CON: TIE0 Position                   */
#define T9_CON_TIE0_Msk                       (0x01UL << T9_CON_TIE0_Pos)                             /*!< T9 CON: TIE0 Mask                       */
#define T9_CON_TIE1_Pos                       9                                                       /*!< T9 CON: TIE1 Position                   */
#define T9_CON_TIE1_Msk                       (0x01UL << T9_CON_TIE1_Pos)                             /*!< T9 CON: TIE1 Mask                       */
#define T9_CON_TOVE_Pos                       10                                                      /*!< T9 CON: TOVE Position                   */
#define T9_CON_TOVE_Msk                       (0x01UL << T9_CON_TOVE_Pos)                             /*!< T9 CON: TOVE Mask                       */
#define T9_CON_TIF0_Pos                       12                                                      /*!< T9 CON: TIF0 Position                   */
#define T9_CON_TIF0_Msk                       (0x01UL << T9_CON_TIF0_Pos)                             /*!< T9 CON: TIF0 Mask                       */
#define T9_CON_TIF1_Pos                       13                                                      /*!< T9 CON: TIF1 Position                   */
#define T9_CON_TIF1_Msk                       (0x01UL << T9_CON_TIF1_Pos)                             /*!< T9 CON: TIF1 Mask                       */
#define T9_CON_TOVF_Pos                       14                                                      /*!< T9 CON: TOVF Position                   */
#define T9_CON_TOVF_Msk                       (0x01UL << T9_CON_TOVF_Pos)                             /*!< T9 CON: TOVF Mask                       */

/* -----------------------------------  T9_CMD  ----------------------------------- */
#define T9_CMD_TEN_Pos                        0                                                       /*!< T9 CMD: TEN Position                    */
#define T9_CMD_TEN_Msk                        (0x01UL << T9_CMD_TEN_Pos)                              /*!< T9 CMD: TEN Mask                        */
#define T9_CMD_TCLR_Pos                       1                                                       /*!< T9 CMD: TCLR Position                   */
#define T9_CMD_TCLR_Msk                       (0x01UL << T9_CMD_TCLR_Pos)                             /*!< T9 CMD: TCLR Mask                       */
#define T9_CMD_TOUT_Pos                       15                                                      /*!< T9 CMD: TOUT Position                   */
#define T9_CMD_TOUT_Msk                       (0x01UL << T9_CMD_TOUT_Pos)                             /*!< T9 CMD: TOUT Mask                       */

/* -----------------------------------  T9_GRA  ----------------------------------- */
#define T9_GRA_GRA_Pos                        0                                                       /*!< T9 GRA: GRA Position                    */
#define T9_GRA_GRA_Msk                        (0x0000ffffUL << T9_GRA_GRA_Pos)                        /*!< T9 GRA: GRA Mask                        */

/* -----------------------------------  T9_GRB  ----------------------------------- */
#define T9_GRB_GRB_Pos                        0                                                       /*!< T9 GRB: GRB Position                    */
#define T9_GRB_GRB_Msk                        (0x0000ffffUL << T9_GRB_GRB_Pos)                        /*!< T9 GRB: GRB Mask                        */

/* -----------------------------------  T9_PRS  ----------------------------------- */
#define T9_PRS_PRS_Pos                        0                                                       /*!< T9 PRS: PRS Position                    */
#define T9_PRS_PRS_Msk                        (0x000003ffUL << T9_PRS_PRS_Pos)                        /*!< T9 PRS: PRS Mask                        */

/* -----------------------------------  T9_CNT  ----------------------------------- */
#define T9_CNT_CNT_Pos                        0                                                       /*!< T9 CNT: CNT Position                    */
#define T9_CNT_CNT_Msk                        (0x0000ffffUL << T9_CNT_CNT_Pos)                        /*!< T9 CNT: CNT Mask                        */


/* ================================================================================ */
/* ================          struct 'PWM0' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  PWM0_CTRL  --------------------------------- */
#define PWM0_CTRL_STRT_Pos                    0                                                       /*!< PWM0 CTRL: STRT Position                */
#define PWM0_CTRL_STRT_Msk                    (0x01UL << PWM0_CTRL_STRT_Pos)                          /*!< PWM0 CTRL: STRT Mask                    */
#define PWM0_CTRL_SYNC_Pos                    1                                                       /*!< PWM0 CTRL: SYNC Position                */
#define PWM0_CTRL_SYNC_Msk                    (0x01UL << PWM0_CTRL_SYNC_Pos)                          /*!< PWM0 CTRL: SYNC Mask                    */
#define PWM0_CTRL_INVA_Pos                    3                                                       /*!< PWM0 CTRL: INVA Position                */
#define PWM0_CTRL_INVA_Msk                    (0x01UL << PWM0_CTRL_INVA_Pos)                          /*!< PWM0 CTRL: INVA Mask                    */
#define PWM0_CTRL_CKSEL_Pos                   5                                                       /*!< PWM0 CTRL: CKSEL Position               */
#define PWM0_CTRL_CKSEL_Msk                   (0x07UL << PWM0_CTRL_CKSEL_Pos)                         /*!< PWM0 CTRL: CKSEL Mask                   */
#define PWM0_CTRL_PRIE_Pos                    8                                                       /*!< PWM0 CTRL: PRIE Position                */
#define PWM0_CTRL_PRIE_Msk                    (0x01UL << PWM0_CTRL_PRIE_Pos)                          /*!< PWM0 CTRL: PRIE Mask                    */
#define PWM0_CTRL_PRF_Pos                     12                                                      /*!< PWM0 CTRL: PRF Position                 */
#define PWM0_CTRL_PRF_Msk                     (0x01UL << PWM0_CTRL_PRF_Pos)                           /*!< PWM0 CTRL: PRF Mask                     */

/* ----------------------------------  PWM0_CNT  ---------------------------------- */
#define PWM0_CNT_CNT_Pos                      0                                                       /*!< PWM0 CNT: CNT Position                  */
#define PWM0_CNT_CNT_Msk                      (0x0000ffffUL << PWM0_CNT_CNT_Pos)                      /*!< PWM0 CNT: CNT Mask                      */

/* ----------------------------------  PWM0_PER  ---------------------------------- */
#define PWM0_PER_PERIOD_Pos                   0                                                       /*!< PWM0 PER: PERIOD Position               */
#define PWM0_PER_PERIOD_Msk                   (0x0000ffffUL << PWM0_PER_PERIOD_Pos)                   /*!< PWM0 PER: PERIOD Mask                   */

/* ----------------------------------  PWM0_CMP  ---------------------------------- */
#define PWM0_CMP_CMP_Pos                      0                                                       /*!< PWM0 CMP: CMP Position                  */
#define PWM0_CMP_CMP_Msk                      (0x0000ffffUL << PWM0_CMP_CMP_Pos)                      /*!< PWM0 CMP: CMP Mask                      */


/* ================================================================================ */
/* ================          struct 'PWM1' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  PWM1_CTRL  --------------------------------- */
#define PWM1_CTRL_STRT_Pos                    0                                                       /*!< PWM1 CTRL: STRT Position                */
#define PWM1_CTRL_STRT_Msk                    (0x01UL << PWM1_CTRL_STRT_Pos)                          /*!< PWM1 CTRL: STRT Mask                    */
#define PWM1_CTRL_SYNC_Pos                    1                                                       /*!< PWM1 CTRL: SYNC Position                */
#define PWM1_CTRL_SYNC_Msk                    (0x01UL << PWM1_CTRL_SYNC_Pos)                          /*!< PWM1 CTRL: SYNC Mask                    */
#define PWM1_CTRL_INVA_Pos                    3                                                       /*!< PWM1 CTRL: INVA Position                */
#define PWM1_CTRL_INVA_Msk                    (0x01UL << PWM1_CTRL_INVA_Pos)                          /*!< PWM1 CTRL: INVA Mask                    */
#define PWM1_CTRL_CKSEL_Pos                   5                                                       /*!< PWM1 CTRL: CKSEL Position               */
#define PWM1_CTRL_CKSEL_Msk                   (0x07UL << PWM1_CTRL_CKSEL_Pos)                         /*!< PWM1 CTRL: CKSEL Mask                   */
#define PWM1_CTRL_PRIE_Pos                    8                                                       /*!< PWM1 CTRL: PRIE Position                */
#define PWM1_CTRL_PRIE_Msk                    (0x01UL << PWM1_CTRL_PRIE_Pos)                          /*!< PWM1 CTRL: PRIE Mask                    */
#define PWM1_CTRL_PRF_Pos                     12                                                      /*!< PWM1 CTRL: PRF Position                 */
#define PWM1_CTRL_PRF_Msk                     (0x01UL << PWM1_CTRL_PRF_Pos)                           /*!< PWM1 CTRL: PRF Mask                     */

/* ----------------------------------  PWM1_CNT  ---------------------------------- */
#define PWM1_CNT_CNT_Pos                      0                                                       /*!< PWM1 CNT: CNT Position                  */
#define PWM1_CNT_CNT_Msk                      (0x0000ffffUL << PWM1_CNT_CNT_Pos)                      /*!< PWM1 CNT: CNT Mask                      */

/* ----------------------------------  PWM1_PER  ---------------------------------- */
#define PWM1_PER_PERIOD_Pos                   0                                                       /*!< PWM1 PER: PERIOD Position               */
#define PWM1_PER_PERIOD_Msk                   (0x0000ffffUL << PWM1_PER_PERIOD_Pos)                   /*!< PWM1 PER: PERIOD Mask                   */

/* ----------------------------------  PWM1_CMP  ---------------------------------- */
#define PWM1_CMP_CMP_Pos                      0                                                       /*!< PWM1 CMP: CMP Position                  */
#define PWM1_CMP_CMP_Msk                      (0x0000ffffUL << PWM1_CMP_CMP_Pos)                      /*!< PWM1 CMP: CMP Mask                      */


/* ================================================================================ */
/* ================          struct 'PWM2' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  PWM2_CTRL  --------------------------------- */
#define PWM2_CTRL_STRT_Pos                    0                                                       /*!< PWM2 CTRL: STRT Position                */
#define PWM2_CTRL_STRT_Msk                    (0x01UL << PWM2_CTRL_STRT_Pos)                          /*!< PWM2 CTRL: STRT Mask                    */
#define PWM2_CTRL_SYNC_Pos                    1                                                       /*!< PWM2 CTRL: SYNC Position                */
#define PWM2_CTRL_SYNC_Msk                    (0x01UL << PWM2_CTRL_SYNC_Pos)                          /*!< PWM2 CTRL: SYNC Mask                    */
#define PWM2_CTRL_INVA_Pos                    3                                                       /*!< PWM2 CTRL: INVA Position                */
#define PWM2_CTRL_INVA_Msk                    (0x01UL << PWM2_CTRL_INVA_Pos)                          /*!< PWM2 CTRL: INVA Mask                    */
#define PWM2_CTRL_CKSEL_Pos                   5                                                       /*!< PWM2 CTRL: CKSEL Position               */
#define PWM2_CTRL_CKSEL_Msk                   (0x07UL << PWM2_CTRL_CKSEL_Pos)                         /*!< PWM2 CTRL: CKSEL Mask                   */
#define PWM2_CTRL_PRIE_Pos                    8                                                       /*!< PWM2 CTRL: PRIE Position                */
#define PWM2_CTRL_PRIE_Msk                    (0x01UL << PWM2_CTRL_PRIE_Pos)                          /*!< PWM2 CTRL: PRIE Mask                    */
#define PWM2_CTRL_PRF_Pos                     12                                                      /*!< PWM2 CTRL: PRF Position                 */
#define PWM2_CTRL_PRF_Msk                     (0x01UL << PWM2_CTRL_PRF_Pos)                           /*!< PWM2 CTRL: PRF Mask                     */

/* ----------------------------------  PWM2_CNT  ---------------------------------- */
#define PWM2_CNT_CNT_Pos                      0                                                       /*!< PWM2 CNT: CNT Position                  */
#define PWM2_CNT_CNT_Msk                      (0x0000ffffUL << PWM2_CNT_CNT_Pos)                      /*!< PWM2 CNT: CNT Mask                      */

/* ----------------------------------  PWM2_PER  ---------------------------------- */
#define PWM2_PER_PERIOD_Pos                   0                                                       /*!< PWM2 PER: PERIOD Position               */
#define PWM2_PER_PERIOD_Msk                   (0x0000ffffUL << PWM2_PER_PERIOD_Pos)                   /*!< PWM2 PER: PERIOD Mask                   */

/* ----------------------------------  PWM2_CMP  ---------------------------------- */
#define PWM2_CMP_CMP_Pos                      0                                                       /*!< PWM2 CMP: CMP Position                  */
#define PWM2_CMP_CMP_Msk                      (0x0000ffffUL << PWM2_CMP_CMP_Pos)                      /*!< PWM2 CMP: CMP Mask                      */


/* ================================================================================ */
/* ================          struct 'PWM3' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  PWM3_CTRL  --------------------------------- */
#define PWM3_CTRL_STRT_Pos                    0                                                       /*!< PWM3 CTRL: STRT Position                */
#define PWM3_CTRL_STRT_Msk                    (0x01UL << PWM3_CTRL_STRT_Pos)                          /*!< PWM3 CTRL: STRT Mask                    */
#define PWM3_CTRL_SYNC_Pos                    1                                                       /*!< PWM3 CTRL: SYNC Position                */
#define PWM3_CTRL_SYNC_Msk                    (0x01UL << PWM3_CTRL_SYNC_Pos)                          /*!< PWM3 CTRL: SYNC Mask                    */
#define PWM3_CTRL_INVA_Pos                    3                                                       /*!< PWM3 CTRL: INVA Position                */
#define PWM3_CTRL_INVA_Msk                    (0x01UL << PWM3_CTRL_INVA_Pos)                          /*!< PWM3 CTRL: INVA Mask                    */
#define PWM3_CTRL_CKSEL_Pos                   5                                                       /*!< PWM3 CTRL: CKSEL Position               */
#define PWM3_CTRL_CKSEL_Msk                   (0x07UL << PWM3_CTRL_CKSEL_Pos)                         /*!< PWM3 CTRL: CKSEL Mask                   */
#define PWM3_CTRL_PRIE_Pos                    8                                                       /*!< PWM3 CTRL: PRIE Position                */
#define PWM3_CTRL_PRIE_Msk                    (0x01UL << PWM3_CTRL_PRIE_Pos)                          /*!< PWM3 CTRL: PRIE Mask                    */
#define PWM3_CTRL_PRF_Pos                     12                                                      /*!< PWM3 CTRL: PRF Position                 */
#define PWM3_CTRL_PRF_Msk                     (0x01UL << PWM3_CTRL_PRF_Pos)                           /*!< PWM3 CTRL: PRF Mask                     */

/* ----------------------------------  PWM3_CNT  ---------------------------------- */
#define PWM3_CNT_CNT_Pos                      0                                                       /*!< PWM3 CNT: CNT Position                  */
#define PWM3_CNT_CNT_Msk                      (0x0000ffffUL << PWM3_CNT_CNT_Pos)                      /*!< PWM3 CNT: CNT Mask                      */

/* ----------------------------------  PWM3_PER  ---------------------------------- */
#define PWM3_PER_PERIOD_Pos                   0                                                       /*!< PWM3 PER: PERIOD Position               */
#define PWM3_PER_PERIOD_Msk                   (0x0000ffffUL << PWM3_PER_PERIOD_Pos)                   /*!< PWM3 PER: PERIOD Mask                   */

/* ----------------------------------  PWM3_CMP  ---------------------------------- */
#define PWM3_CMP_CMP_Pos                      0                                                       /*!< PWM3 CMP: CMP Position                  */
#define PWM3_CMP_CMP_Msk                      (0x0000ffffUL << PWM3_CMP_CMP_Pos)                      /*!< PWM3 CMP: CMP Mask                      */


/* ================================================================================ */
/* ================          struct 'PWM4' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  PWM4_CTRL  --------------------------------- */
#define PWM4_CTRL_STRT_Pos                    0                                                       /*!< PWM4 CTRL: STRT Position                */
#define PWM4_CTRL_STRT_Msk                    (0x01UL << PWM4_CTRL_STRT_Pos)                          /*!< PWM4 CTRL: STRT Mask                    */
#define PWM4_CTRL_SYNC_Pos                    1                                                       /*!< PWM4 CTRL: SYNC Position                */
#define PWM4_CTRL_SYNC_Msk                    (0x01UL << PWM4_CTRL_SYNC_Pos)                          /*!< PWM4 CTRL: SYNC Mask                    */
#define PWM4_CTRL_INVA_Pos                    3                                                       /*!< PWM4 CTRL: INVA Position                */
#define PWM4_CTRL_INVA_Msk                    (0x01UL << PWM4_CTRL_INVA_Pos)                          /*!< PWM4 CTRL: INVA Mask                    */
#define PWM4_CTRL_CKSEL_Pos                   5                                                       /*!< PWM4 CTRL: CKSEL Position               */
#define PWM4_CTRL_CKSEL_Msk                   (0x07UL << PWM4_CTRL_CKSEL_Pos)                         /*!< PWM4 CTRL: CKSEL Mask                   */
#define PWM4_CTRL_PRIE_Pos                    8                                                       /*!< PWM4 CTRL: PRIE Position                */
#define PWM4_CTRL_PRIE_Msk                    (0x01UL << PWM4_CTRL_PRIE_Pos)                          /*!< PWM4 CTRL: PRIE Mask                    */
#define PWM4_CTRL_PRF_Pos                     12                                                      /*!< PWM4 CTRL: PRF Position                 */
#define PWM4_CTRL_PRF_Msk                     (0x01UL << PWM4_CTRL_PRF_Pos)                           /*!< PWM4 CTRL: PRF Mask                     */

/* ----------------------------------  PWM4_CNT  ---------------------------------- */
#define PWM4_CNT_CNT_Pos                      0                                                       /*!< PWM4 CNT: CNT Position                  */
#define PWM4_CNT_CNT_Msk                      (0x0000ffffUL << PWM4_CNT_CNT_Pos)                      /*!< PWM4 CNT: CNT Mask                      */

/* ----------------------------------  PWM4_PER  ---------------------------------- */
#define PWM4_PER_PERIOD_Pos                   0                                                       /*!< PWM4 PER: PERIOD Position               */
#define PWM4_PER_PERIOD_Msk                   (0x0000ffffUL << PWM4_PER_PERIOD_Pos)                   /*!< PWM4 PER: PERIOD Mask                   */

/* ----------------------------------  PWM4_CMP  ---------------------------------- */
#define PWM4_CMP_CMP_Pos                      0                                                       /*!< PWM4 CMP: CMP Position                  */
#define PWM4_CMP_CMP_Msk                      (0x0000ffffUL << PWM4_CMP_CMP_Pos)                      /*!< PWM4 CMP: CMP Mask                      */


/* ================================================================================ */
/* ================          struct 'PWM5' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  PWM5_CTRL  --------------------------------- */
#define PWM5_CTRL_STRT_Pos                    0                                                       /*!< PWM5 CTRL: STRT Position                */
#define PWM5_CTRL_STRT_Msk                    (0x01UL << PWM5_CTRL_STRT_Pos)                          /*!< PWM5 CTRL: STRT Mask                    */
#define PWM5_CTRL_SYNC_Pos                    1                                                       /*!< PWM5 CTRL: SYNC Position                */
#define PWM5_CTRL_SYNC_Msk                    (0x01UL << PWM5_CTRL_SYNC_Pos)                          /*!< PWM5 CTRL: SYNC Mask                    */
#define PWM5_CTRL_INVA_Pos                    3                                                       /*!< PWM5 CTRL: INVA Position                */
#define PWM5_CTRL_INVA_Msk                    (0x01UL << PWM5_CTRL_INVA_Pos)                          /*!< PWM5 CTRL: INVA Mask                    */
#define PWM5_CTRL_CKSEL_Pos                   5                                                       /*!< PWM5 CTRL: CKSEL Position               */
#define PWM5_CTRL_CKSEL_Msk                   (0x07UL << PWM5_CTRL_CKSEL_Pos)                         /*!< PWM5 CTRL: CKSEL Mask                   */
#define PWM5_CTRL_PRIE_Pos                    8                                                       /*!< PWM5 CTRL: PRIE Position                */
#define PWM5_CTRL_PRIE_Msk                    (0x01UL << PWM5_CTRL_PRIE_Pos)                          /*!< PWM5 CTRL: PRIE Mask                    */
#define PWM5_CTRL_PRF_Pos                     12                                                      /*!< PWM5 CTRL: PRF Position                 */
#define PWM5_CTRL_PRF_Msk                     (0x01UL << PWM5_CTRL_PRF_Pos)                           /*!< PWM5 CTRL: PRF Mask                     */

/* ----------------------------------  PWM5_CNT  ---------------------------------- */
#define PWM5_CNT_CNT_Pos                      0                                                       /*!< PWM5 CNT: CNT Position                  */
#define PWM5_CNT_CNT_Msk                      (0x0000ffffUL << PWM5_CNT_CNT_Pos)                      /*!< PWM5 CNT: CNT Mask                      */

/* ----------------------------------  PWM5_PER  ---------------------------------- */
#define PWM5_PER_PERIOD_Pos                   0                                                       /*!< PWM5 PER: PERIOD Position               */
#define PWM5_PER_PERIOD_Msk                   (0x0000ffffUL << PWM5_PER_PERIOD_Pos)                   /*!< PWM5 PER: PERIOD Mask                   */

/* ----------------------------------  PWM5_CMP  ---------------------------------- */
#define PWM5_CMP_CMP_Pos                      0                                                       /*!< PWM5 CMP: CMP Position                  */
#define PWM5_CMP_CMP_Msk                      (0x0000ffffUL << PWM5_CMP_CMP_Pos)                      /*!< PWM5 CMP: CMP Mask                      */


/* ================================================================================ */
/* ================          struct 'PWM6' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  PWM6_CTRL  --------------------------------- */
#define PWM6_CTRL_STRT_Pos                    0                                                       /*!< PWM6 CTRL: STRT Position                */
#define PWM6_CTRL_STRT_Msk                    (0x01UL << PWM6_CTRL_STRT_Pos)                          /*!< PWM6 CTRL: STRT Mask                    */
#define PWM6_CTRL_SYNC_Pos                    1                                                       /*!< PWM6 CTRL: SYNC Position                */
#define PWM6_CTRL_SYNC_Msk                    (0x01UL << PWM6_CTRL_SYNC_Pos)                          /*!< PWM6 CTRL: SYNC Mask                    */
#define PWM6_CTRL_INVA_Pos                    3                                                       /*!< PWM6 CTRL: INVA Position                */
#define PWM6_CTRL_INVA_Msk                    (0x01UL << PWM6_CTRL_INVA_Pos)                          /*!< PWM6 CTRL: INVA Mask                    */
#define PWM6_CTRL_CKSEL_Pos                   5                                                       /*!< PWM6 CTRL: CKSEL Position               */
#define PWM6_CTRL_CKSEL_Msk                   (0x07UL << PWM6_CTRL_CKSEL_Pos)                         /*!< PWM6 CTRL: CKSEL Mask                   */
#define PWM6_CTRL_PRIE_Pos                    8                                                       /*!< PWM6 CTRL: PRIE Position                */
#define PWM6_CTRL_PRIE_Msk                    (0x01UL << PWM6_CTRL_PRIE_Pos)                          /*!< PWM6 CTRL: PRIE Mask                    */
#define PWM6_CTRL_PRF_Pos                     12                                                      /*!< PWM6 CTRL: PRF Position                 */
#define PWM6_CTRL_PRF_Msk                     (0x01UL << PWM6_CTRL_PRF_Pos)                           /*!< PWM6 CTRL: PRF Mask                     */

/* ----------------------------------  PWM6_CNT  ---------------------------------- */
#define PWM6_CNT_CNT_Pos                      0                                                       /*!< PWM6 CNT: CNT Position                  */
#define PWM6_CNT_CNT_Msk                      (0x0000ffffUL << PWM6_CNT_CNT_Pos)                      /*!< PWM6 CNT: CNT Mask                      */

/* ----------------------------------  PWM6_PER  ---------------------------------- */
#define PWM6_PER_PERIOD_Pos                   0                                                       /*!< PWM6 PER: PERIOD Position               */
#define PWM6_PER_PERIOD_Msk                   (0x0000ffffUL << PWM6_PER_PERIOD_Pos)                   /*!< PWM6 PER: PERIOD Mask                   */

/* ----------------------------------  PWM6_CMP  ---------------------------------- */
#define PWM6_CMP_CMP_Pos                      0                                                       /*!< PWM6 CMP: CMP Position                  */
#define PWM6_CMP_CMP_Msk                      (0x0000ffffUL << PWM6_CMP_CMP_Pos)                      /*!< PWM6 CMP: CMP Mask                      */


/* ================================================================================ */
/* ================          struct 'PWM7' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  PWM7_CTRL  --------------------------------- */
#define PWM7_CTRL_STRT_Pos                    0                                                       /*!< PWM7 CTRL: STRT Position                */
#define PWM7_CTRL_STRT_Msk                    (0x01UL << PWM7_CTRL_STRT_Pos)                          /*!< PWM7 CTRL: STRT Mask                    */
#define PWM7_CTRL_SYNC_Pos                    1                                                       /*!< PWM7 CTRL: SYNC Position                */
#define PWM7_CTRL_SYNC_Msk                    (0x01UL << PWM7_CTRL_SYNC_Pos)                          /*!< PWM7 CTRL: SYNC Mask                    */
#define PWM7_CTRL_INVA_Pos                    3                                                       /*!< PWM7 CTRL: INVA Position                */
#define PWM7_CTRL_INVA_Msk                    (0x01UL << PWM7_CTRL_INVA_Pos)                          /*!< PWM7 CTRL: INVA Mask                    */
#define PWM7_CTRL_CKSEL_Pos                   5                                                       /*!< PWM7 CTRL: CKSEL Position               */
#define PWM7_CTRL_CKSEL_Msk                   (0x07UL << PWM7_CTRL_CKSEL_Pos)                         /*!< PWM7 CTRL: CKSEL Mask                   */
#define PWM7_CTRL_PRIE_Pos                    8                                                       /*!< PWM7 CTRL: PRIE Position                */
#define PWM7_CTRL_PRIE_Msk                    (0x01UL << PWM7_CTRL_PRIE_Pos)                          /*!< PWM7 CTRL: PRIE Mask                    */
#define PWM7_CTRL_PRF_Pos                     12                                                      /*!< PWM7 CTRL: PRF Position                 */
#define PWM7_CTRL_PRF_Msk                     (0x01UL << PWM7_CTRL_PRF_Pos)                           /*!< PWM7 CTRL: PRF Mask                     */

/* ----------------------------------  PWM7_CNT  ---------------------------------- */
#define PWM7_CNT_CNT_Pos                      0                                                       /*!< PWM7 CNT: CNT Position                  */
#define PWM7_CNT_CNT_Msk                      (0x0000ffffUL << PWM7_CNT_CNT_Pos)                      /*!< PWM7 CNT: CNT Mask                      */

/* ----------------------------------  PWM7_PER  ---------------------------------- */
#define PWM7_PER_PERIOD_Pos                   0                                                       /*!< PWM7 PER: PERIOD Position               */
#define PWM7_PER_PERIOD_Msk                   (0x0000ffffUL << PWM7_PER_PERIOD_Pos)                   /*!< PWM7 PER: PERIOD Mask                   */

/* ----------------------------------  PWM7_CMP  ---------------------------------- */
#define PWM7_CMP_CMP_Pos                      0                                                       /*!< PWM7 CMP: CMP Position                  */
#define PWM7_CMP_CMP_Msk                      (0x0000ffffUL << PWM7_CMP_CMP_Pos)                      /*!< PWM7 CMP: CMP Mask                      */


/* ================================================================================ */
/* ================        struct 'PWMPRS0' Position & Mask        ================ */
/* ================================================================================ */


/* --------------------------------  PWMPRS0_PRSn  -------------------------------- */
#define PWMPRS0_PRSn_PRESCALER_Pos            0                                                       /*!< PWMPRS0 PRSn: PRESCALER Position        */
#define PWMPRS0_PRSn_PRESCALER_Msk            (0x000000ffUL << PWMPRS0_PRSn_PRESCALER_Pos)            /*!< PWMPRS0 PRSn: PRESCALER Mask            */
#define PWMPRS0_PRSn_CLKEN_Pos                15                                                      /*!< PWMPRS0 PRSn: CLKEN Position            */
#define PWMPRS0_PRSn_CLKEN_Msk                (0x01UL << PWMPRS0_PRSn_CLKEN_Pos)                      /*!< PWMPRS0 PRSn: CLKEN Mask                */


/* ================================================================================ */
/* ================        struct 'PWMPRS1' Position & Mask        ================ */
/* ================================================================================ */


/* --------------------------------  PWMPRS1_PRSn  -------------------------------- */
#define PWMPRS1_PRSn_PRESCALER_Pos            0                                                       /*!< PWMPRS1 PRSn: PRESCALER Position        */
#define PWMPRS1_PRSn_PRESCALER_Msk            (0x000000ffUL << PWMPRS1_PRSn_PRESCALER_Pos)            /*!< PWMPRS1 PRSn: PRESCALER Mask            */
#define PWMPRS1_PRSn_CLKEN_Pos                15                                                      /*!< PWMPRS1 PRSn: CLKEN Position            */
#define PWMPRS1_PRSn_CLKEN_Msk                (0x01UL << PWMPRS1_PRSn_CLKEN_Pos)                      /*!< PWMPRS1 PRSn: CLKEN Mask                */


/* ================================================================================ */
/* ================          struct 'I2C0' Position & Mask         ================ */
/* ================================================================================ */


/* -----------------------------------  I2C0_DR  ---------------------------------- */
#define I2C0_DR_ICDR_Pos                      0                                                       /*!< I2C0 DR: ICDR Position                  */
#define I2C0_DR_ICDR_Msk                      (0x000000ffUL << I2C0_DR_ICDR_Pos)                      /*!< I2C0 DR: ICDR Mask                      */

/* -----------------------------------  I2C0_SR  ---------------------------------- */
#define I2C0_SR_RXACK_Pos                     0                                                       /*!< I2C0 SR: RXACK Position                 */
#define I2C0_SR_RXACK_Msk                     (0x01UL << I2C0_SR_RXACK_Pos)                           /*!< I2C0 SR: RXACK Mask                     */
#define I2C0_SR_TMODE_Pos                     1                                                       /*!< I2C0 SR: TMODE Position                 */
#define I2C0_SR_TMODE_Msk                     (0x01UL << I2C0_SR_TMODE_Pos)                           /*!< I2C0 SR: TMODE Mask                     */
#define I2C0_SR_BUSY_Pos                      2                                                       /*!< I2C0 SR: BUSY Position                  */
#define I2C0_SR_BUSY_Msk                      (0x01UL << I2C0_SR_BUSY_Pos)                            /*!< I2C0 SR: BUSY Mask                      */
#define I2C0_SR_MLOST_Pos                     3                                                       /*!< I2C0 SR: MLOST Position                 */
#define I2C0_SR_MLOST_Msk                     (0x01UL << I2C0_SR_MLOST_Pos)                           /*!< I2C0 SR: MLOST Mask                     */
#define I2C0_SR_SSEL_Pos                      4                                                       /*!< I2C0 SR: SSEL Position                  */
#define I2C0_SR_SSEL_Msk                      (0x01UL << I2C0_SR_SSEL_Pos)                            /*!< I2C0 SR: SSEL Mask                      */
#define I2C0_SR_STOP_Pos                      5                                                       /*!< I2C0 SR: STOP Position                  */
#define I2C0_SR_STOP_Msk                      (0x01UL << I2C0_SR_STOP_Pos)                            /*!< I2C0 SR: STOP Mask                      */
#define I2C0_SR_TEND_Pos                      6                                                       /*!< I2C0 SR: TEND Position                  */
#define I2C0_SR_TEND_Msk                      (0x01UL << I2C0_SR_TEND_Pos)                            /*!< I2C0 SR: TEND Mask                      */
#define I2C0_SR_GCALL_Pos                     7                                                       /*!< I2C0 SR: GCALL Position                 */
#define I2C0_SR_GCALL_Msk                     (0x01UL << I2C0_SR_GCALL_Pos)                           /*!< I2C0 SR: GCALL Mask                     */

/* ----------------------------------  I2C0_SAR  ---------------------------------- */
#define I2C0_SAR_GCALL_Pos                    0                                                       /*!< I2C0 SAR: GCALL Position                */
#define I2C0_SAR_GCALL_Msk                    (0x01UL << I2C0_SAR_GCALL_Pos)                          /*!< I2C0 SAR: GCALL Mask                    */
#define I2C0_SAR_SVAD_Pos                     1                                                       /*!< I2C0 SAR: SVAD Position                 */
#define I2C0_SAR_SVAD_Msk                     (0x7fUL << I2C0_SAR_SVAD_Pos)                           /*!< I2C0 SAR: SVAD Mask                     */

/* -----------------------------------  I2C0_CR  ---------------------------------- */
#define I2C0_CR_START_Pos                     0                                                       /*!< I2C0 CR: START Position                 */
#define I2C0_CR_START_Msk                     (0x01UL << I2C0_CR_START_Pos)                           /*!< I2C0 CR: START Mask                     */
#define I2C0_CR_STOP_Pos                      1                                                       /*!< I2C0 CR: STOP Position                  */
#define I2C0_CR_STOP_Msk                      (0x01UL << I2C0_CR_STOP_Pos)                            /*!< I2C0 CR: STOP Mask                      */
#define I2C0_CR_ACKEN_Pos                     3                                                       /*!< I2C0 CR: ACKEN Position                 */
#define I2C0_CR_ACKEN_Msk                     (0x01UL << I2C0_CR_ACKEN_Pos)                           /*!< I2C0 CR: ACKEN Mask                     */
#define I2C0_CR_IINTEN_Pos                    4                                                       /*!< I2C0 CR: IINTEN Position                */
#define I2C0_CR_IINTEN_Msk                    (0x01UL << I2C0_CR_IINTEN_Pos)                          /*!< I2C0 CR: IINTEN Mask                    */
#define I2C0_CR_SOFTRESET_Pos                 5                                                       /*!< I2C0 CR: SOFTRESET Position             */
#define I2C0_CR_SOFTRESET_Msk                 (0x01UL << I2C0_CR_SOFTRESET_Pos)                       /*!< I2C0 CR: SOFTRESET Mask                 */
#define I2C0_CR_IIF_Pos                       7                                                       /*!< I2C0 CR: IIF Position                   */
#define I2C0_CR_IIF_Msk                       (0x01UL << I2C0_CR_IIF_Pos)                             /*!< I2C0 CR: IIF Mask                       */
#define I2C0_CR_INTERVAL_Pos                  8                                                       /*!< I2C0 CR: INTERVAL Position              */
#define I2C0_CR_INTERVAL_Msk                  (0x03UL << I2C0_CR_INTERVAL_Pos)                        /*!< I2C0 CR: INTERVAL Mask                  */

/* ----------------------------------  I2C0_SCLL  --------------------------------- */
#define I2C0_SCLL_SCLL_Pos                    0                                                       /*!< I2C0 SCLL: SCLL Position                */
#define I2C0_SCLL_SCLL_Msk                    (0x0000ffffUL << I2C0_SCLL_SCLL_Pos)                    /*!< I2C0 SCLL: SCLL Mask                    */

/* ----------------------------------  I2C0_SCLH  --------------------------------- */
#define I2C0_SCLH_SCLH_Pos                    0                                                       /*!< I2C0 SCLH: SCLH Position                */
#define I2C0_SCLH_SCLH_Msk                    (0x0000ffffUL << I2C0_SCLH_SCLH_Pos)                    /*!< I2C0 SCLH: SCLH Mask                    */

/* ----------------------------------  I2C0_SDH  ---------------------------------- */
#define I2C0_SDH_SDH_Pos                      0                                                       /*!< I2C0 SDH: SDH Position                  */
#define I2C0_SDH_SDH_Msk                      (0x00007fffUL << I2C0_SDH_SDH_Pos)                      /*!< I2C0 SDH: SDH Mask                      */


/* ================================================================================ */
/* ================          struct 'I2C1' Position & Mask         ================ */
/* ================================================================================ */


/* -----------------------------------  I2C1_DR  ---------------------------------- */
#define I2C1_DR_ICDR_Pos                      0                                                       /*!< I2C1 DR: ICDR Position                  */
#define I2C1_DR_ICDR_Msk                      (0x000000ffUL << I2C1_DR_ICDR_Pos)                      /*!< I2C1 DR: ICDR Mask                      */

/* -----------------------------------  I2C1_SR  ---------------------------------- */
#define I2C1_SR_RXACK_Pos                     0                                                       /*!< I2C1 SR: RXACK Position                 */
#define I2C1_SR_RXACK_Msk                     (0x01UL << I2C1_SR_RXACK_Pos)                           /*!< I2C1 SR: RXACK Mask                     */
#define I2C1_SR_TMODE_Pos                     1                                                       /*!< I2C1 SR: TMODE Position                 */
#define I2C1_SR_TMODE_Msk                     (0x01UL << I2C1_SR_TMODE_Pos)                           /*!< I2C1 SR: TMODE Mask                     */
#define I2C1_SR_BUSY_Pos                      2                                                       /*!< I2C1 SR: BUSY Position                  */
#define I2C1_SR_BUSY_Msk                      (0x01UL << I2C1_SR_BUSY_Pos)                            /*!< I2C1 SR: BUSY Mask                      */
#define I2C1_SR_MLOST_Pos                     3                                                       /*!< I2C1 SR: MLOST Position                 */
#define I2C1_SR_MLOST_Msk                     (0x01UL << I2C1_SR_MLOST_Pos)                           /*!< I2C1 SR: MLOST Mask                     */
#define I2C1_SR_SSEL_Pos                      4                                                       /*!< I2C1 SR: SSEL Position                  */
#define I2C1_SR_SSEL_Msk                      (0x01UL << I2C1_SR_SSEL_Pos)                            /*!< I2C1 SR: SSEL Mask                      */
#define I2C1_SR_STOP_Pos                      5                                                       /*!< I2C1 SR: STOP Position                  */
#define I2C1_SR_STOP_Msk                      (0x01UL << I2C1_SR_STOP_Pos)                            /*!< I2C1 SR: STOP Mask                      */
#define I2C1_SR_TEND_Pos                      6                                                       /*!< I2C1 SR: TEND Position                  */
#define I2C1_SR_TEND_Msk                      (0x01UL << I2C1_SR_TEND_Pos)                            /*!< I2C1 SR: TEND Mask                      */
#define I2C1_SR_GCALL_Pos                     7                                                       /*!< I2C1 SR: GCALL Position                 */
#define I2C1_SR_GCALL_Msk                     (0x01UL << I2C1_SR_GCALL_Pos)                           /*!< I2C1 SR: GCALL Mask                     */

/* ----------------------------------  I2C1_SAR  ---------------------------------- */
#define I2C1_SAR_GCALL_Pos                    0                                                       /*!< I2C1 SAR: GCALL Position                */
#define I2C1_SAR_GCALL_Msk                    (0x01UL << I2C1_SAR_GCALL_Pos)                          /*!< I2C1 SAR: GCALL Mask                    */
#define I2C1_SAR_SVAD_Pos                     1                                                       /*!< I2C1 SAR: SVAD Position                 */
#define I2C1_SAR_SVAD_Msk                     (0x7fUL << I2C1_SAR_SVAD_Pos)                           /*!< I2C1 SAR: SVAD Mask                     */

/* -----------------------------------  I2C1_CR  ---------------------------------- */
#define I2C1_CR_START_Pos                     0                                                       /*!< I2C1 CR: START Position                 */
#define I2C1_CR_START_Msk                     (0x01UL << I2C1_CR_START_Pos)                           /*!< I2C1 CR: START Mask                     */
#define I2C1_CR_STOP_Pos                      1                                                       /*!< I2C1 CR: STOP Position                  */
#define I2C1_CR_STOP_Msk                      (0x01UL << I2C1_CR_STOP_Pos)                            /*!< I2C1 CR: STOP Mask                      */
#define I2C1_CR_ACKEN_Pos                     3                                                       /*!< I2C1 CR: ACKEN Position                 */
#define I2C1_CR_ACKEN_Msk                     (0x01UL << I2C1_CR_ACKEN_Pos)                           /*!< I2C1 CR: ACKEN Mask                     */
#define I2C1_CR_IINTEN_Pos                    4                                                       /*!< I2C1 CR: IINTEN Position                */
#define I2C1_CR_IINTEN_Msk                    (0x01UL << I2C1_CR_IINTEN_Pos)                          /*!< I2C1 CR: IINTEN Mask                    */
#define I2C1_CR_SOFTRESET_Pos                 5                                                       /*!< I2C1 CR: SOFTRESET Position             */
#define I2C1_CR_SOFTRESET_Msk                 (0x01UL << I2C1_CR_SOFTRESET_Pos)                       /*!< I2C1 CR: SOFTRESET Mask                 */
#define I2C1_CR_IIF_Pos                       7                                                       /*!< I2C1 CR: IIF Position                   */
#define I2C1_CR_IIF_Msk                       (0x01UL << I2C1_CR_IIF_Pos)                             /*!< I2C1 CR: IIF Mask                       */
#define I2C1_CR_INTERVAL_Pos                  8                                                       /*!< I2C1 CR: INTERVAL Position              */
#define I2C1_CR_INTERVAL_Msk                  (0x03UL << I2C1_CR_INTERVAL_Pos)                        /*!< I2C1 CR: INTERVAL Mask                  */

/* ----------------------------------  I2C1_SCLL  --------------------------------- */
#define I2C1_SCLL_SCLL_Pos                    0                                                       /*!< I2C1 SCLL: SCLL Position                */
#define I2C1_SCLL_SCLL_Msk                    (0x0000ffffUL << I2C1_SCLL_SCLL_Pos)                    /*!< I2C1 SCLL: SCLL Mask                    */

/* ----------------------------------  I2C1_SCLH  --------------------------------- */
#define I2C1_SCLH_SCLH_Pos                    0                                                       /*!< I2C1 SCLH: SCLH Position                */
#define I2C1_SCLH_SCLH_Msk                    (0x0000ffffUL << I2C1_SCLH_SCLH_Pos)                    /*!< I2C1 SCLH: SCLH Mask                    */

/* ----------------------------------  I2C1_SDH  ---------------------------------- */
#define I2C1_SDH_SDH_Pos                      0                                                       /*!< I2C1 SDH: SDH Position                  */
#define I2C1_SDH_SDH_Msk                      (0x00007fffUL << I2C1_SDH_SDH_Pos)                      /*!< I2C1 SDH: SDH Mask                      */


/* ================================================================================ */
/* ================         struct 'UART0' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  UART0_RBR  --------------------------------- */
#define UART0_RBR_RBR_Pos                     0                                                       /*!< UART0 RBR: RBR Position                 */
#define UART0_RBR_RBR_Msk                     (0x000000ffUL << UART0_RBR_RBR_Pos)                     /*!< UART0 RBR: RBR Mask                     */

/* ----------------------------------  UART0_THR  --------------------------------- */
#define UART0_THR_THR_Pos                     0                                                       /*!< UART0 THR: THR Position                 */
#define UART0_THR_THR_Msk                     (0x000000ffUL << UART0_THR_THR_Pos)                     /*!< UART0 THR: THR Mask                     */

/* ----------------------------------  UART0_DLL  --------------------------------- */
#define UART0_DLL_DLL_Pos                     0                                                       /*!< UART0 DLL: DLL Position                 */
#define UART0_DLL_DLL_Msk                     (0x000000ffUL << UART0_DLL_DLL_Pos)                     /*!< UART0 DLL: DLL Mask                     */

/* ----------------------------------  UART0_DLM  --------------------------------- */
#define UART0_DLM_DLM_Pos                     0                                                       /*!< UART0 DLM: DLM Position                 */
#define UART0_DLM_DLM_Msk                     (0x000000ffUL << UART0_DLM_DLM_Pos)                     /*!< UART0 DLM: DLM Mask                     */

/* ----------------------------------  UART0_IER  --------------------------------- */
#define UART0_IER_DRIE_Pos                    0                                                       /*!< UART0 IER: DRIE Position                */
#define UART0_IER_DRIE_Msk                    (0x01UL << UART0_IER_DRIE_Pos)                          /*!< UART0 IER: DRIE Mask                    */
#define UART0_IER_THREIE_Pos                  1                                                       /*!< UART0 IER: THREIE Position              */
#define UART0_IER_THREIE_Msk                  (0x01UL << UART0_IER_THREIE_Pos)                        /*!< UART0 IER: THREIE Mask                  */
#define UART0_IER_RLSIE_Pos                   2                                                       /*!< UART0 IER: RLSIE Position               */
#define UART0_IER_RLSIE_Msk                   (0x01UL << UART0_IER_RLSIE_Pos)                         /*!< UART0 IER: RLSIE Mask                   */
#define UART0_IER_TEMTIE_Pos                  3                                                       /*!< UART0 IER: TEMTIE Position              */
#define UART0_IER_TEMTIE_Msk                  (0x01UL << UART0_IER_TEMTIE_Pos)                        /*!< UART0 IER: TEMTIE Mask                  */

/* ----------------------------------  UART0_IIR  --------------------------------- */
#define UART0_IIR_IPEN_Pos                    0                                                       /*!< UART0 IIR: IPEN Position                */
#define UART0_IIR_IPEN_Msk                    (0x01UL << UART0_IIR_IPEN_Pos)                          /*!< UART0 IIR: IPEN Mask                    */
#define UART0_IIR_IID_FID_Pos                 1                                                       /*!< UART0 IIR: IID_FID Position             */
#define UART0_IIR_IID_FID_Msk                 (0x07UL << UART0_IIR_IID_FID_Pos)                       /*!< UART0 IIR: IID_FID Mask                 */
#define UART0_IIR_XMITE_Pos                   4                                                       /*!< UART0 IIR: XMITE Position               */
#define UART0_IIR_XMITE_Msk                   (0x01UL << UART0_IIR_XMITE_Pos)                         /*!< UART0 IIR: XMITE Mask                   */
#define UART0_IIR_FIFO_Pos                    6                                                       /*!< UART0 IIR: FIFO Position                */
#define UART0_IIR_FIFO_Msk                    (0x03UL << UART0_IIR_FIFO_Pos)                          /*!< UART0 IIR: FIFO Mask                    */

/* ----------------------------------  UART0_FCR  --------------------------------- */
#define UART0_FCR_FIFOEN_Pos                  0                                                       /*!< UART0 FCR: FIFOEN Position              */
#define UART0_FCR_FIFOEN_Msk                  (0x01UL << UART0_FCR_FIFOEN_Pos)                        /*!< UART0 FCR: FIFOEN Mask                  */
#define UART0_FCR_FCR1_Pos                    1                                                       /*!< UART0 FCR: FCR1 Position                */
#define UART0_FCR_FCR1_Msk                    (0x01UL << UART0_FCR_FCR1_Pos)                          /*!< UART0 FCR: FCR1 Mask                    */
#define UART0_FCR_FCR2_Pos                    2                                                       /*!< UART0 FCR: FCR2 Position                */
#define UART0_FCR_FCR2_Msk                    (0x01UL << UART0_FCR_FCR2_Pos)                          /*!< UART0 FCR: FCR2 Mask                    */
#define UART0_FCR_FIFODEPTH_Pos               6                                                       /*!< UART0 FCR: FIFODEPTH Position           */
#define UART0_FCR_FIFODEPTH_Msk               (0x03UL << UART0_FCR_FIFODEPTH_Pos)                     /*!< UART0 FCR: FIFODEPTH Mask               */

/* ----------------------------------  UART0_LCR  --------------------------------- */
#define UART0_LCR_DLEN_Pos                    0                                                       /*!< UART0 LCR: DLEN Position                */
#define UART0_LCR_DLEN_Msk                    (0x03UL << UART0_LCR_DLEN_Pos)                          /*!< UART0 LCR: DLEN Mask                    */
#define UART0_LCR_STOPBIT_Pos                 2                                                       /*!< UART0 LCR: STOPBIT Position             */
#define UART0_LCR_STOPBIT_Msk                 (0x01UL << UART0_LCR_STOPBIT_Pos)                       /*!< UART0 LCR: STOPBIT Mask                 */
#define UART0_LCR_PEN_Pos                     3                                                       /*!< UART0 LCR: PEN Position                 */
#define UART0_LCR_PEN_Msk                     (0x01UL << UART0_LCR_PEN_Pos)                           /*!< UART0 LCR: PEN Mask                     */
#define UART0_LCR_PARITY_Pos                  4                                                       /*!< UART0 LCR: PARITY Position              */
#define UART0_LCR_PARITY_Msk                  (0x01UL << UART0_LCR_PARITY_Pos)                        /*!< UART0 LCR: PARITY Mask                  */
#define UART0_LCR_STICKP_Pos                  5                                                       /*!< UART0 LCR: STICKP Position              */
#define UART0_LCR_STICKP_Msk                  (0x01UL << UART0_LCR_STICKP_Pos)                        /*!< UART0 LCR: STICKP Mask                  */
#define UART0_LCR_BREAK_Pos                   6                                                       /*!< UART0 LCR: BREAK Position               */
#define UART0_LCR_BREAK_Msk                   (0x01UL << UART0_LCR_BREAK_Pos)                         /*!< UART0 LCR: BREAK Mask                   */
#define UART0_LCR_DLAB_Pos                    7                                                       /*!< UART0 LCR: DLAB Position                */
#define UART0_LCR_DLAB_Msk                    (0x01UL << UART0_LCR_DLAB_Pos)                          /*!< UART0 LCR: DLAB Mask                    */

/* ----------------------------------  UART0_LSR  --------------------------------- */
#define UART0_LSR_DR_Pos                      0                                                       /*!< UART0 LSR: DR Position                  */
#define UART0_LSR_DR_Msk                      (0x01UL << UART0_LSR_DR_Pos)                            /*!< UART0 LSR: DR Mask                      */
#define UART0_LSR_OE_Pos                      1                                                       /*!< UART0 LSR: OE Position                  */
#define UART0_LSR_OE_Msk                      (0x01UL << UART0_LSR_OE_Pos)                            /*!< UART0 LSR: OE Mask                      */
#define UART0_LSR_PE_Pos                      2                                                       /*!< UART0 LSR: PE Position                  */
#define UART0_LSR_PE_Msk                      (0x01UL << UART0_LSR_PE_Pos)                            /*!< UART0 LSR: PE Mask                      */
#define UART0_LSR_FE_Pos                      3                                                       /*!< UART0 LSR: FE Position                  */
#define UART0_LSR_FE_Msk                      (0x01UL << UART0_LSR_FE_Pos)                            /*!< UART0 LSR: FE Mask                      */
#define UART0_LSR_BI_Pos                      4                                                       /*!< UART0 LSR: BI Position                  */
#define UART0_LSR_BI_Msk                      (0x01UL << UART0_LSR_BI_Pos)                            /*!< UART0 LSR: BI Mask                      */
#define UART0_LSR_THRE_Pos                    5                                                       /*!< UART0 LSR: THRE Position                */
#define UART0_LSR_THRE_Msk                    (0x01UL << UART0_LSR_THRE_Pos)                          /*!< UART0 LSR: THRE Mask                    */
#define UART0_LSR_TEMT_Pos                    6                                                       /*!< UART0 LSR: TEMT Position                */
#define UART0_LSR_TEMT_Msk                    (0x01UL << UART0_LSR_TEMT_Pos)                          /*!< UART0 LSR: TEMT Mask                    */
#define UART0_LSR_FIFOE_Pos                   7                                                       /*!< UART0 LSR: FIFOE Position               */
#define UART0_LSR_FIFOE_Msk                   (0x01UL << UART0_LSR_FIFOE_Pos)                         /*!< UART0 LSR: FIFOE Mask                   */

/* ----------------------------------  UART0_SCR  --------------------------------- */
#define UART0_SCR_SCR_Pos                     0                                                       /*!< UART0 SCR: SCR Position                 */
#define UART0_SCR_SCR_Msk                     (0x000000ffUL << UART0_SCR_SCR_Pos)                     /*!< UART0 SCR: SCR Mask                     */

/* ----------------------------------  UART0_BFR  --------------------------------- */
#define UART0_BFR_BFR_Pos                     0                                                       /*!< UART0 BFR: BFR Position                 */
#define UART0_BFR_BFR_Msk                     (0x000000ffUL << UART0_BFR_BFR_Pos)                     /*!< UART0 BFR: BFR Mask                     */

/* ----------------------------------  UART0_DTR  --------------------------------- */
#define UART0_DTR_WAITVAL_Pos                 0                                                       /*!< UART0 DTR: WAITVAL Position             */
#define UART0_DTR_WAITVAL_Msk                 (0x03UL << UART0_DTR_WAITVAL_Pos)                       /*!< UART0 DTR: WAITVAL Mask                 */
#define UART0_DTR_TXINV_Pos                   4                                                       /*!< UART0 DTR: TXINV Position               */
#define UART0_DTR_TXINV_Msk                   (0x01UL << UART0_DTR_TXINV_Pos)                         /*!< UART0 DTR: TXINV Mask                   */
#define UART0_DTR_RXINV_Pos                   5                                                       /*!< UART0 DTR: RXINV Position               */
#define UART0_DTR_RXINV_Msk                   (0x01UL << UART0_DTR_RXINV_Pos)                         /*!< UART0 DTR: RXINV Mask                   */
#define UART0_DTR_DMS_Pos                     6                                                       /*!< UART0 DTR: DMS Position                 */
#define UART0_DTR_DMS_Msk                     (0x01UL << UART0_DTR_DMS_Pos)                           /*!< UART0 DTR: DMS Mask                     */
#define UART0_DTR_SMS_Pos                     7                                                       /*!< UART0 DTR: SMS Position                 */
#define UART0_DTR_SMS_Msk                     (0x01UL << UART0_DTR_SMS_Pos)                           /*!< UART0 DTR: SMS Mask                     */


/* ================================================================================ */
/* ================         struct 'UART1' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  UART1_DLL  --------------------------------- */
#define UART1_DLL_DLL_Pos                     0                                                       /*!< UART1 DLL: DLL Position                 */
#define UART1_DLL_DLL_Msk                     (0x000000ffUL << UART1_DLL_DLL_Pos)                     /*!< UART1 DLL: DLL Mask                     */

/* ----------------------------------  UART1_THR  --------------------------------- */
#define UART1_THR_THR_Pos                     0                                                       /*!< UART1 THR: THR Position                 */
#define UART1_THR_THR_Msk                     (0x000000ffUL << UART1_THR_THR_Pos)                     /*!< UART1 THR: THR Mask                     */

/* ----------------------------------  UART1_RBR  --------------------------------- */
#define UART1_RBR_RBR_Pos                     0                                                       /*!< UART1 RBR: RBR Position                 */
#define UART1_RBR_RBR_Msk                     (0x000000ffUL << UART1_RBR_RBR_Pos)                     /*!< UART1 RBR: RBR Mask                     */

/* ----------------------------------  UART1_IER  --------------------------------- */
#define UART1_IER_DRIE_Pos                    0                                                       /*!< UART1 IER: DRIE Position                */
#define UART1_IER_DRIE_Msk                    (0x01UL << UART1_IER_DRIE_Pos)                          /*!< UART1 IER: DRIE Mask                    */
#define UART1_IER_THREIE_Pos                  1                                                       /*!< UART1 IER: THREIE Position              */
#define UART1_IER_THREIE_Msk                  (0x01UL << UART1_IER_THREIE_Pos)                        /*!< UART1 IER: THREIE Mask                  */
#define UART1_IER_RLSIE_Pos                   2                                                       /*!< UART1 IER: RLSIE Position               */
#define UART1_IER_RLSIE_Msk                   (0x01UL << UART1_IER_RLSIE_Pos)                         /*!< UART1 IER: RLSIE Mask                   */
#define UART1_IER_TEMTIE_Pos                  3                                                       /*!< UART1 IER: TEMTIE Position              */
#define UART1_IER_TEMTIE_Msk                  (0x01UL << UART1_IER_TEMTIE_Pos)                        /*!< UART1 IER: TEMTIE Mask                  */

/* ----------------------------------  UART1_DLM  --------------------------------- */
#define UART1_DLM_DLM_Pos                     0                                                       /*!< UART1 DLM: DLM Position                 */
#define UART1_DLM_DLM_Msk                     (0x000000ffUL << UART1_DLM_DLM_Pos)                     /*!< UART1 DLM: DLM Mask                     */

/* ----------------------------------  UART1_FCR  --------------------------------- */
#define UART1_FCR_FIFOEN_Pos                  0                                                       /*!< UART1 FCR: FIFOEN Position              */
#define UART1_FCR_FIFOEN_Msk                  (0x01UL << UART1_FCR_FIFOEN_Pos)                        /*!< UART1 FCR: FIFOEN Mask                  */
#define UART1_FCR_FCR1_Pos                    1                                                       /*!< UART1 FCR: FCR1 Position                */
#define UART1_FCR_FCR1_Msk                    (0x01UL << UART1_FCR_FCR1_Pos)                          /*!< UART1 FCR: FCR1 Mask                    */
#define UART1_FCR_FCR2_Pos                    2                                                       /*!< UART1 FCR: FCR2 Position                */
#define UART1_FCR_FCR2_Msk                    (0x01UL << UART1_FCR_FCR2_Pos)                          /*!< UART1 FCR: FCR2 Mask                    */
#define UART1_FCR_FIFODEPTH_Pos               6                                                       /*!< UART1 FCR: FIFODEPTH Position           */
#define UART1_FCR_FIFODEPTH_Msk               (0x03UL << UART1_FCR_FIFODEPTH_Pos)                     /*!< UART1 FCR: FIFODEPTH Mask               */

/* ----------------------------------  UART1_IIR  --------------------------------- */
#define UART1_IIR_IPEN_Pos                    0                                                       /*!< UART1 IIR: IPEN Position                */
#define UART1_IIR_IPEN_Msk                    (0x01UL << UART1_IIR_IPEN_Pos)                          /*!< UART1 IIR: IPEN Mask                    */
#define UART1_IIR_IID_FID_Pos                 1                                                       /*!< UART1 IIR: IID_FID Position             */
#define UART1_IIR_IID_FID_Msk                 (0x07UL << UART1_IIR_IID_FID_Pos)                       /*!< UART1 IIR: IID_FID Mask                 */
#define UART1_IIR_XMITE_Pos                   4                                                       /*!< UART1 IIR: XMITE Position               */
#define UART1_IIR_XMITE_Msk                   (0x01UL << UART1_IIR_XMITE_Pos)                         /*!< UART1 IIR: XMITE Mask                   */
#define UART1_IIR_FIFO_Pos                    6                                                       /*!< UART1 IIR: FIFO Position                */
#define UART1_IIR_FIFO_Msk                    (0x03UL << UART1_IIR_FIFO_Pos)                          /*!< UART1 IIR: FIFO Mask                    */

/* ----------------------------------  UART1_LCR  --------------------------------- */
#define UART1_LCR_DLEN_Pos                    0                                                       /*!< UART1 LCR: DLEN Position                */
#define UART1_LCR_DLEN_Msk                    (0x03UL << UART1_LCR_DLEN_Pos)                          /*!< UART1 LCR: DLEN Mask                    */
#define UART1_LCR_STOPBIT_Pos                 2                                                       /*!< UART1 LCR: STOPBIT Position             */
#define UART1_LCR_STOPBIT_Msk                 (0x01UL << UART1_LCR_STOPBIT_Pos)                       /*!< UART1 LCR: STOPBIT Mask                 */
#define UART1_LCR_PEN_Pos                     3                                                       /*!< UART1 LCR: PEN Position                 */
#define UART1_LCR_PEN_Msk                     (0x01UL << UART1_LCR_PEN_Pos)                           /*!< UART1 LCR: PEN Mask                     */
#define UART1_LCR_PARITY_Pos                  4                                                       /*!< UART1 LCR: PARITY Position              */
#define UART1_LCR_PARITY_Msk                  (0x01UL << UART1_LCR_PARITY_Pos)                        /*!< UART1 LCR: PARITY Mask                  */
#define UART1_LCR_STICKP_Pos                  5                                                       /*!< UART1 LCR: STICKP Position              */
#define UART1_LCR_STICKP_Msk                  (0x01UL << UART1_LCR_STICKP_Pos)                        /*!< UART1 LCR: STICKP Mask                  */
#define UART1_LCR_BREAK_Pos                   6                                                       /*!< UART1 LCR: BREAK Position               */
#define UART1_LCR_BREAK_Msk                   (0x01UL << UART1_LCR_BREAK_Pos)                         /*!< UART1 LCR: BREAK Mask                   */
#define UART1_LCR_DLAB_Pos                    7                                                       /*!< UART1 LCR: DLAB Position                */
#define UART1_LCR_DLAB_Msk                    (0x01UL << UART1_LCR_DLAB_Pos)                          /*!< UART1 LCR: DLAB Mask                    */

/* ----------------------------------  UART1_LSR  --------------------------------- */
#define UART1_LSR_DR_Pos                      0                                                       /*!< UART1 LSR: DR Position                  */
#define UART1_LSR_DR_Msk                      (0x01UL << UART1_LSR_DR_Pos)                            /*!< UART1 LSR: DR Mask                      */
#define UART1_LSR_OE_Pos                      1                                                       /*!< UART1 LSR: OE Position                  */
#define UART1_LSR_OE_Msk                      (0x01UL << UART1_LSR_OE_Pos)                            /*!< UART1 LSR: OE Mask                      */
#define UART1_LSR_PE_Pos                      2                                                       /*!< UART1 LSR: PE Position                  */
#define UART1_LSR_PE_Msk                      (0x01UL << UART1_LSR_PE_Pos)                            /*!< UART1 LSR: PE Mask                      */
#define UART1_LSR_FE_Pos                      3                                                       /*!< UART1 LSR: FE Position                  */
#define UART1_LSR_FE_Msk                      (0x01UL << UART1_LSR_FE_Pos)                            /*!< UART1 LSR: FE Mask                      */
#define UART1_LSR_BI_Pos                      4                                                       /*!< UART1 LSR: BI Position                  */
#define UART1_LSR_BI_Msk                      (0x01UL << UART1_LSR_BI_Pos)                            /*!< UART1 LSR: BI Mask                      */
#define UART1_LSR_THRE_Pos                    5                                                       /*!< UART1 LSR: THRE Position                */
#define UART1_LSR_THRE_Msk                    (0x01UL << UART1_LSR_THRE_Pos)                          /*!< UART1 LSR: THRE Mask                    */
#define UART1_LSR_TEMT_Pos                    6                                                       /*!< UART1 LSR: TEMT Position                */
#define UART1_LSR_TEMT_Msk                    (0x01UL << UART1_LSR_TEMT_Pos)                          /*!< UART1 LSR: TEMT Mask                    */
#define UART1_LSR_FIFOE_Pos                   7                                                       /*!< UART1 LSR: FIFOE Position               */
#define UART1_LSR_FIFOE_Msk                   (0x01UL << UART1_LSR_FIFOE_Pos)                         /*!< UART1 LSR: FIFOE Mask                   */

/* ----------------------------------  UART1_SCR  --------------------------------- */
#define UART1_SCR_SCR_Pos                     0                                                       /*!< UART1 SCR: SCR Position                 */
#define UART1_SCR_SCR_Msk                     (0x000000ffUL << UART1_SCR_SCR_Pos)                     /*!< UART1 SCR: SCR Mask                     */

/* ----------------------------------  UART1_BFR  --------------------------------- */
#define UART1_BFR_BFR_Pos                     0                                                       /*!< UART1 BFR: BFR Position                 */
#define UART1_BFR_BFR_Msk                     (0x000000ffUL << UART1_BFR_BFR_Pos)                     /*!< UART1 BFR: BFR Mask                     */

/* ----------------------------------  UART1_DTR  --------------------------------- */
#define UART1_DTR_WAITVAL_Pos                 0                                                       /*!< UART1 DTR: WAITVAL Position             */
#define UART1_DTR_WAITVAL_Msk                 (0x03UL << UART1_DTR_WAITVAL_Pos)                       /*!< UART1 DTR: WAITVAL Mask                 */
#define UART1_DTR_TXINV_Pos                   4                                                       /*!< UART1 DTR: TXINV Position               */
#define UART1_DTR_TXINV_Msk                   (0x01UL << UART1_DTR_TXINV_Pos)                         /*!< UART1 DTR: TXINV Mask                   */
#define UART1_DTR_RXINV_Pos                   5                                                       /*!< UART1 DTR: RXINV Position               */
#define UART1_DTR_RXINV_Msk                   (0x01UL << UART1_DTR_RXINV_Pos)                         /*!< UART1 DTR: RXINV Mask                   */
#define UART1_DTR_DMS_Pos                     6                                                       /*!< UART1 DTR: DMS Position                 */
#define UART1_DTR_DMS_Msk                     (0x01UL << UART1_DTR_DMS_Pos)                           /*!< UART1 DTR: DMS Mask                     */
#define UART1_DTR_SMS_Pos                     7                                                       /*!< UART1 DTR: SMS Position                 */
#define UART1_DTR_SMS_Msk                     (0x01UL << UART1_DTR_SMS_Pos)                           /*!< UART1 DTR: SMS Mask                     */


/* ================================================================================ */
/* ================         struct 'UART2' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  UART2_DLL  --------------------------------- */
#define UART2_DLL_DLL_Pos                     0                                                       /*!< UART2 DLL: DLL Position                 */
#define UART2_DLL_DLL_Msk                     (0x000000ffUL << UART2_DLL_DLL_Pos)                     /*!< UART2 DLL: DLL Mask                     */

/* ----------------------------------  UART2_THR  --------------------------------- */
#define UART2_THR_THR_Pos                     0                                                       /*!< UART2 THR: THR Position                 */
#define UART2_THR_THR_Msk                     (0x000000ffUL << UART2_THR_THR_Pos)                     /*!< UART2 THR: THR Mask                     */

/* ----------------------------------  UART2_RBR  --------------------------------- */
#define UART2_RBR_RBR_Pos                     0                                                       /*!< UART2 RBR: RBR Position                 */
#define UART2_RBR_RBR_Msk                     (0x000000ffUL << UART2_RBR_RBR_Pos)                     /*!< UART2 RBR: RBR Mask                     */

/* ----------------------------------  UART2_IER  --------------------------------- */
#define UART2_IER_DRIE_Pos                    0                                                       /*!< UART2 IER: DRIE Position                */
#define UART2_IER_DRIE_Msk                    (0x01UL << UART2_IER_DRIE_Pos)                          /*!< UART2 IER: DRIE Mask                    */
#define UART2_IER_THREIE_Pos                  1                                                       /*!< UART2 IER: THREIE Position              */
#define UART2_IER_THREIE_Msk                  (0x01UL << UART2_IER_THREIE_Pos)                        /*!< UART2 IER: THREIE Mask                  */
#define UART2_IER_RLSIE_Pos                   2                                                       /*!< UART2 IER: RLSIE Position               */
#define UART2_IER_RLSIE_Msk                   (0x01UL << UART2_IER_RLSIE_Pos)                         /*!< UART2 IER: RLSIE Mask                   */
#define UART2_IER_TEMTIE_Pos                  3                                                       /*!< UART2 IER: TEMTIE Position              */
#define UART2_IER_TEMTIE_Msk                  (0x01UL << UART2_IER_TEMTIE_Pos)                        /*!< UART2 IER: TEMTIE Mask                  */

/* ----------------------------------  UART2_DLM  --------------------------------- */
#define UART2_DLM_DLM_Pos                     0                                                       /*!< UART2 DLM: DLM Position                 */
#define UART2_DLM_DLM_Msk                     (0x000000ffUL << UART2_DLM_DLM_Pos)                     /*!< UART2 DLM: DLM Mask                     */

/* ----------------------------------  UART2_FCR  --------------------------------- */
#define UART2_FCR_FIFOEN_Pos                  0                                                       /*!< UART2 FCR: FIFOEN Position              */
#define UART2_FCR_FIFOEN_Msk                  (0x01UL << UART2_FCR_FIFOEN_Pos)                        /*!< UART2 FCR: FIFOEN Mask                  */
#define UART2_FCR_FCR1_Pos                    1                                                       /*!< UART2 FCR: FCR1 Position                */
#define UART2_FCR_FCR1_Msk                    (0x01UL << UART2_FCR_FCR1_Pos)                          /*!< UART2 FCR: FCR1 Mask                    */
#define UART2_FCR_FCR2_Pos                    2                                                       /*!< UART2 FCR: FCR2 Position                */
#define UART2_FCR_FCR2_Msk                    (0x01UL << UART2_FCR_FCR2_Pos)                          /*!< UART2 FCR: FCR2 Mask                    */
#define UART2_FCR_FIFODEPTH_Pos               6                                                       /*!< UART2 FCR: FIFODEPTH Position           */
#define UART2_FCR_FIFODEPTH_Msk               (0x03UL << UART2_FCR_FIFODEPTH_Pos)                     /*!< UART2 FCR: FIFODEPTH Mask               */

/* ----------------------------------  UART2_IIR  --------------------------------- */
#define UART2_IIR_IPEN_Pos                    0                                                       /*!< UART2 IIR: IPEN Position                */
#define UART2_IIR_IPEN_Msk                    (0x01UL << UART2_IIR_IPEN_Pos)                          /*!< UART2 IIR: IPEN Mask                    */
#define UART2_IIR_IID_FID_Pos                 1                                                       /*!< UART2 IIR: IID_FID Position             */
#define UART2_IIR_IID_FID_Msk                 (0x07UL << UART2_IIR_IID_FID_Pos)                       /*!< UART2 IIR: IID_FID Mask                 */
#define UART2_IIR_XMITE_Pos                   4                                                       /*!< UART2 IIR: XMITE Position               */
#define UART2_IIR_XMITE_Msk                   (0x01UL << UART2_IIR_XMITE_Pos)                         /*!< UART2 IIR: XMITE Mask                   */
#define UART2_IIR_FIFO_Pos                    6                                                       /*!< UART2 IIR: FIFO Position                */
#define UART2_IIR_FIFO_Msk                    (0x03UL << UART2_IIR_FIFO_Pos)                          /*!< UART2 IIR: FIFO Mask                    */

/* ----------------------------------  UART2_LCR  --------------------------------- */
#define UART2_LCR_DLEN_Pos                    0                                                       /*!< UART2 LCR: DLEN Position                */
#define UART2_LCR_DLEN_Msk                    (0x03UL << UART2_LCR_DLEN_Pos)                          /*!< UART2 LCR: DLEN Mask                    */
#define UART2_LCR_STOPBIT_Pos                 2                                                       /*!< UART2 LCR: STOPBIT Position             */
#define UART2_LCR_STOPBIT_Msk                 (0x01UL << UART2_LCR_STOPBIT_Pos)                       /*!< UART2 LCR: STOPBIT Mask                 */
#define UART2_LCR_PEN_Pos                     3                                                       /*!< UART2 LCR: PEN Position                 */
#define UART2_LCR_PEN_Msk                     (0x01UL << UART2_LCR_PEN_Pos)                           /*!< UART2 LCR: PEN Mask                     */
#define UART2_LCR_PARITY_Pos                  4                                                       /*!< UART2 LCR: PARITY Position              */
#define UART2_LCR_PARITY_Msk                  (0x01UL << UART2_LCR_PARITY_Pos)                        /*!< UART2 LCR: PARITY Mask                  */
#define UART2_LCR_STICKP_Pos                  5                                                       /*!< UART2 LCR: STICKP Position              */
#define UART2_LCR_STICKP_Msk                  (0x01UL << UART2_LCR_STICKP_Pos)                        /*!< UART2 LCR: STICKP Mask                  */
#define UART2_LCR_BREAK_Pos                   6                                                       /*!< UART2 LCR: BREAK Position               */
#define UART2_LCR_BREAK_Msk                   (0x01UL << UART2_LCR_BREAK_Pos)                         /*!< UART2 LCR: BREAK Mask                   */
#define UART2_LCR_DLAB_Pos                    7                                                       /*!< UART2 LCR: DLAB Position                */
#define UART2_LCR_DLAB_Msk                    (0x01UL << UART2_LCR_DLAB_Pos)                          /*!< UART2 LCR: DLAB Mask                    */

/* ----------------------------------  UART2_LSR  --------------------------------- */
#define UART2_LSR_DR_Pos                      0                                                       /*!< UART2 LSR: DR Position                  */
#define UART2_LSR_DR_Msk                      (0x01UL << UART2_LSR_DR_Pos)                            /*!< UART2 LSR: DR Mask                      */
#define UART2_LSR_OE_Pos                      1                                                       /*!< UART2 LSR: OE Position                  */
#define UART2_LSR_OE_Msk                      (0x01UL << UART2_LSR_OE_Pos)                            /*!< UART2 LSR: OE Mask                      */
#define UART2_LSR_PE_Pos                      2                                                       /*!< UART2 LSR: PE Position                  */
#define UART2_LSR_PE_Msk                      (0x01UL << UART2_LSR_PE_Pos)                            /*!< UART2 LSR: PE Mask                      */
#define UART2_LSR_FE_Pos                      3                                                       /*!< UART2 LSR: FE Position                  */
#define UART2_LSR_FE_Msk                      (0x01UL << UART2_LSR_FE_Pos)                            /*!< UART2 LSR: FE Mask                      */
#define UART2_LSR_BI_Pos                      4                                                       /*!< UART2 LSR: BI Position                  */
#define UART2_LSR_BI_Msk                      (0x01UL << UART2_LSR_BI_Pos)                            /*!< UART2 LSR: BI Mask                      */
#define UART2_LSR_THRE_Pos                    5                                                       /*!< UART2 LSR: THRE Position                */
#define UART2_LSR_THRE_Msk                    (0x01UL << UART2_LSR_THRE_Pos)                          /*!< UART2 LSR: THRE Mask                    */
#define UART2_LSR_TEMT_Pos                    6                                                       /*!< UART2 LSR: TEMT Position                */
#define UART2_LSR_TEMT_Msk                    (0x01UL << UART2_LSR_TEMT_Pos)                          /*!< UART2 LSR: TEMT Mask                    */
#define UART2_LSR_FIFOE_Pos                   7                                                       /*!< UART2 LSR: FIFOE Position               */
#define UART2_LSR_FIFOE_Msk                   (0x01UL << UART2_LSR_FIFOE_Pos)                         /*!< UART2 LSR: FIFOE Mask                   */

/* ----------------------------------  UART2_SCR  --------------------------------- */
#define UART2_SCR_SCR_Pos                     0                                                       /*!< UART2 SCR: SCR Position                 */
#define UART2_SCR_SCR_Msk                     (0x000000ffUL << UART2_SCR_SCR_Pos)                     /*!< UART2 SCR: SCR Mask                     */

/* ----------------------------------  UART2_BFR  --------------------------------- */
#define UART2_BFR_BFR_Pos                     0                                                       /*!< UART2 BFR: BFR Position                 */
#define UART2_BFR_BFR_Msk                     (0x000000ffUL << UART2_BFR_BFR_Pos)                     /*!< UART2 BFR: BFR Mask                     */

/* ----------------------------------  UART2_DTR  --------------------------------- */
#define UART2_DTR_WAITVAL_Pos                 0                                                       /*!< UART2 DTR: WAITVAL Position             */
#define UART2_DTR_WAITVAL_Msk                 (0x03UL << UART2_DTR_WAITVAL_Pos)                       /*!< UART2 DTR: WAITVAL Mask                 */
#define UART2_DTR_TXINV_Pos                   4                                                       /*!< UART2 DTR: TXINV Position               */
#define UART2_DTR_TXINV_Msk                   (0x01UL << UART2_DTR_TXINV_Pos)                         /*!< UART2 DTR: TXINV Mask                   */
#define UART2_DTR_RXINV_Pos                   5                                                       /*!< UART2 DTR: RXINV Position               */
#define UART2_DTR_RXINV_Msk                   (0x01UL << UART2_DTR_RXINV_Pos)                         /*!< UART2 DTR: RXINV Mask                   */
#define UART2_DTR_DMS_Pos                     6                                                       /*!< UART2 DTR: DMS Position                 */
#define UART2_DTR_DMS_Msk                     (0x01UL << UART2_DTR_DMS_Pos)                           /*!< UART2 DTR: DMS Mask                     */
#define UART2_DTR_SMS_Pos                     7                                                       /*!< UART2 DTR: SMS Position                 */
#define UART2_DTR_SMS_Msk                     (0x01UL << UART2_DTR_SMS_Pos)                           /*!< UART2 DTR: SMS Mask                     */


/* ================================================================================ */
/* ================         struct 'UART3' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  UART3_DLL  --------------------------------- */
#define UART3_DLL_DLL_Pos                     0                                                       /*!< UART3 DLL: DLL Position                 */
#define UART3_DLL_DLL_Msk                     (0x000000ffUL << UART3_DLL_DLL_Pos)                     /*!< UART3 DLL: DLL Mask                     */

/* ----------------------------------  UART3_THR  --------------------------------- */
#define UART3_THR_THR_Pos                     0                                                       /*!< UART3 THR: THR Position                 */
#define UART3_THR_THR_Msk                     (0x000000ffUL << UART3_THR_THR_Pos)                     /*!< UART3 THR: THR Mask                     */

/* ----------------------------------  UART3_RBR  --------------------------------- */
#define UART3_RBR_RBR_Pos                     0                                                       /*!< UART3 RBR: RBR Position                 */
#define UART3_RBR_RBR_Msk                     (0x000000ffUL << UART3_RBR_RBR_Pos)                     /*!< UART3 RBR: RBR Mask                     */

/* ----------------------------------  UART3_IER  --------------------------------- */
#define UART3_IER_DRIE_Pos                    0                                                       /*!< UART3 IER: DRIE Position                */
#define UART3_IER_DRIE_Msk                    (0x01UL << UART3_IER_DRIE_Pos)                          /*!< UART3 IER: DRIE Mask                    */
#define UART3_IER_THREIE_Pos                  1                                                       /*!< UART3 IER: THREIE Position              */
#define UART3_IER_THREIE_Msk                  (0x01UL << UART3_IER_THREIE_Pos)                        /*!< UART3 IER: THREIE Mask                  */
#define UART3_IER_RLSIE_Pos                   2                                                       /*!< UART3 IER: RLSIE Position               */
#define UART3_IER_RLSIE_Msk                   (0x01UL << UART3_IER_RLSIE_Pos)                         /*!< UART3 IER: RLSIE Mask                   */
#define UART3_IER_TEMTIE_Pos                  3                                                       /*!< UART3 IER: TEMTIE Position              */
#define UART3_IER_TEMTIE_Msk                  (0x01UL << UART3_IER_TEMTIE_Pos)                        /*!< UART3 IER: TEMTIE Mask                  */

/* ----------------------------------  UART3_DLM  --------------------------------- */
#define UART3_DLM_DLM_Pos                     0                                                       /*!< UART3 DLM: DLM Position                 */
#define UART3_DLM_DLM_Msk                     (0x000000ffUL << UART3_DLM_DLM_Pos)                     /*!< UART3 DLM: DLM Mask                     */

/* ----------------------------------  UART3_FCR  --------------------------------- */
#define UART3_FCR_FIFOEN_Pos                  0                                                       /*!< UART3 FCR: FIFOEN Position              */
#define UART3_FCR_FIFOEN_Msk                  (0x01UL << UART3_FCR_FIFOEN_Pos)                        /*!< UART3 FCR: FIFOEN Mask                  */
#define UART3_FCR_FCR1_Pos                    1                                                       /*!< UART3 FCR: FCR1 Position                */
#define UART3_FCR_FCR1_Msk                    (0x01UL << UART3_FCR_FCR1_Pos)                          /*!< UART3 FCR: FCR1 Mask                    */
#define UART3_FCR_FCR2_Pos                    2                                                       /*!< UART3 FCR: FCR2 Position                */
#define UART3_FCR_FCR2_Msk                    (0x01UL << UART3_FCR_FCR2_Pos)                          /*!< UART3 FCR: FCR2 Mask                    */
#define UART3_FCR_FIFODEPTH_Pos               6                                                       /*!< UART3 FCR: FIFODEPTH Position           */
#define UART3_FCR_FIFODEPTH_Msk               (0x03UL << UART3_FCR_FIFODEPTH_Pos)                     /*!< UART3 FCR: FIFODEPTH Mask               */

/* ----------------------------------  UART3_IIR  --------------------------------- */
#define UART3_IIR_IPEN_Pos                    0                                                       /*!< UART3 IIR: IPEN Position                */
#define UART3_IIR_IPEN_Msk                    (0x01UL << UART3_IIR_IPEN_Pos)                          /*!< UART3 IIR: IPEN Mask                    */
#define UART3_IIR_IID_FID_Pos                 1                                                       /*!< UART3 IIR: IID_FID Position             */
#define UART3_IIR_IID_FID_Msk                 (0x07UL << UART3_IIR_IID_FID_Pos)                       /*!< UART3 IIR: IID_FID Mask                 */
#define UART3_IIR_XMITE_Pos                   4                                                       /*!< UART3 IIR: XMITE Position               */
#define UART3_IIR_XMITE_Msk                   (0x01UL << UART3_IIR_XMITE_Pos)                         /*!< UART3 IIR: XMITE Mask                   */
#define UART3_IIR_FIFO_Pos                    6                                                       /*!< UART3 IIR: FIFO Position                */
#define UART3_IIR_FIFO_Msk                    (0x03UL << UART3_IIR_FIFO_Pos)                          /*!< UART3 IIR: FIFO Mask                    */

/* ----------------------------------  UART3_LCR  --------------------------------- */
#define UART3_LCR_DLEN_Pos                    0                                                       /*!< UART3 LCR: DLEN Position                */
#define UART3_LCR_DLEN_Msk                    (0x03UL << UART3_LCR_DLEN_Pos)                          /*!< UART3 LCR: DLEN Mask                    */
#define UART3_LCR_STOPBIT_Pos                 2                                                       /*!< UART3 LCR: STOPBIT Position             */
#define UART3_LCR_STOPBIT_Msk                 (0x01UL << UART3_LCR_STOPBIT_Pos)                       /*!< UART3 LCR: STOPBIT Mask                 */
#define UART3_LCR_PEN_Pos                     3                                                       /*!< UART3 LCR: PEN Position                 */
#define UART3_LCR_PEN_Msk                     (0x01UL << UART3_LCR_PEN_Pos)                           /*!< UART3 LCR: PEN Mask                     */
#define UART3_LCR_PARITY_Pos                  4                                                       /*!< UART3 LCR: PARITY Position              */
#define UART3_LCR_PARITY_Msk                  (0x01UL << UART3_LCR_PARITY_Pos)                        /*!< UART3 LCR: PARITY Mask                  */
#define UART3_LCR_STICKP_Pos                  5                                                       /*!< UART3 LCR: STICKP Position              */
#define UART3_LCR_STICKP_Msk                  (0x01UL << UART3_LCR_STICKP_Pos)                        /*!< UART3 LCR: STICKP Mask                  */
#define UART3_LCR_BREAK_Pos                   6                                                       /*!< UART3 LCR: BREAK Position               */
#define UART3_LCR_BREAK_Msk                   (0x01UL << UART3_LCR_BREAK_Pos)                         /*!< UART3 LCR: BREAK Mask                   */
#define UART3_LCR_DLAB_Pos                    7                                                       /*!< UART3 LCR: DLAB Position                */
#define UART3_LCR_DLAB_Msk                    (0x01UL << UART3_LCR_DLAB_Pos)                          /*!< UART3 LCR: DLAB Mask                    */

/* ----------------------------------  UART3_LSR  --------------------------------- */
#define UART3_LSR_DR_Pos                      0                                                       /*!< UART3 LSR: DR Position                  */
#define UART3_LSR_DR_Msk                      (0x01UL << UART3_LSR_DR_Pos)                            /*!< UART3 LSR: DR Mask                      */
#define UART3_LSR_OE_Pos                      1                                                       /*!< UART3 LSR: OE Position                  */
#define UART3_LSR_OE_Msk                      (0x01UL << UART3_LSR_OE_Pos)                            /*!< UART3 LSR: OE Mask                      */
#define UART3_LSR_PE_Pos                      2                                                       /*!< UART3 LSR: PE Position                  */
#define UART3_LSR_PE_Msk                      (0x01UL << UART3_LSR_PE_Pos)                            /*!< UART3 LSR: PE Mask                      */
#define UART3_LSR_FE_Pos                      3                                                       /*!< UART3 LSR: FE Position                  */
#define UART3_LSR_FE_Msk                      (0x01UL << UART3_LSR_FE_Pos)                            /*!< UART3 LSR: FE Mask                      */
#define UART3_LSR_BI_Pos                      4                                                       /*!< UART3 LSR: BI Position                  */
#define UART3_LSR_BI_Msk                      (0x01UL << UART3_LSR_BI_Pos)                            /*!< UART3 LSR: BI Mask                      */
#define UART3_LSR_THRE_Pos                    5                                                       /*!< UART3 LSR: THRE Position                */
#define UART3_LSR_THRE_Msk                    (0x01UL << UART3_LSR_THRE_Pos)                          /*!< UART3 LSR: THRE Mask                    */
#define UART3_LSR_TEMT_Pos                    6                                                       /*!< UART3 LSR: TEMT Position                */
#define UART3_LSR_TEMT_Msk                    (0x01UL << UART3_LSR_TEMT_Pos)                          /*!< UART3 LSR: TEMT Mask                    */
#define UART3_LSR_FIFOE_Pos                   7                                                       /*!< UART3 LSR: FIFOE Position               */
#define UART3_LSR_FIFOE_Msk                   (0x01UL << UART3_LSR_FIFOE_Pos)                         /*!< UART3 LSR: FIFOE Mask                   */

/* ----------------------------------  UART3_SCR  --------------------------------- */
#define UART3_SCR_SCR_Pos                     0                                                       /*!< UART3 SCR: SCR Position                 */
#define UART3_SCR_SCR_Msk                     (0x000000ffUL << UART3_SCR_SCR_Pos)                     /*!< UART3 SCR: SCR Mask                     */

/* ----------------------------------  UART3_BFR  --------------------------------- */
#define UART3_BFR_BFR_Pos                     0                                                       /*!< UART3 BFR: BFR Position                 */
#define UART3_BFR_BFR_Msk                     (0x000000ffUL << UART3_BFR_BFR_Pos)                     /*!< UART3 BFR: BFR Mask                     */

/* ----------------------------------  UART3_DTR  --------------------------------- */
#define UART3_DTR_WAITVAL_Pos                 0                                                       /*!< UART3 DTR: WAITVAL Position             */
#define UART3_DTR_WAITVAL_Msk                 (0x03UL << UART3_DTR_WAITVAL_Pos)                       /*!< UART3 DTR: WAITVAL Mask                 */
#define UART3_DTR_TXINV_Pos                   4                                                       /*!< UART3 DTR: TXINV Position               */
#define UART3_DTR_TXINV_Msk                   (0x01UL << UART3_DTR_TXINV_Pos)                         /*!< UART3 DTR: TXINV Mask                   */
#define UART3_DTR_RXINV_Pos                   5                                                       /*!< UART3 DTR: RXINV Position               */
#define UART3_DTR_RXINV_Msk                   (0x01UL << UART3_DTR_RXINV_Pos)                         /*!< UART3 DTR: RXINV Mask                   */
#define UART3_DTR_DMS_Pos                     6                                                       /*!< UART3 DTR: DMS Position                 */
#define UART3_DTR_DMS_Msk                     (0x01UL << UART3_DTR_DMS_Pos)                           /*!< UART3 DTR: DMS Mask                     */
#define UART3_DTR_SMS_Pos                     7                                                       /*!< UART3 DTR: SMS Position                 */
#define UART3_DTR_SMS_Msk                     (0x01UL << UART3_DTR_SMS_Pos)                           /*!< UART3 DTR: SMS Mask                     */


/* ================================================================================ */
/* ================          struct 'SPI0' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  SPI0_TDR  ---------------------------------- */
#define SPI0_TDR_TDR_Pos                      0                                                       /*!< SPI0 TDR: TDR Position                  */
#define SPI0_TDR_TDR_Msk                      (0x0001ffffUL << SPI0_TDR_TDR_Pos)                      /*!< SPI0 TDR: TDR Mask                      */

/* ----------------------------------  SPI0_RDR  ---------------------------------- */
#define SPI0_RDR_RDR_Pos                      0                                                       /*!< SPI0 RDR: RDR Position                  */
#define SPI0_RDR_RDR_Msk                      (0x0001ffffUL << SPI0_RDR_RDR_Pos)                      /*!< SPI0 RDR: RDR Mask                      */

/* -----------------------------------  SPI0_CR  ---------------------------------- */
#define SPI0_CR_BITSEL_Pos                    0                                                       /*!< SPI0 CR: BITSEL Position                */
#define SPI0_CR_BITSEL_Msk                    (0x03UL << SPI0_CR_BITSEL_Pos)                          /*!< SPI0 CR: BITSEL Mask                    */
#define SPI0_CR_CPOL_Pos                      2                                                       /*!< SPI0 CR: CPOL Position                  */
#define SPI0_CR_CPOL_Msk                      (0x01UL << SPI0_CR_CPOL_Pos)                            /*!< SPI0 CR: CPOL Mask                      */
#define SPI0_CR_CPHA_Pos                      3                                                       /*!< SPI0 CR: CPHA Position                  */
#define SPI0_CR_CPHA_Msk                      (0x01UL << SPI0_CR_CPHA_Pos)                            /*!< SPI0 CR: CPHA Mask                      */
#define SPI0_CR_MSBF_Pos                      4                                                       /*!< SPI0 CR: MSBF Position                  */
#define SPI0_CR_MSBF_Msk                      (0x01UL << SPI0_CR_MSBF_Pos)                            /*!< SPI0 CR: MSBF Mask                      */
#define SPI0_CR_MS_Pos                        5                                                       /*!< SPI0 CR: MS Position                    */
#define SPI0_CR_MS_Msk                        (0x01UL << SPI0_CR_MS_Pos)                              /*!< SPI0 CR: MS Mask                        */
#define SPI0_CR_SSPOL_Pos                     7                                                       /*!< SPI0 CR: SSPOL Position                 */
#define SPI0_CR_SSPOL_Msk                     (0x01UL << SPI0_CR_SSPOL_Pos)                           /*!< SPI0 CR: SSPOL Mask                     */
#define SPI0_CR_SSMO_Pos                      8                                                       /*!< SPI0 CR: SSMO Position                  */
#define SPI0_CR_SSMO_Msk                      (0x01UL << SPI0_CR_SSMO_Pos)                            /*!< SPI0 CR: SSMO Mask                      */
#define SPI0_CR_SSMASK_Pos                    9                                                       /*!< SPI0 CR: SSMASK Position                */
#define SPI0_CR_SSMASK_Msk                    (0x01UL << SPI0_CR_SSMASK_Pos)                          /*!< SPI0 CR: SSMASK Mask                    */
#define SPI0_CR_LBE_Pos                       10                                                      /*!< SPI0 CR: LBE Position                   */
#define SPI0_CR_LBE_Msk                       (0x01UL << SPI0_CR_LBE_Pos)                             /*!< SPI0 CR: LBE Mask                       */
#define SPI0_CR_SSOUT_Pos                     11                                                      /*!< SPI0 CR: SSOUT Position                 */
#define SPI0_CR_SSOUT_Msk                     (0x01UL << SPI0_CR_SSOUT_Pos)                           /*!< SPI0 CR: SSOUT Mask                     */
#define SPI0_CR_SSMODE_Pos                    12                                                      /*!< SPI0 CR: SSMODE Position                */
#define SPI0_CR_SSMODE_Msk                    (0x01UL << SPI0_CR_SSMODE_Pos)                          /*!< SPI0 CR: SSMODE Mask                    */
#define SPI0_CR_RXIE_Pos                      13                                                      /*!< SPI0 CR: RXIE Position                  */
#define SPI0_CR_RXIE_Msk                      (0x01UL << SPI0_CR_RXIE_Pos)                            /*!< SPI0 CR: RXIE Mask                      */
#define SPI0_CR_TXIE_Pos                      14                                                      /*!< SPI0 CR: TXIE Position                  */
#define SPI0_CR_TXIE_Msk                      (0x01UL << SPI0_CR_TXIE_Pos)                            /*!< SPI0 CR: TXIE Mask                      */
#define SPI0_CR_SSCIE_Pos                     15                                                      /*!< SPI0 CR: SSCIE Position                 */
#define SPI0_CR_SSCIE_Msk                     (0x01UL << SPI0_CR_SSCIE_Pos)                           /*!< SPI0 CR: SSCIE Mask                     */
#define SPI0_CR_RXBC_Pos                      19                                                      /*!< SPI0 CR: RXBC Position                  */
#define SPI0_CR_RXBC_Msk                      (0x01UL << SPI0_CR_RXBC_Pos)                            /*!< SPI0 CR: RXBC Mask                      */
#define SPI0_CR_TXBC_Pos                      20                                                      /*!< SPI0 CR: TXBC Position                  */
#define SPI0_CR_TXBC_Msk                      (0x01UL << SPI0_CR_TXBC_Pos)                            /*!< SPI0 CR: TXBC Mask                      */

/* -----------------------------------  SPI0_SR  ---------------------------------- */
#define SPI0_SR_RRDY_Pos                      0                                                       /*!< SPI0 SR: RRDY Position                  */
#define SPI0_SR_RRDY_Msk                      (0x01UL << SPI0_SR_RRDY_Pos)                            /*!< SPI0 SR: RRDY Mask                      */
#define SPI0_SR_TRDY_Pos                      1                                                       /*!< SPI0 SR: TRDY Position                  */
#define SPI0_SR_TRDY_Msk                      (0x01UL << SPI0_SR_TRDY_Pos)                            /*!< SPI0 SR: TRDY Mask                      */
#define SPI0_SR_SBUSY_Pos                     2                                                       /*!< SPI0 SR: SBUSY Position                 */
#define SPI0_SR_SBUSY_Msk                     (0x01UL << SPI0_SR_SBUSY_Pos)                           /*!< SPI0 SR: SBUSY Mask                     */
#define SPI0_SR_UDRF_Pos                      3                                                       /*!< SPI0 SR: UDRF Position                  */
#define SPI0_SR_UDRF_Msk                      (0x01UL << SPI0_SR_UDRF_Pos)                            /*!< SPI0 SR: UDRF Mask                      */
#define SPI0_SR_OVRF_Pos                      4                                                       /*!< SPI0 SR: OVRF Position                  */
#define SPI0_SR_OVRF_Msk                      (0x01UL << SPI0_SR_OVRF_Pos)                            /*!< SPI0 SR: OVRF Mask                      */
#define SPI0_SR_SSON_Pos                      5                                                       /*!< SPI0 SR: SSON Position                  */
#define SPI0_SR_SSON_Msk                      (0x01UL << SPI0_SR_SSON_Pos)                            /*!< SPI0 SR: SSON Mask                      */
#define SPI0_SR_SSDET_Pos                     6                                                       /*!< SPI0 SR: SSDET Position                 */
#define SPI0_SR_SSDET_Msk                     (0x01UL << SPI0_SR_SSDET_Pos)                           /*!< SPI0 SR: SSDET Mask                     */

/* -----------------------------------  SPI0_BR  ---------------------------------- */
#define SPI0_BR_BR_Pos                        0                                                       /*!< SPI0 BR: BR Position                    */
#define SPI0_BR_BR_Msk                        (0x000000ffUL << SPI0_BR_BR_Pos)                        /*!< SPI0 BR: BR Mask                        */

/* -----------------------------------  SPI0_EN  ---------------------------------- */
#define SPI0_EN_ENABLE_Pos                    0                                                       /*!< SPI0 EN: ENABLE Position                */
#define SPI0_EN_ENABLE_Msk                    (0x01UL << SPI0_EN_ENABLE_Pos)                          /*!< SPI0 EN: ENABLE Mask                    */

/* -----------------------------------  SPI0_LR  ---------------------------------- */
#define SPI0_LR_STL_Pos                       0                                                       /*!< SPI0 LR: STL Position                   */
#define SPI0_LR_STL_Msk                       (0x01UL << SPI0_LR_STL_Pos)                             /*!< SPI0 LR: STL Mask                       */
#define SPI0_LR_BTL_Pos                       5                                                       /*!< SPI0 LR: BTL Position                   */
#define SPI0_LR_BTL_Msk                       (0x1fUL << SPI0_LR_BTL_Pos)                             /*!< SPI0 LR: BTL Mask                       */
#define SPI0_LR_SPL_Pos                       10                                                      /*!< SPI0 LR: SPL Position                   */
#define SPI0_LR_SPL_Msk                       (0x1fUL << SPI0_LR_SPL_Pos)                             /*!< SPI0 LR: SPL Mask                       */


/* ================================================================================ */
/* ================          struct 'SPI1' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  SPI1_RDR  ---------------------------------- */
#define SPI1_RDR_RDR_Pos                      0                                                       /*!< SPI1 RDR: RDR Position                  */
#define SPI1_RDR_RDR_Msk                      (0x0001ffffUL << SPI1_RDR_RDR_Pos)                      /*!< SPI1 RDR: RDR Mask                      */

/* ----------------------------------  SPI1_TDR  ---------------------------------- */
#define SPI1_TDR_TDR_Pos                      0                                                       /*!< SPI1 TDR: TDR Position                  */
#define SPI1_TDR_TDR_Msk                      (0x0001ffffUL << SPI1_TDR_TDR_Pos)                      /*!< SPI1 TDR: TDR Mask                      */

/* -----------------------------------  SPI1_CR  ---------------------------------- */
#define SPI1_CR_BITSEL_Pos                    0                                                       /*!< SPI1 CR: BITSEL Position                */
#define SPI1_CR_BITSEL_Msk                    (0x03UL << SPI1_CR_BITSEL_Pos)                          /*!< SPI1 CR: BITSEL Mask                    */
#define SPI1_CR_CPOL_Pos                      2                                                       /*!< SPI1 CR: CPOL Position                  */
#define SPI1_CR_CPOL_Msk                      (0x01UL << SPI1_CR_CPOL_Pos)                            /*!< SPI1 CR: CPOL Mask                      */
#define SPI1_CR_CPHA_Pos                      3                                                       /*!< SPI1 CR: CPHA Position                  */
#define SPI1_CR_CPHA_Msk                      (0x01UL << SPI1_CR_CPHA_Pos)                            /*!< SPI1 CR: CPHA Mask                      */
#define SPI1_CR_MSBF_Pos                      4                                                       /*!< SPI1 CR: MSBF Position                  */
#define SPI1_CR_MSBF_Msk                      (0x01UL << SPI1_CR_MSBF_Pos)                            /*!< SPI1 CR: MSBF Mask                      */
#define SPI1_CR_MS_Pos                        5                                                       /*!< SPI1 CR: MS Position                    */
#define SPI1_CR_MS_Msk                        (0x01UL << SPI1_CR_MS_Pos)                              /*!< SPI1 CR: MS Mask                        */
#define SPI1_CR_SSPOL_Pos                     7                                                       /*!< SPI1 CR: SSPOL Position                 */
#define SPI1_CR_SSPOL_Msk                     (0x01UL << SPI1_CR_SSPOL_Pos)                           /*!< SPI1 CR: SSPOL Mask                     */
#define SPI1_CR_SSMO_Pos                      8                                                       /*!< SPI1 CR: SSMO Position                  */
#define SPI1_CR_SSMO_Msk                      (0x01UL << SPI1_CR_SSMO_Pos)                            /*!< SPI1 CR: SSMO Mask                      */
#define SPI1_CR_SSMASK_Pos                    9                                                       /*!< SPI1 CR: SSMASK Position                */
#define SPI1_CR_SSMASK_Msk                    (0x01UL << SPI1_CR_SSMASK_Pos)                          /*!< SPI1 CR: SSMASK Mask                    */
#define SPI1_CR_LBE_Pos                       10                                                      /*!< SPI1 CR: LBE Position                   */
#define SPI1_CR_LBE_Msk                       (0x01UL << SPI1_CR_LBE_Pos)                             /*!< SPI1 CR: LBE Mask                       */
#define SPI1_CR_SSOUT_Pos                     11                                                      /*!< SPI1 CR: SSOUT Position                 */
#define SPI1_CR_SSOUT_Msk                     (0x01UL << SPI1_CR_SSOUT_Pos)                           /*!< SPI1 CR: SSOUT Mask                     */
#define SPI1_CR_SSMODE_Pos                    12                                                      /*!< SPI1 CR: SSMODE Position                */
#define SPI1_CR_SSMODE_Msk                    (0x01UL << SPI1_CR_SSMODE_Pos)                          /*!< SPI1 CR: SSMODE Mask                    */
#define SPI1_CR_RXIE_Pos                      13                                                      /*!< SPI1 CR: RXIE Position                  */
#define SPI1_CR_RXIE_Msk                      (0x01UL << SPI1_CR_RXIE_Pos)                            /*!< SPI1 CR: RXIE Mask                      */
#define SPI1_CR_TXIE_Pos                      14                                                      /*!< SPI1 CR: TXIE Position                  */
#define SPI1_CR_TXIE_Msk                      (0x01UL << SPI1_CR_TXIE_Pos)                            /*!< SPI1 CR: TXIE Mask                      */
#define SPI1_CR_SSCIE_Pos                     15                                                      /*!< SPI1 CR: SSCIE Position                 */
#define SPI1_CR_SSCIE_Msk                     (0x01UL << SPI1_CR_SSCIE_Pos)                           /*!< SPI1 CR: SSCIE Mask                     */
#define SPI1_CR_RXBC_Pos                      19                                                      /*!< SPI1 CR: RXBC Position                  */
#define SPI1_CR_RXBC_Msk                      (0x01UL << SPI1_CR_RXBC_Pos)                            /*!< SPI1 CR: RXBC Mask                      */
#define SPI1_CR_TXBC_Pos                      20                                                      /*!< SPI1 CR: TXBC Position                  */
#define SPI1_CR_TXBC_Msk                      (0x01UL << SPI1_CR_TXBC_Pos)                            /*!< SPI1 CR: TXBC Mask                      */

/* -----------------------------------  SPI1_SR  ---------------------------------- */
#define SPI1_SR_RRDY_Pos                      0                                                       /*!< SPI1 SR: RRDY Position                  */
#define SPI1_SR_RRDY_Msk                      (0x01UL << SPI1_SR_RRDY_Pos)                            /*!< SPI1 SR: RRDY Mask                      */
#define SPI1_SR_TRDY_Pos                      1                                                       /*!< SPI1 SR: TRDY Position                  */
#define SPI1_SR_TRDY_Msk                      (0x01UL << SPI1_SR_TRDY_Pos)                            /*!< SPI1 SR: TRDY Mask                      */
#define SPI1_SR_SBUSY_Pos                     2                                                       /*!< SPI1 SR: SBUSY Position                 */
#define SPI1_SR_SBUSY_Msk                     (0x01UL << SPI1_SR_SBUSY_Pos)                           /*!< SPI1 SR: SBUSY Mask                     */
#define SPI1_SR_UDRF_Pos                      3                                                       /*!< SPI1 SR: UDRF Position                  */
#define SPI1_SR_UDRF_Msk                      (0x01UL << SPI1_SR_UDRF_Pos)                            /*!< SPI1 SR: UDRF Mask                      */
#define SPI1_SR_OVRF_Pos                      4                                                       /*!< SPI1 SR: OVRF Position                  */
#define SPI1_SR_OVRF_Msk                      (0x01UL << SPI1_SR_OVRF_Pos)                            /*!< SPI1 SR: OVRF Mask                      */
#define SPI1_SR_SSON_Pos                      5                                                       /*!< SPI1 SR: SSON Position                  */
#define SPI1_SR_SSON_Msk                      (0x01UL << SPI1_SR_SSON_Pos)                            /*!< SPI1 SR: SSON Mask                      */
#define SPI1_SR_SSDET_Pos                     6                                                       /*!< SPI1 SR: SSDET Position                 */
#define SPI1_SR_SSDET_Msk                     (0x01UL << SPI1_SR_SSDET_Pos)                           /*!< SPI1 SR: SSDET Mask                     */

/* -----------------------------------  SPI1_BR  ---------------------------------- */
#define SPI1_BR_BR_Pos                        0                                                       /*!< SPI1 BR: BR Position                    */
#define SPI1_BR_BR_Msk                        (0x000000ffUL << SPI1_BR_BR_Pos)                        /*!< SPI1 BR: BR Mask                        */

/* -----------------------------------  SPI1_EN  ---------------------------------- */
#define SPI1_EN_ENABLE_Pos                    0                                                       /*!< SPI1 EN: ENABLE Position                */
#define SPI1_EN_ENABLE_Msk                    (0x01UL << SPI1_EN_ENABLE_Pos)                          /*!< SPI1 EN: ENABLE Mask                    */

/* -----------------------------------  SPI1_LR  ---------------------------------- */
#define SPI1_LR_STL_Pos                       0                                                       /*!< SPI1 LR: STL Position                   */
#define SPI1_LR_STL_Msk                       (0x01UL << SPI1_LR_STL_Pos)                             /*!< SPI1 LR: STL Mask                       */
#define SPI1_LR_BTL_Pos                       5                                                       /*!< SPI1 LR: BTL Position                   */
#define SPI1_LR_BTL_Msk                       (0x1fUL << SPI1_LR_BTL_Pos)                             /*!< SPI1 LR: BTL Mask                       */
#define SPI1_LR_SPL_Pos                       10                                                      /*!< SPI1 LR: SPL Position                   */
#define SPI1_LR_SPL_Msk                       (0x1fUL << SPI1_LR_SPL_Pos)                             /*!< SPI1 LR: SPL Mask                       */


/* ================================================================================ */
/* ================          struct 'ADC' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  ADC_CR  ----------------------------------- */
#define ADC_CR_ADSEL_Pos                      0                                                       /*!< ADC CR: ADSEL Position                  */
#define ADC_CR_ADSEL_Msk                      (0x0fUL << ADC_CR_ADSEL_Pos)                            /*!< ADC CR: ADSEL Mask                      */
#define ADC_CR_ADIF_Pos                       5                                                       /*!< ADC CR: ADIF Position                   */
#define ADC_CR_ADIF_Msk                       (0x01UL << ADC_CR_ADIF_Pos)                             /*!< ADC CR: ADIF Mask                       */
#define ADC_CR_AFLAG_Pos                      6                                                       /*!< ADC CR: AFLAG Position                  */
#define ADC_CR_AFLAG_Msk                      (0x01UL << ADC_CR_AFLAG_Pos)                            /*!< ADC CR: AFLAG Mask                      */
#define ADC_CR_ADST_Pos                       7                                                       /*!< ADC CR: ADST Position                   */
#define ADC_CR_ADST_Msk                       (0x01UL << ADC_CR_ADST_Pos)                             /*!< ADC CR: ADST Mask                       */
#define ADC_CR_ADEOC_Pos                      8                                                       /*!< ADC CR: ADEOC Position                  */
#define ADC_CR_ADEOC_Msk                      (0x01UL << ADC_CR_ADEOC_Pos)                            /*!< ADC CR: ADEOC Mask                      */

/* -----------------------------------  ADC_MR  ----------------------------------- */
#define ADC_MR_ADCS_Pos                       0                                                       /*!< ADC MR: ADCS Position                   */
#define ADC_MR_ADCS_Msk                       (0x000000ffUL << ADC_MR_ADCS_Pos)                       /*!< ADC MR: ADCS Mask                       */
#define ADC_MR_TSEL_Pos                       8                                                       /*!< ADC MR: TSEL Position                   */
#define ADC_MR_TSEL_Msk                       (0x07UL << ADC_MR_TSEL_Pos)                             /*!< ADC MR: TSEL Mask                       */
#define ADC_MR_EXTRG_Pos                      11                                                      /*!< ADC MR: EXTRG Position                  */
#define ADC_MR_EXTRG_Msk                      (0x01UL << ADC_MR_EXTRG_Pos)                            /*!< ADC MR: EXTRG Mask                      */
#define ADC_MR_ADIE_Pos                       12                                                      /*!< ADC MR: ADIE Position                   */
#define ADC_MR_ADIE_Msk                       (0x01UL << ADC_MR_ADIE_Pos)                             /*!< ADC MR: ADIE Mask                       */
#define ADC_MR_ADSTBY_Pos                     14                                                      /*!< ADC MR: ADSTBY Position                 */
#define ADC_MR_ADSTBY_Msk                     (0x01UL << ADC_MR_ADSTBY_Pos)                           /*!< ADC MR: ADSTBY Mask                     */
#define ADC_MR_ADCEN_Pos                      15                                                      /*!< ADC MR: ADCEN Position                  */
#define ADC_MR_ADCEN_Msk                      (0x01UL << ADC_MR_ADCEN_Pos)                            /*!< ADC MR: ADCEN Mask                      */

/* -----------------------------------  ADC_DR  ----------------------------------- */
#define ADC_DR_ADLR_Pos                       4                                                       /*!< ADC DR: ADLR Position                   */
#define ADC_DR_ADLR_Msk                       (0x0fUL << ADC_DR_ADLR_Pos)                             /*!< ADC DR: ADLR Mask                       */
#define ADC_DR_ADHR_Pos                       8                                                       /*!< ADC DR: ADHR Position                   */
#define ADC_DR_ADHR_Msk                       (0x000000ffUL << ADC_DR_ADHR_Pos)                       /*!< ADC DR: ADHR Mask                       */


/* ================================================================================ */
/* ================          struct 'FMC' Position & Mask          ================ */
/* ================================================================================ */


/* -----------------------------------  FMC_CFG  ---------------------------------- */
#define FMC_CFG_CWAIT_Pos                     0                                                       /*!< FMC CFG: CWAIT Position                 */
#define FMC_CFG_CWAIT_Msk                     (0x1fUL << FMC_CFG_CWAIT_Pos)                           /*!< FMC CFG: CWAIT Mask                     */
#define FMC_CFG_CZWAIT_Pos                    7                                                       /*!< FMC CFG: CZWAIT Position                */
#define FMC_CFG_CZWAIT_Msk                    (0x01UL << FMC_CFG_CZWAIT_Pos)                          /*!< FMC CFG: CZWAIT Mask                    */
#define FMC_CFG_DWAIT_Pos                     8                                                       /*!< FMC CFG: DWAIT Position                 */
#define FMC_CFG_DWAIT_Msk                     (0x1fUL << FMC_CFG_DWAIT_Pos)                           /*!< FMC CFG: DWAIT Mask                     */

/* -----------------------------------  FMC_CON  ---------------------------------- */
#define FMC_CON_PROG_Pos                      0                                                       /*!< FMC CON: PROG Position                  */
#define FMC_CON_PROG_Msk                      (0x01UL << FMC_CON_PROG_Pos)                            /*!< FMC CON: PROG Mask                      */
#define FMC_CON_SERA_Pos                      1                                                       /*!< FMC CON: SERA Position                  */
#define FMC_CON_SERA_Msk                      (0x01UL << FMC_CON_SERA_Pos)                            /*!< FMC CON: SERA Mask                      */
#define FMC_CON_MASE_Pos                      2                                                       /*!< FMC CON: MASE Position                  */
#define FMC_CON_MASE_Msk                      (0x01UL << FMC_CON_MASE_Pos)                            /*!< FMC CON: MASE Mask                      */
#define FMC_CON_NVSTR_Pos                     7                                                       /*!< FMC CON: NVSTR Position                 */
#define FMC_CON_NVSTR_Msk                     (0x01UL << FMC_CON_NVSTR_Pos)                           /*!< FMC CON: NVSTR Mask                     */
#define FMC_CON_CTBIT_Pos                     8                                                       /*!< FMC CON: CTBIT Position                 */
#define FMC_CON_CTBIT_Msk                     (0x01UL << FMC_CON_CTBIT_Pos)                           /*!< FMC CON: CTBIT Mask                     */
#define FMC_CON_DTBIT_Pos                     9                                                       /*!< FMC CON: DTBIT Position                 */
#define FMC_CON_DTBIT_Msk                     (0x01UL << FMC_CON_DTBIT_Pos)                           /*!< FMC CON: DTBIT Mask                     */
#define FMC_CON_CS_Pos                        11                                                      /*!< FMC CON: CS Position                    */
#define FMC_CON_CS_Msk                        (0x01UL << FMC_CON_CS_Pos)                              /*!< FMC CON: CS Mask                        */
#define FMC_CON_OE_Pos                        12                                                      /*!< FMC CON: OE Position                    */
#define FMC_CON_OE_Msk                        (0x01UL << FMC_CON_OE_Pos)                              /*!< FMC CON: OE Mask                        */
#define FMC_CON_AE_Pos                        13                                                      /*!< FMC CON: AE Position                    */
#define FMC_CON_AE_Msk                        (0x01UL << FMC_CON_AE_Pos)                              /*!< FMC CON: AE Mask                        */
#define FMC_CON_CSEL_Pos                      14                                                      /*!< FMC CON: CSEL Position                  */
#define FMC_CON_CSEL_Msk                      (0x01UL << FMC_CON_CSEL_Pos)                            /*!< FMC CON: CSEL Mask                      */
#define FMC_CON_DSEL_Pos                      15                                                      /*!< FMC CON: DSEL Position                  */
#define FMC_CON_DSEL_Msk                      (0x01UL << FMC_CON_DSEL_Pos)                            /*!< FMC CON: DSEL Mask                      */
#define FMC_CON_TSMD_Pos                      16                                                      /*!< FMC CON: TSMD Position                  */
#define FMC_CON_TSMD_Msk                      (0x01UL << FMC_CON_TSMD_Pos)                            /*!< FMC CON: TSMD Mask                      */
#define FMC_CON_TRSL_Pos                      17                                                      /*!< FMC CON: TRSL Position                  */
#define FMC_CON_TRSL_Msk                      (0x01UL << FMC_CON_TRSL_Pos)                            /*!< FMC CON: TRSL Mask                      */
#define FMC_CON_PAGE_Pos                      18                                                      /*!< FMC CON: PAGE Position                  */
#define FMC_CON_PAGE_Msk                      (0x01UL << FMC_CON_PAGE_Pos)                            /*!< FMC CON: PAGE Mask                      */
#define FMC_CON_FSRD_Pos                      20                                                      /*!< FMC CON: FSRD Position                  */
#define FMC_CON_FSRD_Msk                      (0x01UL << FMC_CON_FSRD_Pos)                            /*!< FMC CON: FSRD Mask                      */
#define FMC_CON_BBLK_Pos                      21                                                      /*!< FMC CON: BBLK Position                  */
#define FMC_CON_BBLK_Msk                      (0x01UL << FMC_CON_BBLK_Pos)                            /*!< FMC CON: BBLK Mask                      */
#define FMC_CON_SELF_CODE_Pos                 24                                                      /*!< FMC CON: SELF_CODE Position             */
#define FMC_CON_SELF_CODE_Msk                 (0x0fUL << FMC_CON_SELF_CODE_Pos)                       /*!< FMC CON: SELF_CODE Mask                 */
#define FMC_CON_SELF_Pos                      28                                                      /*!< FMC CON: SELF Position                  */
#define FMC_CON_SELF_Msk                      (0x01UL << FMC_CON_SELF_Pos)                            /*!< FMC CON: SELF Mask                      */
#define FMC_CON_STOP_Pos                      30                                                      /*!< FMC CON: STOP Position                  */
#define FMC_CON_STOP_Msk                      (0x01UL << FMC_CON_STOP_Pos)                            /*!< FMC CON: STOP Mask                      */
#define FMC_CON_RST_Pos                       31                                                      /*!< FMC CON: RST Position                   */
#define FMC_CON_RST_Msk                       (0x01UL << FMC_CON_RST_Pos)                             /*!< FMC CON: RST Mask                       */

/* -----------------------------------  FMC_ODR  ---------------------------------- */
#define FMC_ODR_ODR_Pos                       0                                                       /*!< FMC ODR: ODR Position                   */
#define FMC_ODR_ODR_Msk                       (0xffffffffUL << FMC_ODR_ODR_Pos)                       /*!< FMC ODR: ODR Mask                       */

/* -----------------------------------  FMC_IDR  ---------------------------------- */
#define FMC_IDR_FMIDR_Pos                     0                                                       /*!< FMC IDR: FMIDR Position                 */
#define FMC_IDR_FMIDR_Msk                     (0xffffffffUL << FMC_IDR_FMIDR_Pos)                     /*!< FMC IDR: FMIDR Mask                     */

/* -----------------------------------  FMC_AR  ----------------------------------- */
#define FMC_AR_A0_Pos                         0                                                       /*!< FMC AR: A0 Position                     */
#define FMC_AR_A0_Msk                         (0x01UL << FMC_AR_A0_Pos)                               /*!< FMC AR: A0 Mask                         */
#define FMC_AR_A1_Pos                         1                                                       /*!< FMC AR: A1 Position                     */
#define FMC_AR_A1_Msk                         (0x01UL << FMC_AR_A1_Pos)                               /*!< FMC AR: A1 Mask                         */
#define FMC_AR_ADDR_Pos                       2                                                       /*!< FMC AR: ADDR Position                   */
#define FMC_AR_ADDR_Msk                       (0x0001ffffUL << FMC_AR_ADDR_Pos)                       /*!< FMC AR: ADDR Mask                       */
#define FMC_AR_REDE_Pos                       19                                                      /*!< FMC AR: REDE Position                   */
#define FMC_AR_REDE_Msk                       (0x01UL << FMC_AR_REDE_Pos)                             /*!< FMC AR: REDE Mask                       */
#define FMC_AR_PRTE_Pos                       20                                                      /*!< FMC AR: PRTE Position                   */
#define FMC_AR_PRTE_Msk                       (0x01UL << FMC_AR_PRTE_Pos)                             /*!< FMC AR: PRTE Mask                       */
#define FMC_AR_IFREN_Pos                      21                                                      /*!< FMC AR: IFREN Position                  */
#define FMC_AR_IFREN_Msk                      (0x01UL << FMC_AR_IFREN_Pos)                            /*!< FMC AR: IFREN Mask                      */
#define FMC_AR_LDTE_Pos                       22                                                      /*!< FMC AR: LDTE Position                   */
#define FMC_AR_LDTE_Msk                       (0x01UL << FMC_AR_LDTE_Pos)                             /*!< FMC AR: LDTE Mask                       */
#define FMC_AR_DCTE_Pos                       23                                                      /*!< FMC AR: DCTE Position                   */
#define FMC_AR_DCTE_Msk                       (0x01UL << FMC_AR_DCTE_Pos)                             /*!< FMC AR: DCTE Mask                       */

/* ----------------------------------  FMC_TEST  ---------------------------------- */
#define FMC_TEST_EX_Pos                       0                                                       /*!< FMC TEST: EX Position                   */
#define FMC_TEST_EX_Msk                       (0x01UL << FMC_TEST_EX_Pos)                             /*!< FMC TEST: EX Mask                       */
#define FMC_TEST_AUTODIS_Pos                  4                                                       /*!< FMC TEST: AUTODIS Position              */
#define FMC_TEST_AUTODIS_Msk                  (0x01UL << FMC_TEST_AUTODIS_Pos)                        /*!< FMC TEST: AUTODIS Mask                  */
#define FMC_TEST_WRITE_KEY_Pos                8                                                       /*!< FMC TEST: WRITE_KEY Position            */
#define FMC_TEST_WRITE_KEY_Msk                (0x000000ffUL << FMC_TEST_WRITE_KEY_Pos)                /*!< FMC TEST: WRITE_KEY Mask                */

/* -----------------------------------  FMC_CRC  ---------------------------------- */
#define FMC_CRC_CRC16_Pos                     0                                                       /*!< FMC CRC: CRC16 Position                 */
#define FMC_CRC_CRC16_Msk                     (0x0000ffffUL << FMC_CRC_CRC16_Pos)                     /*!< FMC CRC: CRC16 Mask                     */
#define FMC_CRC_SEL_Pos                       16                                                      /*!< FMC CRC: SEL Position                   */
#define FMC_CRC_SEL_Msk                       (0x01UL << FMC_CRC_SEL_Pos)                             /*!< FMC CRC: SEL Mask                       */
#define FMC_CRC_CE_Pos                        20                                                      /*!< FMC CRC: CE Position                    */
#define FMC_CRC_CE_Msk                        (0x01UL << FMC_CRC_CE_Pos)                              /*!< FMC CRC: CE Mask                        */

/* ---------------------------------  FMC_PROTECT  -------------------------------- */
#define FMC_PROTECT_SP0_Pos                   0                                                       /*!< FMC PROTECT: SP0 Position               */
#define FMC_PROTECT_SP0_Msk                   (0x01UL << FMC_PROTECT_SP0_Pos)                         /*!< FMC PROTECT: SP0 Mask                   */
#define FMC_PROTECT_SP1_Pos                   1                                                       /*!< FMC PROTECT: SP1 Position               */
#define FMC_PROTECT_SP1_Msk                   (0x01UL << FMC_PROTECT_SP1_Pos)                         /*!< FMC PROTECT: SP1 Mask                   */
#define FMC_PROTECT_SP2_Pos                   2                                                       /*!< FMC PROTECT: SP2 Position               */
#define FMC_PROTECT_SP2_Msk                   (0x01UL << FMC_PROTECT_SP2_Pos)                         /*!< FMC PROTECT: SP2 Mask                   */
#define FMC_PROTECT_SP3_Pos                   3                                                       /*!< FMC PROTECT: SP3 Position               */
#define FMC_PROTECT_SP3_Msk                   (0x01UL << FMC_PROTECT_SP3_Pos)                         /*!< FMC PROTECT: SP3 Mask                   */
#define FMC_PROTECT_BP0_Pos                   4                                                       /*!< FMC PROTECT: BP0 Position               */
#define FMC_PROTECT_BP0_Msk                   (0x01UL << FMC_PROTECT_BP0_Pos)                         /*!< FMC PROTECT: BP0 Mask                   */
#define FMC_PROTECT_BP1_Pos                   5                                                       /*!< FMC PROTECT: BP1 Position               */
#define FMC_PROTECT_BP1_Msk                   (0x01UL << FMC_PROTECT_BP1_Pos)                         /*!< FMC PROTECT: BP1 Mask                   */
#define FMC_PROTECT_BP2_Pos                   6                                                       /*!< FMC PROTECT: BP2 Position               */
#define FMC_PROTECT_BP2_Msk                   (0x01UL << FMC_PROTECT_BP2_Pos)                         /*!< FMC PROTECT: BP2 Mask                   */
#define FMC_PROTECT_BP3_Pos                   7                                                       /*!< FMC PROTECT: BP3 Position               */
#define FMC_PROTECT_BP3_Msk                   (0x01UL << FMC_PROTECT_BP3_Pos)                         /*!< FMC PROTECT: BP3 Mask                   */
#define FMC_PROTECT_DP0_Pos                   8                                                       /*!< FMC PROTECT: DP0 Position               */
#define FMC_PROTECT_DP0_Msk                   (0x01UL << FMC_PROTECT_DP0_Pos)                         /*!< FMC PROTECT: DP0 Mask                   */
#define FMC_PROTECT_DP1_Pos                   9                                                       /*!< FMC PROTECT: DP1 Position               */
#define FMC_PROTECT_DP1_Msk                   (0x01UL << FMC_PROTECT_DP1_Pos)                         /*!< FMC PROTECT: DP1 Mask                   */
#define FMC_PROTECT_DP2_Pos                   10                                                      /*!< FMC PROTECT: DP2 Position               */
#define FMC_PROTECT_DP2_Msk                   (0x01UL << FMC_PROTECT_DP2_Pos)                         /*!< FMC PROTECT: DP2 Mask                   */
#define FMC_PROTECT_DP3_Pos                   11                                                      /*!< FMC PROTECT: DP3 Position               */
#define FMC_PROTECT_DP3_Msk                   (0x01UL << FMC_PROTECT_DP3_Pos)                         /*!< FMC PROTECT: DP3 Mask                   */
#define FMC_PROTECT_BP4_Pos                   12                                                      /*!< FMC PROTECT: BP4 Position               */
#define FMC_PROTECT_BP4_Msk                   (0x01UL << FMC_PROTECT_BP4_Pos)                         /*!< FMC PROTECT: BP4 Mask                   */
#define FMC_PROTECT_BP5_Pos                   13                                                      /*!< FMC PROTECT: BP5 Position               */
#define FMC_PROTECT_BP5_Msk                   (0x01UL << FMC_PROTECT_BP5_Pos)                         /*!< FMC PROTECT: BP5 Mask                   */
#define FMC_PROTECT_CIP0_Pos                  14                                                      /*!< FMC PROTECT: CIP0 Position              */
#define FMC_PROTECT_CIP0_Msk                  (0x01UL << FMC_PROTECT_CIP0_Pos)                        /*!< FMC PROTECT: CIP0 Mask                  */
#define FMC_PROTECT_DIP_Pos                   15                                                      /*!< FMC PROTECT: DIP Position               */
#define FMC_PROTECT_DIP_Msk                   (0x01UL << FMC_PROTECT_DIP_Pos)                         /*!< FMC PROTECT: DIP Mask                   */
#define FMC_PROTECT_SP4_Pos                   16                                                      /*!< FMC PROTECT: SP4 Position               */
#define FMC_PROTECT_SP4_Msk                   (0x01UL << FMC_PROTECT_SP4_Pos)                         /*!< FMC PROTECT: SP4 Mask                   */
#define FMC_PROTECT_SP5_Pos                   17                                                      /*!< FMC PROTECT: SP5 Position               */
#define FMC_PROTECT_SP5_Msk                   (0x01UL << FMC_PROTECT_SP5_Pos)                         /*!< FMC PROTECT: SP5 Mask                   */
#define FMC_PROTECT_SP6_Pos                   18                                                      /*!< FMC PROTECT: SP6 Position               */
#define FMC_PROTECT_SP6_Msk                   (0x01UL << FMC_PROTECT_SP6_Pos)                         /*!< FMC PROTECT: SP6 Mask                   */
#define FMC_PROTECT_SP7_Pos                   19                                                      /*!< FMC PROTECT: SP7 Position               */
#define FMC_PROTECT_SP7_Msk                   (0x01UL << FMC_PROTECT_SP7_Pos)                         /*!< FMC PROTECT: SP7 Mask                   */
#define FMC_PROTECT_BP6_Pos                   20                                                      /*!< FMC PROTECT: BP6 Position               */
#define FMC_PROTECT_BP6_Msk                   (0x01UL << FMC_PROTECT_BP6_Pos)                         /*!< FMC PROTECT: BP6 Mask                   */
#define FMC_PROTECT_BP7_Pos                   21                                                      /*!< FMC PROTECT: BP7 Position               */
#define FMC_PROTECT_BP7_Msk                   (0x01UL << FMC_PROTECT_BP7_Pos)                         /*!< FMC PROTECT: BP7 Mask                   */
#define FMC_PROTECT_BP8_Pos                   22                                                      /*!< FMC PROTECT: BP8 Position               */
#define FMC_PROTECT_BP8_Msk                   (0x01UL << FMC_PROTECT_BP8_Pos)                         /*!< FMC PROTECT: BP8 Mask                   */
#define FMC_PROTECT_BP9_Pos                   23                                                      /*!< FMC PROTECT: BP9 Position               */
#define FMC_PROTECT_BP9_Msk                   (0x01UL << FMC_PROTECT_BP9_Pos)                         /*!< FMC PROTECT: BP9 Mask                   */
#define FMC_PROTECT_BP10_Pos                  28                                                      /*!< FMC PROTECT: BP10 Position              */
#define FMC_PROTECT_BP10_Msk                  (0x01UL << FMC_PROTECT_BP10_Pos)                        /*!< FMC PROTECT: BP10 Mask                  */
#define FMC_PROTECT_BP11_Pos                  29                                                      /*!< FMC PROTECT: BP11 Position              */
#define FMC_PROTECT_BP11_Msk                  (0x01UL << FMC_PROTECT_BP11_Pos)                        /*!< FMC PROTECT: BP11 Mask                  */
#define FMC_PROTECT_CIP1_Pos                  30                                                      /*!< FMC PROTECT: CIP1 Position              */
#define FMC_PROTECT_CIP1_Msk                  (0x01UL << FMC_PROTECT_CIP1_Pos)                        /*!< FMC PROTECT: CIP1 Mask                  */
#define FMC_PROTECT_BANKSWAPOTP_Pos           31                                                      /*!< FMC PROTECT: BANKSWAPOTP Position       */
#define FMC_PROTECT_BANKSWAPOTP_Msk           (0x01UL << FMC_PROTECT_BANKSWAPOTP_Pos)                 /*!< FMC PROTECT: BANKSWAPOTP Mask           */

/* ----------------------------------  FMC_RPROT  --------------------------------- */
#define FMC_RPROT_FMRPROT_Pos                 0                                                       /*!< FMC RPROT: FMRPROT Position             */
#define FMC_RPROT_FMRPROT_Msk                 (0x0000ffffUL << FMC_RPROT_FMRPROT_Pos)                 /*!< FMC RPROT: FMRPROT Mask                 */
#define FMC_RPROT_CERS_Pos                    16                                                      /*!< FMC RPROT: CERS Position                */
#define FMC_RPROT_CERS_Msk                    (0x01UL << FMC_RPROT_CERS_Pos)                          /*!< FMC RPROT: CERS Mask                    */
#define FMC_RPROT_RPROT_Pos                   20                                                      /*!< FMC RPROT: RPROT Position               */
#define FMC_RPROT_RPROT_Msk                   (0x01UL << FMC_RPROT_RPROT_Pos)                         /*!< FMC RPROT: RPROT Mask                   */

/* -----------------------------------  FMC_BCR  ---------------------------------- */
#define FMC_BCR_BSW_Pos                       0                                                       /*!< FMC BCR: BSW Position                   */
#define FMC_BCR_BSW_Msk                       (0x01UL << FMC_BCR_BSW_Pos)                             /*!< FMC BCR: BSW Mask                       */
#define FMC_BCR_BSE_Pos                       4                                                       /*!< FMC BCR: BSE Position                   */
#define FMC_BCR_BSE_Msk                       (0x01UL << FMC_BCR_BSE_Pos)                             /*!< FMC BCR: BSE Mask                       */
#define FMC_BCR_WTIDKY_Pos                    16                                                      /*!< FMC BCR: WTIDKY Position                */
#define FMC_BCR_WTIDKY_Msk                    (0x0000ffffUL << FMC_BCR_WTIDKY_Pos)                    /*!< FMC BCR: WTIDKY Mask                    */

/* -----------------------------------  FMC_BSR  ---------------------------------- */
#define FMC_BSR_BSWST_Pos                     0                                                       /*!< FMC BSR: BSWST Position                 */
#define FMC_BSR_BSWST_Msk                     (0x01UL << FMC_BSR_BSWST_Pos)                           /*!< FMC BSR: BSWST Mask                     */
#define FMC_BSR_BSST_Pos                      4                                                       /*!< FMC BSR: BSST Position                  */
#define FMC_BSR_BSST_Msk                      (0x01UL << FMC_BSR_BSST_Pos)                            /*!< FMC BSR: BSST Mask                      */
#define FMC_BSR_CBF_Pos                       8                                                       /*!< FMC BSR: CBF Position                   */
#define FMC_BSR_CBF_Msk                       (0x01UL << FMC_BSR_CBF_Pos)                             /*!< FMC BSR: CBF Mask                       */

/* ----------------------------------  FMC_ECCMR  --------------------------------- */
#define FMC_ECCMR_CECCEN_Pos                  0                                                       /*!< FMC ECCMR: CECCEN Position              */
#define FMC_ECCMR_CECCEN_Msk                  (0x01UL << FMC_ECCMR_CECCEN_Pos)                        /*!< FMC ECCMR: CECCEN Mask                  */
#define FMC_ECCMR_DECCEN_Pos                  1                                                       /*!< FMC ECCMR: DECCEN Position              */
#define FMC_ECCMR_DECCEN_Msk                  (0x01UL << FMC_ECCMR_DECCEN_Pos)                        /*!< FMC ECCMR: DECCEN Mask                  */

/* ---------------------------------  FMC_FMC_IER  -------------------------------- */
#define FMC_FMC_IER_CECCIEN_Pos               0                                                       /*!< FMC FMC_IER: CECCIEN Position           */
#define FMC_FMC_IER_CECCIEN_Msk               (0x01UL << FMC_FMC_IER_CECCIEN_Pos)                     /*!< FMC FMC_IER: CECCIEN Mask               */
#define FMC_FMC_IER_DECCIEN_Pos               4                                                       /*!< FMC FMC_IER: DECCIEN Position           */
#define FMC_FMC_IER_DECCIEN_Msk               (0x01UL << FMC_FMC_IER_DECCIEN_Pos)                     /*!< FMC FMC_IER: DECCIEN Mask               */
#define FMC_FMC_IER_BSEN_Pos                  8                                                       /*!< FMC FMC_IER: BSEN Position              */
#define FMC_FMC_IER_BSEN_Msk                  (0x01UL << FMC_FMC_IER_BSEN_Pos)                        /*!< FMC FMC_IER: BSEN Mask                  */
#define FMC_FMC_IER_WEIEN_Pos                 12                                                      /*!< FMC FMC_IER: WEIEN Position             */
#define FMC_FMC_IER_WEIEN_Msk                 (0x01UL << FMC_FMC_IER_WEIEN_Pos)                       /*!< FMC FMC_IER: WEIEN Mask                 */
#define FMC_FMC_IER_WDIEN_Pos                 13                                                      /*!< FMC FMC_IER: WDIEN Position             */
#define FMC_FMC_IER_WDIEN_Msk                 (0x01UL << FMC_FMC_IER_WDIEN_Pos)                       /*!< FMC FMC_IER: WDIEN Mask                 */

/* ---------------------------------  FMC_FMC_ISR  -------------------------------- */
#define FMC_FMC_ISR_CECCSERR_Pos              0                                                       /*!< FMC FMC_ISR: CECCSERR Position          */
#define FMC_FMC_ISR_CECCSERR_Msk              (0x01UL << FMC_FMC_ISR_CECCSERR_Pos)                    /*!< FMC FMC_ISR: CECCSERR Mask              */
#define FMC_FMC_ISR_CECCDERR_Pos              1                                                       /*!< FMC FMC_ISR: CECCDERR Position          */
#define FMC_FMC_ISR_CECCDERR_Msk              (0x01UL << FMC_FMC_ISR_CECCDERR_Pos)                    /*!< FMC FMC_ISR: CECCDERR Mask              */
#define FMC_FMC_ISR_DECCSERR_Pos              4                                                       /*!< FMC FMC_ISR: DECCSERR Position          */
#define FMC_FMC_ISR_DECCSERR_Msk              (0x01UL << FMC_FMC_ISR_DECCSERR_Pos)                    /*!< FMC FMC_ISR: DECCSERR Mask              */
#define FMC_FMC_ISR_DECCDERR_Pos              5                                                       /*!< FMC FMC_ISR: DECCDERR Position          */
#define FMC_FMC_ISR_DECCDERR_Msk              (0x01UL << FMC_FMC_ISR_DECCDERR_Pos)                    /*!< FMC FMC_ISR: DECCDERR Mask              */
#define FMC_FMC_ISR_BSERR_Pos                 8                                                       /*!< FMC FMC_ISR: BSERR Position             */
#define FMC_FMC_ISR_BSERR_Msk                 (0x01UL << FMC_FMC_ISR_BSERR_Pos)                       /*!< FMC FMC_ISR: BSERR Mask                 */
#define FMC_FMC_ISR_WEF_Pos                   12                                                      /*!< FMC FMC_ISR: WEF Position               */
#define FMC_FMC_ISR_WEF_Msk                   (0x01UL << FMC_FMC_ISR_WEF_Pos)                         /*!< FMC FMC_ISR: WEF Mask                   */
#define FMC_FMC_ISR_WDF_Pos                   13                                                      /*!< FMC FMC_ISR: WDF Position               */
#define FMC_FMC_ISR_WDF_Msk                   (0x01UL << FMC_FMC_ISR_WDF_Pos)                         /*!< FMC FMC_ISR: WDF Mask                   */


/* ================================================================================ */
/* ================         struct 'MEMCR' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  MEMCR_CR  ---------------------------------- */
#define MEMCR_CR_REMAP0_Pos                   0                                                       /*!< MEMCR CR: REMAP0 Position               */
#define MEMCR_CR_REMAP0_Msk                   (0x01UL << MEMCR_CR_REMAP0_Pos)                         /*!< MEMCR CR: REMAP0 Mask                   */
#define MEMCR_CR_REMAP1_Pos                   1                                                       /*!< MEMCR CR: REMAP1 Position               */
#define MEMCR_CR_REMAP1_Msk                   (0x01UL << MEMCR_CR_REMAP1_Pos)                         /*!< MEMCR CR: REMAP1 Mask                   */
#define MEMCR_CR_REMAP2_Pos                   2                                                       /*!< MEMCR CR: REMAP2 Position               */
#define MEMCR_CR_REMAP2_Msk                   (0x01UL << MEMCR_CR_REMAP2_Pos)                         /*!< MEMCR CR: REMAP2 Mask                   */
#define MEMCR_CR_REMAP3_Pos                   3                                                       /*!< MEMCR CR: REMAP3 Position               */
#define MEMCR_CR_REMAP3_Msk                   (0x01UL << MEMCR_CR_REMAP3_Pos)                         /*!< MEMCR CR: REMAP3 Mask                   */


/* ================================================================================ */
/* ================         struct 'LEGACY' Position & Mask        ================ */
/* ================================================================================ */


/* ------------------------------  LEGACY_PMULEGACY  ------------------------------ */
#define LEGACY_PMULEGACY_LEGACY_NORMAL_Pos    0                                                       /*!< LEGACY PMULEGACY: LEGACY_NORMAL Position */
#define LEGACY_PMULEGACY_LEGACY_NORMAL_Msk    (0x0fUL << LEGACY_PMULEGACY_LEGACY_NORMAL_Pos)          /*!< LEGACY PMULEGACY: LEGACY_NORMAL Mask    */
#define LEGACY_PMULEGACY_MODCHGKEY_Pos        8                                                       /*!< LEGACY PMULEGACY: MODCHGKEY Position    */
#define LEGACY_PMULEGACY_MODCHGKEY_Msk        (0x000000ffUL << LEGACY_PMULEGACY_MODCHGKEY_Pos)        /*!< LEGACY PMULEGACY: MODCHGKEY Mask        */
#define LEGACY_PMULEGACY_MODE_Pos             31                                                      /*!< LEGACY PMULEGACY: MODE Position         */
#define LEGACY_PMULEGACY_MODE_Msk             (0x01UL << LEGACY_PMULEGACY_MODE_Pos)                   /*!< LEGACY PMULEGACY: MODE Mask             */



/* ================================================================================ */
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */

#define CHIP_CONFIG_BASE                0x4000F000UL
#define PMU_BASE                        0x40000000UL
#define PCA_BASE                        0x40000200UL
#define PCB_BASE                        0x40000220UL
#define PCC_BASE                        0x40000240UL
#define PCD_BASE                        0x40000260UL
#define PCE_BASE                        0x40000280UL
#define PCF_BASE                        0x400002A0UL
#define PA_BASE                         0x40000300UL
#define PB_BASE                         0x40000310UL
#define PC_BASE                         0x40000320UL
#define PD_BASE                         0x40000330UL
#define PE_BASE                         0x40000340UL
#define PF_BASE                         0x40000350UL
#define WDT_BASE                        0x40000400UL
#define FRT_BASE                        0x40000500UL
#define T0_BASE                         0x40000C00UL
#define T1_BASE                         0x40000C20UL
#define T2_BASE                         0x40000C40UL
#define T3_BASE                         0x40000C60UL
#define T4_BASE                         0x40000C80UL
#define T5_BASE                         0x40000CA0UL
#define T6_BASE                         0x40000CC0UL
#define T7_BASE                         0x40000CE0UL
#define T8_BASE                         0x40000D00UL
#define T9_BASE                         0x40000D20UL
#define PWM0_BASE                       0x40000700UL
#define PWM1_BASE                       0x40000720UL
#define PWM2_BASE                       0x40000740UL
#define PWM3_BASE                       0x40000760UL
#define PWM4_BASE                       0x40000780UL
#define PWM5_BASE                       0x400007A0UL
#define PWM6_BASE                       0x400007C0UL
#define PWM7_BASE                       0x400007E0UL
#define PWMPRS0_BASE                    0x4000077CUL
#define PWMPRS1_BASE                    0x400007FCUL
#define I2C0_BASE                       0x40000A00UL
#define I2C1_BASE                       0x40000A80UL
#define UART0_BASE                      0x40000B00UL
#define UART1_BASE                      0x40000B40UL
#define UART2_BASE                      0x40000B80UL
#define UART3_BASE                      0x40000BC0UL
#define SPI0_BASE                       0x40000800UL
#define SPI1_BASE                       0x40000820UL
#define ADC_BASE                        0x40000E00UL
#define FMC_BASE                        0x40000100UL
#define MEMCR_BASE                      0x400000E0UL
#define LEGACY_BASE                     0x400000F8UL


/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

#define CHIP_CONFIG                     ((CHIP_CONFIG_Type        *) CHIP_CONFIG_BASE)
#define PMU                             ((PMU_Type                *) PMU_BASE)
#define PCA                             ((PCA_Type                *) PCA_BASE)
#define PCB                             ((PCA_Type                *) PCB_BASE)
#define PCC                             ((PCA_Type                *) PCC_BASE)
#define PCD                             ((PCA_Type                *) PCD_BASE)
#define PCE                             ((PCA_Type                *) PCE_BASE)
#define PCF                             ((PCA_Type                *) PCF_BASE)
#define PA                              ((PA_Type                 *) PA_BASE)
#define PB                              ((PA_Type                 *) PB_BASE)
#define PC                              ((PA_Type                 *) PC_BASE)
#define PD                              ((PA_Type                 *) PD_BASE)
#define PE                              ((PA_Type                 *) PE_BASE)
#define PF                              ((PA_Type                 *) PF_BASE)
#define WDT                             ((WDT_Type                *) WDT_BASE)
#define FRT                             ((FRT_Type                *) FRT_BASE)
#define T0                              ((T0_Type                 *) T0_BASE)
#define T1                              ((T0_Type                 *) T1_BASE)
#define T2                              ((T0_Type                 *) T2_BASE)
#define T3                              ((T0_Type                 *) T3_BASE)
#define T4                              ((T0_Type                 *) T4_BASE)
#define T5                              ((T0_Type                 *) T5_BASE)
#define T6                              ((T0_Type                 *) T6_BASE)
#define T7                              ((T0_Type                 *) T7_BASE)
#define T8                              ((T0_Type                 *) T8_BASE)
#define T9                              ((T0_Type                 *) T9_BASE)
#define PWM0                            ((PWM0_Type               *) PWM0_BASE)
#define PWM1                            ((PWM0_Type               *) PWM1_BASE)
#define PWM2                            ((PWM0_Type               *) PWM2_BASE)
#define PWM3                            ((PWM0_Type               *) PWM3_BASE)
#define PWM4                            ((PWM0_Type               *) PWM4_BASE)
#define PWM5                            ((PWM0_Type               *) PWM5_BASE)
#define PWM6                            ((PWM0_Type               *) PWM6_BASE)
#define PWM7                            ((PWM0_Type               *) PWM7_BASE)
#define PWMPRS0                         ((PWMPRS0_Type            *) PWMPRS0_BASE)
#define PWMPRS1                         ((PWMPRS0_Type            *) PWMPRS1_BASE)
#define I2C0                            ((I2C0_Type               *) I2C0_BASE)
#define I2C1                            ((I2C0_Type               *) I2C1_BASE)
#define UART0                           ((UART0_Type              *) UART0_BASE)
#define UART1                           ((UART0_Type              *) UART1_BASE)
#define UART2                           ((UART0_Type              *) UART2_BASE)
#define UART3                           ((UART0_Type              *) UART3_BASE)
#define SPI0                            ((SPI0_Type               *) SPI0_BASE)
#define SPI1                            ((SPI0_Type               *) SPI1_BASE)
#define ADC                             ((ADC_Type                *) ADC_BASE)
#define FMC                             ((FMC_Type                *) FMC_BASE)
#define MEMCR                           ((MEMCR_Type              *) MEMCR_BASE)
#define LEGACY                          ((LEGACY_Type             *) LEGACY_BASE)


/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group A33G53x */
/** @} */ /* End of group ABOV Semiconductor Co., Ltd. */

#ifdef __cplusplus
}
#endif


#endif  /* A33G53x_H */

