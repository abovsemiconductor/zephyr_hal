/**
 *******************************************************************************
 * @file        hal_afe.c
 * @author      ABOV R&D Division
 * @brief       Analog Front End (AFE)
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

#if defined(_AFE)
#include "hal_afe.h"
#include "hal_afe_prv.h"

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
#include "hpl_nmi.h"
#endif

typedef struct
{
    AFE_OPS_e                 eOps;

    pfnAFE_IRQ_Handler_t      pfnHandler;
    void                      *pContext;

    AFE_MODE_e                eMode;
    AFE_CMP_INTR_TRG_e        eIntrTrg;
    AFE_CMP_INTR_TRG_POL_e    eIntrTrgPol;

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
    bool                      bNmiEnable;
#endif

} AFE_CTRL_BLK_t;

static AFE_CTRL_BLK_t s_tAcb[AFE_CH_NUM];

static void PRV_AFE_IRQHandler(AFE_ID_e eId);

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
static void PRV_AFE_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < AFE_CH_NUM; i++)
    {
        if(s_tAcb[i].bNmiEnable == true)
        {
            PRV_AFE_IRQHandler((AFE_ID_e)i);
        }
    }
}
#endif

static AFE_Type *PRV_AFE_GetReg(P_AFE_ID_e eId)
{
    return AFE_GetReg((P_AFE_ID_e)eId);
}

static HAL_ERR_e PRV_AFE_SetScuEnable(P_AFE_ID_e eId, bool bEnable)
{
    return AFE_SetScuEnable((P_AFE_ID_e)eId, bEnable);
}

HAL_ERR_e HAL_AFE_Init(AFE_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    AFE_Type *ptAfe;

    if((uint32_t)eId >= AFE_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_AFE_SetScuEnable((P_AFE_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tAcb[(uint32_t)eId], 0, sizeof(AFE_CTRL_BLK_t));

    ptAfe = PRV_AFE_GetReg((P_AFE_ID_e)eId);

    SET_AFE_CR_OPAMP_EN(ptAfe, eId, true);

    return eErr;
}

HAL_ERR_e HAL_AFE_Uninit(AFE_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    AFE_Type *ptAfe;
    IRQn_Type eIrq;

    if((uint32_t)eId >= AFE_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAfe = PRV_AFE_GetReg((P_AFE_ID_e)eId);
    SET_AFE_CR_OPAMP_EN(ptAfe, eId, false);

    eErr = PRV_AFE_SetScuEnable((P_AFE_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcily, disable NVIC Interrupt */
    eIrq = AFE_GetIRQNum((P_AFE_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    memset(&s_tAcb[(uint32_t)eId], 0, sizeof(AFE_CTRL_BLK_t));

    return eErr;
}

HAL_ERR_e HAL_AFE_SetConfig(AFE_ID_e eId, AFE_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    AFE_Type *ptAfe;
    AFE_CTRL_BLK_t *ptAcb;

    if((uint32_t)eId >= AFE_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAfe = PRV_AFE_GetReg((P_AFE_ID_e)eId);
    ptAcb = &s_tAcb[(uint32_t)eId];

    switch(ptCfg->eMode)
    {
        case AFE_MODE_CMP:
            SET_AFE_CR_CMP_INTR_TRG(ptAfe, eId, ptCfg->tCmp.eIntrTrg);
            SET_AFE_CR_CMP_INTR_POL(ptAfe, eId, ptCfg->tCmp.eIntrTrgPol);
            SET_AFE_CR_CMP_OUTPUT_POL(ptAfe, eId, ptCfg->tCmp.bTrgOutPol);
            SET_AFE_DR_CMP_DBNC_SHIFT(ptAfe, eId, ptCfg->tCmp.un8DebCnt);
            SET_AFE_CR_CMP_EN(ptAfe, eId, true);
            ptAcb->eIntrTrg = ptCfg->tCmp.eIntrTrg;
            ptAcb->eIntrTrgPol = ptCfg->tCmp.eIntrTrgPol;
            break;
        case AFE_MODE_OPAMP:
        case AFE_MODE_UNITY_GAIN:
            SET_AFE_CR_CMP_EN(ptAfe, eId, false);
            if(ptCfg->eMode == AFE_MODE_UNITY_GAIN)
            {
                SET_AFE_CR_UGAIN_EN(ptAfe, eId, true);
            }
            else
            {
                SET_AFE_CR_UGAIN_EN(ptAfe, eId, false);
            }
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    if(eErr == HAL_ERR_OK)
    {
        ptAcb->eMode = ptCfg->eMode;
    }
    else
    {
        ptAcb->eMode = AFE_MODE_MAX;
    }

    return eErr;
}

HAL_ERR_e HAL_AFE_SetIRQ(AFE_ID_e eId, AFE_OPS_e eOps, pfnAFE_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio, bool bNonMask)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    AFE_CTRL_BLK_t *ptAcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= AFE_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAcb = &s_tAcb[(uint32_t)eId];
    eIrq = AFE_GetIRQNum((P_AFE_ID_e)eId);

    switch(eOps)
    {
        case AFE_OPS_INTR:
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            if(ptAcb->bNmiEnable == true)
            {
                (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
                ptAcb->bNmiEnable = false;
            }
#endif /* _NMI && CONFIG_NMI_ANY_INTERRUPT */

            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            ptAcb->pfnHandler = pfnHandler;
            ptAcb->pContext = pContext;
            break;

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
        case AFE_OPS_NMI:
            eErr = HPL_NMI_SetSource(eIrq, &PRV_AFE_NMIHandler, pContext, true);
            ptAcb->bNmiEnable = true;
            if(eErr == HAL_ERR_OK)
            {
                ptAcb->pfnHandler = pfnHandler;
                ptAcb->pContext = pContext;
            }
            break;
#endif /* _NMI && CONFIG_NMI_ANY_INTERRUPT */
        case AFE_OPS_POLL:
        default:
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            if(ptAcb->bNmiEnable == true)
            {
                (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
                ptAcb->bNmiEnable = false;
            }
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptAcb->pContext = NULL;
            ptAcb->pfnHandler = NULL;
            break;
    }

    ptAcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_AFE_Start(AFE_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    AFE_Type *ptAfe;
    AFE_CTRL_BLK_t *ptAcb;

    if((uint32_t)eId >= AFE_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAfe = AFE_GetReg((P_AFE_ID_e)eId);
    ptAcb = &s_tAcb[(uint32_t)eId];

    if(ptAcb->eMode == AFE_MODE_CMP)
    {
        SET_AFE_IER_CMP_FLAG_CLR(ptAfe, eId, true);

        if(ptAcb->eOps == AFE_OPS_INTR 
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
           || ptAcb->eOps == AFE_OPS_NMI)
#else
           )
#endif
        {
            SET_AFE_IER_CMP_EN(ptAfe, eId, true);
        }
    }
    else
    {
        SET_AFE_IER_CMP_EN(ptAfe, eId, false);
    }

    return eErr;
}

HAL_ERR_e HAL_AFE_Stop(AFE_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    AFE_Type *ptAfe;

    if((uint32_t)eId >= AFE_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAfe = AFE_GetReg((P_AFE_ID_e)eId);

    SET_AFE_IER_CMP_EN(ptAfe, eId, false);

    return eErr;
}

HAL_ERR_e HAL_AFE_SetWaitComplete(AFE_ID_e eId, uint32_t un32Timeout)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    AFE_Type *ptAfe;
    AFE_CTRL_BLK_t *ptAcb;

    if((uint32_t)eId >= AFE_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptAfe = AFE_GetReg((P_AFE_ID_e)eId);
    ptAcb = &s_tAcb[(uint32_t)eId];

    if(ptAcb->eMode == AFE_MODE_CMP)
    {
        while(!GET_AFE_IER_CMP_FLAG(ptAfe, eId))
        {
            un32Timeout--;
            if(un32Timeout == 0)
            {
                eErr = HAL_ERR_TIMEOUT;
                break;
            }
        }
        SET_AFE_IER_CMP_FLAG_CLR(ptAfe, eId, true);
    }

    return eErr;
}

static void PRV_AFE_IRQHandler(AFE_ID_e eId)
{
    AFE_Type *ptAfe;
    AFE_CTRL_BLK_t *ptAcb = NULL;
    uint32_t un32Status = 0;
    uint32_t un32Event = 0;
    AFE_Context_t *ptContext;
    AFE_CMP_INTR_TRG_POL_e eIntrTrgPol = AFE_CMP_INTR_TRG_POL_MAX;

    ptAfe = PRV_AFE_GetReg((P_AFE_ID_e)eId);
    ptAcb = &s_tAcb[(uint32_t)eId];

    un32Status = GET_AFE_IER_SR(ptAfe);
    if(un32Status & AFE_INTR_ASSERTED(eId))
    {
        eIntrTrgPol = (AFE_CMP_INTR_TRG_POL_e)GET_AFE_SR_EDGE_POL_FLAG(ptAfe, eId);
        SET_AFE_IER_CMP_FLAG_CLR(ptAfe, eId, true);
        ptContext = (AFE_Context_t *)ptAcb->pContext;
        ptContext->eId = eId;
    }

    switch(ptAcb->eIntrTrg)
    {
        case AFE_CMP_INTR_TRG_LEVEL:
            if(ptAcb->eIntrTrgPol == AFE_CMP_INTR_TRG_POL_LOW_FALLING)
            {
                un32Event = AFE_CMP_EVENT_LOW;
            }
            else
            {
                un32Event = AFE_CMP_EVENT_HIGH;
            }
            break;
        case AFE_CMP_INTR_TRG_SINGLE_EDGE:
            if(eIntrTrgPol == AFE_CMP_INTR_TRG_POL_LOW_FALLING)
            {
                un32Event = AFE_CMP_EVENT_FALLING;
            }
            else
            {
                un32Event = AFE_CMP_EVENT_RISING;
            }
            break;
        case AFE_CMP_INTR_TRG_BOTH_EDGE:
            if(eIntrTrgPol == AFE_CMP_INTR_TRG_POL_LOW_FALLING)
            {
                un32Event = AFE_CMP_EVENT_FALLING;
            }
            else
            {
                un32Event = AFE_CMP_EVENT_RISING;
            }
            break;
        default:
            break;
    }

    if(ptAcb->pfnHandler != NULL && un32Event != 0)
    {
        ptAcb->pfnHandler(un32Event, ptAcb->pContext);
    }
}

void AFE0_IRQHandler(void)
{
    PRV_AFE_IRQHandler(AFE_ID_0);
}

void AFE1_IRQHandler(void)
{
    PRV_AFE_IRQHandler(AFE_ID_1);
}

void AFE2_IRQHandler(void)
{
    PRV_AFE_IRQHandler(AFE_ID_2);
}

void AFE3_IRQHandler(void)
{
    PRV_AFE_IRQHandler(AFE_ID_3);
}

#endif /* _AFE */
