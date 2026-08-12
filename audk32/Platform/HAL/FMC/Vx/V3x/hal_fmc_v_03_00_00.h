/**
 *******************************************************************************
 * @file        hal_fmc_v_03_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 03.00.00 typed FMC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_FMC_V_03_00_00_H_
#define _HAL_FMC_V_03_00_00_H_

#include "hal_fmc.h"

/* Feature(Function) Configuration Define */
#define FMC_FEATURE_FLASH_BASE_ADDR                   STARTUP_FLASH_BASE_ADDR
#define FMC_FEATURE_CODE_FLASH_BASE_OFFSET            STARTUP_CODE_FLASH_BASE_OFFSET
#define FMC_FEATURE_DATA_FLASH_BASE_OFFSET            STARTUP_DATA_FLASH_BASE_OFFSET
#define FMC_FEATURE_SYSTEM_FLASH_BASE_OFFSET          STARTUP_SYSTEM_FLASH_BASE_OFFSET
#define FMC_FEATURE_SYSTEM_FLASH_OFFSET_MASK          STARTUP_SYSTEM_FLASH_OFFSET_MASK
#define FMC_FEATURE_PAGE_SIZE                         STARTUP_PAGE_SIZE
#define FMC_FEATURE_DATA_PAGE_SIZE                    STARTUP_DATA_PAGE_SIZE
#define FMC_FEATURE_SELF_PROGRAM_ERASE                0
#define FMC_FEATURE_WRITE_IMPL_BY_SELF_WRITE          0
#define FMC_FEATURE_PASSWD_LOCK                       1
#define FMC_FEATURE_CRC                               0
#define FMC_FEATURE_IRQ_SERVICE                       0 /* Only Write done interrupt is supported but nobody uses this feature in NO-OS environment */
#define FMC_FEATURE_RUMTIME_READ_PROTECTION           1

#define FMC_FEATURE_CFMC_BANK_SWITCH                  0
#if defined (CFMC_CONF_BBLOCK_Pos)
#define FMC_FEATURE_CFMC_BBLOCK                       1
#else
#define FMC_FEATURE_CFMC_BBLOCK                       0
#endif
#define FMC_FEATURE_CFMC_BBLOCK_IMPL_BY_WRITE_PROT    0
#define FMC_FEATURE_CFMC_IDCACHE                      1

#define FMC_FEATURE_DFMC_WRITE_BYTE                   0

/* Internal Macro */
#define CFMC_REG_BASE                                 CFMC_BASE
#define DFMC_REG_BASE                                 DFMC_BASE

/* Flash P/E Mode commands */
#define FMC_PE_MODE_CMD1                              0x01234567
#define FMC_PE_MODE_CMD2                              0x12345678
#define FMC_PE_MODE_CMD3                              0x23456789
#define CFMC_SYSFLASH_PE_MODE_CMD1                    0x3456789A
#define CFMC_SYSFLASH_PE_MODE_CMD2                    0x456789AB
#define CFMC_SYSFLASH_PE_MODE_CMD3                    0x56789ABC

/* Status check count */
#define FMC_PE_STATUS_CHECK_COUNT                     0x35000
#define FMC_STATUS_CHECK_COUNT                        20
#define FMC_STATUS_ERROR_Mask                         0x003F0000

/* Write Protection Mask */
#define FMC_WPROT_WPROT_Mask                          0x0000FFFF
#define FMC_WPROT_WPROT_BIT_Pos                       0
#define FMC_WPROT_LAST_BLK_Mask                       0x00008000
#define FMC_WPROT_LAST_4KBLK_Mask                     0xFF000000

/* Read protection command */
#define FMC_RD_PROTECT_LEVEL1_CMD                     0x39
#define FMC_RD_PROTECT_LEVEL2_CMD                     0x07
#define FMC_RD_PROTECT_PASSWD_CMD                     0x80

/* CRC property */
/* Address should be aligned to 512B */
#define CFMC_CRC_ADDR_ALIGNMENT                       0xFF
#define DFMC_CRC_ADDR_ALIGNMENT                       0x3F

/* Define internal variant features */
#if defined (CFMC_CTRL_S1KERS_Pos)
#define FMC_VARIANT_FEATURE_1KB_SECTOR                1
#else
#define FMC_VARIANT_FEATURE_FMC_1KB_SECTOR            0
#endif

#if defined (CFMC_CTRL_SERS_Pos)
#define FMC_VARIANT_FEATURE_2KB_SECTOR                1
#else
#define FMC_VARIANT_FEATURE_FMC_2KB_SECTOR            0
#endif

#if defined (CFMC_CTRL_S4KERS_Pos)
#define FMC_VARIANT_FEATURE_4KB_SECTOR                1
#else
#define FMC_VARIANT_FEATURE_4KB_SECTOR                0
#endif

#if defined (CFMC_CTRL_BURSTMD_Pos)
#define FMC_VARIANT_FEATURE_BURST_PGM                 1
#else
#define FMC_VARIANT_FEATURE_BURST_PGM                 0
#endif

#if defined (CFMC_CONF_BBLOCK_Pos)
#define FMC_VARIANT_FEATURE_CFMC_BBLOCK               1
#else
#define FMC_VARIANT_FEATURE_CFMC_BBLOCK               0
#endif

#if defined (CFMC_CONF_WRITE_Pos)
#define FMC_VARIANT_FEATURE_CFMC_REGISTER_UPDATE      1
#else
#define FMC_VARIANT_FEATURE_CFMC_REGISTER_UPDATE      0
#endif

/* Macro definition */
#define SET_CFMC_CFGR_DCACHE_RESET(Peri,Data)         SET_BIT(Peri,Data,CFMC,CONF,DCRST)
#define SET_CFMC_CFGR_ICACHE_RESET(Peri,Data)         SET_BIT(Peri,Data,CFMC,CONF,ICRST)
#define SET_CFMC_CFGR_DCACHE_EN(Peri,Data)            SET_BIT(Peri,Data,CFMC,CONF,DCEN)
#define SET_CFMC_CFGR_ICACHE_EN(Peri,Data)            SET_BIT(Peri,Data,CFMC,CONF,ICEN)
#if (FMC_VARIANT_FEATURE_CFMC_REGISTER_UPDATE)
#define SET_CFMC_CFGR_REGISTER_UPDATE(Peri,Data)      SET_BIT(Peri,Data,CFMC,CONF,WRITE)
#endif
#if (FMC_VARIANT_FEATURE_CFMC_BBLOCK)
#define SET_CFMC_CFGR_WPROT_BBLK(Peri,Data)           SET_BIT(Peri,Data,CFMC,CONF,BBLOCK)
#endif
#define SET_FMC_CFGR_LATENCY(Peri,Data)               SET_BIT(Peri,Data,CFMC,CONF,LATENCY)
#define SET_FMC_CFGR(Peri,Data)                       SET_REG(Peri,Data,CONF)

#define SET_FMC_CR_FLASH_LOCK(Peri,Data)              (Peri->CTRL = (Data > 0)? ((Peri->CTRL & ~CFMC_CTRL_FLOCK_Msk) | 0x80000000) \
                                                      : (Peri->CTRL & ~CFMC_CTRL_FLOCK_Msk))
#define SET_FMC_CR_SYSFLASH_LOCK(Peri,Data)           SET_BIT(Peri,Data,CFMC,CTRL,OLOCK)

#if (FMC_VARIANT_FEATURE_BURST_PGM == 1)
#define SET_FMC_CR_BURST_PGM(Peri,Data)               SET_BIT(Peri,Data,CFMC,CTRL,BURSTMD)
#endif

#define SET_FMC_CR_WR_DONE_IRQ_EN(Peri,Data)          SET_BIT(Peri,Data,CFMC,CTRL,WDIEN)
#define SET_FMC_CR_ERS_512B(Peri,Data)                SET_BIT(Peri,Data,CFMC,CTRL,PERS)

#if (FMC_VARIANT_FEATURE_1KB_SECTOR == 1)
#define SET_FMC_CR_ERS_1KB(Peri,Data)                 SET_BIT(Peri,Data,CFMC,CTRL,S1KERS)
#endif

#if (FMC_VARIANT_FEATURE_2KB_SECTOR == 1)
#define SET_FMC_CR_ERS_2KB(Peri,Data)                 SET_BIT(Peri,Data,CFMC,CTRL,SERS)
#endif

#if (FMC_VARIANT_FEATURE_4KB_SECTOR == 1)
#define SET_FMC_CR_ERS_4KB(Peri,Data)                 SET_BIT(Peri,Data,CFMC,CTRL,S4KERS)
#endif

#define SET_FMC_CR_ERS_CHIP(Peri,Data)                SET_BIT(Peri,Data,CFMC,CTRL,CERS)
#define SET_FMC_CR_PGM(Peri,Data)                     SET_BIT(Peri,Data,CFMC,CTRL,PGM)
#define GET_FMC_CR(Peri)                              GET_REG(Peri,CTRL)
#define SET_FMC_CR(Peri,Data)                         SET_REG(Peri,Data,CTRL)
#define CLEAR_FMC_CR(Peri)                            SET_REG(Peri,0,CTRL)

#define SET_FMC_FLSKEYR(Peri,Data)                    SET_REG(Peri,Data,FLSKEY)
#define SET_CFMC_OTPKEYR(Peri,Data)                   SET_REG(Peri,Data,OTPKEY)

#define GET_FMC_STR_CRCDONE(Peri)                     GET_BIT(Peri,CFMC,STAT,CDONE)
#define GET_FMC_STR_WRDONE(Peri)                      GET_BIT(Peri,CFMC,STAT,WDONE)
#define GET_FMC_STR_CRCBUSY(Peri)                     GET_BIT(Peri,CFMC,STAT,CBUSY)
#define GET_FMC_STR_WRBUSY(Peri)                      GET_BIT(Peri,CFMC,STAT,WBUSY)
#define SET_FMC_STR(Peri,Data)                        SET_REG(Peri,Data,STAT)
#define GET_FMC_STR(Peri)                             GET_REG(Peri,STAT)
#define CLEAR_FMC_STR(Peri)                           SET_REG(Peri,0xFFFFFFFC,STAT)

/* Pseudo STR by READPROT register */
#define GET_CFMC_STR_PWMATCH(Peri)                    GET_BIT(Peri,CFMC,READPROT,PWMATCH)
#define GET_CFMC_STR_ERS_CHIP(Peri)                   GET_BIT(Peri,CFMC,READPROT,CERSD)
#define GET_CFMC_STR_RPROT_LVL2_DBG(Peri)             GET_BIT(Peri,CFMC,READPROT,LVL2_STS)
#define GET_CFMC_STR_RPROT_LVL1_DBG(Peri)             GET_BIT(Peri,CFMC,READPROT,LVL1_STS)
#define GET_CFMC_STR_RPROT_LVL2(Peri)                 GET_BIT(Peri,CFMC,READPROT,LVL2_EN)
#define GET_CFMC_STR_RPROT_LVL1(Peri)                 GET_BIT(Peri,CFMC,READPROT,LVL1_EN)
#define GET_CFMC_STR_DBG_CONNECTION(Peri)             GET_BIT(Peri,CFMC,READPROT,DBGMOD)

#define SET_FMC_RPR_RPROT(Peri,Data)                  SET_BIT(Peri,Data,CFMC,READPROT,RPROT)
#define GET_FMC_RPR(Peri)                             GET_REG(Peri,READPROT)

#define SET_CFMC_PASSWD_REGISTER(Peri,Data)           SET_REG(Peri,Data,PWPRST)
#define SET_CFMC_PASSWD_MATCH(Peri,Data)              SET_REG(Peri,Data,PWIN)

#define SET_FMC_WPR_WPROT(Peri,Data)                  SET_REG(Peri,Data,FLSPROT)
#define GET_FMC_WPR_WPROT(Peri)                       GET_REG(Peri,FLSPROT)

/* CRC */
#define SET_FMC_CRC_START_ADDR(Peri,Data)             SET_REG(Peri,Data,CHKSADDR)
#define SET_FMC_CRC_END_ADDR(Peri,Data)               SET_REG(Peri,Data,CHKEADDR)
#define GET_FMC_CRC_RESULT(Peri)                      GET_BIT(Peri,CFMC,CHKDOUT,CDOUT)
#define SET_FMC_CRC_CR_BACKGROUND_MODE(Peri,Data)     SET_BIT(Peri,Data,CFMC,CHKCTRL,BGEN)
#define SET_FMC_CRC_CR_BURST_MODE(Peri,Data)          SET_BIT(Peri,Data,CFMC,CHKCTRL,BSTEN)
#define SET_FMC_CRC_CR_IRQ_EN(Peri,Data)              SET_BIT(Peri,Data,CFMC,CHKCTRL,CDIEN)
#define SET_FMC_CRC_CR_RESET_CRC_DATA(Peri,Data)      SET_BIT(Peri,Data,CFMC,CHKCTRL,CDRST)

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_CFMC_PROT_RESET(Peri,Data)            SET_BIT(Peri,Data,SCU,PRER1,CFMC)
#define SET_SCU_DFMC_PROT_RESET(Peri,Data)            SET_BIT(Peri,Data,SCU,PRER1,DFMC)

/* Inline functions */
static __inline IRQn_Type FMC_GetIRQNumber(FMC_ID_e eFmcID);
static __inline uint32_t FMC_GetEvent(FMC_ID_e eFmcID);
static __inline void FMC_SetConfig(FMC_ID_e eFmcID, FMC_CONFIG_t tConfig);
static __inline void CFMC_SetCache(CFMC_CACHE_ID_e eCacheID, bool bRequestEnable);
static __inline void FMC_SetWriteProtect(FMC_ID_e eFmcID, uint32_t un32BlockIdx, uint32_t un32TargetBlk, bool bRequestLock);
static __inline void CFMC_SetWriteProtectBootBlk(bool bRequestLock);
static __inline HAL_ERR_e FMC_SetReadProtect(FMC_ID_e eFmcID, FMC_RD_PROTECT_CONFIG_t tRdProtectConfig);
static __inline HAL_ERR_e FMC_SetMatchedPassword(FMC_ID_e eFmcID, uint32_t un32Password);
static __inline HAL_ERR_e FMC_Erase(FMC_ID_e eFmcID, uint32_t un32PageAddr, FMC_ERASE_MODE_e eEraseMode, bool bIsSystemFlash);
static __inline HAL_ERR_e FMC_Write(FMC_ID_e eFmcID, volatile uint32_t un32FlashAddr, uint32_t *pun32Data, uint32_t un32Len, bool bIsWordWrite, bool bIsSystemFlash);
static __inline HAL_ERR_e FMC_GetCRC(FMC_ID_e eFmcID, FMC_CRC_MODE_e eCrcMode, uint32_t un32FlashAddr, uint32_t un32Len, uint32_t *pun32ResultCRC);

RAMFUNC static __inline IRQn_Type FMC_GetIRQNumber(FMC_ID_e eFmcID)
{
    return (IRQn_Type)(CFMC_IRQn + (IRQn_Type)eFmcID);
}

RAMFUNC static __inline uint32_t FMC_GetEvent(FMC_ID_e eFmcID)
{
    CFMC_Type *ptRegBase;
    uint32_t un32Event;

    if (eFmcID == FMC_ID_CFMC)
    {
        ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    }
    else
    {
        ptRegBase = (CFMC_Type *)DFMC_REG_BASE;
    }

    un32Event = GET_FMC_STR(ptRegBase);
    CLEAR_FMC_STR(ptRegBase);

    return un32Event;
}

RAMFUNC static __inline void FMC_SetConfig(FMC_ID_e eFmcID, FMC_CONFIG_t tConfig)
{
    /* Operation time-out is not supported */
    /* CRC is not supported */
    /* Set up bus-latency only */

    CFMC_Type *ptRegBase;

    if (eFmcID == FMC_ID_CFMC)
    {
        ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    }
    else
    {
        ptRegBase = (CFMC_Type *)DFMC_REG_BASE;
    }

#if (FMC_VARIANT_FEATURE_CFMC_REGISTER_UPDATE == 1)
    SET_CFMC_CFGR_REGISTER_UPDATE(ptRegBase, true);
#endif

    SET_FMC_CFGR_LATENCY(ptRegBase, tConfig.un8Latency);
    CLEAR_FMC_STR(ptRegBase);

    return;
}

RAMFUNC static __inline void CFMC_SetCache(CFMC_CACHE_ID_e eCacheID, bool bRequestEnable)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;

    switch (eCacheID)
    {
        case CFMC_INST_CACHE:
            if (bRequestEnable)
            {
                SET_CFMC_CFGR_ICACHE_RESET(ptRegBase, true);
                SET_CFMC_CFGR_ICACHE_RESET(ptRegBase, false);
                SET_CFMC_CFGR_ICACHE_EN(ptRegBase, true);
            }
            else
            {
                SET_CFMC_CFGR_ICACHE_EN(ptRegBase, false);
            }
            break;

        case CFMC_DATA_CACHE:
            if (bRequestEnable)
            {
                SET_CFMC_CFGR_DCACHE_RESET(ptRegBase, true);
                SET_CFMC_CFGR_DCACHE_RESET(ptRegBase, false);
                SET_CFMC_CFGR_DCACHE_EN(ptRegBase, true);
            }
            else
            {
                SET_CFMC_CFGR_DCACHE_EN(ptRegBase, false);
            }
            break;

        case CFMC_INST_DATA_CACHE:
            if (bRequestEnable)
            {
                SET_CFMC_CFGR_ICACHE_RESET(ptRegBase, true);
                SET_CFMC_CFGR_DCACHE_RESET(ptRegBase, true);
                SET_CFMC_CFGR_ICACHE_RESET(ptRegBase, false);
                SET_CFMC_CFGR_DCACHE_RESET(ptRegBase, false);

                SET_CFMC_CFGR_ICACHE_EN(ptRegBase, true);
                SET_CFMC_CFGR_DCACHE_EN(ptRegBase, true);
            }
            else
            {
                SET_CFMC_CFGR_ICACHE_EN(ptRegBase, false);
                SET_CFMC_CFGR_DCACHE_EN(ptRegBase, false);
            }
            break;

    }
}

RAMFUNC static __inline void FMC_SetWriteProtect(FMC_ID_e eFmcID, uint32_t un32BlockIdx, uint32_t un32TargetBlk, bool bRequestLock)
{
    CFMC_Type *ptRegBase;
    uint32_t un32Reg;

    (void)un32BlockIdx;

    if (eFmcID == FMC_ID_CFMC)
    {
        ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    }
    else
    {
        ptRegBase = (CFMC_Type *)DFMC_REG_BASE;
    }
    un32Reg = GET_FMC_WPR_WPROT(ptRegBase);

    if (!bRequestLock)
    {
        /* Update Lower Write Protect */
        if (un32TargetBlk == 0xFFFFFFFF)
        {
            un32Reg &= ~FMC_WPROT_WPROT_Mask;
        }
        else
        {
            un32Reg &= ~un32TargetBlk;
        }

        /* Update Higher Write Protect (4KB) */
        if (un32TargetBlk & FMC_WPROT_LAST_BLK_Mask)
        {
            un32Reg |= FMC_WPROT_LAST_4KBLK_Mask;
        }
    }
    else
    {
        /* Update Lower Write Protect */
        if (un32TargetBlk == 0xFFFFFFFF)
        {
            un32Reg |= FMC_WPROT_WPROT_Mask;
        }
        else
        {
            un32Reg |= un32TargetBlk;
        }

        /* Update Higher Write Protect (4KB) */
        if (un32TargetBlk & FMC_WPROT_LAST_BLK_Mask)
        {
            un32Reg &= ~FMC_WPROT_LAST_4KBLK_Mask;
        }
    }
    SET_FMC_WPR_WPROT(ptRegBase, un32Reg);

    return;
}


RAMFUNC static __inline void CFMC_SetWriteProtectBootBlk(bool bRequestLock)
{
#if (FMC_VARIANT_FEATURE_CFMC_BBLOCK == 1)
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;

    SET_CFMC_CFGR_WPROT_BBLK(ptRegBase, bRequestLock);
#endif

    return;
}

RAMFUNC static __inline HAL_ERR_e FMC_SetReadProtect(FMC_ID_e eFmcID, FMC_RD_PROTECT_CONFIG_t tRdProtectConfig)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    uint16_t un16RdProtectCMD;
    uint32_t un32Status;
    uint8_t un8Cnt = 0;

    if (eFmcID == FMC_ID_DFMC)
    {
        return HAL_ERR_NOT_SUPPORTED;
    }

    if (GET_CFMC_STR_DBG_CONNECTION(ptRegBase))
    {
        __asm volatile ("cpsid i");
    }

    if (tRdProtectConfig.eRdProtectLevel >= FMC_RD_PROTECT_PASSWD)
    {
        SET_CFMC_PASSWD_REGISTER(ptRegBase, tRdProtectConfig.un32RegisteredPasswd);
        SET_CFMC_PASSWD_REGISTER(ptRegBase, tRdProtectConfig.un32RegisteredPasswd);
    }

    switch (tRdProtectConfig.eRdProtectLevel)
    {
        case FMC_RD_PROTECT_LEVEL1:
            un16RdProtectCMD = FMC_RD_PROTECT_LEVEL1_CMD;
            un32Status = BIT_NAME_MSK(CFMC_,READPROT_,LVL1_EN_);
            break;

        case FMC_RD_PROTECT_LEVEL2:
            un16RdProtectCMD = FMC_RD_PROTECT_LEVEL2_CMD;
            un32Status = BIT_NAME_MSK(CFMC_,READPROT_,LVL2_EN_);
            break;

        case FMC_RD_PROTECT_LEVEL1_PASSWD:
            un16RdProtectCMD = FMC_RD_PROTECT_LEVEL1_CMD | FMC_RD_PROTECT_PASSWD_CMD;
            un32Status = BIT_NAME_MSK(CFMC_,READPROT_,LVL1_EN_);
            break;

        case FMC_RD_PROTECT_LEVEL2_PASSWD:
            un16RdProtectCMD = FMC_RD_PROTECT_LEVEL2_CMD | FMC_RD_PROTECT_PASSWD_CMD;
            un32Status = BIT_NAME_MSK(CFMC_,READPROT_,LVL2_EN_);
            break;

        default:
            if (GET_CFMC_STR_DBG_CONNECTION(ptRegBase))
            {
                __asm volatile ("cpsie i");
            }
            return HAL_ERR_PARAMETER;
    }

    SET_FMC_RPR_RPROT(ptRegBase, un16RdProtectCMD);
    do
    {
        __NOP();__NOP();__NOP();__NOP();__NOP();
        un8Cnt++;
        if (un8Cnt > FMC_STATUS_CHECK_COUNT)
        {
            break;
        }
    } while(!(GET_FMC_RPR(ptRegBase) & un32Status));

    if (un8Cnt > FMC_STATUS_CHECK_COUNT)
    {
        return HAL_ERR_TIMEOUT;
    }
    else
    {
        return HAL_ERR_OK;
    }
}

RAMFUNC static __inline HAL_ERR_e FMC_SetMatchedPassword(FMC_ID_e eFmcID, uint32_t un32Password)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;;
    uint8_t un8Cnt = 0;

    if (eFmcID == FMC_ID_DFMC)
    {
        return HAL_ERR_NOT_SUPPORTED;
    }

    SET_CFMC_PASSWD_MATCH(ptRegBase, un32Password);
    SET_CFMC_PASSWD_MATCH(ptRegBase, un32Password);

    do
    {
        __NOP();__NOP();__NOP();__NOP();__NOP();
        un8Cnt++;
        if (un8Cnt > FMC_STATUS_CHECK_COUNT)
        {
            break;
        }
    } while(!GET_CFMC_STR_PWMATCH(ptRegBase));

    if (GET_CFMC_STR_DBG_CONNECTION(ptRegBase))
    {
        __asm volatile ("cpsie i");
    }

    if (un8Cnt > FMC_STATUS_CHECK_COUNT)
    {
        return HAL_ERR_TIMEOUT;
    }
    else
    {
        return HAL_ERR_OK;
    }
}

RAMFUNC static __inline HAL_ERR_e FMC_Erase(FMC_ID_e eFmcID, uint32_t un32PageAddr, FMC_ERASE_MODE_e eEraseMode, bool bIsSystemFlash)
{
    CFMC_Type *ptRegBase;
    uint32_t un32State = 0xFF;
    uint32_t un32Cnt = 0;

    if (eFmcID == FMC_ID_CFMC)
    {
        un32PageAddr |= (FMC_FEATURE_FLASH_BASE_ADDR | FMC_FEATURE_CODE_FLASH_BASE_OFFSET);
        ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    }
    else
    {
        ptRegBase = (CFMC_Type *)DFMC_REG_BASE;
        un32PageAddr |= (FMC_FEATURE_FLASH_BASE_ADDR | FMC_FEATURE_DATA_FLASH_BASE_OFFSET);
    }

    /* Make up byte-address to be aligned to word size */
    un32PageAddr = un32PageAddr & ~(0x3);

    /* Setup PE command */
    if (bIsSystemFlash)
    {
        SET_CFMC_OTPKEYR(ptRegBase, CFMC_SYSFLASH_PE_MODE_CMD1);
        SET_CFMC_OTPKEYR(ptRegBase, CFMC_SYSFLASH_PE_MODE_CMD2);
        SET_CFMC_OTPKEYR(ptRegBase, CFMC_SYSFLASH_PE_MODE_CMD3);
    }
    else
    {
        SET_FMC_FLSKEYR(ptRegBase, FMC_PE_MODE_CMD1);
        SET_FMC_FLSKEYR(ptRegBase, FMC_PE_MODE_CMD2);
        SET_FMC_FLSKEYR(ptRegBase, FMC_PE_MODE_CMD3);
    }

    /* Setup Erase option */
    switch (eEraseMode)
    {
        case FMC_PAGE_ERASE_MODE:
            SET_FMC_CR_ERS_512B(ptRegBase, true);
            break;

#if (FMC_VARIANT_FEATURE_1KB_SECTOR == 1)
        case FMC_1KB_ERASE_MODE:
            SET_FMC_CR_ERS_1KB(ptRegBase, true);
            break;
#endif

#if (FMC_VARIANT_FEATURE_2KB_SECTOR == 1)
        case FMC_2KB_ERASE_MODE:
            SET_FMC_CR_ERS_2KB(ptRegBase, true);
            break;
#endif

#if (FMC_VARIANT_FEATURE_4KB_SECTOR == 1)
        case FMC_4KB_ERASE_MODE:
            SET_FMC_CR_ERS_4KB(ptRegBase, true);
            break;
#endif
        case FMC_CHIP_ERASE_MODE:
            SET_FMC_CR_ERS_CHIP(ptRegBase, true);
            break;

        default:
            /* Re-Lock Flash */
            if (bIsSystemFlash)
            {
                SET_FMC_CR_SYSFLASH_LOCK(ptRegBase, true);
            }
            else
            {
                SET_FMC_CR_FLASH_LOCK(ptRegBase, true);
            }
            return HAL_ERR_PARAMETER;
    }

    /* Signaling Erase flash commands to Bus */
    *(volatile uint32_t *)un32PageAddr = 0xFFFFFFFF;

    /* Check if Erase is done */
    do
    {
        __NOP();__NOP();__NOP();__NOP();__NOP();
        un32Cnt++;
        if (un32Cnt > FMC_PE_STATUS_CHECK_COUNT)
        {
            break;
        }
        un32State= GET_FMC_STR_WRBUSY(ptRegBase);
    }while (un32State);

    /* Clear Erase option */
    switch (eEraseMode)
    {
         case FMC_PAGE_ERASE_MODE:
             SET_FMC_CR_ERS_512B(ptRegBase, false);
             break;

#if (FMC_VARIANT_FEATURE_1KB_SECTOR == 1)
         case FMC_1KB_ERASE_MODE:
             SET_FMC_CR_ERS_1KB(ptRegBase, false);
             break;
#endif

#if (FMC_VARIANT_FEATURE_2KB_SECTOR == 1)
         case FMC_2KB_ERASE_MODE:
             SET_FMC_CR_ERS_2KB(ptRegBase, false);
             break;
#endif

#if (FMC_VARIANT_FEATURE_4KB_SECTOR == 1)
         case FMC_4KB_ERASE_MODE:
             SET_FMC_CR_ERS_4KB(ptRegBase, false);
             break;
#endif
         case FMC_CHIP_ERASE_MODE:
             SET_FMC_CR_ERS_CHIP(ptRegBase, false);
             break;

         default:
             return HAL_ERR_PARAMETER;
    }

    /* Re-Lock Flash */
    if (bIsSystemFlash)
    {
        SET_FMC_CR_SYSFLASH_LOCK(ptRegBase, true);
    }
    else
    {
        SET_FMC_CR_FLASH_LOCK(ptRegBase, true);
    }

    if (un32Cnt > FMC_PE_STATUS_CHECK_COUNT)
    {
        return HAL_ERR_TIMEOUT;
    }
    else
    {
        un32State = GET_FMC_STR(ptRegBase);
        SET_FMC_STR(ptRegBase, un32State);

        if (un32State & FMC_STATUS_ERROR_Mask)
        {
            return HAL_ERR_INVALID_USE;
        }

        return HAL_ERR_OK;
    }
}

RAMFUNC static __inline HAL_ERR_e FMC_Write(FMC_ID_e eFmcID, volatile uint32_t un32FlashAddr, uint32_t *pun32Data, uint32_t un32Len, bool bIsWordWrite, bool bIsSystemFlash)
{
    CFMC_Type *ptRegBase;
    uint32_t i;
    uint32_t un32State = 0xFF;
    uint32_t un32Cnt = 0;

    /* word write only */
    if (!bIsWordWrite)
    {
        return HAL_ERR_NOT_SUPPORTED;
    }

    if (eFmcID == FMC_ID_CFMC)
    {
        ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
        un32FlashAddr |= (FMC_FEATURE_FLASH_BASE_ADDR | FMC_FEATURE_CODE_FLASH_BASE_OFFSET);
    }
    else
    {
        ptRegBase = (CFMC_Type *)DFMC_REG_BASE;
        un32FlashAddr |= (FMC_FEATURE_FLASH_BASE_ADDR | FMC_FEATURE_DATA_FLASH_BASE_OFFSET);
    }

    /* Make up byte-address to be aligned to word size */
    un32FlashAddr = un32FlashAddr & ~(0x3);

    /* Select target flash */
    if (bIsSystemFlash)
    {
        SET_CFMC_OTPKEYR(ptRegBase, CFMC_SYSFLASH_PE_MODE_CMD1);
        SET_CFMC_OTPKEYR(ptRegBase, CFMC_SYSFLASH_PE_MODE_CMD2);
        SET_CFMC_OTPKEYR(ptRegBase, CFMC_SYSFLASH_PE_MODE_CMD3);
    }
    else
    {
        SET_FMC_FLSKEYR(ptRegBase, FMC_PE_MODE_CMD1);
        SET_FMC_FLSKEYR(ptRegBase, FMC_PE_MODE_CMD2);
        SET_FMC_FLSKEYR(ptRegBase, FMC_PE_MODE_CMD3);
    }

    /* Singaling Write Command to Bus */
    SET_FMC_CR_PGM(ptRegBase, true);

    /* Singaling Data to Bus and latch all signals */
    for (i=0; i<un32Len; i++, un32FlashAddr +=4)
    {
        *(uint32_t *)un32FlashAddr = *pun32Data++;

        /* Check if Write is done */
        un32Cnt = 0;
        do
        {
            __NOP();__NOP();__NOP();__NOP();__NOP();
            un32Cnt++;
            if (un32Cnt > FMC_PE_STATUS_CHECK_COUNT)
            {
                goto EXIT_WRITE;
            }
            un32State = GET_FMC_STR_WRBUSY(ptRegBase);
        }while (un32State);
    }

EXIT_WRITE:
    /* Re-Lock Flash */
    if (bIsSystemFlash)
    {
        SET_FMC_CR_SYSFLASH_LOCK(ptRegBase, true);
    }
    else
    {
        SET_FMC_CR_FLASH_LOCK(ptRegBase, true);
    }

    SET_FMC_CR_PGM(ptRegBase, false);

    if (un32Cnt > FMC_PE_STATUS_CHECK_COUNT)
    {
        return HAL_ERR_TIMEOUT;
    }
    else
    {
        un32State = GET_FMC_STR(ptRegBase);
        SET_FMC_STR(ptRegBase, un32State);

        if (un32State & FMC_STATUS_ERROR_Mask)
        {
            return HAL_ERR_INVALID_USE;
        }

        return HAL_ERR_OK;
    }
}

RAMFUNC static __inline HAL_ERR_e FMC_GetCRC(FMC_ID_e eFmcID, FMC_CRC_MODE_e eCrcMode, uint32_t un32FlashAddr, uint32_t un32Len, uint32_t *pun32ResultCRC)
{
    CFMC_Type *ptRegBase;
    uint32_t un32State = 0xFF;
    uint32_t un32AddressMask;
    uint32_t un32SizeGranularity;
    uint8_t un8Cnt = 0;

    if (eFmcID == FMC_ID_CFMC)
    {
        ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
        un32AddressMask = CFMC_CRC_ADDR_ALIGNMENT;
        un32SizeGranularity = CFMC_CRC_ADDR_ALIGNMENT + 1;
    }
    else
    {
        ptRegBase = (CFMC_Type *)DFMC_REG_BASE;
        un32AddressMask = DFMC_CRC_ADDR_ALIGNMENT;
        un32SizeGranularity = DFMC_CRC_ADDR_ALIGNMENT + 1;
    }

    if (un32FlashAddr & un32AddressMask)
    {
        return HAL_ERR_PARAMETER;
    }
    if (un32Len % un32SizeGranularity)
    {
        return HAL_ERR_PARAMETER;
    }


    SET_FMC_CRC_START_ADDR(ptRegBase, un32FlashAddr);
    SET_FMC_CRC_END_ADDR(ptRegBase, (un32FlashAddr + un32Len - 1));
    SET_FMC_CRC_CR_RESET_CRC_DATA(ptRegBase, true);

    switch (eCrcMode)
    {
        case FMC_CRC_BACKGROUND_MODE:
            SET_FMC_CRC_CR_IRQ_EN(ptRegBase, false);
            SET_FMC_CRC_CR_BACKGROUND_MODE(ptRegBase, true);
            break;

        case FMC_CRC_BURST_MODE:
            SET_FMC_CRC_CR_IRQ_EN(ptRegBase, false);
            SET_FMC_CRC_CR_BURST_MODE(ptRegBase, true);
            break;

        case FMC_CRC_BACKGROUND_IRQ_MODE:
            SET_FMC_CRC_CR_IRQ_EN(ptRegBase, true);
            SET_FMC_CRC_CR_BACKGROUND_MODE(ptRegBase, true);
            break;

        case FMC_CRC_BURST_IRQ_MODE:
            SET_FMC_CRC_CR_IRQ_EN(ptRegBase, true);
            SET_FMC_CRC_CR_BURST_MODE(ptRegBase, true);
            break;

        default:
            SET_FMC_CRC_CR_RESET_CRC_DATA(ptRegBase, false);
            return HAL_ERR_PARAMETER;
    }

    do
    {
        __NOP();__NOP();__NOP();__NOP();__NOP();
        un8Cnt++;
        if (un8Cnt > FMC_STATUS_CHECK_COUNT)
        {
            break;
        }

        un32State = GET_FMC_STR_CRCBUSY(ptRegBase);
    }while(un32State);

    SET_FMC_CRC_CR_RESET_CRC_DATA(ptRegBase, false);

    if (un8Cnt > FMC_STATUS_CHECK_COUNT)
    {
        return HAL_ERR_TIMEOUT;
    }

    un32State = GET_FMC_CRC_RESULT(ptRegBase);
    *pun32ResultCRC = un32State;

    return HAL_ERR_OK;
}

#endif /* _HAL_FMC_V_03_00_00_H_ */
