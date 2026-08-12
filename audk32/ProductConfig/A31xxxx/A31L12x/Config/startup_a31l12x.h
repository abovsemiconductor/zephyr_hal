/**
 *******************************************************************************
 * @file        startup_a31l12x.h
 * @author      ABOV R&D Division
 * @brief       Startup APIs for A31L12x
 *
 * Copyright 2025 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _STARTUP_A31L12X_H_
#define _STARTUP_A31L12X_H_

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
    if(SCUCC->CHIPID == 0x4D31F004)
    {
        return (int8_t *)"A31L123 : Flash 64KB / SRAM 8KB";
    }
    else if(SCUCC->CHIPID == 0x4D31F005)
    {
        return (int8_t *)"A31L122 : Flash 32KB / SRAM 8KB";
    }
    else
    {
        return (int8_t *)"Unknown";
    }
}

/* Port flash geometry here */
#define STARTUP_FLASH_BASE_ADDR             0x10000000
#define STARTUP_CODE_FLASH_BASE_OFFSET      0x00000000
#define STARTUP_SYSTEM_FLASH_BASE_OFFSET    0x0FFFF000
#define STARTUP_SYSTEM_FLASH_OFFSET_MASK    0x00000FFF
#define STARTUP_PAGE_SIZE                   0x80

#define STARTUP_NON_USER_INFO_BASE_OFFSET   STARTUP_SYSTEM_FLASH_BASE_OFFSET
#define STARTUP_NON_USER_INFO_SIZE          0x200

typedef struct
{
    uint32_t    un32CflashSize;
    uint32_t    un32SystemFlashSize;
    uint32_t    un32CflashWProtectedSegSize;
} CONFIG_FLASH_INFO_t;

static __inline CONFIG_FLASH_INFO_t PRV_CHIPSET_GetFlashGeometricInfo(void);

RAMFUNC static __inline CONFIG_FLASH_INFO_t PRV_CHIPSET_GetFlashGeometricInfo(void)
{
    CONFIG_FLASH_INFO_t tFlashGeometricInfo;

    switch (SCUCC->CHIPID)
    {
        case 0x4D31F004: /* A31L123 */
            tFlashGeometricInfo.un32CflashSize = 0x10000;
            tFlashGeometricInfo.un32SystemFlashSize = 0x800;
            tFlashGeometricInfo.un32CflashWProtectedSegSize = 0x800;
            break;

        case 0x4D31F005: /* A31L122 */
            tFlashGeometricInfo.un32CflashSize = 0x8000;
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
            | (0x00UL << Pn_AFSR1_AFSR7_Pos)    /* P7  - 0 : T43OUTB 1 : EC43   2 :        3 : MOSI1  4 : AN7 5 : CP1P1 6 : CP1OUT 7 : SEG15 */
            | (0x00UL << Pn_AFSR1_AFSR6_Pos)    /* P6  - 0 : T43OUTA 1 : T43INP 2 :        3 : MISO1  4 : AN6 5 :       6 : CP0OUT 7 : SEG16 */
            | (0x00UL << Pn_AFSR1_AFSR5_Pos)    /* P5  - 0 : T40OUTA 1 : T40INP 2 :        3 : SCK1   4 : AN5 5 : CP0N2 6 : CP1N2  7 :       */
            | (0x00UL << Pn_AFSR1_AFSR4_Pos)    /* P4  - 0 :         1 : T43INP 2 : SS1    3 : SCK10  4 : AN4 5 : CP0N1 6 : CP1N1  7 :       */
            | (0x00UL << Pn_AFSR1_AFSR3_Pos)    /* P3  - 0 : T41OUTB 1 : EC41   2 : RXD10  3 : MISO10 4 : AN3 5 : CP1P0 6 : ADTRG  7 : SEG17 */
            | (0x00UL << Pn_AFSR1_AFSR2_Pos)    /* P2  - 0 : T41OUTA 1 : T41INP 2 : TXD10  3 : MOSI10 4 : AN2 5 : CP1N0 6 : CP1OUT 7 : SEG18 */
            | (0x00UL << Pn_AFSR1_AFSR1_Pos)    /* P1  - 0 : T40OUTB 1 : EC40   2 : T42INP 3 : SS10   4 : AN1 5 : CP0P0 6 :        7 : SEG19 */
            | (0x00UL << Pn_AFSR1_AFSR0_Pos);   /* P0  - 0 : T40OUTA 1 : T40INP 2 :        3 :        4 : AN0 5 : CP0N0 6 : CP0OUT 7 :       */

    PA->AFSR2 = 0x00UL
            | (0x00UL << Pn_AFSR2_AFSR9_Pos)    /* P9  - 0 :         1 :        2 : LPTXD  3 :        4 : AN9 5 :       6 :        7 : SEG13 */
            | (0x00UL << Pn_AFSR2_AFSR8_Pos);   /* P8  - 0 :         1 :        2 : LPRXD  3 :        4 : AN8 5 :       6 :        7 : SEG12 */

    PA->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down  */
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
            | (0x00UL << Pn_MOD_MODE12_Pos)     /* P12 */
            | (0x00UL << Pn_MOD_MODE11_Pos)     /* P11 */
            | (0x00UL << Pn_MOD_MODE10_Pos)     /* P10 */
            | (0x00UL << Pn_MOD_MODE9_Pos)      /* P9 */
            | (0x00UL << Pn_MOD_MODE8_Pos)      /* P8 */
            | (0x00UL << Pn_MOD_MODE7_Pos)      /* P7 */
            | (0x00UL << Pn_MOD_MODE6_Pos)      /* P6 */
            | (0x00UL << Pn_MOD_MODE5_Pos)      /* P5  - Alternative function mode (SWDIO) */
            | (0x00UL << Pn_MOD_MODE4_Pos)      /* P4  - Alternative function mode (SWCLK) */
            | (0x00UL << Pn_MOD_MODE2_Pos)      /* P2 */
            | (0x00UL << Pn_MOD_MODE3_Pos)      /* P3 */
            | (0x00UL << Pn_MOD_MODE1_Pos)      /* P1 */
            | (0x00UL << Pn_MOD_MODE0_Pos);     /* P0 */

    PB->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
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
            | (0x00UL << Pn_AFSR1_AFSR7_Pos)    /* P7  - 0 : T42OUTB 1 : EC42   2 : RTCOUT 3 : MISO0 4 : SDA1 5 : LPDE 6 : ADTRG 7 : SEG5  */
            | (0x00UL << Pn_AFSR1_AFSR6_Pos)    /* P6  - 0 : T42OUTA 1 : T42INP 2 :        3 : SCK0  4 : SCL1 5 :      6 :       7 : SEG6  */
            | (0x00UL << Pn_AFSR1_AFSR5_Pos)    /* P5  - 0 :         1 :        2 :        3 : SS0   4 :      5 : LPDE 6 :       7 : SEG7  */
            | (0x00UL << Pn_AFSR1_AFSR4_Pos)    /* P4  - 0 : T41OUTB 1 : EC41   2 : LPRXD  3 :       4 : SDA1 5 :      6 : ADTRG 7 : SEG8  */
            | (0x00UL << Pn_AFSR1_AFSR3_Pos)    /* P3  - 0 : T41OUTA 1 : T41INP 2 : LPTXD  3 : SCK0  4 : SCL1 5 :      6 : ADTRG 7 : SEG9  */
            | (0x00UL << Pn_AFSR1_AFSR2_Pos)    /* P2  - 0 : T50OUT  1 :        2 :        3 :       4 :      5 :      6 :       7 : SEG10 */
            | (0x00UL << Pn_AFSR1_AFSR1_Pos)    /* P1  - 0 :         1 :        2 : RXD1   3 :       4 : AN11 5 : LPDE 6 :       7 : SEG11 */
            | (0x00UL << Pn_AFSR1_AFSR0_Pos);   /* P0  - 0 :         1 :        2 : TXD1   3 :       4 : AN0  5 :      6 :       7 : SEG12 */

    PB->AFSR2 = 0x00UL
            | (0x00UL << Pn_AFSR2_AFSR12_Pos)   /* P12  - 0 : T42INP  1 :        2 :  3 :       4 : 5 : 6 : 7 : SEG0 */
            | (0x00UL << Pn_AFSR2_AFSR11_Pos)   /* P11  - 0 : T43INP  1 :        2 :  3 :       4 : 5 : 6 : 7 : SEG1 */
            | (0x00UL << Pn_AFSR2_AFSR10_Pos)   /* P10  - 0 : T43OUTB 1 : EC43   2 :  3 :       4 : 5 : 6 : 7 : SEG2 */
            | (0x00UL << Pn_AFSR2_AFSR9_Pos)    /* P9   - 0 : T43OUTA 1 : T43INP 2 :  3 :       4 : 5 : 6 : 7 : SEG3 */
            | (0x00UL << Pn_AFSR2_AFSR8_Pos);   /* P8   - 0 :         1 :        2 :  3 : MOSI0 4 : 5 : 6 : 7 : SEG4 */

    PB->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
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
            | (0x00UL << Pn_MOD_MODE11_Pos)     /* P11 */
            | (0x00UL << Pn_MOD_MODE10_Pos)     /* P10 */
            | (0x00UL << Pn_MOD_MODE9_Pos)      /* P9 */
            | (0x00UL << Pn_MOD_MODE8_Pos)      /* P8 */
            | (0x00UL << Pn_MOD_MODE7_Pos)      /* P7 */
            | (0x02UL << Pn_MOD_MODE6_Pos)      /* P6  - Alternative function mode (SWCLK) */
            | (0x02UL << Pn_MOD_MODE5_Pos)      /* P5  - Alternative function mode (SWDIO) */
            | (0x00UL << Pn_MOD_MODE4_Pos)      /* P4 */
            | (0x00UL << Pn_MOD_MODE3_Pos)      /* P3 */
            | (0x00UL << Pn_MOD_MODE2_Pos)      /* P2 */
            | (0x00UL << Pn_MOD_MODE1_Pos)      /* P1 */
            | (0x00UL << Pn_MOD_MODE0_Pos);     /* P0 */

    PC->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
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
            | (0x00UL << Pn_AFSR1_AFSR7_Pos)    /* P7  - 0 : T40OUTA 1 : T40INP 2 : RXD10 3 : MISO10 4 : SC0RST  5 : SC0RXD 6 : SS1    7 : SEG24 */
            | (0x00UL << Pn_AFSR1_AFSR6_Pos)    /* P6  - 0 : SWCLK   1 :        2 : TXD10 3 : MOSI10 4 : SC0DATA 5 : SC0TXD 6 :        7 :       */
            | (0x00UL << Pn_AFSR1_AFSR5_Pos)    /* P5  - 0 : SWDIO   1 :        2 :       3 :        4 :         5 :        6 :        7 :       */
            | (0x00UL << Pn_AFSR1_AFSR4_Pos)    /* P4  - 0 :         1 :        2 :       3 : MOSI1  4 : SC0DATA 5 : SC0TXD 6 : CP1OUT 7 :       */
            | (0x00UL << Pn_AFSR1_AFSR3_Pos)    /* P3  - 0 :         1 :        2 :       3 : MISO1  4 : SC0RST  5 : SC0RXD 6 : CP0OUT 7 :       */
            | (0x00UL << Pn_AFSR1_AFSR2_Pos)    /* P2  - 0 :         1 :        2 : RXD0  3 :        4 : SC0CLK  5 :        6 :        7 : COM2  */
            | (0x00UL << Pn_AFSR1_AFSR1_Pos)    /* P1  - 0 : CLKO    1 :        2 : TXD0  3 :        4 : SC0PWR  5 :        6 :        7 : COM1  */
            | (0x00UL << Pn_AFSR1_AFSR0_Pos);   /* P0  - 0 : CLKO    1 :        2 :       3 :        4 : SC0IN   5 :        6 :        7 : COM0  */

    PC->AFSR2 = 0x00UL
            | (0x00UL << Pn_AFSR2_AFSR11_Pos)   /* P11  - 0 : 1 : 2 : RXD1  3 :       4 :        5 : LPDE 6 : 7 : COM7/SEG28 */
            | (0x00UL << Pn_AFSR2_AFSR10_Pos)   /* P10  - 0 : 1 : 2 : TXD1  3 :       4 : SC0IN  5 :      6 : 7 : COM6/SEG27 */
            | (0x00UL << Pn_AFSR2_AFSR9_Pos)    /* P9   - 0 : 1 : 2 : LPRXD 3 : SS10  4 : SC0PWR 5 :      6 : 7 : COM5/SEG26 */
            | (0x00UL << Pn_AFSR2_AFSR8_Pos);   /* P8   - 0 : 1 : 2 : LPTXD 3 : SCK10 4 : SC0CLK 5 :      6 : 7 : COM4/SEG25 */

    PC->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
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
            | (0x00UL << Pn_AFSR1_AFSR7_Pos)   /* P7  - 0 :         1 :        2 :      3 :       4 :         5 :        6 :       7 : COM3  */
            | (0x00UL << Pn_AFSR1_AFSR6_Pos)   /* P6  - 0 :         1 :        2 :      3 :       4 :         5 :        6 :       7 : SEG32 */
            | (0x00UL << Pn_AFSR1_AFSR5_Pos)   /* P5  - 0 : BOOT    1 :        2 :      3 :       4 :         5 :        6 :       7 :       */
            | (0x00UL << Pn_AFSR1_AFSR4_Pos)   /* P4  - 0 :         1 : T50INP 2 : RXD0 3 :       4 : SC1PWR  5 : SDA0   6 : CP1P5 7 :       */
            | (0x00UL << Pn_AFSR1_AFSR3_Pos)   /* P3  - 0 :         1 :        2 : TXD0 3 :       4 : SC1N    5 : SCL0   6 : CP1P4 7 : VLC0  */
            | (0x00UL << Pn_AFSR1_AFSR2_Pos)   /* P2  - 0 : T43OUTB 1 : EC43   2 : EC50 3 : MOSI1 4 : SC1DATA 5 : SC1TXD 6 : CP1P3 7 : SEG31 */
            | (0x00UL << Pn_AFSR1_AFSR1_Pos)   /* P1  - 0 : T43OUTA 1 : T43INP 2 :      3 : MISO1 4 : SC1RST  5 : SC1RXD 6 : CP1P2 7 : SEG30 */
            | (0x00UL << Pn_AFSR1_AFSR0_Pos);  /* P0  - 0 : T40OUTB 1 : EC40   2 :      3 : SCK1  4 : SC1CLK  5 : CP1N3  6 :       7 : SEG29 */

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
            | (0x00UL << Pn_MOD_MODE4_Pos)   /* P4 */
            | (0x02UL << Pn_MOD_MODE3_Pos)   /* P3 */
            | (0x02UL << Pn_MOD_MODE2_Pos)   /* P2 */
            | (0x00UL << Pn_MOD_MODE1_Pos)   /* P1 */
            | (0x00UL << Pn_MOD_MODE0_Pos);  /* P0 */

    PE->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << Pn_TYP_TYP4_Pos)    /* P4 */
            | (0x00UL << Pn_TYP_TYP3_Pos)    /* P3 */
            | (0x00UL << Pn_TYP_TYP2_Pos)    /* P2 */
            | (0x00UL << Pn_TYP_TYP1_Pos)    /* P1 */
            | (0x00UL << Pn_TYP_TYP0_Pos);   /* P0 */

    PE->AFSR1 = 0x00UL
            | (0x00UL << Pn_AFSR1_AFSR4_Pos)   /* P4 - 0 : RTCOUT 1 : 2 : 3 : 4 : 5 : 6 : 7 : */
            | (0x00UL << Pn_AFSR1_AFSR3_Pos)   /* P3 - 0 : XOUT   1 : 2 : 3 : 4 : 5 : 6 : 7 : */
            | (0x00UL << Pn_AFSR1_AFSR2_Pos)   /* P2 - 0 : XIN    1 : 2 : 3 : 4 : 5 : 6 : 7 : */
            | (0x00UL << Pn_AFSR1_AFSR1_Pos)   /* P1 - 0 : SXOUT  1 : 2 : 3 : 4 : 5 : 6 : 7 : */
            | (0x00UL << Pn_AFSR1_AFSR0_Pos);  /* P0 - 0 : SXIN   1 : 2 : 3 : 4 : 5 : 6 : 7 : */

    PE->AFSR2 = 0x00UL;

    PE->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << Pn_PUPD_PUPD4_Pos)    /* P4 */
            | (0x00UL << Pn_PUPD_PUPD3_Pos)    /* P3 */
            | (0x00UL << Pn_PUPD_PUPD2_Pos)    /* P2 */
            | (0x00UL << Pn_PUPD_PUPD1_Pos)    /* P1 */
            | (0x00UL << Pn_PUPD_PUPD0_Pos);   /* P0 */

    PE->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << Pn_OUTDR_OUTDR4_Pos)    /* P4 */
            | (0x00UL << Pn_OUTDR_OUTDR3_Pos)    /* P3 */
            | (0x00UL << Pn_OUTDR_OUTDR2_Pos)    /* P2 */
            | (0x00UL << Pn_OUTDR_OUTDR1_Pos)    /* P1 */
            | (0x00UL << Pn_OUTDR_OUTDR0_Pos);   /* P0 */

    /* PORT - F */
    PF->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x00UL << Pn_MOD_MODE3_Pos)    /* P3 */
            | (0x00UL << Pn_MOD_MODE2_Pos)    /* P2 */
            | (0x00UL << Pn_MOD_MODE1_Pos)    /* P1 */
            | (0x00UL << Pn_MOD_MODE0_Pos);   /* P0 */

    PF->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << Pn_TYP_TYP3_Pos)    /* P3 */
            | (0x00UL << Pn_TYP_TYP2_Pos)    /* P2 */
            | (0x00UL << Pn_TYP_TYP1_Pos)    /* P1 */
            | (0x00UL << Pn_TYP_TYP0_Pos);   /* P0 */

    PF->AFSR1 = 0x00UL
            | (0x00UL << Pn_AFSR1_AFSR3_Pos)    /* P3  - 0 :        1 :        2 : 3 : MOSI0 4 : AN15 5 : 6 : 7: SEG20 */
            | (0x00UL << Pn_AFSR1_AFSR2_Pos)    /* P2  - 0 :        1 : T50INP 2 : 3 : MISO0 4 : AN14 5 : 6 : 7: SEG21 */
            | (0x00UL << Pn_AFSR1_AFSR1_Pos)    /* P1  - 0 : T50OUT 1 :        2 : 3 :       4 : AN13 5 : 6 : 7: SEG22 */
            | (0x00UL << Pn_AFSR1_AFSR0_Pos);   /* P0  - 0 :        1 : EC50   2 : 3 :       4 : AN12 5 : 6 : 7: SEG23 */

    PF->AFSR2 = 0x00UL;

    PF->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << Pn_PUPD_PUPD3_Pos)    /* P3 */
            | (0x00UL << Pn_PUPD_PUPD2_Pos)    /* P2 */
            | (0x00UL << Pn_PUPD_PUPD1_Pos)    /* P1 */
            | (0x00UL << Pn_PUPD_PUPD0_Pos);   /* P0 */

    PF->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << Pn_OUTDR_OUTDR3_Pos)    /* P3 */
            | (0x00UL << Pn_OUTDR_OUTDR2_Pos)    /* P2 */
            | (0x00UL << Pn_OUTDR_OUTDR1_Pos)    /* P1 */
            | (0x00UL << Pn_OUTDR_OUTDR0_Pos);   /* P0 */

}

extern void SystemClock_Config(void);

#endif /* _STARTUP_A31L12X_H_ */
