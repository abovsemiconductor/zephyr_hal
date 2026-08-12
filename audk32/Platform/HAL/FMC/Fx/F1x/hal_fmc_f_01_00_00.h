/**
 *******************************************************************************
 * @file        hal_fmc_f_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed FMC
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_FMC_F_01_00_00_H_
#define _HAL_FMC_F_01_00_00_H_

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
#define FMC_FEATURE_SELF_PROGRAM_ERASE                0
#define FMC_FEATURE_WRITE_IMPL_BY_SELF_WRITE          0
#define FMC_FEATURE_RUMTIME_READ_PROTECTION           1
#define FMC_FEATURE_ICACHE                            0
#define FMC_FEATURE_BBLOCK                            0
#define FMC_FEATURE_PAGE_WRITE                        1


/* Internal Macro */
typedef volatile FMC_Type                             CFMC_Type;
#define CFMC_REG_BASE                                 FMC_BASE
#define DFMC_REG_BASE                                 DFMC_BASE

/* FMC Mode Definition */
#define CFMC_MR_MODE_CMD                              0x5FFFFFFF
#define DFMC_MR_MODE_CMD                              0x59999990
#define CFMC_PE_MODE_CMD1                             0x08192A3B
#define CFMC_PE_MODE_CMD2                             0x4C5D6E7F
#define DFMC_PE_MODE_CMD1                             0xA9C46E91
#define DFMC_PE_MODE_CMD2                             0x78F5B3D2
#define CFMC_AR_CHIP_ERS_CMD                          0x5F9A30D7
#define DFMC_AR_CHIP_ERS_CMD                          0x4BC27F54
#define FMC_DR_PAGE_ERS_CMD                           0xFFFFFFFF

#define FMC_MR_MODE_CMD(x)                            (x == 0 ? CFMC_MR_MODE_CMD : DFMC_MR_MODE_CMD)
#define FMC_PE_MODE_CMD1(x)                           (x == 0 ? CFMC_PE_MODE_CMD1 : DFMC_PE_MODE_CMD1)
#define FMC_PE_MODE_CMD2(x)                           (x == 0 ? CFMC_PE_MODE_CMD2 : DFMC_PE_MODE_CMD2)
#define FMC_AR_CHIP_ERS_CMD(x)                        (x == 0 ? CFMC_AR_CHIP_ERS_CMD : DFMC_AR_CHIP_ERS_CMD)

/* Magic key for updating command in CR */
#define CFMC_CR_WKY_RST_PE                            0x6C930000
#define DFMC_CR_WKY_RST_PE                            0xB69C0000
#define FMC_CR_WKY(x)                                 (x == 0 ? CFMC_CR_WKY_RST_PE : DFMC_CR_WKY_RST_PE)
#define FMC_CR_BUFF_RST_CMD(x)                        (FMC_CR_WKY(x) | 0x00000001)
#define FMC_CR_PAGE_ERS_CMD(x)                        (FMC_CR_WKY(x) | 0x00000002)
#define FMC_CR_PAGE_PGM_CMD(x)                        (FMC_CR_WKY(x) | 0x00000004)
#define FMC_CR_CHIP_ERS_CMD(x)                        (FMC_CR_WKY(x) | 0x00000008)

#define FMC_CR_CS_FLASH                               0x0000A400
#define FMC_CR_CS_SYSFLASH                            0x00003800
#define FMC_CR_CS_NO_FLASH                            0x00000000

/* Magic key for updating command in BCR */
#define CFMC_BCR_WKY_SYSFLASH_WPROT                   0xC1BE0000
#define CFMC_BCR_SYSFLASH_WPROT                       (CFMC_BCR_WKY_SYSFLASH_WPROT | 0x555)

/* Suedo registers */
#define CFMC_SEUDO_RPROTR                             0x1FFFF200UL
#define CFMC_SEUDO_WDT_CFGR                           0x1FFFF20CUL
#define CFMC_SEUDO_LVRST_CFGR                         0x1FFFF210UL
#define CFMC_SEUDO_CFGOPT_WPROTR                      0x1FFFF214UL
#define CFMC_SEUDO_WPROTR                             0x1FFFF240UL
#define CFMC_SEUDO_WPROTR2                            0x1FFFF244UL
#define DFMC_SEUDO_WPROTR                             0x1FFFF270UL

/* Magic key and commands for read protection */
#define CFMC_SEUDO_WKY_RPROTR                         0x69C8A270UL
#define CFMC_SEUDO_RD_PROTECT_LEVEL1_CMD              (CFMC_SEUDO_WKY_RPROTR | 0x02)
#define CFMC_SEUDO_RD_PROTECT_LEVEL2_CMD              (CFMC_SEUDO_WKY_RPROTR | 0x01)
#define CFMC_SEUDO_RD_PROTECT_LEVEL0_CMD              (CFMC_SEUDO_WKY_RPROTR | 0x03)

/* Define internal variant features */
#define CFMC_VARIANT_FEATURE_PAGE_SIZE                0x00000100UL
#define CFMC_VARIANT_FEATURE_PAGE_WORD_SIZE           (CFMC_VARIANT_FEATURE_PAGE_SIZE/4)
#define CFMC_VARIANT_FEATURE_PAGE_OFFSET_Msk          0xFFFFFF00UL
#define DFMC_VARIANT_FEATURE_PAGE_SIZE                0x00000020UL
#define DFMC_VARIANT_FEATURE_PAGE_WORD_SIZE           (DFMC_VARIANT_FEATURE_PAGE_SIZE/4)
#define DFMC_VARIANT_FEATURE_PAGE_OFFSET_Msk          0xFFFFFFE0UL

#define FMC_VARIANT_FEATURE_PAGE_SIZE(x)              (x == 0 ? CFMC_VARIANT_FEATURE_PAGE_SIZE : DFMC_VARIANT_FEATURE_PAGE_SIZE)
#define FMC_VARIANT_FEATURE_PAGE_WORD_SIZE(x)         (x == 0 ? CFMC_VARIANT_FEATURE_PAGE_WORD_SIZE : DFMC_VARIANT_FEATURE_PAGE_WORD_SIZE)
#define FMC_VARIANT_FEATURE_PAGE_OFFSET_Msk(x)        (x == 0 ? CFMC_VARIANT_FEATURE_PAGE_OFFSET_Msk : DFMC_VARIANT_FEATURE_PAGE_OFFSET_Msk)
#define FMC_VARIANT_FEATURE_FLASH_OFFSET(x)           (x == 0 ? FMC_FEATURE_CODE_FLASH_BASE_OFFSET : FMC_FEATURE_DATA_FLASH_BASE_OFFSET)

/* Bit/Register Macro */
#define SET_SCU_CFMC_PCER(Peri,Data)                  SET_BIT(Peri,Data,SCUCG,PPCLKEN2,FMCLKE)
#define SET_SCU_DFMC_PCER(Peri,Data)                  SET_BIT(Peri,Data,SCUCG,PPCLKEN2,DFMCLKE)

#define SET_FMC_MR(Peri,Data)                         do{\
                                                          SET_REG(Peri,FMC_MR_MODE_CMD(Data),ADR);\
                                                      }while(0)

#define SET_FMC_CR_PMODE(Peri,Data)                   do{\
                                                          SET_REG(Peri,FMC_PE_MODE_CMD1(Data),IDR1);\
                                                          SET_REG(Peri,FMC_PE_MODE_CMD2(Data),IDR2);\
                                                      }while(0)

#define SET_CFMC_CR_CHIP_ERS_PROT(Peri,Data)          do{\
                                                        if (Data) SET_REG(Peri, CFMC_BCR_SYSFLASH_WPROT, BCR);\
                                                        else SET_REG(Peri, 0,BCR);\
                                                      }while(0)


#define SET_FMC_CR_PGM(Peri,Data)                     SET_BIT(Peri,Data,FMC,CR,FMOD)
#define SET_FMC_CR(Peri,Data)                         SET_REG(Peri,Data,CR)

#define GET_FMC_DR_BUF_ADDR(Peri)                     GET_REG_ADDR(Peri,PAGEBUF)
#define SET_FMC_AR(Peri,Data)                         SET_REG(Peri,Data,ADR)

#define GET_FMC_STR_PMODE1(Peri)                      GET_REG(Peri,IDR1)
#define GET_FMC_STR_PMODE2(Peri)                      GET_REG(Peri,IDR2)
#define GET_FMC_STR_WRBUSY(Peri)                      GET_BIT(Peri,FMC,CR,FMBUSY)
#define SET_FMC_STR_ERR(Peri,Data)                    SET_BIT(Peri,Data,FMC,ERFLAG,FMOPFLAG)
#define GET_FMC_STR_ERR(Peri)                         GET_BIT(Peri,FMC,ERFLAG,FMOPFLAG)


/* External reference */

/* Inline functions */
static __inline void FMC_SetConfig(FMC_ID_e eFmcID, FMC_CONFIG_t tConfig);
static __inline void FMC_SetWriteProtect(FMC_ID_e eFmcID, uint32_t un32BlockIdx, uint32_t un32TargetBlk, bool bRequestLock);
static __inline HAL_ERR_e FMC_SetReadProtect(FMC_ID_e eFmcID, FMC_RD_PROTECT_CONFIG_t tRdProtectConfig);
static __inline HAL_ERR_e FMC_Erase(FMC_ID_e eFmcID, volatile uint32_t un32PageAddr, FMC_ERASE_MODE_e eEraseMode, bool bIsSystemFlash);
static __inline HAL_ERR_e FMC_Write(FMC_ID_e eFmcID, volatile uint32_t un32FlashAddr, uint32_t *pun32Data, uint32_t un32Len, bool bIsWordWrite, bool bIsSystemFlash);

RAMFUNC static __inline void FMC_SetConfig(FMC_ID_e eFmcID, FMC_CONFIG_t tConfig)
{
    if (eFmcID == FMC_ID_CFMC)
    {
        SET_SCU_CFMC_PCER(((SCUCG_Type*)SCUCG_BASE), true);
    }
    else
    {
        SET_SCU_DFMC_PCER(((SCUCG_Type*)SCUCG_BASE), true);
    }

    /* No configuration mechanism */
    return;
}

/* Assume : Config option area should be erased before */
RAMFUNC static __inline void FMC_SetWriteProtect(FMC_ID_e eFmcID, uint32_t un32BlockIdx, uint32_t un32TargetBlk, bool bRequestLock)
{
    uint32_t un32WProtAddr = 0;

    if (bRequestLock)
    {
        un32TargetBlk = ~un32TargetBlk;
    }

    if (eFmcID == FMC_ID_CFMC)
    {
        un32WProtAddr = (un32BlockIdx == 0 ? CFMC_SEUDO_WPROTR : CFMC_SEUDO_WPROTR2);
    }
    else
    {
        /* Data Flash Write protection area at Code Flash. */
        eFmcID = FMC_ID_CFMC;
        un32WProtAddr = DFMC_SEUDO_WPROTR;
    }

    FMC_Write(eFmcID, un32WProtAddr, &un32TargetBlk, 1, true, true);

    return;
}

/* Assume : Config option area should be erased before */
RAMFUNC static __inline HAL_ERR_e FMC_SetReadProtect(FMC_ID_e eFmcID, FMC_RD_PROTECT_CONFIG_t tRdProtectConfig)
{
    uint32_t un32ReadProtConfig;

    switch (tRdProtectConfig.eRdProtectLevel)
    {
        case FMC_RD_PROTECT_LEVEL0:
            un32ReadProtConfig = CFMC_SEUDO_RD_PROTECT_LEVEL0_CMD;
            break;

        case FMC_RD_PROTECT_LEVEL1:
            un32ReadProtConfig = CFMC_SEUDO_RD_PROTECT_LEVEL1_CMD;
            break;

        case FMC_RD_PROTECT_LEVEL2:
            un32ReadProtConfig = CFMC_SEUDO_RD_PROTECT_LEVEL2_CMD;
            break;

        default:
            return HAL_ERR_PARAMETER;
    }

    FMC_Write(eFmcID, CFMC_SEUDO_RPROTR, &un32ReadProtConfig, 1, true, true);

    return HAL_ERR_OK;
}

RAMFUNC static __inline HAL_ERR_e FMC_Erase (FMC_ID_e eFmcID, volatile uint32_t un32PageAddr, FMC_ERASE_MODE_e eEraseMode, bool bIsSystemFlash)
{
    CFMC_Type *ptRegBase;
    uint32_t *pun32PageBuf;
    uint32_t un32State=0xFF;
    uint32_t un32EraseCmd;
    uint32_t un32SelectedFlash;
    uint32_t un32PageWordSize;
    uint32_t i;

#if (CONFIG_DEBUG == 1)
    FMC_RD_PROTECT_CONFIG_t tRdProtectConfig;
#endif

    if (eFmcID == FMC_ID_CFMC)
    {
        ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    }
    else
    {
        ptRegBase = (CFMC_Type *)DFMC_REG_BASE;
    }

    pun32PageBuf = (uint32_t *)GET_FMC_DR_BUF_ADDR(ptRegBase);

    if (eEraseMode == FMC_CHIP_ERASE_MODE)
    {
        un32PageAddr = FMC_AR_CHIP_ERS_CMD(eFmcID);
        un32EraseCmd  = FMC_CR_CHIP_ERS_CMD(eFmcID);
    }
    else if (eEraseMode == FMC_PAGE_ERASE_MODE)
    {
        /* Skip just in the case of non user-info area */
        if (bIsSystemFlash)
        {
            if ((un32PageAddr >= STARTUP_NON_USER_INFO_BASE_OFFSET) && (un32PageAddr < STARTUP_NON_USER_INFO_BASE_OFFSET + STARTUP_NON_USER_INFO_SIZE))
            {
                return HAL_ERR_PARAMETER;
            }
        }

        un32PageAddr |= (STARTUP_FLASH_BASE_ADDR | FMC_VARIANT_FEATURE_FLASH_OFFSET(eFmcID));
        un32PageAddr &= FMC_VARIANT_FEATURE_PAGE_OFFSET_Msk(eFmcID);
        un32EraseCmd  = FMC_CR_PAGE_ERS_CMD(eFmcID);
    }
    else
    {
        return HAL_ERR_PARAMETER;
    }
    
    SET_FMC_STR_ERR(ptRegBase, true);

    SET_FMC_MR(ptRegBase, eFmcID);
    __asm volatile ("cpsid i");

    SET_FMC_CR_PMODE(ptRegBase, eFmcID);

    /* Reset page buffer */
    SET_FMC_CR(ptRegBase, FMC_CR_BUFF_RST_CMD(eFmcID));

    /* Setup chip erase protection */
    if (bIsSystemFlash)
    {
        un32SelectedFlash = FMC_CR_CS_SYSFLASH;
    }
    else
    {
        un32SelectedFlash = FMC_CR_CS_FLASH;
    }

    if ((eFmcID == FMC_ID_CFMC) && (eEraseMode == FMC_CHIP_ERASE_MODE))
    {
        SET_CFMC_CR_CHIP_ERS_PROT(ptRegBase, true);
    }

    /* Page buffer has to be set 0xFFFFFFFF on erase operation */
    un32PageWordSize = FMC_VARIANT_FEATURE_PAGE_WORD_SIZE(eFmcID);

    for (i = 0; i < un32PageWordSize; i++)
    {
        *pun32PageBuf++ = FMC_DR_PAGE_ERS_CMD;
    }

    SET_FMC_AR(ptRegBase, un32PageAddr);

    /* Check if flash stays in PE state still */
    if ((GET_FMC_STR_PMODE1(ptRegBase) != FMC_PE_MODE_CMD1(eFmcID)) || (GET_FMC_STR_PMODE2(ptRegBase) != FMC_PE_MODE_CMD2(eFmcID)))
    {
        goto ERS_EXIT;
    }

    /* Fire Erase Command */
    SET_FMC_CR_PGM(ptRegBase,  un32SelectedFlash | un32EraseCmd);

    /* Check PGM Result status */
    do
    {
        un32State = GET_FMC_STR_WRBUSY(ptRegBase);
        if (GET_FMC_STR_ERR(ptRegBase))
        {
            SET_FMC_STR_ERR(ptRegBase, true);
            goto ERS_EXIT;
        }
    } while(un32State);

#if (CONFIG_DEBUG == 1)
    if ((*(uint32_t *)CFMC_SEUDO_RPROTR) == 0xFFFFFFFF)
    {
        tRdProtectConfig.eRdProtectLevel = FMC_RD_PROTECT_LEVEL0;
        FMC_SetReadProtect(eFmcID, tRdProtectConfig);
    }
#endif

ERS_EXIT:
    if ((eFmcID == FMC_ID_CFMC) && (eEraseMode == FMC_CHIP_ERASE_MODE))
    {
        SET_CFMC_CR_CHIP_ERS_PROT(ptRegBase, false);
    }

    /* Come back to Read mode */
    __asm volatile ("cpsie i");

    return HAL_ERR_OK;
}

RAMFUNC static __inline HAL_ERR_e FMC_Write(FMC_ID_e eFmcID, volatile uint32_t un32FlashAddr, uint32_t *pun32Data, uint32_t un32Len, bool bIsWordWrite, bool bIsSystemFlash)
{
    CFMC_Type *ptRegBase;
    uint32_t un32PageBaseAddr;
    uint32_t *pun32PageBaseOffset;
    uint32_t un32Offset;
    uint32_t un32Size = un32Len;
    uint32_t un32WordSize = 0;
    uint32_t un32FlashLastAddr;
    uint32_t un32PageWordSize;
    uint32_t un32PageBufSize = 0;
    uint32_t *pun32PageBuf;
    uint32_t un32State=0xFF;
    uint32_t i;

    if (eFmcID == FMC_ID_CFMC)
    {
        ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    }
    else
    {
        ptRegBase = (CFMC_Type *)DFMC_REG_BASE;
    }

    pun32PageBuf = (uint32_t *)GET_FMC_DR_BUF_ADDR(ptRegBase);

    un32PageWordSize = FMC_VARIANT_FEATURE_PAGE_SIZE(eFmcID);       

    /* Skip just in the case of non user-info area */
    if (bIsSystemFlash)
    {
        if ((un32FlashAddr >= STARTUP_NON_USER_INFO_BASE_OFFSET) && (un32FlashAddr < STARTUP_NON_USER_INFO_BASE_OFFSET + STARTUP_NON_USER_INFO_SIZE))
        {
            return HAL_ERR_PARAMETER;
        }
    }

    /* word addressing */
    un32FlashAddr = un32FlashAddr & ~0x3;
    un32FlashLastAddr = un32FlashAddr + (un32Size << 2) - 1;

    do
    {
        un32PageBaseAddr = un32FlashAddr & FMC_VARIANT_FEATURE_PAGE_OFFSET_Msk(eFmcID);
        pun32PageBaseOffset = (uint32_t *)(un32PageBaseAddr | (STARTUP_FLASH_BASE_ADDR | FMC_VARIANT_FEATURE_FLASH_OFFSET(eFmcID)));
        un32Offset = (un32FlashAddr & ~(FMC_VARIANT_FEATURE_PAGE_OFFSET_Msk(eFmcID))) & ~0x3;

        SET_FMC_STR_ERR(ptRegBase, true);

        SET_FMC_MR(ptRegBase, eFmcID);

        __asm volatile ("cpsid i");

        SET_FMC_CR_PMODE(ptRegBase, eFmcID);

        /* Reset page buffer */
        SET_FMC_CR(ptRegBase, FMC_CR_BUFF_RST_CMD(eFmcID));

        /* Read back */
        for (i = 0; i < un32PageWordSize; i++)
        {
            pun32PageBuf[i] = *pun32PageBaseOffset++;
        }

        /* Write back */
        if ((un32FlashLastAddr >= un32PageBaseAddr) && (un32FlashLastAddr < un32PageBaseAddr + un32PageWordSize))
        {
            un32PageBufSize = (un32FlashLastAddr - un32FlashAddr + 1)/4;
        }
        else
        {
            un32PageBufSize = (un32PageBaseAddr + un32PageWordSize - un32FlashAddr)/4;
        }

        un32WordSize += un32PageBufSize;

        /* Only Word (4byte) write */
        if (un32WordSize == 0)
        {
            un32WordSize = 1;
        }

        for (i = 0, un32Offset /=4 ; i < un32PageBufSize; i++)
        {
            pun32PageBuf[un32Offset + i] = *pun32Data++;
        }

        SET_FMC_AR(ptRegBase, (un32FlashAddr & FMC_VARIANT_FEATURE_PAGE_OFFSET_Msk(eFmcID) | (STARTUP_FLASH_BASE_ADDR | FMC_VARIANT_FEATURE_FLASH_OFFSET(eFmcID))));

        /* Check if flash stays in PE state still */
        if ((GET_FMC_STR_PMODE1(ptRegBase) != FMC_PE_MODE_CMD1(eFmcID)) || (GET_FMC_STR_PMODE2(ptRegBase) != FMC_PE_MODE_CMD2(eFmcID)))
        {
            return HAL_ERR_HW;
        }

        /* Fire Write Command */
        if (bIsSystemFlash)
        {
            SET_FMC_CR_PGM(ptRegBase, FMC_CR_CS_SYSFLASH | FMC_CR_PAGE_PGM_CMD(eFmcID));
        }
        else
        {
            SET_FMC_CR_PGM(ptRegBase, FMC_CR_CS_FLASH | FMC_CR_PAGE_PGM_CMD(eFmcID));
        }

        /* Check PGM Result status */
        do
        {
            un32State = GET_FMC_STR_WRBUSY(ptRegBase);
            if (GET_FMC_STR_ERR(ptRegBase))
            {
                SET_FMC_STR_ERR(ptRegBase,true);

                /* Come back to Read mode */
                 __asm volatile ("cpsie i");

                return HAL_ERR_TIMEOUT;
            }
        } while(un32State);

        /* Come back to Read mode */
        __asm volatile ("cpsie i");

        un32FlashAddr = un32PageBaseAddr + FMC_VARIANT_FEATURE_PAGE_SIZE(eFmcID);
    } while(un32WordSize < un32Len);

    return HAL_ERR_OK;
}

#endif /* _HAL_CFMC_F_01_00_00_H_ */
