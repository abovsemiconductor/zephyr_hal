/**
 *******************************************************************************
 * @file        startup_a31g21x.h
 * @author      ABOV R&D Division
 * @brief       Startup APIs for A31G21x
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _STARTUP_A31G21X_H_
#define _STARTUP_A31G21X_H_

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

#define LSI_CLOCK   (500000)    /* The clock speed of Internal Low Speed Oscillator */
#define LSE_CLOCK   (32768)     /* The clock speed of External Low Speed Oscillator (SXTAL) */
#define HSI_CLOCK   (32000000)  /* The clock speed of Internal High Speed Oscillator */
#define HSE_CLOCK   (8000000)   /* The clock speed of External High Speed Oscillator(XTAL) */

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
    if(SCUCC->CHIPID == 0x4D31A008)
    {
        return (int8_t *)"A31G213 : Flash 64KB / SRAM 6KB";
    }
    else if(SCUCC->CHIPID == 0x4D31A009)
    {
        return (int8_t *)"A31G212 : Flash 32KB / SRAM 6KB";
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
        case 0x4D31A008: /* A31G213 */
            tFlashGeometricInfo.un32CflashSize = 0x10000;
            tFlashGeometricInfo.un32SystemFlashSize = 0x600;
            tFlashGeometricInfo.un32CflashWProtectedSegSize = 0x800;
            break;

        case 0x4D31A009: /* A31G212 */
            tFlashGeometricInfo.un32CflashSize = 0x8000;
            tFlashGeometricInfo.un32SystemFlashSize = 0x600;
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

    SCU->CSCR = (SCU->CSCR & 0x000F0FF) | 0xA5070800U;  /* Enables LSI oscillator and disables HSI, HSE, LSE */
    SCU->SCCR = 0x570A0000U;  /* Select LSI (500kHz) */
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
    PCU->PORTEN = 0x15;
    PCU->PORTEN = 0x51;

    /*--------------------------------------------------------------
     *    PORT INIT
     *        PA PB PC PD PE PF
     *--------------------------------------------------------------*/
    /* PORT - A */
    PA->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x01UL << PORT_MOD_MODE7_Pos)      /* P7 */
            | (0x01UL << PORT_MOD_MODE6_Pos)      /* P6 */
            | (0x01UL << PORT_MOD_MODE5_Pos)      /* P5 */
            | (0x01UL << PORT_MOD_MODE4_Pos)      /* P4 */
            | (0x01UL << PORT_MOD_MODE3_Pos)      /* P3 */
            | (0x01UL << PORT_MOD_MODE2_Pos)      /* P2 */
            | (0x01UL << PORT_MOD_MODE1_Pos)      /* P1 */
            | (0x01UL << PORT_MOD_MODE0_Pos);     /* P0 */

    PA->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << PORT_TYP_TYP7_Pos)       /* P7 */
            | (0x00UL << PORT_TYP_TYP6_Pos)       /* P6 */
            | (0x00UL << PORT_TYP_TYP5_Pos)       /* P5 */
            | (0x00UL << PORT_TYP_TYP4_Pos)       /* P4 */
            | (0x00UL << PORT_TYP_TYP3_Pos)       /* P3 */
            | (0x00UL << PORT_TYP_TYP2_Pos)       /* P2 */
            | (0x00UL << PORT_TYP_TYP1_Pos)       /* P1 */
            | (0x00UL << PORT_TYP_TYP0_Pos);      /* P0 */

    PA->AFSR1 = 0x00UL
            | (0x00UL << PORT_AFSR1_AFSR7_Pos)    /* P7  - 0 :      1 : T130     2 : T13C       3 : AN7/DA0        4 : CS2/COM10 */
            | (0x00UL << PORT_AFSR1_AFSR6_Pos)    /* P6  - 0 :      1 : T11O     2 : T11C       3 : AN6            4 : CS1/COM11 */
            | (0x00UL << PORT_AFSR1_AFSR5_Pos)    /* P5  - 0 :      1 : T12O     2 : T12C       3 : AN5            4 : CS0/COM12 */
            | (0x00UL << PORT_AFSR1_AFSR4_Pos)    /* P4  - 0 :      1 :          2 :            3 : AN4            4 : CS7/COM13 */
            | (0x00UL << PORT_AFSR1_AFSR3_Pos)    /* P3  - 0 :      1 :          2 :            3 : AN3            4 : CS6/COM14 */
            | (0x00UL << PORT_AFSR1_AFSR2_Pos)    /* P2  - 0 :      1 : EC12     2 :            3 : AN2/AVREF      4 : CS5/COM15 */
            | (0x00UL << PORT_AFSR1_AFSR1_Pos)    /* P1  - 0 :      1 : SCL1     2 :            3 : AN1            4 : CS4 */
            | (0x00UL << PORT_AFSR1_AFSR0_Pos);   /* P0  - 0 :      1 : SDA1     2 :            3 : AN0            4 : CS3 */

    PA->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down  */
            | (0x00UL << PORT_PUPD_PUPD7_Pos)     /* P7 */
            | (0x00UL << PORT_PUPD_PUPD6_Pos)     /* P6 */
            | (0x00UL << PORT_PUPD_PUPD5_Pos)     /* P5 */
            | (0x00UL << PORT_PUPD_PUPD4_Pos)     /* P4 */
            | (0x00UL << PORT_PUPD_PUPD3_Pos)     /* P3 */
            | (0x00UL << PORT_PUPD_PUPD2_Pos)     /* P2 */
            | (0x00UL << PORT_PUPD_PUPD1_Pos)     /* P1 */
            | (0x00UL << PORT_PUPD_PUPD0_Pos);    /* P0 */

    PA->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << PORT_OUTDR_OUTDR7_Pos)   /* P7 */
            | (0x00UL << PORT_OUTDR_OUTDR6_Pos)   /* P6 */
            | (0x00UL << PORT_OUTDR_OUTDR5_Pos)   /* P5 */
            | (0x00UL << PORT_OUTDR_OUTDR4_Pos)   /* P4 */
            | (0x00UL << PORT_OUTDR_OUTDR3_Pos)   /* P3 */
            | (0x00UL << PORT_OUTDR_OUTDR2_Pos)   /* P2 */
            | (0x00UL << PORT_OUTDR_OUTDR1_Pos)   /* P1 */
            | (0x00UL << PORT_OUTDR_OUTDR0_Pos);  /* P0 */

    /* PORT - B */
    PB->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x01UL << PORT_MOD_MODE7_Pos)      /* P7 */
            | (0x01UL << PORT_MOD_MODE6_Pos)      /* P6 */
            | (0x02UL << PORT_MOD_MODE5_Pos)      /* P5  - Alternative function mode (SWDIO) */
            | (0x02UL << PORT_MOD_MODE4_Pos)      /* P4  - Alternative function mode (SWCLK) */
            | (0x01UL << PORT_MOD_MODE2_Pos)      /* P2 */
            | (0x02UL << PORT_MOD_MODE3_Pos)      /* P3 */
            | (0x01UL << PORT_MOD_MODE1_Pos)      /* P1 */
            | (0x01UL << PORT_MOD_MODE0_Pos);     /* P0 */

    PB->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << PORT_TYP_TYP7_Pos)       /* P7 */
            | (0x00UL << PORT_TYP_TYP6_Pos)       /* P6 */
            | (0x00UL << PORT_TYP_TYP5_Pos)       /* P5 */
            | (0x00UL << PORT_TYP_TYP4_Pos)       /* P4 */
            | (0x00UL << PORT_TYP_TYP3_Pos)       /* P3 */
            | (0x00UL << PORT_TYP_TYP1_Pos)       /* P1 */
            | (0x00UL << PORT_TYP_TYP2_Pos)       /* P2 */
            | (0x00UL << PORT_TYP_TYP0_Pos);      /* P0 */

    PB->AFSR1 = 0x00UL
            | (0x00UL << PORT_AFSR1_AFSR7_Pos)    /* P7  - 0 :                1 : RXD1           2 :                3 : AN12           4 : CS18 */
            | (0x00UL << PORT_AFSR1_AFSR6_Pos)    /* P6  - 0 :                1 : TXD1           2 : EC11           3 : AN11           4 : CS17 */
            | (0x02UL << PORT_AFSR1_AFSR5_Pos)    /* P5  - 0 :                1 : RXD0           2 : SWDIO          3 :                4 : */
            | (0x02UL << PORT_AFSR1_AFSR4_Pos)    /* P4  - 0 :                1 : TXD0           2 : SWCLK          3 :                4 : */
            | (0x01UL << PORT_AFSR1_AFSR3_Pos)    /* P3  - 0 :                1 : BOOT           2 : SS10           3 :                4 : */
            | (0x00UL << PORT_AFSR1_AFSR2_Pos)    /* P2  - 0 :                1 : EC13           2 : SCK10          3 : AN10           4 : CS10/COM7 */
            | (0x00UL << PORT_AFSR1_AFSR1_Pos)    /* P1  - 0 :                1 : RXD10          2 : MISO10         3 : AN9            4 : CS9/COM8 */
            | (0x00UL << PORT_AFSR1_AFSR0_Pos);   /* P0  - 0 :                1 : TXD10          2 : MOSI10         3 : AN8            4 : CS8/COM9 */

    PB->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << PORT_PUPD_PUPD7_Pos)     /* P7 */
            | (0x00UL << PORT_PUPD_PUPD6_Pos)     /* P6 */
            | (0x00UL << PORT_PUPD_PUPD5_Pos)     /* P5 */
            | (0x00UL << PORT_PUPD_PUPD4_Pos)     /* P4 */
            | (0x00UL << PORT_PUPD_PUPD3_Pos)     /* P3 */
            | (0x00UL << PORT_PUPD_PUPD2_Pos)     /* P2 */
            | (0x00UL << PORT_PUPD_PUPD1_Pos)     /* P1 */
            | (0x00UL << PORT_PUPD_PUPD0_Pos);    /* P0 */

    PB->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << PORT_OUTDR_OUTDR7_Pos)   /* P7 */
            | (0x00UL << PORT_OUTDR_OUTDR6_Pos)   /* P6 */
            | (0x00UL << PORT_OUTDR_OUTDR5_Pos)   /* P5 */
            | (0x00UL << PORT_OUTDR_OUTDR3_Pos)   /* P3 */
            | (0x00UL << PORT_OUTDR_OUTDR4_Pos)   /* P4 */
            | (0x00UL << PORT_OUTDR_OUTDR2_Pos)   /* P2 */
            | (0x00UL << PORT_OUTDR_OUTDR1_Pos)   /* P1 */
            | (0x00UL << PORT_OUTDR_OUTDR0_Pos);  /* P0 */

    /* PORT - C */
    PC->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x02UL << PORT_MOD_MODE5_Pos)      /* P5 */
            | (0x01UL << PORT_MOD_MODE4_Pos)      /* P4 */
            | (0x01UL << PORT_MOD_MODE3_Pos)      /* P3 */
            | (0x01UL << PORT_MOD_MODE2_Pos)      /* P2 */
            | (0x01UL << PORT_MOD_MODE1_Pos)      /* P1 */
            | (0x01UL << PORT_MOD_MODE0_Pos);     /* P0 */

    PC->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << PORT_TYP_TYP5_Pos)       /* P5 */
            | (0x00UL << PORT_TYP_TYP4_Pos)       /* P4 */
            | (0x00UL << PORT_TYP_TYP3_Pos)       /* P3 */
            | (0x00UL << PORT_TYP_TYP2_Pos)       /* P2 */
            | (0x00UL << PORT_TYP_TYP1_Pos)       /* P1 */
            | (0x00UL << PORT_TYP_TYP0_Pos);      /* P0 */

    PC->AFSR1 = 0x00UL
            | (0x00UL << PORT_AFSR1_AFSR5_Pos)    /* P5  - 0 : nRESET         1 :                2 :                3 :                4 : */
            | (0x00UL << PORT_AFSR1_AFSR4_Pos)    /* P4  - 0 :                1 :                2 : SCK20          3 :                4 : CS23/COM2 */
            | (0x00UL << PORT_AFSR1_AFSR3_Pos)    /* P3  - 0 :                1 : EC21           2 : MISO20         3 :                4 : CS22/COM3 */
            | (0x00UL << PORT_AFSR1_AFSR2_Pos)    /* P2  - 0 :                1 : EC20           2 : MOSI20         3 :                4 : CS21/COM4 */
            | (0x00UL << PORT_AFSR1_AFSR1_Pos)    /* P1  - 0 :                1 : T21O           2 : T21C           3 :                4 : CS20/COM5 */
            | (0x00UL << PORT_AFSR1_AFSR0_Pos);   /* P0  - 0 :                1 : T20O           2 : T20C           3 : AN13           4 : CS19/COM6 */

    PC->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << PORT_PUPD_PUPD5_Pos)     /* P5 */
            | (0x00UL << PORT_PUPD_PUPD4_Pos)     /* P4 */
            | (0x00UL << PORT_PUPD_PUPD3_Pos)     /* P3 */
            | (0x00UL << PORT_PUPD_PUPD2_Pos)     /* P2 */
            | (0x00UL << PORT_PUPD_PUPD1_Pos)     /* P1 */
            | (0x00UL << PORT_PUPD_PUPD0_Pos);    /* P0 */

    PC->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << PORT_OUTDR_OUTDR5_Pos)   /* P5 */
            | (0x00UL << PORT_OUTDR_OUTDR4_Pos)   /* P4 */
            | (0x00UL << PORT_OUTDR_OUTDR3_Pos)   /* P3 */
            | (0x00UL << PORT_OUTDR_OUTDR2_Pos)   /* P2 */
            | (0x00UL << PORT_OUTDR_OUTDR1_Pos)   /* P1 */
            | (0x00UL << PORT_OUTDR_OUTDR0_Pos);  /* P0 */

    /* PORT - D */
    PD->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x01UL << PORT_MOD_MODE5_Pos)   /* P5 */
            | (0x01UL << PORT_MOD_MODE4_Pos)   /* P4 */
            | (0x01UL << PORT_MOD_MODE3_Pos)   /* P3 */
            | (0x01UL << PORT_MOD_MODE2_Pos)   /* P2 */
            | (0x01UL << PORT_MOD_MODE1_Pos)   /* P1 */
            | (0x01UL << PORT_MOD_MODE0_Pos);  /* P0 */

    PD->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << PORT_TYP_TYP5_Pos)   /* P5 */
            | (0x00UL << PORT_TYP_TYP4_Pos)   /* P4 */
            | (0x00UL << PORT_TYP_TYP3_Pos)   /* P3 */
            | (0x00UL << PORT_TYP_TYP2_Pos)   /* P2 */
            | (0x00UL << PORT_TYP_TYP1_Pos)   /* P1 */
            | (0x00UL << PORT_TYP_TYP0_Pos);  /* P0 */

    PD->AFSR1 = 0x00UL
            | (0x00UL << PORT_AFSR1_AFSR5_Pos)   /* P5  - 0 :        1 :                2 : SS11           3 :                4 : SEG6 */
            | (0x00UL << PORT_AFSR1_AFSR4_Pos)   /* P4  - 0 :        1 : BLNK           2 : SCK11          3 :                4 : SEG7 */
            | (0x00UL << PORT_AFSR1_AFSR3_Pos)   /* P3  - 0 :        1 : RXD11          2 : MISO11         3 :                4 : SEG8 */
            | (0x00UL << PORT_AFSR1_AFSR2_Pos)   /* P2  - 0 :        1 : TXD11          2 : MOSI11         3 :                4 : SEG9 */
            | (0x00UL << PORT_AFSR1_AFSR1_Pos)   /* P1  - 0 :        1 : SDA0           2 : EC10           3 :                4 : COM2 */
            | (0x00UL << PORT_AFSR1_AFSR0_Pos);  /* P0  - 0 :        1 : SCL0           2 : SS20           3 :                4 : COM1 */

    PD->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << PORT_PUPD_PUPD5_Pos)   /* P5 */
            | (0x00UL << PORT_PUPD_PUPD4_Pos)   /* P4 */
            | (0x00UL << PORT_PUPD_PUPD3_Pos)   /* P3 */
            | (0x00UL << PORT_PUPD_PUPD2_Pos)   /* P2 */
            | (0x00UL << PORT_PUPD_PUPD1_Pos)   /* P1 */
            | (0x00UL << PORT_PUPD_PUPD0_Pos);  /* P0 */

    PD->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << PORT_OUTDR_OUTDR5_Pos)   /* P5 */
            | (0x00UL << PORT_OUTDR_OUTDR4_Pos)   /* P4 */
            | (0x00UL << PORT_OUTDR_OUTDR3_Pos)   /* P3 */
            | (0x00UL << PORT_OUTDR_OUTDR2_Pos)   /* P2 */
            | (0x00UL << PORT_OUTDR_OUTDR1_Pos)   /* P1 */
            | (0x00UL << PORT_OUTDR_OUTDR0_Pos);  /* P0 */


    /* PORT - E */
    PE->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x01UL << PORT_MOD_MODE7_Pos)   /* P7 */
            | (0x01UL << PORT_MOD_MODE6_Pos)   /* P6 */
            | (0x01UL << PORT_MOD_MODE5_Pos)   /* P5 */
            | (0x01UL << PORT_MOD_MODE4_Pos)   /* P4 */
            | (0x01UL << PORT_MOD_MODE3_Pos)   /* P3 */
            | (0x01UL << PORT_MOD_MODE2_Pos)   /* P2 */
            | (0x01UL << PORT_MOD_MODE1_Pos)   /* P1 */
            | (0x01UL << PORT_MOD_MODE0_Pos);  /* P0 */

    PE->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << PORT_TYP_TYP7_Pos)    /* P7 */
            | (0x00UL << PORT_TYP_TYP6_Pos)    /* P6 */
            | (0x00UL << PORT_TYP_TYP5_Pos)    /* P5 */
            | (0x00UL << PORT_TYP_TYP4_Pos)    /* P4 */
            | (0x00UL << PORT_TYP_TYP3_Pos)    /* P3 */
            | (0x00UL << PORT_TYP_TYP2_Pos)    /* P2 */
            | (0x00UL << PORT_TYP_TYP1_Pos)    /* P1 */
            | (0x00UL << PORT_TYP_TYP0_Pos);   /* P0 */

    PE->AFSR1 = 0x00UL
            | (0x00UL << PORT_AFSR1_AFSR7_Pos)   /* P7 - 0 :      1 : T11O           2 : T11C           3 :                4 : CS11/SEG5 */
            | (0x00UL << PORT_AFSR1_AFSR6_Pos)   /* P6 - 0 :      1 : T10O           2 : T10C           3 :                4 : CS12/SEG4 */
            | (0x00UL << PORT_AFSR1_AFSR5_Pos)   /* P5 - 0 :      1 : PWM30CB        2 : MOSI21         3 :                4 : CS13/SEG3 */
            | (0x00UL << PORT_AFSR1_AFSR4_Pos)   /* P4 - 0 :      1 : PWM30CA        2 : MISO21         3 :                4 : CS14/SEG2 */
            | (0x00UL << PORT_AFSR1_AFSR3_Pos)   /* P3 - 0 :      1 : PWM30BB        2 : SCK21          3 :                4 : CS15/SEG1 */
            | (0x00UL << PORT_AFSR1_AFSR2_Pos)   /* P2 - 0 :      1 : PWM30BA        2 : SS21           3 :                4 : CS16/SEG0 */
            | (0x00UL << PORT_AFSR1_AFSR1_Pos)   /* P1 - 0 :      1 : PWM30AB        2 :                3 :                4 : */
            | (0x00UL << PORT_AFSR1_AFSR0_Pos);  /* P0 - 0 :      1 : PWM30AA        2 :                3 :                4 : */

    PE->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << PORT_PUPD_PUPD7_Pos)   /* P7 */
            | (0x00UL << PORT_PUPD_PUPD6_Pos)   /* P6 */
            | (0x00UL << PORT_PUPD_PUPD5_Pos)   /* P5 */
            | (0x00UL << PORT_PUPD_PUPD4_Pos)   /* P4 */
            | (0x00UL << PORT_PUPD_PUPD3_Pos)   /* P3 */
            | (0x00UL << PORT_PUPD_PUPD2_Pos)   /* P2 */
            | (0x00UL << PORT_PUPD_PUPD1_Pos)   /* P1 */
            | (0x00UL << PORT_PUPD_PUPD0_Pos);  /* P0 */

    PE->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << PORT_OUTDR_OUTDR7_Pos)   /* P7 */
            | (0x00UL << PORT_OUTDR_OUTDR6_Pos)   /* P6 */
            | (0x00UL << PORT_OUTDR_OUTDR5_Pos)   /* P5 */
            | (0x00UL << PORT_OUTDR_OUTDR4_Pos)   /* P4 */
            | (0x00UL << PORT_OUTDR_OUTDR3_Pos)   /* P3 */
            | (0x00UL << PORT_OUTDR_OUTDR2_Pos)   /* P2 */
            | (0x00UL << PORT_OUTDR_OUTDR1_Pos)   /* P1 */
            | (0x00UL << PORT_OUTDR_OUTDR0_Pos);  /* P0 */

    /* PORT - F */
    PF->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x01UL << PORT_MOD_MODE7_Pos)   /* P7 */
            | (0x01UL << PORT_MOD_MODE6_Pos)   /* P6 */
            | (0x01UL << PORT_MOD_MODE5_Pos)   /* P5 */
            | (0x01UL << PORT_MOD_MODE4_Pos)   /* P4 */
            | (0x01UL << PORT_MOD_MODE3_Pos)   /* P3 */
            | (0x01UL << PORT_MOD_MODE2_Pos)   /* P2 */
            | (0x02UL << PORT_MOD_MODE1_Pos)   /* P1 */
            | (0x02UL << PORT_MOD_MODE0_Pos);  /* P0 */

    PF->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << PORT_TYP_TYP7_Pos)   /* P7 */
            | (0x00UL << PORT_TYP_TYP6_Pos)   /* P6 */
            | (0x00UL << PORT_TYP_TYP5_Pos)   /* P5 */
            | (0x00UL << PORT_TYP_TYP4_Pos)   /* P4 */
            | (0x00UL << PORT_TYP_TYP3_Pos)   /* P3 */
            | (0x00UL << PORT_TYP_TYP2_Pos)   /* P2 */
            | (0x00UL << PORT_TYP_TYP1_Pos)   /* P1 */
            | (0x00UL << PORT_TYP_TYP0_Pos);  /* P0 */

    PF->AFSR1 = 0x00UL
            | (0x00UL << PORT_AFSR1_AFSR7_Pos)   /* P7  - 0 :            1 : T30C           2 : SDA0           3 :                4 : */
            | (0x00UL << PORT_AFSR1_AFSR6_Pos)   /* P6  - 0 :            1 : EC30           2 : SCL0           3 :                4 : */
            | (0x00UL << PORT_AFSR1_AFSR5_Pos)   /* P5  - 0 :            1 : BLNK           2 :                3 :                4 : */
            | (0x00UL << PORT_AFSR1_AFSR4_Pos)   /* P4  - 0 :            1 : CLKO           2 :                3 :                4 : */
            | (0x00UL << PORT_AFSR1_AFSR3_Pos)   /* P3  - 0 :            1 : RXD1           2 : T30C           3 : SXOUT          4 : */
            | (0x00UL << PORT_AFSR1_AFSR2_Pos)   /* P2  - 0 :            1 : TXD1           2 : EC30           3 : SXIN           4 : */
            | (0x03UL << PORT_AFSR1_AFSR1_Pos)   /* P1  - 0 :            1 : SDA1           2 :                3 : XIN            4 : */
            | (0x03UL << PORT_AFSR1_AFSR0_Pos);  /* P0  - 0 :            1 : SCL1           2 :                3 : XOUT           4 : */

    PF->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << PORT_PUPD_PUPD7_Pos)   /* P7 */
            | (0x00UL << PORT_PUPD_PUPD6_Pos)   /* P6 */
            | (0x00UL << PORT_PUPD_PUPD5_Pos)   /* P5 */
            | (0x00UL << PORT_PUPD_PUPD4_Pos)   /* P4 */
            | (0x00UL << PORT_PUPD_PUPD3_Pos)   /* P3 */
            | (0x00UL << PORT_PUPD_PUPD2_Pos)   /* P2 */
            | (0x00UL << PORT_PUPD_PUPD1_Pos)   /* P1 */
            | (0x00UL << PORT_PUPD_PUPD0_Pos);  /* P0 */

    PF->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << PORT_OUTDR_OUTDR7_Pos)   /* P7 */
            | (0x00UL << PORT_OUTDR_OUTDR6_Pos)   /* P6 */
            | (0x00UL << PORT_OUTDR_OUTDR5_Pos)   /* P5 */
            | (0x00UL << PORT_OUTDR_OUTDR4_Pos)   /* P4 */
            | (0x00UL << PORT_OUTDR_OUTDR3_Pos)   /* P3 */
            | (0x00UL << PORT_OUTDR_OUTDR2_Pos)   /* P2 */
            | (0x00UL << PORT_OUTDR_OUTDR1_Pos)   /* P1 */
            | (0x00UL << PORT_OUTDR_OUTDR0_Pos);  /* P0 */

    /* disable writing permittion of ALL PCU register */
    PCU->PORTEN = 0x00;
}

extern void SystemClock_Config(void);

#endif /* _STARTUP_A31G21X_H_ */
