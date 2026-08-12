/**
 *******************************************************************************
 * @file        hal_scu.c
 * @author      ABOV R&D Division
 * @brief       System Control Unit
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
#include "hal_scu.h"
#include "hll_scu.h"
#include "hal_scu_prv.h"
#include "hpl_nmi.h"

void HAL_SCU_SetSWReset(void)
{
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HLL_SCU_SetSWReset();
#else
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;
    SET_SCU_SRCR_SW_RST(ptScu, SCU_SOFTWARE_RST);
#endif
}

HAL_ERR_e HAL_SCU_SetReset(SCU_RST_e eRst, bool bEnable)
{
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
#if defined(SCU_FEATURE_VX_RESET_ENABLE)
    HAL_ERR_e eErr = HAL_ERR_OK;

    switch (eRst)
    {
        case SCU_RST_SW:
            HLL_SCU_SetSWResetEnable(bEnable);
            break;

        case SCU_RST_CPU:
            HLL_SCU_SetCPUResetEnable(bEnable);
            break;

        case SCU_RST_EXT_PIN:
            HLL_SCU_SetExtPinResetEnable(bEnable);
            break;

#if defined(SCU_FEATURE_RST_CPU_LOCKUP)
        case SCU_RST_CPU_LOCKUP:
            HLL_SCU_SetCPULockupResetEnable(bEnable);
            break;
#endif
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    return eErr;
#elif defined(SCU_FEATURE_FX_RESET_ENABLE)
    (void)eRst;
    (void)bEnable;
    return HAL_ERR_OK;
#else
    (void)eRst;
    (void)bEnable;
    return HAL_ERR_NOT_SUPPORTED;
#endif

#else /* AUDK32_FEATURE_HLL_SUPPORT */
#if defined(SCU_FEATURE_VX_RESET_ENABLE)
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;

    switch (eRst)
    {
        case SCU_RST_SW:
            SET_SCU_RSER_SW_EN(ptScu, bEnable);
            break;

        case SCU_RST_CPU:
            SET_SCU_RSER_CPU_EN(ptScu, bEnable);
            break;

        case SCU_RST_EXT_PIN:
            SET_SCU_RSER_EXTPIN_EN(ptScu, bEnable);
            break;

#if defined(SCU_FEATURE_RST_CPU_LOCKUP)
        case SCU_RST_CPU_LOCKUP:
            SET_SCU_RSER_CPU_LOCKUP_EN(ptScu, bEnable);
            break;
#endif

        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    return eErr;

#elif defined(SCU_FEATURE_FX_RESET_ENABLE)
    (void)eRst;
    (void)bEnable;
    return HAL_ERR_OK;
#else
    (void)eRst;
    (void)bEnable;
    return HAL_ERR_NOT_SUPPORTED;
#endif

#endif /* AUDK32_FEATURE_HLL_SUPPORT */
}

HAL_ERR_e HAL_SCU_GetResetEvent(SCU_RST_e eRst, bool *pbEvent)
{
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
    HAL_ERR_e eErr = HAL_ERR_OK;

    switch (eRst)
    {
        case SCU_RST_SW:
            if (HLL_SCU_GetSWResetEnable())
            {
                *pbEvent = HLL_SCU_GetSWResetEvent();
                HLL_SCU_SetSWResetEvent(true);
            }
            break;

        case SCU_RST_CPU:
            if (HLL_SCU_GetCPUResetEnable())
            {
                *pbEvent = HLL_SCU_GetCPUResetEvent();
                HLL_SCU_SetCPUResetEvent(true);
            }
            break;

        case SCU_RST_EXT_PIN:
            if (HLL_SCU_GetExtPinResetEnable())
            {
                *pbEvent = HLL_SCU_GetExtPinResetEvent();
                HLL_SCU_SetExtPinResetEvent(true);
            }
            break;

        case SCU_RST_POR:
            *pbEvent = HLL_SCU_GetPORResetEvent();
            break;

#if defined(SCU_FEATURE_RST_CPU_LOCKUP)
        case SCU_RST_CPU_LOCKUP:
            if (HLL_SCU_GetCPULockupResetEnable())
            {
                *pbEvent = HLL_SCU_GetCPULockupResetEvent();
                HLL_SCU_SetCPULockupResetEvent(true);
            }
            break;
#endif

        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    return eErr;
#else
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;

    switch (eRst)
    {
        case SCU_RST_SW:
            if (GET_SCU_RSER_SW_EN(ptScu))
            {
                *pbEvent = GET_SCU_RSSR_SW_FLAG(ptScu);
                SET_SCU_RSSR_SW_FLAG(ptScu, true);
            }
            break;

        case SCU_RST_CPU:
            if (GET_SCU_RSER_CPU_EN(ptScu))
            {
                *pbEvent = GET_SCU_RSSR_CPU_FLAG(ptScu);
                SET_SCU_RSSR_CPU_FLAG(ptScu, true);
            }
            break;

        case SCU_RST_EXT_PIN:
            if (GET_SCU_RSER_EXTPIN_EN(ptScu))
            {
                *pbEvent = GET_SCU_RSSR_EXTPIN_FLAG(ptScu);
                SET_SCU_RSSR_EXTPIN_FLAG(ptScu, true);
            }
            break;

        case SCU_RST_POR:
            *pbEvent = GET_SCU_RSSR_POR_FLAG(ptScu);
            break;

#if defined(SCU_FEATURE_RST_CPU_LOCKUP)
        case SCU_RST_CPU_LOCKUP:
            if (GET_SCU_RSER_CPU_LOCKUP_EN(ptScu))
            {
                *pbEvent = GET_SCU_RSSR_CPU_LOCKUP_FLAG(ptScu);
                SET_SCU_RSSR_CPU_LOCKUP_FLAG(ptScu, true);
            }
            break;
#endif

        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    return eErr;
#endif
}

HAL_ERR_e HAL_SCU_GetBootPinLevel(bool *pbLevel)
{
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
#if defined(SCU_FEATURE_BOOT_PIN_LEVEL) 
    *pbLevel = HLL_SCU_GetBootPinLevel(); 
    return HAL_ERR_OK; 
#else 
    (void)pbLevel; 
    return HAL_ERR_NOT_SUPPORTED; 
#endif
#else
#if defined(SCU_FEATURE_BOOT_PIN_LEVEL)
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;
    *pbLevel = GET_SCU_BOOTPIN_ST(ptScu);
    return HAL_ERR_OK;
#else
    (void)pbLevel;
    return HAL_ERR_NOT_SUPPORTED;
#endif
#endif
}

HAL_ERR_e HAL_SCU_SetResetPinDebounce(uint8_t un8Count, bool bEnable)
{
#if defined(AUDK32_FEATURE_HLL_SUPPORT)
#if defined(SCU_FEATURE_RESET_PIN_DEBOUNCE)
    HLL_SCU_SetResetPinDebounceCount(un8Count);
    HLL_SCU_SetResetPinDebounceEnable(bEnable);
    return HAL_ERR_OK;
#else
    (void)un8Count;
    (void)bEnable;
    return HAL_ERR_NOT_SUPPORTED;
#endif
#else
#if defined(SCU_FEATURE_RESET_PIN_DEBOUNCE)
    SCUDB_Type *ptScu = (SCUDEB_Type *)SCU_RSTDBCR_BASE;
    SET_SCU_RSTDB_CNT(ptScu, un8Count);
    SET_SCU_RSTDB_EN(ptScu, bEnable);
    return HAL_ERR_OK;
#else
    (void)un8Count;
    (void)bEnable;
    return HAL_ERR_NOT_SUPPORTED;
#endif
#endif
}
