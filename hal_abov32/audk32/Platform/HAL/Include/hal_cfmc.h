/**
 *******************************************************************************
 * @file        hal_cfmc.h
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

/**
 * @addtogroup  HAL HAL (Hardware Abstraction Layer)
 * @{
 * @defgroup    HAL_CFMC CFMC
 * @{
 * @brief       Code Flash Memory Controller
 */

#ifndef _HAL_CFMC_H_
#define _HAL_CFMC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"
#include "abov_config.h"

/**
 * @brief Flash geometric information (physical structure and parameter)
 */
typedef CONFIG_FLASH_INFO_t CFMC_GEOMETRY_t;

/**
 * @brief Configuration for flash controller
 */
typedef struct
{
    uint8_t un8Latency;                     /**< Operation latency of flash controller */
    uint8_t un8TimeOut;                     /**< Flash write timeout. Check manual to see if your target device supports or not */
    bool    bReqCrcInit;                    /**< Flag to check CRC init was done or not but deprecated */
    bool    bReqCrcEnable;                  /**< Flag to check CRC is enabled or not currently but deprecataed */
} CFMC_CONFIG_t;

/**
 * @brief Erase modes of flash controller which can be avaiable device to device
 */
typedef enum
{
    CFMC_CHIP_ERASE_MODE,                   /**< Erase whole code flash area at a time */
    CFMC_PAGE_ERASE_MODE,                   /**< Erase a sector which is aligned to Page size */
    CFMC_1KB_ERASE_MODE,                    /**< Erase a sector which is aligned to 1KB */
    CFMC_2KB_ERASE_MODE = 4,                /**< Erase a sector which is aligned to 2KB */
    CFMC_4KB_ERASE_MODE = 8,                /**< Erase a sector which is aligned to 4KB */
} CFMC_ERASE_MODE_e;

/**
 * @brief Modes of CRC module in flash controller which is under develop.\n
          Independent CRC module is preferred to CRC module in side of flash controller.
 */
typedef enum
{
    CFMC_CRC_BACKGROUND_MODE,
    CFMC_CRC_BURST_MODE,
    CFMC_CRC_BACKGROUND_IRQ_MODE,
    CFMC_CRC_BURST_IRQ_MODE,
} CFMC_CRC_MODE_e;

/**
 * @brief Read protection mode.
 */
typedef enum
{
    CFMC_RD_PROTECT_LEVEL0,                 /**< Read Mode which cannot be available device by device */
    CFMC_RD_PROTECT_LEVEL1,                 /**< Flash access is prohbitted debug or Boot operation mode */
    CFMC_RD_PROTECT_LEVEL2,                 /**< Flash access is prohbitted Boot operation mode or debug operation mode is not allowed */
    CFMC_RD_PROTECT_PASSWD,
    CFMC_RD_PROTECT_LEVEL1_PASSWD = CFMC_RD_PROTECT_PASSWD,  /**< Level 1 + Password */
    CFMC_RD_PROTECT_LEVEL2_PASSWD,                           /**< Level 2 + Password */
} CFMC_RD_PROTECT_LEVEL_e;

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
 * @brief Configuration for read protection.
 */
typedef struct
{
    CFMC_RD_PROTECT_LEVEL_e eRdProtectLevel;     /**< Read protection mode */
    uint32_t un32RegisteredPasswd;               /**< Password for Password mode */
} CFMC_RD_PROTECT_CONFIG_t;

/**
 *******************************************************************************
 * @brief       Initialization for CMFC only.\n
 *              (API resides at code_section_on_ram section on RAM).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CFMC_Init(void);

/**
 *******************************************************************************
 * @brief       Get flash gemetric information detected at run-time.\n
 *              (API resides at code_section_on_ram section on RAM).
 * @return      ::CFMC_GEOMETRY_t : Structure of flash geometric
 ******************************************************************************/
CFMC_GEOMETRY_t HAL_CFMC_GetGeometry(void);

/**
 *******************************************************************************
 * @brief       Set flash controller up.\n
 *              (API resides at code_section_on_ram section on RAM).
 * @param[in]   *ptReqConfig : flash controller configuration reuqested by user.
 *              Only latency is avaiable for now.
 * @return      void : None
 ******************************************************************************/
void HAL_CFMC_SetConfig(CFMC_CONFIG_t *ptReqConfig);

/**
 *******************************************************************************
 * @brief       Set up cache configuration of code flash controller up.\n
 *              (API resides at code_section_on_ram section on RAM).
 * @param[in]   bRequestEnable : Cache enable reqeust by user.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CFMC_SetCache(bool bRequestEnable);

/**
 *******************************************************************************
 * @brief       Activate Write Protection on code flash area only.\n
 *              (API resides at code_section_on_ram section on RAM).
 * @param[in]   un32FlashOffset : Flash offset of code flash to protect.
 * @param[in]   un32Len : Write protection size from un32FlashOffset.
 * @param[in]   bRequestLock : Write protection request by user.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CFMC_SetWriteProtect(uint32_t un32FlashOffset, uint32_t un32Len, bool bRequestLock);

/**
 *******************************************************************************
 * @brief       Activate Write Protection on Bootblock only.
 *              (API resides at code_section_on_ram section on RAM).
 * @param[in]   bRequestLock : Write protection request by user.
 * @return      void : None
 ******************************************************************************/
void HAL_CFMC_SetWriteProtectBootBlk(bool bRequestLock);

/**
 *******************************************************************************
 * @brief       Activate Read Protection in run-time.
 *              (API resides at code_section_on_ram section on RAM).
 * @param[in]   tRdProtectConfig : Read protection level.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CFMC_SetReadProtect(CFMC_RD_PROTECT_CONFIG_t tRdProtectConfig);

/**
 *******************************************************************************
 * @brief       Erase flash area (system or code)\n
 *              (API resides at code_section_on_ram section on RAM).
 * @param[in]   un32FlashOffset : Flash offset from base of code flash.\n
 *              It should be alinged to sector size.
 * @param[in]   eEraseMode : Flash erase mode
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CFMC_Erase(uint32_t un32FlashOffset, CFMC_ERASE_MODE_e eEraseMode);

/**
 *******************************************************************************
 * @brief       Write data onto flash area (system or code)\n
 *              (API resides at code_section_on_ram section on RAM).
 * @param[in]   un32FlashOffset : Flash offset from base of code flash to write data
 * @param[in]   *pun8Data : Flash address of data to write.
 *              It is a byte addressing.
 * @param[in]   un32Len : data size to write.
 *              It is a byte addressing.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CFMC_Write(uint32_t un32FlashOffset, uint8_t *pun8Data, uint32_t un32Len);

/**
 *******************************************************************************
 * @brief       Erase flash area (system or code) without CPU intervention.\n
 *              (API resides at code flash itself).
 * @param[in]   un32FlashOffset : Flash offset from base of code flash to erase
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CFMC_SelfErase(uint32_t un32FlashOffset);

/**
 *******************************************************************************
 * @brief       Write data onto flash (system or code) without CPU intervention.\n
 *              (API resides at code flash itself).
 * @param[in]   un32FlashOffset : Flash offset from base of code flash to write data
 * @param[in]   *pun8Data : Flash address of data to write.
 *              It is a byte addressing.
 * @param[in]   un32Len : data size to write.
 *              It is a byte addressing.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_CFMC_SelfWrite(uint32_t un32FlashOffset, uint8_t *pun8Data, uint32_t un32Len);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_CFMC_H_ */

/** @} */
/** @} */
