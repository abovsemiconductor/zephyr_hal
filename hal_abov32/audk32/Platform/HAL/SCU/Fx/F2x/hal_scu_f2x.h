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
#include "hal_scu_f_02_00_00.h"
#else
#error "define CONFIG_SCU_VER_MINOR of F-type SCU at config_xxx.h"
#endif

#elif (CONFIG_SCU_VER_EXT == 1)

#if (CONFIG_SCU_VER_MINOR == 0)
#include "hal_scu_f_02_01_00.h"
#else
#error "define CONFIG_SCU_VER_MINOR of F-type SCU at config_xxx.h"
#endif

#else
#error "define CONFIG_SCU_VER_EXT of F-type SCU at config_xxx.h"
#endif

#define SCUCLK_CLK_OUTPUT_DIV_MAX                     8

#define HLL_SCU_CLK_SET_HSE_ENABLE(Enable)                         \
    SET_SCU_CSCR_HSE(                                              \
        HLL_SCUCLK_REG,                                            \
        (uint32_t)(Enable))

#define HLL_SCU_CLK_SET_HSI_ENABLE(Enable)                         \
    SET_SCU_CSCR_HSI(                                              \
        HLL_SCUCLK_REG,                                            \
        (uint32_t)(Enable))

#define HLL_SCU_CLK_SET_LSI_ENABLE(Enable)                         \
    SET_SCU_CSCR_LSI(                                              \
        HLL_SCUCLK_REG,                                            \
        (uint32_t)(Enable))

#define HLL_SCU_CLK_SET_LSE_ENABLE(Enable)                         \
    SET_SCU_CSCR_LSE(                                              \
        HLL_SCUCLK_REG,                                            \
        (uint32_t)(Enable))

#define HLL_SCU_CLK_SET_HSE_DIVIDER(Div)                           \
    ((void)(Div))

#define HLL_SCU_CLK_SET_HSI_DIVIDER(Div)                           \
    SET_SCU_CSCR_HSI_SEL(                                          \
        HLL_SCUCLK_REG,                                            \
        (uint8_t)(Div))

#define HLL_SCU_CLK_SET_LSI_DIVIDER(Div)                           \
    ((void)(Div))

#define HLL_SCU_CLK_SET_LSE_DIVIDER(Div)                           \
    ((void)(Div))

#define HLL_SCU_CLK_SET_HCLK_DIVIDER(Div)                          \
    SET_SCU_SCCR_HCLKDIV(                                          \
        HLL_SCUCLK_REG,                                            \
        SCUCLK_HDIV((uint8_t)(Div)))

#define HLL_SCU_CLK_GET_PCLK_DIVIDER()                             \
    GET_SCU_SCCR_PCLKDIV(HLL_SCUCLK_REG)

#define HLL_SCU_CLK_SET_MCLK_SOURCE(Source)                        \
    SET_SCU_SCCR_MCLKSEL(                                          \
        HLL_SCUCLK_REG,                                            \
        (uint32_t)(Source))

#define HLL_SCU_CLK_SET_PLL_SOURCE_HSE(UseHSE)                     \
    SET_SCU_SCCR_PLLCLKSEL(                                        \
        HLL_SCUCLK_REG,                                            \
        (bool)(UseHSE))

#define HLL_SCU_CLK_SET_FLASH_LATENCY_DEFAULT()                    \
    ((void)0)

#define HLL_SCU_CLK_SET_OUTPUT_DIVIDER(Div)                  \
    SET_SCU_COR_CLKODIV(                                      \
        HLL_SCUCLK_REG,                                       \
        (uint8_t)(Div))

#define HLL_SCU_CLK_SET_OUTPUT_SOURCE(Source)                 \
    SET_SCU_COR_CLKOINSEL(                                    \
        HLL_SCUCLK_REG,                                       \
        (uint8_t)(Source))

#define HLL_SCU_CLK_SET_OUTPUT_ENABLE(Enable)                 \
    SET_SCU_COR_CLKOEN(                                       \
        HLL_SCUCLK_REG,                                       \
        (bool)(Enable))

#define HLL_SCU_CLK_IS_VALID_OUTPUT_DIV(Div)                  \
    ((uint8_t)(Div) < SCUCLK_CLK_OUTPUT_DIV_MAX)

#define HLL_SCU_CLK_OUTPUT_SRC_MCLK                           \
    SCUCLK_OUTPUT_INCLK_MCLK

#define HLL_SCU_CLK_OUTPUT_SRC_WDT                            \
    SCUCLK_OUTPUT_INCLK_WDT

#define HLL_SCU_CLK_OUTPUT_SRC_HSI                            \
    SCUCLK_OUTPUT_INCLK_HSI

#define HLL_SCU_CLK_OUTPUT_SRC_HCLK                           \
    SCUCLK_OUTPUT_INCLK_HCLK

#define HLL_SCU_CLK_OUTPUT_SRC_PCLK                           \
    SCUCLK_OUTPUT_INCLK_PCLK

#define HLL_SCU_CLK_GET_OUTPUT_SOURCE_VALUE(Source, Output) \
    HLL_SCU_CLK_GetOutputSourceValueImpl((P_SCUCLK_SRC_e)(Source), (Output))

#define HLL_SCU_CLK_SET_PLL_ENABLE(Enable)                      \
    SET_SCU_PLLCON_PLLEN(                                       \
        HLL_SCUCLK_REG,                                         \
        (bool)(Enable))

#define HLL_SCU_CLK_SET_PLL_SOURCE_HSE(UseHSE)                  \
    SET_SCU_SCCR_PLLCLKSEL(                                     \
        HLL_SCUCLK_REG,                                         \
        (bool)(UseHSE))

#define HLL_SCU_CLK_SET_PLL_SOURCE_DIVIDER(Div)                 \
    ((void)(Div))

#define HLL_SCU_CLK_SET_PLL_HSE_SOURCE(Div)                     \
    do                                                          \
    {                                                           \
        (void)(Div);                                            \
        SET_SCU_CSCR_HSE(                                       \
            HLL_SCUCLK_REG,                                     \
            ((uint32_t)true << SCUCLK_SRC_ENABLE_POS));         \
    } while (0)

#define HLL_SCU_CLK_SET_PLL_HSI_SOURCE(Div)                     \
    do                                                          \
    {                                                           \
        (void)(Div);                                            \
        SET_SCU_CSCR_HSI(                                       \
            HLL_SCUCLK_REG,                                     \
            ((uint32_t)true << SCUCLK_SRC_ENABLE_POS));         \
    } while (0)

#define HLL_SCU_CLK_SET_PLL_CONTROL(Value)                      \
    SET_SCU_PLLCON(                                             \
        HLL_SCUCLK_REG,                                         \
        (uint32_t)(Value))

#define HLL_SCU_CLK_SET_PLL_CONTROL_KEY()                       \
    SET_SCU_PLLCON(                                             \
        HLL_SCUCLK_REG,                                         \
        SCUCLK_PLLCON_KEY_VALUE)

#define HLL_SCU_CLK_GET_PLL_LOCK()                              \
    GET_SCU_PLLCON_LOCK(HLL_SCUCLK_REG)

#define HLL_SCU_CLK_GET_PLL_READY()                             \
    ((GET_SCU_PLLCON(HLL_SCUCLK_REG) & (1UL << 30)) != 0UL)

#define HLL_SCU_CLK_GET_PLL_HSE_CLOCK(Div)                      \
    ((void)(Div), HSE_CLOCK)

#define HLL_SCU_CLK_GET_PLL_HSI_CLOCK(Div)                      \
    ((void)(Div), HSI_CLOCK)

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
#if defined(SCU_FEATURE_VX_PLL_BLOCK)
        case P_SCUCLK_SRC_PLL:
            un32Data = SCUCLK_MCLKSEL_PLL;
            break;
#endif
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

static __inline HAL_ERR_e SCUCLK_SetPLLSrcDiv(P_SCUCLK_PLL_SRC_e eSrcClk, P_SCUCLK_DIV_e eSrcDiv, uint32_t *pun32PllClk)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCUCLK_Type *ptScuClk = (SCUCLK_Type *)SCUCLK_REG_BASE;
    uint32_t un32Data = 0;

    un32Data = (true << SCUCLK_SRC_ENABLE_POS);

    switch(eSrcClk)
    {
        case P_SCUCLK_PLL_SRC_HSE:
            SET_SCU_CSCR_HSE(ptScuClk, un32Data);
            *pun32PllClk = HSE_CLOCK;
            break;
        case P_SCUCLK_PLL_SRC_HSI:
            SET_SCU_CSCR_HSI(ptScuClk, un32Data);
            *pun32PllClk = HSI_CLOCK;
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

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

#if defined(AUDK32_FEATURE_HLL_SUPPORT)
__STATIC_INLINE HAL_ERR_e HLL_SCU_CLK_GetOutputSourceValueImpl(
    SCUCLK_SRC_e eSrc,
    uint32_t *pun32Output)
{
    switch (eSrc)
    {
        case SCUCLK_SRC_MCLK:
            *pun32Output = SCUCLK_OUTPUT_INCLK_MCLK;
            break;

        case SCUCLK_SRC_WDT:
            *pun32Output = SCUCLK_OUTPUT_INCLK_WDT;
            break;

        case SCUCLK_SRC_HSI:
            *pun32Output = SCUCLK_OUTPUT_INCLK_HSI;
            break;

        case SCUCLK_SRC_HCLK:
            *pun32Output = SCUCLK_OUTPUT_INCLK_HCLK;
            break;

        case SCUCLK_SRC_PCLK:
            *pun32Output = SCUCLK_OUTPUT_INCLK_PCLK;
            break;

        default:
            return HAL_ERR_PARAMETER;
    }

    return HAL_ERR_OK;
}
#endif

#endif /* _HAL_SCH_F1X_H_ */
