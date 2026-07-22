/**
 *******************************************************************************
 * @file        hal_fmc.h
 * @author      ABOV R&D Division
 * @brief       Flash Memory Controller
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/**
 * @addtogroup  HAL HAL (Hardware Abstraction Layer)
 * @{
 * @defgroup    HAL_FMC FMC
 * @{
 * @brief       Code/Data Flash Memory Controller
 */

#ifndef _HAL_FMC_H_
#define _HAL_FMC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "abov_config.h"
#include "hal_common.h"


/**
 * @brief Flash controller ID
 */
typedef enum
{
    FMC_ID_CFMC,                            /**< Code flash controller */
    FMC_ID_DFMC                             /**< Data flash controller */
} FMC_ID_e;

/**
 * @brief Flash geometric information (physical structure and parameter)
 */
typedef CONFIG_FLASH_INFO_t FMC_GEOMETRY_t;

/**
 * @brief Configuration for flash controller
 */
typedef struct
{
    uint8_t un8Latency;                     /**< Operation latency of flash controller */
    uint8_t un8TimeOut;                     /**< Flash write timeout. Check manual to see if your target device supports or not */
    bool    bReqCrcInit;                    /**< Flag to check CRC init was done or not but deprecated */
    bool    bReqCrcEnable;                  /**< Flag to check CRC is enabled or not currently but deprecataed */
} FMC_CONFIG_t;

/**
 * @brief Erase modes of flash controller which can be avaiable device to device
 */
typedef enum
{
    FMC_CHIP_ERASE_MODE,                    /**< Erase whole flash area at a time */
    FMC_PAGE_ERASE_MODE,                    /**< Erase a sector which is aligned to Page size */
    FMC_1KB_ERASE_MODE,                     /**< Erase a sector which is aligned to 1KB */
    FMC_2KB_ERASE_MODE = 4,                 /**< Erase a sector which is aligned to 2KB */
    FMC_4KB_ERASE_MODE = 8,                 /**< Erase a sector which is aligned to 4KB */
} FMC_ERASE_MODE_e;

/**
 * @brief Modes of CRC module in flash controller which is under develop.\n
          Independent CRC module is preferred to CRC module in side of flash controller.
 */
typedef enum
{
    FMC_CRC_BACKGROUND_MODE,
    FMC_CRC_BURST_MODE,
    FMC_CRC_BACKGROUND_IRQ_MODE,
    FMC_CRC_BURST_IRQ_MODE,
} FMC_CRC_MODE_e;


/**
 * @brief Read protection mode.
 */
typedef enum
{
    FMC_RD_PROTECT_LEVEL0,                 /**< Read Mode which cannot be available device by device */
    FMC_RD_PROTECT_LEVEL1,                  /**< Flash access is prohbitted debug or Boot operation mode */
    FMC_RD_PROTECT_LEVEL2,                  /**< Flash access is prohbitted Boot operation mode or debug operation mode is not allowed */
    FMC_RD_PROTECT_PASSWD,
    FMC_RD_PROTECT_LEVEL1_PASSWD = FMC_RD_PROTECT_PASSWD,   /**< Level 1 + Password */
    FMC_RD_PROTECT_LEVEL2_PASSWD,                           /**< Level 2 + Password */
} FMC_RD_PROTECT_LEVEL_e;

/**
 * @brief Configuration for read protection.
 */
typedef struct
{
    FMC_RD_PROTECT_LEVEL_e eRdProtectLevel;     /**< Read protection mode */
    uint32_t un32RegisteredPasswd;              /**< Password for Password mode */
} FMC_RD_PROTECT_CONFIG_t;

/**
 * @brief Flash Bank ID
 */
typedef enum
{
    CFMC_BANK_SINGLE,                           /**< FMC is single bank mode or FMC does not support multi-banks */
    CFMC_BANK_A,                                /**< Flash Bank A ID when FMC is configured to multi-banks */
    CFMC_BANK_B                                 /**< Flash Bank B ID when FMC is configured to multi-banks */
} CFMC_BANK_ID_e;

/**
 * @brief Cache mode during FMC is operating.
 */
typedef enum
{
    CFMC_INST_CACHE,                            /**< Instruction cache is enabled */
    CFMC_DATA_CACHE,                            /**< Data cache is enabled */
    CFMC_INST_DATA_CACHE                        /**< Instruction and data cache are enabled */
} CFMC_CACHE_ID_e;

/**
 * @brief IRQ handler but it is deprecated.
 */
typedef void (*pfnFMC_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialization for flash controller (system, code and data flash).\n
 *              (API resides at code_section_on_ram section on RAM).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_FMC_Init(void);

/**
 *******************************************************************************
 * @brief       Get flash (system, code and data) gemetric information detected at run-time.\n
 *              (API resides at code_section_on_ram section on RAM).
 * @return      ::FMC_GEOMETRY_t : Structure of flash geometric
 ******************************************************************************/
FMC_GEOMETRY_t HAL_FMC_GetGeometry(void);

/**
 *******************************************************************************
 * @brief       Set flash (system, code or data) controller up.\n
 *              (API resides at code_section_on_ram section on RAM).
 * @param[in]   eFmcID : Flash controller ID.
 * @param[in]   *ptReqConfig : flash controller configuration reuqested by user.\n
 *              Timeout is not for all devices but latency is available for all devices.
 * @return      void : None
 ******************************************************************************/
void HAL_FMC_SetConfig(FMC_ID_e eFmcID, FMC_CONFIG_t *ptReqConfig);

/**
 *******************************************************************************
 * @brief       Set up cache configuration of code flash controller up.\n
 *              (API resides at code_section_on_ram section on RAM).
 * @param[in]   eCacheID : Cache identifier.
 * @param[in]   bRequestEnable : Cache enable reqeust by user.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CFMC_SetCache(CFMC_CACHE_ID_e eCacheID, bool bRequestEnable);

/**
 *******************************************************************************
 * @brief       Activate Write Protection on flash (code or data).\n
 *              (API resides at code_section_on_ram section on RAM).
 * @param[in]   eFmcID : Flash controller ID.
 * @param[in]   un32FlashOffset : Offset from base of flash (code or data).
 * @param[in]   un32Len : Write protection size from un32FlashOffset.
 * @param[in]   bRequestLock : Write protection request by user.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_FMC_SetWriteProtect(FMC_ID_e eFmcID, uint32_t un32FlashOffset, uint32_t un32Len, bool bRequestLock);

/**
 *******************************************************************************
 * @brief       Activate runtime read-protection.\n
 *              (API resides at code_section_on_ram section on RAM).
 * @param[in]   eFmcID : Flash controller ID.
 * @param[in]   FMC_RD_PROTECT_CONFIG_t : Configuration for read-protection.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_FMC_SetReadProtect(FMC_ID_e eFmcID, FMC_RD_PROTECT_CONFIG_t tRdProtectConfig);

/**
 *******************************************************************************
 * @brief       Activate Write Protection on Bootblock only.
 *              (API resides at code_section_on_ram section on RAM).
 * @param[in]   bRequestLock : Write protection request by user.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CFMC_SetWriteProtectBootBlk(bool bRequestLock);

/**
 *******************************************************************************
 * @brief       Erase flash area (system, code or data)\n
 *              (API resides at code_section_on_ram section on RAM).
 * @param[in]   eFmcID : Flash controller ID.
 * @param[in]   un32FlashOffset : Offset from base of flash (code or data).\n
 *              It should be alinged to sector size.
 * @param[in]   eEraseMode : Flash erase mode
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_FMC_Erase(FMC_ID_e eFmcID, uint32_t un32FlashOffset, FMC_ERASE_MODE_e eEraseMode);

/**
 *******************************************************************************
 * @brief       Write data onto flash area (system, code or data)\n
 *              (API resides at code_section_on_ram section on RAM).
 * @param[in]   eFmcID : Flash controller ID.
 * @param[in]   un32FlashOffset : Offset from base of flash (code or data).\n
 *              It should be alinged to sector size.
 * @param[in]   *pun8Data : Flash address of data to write.
 *              It is a byte addressing.
 * @param[in]   un32Len : data size to write.
 *              It is a byte addressing.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_FMC_Write(FMC_ID_e eFmcID, uint32_t un32FlashOffset, uint8_t *pun8Data, uint32_t un32Len);

/**
 *******************************************************************************
 * @brief       Byte write data onto data flash area only \n
 *              (API resides at code_section_on_ram section on RAM).
 * @param[in]   un32FlashOffset : Offset from base of data flash.\n
 *              It should be alinged to sector size.
 * @param[in]   *pun8Data : Flash address of data to write.
 *              It is a byte addressing.
 * @param[in]   un32Len : data size to write.
 *              It is a byte addressing.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_DFMC_WriteByte(uint32_t un32FlashOffset, uint8_t *pun8Data, uint32_t un32Len);

/**
 *******************************************************************************
 * @brief       Erase flash area (system, code or data) without CPU intervention.\n
 *              (API resides at code flash itself).
 * @param[in]   eFmcID : Flash controller ID.
 * @param[in]   un32FlashOffset : Offset from base of flash (code or data).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_FMC_SelfErase(FMC_ID_e eFmcID, uint32_t un32FlashOffset);

/**
 *******************************************************************************
 * @brief       Write data onto flash (system, code or data) without CPU intervention.\n
 *              (API resides at code flash itself).
 * @param[in]   eFmcID : Flash controller ID.
 * @param[in]   un32FlashOffset : Offset from base of flash (code or data).
 * @param[in]   *pun8Data : Flash address of data to write.
 *              It is a byte addressing.
 * @param[in]   un32Len : data size to write.
 *              It is a byte addressing.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_FMC_SelfWrite(FMC_ID_e eFmcID, uint32_t un32FlashOffset, uint8_t *pun8Data, uint32_t un32Len);

/**
 *******************************************************************************
 * @brief       Divide code flash into multiple banks.
 *              (API resides at code flash itself).
 * @param[in]   bRequestMultiBank : Multibank request by user.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CFMC_SetMultiBankConfig(bool bRequestMultiBank);

/**
 *******************************************************************************
 * @brief       Get bank-siwth information of a target bank in code flash.
 *              (API resides at code flash itself).
 * @param[out]  *peBootBank : which bank is switched from booting.
 * @param[out]  *pbBankSwitchDone : bank switching is done or not.
 * @param[out]  *peActiveBank : which bank is active
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CFMC_GetBankSwitchStatus(CFMC_BANK_ID_e *peBootBank, bool *pbBankSwitchDone, CFMC_BANK_ID_e *peActiveBank);

/**
 *******************************************************************************
 * @brief       Get bank-siwth information of a target bank in code flash.
 *              (API resides at code flash itself).
 * @param[in]   eBankID : Bank ID to be active.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CFMC_SetActiveBank(CFMC_BANK_ID_e eBankID);

/**
 *******************************************************************************
 * @brief       Store Boot Bank information onto a part of UserInfo (System flash)
 *              (API resides at code flash itself).
 * @param[in]   eBankID : Bank ID to be active and stored.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CFMC_SetBootBankOnUserInfo(CFMC_BANK_ID_e eBankID);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_FMC_H_ */

/** @} */
/** @} */
