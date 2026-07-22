/**
 *******************************************************************************
 * @file        startup_a31t21x.h
 * @author      ABOV R&D Division
 * @brief       Startup APIs for A31T21x
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _STARTUP_A31T21X_H_
#define _STARTUP_A31T21X_H_

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
    if(SCUCC->CHIPID == 0x4D31A01D)
    {
        return (int8_t *)"A31T216 : Flash 256KB / SRAM 16KB";
    }
    else if(SCUCC->CHIPID == 0x4D31A01C)
    {
        return (int8_t *)"A31T214 : Flash 128KB / SRAM 16KB";
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
        case 0x4D31A01D: /* A31T216 */
            tFlashGeometricInfo.un32CflashSize = 0x40000;
            tFlashGeometricInfo.un32SystemFlashSize = 0x600;
            tFlashGeometricInfo.un32CflashWProtectedSegSize = 0x2000;
            break;

        case 0x4D31A01C: /* A31T214 */
            tFlashGeometricInfo.un32CflashSize = 0x20000;
            tFlashGeometricInfo.un32SystemFlashSize = 0x600;
            tFlashGeometricInfo.un32CflashWProtectedSegSize = 0x2000;
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

    /* GPIO Access Enable */
    PCU->PORTEN = 0x15;
    PCU->PORTEN = 0x51;

    /* Flash Access Time Configuration */
    FMC->MR = 0x81;
    FMC->MR = 0x28;
    FMC->CFG = (0x7858 << 16) | (3<<8);
    FMC->MR = 0;

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
            | (0x01UL << PORT_MOD_MODE11_Pos)     /* P11 */
            | (0x01UL << PORT_MOD_MODE10_Pos)     /* P10 */
            | (0x01UL << PORT_MOD_MODE9_Pos)      /* P9 */
            | (0x01UL << PORT_MOD_MODE8_Pos)      /* P8 */
            | (0x01UL << PORT_MOD_MODE7_Pos)      /* P7 */
            | (0x01UL << PORT_MOD_MODE6_Pos)      /* P6 */
            | (0x01UL << PORT_MOD_MODE5_Pos)      /* P5 */
            | (0x01UL << PORT_MOD_MODE4_Pos)      /* P4 */
            | (0x01UL << PORT_MOD_MODE3_Pos)      /* P3 */
            | (0x01UL << PORT_MOD_MODE2_Pos)      /* P2 */
            | (0x01UL << PORT_MOD_MODE1_Pos)      /* P1 */
            | (0x01UL << PORT_MOD_MODE0_Pos);     /* P0 */

    PA->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << PORT_TYP_TYP11_Pos)      /* P11 */
            | (0x00UL << PORT_TYP_TYP10_Pos)      /* P10 */
            | (0x00UL << PORT_TYP_TYP9_Pos)       /* P9 */
            | (0x00UL << PORT_TYP_TYP8_Pos)       /* P8 */
            | (0x00UL << PORT_TYP_TYP7_Pos)       /* P7 */
            | (0x00UL << PORT_TYP_TYP6_Pos)       /* P6 */
            | (0x00UL << PORT_TYP_TYP5_Pos)       /* P5 */
            | (0x00UL << PORT_TYP_TYP4_Pos)       /* P4 */
            | (0x00UL << PORT_TYP_TYP3_Pos)       /* P3 */
            | (0x00UL << PORT_TYP_TYP2_Pos)       /* P2 */
            | (0x00UL << PORT_TYP_TYP1_Pos)       /* P1 */
            | (0x00UL << PORT_TYP_TYP0_Pos);      /* P0 */

    PA->AFSR1 = 0x00UL
            | (0x00UL << PORT_AFSR1_AFSB7_Pos)    /* P7  - 0:SEG16 1:     2: 3: 4:AN08       5: */
            | (0x00UL << PORT_AFSR1_AFSB6_Pos)    /* P6  - 0:SEG17 1:SCL1 2: 3: 4:AN09       5: */
            | (0x00UL << PORT_AFSR1_AFSB5_Pos)    /* P5  - 0:SEG18 1:SDA1 2: 3: 4:AN10       5: */
            | (0x00UL << PORT_AFSR1_AFSB4_Pos)    /* P4  - 0:SEG19 1:     2: 3: 4:AN11       5: */
            | (0x00UL << PORT_AFSR1_AFSB3_Pos)    /* P3  - 0:SEG20 1:     2: 3: 4:AN12       5: */
            | (0x00UL << PORT_AFSR1_AFSB2_Pos)    /* P2  - 0:SEG21 1:     2: 3: 4:AN13       5: */
            | (0x00UL << PORT_AFSR1_AFSB1_Pos)    /* P1  - 0:SEG22 1:     2: 3: 4:AN14/AVREF 5: */
            | (0x00UL << PORT_AFSR1_AFSB0_Pos);   /* P0  - 0:      1:SDA1 2: 3: 4:           5: CAPN */

    PA->AFSR2 = 0x00UL
            | (0x00UL << PORT_AFSR2_AFSB11_Pos)   /* P11 - 0:SEG12 1:T13O   2:T13C   3: 4:AN04 5: CS3 */
            | (0x00UL << PORT_AFSR2_AFSB10_Pos)   /* P10 - 0:SEG13 1:(T11O) 2:(T11C) 3: 4:AN05 5: CS2 */
            | (0x00UL << PORT_AFSR2_AFSB9_Pos)    /* P9  - 0:SEG14 1:T12O   2:T12C   3: 4:AN06 5: CS1 */
            | (0x00UL << PORT_AFSR2_AFSB8_Pos);   /* P8  - 0:SEG15 1:       2:       3: 4:AN07 5: CS0 */

    PA->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down  */
            | (0x00UL << PORT_PUPD_PUPD11_Pos)    /* P11 */
            | (0x00UL << PORT_PUPD_PUPD10_Pos)    /* P10 */
            | (0x00UL << PORT_PUPD_PUPD9_Pos)     /* P9 */
            | (0x00UL << PORT_PUPD_PUPD8_Pos)     /* P8 */
            | (0x00UL << PORT_PUPD_PUPD7_Pos)     /* P7 */
            | (0x00UL << PORT_PUPD_PUPD6_Pos)     /* P6 */
            | (0x00UL << PORT_PUPD_PUPD5_Pos)     /* P5 */
            | (0x00UL << PORT_PUPD_PUPD4_Pos)     /* P4 */
            | (0x00UL << PORT_PUPD_PUPD3_Pos)     /* P3 */
            | (0x00UL << PORT_PUPD_PUPD2_Pos)     /* P2 */
            | (0x00UL << PORT_PUPD_PUPD1_Pos)     /* P1 */
            | (0x00UL << PORT_PUPD_PUPD0_Pos);    /* P0 */

    PA->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << PORT_OUTDR_OUTDR11_Pos)  /* P11 */
            | (0x00UL << PORT_OUTDR_OUTDR10_Pos)  /* P10 */
            | (0x00UL << PORT_OUTDR_OUTDR9_Pos)   /* P9 */
            | (0x00UL << PORT_OUTDR_OUTDR8_Pos)   /* P8 */
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
            | (0x01UL << PORT_MOD_MODE11_Pos)     /* P11 */
            | (0x01UL << PORT_MOD_MODE10_Pos)     /* P10 */
            | (0x01UL << PORT_MOD_MODE9_Pos)      /* P9 */
            | (0x01UL << PORT_MOD_MODE8_Pos)      /* P8 */
            | (0x01UL << PORT_MOD_MODE7_Pos)      /* P7 */
            | (0x01UL << PORT_MOD_MODE6_Pos)      /* P6 */
            | (0x01UL << PORT_MOD_MODE5_Pos)      /* P5 */
            | (0x01UL << PORT_MOD_MODE4_Pos)      /* P4 */
            | (0x02UL << PORT_MOD_MODE3_Pos)      /* P3 */
            | (0x01UL << PORT_MOD_MODE2_Pos)      /* P2 */
            | (0x01UL << PORT_MOD_MODE1_Pos)      /* P1 */
            | (0x01UL << PORT_MOD_MODE0_Pos);     /* P0 */

    PB->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << PORT_TYP_TYP11_Pos)      /* P11 */
            | (0x00UL << PORT_TYP_TYP10_Pos)      /* P10 */
            | (0x00UL << PORT_TYP_TYP9_Pos)       /* P9 */
            | (0x00UL << PORT_TYP_TYP8_Pos)       /* P8 */
            | (0x00UL << PORT_TYP_TYP7_Pos)       /* P7 */
            | (0x00UL << PORT_TYP_TYP6_Pos)       /* P6 */
            | (0x00UL << PORT_TYP_TYP5_Pos)       /* P5 */
            | (0x00UL << PORT_TYP_TYP4_Pos)       /* P4 */
            | (0x00UL << PORT_TYP_TYP3_Pos)       /* P3 */
            | (0x00UL << PORT_TYP_TYP1_Pos)       /* P1 */
            | (0x00UL << PORT_TYP_TYP2_Pos)       /* P2 */
            | (0x00UL << PORT_TYP_TYP0_Pos);      /* P0 */

    PB->AFSR1 = 0x00UL
            | (0x00UL << PORT_AFSR1_AFSB7_Pos)    /* P7  - 0:SEG05 1:            2:             3:         4:    5: */
            | (0x00UL << PORT_AFSR1_AFSB6_Pos)    /* P6  - 0:SEG06 1:            2:             3:         4:    5: */
            | (0x00UL << PORT_AFSR1_AFSB5_Pos)    /* P5  - 0:SEG07 1:RXD0        2:(T30C)       3:         4:    5: CS8 */
            | (0x00UL << PORT_AFSR1_AFSB4_Pos)    /* P4  - 0:SEG08 1:TXD0        2:EC30         3:         4:AN0 5: CS7 */
            | (0x01UL << PORT_AFSR1_AFSB3_Pos)    /* P3  - 0:      1:BOOT        2:USART10_SS   3:(SS20)   4:    5: */
            | (0x00UL << PORT_AFSR1_AFSB2_Pos)    /* P2  - 0:SEG09 1:            2:USART10_SCK  3:(SCK20)  4:AN1 5: CS6 */
            | (0x00UL << PORT_AFSR1_AFSB1_Pos)    /* P1  - 0:SEG10 1:USART10_RXD 2:USART10_MISO 3:(MISO20) 4:AN2 5: CS5 */
            | (0x00UL << PORT_AFSR1_AFSB0_Pos);   /* P0  - 0:SEG11 1:USART10_TXD 2:USART10_MOSI 3:(MOSI20) 4:AN3 5: CS4 */

    PB->AFSR2 = 0x00UL
            | (0x00UL << PORT_AFSR2_AFSB11_Pos)   /* P11 - 0:SEG01      1:RXD1 2:EC13 3: 4:AN04 5: CS3 */
            | (0x00UL << PORT_AFSR2_AFSB10_Pos)   /* P10 - 0:COM5/SEG02 1:TXD1 2:EC12 3: 4:AN05 5: CS2 */
            | (0x00UL << PORT_AFSR2_AFSB9_Pos)    /* P9  - 0:COM6/SEG03 1:     2:     3: 4:AN06 5: CS1 */
            | (0x00UL << PORT_AFSR2_AFSB8_Pos);   /* P8  - 0:COM7/SEG04 1:     2:     3: 4:AN07 5: CS0 */

    PB->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << PORT_PUPD_PUPD11_Pos)    /* P11 */
            | (0x00UL << PORT_PUPD_PUPD10_Pos)    /* P10 */
            | (0x00UL << PORT_PUPD_PUPD9_Pos)     /* P9 */
            | (0x00UL << PORT_PUPD_PUPD8_Pos)     /* P8 */
            | (0x00UL << PORT_PUPD_PUPD7_Pos)     /* P7 */
            | (0x00UL << PORT_PUPD_PUPD6_Pos)     /* P6 */
            | (0x00UL << PORT_PUPD_PUPD5_Pos)     /* P5 */
            | (0x00UL << PORT_PUPD_PUPD4_Pos)     /* P4 */
            | (0x00UL << PORT_PUPD_PUPD3_Pos)     /* P3 */
            | (0x00UL << PORT_PUPD_PUPD2_Pos)     /* P2 */
            | (0x00UL << PORT_PUPD_PUPD1_Pos)     /* P1 */
            | (0x00UL << PORT_PUPD_PUPD0_Pos);    /* P0 */

    PB->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << PORT_OUTDR_OUTDR11_Pos)  /* P11 */
            | (0x00UL << PORT_OUTDR_OUTDR10_Pos)  /* P10 */
            | (0x00UL << PORT_OUTDR_OUTDR9_Pos)   /* P9 */
            | (0x00UL << PORT_OUTDR_OUTDR8_Pos)   /* P8 */
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
            | (0x02UL << PORT_MOD_MODE8_Pos)      /* P8 */
            | (0x02UL << PORT_MOD_MODE7_Pos)      /* P7 */
            | (0x02UL << PORT_MOD_MODE6_Pos)      /* P6 */
            | (0x02UL << PORT_MOD_MODE5_Pos)      /* P5 */
            | (0x01UL << PORT_MOD_MODE4_Pos)      /* P4 */
            | (0x01UL << PORT_MOD_MODE3_Pos)      /* P3 */
            | (0x01UL << PORT_MOD_MODE2_Pos)      /* P2 */
            | (0x01UL << PORT_MOD_MODE1_Pos)      /* P1 */
            | (0x01UL << PORT_MOD_MODE0_Pos);     /* P0 */

    PC->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << PORT_TYP_TYP8_Pos)       /* P8 */
            | (0x00UL << PORT_TYP_TYP7_Pos)       /* P7 */
            | (0x00UL << PORT_TYP_TYP6_Pos)       /* P6 */
            | (0x00UL << PORT_TYP_TYP5_Pos)       /* P5 */
            | (0x00UL << PORT_TYP_TYP4_Pos)       /* P4 */
            | (0x00UL << PORT_TYP_TYP3_Pos)       /* P3 */
            | (0x00UL << PORT_TYP_TYP2_Pos)       /* P2 */
            | (0x00UL << PORT_TYP_TYP1_Pos)       /* P1 */
            | (0x00UL << PORT_TYP_TYP0_Pos);      /* P0 */

    PC->AFSR1 = 0x00UL
            | (0x00UL << PORT_AFSR1_AFSB7_Pos)    /* P5  - 0: 1:       2:       3:       4: 5: */
            | (0x00UL << PORT_AFSR1_AFSB6_Pos)    /* P5  - 0: 1:       2:       3:       4: 5: */
            | (0x00UL << PORT_AFSR1_AFSB5_Pos)    /* P5  - 0: 1:       2:       3:       4: 5: */
            | (0x00UL << PORT_AFSR1_AFSB4_Pos)    /* P4  - 0: 1:(T10O) 2:(T10C) 3:SS20   4: 5:ISEG14/CS15 */
            | (0x00UL << PORT_AFSR1_AFSB3_Pos)    /* P3  - 0: 1:       2:EC21   3:SCK20  4: 5:ISEG15/CS14 */
            | (0x00UL << PORT_AFSR1_AFSB2_Pos)    /* P2  - 0: 1:       2:EC20   3:MISO20 4: 5:CS13 */
            | (0x00UL << PORT_AFSR1_AFSB1_Pos)    /* P1  - 0: 1:T21O   2:T21C   3:MOSI20 4: 5:CS12 */
            | (0x00UL << PORT_AFSR1_AFSB0_Pos);   /* P0  - 0: 1:T20O   2:T20C   3:       4: 5:CS11 */

    PC->AFSR2 = 0x00UL
            | (0x00UL << PORT_AFSR2_AFSB8_Pos);   /* P0  - 0: 1: 2: 3: 4: 5: */

    PC->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << PORT_PUPD_PUPD8_Pos)     /* P8 */
            | (0x00UL << PORT_PUPD_PUPD7_Pos)     /* P7 */
            | (0x00UL << PORT_PUPD_PUPD6_Pos)     /* P6 */
            | (0x00UL << PORT_PUPD_PUPD5_Pos)     /* P5 */
            | (0x00UL << PORT_PUPD_PUPD4_Pos)     /* P4 */
            | (0x00UL << PORT_PUPD_PUPD3_Pos)     /* P3 */
            | (0x00UL << PORT_PUPD_PUPD2_Pos)     /* P2 */
            | (0x00UL << PORT_PUPD_PUPD1_Pos)     /* P1 */
            | (0x00UL << PORT_PUPD_PUPD0_Pos);    /* P0 */

    PC->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << PORT_OUTDR_OUTDR8_Pos)   /* P8 */
            | (0x00UL << PORT_OUTDR_OUTDR7_Pos)   /* P7 */
            | (0x00UL << PORT_OUTDR_OUTDR6_Pos)   /* P6 */
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
            | (0x00UL << PORT_AFSR1_AFSB5_Pos)   /* P5  - 0: 1:            2:USART11_SS   3:(SS21)   4: 5:ISEG8/ICOM8/CS21 */
            | (0x00UL << PORT_AFSR1_AFSB4_Pos)   /* P4  - 0: 1:BLNK(PWM)   2:USART11_SCK  3:(SCK21)  4: 5:ISEG9/ICOM9/CS20 */
            | (0x00UL << PORT_AFSR1_AFSB3_Pos)   /* P3  - 0: 1:USART11_RXD 2:USART11_MISO 3:(MISO21) 4: 5:ISEG10/ICOM10/CS19 */
            | (0x00UL << PORT_AFSR1_AFSB2_Pos)   /* P2  - 0: 1:USART11_TXD 2:USART11_MOSI 3:(MOSI21) 4: 5:ISEG11/ICOM11/CS18 */
            | (0x00UL << PORT_AFSR1_AFSB1_Pos)   /* P1  - 0: 1:SDA0        2:EC11         3:         4: 5:ISEG12/ICOM12/CS17 */
            | (0x00UL << PORT_AFSR1_AFSB0_Pos);  /* P0  - 0: 1:SCL0        2:EC10         3:CLKO     4: 5:ISEG13/CS16 */

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
            | (0x02UL << PORT_MOD_MODE12_Pos)  /* P12 */
            | (0x01UL << PORT_MOD_MODE11_Pos)  /* P11 */
            | (0x01UL << PORT_MOD_MODE10_Pos)  /* P10 */
            | (0x01UL << PORT_MOD_MODE9_Pos)   /* P9 */
            | (0x01UL << PORT_MOD_MODE8_Pos)   /* P8 */
            | (0x01UL << PORT_MOD_MODE7_Pos)   /* P7 */
            | (0x01UL << PORT_MOD_MODE6_Pos)   /* P6 */
            | (0x01UL << PORT_MOD_MODE5_Pos)   /* P5 */
            | (0x01UL << PORT_MOD_MODE4_Pos)   /* P4 */
            | (0x01UL << PORT_MOD_MODE3_Pos)   /* P3 */
            | (0x01UL << PORT_MOD_MODE2_Pos)   /* P2 */
            | (0x01UL << PORT_MOD_MODE1_Pos)   /* P1 */
            | (0x01UL << PORT_MOD_MODE0_Pos);  /* P0 */

    PE->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << PORT_TYP_TYP12_Pos)   /* P12 */
            | (0x00UL << PORT_TYP_TYP11_Pos)   /* P11 */
            | (0x00UL << PORT_TYP_TYP10_Pos)   /* P10 */
            | (0x00UL << PORT_TYP_TYP9_Pos)    /* P9 */
            | (0x00UL << PORT_TYP_TYP8_Pos)    /* P8 */
            | (0x00UL << PORT_TYP_TYP7_Pos)    /* P7 */
            | (0x00UL << PORT_TYP_TYP6_Pos)    /* P6 */
            | (0x00UL << PORT_TYP_TYP5_Pos)    /* P5 */
            | (0x00UL << PORT_TYP_TYP4_Pos)    /* P4 */
            | (0x00UL << PORT_TYP_TYP3_Pos)    /* P3 */
            | (0x00UL << PORT_TYP_TYP2_Pos)    /* P2 */
            | (0x00UL << PORT_TYP_TYP1_Pos)    /* P1 */
            | (0x00UL << PORT_TYP_TYP0_Pos);   /* P0 */

    PE->AFSR1 = 0x00UL
            | (0x00UL << PORT_AFSR1_AFSB7_Pos)   /* P7   - 0:COM0       1:PWM30AA 2:       3:          4: 5:ISEG0/ICOM0 */
            | (0x00UL << PORT_AFSR1_AFSB6_Pos)   /* P6   - 0:COM1       1:PWM30AB 2:       3:          4: 5:ISEG1/ICOM1 */
            | (0x00UL << PORT_AFSR1_AFSB5_Pos)   /* P5   - 0:COM2       1:PWM30BA 2:       3:SS21      4: 5:ISEG2/ICOM2 */
            | (0x00UL << PORT_AFSR1_AFSB4_Pos)   /* P4   - 0:COM3/SEG31 1:PWM30BB 2:       3:SCK21     4: 5:ISEG3/ICOM3 */
            | (0x00UL << PORT_AFSR1_AFSB3_Pos)   /* P3   - 0:COM4/SEG0  1:PWM30CA 2:(SDA0) 3:MISO21    4: 5:ISEG4/ICOM4 */
            | (0x00UL << PORT_AFSR1_AFSB2_Pos)   /* P2   - 0:           1:PWM30CB 2:(SCL0) 3:MOSI21    4: 5:ISEG5/ICOM5 */
            | (0x00UL << PORT_AFSR1_AFSB1_Pos)   /* P1   - 0:           1:T10O    2:T10C   3:BLNK(PWM) 4: 5:ISEG6/ICOM6/CS23 */
            | (0x00UL << PORT_AFSR1_AFSB0_Pos);  /* P0   - 0:           1:T11O    2:T11C   3:          4: 5:ISEG7/ICOM7/CS22 */

    PE->AFSR2 = 0x00UL
            | (0x01UL << PORT_AFSR2_AFSB12_Pos)  /* P12  - 0:       1:nRESET 2:       3:       4:       5: */
            | (0x00UL << PORT_AFSR2_AFSB11_Pos)  /* P11  - 0:SEG27  1:       2:       3:       4:VLC0   5: */
            | (0x00UL << PORT_AFSR2_AFSB10_Pos)  /* P10  - 0:SEG28  1:       2:       3:       4:VLC1   5: */
            | (0x00UL << PORT_AFSR2_AFSB9_Pos)   /* P9   - 0:SEG29  1:       2:       3:       4:VLC2   5: */
            | (0x00UL << PORT_AFSR2_AFSB8_Pos);  /* P8   - 0:SEG30  1:       2:       3:       4:VLC3   5: */

    PE->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << PORT_PUPD_PUPD12_Pos)  /* P12 */
            | (0x00UL << PORT_PUPD_PUPD11_Pos)  /* P11 */
            | (0x00UL << PORT_PUPD_PUPD10_Pos)  /* P10 */
            | (0x00UL << PORT_PUPD_PUPD9_Pos)   /* P9 */
            | (0x00UL << PORT_PUPD_PUPD8_Pos)   /* P8 */
            | (0x00UL << PORT_PUPD_PUPD7_Pos)   /* P7 */
            | (0x00UL << PORT_PUPD_PUPD6_Pos)   /* P6 */
            | (0x00UL << PORT_PUPD_PUPD5_Pos)   /* P5 */
            | (0x00UL << PORT_PUPD_PUPD4_Pos)   /* P4 */
            | (0x00UL << PORT_PUPD_PUPD3_Pos)   /* P3 */
            | (0x00UL << PORT_PUPD_PUPD2_Pos)   /* P2 */
            | (0x00UL << PORT_PUPD_PUPD1_Pos)   /* P1 */
            | (0x00UL << PORT_PUPD_PUPD0_Pos);  /* P0 */

    PE->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << PORT_OUTDR_OUTDR12_Pos)  /* P12 */
            | (0x00UL << PORT_OUTDR_OUTDR11_Pos)  /* P11 */
            | (0x00UL << PORT_OUTDR_OUTDR10_Pos)  /* P10 */
            | (0x00UL << PORT_OUTDR_OUTDR9_Pos)   /* P9 */
            | (0x00UL << PORT_OUTDR_OUTDR8_Pos)   /* P8 */
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
            | (0x02UL << PORT_MOD_MODE7_Pos)   /* P7 */
            | (0x02UL << PORT_MOD_MODE6_Pos)   /* P6 */
            | (0x01UL << PORT_MOD_MODE5_Pos)   /* P5 */
            | (0x01UL << PORT_MOD_MODE4_Pos)   /* P4 */
            | (0x01UL << PORT_MOD_MODE3_Pos)   /* P3 */
            | (0x01UL << PORT_MOD_MODE2_Pos)   /* P2 */
            | (0x02UL << PORT_MOD_MODE1_Pos)   /* P1  - Alternative function mode (SWCLK) */
            | (0x02UL << PORT_MOD_MODE0_Pos);  /* P0  - Alternative function mode (SWDIO) */

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
            | (0x04UL << PORT_AFSR1_AFSB7_Pos)   /* P7  - 0:      1:(RXD0) 2:(SCL1) 3:       4:XOUT  5: */
            | (0x04UL << PORT_AFSR1_AFSB6_Pos)   /* P6  - 0:      1:(TXD0) 2:(SDA1) 3:       4:XIN   5: */
            | (0x00UL << PORT_AFSR1_AFSB5_Pos)   /* P5  - 0:      1:(RXD1) 2:(EC30) 3:       4:SXOUT 5: */
            | (0x00UL << PORT_AFSR1_AFSB4_Pos)   /* P4  - 0:      1:(TXD1) 2:       3:       4:SXIN  5: */
            | (0x00UL << PORT_AFSR1_AFSB3_Pos)   /* P3  - 0:SEG23 1:       2:T30C   3:       4:      5: */
            | (0x00UL << PORT_AFSR1_AFSB2_Pos)   /* P2  - 0:SEG24 1:       2:       3:(CLK0) 4:      5: */
            | (0x03UL << PORT_AFSR1_AFSB1_Pos)   /* P1  - 0:SEG25 1:       2:       3:SWCLK  4:      5: */
            | (0x03UL << PORT_AFSR1_AFSB0_Pos);  /* P0  - 0:SEG26 1:       2:       3:SWDIO  4:      5: */

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

#endif /* _STARTUP_A31T21X_H_ */
