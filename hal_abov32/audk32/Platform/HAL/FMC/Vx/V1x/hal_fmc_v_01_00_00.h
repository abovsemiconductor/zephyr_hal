/**
 *******************************************************************************
 * @file        hal_fmc_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed FMC
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_FMC_V_01_00_00_H_
#define _HAL_FMC_V_01_00_00_H_

#include "hal_fmc.h"

/* External References */
extern int8_t PRV_CHIPSET_GetDebuggerConnectionStatus (void);

/* Feature(Function) Configuration Define */
#define FMC_FEATURE_FLASH_BASE_ADDR                   STARTUP_FLASH_BASE_ADDR
#define FMC_FEATURE_CODE_FLASH_BASE_OFFSET            STARTUP_CODE_FLASH_BASE_OFFSET
#define FMC_FEATURE_DATA_FLASH_BASE_OFFSET            STARTUP_DATA_FLASH_BASE_OFFSET
#define FMC_FEATURE_SYSTEM_FLASH_BASE_OFFSET          STARTUP_SYSTEM_FLASH_BASE_OFFSET
#define FMC_FEATURE_SYSTEM_FLASH_OFFSET_MASK          STARTUP_SYSTEM_FLASH_OFFSET_MASK
#define FMC_FEATURE_PAGE_SIZE                         STARTUP_PAGE_SIZE
#define FMC_FEATURE_DATA_PAGE_SIZE                    STARTUP_DATA_PAGE_SIZE
#define FMC_FEATURE_SELF_PROGRAM_ERASE                1
#define FMC_FEATURE_WRITE_IMPL_BY_SELF_WRITE          0
#define FMC_FEATURE_PASSWD_LOCK                       0
#define FMC_FEATURE_CRC                               0
#define FMC_FEATURE_IRQ_SERVICE                       0
#define FMC_FEATURE_RUMTIME_READ_PROTECTION           1

#define FMC_FEATURE_CFMC_BANK_SWITCH                  0
#define FMC_FEATURE_CFMC_BBLOCK                       1
#define FMC_FEATURE_CFMC_IDCACHE                      0

#define FMC_FEATURE_DFMC_WRITE_BYTE                   1

/* For this IP Only */
#define FMC_FEATURE_CFMC_BBLOCK_IMPL_BY_WRITE_PROT    0

/* Internal Macro */
#define CFMC_REG_BASE                                 FMC_BASE
#define DFMC_REG_BASE                                 FMC_BASE

/* Magic key for updating BBLOCK in CON */
#define FMC_CR_WKY_EXT_KEY                            0x00004A00

/* Write Protection Mask */
#define FMC_WPROT_WPROT_Mask                          0x00003FFF

/* Write Protection Bit Field Transposition */
#define FMC_WPROT_TRNASPOS_BITS                       4
#define FMC_WPROT_TRANSPOS_POS                        8
#define FMC_WPROT_TRANSPOS_MASK                       (0x0FUL << FMC_WPROT_TRANSPOS_POS)

/* Read protection command */
#define FMC_RD_PROTECT_LEVEL1_CMD                     0x39
#define FMC_RD_PROTECT_LEVEL2_CMD                     0x75

/* Self operation commands */
#define CFMC_CR_SELF_WKEY                             0x06000000
#define CFMC_CR_SELF_PGM_CMD                          (FMC_CON_SELF_Msk|CFMC_CR_SELF_WKEY|FMC_CON_PROG_Msk)
#define CFMC_CR_SELF_ERS_CMD                          (FMC_CON_SELF_Msk|CFMC_CR_SELF_WKEY|FMC_CON_SERA_Msk) /* Erasing Sector */

/* Bit/Register Macro */
#define SET_FMC_CR(Peri,Data)                         SET_REG(Peri,Data,CON)
#define SET_CFMC_CR_WPROT_BBLK(Peri,Data)             SET_BIT(Peri,Data,FMC,CON,BBLK)

#define SET_CFMC_CR_CS(Peri,Data)                     SET_BIT(Peri,Data,FMC,CON,CSEL)
#define SET_DFMC_CR_CS(Peri,Data)                     SET_BIT(Peri,Data,FMC,CON,DSEL)
#define SET_FMC_CR_CS(Peri,Data)                      SET_BIT(Peri,Data,FMC,CON,CS)

#define SET_FMC_CR_ERS_512B(Peri,Data)                SET_BIT(Peri,Data,FMC,CON,PAGE)
#define SET_FMC_CR_ERS_1KB(Peri,Data)                 SET_BIT(Peri,Data,FMC,CON,SERA)
#define SET_FMC_CR_ERS_CHIP(Peri,Data)                SET_BIT(Peri,Data,FMC,CON,MASE)

#define SET_FMC_CR_LATCH_SIGNAL(Peri,Data)            SET_BIT(Peri,Data,FMC,CON,AE)
#define SET_FMC_CR_PGM(Peri,Data)                     SET_BIT(Peri,Data,FMC,CON,PROG)
#define SET_FMC_CR_HVEN(Peri,Data)                    SET_BIT(Peri,Data,FMC,CON,NVSTR)
#define CLEAR_FMC_CR(Peri)                            SET_REG(Peri,0,CON)

#define SET_FMC_AR(Peri,Data)                         SET_REG(Peri,Data,AR)
#define SET_FMC_DR(Peri,Data)                         SET_REG(Peri,Data,ODR)

#define GET_CFMC_STR_WRBUSY(Peri)                     GET_BIT(Peri,FMC,CON,CTBIT)
#define SET_CFMC_STR(Peri,Data)                       SET_REG(Peri,Data,CTBIT)
#define GET_DFMC_STR_WRBUSY(Peri)                     GET_BIT(Peri,FMC,CON,DTBIT)
#define SET_DFMC_STR(Peri,Data)                       SET_REG(Peri,Data,DTBIT)

#define SET_CFMC_CFGR_LATENCY(Peri,Data)              SET_BIT(Peri,Data,FMC,CFG,CWAIT)
#define SET_DFMC_CFGR_LATENCY(Peri,Data)              SET_BIT(Peri,Data,FMC,CFG,DWAIT)

#define SET_FMC_EXT_MODE(Peri,Data)                   SET_BIT(Peri,Data | FMC_CR_WKY_EXT_KEY,FMC,TEST,EX)
#define SET_FMC_WPR_WPROT(Peri,Data)                  SET_REG(Peri,Data,PROTECT)
#define GET_FMC_WPR_WPROT(Peri)                       GET_REG(Peri,PROTECT)

#define SET_FMC_RPR_RPROT(Peri,Data)                  SET_BIT(Peri,Data,FMC,RPROT,FMRPROT)
#define GET_FMC_RPR_RPROT_STATUS(Peri)                GET_BIT(Peri,FMC,RPROT,RPROT)
#define GET_FMC_RPR(Peri)                             GET_REG(Peri,RPROT)

/* Define internal variant features */
#define FMC_VARIANT_FEATURE_ADDR_MASK                 0x7FFFF

/* Inline functions */
static __inline void FMC_SetConfig(FMC_ID_e eFmcID, FMC_CONFIG_t tConfig);
static __inline void FMC_SetWriteProtect(FMC_ID_e eFmcID, uint32_t un32BlockIdx, uint32_t un32TargetBlk, bool bRequestLock);
static __inline void CFMC_SetWriteProtectBootBlk(bool bRequestLock);
static __inline HAL_ERR_e FMC_SetReadProtect(FMC_ID_e eFmcID, FMC_RD_PROTECT_CONFIG_t tRdProtectConfig);
static __inline HAL_ERR_e FMC_Erase(FMC_ID_e eFmcID, uint32_t un32PageAddr, FMC_ERASE_MODE_e eEraseMode, bool bIsSystemFlash);
static __inline HAL_ERR_e FMC_Write(FMC_ID_e eFmcID, uint32_t un32FlashAddr, uint32_t *pun32Data, uint32_t un32Len, bool bIsWordWrite, bool bIsSystemFlash);

RAMFUNC static __inline void FMC_SetConfig(FMC_ID_e eFmcID, FMC_CONFIG_t tConfig)
{
    /* Operation time-out is not supported */
    /* CRC is not supported */
    /* Time-out is not supported */
    /* Set up bus-latency only */

    FMC_Type *ptRegBase = (FMC_Type *)CFMC_REG_BASE;

    if (eFmcID == FMC_ID_CFMC)
    {
        SET_CFMC_CFGR_LATENCY(ptRegBase, tConfig.un8Latency);
    }
    else
    {
        SET_DFMC_CFGR_LATENCY(ptRegBase, tConfig.un8Latency);
    }

    return;
}

RAMFUNC static __inline void FMC_SetWriteProtect(FMC_ID_e eFmcID, uint32_t un32BlockIdx, uint32_t un32TargetBlk, bool bRequestLock)
{
    FMC_Type *ptRegBase = (FMC_Type *)CFMC_REG_BASE;
    uint32_t un32Reg;
    uint32_t un32Val;

    (void)un32BlockIdx;

    if (eFmcID == FMC_ID_CFMC)
    {
        if (un32TargetBlk & FMC_WPROT_TRANSPOS_MASK)
        {
            un32Val = (un32TargetBlk & FMC_WPROT_TRANSPOS_MASK) << FMC_WPROT_TRNASPOS_BITS;
        }
        else
        {
            un32Val = un32TargetBlk;
        }
    }
    else
    {
        un32Val = un32TargetBlk << FMC_WPROT_TRNASPOS_BITS;
    }

    un32Val &= FMC_WPROT_WPROT_Mask;
    un32Reg = GET_FMC_WPR_WPROT(ptRegBase);

    if (!bRequestLock)
    {
        if (un32TargetBlk == 0xFFFFFFFF)
        {
            if (eFmcID == FMC_ID_CFMC)
            {
                un32Reg |= (FMC_WPROT_WPROT_Mask & ~FMC_WPROT_TRANSPOS_MASK);
            }
            else
            {
                un32Reg |= FMC_WPROT_TRANSPOS_MASK;
            }
        }
        else
        {
            un32Reg |= un32Val;
        }
    }
    else
    {
        /* Update Lower Write Protect */
        if (un32TargetBlk == 0xFFFFFFFF)
        {
            if (eFmcID == FMC_ID_CFMC)
            {
                un32Reg &= FMC_WPROT_TRANSPOS_MASK;
            }
            else
            {
                un32Reg &= ~FMC_WPROT_TRANSPOS_MASK;
            }
        }
        else
        {
            un32Reg &= ~un32Val;
        }
    }
    SET_FMC_WPR_WPROT(ptRegBase, un32Reg);

    return;
}

RAMFUNC static __inline void CFMC_SetWriteProtectBootBlk(bool bRequestLock)
{
    FMC_Type *ptRegBase = (FMC_Type *)CFMC_REG_BASE;

    SET_FMC_EXT_MODE(ptRegBase, true);
    SET_CFMC_CR_WPROT_BBLK(ptRegBase, bRequestLock);
    SET_FMC_EXT_MODE(ptRegBase, false);

    return;
}

RAMFUNC static __inline HAL_ERR_e FMC_SetReadProtect(FMC_ID_e eFmcID, FMC_RD_PROTECT_CONFIG_t tRdProtectConfig)
{
    FMC_Type *ptRegBase = (FMC_Type *)CFMC_REG_BASE;
    uint8_t un8RdProtectCMD;
    uint32_t un32Status;

#if (CONFIG_EMUL_JTAG_CONNECTION == 1)
    int8_t n8DebuggerConnected = PRV_CHIPSET_GetDebuggerConnectionStatus();
#else
    int8_t n8DebuggerConnected = 0;
#endif

    /* This API sets read protection of both code and data flash at a time */
    if (n8DebuggerConnected)
    {
        __asm volatile ("cpsid i");
    }

    switch (tRdProtectConfig.eRdProtectLevel)
    {
        case FMC_RD_PROTECT_LEVEL1:
            un8RdProtectCMD = FMC_RD_PROTECT_LEVEL1_CMD;
            break;

        default:
           /* FMC_RD_PROTECT_LEVEL2 : Not supported */
            if (n8DebuggerConnected)
            {
                __asm volatile ("cpsie i");
            }
            return HAL_ERR_PARAMETER;
    }

    SET_FMC_RPR_RPROT(ptRegBase, un8RdProtectCMD);

    do
    {
        un32Status = GET_FMC_RPR_RPROT_STATUS(ptRegBase);
    } while(!un32Status);

    return HAL_ERR_OK;
}

RAMFUNC static __inline HAL_ERR_e FMC_Erase(FMC_ID_e eFmcID, uint32_t un32PageAddr, FMC_ERASE_MODE_e eEraseMode, bool bIsSystemFlash)
{
    FMC_Type *ptRegBase = (FMC_Type *)CFMC_REG_BASE;
    uint32_t un32State;

    /* Enter Extended Mode */
    SET_FMC_EXT_MODE(ptRegBase, true);

    if (eFmcID == FMC_ID_CFMC)
    {
        SET_CFMC_CR_CS(ptRegBase, true);
    }
    else
    {
        SET_DFMC_CR_CS(ptRegBase, true);
    }
    SET_FMC_CR_CS(ptRegBase, true);

    SET_FMC_AR(ptRegBase, (un32PageAddr & FMC_VARIANT_FEATURE_ADDR_MASK));

    /* Disable interrupt */
    __asm volatile ("cpsid i");

    switch (eEraseMode)
    {
        case FMC_PAGE_ERASE_MODE:
            SET_FMC_CR_ERS_512B(ptRegBase, true);
            break;

        case FMC_1KB_ERASE_MODE:
            SET_FMC_CR_ERS_1KB(ptRegBase, true);
            break;

        case FMC_CHIP_ERASE_MODE:
            SET_FMC_CR_ERS_CHIP(ptRegBase, true);
            break;

        default:
            /* Enable interrupt */
            __asm volatile ("cpsie i");

            /* Come back to Read mode */
            CLEAR_FMC_CR(ptRegBase);

            /* Exit Extended Mode */
            SET_FMC_EXT_MODE(ptRegBase, false);

            return HAL_ERR_PARAMETER;
    }

    /* Latch signals */
    SET_FMC_CR_LATCH_SIGNAL(ptRegBase, true);

    /* Enable high voltage */
    SET_FMC_CR_HVEN(ptRegBase, true);

    /* Check is Erase is done */
    do
    {
        if (eFmcID == FMC_ID_CFMC)
        {
            un32State = GET_CFMC_STR_WRBUSY(ptRegBase);
        }
        else
        {
            un32State = GET_DFMC_STR_WRBUSY(ptRegBase);
        }
    }
    while (un32State);

    /* Disable high voltage */
    SET_FMC_CR_HVEN(ptRegBase, false);

    /* Enable interrupt */
    __asm volatile ("cpsie i");

    /* Clear status just atfer P/E is done */
    if (eFmcID == FMC_ID_CFMC)
    {
        SET_CFMC_CR_CS(ptRegBase, false);
    }
    else
    {
        SET_DFMC_CR_CS(ptRegBase, false);
    }
    SET_FMC_CR_CS(ptRegBase, false);

    /* Come back to Read mode */
    CLEAR_FMC_CR(ptRegBase);

    /* Exit Extended Mode */
    SET_FMC_EXT_MODE(ptRegBase, false);

    return HAL_ERR_OK;
}

RAMFUNC static __inline HAL_ERR_e FMC_Write(FMC_ID_e eFmcID, uint32_t un32FlashAddr, uint32_t *pun32Data, uint32_t un32Len, bool bIsWordWrite, bool bIsSystemFlash)
{
    FMC_Type *ptRegBase = (FMC_Type *)CFMC_REG_BASE;
    uint8_t *pun8ByteData = (uint8_t *)pun32Data;
    uint32_t un32State;
    uint32_t i;

    if (eFmcID == FMC_ID_DFMC)
    {
        if (bIsWordWrite)
        {
            /* DFMC supports byte-write only */
            return HAL_ERR_NOT_SUPPORTED;
        }
    }

    /* Singaling Data to Bus and latch all signals */
    for (i = 0; i < un32Len; i++)
    {
        /* Chip Select : Code flash */
        if (eFmcID == FMC_ID_CFMC)
        {
            SET_CFMC_CR_CS(ptRegBase, true);
        }
        else
        {
            SET_DFMC_CR_CS(ptRegBase, true);
        }
        SET_FMC_CR_CS(ptRegBase, true);

        /* Disable interrupt */
        __asm volatile ("cpsid i");

        /* Signaling Write command to Bus */
        SET_FMC_CR_PGM(ptRegBase, true);

        /* Signaling Address and data to Bus */
        SET_FMC_AR(ptRegBase, (un32FlashAddr & FMC_VARIANT_FEATURE_ADDR_MASK));
        if (bIsWordWrite)
        {
            SET_FMC_DR(ptRegBase, *pun32Data++);
        }
        else
        {
            SET_FMC_DR(ptRegBase, *pun8ByteData++);
        }

        /* Latch signals */
        SET_FMC_CR_LATCH_SIGNAL(ptRegBase, true);

        /* Enable high voltage */
        SET_FMC_CR_HVEN(ptRegBase, true);

        do
        {
            if (eFmcID == FMC_ID_CFMC)
            {
                un32State = GET_CFMC_STR_WRBUSY(ptRegBase);
            }
            else
            {
                un32State = GET_DFMC_STR_WRBUSY(ptRegBase);
            }
        }while(un32State);

        /* Disable high voltage */
        SET_FMC_CR_HVEN(ptRegBase, false);

        /* Enable interrupt */
        __asm volatile ("cpsie i");

        /* Inactive write command */
        SET_FMC_CR_PGM(ptRegBase, false);

        /* Clear status just atfer P/E is done */
        if (eFmcID == FMC_ID_CFMC)
        {
            SET_CFMC_CR_CS(ptRegBase, false);
        }
        else
        {
            SET_DFMC_CR_CS(ptRegBase, false);
        }
        SET_FMC_CR_CS(ptRegBase, false);

        /* Come back to Read mode */
        CLEAR_FMC_CR(ptRegBase);

        if (bIsWordWrite)
        {
            un32FlashAddr +=4;
        }
        else
        {
            un32FlashAddr++;
        }
    }

    return HAL_ERR_OK;
}

static __inline HAL_ERR_e FMC_SelfErase(FMC_ID_e eFmcID, uint32_t un32PageAddr)
{
    FMC_Type *ptRegBase = (FMC_Type *)CFMC_REG_BASE;

    if (eFmcID == FMC_ID_CFMC)
    {
        un32PageAddr |= (FMC_FEATURE_FLASH_BASE_ADDR | FMC_FEATURE_CODE_FLASH_BASE_OFFSET);
    }
    else
    {
        un32PageAddr |= (FMC_FEATURE_FLASH_BASE_ADDR | FMC_FEATURE_DATA_FLASH_BASE_OFFSET);
    }

    SET_FMC_EXT_MODE(ptRegBase, true);

    SET_FMC_CR(ptRegBase, CFMC_CR_SELF_ERS_CMD);
    __NOP();__NOP();__NOP();__NOP();__NOP();

    *(uint32_t *)un32PageAddr = 0xFFFFFFFF;
    __NOP();__NOP();__NOP();__NOP();__NOP();

    CLEAR_FMC_CR(ptRegBase);
    __NOP();__NOP();__NOP();__NOP();__NOP();

    SET_FMC_EXT_MODE(ptRegBase, false);

    return HAL_ERR_OK;
}

static __inline HAL_ERR_e FMC_SelfWrite(FMC_ID_e eFmcID, uint32_t un32FlashAddr, uint32_t *pun32Data)
{
    FMC_Type *ptRegBase = (FMC_Type *)CFMC_REG_BASE;

    if (eFmcID == FMC_ID_CFMC)
    {
        un32FlashAddr |= (FMC_FEATURE_FLASH_BASE_ADDR | FMC_FEATURE_CODE_FLASH_BASE_OFFSET);
    }
    else
    {
        un32FlashAddr |= (FMC_FEATURE_FLASH_BASE_ADDR | FMC_FEATURE_DATA_FLASH_BASE_OFFSET);
    }

    SET_FMC_EXT_MODE(ptRegBase, true);

    /* Signalng Write to Bus */
    __asm volatile ("cpsid i");

    SET_FMC_CR(ptRegBase, CFMC_CR_SELF_PGM_CMD);
    __NOP();__NOP();__NOP();__NOP();__NOP();

    *(uint32_t *)un32FlashAddr = *pun32Data;
    __NOP();__NOP();__NOP();__NOP();__NOP();

    CLEAR_FMC_CR(ptRegBase);
    __NOP();__NOP();__NOP();__NOP();__NOP();

    __asm volatile ("cpsie i");

    SET_FMC_EXT_MODE(ptRegBase, false);

    return HAL_ERR_OK;
}

#endif /* _HAL_FMC_V_02_01_00_H_ */

