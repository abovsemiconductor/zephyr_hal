/**
 *******************************************************************************
 * @file        hal_timer3.c
 * @author      ABOV R&D Division
 * @brief       2N typed timer
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

#if defined(_TIMER3)
#include "hal_timer3.h"
#include "hal_timer3_prv.h"
#if defined(TIMER3_FEATURE_NMI_BLANK) && defined(_NMI)
#include "hpl_nmi.h"
#endif

typedef struct
{
     TIMER3_OPS_e                eOps;
     pfnTIMER3_IRQ_Handler_t    pfnHandler;
     void                       *pContext;

     TIMER3_MODE_e              eMode;
} TIMER3_CTRL_BLK_t;

static TIMER3_CTRL_BLK_t s_tTcb[TIMER3_CH_NUM];

static void PRV_TIMER3_IRQHandler(TIMER3_ID_e eId);

#if defined(TIMER3_FEATURE_NMI_BLANK) && defined(_NMI)
static void PRV_TIMER3_NMIHandler(uint32_t un32Event, void *pContext)
{
    PRV_TIMER3_IRQHandler(TIMER3_ID_0);
}
#endif

static TIMER3_Type *PRV_TIMER3_GetReg(TIMER3_ID_e eId)
{
    return TIMER3_GetReg((uint32_t)eId);
}

static HAL_ERR_e PRV_TIMER3_SetScuEnable(P_TIMER3_ID_e eId, bool bEnable)
{
    return TIMER3_SetScuEnable(eId, bEnable);
}

HAL_ERR_e HAL_TIMER3_Init(TIMER3_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER3_Type *ptTimer;

    if((uint32_t)eId >= TIMER3_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_TIMER3_SetScuEnable((P_TIMER3_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tTcb[(uint32_t)eId], 0x00, sizeof(TIMER3_CTRL_BLK_t));

    ptTimer = PRV_TIMER3_GetReg(eId);
    /* clear control register */
    SET_TIMER3_CR(ptTimer, 0x00);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER3_Uninit(TIMER3_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= TIMER3_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_TIMER3_SetScuEnable((P_TIMER3_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = TIMER3_GetIRQNum((P_TIMER3_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tTcb[(uint32_t)eId], 0x00, sizeof(TIMER3_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER3_SetClkConfig(TIMER3_ID_e eId, TIMER3_CLK_CFG_t *ptClkCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER3_Type *ptTimer;

    if((uint32_t)eId >= TIMER3_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(ptClkCfg->un16PreScale >= TIMER3_PRESCALE_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    ptTimer = PRV_TIMER3_GetReg(eId);

    switch(ptClkCfg->eClk)
    {
        case TIMER3_CLK_MCCR:
            TIMER3_SetMccrClk((P_TIMER3_ID_e)eId, ptTimer, 
                              (P_TIMER3_CLK_MCCR_e)ptClkCfg->uSubClk.eMccr,
                              ptClkCfg->un8MccrDiv);
            break;
        case TIMER3_CLK_EXT:
            TIMER3_SetExtClk((P_TIMER3_ID_e)eId, ptTimer,
                             (P_TIMER3_EXTCLK_EDGE_e)ptClkCfg->uSubClk.eExtClkEdge);
            break;
        case TIMER3_CLK_PCLK:
            TIMER3_SetPClk((P_TIMER3_ID_e)eId, ptTimer,
                           (P_TIMER3_PCLK_DIV_e)P_TIMER3_PCLK_DIV_MAX);
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    /* Prescale */
    SET_TIMER3_PREDR(ptTimer, ptClkCfg->un16PreScale);

    return eErr;
}

HAL_ERR_e HAL_TIMER3_SetConfig(TIMER3_ID_e eId, TIMER3_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER3_Type *ptTimer;
    TIMER3_CTRL_BLK_t *ptTcb;

    if((uint32_t)eId >= TIMER3_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(ptCfg->eMode >= TIMER3_MODE_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    ptTimer = PRV_TIMER3_GetReg(eId);
    ptTcb = &s_tTcb[eId];

    /* Clear Count Register */
    SET_TIMER3_CR_CLR(ptTimer, true);

    /* working mode */
    SET_TIMER3_CR_MODE(ptTimer, (uint8_t)ptCfg->eMode);

#if TIMER3_INTERRUPT_ENABLE_CONCURRENT
    SET_TIMER3_IER(ptTimer, (uint8_t)ptCfg->un8IntrEnable);
#else
    /* clear interrupt enable*/
    SET_TIMER3_IER(ptTimer, 0x00);

    if(ptCfg->un8IntrEnable)
    {
        if(ptCfg->un8IntrEnable & TIMER3_INTR_PERIOD_MATCH)
        {
            SET_TIMER3_IER_MATCH_P_EN(ptTimer, true);
        }
        if(ptCfg->un8IntrEnable & TIMER3_INTR_MATCH_CH_A)
        {
            SET_TIMER3_IER_MATCH_A_EN(ptTimer, true);
        }
        if(ptCfg->un8IntrEnable & TIMER3_INTR_MATCH_CH_B)
        {
            SET_TIMER3_IER_MATCH_B_EN(ptTimer, true);
        }
        if(ptCfg->un8IntrEnable & TIMER3_INTR_MATCH_CH_C)
        {
            SET_TIMER3_IER_MATCH_C_EN(ptTimer, true);
        }
        if(ptCfg->un8IntrEnable & TIMER3_INTR_BOTTOM)
        {
            SET_TIMER3_IER_BOTTOM_EN(ptTimer, true);
        }

        /* if capture mode select */
        if(ptCfg->eMode == TIMER3_MODE_CAPTURE && ptCfg->un8IntrEnable & TIMER3_INTR_CAPTURE)
        {
            SET_TIMER3_IER_CAP_EN(ptTimer, true);
        }

        /* if high-impedance enable */
        if(ptCfg->tOutputCfg.bHizEnable == true && ptCfg->un8IntrEnable & TIMER3_INTR_HIZ)
        {
            SET_TIMER3_IER_HIZ_EN(ptTimer, true);
        }
    }
#endif

    /* if capture mode select */
    if(ptCfg->eMode == TIMER3_MODE_CAPTURE)
    {
        SET_TIMER3_CR_CAPPORT_POL(ptTimer, (uint8_t)ptCfg->eCapClr);
    }

    /* output mode and configuration */
    SET_TIMER3_CR_XA_PORT_POL(ptTimer, (uint8_t)ptCfg->tOutputCfg.eXAPol);
    SET_TIMER3_CR_XB_PORT_POL(ptTimer, (uint8_t)ptCfg->tOutputCfg.eXBPol);
    SET_TIMER3_CR_OUTPUT_MODE(ptTimer, (uint8_t)ptCfg->tOutputCfg.eOutputMode);

    /* output delay configuration */
    SET_TIMER3_CR_OUTPUT_DLY(ptTimer, ptCfg->tDlyCfg.bEnable);
    SET_TIMER3_CR_OUTPUT_DLY_POS(ptTimer, (uint8_t)ptCfg->tDlyCfg.ePos);
    SET_TIMER3_CR_OUTPUT_DLY_VALUE(ptTimer, (uint16_t)ptCfg->tDlyCfg.un16Value);

    /* high-impedance configuration */
    SET_TIMER3_CR_HIZ_EN(ptTimer, ptCfg->tOutputCfg.bHizEnable);
    SET_TIMER3_CR_HIZ_EDGE(ptTimer, (uint8_t)ptCfg->tOutputCfg.eHizEdge);
    SET_TIMER3_CR_HIZ_SRC(ptTimer, (uint8_t)ptCfg->tOutputCfg.eHizSrc);

    /* reload */
    SET_TIMER3_CR_RELOAD(ptTimer, ptCfg->eReload);

    /* period match counter for interrupt */
    SET_TIMER3_CR_PERIOD_MATCH_CNT(ptTimer, ptCfg->un8PeriodMatchCnt);

    /* Set Period */
    SET_TIMER3_DR_P(ptTimer, ptCfg->utData.tGRD.un16DataP);
    /* Set Data A */
    SET_TIMER3_DR_A(ptTimer, ptCfg->utData.tGRD.un16DataA);
    /* Set Data B */
    SET_TIMER3_DR_B(ptTimer, ptCfg->utData.tGRD.un16DataB);
    /* Set Data C */
    SET_TIMER3_DR_C(ptTimer, ptCfg->utData.tGRD.un16DataC);

    ptTcb->eMode = ptCfg->eMode;

    /* CR Register MS, FORCA, DLYEN, DLYPOS, CPOL, UPDT, PMOC */
    /* Update CR Register */
#if 0
    {
        uint32_t un32Data = 0, un32Reg = 0;
        un32Data = SET_TIMER3_CR_MODE_POS(ptCfg->eMode)
                   | SET_TIMER3_CR_FORCA_POS(ptCfg->tOutputCfg.eOutputMode)
                   | SET_TIMER3_CR_DLYEN_POS(ptCfg->tDlyCfg.bDlyEnable)
                   | SET_TIMER3_CR_DLYPOS_POS(ptCfg->tDlyCfg.eDlyPos)
                   | SET_TIMER3_CR_CAPPORT_POS(ptCfg->eCapClr)
                   | SET_TIMER3_CR_RELOAD_POS(ptCfg->eReload)
                   | SET_TIMER3_CR_PMOC_POS(ptCfg->ePeriodMatchCnt);

        un32Reg = (GET_TIMER3_CR(ptTimer) 
                  & ~(TIMER3_CR_MODE_MSK
                      | TIMER3_CR_FORCA_MSK 
                      | TIMER3_CR_DLYEN_MSK
                      | TIMER3_CR_DLYPOS_MSK
                      | TIMER3_CR_RELOAD_MSK
                      | TIMER3_CR_PMOC_MSK));

        SET_TIMER3_CR(ptTimer, (un32Reg | un32Data));
    }
#endif

    return eErr;
}

HAL_ERR_e HAL_TIMER3_SetAdcTrgConfig(TIMER3_ID_e eId, TIMER3_ADCTRG_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER3_Type *ptTimer;

    if((uint32_t)eId >= TIMER3_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER3_GetReg(eId);
    SET_TIMER3_DR_ADC(ptTimer, ptCfg->un16GenData);
    SET_TIMER3_ADCTRG(ptTimer, ptCfg->un8Enable);

    return eErr;
}

HAL_ERR_e HAL_TIMER3_SetIRQ(TIMER3_ID_e eId, TIMER3_OPS_e eOps, pfnTIMER3_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio, bool bBlnkNonMask)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER3_CTRL_BLK_t *ptTcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= TIMER3_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

#if defined(TIMER3_FEATURE_NMI_BLANK) && defined(_NMI)
#else
    if(bBlnkNonMask == true)
    {
        return HAL_ERR_NOT_SUPPORTED;
    }
#endif

    ptTcb = &s_tTcb[(uint32_t)eId];
    eIrq = TIMER3_GetIRQNum((P_TIMER3_ID_e)eId);

    switch(eOps)
    {
        case TIMER3_OPS_INTR:
#if defined(TIMER3_FEATURE_IRQ_UNMASK_ENABLE)
            TIMER3_SetIntrUnMask(eIrq, true);
#endif
#if defined(TIMER3_FEATURE_NMI_BLANK) && defined(_NMI)
            eErr = HPL_NMI_SetIRQ(NMI_INTR_TIMER3_BLNK, &PRV_TIMER3_NMIHandler, NULL, bBlnkNonMask);
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            ptTcb->pfnHandler = pfnHandler;
            ptTcb->pContext = pContext;
            break;
        case TIMER3_OPS_POLL:
        default:
#if defined(TIMER3_FEATURE_IRQ_UNMASK_ENABLE)
            TIMER3_SetIntrUnMask(eIrq, false);
#endif
#if defined(TIMER3_FEATURE_NMI_BLANK) && defined(_NMI)
            eErr = HPL_NMI_SetIRQ(NMI_INTR_TIMER3_BLNK, NULL, NULL, false);
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptTcb->pContext = NULL;
            ptTcb->pfnHandler = NULL;
            break;
    }

    ptTcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_TIMER3_SetOutputPort(TIMER3_ID_e eId, uint8_t un8PortEnable, uint8_t un8PortLevel)
{
    TIMER3_Type *ptTimer;
    uint32_t un32Data = 0;

    if((uint32_t)eId >= TIMER3_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER3_GetReg(eId);

    un32Data = (GET_TIMER3_OUTCR(ptTimer) & ~(TIMER3_OUTCR_EN_LVL_MSK));
    SET_TIMER3_OUTCR(ptTimer, (un32Data 
                     | (TIMER3_OUTCR_WTIDKY << TIMER3_OUTCR_WTIDKY_POS)
                     | ((un8PortEnable & TIMER3_OUTCR_EN_MSK) << TIMER3_OUTCR_EN_POS) 
                     | (un8PortLevel & TIMER3_OUTCR_LVL_MSK)));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER3_GetStatus(TIMER3_ID_e eId, uint32_t *pun32Status)
{
    TIMER3_Type *ptTimer;

    if((uint32_t)eId >= TIMER3_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER3_GetReg(eId);
    *pun32Status = GET_TIMER3_IER_FLAG(ptTimer);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER3_SetData(TIMER3_ID_e eId, TIMER3_DATA_e eSel, uint32_t un32Data)
{
    TIMER3_Type *ptTimer;

    if((uint32_t)eId >= TIMER3_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER3_GetReg(eId);

    switch(eSel)
    {
        case TIMER3_DATA_P:
             SET_TIMER3_DR_P(ptTimer, un32Data);
             break;
        case TIMER3_DATA_A:
             SET_TIMER3_DR_A(ptTimer, un32Data);
             break;
        case TIMER3_DATA_B:
             SET_TIMER3_DR_B(ptTimer, un32Data);
             break;
        case TIMER3_DATA_C:
             SET_TIMER3_DR_C(ptTimer, un32Data);
             break;
        case TIMER3_DATA_ADC:
             SET_TIMER3_DR_ADC(ptTimer, un32Data);
             break;
        default:
             break;
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER3_GetData(TIMER3_ID_e eId, TIMER3_DATA_e eSel, uint32_t *pun32Data)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    TIMER3_Type *ptTimer;

    if((uint32_t)eId >= TIMER3_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER3_GetReg(eId);

    switch(eSel)
    {
        case TIMER3_DATA_P:
             *pun32Data = GET_TIMER3_DR_P(ptTimer);
             break;
        case TIMER3_DATA_A:
             *pun32Data = GET_TIMER3_DR_A(ptTimer);
             break;
        case TIMER3_DATA_B:
             *pun32Data = GET_TIMER3_DR_B(ptTimer);
             break;
        case TIMER3_DATA_C:
             *pun32Data = GET_TIMER3_DR_C(ptTimer);
             break;
        case TIMER3_DATA_CAP:
             *pun32Data = GET_TIMER3_DR_CAP(ptTimer);
             break;
        case TIMER3_DATA_ADC:
             *pun32Data = GET_TIMER3_DR_ADC(ptTimer);
             break;
        default:
            *pun32Data = 0;
             eErr = HAL_ERR_PARAMETER;
             break;
    }

    return eErr;
}

HAL_ERR_e HAL_TIMER3_Start(TIMER3_ID_e eId)
{
    TIMER3_Type *ptTimer;

    if((uint32_t)eId >= TIMER3_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER3_GetReg(eId);
    SET_TIMER3_CR_EN(ptTimer, true);
    return HAL_ERR_OK;
}

HAL_ERR_e HAL_TIMER3_Stop(TIMER3_ID_e eId)
{
    TIMER3_Type *ptTimer;

    if((uint32_t)eId >= TIMER3_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptTimer = PRV_TIMER3_GetReg(eId);
    SET_TIMER3_CR_EN(ptTimer, false);
    return HAL_ERR_OK;
}

static void PRV_TIMER3_IRQHandler(TIMER3_ID_e eId)
{
    TIMER3_Type *ptTimer;
    TIMER3_CTRL_BLK_t *ptTcb;
    uint32_t un32Event=0;

    ptTimer = PRV_TIMER3_GetReg(eId);
    ptTcb = &s_tTcb[eId];

    /* get interrupt flag */
    un32Event = (uint32_t)GET_TIMER3_IER_FLAG(ptTimer);

    /* clear interrupt flag */
    SET_TIMER3_IER_FLAG(ptTimer, (uint8_t)(un32Event & 0xFF));

    if(ptTcb->pfnHandler != NULL && un32Event)
    {
        ptTcb->pfnHandler(un32Event, ptTcb->pContext);
    }
}

void TIMER30_IRQHandler(void)
{
    PRV_TIMER3_IRQHandler(TIMER3_ID_0);
}

void TIMER31_IRQHandler(void)
{
    PRV_TIMER3_IRQHandler(TIMER3_ID_1);
}

void TIMER32_IRQHandler(void)
{
    PRV_TIMER3_IRQHandler(TIMER3_ID_2);
}

void TIMER33_IRQHandler(void)
{
    PRV_TIMER3_IRQHandler(TIMER3_ID_3);
}

void TIMER34_IRQHandler(void)
{
    PRV_TIMER3_IRQHandler(TIMER3_ID_4);
}

void TIMER35_IRQHandler(void)
{
    PRV_TIMER3_IRQHandler(TIMER3_ID_5);
}

void TIMER36_IRQHandler(void)
{
    PRV_TIMER3_IRQHandler(TIMER3_ID_6);
}

void TIMER37_IRQHandler(void)
{
    PRV_TIMER3_IRQHandler(TIMER3_ID_7);
}

void TIMER38_IRQHandler(void)
{
    PRV_TIMER3_IRQHandler(TIMER3_ID_8);
}

void TIMER39_IRQHandler(void)
{
    PRV_TIMER3_IRQHandler(TIMER3_ID_9);
}

#endif /* _TIMER3 */
