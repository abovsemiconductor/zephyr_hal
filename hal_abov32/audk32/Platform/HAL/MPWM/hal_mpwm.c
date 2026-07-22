/**
 *******************************************************************************
 * @file        hal_mpwm.c
 * @author      ABOV R&D Division
 * @brief       Motor Pulse Width Modulation
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

#if defined(_MPWM)
#include "hal_mpwm.h"
#include "hal_mpwm_prv.h"

#if defined(_NMI) && (defined(CONFIG_NMI_ANY_INTERRUPT) || defined(MPWM_FEATURE_NMI))
#include "hpl_nmi.h"
#endif

typedef struct
{
    MPWM_OPS_e               eOps;
    pfnMPWM_IRQ_Handler_t    pfnPROTHandler;
    void                     *pPROTContext;
    pfnMPWM_IRQ_Handler_t    pfnOVHandler;
    void                     *pOVContext;
#if defined(MPWM_FEATURE_SIGNAL_SINGLE_INTERRUPT)
    pfnMPWM_IRQ_Handler_t    pfnPWMHandler;
    void                     *pPWMContext;
#else
    pfnMPWM_IRQ_Handler_t    pfnPWMUHandler;
    void                     *pPWMUContext;
    pfnMPWM_IRQ_Handler_t    pfnPVHandler;
    void                     *pPVContext;
    pfnMPWM_IRQ_Handler_t    pfnPWHandler;
    void                     *pPWContext;
#endif

    MPWM_MODE_e              eMode;
    uint8_t                  un8PROTIntr;
    uint8_t                  un8OVIntr;
#if defined(_NMI) 
#if defined(MPWM_FEATURE_NMI)
    bool                     bProtNonMask;
    bool                     bOVNonMask;
#endif
#if defined(CONFIG_NMI_ANY_INTERRUPT) 
    bool                     bNmiEnable;
    MPWM_INTR_HDLR_e         eHdlr;
#endif
#endif
} MPWM_CTRL_BLK_t;

static MPWM_CTRL_BLK_t s_tMcb[MPWM_CH_NUM];
static void PRV_MPWM_PROTIRQHandler(MPWM_ID_e eId);
static void PRV_MPWM_OVIRQHandler(MPWM_ID_e eId);

#if defined(MPWM_FEATURE_SIGNAL_SINGLE_INTERRUPT)
static void PRV_MPWM_PWMIRQHandler(MPWM_ID_e eId);
#else
static void PRV_MPWM_PWMUIRQHandler(MPWM_ID_e eId);
static void PRV_MPWM_PVIRQHandler(MPWM_ID_e eId);
static void PRV_MPWM_PWIRQHandler(MPWM_ID_e eId);
#endif

#if defined(_NMI) 
#if defined(CONFIG_NMI_ANY_INTERRUPT) 
static void PRV_MPWM_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < MPWM_CH_NUM; i++)
    {
        if(s_tMcb[i].bNmiEnable == true)
        {
            switch(s_tMcb[i].eHdlr)
            {
                case MPWM_INTR_HDLR_PROTECTION:
                    (void)PRV_MPWM_PROTIRQHandler((MPWM_ID_e)i);
                    break;
                case MPWM_INTR_HDLR_OVERVOLTAGE:
                    (void)PRV_MPWM_OVIRQHandler((MPWM_ID_e)i);
                    break;
#if defined(MPWM_FEATURE_SIGNAL_SINGLE_INTERRUPT)
                case MPWM_INTR_HDLR_PWM:
                    (void)PRV_MPWM_PWMIRQHandler((MPWM_ID_e)i);
                    break;
#else
                case MPWM_INTR_HDLR_SIG_U:
                    (void)PRV_MPWM_PWMUIRQHandler((MPWM_ID_e)i);
                    break;
                case MPWM_INTR_HDLR_SIG_V:
                    (void)PRV_MPWM_PVIRQHandler((MPWM_ID_e)i);
                    break;
                case MPWM_INTR_HDLR_SIG_W:
                    (void)PRV_MPWM_PWIRQHandler((MPWM_ID_e)i);
                    break;
#endif
                default:
                    break;
            }
        }
    }
}
#endif

#if defined(MPWM_FEATURE_NMI)
static void PRV_MPWM_OVPNMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < MPWM_CH_NUM; i++)
    {
        if(s_tMcb[i].bOVNonMask == true)
        {
            HPL_NMI_SetEnable((NMI_INTR_e)((uint32_t)NMI_INTR_OVP0 + (i*2)), false);
            PRV_MPWM_OVIRQHandler((MPWM_ID_e)i);
        }
    }
}

static void PRV_MPWM_PROTNMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < MPWM_CH_NUM; i++)
    {
        if(s_tMcb[i].bProtNonMask == true)
        {
            HPL_NMI_SetEnable((NMI_INTR_e)((uint32_t)NMI_INTR_PROT0 + (i*2)), false);
            PRV_MPWM_PROTIRQHandler((MPWM_ID_e)i);
        }
    }
}
#endif

static HAL_ERR_e PRV_MPWM_SetNMI(MPWM_ID_e eId, IRQn_Type eIrq, MPWM_INTR_HDLR_e eHdlr, 
                            void *pContext, bool bEnable)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    NMI_INTR_e eNmi = NMI_INTR_MAX;
    pfnNMI_IRQ_Handler_t pfnHandler;
    MPWM_CTRL_BLK_t *ptMcb;

    ptMcb = &s_tMcb[(uint32_t)eId];

    switch(eHdlr)
    {
        case MPWM_INTR_HDLR_PROTECTION:
#if defined(MPWM_FEATURE_NMI)
            ptMcb->bProtNonMask = bEnable;
            pfnHandler = &PRV_MPWM_PROTNMIHandler;
            eNmi = (NMI_INTR_e)((uint32_t)NMI_INTR_PROT0 + ((uint32_t)eId * 2));
            eErr = HPL_NMI_SetIRQ(eNmi, pfnHandler, NULL, bEnable);
#elif defined(CONFIG_NMI_ANY_INTERRUPT)
            ptMcb->eHdlr = eHdlr;
            ptMcb->bNmiEnable = bEnable;
            eErr = HPL_NMI_SetSource(eIrq, &PRV_MPWM_NMIHandler, pContext, bEnable);
#endif
            break;
        case MPWM_INTR_HDLR_OVERVOLTAGE:
#if defined(MPWM_FEATURE_NMI)
            ptMcb->bOVNonMask = bEnable;
            pfnHandler = &PRV_MPWM_OVPNMIHandler;
            eNmi = (NMI_INTR_e)((uint32_t)NMI_INTR_OVP0 + ((uint32_t)eId * 2));
            eErr = HPL_NMI_SetIRQ(eNmi, pfnHandler, NULL, bEnable);
#elif defined(CONFIG_NMI_ANY_INTERRUPT)
            ptMcb->eHdlr = eHdlr;
            ptMcb->bNmiEnable = bEnable;
            eErr = HPL_NMI_SetSource(eIrq, &PRV_MPWM_NMIHandler, pContext, bEnable);
#endif
            break;

#if defined(CONFIG_NMI_ANY_INTERRUPT)
#if defined(MPWM_FEATURE_SIGNAL_SINGLE_INTERRUPT)
        case MPWM_INTR_HDLR_PWM:
#else
        case MPWM_INTR_HDLR_SIG_U:
        case MPWM_INTR_HDLR_SIG_V:
        case MPWM_INTR_HDLR_SIG_W:
#endif
            ptMcb->eHdlr = eHdlr;
            ptMcb->bNmiEnable = bEnable;
            eErr = HPL_NMI_SetSource(eIrq, &PRV_MPWM_NMIHandler, pContext, bEnable);
#endif
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    return eErr;
}
#endif /* _NMI */

static MPWM_Type *PRV_MPWM_GetReg(MPWM_ID_e eId)
{
    return MPWM_GetReg((uint32_t)eId);
}

static HAL_ERR_e PRV_MPWM_SetScuEnable(P_MPWM_ID_e eId, bool bEnable)
{
    return MPWM_SetScuEnable(eId, bEnable);
}

static HAL_ERR_e PRV_MPWM_SetIRQHandler(MPWM_ID_e eId, MPWM_INTR_HDLR_e eHdlr,
                            pfnMPWM_IRQ_Handler_t pfnHandler, void *pContext)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    MPWM_CTRL_BLK_t *ptMcb;

    ptMcb = &s_tMcb[(uint32_t)eId];

    switch(eHdlr)
    {
        case MPWM_INTR_HDLR_PROTECTION:
            ptMcb->pfnPROTHandler = pfnHandler;
            ptMcb->pPROTContext = pContext;
            break;
        case MPWM_INTR_HDLR_OVERVOLTAGE:
            ptMcb->pfnOVHandler = pfnHandler;
            ptMcb->pOVContext = pContext;
            break;
#if defined(MPWM_FEATURE_SIGNAL_SINGLE_INTERRUPT)
        case MPWM_INTR_HDLR_PWM:
            ptMcb->pfnPWMHandler = pfnHandler;
            ptMcb->pPWMContext = pContext;
            break;
#else
        case MPWM_INTR_HDLR_SIG_U:
            ptMcb->pfnPWMUHandler = pfnHandler;
            ptMcb->pPWMUContext = pContext;
            break;
        case MPWM_INTR_HDLR_SIG_V:
            ptMcb->pfnPVHandler = pfnHandler;
            ptMcb->pPVContext = pContext;
            break;
        case MPWM_INTR_HDLR_SIG_W:
            ptMcb->pfnPWHandler = pfnHandler;
            ptMcb->pPWContext = pContext;
            break;
#endif
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    return eErr;

}

static HAL_ERR_e PRV_MPWM_SetPDConfig(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_SD_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    MPWM_Type *ptMpwm;

    ptMpwm = PRV_MPWM_GetReg(eId);
    switch(eSig)
    {
        case MPWM_SIG_U:
            /* Signal-U High Duty */
            SET_MPWM_DR_DUTY_UH_VAL(ptMpwm, (uint16_t)ptCfg->un16HDuty);
            /* Signal-U Low Duty */
            SET_MPWM_DR_DUTY_UL_VAL(ptMpwm, (uint16_t)ptCfg->un16LDuty);
            break;        
        case MPWM_SIG_V:
            /* Signal-V High Duty */
            SET_MPWM_DR_DUTY_VH_VAL(ptMpwm, (uint16_t)ptCfg->un16HDuty);
            /* Signal-V Low Duty */
            SET_MPWM_DR_DUTY_VL_VAL(ptMpwm, (uint16_t)ptCfg->un16LDuty);
            break;        
        case MPWM_SIG_W:
            /* Signal-W High Duty */
            SET_MPWM_DR_DUTY_WH_VAL(ptMpwm, (uint16_t)ptCfg->un16HDuty);
            /* Signal-W Low Duty */
            SET_MPWM_DR_DUTY_WL_VAL(ptMpwm, (uint16_t)ptCfg->un16LDuty);
            break;        
        default:
            eErr = HAL_ERR_PARAMETER;
            break;        
    }

    return eErr;
}

static HAL_ERR_e PRV_MPWM_SetPPConfig(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_SP_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    MPWM_Type *ptMpwm;

    ptMpwm = PRV_MPWM_GetReg(eId);

    switch(eSig)
    {
        case MPWM_SIG_U:
            /* Signal-U High Output, Start, and Force Level */
            SET_MPWM_CR_UH_OUTPUT_LVL(ptMpwm, (uint8_t)ptCfg->tHPort.eOutLevel);
            SET_MPWM_CR_UH_INV_START_LVL(ptMpwm, (uint8_t)ptCfg->tHPort.eStartLevel);
            SET_MPWM_CR_UH_FORCE_LVL(ptMpwm, (uint8_t)ptCfg->tHPort.eForceLevel);

            /* Signal-U Low Output, Start, and Force Level */
            SET_MPWM_CR_UL_OUTPUT_LVL(ptMpwm, (uint8_t)ptCfg->tLPort.eOutLevel);
            SET_MPWM_CR_UL_INV_START_LVL(ptMpwm, (uint8_t)ptCfg->tLPort.eStartLevel);
            SET_MPWM_CR_UL_FORCE_LVL(ptMpwm, (uint8_t)ptCfg->tLPort.eForceLevel);
            break;        
        case MPWM_SIG_V:
            /* Signal-V High Output, Start, and Force Level */
            SET_MPWM_CR_VH_OUTPUT_LVL(ptMpwm, (uint8_t)ptCfg->tHPort.eOutLevel);
            SET_MPWM_CR_VH_INV_START_LVL(ptMpwm, (uint8_t)ptCfg->tHPort.eStartLevel);
            SET_MPWM_CR_VH_FORCE_LVL(ptMpwm, (uint8_t)ptCfg->tHPort.eForceLevel);

            /* Signal-V Low Output, Start, and Force Level */
            SET_MPWM_CR_VL_OUTPUT_LVL(ptMpwm, (uint8_t)ptCfg->tLPort.eOutLevel);
            SET_MPWM_CR_VL_INV_START_LVL(ptMpwm, (uint8_t)ptCfg->tLPort.eStartLevel);
            SET_MPWM_CR_VL_FORCE_LVL(ptMpwm, (uint8_t)ptCfg->tLPort.eForceLevel);
            break;        
        case MPWM_SIG_W:
            /* Signal-W High Output, Start, and Force Level */
            SET_MPWM_CR_WH_OUTPUT_LVL(ptMpwm, (uint8_t)ptCfg->tHPort.eOutLevel);
            SET_MPWM_CR_WH_INV_START_LVL(ptMpwm, (uint8_t)ptCfg->tHPort.eStartLevel);
            SET_MPWM_CR_WH_FORCE_LVL(ptMpwm, (uint8_t)ptCfg->tHPort.eForceLevel);

            /* Signal-W Low Output, Start, and Force Level */
            SET_MPWM_CR_WL_OUTPUT_LVL(ptMpwm, (uint8_t)ptCfg->tLPort.eOutLevel);
            SET_MPWM_CR_WL_INV_START_LVL(ptMpwm, (uint8_t)ptCfg->tLPort.eStartLevel);
            SET_MPWM_CR_WL_FORCE_LVL(ptMpwm, (uint8_t)ptCfg->tLPort.eForceLevel);
            break;        
        default:
            eErr = HAL_ERR_PARAMETER;
            break;        
    }

    return eErr;

}

static HAL_ERR_e PRV_MPWM_SetSDPConfig(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_SDP_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    /* Set Signal Port */
    eErr = PRV_MPWM_SetPPConfig(eId, eSig, &ptCfg->tSPCfg);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Set Signal Duty */
    eErr = PRV_MPWM_SetPDConfig(eId, eSig, &ptCfg->tSDCfg);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    return eErr;
}

static HAL_ERR_e PRV_MPWM_SetDTConfig(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_DT_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    MPWM_Type *ptMpwm;

    ptMpwm = PRV_MPWM_GetReg(eId);

    switch(eSig)
    {
        case MPWM_SIG_PWM:
            SET_MPWM_DEADTIME_EN(ptMpwm, ptCfg->bEnable);
            if(ptCfg->bEnable == true)
            {
                SET_MPWM_DEADTIME_MODE_SEL(ptMpwm, (uint8_t)ptCfg->eMode);
                SET_MPWM_DEADTIME_SCPROT_DIS(ptMpwm, (uint8_t)ptCfg->bSCPDisable);
                SET_MPWM_DEADTIME_PRESCALE(ptMpwm, (uint8_t)ptCfg->ePreScale);
                SET_MPWM_DEADTIME_VAL(ptMpwm, (uint8_t)ptCfg->un8EdgeDTValue);
            }
            break;
        case MPWM_SIG_U:
            SET_MPWM_DEADTIME_U_EN(ptMpwm, ptCfg->bEnable);
            if(ptCfg->bEnable == true)
            {
                SET_MPWM_DEADTIME_U_MODE_SEL(ptMpwm, (uint8_t)ptCfg->eMode);
                SET_MPWM_DEADTIME_U_SCPROT_DIS(ptMpwm, (uint8_t)ptCfg->bSCPDisable);
                SET_MPWM_DEADTIME_U_PRESCALE(ptMpwm, (uint8_t)ptCfg->ePreScale);
                SET_MPWM_DEADTIME_U_VAL(ptMpwm, (uint8_t)ptCfg->un8EdgeDTValue);
            }
            break;
        case MPWM_SIG_V:
            SET_MPWM_DEADTIME_V_EN(ptMpwm, ptCfg->bEnable);
            if(ptCfg->bEnable == true)
            {
                SET_MPWM_DEADTIME_V_MODE_SEL(ptMpwm, (uint8_t)ptCfg->eMode);
                SET_MPWM_DEADTIME_V_SCPROT_DIS(ptMpwm, (uint8_t)ptCfg->bSCPDisable);
                SET_MPWM_DEADTIME_V_PRESCALE(ptMpwm, (uint8_t)ptCfg->ePreScale);
                SET_MPWM_DEADTIME_V_VAL(ptMpwm, (uint8_t)ptCfg->un8EdgeDTValue);
            }
            break;
        case MPWM_SIG_W:
            SET_MPWM_DEADTIME_W_EN(ptMpwm, ptCfg->bEnable);
            if(ptCfg->bEnable == true)
            {
                SET_MPWM_DEADTIME_W_MODE_SEL(ptMpwm, (uint8_t)ptCfg->eMode);
                SET_MPWM_DEADTIME_W_SCPROT_DIS(ptMpwm, (uint8_t)ptCfg->bSCPDisable);
                SET_MPWM_DEADTIME_W_PRESCALE(ptMpwm, (uint8_t)ptCfg->ePreScale);
                SET_MPWM_DEADTIME_W_VAL(ptMpwm, (uint8_t)ptCfg->un8EdgeDTValue);
            }
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    return eErr;
}

static HAL_ERR_e PRV_MPWM_SetProtConfig(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_ALERT_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    MPWM_Type *ptMpwm;
    MPWM_CTRL_BLK_t *ptMcb;

    ptMpwm = PRV_MPWM_GetReg(eId);
    ptMcb = &s_tMcb[eId];

    switch(eSig)
    {
        case MPWM_SIG_PWM:
        case MPWM_SIG_U:
            if(ptCfg->bEnable == true)
            {
                SET_MPWM_PROT_PWM_U_POL(ptMpwm, (uint8_t)ptCfg->eInPolarity);
                SET_MPWM_PROT_PWM_U_DEBOUNCE(ptMpwm, (uint8_t)ptCfg->un8Debounce);
                SET_MPWM_PROT_UH_OUTPUT(ptMpwm, (uint8_t)ptCfg->bHLevelOutEnable);
                SET_MPWM_PROT_UL_OUTPUT(ptMpwm, (uint8_t)ptCfg->bLLevelOutEnable);
                if(ptCfg->bIntrEnable == true)
                {
                    ptMcb->un8PROTIntr |= MPWM_SIG_U;
                }
                else
                {
                    ptMcb->un8PROTIntr &= ~(MPWM_SIG_U);
                }
            }
            SET_MPWM_PROT_PWM_U_EN(ptMpwm, ptCfg->bEnable);
            break;
        case MPWM_SIG_V:
            if(ptCfg->bEnable == true)
            {
                SET_MPWM_PROT_V_POL(ptMpwm, (uint8_t)ptCfg->eInPolarity);
                SET_MPWM_PROT_V_DEBOUNCE(ptMpwm, (uint8_t)ptCfg->un8Debounce);
                SET_MPWM_PROT_VH_OUTPUT(ptMpwm, (uint8_t)ptCfg->bHLevelOutEnable);
                SET_MPWM_PROT_VL_OUTPUT(ptMpwm, (uint8_t)ptCfg->bLLevelOutEnable);
                if(ptCfg->bIntrEnable == true)
                {
                    ptMcb->un8PROTIntr |= MPWM_SIG_U;
                }
                else
                {
                    ptMcb->un8PROTIntr &= ~(MPWM_SIG_U);
                }
            }
            SET_MPWM_PROT_V_EN(ptMpwm, ptCfg->bEnable);
            break;
        case MPWM_SIG_W:
            if(ptCfg->bEnable == true)
            {
                SET_MPWM_PROT_W_POL(ptMpwm, (uint8_t)ptCfg->eInPolarity);
                SET_MPWM_PROT_W_DEBOUNCE(ptMpwm, (uint8_t)ptCfg->un8Debounce);
                SET_MPWM_PROT_WH_OUTPUT(ptMpwm, (uint8_t)ptCfg->bHLevelOutEnable);
                SET_MPWM_PROT_WL_OUTPUT(ptMpwm, (uint8_t)ptCfg->bLLevelOutEnable);
                if(ptCfg->bIntrEnable == true)
                {
                    ptMcb->un8PROTIntr |= MPWM_SIG_U;
                }
                else
                {
                    ptMcb->un8PROTIntr &= ~(MPWM_SIG_U);
                }
            }
            SET_MPWM_PROT_W_EN(ptMpwm, ptCfg->bEnable);
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    if(eErr == HAL_ERR_OK)
    {
        if(ptMcb->un8PROTIntr == 0)
        {
            SET_MPWM_IER_PROT_EN(ptMpwm, false);
        }
        else
        {
            SET_MPWM_IER_PROT_EN(ptMpwm, true);
        }
    }

    return eErr;
}

static HAL_ERR_e PRV_MPWM_SetOVConfig(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_ALERT_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    MPWM_Type *ptMpwm;
    MPWM_CTRL_BLK_t *ptMcb;

    ptMpwm = PRV_MPWM_GetReg(eId);
    ptMcb = &s_tMcb[eId];

    switch(eSig)
    {
        case MPWM_SIG_PWM:
        case MPWM_SIG_U:
            if(ptCfg->bEnable == true)
            {
                SET_MPWM_OV_PWM_U_POL(ptMpwm, (uint8_t)ptCfg->eInPolarity);
                SET_MPWM_OV_PWM_U_DEBOUNCE(ptMpwm, (uint8_t)ptCfg->un8Debounce);
                SET_MPWM_OV_UH_OUTPUT(ptMpwm, (uint8_t)ptCfg->bHLevelOutEnable);
                SET_MPWM_OV_UL_OUTPUT(ptMpwm, (uint8_t)ptCfg->bLLevelOutEnable);
                if(ptCfg->bIntrEnable == true)
                {
                    ptMcb->un8OVIntr |= MPWM_SIG_U;
                }
                else
                {
                    ptMcb->un8OVIntr &= ~(MPWM_SIG_U);
                }
            }
            SET_MPWM_OV_PWM_U_EN(ptMpwm, ptCfg->bEnable);
            break;
        case MPWM_SIG_V:
            if(ptCfg->bEnable == true)
            {
                SET_MPWM_OV_V_POL(ptMpwm, (uint8_t)ptCfg->eInPolarity);
                SET_MPWM_OV_V_DEBOUNCE(ptMpwm, (uint8_t)ptCfg->un8Debounce);
                SET_MPWM_OV_VH_OUTPUT(ptMpwm, (uint8_t)ptCfg->bHLevelOutEnable);
                SET_MPWM_OV_VL_OUTPUT(ptMpwm, (uint8_t)ptCfg->bLLevelOutEnable);
                if(ptCfg->bIntrEnable == true)
                {
                    ptMcb->un8OVIntr |= MPWM_SIG_U;
                }
                else
                {
                    ptMcb->un8OVIntr &= ~(MPWM_SIG_U);
                }
            }
            SET_MPWM_OV_V_EN(ptMpwm, ptCfg->bEnable);
            break;
        case MPWM_SIG_W:
            if(ptCfg->bEnable == true)
            {
                SET_MPWM_OV_W_POL(ptMpwm, (uint8_t)ptCfg->eInPolarity);
                SET_MPWM_OV_W_DEBOUNCE(ptMpwm, (uint8_t)ptCfg->un8Debounce);
                SET_MPWM_OV_WH_OUTPUT(ptMpwm, (uint8_t)ptCfg->bHLevelOutEnable);
                SET_MPWM_OV_WL_OUTPUT(ptMpwm, (uint8_t)ptCfg->bLLevelOutEnable);
                if(ptCfg->bIntrEnable == true)
                {
                    ptMcb->un8OVIntr |= MPWM_SIG_U;
                }
                else
                {
                    ptMcb->un8OVIntr &= ~(MPWM_SIG_U);
                }
            }
            SET_MPWM_OV_W_EN(ptMpwm, ptCfg->bEnable);
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    if(eErr == HAL_ERR_OK)
    {
        if(ptMcb->un8OVIntr == 0)
        {
            SET_MPWM_IER_OV_EN(ptMpwm, false);
        }
        else
        {
            SET_MPWM_IER_OV_EN(ptMpwm, true);
        }
    }

    return eErr;
}

static HAL_ERR_e PRV_MPWM_SetCapConfig(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_CAP_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    MPWM_Type *ptMpwm;

    ptMpwm = PRV_MPWM_GetReg(eId);

    switch(eSig)
    {
        case MPWM_SIG_U:
            SET_MPWM_CAP_U_EN(ptMpwm, ptCfg->bEnable);
            if(ptCfg->bEnable == true)
            {
                SET_MPWM_CAP_U_CLEAR_CNT(ptMpwm, 0x1UL);
                SET_MPWM_SUBCAP_U_EDGE(ptMpwm, ptCfg->eEdgeMode);
            }
            break;
        case MPWM_SIG_V:
            SET_MPWM_CAP_V_EN(ptMpwm, ptCfg->bEnable);
            if(ptCfg->bEnable == true)
            {
                SET_MPWM_CAP_V_CLEAR_CNT(ptMpwm, 0x1UL);
                SET_MPWM_SUBCAP_V_EDGE(ptMpwm, ptCfg->eEdgeMode);
            }
            break;
        case MPWM_SIG_W:
            SET_MPWM_CAP_W_EN(ptMpwm, ptCfg->bEnable);
            if(ptCfg->bEnable == true)
            {
                SET_MPWM_CAP_W_CLEAR_CNT(ptMpwm, 0x1UL);
                SET_MPWM_SUBCAP_W_EDGE(ptMpwm, ptCfg->eEdgeMode);
            }
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    return eErr;
}

static HAL_ERR_e PRV_MPWM_SetPWMConfig(MPWM_ID_e eId, MPWM_PWM_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    MPWM_Type *ptMpwm;

    ptMpwm = PRV_MPWM_GetReg(eId);

    SET_MPWM_DR_PERIOD_VAL(ptMpwm, ptCfg->un16Period);

    /* Set All Interrupt one-shot */
    SET_MPWM_IER_SIG_ATR(ptMpwm, ptCfg->un32IntrEnable);

    /* Set Signal-U High / Low Duty and Port */
    eErr = PRV_MPWM_SetSDPConfig(eId, MPWM_SIG_U, &ptCfg->tUSDPCfg);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Set Signal-V High / Low Duty and Port */
    eErr = PRV_MPWM_SetSDPConfig(eId, MPWM_SIG_V, &ptCfg->tVSDPCfg);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Set Signal-W High / Low Duty and Port */
    eErr = PRV_MPWM_SetSDPConfig(eId, MPWM_SIG_W, &ptCfg->tWSDPCfg);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Set Dead-Time */
    eErr = PRV_MPWM_SetDTConfig(eId, MPWM_SIG_PWM, &ptCfg->tDTCfg);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Set Protection Input */
    eErr = PRV_MPWM_SetProtConfig(eId, MPWM_SIG_PWM, &ptCfg->tProtCfg);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Set Over-voltage Input */
    eErr = PRV_MPWM_SetOVConfig(eId, MPWM_SIG_PWM, &ptCfg->tOVCfg);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    return eErr;
}

static HAL_ERR_e PRV_MPWM_SetSigConfig(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_INDIV_SIG_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    MPWM_Type *ptMpwm;

    ptMpwm = PRV_MPWM_GetReg(eId);

    switch(eSig)
    {
        case MPWM_SIG_U:
            SET_MPWM_DR_PERIOD_U_VAL(ptMpwm, ptCfg->un16Period);
            SET_MPWM_IER_SIG_ATR_MSK(ptMpwm, ptCfg->un32IntrEnable, MPWM_INTR_SIG_U_MSK);
            break;
        case MPWM_SIG_V:
            SET_MPWM_DR_PERIOD_V_VAL(ptMpwm, ptCfg->un16Period);
            SET_MPWM_IER_SIG_ATR_MSK(ptMpwm, ptCfg->un32IntrEnable, MPWM_INTR_SIG_V_MSK);
            break;
        case MPWM_SIG_W:
            SET_MPWM_DR_PERIOD_W_VAL(ptMpwm, ptCfg->un16Period);
            SET_MPWM_IER_SIG_ATR_MSK(ptMpwm, ptCfg->un32IntrEnable, MPWM_INTR_SIG_W_MSK);
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    /* Set Signal-U High / Low Duty and Port */
    eErr = PRV_MPWM_SetSDPConfig(eId, eSig, &ptCfg->tSDPCfg);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Set Dead-Time */
    eErr = PRV_MPWM_SetDTConfig(eId, eSig, &ptCfg->tDTCfg);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Set Protection Input */
    eErr = PRV_MPWM_SetProtConfig(eId, eSig, &ptCfg->tProtCfg);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Set Over-voltage Input */
    eErr = PRV_MPWM_SetOVConfig(eId, eSig, &ptCfg->tOVCfg);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    return eErr;
}

static HAL_ERR_e PRV_MPWM_SetINDIVConfig(MPWM_ID_e eId, MPWM_INDIV_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    eErr = PRV_MPWM_SetSigConfig(eId, MPWM_SIG_U, &ptCfg->tUCfg);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    eErr = PRV_MPWM_SetSigConfig(eId, MPWM_SIG_V, &ptCfg->tVCfg);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    eErr = PRV_MPWM_SetSigConfig(eId, MPWM_SIG_W, &ptCfg->tWCfg);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    return eErr;
}

HAL_ERR_e HAL_MPWM_Init(MPWM_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    MPWM_Type *ptMpwm;

    if((uint32_t)eId >= MPWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_MPWM_SetScuEnable((P_MPWM_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    memset(&s_tMcb[(uint32_t)eId], 0x00, sizeof(MPWM_CTRL_BLK_t));

    ptMpwm = PRV_MPWM_GetReg(eId);
    SET_MPWM_CR_EN(ptMpwm, true);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_MPWM_Uninit(MPWM_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    if((uint32_t)eId >= MPWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_MPWM_SetScuEnable((P_MPWM_ID_e)eId, false);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    /* Forcibly, disable Protection Interrupt */
    eIrq = MPWM_GetIRQNum((P_MPWM_ID_e)eId, P_MPWM_INTR_PROT);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    /* Forcibly, disable Overvoltage Interrupt */
    eIrq = MPWM_GetIRQNum((P_MPWM_ID_e)eId, P_MPWM_INTR_OV);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

#if defined(MPWM_FEATURE_SIG_SINGLE_INTERRUPT)
    /* Forcibly, disable PWM Interrupt */
    eIrq = MPWM_GetIRQNum((P_MPWM_ID_e)eId, P_MPWM_INTR_PWM);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);
#else
    /* Forcibly, disable Signal-U Interrupt */
    eIrq = MPWM_GetIRQNum((P_MPWM_ID_e)eId, P_MPWM_INTR_SIG_U);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    /* Forcibly, disable Signal-V Interrupt */
    eIrq = MPWM_GetIRQNum((P_MPWM_ID_e)eId, P_MPWM_INTR_SIG_V);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    /* Forcibly, disable Signal-W Interrupt */
    eIrq = MPWM_GetIRQNum((P_MPWM_ID_e)eId, P_MPWM_INTR_SIG_W);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);
#endif

    memset(&s_tMcb[(uint32_t)eId], 0x00, sizeof(MPWM_CTRL_BLK_t));

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_MPWM_SetClkConfig(MPWM_ID_e eId, MPWM_CLK_CFG_t *ptClkCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= MPWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    switch(ptClkCfg->eClk)
    {
        case MPWM_CLK_MCCR:
            MPWM_SetMccrClk((P_MPWM_ID_e)eId, (P_MPWM_CLK_MCCR_e)ptClkCfg->eMccr, ptClkCfg->un8MccrDiv);
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    return eErr;
}

HAL_ERR_e HAL_MPWM_SetConfig(MPWM_ID_e eId, MPWM_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    MPWM_Type *ptMpwm;
    MPWM_CTRL_BLK_t *ptMcb;

    if((uint32_t)eId >= MPWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(ptCfg->eMode >= MPWM_MODE_MAX)
    {
        return HAL_ERR_PARAMETER;
    }

    ptMpwm = PRV_MPWM_GetReg(eId);
    ptMcb = &s_tMcb[eId];

    SET_MPWM_CR_MODE(ptMpwm, MPWM_MODE((uint8_t)ptCfg->eMode));
    SET_MPWM_CR_CHANNEL_MODE(ptMpwm, (uint8_t)ptCfg->eChannelMode);
    SET_MPWM_CR_COUNTER_MODE(ptMpwm, (uint8_t)ptCfg->eCounterMode);
    SET_MPWM_CR_UPDATE_DUTY_PERIOD(ptMpwm, (uint8_t)ptCfg->bPeriodMatch);
    SET_MPWM_CR_UPDATE_DUTY_BOTTOM(ptMpwm, (uint8_t)ptCfg->bBottomMatch);

    ptMcb->eMode = ptCfg->eMode;

    return eErr;
}

HAL_ERR_e HAL_MPWM_SetModeConfig(MPWM_ID_e eId, MPWM_MODE_e eMode, void *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= MPWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    if(eMode == MPWM_MODE_MOTOR || eMode == MPWM_MODE_NORMAL) 
    {
        eErr = PRV_MPWM_SetPWMConfig(eId, (MPWM_PWM_CFG_t *)ptCfg);
    }
    else
    {
        eErr = PRV_MPWM_SetINDIVConfig(eId, (MPWM_INDIV_CFG_t *)ptCfg);
    }

    return eErr;
}

HAL_ERR_e HAL_MPWM_SetDTConfig(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_DT_CFG_t *ptCfg)
{
    if((uint32_t)eId >= MPWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    return PRV_MPWM_SetDTConfig(eId, eSig, ptCfg);
}

HAL_ERR_e HAL_MPWM_SetProtConfig(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_ALERT_CFG_t *ptCfg)
{
    if((uint32_t)eId >= MPWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    return PRV_MPWM_SetProtConfig(eId, eSig, ptCfg);
}

HAL_ERR_e HAL_MPWM_SetOVConfig(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_ALERT_CFG_t *ptCfg)
{
    if((uint32_t)eId >= MPWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    return PRV_MPWM_SetOVConfig(eId, eSig, ptCfg);
}

HAL_ERR_e HAL_MPWM_SetCapConfig(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_CAP_CFG_t *ptCfg)
{
    if((uint32_t)eId >= MPWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    return PRV_MPWM_SetCapConfig(eId, eSig, ptCfg);
}

HAL_ERR_e HAL_MPWM_SetAdcTrgConfig(MPWM_ID_e eId, MPWM_ADCTRG_CFG_t *ptCfg)
{
    MPWM_Type *ptMpwm;
    uint32_t un32AddrReg = 0, un32RegOffset = 0;
    uint32_t un32IntrEnable = 0, un32IntrMask = 0;

    if((uint32_t)eId >= MPWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptMpwm = PRV_MPWM_GetReg(eId);

    un32AddrReg = (uint32_t)GET_MPWM_ADCTRG_BASE_ADDR(ptMpwm);
    un32RegOffset = (uint32_t)ptCfg->un8Idx * MPWM_ADCTRG_REG_OFFSET;

    SET_MPWM_ADCTRG_SRC(un32AddrReg, (uint8_t)ptCfg->eSrc, un32RegOffset);
    SET_MPWM_ADCTRG_MODE(un32AddrReg, (uint8_t)ptCfg->eMode, un32RegOffset);
    SET_MPWM_ADCTRG_CNT(un32AddrReg, (uint16_t)ptCfg->un16GenData, un32RegOffset);
    SET_MPWM_ADCTRG_UPDATE(un32AddrReg, (uint8_t)ptCfg->bTrgUpdate, un32RegOffset);

    un32IntrMask = MPWM_INTR_ATR1_MSK << ptCfg->un8Idx;

    if(ptCfg->bIntrEnable == true)
    {
        un32IntrEnable = MPWM_INTR_ATR1_MSK << ptCfg->un8Idx;
    }

    SET_MPWM_IER_SIG_ATR_MSK(ptMpwm, un32IntrEnable, un32IntrMask);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_MPWM_SetDuty(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_SD_CFG_t *ptCfg)
{
    if((uint32_t)eId >= MPWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    return PRV_MPWM_SetPDConfig(eId, eSig, ptCfg);
}

HAL_ERR_e HAL_MPWM_SetPort(MPWM_ID_e eId, MPWM_SIG_e eSig, MPWM_SP_CFG_t *ptCfg)
{
    if((uint32_t)eId >= MPWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    return PRV_MPWM_SetPPConfig(eId, eSig, ptCfg);
}

HAL_ERR_e HAL_MPWM_SetPeriod(MPWM_ID_e eId, MPWM_SIG_e eSig, uint16_t un16Period)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    MPWM_Type *ptMpwm;

    if((uint32_t)eId >= MPWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptMpwm = PRV_MPWM_GetReg(eId);

    switch(eSig)
    {
        case MPWM_SIG_PWM:
            SET_MPWM_DR_PERIOD_VAL(ptMpwm, un16Period);
            break;
        case MPWM_SIG_U:
            SET_MPWM_DR_PERIOD_U_VAL(ptMpwm, un16Period);
            break;
        case MPWM_SIG_V:
            SET_MPWM_DR_PERIOD_V_VAL(ptMpwm, un16Period);
            break;
        case MPWM_SIG_W:
            SET_MPWM_DR_PERIOD_W_VAL(ptMpwm, un16Period);
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    return eErr;
}

HAL_ERR_e HAL_MPWM_SetInterval(MPWM_ID_e eId, MPWM_SIG_e eSig, uint8_t un8Interval)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    MPWM_Type *ptMpwm;

    if((uint32_t)eId >= MPWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptMpwm = PRV_MPWM_GetReg(eId);

    switch(eSig)
    {
        case MPWM_SIG_PWM:
            SET_MPWM_CR_INTR_INTV_VAL(ptMpwm, un8Interval);
            break;
        case MPWM_SIG_U:
            SET_MPWM_CR_PWM_U_INTR_INTV_VAL(ptMpwm, un8Interval);
            break;
        case MPWM_SIG_V:
            SET_MPWM_CR_V_INTR_INTV_VAL(ptMpwm, un8Interval);
            break;
        case MPWM_SIG_W:
            SET_MPWM_CR_W_INTR_INTV_VAL(ptMpwm, un8Interval);
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    return eErr;
}

HAL_ERR_e HAL_MPWM_SetIRQ(MPWM_ID_e eId, MPWM_INTR_HDLR_e eHdlr, MPWM_OPS_e eOps, 
                          pfnMPWM_IRQ_Handler_t pfnHandler, void *pContext, 
                          uint32_t un32IRQPrio)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    MPWM_CTRL_BLK_t *ptMcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= MPWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptMcb = &s_tMcb[(uint32_t)eId];
    eIrq = MPWM_GetIRQNum((P_MPWM_ID_e)eId, (P_MPWM_INTR_e)eHdlr);
    switch(eOps)
    {
        case MPWM_OPS_INTR:
#if defined(_NMI) && (defined(CONFIG_NMI_ANY_INTERRUPT) || defined(MPWM_FEATURE_NMI))
            eErr = PRV_MPWM_SetNMI(eId, eIrq, eHdlr, NULL, false);
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            eErr = PRV_MPWM_SetIRQHandler(eId, eHdlr, pfnHandler, pContext);
            break;
#if defined(_NMI) && (defined(CONFIG_NMI_ANY_INTERRUPT) || defined(MPWM_FEATURE_NMI))
        case MPWM_OPS_NMI:
            eErr = PRV_MPWM_SetNMI(eId, eIrq, eHdlr, pContext, true);
            eErr = PRV_MPWM_SetIRQHandler(eId, eHdlr, pfnHandler, pContext);
            break;
#endif
        case MPWM_OPS_POLL:
        default:
#if defined(_NMI) && (defined(CONFIG_NMI_ANY_INTERRUPT) || defined(MPWM_FEATURE_NMI))
            eErr = PRV_MPWM_SetNMI(eId, eIrq, eHdlr, NULL, false);
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            eErr = PRV_MPWM_SetIRQHandler(eId, eHdlr, NULL, NULL);
            break;
    }

    ptMcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_MPWM_Start(MPWM_ID_e eId, MPWM_MODE_e eMode, MPWM_START_MODE_e eStartMode, uint8_t un8Sig)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    MPWM_Type *ptMpwm;
    MPWM_CTRL_BLK_t *ptMcb;
    NMI_INTR_e eNmi = NMI_INTR_MAX;

    if((uint32_t)eId >= MPWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptMpwm = PRV_MPWM_GetReg(eId);
    ptMcb = &s_tMcb[eId];
    
    if(ptMcb->un8OVIntr != 0)
    {
        SET_MPWM_IER_OV_EN(ptMpwm, true);
    }

    if(ptMcb->un8PROTIntr != 0)
    {
        SET_MPWM_IER_PROT_EN(ptMpwm, true);
    }

    if(ptMcb->bOVNonMask == true)
    {
        if(eId == MPWM_ID_0)
        {
            eNmi = NMI_INTR_OVP0;
        }
        else if (eId == MPWM_ID_1)
        {
            eNmi = NMI_INTR_OVP1;
        }
        HPL_NMI_SetEnable(eNmi, true);
    }

    if(ptMcb->bProtNonMask == true)
    {
        if(eId == MPWM_ID_0)
        {
            eNmi = NMI_INTR_PROT0;
        }
        else if (eId == MPWM_ID_1)
        {
            eNmi = NMI_INTR_PROT1;
        }
        HPL_NMI_SetEnable(eNmi, true);
    }

    if(eMode == MPWM_MODE_MOTOR || eMode == MPWM_MODE_NORMAL)
    {
        switch(eStartMode)
        {
            case MPWM_START_MODE_RECOUNT:
                SET_MPWM_CR_HALT(ptMpwm, false);
                SET_MPWM_CR_START(ptMpwm, true);
                break;
            case MPWM_START_MODE_RESUME:
                SET_MPWM_CR_HALT(ptMpwm, false);
                SET_MPWM_CR_PWM_U_CONTI(ptMpwm, true);
                break;
            default:
                eErr = HAL_ERR_PARAMETER;
                break;
        }
    }
    else
    {
        switch(eStartMode)
        {
            case MPWM_START_MODE_RECOUNT:
                if(un8Sig & MPWM_SIG_U)
                {
                    SET_MPWM_CR_PWM_U_EN(ptMpwm, true);
                    SET_MPWM_CR_PWM_U_START(ptMpwm, true);
                }
                if(un8Sig & MPWM_SIG_V)
                {
                    SET_MPWM_CR_V_EN(ptMpwm, true);
                    SET_MPWM_CR_V_START(ptMpwm, true);
                }
                if(un8Sig & MPWM_SIG_W)
                {
                    SET_MPWM_CR_V_EN(ptMpwm, true);
                    SET_MPWM_CR_W_EN(ptMpwm, true);
                    SET_MPWM_CR_W_START(ptMpwm, true);
                }
                break;
            case MPWM_START_MODE_RESUME:
                if(un8Sig & MPWM_SIG_U)
                {
                    SET_MPWM_CR_PWM_U_CONTI(ptMpwm, true);
                }
                if(un8Sig & MPWM_SIG_V)
                {
                    SET_MPWM_CR_V_CONTI(ptMpwm, true);
                }
                if(un8Sig & MPWM_SIG_W)
                {
                    SET_MPWM_CR_W_CONTI(ptMpwm, true);
                }
                break;
            default:
                eErr = HAL_ERR_PARAMETER;
                break;
        }

    }

    return eErr;
}

HAL_ERR_e HAL_MPWM_Stop(MPWM_ID_e eId, MPWM_MODE_e eMode, MPWM_STOP_MODE_e eStopMode, uint8_t un8Sig)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    MPWM_Type *ptMpwm;
    MPWM_CTRL_BLK_t *ptMcb;
    NMI_INTR_e eNmi = NMI_INTR_MAX;

    if((uint32_t)eId >= MPWM_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptMpwm = PRV_MPWM_GetReg(eId);
    ptMcb = &s_tMcb[eId];

    if(ptMcb->un8OVIntr != 0)
    {
        SET_MPWM_IER_OV_EN(ptMpwm, false);
    }

    if(ptMcb->un8PROTIntr != 0)
    {
        SET_MPWM_IER_PROT_EN(ptMpwm, false);
    }

    if(ptMcb->bOVNonMask == true)
    {
        if(eId == MPWM_ID_0)
        {
            eNmi = NMI_INTR_OVP0;
        }
        else if (eId == MPWM_ID_1)
        {
            eNmi = NMI_INTR_OVP1;
        }
        HPL_NMI_SetEnable(eNmi, false);
    }

    if(ptMcb->bProtNonMask == true)
    {
        if(eId == MPWM_ID_0)
        {
            eNmi = NMI_INTR_PROT0;
        }
        else if (eId == MPWM_ID_1)
        {
            eNmi = NMI_INTR_PROT1;
        }
        HPL_NMI_SetEnable(eNmi, false);
    }

    if(eMode == MPWM_MODE_MOTOR || eMode == MPWM_MODE_NORMAL)
    {
        switch(eStopMode)
        {
            case MPWM_STOP_MODE_CLEAR:
                SET_MPWM_CR_START(ptMpwm, false);
                break;
            case MPWM_STOP_MODE_REMAIN:
                SET_MPWM_CR_HALT(ptMpwm, true);
                break;
            case MPWM_STOP_MODE_RESET:
                SET_MPWM_CR_PWM_U_STOP(ptMpwm, true);
                break;
            case MPWM_STOP_MODE_DISABLE:
                SET_MPWM_CR_PWM_U_DIS(ptMpwm, true);
                break;
            default:
                eErr = HAL_ERR_PARAMETER;
                break;
        }
    }
    else
    {
        switch(eStopMode)
        {
            case MPWM_STOP_MODE_CLEAR:
            case MPWM_STOP_MODE_RESET:
                if(un8Sig & MPWM_SIG_U)
                {
                    SET_MPWM_CR_PWM_U_STOP(ptMpwm, true);
                }
                if(un8Sig & MPWM_SIG_V)
                {
                    SET_MPWM_CR_V_STOP(ptMpwm, true);
                }
                if(un8Sig & MPWM_SIG_W)
                {
                    SET_MPWM_CR_W_STOP(ptMpwm, true);
                }
                break;
            case MPWM_STOP_MODE_REMAIN:
                if(un8Sig & MPWM_SIG_U)
                {
                    SET_MPWM_CR_PWM_U_HALT(ptMpwm, true);
                }
                if(un8Sig & MPWM_SIG_V)
                {
                    SET_MPWM_CR_V_HALT(ptMpwm, true);
                }
                if(un8Sig & MPWM_SIG_W)
                {
                    SET_MPWM_CR_W_HALT(ptMpwm, true);
                }
                break;
            case MPWM_STOP_MODE_DISABLE:
                if(un8Sig & MPWM_SIG_U)
                {
                    SET_MPWM_CR_PWM_U_DIS(ptMpwm, true);
                }
                if(un8Sig & MPWM_SIG_V)
                {
                    SET_MPWM_CR_V_DIS(ptMpwm, true);
                }
                if(un8Sig & MPWM_SIG_W)
                {
                    SET_MPWM_CR_W_DIS(ptMpwm, true);
                }
                break;
            default:
                eErr = HAL_ERR_PARAMETER;
                break;
        }
    }
    return eErr;
}

static void PRV_MPWM_PROTIRQHandler(MPWM_ID_e eId)
{
    MPWM_Type *ptMpwm;
    MPWM_CTRL_BLK_t *ptMcb;
    uint32_t un32Event = 0;

    ptMpwm = PRV_MPWM_GetReg(eId);
    ptMcb = &s_tMcb[eId];

    un32Event = GET_MPWM_PROT_SR(ptMpwm);
    un32Event = (un32Event | (MPWM_PROTECTION_ACCESS_KEY << MPWM_PROTECTION_ACCESS_KEY_OFFSET));

    SET_MPWM_PROT_SR(ptMpwm, un32Event);
    un32Event = un32Event & MPWM_INTR_PROT_MSK;

    SET_MPWM_IER_PROT_EN(ptMpwm, false);

    if(ptMcb->pfnPROTHandler != NULL && un32Event)
    {
        ptMcb->pfnPROTHandler(un32Event, ptMcb->pPROTContext);
    }
}

static void PRV_MPWM_OVIRQHandler(MPWM_ID_e eId)
{
    MPWM_Type *ptMpwm;
    MPWM_CTRL_BLK_t *ptMcb;
    uint32_t un32Event = 0;

    ptMpwm = PRV_MPWM_GetReg(eId);
    ptMcb = &s_tMcb[eId];

    un32Event = GET_MPWM_OV_SR(ptMpwm);
    un32Event = (un32Event | (MPWM_OVERVOLTAGE_ACCESS_KEY << MPWM_OVERVOLTAGE_ACCESS_KEY_OFFSET));

    SET_MPWM_OV_SR(ptMpwm, un32Event);
    un32Event = un32Event & MPWM_INTR_OV_MSK;

    SET_MPWM_IER_OV_EN(ptMpwm, false);

    if(ptMcb->pfnOVHandler != NULL && un32Event)
    {
        ptMcb->pfnOVHandler(un32Event, ptMcb->pOVContext);
    }
}

#if defined(MPWM_FEATURE_SIG_SINGLE_INTERRUPT)
static void PRV_MPWM_PWMIRQHandler(MPWM_ID_e eId)
{
    MPWM_Type *ptMpwm;
    MPWM_CTRL_BLK_t *ptMcb;
    uint32_t un32Event=0;

    ptMpwm = PRV_MPWM_GetReg(eId);
    ptMcb = &s_tMcb[eId];

    if(ptMcb->pfnPWMHandler != NULL && un32Event)
    {
        ptMcb->pfnPWMHandler(un32Event, ptMcb->pPWMContext);
    }
}
#else
static void PRV_MPWM_PWMUIRQHandler(MPWM_ID_e eId)
{
    MPWM_Type *ptMpwm;
    MPWM_CTRL_BLK_t *ptMcb;
    uint32_t un32Status = 0, un32Event = 0;

    ptMpwm = PRV_MPWM_GetReg(eId);
    ptMcb = &s_tMcb[eId];

    un32Status = GET_MPWM_IER_SR_SIG_ATR(ptMpwm);

    if(ptMcb->eMode == MPWM_MODE_MOTOR || ptMcb->eMode == MPWM_MODE_NORMAL)
    {
        un32Event = un32Status & MPWM_INTR_PWM_MSK;
    }
    else
    {
        un32Event = un32Status & MPWM_INTR_SIG_U_MSK;
    }

    SET_MPWM_IER_SR_SIG_ATR(ptMpwm, un32Event);

    if(ptMcb->pfnPWMUHandler != NULL && un32Event)
    {
        ptMcb->pfnPWMUHandler(un32Event, ptMcb->pPWMUContext);
    }
}

static void PRV_MPWM_PVIRQHandler(MPWM_ID_e eId)
{
    MPWM_Type *ptMpwm;
    MPWM_CTRL_BLK_t *ptMcb;
    uint32_t un32Status = 0, un32Event = 0;

    ptMpwm = PRV_MPWM_GetReg(eId);
    ptMcb = &s_tMcb[eId];

    un32Status = GET_MPWM_IER_SR_SIG_ATR(ptMpwm);
    un32Event = un32Status & MPWM_INTR_SIG_V_MSK;
    SET_MPWM_IER_SR_SIG_ATR(ptMpwm, un32Event);

    if(ptMcb->pfnPVHandler != NULL && un32Event)
    {
        ptMcb->pfnPVHandler(un32Event, ptMcb->pPVContext);
    }
}

static void PRV_MPWM_PWIRQHandler(MPWM_ID_e eId)
{
    MPWM_Type *ptMpwm;
    MPWM_CTRL_BLK_t *ptMcb;
    uint32_t un32Status = 0, un32Event = 0;

    ptMpwm = PRV_MPWM_GetReg(eId);
    ptMcb = &s_tMcb[eId];

    un32Status = GET_MPWM_IER_SR_SIG_ATR(ptMpwm);
    un32Event = un32Status & MPWM_INTR_SIG_W_MSK;
    SET_MPWM_IER_SR_SIG_ATR(ptMpwm, un32Event);

    if(ptMcb->pfnPWHandler != NULL && un32Event)
    {
        ptMcb->pfnPWHandler(un32Event, ptMcb->pPWContext);
    }
}
#endif /* MPWM_FEATURE_SIG_SINGLE_INTERRUPT */

void MPWM0_PROTIRQHandler(void)
{
    PRV_MPWM_PROTIRQHandler(MPWM_ID_0);
}

void MPWM1_PROTIRQHandler(void)
{
    PRV_MPWM_PROTIRQHandler(MPWM_ID_1);
}

void MPWM0_OVIRQHandler(void)
{
    PRV_MPWM_OVIRQHandler(MPWM_ID_0);
}

void MPWM1_OVIRQHandler(void)
{
    PRV_MPWM_OVIRQHandler(MPWM_ID_1);
}

#if defined(MPWM_FEATURE_SIG_SINGLE_INTERRUPT)
void MPWM0_PWMIRQHandler(void)
{
    PRV_MPWM_PWMIRQHandler(MPWM_ID_0);
}

void MPWM1_PWMIRQHandler(void)
{
    PRV_MPWM_PWMIRQHandler(MPWM_ID_1);
}
#else
void MPWM0_PWMUIRQHandler(void)
{
    PRV_MPWM_PWMUIRQHandler(MPWM_ID_0);
}
void MPWM0_PVIRQHandler(void)
{
    PRV_MPWM_PVIRQHandler(MPWM_ID_0);
}

void MPWM0_PWIRQHandler(void)
{
    PRV_MPWM_PWIRQHandler(MPWM_ID_0);
}

void MPWM1_PWMUIRQHandler(void)
{
    PRV_MPWM_PWMUIRQHandler(MPWM_ID_1);
}

void MPWM1_PVIRQHandler(void)
{
    PRV_MPWM_PVIRQHandler(MPWM_ID_1);
}

void MPWM1_PWIRQHandler(void)
{
    PRV_MPWM_PWIRQHandler(MPWM_ID_1);
}
#endif /* MPWM_FEATURE_SIG_SINGLE_INTERRUPT */

#endif /* _MPWM */
