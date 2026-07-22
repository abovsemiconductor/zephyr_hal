/**
 *******************************************************************************
 * @file        hal_scu_v2x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V2x typed SCU
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_SCU_V2X_H_
#define _HAL_SCU_V2X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */

#if (CONFIG_SCU_VER_EXT == 0)

#if (CONFIG_SCU_VER_MINOR == 0)
#include "hal_scu_v_02_00_00.h"
#elif (CONFIG_SCU_VER_MINOR == 1)
#include "hal_scu_v_02_00_01.h"
#elif (CONFIG_SCU_VER_MINOR == 2)
#include "hal_scu_v_02_00_02.h"
#elif (CONFIG_SCU_VER_MINOR == 3)
#include "hal_scu_v_02_00_03.h"
#elif (CONFIG_SCU_VER_MINOR == 4)
#include "hal_scu_v_02_00_04.h"
#elif (CONFIG_SCU_VER_MINOR == 5)
#include "hal_scu_v_02_00_05.h"
#elif (CONFIG_SCU_VER_MINOR == 6)
#include "hal_scu_v_02_00_06.h"
#else
#error "define CONFIG_SCU_VER_MINOR of V-type SCU at config_xxx.h"
#endif

#else
#error "define CONFIG_SCU_VER_EXT of V-type SCU at config_xxx.h"
#endif

#define SCUCLK_CLK_OUTPUT_DIV_MAX                     15

static __inline uint32_t PRV_SCUCLK_GetMClk(P_SCUCLK_SRC_e eMClk)
{
    switch(eMClk)
    {
        case P_SCUCLK_SRC_HSE:
             return SCUCLK_MCLKSEL_HSE;
        case P_SCUCLK_SRC_HSI:
             return SCUCLK_MCLKSEL_HSI;
        case P_SCUCLK_SRC_LSI:
             return SCUCLK_MCLKSEL_LSI;
        case P_SCUCLK_SRC_LSE:
             return SCUCLK_MCLKSEL_LSE;
        case P_SCUCLK_SRC_PLL_HSE:
        case P_SCUCLK_SRC_PLL_HSI:
             return SCUCLK_MCLKSEL_PLL;
        default:
             break;
    }
    return 0xFF;
}

static __inline void SCUCLK_SetFlashLatencyDefault(void)
{
    CFMC_Type *ptCfmc = (CFMC_Type *)SCU_CFMC_ADDR;
#if defined(SCU_DFMC_ADDR)
    DFMC_Type *ptDfmc = (DFMC_Type *)SCU_DFMC_ADDR;
#endif

    SET_SCU_CFMC_LATENCY(ptCfmc, SCU_FMC_DEFAULT_LATENCY);
#if defined(SCU_DFMC_ADDR)
    SET_SCU_DFMC_LATENCY(ptDfmc, SCU_FMC_DEFAULT_LATENCY);
#endif
}

static __inline void SCUCLK_SetFlashLatency(uint32_t un32CoreClock)
{
    CFMC_Type *ptCfmc = (CFMC_Type *)SCU_CFMC_ADDR;
#if defined(SCU_DFMC_ADDR)
    DFMC_Type *ptDfmc = (DFMC_Type *)SCU_DFMC_ADDR;
#endif

    uint8_t un8Wait = 0;

    if(un32CoreClock <= SCUCLK_FMC_CLK_WAIT_0)
    {
        un8Wait = 0;
    }
    else if(un32CoreClock <= SCUCLK_FMC_CLK_WAIT_1)
    {
        un8Wait = 1;
    }
    else if(un32CoreClock <= SCUCLK_FMC_CLK_WAIT_2)
    {
        un8Wait = 2;
    }
    else if(un32CoreClock <= SCUCLK_FMC_CLK_WAIT_3)
    {
        un8Wait = 3;
    }
    else if(un32CoreClock <= SCUCLK_FMC_CLK_WAIT_4)
    {
        un8Wait = 4;
    }
    else
    {
        un8Wait = 5;
    }

    SET_SCU_CFMC_LATENCY(ptCfmc, un8Wait);
#if defined(SCU_DFMC_ADDR)
    SET_SCU_DFMC_LATENCY(ptDfmc, un8Wait);
#endif
}


static __inline HAL_ERR_e SCUCLK_SetMClk(P_SCUCLK_SRC_e eMClk, P_SCUCLK_DIV_e ePreMClkDiv, 
                                         P_SCUCLK_DIV_e ePostMClkDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCUCLK_Type *ptScuClk = (SCUCLK_Type *)SCUCLK_REG_BASE;
    uint32_t un32Data = 0;
    uint8_t un8PClkDiv = 0;

    (void)ePreMClkDiv;

    switch(eMClk)
    {
        case P_SCUCLK_SRC_HSE:
            SET_SCU_CSCR_HSE(ptScuClk, true);
            SystemCoreClock = HSE_CLOCK / SCUCLK_EXPO2((uint8_t)ePostMClkDiv);
            un32Data = SCUCLK_MCLKSEL_HSE;
            break;
        case P_SCUCLK_SRC_HSI:
            SET_SCU_CSCR_HSI(ptScuClk, true);
            SystemCoreClock = HSI_CLOCK / SCUCLK_EXPO2((uint8_t)ePostMClkDiv);
            un32Data = SCUCLK_MCLKSEL_HSI;
            break;
        case P_SCUCLK_SRC_LSI:
            SET_SCU_CSCR_LSI(ptScuClk, true);
            SystemCoreClock = LSI_CLOCK / SCUCLK_EXPO2((uint8_t)ePostMClkDiv);
            un32Data = SCUCLK_MCLKSEL_LSI;
            break;
#if defined(SCU_FEATURE_UNSUPPORT_LSE)
#else
        case P_SCUCLK_SRC_LSE:
            SET_SCU_CSCR_LSE(ptScuClk, true);
            SystemCoreClock = LSE_CLOCK / SCUCLK_EXPO2((uint8_t)ePostMClkDiv);
            un32Data = SCUCLK_MCLKSEL_LSE;
            break;
#endif
        case P_SCUCLK_SRC_PLL:
            un32Data = SCUCLK_MCLKSEL_PLL;
            break; 
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    SET_SCU_SCCR_HCLKDIV(ptScuClk, (uint8_t)ePostMClkDiv);

    /* Update the value of SystemPeriClock with the peripheral clock divider */
    un8PClkDiv = GET_SCU_SCCR_PCLKDIV(ptScuClk);
    SystemPeriClock = SystemCoreClock / SCUCLK_EXPO2((uint8_t)un8PClkDiv);

    /* Flash wait default value */
    SCUCLK_SetFlashLatencyDefault();

    SET_SCU_SCCR_MCLKSEL(ptScuClk, un32Data);

    return eErr;
}

static __inline HAL_ERR_e SCUCLK_SetClkOut(P_SCUCLK_SRC_e eSrc, uint8_t un8OutputDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCUCLK_Type *ptScuClk = (SCUCLK_Type *)SCUCLK_REG_BASE;
    uint8_t un8Data = 0;

    if(un8OutputDiv > SCUCLK_CLK_OUTPUT_DIV_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    SET_SCU_COR_CLKODIV(ptScuClk, un8OutputDiv);

#if defined(SCU_FEATURE_SELECT_OUTPUT_CLK)
    switch(eSrc)
    {
        case P_SCUCLK_SRC_MCLK:
            un8Data = SCUCLK_OUTPUT_INCLK_MCLK;
            break;
        case P_SCUCLK_SRC_LSI:
            un8Data = SCUCLK_OUTPUT_INCLK_LSI;
            break;
        case P_SCUCLK_SRC_LSE:
            un8Data = SCUCLK_OUTPUT_INCLK_LSE;
            break;
        case P_SCUCLK_SRC_HSI:
            un8Data = SCUCLK_OUTPUT_INCLK_HSI;
            break;
        case P_SCUCLK_SRC_HSE:
            un8Data = SCUCLK_OUTPUT_INCLK_HSE;
            break;
        case P_SCUCLK_SRC_PLL:
            un8Data = SCUCLK_OUTPUT_INCLK_PLL;
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
     }

     SET_SCU_COR_CLKOSEL(ptScuClk, un8Data);
#endif

     return eErr;
}

static __inline HAL_ERR_e SCUCLK_SetPLLSrcDiv(P_SCUCLK_PLL_SRC_e eSrcClk, P_SCUCLK_DIV_e eSrcDiv, uint32_t *pun32PllClk)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCUCLK_Type *ptScuClk = (SCUCLK_Type *)SCUCLK_REG_BASE;
    uint32_t un32Data = 0, un32Div = 0;

    SET_SCU_SCCR_PLLPREDIV(ptScuClk, eSrcDiv);

    switch(eSrcDiv)
    {
        case P_SCUCLK_DIV_NONE:
            un32Div = 1;
            break;
        case P_SCUCLK_DIV_2:
            un32Div = 2;
            break;
        case P_SCUCLK_DIV_4:
            un32Div = 4;
            break;
        case P_SCUCLK_DIV_8:
            un32Div = 8;
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    un32Data = (true << SCUCLK_SRC_ENABLE_POS);

    switch(eSrcClk)
    {
        case P_SCUCLK_PLL_SRC_HSE:
            SET_SCU_CSCR_HSE(ptScuClk, un32Data);
            *pun32PllClk = HSE_CLOCK / un32Div;
            break;
        case P_SCUCLK_PLL_SRC_HSI:
            SET_SCU_CSCR_HSI(ptScuClk, un32Data);
            *pun32PllClk = HSI_CLOCK / un32Div;
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    return eErr;
}

static __inline void SCULVD_SetWkupSrc(bool bEnable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;
    SET_SCU_LVD_WKUP_EN(ptScu, bEnable);
}

static __inline void SCULVD_GetWkupEvent(bool *pbEvent)
{
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
}

static __inline void SCULVD_SetResetSrc(bool bEnable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;
    SET_SCU_LVD_RST_SRC_EN(ptScu, bEnable);
}

static __inline void SCULVD_GetResetSrcEvent(bool *pbEnable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;
    if(GET_SCU_LVD_RST_SRC_EN(ptScu))
    {
        *pbEnable = GET_SCU_LVD_RST_SRC_FLAG(ptScu);
    }
    else
    {
        *pbEnable = false;
    }

    SET_SCU_LVD_RST_SRC_FLAG(ptScu, true);
}

#endif /* _HAL_SCH_V2X_H_ */
