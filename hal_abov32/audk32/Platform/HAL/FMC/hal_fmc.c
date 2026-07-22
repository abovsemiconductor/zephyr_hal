/**
 *******************************************************************************
 * @file        hal_fmc.c
 * @author      ABOV R&D Division
 * @brief       Flash Memory Controller (Code and Data)
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

#if defined(_CFMC) && defined (_DFMC)
#include "hal_fmc.h"
#include "hal_fmc_prv.h"

#define FMC_PAGE_SIZE                   FMC_FEATURE_PAGE_SIZE

#define CFMC_BBLOCK_GRANULARITY         0x400
#define CFMC_DEFAULT_BUS_LATENCY        3
#define CFMC_DEFAULT_TIMEOUT            0
#define CFMC_SYSTEM_FLASH_BASE_OFFSET   FMC_FEATURE_SYSTEM_FLASH_BASE_OFFSET

#define DFMC_DEFAULT_BUS_LATENCY        3
#define DFMC_DEFAULT_TIMEOUT            0
#define DFMC_BASE_ADDR                  (FMC_FEATURE_FLASH_BASE_ADDR | FMC_FEATURE_DATA_FLASH_BASE_OFFSET)

#define FMC_DATA_SYSTEM_FLASH_ADDR      FMC_FEATURE_DATA_FLASH_BASE_OFFSET

#define FMC_IRQ_DEFAULT_PRIORITY        3
#define FMC_INVALID_WPROT_BLOCK         0xFF

/* Internal macro for password lock testing only */
#define HAL_FMC_TEST_RD_PROTECT         0

/* Linker control */
#if defined (EXTRN_FPA_CFMC) || defined (EXTRN_FPA_DFMC)
#undef RAMFUNC
#define RAMFUNC
#endif

/* Flash Global Control Block */
FMC_CTRL_BLK_t s_tFmcCB;

/* Define Bank switching Boot-rom command */
#if (FMC_FEATURE_CFMC_BANK_SWITCH == 1)
#if (FMC_FEATURE_CFMC_BANK_SWITCH_CMD_TYPE == 1)
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
#elif (FMC_FEATURE_CFMC_BANK_SWITCH_CMD_TYPE == 2)
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

#if !defined (EXTRN_FPA_CFMC) && !defined (EXTRN_FPA_DFMC)
#if (FMC_FEATURE_IRQ_SERVICE == 1)
static uint32_t s_un32EventCFMC = 0;
static uint32_t s_un32EventDFMC = 0;
#endif

#if (CONFIG_EMUL_JTAG_CONNECTION == 1)
extern void PRV_CHIPSET_SetDebuggerConnectionStatus (void);
#endif

#if (FMC_FEATURE_IRQ_SERVICE == 1)
RAMFUNC void CFMC_IRQ_Handler(void);
RAMFUNC void CFMC_IRQ_Handler(void)
{
    s_un32EventCFMC = FMC_GetEvent(FMC_ID_CFMC);
    return;
}

RAMFUNC void DFMC_IRQ_Handler(void);
RAMFUNC void DFMC_IRQ_Handler(void)
{
    s_un32EventDFMC = FMC_GetEvent(FMC_ID_DFMC);
    return;
}
#endif
#endif /* !EXTRN_FPA_CFMC && !EXTRN_FPA_DFMC */

#if (FMC_FEATURE_DFMC_WRITE_BYTE == 1) && (FMC_FEATURE_WRITE_IMPL_BY_SELF_WRITE == 1)
RAMFUNC static uint32_t PRV_HAL_DFMC_GetMaskedData(uint32_t un32FlashAddr, uint8_t *pun8Data, int32_t un32Len, uint32_t *pun32WrittenLen);
RAMFUNC static uint32_t PRV_HAL_DFMC_GetMaskedData(uint32_t un32FlashAddr, uint8_t *pun8Data, int32_t un32Len, uint32_t *pun32WrittenLen)
{
    uint32_t un32MaxToWrite;
    uint32_t un32DataWord = 0;
    uint32_t un32StartByteIndex;
    uint32_t un32Cnt;
    uint32_t un32DataMask = 0;

    un32StartByteIndex = un32FlashAddr & 0x3;
    un32MaxToWrite = 4 - un32StartByteIndex;
    if (un32Len <= un32MaxToWrite)
    {
        un32MaxToWrite = un32Len;
    }

    for (un32Cnt = 0; un32Cnt < un32MaxToWrite; un32Cnt++, pun8Data++)
    {
        un32DataWord = un32DataWord | (*pun8Data << (8 * (un32StartByteIndex + un32Cnt)));
        un32DataMask = un32DataMask | (0xFF << (8 * (un32StartByteIndex + un32Cnt)));
    }

    un32DataWord |= (*(uint32_t *)((un32FlashAddr | DFMC_BASE_ADDR) & ~0x3)) & ~un32DataMask;
    *pun32WrittenLen = un32MaxToWrite;
    return un32DataWord;
}
#endif

RAMFUNC static uint8_t PRV_FMC_GetWriteProtectedBlock (CONFIG_FLASH_GEOMETRY_t *ptFlashGeometry, uint32_t un32Offset)
{
    uint32_t un32WProtectedSegStartOffset;
    uint32_t un32WProtectedSegSize;
    uint8_t un8NumWProtectedSegs;
    uint8_t un8BlockID;

    for (un8BlockID = 0; un8BlockID < ptFlashGeometry->un8NumWProtectedBlocks; un8BlockID++)
    {
        un32WProtectedSegStartOffset = ptFlashGeometry->tWProtectedBlocks[un8BlockID].un32WProtectedSegStartOffset;
        un32WProtectedSegSize = ptFlashGeometry->tWProtectedBlocks[un8BlockID].un32WProtectedSegSize;
        un8NumWProtectedSegs = ptFlashGeometry->tWProtectedBlocks[un8BlockID].un8NumWProtectedSegs;

        if ((un32Offset >= un32WProtectedSegStartOffset) && (un32Offset < un32WProtectedSegStartOffset + un8NumWProtectedSegs*un32WProtectedSegSize))
        {
            return un8BlockID;
        }
    }

    return FMC_INVALID_WPROT_BLOCK;
}

RAMFUNC HAL_ERR_e HAL_FMC_Init(void)
{
    FMC_CONFIG_t tReqConfig;
#if (FMC_FEATURE_IRQ_SERVICE == 1)
    IRQn_Type eIrq;
#endif

    /* Restore Flash geometic information */
    s_tFmcCB.tGeometry = PRV_CHIPSET_GetFlashGeometricInfo();

    /* Default state (READ Only) refer to manual */
#if (FMC_FEATURE_CFMC_IDCACHE == 1)
    HAL_CFMC_SetCache(CFMC_INST_DATA_CACHE, true);
#endif

    /* Defaut Lock state varys device to device */
    tReqConfig.bReqCrcEnable = false;
    tReqConfig.bReqCrcInit = false;
    tReqConfig.un8Latency = CFMC_DEFAULT_BUS_LATENCY;
    tReqConfig.un8TimeOut = CFMC_DEFAULT_TIMEOUT;
    HAL_FMC_SetConfig(FMC_ID_CFMC, &tReqConfig);

    tReqConfig.bReqCrcEnable = false;
    tReqConfig.bReqCrcInit = false;
    tReqConfig.un8Latency = DFMC_DEFAULT_BUS_LATENCY;
    tReqConfig.un8TimeOut = DFMC_DEFAULT_TIMEOUT;
    HAL_FMC_SetConfig(FMC_ID_DFMC, &tReqConfig);

#if (FMC_FEATURE_IRQ_SERVICE == 1)
    eIrq = FMC_GetIRQNumber(FMC_ID_CFMC);
    NVIC_DisableIRQ(eIrq);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_SetPriority(eIrq,FMC_IRQ_DEFAULT_PRIORITY);
    NVIC_EnableIRQ(eIrq);

    eIrq = FMC_GetIRQNumber(FMC_ID_DFMC);
    NVIC_DisableIRQ(eIrq);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_SetPriority(eIrq,FMC_IRQ_DEFAULT_PRIORITY);
    NVIC_EnableIRQ(eIrq);
#endif

#if (CONFIG_EMUL_JTAG_CONNECTION == 1)
    PRV_CHIPSET_SetDebuggerConnectionStatus();
#endif

    return HAL_ERR_OK;
}

RAMFUNC FMC_GEOMETRY_t HAL_FMC_GetGeometry(void)
{
    return s_tFmcCB.tGeometry;
}

RAMFUNC void HAL_FMC_SetConfig(FMC_ID_e eFmcID, FMC_CONFIG_t *ptReqConfig)
{
    FMC_CONFIG_t tConfig;

    tConfig.bReqCrcEnable = ptReqConfig->bReqCrcEnable;
    tConfig.bReqCrcInit = ptReqConfig->bReqCrcInit;
    tConfig.un8Latency = ptReqConfig->un8Latency;
    tConfig.un8TimeOut = ptReqConfig->un8TimeOut;
    FMC_SetConfig(eFmcID, tConfig);

    return;
}

RAMFUNC HAL_ERR_e HAL_CFMC_SetCache(CFMC_CACHE_ID_e eCacheID, bool bRequestEnable)
{
#if (FMC_FEATURE_CFMC_IDCACHE == 1)
    CFMC_SetCache(eCacheID, bRequestEnable);
    return HAL_ERR_OK;
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

RAMFUNC HAL_ERR_e HAL_FMC_SetWriteProtect(FMC_ID_e eFmcID, uint32_t un32FlashOffset, uint32_t un32Len, bool bRequestLock)
{
    uint32_t un32StartIndex = 0;
    uint32_t un32EndIndex = 0;
    uint32_t un32TargetBlks = 0;
    uint32_t un32FlashSize;
    CONFIG_FLASH_GEOMETRY_t *ptFlashGeometry;

    uint8_t un8StartBlockID;
    uint8_t un8LastBlockID;
    uint32_t i;
    uint32_t un32TotalWProtectedSegs = 0;
    
    if (eFmcID == FMC_ID_CFMC)
    {
        un32FlashSize = s_tFmcCB.tGeometry.tCflash.un32Size;
        ptFlashGeometry = &s_tFmcCB.tGeometry.tCflash;
    }
    else
    {
        un32FlashSize = s_tFmcCB.tGeometry.tDflash.un32Size;
        ptFlashGeometry = &s_tFmcCB.tGeometry.tDflash;
    }

    for (i = 0; i < ptFlashGeometry->un8NumWProtectedBlocks; i++)
    {
        un32TotalWProtectedSegs += ptFlashGeometry->tWProtectedBlocks[i].un8NumWProtectedSegs;
    }

    if (un32FlashOffset != 0xFFFFFFFF)
    {
        if (un32FlashOffset + un32Len > un32FlashSize)
        {
            return HAL_ERR_PARAMETER;
        }

        un8StartBlockID = PRV_FMC_GetWriteProtectedBlock(ptFlashGeometry, un32FlashOffset);
        un8LastBlockID = PRV_FMC_GetWriteProtectedBlock(ptFlashGeometry, un32FlashOffset+un32Len -1);

        for (i = 0, un32StartIndex = 0; i < un8StartBlockID; i++)
        {
            un32StartIndex += ptFlashGeometry->tWProtectedBlocks[i].un8NumWProtectedSegs;
        }
        un32StartIndex += (un32FlashOffset - ptFlashGeometry->tWProtectedBlocks[i].un32WProtectedSegStartOffset) / ptFlashGeometry->tWProtectedBlocks[i].un32WProtectedSegSize;

        for (i = 0, un32EndIndex = 0; i < un8LastBlockID; i++)
        {
            un32EndIndex += ptFlashGeometry->tWProtectedBlocks[i].un8NumWProtectedSegs;
        }
        un32EndIndex += (un32FlashOffset + un32Len - ptFlashGeometry->tWProtectedBlocks[i].un32WProtectedSegStartOffset) / ptFlashGeometry->tWProtectedBlocks[i].un32WProtectedSegSize;
    }
    else
    {
        un32TargetBlks = 0xFFFFFFFF;
        un32EndIndex = un32TotalWProtectedSegs;
    }

    for (i = un32StartIndex; i < un32EndIndex; i++)
    {
        un32TargetBlks |= (1 << i % 32);
        if (i % 32 == 31 || i == un32EndIndex - 1)
        {
            FMC_SetWriteProtect(eFmcID, i / 32, un32TargetBlks, bRequestLock);
        }
    }

    return HAL_ERR_OK;
}

#if (FMC_FEATURE_CFMC_BBLOCK == 1)
#if (FMC_FEATURE_CFMC_BBLOCK_IMPL_BY_WRITE_PROT == 1)
RAMFUNC HAL_ERR_e HAL_CFMC_SetWriteProtectBootBlk(CFMC_BANK_ID_e eBankID, uint32_t un32FlashOffset, uint32_t un32Len, bool bRequestLock)
{
    HAL_ERR_e eRet;
    uint32_t un32StartIndex;
    uint32_t un32EndIndex;
    uint32_t i;
    uint32_t un32TargetBlk = 0;
    uint32_t un32CflashOffset;
    CONFIG_FLASH_GEOMETRY_t *ptFlashGeometry = &s_tFmcCB.tGeometry.tCflash;

    if (eBankID == CFMC_BANK_SINGLE) || (eBankID == CFMC_BANK_A)
    {
        un32CflashOffset = un32FlashOffset;
    }
    else
    {
        un32CflashOffset = un32FlashOffset + ptFlashGeometry->un32Size/2;
    }

    if ((un32FlashOffset + un32Len) > ptFlashGeometry->tWProtectedBlocks[0].un32WProtectedSegSize)
    {
        return HAL_ERR_PARAMETER;
    }

    un32StartIndex = un32FlashOffset / CFMC_BBLOCK_GRANULARITY;
    un32EndIndex = (un32FlashOffset + un32Len) / CFMC_BBLOCK_GRANULARITY;
    for (i = un32StartIndex; i < un32EndIndex; i++)
    {
        un32TargetBlk |= (1 << i);
    }

    eRet = CFMC_SetWriteProtectBootBlk(eBankID, un32TargetBlk, bRequestLock);
    return eRet;
}
#else
RAMFUNC HAL_ERR_e HAL_CFMC_SetWriteProtectBootBlk(bool bRequestLock)
{
    CFMC_SetWriteProtectBootBlk(bRequestLock);
    return HAL_ERR_OK;
}
#endif /* FMC_FEATURE_CFMC_BBLOCK_IMPL_BY_WRITE_PROT == 1 */
#else
RAMFUNC HAL_ERR_e HAL_CFMC_SetWriteProtectBootBlk(bool bRequestLock)
{
    return HAL_ERR_NOT_SUPPORTED;
}
#endif /* FMC_FEATURE_CFMC_BBLOCK == 1 */


#if !defined (EXTRN_FPA_CFMC) && !defined (EXTRN_FPA_DFMC)
RAMFUNC HAL_ERR_e HAL_FMC_SetReadUnProtect(FMC_ID_e eFmcID, uint32_t un32Password)
{
#if (FMC_FEATURE_RUMTIME_READ_PROTECTION == 1)
#if (FMC_FEATURE_PASSWD_LOCK == 1)
    HAL_ERR_e eRet;

    eRet = FMC_SetMatchedPassword(eFmcID, un32Password);
    return eRet;
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif

}

RAMFUNC HAL_ERR_e HAL_FMC_SetReadProtect(FMC_ID_e eFmcID, FMC_RD_PROTECT_CONFIG_t tRdProtectConfig)
{
#if (FMC_FEATURE_RUMTIME_READ_PROTECTION == 1)
    HAL_ERR_e eRet;

    eRet = FMC_SetReadProtect(eFmcID, tRdProtectConfig);

#if (HAL_FMC_TEST_RD_PROTECT == 1)
    HAL_FMC_SetReadUnProtect(eFmcID, tRdProtectConfig.un32RegisteredPasswd);
#endif

    return eRet;
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif
}
#endif /* !EXTRN_FPA_CFMC && !EXTRN_FPA_DFMC */

RAMFUNC HAL_ERR_e HAL_FMC_Erase(FMC_ID_e eFmcID, uint32_t un32FlashOffset, FMC_ERASE_MODE_e eEraseMode)
{
    bool bIsSystemFlash;
    uint32_t un32FlashSize;
    uint32_t un32EraseBlkSize;
    uint32_t un32PageSize;
    HAL_ERR_e eRet;

    if (eFmcID == FMC_ID_CFMC)
    {
        if (un32FlashOffset < s_tFmcCB.tGeometry.tSysflash.un32BaseAddr)
        {
            un32FlashSize = s_tFmcCB.tGeometry.tCflash.un32Size;
            bIsSystemFlash = false;
        }
        else
        {
            un32FlashSize = s_tFmcCB.tGeometry.tSysflash.un32Size;
            bIsSystemFlash = true;
        }
    }
    else
    {
        un32FlashSize = s_tFmcCB.tGeometry.tDflash.un32Size;
        bIsSystemFlash = false;
    }

    if (bIsSystemFlash)
    {
        if ((un32FlashOffset & FMC_FEATURE_SYSTEM_FLASH_OFFSET_MASK) + FMC_PAGE_SIZE > un32FlashSize)
        {
            return HAL_ERR_PARAMETER;
        }
    }
    else
    {
        if (eFmcID == FMC_ID_CFMC)
        {
            un32PageSize = FMC_FEATURE_PAGE_SIZE;
        }
        else
        {
            un32PageSize = FMC_FEATURE_DATA_PAGE_SIZE;
        }

        un32EraseBlkSize = un32PageSize * eEraseMode;
        if (un32FlashOffset + un32EraseBlkSize > un32FlashSize)
        {
            return HAL_ERR_PARAMETER;
        }
    }

    eRet = FMC_Erase(eFmcID, un32FlashOffset, eEraseMode, bIsSystemFlash);
    return eRet;
}

RAMFUNC HAL_ERR_e HAL_FMC_Write(FMC_ID_e eFmcID, uint32_t un32FlashOffset, uint8_t *pun8Data, uint32_t un32Len)
{
    uint32_t *pun32Data = (uint32_t *)pun8Data;
    bool bIsSystemFlash;

#if (!FMC_FEATURE_WRITE_IMPL_BY_SELF_WRITE)
    HAL_ERR_e eRet;
#else
    uint32_t un32Cnt;
#endif
    uint32_t un32FlashSize;

    if (eFmcID == FMC_ID_CFMC)
    {
        if (un32FlashOffset < s_tFmcCB.tGeometry.tSysflash.un32BaseAddr)
        {
            un32FlashSize = s_tFmcCB.tGeometry.tCflash.un32Size;
            bIsSystemFlash = false;
        }
        else
        {
            un32FlashSize = s_tFmcCB.tGeometry.tSysflash.un32Size;
            bIsSystemFlash = true;
        }
    }
    else
    {
        un32FlashSize = s_tFmcCB.tGeometry.tDflash.un32Size;
        bIsSystemFlash = false;
    }

    if (bIsSystemFlash)
    {
        if ((un32FlashOffset & FMC_FEATURE_SYSTEM_FLASH_OFFSET_MASK) + un32Len > un32FlashSize)
        {
            return HAL_ERR_PARAMETER;
        }
    }
    else
    {
        if (un32FlashOffset + un32Len > un32FlashSize)
        {
            return HAL_ERR_PARAMETER;
        }
    }

    /* Length in word */
    un32Len = un32Len >> 2;

#if (!FMC_FEATURE_WRITE_IMPL_BY_SELF_WRITE)
    eRet = FMC_Write(eFmcID, un32FlashOffset, pun32Data, un32Len, true, bIsSystemFlash);

    return eRet;
#else
    /* Make up byte address alinged to word */
    un32FlashOffset = un32FlashOffset & ~(0x3);

    for (un32Cnt = 0; un32Cnt <un32Len; un32Cnt++, un32FlashOffset+=4, pun32Data++)
    {
        FMC_SelfWriteFromRAM(eFmcID, un32FlashOffset, pun32Data);
    }

    return HAL_ERR_OK;
#endif
}

RAMFUNC HAL_ERR_e HAL_DFMC_WriteByte(uint32_t un32FlashOffset, uint8_t *pun8Data, uint32_t un32Len)
{
#if (FMC_FEATURE_DFMC_WRITE_BYTE == 1)

#if (!FMC_FEATURE_WRITE_IMPL_BY_SELF_WRITE)
    uint32_t *pun32Data = (uint32_t *)pun8Data;
#else
    uint32_t un32Cnt;
    uint32_t un32MaskedData;
    uint32_t un32MaxWordsToWrite;
    uint32_t un32WrittenLen;
    uint32_t i;
#endif

    /* Enable a write to System flash */
    if (un32FlashOffset + un32Len > s_tFmcCB.tGeometry.tDflash.un32Size)
    {
        return HAL_ERR_PARAMETER;
    }

#if (!FMC_FEATURE_WRITE_IMPL_BY_SELF_WRITE)
    FMC_Write(FMC_ID_DFMC, un32FlashOffset, pun32Data, un32Len, false, false);
#else
    /* Write first unaliged or alinged word */
    un32MaskedData = PRV_HAL_DFMC_GetMaskedData(un32FlashOffset, pun8Data, un32Len, &un32WrittenLen);
    un32FlashOffset = un32FlashOffset & ~(0x3);
    FMC_SelfWriteFromRAM(FMC_ID_DFMC, un32FlashOffset, &un32MaskedData);

    /* Write alinged words data only */
    un32MaxWordsToWrite = (un32Len - un32WrittenLen) / 4;
    for (un32Cnt = 0, un32FlashOffset+=4; un32Cnt <un32MaxWordsToWrite; un32Cnt++, un32FlashOffset+=4, un32WrittenLen+=4)
    {
        un32MaskedData = 0;
        for (i=0; i<4; i++)
        {
            un32MaskedData = un32MaskedData | (pun8Data[un32WrittenLen + i] << (8 * i));
        }
        FMC_SelfWriteFromRAM(FMC_ID_DFMC, un32FlashOffset, &un32MaskedData);
    }

    /* Write last unaligned or aligned word */
    un32Len = un32Len - un32WrittenLen;
    un32MaskedData = PRV_HAL_DFMC_GetMaskedData(un32FlashOffset, &pun8Data[un32WrittenLen], un32Len, &un32WrittenLen);
    FMC_SelfWriteFromRAM(FMC_ID_DFMC, un32FlashOffset, &un32MaskedData);
#endif
    return HAL_ERR_OK;
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif /* FMC_FEATURE_DFMC_WRITE_BYTE == 1 */

}

#if !defined (EXTRN_FPA_CFMC) && !defined (EXTRN_FPA_DFMC)
HAL_ERR_e HAL_FMC_SelfErase(FMC_ID_e eFmcID, uint32_t un32FlashOffset)
{
#if (FMC_FEATURE_SELF_PROGRAM_ERASE == 1)
    bool bIsSystemFlash;
    uint32_t un32FlashSize;
    HAL_ERR_e eRet;

    if (eFmcID == FMC_ID_CFMC)
    {
        if (un32FlashOffset < s_tFmcCB.tGeometry.tSysflash.un32BaseAddr)
        {
            un32FlashSize = s_tFmcCB.tGeometry.tCflash.un32Size;
            bIsSystemFlash = false;
        }
        else
        {
            un32FlashSize = s_tFmcCB.tGeometry.tSysflash.un32Size;
            bIsSystemFlash = true;
        }
    }
    else
    {
        un32FlashSize = s_tFmcCB.tGeometry.tDflash.un32Size;
        bIsSystemFlash = false;
    }

    if (bIsSystemFlash)
    {
        if ((un32FlashOffset & FMC_FEATURE_SYSTEM_FLASH_OFFSET_MASK) + FMC_PAGE_SIZE > un32FlashSize)
        {
            return HAL_ERR_PARAMETER;
        }
    }
    else
    {
        if (un32FlashOffset + FMC_FEATURE_PAGE_SIZE > un32FlashSize)
        {
            return HAL_ERR_PARAMETER;
        }
    }

    /* Make up 512B alinged address which is common whatever erase mode is taken */
    un32FlashOffset = un32FlashOffset & ~(FMC_PAGE_SIZE - 1);
    eRet = FMC_SelfErase(eFmcID, un32FlashOffset);

    return eRet;
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_FMC_SelfWrite(FMC_ID_e eFmcID, uint32_t un32FlashOffset, uint8_t *pun8Data, uint32_t un32Len)
{
#if (FMC_FEATURE_SELF_PROGRAM_ERASE == 1)
    bool bIsSystemFlash;
    uint32_t un32Cnt;
    uint32_t un32FlashSize;
    uint32_t *pun32Data = (uint32_t *)pun8Data;
    HAL_ERR_e eRet = HAL_ERR_OK;

    if (eFmcID == FMC_ID_CFMC)
    {
        if (un32FlashOffset < s_tFmcCB.tGeometry.tSysflash.un32BaseAddr)
        {
            un32FlashSize = s_tFmcCB.tGeometry.tCflash.un32Size;
            bIsSystemFlash = false;
        }
        else
        {
            un32FlashSize = s_tFmcCB.tGeometry.tSysflash.un32Size;
            bIsSystemFlash = true;
        }
    }
    else
    {
        un32FlashSize = s_tFmcCB.tGeometry.tDflash.un32Size;
        bIsSystemFlash = false;
    }

    if (bIsSystemFlash)
    {
        if ((un32FlashOffset & FMC_FEATURE_SYSTEM_FLASH_OFFSET_MASK) + un32Len > un32FlashSize)
        {
            return HAL_ERR_PARAMETER;
        }
    }
    else
    {
        if (un32FlashOffset + un32Len > un32FlashSize)
        {
            return HAL_ERR_PARAMETER;
        }
    }

    /* Make up word alinged Byte addressing */
    un32FlashOffset = un32FlashOffset & ~(0x3);
    un32Len = un32Len >> 2;

    for (un32Cnt = 0; un32Cnt <un32Len; un32Cnt++, un32FlashOffset+=4, pun32Data++)
    {
        eRet |= FMC_SelfWrite(eFmcID, un32FlashOffset, pun32Data);
        if (eRet)
        {
            return HAL_ERR_SPECIFIC;
        }
    }

    return HAL_ERR_OK;
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_FMC_GetCRC(FMC_ID_e eFmcID, FMC_CRC_MODE_e eCrcMode, uint32_t un32FlashAddr, uint32_t un32Len, uint32_t *pun32CrCResult)
{
#if (FMC_FEATURE_CRC == 1)
    int32_t n32FlashSize;
    HAL_ERR_e eRet;

    if (eFmcID == FMC_ID_CFMC)
    {
        n32FlashSize = s_tFmcCB.tGeometry.tCflash.un32Size;
    }
    else
    {
        n32FlashSize = s_tFmcCB.tGeometry.tDflash.un32Size;
    }

    if (un32FlashAddr + un32Len > n32FlashSize)
    {
        return HAL_ERR_PARAMETER;
    }

    /* Make up word alinged Byte addressing */
    un32FlashAddr = un32FlashAddr & ~(0x3);
    eRet = FMC_GetCRC(eFmcID, eCrcMode, un32FlashAddr, un32Len, pun32CrCResult);
    return eRet;
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

#endif /* !EXTRN_FPA_CFMC && !EXTRN_FPA_DFMC */

RAMFUNC HAL_ERR_e HAL_CFMC_SetMultiBankConfig(bool bRequestMultiBank)
{
#if (FMC_FEATURE_CFMC_BANK_SWITCH == 1)
    CFMC_SetMultiBankConfig(bRequestMultiBank);
    return HAL_ERR_OK;
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

RAMFUNC HAL_ERR_e HAL_CFMC_GetBankSwitchStatus(CFMC_BANK_ID_e *peBootBank, bool *pbBankSwitchDone, CFMC_BANK_ID_e *peActiveBank)
{
#if (FMC_FEATURE_CFMC_BANK_SWITCH == 1)
    HAL_ERR_e eRet;

    eRet = CFMC_GetBankSwitchStatus(peBootBank, pbBankSwitchDone, peActiveBank);
    return eRet;
#else
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

RAMFUNC HAL_ERR_e HAL_CFMC_SetActiveBank(CFMC_BANK_ID_e eBankID)
{
#if (FMC_FEATURE_CFMC_BANK_SWITCH == 1)
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
#if (FMC_FEATURE_CFMC_BANK_SWITCH == 1)
    uint32_t un32Len;

    /* STEP1. Erase Bank switching command (boot-rom command) area in UserInfo */
    CFMC_EraseUserInfo(FMC_FEATURE_CFMC_BANK_SWITCH_CMD_OFFSET, FMC_PAGE_ERASE_MODE, PRV_CMFC_USERINFO_BANK_SWITCH_ID);

    /* STEP2. Write command into Bank switching command (boot-rom command) area in UserInfo */
    if (eBankID  == CFMC_BANK_A)
    {
        un32Len = sizeof(s_aun32BootARomCMD);
        un32Len = un32Len >> 2;
        CFMC_WriteToUserInfo(FMC_FEATURE_CFMC_BANK_SWITCH_CMD_OFFSET, (uint32_t *)&s_aun32BootARomCMD, un32Len, PRV_CMFC_USERINFO_BANK_SWITCH_ID);
    }
    else if (eBankID  == CFMC_BANK_B)
    {
        un32Len = sizeof(s_aun32BootBRomCMD);
        un32Len = un32Len >> 2;
        CFMC_WriteToUserInfo(FMC_FEATURE_CFMC_BANK_SWITCH_CMD_OFFSET, (uint32_t *)&s_aun32BootBRomCMD, un32Len, PRV_CMFC_USERINFO_BANK_SWITCH_ID);
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

#endif /* _CFMC && _DFMC */

