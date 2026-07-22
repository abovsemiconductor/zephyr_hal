/**
 *******************************************************************************
 * @file        hal_cfmc_f_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed CFMC
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_CFMC_F_01_00_00_H_
#define _HAL_CFMC_F_01_00_00_H_

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
#define CFMC_FEATURE_RUMTIME_READ_PROTECTION          1
#define CFMC_FEATURE_ICACHE                           0
#define CFMC_FEATURE_BBLOCK                           0
#define CFMC_FEATURE_PAGE_WRITE                       1


/* Internal Macro */
typedef volatile FMC_Type                             CFMC_Type;
#define CFMC_REG_BASE                                 FMC_BASE

/* CFMC Mode Definition */
#define CFMC_MR_MODE_CMD                              0x5FFFFFFF
#define CFMC_PE_MODE_CMD1                             0x08192A3B
#define CFMC_PE_MODE_CMD2                             0x4C5D6E7F
#define CFMC_AR_CHIP_ERS_CMD                          0x5F9A30D7
#define CFMC_DR_PAGE_ERS_CMD                          0xFFFFFFFF

/* Magic key for updating command in CR */
#define CFMC_CR_WKY_RST_PE                            0x6C930000
#define CFMC_CR_BUFF_RST_CMD                          (CFMC_CR_WKY_RST_PE | 0x00000001)
#define CFMC_CR_PAGE_ERS_CMD                          (CFMC_CR_WKY_RST_PE | 0x00000002)
#define CFMC_CR_PAGE_PGM_CMD                          (CFMC_CR_WKY_RST_PE | 0x00000004)
#define CFMC_CR_CHIP_ERS_CMD                          (CFMC_CR_WKY_RST_PE | 0x00000008)

#define CFMC_CR_CS_FLASH                              0x0000A400
#define CFMC_CR_CS_SYSFLASH                           0x00003800
#define CFMC_CR_CS_NO_FLASH                           0x00000000

/* Magic key for updating command in BCR */
#define CFMC_BCR_WKY_SYSFLASH_WPROT                   0xC1BE0000
#define CFMC_BCR_SYSFLASH_WPROT                       (CFMC_BCR_WKY_SYSFLASH_WPROT | 0x555)

/* Suedo registers */
#define CFMC_SEUDO_RPROTR                             0x1FFFF200UL
#define CFMC_SEUDO_WDT_CFGR                           0x1FFFF20CUL
#define CFMC_SEUDO_LVRST_CFGR                         0x1FFFF210UL
#define CFMC_SEUDO_CFGOPT_WPROTR                      0x1FFFF214UL
#define CFMC_SEUDO_WPROTR                             0x1FFFF240UL

/* Magic key and commands for read protection */
#define CFMC_SEUDO_WKY_RPROTR                         0x69C8A270UL
#define CFMC_SEUDO_RD_PROTECT_LEVEL1_CMD              (CFMC_SEUDO_WKY_RPROTR | 0x02)
#define CFMC_SEUDO_RD_PROTECT_LEVEL2_CMD              (CFMC_SEUDO_WKY_RPROTR | 0x01)
#define CFMC_SEUDO_RD_PROTECT_LEVEL0_CMD              (CFMC_SEUDO_WKY_RPROTR | 0x03)

/* Define internal variant features */
#define CFMC_VARIANT_FEATURE_PAGE_SIZE                0x00000080UL
#define CFMC_VARIANT_FEATURE_PAGE_WORD_SIZE           (CFMC_VARIANT_FEATURE_PAGE_SIZE/4)
#define CFMC_VARIANT_FEATURE_PAGE_OFFSET_Msk          0xFFFFFF80UL

/* Bit/Register Macro */
#define SET_SCU_FMC_PCER(Peri,Data)                   SET_BIT(Peri,Data,SCUCG,PPCLKEN2,FMCLKE)

#define SET_CFMC_MR(Peri,Data)                        do{\
                                                          (void)Data;\
                                                          SET_REG(Peri,CFMC_MR_MODE_CMD,ADR);\
                                                      }while(0)

#define SET_CFMC_CR_PMODE(Peri,Data)                  do{\
                                                          (void)Data;\
                                                          SET_REG(Peri,CFMC_PE_MODE_CMD1,IDR1);\
                                                          SET_REG(Peri,CFMC_PE_MODE_CMD2,IDR2);\
                                                      }while(0)

#define SET_CFMC_CR_CHIP_ERS_PROT(Peri,Data)          do{\
                                                        if (Data) SET_REG(Peri, CFMC_BCR_SYSFLASH_WPROT,BCR);\
                                                        else SET_REG(Peri, 0,BCR);\
                                                      }while(0)


#define SET_CFMC_CR_PGM(Peri,Data)                    SET_BIT(Peri,Data,FMC,CR,FMOD)
#define SET_CFMC_CR(Peri,Data)                        SET_REG(Peri,Data,CR)

#define GET_CFMC_DR_BUF_ADDR(Peri)                    GET_REG_ADDR(Peri,PAGEBUF)
#define SET_CFMC_AR(Peri,Data)                        SET_REG(Peri,Data,ADR)

#define GET_CFMC_STR_PMODE1(Peri)                     GET_REG(Peri,IDR1)
#define GET_CFMC_STR_PMODE2(Peri)                     GET_REG(Peri,IDR2)
#define GET_CFMC_STR_WRBUSY(Peri)                     GET_BIT(Peri,FMC,CR,FMBUSY)
#define SET_CFMC_STR_ERR(Peri,Data)                   SET_BIT(Peri,Data,FMC,ERFLAG,FMOPFLAG)
#define GET_CFMC_STR_ERR(Peri)                        GET_BIT(Peri,FMC,ERFLAG,FMOPFLAG)


/* External reference */
extern uint32_t g_un32PageBuffer[];
extern RAMFUNC HAL_ERR_e PRV_CFMC_PageWrite(uint32_t un32FlashAddr, uint32_t *pun32Data, bool bIsSystemFlash);


/* Inline functions */
static __inline void CFMC_SetConfig(CFMC_CONFIG_t tConfig);
static __inline void CFMC_SetWriteProtect(uint32_t un32TargetBlk, bool bRequestLock);
static __inline HAL_ERR_e CFMC_SetReadProtect(CFMC_RD_PROTECT_CONFIG_t tRdProtectConfig);
static __inline void CFMC_Erase(volatile uint32_t un32PageAddr, CFMC_ERASE_MODE_e eEraseMode, bool bIsSystemFlash);
static __inline void CFMC_Write(volatile uint32_t un32FlashAddr, uint32_t *pun32Data, uint32_t un32Len, bool bIsWordWrite, bool bIsSystemFlash);

RAMFUNC static __inline void CFMC_SetConfig(CFMC_CONFIG_t tConfig)
{
    SET_SCU_FMC_PCER(((SCUCG_Type*)SCUCG_BASE), true);

    /* No configuration mechanism */
    return;
}

/* Assume : Config option area should be erased before */
RAMFUNC static __inline void CFMC_SetWriteProtect(uint32_t un32TargetBlk, bool bRequestLock)
{
    if (bRequestLock)
    {
        un32TargetBlk = ~un32TargetBlk;

    }

    CFMC_Write(CFMC_SEUDO_WPROTR, &un32TargetBlk, 1, true, true);

    return;
}

/* Assume : Config option area should be erased before */
RAMFUNC static __inline HAL_ERR_e CFMC_SetReadProtect(CFMC_RD_PROTECT_CONFIG_t tRdProtectConfig)
{
    uint32_t un32ReadProtConfig;

    switch (tRdProtectConfig.eRdProtectLevel)
    {
        case CFMC_RD_PROTECT_LEVEL0:
            un32ReadProtConfig = CFMC_SEUDO_RD_PROTECT_LEVEL0_CMD;
            break;

        case CFMC_RD_PROTECT_LEVEL1:
            un32ReadProtConfig = CFMC_SEUDO_RD_PROTECT_LEVEL1_CMD;
            break;

        case CFMC_RD_PROTECT_LEVEL2:
            un32ReadProtConfig = CFMC_SEUDO_RD_PROTECT_LEVEL2_CMD;
            break;

        default:
            return HAL_ERR_PARAMETER;
    }

    CFMC_Write(CFMC_SEUDO_RPROTR, &un32ReadProtConfig, 1, true, true);

    return HAL_ERR_OK;
}

RAMFUNC static __inline void CFMC_Erase (volatile uint32_t un32PageAddr, CFMC_ERASE_MODE_e eEraseMode, bool bIsSystemFlash)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    uint32_t *pun32PageBuf = (uint32_t *)GET_CFMC_DR_BUF_ADDR(ptRegBase);
    uint32_t un32State=0xFF;
    uint32_t un32EraseCmd;
    uint32_t un32SelectedFlash;
    uint32_t i;

#if (CONFIG_DEBUG == 1)
    CFMC_RD_PROTECT_CONFIG_t tRdProtectConfig;
#endif

    if (eEraseMode == CFMC_CHIP_ERASE_MODE)
    {
        un32PageAddr = CFMC_AR_CHIP_ERS_CMD;
        un32EraseCmd  = CFMC_CR_CHIP_ERS_CMD;
    }
    else if (eEraseMode == CFMC_PAGE_ERASE_MODE)
    {
        /* Skip just in the case of non user-info area */
        if (bIsSystemFlash)
        {
            if ((un32PageAddr >= STARTUP_NON_USER_INFO_BASE_OFFSET) && (un32PageAddr < STARTUP_NON_USER_INFO_BASE_OFFSET + STARTUP_NON_USER_INFO_SIZE))
            {
                return;
            }
        }

        un32PageAddr |= STARTUP_FLASH_BASE_ADDR;
        un32PageAddr &= CFMC_VARIANT_FEATURE_PAGE_OFFSET_Msk;
        un32EraseCmd  = CFMC_CR_PAGE_ERS_CMD;
    }
    else
    {
        return;
    }

    SET_CFMC_MR(ptRegBase, true);
    __asm volatile ("cpsid i");

    SET_CFMC_CR_PMODE(ptRegBase, true);

    /* Reset page buffer */
    SET_CFMC_CR(ptRegBase, CFMC_CR_BUFF_RST_CMD);

    /* Setup chip erase protection */
    if (bIsSystemFlash)
    {
        if (eEraseMode == CFMC_CHIP_ERASE_MODE)
        {
            un32SelectedFlash = CFMC_CR_CS_FLASH;
        }
        else
        {
            un32SelectedFlash = CFMC_CR_CS_SYSFLASH;
        }
    }
    else
    {
        un32SelectedFlash = CFMC_CR_CS_FLASH;
    }

    if (eEraseMode == CFMC_CHIP_ERASE_MODE)
    {
        SET_CFMC_CR_CHIP_ERS_PROT(ptRegBase, true);
    }

    /* Page buffer has to be set 0xFFFFFFFF on erase operation */
    for (i = 0; i < CFMC_VARIANT_FEATURE_PAGE_WORD_SIZE; i++)
    {
        *pun32PageBuf++ = CFMC_DR_PAGE_ERS_CMD;
    }

    SET_CFMC_AR(ptRegBase,un32PageAddr);

    /* Check if flash stays in PE state still */
    if ((GET_CFMC_STR_PMODE1(ptRegBase) != CFMC_PE_MODE_CMD1) || (GET_CFMC_STR_PMODE2(ptRegBase) != CFMC_PE_MODE_CMD2))
    {
        goto ERS_EXIT;
    }

    /* Fire Erase Command */
    SET_CFMC_CR_PGM(ptRegBase,  un32SelectedFlash | un32EraseCmd);

    /* Check PGM Result status */
    do
    {
        un32State = GET_CFMC_STR_WRBUSY(ptRegBase);
        if (GET_CFMC_STR_ERR(ptRegBase))
        {
            SET_CFMC_STR_ERR(ptRegBase,true);
            goto ERS_EXIT;
        }
    } while(un32State);

#if (CONFIG_DEBUG == 1)
    if ((*(uint32_t *)CFMC_SEUDO_RPROTR) == 0xFFFFFFFF)
    {
        tRdProtectConfig.eRdProtectLevel = CFMC_RD_PROTECT_LEVEL0;
        CFMC_SetReadProtect(tRdProtectConfig);
    }
#endif

ERS_EXIT:
    if (eEraseMode == CFMC_CHIP_ERASE_MODE)
    {
        SET_CFMC_CR_CHIP_ERS_PROT(ptRegBase, false);
    }

    /* Come back to Read mode */
    __asm volatile ("cpsie i");

    return;
}

RAMFUNC static __inline void CFMC_Write(volatile uint32_t un32FlashAddr, uint32_t *pun32Data, uint32_t un32Len, bool bIsWordWrite, bool bIsSystemFlash)
{
    uint32_t un32PageBaseAddr;
    uint32_t *pun32PageBaseOffset;
    uint32_t un32Offset;
    uint32_t un32Size = un32Len;
    uint32_t un32TotalSize = 0, un32WriteLen = 0;
    uint32_t un32FlashLastAddr;
    uint32_t i;

    /* Skip just in the case of non user-info area */
    if (bIsSystemFlash)
    {
        if ((un32FlashAddr >= STARTUP_NON_USER_INFO_BASE_OFFSET) && (un32FlashAddr < STARTUP_NON_USER_INFO_BASE_OFFSET + STARTUP_NON_USER_INFO_SIZE))
        {
            return;
        }
    }

    /* word addressing */
    un32FlashAddr = un32FlashAddr & ~0x3;
    un32FlashLastAddr = un32FlashAddr + (un32Size << 2) - 1;

    do
    {
        un32PageBaseAddr = un32FlashAddr & CFMC_VARIANT_FEATURE_PAGE_OFFSET_Msk;
        pun32PageBaseOffset = (uint32_t *)(un32PageBaseAddr | STARTUP_FLASH_BASE_ADDR);
        un32Offset = (un32FlashAddr & ~CFMC_VARIANT_FEATURE_PAGE_OFFSET_Msk) & ~0x3;

        /* Read back */
        for (i = 0; i < CFMC_VARIANT_FEATURE_PAGE_WORD_SIZE; i++)
        {
            g_un32PageBuffer[i] = *pun32PageBaseOffset++;
        }

        /* Write back */
        if ((un32FlashLastAddr >= un32PageBaseAddr) && (un32FlashLastAddr < un32PageBaseAddr + CFMC_VARIANT_FEATURE_PAGE_SIZE))
        {
            un32WriteLen = (un32FlashLastAddr - un32FlashAddr + 1)/4;
        }
        else
        {
            un32WriteLen = (un32PageBaseAddr + CFMC_VARIANT_FEATURE_PAGE_SIZE - un32FlashAddr)/4;
        }

        un32TotalSize += un32WriteLen;

        for (i = 0, un32Offset /=4 ; i < un32WriteLen; i++)
        {
            g_un32PageBuffer[un32Offset + i] = *pun32Data++;
        }

        /* Page Write to flash */
        PRV_CFMC_PageWrite(un32PageBaseAddr | STARTUP_FLASH_BASE_ADDR, &g_un32PageBuffer[0], bIsSystemFlash);

        un32FlashAddr = un32PageBaseAddr + CFMC_VARIANT_FEATURE_PAGE_SIZE;
    }while(un32TotalSize < un32Len);

   return;
}

#endif /* _HAL_CFMC_F_01_00_00_H_ */
