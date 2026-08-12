/**
 *******************************************************************************
 * @file        hal_lcd_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed LCD
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_LCD_F1X_H_
#define _HAL_LCD_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define LCD_CH_NUM                                    CONFIG_LCD_MAX_COUNT
#define LCD_COM_CH_NUM                                CONFIG_LCD_MAX_COM_CH_NUM
#define LCD_SEG_CH_NUM                                CONFIG_LCD_MAX_SEG_CH_NUM
#define LCD_VLC_CH_NUM                                CONFIG_LCD_MAX_VLC_CH_NUM

#if (CONFIG_LCD_VER_EXT == 0)

#if (CONFIG_LCD_VER_MINOR == 0)
#include "hal_lcd_f_01_00_00.h"
#elif (CONFIG_LCD_VER_MINOR == 1)
#include "hal_lcd_f_01_00_01.h"
#elif (CONFIG_LCD_VER_MINOR == 2)
#include "hal_lcd_f_01_00_02.h"
#elif (CONFIG_LCD_VER_MINOR == 3)
#include "hal_lcd_f_01_00_03.h"
#elif (CONFIG_LCD_VER_MINOR == 4)
#include "hal_lcd_f_01_00_04.h"
#else
#error "define CONFIG_LCD_VER_MINOR of F-type LCD at config_xxx.h"
#endif

#else
#error "define CONFIG_LCD_VER_EXT of F-type LCD at config_xxx.h"
#endif

static __inline LCD_Type *LCD_GetReg(P_LCD_ID_e eId)
{
        return (LCD_Type *)(LCD_REG_BASE + (uint32_t)eId);
}

static __inline HAL_ERR_e LCD_SetScuEnable(P_LCD_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_LCD_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_LCD_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_LCD_PCER(ptScu, (uint32_t)eId, un32Enable);

    return HAL_ERR_OK;
}

static __inline HAL_ERR_e LCD_SetClk(P_LCD_ID_e eId, P_LCD_CLK_e eClk, P_LCD_CLK_MCCR_e eMccrClk, uint8_t un8ClkDiv)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_LCD_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_LCD_PPCLKSR(ptScu, eClk);

    if(eClk == P_LCD_CLK_MCCR)
    {
        SET_SCU_LCD_MCCR_SEL(ptScu, SCU_MCCR_MODE(eMccrClk));
        SET_SCU_LCD_MCCR_DIV(ptScu, un8ClkDiv);
    }

    return HAL_ERR_OK;
}

#endif /* _HAL_LCD_F1X_H_ */
