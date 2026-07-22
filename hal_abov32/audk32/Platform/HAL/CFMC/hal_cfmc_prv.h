/**
 *******************************************************************************
 * @file        hal_cfmc_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for CFMC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_CFMC_PRV_H_
#define _HAL_CFMC_PRV_H_

#include "abov_config.h"

/* Define UserInfo areas */
typedef enum
{
    PRV_CMFC_USERINFO_READ_PROTECT_ID,
    PRV_CMFC_USERINFO_BANK_SWITCH_ID
} PRV_CMFC_USERINFO_ID_e;

typedef enum
{
    EVENT_CFMC_ERR_READ_PROTECTION,
    EVENT_CFMC_ERR_WRITE_SEQUENCE,
    EVENT_CFMC_ERR_SYSTEM_FLASH,
    EVENT_CFMC_ERR_FLASH_PROTECT,
    EVENT_CFMC_ERR_SYSTEM_FLASH_LOCK,
    EVENT_CFMC_ERR_FLASH_LOCK,
    EVENT_CFMC_CRC_DONE,
    EVENT_CFMC_WRITE_DONE,
    EVENT_CFMC_CRC_BUSY,
    EVENT_CFMC_WRITE_BUSY,
} CFMC_EVENT_e;

/* Define IP version */
#if (CONFIG_CFMC_VER_VENDOR == 'V')

#if (CONFIG_CFMC_VER_MAJOR == 2)
#include "Vx/V2x/hal_cfmc_v2x.h"
#elif (CONFIG_CFMC_VER_MAJOR == 3)
#include "Vx/V3x/hal_cfmc_v3x.h"
#else
#error "define CONFIG_CFMC_VER_MAJOR of V-type CFMC at config_xxx.h"
#endif

#elif (CONFIG_CFMC_VER_VENDOR == 'F')
#if (CONFIG_CFMC_VER_MAJOR == 1)
#include "Fx/F1x/hal_cfmc_f1x.h"
#else
#error "define CONFIG_CFMC_VER_MAJOR of F-type CFMC at config_xxx.h"
#endif

#else
#error "define CONFIG_CFMC_VER_VENDOR of CFMC at config_xxx.h"
#endif

#endif /* _HAL_CFMC_PRV_H_ */

