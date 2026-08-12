/**
 *******************************************************************************
 * @file        hal_cfmc.c
 * @author      ABOV R&D Division
 * @brief       Code Flash Memory Controller
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#include "abov_config.h"

#if defined(_CFMC) && !defined (_DFMC)
#include "hal_cfmc.h"
#include "hal_cfmc_prv.h"

#define CFMC_PAGE_SIZE                  CFMC_FEATURE_PAGE_SIZE
#define CFMC_BBLOCK_GRANULARITY         0x400
#define CFMC_DEFAULT_BUS_LATENCY        3
#define CFMC_SYSTEM_FLASH_BASE_OFFSET   CFMC_FEATURE_SYSTEM_FLASH_BASE_OFFSET
#define CFMC_SYSTEM_FLASH_OFFSET_MASK   CFMC_FEATURE_SYSTEM_FLASH_OFFSET_MASK

/* Linker control */
#if defined (EXTRN_FPA_CFMC)
#undef RAMFUNC
#define RAMFUNC
#endif

#if !defined (EXTRN_FPA_CFMC)
#if (CONFIG_EMUL_JTAG_CONNECTION == 1)
extern void PRV_CHIPSET_SetDebuggerConnectionStatus (void);
#endif
#endif /* !EXTRN_FPA_CFMC */

/* Define Flash Control Block */
typedef CONFIG_FLASH_INFO_t CFMC_CTRL_BLK_t;
static CFMC_CTRL_BLK_t s_tCfmcCB;

/* Define Bank switching Boot-rom command */
#if (CFMC_FEATURE_BANK_SWITCH == 1)
#if (CFMC_FEATURE_BANK_SWITCH_CMD_TYPE == 1)
static uint32_t s_aun32BootARomCMD[] =
{
    0x55555555, 0xAAAAAAAA,
    0xED8D0154, 0xAA910010
};

static uint32_t s_aun32BootBRomCMD[] =
{
    0x55555555, 0xAAAAAAAA,
    0xED8D0154, 0xAA910010,
    0xED8E0154, 0xAA910011
};
#elif (CFMC_FEATURE_BANK_SWITCH_CMD_TYPE == 2)
static uint32_t s_aun32BootARomCMD = 0x5A3C0F10;
static uint32_t s_aun32BootBRomCMD = 0x5A3C0F00;
#else
static uint32_t s_aun32BootARomCMD[] =
{
    0x55555555, 0xAAAAAAAA,
    0xED3A014C, 0x00000000,
    0xED810148, 0xAA910010,
};

static uint32_t s_aun32BootBRomCMD[] =
{
    0x55555555, 0xAAAAAAAA,
    0xED810148, 0xAA910010,
    0xED820148, 0xAA910011,
    0xED3B014C, 0x00000100,
};
#endif
#endif

HAL_ERR_e HAL_CFMC_Init(void)
{
    CFMC_CONFIG_t tReqConfig;

    /* Restore Flash geometic information */
    s_tCfmcCB = PRV_CHIPSET_GetFlashGeometricInfo();

    /* Interrupt configruation varys device to device */

    /* Default state (READ Only) refer to manual */

    /* Defaut Lock state varys device to device */
    tReqConfig.bReqCrcEnable = false;
    tReqConfig.bReqCrcInit = false;
    tReqConfig.un8Latency = CFMC_DEFAULT_BUS_LATENCY;
    HAL_CFMC_SetConfig(&tReqConfig);

#if (CONFIG_EMUL_JTAG_CONNECTION == 1)
    PRV_CHIPSET_SetDebuggerConnectionStatus();
#endif

    return HAL_ERR_OK;
}

CFMC_GEOMETRY_t HAL_CFMC_GetGeometry(void)
{
    return s_tCfmcCB;
}

void HAL_CFMC_SetConfig(CFMC_CONFIG_t *ptReqConfig)
{
    CFMC_CONFIG_t tConfig;

    tConfig.bReqCrcEnable = ptReqConfig->bReqCrcEnable;
    tConfig.bReqCrcInit = ptReqConfig->bReqCrcInit;
    tConfig.un8Latency = ptReqConfig->un8Latency;

    CFMC_SetConfig(tConfig);
    return;
}

HAL_ERR_e HAL_CFMC_SetCache(bool bRequestEnable)
{
#if (CFMC_FEATURE_ICACHE == 1)
    CFMC_SetCache(bRequestEnable);
    return HAL_ERR_OK;
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_CFMC_SetWriteProtect(uint32_t un32FlashOffset, uint32_t un32Len, bool bRequestLock)
{
    uint32_t un32StartIndex;
    uint32_t un32EndIndex;
    uint32_t un32TargetBlks = 0;
    uint32_t i;

    if (un32FlashOffset == 0xFFFFFFFF)
    {
        un32TargetBlks = 0xFFFFFFFF;
    }
    else
    {
        if (un32FlashOffset + un32Len > s_tCfmcCB.un32CflashSize)
        {
            return HAL_ERR_PARAMETER;
        }

        un32StartIndex = un32FlashOffset / s_tCfmcCB.un32CflashWProtectedSegSize;
        un32EndIndex = (un32FlashOffset + un32Len) / s_tCfmcCB.un32CflashWProtectedSegSize;
        for (i = un32StartIndex; i < un32EndIndex; i++)
        {
            un32TargetBlks |= (1 << i);
        }
    }

    CFMC_SetWriteProtect(un32TargetBlks, bRequestLock);

    return HAL_ERR_OK;
}

void HAL_CFMC_SetWriteProtectBootBlk(bool bRequestLock)
{
#if (CFMC_FEATURE_BBLOCK == 1)
    CFMC_SetWriteProtectBootBlk(bRequestLock);
#endif

    return;
}

#if !defined (EXTRN_FPA_CFMC)
HAL_ERR_e HAL_CFMC_SetReadProtect(CFMC_RD_PROTECT_CONFIG_t tRdProtectConfig)
{
    HAL_ERR_e eRet = HAL_ERR_OK;

#if (CFMC_FEATURE_RUMTIME_READ_PROTECTION == 1)
    eRet = CFMC_SetReadProtect(tRdProtectConfig);
#endif

    return eRet;
}
#endif /* !EXTRN_FPA_CFMC */

RAMFUNC HAL_ERR_e HAL_CFMC_Erase(uint32_t un32FlashOffset, CFMC_ERASE_MODE_e eEraseMode)
{
    bool bIsSystemFlash;

    /* System flash */
    if (un32FlashOffset >= CFMC_SYSTEM_FLASH_BASE_OFFSET)
    {
        if ((un32FlashOffset & CFMC_SYSTEM_FLASH_OFFSET_MASK) + CFMC_PAGE_SIZE > s_tCfmcCB.un32SystemFlashSize)
        {
            return HAL_ERR_PARAMETER;
        }
        bIsSystemFlash = true;
    }
    else /* Code flash */
    {
        if (un32FlashOffset + CFMC_PAGE_SIZE > s_tCfmcCB.un32CflashSize)
        {
            return HAL_ERR_PARAMETER;
        }
        bIsSystemFlash = false;
    }

    /* Make up byte-address */
    CFMC_Erase(un32FlashOffset, eEraseMode, bIsSystemFlash);

    return HAL_ERR_OK;
}

RAMFUNC HAL_ERR_e HAL_CFMC_Write(uint32_t un32FlashOffset, uint8_t *pun8Data, uint32_t un32Len)
{
    uint32_t *pun32Data = (uint32_t *)pun8Data;

#if (!CFMC_FEATURE_WRITE_IMPL_BY_SELF_WRITE)
    bool bIsSystemFlash;
#else
    uint32_t un32Cnt;
#endif

    /* Enable a write to System flash */
    if (un32FlashOffset >= CFMC_SYSTEM_FLASH_BASE_OFFSET)
    {
        if ((un32FlashOffset & CFMC_SYSTEM_FLASH_OFFSET_MASK) + un32Len > s_tCfmcCB.un32SystemFlashSize)
        {
            return HAL_ERR_PARAMETER;
        }
#if (!CFMC_FEATURE_WRITE_IMPL_BY_SELF_WRITE)
        bIsSystemFlash = true;
#endif
    }
    else
    {
        if (un32FlashOffset + un32Len > s_tCfmcCB.un32CflashSize)
        {
            return HAL_ERR_PARAMETER;
        }
#if (!CFMC_FEATURE_WRITE_IMPL_BY_SELF_WRITE)
        bIsSystemFlash = false;
#endif
    }

    /* Make up word aligned size */
    un32Len = un32Len >> 2;

#if (!CFMC_FEATURE_WRITE_IMPL_BY_SELF_WRITE)
    /* Make up byte-address */
    CFMC_Write(un32FlashOffset, pun32Data, un32Len, true, bIsSystemFlash);
#else
    /* Make up byte-address to be aligned word size */
    un32FlashOffset = un32FlashOffset & ~(0x3);
    for (un32Cnt = 0; un32Cnt <un32Len; un32Cnt++, un32FlashOffset+=4, pun32Data++)
    {
        CFMC_SelfWriteFromRAM(un32FlashOffset, pun32Data);
    }
#endif

    return HAL_ERR_OK;
}

#if !defined (EXTRN_FPA_CFMC)
HAL_ERR_e HAL_CFMC_SelfErase(uint32_t un32FlashOffset)
{
#if (CFMC_FEATURE_SELF_PROGRAM_ERASE == 1)
    /* System flash */
    if (un32FlashOffset >= CFMC_SYSTEM_FLASH_BASE_OFFSET)
    {
        if ((un32FlashOffset & CFMC_SYSTEM_FLASH_OFFSET_MASK) + CFMC_PAGE_SIZE > s_tCfmcCB.un32SystemFlashSize)
        {
            return HAL_ERR_PARAMETER;
        }
    }
    else /* Code flash */
    {
        if (un32FlashOffset + CFMC_PAGE_SIZE > s_tCfmcCB.un32CflashSize)
        {
            return HAL_ERR_PARAMETER;
        }
    }

    /* Make up byte-address to be aligned to Page size */
    un32FlashOffset = un32FlashOffset & ~(CFMC_PAGE_SIZE-1);
    CFMC_SelfErase(un32FlashOffset);
#endif

    return HAL_ERR_OK;
}


HAL_ERR_e HAL_CFMC_SelfWrite(uint32_t un32FlashOffset, uint8_t *pun8Data, uint32_t un32Len)
{
#if (CFMC_FEATURE_SELF_PROGRAM_ERASE == 1)
    uint32_t un32Cnt;
    uint32_t *pun32Data = (uint32_t *)pun8Data;

    /* Enable a write to System flash */
    if (un32FlashOffset >= CFMC_SYSTEM_FLASH_BASE_OFFSET)
    {
        if ((un32FlashOffset & CFMC_SYSTEM_FLASH_OFFSET_MASK) + un32Len > s_tCfmcCB.un32SystemFlashSize)
        {
            return HAL_ERR_PARAMETER;
        }
    }
    else
    {
        if (un32FlashOffset + un32Len > s_tCfmcCB.un32CflashSize)
        {
            return HAL_ERR_PARAMETER;
        }
    }

    /* Make up byte-address to be aligned to word size */
    un32FlashOffset = un32FlashOffset & ~(0x3);
    un32Len = un32Len >> 2;
    for (un32Cnt = 0; un32Cnt <un32Len; un32Cnt++, un32FlashOffset+=4, pun32Data++)
    {
        CFMC_SelfWrite(un32FlashOffset, pun32Data);
    }
#endif

    return HAL_ERR_OK;
}
#endif /* !EXTRN_FPA_CFMC */

RAMFUNC HAL_ERR_e HAL_CFMC_SetMultiBankConfig(bool bRequestMultiBank)
{
#if (CFMC_FEATURE_BANK_SWITCH == 1)
    CFMC_SetMultiBankConfig(bRequestMultiBank);
    return HAL_ERR_OK;
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

RAMFUNC HAL_ERR_e HAL_CFMC_GetBankSwitchStatus(CFMC_BANK_ID_e *peBootBank, bool *pbBankSwitchDone, CFMC_BANK_ID_e *peActiveBank)
{
#if (CFMC_FEATURE_BANK_SWITCH == 1)
    HAL_ERR_e eRet;

    eRet = CFMC_GetBankSwitchStatus(peBootBank, pbBankSwitchDone, peActiveBank);
    return eRet;
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

RAMFUNC HAL_ERR_e HAL_CFMC_SetActiveBank(CFMC_BANK_ID_e eBankID)
{
#if (CFMC_FEATURE_BANK_SWITCH == 1)
    HAL_ERR_e eRet;

    if ((eBankID != CFMC_BANK_A) && (eBankID != CFMC_BANK_B))
    {
        return HAL_ERR_PARAMETER;
    }

    eRet = CFMC_SetActiveBank(eBankID);
    return eRet;
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

RAMFUNC HAL_ERR_e HAL_CFMC_SetBootBankOnUserInfo(CFMC_BANK_ID_e eBankID)
{
#if (CFMC_FEATURE_BANK_SWITCH == 1)
    uint32_t un32Len;

    /* STEP1. Erase Bank switching command (boot-rom command) area in UserInfo */
    CFMC_EraseUserInfo(CFMC_FEATURE_BANK_SWITCH_CMD_OFFSET, CFMC_PAGE_ERASE_MODE, PRV_CMFC_USERINFO_BANK_SWITCH_ID);

    /* STEP2. Write command into Bank switching command (boot-rom command) area in UserInfo */
    if (eBankID  == CFMC_BANK_A)
    {
        un32Len = sizeof(s_aun32BootARomCMD);
        un32Len = un32Len >> 2;
        CFMC_WriteToUserInfo(CFMC_FEATURE_BANK_SWITCH_CMD_OFFSET, (uint32_t *)&s_aun32BootARomCMD, un32Len, PRV_CMFC_USERINFO_BANK_SWITCH_ID);
    }
    else if (eBankID  == CFMC_BANK_B)
    {
        un32Len = sizeof(s_aun32BootBRomCMD);
        un32Len = un32Len >> 2;
        CFMC_WriteToUserInfo(CFMC_FEATURE_BANK_SWITCH_CMD_OFFSET, (uint32_t *)&s_aun32BootBRomCMD, un32Len, PRV_CMFC_USERINFO_BANK_SWITCH_ID);
    }
    else
    {
        /* Erase boot-bank information on UserInfo just in case of CFMC_BANK_SINGLE */
    }

    return HAL_ERR_OK;
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

#endif /* _CFMC && !_DFMC */

