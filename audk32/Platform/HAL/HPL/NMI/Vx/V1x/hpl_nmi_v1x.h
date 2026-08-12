/**
 *******************************************************************************
 * @file        hpl_nmi_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed SCU NMI 
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HPL_NMI_V1X_H_
#define _HPL_NMI_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define NMI_MAX_NUM                                   CONFIG_SCU_NMI_MAX_COUNT

#if (CONFIG_SCU_VER_EXT == 0)

#if (CONFIG_SCU_VER_MINOR == 0) || (CONFIG_SCU_VER_MINOR == 1) || (CONFIG_SCU_VER_MINOR == 3) \
    || (CONFIG_SCU_VER_MINOR == 4)
#include "hpl_nmi_v_01_00_0x.h"
#elif (CONFIG_SCU_VER_MINOR == 2)
#include "hpl_nmi_v_01_00_02.h"
#else
#error "define CONFIG_SCU_VER_MINOR of V-type SCU at config_xxx.h"
#endif

#else
#error "define CONFIG_SCU_VER_EXT of V-type SCU at config_xxx.h"
#endif

HAL_ERR_e NMI_SetEnable(P_NMI_INTR_e eNmi, bool bEnable)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type*)SCU_REG_BASE;

    switch(eNmi)
    {
        case P_NMI_INTR_LVD:
            SET_SCU_NMI_LVD_IER_EN(ptScu, bEnable);
            break;
        case P_NMI_INTR_MCLK:
            SET_SCU_NMI_MCLK_IER_EN(ptScu, bEnable);
            break;
        case P_NMI_INTR_WDT:
            SET_SCU_NMI_WDT_IER_EN(ptScu, bEnable);
            break;
#if defined(SCUNMI_FEATURE_TIMER3_BLNK)
        case P_NMI_INTR_TIMER3_BLNK:
            SET_SCU_NMI_TIMER3_BLNK_IER_EN(ptScu, bEnable);
            break;
#endif
#if defined(SCUNMI_FEATURE_CMP)
        case P_NMI_INTR_CMP:
            SET_SCU_NMI_CMP_IER_EN(ptScu, bEnable);
            break;
#endif
#if defined(SCUNMI_FEATURE_FLASH_SWAP)
        case P_NMI_INTR_FLASH_SWAP:
            SET_SCU_NMI_FLASH_SWAP_IER_EN(ptScu, bEnable);
            break;
#endif
#if defined(SCUNMI_FEATURE_MPWM)
        case NMI_INTR_OVP0:
            SET_SCU_NMI_OVP0_IER_EN(ptScu, bEnable);
            break;
        case NMI_INTR_PROT0:
            SET_SCU_NMI_PROT0_IER_EN(ptScu, bEnable);
            break;
        case NMI_INTR_OVP1:
            SET_SCU_NMI_OVP1_IER_EN(ptScu, bEnable);
            break;
        case NMI_INTR_PROT1:
            SET_SCU_NMI_PROT1_IER_EN(ptScu, bEnable);
#endif
#if defined(CONFIG_NMI_ANY_INTERRUPT)
        case NMI_INTR_SOURCE:
            SET_SCU_NMI_EN(ptScu, bEnable);
#endif
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    return eErr;
}

#endif /* _HPL_NMI_V1X_H_ */
