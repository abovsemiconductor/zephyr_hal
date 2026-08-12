/**
 *******************************************************************************
 * @file        hal_rtc.c
 * @author      ABOV R&D Division
 * @brief       Real-time clock
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

#if defined(_RTC)
#include "hal_rtc.h"
#include "hal_rtc_prv.h"

typedef struct
{
    /* Interrupt */
    RTC_OPS_e                eOps;
    pfnRTC_IRQ_Handler_t    pfnHandler;
    void                    *pContext;
} RTC_CTRL_BLK_t;

static RTC_CTRL_BLK_t s_tRcb[RTC_CH_NUM];

static RTC_Type *PRV_RTC_GetReg(P_RTC_ID_e eId)
{
    return RTC_GetReg((P_RTC_ID_e)eId);
}

static HAL_ERR_e PRV_RTC_SetScuEnable(P_RTC_ID_e eId, bool bEnable)
{
    return RTC_SetScuEnable((P_RTC_ID_e)eId, bEnable);
}

HAL_ERR_e HAL_RTC_Init(RTC_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    RTC_Type *ptRtc;

    if((uint32_t)eId >= RTC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_RTC_SetScuEnable((P_RTC_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tRcb[(uint32_t)eId], 0, sizeof(RTC_CTRL_BLK_t));

    ptRtc = PRV_RTC_GetReg((P_RTC_ID_e)eId);
    SET_RTC_CR_EN(ptRtc, false);
    SET_RTC_CR_START(ptRtc, false);

    return eErr;
}

HAL_ERR_e HAL_RTC_Uninit(RTC_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    RTC_Type *ptRtc;
    IRQn_Type eIrq;

    if((uint32_t)eId >= RTC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptRtc = PRV_RTC_GetReg((P_RTC_ID_e)eId);
    SET_RTC_CR_EN(ptRtc, false);
    SET_RTC_CR_START(ptRtc, false);

    eErr = PRV_RTC_SetScuEnable((P_RTC_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = RTC_GetIRQNum((P_RTC_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tRcb[(uint32_t)eId], 0, sizeof(RTC_CTRL_BLK_t));

    return eErr;
}

HAL_ERR_e HAL_RTC_SetClkConfig(RTC_ID_e eId, RTC_CLK_CFG_t *ptClkCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    RTC_Type *ptRtc;
#if defined(RTC_FEATURE_SUBSECOND_COUNTER)
    uint32_t un32Clk = 0;
    uint32_t un32Delay = 0;
#endif

    if((uint32_t)eId >= RTC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptRtc = PRV_RTC_GetReg((P_RTC_ID_e)eId);

    SET_RTC_CR_EN(ptRtc, false);

    eErr = RTC_SetClk((P_RTC_ID_e)eId, (P_RTC_CLK_e)ptClkCfg->eClk, (P_RTC_CLK_MCCR_e)ptClkCfg->eMccr, ptClkCfg->un8MccrDiv);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    SET_RTC_CR_EN(ptRtc, 1UL);

#if defined(RTC_FEATURE_SUBSECOND_COUNTER)
    if(ptClkCfg->eClk == RTC_CLK_LSI40KHZ)
    {
        un32Clk = 40000;
    }
    else
    {
        switch(ptClkCfg->eMccr)
        {
            case RTC_CLK_MCCR_LSI:
                un32Clk = LSI_CLOCK/ptClkCfg->un8MccrDiv;
                break;
            case RTC_CLK_MCCR_LSE:
                un32Clk = LSE_CLOCK/ptClkCfg->un8MccrDiv;
                break;
            case RTC_CLK_MCCR_MCLK:
                un32Clk = HSI_CLOCK/ptClkCfg->un8MccrDiv;
                break;
            case RTC_CLK_MCCR_HSI:
                un32Clk = HSI_CLOCK/ptClkCfg->un8MccrDiv;
                break;
            case RTC_CLK_MCCR_HSE:
                un32Clk = HSE_CLOCK/ptClkCfg->un8MccrDiv;
                break;
            case RTC_CLK_MCCR_PLL:
                un32Clk = HSI_CLOCK/ptClkCfg->un8MccrDiv;
                break;
            default:
                eErr = HAL_ERR_PARAMETER;
                break;
        }
    }

    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    un32Delay = (SystemPeriClock / un32Clk) + RTC_DELAY_MARGIN;
    for(int i=0; i<un32Delay; i++)
    {
        __NOP();
    }

    SET_RTC_DR_SUBSEC(ptRtc, (un32Clk - 1));
#endif

    return eErr;
}

HAL_ERR_e HAL_RTC_SetConfig(RTC_ID_e eId, RTC_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    RTC_Type *ptRtc;

    if((uint32_t)eId >= RTC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptRtc = PRV_RTC_GetReg((P_RTC_ID_e)eId);

    if(ptCfg->bErrCorEn == true)
    {
        SET_RTC_CR_ERRCOR_EN(ptRtc, true);
        SET_RTC_CR_ERRCOR_DIR(ptRtc, ptCfg->eErrCorDir);
        SET_RTC_CR_ERRCOR_TIME(ptRtc, ptCfg->eErrCorTime);
        SET_RTC_DR_ERRCOR(ptRtc, ptCfg->un32ErrCorData);
    }
    else
    {
        SET_RTC_CR_ERRCOR_EN(ptRtc, false);
    }

    RTC_SetPortMode((P_RTC_ID_e)eId, ptCfg->bRTCClkOut, false);

    return eErr;
}

HAL_ERR_e HAL_RTC_SetIRQ(RTC_ID_e eId, RTC_OPS_e eOps, pfnRTC_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    RTC_CTRL_BLK_t *ptRcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= RTC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptRcb = &s_tRcb[(uint32_t)eId];
    eIrq = RTC_GetIRQNum((P_RTC_ID_e)eId);

    switch(eOps)
    {
        case RTC_OPS_INTR:
#if defined (RTC_FEATURE_IRQ_UNMASK_ENABLE)
            RTC_SetIntrUnMask(eIrq, true, P_RTC_FUNC_MAX); 
#endif
            ptRcb->pfnHandler = pfnHandler;
            ptRcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            break;
        case RTC_OPS_POLL:
        default:
#if defined (RTC_FEATURE_IRQ_UNMASK_ENABLE)
            RTC_SetIntrUnMask(eIrq, false, P_RTC_FUNC_MAX); 
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptRcb->pContext = NULL;
            ptRcb->pfnHandler = NULL;
            break;
    }

    ptRcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_RTC_Start(RTC_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    RTC_Type *ptRtc;

    if((uint32_t)eId >= RTC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptRtc = PRV_RTC_GetReg((P_RTC_ID_e)eId);
    SET_RTC_CR_START(ptRtc, true);

    return eErr;
}

HAL_ERR_e HAL_RTC_Stop(RTC_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    RTC_Type *ptRtc;

    if((uint32_t)eId >= RTC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptRtc = PRV_RTC_GetReg((P_RTC_ID_e)eId);
    SET_RTC_CR_START(ptRtc, false);

    return eErr;
}

HAL_ERR_e HAL_RTC_SetClock(RTC_ID_e eId, RTC_CLOCK_t *ptClock)
{
    RTC_Type *ptRtc;
    uint32_t un32TimeOut = 40000000;

    if((uint32_t)eId >= RTC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptRtc = PRV_RTC_GetReg((P_RTC_ID_e)eId);

    if(GET_RTC_CR_START(ptRtc))
    {
        SET_RTC_CR_RWMODE(ptRtc, true);

        while(!GET_RTC_SR_RWMODE(ptRtc))
        {
            un32TimeOut--;
            if(un32TimeOut == 0)
            {
                return HAL_ERR_HW;
            }
        }
    }

    SET_RTC_CR_24HOUR(ptRtc, ptClock->b24Hour);
#if defined (RTC_FEATURE_IRQ_UNMASK_ENABLE)
    RTC_SetIntrUnMask(RTC_0_IRQ, false, P_RTC_FUNC_WATCH);
#endif
    SET_RTC_IER_CONST_PERIOD_EN(ptRtc, ptClock->ePeriod);
#if defined (RTC_FEATURE_IRQ_UNMASK_ENABLE)
    RTC_SetIntrUnMask(RTC_0_IRQ, true, P_RTC_FUNC_WATCH);
#endif

#if defined (RTC_FEATURE_TIME_REG_UNIFIED)
    uint32_t un32Time = (ptClock->tTime.un8Sec << RTCC_TIME_CNT_SEC_Pos)
                        | (ptClock->tTime.un8Min << RTCC_TIME_CNT_MIN_Pos)
                        | (ptClock->tTime.un8Hour << RTCC_TIME_CNT_HOUR_Pos);
    SET_RTC_DR_TIME(ptRtc, un32Time);
#else
    SET_RTC_DR_SEC(ptRtc, ptClock->tTime.un8Sec);
    SET_RTC_DR_MIN(ptRtc, ptClock->tTime.un8Min);
    SET_RTC_DR_HOUR(ptRtc, ptClock->tTime.un8Hour);
#endif
#if defined (RTC_FEATURE_DATE_REG_UNIFIED)
    uint32_t un32Date = (ptClock->tDate.un8Day << RTCC_DATE_CNT_DAY_Pos)
                        | (ptClock->tDate.un8Week << RTCC_DATE_CNT_WEEK_Pos)
                        | (ptClock->tDate.un8Month << RTCC_DATE_CNT_MONTH_Pos)
                        | (ptClock->tDate.un8Year << RTCC_DATE_CNT_YEAR_Pos);
    SET_RTC_DR_DATE(ptRtc, un32Date);
#else
    SET_RTC_DR_DAY(ptRtc, ptClock->tDate.un8Day);
    SET_RTC_DR_WEEK(ptRtc, ptClock->tDate.un8Week);
    SET_RTC_DR_MONTH(ptRtc, ptClock->tDate.un8Month);
    SET_RTC_DR_YEAR(ptRtc, ptClock->tDate.un8Year);
#endif
    un32TimeOut = 40000000;
    if(GET_RTC_CR_START(ptRtc))
    {
        SET_RTC_CR_RWMODE(ptRtc, false);
        while(GET_RTC_SR_RWMODE(ptRtc))
        {
            un32TimeOut--;
            if(un32TimeOut == 0)
            {
                return HAL_ERR_HW;
            }
        }
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_RTC_GetClock(RTC_ID_e eId, RTC_TIME_t *ptTime, RTC_DATE_t *ptDate)
{
    RTC_Type *ptRtc;
#if defined (RTC_FEATURE_READ_OPERATION)
    uint32_t un32TimeOut = 40000000;
#endif

    if((uint32_t)eId >= RTC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptRtc = PRV_RTC_GetReg((P_RTC_ID_e)eId);

#if defined (RTC_FEATURE_READ_OPERATION)
    if(GET_RTC_CR_START(ptRtc))
    {
        SET_RTC_CR_RWMODE(ptRtc, true);

        while(!GET_RTC_SR_RWMODE(ptRtc))
        {
            un32TimeOut--;
            if(un32TimeOut == 0)
            {
                return HAL_ERR_HW;
            }
        }
    }
#endif

#if defined (RTC_FEATURE_TIME_REG_UNIFIED)
    uint32_t un32Time = GET_RTC_DR_TIME(ptRtc);
    ptTime->un8Sec = (un32Time & RTCC_TIME_CNT_SEC_Msk) >> RTCC_TIME_CNT_SEC_Pos;
    ptTime->un8Min = (un32Time & RTCC_TIME_CNT_MIN_Msk) >> RTCC_TIME_CNT_MIN_Pos;
    ptTime->un8Hour = (un32Time & RTCC_TIME_CNT_HOUR_Msk) >> RTCC_TIME_CNT_HOUR_Pos;
#else
    ptTime->un8Sec = GET_RTC_DR_SEC(ptRtc);
    ptTime->un8Min = GET_RTC_DR_MIN(ptRtc);
    ptTime->un8Hour = GET_RTC_DR_HOUR(ptRtc);
#endif
#if defined (RTC_FEATURE_DATE_REG_UNIFIED)
    uint32_t un32Date = GET_RTC_DR_DATE(ptRtc);
    ptDate->un8Day = (un32Date & RTCC_DATE_CNT_DAY_Msk) >> RTCC_DATE_CNT_DAY_Pos;
    ptDate->un8Week = (un32Date & RTCC_DATE_CNT_WEEK_Msk) >> RTCC_DATE_CNT_WEEK_Pos;
    ptDate->un8Month = (un32Date & RTCC_DATE_CNT_MONTH_Msk) >> RTCC_DATE_CNT_MONTH_Pos;
    ptDate->un8Year = (un32Date & RTCC_DATE_CNT_YEAR_Msk) >> RTCC_DATE_CNT_YEAR_Pos;
#else
    ptDate->un8Day = GET_RTC_DR_DAY(ptRtc);
    ptDate->un8Week = GET_RTC_DR_WEEK(ptRtc);
    ptDate->un8Month = GET_RTC_DR_MONTH(ptRtc);
    ptDate->un8Year = GET_RTC_DR_YEAR(ptRtc);
#endif

#if defined (RTC_FEATURE_READ_OPERATION)
    un32TimeOut = 40000000;
    if(GET_RTC_CR_START(ptRtc))
    {
        SET_RTC_CR_RWMODE(ptRtc, false);
        while(GET_RTC_SR_RWMODE(ptRtc))
        {
            un32TimeOut--;
            if(un32TimeOut == 0)
            {
                return HAL_ERR_HW;
            }
        }
    }
#endif

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_RTC_SetAlarm(RTC_ID_e eId, RTC_ALARM_t *ptAlarm)
{
    RTC_Type *ptRtc;

    if((uint32_t)eId >= RTC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptRtc = PRV_RTC_GetReg((P_RTC_ID_e)eId);

#if defined (RTC_FEATURE_IRQ_UNMASK_ENABLE)
    RTC_SetIntrUnMask(RTC_0_IRQ, false, P_RTC_FUNC_ALARM);
#endif

    if(ptAlarm->bAlarmEn == true)
    {
        SET_RTC_DR_ALARM_WEEK(ptRtc, ptAlarm->un8Week);
        SET_RTC_DR_ALARM_HOUR(ptRtc, ptAlarm->un8Hour);
        SET_RTC_DR_ALARM_MIN(ptRtc, ptAlarm->un8Min);
        SET_RTC_IER_ALARM_EN(ptRtc, true);
    }
    else
    {
        SET_RTC_IER_ALARM_EN(ptRtc,false);
    }

#if defined (RTC_FEATURE_IRQ_UNMASK_ENABLE)
    RTC_SetIntrUnMask(RTC_0_IRQ, true, P_RTC_FUNC_ALARM);
#endif

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_RTC_SetTimestamp(RTC_ID_e eId, bool bTimestampEn, RTC_TS_EVT_e eTsEvt)
{
#if defined(RTC_FEATURE_TIMESTAMP)
    RTC_Type *ptRtc;

    if((uint32_t)eId >= RTC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptRtc = PRV_RTC_GetReg((P_RTC_ID_e)eId);

    if(bTimestampEn == true)
    {
        SET_RTC_CR_TIMESTAMP_EDGE(ptRtc, eTsEvt);
        SET_RTC_IER_TIMESTAMP_EN(ptRtc, true);
    }
    else
    {
        SET_RTC_IER_TIMESTAMP_EN(ptRtc, false);
    }

    RTC_SetPortMode((P_RTC_ID_e)eId, bTimestampEn, bTimestampEn);

    return HAL_ERR_OK;
#else
    (void)eId;
    (void)bTimestampEn;
    (void)eTsEvt;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_RTC_GetTimestamp(RTC_ID_e eId, RTC_TIME_t *ptTime, RTC_DATE_t *ptDate)
{
#if defined(RTC_FEATURE_TIMESTAMP)
    RTC_Type *ptRtc;

    if((uint32_t)eId >= RTC_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptRtc = PRV_RTC_GetReg((P_RTC_ID_e)eId);

    ptTime->un8Sec = GET_RTC_DR_TIMESTAMP_SEC(ptRtc);
    ptTime->un8Min = GET_RTC_DR_TIMESTAMP_MIN(ptRtc);
    ptTime->un8Hour = GET_RTC_DR_TIMESTAMP_HOUR(ptRtc);
    ptDate->un8Day = GET_RTC_DR_TIMESTAMP_DAY(ptRtc);
    ptDate->un8Week = GET_RTC_DR_TIMESTAMP_WEEK(ptRtc);
    ptDate->un8Month = GET_RTC_DR_TIMESTAMP_MONTH(ptRtc);
    ptDate->un8Year = GET_RTC_DR_TIMESTAMP_YEAR(ptRtc);

    return HAL_ERR_OK;
#else
    (void)eId;
    (void)ptTime;
    (void)ptDate;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_RTC_SetWakeupSrc(RTC_ID_e eId, bool bEnable, bool bExtPinEnable)
{
    (void)eId;
#if defined (RTC_FEATURE_WAKEUP_SOURCE)
    RTC_SetWkupSrc(bEnable, bExtPinEnable); 
    return HAL_ERR_OK;
#else
    (void)eId;
    (void)bEnable;
    (void)bExtPinEnable;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

void PRV_RTC_IRQHandler(RTC_ID_e eId)
{
    RTC_Type *ptRtc;
    RTC_CTRL_BLK_t *ptRcb;
#if defined (RTC_FEATURE_WAKEUP_SOURCE)
    RTC_Context_t *ptContext;
#endif
    uint32_t un32Event = 0;

    ptRtc = PRV_RTC_GetReg((P_RTC_ID_e)eId);
    ptRcb = &s_tRcb[(uint32_t)eId];

#if defined (RTC_FEATURE_WAKEUP_SOURCE)
    if(ptRcb->pContext != NULL)
    {
        ptContext = (RTC_Context_t *)ptRcb->pContext;
        RTC_GetWkupEvent(&ptContext->bWakeup);
    }
#endif
    if(GET_RTC_IER_CONST_PERIOD_FLAG(ptRtc))
    {
        un32Event |= RTC_EVENT_PERIOD;
        SET_RTC_IER_CONST_PERIOD_FLAG(ptRtc, RTC_INTR_CLEAR);
    }

    if(GET_RTC_IER_ALARM_FLAG(ptRtc))
    {
        un32Event |= RTC_EVENT_ALARM;
        SET_RTC_IER_ALARM_FLAG(ptRtc, RTC_INTR_CLEAR);
    }

#if defined (RTC_FEATURE_TIMESTAMP)
    if(GET_RTC_IER_TIMESTAMP_FLAG(ptRtc))
    {
        un32Event |= RTC_EVENT_TIMESTAMP;
        SET_RTC_IER_TIMESTAMP_FLAG(ptRtc, false);
    }
#endif

    if(ptRcb != NULL)
    {
        if(ptRcb->pfnHandler != NULL && un32Event != 0)
        {
            ptRcb->pfnHandler(un32Event,ptRcb->pContext);
        }
    }
}

void RTC0_IRQHandler(void)
{
    PRV_RTC_IRQHandler(RTC_ID_0);
}

#endif /* _RTC */
