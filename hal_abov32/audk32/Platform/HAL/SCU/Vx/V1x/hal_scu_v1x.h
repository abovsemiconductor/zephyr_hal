/**
 *******************************************************************************
 * @file        hal_scu_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed SCU
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_SCU_V1X_H_
#define _HAL_SCU_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */

#if (CONFIG_SCU_VER_EXT == 0)

#if (CONFIG_SCU_VER_MINOR == 0)
#include "hal_scu_v_01_00_00.h"
#elif (CONFIG_SCU_VER_MINOR == 1)
#include "hal_scu_v_01_00_01.h"
#elif (CONFIG_SCU_VER_MINOR == 2)
#include "hal_scu_v_01_00_02.h"
#elif (CONFIG_SCU_VER_MINOR == 3)
#include "hal_scu_v_01_00_03.h"
#elif (CONFIG_SCU_VER_MINOR == 4)
#include "hal_scu_v_01_00_04.h"
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
        case P_SCUCLK_SRC_HSI:
             return SCUCLK_MCLKSEL_PLL_BYPASS;
        case P_SCUCLK_SRC_LSI:
             return SCUCLK_MCLKSEL_LSI;
        case P_SCUCLK_SRC_LSE:
             return SCUCLK_MCLKSEL_LSE;
        case P_SCUCLK_SRC_PLL:
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
    SET_SCU_FMC_ACCESS_EN(ptCfmc);
    SET_SCU_CFMC_LATENCY(ptCfmc, SCU_FMC_DEFAULT_LATENCY);
    SET_SCU_FMC_ACCESS_DIS(ptCfmc);
#if defined(SCU_DFMC_ADDR)
    SET_SCU_FMC_ACCESS_EN(ptDfmc);
    SET_SCU_DFMC_LATENCY(ptDfmc, SCU_FMC_DEFAULT_LATENCY);
    SET_SCU_FMC_ACCESS_DIS(ptDfmc);
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
#if (CONFIG_SCU_VER_MINOR == 1)
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
#endif

    SET_SCU_FMC_ACCESS_EN(ptCfmc);
    SET_SCU_CFMC_LATENCY(ptCfmc, un8Wait);
    SET_SCU_FMC_ACCESS_DIS(ptCfmc);
#if defined(SCU_DFMC_ADDR)
    SET_SCU_FMC_ACCESS_EN(ptDfmc);
    SET_SCU_DFMC_LATENCY(ptDfmc, un8Wait);
    SET_SCU_FMC_ACCESS_DIS(ptDfmc);
#endif

}

static __inline HAL_ERR_e SCUCLK_SetMClkDiv(P_SCUCLK_SRC_e eMClk, P_SCUCLK_DIV_e eMClkDiv)
{
    SCUCLK_Type *ptScuClk = (SCUCLK_Type *)SCUCLK_REG_BASE;
    uint32_t un32Data = 0;

    un32Data = (true << SCUCLK_SRC_ENABLE_POS) | (eMClkDiv & SCUCLK_SRC_MODE_MSK);

    switch(eMClk)
    {
        case P_SCUCLK_SRC_HSE:
            SET_SCU_CSCR_HSE(ptScuClk, un32Data);
            SystemCoreClock=HSE_CLOCK/SCUCLK_EXPO2((uint8_t)eMClkDiv);
            break;
        case P_SCUCLK_SRC_HSI:
            SET_SCU_CSCR_HSI(ptScuClk, un32Data);
            SystemCoreClock=HSI_CLOCK/SCUCLK_EXPO2((uint8_t)eMClkDiv);
            break;
        case P_SCUCLK_SRC_LSI:
            SET_SCU_CSCR_LSI(ptScuClk, un32Data);
            SystemCoreClock=LSI_CLOCK/SCUCLK_EXPO2((uint8_t)eMClkDiv);
            break;
        case P_SCUCLK_SRC_LSE:
            SET_SCU_CSCR_LSE(ptScuClk, un32Data);
            SystemCoreClock=LSE_CLOCK/SCUCLK_EXPO2((uint8_t)eMClkDiv);
            break;
        default:
            break;
    }

    return HAL_ERR_OK;
}

static __inline HAL_ERR_e SCUCLK_SetMClk(P_SCUCLK_SRC_e eMClk, P_SCUCLK_DIV_e ePreMClkDiv, 
                                         P_SCUCLK_DIV_e ePostMClkDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCUCLK_Type *ptScuClk = (SCUCLK_Type *)SCUCLK_REG_BASE;
    uint32_t un32Data = 0;

    (void)ePostMClkDiv;

    un32Data = (true << SCUCLK_SRC_ENABLE_POS) | (ePreMClkDiv & SCUCLK_SRC_MODE_MSK);

    switch(eMClk)
    {
        case P_SCUCLK_SRC_HSE:
            SET_SCU_CSCR_HSE(ptScuClk, un32Data);
            SystemCoreClock = HSE_CLOCK / SCUCLK_EXPO2((uint8_t)ePreMClkDiv);
            un32Data = SCUCLK_MCLKSEL_PLL_BYPASS;
            break;
        case P_SCUCLK_SRC_HSI:
            SET_SCU_CSCR_HSI(ptScuClk, un32Data);
            SystemCoreClock = HSI_CLOCK / SCUCLK_EXPO2((uint8_t)ePreMClkDiv);
            un32Data = SCUCLK_MCLKSEL_PLL_BYPASS;
            break;
        case P_SCUCLK_SRC_LSI:
            SET_SCU_CSCR_LSI(ptScuClk, un32Data);
            SystemCoreClock = LSI_CLOCK / SCUCLK_EXPO2((uint8_t)ePreMClkDiv);
            un32Data = SCUCLK_MCLKSEL_LSI;
            break;
        case P_SCUCLK_SRC_LSE:
            SET_SCU_CSCR_LSE(ptScuClk, un32Data);
            SystemCoreClock = LSE_CLOCK / SCUCLK_EXPO2((uint8_t)ePreMClkDiv);
            un32Data = SCUCLK_MCLKSEL_LSE;
#if defined (SCU_FEATURE_HAS_LSE_STABLE_DELAY)
            SystemDelayMS(SCU_LSE_STABLE_DELAY_MS);
#endif
            break;
        case P_SCUCLK_SRC_PLL:
            un32Data = SCUCLK_MCLKSEL_PLL;
            break; 
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    /* Update the value of SystemPeriClock */
    SystemPeriClock = SystemCoreClock;

    /* Flash wait default value */
    SCUCLK_SetFlashLatencyDefault();

    SET_SCU_SCCR_MCLKSEL(ptScuClk, un32Data);

    return eErr;
}

static __inline HAL_ERR_e SCUCLK_SetClkOut(P_SCUCLK_SRC_e eSrc, uint8_t un8OutputDiv)
{
    SCUCLK_Type *ptScuClk = (SCUCLK_Type *)SCUCLK_REG_BASE;

    (void)eSrc;

    if(un8OutputDiv > SCUCLK_CLK_OUTPUT_DIV_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    SET_SCU_COR_CLKODIV(ptScuClk, un8OutputDiv);

    return HAL_ERR_OK;
}

static __inline HAL_ERR_e SCUCLK_SetPLLSrcDiv(P_SCUCLK_PLL_SRC_e eSrcClk, P_SCUCLK_DIV_e eSrcDiv, uint32_t *pun32PllClk)

{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCUCLK_Type *ptScuClk = (SCUCLK_Type *)SCUCLK_REG_BASE;
    uint32_t un32Data = 0;

    un32Data = (true << SCUCLK_SRC_ENABLE_POS) | (eSrcDiv & SCUCLK_SRC_MODE_MSK);

    switch(eSrcClk)
    {
        case P_SCUCLK_PLL_SRC_HSE:
            SET_SCU_CSCR_HSE(ptScuClk, un32Data);
            *pun32PllClk = HSE_CLOCK/SCUCLK_EXPO2((uint8_t)eSrcDiv);
            break;
        case P_SCUCLK_PLL_SRC_HSI:
            SET_SCU_CSCR_HSI(ptScuClk, un32Data);
            *pun32PllClk = HSI_CLOCK/SCUCLK_EXPO2((uint8_t)eSrcDiv);
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

static __inline void SCULVD_GetResetSrcEvent(bool *pbEvent)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;
    if(GET_SCU_LVD_RST_SRC_EN(ptScu))
    {
        *pbEvent = GET_SCU_LVD_RST_SRC_FLAG(ptScu);
    }
    else
    {
        *pbEvent = false;
    }

    SET_SCU_LVD_RST_SRC_FLAG(ptScu, true);
}

#endif /* _HAL_SCH_V1X_H_ */
