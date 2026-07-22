/**
 *******************************************************************************
 * @file        hal_hsicmu.c
 * @author      ABOV R&D Division
 * @brief       Cyclic Redundancy Check
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

#if defined(_HSICMU)
#include "hal_hsicmu.h"
#include "hal_hsicmu_prv.h"

typedef struct
{
    pfnHSICMU_IRQ_Handler_t  pfnHandler;
    void                    *pContext;
} HSICMU_CTRL_BLK_t;

static HSICMU_CTRL_BLK_t s_tHcb[HSICMU_CH_NUM];

static HSICMU_Type *PRV_HSICMU_GetReg(P_HSICMU_ID_e eId)
{
    return HSICMU_GetReg((P_HSICMU_ID_e)eId);
}

static HAL_ERR_e PRV_HSICMU_SetScuEnable(P_HSICMU_ID_e eId, bool bEnable)
{
    return HSICMU_SetScuEnable((P_HSICMU_ID_e)eId, bEnable);
}

HAL_ERR_e HAL_HSICMU_Init(HSICMU_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= HSICMU_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_HSICMU_SetScuEnable((P_HSICMU_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tHcb[(uint32_t)eId], 0x00, sizeof(HSICMU_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_HSICMU_Uninit(HSICMU_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= HSICMU_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_HSICMU_SetScuEnable((P_HSICMU_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tHcb[(uint32_t)eId], 0x00, sizeof(HSICMU_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_HSICMU_SetConfig(HSICMU_ID_e eId, HSICMU_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    HSICMU_Type *ptHsicmu;

    if((uint32_t)eId >= HSICMU_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptHsicmu = PRV_HSICMU_GetReg((P_HSICMU_ID_e)eId);

    ptHsicmu->CFG = 0x00
                | (ptCfg->un32Reload << HSICMU_CFG_RELOAD_Pos)
                | (ptCfg->ePreDiv << HSICMU_CFG_PREDIV_Pos)
                | (ptCfg->eSyncDiv << HSICMU_CFG_SYNCDIV_Pos)
                | (ptCfg->eSyncSrc << HSICMU_CFG_SYNCSRC_Pos) 
                | (ptCfg->eSyncPol << HSICMU_CFG_SESYNCPOL_Pos)
                | (1 << HSICMU_CFG_AC_EN_Pos);

    ptHsicmu->THR = ptCfg->un16ErrRate;

    SET_HSICMU_CR_TRIMVALUE(ptHsicmu, true);
    SET_HSICMU_CR_AUTOTRIM_EN(ptHsicmu, true);

    return eErr;
}

HAL_ERR_e HAL_HSICMU_Start(HSICMU_ID_e eId)
{
    HSICMU_Type *ptHsicmu;

    if((uint32_t)eId >= HSICMU_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptHsicmu = PRV_HSICMU_GetReg((P_HSICMU_ID_e)eId);

    SET_HSICMU_CR_SW_SYNC(ptHsicmu, true);
    SET_HSICMU_CR_SYNC_START(ptHsicmu, true);
    SET_HSICMU_CR_TIMER(ptHsicmu, true);

    SET_HSICMU_CR_EN(ptHsicmu, true);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_HSICMU_Stop(HSICMU_ID_e eId)
{
    HSICMU_Type *ptHsicmu;

    if((uint32_t)eId >= HSICMU_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptHsicmu = PRV_HSICMU_GetReg((P_HSICMU_ID_e)eId);

    SET_HSICMU_CR_SW_SYNC(ptHsicmu, false);
    SET_HSICMU_CR_SYNC_START(ptHsicmu, false);
    SET_HSICMU_CR_TIMER(ptHsicmu, false);

    SET_HSICMU_CR_EN(ptHsicmu, false);

    return HAL_ERR_OK;
}

#endif /* _HSICMU */
