/**
 *******************************************************************************
 * @file        startup_a31g32x.h
 * @author      ABOV R&D Division
 * @brief       Startup APIs for A31G32x
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _STARTUP_A31G32X_H_
#define _STARTUP_A31G32X_H_

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

#define LSI_CLOCK   (750000)    /* The clock speed of Internal Low Speed Oscillator */
#define LSE_CLOCK   (32768)     /* The clock speed of External Low Speed Oscillator (SXTAL) */
#define HSI_CLOCK   (48000000)  /* The clock speed of Internal High Speed Oscillator */
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
    if(SCUCC->CHIPID == 0x4D31A006)
    {
        return (int8_t *)"A31G324 : Flash 128KB / SRAM 16KB";
    }
    else if(SCUCC->CHIPID == 0x4D31A007)
    {
        return (int8_t *)"A31G323 : Flash 64KB / SRAM 16KB";
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
        case 0x4D31A006: /* A31G324 */
            tFlashGeometricInfo.un32CflashSize = 0x20000;
            tFlashGeometricInfo.un32SystemFlashSize = 0x600;
            tFlashGeometricInfo.un32CflashWProtectedSegSize = 0x1000;
            break;

        case 0x4D31A007: /* A31G323 */
            tFlashGeometricInfo.un32CflashSize = 0x10000;
            tFlashGeometricInfo.un32SystemFlashSize = 0x600;
            tFlashGeometricInfo.un32CflashWProtectedSegSize = 0x1000;
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
    /* disable WDT ;default ON so you must turn off */
    WDT->CR = 0            |
              (0x5A69<<16) |
              (0x25<<10)   |
              (0x1A<<4);

    SCU->CSCR = (SCU->CSCR & 0x000F0FF) | 0xA5070800U; /* Enable low speed internal oscillator */
    SCU->SCCR = 0x570A0000U; /* Select LSI (500kHz) */
    SCU->CSCR = 0xA5070800U; /* Disable HSI, HSE, LSE */
}

static __inline void PRV_PORT_Init(void)
{
    /* Peripheral Enable Register 1  0:Disable 1:Enable */
    SCU->PER1 |= 0x00UL
              | (0x01UL << SCU_PER1_GPIOF_Pos)    /* GPIO F */
              | (0x01UL << SCU_PER1_GPIOC_Pos)    /* GPIO C */
              | (0x01UL << SCU_PER1_GPIOB_Pos)    /* GPIO B */
              | (0x01UL << SCU_PER1_GPIOA_Pos);   /* GPIO A */

    /* Peripheral Clock Enable Register 1 0:Disable 1:Enable */
    SCU->PCER1 |= 0x00UL
               | (0x01UL << SCU_PCER1_GPIOF_Pos)  /* GPIO F */
               | (0x01UL << SCU_PCER1_GPIOC_Pos)  /* GPIO C */
               | (0x01UL << SCU_PCER1_GPIOB_Pos)  /* GPIO B */
               | (0x01UL << SCU_PCER1_GPIOA_Pos); /* GPIO A */

    /* enable writing permittion of ALL PCU register */
    PCU->PORTEN = 0x15;
    PCU->PORTEN = 0x51;

    /*--------------------------------------------------------------
     *    PORT INIT
     *        PA PB PC PF
     *-------------------------------------------------------------- */
    /* PORT - A */
    PA->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x01UL << PORT_MOD_MODE15_Pos)     /* P15 */
            | (0x02UL << PORT_MOD_MODE14_Pos)     /* P14 */
            | (0x02UL << PORT_MOD_MODE13_Pos)     /* P13 */
            | (0x01UL << PORT_MOD_MODE12_Pos)     /* P12 */
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
            | (0x00UL << PORT_TYP_TYP15_Pos)      /* P15 */
            | (0x00UL << PORT_TYP_TYP14_Pos)      /* P14 */
            | (0x00UL << PORT_TYP_TYP13_Pos)      /* P13 */
            | (0x00UL << PORT_TYP_TYP12_Pos)      /* P12 */
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
            | (0x00UL << PORT_AFSR1_AFSR7_Pos)    /* P7  - 0:SPI20_MOSI  1:CP1_OUT      2:             3:PWM30AB 4:EC12 5:T12CAP 6:T12OUT 7:T40CAP_CH2 8:T40OUT 9:A19 10:AN7 */
            | (0x00UL << PORT_AFSR1_AFSR6_Pos)    /* P6  - 0:SPI20_MISO  1:CP0_OUT      2:             3:BLNK30  4:EC11 5:T11CAP 6:T11OUT 7:T40CAP_CH1 8:T40OUT 9:RD  10:AN6 */
            | (0x00UL << PORT_AFSR1_AFSR5_Pos)    /* P5  - 0:SPI20_SCK   1:             2:             3:        4:EC20 5:       6:       7:           8:       9:    10:AN5/CP0_N1/CP1_N1/DAC_OU/T2 */
            | (0x00UL << PORT_AFSR1_AFSR4_Pos)    /* P4  - 0:SPI20_SS    1:             2:USART11_SCK  3:        4:     5:       6:       7:           8:       9:    10:AN4/CP0_N0/CP1_N0/DAC_OU/T1 */
            | (0x00UL << PORT_AFSR1_AFSR3_Pos)    /* P3  - 0:USART11_RXD 1:             2:USART11_MISO 3:        4:EC10 5:T10CAP 6:T10OUT 7:T20CAP     8:T20OUT 9:    10:AN3/CP1_P0 */
            | (0x00UL << PORT_AFSR1_AFSR2_Pos)    /* P2  - 0:USART11_TXD 1:             2:USART11_MOSI 3:CP1_OUT 4:EC10 5:T10CAP 6:T10OUT 7:T20CAP     8:T20OUT 9:    10:AN2/CP1_N2 */
            | (0x00UL << PORT_AFSR1_AFSR1_Pos)    /* P1  - 0:USART13_RXD 1:USART13_MISO 2:USART11_SS   3:        4:EC13 5:T13CAP 6:T13OUT 7:T20CAP     8:T20OUT 9:    10:AN1/CP0_P0 */
            | (0x00UL << PORT_AFSR1_AFSR0_Pos);   /* P0  - 0:USART13_TXD 1:USART13_MOSI 2:             3:CP0_OUT 4:EC20 5:       6:       7:RTC_TAMP2  8:       9:    10:AN0/CP0_N2 */

    PA->AFSR2 = 0x00UL
            | (0x00UL << PORT_AFSR2_AFSR15_Pos)   /* P15  - 0:USART11_RXD 1:USART13_SS   2:USART11_MISO 3:SPI20_SS 4:EC21   5:   6:   7:   8:   9:ALE  10: */
            | (0x01UL << PORT_AFSR2_AFSR14_Pos)   /* P14  - 0:USART11_TXD 1:SWCLK        2:USART11_MOSI 3:         4:       5:   6:   7:   8:   9:     10: */
            | (0x01UL << PORT_AFSR2_AFSR13_Pos)   /* P13  - 0:            1:SWDIO        2:             3:         4:       5:   6:   7:   8:   9:     10: */
            | (0x00UL << PORT_AFSR2_AFSR12_Pos)   /* P12  - 0:CP1_OUT     1:USART10_SS   2:             3:EC30     4:T30CAP 5:   6:   7:   8:   9:AD03 10:USBDP */
            | (0x00UL << PORT_AFSR2_AFSR11_Pos)   /* P11  - 0:CP0_OUT     1:             2:             3:         4:       5:   6:   7:   8:   9:AD04 10:USBDM */
            | (0x00UL << PORT_AFSR2_AFSR10_Pos)   /* P10  - 0:USART10_RXD 1:USART10_MISO 2:             3:PWM30CA  4:EC21   5:   6:   7:   8:   9:AD05 10: */
            | (0x00UL << PORT_AFSR2_AFSR9_Pos)    /* P9   - 0:USART10_TXD 1:USART10_MOSI 2:             3:PWM30BA  4:       5:   6:   7:   8:   9:AD06 10: */
            | (0x00UL << PORT_AFSR2_AFSR8_Pos);   /* P8   - 0:            1:USART10_SCK  2:             3:PWM30AA  4:       5:   6:   7:   8:   9:AD07 10: */

    PA->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << PORT_PUPD_PUPD15_Pos)    /* P15 */
            | (0x00UL << PORT_PUPD_PUPD14_Pos)    /* P14 */
            | (0x00UL << PORT_PUPD_PUPD13_Pos)    /* P13 */
            | (0x00UL << PORT_PUPD_PUPD12_Pos)    /* P12 */
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
            | (0x00UL << PORT_OUTDR_OUTDR15_Pos)  /* P15 */
            | (0x00UL << PORT_OUTDR_OUTDR14_Pos)  /* P14 */
            | (0x00UL << PORT_OUTDR_OUTDR13_Pos)  /* P13 */
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

    /* PORT - B */
    PB->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x01UL << PORT_MOD_MODE15_Pos)     /* P15 */
            | (0x01UL << PORT_MOD_MODE14_Pos)     /* P14 */
            | (0x01UL << PORT_MOD_MODE13_Pos)     /* P13 */
            | (0x01UL << PORT_MOD_MODE12_Pos)     /* P12 */
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

    PB->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << PORT_TYP_TYP15_Pos)      /* P15 */
            | (0x00UL << PORT_TYP_TYP14_Pos)      /* P14 */
            | (0x00UL << PORT_TYP_TYP13_Pos)      /* P13 */
            | (0x00UL << PORT_TYP_TYP12_Pos)      /* P12 */
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

    PB->AFSR1 = 0x00UL
            | (0x00UL << PORT_AFSR1_AFSR7_Pos)    /* P7  - 0:USART10_RXD 1:USART10_MISO 2:I2C0_SDA 3:           4:EC12 5:T12CAP 6:T12OUT 7:           8:       9:CS   10: */
            | (0x00UL << PORT_AFSR1_AFSR6_Pos)    /* P6  - 0:USART10_TXD 1:USART10_MOSI 2:I2C0_SCL 3:           4:EC11 5:T11CAP 6:T11OUT 7:T40CAP_CH3 8:T40OUT 9:LWR  10: */
            | (0x00UL << PORT_AFSR1_AFSR5_Pos)    /* P5  - 0:            1:             2:         3:SPI20_MOSI 4:     5:T21CAP 6:T21OUT 7:T40CAP_CH2 8:T40OUT 9:AD00 10: */
            | (0x00UL << PORT_AFSR1_AFSR4_Pos)    /* P4  - 0:            1:             2:         3:SPI20_MISO 4:     5:       6:       7:T40CAP_CH1 8:T40OUT 9:AD01 10: */
            | (0x00UL << PORT_AFSR1_AFSR3_Pos)    /* P3  - 0:            1:             2:         3:SPI20_SCK  4:     5:T20CAP 6:T20OUT 7:           8:       9:AD02 10: */
            | (0x00UL << PORT_AFSR1_AFSR2_Pos)    /* P2  - 0:            1:             2:         3:           4:EC13 5:T13CAP 6:T13OUT 7:           8:       9:AD14 10: */
            | (0x00UL << PORT_AFSR1_AFSR1_Pos)    /* P1  - 0:            1:USART12_SS   2:         3:PWM30CB    4:EC13 5:T13CAP 6:T13OUT 7:           8:       9:AD15 10:AN9 */
            | (0x00UL << PORT_AFSR1_AFSR0_Pos);   /* P0  - 0:            1:USART12_SCK  2:         3:PWM30BB    4:     5:T21CAP 6:T21OUT 7:T40CAP_CH3 8:T40OUT 9:A16  10:AN8 */

    PB->AFSR2 = 0x00UL
            | (0x00UL << PORT_AFSR2_AFSR15_Pos)   /* P15  - 0:SPI21_MOSI  1:             2:         3:PWM30CB   4:EC10 5:T10CAP 6:T10OUT 7:T21CAP 8:T21OUT 9:AD08 10: */
            | (0x00UL << PORT_AFSR2_AFSR14_Pos)   /* P14  - 0:SPI21_MISO  1:USART12_SS   2:I2C1_SDA 3:PWM30BB   4:EC10 5:T10CAP 6:T10OUT 7:       8:       9:AD09 10: */
            | (0x00UL << PORT_AFSR2_AFSR13_Pos)   /* P13  - 0:SPI21_SCK   1:             2:I2C1_SCL 3:PWM30AB   4:     5:       6:       7:       8:       9:AD10 10: */
            | (0x00UL << PORT_AFSR2_AFSR12_Pos)   /* P12  - 0:SPI21_SS    1:USART12_SCK  2:         3:BLNK30    4:EC13 5:T13CAP 6:T13OUT 7:       8:       9:AD11 10: */
            | (0x00UL << PORT_AFSR2_AFSR11_Pos)   /* P11  - 0:USART12_RXD 1:USART12_MISO 2:I2C1_SDA 3:          4:     5:T20CAP 6:T20OUT 7:       8:       9:AD12 10: */
            | (0x00UL << PORT_AFSR2_AFSR10_Pos)   /* P10  - 0:USART12_TXD 1:USART12_MOSI 2:I2C1_SCL 3:SPI21_SCK 4:     5:T20CAP 6:T20OUT 7:       8:       9:AD13 10: */
            | (0x00UL << PORT_AFSR2_AFSR9_Pos)    /* P9   - 0:            1:ISC0_SDL     2:         3:SPI21_SS  4:EC12 5:T12CAP 6:T12OUT 7:       8:       9:     10: */
            | (0x00UL << PORT_AFSR2_AFSR8_Pos);   /* P8   - 0:            1:I2C0_SCL     2:         3:          4:EC11 5:T11CAP 6:T11OUT 7:       8:       9:     10: */

    PB->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << PORT_PUPD_PUPD15_Pos)    /* P15 */
            | (0x00UL << PORT_PUPD_PUPD14_Pos)    /* P14 */
            | (0x00UL << PORT_PUPD_PUPD13_Pos)    /* P13 */
            | (0x00UL << PORT_PUPD_PUPD12_Pos)    /* P12 */
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
            | (0x00UL << PORT_OUTDR_OUTDR15_Pos)  /* P15 */
            | (0x00UL << PORT_OUTDR_OUTDR14_Pos)  /* P14 */
            | (0x00UL << PORT_OUTDR_OUTDR13_Pos)  /* P13 */
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

    /* PORT - C */
    PC->MOD = 0x00UL  /* 0 : Input Mode 1 : Output Mode 2 : Alternative function mode */
            | (0x01UL << PORT_MOD_MODE15_Pos)     /* P15 */
            | (0x01UL << PORT_MOD_MODE14_Pos)     /* P14 */
            | (0x01UL << PORT_MOD_MODE13_Pos)     /* P13 */
            | (0x01UL << PORT_MOD_MODE12_Pos)     /* P12 */
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

    PC->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << PORT_TYP_TYP15_Pos)      /* P15 */
            | (0x00UL << PORT_TYP_TYP14_Pos)      /* P14 */
            | (0x00UL << PORT_TYP_TYP13_Pos)      /* P13 */
            | (0x00UL << PORT_TYP_TYP12_Pos)      /* P12 */
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

    PC->AFSR1 = 0x00UL
            | (0x00UL << PORT_AFSR1_AFSR7_Pos)    /* P7  - 0:            1:             2:   3:   4:     5:       6:       7:T40CAP_CH2 8:T40OUT 9:UDS   10: */
            | (0x00UL << PORT_AFSR1_AFSR6_Pos)    /* P6  - 0:            1:             2:   3:   4:     5:T21CAP 6:T21OUT 7:T40CAP_CH1 8:T40OUT 9:NWAIT 10: */
            | (0x00UL << PORT_AFSR1_AFSR5_Pos)    /* P5  - 0:USART12_RXD 1:USART12_MISO 2:   3:   4:     5:T21CAP 6:T21OUT 7:           8:       9:A17   10:AN15 */
            | (0x00UL << PORT_AFSR1_AFSR4_Pos)    /* P4  - 0:USART12_TXD 1:USART12_MOSI 2:   3:   4:     5:       6:       7:EC40       8:       9:A18   10:AN14 */
            | (0x00UL << PORT_AFSR1_AFSR3_Pos)    /* P3  - 0:SPI21_MOSI  1:             2:   3:   4:EC13 5:T13CAP 6:T13OUT 7:           8:       9:AD02  10:AN13 */
            | (0x00UL << PORT_AFSR1_AFSR2_Pos)    /* P2  - 0:SPI21_MISO  1:             2:   3:   4:     5:       6:       7:           8:       9:AD01  10:AN12 */
            | (0x00UL << PORT_AFSR1_AFSR1_Pos)    /* P1  - 0:            1:             2:   3:   4:     5:       6:       7:           8:       9:AD00  10:AN11/CP1_P1 */
            | (0x00UL << PORT_AFSR1_AFSR0_Pos);   /* P0  - 0:            1:             2:   3:   4:     5:       6:       7:           8:       9:LWR   10:AN10/CP0_P1 */

    PC->AFSR2 = 0x00UL
            | (0x00UL << PORT_AFSR2_AFSR15_Pos)   /* P15  - 0:            1:             2:            3:             4:     5:   6:   7:           8:       9:    10:SXOUT */
            | (0x00UL << PORT_AFSR2_AFSR14_Pos)   /* P14  - 0:            1:             2:            3:             4:     5:   6:   7:           8:       9:    10:SXIN */
            | (0x00UL << PORT_AFSR2_AFSR13_Pos)   /* P13  - 0:            1:             2:            3:             4:     5:   6:   7:RTC_TA/MP1 8:       9:    10: */
            | (0x00UL << PORT_AFSR2_AFSR12_Pos)   /* P12  - 0:            1:USART13_SCK  2:            3:USART12_SCK  4:     5:   6:   7:           8:       9:CS2 10: */
            | (0x00UL << PORT_AFSR2_AFSR11_Pos)   /* P11  - 0:USART13_RXD 1:USART13_MISO 2:USART12_RXD 3:USART12_MISO 4:EC21 5:   6:   7:           8:       9:RD  10: */
            | (0x00UL << PORT_AFSR2_AFSR10_Pos)   /* P10  - 0:USART13_TXD 1:USART13_MOSI 2:USART12_TXD 3:USART12_MOSI 4:     5:   6:   7:           8:       9:LDS 10: */
            | (0x00UL << PORT_AFSR2_AFSR9_Pos)    /* P9   - 0:            1:             2:            3:             4:     5:   6:   7:EC40       8:       9:CS3 10: */
            | (0x00UL << PORT_AFSR2_AFSR8_Pos);   /* P8   - 0:            1:             2:            3:             4:     5:   6:   7:T40CAP_CH3 8:T40OUT 9:UWR 10: */

    PC->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << PORT_PUPD_PUPD12_Pos)    /* P12 */
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

    PC->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
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
            | (0x01UL << PORT_MOD_MODE2_Pos)      /* P2 */
            | (0x02UL << PORT_MOD_MODE1_Pos)      /* P1 */
            | (0x02UL << PORT_MOD_MODE0_Pos);     /* P0 */

    PF->TYP = 0x00UL  /* 0 : Push-pull Output 1 : Open-drain Output */
            | (0x00UL << PORT_TYP_TYP2_Pos)       /* P2 */
            | (0x00UL << PORT_TYP_TYP1_Pos)       /* P1 */
            | (0x00UL << PORT_TYP_TYP0_Pos);      /* P0 */

    PC->AFSR1 = 0x00UL
            | (0x00UL << PORT_AFSR1_AFSR2_Pos)    /* P2  - 0:   1:     2:   3:USART21_SS 4:     5:T21CAP 6:T21OUT 7:EC40 8:       9:CS1 10: */
            | (0x0AUL << PORT_AFSR1_AFSR1_Pos)    /* P1  - 0:   1:     2:   3:           4:     5:       6:       7:     8:       9:    10:XOUT */
            | (0x0AUL << PORT_AFSR1_AFSR0_Pos);   /* P0  - 0:   1:CLK0 2:   3:           4:     5:       6:       7:     8:       9:    10:XIN */

    PF->PUPD = 0x00UL  /* 0 : Disable Pull-up/down 1 : Enable Pull-up 2 : Enable Pull-down */
            | (0x00UL << PORT_PUPD_PUPD2_Pos)     /* P2 */
            | (0x00UL << PORT_PUPD_PUPD1_Pos)     /* P1 */
            | (0x00UL << PORT_PUPD_PUPD0_Pos);    /* P0 */

    PF->OUTDR = 0x00UL  /* 0 : Output Low 1 : Output High */
            | (0x00UL << PORT_OUTDR_OUTDR2_Pos)   /* P2 */
            | (0x00UL << PORT_OUTDR_OUTDR1_Pos)   /* P1 */
            | (0x00UL << PORT_OUTDR_OUTDR0_Pos);  /* P0 */

    /* disable writing permittion of ALL PCU register */
    PCU->PORTEN = 0x00;
}

extern void SystemClock_Config(void);

#endif /* _STARTUP_A31G32X_H_ */
