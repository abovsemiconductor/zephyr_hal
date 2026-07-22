/**
 *******************************************************************************
 * @file        hal_cfmc_v_03_01_01.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 03.01.00 typed CFMC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_CFMC_V_03_01_01_H_
#define _HAL_CFMC_V_03_01_01_H_

#include "hal_cfmc.h"

/* External References */
extern int8_t PRV_CHIPSET_GetDebuggerConnectionStatus (void);

/* Feature(Function) Configuration Define */
#define CFMC_FEATURE_FLASH_BASE_ADDR                  STARTUP_FLASH_BASE_ADDR
#define CFMC_FEATURE_CODE_FLASH_BASE_OFFSET           STARTUP_CODE_FLASH_BASE_OFFSET
#define CFMC_FEATURE_SYSTEM_FLASH_BASE_OFFSET         STARTUP_SYSTEM_FLASH_BASE_OFFSET
#define CFMC_FEATURE_SYSTEM_FLASH_OFFSET_MASK         STARTUP_SYSTEM_FLASH_OFFSET_MASK
#define CFMC_FEATURE_PAGE_SIZE                        STARTUP_PAGE_SIZE
#define CFMC_FEATURE_SELF_PROGRAM_ERASE               0
#define CFMC_FEATURE_WRITE_IMPL_BY_SELF_WRITE         0
#define CFMC_FEATURE_PASSWD_LOCK                      1
#define CFMC_FEATURE_CRC                              0
#define CFMC_FEATURE_IRQ_SERVICE                      0 /* Only Write done interrupt is supported but nobody uses this feature in NO-OS environment */
#define CFMC_FEATURE_RUMTIME_READ_PROTECTION          0
#define CFMC_FEATURE_ICACHE                           1

#define CFMC_FEATURE_BANK_SWITCH                      0
#if defined (CFMC_CFGR_BBLOCK_Pos)
#define CFMC_FEATURE_BBLOCK                           1
#else
#define CFMC_FEATURE_BBLOCK                           0
#endif
#define CFMC_FEATURE_BBLOCK_IMPL_BY_WRITE_PROT        0
#define CFMC_FEATURE_IDCACHE                          1

#define DFMC_FEATURE_WRITE_BYTE                       0

/* Interanl Macro */
#define CFMC_REG_BASE                                 CFMC_BASE

/* Flash P/E Mode commands */
#define CFMC_PE_MODE_CMD1                             0x01234567
#define CFMC_PE_MODE_CMD2                             0x12345678
#define CFMC_PE_MODE_CMD3                             0x23456789
#define CFMC_SYSFLASH_PE_MODE_CMD1                    0x3456789A
#define CFMC_SYSFLASH_PE_MODE_CMD2                    0x456789AB
#define CFMC_SYSFLASH_PE_MODE_CMD3                    0x56789ABC

/* Status check count */
#define CFMC_PE_STATUS_CHECK_COUNT                    0x35000
#define CFMC_STATUS_CHECK_COUNT                       20
#define CFMC_STATUS_ERROR_Mask                        0x007F0000

/* Write Protection Mask */
#define CFMC_WPROT_WPROT_Mask                         0x0000FFFF
#define CFMC_WPROT_WPROT_BIT_Pos                      0
#define CFMC_WPROT_LAST_BLK_Mask                      0x00008000
#define CFMC_WPROT_LAST_4KBLK_Mask                    0xFF000000

/* Read protection command */
#define CFMC_RD_PROTECT_LEVEL1_CMD                    0x39
#define CFMC_RD_PROTECT_LEVEL2_CMD                    0x07
#define CFMC_RD_PROTECT_PASSWD_CMD                    0x80

/* CRC property */
/* Address should be aligned to 512B */
#define CFMC_CRC_ADDR_ALIGNMENT                       0xFF
#define DFMC_CRC_ADDR_ALIGNMENT                       0x3F

/* Define internal variant features */
#if defined (CFMC_CTRL_S1KERS_Pos)
#define CFMC_VARIANT_FEATURE_1KB_SECTOR               1
#else
#define CFMC_VARIANT_FEATURE_1KB_SECTOR               0
#endif

#if defined (CFMC_CTRL_SERS_Pos)
#define CFMC_VARIANT_FEATURE_2KB_SECTOR               1
#else
#define CFMC_VARIANT_FEATURE_2KB_SECTOR               0
#endif

#if defined (CFMC_CTRL_S4KERS_Pos)
#define CFMC_VARIANT_FEATURE_4KB_SECTOR               1
#else
#define CFMC_VARIANT_FEATURE_4KB_SECTOR               0
#endif

#if defined (CFMC_CTRL_BURSTMD_Pos)
#define CFMC_VARIANT_FEATURE_BURST_PGM                1
#else
#define CFMC_VARIANT_FEATURE_BURST_PGM                0
#endif

#if defined (CFMC_CONF_BBLOCK_Pos)
#define CFMC_VARIANT_FEATURE_BBLOCK                   1
#else
#define CFMC_VARIANT_FEATURE_BBLOCK                   0
#endif

#if defined (CFMC_CONF_WRITE_Pos)
#define CFMC_VARIANT_FEATURE_REGISTER_UPDATE          1
#else
#define CFMC_VARIANT_FEATURE_REGISTER_UPDATE          0
#endif

/* Bit/Register Macro */
#if (CFMC_VARIANT_FEATURE_BBLOCK)
#define SET_CFMC_CFGR_BBLOCK(Peri,Data)               SET_BIT(Peri,Data,CFMC,CONF,BBLOCK)
#endif

#if (CFMC_VARIANT_FEATURE_REGISTER_UPDATE)
#define SET_CFMC_CFGR_REGISTER_UPDATE(Peri,Data)      SET_BIT(Peri,Data,CFMC,CONF,WRITE)
#endif
#if (CFMC_VARIANT_FEATURE_BBLOCK)
#define SET_CFMC_CFGR_WPROT_BBLK(Peri,Data)           SET_BIT(Peri,Data,CFMC,CONF,BBLOCK)
#endif
#define SET_CFMC_CFGR_LATENCY(Peri,Data)              SET_BIT(Peri,Data,CFMC,CONF,LATENCY)
#define SET_CFMC_CFGR(Peri,Data)                      SET_REG(Peri,Data,CONF)

#define SET_CFMC_CR_FLASH_LOCK(Peri,Data)             (Peri->CTRL = (Data > 0)? ((Peri->CTRL & ~CFMC_CTRL_FLOCK_Msk) \
                                                      | 0x80000000) : (Peri->CTRL & ~CFMC_CTRL_FLOCK_Msk))
#define SET_CFMC_CR_INFOFLASH_LOCK(Peri,Data)          SET_BIT(Peri,Data,CFMC,CTRL,INFOLOCK)

#if (CFMC_VARIANT_FEATURE_BURST_PGM == 1)
#define SET_CFMC_CR_BURST_PGM(Peri,Data)              SET_BIT(Peri,Data,CFMC,CTRL,BURSTMD)
#endif

#define SET_CFMC_CR_WR_DONE_IRQ_EN(Peri,Data)         SET_BIT(Peri,Data,CFMC,CTRL,WDIEN)
#define SET_CFMC_CR_ERS_512B(Peri,Data)               SET_BIT(Peri,Data,CFMC,CTRL,PERS)

#if (CFMC_VARIANT_FEATURE_1KB_SECTOR == 1)
#define SET_CFMC_CR_ERS_1KB(Peri,Data)                SET_BIT(Peri,Data,CFMC,CTRL,S1KERS)
#endif

#if (CFMC_VARIANT_FEATURE_2KB_SECTOR == 1)
#define SET_CFMC_CR_ERS_2KB(Peri,Data)                SET_BIT(Peri,Data,CFMC,CTRL,SERS)
#endif

#if (CFMC_VARIANT_FEATURE_4KB_SECTOR == 1)
#define SET_CFMC_CR_ERS_4KB(Peri,Data)                SET_BIT(Peri,Data,CFMC,CTRL,S4KERS)
#endif

#define SET_CFMC_CR_ERS_CHIP(Peri,Data)               SET_BIT(Peri,Data,CFMC,CTRL,CERS)
#define SET_CFMC_CR_PGM(Peri,Data)                    SET_BIT(Peri,Data,CFMC,CTRL,PGM)
#define GET_CFMC_CR(Peri)                             GET_REG(Peri,CTRL)
#define SET_CFMC_CR(Peri,Data)                        SET_REG(Peri,Data,CTRL)
#define CLEAR_CFMC_CR(Peri)                           SET_REG(Peri,0,CTRL)

#define SET_CFMC_FLSKEYR(Peri,Data)                   SET_REG(Peri,Data,FLSKEY)
#define SET_CFMC_INFOKEYR(Peri,Data)                  SET_REG(Peri,Data,INFOKEY)

#define GET_CFMC_STR_CRCDONE(Peri)                    GET_BIT(Peri,CFMC,STAT,CDONE)
#define GET_CFMC_STR_WRDONE(Peri)                     GET_BIT(Peri,CFMC,STAT,WDONE)
#define GET_CFMC_STR_WRBUSY(Peri)                     GET_BIT(Peri,CFMC,STAT,WBUSY)
#define SET_CFMC_STR(Peri,Data)                       SET_REG(Peri,Data,STAT)
#define GET_CFMC_STR(Peri)                            GET_REG(Peri,STAT)
#define CLEAR_CFMC_STR(Peri)                          SET_REG(Peri,0xFFFFFFFC,STAT)

/* Pseudo STR by READPROT register */
#define GET_CFMC_STR_PWMATCH(Peri)                    GET_BIT(Peri,CFMC,READPROT,PWMATCH)
#define GET_CFMC_STR_ERS_CHIP(Peri)                   GET_BIT(Peri,CFMC,READPROT,CERSD)
#define GET_CFMC_STR_RPROT_LVL2_DBG(Peri)             GET_BIT(Peri,CFMC,READPROT,LVL2_STS)
#define GET_CFMC_STR_RPROT_LVL1_DBG(Peri)             GET_BIT(Peri,CFMC,READPROT,LVL1_STS)
#define GET_CFMC_STR_RPROT_LVL2(Peri)                 GET_BIT(Peri,CFMC,READPROT,LVL2_EN)
#define GET_CFMC_STR_RPROT_LVL1(Peri)                 GET_BIT(Peri,CFMC,READPROT,LVL1_EN)
#define GET_CFMC_STR_DBG_CONNECTION(Peri)             GET_BIT(Peri,CFMC,READPROT,DBGMOD)

#define SET_CFMC_RPR_RPROT(Peri,Data)                 SET_BIT(Peri,Data,CFMC,READPROT,RPROT)
#define GET_CFMC_RPR(Peri)                            GET_REG(Peri,READPROT)

#define SET_CFMC_PASSWD_REGISTER(Peri,Data)           SET_REG(Peri,Data,PWPRST)
#define SET_CFMC_PASSWD_MATCH(Peri,Data)              SET_REG(Peri,Data,PWIN)

#define SET_CFMC_WPR_WPROT(Peri,Data)                 SET_REG(Peri,Data,FLSPROT)
#define GET_CFMC_WPR_WPROT(Peri)                      GET_REG(Peri,FLSPROT)

/* CRC */
#define SET_CFMC_CFGR_ICACHE_RESET(Peri,Data)         (void)Peri
#define SET_CFMC_CFGR_ICACHE_EN(Peri,Data)            (void)Peri
#define GET_CFMC_STR_CRCBUSY(Peri)                    (void)Peri
#define SET_CFMC_CRC_START_ADDR(Peri,Data)            (void)Peri
#define SET_CFMC_CRC_END_ADDR(Peri,Data)              (void)Peri
#define GET_CFMC_CRC_RESULT(Peri)                     (void)Peri
#define SET_CFMC_CRC_CR_BACKGROUND_MODE(Peri,Data)    (void)Peri
#define SET_CFMC_CRC_CR_BURST_MODE(Peri,Data)         (void)Peri
#define SET_CFMC_CRC_CR_IRQ_EN(Peri,Data)             (void)Peri
#define SET_CFMC_CRC_CR_RESET_CRC_DATA(Peri,Data)     (void)Peri

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_CFMC_PROT_RESET(Peri,Data)            SET_BIT(Peri,Data,SCU,PRER1,CFMC)

/* Inline functions */
static __inline IRQn_Type CFMC_GetIRQNumber(void);
static __inline uint32_t CFMC_GetEvent(void);
static __inline void CFMC_SetConfig(CFMC_CONFIG_t tConfig);
static __inline void CFMC_SetCache(bool bRequestEnable);
static __inline void CFMC_SetWriteProtect(uint32_t un32TargetBlk, bool bRequestLock);
static __inline void CFMC_SetWriteProtectBootBlk(bool bRequestLock);
static __inline HAL_ERR_e CFMC_SetReadProtect(CFMC_RD_PROTECT_CONFIG_t tRdProtectConfig);
static __inline HAL_ERR_e CFMC_SetMatchedPassword(uint32_t un32Password);
static __inline HAL_ERR_e CFMC_Erase(volatile uint32_t un32PageAddr, CFMC_ERASE_MODE_e eEraseMode, bool bIsSystemFlash);
static __inline HAL_ERR_e CFMC_Write(volatile uint32_t un32FlashAddr, uint32_t *pun32Data, uint32_t un32Len, bool bIsWordWrite, bool bIsSystemFlash);
static __inline HAL_ERR_e CFMC_GetCRC(CFMC_CRC_MODE_e eCrcMode, uint32_t un32FlashAddr, uint32_t un32Len, uint32_t *pun32ResultCRC);

RAMFUNC static __inline IRQn_Type CFMC_GetIRQNumber(void)
{
    return (IRQn_Type)(CFMC_IRQn);
}

RAMFUNC static __inline uint32_t CFMC_GetEvent(void)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    uint32_t un32Event;

    un32Event = GET_CFMC_STR(ptRegBase);
    CLEAR_CFMC_STR(ptRegBase);

    return un32Event;
}

RAMFUNC static __inline void CFMC_SetConfig(CFMC_CONFIG_t tConfig)
{
    /* Operation time-out is not supported */
    /* CRC is not supported */
    /* Set up bus-latency only */

    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;

#if (CFMC_VARIANT_FEATURE_REGISTER_UPDATE == 1)
    SET_CFMC_CFGR_REGISTER_UPDATE(ptRegBase, true);
#endif

    SET_CFMC_CFGR_LATENCY(ptRegBase, tConfig.un8Latency);
    CLEAR_CFMC_STR(ptRegBase);

    return;
}

RAMFUNC static __inline void CFMC_SetCache(bool bRequestEnable)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;

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

    return;
}

RAMFUNC static __inline void CFMC_SetWriteProtect(uint32_t un32TargetBlk, bool bRequestLock)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    uint32_t un32Reg;

    un32Reg = GET_CFMC_WPR_WPROT(ptRegBase);

    if (!bRequestLock)
    {
        /* Update Lower Write Protect */
        if (un32TargetBlk == 0xFFFFFFFF)
        {
            un32Reg &= ~CFMC_WPROT_WPROT_Mask;
        }
        else
        {
            un32Reg &= ~un32TargetBlk;
        }

        /* Update Higher Write Protect (4KB) */
        if (un32TargetBlk & CFMC_WPROT_LAST_BLK_Mask)
        {
            un32Reg |= CFMC_WPROT_LAST_4KBLK_Mask;
        }
    }
    else
    {
        /* Update Lower Write Protect */
        if (un32TargetBlk == 0xFFFFFFFF)
        {
            un32Reg |= CFMC_WPROT_WPROT_Mask;
        }
        else
        {
            un32Reg |= un32TargetBlk;
        }

        /* Update Higher Write Protect (4KB) */
        if (un32TargetBlk & CFMC_WPROT_LAST_BLK_Mask)
        {
            un32Reg &= ~CFMC_WPROT_LAST_4KBLK_Mask;
        }
    }
    SET_CFMC_WPR_WPROT(ptRegBase, un32Reg);

    return;
}

RAMFUNC static __inline void CFMC_SetWriteProtectBootBlk(bool bRequestLock)
{
#if (CFMC_VARIANT_FEATURE_BBLOCK == 1)

    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;

    SET_CFMC_CFGR_WPROT_BBLK(ptRegBase, bRequestLock);
#endif

    return;
}

RAMFUNC static __inline HAL_ERR_e CFMC_SetReadProtect(CFMC_RD_PROTECT_CONFIG_t tRdProtectConfig)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    uint16_t un16RdProtectCMD;
    uint32_t un32Status;
    uint8_t un8Cnt = 0;

    if (GET_CFMC_STR_DBG_CONNECTION(ptRegBase))
    {
        __asm volatile ("cpsid i");
    }

    if (tRdProtectConfig.eRdProtectLevel >= CFMC_RD_PROTECT_PASSWD)
    {
        SET_CFMC_PASSWD_REGISTER(ptRegBase, tRdProtectConfig.un32RegisteredPasswd);
        SET_CFMC_PASSWD_REGISTER(ptRegBase, tRdProtectConfig.un32RegisteredPasswd);
    }

    switch (tRdProtectConfig.eRdProtectLevel)
    {
        case CFMC_RD_PROTECT_LEVEL1:
            un16RdProtectCMD = CFMC_RD_PROTECT_LEVEL1_CMD;
            un32Status = BIT_NAME_MSK(CFMC_,READPROT_,LVL1_EN_);
            break;

        case CFMC_RD_PROTECT_LEVEL2:
            un16RdProtectCMD = CFMC_RD_PROTECT_LEVEL2_CMD;
            un32Status = BIT_NAME_MSK(CFMC_,READPROT_,LVL2_EN_);
            break;

        case CFMC_RD_PROTECT_LEVEL1_PASSWD:
            un16RdProtectCMD = CFMC_RD_PROTECT_LEVEL1_CMD | CFMC_RD_PROTECT_PASSWD_CMD;
            un32Status = BIT_NAME_MSK(CFMC_,READPROT_,LVL1_EN_);
            break;

        case CFMC_RD_PROTECT_LEVEL2_PASSWD:
            un16RdProtectCMD = CFMC_RD_PROTECT_LEVEL2_CMD | CFMC_RD_PROTECT_PASSWD_CMD;
            un32Status = BIT_NAME_MSK(CFMC_,READPROT_,LVL2_EN_);
            break;

        default:
            if (GET_CFMC_STR_DBG_CONNECTION(ptRegBase))
            {
                __asm volatile ("cpsie i");
            }
            return HAL_ERR_PARAMETER;
    }

    SET_CFMC_RPR_RPROT(ptRegBase, un16RdProtectCMD);
    do
    {
        __NOP();__NOP();__NOP();__NOP();__NOP();
        un8Cnt++;
        if (un8Cnt > CFMC_STATUS_CHECK_COUNT)
        {
            break;
        }
    } while(!(GET_CFMC_RPR(ptRegBase) & un32Status));

    if (un8Cnt > CFMC_STATUS_CHECK_COUNT)
    {
        return HAL_ERR_TIMEOUT;
    }
    else
    {
        return HAL_ERR_OK;
    }
}

RAMFUNC static __inline HAL_ERR_e CFMC_SetMatchedPassword(uint32_t un32Password)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;;
    uint8_t un8Cnt = 0;

    SET_CFMC_PASSWD_MATCH(ptRegBase, un32Password);
    SET_CFMC_PASSWD_MATCH(ptRegBase, un32Password);

    do
    {
        __NOP();__NOP();__NOP();__NOP();__NOP();
        un8Cnt++;
        if (un8Cnt > CFMC_STATUS_CHECK_COUNT)
        {
            break;
        }
    } while(!GET_CFMC_STR_PWMATCH(ptRegBase));

    if (GET_CFMC_STR_DBG_CONNECTION(ptRegBase))
    {
        __asm volatile ("cpsie i");
    }

    if (un8Cnt > CFMC_STATUS_CHECK_COUNT)
    {
        return HAL_ERR_TIMEOUT;
    }
    else
    {
        return HAL_ERR_OK;
    }
}

RAMFUNC static __inline HAL_ERR_e CFMC_Erase(volatile uint32_t un32PageAddr, CFMC_ERASE_MODE_e eEraseMode, bool bIsSystemFlash)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;;
    uint32_t un32State = 0xFF;
    uint8_t un8Cnt = 0;

    /* Setup PE command */
    if (bIsSystemFlash)
    {
        SET_CFMC_INFOKEYR(ptRegBase, CFMC_SYSFLASH_PE_MODE_CMD1);
        SET_CFMC_INFOKEYR(ptRegBase, CFMC_SYSFLASH_PE_MODE_CMD2);
        SET_CFMC_INFOKEYR(ptRegBase, CFMC_SYSFLASH_PE_MODE_CMD3);
    }
    else
    {
        SET_CFMC_FLSKEYR(ptRegBase, CFMC_PE_MODE_CMD1);
        SET_CFMC_FLSKEYR(ptRegBase, CFMC_PE_MODE_CMD2);
        SET_CFMC_FLSKEYR(ptRegBase, CFMC_PE_MODE_CMD3);
    }

    /* Setup Erase option */
    switch (eEraseMode)
    {
        case CFMC_PAGE_ERASE_MODE:
            SET_CFMC_CR_ERS_512B(ptRegBase, true);
            break;

#if (CFMC_VARIANT_FEATURE_1KB_SECTOR == 1)
        case CFMC_1KB_ERASE_MODE:
            SET_CFMC_CR_ERS_1KB(ptRegBase, true);
            break;
#endif

#if (CFMC_VARIANT_FEATURE_2KB_SECTOR == 1)
        case CFMC_2KB_ERASE_MODE:
            SET_CFMC_CR_ERS_2KB(ptRegBase, true);
            break;
#endif

#if (CFMC_VARIANT_FEATURE_4KB_SECTOR == 1)
        case CFMC_4KB_ERASE_MODE:
            SET_CFMC_CR_ERS_4KB(ptRegBase, true);
            break;
#endif
        case CFMC_CHIP_ERASE_MODE:
            SET_CFMC_CR_ERS_CHIP(ptRegBase, true);
            break;

        default:
            /* Re-Lock Flash */
            if (bIsSystemFlash)
            {
                SET_CFMC_CR_INFOFLASH_LOCK(ptRegBase, true);
            }
            else
            {
                SET_CFMC_CR_FLASH_LOCK(ptRegBase, true);
            }
            return HAL_ERR_PARAMETER;
    }

    /* Signaling Erase flash commands to Bus */
    un32PageAddr = un32PageAddr & ~(0x3);
    *(volatile uint32_t *)un32PageAddr = 0xFFFFFFFF;

    /* Check if Erase is done */
    do
    {
        __NOP();__NOP();__NOP();__NOP();__NOP();
        un8Cnt++;
        if (un8Cnt > CFMC_PE_STATUS_CHECK_COUNT)
        {
            break;
        }
        un32State= GET_CFMC_STR_WRBUSY(ptRegBase);
    }while (un32State);

    /* Clear Erase option */
    switch (eEraseMode)
    {
         case CFMC_PAGE_ERASE_MODE:
             SET_CFMC_CR_ERS_512B(ptRegBase, false);
             break;

#if (CFMC_VARIANT_FEATURE_1KB_SECTOR == 1)
         case CFMC_1KB_ERASE_MODE:
             SET_CFMC_CR_ERS_1KB(ptRegBase, false);
             break;
#endif

#if (CFMC_VARIANT_FEATURE_2KB_SECTOR == 1)
         case CFMC_2KB_ERASE_MODE:
             SET_CFMC_CR_ERS_2KB(ptRegBase, false);
             break;
#endif

#if (CFMC_VARIANT_FEATURE_4KB_SECTOR == 1)
         case CFMC_4KB_ERASE_MODE:
             SET_CFMC_CR_ERS_4KB(ptRegBase, false);
             break;
#endif
         case CFMC_CHIP_ERASE_MODE:
             SET_CFMC_CR_ERS_CHIP(ptRegBase, false);
             break;

         default:
             return HAL_ERR_PARAMETER;
    }

    /* Re-Lock Flash */
    if (bIsSystemFlash)
    {
        SET_CFMC_CR_INFOFLASH_LOCK(ptRegBase, true);
    }
    else
    {
        SET_CFMC_CR_FLASH_LOCK(ptRegBase, true);
    }

    if (un8Cnt > CFMC_PE_STATUS_CHECK_COUNT)
    {
        return HAL_ERR_TIMEOUT;
    }
    else
    {
        un32State = GET_CFMC_STR(ptRegBase);
        SET_CFMC_STR(ptRegBase, un32State);

        if (un32State & CFMC_STATUS_ERROR_Mask)
        {
            return HAL_ERR_INVALID_USE;
        }

        return HAL_ERR_OK;
    }
}

RAMFUNC static __inline HAL_ERR_e CFMC_Write(volatile uint32_t un32FlashAddr, uint32_t *pun32Data, uint32_t un32Len, bool bIsWordWrite, bool bIsSystemFlash)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;;
    uint32_t i;
    uint32_t un32State = 0xFF;
    uint8_t un8Cnt;

    /* word write only */
    if (!bIsWordWrite)
    {
        return HAL_ERR_NOT_SUPPORTED;
    }

    /* Select target flash */
    if (bIsSystemFlash)
    {
        SET_CFMC_INFOKEYR(ptRegBase, CFMC_SYSFLASH_PE_MODE_CMD1);
        SET_CFMC_INFOKEYR(ptRegBase, CFMC_SYSFLASH_PE_MODE_CMD2);
        SET_CFMC_INFOKEYR(ptRegBase, CFMC_SYSFLASH_PE_MODE_CMD3);
    }
    else
    {
        SET_CFMC_FLSKEYR(ptRegBase, CFMC_PE_MODE_CMD1);
        SET_CFMC_FLSKEYR(ptRegBase, CFMC_PE_MODE_CMD2);
        SET_CFMC_FLSKEYR(ptRegBase, CFMC_PE_MODE_CMD3);
    }

    /* Singaling Write Command to Bus */
    SET_CFMC_CR_PGM(ptRegBase, true);

    /* Singaling Data to Bus and latch all signals */
    un32FlashAddr = un32FlashAddr & ~(0x3);
    for (i=0; i<un32Len; i++, un32FlashAddr +=4)
    {
        *(uint32_t *)un32FlashAddr = *pun32Data++;

        /* Check if Write is done */
        un8Cnt =0;
        do
        {
            __NOP();__NOP();__NOP();__NOP();__NOP();
            un8Cnt++;
            if (un8Cnt > CFMC_PE_STATUS_CHECK_COUNT)
            {
                goto EXIT_WRITE;
            }
            un32State= GET_CFMC_STR_WRBUSY(ptRegBase);
        }while (un32State);
    }

EXIT_WRITE:
    /* Re-Lock Flash */
    if (bIsSystemFlash)
    {
        SET_CFMC_CR_INFOFLASH_LOCK(ptRegBase, true);
    }
    else
    {
        SET_CFMC_CR_FLASH_LOCK(ptRegBase, true);
    }

    SET_CFMC_CR_PGM(ptRegBase, false);

    if (un8Cnt > CFMC_PE_STATUS_CHECK_COUNT)
    {
        return HAL_ERR_TIMEOUT;
    }
    else
    {
        un32State = GET_CFMC_STR(ptRegBase);
        SET_CFMC_STR(ptRegBase, un32State);

        if (un32State & CFMC_STATUS_ERROR_Mask)
        {
            return HAL_ERR_INVALID_USE;
        }

        return HAL_ERR_OK;
    }
}

RAMFUNC static __inline HAL_ERR_e CFMC_GetCRC(CFMC_CRC_MODE_e eCrcMode, uint32_t un32FlashAddr, uint32_t un32Len, uint32_t *pun32ResultCRC)
{
#if (CFMC_FEATURE_CRC)
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;;
    uint32_t un32State = 0xFF;
    uint32_t un32AddressMask;
    uint32_t un32SizeGranularity;
    uint8_t un8Cnt = 0;

    ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    un32AddressMask = CFMC_CRC_ADDR_ALIGNMENT;
    un32SizeGranularity = CFMC_CRC_ADDR_ALIGNMENT + 1;

    if (un32FlashAddr & un32AddressMask)
    {
        return HAL_ERR_PARAMETER;
    }
    if (un32Len % un32SizeGranularity)
    {
        return HAL_ERR_PARAMETER;
    }

    SET_CFMC_CRC_START_ADDR(ptRegBase, un32FlashAddr);
    SET_CFMC_CRC_END_ADDR(ptRegBase, (un32FlashAddr + un32Len - 1));
    SET_CFMC_CRC_CR_RESET_CRC_DATA(ptRegBase, true);

    switch (eCrcMode)
    {
        case CFMC_CRC_BACKGROUND_MODE:
            SET_CFMC_CRC_CR_IRQ_EN(ptRegBase, false);
            SET_CFMC_CRC_CR_BACKGROUND_MODE(ptRegBase, true);
            break;

        case CFMC_CRC_BURST_MODE:
            SET_CFMC_CRC_CR_IRQ_EN(ptRegBase, false);
            SET_CFMC_CRC_CR_BURST_MODE(ptRegBase, true);
            break;

        case CFMC_CRC_BACKGROUND_IRQ_MODE:
            SET_CFMC_CRC_CR_IRQ_EN(ptRegBase, true);
            SET_CFMC_CRC_CR_BACKGROUND_MODE(ptRegBase, true);
            break;

        case CFMC_CRC_BURST_IRQ_MODE:
            SET_CFMC_CRC_CR_IRQ_EN(ptRegBase, true);
            SET_CFMC_CRC_CR_BURST_MODE(ptRegBase, true);
            break;

        default:
            SET_CFMC_CRC_CR_RESET_CRC_DATA(ptRegBase, false);
            return HAL_ERR_PARAMETER;
    }

    do
    {
        __NOP();__NOP();__NOP();__NOP();__NOP();
        un8Cnt++;
        if (un8Cnt > CFMC_STATUS_CHECK_COUNT)
        {
            break;
        }

        un32State = GET_CFMC_STR_CRCBUSY(ptRegBase);
    }while(un32State);

    SET_CFMC_CRC_CR_RESET_CRC_DATA(ptRegBase, false);

    if (un8Cnt > CFMC_STATUS_CHECK_COUNT)
    {
        return HAL_ERR_TIMEOUT;
    }

    un32State = GET_CFMC_CRC_RESULT(ptRegBase);
    *pun32ResultCRC = un32State;
#endif
    return HAL_ERR_OK;
}

#endif /* _HAL_CFMC_V_03_01_01_H_ */
