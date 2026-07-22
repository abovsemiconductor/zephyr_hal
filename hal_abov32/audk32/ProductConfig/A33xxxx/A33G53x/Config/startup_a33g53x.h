/**
 *******************************************************************************
 * @file        startup_a33g53x.h
 * @author      ABOV R&D Division
 * @brief       Startup APIs for A33G53x
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _STARTUP_A33G53X_H_
#define _STARTUP_A33G53X_H_

/* place a function into a ram section macro */
#if defined ( NO_RAMFUNCS )
#define RAMFUNC

#elif defined (__ICCARM__)
#define RAMFUNC                                       __ramfunc
#ifndef __inline
#define __inline                                      inline
#endif

#elif defined (__CC_ARM) || defined (__ARMCC_VERSION)
#define RAMFUNC                                       __attribute__ ((section ("code_section_on_ram")))

#elif defined (__GNUC__)
#define RAMFUNC                                       __attribute__ ((long_call, section (".code_section_on_ram")))

#endif

#define LSI_CLOCK   (1000000)   /* The clock speed of Internal Low Speed Oscillator */
#define LSE_CLOCK   (32768)     /* The clock speed of External Low Speed Oscillator (SXTAL) */
#define HSI_CLOCK   (16000000)  /* The clock speed of Internal High Speed Oscillator */
#define HSE_CLOCK   (8000000)   /* The clock speed of External High Speed Oscillator(XTAL) */

#define PMU_LEGACY_MODE           (0x0001UL<<31)
#define PMU_LEGACY_MODE_NORMAL    (0x0000UL<<31)
#define PMU_LEGACY_MODE_LEGACY    (0x0001UL<<31)


#define PMU_LEGACY_LEGACY_STEP1    (0xDADAUL<<0)
#define PMU_LEGACY_LEGACY_STEP2    (0xDA00UL<<0)

#define PMU_LEGACY_NORMAL_STEP1    (0xDADAUL<<0)
#define PMU_LEGACY_NORMAL_STEP2    (0xDAADUL<<0)

extern void SystemClock_Config(void);

static __inline int8_t *PRV_CHIPSET_GetCoreInfo(void)
{
    return (int8_t *)"Cortex-M3";
}

static __inline int8_t *PRV_CHIPSET_GetInfo(void)
{
     return (int8_t *)"A33G53x";
}

/* Port flash geometry here */
#define STARTUP_FLASH_BASE_ADDR             0x00000000
#define STARTUP_CODE_FLASH_BASE_OFFSET      0x00000000
#define STARTUP_DATA_FLASH_BASE_OFFSET      0x0F000000
#define STARTUP_SYSTEM_FLASH_BASE_OFFSET    0x00100000
#define STARTUP_SYSTEM_FLASH_OFFSET_MASK    0x000FFFFF
#define STARTUP_PAGE_SIZE                   0x200
#define STARTUP_DATA_PAGE_SIZE              0x200

#define CONFIG_MAX_WPROT_BLOCKS             6
typedef struct
{
    uint32_t    un32WProtectedSegStartOffset;
    uint32_t    un32WProtectedSegSize;
    uint8_t     un8NumWProtectedSegs;
} CONFIG_WPROT_BLOCKS_t;

typedef struct
{
    uint32_t    un32Size;
    uint32_t    un32BaseAddr;
    uint8_t     un8NumWProtectedBlocks;
    CONFIG_WPROT_BLOCKS_t tWProtectedBlocks[CONFIG_MAX_WPROT_BLOCKS];
} CONFIG_FLASH_GEOMETRY_t;

/* General purpose system flash area only */
typedef struct
{
    uint32_t    un32Size;
    uint32_t    un32BaseAddr;
    uint32_t    un32SysSegSize;
    uint8_t     un8NumSysSegs;
} CONFIG_SYSFLASH_GEOMETRY_t;

typedef struct
{
    CONFIG_FLASH_GEOMETRY_t    tCflash;
    CONFIG_FLASH_GEOMETRY_t    tDflash;
    CONFIG_SYSFLASH_GEOMETRY_t tSysflash;
} CONFIG_FLASH_INFO_t;

static __inline CONFIG_FLASH_INFO_t PRV_CHIPSET_GetFlashGeometricInfo(void);

/* Be careful:Number of Blocks should not exeed to CONFIG_MAX_WPROT_BLOCKS */
RAMFUNC static __inline CONFIG_FLASH_INFO_t PRV_CHIPSET_GetFlashGeometricInfo(void)
{
    CONFIG_FLASH_INFO_t tFlashGeometricInfo;

    tFlashGeometricInfo.tCflash.un32BaseAddr = STARTUP_CODE_FLASH_BASE_OFFSET | STARTUP_FLASH_BASE_ADDR;
    tFlashGeometricInfo.tCflash.un8NumWProtectedBlocks = 6;

    tFlashGeometricInfo.tCflash.tWProtectedBlocks[0].un32WProtectedSegStartOffset = 0;
    tFlashGeometricInfo.tCflash.tWProtectedBlocks[0].un32WProtectedSegSize = 0x1000;
    tFlashGeometricInfo.tCflash.tWProtectedBlocks[0].un8NumWProtectedSegs = 4;

    tFlashGeometricInfo.tCflash.tWProtectedBlocks[1].un32WProtectedSegStartOffset = 0x00004000;
    tFlashGeometricInfo.tCflash.tWProtectedBlocks[1].un32WProtectedSegSize = 0xC000;
    tFlashGeometricInfo.tCflash.tWProtectedBlocks[1].un8NumWProtectedSegs = 1;

    tFlashGeometricInfo.tCflash.tWProtectedBlocks[2].un32WProtectedSegStartOffset = 0x00010000;
    tFlashGeometricInfo.tCflash.tWProtectedBlocks[2].un32WProtectedSegSize = 0x10000;

    tFlashGeometricInfo.tDflash.un32BaseAddr = STARTUP_DATA_FLASH_BASE_OFFSET | STARTUP_FLASH_BASE_ADDR;
    tFlashGeometricInfo.tDflash.un32Size = 0x8000;
    tFlashGeometricInfo.tDflash.un8NumWProtectedBlocks = 1;
    tFlashGeometricInfo.tDflash.tWProtectedBlocks[0].un32WProtectedSegStartOffset = 0;
    tFlashGeometricInfo.tDflash.tWProtectedBlocks[0].un32WProtectedSegSize = 0x2000;
    tFlashGeometricInfo.tDflash.tWProtectedBlocks[0].un8NumWProtectedSegs = 4;

    /* If FMC supports data flash, System flash should not be accessed by user */
    tFlashGeometricInfo.tSysflash.un32BaseAddr = STARTUP_SYSTEM_FLASH_BASE_OFFSET | STARTUP_FLASH_BASE_ADDR;
    tFlashGeometricInfo.tSysflash.un32Size = 0;
    tFlashGeometricInfo.tSysflash.un32SysSegSize = 0;
    tFlashGeometricInfo.tSysflash.un8NumSysSegs = 0;

    switch (CHIP_CONFIG->CHIPIDR)
    {
        case 0x47335381: /* A33G539 */
            tFlashGeometricInfo.tCflash.un32Size = 0xC0000;
            tFlashGeometricInfo.tCflash.tWProtectedBlocks[2].un8NumWProtectedSegs = 5;

            tFlashGeometricInfo.tCflash.tWProtectedBlocks[3].un32WProtectedSegStartOffset = 0x00060000;
            tFlashGeometricInfo.tCflash.tWProtectedBlocks[3].un32WProtectedSegSize = 0x1000;
            tFlashGeometricInfo.tCflash.tWProtectedBlocks[3].un8NumWProtectedSegs = 4;

            tFlashGeometricInfo.tCflash.tWProtectedBlocks[4].un32WProtectedSegStartOffset = 0x00064000;
            tFlashGeometricInfo.tCflash.tWProtectedBlocks[4].un32WProtectedSegSize = 0xC000;
            tFlashGeometricInfo.tCflash.tWProtectedBlocks[4].un8NumWProtectedSegs = 1;

            tFlashGeometricInfo.tCflash.tWProtectedBlocks[5].un32WProtectedSegStartOffset = 0x00070000;
            tFlashGeometricInfo.tCflash.tWProtectedBlocks[5].un32WProtectedSegSize = 0x10000;
            tFlashGeometricInfo.tCflash.tWProtectedBlocks[5].un8NumWProtectedSegs = 5;

            break;

        case 0x47335380: /* A33G538 */
            tFlashGeometricInfo.tCflash.un32Size = 0x80000;
            tFlashGeometricInfo.tCflash.tWProtectedBlocks[2].un8NumWProtectedSegs = 3;

            tFlashGeometricInfo.tCflash.tWProtectedBlocks[3].un32WProtectedSegStartOffset = 0x00040000;
            tFlashGeometricInfo.tCflash.tWProtectedBlocks[3].un32WProtectedSegSize = 0x1000;
            tFlashGeometricInfo.tCflash.tWProtectedBlocks[3].un8NumWProtectedSegs = 4;

            tFlashGeometricInfo.tCflash.tWProtectedBlocks[4].un32WProtectedSegStartOffset = 0x00044000;
            tFlashGeometricInfo.tCflash.tWProtectedBlocks[4].un32WProtectedSegSize = 0xC000;
            tFlashGeometricInfo.tCflash.tWProtectedBlocks[4].un8NumWProtectedSegs = 1;

            tFlashGeometricInfo.tCflash.tWProtectedBlocks[5].un32WProtectedSegStartOffset = 0x00050000;
            tFlashGeometricInfo.tCflash.tWProtectedBlocks[5].un32WProtectedSegSize = 0x10000;
            tFlashGeometricInfo.tCflash.tWProtectedBlocks[5].un8NumWProtectedSegs = 3;
            break;

        default:
            tFlashGeometricInfo.tCflash.un32Size = 0;
            tFlashGeometricInfo.tDflash.un32Size = 0;
            tFlashGeometricInfo.tSysflash.un32Size = 0;
            break;
    }

    return tFlashGeometricInfo;
}

static __inline void PRV_CHIPSET_Init(void)
{
    uint32_t reg_val;

    LEGACY->PMULEGACY = PMU_LEGACY_NORMAL_STEP1;
    LEGACY->PMULEGACY = PMU_LEGACY_NORMAL_STEP2;
    __enable_irq();     /* Enable Global interrupt in core */
    do
    {
        reg_val = LEGACY->PMULEGACY;
    } while ((reg_val & PMU_LEGACY_MODE) != PMU_LEGACY_MODE_NORMAL);

    WDT->CON = 0;       /* Disable Watchdog Timer */
    FMC->CFG = 0x0303;  /* Set Flash Wait Time */

#if 0
    /* JTAG(SWO) Port Setting */
    PCU_ConfigureFunction (PCC, PIN_0, PC0_MUX_nTRST);
    PCU_ConfigureFunction (PCC, PIN_1, PC1_MUX_TDI);
    PCU_ConfigureFunction (PCC, PIN_2, PC2_MUX_TMS);
    PCU_ConfigureFunction (PCC, PIN_3, PC3_MUX_TCK);
    PCU_ConfigureFunction (PCC, PIN_4, PC4_MUX_TDO);

    PCU_SetDirection(PCC, PIN_0, LOGIC_INPUT);
    PCU_SetDirection(PCC, PIN_1, LOGIC_INPUT);
    PCU_SetDirection(PCC, PIN_2, LOGIC_INPUT);
    PCU_SetDirection(PCC, PIN_3, LOGIC_INPUT);
    PCU_SetDirection(PCC, PIN_4, PUSHPULL_OUTPUT);

    PCC->PCR = 0x4F;
#endif

    reg_val = PMU->CCR;
    reg_val &= ~(PMU_CCR_ROSCEN_Msk);
    reg_val |= (0x02UL<<PMU_CCR_ROSCEN_Pos);    /* RingOSC */

    PMU->CCR = reg_val;
    PMU->BCCR = 0x00;
    PMU->PLLCON = 0;

    SystemCoreClock = 1000000;
    SystemPeriClock = 1000000;

    __disable_irq();
}

static __inline void PRV_CHIPSET_ClockInit(void)
{
    uint32_t    reg_val;

    reg_val = PMU->BCCR;
    reg_val &= ~(PMU_BCCR_MCLKSEL_Msk|PMU_BCCR_PCLKDIV_Msk|PMU_BCCR_HCLKDIV_Msk);
    reg_val |= (0x00UL<<PMU_BCCR_MCLKSEL_Pos);    /* RingOSC to main clock */
    reg_val |= (0x00UL<<PMU_BCCR_HCLKDIV_Pos);    /* Main Clock ->  HCLK = HCLK/1 (AHB Bus Clock) */
    reg_val |= (0x00UL<<PMU_BCCR_PCLKDIV_Pos);    /* Main Clock -> PCLK = PCLK/1 (APB Bus Clock) */
    PMU->BCCR = reg_val;

    reg_val = PMU->CCR;
    reg_val &= ~(PMU_CCR_IOSC16EN_Msk|PMU_CCR_SXOSCEN_Msk|PMU_CCR_MXOSCEN_Msk);
    reg_val |= (0x02UL<<PMU_CCR_IOSC16EN_Pos);    /* IOSC16 Enable and Div 1 */
    reg_val |= (0x02UL<<PMU_CCR_MXOSCEN_Pos);     /* MXOSC Enable and Div 1 */
    reg_val |= (0x02UL<<PMU_CCR_SXOSCEN_Pos);     /* SXOSC Enable and Div 1 */
    PMU->CCR = reg_val;

    /* MXOSC -> Monitoring of MXOSC Oscillation */
    PMU->CMR = (0x00UL<<PMU_CMR_MXOSCSTS_Pos | 0x01UL<<PMU_CMR_MXOSCMNT_Pos);

    if (PMU->CCR & PMU_CCR_MXOSCEN_Msk)
    {   /* Check Oscillation of MXOSC */
        while (1)
        {
            reg_val = PMU->CMR;
            if (reg_val & PMU_CMR_MXOSCSTS_Msk)   /* Does MXOSC oscillate normally? */
            {
                break;
            }
	    }
    }
#if 0
    if (PMU_SetPLLFreq(PMU, XTAL8MHz, PLL74MHz)) {    /* PLL Setting */
        ;
    }
#endif

    PMU->PCCR = 0xFFFFFFFFUL;    /* Peipheral Clock Control Enable */
    PMU->PER = 0xFFFFFFFFUL;     /* Peripheral Enable */
    PMU->PRER = 0xFFFFFFFFUL;    /* Peripheral Reset Enable */

    reg_val = (0x01UL<<PMU_LVDCON_LVDEN_Pos);
    reg_val |= (0x01UL<<PMU_LVDCON_LVDRF_Pos);
    reg_val |= (0x01UL<<PMU_LVDCON_LVDREN_Pos);
    reg_val |= (0x00UL<<PMU_LVDCON_LVDRL_Pos);

    PMU->LVDCON = reg_val;      /* LVD Reset 2.6V */

    PCC->DPR = 8;               /* PC6 debounce */
    PCC->DER = (0x0001<<6);     /* PC6 (nReset) */

    PMU->RSER |= (0x01UL<<PMU_RSER_RSTRSTE_Pos|0x01UL<<PMU_RSER_LVDRSTE_Pos);    /* set Reset Source (LVD, nRESET) */
}

static __inline void PRV_PORT_Init(void)
{
    /* Peripheral Enable Register 1  0:Disable 1:Enable */
    PMU->PER |= 0x00UL
            | (0x01UL << PMU_PER_GPIOF_Pos)   /* GPIO F */
            | (0x01UL << PMU_PER_GPIOE_Pos)   /* GPIO E */
            | (0x01UL << PMU_PER_GPIOD_Pos)   /* GPIO D */
            | (0x01UL << PMU_PER_GPIOC_Pos)   /* GPIO C */
            | (0x01UL << PMU_PER_GPIOB_Pos)   /* GPIO B */
            | (0x01UL << PMU_PER_GPIOA_Pos);  /* GPIO A */

    /* Peripheral Clock Enable Register 1 0:Disable 1:Enable */
    PMU->PCCR |= 0x00UL
            | (0x01UL << PMU_PCCR_GPIO_Pos);   /* GPIO for All(A~F) */

    /*--------------------------------------------------------------
     *    PORT INIT
     *        PA PB PC PD PE PF
     *--------------------------------------------------------------*/
    /* PORT - A */
    PA->ODR = 0; /* gpio output default 0 (low ) */

    PCA->MR = 0x00UL
            | (0x00UL << PCA_MR_P15_Pos)   /* P15 - 0:PA15 1:T9C 2: 3:AN15 */
            | (0x00UL << PCA_MR_P14_Pos)   /* P14 - 0:PA14 1:T8C 2: 3:AN14 */
            | (0x00UL << PCA_MR_P13_Pos)   /* P13 - 0:PA13 1:T7C 2: 3: */
            | (0x00UL << PCA_MR_P12_Pos)   /* P12 - 0:PA12 1:T6C 2: 3: */
            | (0x00UL << PCA_MR_P11_Pos)   /* P11 - 0:PA11 1:T5C 2: 3: */
            | (0x00UL << PCA_MR_P10_Pos)   /* P10 - 0:PA10 1:T4C 2: 3: */
            | (0x00UL << PCA_MR_P9_Pos)    /* P9  - 0:PA9  1:T3C 2: 3: */
            | (0x00UL << PCA_MR_P8_Pos)    /* P8  - 0:PA8  1:T2C 2: 3: */
            | (0x00UL << PCA_MR_P7_Pos)    /* P7  - 0:PA7  1:T1C 2: 3:AN7 */
            | (0x00UL << PCA_MR_P6_Pos)    /* P6  - 0:PA6  1:T0C 2: 3:AN6 */
            | (0x00UL << PCA_MR_P5_Pos)    /* P5  - 0:PA5  1:    2: 3:AN5 */
            | (0x00UL << PCA_MR_P4_Pos)    /* P4  - 0:PA4  1:    2: 3:AN4 */
            | (0x00UL << PCA_MR_P3_Pos)    /* P3  - 0:PA3  1:    2: 3:AN3 */
            | (0x00UL << PCA_MR_P2_Pos)    /* P2  - 0:PA2  1:    2: 3:AN2 */
            | (0x00UL << PCA_MR_P1_Pos)    /* P1  - 0:PA1  1:    2: 3:AN1 */
            | (0x00UL << PCA_MR_P0_Pos);   /* P0  - 0:PA0  1:    2: 3:AN0 */

    PCA->CR = 0;
    PCA->PCR = 0;

    /* PORT - B */
    PB->ODR = 0; /* gpio output default 0 (low ) */

    PCB->MR = 0x00UL
            | (0x00UL << PCB_MR_P15_Pos)   /* P15 - 0:PB15 1:SDA0  2: 3: */
            | (0x00UL << PCB_MR_P14_Pos)   /* P14 - 0:PB14 1:SCL0  2: 3: */
            | (0x00UL << PCB_MR_P13_Pos)   /* P13 - 0:PB13 1:MISO0 2: 3: */
            | (0x00UL << PCB_MR_P12_Pos)   /* P12 - 0:PB12 1:MOSI0 2: 3: */
            | (0x00UL << PCB_MR_P11_Pos)   /* P11 - 0:PB11 1:SCK0  2: 3: */
            | (0x00UL << PCB_MR_P10_Pos)   /* P10 - 0:PB10 1:SS0   2: 3: */
            | (0x00UL << PCB_MR_P9_Pos)    /* P9  - 0:PB9  1:T9O   2: 3: */
            | (0x00UL << PCB_MR_P8_Pos)    /* P8  - 0:PB8  1:T8O   2: 3: */
            | (0x00UL << PCB_MR_P7_Pos)    /* P7  - 0:PB7  1:T7O   2: 3: */
            | (0x00UL << PCB_MR_P6_Pos)    /* P6  - 0:PB6  1:T6O   2: 3: */
            | (0x00UL << PCB_MR_P5_Pos)    /* P5  - 0:PB5  1:T5O   2: 3: */
            | (0x00UL << PCB_MR_P4_Pos)    /* P4  - 0:PB4  1:T4O   2: 3: */
            | (0x00UL << PCB_MR_P3_Pos)    /* P3  - 0:PB3  1:T3O   2: 3: */
            | (0x00UL << PCB_MR_P2_Pos)    /* P2  - 0:PB2  1:T2O   2: 3: */
            | (0x00UL << PCB_MR_P1_Pos)    /* P1  - 0:PB1  1:T1O   2: 3: */
            | (0x00UL << PCB_MR_P0_Pos);   /* P0  - 0:PB0  1:T0O   2: 3: */

    PCB->CR = 0;
    PCB->PCR = 0;

    /* PORT - C */
    PC->ODR = 0; /* gpio output default 0 (low ) */

    PCC->MR = 0x00UL
            | (0x01UL << PCC_MR_P15_Pos)   /* P15 - 0:PC15 1:XTALI      2:CLKIN 3: */
            | (0x01UL << PCC_MR_P14_Pos)   /* P14 - 0:PC14 1:XTALO      2:      3: */
            | (0x00UL << PCC_MR_P13_Pos)   /* P13 - 0:PC13 1:CLKO       2:      3: */
            | (0x00UL << PCC_MR_P12_Pos)   /* P12 - 0:PC12 1:STBYO      2:      3: */
            | (0x00UL << PCC_MR_P11_Pos)   /* P11 - 0:PC11 1:TXD2       2:      3: */
            | (0x00UL << PCC_MR_P10_Pos)   /* P10 - 0:PC10 1:RXD2       2:      3: */
            | (0x00UL << PCC_MR_P9_Pos)    /* P9  - 0:PC9  1:TXD0       2:      3: */
            | (0x00UL << PCC_MR_P8_Pos)    /* P8  - 0:PC8  1:RXD0       2:      3: */
            | (0x00UL << PCC_MR_P7_Pos)    /* P7  - 0:PC7  1:           2:      3: */
            | (0x01UL << PCC_MR_P6_Pos)    /* P6  - 0:PC6  1:nRESET     2:      3: */
            | (0x00UL << PCC_MR_P5_Pos)    /* P5  - 0:PC5  1:           2:      3: */
            | (0x01UL << PCC_MR_P4_Pos)    /* P4  - 0:PC4  1:TDO(SWO)   2:      3: */
            | (0x01UL << PCC_MR_P3_Pos)    /* P3  - 0:PC3  1:TCK(SWCLK) 2:      3: */
            | (0x01UL << PCC_MR_P2_Pos)    /* P2  - 0:PC2  1:TMS(SWDIO) 2:      3: */
            | (0x01UL << PCC_MR_P1_Pos)    /* P1  - 0:PC1  1:TDI        2:      3: */
            | (0x01UL << PCC_MR_P0_Pos);   /* P0  - 0:PC0  1:nTRST      2:      3: */

    PCC->CR = 0x00UL
            | (0x03UL << PCC_CR_P15_Pos)
            | (0x03UL << PCC_CR_P14_Pos)
            | (0x03UL << PCC_CR_P13_Pos)
            | (0x03UL << PCC_CR_P12_Pos)
            | (0x03UL << PCC_CR_P11_Pos)
            | (0x03UL << PCC_CR_P10_Pos)
            | (0x00UL << PCC_CR_P9_Pos)
            | (0x02UL << PCC_CR_P8_Pos)
            | (0x03UL << PCC_CR_P7_Pos)
            | (0x02UL << PCC_CR_P6_Pos)
            | (0x03UL << PCC_CR_P5_Pos)
            | (0x00UL << PCC_CR_P4_Pos)
            | (0x02UL << PCC_CR_P3_Pos)
            | (0x02UL << PCC_CR_P2_Pos)
            | (0x02UL << PCC_CR_P1_Pos)
            | (0x02UL << PCC_CR_P0_Pos);

    PCC->PCR = 0x00UL
            | (0x00UL << PCC_PCR_P15_Pos)
            | (0x00UL << PCC_PCR_P14_Pos)
            | (0x00UL << PCC_PCR_P13_Pos)
            | (0x00UL << PCC_PCR_P12_Pos)
            | (0x00UL << PCC_PCR_P11_Pos)
            | (0x00UL << PCC_PCR_P10_Pos)
            | (0x00UL << PCC_PCR_P9_Pos)
            | (0x00UL << PCC_PCR_P8_Pos)
            | (0x00UL << PCC_PCR_P7_Pos)
            | (0x01UL << PCC_PCR_P6_Pos)
            | (0x00UL << PCC_PCR_P5_Pos)
            | (0x00UL << PCC_PCR_P4_Pos)
            | (0x01UL << PCC_PCR_P3_Pos)
            | (0x01UL << PCC_PCR_P2_Pos)
            | (0x01UL << PCC_PCR_P1_Pos)
            | (0x01UL << PCC_PCR_P0_Pos);

    /* PORT - D */
    PD->ODR = 0; /* gpio output default 0 (low ) */

    PCD->MR = 0x00UL
            | (0x00UL << PCD_MR_P15_Pos)   /* P15 - 0:PD15 1:SDA1  2: 3: */
            | (0x00UL << PCD_MR_P14_Pos)   /* P14 - 0:PD14 1:SCL1  2: 3: */
            | (0x00UL << PCD_MR_P13_Pos)   /* P13 - 0:PD13 1:TXD1  2: 3: */
            | (0x00UL << PCD_MR_P12_Pos)   /* P12 - 0:PD12 1:RXD1  2: 3: */
            | (0x00UL << PCD_MR_P11_Pos)   /* P11 - 0:PD11 1:MISO1 2: 3: */
            | (0x00UL << PCD_MR_P10_Pos)   /* P10 - 0:PD10 1:MOSI1 2: 3: */
            | (0x00UL << PCD_MR_P9_Pos)    /* P9  - 0:PD9  1:SCK1  2: 3: */
            | (0x00UL << PCD_MR_P8_Pos)    /* P8  - 0:PD8  1:SS1   2: 3: */
            | (0x00UL << PCD_MR_P7_Pos)    /* P7  - 0:PD7  1:PWMA7 2: 3: */
            | (0x00UL << PCD_MR_P6_Pos)    /* P6  - 0:PD6  1:PWMA6 2: 3: */
            | (0x00UL << PCD_MR_P5_Pos)    /* P5  - 0:PD5  1:PWMA5 2: 3: */
            | (0x00UL << PCD_MR_P4_Pos)    /* P4  - 0:PD4  1:PWMA4 2: 3: */
            | (0x00UL << PCD_MR_P3_Pos)    /* P3  - 0:PD3  1:PWMA3 2: 3: */
            | (0x00UL << PCD_MR_P2_Pos)    /* P2  - 0:PD2  1:PWMA2 2: 3: */
            | (0x00UL << PCD_MR_P1_Pos)    /* P1  - 0:PD1  1:PWMA1 2: 3: */
            | (0x00UL << PCD_MR_P0_Pos);   /* P0  - 0:PD0  1:PWMA0 2: 3: */

    PCD->CR = 0;
    PCD->PCR = 0;

    /* PORT - E */
    PE->ODR = 0; /* gpio output default 0 (low ) */

    PCE->MR = 0x00UL
            | (0x00UL << PCE_MR_P15_Pos)   /* P15 - 0:PE15 1:TraceCLK 2:     3: */
            | (0x00UL << PCE_MR_P14_Pos)   /* P14 - 0:PE14 1:TraceD0  2:     3: */
            | (0x00UL << PCE_MR_P13_Pos)   /* P13 - 0:PE13 1:TraceD1  2:     3: */
            | (0x00UL << PCE_MR_P12_Pos)   /* P12 - 0:PE12 1:TraceD2  2:     3: */
            | (0x00UL << PCE_MR_P11_Pos)   /* P11 - 0:PE11 1:TraceD3  2:     3: */
            | (0x00UL << PCE_MR_P9_Pos)    /* P9  - 0:PE9  1:SXOUT    2:     3: */
            | (0x00UL << PCE_MR_P8_Pos)    /* P8  - 0:PE8  1:SXIN     2:     3: */
            | (0x00UL << PCE_MR_P7_Pos)    /* P7  - 0:PE7  1:PWMB7    2:TXD3 3: */
            | (0x00UL << PCE_MR_P6_Pos)    /* P6  - 0:PE6  1:PWMB6    2:RXD3 3: */
            | (0x00UL << PCE_MR_P5_Pos)    /* P5  - 0:PE5  1:PWMB5    2:     3: */
            | (0x00UL << PCE_MR_P4_Pos)    /* P4  - 0:PE4  1:PWMB4    2:     3: */
            | (0x00UL << PCE_MR_P3_Pos)    /* P3  - 0:PE3  1:PWMB3    2:     3: */
            | (0x00UL << PCE_MR_P2_Pos)    /* P2  - 0:PE2  1:PWMB2    2:     3: */
            | (0x00UL << PCE_MR_P1_Pos)    /* P1  - 0:PE1  1:PWMB1    2:     3: */
            | (0x00UL << PCE_MR_P0_Pos);   /* P0  - 0:PE0  1:PWMB0    2:     3: */

    PCE->CR = 0;
    PCE->PCR = 0;

    /* PORT - F */
    PF->ODR = 0; /* gpio output default 0 (low ) */

    PCF->MR = 0x00UL
            | (0x00UL << PCF_MR_P11_Pos)   /* P11 - 0:PF11 1: 2:FRT0_FMF 3: */
            | (0x00UL << PCF_MR_P9_Pos)    /* P9  - 0:PF9  1: 2:         3: */
            | (0x00UL << PCF_MR_P8_Pos)    /* P8  - 0:PF8  1: 2:         3: */
            | (0x00UL << PCF_MR_P7_Pos)    /* P7  - 0:PF7  1: 2:         3: */
            | (0x00UL << PCF_MR_P6_Pos)    /* P6  - 0:PF6  1: 2:         3: */
            | (0x00UL << PCF_MR_P5_Pos)    /* P5  - 0:PF5  1: 2:         3:AN13 */
            | (0x00UL << PCF_MR_P4_Pos)    /* P4  - 0:PF4  1: 2:         3:AN12 */
            | (0x00UL << PCF_MR_P3_Pos)    /* P3  - 0:PF3  1: 2:         3:AN11 */
            | (0x00UL << PCF_MR_P2_Pos)    /* P2  - 0:PF2  1: 2:         3:AN10 */
            | (0x00UL << PCF_MR_P1_Pos)    /* P1  - 0:PF1  1: 2:         3:AN9 */
            | (0x00UL << PCF_MR_P0_Pos);   /* P0  - 0:PF0  1: 2:         3:AN8 */


    PCF->CR = 0;
    PCF->PCR = 0;
}

#endif /* _STARTUP_A33G53X_H_ */
