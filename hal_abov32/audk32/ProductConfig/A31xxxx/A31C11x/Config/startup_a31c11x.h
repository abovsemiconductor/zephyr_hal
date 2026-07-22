/**
 *******************************************************************************
 * @file        startup_a31c11x.h
 * @author      ABOV R&D Division
 * @brief       Startup APIs for A31C11x
 *
 * Copyright 2026 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _STARTUP_A31C11X_H_
#define _STARTUP_A31C11X_H_

/* place a function into a ram section macro */
#if defined ( NO_RAMFUNCS )
#define RAMFUNC

#elif defined (__ICCARM__)
#define RAMFUNC                                       __ramfunc
#ifndef __inline
#define __inline                                      inline
#endif

#elif defined (__CC_ARM) || (__ARMCC_VERSION)
#define RAMFUNC                                       __attribute__ ((section ("code_section_on_ram")))

#elif defined (__GNUC__)
#define RAMFUNC                                       __attribute__ ((long_call, section (".code_section_on_ram")))

#endif

/* A31C11x Clock Source */
#define LSI_CLOCK   (32000)    /* The clock speed of Internal Low Speed Oscillator */
#define HSI_CLOCK   (32000000)  /* The clock speed of Internal High Speed Oscillator */

extern void SystemClock_Config(void);

static __inline int8_t *PRV_CHIPSET_GetCoreInfo(void)
{
    if(((CHIPCONFIG->CHIPID & 0x00FF0000) >> 16) == 0x31)
    {
        return (int8_t *)"Cortex-M0+";
    }
    else
    {
        return (int8_t *)"Unknown";
    }
}

static __inline int8_t *PRV_CHIPSET_GetInfo(void)
{
    if(CHIPCONFIG->CHIPID == 0x43311110)
    {
        return (int8_t *)"A31C111 : Code Flash 16KB / SRAM 2KB";
    }
    else
    {
        return (int8_t *)"Unknown";
    }
}

/* Port flash geometry here */
#define STARTUP_FLASH_BASE_ADDR             0x00000000
#define STARTUP_CODE_FLASH_BASE_OFFSET      0x00000000
#define STARTUP_SYSTEM_FLASH_BASE_OFFSET    0x0F000000
#define STARTUP_SYSTEM_FLASH_OFFSET_MASK    0x00FFFFFF
#define STARTUP_PAGE_SIZE                   0x200

#define CONFIG_MAX_WPROT_BLOCKS             3
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
    uint32_t    un32CflashSize;
    uint32_t    un32SystemFlashSize;
    uint32_t    un32CflashWProtectedSegSize;    /*  Size per 1bit of Protection register*/
} CONFIG_FLASH_INFO_t;

static __inline CONFIG_FLASH_INFO_t PRV_CHIPSET_GetFlashGeometricInfo(void);

RAMFUNC static __inline CONFIG_FLASH_INFO_t PRV_CHIPSET_GetFlashGeometricInfo(void)
{
    CONFIG_FLASH_INFO_t tFlashGeometricInfo;

    switch (CHIPCONFIG->CHIPID)
    {
        case 0x43311110: /* A31C111 */
            tFlashGeometricInfo.un32CflashSize = 0x4000;
            tFlashGeometricInfo.un32SystemFlashSize = 0x800;
            tFlashGeometricInfo.un32CflashWProtectedSegSize = 0x800;
            break;
        default:
            tFlashGeometricInfo.un32CflashSize = 0;
            tFlashGeometricInfo.un32SystemFlashSize = 0;
            tFlashGeometricInfo.un32CflashWProtectedSegSize = 0;
            break;
    }
    return tFlashGeometricInfo;
}

static __inline void PRV_CHIPSET_Init(void)
{
    uint32_t reg;

    /* WDT Access Enable */
    WDT->AEN = 0xA55A;
    /* WDT Disable */
    WDT->CON = 0;

    /* SCU Access Enable */
    SCU->SYSTEN = 0x57;
    SCU->SYSTEN = 0x75;
#if 0
    /* GPIO Access Enable */
    PORTEN->EN = 0x15;
    PORTEN->EN = 0x51;
#endif
    /* Forcily, set 1 into flash latency value */
    reg = CFMC->CONF;
    reg &= ~(CFMC_CONF_LATENCY_Msk);
    reg |= (0x01UL << CFMC_CONF_LATENCY_Pos);
    CFMC->CONF = reg;

}

static __inline void PRV_PORT_Init(void)
{
    /* Peripheral Enable Register 1  0:Disable 1:Enable */
    SCU->PER1 |= 0x00UL
            | (0x01UL << SCU_PER1_GPIOF_Pos)    /* GPIO F */
            | (0x01UL << SCU_PER1_GPIOE_Pos)    /* GPIO E */
            | (0x01UL << SCU_PER1_GPIOD_Pos)    /* GPIO D */
            | (0x01UL << SCU_PER1_GPIOC_Pos)    /* GPIO C */
            | (0x01UL << SCU_PER1_GPIOB_Pos)    /* GPIO B */
            | (0x01UL << SCU_PER1_GPIOA_Pos);   /* GPIO A */

    /* Peripheral Clock Enable Register 1 0:Disable 1:Enable */
    SCU->PCER1 |= 0x00UL
            | (0x01UL << SCU_PCER1_GPIOF_Pos)   /* GPIO F */
            | (0x01UL << SCU_PCER1_GPIOE_Pos)   /* GPIO E */
            | (0x01UL << SCU_PCER1_GPIOD_Pos)   /* GPIO D */
            | (0x01UL << SCU_PCER1_GPIOC_Pos)   /* GPIO C */
            | (0x01UL << SCU_PCER1_GPIOB_Pos)   /* GPIO B */
            | (0x01UL << SCU_PCER1_GPIOA_Pos);  /* GPIO A */

    /* enable writing permittion of ALL PCU register */
    PORTEN->EN = 0x15;
    PORTEN->EN = 0x51;

    /*--------------------------------------------------------------
     *    PORT INIT
     *        PA PB PC PD
     *-------------------------------------------------------------*/
    /* PORT - A */
    PA->ODR = 0; /* gpio output default 0 (low ) */

    PA->MR1 = 0x00UL
              | (0x00UL << PCU_MR1_P7MUX_Pos);    /* P7 - 0:PA7 1:     2:     3:     4:      7:AN7/AVREF */

    PA->MR2 = 0x00UL;

    PA->CR = 0;
    PA->PRCR = 0;

    /* PORT - B */
    PB->ODR = 0; /* gpio output default 0 (low ) */

    PB->MR1 = 0x00UL
              | (0x03UL << PCU_MR1_P5MUX_Pos)    /* P5 - 0:PB5 1:RXD0   2:     3:SWDIO    4:       7:*/
              | (0x03UL << PCU_MR1_P4MUX_Pos)    /* P4 - 0:PB4 1:TXD0   2:     3:SWCLK    4:       7:*/
              | (0x03UL << PCU_MR1_P3MUX_Pos)    /* P3 - 0:PB3 1:       2:     3:nBOOT    4:SS10   7:*/
              | (0x00UL << PCU_MR1_P2MUX_Pos)    /* P2 - 0:PB2 1:       2:     3:CLKO     4:SCK10  7:AN10 */
              | (0x00UL << PCU_MR1_P1MUX_Pos)    /* P1 - 0:PB1 1:RXD10  2:     3:         4:MISO10 7:AN9 */
              | (0x00UL << PCU_MR1_P0MUX_Pos);   /* P0 - 0:PB0 1:TXD10  2:     3:         4:MOSI10 7:AN8 */

    PB->MR2 = 0x00UL;

    PB->CR = 0;
    PB->PRCR = 0;

    /* PORT - C */
    PC->ODR = 0; /* gpio output default 0 (low ) */

    PC->MR1 = 0x00UL;

    PC->MR2 = 0x00UL
              | (0x03UL << PCU_MR2_P9MUX_Pos);   /* P9 - 0:PC9 1:     2: 3:nRESET   4:   7: */

    PC->CR = 0;
    PC->PRCR = 0;

    /* PORT - D */
    PD->ODR = 0; /* gpio output default 0 (low ) */

    PD->MR1 = 0x00UL
              | (0x00UL << PCU_MR1_P1MUX_Pos)    /* P1 - 0:PD1 1:SDA0  2:     3: 4:       7: */
              | (0x00UL << PCU_MR1_P0MUX_Pos);   /* P0 - 0:PD0 1:SCL0  2:     3: 4:       7: */

    PD->CR = 0;
    PD->PRCR = 0;

    /* PORT - E */
    PE->ODR = 0; /* gpio output default 0 (low ) */

    PE->MR1 = 0x00UL
              | (0x00UL << PCU_MR1_P7MUX_Pos)    /* P7 - 0:PE7 1:   2:T1IO 3:STBYO 4:       7: */
              | (0x00UL << PCU_MR1_P6MUX_Pos)    /* P6 - 0:PE6 1:   2:T0IO 3:WDTO  4:       7: */
              | (0x00UL << PCU_MR1_P3MUX_Pos)    /* P3 - 0:PE3 1:   2:T2IO 3:      4:       7:AN17 */
              | (0x00UL << PCU_MR1_P2MUX_Pos)    /* P2 - 0:PE2 1:   2:     3:      4:       7:AN16 */
              | (0x00UL << PCU_MR1_P1MUX_Pos)    /* P1 - 0:PE1 1:   2:T3IO 3:      4:       7:AN15 */
              | (0x00UL << PCU_MR1_P0MUX_Pos);   /* P0 - 0:PE0 1:   2:T2IO 3:      4:       7:AN14 */

    PE->MR2 = 0x00UL;

    PE->CR = 0;

    /* PORT - F */
    PF->ODR = 0; /* gpio output default 0 (low ) */

    PF->MR1 = 0x00UL
              | (0x07UL << PCU_MR1_P1MUX_Pos)    /* P1 - 0:PF1 1:    2:     3:     4:RXD0  7: */
              | (0x07UL << PCU_MR1_P0MUX_Pos);   /* P0 - 0:PF0 1:    2:     3:     4:TXD0  7: */

    PF->CR = 0;
    PF->PRCR = 0;

    /* disable writing permittion of ALL PCU register */
    PORTEN->EN = 0x00;
}

#endif /* _STARTUP_A31C11X_H_ */
