/**
 *******************************************************************************
 * @file        hal_fmc_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for FMC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_FMC_PRV_H_
#define _HAL_FMC_PRV_H_

#include "abov_config.h"

/* Define UserInfo areas */
typedef enum
{
    PRV_CMFC_USERINFO_READ_PROTECT_ID,
    PRV_CMFC_USERINFO_BANK_SWITCH_ID
} PRV_CMFC_USERINFO_ID_e;

typedef enum
{
    EVENT_FMC_ERR_READ_PROTECTION,
    EVENT_FMC_ERR_WRITE_SEQUENCE,
    EVENT_FMC_ERR_SYSTEM_FLASH,
    EVENT_FMC_ERR_FLASH_PROTECT,
    EVENT_FMC_ERR_SYSTEM_FLASH_LOCK,
    EVENT_FMC_ERR_FLASH_LOCK,
    EVENT_FMC_CRC_DONE,
    EVENT_FMC_WRITE_DONE,
    EVENT_FMC_CRC_BUSY,
    EVENT_FMC_WRITE_BUSY,
} FMC_EVENT_e;

typedef struct
{
    pfnFMC_IRQ_Handler_t  pfnHandler;
    void                  *pContext;
    CONFIG_FLASH_INFO_t   tGeometry;
} FMC_CTRL_BLK_t;

/* Define IP version */
#if (CONFIG_FMC_VER_VENDOR == 'V')

#if (CONFIG_FMC_VER_MAJOR == 1)
#include "Vx/V1x/hal_fmc_v1x.h"
#elif (CONFIG_FMC_VER_MAJOR == 2)
#include "Vx/V2x/hal_fmc_v2x.h"
#elif (CONFIG_FMC_VER_MAJOR == 3)
#include "Vx/V3x/hal_fmc_v3x.h"
#else
#error "define CONFIG_FMC_VER_MAJOR of V-type FMC at config_xxx.h"
#endif

#elif (CONFIG_FMC_VER_VENDOR == 'F')

#if (CONFIG_FMC_VER_MAJOR == 1)
#include "Fx/F1x/hal_fmc_f1x.h"
#else
#error "define CONFIG_FMC_VER_MAJOR of F-type FMC at config_xxx.h"
#endif

#else
#error "define CONFIG_FMC_VER_VENDOR of FMC at config_xxx.h"
#endif

#endif /* _HAL_FMC_PRV_H_ */

