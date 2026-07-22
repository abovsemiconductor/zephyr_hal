/**
 *******************************************************************************
 * @file        startup_a34l71x.h
 * @author      ABOV R&D Division
 * @brief       Startup APIs for A34L71x
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _STARTUP_A34L71X_H_
#define _STARTUP_A34L71X_H_

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

#define LSI_CLOCK   (40000)     /* The clock speed of Internal Low Speed Oscillator */
#define LSE_CLOCK   (32768)     /* The clock speed of External Low Speed Oscillator (SXTAL) */
#define HSI_CLOCK   (32000000)  /* The clock speed of Internal High Speed Oscillator */
#define HSE_CLOCK   (8000000)   /* The clock speed of External High Speed Oscillator(XTAL) */

extern void SystemClock_Config(void);

static __inline int8_t *PRV_CHIPSET_GetCoreInfo(void)
{
    if(((CHIPCONFIG->CHIPID & 0x00FF0000) >> 16) == 0x34)
    {
        return (int8_t *)"Cortex-M4";
    }
    else
    {
        return (int8_t *)"Unknown";
    }
}

static __inline int8_t *PRV_CHIPSET_GetInfo(void)
{
    if(CHIPCONFIG->CHIPID == 0x4C347160)
    {
        return (int8_t *)"A34L716 : Flash 256KB / SRAM 24KB";
    }
    else
    {
        return (int8_t *)"Unknown";
    }
}

/* Port flash geometry here */
#define STARTUP_FLASH_BASE_ADDR             0x00000000
#define STARTUP_CODE_FLASH_BASE_OFFSET      0x00000000
#define STARTUP_DATA_FLASH_BASE_OFFSET      0x0E000000
#define STARTUP_SYSTEM_FLASH_BASE_OFFSET    0x0F000000
#define STARTUP_SYSTEM_FLASH_OFFSET_MASK    0x00FFFFFF
#define STARTUP_PAGE_SIZE                   0x200
#define STARTUP_DATA_PAGE_SIZE              0x200

#define CONFIG_MAX_WPROT_BLOCKS             1

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
    tFlashGeometricInfo.tCflash.un8NumWProtectedBlocks = 1;
    tFlashGeometricInfo.tCflash.tWProtectedBlocks[0].un32WProtectedSegStartOffset = 0;
    tFlashGeometricInfo.tCflash.tWProtectedBlocks[0].un32WProtectedSegSize = 0x4000;
    tFlashGeometricInfo.tCflash.tWProtectedBlocks[0].un8NumWProtectedSegs = 16;

    tFlashGeometricInfo.tDflash.un32BaseAddr = STARTUP_DATA_FLASH_BASE_OFFSET | STARTUP_FLASH_BASE_ADDR;
    tFlashGeometricInfo.tDflash.un32Size = 0x8000;
    tFlashGeometricInfo.tDflash.un8NumWProtectedBlocks = 1;
    tFlashGeometricInfo.tDflash.tWProtectedBlocks[0].un32WProtectedSegStartOffset = 0;
    tFlashGeometricInfo.tDflash.tWProtectedBlocks[0].un32WProtectedSegSize = 0x800;
    tFlashGeometricInfo.tDflash.tWProtectedBlocks[0].un8NumWProtectedSegs = 16;

    /* If FMC supports data flash, System flash should not be accessed by user */
    tFlashGeometricInfo.tSysflash.un32BaseAddr = STARTUP_SYSTEM_FLASH_BASE_OFFSET | STARTUP_FLASH_BASE_ADDR;
    tFlashGeometricInfo.tSysflash.un32Size = 0;
    tFlashGeometricInfo.tSysflash.un32SysSegSize = 0;
    tFlashGeometricInfo.tSysflash.un8NumSysSegs = 0;

    switch (CHIPCONFIG->CHIPID)
    {
        case 0x4C347160: /* A34L716 */
            tFlashGeometricInfo.tCflash.un32Size = 0x40000;
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

    /* WDT Access Enable */
    WDT->AEN = 0xA55A;
    /* WDT Disable */
    WDT->CON = 0;


    /* SCU Access Enable */
    SCU->SYSTEN = 0x57;
    SCU->SYSTEN = 0x75;

    /* GPIO Access Enable */
    PORTEN->EN = 0x15;
    PORTEN->EN = 0x51;
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
     *        PA PB PC PD PE PF PG
     *-------------------------------------------------------------*/
    /* PORT - A */
    PA->ODR = 0; /* gpio output default 0 (low ) */

        PA->MR1 = 0x00UL
            | (0x00UL << PCU_MR1_P7MUX_Pos)    /* P7  - 0:PA7  1:      2:      3:      4:      5:     7:AN7/DAO0 */
            | (0x00UL << PCU_MR1_P6MUX_Pos)    /* P6  - 0:PA6  1:      2:      3:      4:      5:     7:AN6/AO1  */
            | (0x00UL << PCU_MR1_P5MUX_Pos)    /* P5  - 0:PA5  1:      2:      3:      4:      5:     7:AN5/AIN1 */
            | (0x00UL << PCU_MR1_P4MUX_Pos)    /* P4  - 0:PA4  1:      2:      3:      4:      5:     7:AN4/AIP1 */
            | (0x00UL << PCU_MR1_P3MUX_Pos)    /* P3  - 0:PA3  1:      2:      3:      4:      5:     7:AN3/AO0  */
            | (0x00UL << PCU_MR1_P2MUX_Pos)    /* P2  - 0:PA2  1:      2:      3:      4:      5:     7:AN2/AIN0 */
            | (0x00UL << PCU_MR1_P1MUX_Pos)    /* P1  - 0:PA1  1:MISO1 2:      3:      4:      5:     7:AN1/AIP0 */
            | (0x00UL << PCU_MR1_P0MUX_Pos);   /* P0  - 0:PA0  1:MOSI1 2:      3:      4:      5:     7:AN0      */

    PA->MR2 = 0x00UL
            | (0x00UL << PCU_MR2_P15MUX_Pos)   /* P15 - 0:PA15 1:SCK0  2:      3:RXD0  4:      5:SEG6 7:AN15     */
            | (0x00UL << PCU_MR2_P14MUX_Pos)   /* P14 - 0:PA14 1:SS0   2:T6IO  3:WDTO  4:      5:SEG5 7:AN14     */
            | (0x00UL << PCU_MR2_P13MUX_Pos)   /* P13 - 0:PA13 1:SDA1  2:      3:      4:      5:SEG4 7:AN13     */
            | (0x00UL << PCU_MR2_P12MUX_Pos)   /* P12 - 0:PA12 1:SCL1  2:      3:      4:      5:SEG3 7:AN12     */
            | (0x00UL << PCU_MR2_P11MUX_Pos)   /* P11 - 0:PA11 1:      2:      3:      4:      5:SEG2 7:AN11     */
            | (0x00UL << PCU_MR2_P10MUX_Pos)   /* P10 - 0:PA10 1:      2:      3:      4:      5:SEG1 7:AN10     */
            | (0x00UL << PCU_MR2_P9MUX_Pos)    /* P9  - 0:PA9  1:      2:      3:      4:      5:SEG0 7:AN9      */
            | (0x00UL << PCU_MR2_P8MUX_Pos);   /* P8  - 0:PA8  1:      2:      3:      4:      5:     7:AN8/DAO1 */

    PA->CR = 0;
    PA->PRCR = 0;

    /* PORT - B */
    PB->ODR = 0; /* gpio output default 0 (low ) */

    PB->MR1 = 0x00UL
            | (0x00UL << PCU_MR1_P7MUX_Pos)    /* P7  - 0:PB7  1:      2:      3:       4:       5:VLC3       7:     */
            | (0x00UL << PCU_MR1_P6MUX_Pos)    /* P6  - 0:PB6  1:      2:      3:       4:       5:CAPL       7:     */
            | (0x00UL << PCU_MR1_P5MUX_Pos)    /* P5  - 0:PB5  1:      2:      3:       4:       5:CAPH       7:     */
            | (0x00UL << PCU_MR1_P4MUX_Pos)    /* P4  - 0:PB4  1:      2:      3:       4:       5:COM3       7:     */
            | (0x00UL << PCU_MR1_P3MUX_Pos)    /* P3  - 0:PB3  1:SDA0  2:      3:       4:       5:COM2       7:     */
            | (0x00UL << PCU_MR1_P2MUX_Pos)    /* P2  - 0:PB2  1:SCL0  2:      3:       4:       5:COM1       7:     */
            | (0x00UL << PCU_MR1_P1MUX_Pos)    /* P1  - 0:PB1  1:MISO0 2:      3:       4:       5:COM0       7:     */
            | (0x00UL << PCU_MR1_P0MUX_Pos);   /* P0  - 0:PB0  1:MOSI0 2:      3:TXD0   4:       5:SEG7       7:AN16 */

    PB->MR2 = 0x00UL
            | (0x00UL << PCU_MR2_P15MUX_Pos)   /* P15 - 0:PB15 1:TXD10 2:      3:LPTXD0 4:MOSI10 5:SEG12      7:     */
            | (0x00UL << PCU_MR2_P14MUX_Pos)   /* P14 - 0:PB14 1:SDA1  2:      3:LPDE0  4:SCK10  5:COM7/SEG11 7:     */
            | (0x00UL << PCU_MR2_P13MUX_Pos)   /* P13 - 0:PB13 1:SCL1  2:      3:       4:SS10   5:COM6/SEG10 7:     */
            | (0x00UL << PCU_MR2_P12MUX_Pos)   /* P12 - 0:PB12 1:      2:      3:CLKO   4:       5:COM5/SEG9  7:     */
            | (0x00UL << PCU_MR2_P11MUX_Pos)   /* P11 - 0:PB11 1:      2:T7IO  3:STBYO  4:       5:COM4/SEG8  7:     */
            | (0x00UL << PCU_MR2_P10MUX_Pos)   /* P10 - 0:PB10 1:      2:      3:       4:       5:VLC0       7:     */
            | (0x00UL << PCU_MR2_P9MUX_Pos)    /* P9  - 0:PB9  1:      2:      3:       4:       5:VLC1       7:     */
            | (0x00UL << PCU_MR2_P8MUX_Pos);   /* P8  - 0:PB8  1:      2:      3:       4:       5:VLC2       7:     */

    PB->CR = 0;
    PB->PRCR = 0;

    /* PORT - C */
    PC->ODR = 0; /* gpio output default 0 (low ) */

    PC->MR1 = 0x00UL
            | (0x00UL << PCU_MR1_P7MUX_Pos)    /* P7  - 0:PC7  1:      2:RTC_OUT   3:RTC_TAMP1 4:       5:SEG18 7:    */
            | (0x02UL << PCU_MR1_P6MUX_Pos)    /* P6  - 0:PC6  1:TXD0  2:SWDIO/TMS 3:          4:       5:      7:    */
            | (0x02UL << PCU_MR1_P5MUX_Pos)    /* P5  - 0:PC5  1:RXD0  2:SWCLK/TCK 3:          4:       5:      7:    */
            | (0x02UL << PCU_MR1_P4MUX_Pos)    /* P4  - 0:PC4  1:RXD11 2:nTRST     3:LPRXD1    4:MISO11 5:SEG17 7:    */
            | (0x02UL << PCU_MR1_P3MUX_Pos)    /* P3  - 0:PC3  1:TXD11 2:TDI       3:LPTXD1    4:MOSI11 5:SEG16 7:    */
            | (0x02UL << PCU_MR1_P2MUX_Pos)    /* P2  - 0:PC2  1:SDA0  2:TDO       3:LPDE1     4:SCK11  5:SEG15 7:    */
            | (0x00UL << PCU_MR1_P1MUX_Pos)    /* P1  - 0:PC1  1:SCL0  2:          3:          4:SS11   5:SEG14 7:    */
            | (0x00UL << PCU_MR1_P0MUX_Pos);   /* P0  - 0:PC0  1:RXD10 2:          3:LPRXD0    4:MISO10 5:SEG13 7:    */

    PC->MR2 = 0x00UL
            | (0x00UL << PCU_MR2_P15MUX_Pos)   /* P15 - 0:PC15 1:       2:         3:          4:USBDM  5:       7:   */
            | (0x00UL << PCU_MR2_P14MUX_Pos)   /* P14 - 0:PC14 1:       2:         3:          4:USBDP  5:       7:   */
            | (0x02UL << PCU_MR2_P13MUX_Pos)   /* P13 - 0:PC13 1:       2:nBOOT*   3:          4:       5:       7:   */
            | (0x02UL << PCU_MR2_P12MUX_Pos)   /* P12 - 0:PC12 1:       2:nRESET*  3:          4:       5:       7:   */
            | (0x00UL << PCU_MR2_P11MUX_Pos)   /* P11 - 0:PC11 1:RXD11 2:T1IO      3:LPRXD1    4:MISO11 5:SEG22  7:   */
            | (0x00UL << PCU_MR2_P10MUX_Pos)   /* P10 - 0:PC10 1:TXD11 2:T0IO      3:LPTXD1    4:MOSI11 5:SEG21  7:   */
            | (0x00UL << PCU_MR2_P9MUX_Pos)    /* P9  - 0:PC9  1:SDA1  2:          3:LPDE1     4:SCK11  5:SEG20  7:   */
            | (0x00UL << PCU_MR2_P8MUX_Pos);   /* P8  - 0:PC8  1:SCL1  2:          3:RTC_TAMP2 4:SS11   5:SEG19  7:   */

    PC->CR = 0;
    PC->PRCR = 0;

    /* PORT - D */
    PD->ODR = 0; /* gpio output default 0 (low ) */

    PD->MR1 = 0x00UL
            | (0x00UL << PCU_MR1_P7MUX_Pos)    /* P7  - 0:PD7  1:     2      3:      4:      5:      7:AN18  */
            | (0x00UL << PCU_MR1_P6MUX_Pos)    /* P6  - 0:PD6  1:     2      3:      4:      5:      7:AN17  */
            | (0x07UL << PCU_MR1_P5MUX_Pos)    /* P5  - 0:PD5  1:SCK1 2      3:      4:      5:      7:SXOUT */
            | (0x07UL << PCU_MR1_P4MUX_Pos)    /* P4  - 0:PD4  1:SS1  2      3:      4:      5:      7:SXIN  */
            | (0x07UL << PCU_MR1_P3MUX_Pos)    /* P3  - 0:PD3  1:     2      3:      4:      5:      7:XIN   */
            | (0x07UL << PCU_MR1_P2MUX_Pos)    /* P2  - 0:PD2  1:     2      3:      4:      5:      7:XOUT  */
            | (0x03UL << PCU_MR1_P1MUX_Pos)    /* P1  - 0:PD1  1:     2      3:TXD0  4:      5:      7:      */
            | (0x03UL << PCU_MR1_P0MUX_Pos);   /* P0  - 0:PD0  1:SOF  2      3:RXD0  4:      5:      7:      */

    PD->MR2 = 0x00UL
            | (0x00UL << PCU_MR2_P15MUX_Pos)   /* P15 - 0:PD15 1:SCK0 2:     3:      4:      5:      7:      */
            | (0x00UL << PCU_MR2_P14MUX_Pos)   /* P14 - 0:PD14 1:SS0  2:     3:      4:      5:      7:      */
            | (0x00UL << PCU_MR2_P13MUX_Pos)   /* P13 - 0:PD13 1:     2:T3IO 3:      4:      5:      7:      */
            | (0x00UL << PCU_MR2_P12MUX_Pos)   /* P12 - 0:PD12 1:     2:T2IO 3:      4:      5:      7:      */
            | (0x00UL << PCU_MR2_P11MUX_Pos)   /* P11 - 0:PD11 1:     2:T1IO 3:      4:      5:      7:      */
            | (0x00UL << PCU_MR2_P10MUX_Pos)   /* P10 - 0:PD10 1:     2:T0IO 3:      4:      5:      7:      */
            | (0x00UL << PCU_MR2_P9MUX_Pos)    /* P9  - 0:PD9  1:     2:T7IO 3:STBY0 4:      5:      7:      */
            | (0x00UL << PCU_MR2_P8MUX_Pos);   /* P8  - 0:PD8  1:     2:T6IO 3:WDT0  4:      5:      7:      */

    PD->CR = 0;
    PD->PRCR = 0;

    /* PORT - E */
    PE->ODR = 0; /* gpio output default 0 (low ) */

    PE->MR1 = 0x00UL
            | (0x00UL << PCU_MR1_P7MUX_Pos)    /* P7  - 0:PE7  1:MISO1 2:     3:TXD0 4:       5:SEG35 7:     */
            | (0x00UL << PCU_MR1_P6MUX_Pos)    /* P6  - 0:PE6  1:MOSI1 2:T7IO 3:RXD0 4:       5:SEG34 7:     */
            | (0x00UL << PCU_MR1_P5MUX_Pos)    /* P5  - 0:PE5  1:SCK1  2:T6IO 3:     4:       5:SEG33 7:     */
            | (0x00UL << PCU_MR1_P4MUX_Pos)    /* P4  - 0:PE4  1:SS1   2:T5IO 3:     4:       5:SEG32 7:     */
            | (0x00UL << PCU_MR1_P3MUX_Pos)    /* P3  - 0:PE3  1:      2:     3:     4:       5:SEG31 7:     */
            | (0x00UL << PCU_MR1_P2MUX_Pos)    /* P2  - 0:PE2  1:      2:     3:     4:       5:SEG30 7:     */
            | (0x00UL << PCU_MR1_P1MUX_Pos)    /* P1  - 0:PE1  1:      2:T5IO 3:     4:       5:SEG29 7:     */
            | (0x00UL << PCU_MR1_P0MUX_Pos);   /* P0  - 0:PE0  1:      2:     3:     4:       5:SEG28 7:     */

    PE->MR2 = 0x00UL
            | (0x00UL << PCU_MR2_P15MUX_Pos)   /* P15 - 0:PE15 1:      2:T4IO 3:     4:       5:SEG43 7:     */
            | (0x00UL << PCU_MR2_P14MUX_Pos)   /* P14 - 0:PE14 1:      2:T3IO 3:     4:       5:SEG42 7:     */
            | (0x00UL << PCU_MR2_P13MUX_Pos)   /* P13 - 0:PE13 1:      2:T2IO 3:     4:       5:SEG41 7:     */
            | (0x00UL << PCU_MR2_P12MUX_Pos)   /* P12 - 0:PE12 1:RXD10 2:T3IO 3:AD1E 4:MISO10 5:SEG40 7:     */
            | (0x00UL << PCU_MR2_P11MUX_Pos)   /* P11 - 0:PE11 1:TXD10 2:T2IO 3:AD1S 4:MOSI10 5:SEG39 7:     */
            | (0x00UL << PCU_MR2_P10MUX_Pos)   /* P10 - 0:PE10 1:      2:T1IO 3:AD0E 4:SCK10  5:SEG38 7:     */
            | (0x00UL << PCU_MR2_P9MUX_Pos)    /* P9  - 0:PE9  1:      2:TOI0 3:AD0S 4:SS10   5:SEG37 7:     */
            | (0x00UL << PCU_MR2_P8MUX_Pos);   /* P8  - 0:PE8  1:      2:     3:     4:       5:SEG36 7:     */

    PE->CR = 0;
    PE->PRCR = 0;

    /* PORT - F */
    PF->ODR = 0; /* gpio output default 0 (low ) */

    PF->MR1 = 0x00UL
            | (0x00UL << PCU_MR1_P5MUX_Pos)    /* P5  - 0:PF5  1:MISO0 2:     3:LPRXD0  4:    5:     7:    */
            | (0x00UL << PCU_MR1_P4MUX_Pos)    /* P4  - 0:PF4  1:MOSI0 2:T3IO 3:LPTXD0  4:    5:     7:    */
            | (0x00UL << PCU_MR1_P3MUX_Pos)    /* P3  - 0:PF3  1:SCK0  2:T2IO 3:LPDE0   4:    5:     7:    */
            | (0x00UL << PCU_MR1_P2MUX_Pos)    /* P2  - 0:PF2  1:SS0   2:T1IO 3:        4:    5:     7:    */
            | (0x00UL << PCU_MR1_P1MUX_Pos)    /* P1  - 0:PF1  1:SDA0  2:T0IO 3:        4:    5:     7:    */
            | (0x00UL << PCU_MR1_P0MUX_Pos);   /* P0  - 0:PF0  1:SCL0  2:     3:CLK0    4:    5:     7:    */

    PF->MR2 = 0x00UL;

    PF->CR = 0;
    PF->PRCR = 0;

    /* disable writing permittion of ALL PCU register */
    PORTEN->EN = 0x00;
}

#endif /* _STARTUP_A34L71X_H_ */
