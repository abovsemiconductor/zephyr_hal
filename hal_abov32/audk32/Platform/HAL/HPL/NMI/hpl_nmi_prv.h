/**
 *******************************************************************************
 * @file        hpl_nmi_prv.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for SCU NMI
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HPL_NMI_PRV_H_
#define _HPL_NMI_PRV_H_

#include "abov_config.h"

typedef enum
{
    P_NMI_INTR_LVD,
    P_NMI_INTR_MCLK,
    P_NMI_INTR_WDT,
    P_NMI_INTR_OVP0,
    P_NMI_INTR_TIMER3_BLNK = P_NMI_INTR_OVP0,
    P_NMI_INTR_PROT0,
    P_NMI_INTR_CMP = P_NMI_INTR_PROT0,
    P_NMI_INTR_OVP1,
    P_NMI_INTR_FLASH_SWAP = P_NMI_INTR_OVP1,
    P_NMI_INTR_PROT1,
    P_NMI_INTR_SOURCE,
    P_NMI_INTR_MAX
} P_NMI_INTR_e;

#if (CONFIG_SCU_VER_VENDOR == 'F')

#if (CONFIG_SCU_VER_MAJOR == 1)
#include "Fx/F1x/hpl_nmi_f1x.h"
#elif (CONFIG_SCU_VER_MAJOR == 2)
#include "Fx/F2x/hpl_nmi_f2x.h"
#else
#error "define CONFIG_SCU_VER_MAJOR of F-type SCU at config_xxx.h"
#endif

#elif (CONFIG_SCU_VER_VENDOR == 'V')

#if (CONFIG_SCU_VER_MAJOR == 1)
#include "Vx/V1x/hpl_nmi_v1x.h"
#elif (CONFIG_SCU_VER_MAJOR == 2)
#include "Vx/V2x/hpl_nmi_v2x.h"
#elif (CONFIG_SCU_VER_MAJOR == 4)
#include "Vx/V4x/hpl_nmi_v4x.h"
#else /* CONFIG_SCU_VER_MAJOR */
#error "define CONFIG_SCU_VER_MAJOR of V-type SCU at config_xxx.h"
#endif

#else /* CONFIG_SCU_VER_VENDOR */
#error "define CONFIG_SCU_VER_VENDOR of SCU at config_xxx.h"
#endif

#endif /* _HPL_NMI_PRV_H_ */
