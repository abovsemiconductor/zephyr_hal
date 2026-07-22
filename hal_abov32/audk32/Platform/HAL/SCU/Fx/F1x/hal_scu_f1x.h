/**
 *******************************************************************************
 * @file        hal_scu_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed SCU
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_SCU_F1X_H_
#define _HAL_SCU_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */

#if (CONFIG_SCU_VER_EXT == 0)

#if (CONFIG_SCU_VER_MINOR == 0)
#include "hal_scu_f_01_00_00.h"
#elif (CONFIG_SCU_VER_MINOR == 1)
#include "hal_scu_f_01_00_01.h"
#else
#error "define CONFIG_SCU_VER_MINOR of F-type SCU at config_xxx.h"
#endif

#elif (CONFIG_SCU_VER_EXT == 1)

#if (CONFIG_SCU_VER_MINOR == 0)
#include "hal_scu_f_01_01_00.h"
#else
#error "define CONFIG_SCU_VER_MINOR of F-type SCU at config_xxx.h"
#endif

#else
#error "define CONFIG_SCU_VER_EXT of F-type SCU at config_xxx.h"
#endif

#define SCUCLK_CLK_OUTPUT_DIV_MAX                     8

static __inline uint32_t PRV_SCUCLK_GetMClk(P_SCUCLK_SRC_e eMClk)
{
    switch(eMClk)
    {
        case P_SCUCLK_SRC_HSE:
             return SCUCLK_MCLKSEL_HSE;
        case P_SCUCLK_SRC_HSI:
             return SCUCLK_MCLKSEL_HSI;
        case P_SCUCLK_SRC_WDT:
             return SCUCLK_MCLKSEL_WDT;
        case P_SCUCLK_SRC_LSE:
             return SCUCLK_MCLKSEL_LSE;
        default:
             break;
    }

    return 0xFF;
}

static __inline void SCUCLK_SetFlashLatency(uint32_t un32CoreClock)
{
    (void)un32CoreClock;
}

static __inline HAL_ERR_e SCUCLK_SetMClk(P_SCUCLK_SRC_e eMClk, P_SCUCLK_DIV_e ePreMClkDiv, 
                                         P_SCUCLK_DIV_e ePostMClkDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCUCLK_Type *ptScuClk = (SCUCLK_Type *)SCUCLK_REG_BASE;
    uint32_t un32Data = 0;
    uint8_t un8PClkDiv = 0;

    switch(eMClk)
    {
        case P_SCUCLK_SRC_HSE:
            SET_SCU_CSCR_HSE(ptScuClk, true);
            SystemCoreClock = HSE_CLOCK;
            un32Data = SCUCLK_MCLKSEL_HSE;
            break;
        case P_SCUCLK_SRC_HSI:
            SET_SCU_CSCR_HSI_SEL(ptScuClk, (uint8_t)ePreMClkDiv);
            SET_SCU_CSCR_HSI(ptScuClk, true);
            SystemCoreClock = HSI_CLOCK / SCUCLK_EXPO2((uint8_t)ePreMClkDiv);
            un32Data = SCUCLK_MCLKSEL_HSI;
            break;
        case P_SCUCLK_SRC_LSI:
            SET_SCU_CSCR_LSI(ptScuClk, true);

            SystemCoreClock = LSI_CLOCK;
            un32Data = SCUCLK_MCLKSEL_WDT;
            break;
        case P_SCUCLK_SRC_LSE:
            SET_SCU_CSCR_LSE(ptScuClk, true);
            SystemCoreClock = LSE_CLOCK;
            un32Data = SCUCLK_MCLKSEL_LSE;
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    /* Post Divider */
    SET_SCU_SCCR_HCLKDIV(ptScuClk, SCUCLK_HDIV((uint8_t)ePostMClkDiv));

    /* Update the value of SystemCoreClock with the post clock divider */
    SystemCoreClock = SystemCoreClock / SCUCLK_EXPO2((uint8_t)ePostMClkDiv);

    /* Update the value of SystemPeriClock with the peripheral clock divider */
    un8PClkDiv = GET_SCU_SCCR_PCLKDIV(ptScuClk);
    SystemPeriClock = SystemCoreClock / SCUCLK_EXPO2((uint8_t)un8PClkDiv);

    SET_SCU_SCCR_MCLKSEL(ptScuClk, un32Data);

    return eErr;
}

static __inline HAL_ERR_e SCUCLK_SetClkOut(P_SCUCLK_SRC_e eSrc, uint8_t un8OutputDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCUCLK_Type *ptScuClk = (SCUCLK_Type *)SCUCLK_REG_BASE;
    uint8_t un8Data = 0;

    if(un8OutputDiv >= SCUCLK_CLK_OUTPUT_DIV_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    SET_SCU_COR_CLKODIV(ptScuClk, un8OutputDiv);

    switch(eSrc)
    {
        case P_SCUCLK_SRC_MCLK:
            un8Data = SCUCLK_OUTPUT_INCLK_MCLK;
            break;
        case P_SCUCLK_SRC_WDT:
            un8Data = SCUCLK_OUTPUT_INCLK_WDT;
            break;
        case P_SCUCLK_SRC_HSI:
            un8Data = SCUCLK_OUTPUT_INCLK_HSI;
            break;
        case P_SCUCLK_SRC_HCLK:
            un8Data = SCUCLK_OUTPUT_INCLK_HCLK;
            break;
        case P_SCUCLK_SRC_PCLK:
            un8Data = SCUCLK_OUTPUT_INCLK_PCLK;
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
     }

     SET_SCU_COR_CLKOINSEL(ptScuClk, un8Data);

     return eErr;
}

static __inline void SCULVD_SetWkupSrc(bool bEnable)
{
#if 0
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;
    SET_SCU_LVD_WKUP_EN(ptScu, bEnable);
#endif
}

static __inline void SCULVD_GetWkupEvent(bool *pbEvent)
{
#if 0
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;

    uint8_t un8Prev = GET_SCU_LVD_PREVMODE(ptScu);

    if(GET_SCU_LVD_WKUP_EN(ptScu))
    {
        if(un8Prev == SCU_PREVMODE_SLEEP || un8Prev == SCU_PREVMODE_DEEPSLEEP)
        {
            *pbEvent = GET_SCU_LVD_WKUP_FLAG(ptScu);
        }
    }
    else
    {
        *pbEvent = false;
    }
#endif
}

static __inline void SCULVD_SetResetSrc(bool bEnable)
{
    (void)bEnable;
}

static __inline void SCULVD_GetResetSrcEvent(bool *pbEvent)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;

    *pbEvent = GET_SCU_LVD_RST_SRC_FLAG(ptScu);

    SET_SCU_LVD_RST_SRC_FLAG(ptScu, true);
}

#if defined(SCU_FEATURE_LVI_CLOCK_ENABLE)
static __inline void SCULVD_SetScuEnable(bool bEnable)
{
    SCUCLK_Type *ptScuClk = (SCUCLK_Type *)SCUCLK_REG_BASE;
    SET_SCU_LVD_PCER(ptScuClk, bEnable);
}
#endif

#if defined(SCU_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void SCU_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, (uint8_t)eIrq, bEnable);
}
#endif
#if defined(SCU_FEATURE_DEEPSLEEP_SUB_MODE)
static __inline void SCUPWR_SetPostProcess(void)
{
    SET_SCU_PMU_DS1_PERI_DIS();
}
#endif

#endif /* _HAL_SCH_F1X_H_ */
