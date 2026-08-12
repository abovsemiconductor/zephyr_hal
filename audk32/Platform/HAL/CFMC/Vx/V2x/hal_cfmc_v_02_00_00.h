/**
 *******************************************************************************
 * @file        hal_cfmc_v_02_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 02.00.00 typed CFMC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_CFMC_V_02_00_00_H_
#define _HAL_CFMC_V_02_00_00_H_

#include "hal_cfmc.h"

/* External References */
extern int8_t PRV_CHIPSET_GetDebuggerConnectionStatus (void);

/* Feature(Function) Configuration Define */
#define CFMC_FEATURE_FLASH_BASE_ADDR                  STARTUP_FLASH_BASE_ADDR
#define CFMC_FEATURE_CODE_FLASH_BASE_OFFSET           STARTUP_CODE_FLASH_BASE_OFFSET
#define CFMC_FEATURE_SYSTEM_FLASH_BASE_OFFSET         STARTUP_SYSTEM_FLASH_BASE_OFFSET
#define CFMC_FEATURE_SYSTEM_FLASH_OFFSET_MASK         STARTUP_SYSTEM_FLASH_OFFSET_MASK
#define CFMC_FEATURE_PAGE_SIZE                        STARTUP_PAGE_SIZE
#define CFMC_FEATURE_SELF_PROGRAM_ERASE               1
#define CFMC_FEATURE_WRITE_IMPL_BY_SELF_WRITE         1
#define CFMC_FEATURE_RUMTIME_READ_PROTECTION          1
#define CFMC_FEATURE_ICACHE                           0
#define CFMC_FEATURE_BBLOCK                           1

/* Internal Macro */
typedef volatile FMC_Type                             CFMC_Type;
#define CFMC_REG_BASE                                 FMC_BASE

/* CFMC Mode Definition */
#define CFMC_PE_MODE_CMD1                             0x0000005A
#define CFMC_PE_MODE_CMD2                             0x000000A5
#define CFMC_TRIM_MODE_CMD1                           0x000000A5
#define CFMC_TRIM_MODE_CMD2                           0x0000005A
#define CFMC_AMBA_MODE_CMD1                           0x00000081
#define CFMC_AMBA_MODE_CMD2                           0x00000028
#define CFMC_PROTECT_MODE_CMD1                        0x00000066
#define CFMC_PROTECT_MODE_CMD2                        0x00000099

/* Magic key for updating latency in CFGR */
#define CFMC_CFGR_WKY_LATENCY                         0x78580000

/* Read protection command */
#define CFMC_RD_PROTECT_LEVEL1_CMD                    0x39

/* Bit/Register Macro */
#define SET_CFMC_MR(Peri,Data)                        SET_REG(Peri,Data,MR)
#define CLEAR_CFMC_MR(Peri)                           SET_REG(Peri,0,MR)

#define SET_CFMC_CR_LOCKSEL(Peri,Data)                SET_BIT(Peri,Data,FMC,CR,LOCKSEL)
#define SET_CFMC_CR_SELFPGM(Peri,Data)                SET_BIT(Peri,Data,FMC,CR,SELFPGM)
#define SET_CFMC_CR_SYSFLASH_EN(Peri,Data)            SET_BIT(Peri,Data,FMC,CR,IFEN)
#define SET_CFMC_CR_WPROT_BBLK(Peri,Data)             SET_BIT(Peri,Data,FMC,CR,BBLOCK)

#define SET_CFMC_CR_ERS(Peri,Data)                    SET_BIT(Peri,Data,FMC,CR,ERS)
#define SET_CFMC_CR_ERS_1KB(Peri,Data)                SET_BIT(Peri,Data,FMC,CR,SECT1K)
#define SET_CFMC_CR_ERS_4KB(Peri,Data)                SET_BIT(Peri,Data,FMC,CR,SECT4K)
#define SET_CFMC_CR_ERS_CHIP(Peri,Data)               SET_BIT(Peri,Data,FMC,CR,MAS)
#define SET_CFMC_CR_PMODE(Peri,Data)                  SET_BIT(Peri,Data,FMC,CR,PMODE)
#define GET_CFMC_CR_PMODE(Peri)                       GET_BIT(Peri,FMC,CR,PMODE)
#define CLEAR_CFMC_CR(Peri)                           SET_REG(Peri,0,CR)

#define SET_CFMC_CR_LATCH_SIGNAL(Peri,Data)           SET_BIT(Peri,Data,FMC,CR,WADCK)
#define SET_CFMC_CR_PGM(Peri,Data)                    SET_BIT(Peri,Data,FMC,CR,PGM)
#define SET_CFMC_CR_HVEN(Peri,Data)                   SET_BIT(Peri,Data,FMC,CR,HVEN)

#define SET_CFMC_AR(Peri,Data)                        SET_REG(Peri,Data,AR)
#define SET_CFMC_DR(Peri,Data)                        SET_REG(Peri,Data,DR)

#define GET_CFMC_STR_WRBUSY(Peri)                     GET_BIT(Peri,FMC,BUSY,WRBUSY)
#define SET_CFMC_STR(Peri,Data)                       SET_REG(Peri,Data,BUSY)

#define SET_CFMC_CFGR(Peri,Data)                      SET_REG(Peri,Data,CFG)
#define SET_CFMC_CFGR_LATENCY(Peri,Data)              SET_BIT(Peri,Data,FMC,CFG,WAIT)
#define SET_CFMC_CFGR_WTIDKY(Peri,Data)               SET_BIT(Peri,Data,FMC,CFG,WTIDKY)

#define SET_CFMC_WPR_WPROT(Peri,Data)                 SET_BIT(Peri,Data,FMC,WPROT,WPROT)
#define GET_CFMC_WPR_WPROT(Peri)                      GET_BIT(Peri,FMC,WPROT,WPROT)

#define SET_CFMC_RPR_RPROT(Peri,Data)                 SET_BIT(Peri,Data,FMC,LOCK,RPROT)

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_CFMC_PROT_RESET(Peri,Data)            SET_BIT(Peri,Data,SCU,PRER1,FMC)

/* Inline functions */
static __inline void CFMC_SetConfig(CFMC_CONFIG_t tConfig);
static __inline void CFMC_SetWriteProtect(uint32_t un32TargetBlk, bool bRequestLock);
static __inline void CFMC_SetWriteProtectBootBlk(bool bRequestLock);
static __inline HAL_ERR_e CFMC_SetReadProtect(CFMC_RD_PROTECT_CONFIG_t tRdProtectConfig);
static __inline void CFMC_Erase(uint32_t un32PageAddr, CFMC_ERASE_MODE_e eEraseMode, bool bIsSystemFlash);
static __inline void CFMC_Write(uint32_t un32FlashAddr, uint32_t *pun32Data, uint32_t un32Len, bool bIsWordWrite, bool bIsSystemFlash);
static __inline void CFMC_SelfWriteFromRAM(uint32_t un32FlashAddr, uint32_t *pun32Data);

RAMFUNC static __inline void CFMC_SetConfig(CFMC_CONFIG_t tConfig)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    uint32_t un32Reg = CFMC_CFGR_WKY_LATENCY;

    SET_CFMC_MR(ptRegBase, CFMC_AMBA_MODE_CMD1);
    SET_CFMC_MR(ptRegBase, CFMC_AMBA_MODE_CMD2);

    un32Reg |= (tConfig.un8Latency << BIT_NAME_POS(FMC_,CFG_,WAIT_));

    SET_CFMC_CFGR(ptRegBase,un32Reg);

    CLEAR_CFMC_MR(ptRegBase);
    CLEAR_CFMC_MR(ptRegBase);

    return;
}

RAMFUNC static __inline void CFMC_SetWriteProtect(uint32_t un32TargetBlk, bool bRequestLock)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    uint32_t un32Reg;

    SET_CFMC_MR(ptRegBase, CFMC_PROTECT_MODE_CMD1);
    SET_CFMC_MR(ptRegBase, CFMC_PROTECT_MODE_CMD2);

    un32Reg = GET_CFMC_WPR_WPROT(ptRegBase);

    if (!bRequestLock)
    {
        un32TargetBlk = un32Reg & ~un32TargetBlk;
    }
    else
    {
        un32TargetBlk = un32Reg | un32TargetBlk;
    }
    SET_CFMC_WPR_WPROT(ptRegBase, un32TargetBlk);

    CLEAR_CFMC_MR(ptRegBase);
    CLEAR_CFMC_MR(ptRegBase);

    return;
}

RAMFUNC static __inline void CFMC_SetWriteProtectBootBlk(bool bRequestLock)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;

    SET_CFMC_MR(ptRegBase, CFMC_PE_MODE_CMD1);
    SET_CFMC_MR(ptRegBase, CFMC_PE_MODE_CMD2);

    SET_CFMC_CR_WPROT_BBLK(ptRegBase, bRequestLock);

    CLEAR_CFMC_MR(ptRegBase);
    CLEAR_CFMC_MR(ptRegBase);

    return;
}

RAMFUNC static __inline HAL_ERR_e CFMC_SetReadProtect(CFMC_RD_PROTECT_CONFIG_t tRdProtectConfig)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
#if (CONFIG_EMUL_JTAG_CONNECTION == 1)
    int8_t n8DebuggerConnected = PRV_CHIPSET_GetDebuggerConnectionStatus();
#else
    int8_t n8DebuggerConnected = 0;
#endif

    if (tRdProtectConfig.eRdProtectLevel != CFMC_RD_PROTECT_LEVEL1)
    {
        return HAL_ERR_PARAMETER;
    }

    if (n8DebuggerConnected)
    {
        __asm volatile ("cpsid i");
    }

    SET_CFMC_MR(ptRegBase, CFMC_PROTECT_MODE_CMD1);
    SET_CFMC_MR(ptRegBase, CFMC_PROTECT_MODE_CMD2);

    SET_CFMC_RPR_RPROT(ptRegBase, CFMC_RD_PROTECT_LEVEL1_CMD);

    CLEAR_CFMC_MR(ptRegBase);
    CLEAR_CFMC_MR(ptRegBase);

    if (n8DebuggerConnected)
    {
        __asm volatile ("cpsie i");
    }

    return HAL_ERR_OK;
}

RAMFUNC static __inline void CFMC_Erase(uint32_t un32PageAddr, CFMC_ERASE_MODE_e eEraseMode, bool bIsSystemFlash)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    uint32_t un32State=0xFF;

    SET_CFMC_MR(ptRegBase, CFMC_PE_MODE_CMD1);
    SET_CFMC_MR(ptRegBase, CFMC_PE_MODE_CMD2);

    /* Signaling Address to Bus */
    un32PageAddr = un32PageAddr >> 2;
    SET_CFMC_AR(ptRegBase, un32PageAddr);

    __asm volatile ("cpsid i");
    SET_CFMC_CR_PMODE(ptRegBase, true);

    /* Select target flash */
    if (bIsSystemFlash)
    {
        SET_CFMC_CR_SYSFLASH_EN(ptRegBase, true);
    }

    switch (eEraseMode)
    {
        case CFMC_1KB_ERASE_MODE:
            SET_CFMC_CR_ERS_1KB(ptRegBase, true);
            break;

        case CFMC_4KB_ERASE_MODE:
            SET_CFMC_CR_ERS_4KB(ptRegBase, true);
            break;

        case CFMC_CHIP_ERASE_MODE:
            /* Setup Erase option */
            SET_CFMC_CR_ERS_CHIP(ptRegBase, true);

        default: /* FMC_512B_ERASE_MODE */
            break;
    }

    /* Signaling Erase to Bus */
    SET_CFMC_CR_ERS(ptRegBase, true);

    /* Latch signals */
    SET_CFMC_CR_LATCH_SIGNAL(ptRegBase, true);

    /* Enable high voltage */
    SET_CFMC_CR_HVEN(ptRegBase, true);

    /* Check a Write is done */
    do
    {
        un32State= GET_CFMC_STR_WRBUSY(ptRegBase);
    }while (un32State);

    /* Disable high voltage */
    SET_CFMC_CR_HVEN(ptRegBase, false);

    /* 0x80 is shown up atfer P/E is done */
    SET_CFMC_STR(ptRegBase, 0x80);

    /* De-select target flash */
    if (bIsSystemFlash)
    {
        SET_CFMC_CR_SYSFLASH_EN(ptRegBase, false);
    }

    /* Come back to Read mode */
    CLEAR_CFMC_CR(ptRegBase);
    __asm volatile ("cpsie i");

    CLEAR_CFMC_MR(ptRegBase);
    CLEAR_CFMC_MR(ptRegBase);

    return;
}

/* This API cannot write the last word at end of wirte protection block */
RAMFUNC static __inline void CFMC_Write(uint32_t un32FlashAddr, uint32_t *pun32Data, uint32_t un32Len, bool bIsWordWrite, bool bIsSystemFlash)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    uint32_t i;
    uint32_t un32State=0xFF;

    SET_CFMC_MR(ptRegBase, CFMC_PE_MODE_CMD1);
    SET_CFMC_MR(ptRegBase, CFMC_PE_MODE_CMD2);

    /* Signaling word-aligned address to Bus */
    un32FlashAddr = un32FlashAddr >> 2;
    SET_CFMC_AR(ptRegBase, un32FlashAddr);

    __asm volatile ("cpsid i");
    SET_CFMC_CR_PMODE(ptRegBase, true);

    /* Select target flash */
    if (bIsSystemFlash)
    {
        SET_CFMC_CR_SYSFLASH_EN(ptRegBase, true);
    }

    /* Singaling Write Command to Bus */
    SET_CFMC_CR_PGM(ptRegBase, true);

    /* Singaling Data to Bus and latch all signals */
    for (i=0; i<un32Len; i++)
    {
        SET_CFMC_DR(ptRegBase, *pun32Data++);
        SET_CFMC_CR_LATCH_SIGNAL(ptRegBase, true);

        /* Enable high voltage */
        SET_CFMC_CR_HVEN(ptRegBase, true);

        /* Check a Write is done */
        do
        {
            un32State= GET_CFMC_STR_WRBUSY(ptRegBase);
        }while (un32State);

        /* Disable high voltage */
        SET_CFMC_CR_HVEN(ptRegBase, false);

        /* 0x80 is shown up atfer P/E is done */
        SET_CFMC_STR(ptRegBase, 0x80);
    }

    /* De-select target flash */
    if (bIsSystemFlash)
    {
        SET_CFMC_CR_SYSFLASH_EN(ptRegBase, false);
    }

    /* Come back to Read mode */
    CLEAR_CFMC_CR(ptRegBase);
    __asm volatile ("cpsie i");

    CLEAR_CFMC_MR(ptRegBase);
    CLEAR_CFMC_MR(ptRegBase);

    return;
}

RAMFUNC static __inline void CFMC_SelfWriteFromRAM(uint32_t un32FlashAddr, uint32_t *pun32Data)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;

    SET_CFMC_MR(ptRegBase, CFMC_PE_MODE_CMD1);
    SET_CFMC_MR(ptRegBase, CFMC_PE_MODE_CMD2);

    /* Signalng Self Programing to Bus */
    SET_CFMC_CR_SELFPGM(ptRegBase, true);

    /* Signalng Write to Bus */
    __asm volatile ("cpsid i");
    SET_CFMC_CR_PGM(ptRegBase,true);
    __NOP();__NOP();__NOP();__NOP();__NOP();

    /* Signaling Address and Data to Bus */
    *(uint32_t *)un32FlashAddr = *pun32Data;
    __NOP();__NOP();__NOP();__NOP();__NOP();

    /* Come back to Read mode */
    CLEAR_CFMC_CR(ptRegBase);
    __NOP();__NOP();__NOP();__NOP();__NOP();
    __asm volatile ("cpsie i");

    CLEAR_CFMC_MR(ptRegBase);
    CLEAR_CFMC_MR(ptRegBase);

    return;
}

static __inline void CFMC_SelfErase(uint32_t un32PageAddr)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;

    SET_CFMC_MR(ptRegBase, CFMC_PE_MODE_CMD1);
    SET_CFMC_MR(ptRegBase, CFMC_PE_MODE_CMD2);

    /* Signalng Self Programing to Bus */
    SET_CFMC_CR_SELFPGM(ptRegBase, true);

    /* Signaling Erase to Bus */
    SET_CFMC_CR_ERS(ptRegBase, true);

    __NOP();__NOP();__NOP();__NOP();__NOP();

    /* Signaling Address and Data to Bus */
    *(uint32_t *)un32PageAddr = 0xFFFFFFFF;
    __NOP();__NOP();__NOP();__NOP();__NOP();

    /* Come back to Read mode */
    CLEAR_CFMC_CR(ptRegBase);
    __NOP();__NOP();__NOP();__NOP();__NOP();

    CLEAR_CFMC_MR(ptRegBase);
    CLEAR_CFMC_MR(ptRegBase);

    return;
}

static __inline void CFMC_SelfWrite(uint32_t un32FlashAddr, uint32_t *pun32Data)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;

    SET_CFMC_MR(ptRegBase, CFMC_PE_MODE_CMD1);
    SET_CFMC_MR(ptRegBase, CFMC_PE_MODE_CMD2);

    /* Signalng Self Programing to Bus */
    SET_CFMC_CR_SELFPGM(ptRegBase, true);

    /* Signalng Write to Bus */
    __asm volatile ("cpsid i");
    SET_CFMC_CR_PGM(ptRegBase,true);
    __NOP();__NOP();__NOP();__NOP();__NOP();

    /* Signaling Address and Data to Bus */
    *(uint32_t *)un32FlashAddr = *pun32Data;
    __NOP();__NOP();__NOP();__NOP();__NOP();

    /* Come back to Read mode */
    CLEAR_CFMC_CR(ptRegBase);
    __NOP();__NOP();__NOP();__NOP();__NOP();
    __asm volatile ("cpsie i");

    CLEAR_CFMC_MR(ptRegBase);
    CLEAR_CFMC_MR(ptRegBase);

    return;
}

#endif /* _HAL_CFMC_V_02_00_00_H_ */
