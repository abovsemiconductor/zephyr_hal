/**
 *******************************************************************************
 * @file        hal_led.c
 * @author      ABOV R&D Division
 * @brief       LED Driver
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

#if defined(_LED)
#include "hal_led.h"
#include "hal_led_prv.h"

typedef struct
{
    LED_OPS_e               eOps;
    pfnLED_IRQ_Handler_t    pfnHandler;
    void                    *pContext;
} LED_CTRL_BLK_t;

static LED_CTRL_BLK_t s_tLcb[LED_CH_NUM];

static LED_Type *PRV_LED_GetReg(P_LED_ID_e eId)
{
    return LED_GetReg((P_LED_ID_e)eId);
}

static HAL_ERR_e PRV_LED_SetScuEnable(P_LED_ID_e eId, bool bEnable)
{
    return LED_SetScuEnable((P_LED_ID_e)eId, bEnable);
}

HAL_ERR_e HAL_LED_Init(LED_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LED_Type *ptLed;

    if((uint32_t)eId >= LED_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_LED_SetScuEnable((P_LED_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tLcb[(uint32_t)eId], 0, sizeof(LED_CTRL_BLK_t));

    ptLed = PRV_LED_GetReg((P_LED_ID_e)eId);
    SET_LED_CON1_LEDEN(ptLed, true);

    SET_LED_INTR_LEDENDF(ptLed, false);      /**< Clear ENDF Flag */
    SET_LED_INTR_LEDINTR(ptLed, false);      /**< Clear INTR Flag */
    SET_LED_INTR_MATCHF(ptLed, false);       /**< Clear MATCH Flag */

    return eErr;
}

HAL_ERR_e HAL_LED_Uninit(LED_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= LED_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_LED_SetScuEnable((P_LED_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = LED_GetIRQNum((P_LED_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tLcb[(uint32_t)eId], 0, sizeof(LED_CTRL_BLK_t));

    return eErr;
}

HAL_ERR_e HAL_LED_SetClkConfig(LED_ID_e eId, LED_CLK_CFG_t *ptClkCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LED_Type *ptLed;

    if((uint32_t)eId >= LED_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = LED_SetClk((P_LED_ID_e)eId, (P_LED_CLK_e)ptClkCfg->eClk,
            (P_LED_CLK_MCCR_e)ptClkCfg->eMccr, ptClkCfg->un8MccrDiv);

    ptLed = PRV_LED_GetReg((P_LED_ID_e)eId);

    SET_LED_PRESD_PRESCALER(ptLed, ptClkCfg->un16Prescale);

    return eErr;
}

HAL_ERR_e HAL_LED_SetConfig(LED_ID_e eId, LED_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LED_Type *ptLed;

    if((uint32_t)eId >= LED_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLed = PRV_LED_GetReg((P_LED_ID_e)eId);

    SET_LED_COMPWID_PULSEWIDTH(ptLed, ptCfg->un8IcomPulse);

    SET_LED_STPD_DURATION(ptLed, ptCfg->un32Duration);

    SET_LED_CON1_MODESEL(ptLed, LED_MODE(ptCfg->eLedMode));

    SET_LED_CON2_OVERLAP(ptLed, ((ptCfg->tOverlap.bEnable == true) ? 0 : 1));
    SET_LED_CON2_OVERLAPTIME(ptLed, ptCfg->tOverlap.eTime);

    return eErr;
}

HAL_ERR_e HAL_LED_SetIRQ(LED_ID_e eId, LED_OPS_e eOps, pfnLED_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LED_Type *ptLed;
    LED_CTRL_BLK_t *ptLcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= LED_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLed = PRV_LED_GetReg((P_LED_ID_e)eId);
    ptLcb = &s_tLcb[(uint32_t)eId];
    eIrq = LED_GetIRQNum((P_LED_ID_e)eId);

    switch(eOps)
    {
        case LED_OPS_INTR:
            ptLcb->pfnHandler = pfnHandler;
            ptLcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            SET_LED_INTR_LEDINTE(ptLed, true);
            break;
        case LED_OPS_POLL:
        default:
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptLcb->pContext = NULL;
            ptLcb->pfnHandler = NULL;
            SET_LED_INTR_LEDINTE(ptLed, false);
            break;
    }

    ptLcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_LED_SetDimming(LED_ID_e eId, LED_DATA_t *ptDimm, uint8_t un8Num)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LED_Type    *ptLed;
    uint32_t    un32AddrReg;
    uint8_t un8Cnt = 0;

    if((uint32_t)eId >= LED_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLed = PRV_LED_GetReg((P_LED_ID_e)eId);

    for(un8Cnt = 0; un8Cnt < un8Num; un8Cnt++)
    {
        if(ptDimm[un8Cnt].un8Num <= LED_ICOM_CH_NUM)
        {
            un32AddrReg = (uint32_t)(GET_LED_DIMMING_BASE_ADDR(ptLed));
            SET_LED_DR_DIMMING(un32AddrReg, ptDimm[un8Cnt].un8Num, ptDimm[un8Cnt].un32Data);
        }
        else
        {
            eErr = HAL_ERR_NOT_SUPPORTED;
            break;
        }
    }

    return eErr;
}

HAL_ERR_e HAL_LED_SetDispData(LED_ID_e eId, LED_DATA_t *ptRam, uint8_t un8Num)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LED_Type *ptLed;
    uint32_t un32AddrReg;
    uint8_t un8Cnt = 0;

    if((uint32_t)eId >= LED_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLed = PRV_LED_GetReg((P_LED_ID_e)eId);

    for(un8Cnt = 0; un8Cnt < un8Num; un8Cnt++)
    {
        if(ptRam[un8Cnt].un8Num <= LED_ICOM_CH_NUM)
        {
            un32AddrReg = (uint32_t)(GET_LED_DISPRAM_BASE_ADDR(ptLed) + ptRam[un8Cnt].un8Num);
            *(volatile uint32_t *)un32AddrReg = ptRam[un8Cnt].un32Data;
        }
        else
        {
            eErr = HAL_ERR_NOT_SUPPORTED;
            break;
        }
    }

    return eErr;
}

HAL_ERR_e HAL_LED_GetDispData(LED_ID_e eId, uint8_t un8IcomNum, uint32_t *pun32Data)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LED_Type    *ptLed;
    uint32_t    un32AddrReg;

    if((uint32_t)eId >= LED_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(un8IcomNum < LED_ICOM_CH_NUM)
    {
        ptLed = PRV_LED_GetReg((P_LED_ID_e)eId);

        un32AddrReg = (uint32_t)(GET_LED_DISPRAM_BASE_ADDR(ptLed) + un8IcomNum);
        *pun32Data = (uint32_t)(*(volatile uint32_t *)un32AddrReg);
    }
    else
    {
        eErr = HAL_ERR_NOT_SUPPORTED;
    }

    return eErr;
}

HAL_ERR_e HAL_LED_SetIcomEnable(LED_ID_e eId, uint32_t un32Enable)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LED_Type *ptLed;
    uint32_t un32AddrReg;

    if((uint32_t)eId >= LED_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(un32Enable >> LED_ICOM_CH_NUM)
    {
        return HAL_ERR_PARAMETER;
    }

    ptLed = PRV_LED_GetReg((P_LED_ID_e)eId);

    un32AddrReg = (uint32_t)GET_LED_COMER_ADDR(ptLed);
    *(volatile uint32_t *)un32AddrReg = un32Enable;

    return eErr;
}

HAL_ERR_e HAL_LED_SetIcomOutput(LED_ID_e eId, uint32_t un32Enable)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LED_Type *ptLed;
    uint32_t un32AddrReg;

    if((uint32_t)eId >= LED_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(un32Enable >> LED_ICOM_CH_NUM)
    {
        return HAL_ERR_PARAMETER;
    }

    ptLed = PRV_LED_GetReg((P_LED_ID_e)eId);

    un32AddrReg = (uint32_t)GET_LED_COMOE_ADDR(ptLed);
    *(volatile uint32_t *)un32AddrReg = un32Enable;

    return eErr;
}

HAL_ERR_e HAL_LED_SetIsegOutput(LED_ID_e eId, uint32_t un32Enable)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LED_Type *ptLed;
    uint32_t un32AddrReg;

    if((uint32_t)eId >= LED_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(un32Enable >> LED_ISEG_CH_NUM)
    {
        return HAL_ERR_PARAMETER;
    }

    ptLed = PRV_LED_GetReg((P_LED_ID_e)eId);

    un32AddrReg = (uint32_t)GET_LED_SEGOE_ADDR(ptLed);
    *(volatile uint32_t *)un32AddrReg = un32Enable;

    return eErr;
}

HAL_ERR_e HAL_LED_Start(LED_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LED_Type *ptLed;

    if((uint32_t)eId >= LED_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLed = PRV_LED_GetReg((P_LED_ID_e)eId);

    SET_LED_CON1_START(ptLed, true);

    return eErr;
}

HAL_ERR_e HAL_LED_Stop(LED_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    LED_Type *ptLed;

    if((uint32_t)eId >= LED_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptLed = PRV_LED_GetReg((P_LED_ID_e)eId);

    SET_LED_CON1_START(ptLed, false);

    return eErr;
}

void PRV_LED_IRQHandler(LED_ID_e eId)
{
    LED_Type *ptLed;
    LED_CTRL_BLK_t *ptLcb;
    uint32_t un32Event = 0;

    ptLed = PRV_LED_GetReg((P_LED_ID_e)eId);
    ptLcb = &s_tLcb[(uint32_t)eId];

    if(GET_LED_INTR_MATCHF(ptLed))
    {
        un32Event |= LED_EVENT_MATCH;
        SET_LED_INTR_MATCHF(ptLed, false);
    }

    if(GET_LED_INTR_LEDINTR(ptLed))
    {
        un32Event |= LED_EVENT_INTR;
        SET_LED_INTR_LEDINTR(ptLed, false);
    }

    if(GET_LED_INTR_LEDENDF(ptLed))
    {
        un32Event |= LED_EVENT_END;
    }

    if((ptLcb->pfnHandler != NULL) && (un32Event != 0))
    {
        ptLcb->pfnHandler(un32Event,ptLcb->pContext);
    }
}

void LED0_IRQHandler(void)
{
    PRV_LED_IRQHandler(LED_ID_0);
}

#endif /* _LED */
