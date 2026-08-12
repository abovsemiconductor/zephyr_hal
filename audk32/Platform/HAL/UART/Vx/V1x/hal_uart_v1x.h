/**
 *******************************************************************************
 * @file        hal_uart_v1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed UART
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_UART_V1X_H_
#define _HAL_UART_V1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define UART_CH_NUM                                   CONFIG_UART_MAX_COUNT

#define UART_IIR_RX_LINE_ERROR                        (0x06)
#define UART_IIR_RX_DATA_AVAIL                        (0x04)
#define UART_IIR_TX_EMPTY                             (0x10)
#define UART_IIR_TX_HOLD_EMPTY                        (0x02)
#define UART_IIR_RX_DMA_DONE                          (0x0C)
#define UART_IIR_TX_DMA_DONE                          (0x0A)

#if (CONFIG_UART_VER_EXT == 0)

#if (CONFIG_UART_VER_MINOR == 0)
#include "hal_uart_v_01_00_00.h"
#elif (CONFIG_UART_VER_MINOR == 1)
#include "hal_uart_v_01_00_01.h"
#elif (CONFIG_UART_VER_MINOR == 2)
#include "hal_uart_v_01_00_02.h"
#elif (CONFIG_UART_VER_MINOR == 3)
#include "hal_uart_v_01_00_03.h"
#elif (CONFIG_UART_VER_MINOR == 4)
#include "hal_uart_v_01_00_04.h"
#elif (CONFIG_UART_VER_MINOR == 5)
#include "hal_uart_v_01_00_05.h"
#elif (CONFIG_UART_VER_MINOR == 6)
#include "hal_uart_v_01_00_06.h"
#elif (CONFIG_UART_VER_MINOR == 7)
#include "hal_uart_v_01_00_07.h"
#elif (CONFIG_UART_VER_MINOR == 8)
#include "hal_uart_v_01_00_08.h"
#else
#error "define CONFIG_UART_VER_MINOR of F-type UART at config_xxx.h"
#endif

#else
#error "define CONFIG_UART_VER_EXT of F-type UART at config_xxx.h"
#endif

#if defined(UART_FEATURE_MCCR)
static uint32_t un32UartBdrClock = 0;
#endif

static __inline HAL_ERR_e UART_SetScuEnable(P_UART_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_UART_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_UART_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_UART_PCER(ptScu, (uint32_t)eId, un32Enable);

#if defined(UART_FEATURE_MCCR)
    if(un32Enable == false)
    {
        un32UartBdrClock = 0;
    }
#endif

    return HAL_ERR_OK;
}

static __inline UART_Type *UART_GetReg(uint32_t uiId)
{
    return (UART_Type *)(UART_REG_BASE + (UART_REG_OFFSET * uiId));
}

static __inline IRQn_Type UART_GetIRQNum(P_UART_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(UART_0_IRQ)
        case P_UART_ID_0:
            eIrq = UART_0_IRQ;
            break;
#endif
#if defined(UART_1_IRQ)
        case P_UART_ID_1:
            eIrq = UART_1_IRQ;
            break;
#endif
#if defined(UART_2_IRQ)
        case P_UART_ID_2:
            eIrq = UART_2_IRQ;
            break;
#endif
#if defined(UART_3_IRQ)
        case P_UART_ID_3:
            eIrq = UART_3_IRQ;
            break;
#endif
#if defined(UART_4_IRQ)
        case P_UART_ID_4:
            eIrq = UART_4_IRQ;
            break;
#endif
#if defined(UART_5_IRQ)
        case P_UART_ID_5:
            eIrq = UART_5_IRQ;
            break;
#endif
#if defined(UART_6_IRQ)
        case P_UART_ID_6:
            eIrq = UART_6_IRQ;
            break;
#endif
#if defined(UART_7_IRQ)
        case P_UART_ID_7:
            eIrq = UART_7_IRQ;
            break;
#endif
#if defined(UART_8_IRQ)
        case P_UART_ID_8:
            eIrq = UART_8_IRQ;
            break;
#endif
#if defined(UART_9_IRQ)
        case P_UART_ID_9:
            eIrq = UART_9_IRQ;
            break;
#endif
#if defined(UART_10_IRQ)
        case P_UART_ID_10:
            eIrq = UART_10_IRQ;
            break;
#endif
#if defined(UART_11_IRQ)
        case P_UART_ID_11:
            eIrq = UART_11_IRQ;
            break;
#endif
#if defined(UART_12_IRQ)
        case P_UART_ID_12:
            eIrq = UART_12_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline HAL_ERR_e UART_SetClk(P_UART_ID_e eId, P_UART_CLK_MCCR_e eMccr, uint8_t un8MccrDiv)
{
#if defined(UART_FEATURE_MCCR)
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_UART_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    switch(eMccr)
    {
        case P_UART_CLK_MCCR_LSI:
            un32UartBdrClock = LSI_CLOCK / un8MccrDiv;
            break;
#if defined(UART_FEATURE_UNSUPPORT_MCCR_LSE)
#else
        case P_UART_CLK_MCCR_LSE:
            un32UartBdrClock = LSE_CLOCK / un8MccrDiv;
            break;
#endif
        case P_UART_CLK_MCCR_MCLK:
            un32UartBdrClock = SystemCoreClock / un8MccrDiv;
            break;
        case P_UART_CLK_MCCR_HSI:
            un32UartBdrClock = HSI_CLOCK / un8MccrDiv;
            break;
#if defined(UART_FEATURE_UNSUPPORT_MCCR_HSE)
#else
        case P_UART_CLK_MCCR_HSE:
            un32UartBdrClock = HSE_CLOCK / un8MccrDiv;
            break;
#endif
        case P_UART_CLK_MCCR_PLL:
            un32UartBdrClock = SystemCoreClock / un8MccrDiv;
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    SET_SCU_UART_MCCR_SEL(ptScu, SCU_UART_MCCR_MODE(eMccr));
    SET_SCU_UART_MCCR_DIV(ptScu, un8MccrDiv);

    return eErr;
#else
    (void)eId;
    (void)eMccr;
    (void)un8MccrDiv;
    /* PCLK selection */
    return HAL_ERR_OK;
#endif
}

static __inline uint32_t UART_GetNumer(void)
{
#if defined(UART_FEATURE_MCCR)
    return un32UartBdrClock;
#else
#if defined(UART_FEATURE_NO_DIV_BAUDRATE)
    return SystemPeriClock;
#else
    return SystemPeriClock / 2;
#endif
#endif
}

#if defined(UART_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void PRV_UART_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, (uint8_t)eIrq, bEnable);
}
#endif

#endif /* _HAL_UART_PRV_H_ */
