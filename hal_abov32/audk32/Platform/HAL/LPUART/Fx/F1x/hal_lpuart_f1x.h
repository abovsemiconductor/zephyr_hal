/**
 *******************************************************************************
 * @file        hal_lpuart_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed LPUART
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_LPUART_F1X_H_
#define _HAL_LPUART_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define LPUART_CH_NUM                                   CONFIG_LPUART_MAX_COUNT

#define LPUART_IIR_RX_DONE                              BIT(0)
#define LPUART_IIR_TX_DONE                              BIT(2)
#define LPUART_IIR_RX_LINE_BUSY                         BIT(12)
#define LPUART_IIR_RX_DATA_OVERRUN                      BIT(15)
#define LPUART_IIR_RX_FRAME_ERROR                       BIT(14)
#define LPUART_IIR_RX_PARITY_ERROR                      BIT(13)
#define LPUART_IIR_DMA_RX_DONE                          BIT(8)
#define LPUART_IIR_DMA_TX_DONE                          BIT(9)

#if (CONFIG_LPUART_VER_EXT == 0)

#if (CONFIG_LPUART_VER_MINOR == 0)
#include "hal_lpuart_f_01_00_00.h"
#elif (CONFIG_LPUART_VER_MINOR == 1)
#include "hal_lpuart_f_01_00_01.h"
#else
#error "define CONFIG_LPUART_VER_MINOR of F-type LPUART at config_xxx.h"
#endif

#else
#error "define CONFIG_LPUART_VER_EXT of F-type LPUART at config_xxx.h"
#endif

#if defined(LPUART_FEATURE_MCCR)
static uint32_t un32UartBdrClock = 0;
#endif

static __inline HAL_ERR_e LPUART_SetScuEnable(P_LPUART_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_LPUART_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_LPUART_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_LPUART_PCER(ptScu, (uint32_t)eId, un32Enable);

#if defined(LPUART_FEATURE_MCCR)
    if(un32Enable == false)
    {
        un32UartBdrClock = 0;
    }
#endif

    return HAL_ERR_OK;
}

static __inline LPUART_Type *LPUART_GetReg(uint32_t uiId)
{
    return (LPUART_Type *)(LPUART_REG_BASE + (LPUART_REG_OFFSET * uiId));
}

static __inline IRQn_Type LPUART_GetIRQNum(P_LPUART_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(LPUART_0_IRQ)
        case P_LPUART_ID_0:
            eIrq = LPUART_0_IRQ;
            break;
#endif
#if defined(LPUART_1_IRQ)
        case P_LPUART_ID_1:
            eIrq = LPUART_1_IRQ;
            break;
#endif
#if defined(LPUART_2_IRQ)
        case P_LPUART_ID_2:
            eIrq = LPUART_2_IRQ;
            break;
#endif
#if defined(LPUART_3_IRQ)
        case P_LPUART_ID_3:
            eIrq = LPUART_3_IRQ;
            break;
#endif
#if defined(LPUART_4_IRQ)
        case P_LPUART_ID_4:
            eIrq = LPUART_4_IRQ;
            break;
#endif
#if defined(LPUART_5_IRQ)
        case P_LPUART_ID_5:
            eIrq = LPUART_5_IRQ;
            break;
#endif
#if defined(LPUART_6_IRQ)
        case P_LPUART_ID_6:
            eIrq = LPUART_6_IRQ;
            break;
#endif
#if defined(LPUART_7_IRQ)
        case P_LPUART_ID_7:
            eIrq = LPUART_7_IRQ;
            break;
#endif
#if defined(LPUART_8_IRQ)
        case P_LPUART_ID_8:
            eIrq = LPUART_8_IRQ;
            break;
#endif
#if defined(LPUART_9_IRQ)
        case P_LPUART_ID_9:
            eIrq = LPUART_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

#if defined(LPUART_FEATURE_SCU_CLK_VX)
static __inline uint32_t LPUART_GetNumer(P_LPUART_ID_e eId)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    uint8_t un8LpUartClkSel, un8LpUartClkDiv;
    uint32_t un32LpUartClk;

    un8LpUartClkSel = GET_SCU_LPUART_CLK_SEL(ptScu, eId);
    un8LpUartClkDiv = GET_SCU_LPUART_CLKDIV_SEL(ptScu, eId);

    switch(un8LpUartClkSel)
    {
#if defined(LPUART_CLK_LSI)
        case LPUART_CLK_LSI:
            un32LpUartClk = LSI_CLOCK;
            break;
#endif
        case LPUART_CLK_LSE:
            un32LpUartClk = LSE_CLOCK;
            break;
        case LPUART_CLK_MCLK:
            un32LpUartClk = SystemCoreClock;
            break;
        case LPUART_CLK_HSI:
            un32LpUartClk = HSI_CLOCK;
            break;
        case LPUART_CLK_HSE:
            un32LpUartClk = HSE_CLOCK;
            break;
#if defined(LPUART_CLK_PLL)
        case LPUART_CLK_PLL:
            un32LpUartClk = SystemCoreClock;
            break;
#endif
        default:
            un32LpUartClk = HSI_CLOCK;
            break;
    }

    return (un32LpUartClk / BIT(un8LpUartClkDiv));
}
#else
static __inline uint32_t LPUART_GetNumer(P_LPUART_ID_e eId)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    uint8_t un8LpUartClk = 0;
    uint8_t un8LpUartHSIClk = 0;

    un8LpUartClk = GET_SCU_LPUART_CLK_SEL(ptScu, eId);
    
    if (un8LpUartClk == LPUART_CLK_PCLK)
    {
        return SystemPeriClock;
    }
    else if (un8LpUartClk == LPUART_CLK_LSE)
    {
        return LSE_CLOCK;
    }
    else if (un8LpUartClk == LPUART_CLK_HSI)
    {
        un8LpUartHSIClk = GET_SCU_HSI_CLK_SEL(ptScu);    
        return (HSI_CLOCK / BIT(un8LpUartHSIClk));
    }

    return HSI_CLOCK;
}
#endif

static __inline void PRV_LPUART_SetReset(P_LPUART_ID_e eId, bool bEnable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_LPUART_MAX_COUNT)
    {
        return;
    }

    SET_SCU_LPUART_RST(ptScu, (uint32_t)eId, bEnable);
}

#if defined(LPUART_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void PRV_LPUART_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, bEnable);
}
#endif

#if defined(LPUART_FEATURE_SCU_CLK_VX)
static __inline HAL_ERR_e LPUART_SetMccrClk(P_LPUART_ID_e eId, P_LPUART_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if (eMccr == P_LPUART_CLK_MCCR_LSI)
    {
        SET_SCU_LPUART_CLK_SEL(ptScu, eId, LPUART_CLK_LSI);
    }
    else if (eMccr == P_LPUART_CLK_MCCR_LSE)
    {
        SET_SCU_LPUART_CLK_SEL(ptScu, eId, LPUART_CLK_LSE);
    }
    else if (eMccr == P_LPUART_CLK_MCCR_MCLK)
    {
        SET_SCU_LPUART_CLK_SEL(ptScu, eId, LPUART_CLK_MCLK);
    }
    else if (eMccr == P_LPUART_CLK_MCCR_HSI)
    {
        SET_SCU_LPUART_CLK_SEL(ptScu, eId, LPUART_CLK_HSI);
    }
    else if (eMccr == P_LPUART_CLK_MCCR_HSE)
    {
        SET_SCU_LPUART_CLK_SEL(ptScu, eId, LPUART_CLK_HSE);
    }
    else if (eMccr == P_LPUART_CLK_MCCR_PLL)
    {
        SET_SCU_LPUART_CLK_SEL(ptScu, eId, LPUART_CLK_PLL);
    }
    else
    {
        eErr = HAL_ERR_PARAMETER;
    }

    if(eErr == HAL_ERR_OK)
    {
        SET_SCU_LPUART_CLKDIV_SEL(ptScu, eId, un8MccrDiv);
    }

    return eErr;
}
#else
static __inline HAL_ERR_e LPUART_SetMccrClk(P_LPUART_ID_e eId, P_LPUART_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if (eMccr == P_LPUART_CLK_MCCR_HSI)
    {
        SET_SCU_LPUART_CLK_SEL(ptScu, eId, LPUART_CLK_HSI);
    }
    else if (eMccr == P_LPUART_CLK_MCCR_LSE)
    {
        SET_SCU_LPUART_CLK_SEL(ptScu, eId, LPUART_CLK_LSE);
    }
    else
    {
        eErr = HAL_ERR_PARAMETER;
    }

    return eErr;
}
#endif

#endif /* _HAL_LPUART_F1X_H_ */
