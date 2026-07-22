/**
 *******************************************************************************
 * @file        startup_a31g33x.h
 * @author      ABOV R&D Division
 * @brief       Startup APIs for A31G33x
 *
 * Copyright 2025 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _STARTUP_A31G33X_H_
#define _STARTUP_A31G33X_H_

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
#define HSE_CLOCK   (8000000)   /* The clock speed of External High Speed Oscillator (XMOSC) */

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
    if(SCUCC->CHIPID == 0x47313360)
    {
        return (int8_t *)"A31G336 : Flash 256KB / SRAM 32KB";
    }
    else
    {
        return (int8_t *)"Unknown";
    }
}

/* Port flash geometry here */
#define STARTUP_FLASH_BASE_ADDR             0x10000000
#define STARTUP_CODE_FLASH_BASE_OFFSET      0x00000000
#define STARTUP_SYSTEM_FLASH_BASE_OFFSET    0x0FFF0000
#define STARTUP_SYSTEM_FLASH_OFFSET_MASK    0x0000FFFF
#define STARTUP_PAGE_SIZE                   0x200

#define STARTUP_NON_USER_INFO_BASE_OFFSET   STARTUP_SYSTEM_FLASH_BASE_OFFSET
#define STARTUP_NON_USER_INFO_SIZE          0x3000

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
        case 0x47313360: /* A31G336 */
            tFlashGeometricInfo.un32CflashSize = 0x40000;
            tFlashGeometricInfo.un32SystemFlashSize = 0x10000;
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
                    | (0x01UL << SCUCG_PPCLKEN1_PDCLKE_Pos)   /* CLK D */
                    | (0x01UL << SCUCG_PPCLKEN1_PCCLKE_Pos)   /* CLK C */
                    | (0x01UL << SCUCG_PPCLKEN1_PBCLKE_Pos)   /* CLK B */
                    | (0x01UL << SCUCG_PPCLKEN1_PACLKE_Pos);  /* CLK A */

    /*--------------------------------------------------------------
     *    PORT INIT
     *        PA PC PD PE
     *--------------------------------------------------------------*/
    /* PORT - A */
    PA->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x00UL << Pn_MOD_MODE15_Pos)     /* P15 */
            | (0x02UL << Pn_MOD_MODE14_Pos)     /* P14 - SWCLK*/
            | (0x02UL << Pn_MOD_MODE13_Pos)     /* P13 - SWDIO*/
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
            | (0x00UL << Pn_AFSR1_AFSR7_Pos)    /* PA7  - 0: T12OUT      1: T12CAP      2: ----        3: MOSI0       4: EC12        5: AN7         6: ----        7: CP1OUT */
            | (0x00UL << Pn_AFSR1_AFSR6_Pos)    /* PA6  - 0: T11OUT      1: T11CAP      2: ----        3: MISO0       4: EC11        5: AN6         6: ----        7: CP0OUT */
            | (0x00UL << Pn_AFSR1_AFSR5_Pos)    /* PA5  - 0: ----        1: ----        2: ----        3: SCK0        4: EC20        5: AN5         6: CP0N1       7: CP1N1  */
            | (0x00UL << Pn_AFSR1_AFSR4_Pos)    /* PA4  - 0: T20OUT      1: T20CAP      2: SS0         3: SCK10       4: ----        5: AN4         6: CP0N0       7: CP1N0  */
            | (0x00UL << Pn_AFSR1_AFSR3_Pos)    /* PA3  - 0: T15OUT      1: T15CAP      2: RXD10       3: MISO10      4: EC15        5: AN3         6: CP1P0       7: ----   */
            | (0x00UL << Pn_AFSR1_AFSR2_Pos)    /* PA2  - 0: T20OUT      1: T20CAP      2: TXD10       3: MOSI10      4: EC20        5: AN2         6: CP1N2       7: CP1OUT */
            | (0x00UL << Pn_AFSR1_AFSR1_Pos)    /* PA1  - 0: T10OUT      1: T10CAP      2: RXD13       3: MISO13      4: EC10        5: AN1         6: CP0P0       7: SS10   */
            | (0x00UL << Pn_AFSR1_AFSR0_Pos);   /* PA0  - 0: ----        1: ----        2: TXD13       3: MOSI13      4: ----        5: AN0         6: CP0N2       7: CP0OUT */

    PA->AFSR2 = 0x00UL
            | (0x00UL << Pn_AFSR2_AFSR15_Pos)   /* PA15 - 0: ----        1: ----        2: RXD10       3: MISO10      4: EC21        5: ----        6: SS0         7: SS13 */
            | (0x00UL << Pn_AFSR2_AFSR14_Pos)   /* PA14 - 0: SWCLK       1: ----        2: TXD10       3: MOSI10      4: ----        5: ----        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR2_AFSR13_Pos)   /* PA13 - 0: SWDIO       1: ----        2: ----        3: SCK10       4: ----        5: ----        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR2_AFSR10_Pos)   /* PA10 - 0: T15OUT      1: T15CAP      2: RXD11       3: MISO11      4: EC15        5: ----        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR2_AFSR9_Pos)    /* PA9  - 0: T14OUT      1: T14CAP      2: TXD11       3: MOSI11      4: EC14        5: SDA2        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR2_AFSR8_Pos);   /* PA8  - 0: T13OUT      1: T13CAP      2: ----        3: SCK11       4: EC13        5: SCL2        6: ----        7: ---- */

    PA->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down  */
            | (0x00UL << Pn_PUPD_PUPD15_Pos)    /* P15 */
            | (0x02UL << Pn_PUPD_PUPD14_Pos)    /* P14 - SWCLK*/
            | (0x01UL << Pn_PUPD_PUPD13_Pos)    /* P13 - SWDIO*/
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
            | (0x00UL << Pn_OUTDR_OUTDR15_Pos)  /* P15 */
            | (0x00UL << Pn_OUTDR_OUTDR14_Pos)  /* P14 */
            | (0x00UL << Pn_OUTDR_OUTDR13_Pos)  /* P13 */
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
            | (0x00UL << Pn_MOD_MODE5_Pos)      /* P5 */
            | (0x00UL << Pn_MOD_MODE4_Pos)      /* P4 */
            | (0x00UL << Pn_MOD_MODE3_Pos)      /* P3 */
            | (0x00UL << Pn_MOD_MODE2_Pos)      /* P2 */
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
            | (0x00UL << Pn_TYP_TYP2_Pos)       /* P2 */
            | (0x00UL << Pn_TYP_TYP1_Pos)       /* P1 */
            | (0x00UL << Pn_TYP_TYP0_Pos);      /* P0 */

    PB->AFSR1 = 0x00UL
            | (0x00UL << Pn_AFSR1_AFSR7_Pos)    /* PB7  - 0: T12OUT     1: T12CAP      2: RXD11       3: MISO11      4: EC12        5: SDA0        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR6_Pos)    /* PB6  - 0: T11OUT     1: T11CAP      2: TXD11       3: MOSI11      4: EC11        5: SCL0        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR5_Pos)    /* PB5  - 0: T21OUT     1: T21CAP      2: ----        3: MOSI0       4: ----        5: ----        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR4_Pos)    /* PB4  - 0: T15OUT     1: T15CAP      2: ----        3: MISO0       4: EC15        5: ----        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR3_Pos)    /* PB3  - 0: T20OUT     1: T20CAP      2: ----        3: SCK0        4: ----        5: ----        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR2_Pos)    /* PB2  - 0: T14OUT     1: T14CAP      2: ----        3: ----        4: EC14        5: ----        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR1_Pos)    /* PB1  - 0: T13OUT     1: T13CAP      2: ----        3: SS12        4: EC13        5: AN9         6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR0_Pos);   /* PB0  - 0: T21OUT     1: T21CAP      2: ----        3: SCK12       4: ----        5: AN8         6: ----        7: ---- */

    PB->AFSR2 = 0x00UL
            | (0x00UL << Pn_AFSR2_AFSR15_Pos)   /* PB15 - 0: T10OUT     1: T10CAP      2: ----        3: MOSI1       4: EC10        5: ADTRG       6: ----        7: ---- */
            | (0x00UL << Pn_AFSR2_AFSR14_Pos)   /* PB14 - 0: T10OUT     1: T10CAP      2: SS12        3: MISO1       4: EC10        5: SDA1        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR2_AFSR13_Pos)   /* PB13 - 0: T21OUT     1: T21CAP      2: ----        3: SCK1        4: ----        5: SCL1        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR2_AFSR12_Pos)   /* PB12 - 0: T14OUT     1: T14CAP      2: SS1         3: SCK12       4: EC14        5: ----        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR2_AFSR11_Pos)   /* PB11 - 0: T20OUT     1: T20CAP      2: RXD12       3: MISO12      4: ----        5: SDA1        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR2_AFSR10_Pos)   /* PB10 - 0: T20OUT     1: T20CAP      2: TXD12       3: MOSI12      4: ----        5: SCL1        6: SCK1        7: ---- */
            | (0x00UL << Pn_AFSR2_AFSR9_Pos)    /* PB9  - 0: T15OUT     1: T15CAP      2: SS1         3: SS11        4: EC15        5: SDA0        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR2_AFSR8_Pos);   /* PB8  - 0: T14OUT     1: T14CAP      2: ----        3: SCK11       4: EC14        5: SCL0        6: ----        7: ---- */

    PB->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down  */
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
            | (0x00UL << Pn_OUTDR_OUTDR4_Pos)    /* P4 */
            | (0x00UL << Pn_OUTDR_OUTDR3_Pos)    /* P3 */
            | (0x00UL << Pn_OUTDR_OUTDR2_Pos)    /* P2 */
            | (0x00UL << Pn_OUTDR_OUTDR1_Pos)    /* P1 */
            | (0x00UL << Pn_OUTDR_OUTDR0_Pos);   /* P0 */

    /* PORT - C */
    PC->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
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

    PC->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
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

    PC->AFSR1 = 0x00UL
            | (0x00UL << Pn_AFSR1_AFSR7_Pos)    /* PC7 - 0: T11OUT       1: T11CAP      2: ----        3: ----        4: EC11        5: ----        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR6_Pos)    /* PC6 - 0: T21OUT       1: T21CAP      2: ----        3: ----        4: ----        5: ----        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR5_Pos)    /* PC5 - 0: T21OUT       1: T21CAP      2: RXD12       3: MISO12      4: ----        5: AN15        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR4_Pos)    /* PC4 - 0: ----         1: ----        2: TXD12       3: MOSI12      4: ----        5: AN14        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR3_Pos)    /* PC3 - 0: T13OUT       1: T13CAP      2: ----        3: MOSI1       4: EC13        5: AN13        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR2_Pos)    /* PC2 - 0: ----         1: ----        2: ----        3: MISO1       4: ----        5: AN12        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR1_Pos)    /* PC1 - 0: ----         1: ----        2: ----        3: ----        4: ----        5: AN11        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR0_Pos);   /* PC0 - 0: ----         1: ----        2: ----        3: ----        4: ----        5: AN10        6: ----        7: ---- */

    PC->AFSR2 = 0x00UL
            | (0x00UL << Pn_AFSR2_AFSR15_Pos)   /* PC15 - 0: SXOUT       1: ----        2: ----        3: ----        4: ----        5: ----        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR2_AFSR14_Pos)   /* PC14 - 0: SXIN        1: ----        2: ----        3: ----        4: ----        5: ----        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR2_AFSR13_Pos)   /* PC13 - 0: ----        1: RTCOUT      2: ----        3: ----        4: ----        5: ----        6: ----        7: ---- */
            | (0x00UL << Pn_AFSR2_AFSR12_Pos)   /* PC12 - 0: ----        1: ----        2: ----        3: SCK12       4: ----        5: ----        6: SCK13       7: ---- */
            | (0x00UL << Pn_AFSR2_AFSR11_Pos)   /* PC11 - 0: ----        1: ----        2: RXD12       3: MISO12      4: EC21        5: RXD13       6: MISO13      7: ---- */
            | (0x00UL << Pn_AFSR2_AFSR10_Pos)   /* PC10 - 0: ----        1: ----        2: TXD12       3: MOSI12      4: ----        5: TXD13       6: MOSI13      7: ---- */
            | (0x00UL << Pn_AFSR2_AFSR9_Pos)    /* PC9  - 0: ----        1: ----        2: ----        3: ----        4: ----        5: ADTRG       6: ----        7: ---- */
            | (0x00UL << Pn_AFSR2_AFSR8_Pos);   /* PC8  - 0: T12OUT      1: T12CAP      2: ----        3: ----        4: EC12        5: ----        6: ----        7: ---- */

    PC->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down  */
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

    PC->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
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

    /* PORT - D */
    PD->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x02UL << Pn_MOD_MODE5_Pos)   /* P5 - BOOT */
            | (0x00UL << Pn_MOD_MODE4_Pos)   /* P4 */
            | (0x00UL << Pn_MOD_MODE3_Pos)   /* P3 */
            | (0x00UL << Pn_MOD_MODE2_Pos);  /* P2 */

    PD->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << Pn_TYP_TYP5_Pos)    /* P5 */
            | (0x00UL << Pn_TYP_TYP4_Pos)    /* P4 */
            | (0x00UL << Pn_TYP_TYP3_Pos)    /* P3 */
            | (0x00UL << Pn_TYP_TYP2_Pos);   /* P2 */

    PD->AFSR1 = 0x00UL
            | (0x00UL << Pn_AFSR1_AFSR5_Pos)  /* PD5 - 0: BOOT       1: RTCOUT       2: ----        3: ----         4: CLKO        5: CMUSYNC    6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR4_Pos)  /* PD4 - 0: ----       1: ----         2: ----        3: SCK13        4: CLKO        5: ----       6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR3_Pos)  /* PD3 - 0: ----       1: ----         2: ----        3: ----         4: ----        5: SDA2       6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR2_Pos); /* PD2 - 0: ----       1: ----         2: ----        3: ----         4: ----        5: SCL2       6: ----        7: ---- */

    PD->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << Pn_PUPD_PUPD5_Pos)   /* P5 */
            | (0x00UL << Pn_PUPD_PUPD4_Pos)   /* P4 */
            | (0x00UL << Pn_PUPD_PUPD3_Pos)   /* P3 */
            | (0x00UL << Pn_PUPD_PUPD2_Pos);  /* P2 */

    PD->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << Pn_OUTDR_OUTDR5_Pos)  /* P5 */
            | (0x00UL << Pn_OUTDR_OUTDR4_Pos)  /* P4 */
            | (0x00UL << Pn_OUTDR_OUTDR3_Pos)  /* P3 */
            | (0x00UL << Pn_OUTDR_OUTDR2_Pos); /* P2 */


    /* PORT - E */
    PF->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x00UL << Pn_MOD_MODE2_Pos)   /* P2 */
            | (0x02UL << Pn_MOD_MODE1_Pos)   /* P1 */
            | (0x02UL << Pn_MOD_MODE0_Pos);  /* P0 */

    PF->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << Pn_TYP_TYP2_Pos)    /* P2 */
            | (0x00UL << Pn_TYP_TYP1_Pos)    /* P1 */
            | (0x00UL << Pn_TYP_TYP0_Pos);   /* P0 */

    PF->AFSR1 = 0x00UL
            | (0x00UL << Pn_AFSR1_AFSR2_Pos)   /* PF2 - 0: T21OUT     1: T21CAP       2: SS12        3: ----         4: ----        5:  ----      6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR1_Pos)   /* PF1 - 0: XOUT       1: ----         2: ----        3: ----         4: ----        5:  ----      6: ----        7: ---- */
            | (0x00UL << Pn_AFSR1_AFSR0_Pos);  /* PF0 - 0: XIN        1: CLKO         2: ----        3: ----         4: ----        5:  ----      6: ----        7: ---- */

    PF->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << Pn_PUPD_PUPD2_Pos)    /* P2 */
            | (0x00UL << Pn_PUPD_PUPD1_Pos)    /* P1 */
            | (0x00UL << Pn_PUPD_PUPD0_Pos);   /* P0 */

    PF->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << Pn_OUTDR_OUTDR2_Pos)    /* P2 */
            | (0x00UL << Pn_OUTDR_OUTDR1_Pos)    /* P1 */
            | (0x00UL << Pn_OUTDR_OUTDR0_Pos);   /* P0 */

}

extern void SystemClock_Config(void);

#endif /* _STARTUP_A31G33X_H_ */
