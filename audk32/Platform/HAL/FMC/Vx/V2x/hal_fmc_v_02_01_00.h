/**
 *******************************************************************************
 * @file        hal_fmc_v_02_01_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 02.01.00 typed FMC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_FMC_V_02_01_00_H_
#define _HAL_FMC_V_02_01_00_H_

#include "hal_fmc.h"

/* Feature(Function) Configuration Define */
#define FMC_FEATURE_FLASH_BASE_ADDR                   STARTUP_FLASH_BASE_ADDR
#define FMC_FEATURE_CODE_FLASH_BASE_OFFSET            STARTUP_CODE_FLASH_BASE_OFFSET
#define FMC_FEATURE_DATA_FLASH_BASE_OFFSET            STARTUP_DATA_FLASH_BASE_OFFSET
#define FMC_FEATURE_SYSTEM_FLASH_BASE_OFFSET          STARTUP_SYSTEM_FLASH_BASE_OFFSET
#define FMC_FEATURE_SYSTEM_FLASH_OFFSET_MASK          STARTUP_SYSTEM_FLASH_OFFSET_MASK
#define FMC_FEATURE_PAGE_SIZE                         STARTUP_PAGE_SIZE
#define FMC_FEATURE_DATA_PAGE_SIZE                    STARTUP_DATA_PAGE_SIZE

#define FMC_FEATURE_CFMC_BANK_SWITCH_CMD_OFFSET       0x0F010800

#define FMC_FEATURE_SELF_PROGRAM_ERASE                1
#define FMC_FEATURE_WRITE_IMPL_BY_SELF_WRITE          1
#define FMC_FEATURE_PASSWD_LOCK                       1
#define FMC_FEATURE_CRC                               0
#define FMC_FEATURE_IRQ_SERVICE                       0
#define FMC_FEATURE_RUMTIME_READ_PROTECTION           1

#define FMC_FEATURE_CFMC_BANK_SWITCH                  1
#define FMC_FEATURE_CFMC_BBLOCK                       1
#define FMC_FEATURE_CFMC_IDCACHE                      0

#define FMC_FEATURE_DFMC_WRITE_BYTE                   1

/* For this IP Only */
#define FMC_FEATURE_CFMC_BBLOCK_IMPL_BY_WRITE_PROT    0

/* Internal Macro */
#define CFMC_REG_BASE                                 CFMC_BASE
#define DFMC_REG_BASE                                 DFMC_BASE

/* CFMC Mode Definition */
#define FMC_PE_MODE_CMD1                              0x0000005A
#define FMC_PE_MODE_CMD2                              0x000000A5
#define FMC_TRIM_MODE_CMD1                            0x000000A5
#define FMC_TRIM_MODE_CMD2                            0x0000005A
#define FMC_AMBA_MODE_CMD1                            0x00000081
#define FMC_AMBA_MODE_CMD2                            0x00000028
#define FMC_PROTECT_MODE_CMD1                         0x00000066
#define FMC_PROTECT_MODE_CMD2                         0x00000099

/* Magic key for updating latency in CFGR */
#define FMC_CFGR_WKY_LATENCY                          0x78580000

/* Magic key for updating BBLOCK in CR */
#define CFMC_CR_WKY_BANK_A_KEY                        0xAAB
#define CFMC_CR_WKY_BANK_B_KEY                        0x55B
#define CFMC_CR_WKY_BBLOCK_KEY                        0xA0000000

/* Magic key for updating multi switch in BCR */
#define CFMC_BCR_WKY_BANK_SW_KEY                      0xAA91

/* Read protection command */
#define FMC_RD_PROTECT_LEVEL1_CMD                     0x39
#define FMC_RD_PROTECT_LEVEL2_CMD                     0x07
#define FMC_RD_PROTECT_PASSWD_CMD                     0x80

/* Bit/Register Macro */
#define SET_FMC_MR(Peri,Data)                         SET_REG(Peri,Data,MR)
#define CLEAR_FMC_MR(Peri)                            SET_REG(Peri,0,MR)

#define SET_FMC_CR_SELFPGM(Peri,Data)                 SET_BIT(Peri,Data,CFMC,CR,SELFPGM)
#define SET_CFMC_CR_SYSFLASH_EN(Peri,Data)            SET_BIT(Peri,Data,CFMC,CR,IFEN)
#define SET_CFMC_CR_WPROT_BBLK(Peri,Data)             (Peri->CR = ((Peri->CR & ~(BIT_NAME_MSK(CFMC_,CR_,BBLOCK_))) \
                                                      | (Data << BIT_NAME_POS(CFMC_,CR_,BBLOCK_)) \
                                                      | CFMC_CR_WKY_BBLOCK_KEY))
#define SET_CFMC_CR_SYS_BANKSEL(Peri,Data)            SET_BIT(Peri,Data,CFMC,CR,BSAEN)
#define SET_CFMC_CR_SYS_RDPROT(Peri,Data)             SET_BIT(Peri,Data,CFMC,CR,RPAEN)
#define SET_CFMC_CR_OTP_BANK_SWITCH(Peri,Data)        SET_BIT(Peri,Data,CFMC,CR,BSAEN)
#define SET_CFMC_CR_OTP_RDPROT(Peri,Data)             SET_BIT(Peri,Data,CFMC,CR,RPAEN)
#define SET_DFMC_CR_WORD_WRITE_MODE(Peri,Data)        SET_BIT(Peri,Data,DFMC,CR,WPGMEN)

#define SET_FMC_CR_ERS(Peri,Data)                     SET_BIT(Peri,Data,CFMC,CR,ERS)
#define SET_FMC_CR_ERS_1KB(Peri,Data)                 SET_BIT(Peri,Data,CFMC,CR,SECT1K)
#define SET_FMC_CR_ERS_4KB(Peri,Data)                 SET_BIT(Peri,Data,CFMC,CR,SECT4K)
#define SET_FMC_CR_ERS_CHIP(Peri,Data)                SET_BIT(Peri,Data,CFMC,CR,MAS)
#define SET_FMC_CR_PMODE(Peri,Data)                   SET_BIT(Peri,Data,CFMC,CR,PMODE)
#define GET_FMC_CR_PMODE(Peri)                        GET_BIT(Peri,CFMC,CR,PMODE)
#define SET_FMC_CR_LATCH_SIGNAL(Peri,Data)            SET_BIT(Peri,Data,CFMC,CR,WADCK)
#define SET_FMC_CR_PGM(Peri,Data)                     SET_BIT(Peri,Data,CFMC,CR,PGM)
#define SET_FMC_CR_HVEN(Peri,Data)                    SET_BIT(Peri,Data,CFMC,CR,HVEN)
#define GET_FMC_CR(Peri)                              GET_REG(Peri,CR)
#define SET_FMC_CR(Peri,Data)                         SET_REG(Peri,Data,CR)
#define CLEAR_FMC_CR(Peri)                            SET_REG(Peri,0,CR)

#define SET_FMC_AR(Peri,Data)                         SET_REG(Peri,Data,AR)
#define SET_FMC_DR(Peri,Data)                         SET_REG(Peri,Data,DR)

#define GET_FMC_STR_WRBUSY(Peri)                      GET_BIT(Peri,CFMC,BUSY,WRBUSY)
#define SET_FMC_STR(Peri,Data)                        SET_REG(Peri,Data,BUSY)

/* Pseudo STR by READPROT register */
#define GET_CFMC_STR_DBG_CONNECTION(Peri)             GET_BIT(Peri,CFMC,RPROT,DBGMOD)

#define SET_FMC_CFGR(Peri,Data)                       SET_REG(Peri,Data,CFG)

#define SET_CFMC_BANK_A_PROT(Peri,Data)               (Peri->ABWPROT = ((uint32_t)CFMC_CR_WKY_BANK_A_KEY << BIT_NAME_POS(CFMC_,ABWPROT_,AB_KEY_)) \
                                                      | (Data << BIT_NAME_POS(CFMC_,ABWPROT_,AB_WPROT_)))
#define GET_CFMC_BANK_A_PROT(Peri)                    GET_BIT(Peri,CFMC,ABWPROT,AB_WPROT)


#define SET_CFMC_BANK_B_PROT(Peri,Data)               (Peri->NBWPROT = ((uint32_t)CFMC_CR_WKY_BANK_B_KEY << BIT_NAME_POS(CFMC_,NBWPROT_,NB_KEY_)) \
                                                      | (Data << BIT_NAME_POS(CFMC_,NBWPROT_,NB_WPROT_)))
#define GET_CFMC_BANK_B_PROT(Peri)                    GET_BIT(Peri,CFMC,NBWPROT,NB_WPROT)

#define SET_CFMC_WPR_WPROT(Peri,Data)                 SET_BIT(Peri,Data,CFMC,WPROT,WPROT)
#define GET_CFMC_WPR_WPROT(Peri)                      GET_BIT(Peri,CFMC,WPROT,WPROT)
#define SET_DFMC_WPR_WPROT(Peri,Data)                 SET_BIT(Peri,Data,DFMC,WPROT,WPROT)
#define GET_DFMC_WPR_WPROT(Peri)                      GET_BIT(Peri,DFMC,WPROT,WPROT)

#define SET_FMC_RPR_RPROT(Peri,Data)                  SET_BIT(Peri,Data,CFMC,RPROT,RPROT)
#define GET_FMC_RPR(Peri)                             GET_REG(Peri,RPROT)

#define SET_FMC_PASSWD_REGISTER(Peri,Data)            SET_REG(Peri,Data,PWPRST)
#define SET_FMC_PASSWD_MATCH(Peri,Data)               SET_REG(Peri,Data,PWIN)

#define SET_CFMC_BCR_MULTI_BANK_CONF(Peri,Data)       SET_BIT_KEY(Peri, CFMC_BCR_WKY_BANK_SW_KEY, Data, CFMC, BCR, BSE)
#define SET_CFMC_BCR_BANK_SWITCH(Peri,Data)           SET_BIT_KEY(Peri, CFMC_BCR_WKY_BANK_SW_KEY, Data, CFMC, BCR, BSW)
#define GET_CFMC_BCR(Peri)                            GET_REG(Peri,BCR)
#define GET_CFMC_BSR_BANK_SWITCH_ERROR(Peri)          GET_BIT(Peri,CFMC,BSR,BSERR)
#define GET_CFMC_BSR_BANK_SWITCH_DONE(Peri)           GET_BIT(Peri,CFMC,BSR,BSWST)
#define GET_CFMC_BSR_ACTIVE_BANK(Peri)                GET_BIT(Peri,CFMC,BSR,BSST)
#define GET_CFMC_BSR_BOOT_BANK(Peri)                  GET_BIT(Peri,CFMC,BSR,CBF)
#define GET_CFMC_BSR(Peri)                            GET_REG(Peri,BSR)

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_FMC_PROT_RESET(Peri,Data)             SET_BIT(Peri,Data,SCU,PRER1,FMC)

/* Inline functions */
static __inline void FMC_SetConfig(FMC_ID_e eFmcID, FMC_CONFIG_t tConfig);
static __inline void FMC_SetWriteProtect(FMC_ID_e eFmcID, uint32_t un32BlockIdx, uint32_t un32TargetBlk, bool bRequestLock);

#if (FMC_FEATURE_CFMC_BBLOCK_IMPL_BY_WRITE_PROT)
static __inline HAL_ERR_e CFMC_SetWriteProtectBootBlk(CFMC_BANK_ID_e eBankID, uint32_t un32TargetBlk, bool bRequestLock);
#else
static __inline void CFMC_SetWriteProtectBootBlk(bool bRequestLock);
#endif
static __inline HAL_ERR_e FMC_SetReadProtect(FMC_ID_e eFmcID, FMC_RD_PROTECT_CONFIG_t tRdProtectConfig);
static __inline HAL_ERR_e FMC_SetMatchedPassword(FMC_ID_e eFmcID, uint32_t un32Password);
static __inline HAL_ERR_e FMC_Erase(FMC_ID_e eFmcID, uint32_t un32PageAddr, FMC_ERASE_MODE_e eEraseMode, bool bIsSystemFlash);
static __inline HAL_ERR_e FMC_Write(FMC_ID_e eFmcID, uint32_t un32FlashAddr, uint32_t *pun32Data, uint32_t un32Len, bool bIsWordWrite, bool bIsSystemFlash);
static __inline void FMC_SelfWriteFromRAM(FMC_ID_e eFmcID, uint32_t un32FlashAddr, uint32_t *pun32Data);
static __inline void CFMC_WriteToUserInfo(volatile uint32_t un32FlashAddr, uint32_t *pun32Data, uint32_t un32Len, PRV_CMFC_USERINFO_ID_e eUserInfoID);
static __inline void CFMC_EraseUserInfo(uint32_t un32PageAddr, FMC_ERASE_MODE_e eEraseMode, PRV_CMFC_USERINFO_ID_e eUserInfoID);
static __inline void CFMC_SetMultiBankConfig(bool bRequestMultiBank);
static __inline HAL_ERR_e CFMC_GetBankSwitchStatus(CFMC_BANK_ID_e *peBootBank, bool *pbBankSwitchDone, CFMC_BANK_ID_e *peActiveBank);
static __inline HAL_ERR_e CFMC_SetActiveBank(CFMC_BANK_ID_e eBankID);

RAMFUNC static __inline void FMC_SetConfig(FMC_ID_e eFmcID, FMC_CONFIG_t tConfig)
{
    /* Operation time-out is not supported */
    /* CRC is not supported */
    /* Set up bus-latency only */

    CFMC_Type *ptRegBase;
    uint32_t un32Reg = FMC_CFGR_WKY_LATENCY;

    if (eFmcID == FMC_ID_CFMC)
    {
        ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
        un32Reg |= (tConfig.un8Latency << BIT_NAME_POS(CFMC_,CFG_,WAIT_));
    }
    else
    {
        ptRegBase = (CFMC_Type *)DFMC_REG_BASE;
        un32Reg |= (tConfig.un8Latency << BIT_NAME_POS(DFMC_,CFG_,WAIT_));
    }

    SET_FMC_MR(ptRegBase, FMC_AMBA_MODE_CMD1);
    SET_FMC_MR(ptRegBase, FMC_AMBA_MODE_CMD2);

    SET_FMC_CFGR(ptRegBase,un32Reg);

    CLEAR_FMC_MR(ptRegBase);
    CLEAR_FMC_MR(ptRegBase);
    return;
}

RAMFUNC static __inline void FMC_SetWriteProtect(FMC_ID_e eFmcID, uint32_t un32BlockIdx, uint32_t un32TargetBlk, bool bRequestLock)
{
    CFMC_Type *ptRegBase;
    uint32_t un32Reg1;
    CONFIG_FLASH_INFO_t tFlashInfo;
    uint8_t un8BBankBIndex;

    (void)un32BlockIdx;

    if (eFmcID == FMC_ID_CFMC)
    {
        ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    }
    else
    {
        ptRegBase = (CFMC_Type *)DFMC_REG_BASE;
    }

    SET_FMC_MR(ptRegBase, FMC_PROTECT_MODE_CMD1);
    SET_FMC_MR(ptRegBase, FMC_PROTECT_MODE_CMD2);

    tFlashInfo = PRV_CHIPSET_GetFlashGeometricInfo();

    if (!bRequestLock)
    {
        if (eFmcID == FMC_ID_CFMC)
        {
            un32Reg1 = GET_CFMC_WPR_WPROT(ptRegBase);
            un8BBankBIndex = (tFlashInfo.tCflash.un32Size / tFlashInfo.tCflash.tWProtectedBlocks[0].un32WProtectedSegSize)/2;

            if (un32TargetBlk & 0x01)
            {
                SET_CFMC_BANK_A_PROT(ptRegBase, 0x0000);
            }
            if (un32TargetBlk & (1 << un8BBankBIndex))
            {
                SET_CFMC_BANK_B_PROT(ptRegBase, 0x0000);
            }
        }
        else
        {
            un32Reg1 = GET_DFMC_WPR_WPROT(ptRegBase);
        }
        un32TargetBlk = un32Reg1 & ~un32TargetBlk;
    }
    else
    {
        if (eFmcID == FMC_ID_CFMC)
        {
            un32Reg1 = GET_CFMC_WPR_WPROT(ptRegBase);
            un8BBankBIndex = (tFlashInfo.tCflash.un32Size / tFlashInfo.tCflash.tWProtectedBlocks[0].un32WProtectedSegSize)/2;

            if (un32TargetBlk & 0x01)
            {
                SET_CFMC_BANK_A_PROT(ptRegBase, 0xFFFF);
            }
            if (un32TargetBlk & (1 << un8BBankBIndex))
            {
                SET_CFMC_BANK_B_PROT(ptRegBase, 0xFFFF);
            }
        }
        else
        {
            un32Reg1 = GET_DFMC_WPR_WPROT(ptRegBase);
        }
        un32TargetBlk = un32Reg1 | un32TargetBlk;
    }

    if (eFmcID == FMC_ID_CFMC)
    {
        SET_CFMC_WPR_WPROT(ptRegBase, un32TargetBlk);
    }
    else
    {
        SET_DFMC_WPR_WPROT(ptRegBase, un32TargetBlk);
    }

    CLEAR_FMC_MR(ptRegBase);
    CLEAR_FMC_MR(ptRegBase);
    return;
}

#if (FMC_FEATURE_CFMC_BBLOCK_IMPL_BY_WRITE_PROT)
RAMFUNC static __inline HAL_ERR_e CFMC_SetWriteProtectBootBlk(CFMC_BANK_ID_e eBankID, uint32_t un32TargetBlk, bool bRequestLock)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    uint32_t un32Reg1;
    uint32_t un32Reg2;
    CONFIG_FLASH_INFO_t tFlashInfo;

    SET_FMC_MR(ptRegBase, FMC_PROTECT_MODE_CMD1);
    SET_FMC_MR(ptRegBase, FMC_PROTECT_MODE_CMD2);

    tFlashInfo = PRV_CHIPSET_GetFlashGeometricInfo();

    switch(eBankID)
    {
        case CFMC_BANK_SINGLE:
        case CFMC_BANK_A:
            un32Reg1 = GET_CFMC_BANK_A_PROT(ptRegBase);
            un32Reg2 = GET_CFMC_WPR_WPROT(ptRegBase);
            if (!bRequestLock)
            {
                un32TargetBlk = un32Reg1 & ~un32TargetBlk;
                un32Reg2 = un32Reg2 & ~0x01;
            }
            else
            {
                un32TargetBlk = un32Reg1 | un32TargetBlk;
                un32Reg2 = un32Reg2 | 0x01;
            }

            SET_CFMC_BANK_A_PROT(ptRegBase, un32TargetBlk);
            SET_CFMC_WPR_WPROT(ptRegBase, un32Reg2);
            break;

        case CFMC_BANK_B:
            un32Reg1 = GET_CFMC_BANK_B_PROT(ptRegBase);
            un32Reg2 = GET_CFMC_WPR_WPROT(ptRegBase);
            if (!bRequestLock)
            {
                un32TargetBlk = un32Reg1 & ~un32TargetBlk;
                un32Reg2 = un32Reg2 & ~(1 << (tFlashInfo.tCflash.un32Size / (tFlashInfo.tCflash.tWProtectedBlocks[0].un32WProtectedSegSize *2)));
            }
            else
            {
                un32TargetBlk = un32Reg1 | un32TargetBlk;
                un32Reg2 = un32Reg2 | (1 << (tFlashInfo.tCflash.un32Size / (tFlashInfo.tCflash.tWProtectedBlocks[0].un32WProtectedSegSize *2)));
            }

            SET_CFMC_BANK_B_PROT(ptRegBase, un32TargetBlk);
            SET_CFMC_WPR_WPROT(ptRegBase, un32Reg2);
            break;

        default:
            break;
    }

    CLEAR_FMC_MR(ptRegBase);
    CLEAR_FMC_MR(ptRegBase);
    return HAL_ERR_OK;
}
#else
RAMFUNC static __inline void CFMC_SetWriteProtectBootBlk(bool bRequestLock)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;

    SET_FMC_MR(ptRegBase, FMC_PE_MODE_CMD1);
    SET_FMC_MR(ptRegBase, FMC_PE_MODE_CMD2);

    SET_CFMC_CR_WPROT_BBLK(ptRegBase, bRequestLock);

    CLEAR_FMC_MR(ptRegBase);
    CLEAR_FMC_MR(ptRegBase);

    return;
}
#endif

RAMFUNC static __inline HAL_ERR_e FMC_SetReadProtect(FMC_ID_e eFmcID, FMC_RD_PROTECT_CONFIG_t tRdProtectConfig)
{
    CFMC_Type *ptRegBase;
    uint16_t un16RdProtectCMD;
    uint32_t un32StatusMask;
    uint32_t un32Status;

    if (eFmcID == FMC_ID_CFMC)
    {
        ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    }
    else
    {
        ptRegBase = (CFMC_Type *)DFMC_REG_BASE;
        if (tRdProtectConfig.eRdProtectLevel != FMC_RD_PROTECT_LEVEL1_PASSWD)
        {
            return HAL_ERR_PARAMETER;
        }
    }

    if (GET_CFMC_STR_DBG_CONNECTION(ptRegBase))
    {
        __asm volatile ("cpsid i");
    }

    if (tRdProtectConfig.eRdProtectLevel >= FMC_RD_PROTECT_PASSWD)
    {
        SET_FMC_PASSWD_REGISTER(ptRegBase, tRdProtectConfig.un32RegisteredPasswd);
        SET_FMC_PASSWD_REGISTER(ptRegBase, tRdProtectConfig.un32RegisteredPasswd);
    }

    SET_FMC_MR(ptRegBase, FMC_PROTECT_MODE_CMD1);
    SET_FMC_MR(ptRegBase, FMC_PROTECT_MODE_CMD2);

    switch (tRdProtectConfig.eRdProtectLevel)
    {
        case FMC_RD_PROTECT_LEVEL1:
            un16RdProtectCMD = FMC_RD_PROTECT_LEVEL1_CMD;
            un32StatusMask = BIT_NAME_MSK(CFMC_,RPROT_,LVL1_EN_);
            break;

        case FMC_RD_PROTECT_LEVEL2:
            un16RdProtectCMD = FMC_RD_PROTECT_LEVEL2_CMD;
            un32StatusMask = BIT_NAME_MSK(CFMC_,RPROT_,LVL2_EN_);
            break;

        case FMC_RD_PROTECT_LEVEL1_PASSWD:
            un16RdProtectCMD = FMC_RD_PROTECT_LEVEL1_CMD | FMC_RD_PROTECT_PASSWD_CMD;
            un32StatusMask = BIT_NAME_MSK(CFMC_,RPROT_,LVL1_EN_);
            break;

        case FMC_RD_PROTECT_LEVEL2_PASSWD:
            un16RdProtectCMD = FMC_RD_PROTECT_LEVEL2_CMD | FMC_RD_PROTECT_PASSWD_CMD;
            un32StatusMask = BIT_NAME_MSK(CFMC_,RPROT_,LVL2_EN_);
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
        un32Status = GET_FMC_RPR(ptRegBase);
    } while(!(un32Status & un32StatusMask));

    CLEAR_FMC_MR(ptRegBase);
    CLEAR_FMC_MR(ptRegBase);

    return HAL_ERR_OK;
}

RAMFUNC static __inline HAL_ERR_e FMC_SetMatchedPassword(FMC_ID_e eFmcID, uint32_t un32Password)
{
    CFMC_Type *ptRegBase;
    uint32_t un32Status;

    if (eFmcID == FMC_ID_CFMC)
    {
        ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    }
    else
    {
        ptRegBase = (CFMC_Type *)DFMC_REG_BASE;
    }

    SET_FMC_PASSWD_MATCH(ptRegBase, un32Password);
    SET_FMC_PASSWD_MATCH(ptRegBase, un32Password);

    do
    {
        un32Status = GET_FMC_RPR(ptRegBase);
    } while(!(un32Status & BIT_NAME_MSK(CFMC_,RPROT_,PWMATCH_)));

    if (GET_CFMC_STR_DBG_CONNECTION(ptRegBase))
    {
        __asm volatile ("cpsie i");
    }

    return HAL_ERR_OK;
}

RAMFUNC static __inline HAL_ERR_e FMC_Erase (FMC_ID_e eFmcID, uint32_t un32PageAddr, FMC_ERASE_MODE_e eEraseMode, bool bIsSystemFlash)
{
    CFMC_Type *ptRegBase;
    uint32_t un32State=0xFF;

    if (eFmcID == FMC_ID_CFMC)
    {
        ptRegBase = (CFMC_Type *)CFMC_REG_BASE;

        un32PageAddr |= (FMC_FEATURE_FLASH_BASE_ADDR | FMC_FEATURE_CODE_FLASH_BASE_OFFSET);

        /* Make up word address */
        un32PageAddr = un32PageAddr >> 2;
    }
    else
    {
        ptRegBase = (CFMC_Type *)DFMC_REG_BASE;
        un32PageAddr |= (FMC_FEATURE_FLASH_BASE_ADDR | FMC_FEATURE_DATA_FLASH_BASE_OFFSET);

        /* Make up byte-address to be aligned to word size */
        un32PageAddr = un32PageAddr & ~(0x3);
    }

    SET_FMC_MR(ptRegBase, FMC_PE_MODE_CMD1);
    SET_FMC_MR(ptRegBase, FMC_PE_MODE_CMD2);

    /* Signaling Address to Bus */
    SET_FMC_AR(ptRegBase, un32PageAddr);

    __asm volatile ("cpsid i");
    SET_FMC_CR_PMODE(ptRegBase, true);

    /* Select target flash */
    if (bIsSystemFlash)
    {
        SET_CFMC_CR_SYSFLASH_EN(ptRegBase, true);
    }

    /* Setup Erase option */
    switch (eEraseMode)
    {
        case FMC_1KB_ERASE_MODE:
            SET_FMC_CR_ERS_1KB(ptRegBase, true);
            break;

        case FMC_4KB_ERASE_MODE:
            SET_FMC_CR_ERS_4KB(ptRegBase, true);
            break;

        case FMC_CHIP_ERASE_MODE:
            SET_FMC_CR_ERS_CHIP(ptRegBase, true);
            break;

        default: /* FMC_PAGE_ERASE_MODE */
            break;
    }

    /* Signaling Erase to Bus */
    SET_FMC_CR_ERS(ptRegBase, true);

    /* Latch signals */
    SET_FMC_CR_LATCH_SIGNAL(ptRegBase, true);

    /* Enable high voltage */
    SET_FMC_CR_HVEN(ptRegBase, true);

    /* Check if Erase is done : Do not add any instruction here!!! */
    do
    {
        un32State= GET_FMC_STR_WRBUSY(ptRegBase);
    }while (un32State);

    /* Disable high voltage */
    SET_FMC_CR_HVEN(ptRegBase, false);

    /* 0x80 is shown up atfer P/E is done */
    SET_FMC_STR(ptRegBase, 0x80);

    /* De-select target flash */
    if (bIsSystemFlash)
    {
        SET_CFMC_CR_SYSFLASH_EN(ptRegBase, false);
    }

    /* Come back to Read mode */
    CLEAR_FMC_CR(ptRegBase);
    __asm volatile ("cpsie i");

    CLEAR_FMC_MR(ptRegBase);
    CLEAR_FMC_MR(ptRegBase);

    return HAL_ERR_OK;
}

RAMFUNC static __inline HAL_ERR_e FMC_Write(FMC_ID_e eFmcID, uint32_t un32FlashAddr, uint32_t *pun32Data, uint32_t un32Len, bool bIsWordWrite, bool bIsSystemFlash)
{
    CFMC_Type *ptRegBase;
    uint32_t i;
    uint32_t un32State=0xFF;
    uint8_t *pun8ByteData = (uint8_t *)pun32Data;

    if (eFmcID == FMC_ID_CFMC)
    {
        ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
        bIsWordWrite = true;

        un32FlashAddr |= (FMC_FEATURE_FLASH_BASE_ADDR | FMC_FEATURE_CODE_FLASH_BASE_OFFSET);

        /* Make up word address */
        un32FlashAddr = un32FlashAddr >> 2;
    }
    else
    {
        ptRegBase = (CFMC_Type *)DFMC_REG_BASE;
        un32FlashAddr |= (FMC_FEATURE_FLASH_BASE_ADDR | FMC_FEATURE_DATA_FLASH_BASE_OFFSET);

        /* Make up byte-address to be aligned to word size */
        un32FlashAddr = un32FlashAddr & ~(0x3);
    }

    SET_FMC_MR(ptRegBase, FMC_PE_MODE_CMD1);
    SET_FMC_MR(ptRegBase, FMC_PE_MODE_CMD2);

    /* Signaling address to Bus */
    SET_FMC_AR(ptRegBase, un32FlashAddr);

    __asm volatile ("cpsid i");
    SET_FMC_CR_PMODE(ptRegBase, true);

    /* Select target flash */
    if (bIsSystemFlash)
    {
        SET_CFMC_CR_SYSFLASH_EN(ptRegBase, true);
    }

    /* Setup Write mode (Word or Byte) */
    if (eFmcID == FMC_ID_DFMC)
    {
        SET_DFMC_CR_WORD_WRITE_MODE(ptRegBase, bIsWordWrite);
    }

    /* Singaling Write Command to Bus */
    SET_FMC_CR_PGM(ptRegBase, true);

    /* Singaling Data to Bus and latch all signals */
    for (i=0; i<un32Len; i++)
    {
        if (bIsWordWrite)
        {
            SET_FMC_DR(ptRegBase, *pun32Data++);
        }
        else
        {
            SET_FMC_DR(ptRegBase, *pun8ByteData++);
        }

        SET_FMC_CR_LATCH_SIGNAL(ptRegBase, true);

        /* Enable high voltage */
        SET_FMC_CR_HVEN(ptRegBase, true);

        /* Check if Write is done : Do not add any instruction here!!! */
        do
        {
            un32State= GET_FMC_STR_WRBUSY(ptRegBase);
        }while (un32State);

        /* Disable high voltage */
        SET_FMC_CR_HVEN(ptRegBase, false);

        /* 0x80 is shown up atfer P/E is done */
        SET_FMC_STR(ptRegBase, 0x80);
    }

    /* De-select target flash */
    if (bIsSystemFlash)
    {
        SET_CFMC_CR_SYSFLASH_EN(ptRegBase, false);
    }

    /* Come back to Read mode */
    CLEAR_FMC_CR(ptRegBase);
    __asm volatile ("cpsie i");

    CLEAR_FMC_MR(ptRegBase);
    CLEAR_FMC_MR(ptRegBase);

    return HAL_ERR_OK;
}

RAMFUNC static __inline void FMC_SelfWriteFromRAM(FMC_ID_e eFmcID, uint32_t un32FlashAddr, uint32_t *pun32Data)
{
    CFMC_Type *ptRegBase;

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

    SET_FMC_MR(ptRegBase, FMC_PE_MODE_CMD1);
    SET_FMC_MR(ptRegBase, FMC_PE_MODE_CMD2);

    /* Signalng Self Programing to Bus */
    SET_FMC_CR_SELFPGM(ptRegBase, true);

    /* Signalng Write to Bus */
    __asm volatile ("cpsid i");
    SET_FMC_CR_PGM(ptRegBase,true);
    __NOP();__NOP();__NOP();__NOP();__NOP();

    /* Signaling Address and Data to Bus */
    *(uint32_t *)un32FlashAddr = *pun32Data;
    __NOP();__NOP();__NOP();__NOP();__NOP();

    /* Come back to Read mode */
    CLEAR_FMC_CR(ptRegBase);
    __NOP();__NOP();__NOP();__NOP();__NOP();
    __asm volatile ("cpsie i");

    CLEAR_FMC_MR(ptRegBase);
    CLEAR_FMC_MR(ptRegBase);

    return;
}

static __inline HAL_ERR_e FMC_SelfErase(FMC_ID_e eFmcID, uint32_t un32PageAddr)
{
    CFMC_Type *ptRegBase;

    if (eFmcID == FMC_ID_CFMC)
    {
        ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
        un32PageAddr |= (FMC_FEATURE_FLASH_BASE_ADDR | FMC_FEATURE_CODE_FLASH_BASE_OFFSET);
    }
    else
    {
        ptRegBase = (CFMC_Type *)DFMC_REG_BASE;
        un32PageAddr |= (FMC_FEATURE_FLASH_BASE_ADDR | FMC_FEATURE_DATA_FLASH_BASE_OFFSET);
    }

    SET_FMC_MR(ptRegBase, FMC_PE_MODE_CMD1);
    SET_FMC_MR(ptRegBase, FMC_PE_MODE_CMD2);

    /* Signalng Self Programing to Bus */
    SET_FMC_CR_SELFPGM(ptRegBase, true);

    /* Signaling Erase to Bus */
    SET_FMC_CR_ERS(ptRegBase, true);

    __NOP();__NOP();__NOP();__NOP();__NOP();

    /* Signaling Address and Data to Bus */
    *(uint32_t *)un32PageAddr = 0xFFFFFFFF;
    __NOP();__NOP();__NOP();__NOP();__NOP();

    /* Come back to Read mode */
    CLEAR_FMC_CR(ptRegBase);
    __NOP();__NOP();__NOP();__NOP();__NOP();

    CLEAR_FMC_MR(ptRegBase);
    CLEAR_FMC_MR(ptRegBase);

    return HAL_ERR_OK;
}

static __inline HAL_ERR_e FMC_SelfWrite(FMC_ID_e eFmcID, uint32_t un32FlashAddr, uint32_t *pun32Data)
{
    CFMC_Type *ptRegBase;

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

    SET_FMC_MR(ptRegBase, FMC_PE_MODE_CMD1);
    SET_FMC_MR(ptRegBase, FMC_PE_MODE_CMD2);

    /* Signalng Self Programing to Bus */
    SET_FMC_CR_SELFPGM(ptRegBase, true);

    /* Signalng Write to Bus */
    __asm volatile ("cpsid i");
    SET_FMC_CR_PGM(ptRegBase,true);
    __NOP();__NOP();__NOP();__NOP();__NOP();

    /* Signaling Address and Data to Bus */
    *(uint32_t *)un32FlashAddr = *pun32Data;
    __NOP();__NOP();__NOP();__NOP();__NOP();

    /* Come back to Read mode */
    CLEAR_FMC_CR(ptRegBase);
    __NOP();__NOP();__NOP();__NOP();__NOP();
    __asm volatile ("cpsie i");

    CLEAR_FMC_MR(ptRegBase);
    CLEAR_FMC_MR(ptRegBase);

    return HAL_ERR_OK;
}

RAMFUNC static __inline void CFMC_WriteToUserInfo(volatile uint32_t un32FlashAddr, uint32_t *pun32Data, uint32_t un32Len, PRV_CMFC_USERINFO_ID_e eUserInfoID)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    uint32_t i;
    uint32_t un32State=0xFF;

    un32FlashAddr |= (FMC_FEATURE_FLASH_BASE_ADDR | FMC_FEATURE_CODE_FLASH_BASE_OFFSET);

    SET_FMC_MR(ptRegBase, FMC_PE_MODE_CMD1);
    SET_FMC_MR(ptRegBase, FMC_PE_MODE_CMD2);

    /* Make up word alinged address */
    un32FlashAddr = un32FlashAddr >> 2;

    /* Signaling address to Bus */
    SET_FMC_AR(ptRegBase, un32FlashAddr);

    __asm volatile ("cpsid i");
    SET_FMC_CR_PMODE(ptRegBase, true);

    /* Select target flash */
    if (eUserInfoID == PRV_CMFC_USERINFO_BANK_SWITCH_ID)
    {
        SET_CFMC_CR_OTP_BANK_SWITCH(ptRegBase, true);
    }
    else
    {
        SET_CFMC_CR_OTP_RDPROT(ptRegBase, true);
    }

    /* Singaling Write Command to Bus */
    SET_FMC_CR_PGM(ptRegBase, true);

    /* Singaling Data to Bus and latch all signals */
    for (i=0; i<un32Len; i++)
    {
        SET_FMC_DR(ptRegBase, *pun32Data++);
        SET_FMC_CR_LATCH_SIGNAL(ptRegBase, true);

        /* Enable high voltage */
        SET_FMC_CR_HVEN(ptRegBase, true);

        /* Check if Write is done : Do not add any instruction here!!! */
        do
        {
            un32State= GET_FMC_STR_WRBUSY(ptRegBase);
        }while (un32State);

        /* Disable high voltage */
        SET_FMC_CR_HVEN(ptRegBase, false);

        /* 0x80 is shown up atfer P/E is done */
        SET_FMC_STR(ptRegBase, 0x80);
    }

    /* De-select target flash */
    if (eUserInfoID == PRV_CMFC_USERINFO_BANK_SWITCH_ID)
    {
        SET_CFMC_CR_OTP_BANK_SWITCH(ptRegBase, false);
    }
    else
    {
        SET_CFMC_CR_OTP_RDPROT(ptRegBase, false);
    }

    /* Come back to Read mode */
    CLEAR_FMC_CR(ptRegBase);
    __asm volatile ("cpsie i");

    CLEAR_FMC_MR(ptRegBase);
    CLEAR_FMC_MR(ptRegBase);

    return;
}

RAMFUNC static __inline void CFMC_EraseUserInfo(uint32_t un32PageAddr, FMC_ERASE_MODE_e eEraseMode, PRV_CMFC_USERINFO_ID_e eUserInfoID)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    uint32_t un32State=0xFF;

    SET_FMC_MR(ptRegBase, FMC_PE_MODE_CMD1);
    SET_FMC_MR(ptRegBase, FMC_PE_MODE_CMD2);

    /* Signaling Address to Bus */
    SET_FMC_AR(ptRegBase, un32PageAddr);

    __asm volatile ("cpsid i");
    SET_FMC_CR_PMODE(ptRegBase, true);

    /* Select target flash */
    if (eUserInfoID == PRV_CMFC_USERINFO_BANK_SWITCH_ID)
    {
        SET_CFMC_CR_OTP_BANK_SWITCH(ptRegBase, true);
    }
    else
    {
        SET_CFMC_CR_OTP_RDPROT(ptRegBase, true);
    }

    switch (eEraseMode)
    {
        case FMC_1KB_ERASE_MODE:
            SET_FMC_CR_ERS_1KB(ptRegBase, true);
            break;

        case FMC_4KB_ERASE_MODE:
            SET_FMC_CR_ERS_4KB(ptRegBase, true);
            break;

        case FMC_CHIP_ERASE_MODE:
            /* Setup Erase option */
            SET_FMC_CR_ERS_CHIP(ptRegBase, true);
            break;

        default: /* FMC_PAGE_ERASE_MODE */
            break;
    }

    /* Signaling Erase to Bus */
    SET_FMC_CR_ERS(ptRegBase, true);

    /* Latch signals */
    SET_FMC_CR_LATCH_SIGNAL(ptRegBase, true);

    /* Enable high voltage */
    SET_FMC_CR_HVEN(ptRegBase, true);

    /* Check if Erase is done : Do not add any instruction here!!! */
    do
    {
        un32State= GET_FMC_STR_WRBUSY(ptRegBase);
    }while (un32State);

    /* Disable high voltage */
    SET_FMC_CR_HVEN(ptRegBase, false);

    /* 0x80 is shown up atfer P/E is done */
    SET_FMC_STR(ptRegBase, 0x80);

    /* De-select target flash */
    if (eUserInfoID == PRV_CMFC_USERINFO_BANK_SWITCH_ID)
    {
        SET_CFMC_CR_OTP_BANK_SWITCH(ptRegBase, false);
    }
    else
    {
        SET_CFMC_CR_OTP_RDPROT(ptRegBase, false);
    }

    /* Come back to Read mode */
    CLEAR_FMC_CR(ptRegBase);
    __asm volatile ("cpsie i");

    CLEAR_FMC_MR(ptRegBase);
    CLEAR_FMC_MR(ptRegBase);

    return;
}

RAMFUNC static __inline void CFMC_SetMultiBankConfig(bool bRequestMultiBank)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;

    SET_CFMC_BCR_MULTI_BANK_CONF(ptRegBase, bRequestMultiBank);
    return;
}

RAMFUNC static __inline HAL_ERR_e CFMC_GetBankSwitchStatus(CFMC_BANK_ID_e *peBootBank, bool *pbBankSwitchDone, CFMC_BANK_ID_e *peActiveBank)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;

    if (GET_CFMC_BSR_BANK_SWITCH_ERROR(ptRegBase))
    {
        return HAL_ERR_SPECIFIC;
    }

    /* which bank device boot from ? */
    if (GET_CFMC_BSR_BOOT_BANK(ptRegBase))
    {
       *peBootBank = CFMC_BANK_B;
    }
    else
    {
        *peBootBank = CFMC_BANK_A;
    }

    /* bank switching is done? */
    if (GET_CFMC_BSR_BANK_SWITCH_DONE(ptRegBase))
    {
        *pbBankSwitchDone = true;
    }
    else
    {
        *pbBankSwitchDone = false;
    }

    /* which bank device use as active or next boot bank */
    if (GET_CFMC_BSR_ACTIVE_BANK(ptRegBase))
    {
        *peActiveBank = CFMC_BANK_B;
    }
    else
    {
        *peActiveBank = CFMC_BANK_A;
    }

    return HAL_ERR_OK;
}

RAMFUNC static __inline HAL_ERR_e CFMC_SetActiveBank(CFMC_BANK_ID_e eBankID)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    uint8_t un8BankID = 0;
    uint32_t un32Error;

    if (eBankID == CFMC_BANK_B)
    {
        un8BankID = 1;
    }

    SET_CFMC_BCR_BANK_SWITCH(ptRegBase, un8BankID);
    un32Error = GET_CFMC_BSR_BANK_SWITCH_ERROR(ptRegBase);

    if (un32Error)
    {
        return HAL_ERR_UNKNOWN;
    }

    return HAL_ERR_OK;
}

#endif /* _HAL_FMC_V_02_01_00_H_ */
