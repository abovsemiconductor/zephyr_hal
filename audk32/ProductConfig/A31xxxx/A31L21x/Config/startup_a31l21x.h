/**
 *******************************************************************************
 * @file        startup_a31l21x.h
 * @author      ABOV R&D Division
 * @brief       Startup APIs for A31L21x
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _STARTUP_A31L21X_H_
#define _STARTUP_A31L21X_H_

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

#define LSI_CLOCK   (40000)     /* The clock speed of Watchdog Timer Oscillator (WDTRC) */
#define LSE_CLOCK   (32768)     /* The clock speed of External Low Speed Oscillator (XSOSC) */
#define HSI_CLOCK   (32000000)  /* The clock speed of Internal High Speed Oscillator (HIRC) */
#define HSE_CLOCK   (16000000)  /* The clock speed of External High Speed Oscillator (XMOSC) */

static __inline int8_t *PRV_CHIPSET_GetCoreInfo(void)
{
    if(((SCUCC->CHIPID & 0x00FF0000) >> 16) == 0x31)
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
    if(SCUCC->CHIPID == 0x4D31F010)
    {
        return (int8_t *)"A31L214 : Flash 128KB / SRAM 20KB";
    }
    else if(SCUCC->CHIPID == 0x4D31F011)
    {
        return (int8_t *)"A31L213 : Flash 64KB / SRAM 20KB";
    }
    else
    {
        return (int8_t *)"Unknown";
    }
}

/* Port flash geometry here */
#define STARTUP_FLASH_BASE_ADDR             0x10000000
#define STARTUP_CODE_FLASH_BASE_OFFSET      0x00000000
#define STARTUP_DATA_FLASH_BASE_OFFSET      0x08800000
#define STARTUP_SYSTEM_FLASH_BASE_OFFSET    0x0FFFF000
#define STARTUP_SYSTEM_FLASH_OFFSET_MASK    0x00000FFF
#define STARTUP_PAGE_SIZE                   0x80
#define STARTUP_DATA_PAGE_SIZE              0x20

#define STARTUP_NON_USER_INFO_BASE_OFFSET   STARTUP_SYSTEM_FLASH_BASE_OFFSET
#define STARTUP_NON_USER_INFO_SIZE          0x200

#define CONFIG_MAX_WPROT_BLOCKS             2

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
    tFlashGeometricInfo.tCflash.un8NumWProtectedBlocks = 2;
    tFlashGeometricInfo.tCflash.tWProtectedBlocks[0].un32WProtectedSegStartOffset = 0;
    tFlashGeometricInfo.tCflash.tWProtectedBlocks[0].un32WProtectedSegSize = 0x800;
    tFlashGeometricInfo.tCflash.tWProtectedBlocks[0].un8NumWProtectedSegs = 32;

    tFlashGeometricInfo.tDflash.un32BaseAddr = STARTUP_DATA_FLASH_BASE_OFFSET | STARTUP_FLASH_BASE_ADDR;
    tFlashGeometricInfo.tDflash.un32Size = 0x1000;
    tFlashGeometricInfo.tDflash.un8NumWProtectedBlocks = 1;
    tFlashGeometricInfo.tDflash.tWProtectedBlocks[0].un32WProtectedSegStartOffset = 0;
    tFlashGeometricInfo.tDflash.tWProtectedBlocks[0].un32WProtectedSegSize = 0x200;
    tFlashGeometricInfo.tDflash.tWProtectedBlocks[0].un8NumWProtectedSegs = 8;

    /* If FMC supports data flash, System flash should not be accessed by user */
    tFlashGeometricInfo.tSysflash.un32BaseAddr = STARTUP_SYSTEM_FLASH_BASE_OFFSET | STARTUP_FLASH_BASE_ADDR;
    tFlashGeometricInfo.tSysflash.un32Size = 0x800;
    tFlashGeometricInfo.tSysflash.un32SysSegSize = 0;
    tFlashGeometricInfo.tSysflash.un8NumSysSegs = 0;

    switch (SCUCC->CHIPID)
    {
        case 0x4D31F010: /* A31L214 */
            tFlashGeometricInfo.tCflash.un32Size = 0x20000;
            tFlashGeometricInfo.tCflash.un8NumWProtectedBlocks = 2;
            tFlashGeometricInfo.tCflash.tWProtectedBlocks[1].un32WProtectedSegStartOffset = 0x10000;
            tFlashGeometricInfo.tCflash.tWProtectedBlocks[1].un32WProtectedSegSize = 0x800;
            tFlashGeometricInfo.tCflash.tWProtectedBlocks[1].un8NumWProtectedSegs = 32;
            break;

        case 0x4D31F011: /* A31L213 */
            tFlashGeometricInfo.tCflash.un32Size = 0x10000;
            tFlashGeometricInfo.tCflash.un8NumWProtectedBlocks = 1;
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
    /* disable WDT - default ON so you must turn off */
    WDT->CR = 0              |
              (0x5A69 << 16) |
              (0x25 << 10)   |
              (0x1A << 4);
}

static __inline void PRV_PORT_Init(void)
{
    /* Peripheral Clock Enable Register 1 0:Disable 1:Enable */
    SCUCG->PPCLKEN1 |= 0x00UL
                    | (0x01UL << SCUCG_PPCLKEN1_PFCLKE_Pos)   /* CLK F */
                    | (0x01UL << SCUCG_PPCLKEN1_PECLKE_Pos)   /* CLK E */
                    | (0x01UL << SCUCG_PPCLKEN1_PDCLKE_Pos)   /* CLK D */
                    | (0x01UL << SCUCG_PPCLKEN1_PCCLKE_Pos)   /* CLK C */
                    | (0x01UL << SCUCG_PPCLKEN1_PBCLKE_Pos)   /* CLK B */
                    | (0x01UL << SCUCG_PPCLKEN1_PACLKE_Pos);  /* CLK A */

    /*--------------------------------------------------------------
     *    PORT INIT
     *        PA PB PC PD PE PF
     *--------------------------------------------------------------*/
    /* PORT - A */
    PA->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x00UL << Pn_MOD_MODE15_Pos)     /* P15 */
            | (0x00UL << Pn_MOD_MODE14_Pos)     /* P14 */
            | (0x00UL << Pn_MOD_MODE13_Pos)     /* P13 */
            | (0x00UL << Pn_MOD_MODE12_Pos)     /* P12 */
            | (0x00UL << Pn_MOD_MODE11_Pos)     /* P11 */
            | (0x00UL << Pn_MOD_MODE10_Pos)     /* P10 */
            | (0x00UL << Pn_MOD_MODE9_Pos)      /* P9 */
            | (0x00UL << Pn_MOD_MODE8_Pos)      /* P8 */
            | (0x00UL << Pn_MOD_MODE7_Pos)      /* P7 */
            | (0x00UL << Pn_MOD_MODE6_Pos)      /* P6 */
            | (0x00UL << Pn_MOD_MODE5_Pos)      /* P5 */
            | (0x00UL << Pn_MOD_MODE4_Pos)      /* P4 */
            | (0x00UL << Pn_MOD_MODE3_Pos)      /* P3 */
            | (0x00UL << Pn_MOD_MODE2_Pos)      /* P2 */
            | (0x00UL << Pn_MOD_MODE1_Pos)      /* P1 */
            | (0x00UL << Pn_MOD_MODE0_Pos);     /* P0 */

    PA->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << Pn_TYP_TYP15_Pos)      /* P15 */
            | (0x00UL << Pn_TYP_TYP14_Pos)      /* P14 */
            | (0x00UL << Pn_TYP_TYP13_Pos)      /* P13 */
            | (0x00UL << Pn_TYP_TYP12_Pos)      /* P12 */
            | (0x00UL << Pn_TYP_TYP11_Pos)      /* P11 */
            | (0x00UL << Pn_TYP_TYP10_Pos)      /* P10 */
            | (0x00UL << Pn_TYP_TYP9_Pos)       /* P9 */
            | (0x00UL << Pn_TYP_TYP8_Pos)       /* P8 */
            | (0x00UL << Pn_TYP_TYP7_Pos)       /* P7 */
            | (0x00UL << Pn_TYP_TYP6_Pos)       /* P6 */
            | (0x00UL << Pn_TYP_TYP5_Pos)       /* P5 */
            | (0x00UL << Pn_TYP_TYP4_Pos)       /* P4 */
            | (0x00UL << Pn_TYP_TYP3_Pos)       /* P3 */
            | (0x00UL << Pn_TYP_TYP2_Pos)       /* P2 */
            | (0x00UL << Pn_TYP_TYP1_Pos)       /* P1 */
            | (0x00UL << Pn_TYP_TYP0_Pos);      /* P0 */

    PA->AFSR1 = 0x00UL
            | (0x00UL << Pn_AFSR1_AFSR7_Pos)    /* P7  - 0 : SEG27 1 :        2 :        3 : AN7 4 : AVREF */
            | (0x00UL << Pn_AFSR1_AFSR6_Pos)    /* P6  - 0 : SEG26 1 :        2 :        3 : AN6 4 :  */
            | (0x00UL << Pn_AFSR1_AFSR5_Pos)    /* P5  - 0 :       1 : T12OUT 2 : T12CAP 3 : AN5 4 :  */
            | (0x00UL << Pn_AFSR1_AFSR4_Pos)    /* P4  - 0 :       1 :        2 :        3 : AN4 4 :  */
            | (0x00UL << Pn_AFSR1_AFSR3_Pos)    /* P3  - 0 :       1 :        2 :        3 : AN3 4 :  */
            | (0x00UL << Pn_AFSR1_AFSR2_Pos)    /* P2  - 0 :       1 : EC12   2 :        3 : AN2 4 :  */
            | (0x00UL << Pn_AFSR1_AFSR1_Pos)    /* P1  - 0 :       1 : SCL1   2 :        3 : AN1 4 :  */
            | (0x00UL << Pn_AFSR1_AFSR0_Pos);   /* P0  - 0 :       1 : SDA1   2 :        3 : AN0 4 :  */

    PA->AFSR2 = 0x00UL
            | (0x00UL << Pn_AFSR2_AFSR15_Pos)   /* P15  - 0 : 1 : 2 : 3 :      4 :  */
            | (0x00UL << Pn_AFSR2_AFSR14_Pos)   /* P14  - 0 : 1 : 2 : 3 :      4 :  */
            | (0x00UL << Pn_AFSR2_AFSR13_Pos)   /* P13  - 0 : 1 : 2 : 3 :      4 :  */
            | (0x00UL << Pn_AFSR2_AFSR12_Pos)   /* P12  - 0 : 1 : 2 : 3 :      4 :  */
            | (0x00UL << Pn_AFSR2_AFSR11_Pos)   /* P11  - 0 : 1 : 2 : 3 :      4 :  */
            | (0x00UL << Pn_AFSR2_AFSR10_Pos)   /* P10  - 0 : 1 : 2 : 3 : AN13 4 :  */
            | (0x00UL << Pn_AFSR2_AFSR9_Pos)    /* P9  - 0 : 1 : 2 : 3 : AN12 4 :  */
            | (0x00UL << Pn_AFSR2_AFSR8_Pos);   /* P8  - 0 : 1 : 2 : 3 : AN11 4 :  */

    PA->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down  */
            | (0x00UL << Pn_PUPD_PUPD11_Pos)    /* P11 */
            | (0x00UL << Pn_PUPD_PUPD10_Pos)    /* P10 */
            | (0x00UL << Pn_PUPD_PUPD9_Pos)     /* P9 */
            | (0x00UL << Pn_PUPD_PUPD8_Pos)     /* P8 */
            | (0x00UL << Pn_PUPD_PUPD7_Pos)     /* P7 */
            | (0x00UL << Pn_PUPD_PUPD6_Pos)     /* P6 */
            | (0x00UL << Pn_PUPD_PUPD5_Pos)     /* P5 */
            | (0x00UL << Pn_PUPD_PUPD4_Pos)     /* P4 */
            | (0x00UL << Pn_PUPD_PUPD3_Pos)     /* P3 */
            | (0x00UL << Pn_PUPD_PUPD2_Pos)     /* P2 */
            | (0x00UL << Pn_PUPD_PUPD1_Pos)     /* P1 */
            | (0x00UL << Pn_PUPD_PUPD0_Pos);    /* P0 */

    PA->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << Pn_OUTDR_OUTDR11_Pos)  /* P11 */
            | (0x00UL << Pn_OUTDR_OUTDR10_Pos)  /* P10 */
            | (0x00UL << Pn_OUTDR_OUTDR9_Pos)   /* P9 */
            | (0x00UL << Pn_OUTDR_OUTDR8_Pos)   /* P8 */
            | (0x00UL << Pn_OUTDR_OUTDR7_Pos)   /* P7 */
            | (0x00UL << Pn_OUTDR_OUTDR6_Pos)   /* P6 */
            | (0x00UL << Pn_OUTDR_OUTDR5_Pos)   /* P5 */
            | (0x00UL << Pn_OUTDR_OUTDR4_Pos)   /* P4 */
            | (0x00UL << Pn_OUTDR_OUTDR3_Pos)   /* P3 */
            | (0x00UL << Pn_OUTDR_OUTDR2_Pos)   /* P2 */
            | (0x00UL << Pn_OUTDR_OUTDR1_Pos)   /* P1 */
            | (0x00UL << Pn_OUTDR_OUTDR0_Pos);  /* P0 */

    /* PORT - B */
    PB->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x00UL << Pn_MOD_MODE15_Pos)     /* P15 */
            | (0x00UL << Pn_MOD_MODE14_Pos)     /* P14 */
            | (0x00UL << Pn_MOD_MODE13_Pos)     /* P13 */
            | (0x00UL << Pn_MOD_MODE12_Pos)     /* P12 */
            | (0x00UL << Pn_MOD_MODE11_Pos)     /* P11 */
            | (0x00UL << Pn_MOD_MODE10_Pos)     /* P10 */
            | (0x00UL << Pn_MOD_MODE9_Pos)      /* P9 */
            | (0x00UL << Pn_MOD_MODE8_Pos)      /* P8 */
            | (0x00UL << Pn_MOD_MODE7_Pos)      /* P7 */
            | (0x00UL << Pn_MOD_MODE6_Pos)      /* P6 */
            | (0x02UL << Pn_MOD_MODE5_Pos)      /* P5  - Alternative function mode (SWDIO) */
            | (0x02UL << Pn_MOD_MODE4_Pos)      /* P4  - Alternative function mode (SWCLK) */
            | (0x00UL << Pn_MOD_MODE2_Pos)      /* P2 */
            | (0x02UL << Pn_MOD_MODE3_Pos)      /* P3 */
            | (0x00UL << Pn_MOD_MODE1_Pos)      /* P1 */
            | (0x00UL << Pn_MOD_MODE0_Pos);     /* P0 */

    PB->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << Pn_TYP_TYP15_Pos)      /* P15 */
            | (0x00UL << Pn_TYP_TYP14_Pos)      /* P14 */
            | (0x00UL << Pn_TYP_TYP13_Pos)      /* P13 */
            | (0x00UL << Pn_TYP_TYP12_Pos)      /* P12 */
            | (0x00UL << Pn_TYP_TYP11_Pos)      /* P11 */
            | (0x00UL << Pn_TYP_TYP10_Pos)      /* P10 */
            | (0x00UL << Pn_TYP_TYP9_Pos)       /* P9 */
            | (0x00UL << Pn_TYP_TYP8_Pos)       /* P8 */
            | (0x00UL << Pn_TYP_TYP7_Pos)       /* P7 */
            | (0x00UL << Pn_TYP_TYP6_Pos)       /* P6 */
            | (0x00UL << Pn_TYP_TYP5_Pos)       /* P5 */
            | (0x00UL << Pn_TYP_TYP4_Pos)       /* P4 */
            | (0x00UL << Pn_TYP_TYP3_Pos)       /* P3 */
            | (0x00UL << Pn_TYP_TYP1_Pos)       /* P1 */
            | (0x00UL << Pn_TYP_TYP2_Pos)       /* P2 */
            | (0x00UL << Pn_TYP_TYP0_Pos);      /* P0 */

    PB->AFSR1 = 0x00UL
            | (0x00UL << Pn_AFSR1_AFSR7_Pos)    /* P7  - 0 : SEG34 1 : RXD1  2 :        3 :      4 : */
            | (0x00UL << Pn_AFSR1_AFSR6_Pos)    /* P6  - 0 : SEG35 1 : TXD1  2 :        3 :      4 : */
            | (0x02UL << Pn_AFSR1_AFSR5_Pos)    /* P5  - 0 : SEG36 1 : RXD0  2 : SWDIO  3 :      4 : */
            | (0x02UL << Pn_AFSR1_AFSR4_Pos)    /* P4  - 0 : SEG37 1 : TXD0  2 : SWCLK  3 :      4 : */
            | (0x01UL << Pn_AFSR1_AFSR3_Pos)    /* P3  - 0 : SEG38 1 : BOOT  2 : SS10   3 :      4 : */
            | (0x00UL << Pn_AFSR1_AFSR2_Pos)    /* P2  - 0 : SEG39 1 :       2 : SCK10  3 : AN10 4 : */
            | (0x00UL << Pn_AFSR1_AFSR1_Pos)    /* P1  - 0 : SEG40 1 : RXD10 2 : MISO10 3 : AN9  4 : */
            | (0x00UL << Pn_AFSR1_AFSR0_Pos);   /* P0  - 0 : SEG41 1 : TXD10 2 : MOSI10 3 : AN8  4 : */

    PB->AFSR2 = 0x00UL
            | (0x00UL << Pn_AFSR2_AFSR15_Pos)   /* P15  - 0 : SEG26 1 :        2 :  3 :  4 : */
            | (0x00UL << Pn_AFSR2_AFSR14_Pos)   /* P14  - 0 : SEG27 1 :        2 :  3 :  4 : */
            | (0x00UL << Pn_AFSR2_AFSR13_Pos)   /* P13  - 0 : SEG28 1 :        2 :  3 :  4 : */
            | (0x00UL << Pn_AFSR2_AFSR12_Pos)   /* P12  - 0 : SEG29 1 :        2 :  3 :  4 : */
            | (0x00UL << Pn_AFSR2_AFSR11_Pos)   /* P11  - 0 : SEG30 1 : T15OUT 2 :  3 :  4 : */
            | (0x00UL << Pn_AFSR2_AFSR10_Pos)   /* P10  - 0 : SEG31 1 : T16OUT 2 :  3 :  4 : */
            | (0x00UL << Pn_AFSR2_AFSR9_Pos)    /* P9   - 0 : SEG32 1 : EC15   2 :  3 :  4 : */
            | (0x00UL << Pn_AFSR2_AFSR8_Pos);   /* P8   - 0 : SEG33 1 : EC16   2 :  3 :  4 : */

    PB->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << Pn_PUPD_PUPD15_Pos)    /* P15 */
            | (0x00UL << Pn_PUPD_PUPD14_Pos)    /* P14 */
            | (0x00UL << Pn_PUPD_PUPD13_Pos)    /* P13 */
            | (0x00UL << Pn_PUPD_PUPD12_Pos)    /* P12 */
            | (0x00UL << Pn_PUPD_PUPD11_Pos)    /* P11 */
            | (0x00UL << Pn_PUPD_PUPD10_Pos)    /* P10 */
            | (0x00UL << Pn_PUPD_PUPD9_Pos)     /* P9 */
            | (0x00UL << Pn_PUPD_PUPD8_Pos)     /* P8 */
            | (0x00UL << Pn_PUPD_PUPD7_Pos)     /* P7 */
            | (0x00UL << Pn_PUPD_PUPD6_Pos)     /* P6 */
            | (0x00UL << Pn_PUPD_PUPD5_Pos)     /* P5 */
            | (0x00UL << Pn_PUPD_PUPD4_Pos)     /* P4 */
            | (0x00UL << Pn_PUPD_PUPD3_Pos)     /* P3 */
            | (0x00UL << Pn_PUPD_PUPD2_Pos)     /* P2 */
            | (0x00UL << Pn_PUPD_PUPD1_Pos)     /* P1 */
            | (0x00UL << Pn_PUPD_PUPD0_Pos);    /* P0 */

    PB->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << Pn_OUTDR_OUTDR15_Pos)   /* P15 */
            | (0x00UL << Pn_OUTDR_OUTDR14_Pos)   /* P14 */
            | (0x00UL << Pn_OUTDR_OUTDR13_Pos)   /* P13 */
            | (0x00UL << Pn_OUTDR_OUTDR12_Pos)   /* P12 */
            | (0x00UL << Pn_OUTDR_OUTDR11_Pos)   /* P11 */
            | (0x00UL << Pn_OUTDR_OUTDR10_Pos)   /* P10 */
            | (0x00UL << Pn_OUTDR_OUTDR9_Pos)    /* P9 */
            | (0x00UL << Pn_OUTDR_OUTDR8_Pos)    /* P8 */
            | (0x00UL << Pn_OUTDR_OUTDR7_Pos)    /* P7 */
            | (0x00UL << Pn_OUTDR_OUTDR6_Pos)    /* P6 */
            | (0x00UL << Pn_OUTDR_OUTDR5_Pos)    /* P5 */
            | (0x00UL << Pn_OUTDR_OUTDR3_Pos)    /* P3 */
            | (0x00UL << Pn_OUTDR_OUTDR4_Pos)    /* P4 */
            | (0x00UL << Pn_OUTDR_OUTDR2_Pos)    /* P2 */
            | (0x00UL << Pn_OUTDR_OUTDR1_Pos)    /* P1 */
            | (0x00UL << Pn_OUTDR_OUTDR0_Pos);   /* P0 */

    /* PORT - C */
    PC->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x00UL << Pn_MOD_MODE12_Pos)     /* P12 */
            | (0x00UL << Pn_MOD_MODE11_Pos)     /* P11 */
            | (0x00UL << Pn_MOD_MODE10_Pos)     /* P10 */
            | (0x00UL << Pn_MOD_MODE9_Pos)      /* P9 */
            | (0x00UL << Pn_MOD_MODE8_Pos)      /* P8 */
            | (0x00UL << Pn_MOD_MODE7_Pos)      /* P7 */
            | (0x02UL << Pn_MOD_MODE6_Pos)      /* P6 */
            | (0x02UL << Pn_MOD_MODE5_Pos)      /* P5 */
            | (0x00UL << Pn_MOD_MODE4_Pos)      /* P4 */
            | (0x00UL << Pn_MOD_MODE3_Pos)      /* P3 */
            | (0x00UL << Pn_MOD_MODE2_Pos)      /* P2 */
            | (0x00UL << Pn_MOD_MODE1_Pos)      /* P1 */
            | (0x00UL << Pn_MOD_MODE0_Pos);     /* P0 */

    PC->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << Pn_TYP_TYP12_Pos)    /* P12 */
            | (0x00UL << Pn_TYP_TYP11_Pos)    /* P11 */
            | (0x00UL << Pn_TYP_TYP10_Pos)    /* P10 */
            | (0x00UL << Pn_TYP_TYP9_Pos)     /* P9 */
            | (0x00UL << Pn_TYP_TYP8_Pos)     /* P8 */
            | (0x00UL << Pn_TYP_TYP7_Pos)     /* P7 */
            | (0x00UL << Pn_TYP_TYP6_Pos)     /* P6 */
            | (0x00UL << Pn_TYP_TYP5_Pos)     /* P5 */
            | (0x00UL << Pn_TYP_TYP4_Pos)     /* P4 */
            | (0x00UL << Pn_TYP_TYP3_Pos)     /* P3 */
            | (0x00UL << Pn_TYP_TYP2_Pos)     /* P2 */
            | (0x00UL << Pn_TYP_TYP1_Pos)     /* P1 */
            | (0x00UL << Pn_TYP_TYP0_Pos);    /* P0 */

    PC->AFSR1 = 0x00UL
            | (0x00UL << Pn_AFSR1_AFSR7_Pos)    /* P7  - 0 : SEG18 1 :        2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR6_Pos)    /* P6  - 0 : SEG19 1 : SCL2   2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR5_Pos)    /* P5  - 0 : SEG20 1 : SDA2   2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR4_Pos)    /* P4  - 0 : SEG21 1 :        2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR3_Pos)    /* P3  - 0 : SEG22 1 : EC21   2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR2_Pos)    /* P2  - 0 : SEG23 1 : EC20   2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR1_Pos)    /* P1  - 0 : SEG24 1 : T21OUT 2 : T21CAP 3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR0_Pos);   /* P0  - 0 : SEG25 1 : T20OUT 2 : T20CAP 3 : 4 : */

    PC->AFSR2 = 0x00UL
            | (0x00UL << Pn_AFSR2_AFSR12_Pos)   /* P12  - 0 : SEG13 1 : 2 : 3 : 4 : */
            | (0x00UL << Pn_AFSR2_AFSR11_Pos)   /* P11  - 0 : SEG14 1 : 2 : 3 : 4 : */
            | (0x00UL << Pn_AFSR2_AFSR10_Pos)   /* P10  - 0 : SEG15 1 : 2 : 3 : 4 : */
            | (0x00UL << Pn_AFSR2_AFSR9_Pos)    /* P9   - 0 : SEG16 1 : 2 : 3 : 4 : */
            | (0x00UL << Pn_AFSR2_AFSR8_Pos);   /* P8   - 0 : SEG17 1 : 2 : 3 : 4 : */

    PC->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << Pn_PUPD_PUPD12_Pos)    /* P12 */
            | (0x00UL << Pn_PUPD_PUPD11_Pos)    /* P11 */
            | (0x00UL << Pn_PUPD_PUPD10_Pos)    /* P10 */
            | (0x00UL << Pn_PUPD_PUPD9_Pos)     /* P9 */
            | (0x00UL << Pn_PUPD_PUPD8_Pos)     /* P8 */
            | (0x00UL << Pn_PUPD_PUPD7_Pos)     /* P7 */
            | (0x00UL << Pn_PUPD_PUPD6_Pos)     /* P6 */
            | (0x00UL << Pn_PUPD_PUPD5_Pos)     /* P5 */
            | (0x00UL << Pn_PUPD_PUPD4_Pos)     /* P4 */
            | (0x00UL << Pn_PUPD_PUPD3_Pos)     /* P3 */
            | (0x00UL << Pn_PUPD_PUPD2_Pos)     /* P2 */
            | (0x00UL << Pn_PUPD_PUPD1_Pos)     /* P1 */
            | (0x00UL << Pn_PUPD_PUPD0_Pos);    /* P0 */

    PC->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << Pn_OUTDR_OUTDR12_Pos)  /* P12 */
            | (0x00UL << Pn_OUTDR_OUTDR11_Pos)  /* P11 */
            | (0x00UL << Pn_OUTDR_OUTDR10_Pos)  /* P10 */
            | (0x00UL << Pn_OUTDR_OUTDR9_Pos)   /* P9 */
            | (0x00UL << Pn_OUTDR_OUTDR8_Pos)   /* P8 */
            | (0x00UL << Pn_OUTDR_OUTDR7_Pos)   /* P7 */
            | (0x00UL << Pn_OUTDR_OUTDR6_Pos)   /* P6 */
            | (0x00UL << Pn_OUTDR_OUTDR5_Pos)   /* P5 */
            | (0x00UL << Pn_OUTDR_OUTDR4_Pos)   /* P4 */
            | (0x00UL << Pn_OUTDR_OUTDR3_Pos)   /* P3 */
            | (0x00UL << Pn_OUTDR_OUTDR2_Pos)   /* P2 */
            | (0x00UL << Pn_OUTDR_OUTDR1_Pos)   /* P1 */
            | (0x00UL << Pn_OUTDR_OUTDR0_Pos);  /* P0 */

    /* PORT - D */
    PD->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x00UL << Pn_MOD_MODE7_Pos)   /* P7 */
            | (0x00UL << Pn_MOD_MODE6_Pos)   /* P6 */
            | (0x00UL << Pn_MOD_MODE5_Pos)   /* P5 */
            | (0x00UL << Pn_MOD_MODE4_Pos)   /* P4 */
            | (0x00UL << Pn_MOD_MODE3_Pos)   /* P3 */
            | (0x00UL << Pn_MOD_MODE2_Pos)   /* P2 */
            | (0x00UL << Pn_MOD_MODE1_Pos)   /* P1 */
            | (0x00UL << Pn_MOD_MODE0_Pos);  /* P0 */

    PD->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << Pn_TYP_TYP7_Pos)   /* P7 */
            | (0x00UL << Pn_TYP_TYP6_Pos)   /* P6 */
            | (0x00UL << Pn_TYP_TYP5_Pos)   /* P5 */
            | (0x00UL << Pn_TYP_TYP4_Pos)   /* P4 */
            | (0x00UL << Pn_TYP_TYP3_Pos)   /* P3 */
            | (0x00UL << Pn_TYP_TYP2_Pos)   /* P2 */
            | (0x00UL << Pn_TYP_TYP1_Pos)   /* P1 */
            | (0x00UL << Pn_TYP_TYP0_Pos);  /* P0 */

    PD->AFSR1 = 0x00UL
            | (0x00UL << Pn_AFSR1_AFSR7_Pos)   /* P7  - 0 : SEG5  1 : EC10  2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR6_Pos)   /* P6  - 0 : SEG6  1 : EC11  2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR5_Pos)   /* P5  - 0 : SEG7  1 :       2 : SS11   3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR4_Pos)   /* P4  - 0 : SEG8  1 :       2 : SCK11  3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR3_Pos)   /* P3  - 0 : SEG9  1 : RXD11 2 : MISO11 3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR2_Pos)   /* P2  - 0 : SEG10 1 : TXD11 2 : MOSI11 3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR1_Pos)   /* P1  - 0 : SEG11 1 : SDA0  2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR0_Pos);  /* P0  - 0 : SEG12 1 : SCL0  2 :        3 : 4 : */

    PD->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << Pn_PUPD_PUPD7_Pos)   /* P7 */
            | (0x00UL << Pn_PUPD_PUPD6_Pos)   /* P6 */
            | (0x00UL << Pn_PUPD_PUPD5_Pos)   /* P5 */
            | (0x00UL << Pn_PUPD_PUPD4_Pos)   /* P4 */
            | (0x00UL << Pn_PUPD_PUPD3_Pos)   /* P3 */
            | (0x00UL << Pn_PUPD_PUPD2_Pos)   /* P2 */
            | (0x00UL << Pn_PUPD_PUPD1_Pos)   /* P1 */
            | (0x00UL << Pn_PUPD_PUPD0_Pos);  /* P0 */

    PD->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << Pn_OUTDR_OUTDR7_Pos)   /* P7 */
            | (0x00UL << Pn_OUTDR_OUTDR6_Pos)   /* P6 */
            | (0x00UL << Pn_OUTDR_OUTDR5_Pos)   /* P5 */
            | (0x00UL << Pn_OUTDR_OUTDR4_Pos)   /* P4 */
            | (0x00UL << Pn_OUTDR_OUTDR3_Pos)   /* P3 */
            | (0x00UL << Pn_OUTDR_OUTDR2_Pos)   /* P2 */
            | (0x00UL << Pn_OUTDR_OUTDR1_Pos)   /* P1 */
            | (0x00UL << Pn_OUTDR_OUTDR0_Pos);  /* P0 */


    /* PORT - E */
    PE->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x00UL << Pn_MOD_MODE15_Pos)  /* P15 */
            | (0x00UL << Pn_MOD_MODE14_Pos)  /* P14 */
            | (0x00UL << Pn_MOD_MODE13_Pos)  /* P13 */
            | (0x00UL << Pn_MOD_MODE12_Pos)  /* P12 */
            | (0x00UL << Pn_MOD_MODE11_Pos)  /* P11 */
            | (0x00UL << Pn_MOD_MODE10_Pos)  /* P10 */
            | (0x00UL << Pn_MOD_MODE9_Pos)   /* P9 */
            | (0x00UL << Pn_MOD_MODE8_Pos)   /* P8 */
            | (0x00UL << Pn_MOD_MODE7_Pos)   /* P7 */
            | (0x00UL << Pn_MOD_MODE6_Pos)   /* P6 */
            | (0x00UL << Pn_MOD_MODE5_Pos)   /* P5 */
            | (0x00UL << Pn_MOD_MODE4_Pos)   /* P4 */
            | (0x02UL << Pn_MOD_MODE3_Pos)   /* P3 */
            | (0x02UL << Pn_MOD_MODE2_Pos)   /* P2 */
            | (0x00UL << Pn_MOD_MODE1_Pos)   /* P1 */
            | (0x00UL << Pn_MOD_MODE0_Pos);  /* P0 */

    PE->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << Pn_TYP_TYP15_Pos)   /* P15 */
            | (0x00UL << Pn_TYP_TYP14_Pos)   /* P14 */
            | (0x00UL << Pn_TYP_TYP13_Pos)   /* P13 */
            | (0x00UL << Pn_TYP_TYP12_Pos)   /* P12 */
            | (0x00UL << Pn_TYP_TYP11_Pos)   /* P11 */
            | (0x00UL << Pn_TYP_TYP10_Pos)   /* P10 */
            | (0x00UL << Pn_TYP_TYP9_Pos)    /* P9 */
            | (0x00UL << Pn_TYP_TYP8_Pos)    /* P8 */
            | (0x00UL << Pn_TYP_TYP7_Pos)    /* P7 */
            | (0x00UL << Pn_TYP_TYP6_Pos)    /* P6 */
            | (0x00UL << Pn_TYP_TYP5_Pos)    /* P5 */
            | (0x00UL << Pn_TYP_TYP4_Pos)    /* P4 */
            | (0x00UL << Pn_TYP_TYP3_Pos)    /* P3 */
            | (0x00UL << Pn_TYP_TYP2_Pos)    /* P2 */
            | (0x00UL << Pn_TYP_TYP1_Pos)    /* P1 */
            | (0x00UL << Pn_TYP_TYP0_Pos);   /* P0 */

    PE->AFSR1 = 0x00UL
            | (0x00UL << Pn_AFSR1_AFSR7_Pos)   /* P7 - 0 : COM7/SEG4 1 : T11OUT  2 : T11CAP 3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR6_Pos)   /* P6 - 0 : COM6/SEG3 1 : T10OUT  2 : T10CAP 3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR5_Pos)   /* P5 - 0 : COM5/SEG2 1 : PWM30CB 2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR4_Pos)   /* P4 - 0 : COM4/SEG1 1 : PWM30CA 2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR3_Pos)   /* P3 - 0 : COM3/SEG0 1 : PWM30BB 2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR2_Pos)   /* P2 - 0 : COM2      1 : PWM30BA 2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR1_Pos)   /* P1 - 0 : COM1      1 : PWM30AB 2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR0_Pos);  /* P0 - 0 : COM0      1 : PWM30AA 2 :        3 : 4 : */

    PE->AFSR2 = 0x00UL
            | (0x00UL << Pn_AFSR2_AFSR15_Pos)   /* P15 - 0 : 1 :       2 : SS12   3 : 4 : */
            | (0x00UL << Pn_AFSR2_AFSR14_Pos)   /* P14 - 0 : 1 :       2 : SCK12  3 : 4 : */
            | (0x00UL << Pn_AFSR2_AFSR13_Pos)   /* P13 - 0 : 1 : RXD12 2 : MISO12 3 : 4 : */
            | (0x00UL << Pn_AFSR2_AFSR12_Pos)   /* P12 - 0 : 1 : TXD12 2 : MOSI12 3 : 4 : */
            | (0x00UL << Pn_AFSR2_AFSR11_Pos)   /* P11 - 0 : 1 :       2 : SS13   3 : 4 : */
            | (0x00UL << Pn_AFSR2_AFSR10_Pos)   /* P10 - 0 : 1 :       2 : SCK13  3 : 4 : */
            | (0x00UL << Pn_AFSR2_AFSR9_Pos)    /* P9  - 0 : 1 : RXD13 2 : MISO13 3 : 4 : */
            | (0x00UL << Pn_AFSR2_AFSR8_Pos);   /* P8  - 0 : 1 : TXD13 2 : MOSI13 3 : 4 : */

    PE->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << Pn_PUPD_PUPD15_Pos)   /* P15 */
            | (0x00UL << Pn_PUPD_PUPD14_Pos)   /* P14 */
            | (0x00UL << Pn_PUPD_PUPD13_Pos)   /* P13 */
            | (0x00UL << Pn_PUPD_PUPD12_Pos)   /* P12 */
            | (0x00UL << Pn_PUPD_PUPD11_Pos)   /* P11 */
            | (0x00UL << Pn_PUPD_PUPD10_Pos)   /* P10 */
            | (0x00UL << Pn_PUPD_PUPD9_Pos)    /* P9 */
            | (0x00UL << Pn_PUPD_PUPD8_Pos)    /* P8 */
            | (0x00UL << Pn_PUPD_PUPD7_Pos)    /* P7 */
            | (0x00UL << Pn_PUPD_PUPD6_Pos)    /* P6 */
            | (0x00UL << Pn_PUPD_PUPD5_Pos)    /* P5 */
            | (0x00UL << Pn_PUPD_PUPD4_Pos)    /* P4 */
            | (0x00UL << Pn_PUPD_PUPD3_Pos)    /* P3 */
            | (0x00UL << Pn_PUPD_PUPD2_Pos)    /* P2 */
            | (0x00UL << Pn_PUPD_PUPD1_Pos)    /* P1 */
            | (0x00UL << Pn_PUPD_PUPD0_Pos);   /* P0 */

    PE->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << Pn_OUTDR_OUTDR15_Pos)   /* P15 */
            | (0x00UL << Pn_OUTDR_OUTDR14_Pos)   /* P14 */
            | (0x00UL << Pn_OUTDR_OUTDR13_Pos)   /* P13 */
            | (0x00UL << Pn_OUTDR_OUTDR12_Pos)   /* P12 */
            | (0x00UL << Pn_OUTDR_OUTDR11_Pos)   /* P11 */
            | (0x00UL << Pn_OUTDR_OUTDR10_Pos)   /* P10 */
            | (0x00UL << Pn_OUTDR_OUTDR9_Pos)    /* P9 */
            | (0x00UL << Pn_OUTDR_OUTDR8_Pos)    /* P8 */
            | (0x00UL << Pn_OUTDR_OUTDR7_Pos)    /* P7 */
            | (0x00UL << Pn_OUTDR_OUTDR6_Pos)    /* P6 */
            | (0x00UL << Pn_OUTDR_OUTDR5_Pos)    /* P5 */
            | (0x00UL << Pn_OUTDR_OUTDR4_Pos)    /* P4 */
            | (0x00UL << Pn_OUTDR_OUTDR3_Pos)    /* P3 */
            | (0x00UL << Pn_OUTDR_OUTDR2_Pos)    /* P2 */
            | (0x00UL << Pn_OUTDR_OUTDR1_Pos)    /* P1 */
            | (0x00UL << Pn_OUTDR_OUTDR0_Pos);   /* P0 */

    /* PORT - F */
    PF->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x00UL << Pn_MOD_MODE11_Pos)   /* P11 */
            | (0x00UL << Pn_MOD_MODE10_Pos)   /* P10 */
            | (0x00UL << Pn_MOD_MODE9_Pos)    /* P9 */
            | (0x00UL << Pn_MOD_MODE8_Pos)    /* P8 */
            | (0x00UL << Pn_MOD_MODE7_Pos)    /* P7 */
            | (0x00UL << Pn_MOD_MODE6_Pos)    /* P6 */
            | (0x00UL << Pn_MOD_MODE5_Pos)    /* P5 */
            | (0x00UL << Pn_MOD_MODE4_Pos)    /* P4 */
            | (0x00UL << Pn_MOD_MODE3_Pos)    /* P3 */
            | (0x00UL << Pn_MOD_MODE2_Pos)    /* P2 */
            | (0x02UL << Pn_MOD_MODE1_Pos)    /* P1 */
            | (0x02UL << Pn_MOD_MODE0_Pos);   /* P0 */

    PF->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << Pn_TYP_TYP11_Pos)   /* P11 */
            | (0x00UL << Pn_TYP_TYP10_Pos)   /* P10 */
            | (0x00UL << Pn_TYP_TYP9_Pos)    /* P9 */
            | (0x00UL << Pn_TYP_TYP8_Pos)    /* P8 */
            | (0x00UL << Pn_TYP_TYP7_Pos)    /* P7 */
            | (0x00UL << Pn_TYP_TYP6_Pos)    /* P6 */
            | (0x00UL << Pn_TYP_TYP5_Pos)    /* P5 */
            | (0x00UL << Pn_TYP_TYP4_Pos)    /* P4 */
            | (0x00UL << Pn_TYP_TYP3_Pos)    /* P3 */
            | (0x00UL << Pn_TYP_TYP2_Pos)    /* P2 */
            | (0x00UL << Pn_TYP_TYP1_Pos)    /* P1 */
            | (0x00UL << Pn_TYP_TYP0_Pos);   /* P0 */

    PF->AFSR1 = 0x00UL
            | (0x00UL << Pn_AFSR1_AFSR7_Pos)    /* P7  - 0 :       1 :        2 : T30CAP 3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR6_Pos)    /* P6  - 0 :       1 : EC30   2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR5_Pos)    /* P5  - 0 :       1 : BLNK   2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR4_Pos)    /* P4  - 0 : CLK0  1 :        2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR3_Pos)    /* P3  - 0 : SXOUT 1 :        2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR2_Pos)    /* P2  - 0 : SXIN  1 :        2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR1_Pos)    /* P1  - 0 : XIN   1 : SDA1   2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR1_AFSR0_Pos);   /* P0  - 0 : XOUT  1 : SCL1   2 :        3 : 4 : */

    PF->AFSR2 = 0x00UL
            | (0x00UL << Pn_AFSR2_AFSR11_Pos)   /* P11  - 0 : 1 : T14OUT 2 : T14CAP 3 : 4 : */
            | (0x00UL << Pn_AFSR2_AFSR10_Pos)   /* P10  - 0 : 1 : T13OUT 2 : T13CAP 3 : 4 : */
            | (0x00UL << Pn_AFSR2_AFSR9_Pos)    /* P9   - 0 : 1 : EC14   2 :        3 : 4 : */
            | (0x00UL << Pn_AFSR2_AFSR8_Pos);   /* P8   - 0 : 1 : EC13   2 :        3 : 4 : */

    PF->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << Pn_PUPD_PUPD11_Pos)   /* P11 */
            | (0x00UL << Pn_PUPD_PUPD10_Pos)   /* P10 */
            | (0x00UL << Pn_PUPD_PUPD9_Pos)    /* P9 */
            | (0x00UL << Pn_PUPD_PUPD8_Pos)    /* P8 */
            | (0x00UL << Pn_PUPD_PUPD7_Pos)    /* P7 */
            | (0x00UL << Pn_PUPD_PUPD6_Pos)    /* P6 */
            | (0x00UL << Pn_PUPD_PUPD5_Pos)    /* P5 */
            | (0x00UL << Pn_PUPD_PUPD4_Pos)    /* P4 */
            | (0x00UL << Pn_PUPD_PUPD3_Pos)    /* P3 */
            | (0x00UL << Pn_PUPD_PUPD2_Pos)    /* P2 */
            | (0x00UL << Pn_PUPD_PUPD1_Pos)    /* P1 */
            | (0x00UL << Pn_PUPD_PUPD0_Pos);   /* P0 */

    PF->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << Pn_OUTDR_OUTDR11_Pos)   /* P11 */
            | (0x00UL << Pn_OUTDR_OUTDR10_Pos)   /* P10 */
            | (0x00UL << Pn_OUTDR_OUTDR9_Pos)    /* P9 */
            | (0x00UL << Pn_OUTDR_OUTDR8_Pos)    /* P8 */
            | (0x00UL << Pn_OUTDR_OUTDR7_Pos)    /* P7 */
            | (0x00UL << Pn_OUTDR_OUTDR6_Pos)    /* P6 */
            | (0x00UL << Pn_OUTDR_OUTDR5_Pos)    /* P5 */
            | (0x00UL << Pn_OUTDR_OUTDR4_Pos)    /* P4 */
            | (0x00UL << Pn_OUTDR_OUTDR3_Pos)    /* P3 */
            | (0x00UL << Pn_OUTDR_OUTDR2_Pos)    /* P2 */
            | (0x00UL << Pn_OUTDR_OUTDR1_Pos)    /* P1 */
            | (0x00UL << Pn_OUTDR_OUTDR0_Pos);   /* P0 */

}

extern void SystemClock_Config(void);

#endif /* _STARTUP_A31L21X_H_ */
