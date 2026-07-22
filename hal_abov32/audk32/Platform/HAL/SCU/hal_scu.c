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
#include "hal_scu_prv.h"
#include "hpl_nmi.h"

void HAL_SCU_SetSWReset(void)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;
    SET_SCU_SRCR_SW_RST(ptScu, SCU_SOFTWARE_RST);
}

HAL_ERR_e HAL_SCU_SetReset(SCU_RST_e eRst, bool bEnable)
{
#if defined(SCU_FEATURE_VX_RESET_ENABLE)
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;

    switch(eRst)
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
}

HAL_ERR_e HAL_SCU_GetResetEvent(SCU_RST_e eRst, bool *pbEvent)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;

    switch(eRst)
    {
        case SCU_RST_SW:
            if(GET_SCU_RSER_SW_EN(ptScu))
            {
                *pbEvent = GET_SCU_RSSR_SW_FLAG(ptScu);
                SET_SCU_RSSR_SW_FLAG(ptScu, true);
            } 
            break;
        case SCU_RST_CPU:
            if(GET_SCU_RSER_CPU_EN(ptScu))
            {
                *pbEvent = GET_SCU_RSSR_CPU_FLAG(ptScu);
                SET_SCU_RSSR_CPU_FLAG(ptScu, true);
            } 
            break;
        case SCU_RST_EXT_PIN:
            if(GET_SCU_RSER_EXTPIN_EN(ptScu))
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
            if(GET_SCU_RSER_CPU_LOCKUP_EN(ptScu))
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
}

HAL_ERR_e HAL_SCU_GetBootPinLevel(bool *pbLevel)
{
#if defined(SCU_FEATURE_BOOT_PIN_LEVEL)
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;
    *pbLevel = GET_SCU_BOOTPIN_ST(ptScu);
    return HAL_ERR_OK;
#else
    (void)pbLevel;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_SCU_SetResetPinDebounce(uint8_t un8Count, bool bEnable)
{
#if defined(SCU_FEATURE_RESET_PIN_DEBOUNCE)
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;
    SET_SCU_RSTDB_CNT(ptScu, un8Count);
    SET_SCU_RSTDB_EN(ptScu, bEnable);
    return HAL_ERR_OK;
#elif defined(SCU_FEATURE_PCU_RESET_PIN_DEBOUNCE)
    SCU_PCU_RSTDBCR_Type *ptRstdbcr = (SCU_PCU_RSTDBCR_Type *)SCU_PCU_RSTDBCR_BASE;
    SET_SCU_PCU_RSTDB_CNT(ptRstdbcr, un8Count);
    SET_SCU_PCU_RSTDB_EN(ptRstdbcr, bEnable);
    return HAL_ERR_OK;
#else
    (void)un8Count;
    (void)bEnable;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}
