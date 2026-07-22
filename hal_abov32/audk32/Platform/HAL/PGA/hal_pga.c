/**
 *******************************************************************************
 * @file        hal_pga.c
 * @author      ABOV R&D Division
 * @brief       Programmable Gain Amplifier
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

#if defined(_PGA)
#include "hal_pga.h"
#include "hal_pga_prv.h"

static PGA_Type *PRV_PGA_GetReg(P_PGA_ID_e eId)
{
    return PGA_GetReg((P_PGA_ID_e)eId);
}

static HAL_ERR_e PRV_PGA_SetScuEnable(P_PGA_ID_e eId, bool bEnable)
{
    return PGA_SetScuEnable((P_PGA_ID_e)eId, bEnable);
}

HAL_ERR_e HAL_PGA_Init(PGA_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= PGA_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_PGA_SetScuEnable((P_PGA_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_PGA_Uninit(PGA_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= PGA_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_PGA_SetScuEnable((P_PGA_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_PGA_SetAmp(PGA_ID_e eId, PGA_OUT_CURR_e eCurr, bool bEnable)
{
    PGA_Type *ptAes;

    if((uint32_t)eId >= PGA_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAes = PRV_PGA_GetReg((P_PGA_ID_e)eId);

    SET_PGA_CR_EN(ptAes, bEnable);
    if(bEnable == true)
    {
        SET_PGA_CR_AMP_CURR_SEL(ptAes, eCurr);
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_PGA_SetGain(PGA_ID_e eId, PGA_GAIN_e eGain, bool bFollow)
{
    PGA_Type *ptAes;

    if((uint32_t)eId >= PGA_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAes = PRV_PGA_GetReg((P_PGA_ID_e)eId);

    SET_PGA_CR_GAIN_EN(ptAes, bFollow);
    if(bFollow == false)
    {
        SET_PGA_CR_GAIN_SEL(ptAes, eGain);
    }

    return HAL_ERR_OK;
}

#endif /* _PGA */
