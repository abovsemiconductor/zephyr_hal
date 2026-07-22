/**
 *******************************************************************************
 * @file        hal_lcd.c
 * @author      ABOV R&D Division
 * @brief       LCD Driver
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

#if defined(_LCD)
#include "hal_lcd.h"
#include "hal_lcd_prv.h"

static LCD_Type *PRV_LCD_GetReg(P_LCD_ID_e eId)
{
    return LCD_GetReg((P_LCD_ID_e)eId);
}

static HAL_ERR_e PRV_LCD_SetScuEnable(P_LCD_ID_e eId, bool bEnable)
{
    return LCD_SetScuEnable((P_LCD_ID_e)eId, bEnable);
}

HAL_ERR_e HAL_LCD_Init(LCD_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= LCD_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_LCD_SetScuEnable((P_LCD_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }
    return eErr;
}

HAL_ERR_e HAL_LCD_Uninit(LCD_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= LCD_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_LCD_SetScuEnable((P_LCD_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    return eErr;
}

HAL_ERR_e HAL_LCD_SetClkConfig(LCD_ID_e eId, LCD_CLK_CFG_t *ptClkCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LCD_Type *ptLcd;

    if((uint32_t)eId >= LCD_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = LCD_SetClk((P_LCD_ID_e)eId, (P_LCD_CLK_e)ptClkCfg->eClk,
            (P_LCD_CLK_MCCR_e)ptClkCfg->eMccr, ptClkCfg->un8MccrDiv);

    ptLcd = PRV_LCD_GetReg((P_LCD_ID_e)eId);
    SET_LCD_CR_LCLKDIV(ptLcd, ptClkCfg->ePreDiv);

    return eErr;
}

HAL_ERR_e HAL_LCD_SetConfig(LCD_ID_e eId, LCD_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LCD_Type *ptLcd;

    if((uint32_t)eId >= LCD_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLcd = PRV_LCD_GetReg((P_LCD_ID_e)eId);

    SET_LCD_CR_DUTYBIAS(ptLcd, ptCfg->eDutyBias);

    SET_LCD_BCCR_CONTRAST(ptLcd, ptCfg->tContrast.bEnable);
    if(ptCfg->tContrast.bEnable == true)
    {
        SET_LCD_BCCR_VLC0VOLT(ptLcd, ptCfg->tContrast.eVlc0Volt);
    }

    SET_LCD_BCCR_AUTOBIAS(ptLcd, ptCfg->tAutoBias.bEnable);
    if(ptCfg->tAutoBias.bEnable == true)
    {
        SET_LCD_BCCR_BMASEL(ptLcd, ptCfg->tAutoBias.eBiasModeA);
    }

#if defined(LCD_FEATURE_EXT_BIAS)
    SET_LCD_BSSR_DRVBIAS(ptLcd, ptCfg->eDriveBias);
#endif

    switch(ptCfg->eDriveBias)
    {
        case LCD_BIAS_INTERNAL:
            SET_LCD_CR_INTBIASR(ptLcd, ptCfg->uType.tInt.eIntBiasResistor);
            break;
#if defined(LCD_FEATURE_EXT_BIAS)
        case LCD_BIAS_EXTERNAL:
            SET_LCD_BSSR_EXTBIASEN(ptLcd, true);
            SET_LCD_BSSR_EXTPATH(ptLcd, true);
            SET_LCD_BSSR_VLC3EN(ptLcd, ptCfg->uType.tExt.bVLC3Enable);
            SET_LCD_BSSR_VLC2EN(ptLcd, ptCfg->uType.tExt.bVLC2Enable); 
            SET_LCD_BSSR_VLC1EN(ptLcd, ptCfg->uType.tExt.bVLC1Enable);
            SET_LCD_BSSR_VLC0EN(ptLcd, ptCfg->uType.tExt.bVLC0Enable);
            break;
#endif
        default:
            eErr = HAL_ERR_PARAMETER; 
            break;
    }

    return eErr;
}

HAL_ERR_e HAL_LCD_Start(LCD_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LCD_Type *ptLcd;

    if((uint32_t)eId >= LCD_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLcd = LCD_GetReg((P_LCD_ID_e)eId);

    SET_LCD_CR_DISPLAY(ptLcd, true);

    return eErr;
}

HAL_ERR_e HAL_LCD_Stop(LCD_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LCD_Type *ptLcd;

    if((uint32_t)eId >= LCD_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLcd = LCD_GetReg((P_LCD_ID_e)eId);

    SET_LCD_CR_DISPLAY(ptLcd, false);

    return eErr;
}

HAL_ERR_e HAL_LCD_SetData(LCD_ID_e eId, LCD_DATA_t *ptLcdData, uint8_t un8SegCnt)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LCD_Type *ptLcd;
    uint8_t  *pn8AddrReg;
    uint8_t un8Cnt = 0;

    if((uint32_t)eId >= LCD_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLcd = LCD_GetReg((P_LCD_ID_e)eId);

    for(un8Cnt = 0; un8Cnt < un8SegCnt; un8Cnt++)
    {
        if(ptLcdData[un8Cnt].un8SegNum <= LCD_SEG_CH_NUM)
        {
#if (LCD_UNUSE_SEG_CH_NUM > 0)
            if ((ptLcdData[un8Cnt].un8SegNum == LCD_UNUSE_SEG_CH_0) || (ptLcdData[un8Cnt].un8SegNum == LCD_UNUSE_SEG_CH_1))
            {
                eErr = HAL_ERR_NOT_SUPPORTED;
                break;
            }
#endif
            pn8AddrReg = (uint8_t *)((uint32_t)GET_LCD_DATA_BASE_ADDR(ptLcd));
            pn8AddrReg[ptLcdData[un8Cnt].un8SegNum] = ptLcdData[un8Cnt].un8Data;
        }
        else
        {
            eErr = HAL_ERR_NOT_SUPPORTED;
            break;
        }
    }

    return eErr; 
}

HAL_ERR_e HAL_LCD_GetData(LCD_ID_e eId, LCD_DATA_t *ptLcdData, uint8_t un8SegCnt)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LCD_Type *ptLcd;
    uint8_t  *pn8AddrReg;
    uint8_t un8Cnt = 0;

    if((uint32_t)eId >= LCD_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLcd = LCD_GetReg((P_LCD_ID_e)eId);

    for(un8Cnt = 0; un8Cnt < un8SegCnt; un8Cnt++)
    {
        if(ptLcdData[un8Cnt].un8SegNum <= LCD_SEG_CH_NUM)
        {
#if (LCD_UNUSE_SEG_CH_NUM > 0)
            if ((ptLcdData[un8Cnt].un8SegNum == LCD_UNUSE_SEG_CH_0) || (ptLcdData[un8Cnt].un8SegNum == LCD_UNUSE_SEG_CH_1))
            {
                eErr = HAL_ERR_NOT_SUPPORTED;
                break;
            }
#endif
            pn8AddrReg = (uint8_t *)((uint32_t)GET_LCD_DATA_BASE_ADDR(ptLcd));
            ptLcdData[un8Cnt].un8Data = pn8AddrReg[ptLcdData[un8Cnt].un8SegNum];
        }
        else
        {
            eErr = HAL_ERR_NOT_SUPPORTED;
            break;
        }
    }

    return eErr; 
}

#endif /* _LCD */
