/**
 *******************************************************************************
 * @file        hal_ebi.c
 * @author      ABOV R&D Division
 * @brief       EBI Driver
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

#if defined(_EBI)
#include "hal_ebi.h"
#include "hal_ebi_prv.h"

static uint32_t s_un32EbiResMap = 0;

static EBI_Type *PRV_EBI_GetReg(P_EBI_ID_e eId)
{
    return EBI_GetReg((P_EBI_ID_e)eId);
}

static HAL_ERR_e PRV_EBI_SetScuEnable(P_EBI_ID_e eId, bool bEnable)
{
    return EBI_SetScuEnable((P_EBI_ID_e)eId, bEnable);
}

HAL_ERR_e HAL_EBI_Init(EBI_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= EBI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(s_un32EbiResMap == 0)
    {
        eErr = PRV_EBI_SetScuEnable((P_EBI_ID_e)eId, (uint32_t)true);
        if(eErr != HAL_ERR_OK)
        {
            return eErr;
        }
    }

    s_un32EbiResMap |= (1UL << (uint32_t)eId);

    return eErr;
}

HAL_ERR_e HAL_EBI_Uninit(EBI_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= EBI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    s_un32EbiResMap &= ~(1UL << (uint32_t)eId);

    if(s_un32EbiResMap == 0)
    {
        eErr = PRV_EBI_SetScuEnable((P_EBI_ID_e)eId, (uint32_t)false);
        if(eErr != HAL_ERR_OK)
        {
            return eErr;
        }
    }

    return eErr;
}

HAL_ERR_e HAL_EBI_SetConfig(EBI_ID_e eId, EBI_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    EBI_Type *ptEcd;
    uint32_t un32AddrReg, un32CfgReg;

    if((uint32_t)eId >= EBI_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptEcd = PRV_EBI_GetReg((P_EBI_ID_e)eId);

    un32CfgReg = 0 \
               | SET_EBI_CR_NORMWAIT_POS(ptCfg->un8NormWait) \
               | SET_EBI_CR_MWIDTH_POS(ptCfg->eMemBusWidth) \
               | SET_EBI_CR_AH_POS(ptCfg->eKeepCycle) \
               | SET_EBI_CR_BLEN_POS(ptCfg->eByteLaneSel) \
               | SET_EBI_CR_IOE_POS(ptCfg->eAddressType) \
               | SET_EBI_CR_EWP_POS(ptCfg->tExtReq.eWaitPolarity) \
               | SET_EBI_CR_EWEN_POS(ptCfg->tExtReq.bEnable) \
               | SET_EBI_CR_PREIDL_POS(ptCfg->tExtCycle.eFallCycle) \
               | SET_EBI_CR_IDLE_POS(ptCfg->tExtCycle.eIdleCycle) \
               ;

    un32AddrReg = (uint32_t)(GET_EBI_CR_BASE_ADDR(ptEcd) + (uint32_t)eId);
    SET_EBI_CR_REG(un32AddrReg, un32CfgReg);

    return eErr;
}

#endif /* _EBI */
