/**
 *******************************************************************************
 * @file        hal_pwm.c
 * @author      ABOV R&D Division
 * @brief       Pulse Width Modulation (PWM)
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#include "abov_config.h"

#if defined(_PWM)
#include "hal_pwm.h"
#include "hal_pwm_prv.h"

typedef struct
{
     PWM_OPS_e               eOps;
     pfnPWM_IRQ_Handler_t    pfnHandler;
     void                    *pContext;
} PWM_CTRL_BLK_t;

static PWM_CTRL_BLK_t s_tPcb[PWM_CH_NUM];

static void PRV_PWM_IRQHandler(PWM_ID_e eId);

static PWM_Type *PRV_PWM_GetReg(PWM_ID_e eId)
{
    return PWM_GetReg((uint32_t)eId);
}

static PWMPRS_Type *PRV_PWM_GetPrsReg(PWM_ID_e eId)
{
    return PWM_GetPrsReg((uint32_t)eId);
}

static HAL_ERR_e PRV_PWM_SetScuEnable(P_PWM_ID_e eId, bool bEnable)
{
    return PWM_SetScuEnable(eId, bEnable);
}

HAL_ERR_e HAL_PWM_Init(PWM_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= PWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_PWM_SetScuEnable((P_PWM_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tPcb[(uint32_t)eId], 0x00, sizeof(PWM_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_PWM_Uninit(PWM_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= PWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_PWM_SetScuEnable((P_PWM_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = PWM_GetIRQNum((P_PWM_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_PWM_SetClkConfig(PWM_ID_e eId, PWM_CLK_CFG_t *ptClkCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    PWM_Type *ptPwm;
    PWMPRS_Type *ptPwmPrs;

    if((uint32_t)eId >= PWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptPwm = PRV_PWM_GetReg(eId);
    ptPwmPrs = PRV_PWM_GetPrsReg(eId);

    switch(ptClkCfg->eClk)
    {
        case PWM_CLK_PCLK:
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    /* Prescale */
    SET_PWMPRS_PRE_SCALE_EN(ptPwmPrs, ptClkCfg->bPreScaleEn);
    SET_PWMPRS_PRE_SCALE(ptPwmPrs, ptClkCfg->un8PreScale);

    /* Clock Divider */
    SET_PWM_CR_CLK_DIV(ptPwm, ptClkCfg->eClkDiv);


    return eErr;
}

HAL_ERR_e HAL_PWM_SetConfig(PWM_ID_e eId, PWM_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    PWM_Type *ptPwm;

    if((uint32_t)eId >= PWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptPwm = PRV_PWM_GetReg(eId);

    SET_PWM_CR_SYNC(ptPwm, ptCfg->bSyncEn);
    SET_PWM_DR_PERIOD(ptPwm, ptCfg->un16Period);
    SET_PWM_DR_DUTY(ptPwm, ptCfg->un16Duty);
    SET_PWM_CR_PORTA_INV(ptPwm, ptCfg->ePAInv);
    
    return eErr;
}

HAL_ERR_e HAL_PWM_SetIRQ(PWM_ID_e eId, PWM_OPS_e eOps, pfnPWM_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    PWM_CTRL_BLK_t *ptPcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= PWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptPcb = &s_tPcb[(uint32_t)eId];
    eIrq = PWM_GetIRQNum((P_PWM_ID_e)eId);

    switch(eOps)
    {
        case PWM_OPS_INTR:
            ptPcb->pfnHandler = pfnHandler;
            ptPcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            break;
        case PWM_OPS_POLL:
        default:
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptPcb->pContext = NULL;
            ptPcb->pfnHandler = NULL;
            break;
    }

    ptPcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_PWM_Start(PWM_ID_e eId)
{
    PWM_Type *ptPwm;
    PWM_CTRL_BLK_t *ptPcb;

    if((uint32_t)eId >= PWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptPwm = PRV_PWM_GetReg(eId);
    ptPcb = &s_tPcb[eId];

    if(ptPcb->eOps == PWM_OPS_INTR)
    {
        SET_PWM_IER_MATCH_EN(ptPwm, true);
    }

    SET_PWM_CR_EN(ptPwm, true);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_PWM_Stop(PWM_ID_e eId)
{
    PWM_Type *ptPwm;
    PWM_CTRL_BLK_t *ptPcb;

    if((uint32_t)eId >= PWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptPwm = PRV_PWM_GetReg(eId);
    ptPcb = &s_tPcb[eId];

    if(ptPcb->eOps == PWM_OPS_INTR)
    {
        SET_PWM_IER_MATCH_EN(ptPwm, false);
    }

    SET_PWM_CR_EN(ptPwm, false);

    return HAL_ERR_OK;
}

static void PRV_PWM_IRQHandler(PWM_ID_e eId)
{
    PWM_Type *ptPwm;
    PWM_CTRL_BLK_t *ptPcb;
    uint32_t un32Event=0;

    ptPwm = PRV_PWM_GetReg(eId);
    ptPcb = &s_tPcb[eId];

    if(GET_PWM_IER_MATCH_FLAG(ptPwm))
    {
        SET_PWM_IER_MATCH_FLAG(ptPwm, true);
        un32Event = PWM_EVENT_MATCH;
    }

    if(ptPcb->pfnHandler != NULL && un32Event)
    {
        ptPcb->pfnHandler(un32Event, ptPcb->pContext);
    }
}

void PWM0_IRQHandler(void)
{
    PRV_PWM_IRQHandler(PWM_ID_0);
}

void PWM1_IRQHandler(void)
{
    PRV_PWM_IRQHandler(PWM_ID_1);
}

void PWM2_IRQHandler(void)
{
    PRV_PWM_IRQHandler(PWM_ID_2);
}

void PWM3_IRQHandler(void)
{
    PRV_PWM_IRQHandler(PWM_ID_3);
}

void PWM4_IRQHandler(void)
{
    PRV_PWM_IRQHandler(PWM_ID_4);
}

void PWM5_IRQHandler(void)
{
    PRV_PWM_IRQHandler(PWM_ID_5);
}

void PWM6_IRQHandler(void)
{
    PRV_PWM_IRQHandler(PWM_ID_6);
}

void PWM7_IRQHandler(void)
{
    PRV_PWM_IRQHandler(PWM_ID_7);
}

void PWM8_IRQHandler(void)
{
    PRV_PWM_IRQHandler(PWM_ID_8);
}

void PWM9_IRQHandler(void)
{
    PRV_PWM_IRQHandler(PWM_ID_9);
}

#endif /* _PWM */
