/**
 *******************************************************************************
 * @file        hal_cfmc_f_01_00_00.c
 * @author      ABOV R&D Division
 * @brief       Private Common APIs for ver 01.00.00 typed CFMC
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
#include "hal_cfmc.h"

#if (CONFIG_CFMC_VER_VENDOR == 'F')
#if (CONFIG_CFMC_VER_MAJOR == 1)
#if (CONFIG_CFMC_VER_EXT == 0)
#if (CONFIG_CFMC_VER_MINOR == 1)

#include "hal_cfmc_f_01_00_01.h"

/* Internal variables */
uint32_t g_un32PageBuffer[CFMC_VARIANT_FEATURE_PAGE_WORD_SIZE];


/* Page write only */
RAMFUNC HAL_ERR_e PRV_CFMC_PageWrite(uint32_t un32FlashAddr, uint32_t *pun32Data, bool bIsSystemFlash)
{
    CFMC_Type *ptRegBase = (CFMC_Type *)CFMC_REG_BASE;
    uint32_t *pun32PageBuf = (uint32_t *)un32FlashAddr;
    uint32_t un32State=0xFF;
    uint32_t i;

    SET_CFMC_MR(ptRegBase, true);
    __asm volatile ("cpsid i");

    SET_CFMC_CR_PMODE(ptRegBase, true);

    /* Fire Write Command */
    if (bIsSystemFlash)
    {
        SET_CFMC_CR_PGM(ptRegBase, CFMC_CR_CS_SYSFLASH | CFMC_CR_PAGE_PGM_CMD);
    }
    else
    {
        SET_CFMC_CR_PGM(ptRegBase, CFMC_CR_CS_FLASH | CFMC_CR_PAGE_PGM_CMD);
    }

    if ((GET_CFMC_STR_PMODE1(ptRegBase) != CFMC_PE_MODE_CMD1) || (GET_CFMC_STR_PMODE2(ptRegBase) != CFMC_PE_MODE_CMD2))
    {
        return HAL_ERR_HW;
    }

    for (i = 0; i < CFMC_VARIANT_FEATURE_PAGE_WORD_SIZE; i++)
    {
        /* Write word data to a physical Flash address */
        *pun32PageBuf++ = *pun32Data++;

        /* Check PGM Result status */
        do
        {
            un32State = GET_CFMC_STR_WRBUSY(ptRegBase);
            if (GET_CFMC_STR_ERR(ptRegBase))
            {
                SET_CFMC_STR_ERR(ptRegBase,true);

                /* Come back to Read mode */
                __asm volatile ("cpsie i");

                return HAL_ERR_BUSY;
            }
        } while(un32State);
    }

    /* Come back to Read mode */
    __asm volatile ("cpsie i");

    return HAL_ERR_OK;
}
#endif
#endif
#endif
#endif /* CONFIG_CFMC_VER_VENDOR && CONFIG_CFMC_VER_MAJOR && CONFIG_CFMC_VER_EXT && CONFIG_CFMC_VER_MINOR */

