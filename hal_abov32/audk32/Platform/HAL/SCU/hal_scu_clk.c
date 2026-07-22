/**
 *******************************************************************************
 * @file        hal_scu_clk.c
 * @author      ABOV R&D Division
 * @brief       Clock sub system in System Control Unit
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
#include "hal_scu.h"
#include "hal_scu_clk.h"
#include "hal_scu_prv.h"

#if defined(_NMI)
#include "hpl_nmi.h"
#endif

#define EXPO2(x) (1 << x)

uint32_t SystemCoreClock = LSI_CLOCK;
uint32_t SystemPeriClock = LSI_CLOCK;
uint32_t SystemDelayMSCount = 1;
uint32_t SystemDelayUSCount = 1;

typedef enum
{
    PRV_SCUCLK_MON_MCLK,
    PRV_SCUCLK_MON_HSE,
    PRV_SCUCLK_MON_LSE,
    PRV_SCUCLK_MON_MAX
} PRV_SCUCLK_MON_e;

typedef struct
{
    pfnSCUCLK_IRQ_Handler_t    pfnHandler;
    void                       *pContext;
    bool                       bEnable;
    bool                       bNmiEnable;
    PRV_SCUCLK_MON_e           eClkMon;
} SCUCLK_CTRL_BLK_t;

#if defined(SCU_FEATURE_VX_PLL_BLOCK)
static uint32_t s_un32PLLClock = 0;
#endif
static SCUCLK_CTRL_BLK_t s_tCcb[CLK_MON_NUM];

#if defined(SCU_FEATURE_VX_CLOCK_MONITOR) && defined(SCU_FEATURE_CLOCK_MONITOR_RESOURCE)
static uint32_t s_un32MonRes = 0;
#endif

static void PRV_SCUCLK_IRQHandler(PRV_SCUCLK_MON_e eMon);

#if defined(_NMI)
static void PRV_SCUCLK_NMIHandler(uint32_t un32Event, void *pContext)
{
    for (int i = 0; i < CLK_MON_NUM; i++)
    {
        if(s_tCcb[i].bNmiEnable == true)
        {
            PRV_SCUCLK_IRQHandler(s_tCcb[i].eClkMon);
        }
    }
}
#endif

#if defined(SCU_FEATURE_VX_PLL_BLOCK)
static void PRV_SCUCLK_PLLDelay(uint32_t un32Delay)
{
    uint32_t un32us = SystemCoreClock / (1000000);
    uint32_t un32Loop;

    if (un32us == 0)
    {
        un32us = 1; /* impossible to create 1us source clock like 32KHz, 40KHz etc. */
    }

    un32Loop = un32Delay * un32us;

    for(volatile uint32_t i = 0; i < un32Loop; i++)
    {
        __NOP();
    }
}
#endif

#if defined(SCU_FEATURE_VX_CLOCK_MONITOR)
static HAL_ERR_e PRV_SCUCLK_SetMonitor(SCUCLK_MON_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCUCLK_Type *ptScuClk = (SCUCLK_Type *)SCUCLK_REG_BASE;
    SCUCLK_CTRL_BLK_t *ptCcb = NULL;
    IRQn_Type eIrq;
    PRV_SCUCLK_MON_e eMon = PRV_SCUCLK_MON_MAX;

    switch(ptCfg->eSrc)
    {
#if defined(SCU_FEATURE_UNSUPPORT_MCLK_MONITOR)
#else
        case SCUCLK_SRC_MCLK:
            eMon = PRV_SCUCLK_MON_MCLK;
            SET_SCU_CMR_MCLKMNT(ptScuClk, ptCfg->bEnable);
            SET_SCU_CMR_MCLKIE(ptScuClk, ptCfg->bEnable);
            eIrq = SCUCLK_MCLK_IRQ;
            break;
#endif
#if defined(SCU_FEATURE_UNSUPPORT_HSE)
#else
        case SCUCLK_SRC_HSE:
            eMon = PRV_SCUCLK_MON_HSE;
            SET_SCU_CMR_HSEMNT(ptScuClk, ptCfg->bEnable);
            SET_SCU_CMR_HSEIE(ptScuClk, ptCfg->bEnable);
            eIrq = SCUCLK_HSE_IRQ;
            break;
#endif
#if defined(SCU_FEATURE_UNSUPPORT_LSE)
#else
        case SCUCLK_SRC_LSE:
            eMon = PRV_SCUCLK_MON_LSE;
            SET_SCU_CMR_LSEMNT(ptScuClk, ptCfg->bEnable);
            SET_SCU_CMR_LSEIE(ptScuClk, ptCfg->bEnable);
            eIrq = SCUCLK_LSE_IRQ;
            break;
#endif
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    ptCcb = &s_tCcb[(uint8_t)eMon];
    ptCcb->bEnable = ptCfg->bEnable;
    ptCcb->eClkMon = eMon;

#if defined(_NMI)
    if(eMon == PRV_SCUCLK_MON_MCLK)
    {
        ptCcb->bNmiEnable = ptCfg->bNmiEnable;
        eErr = HPL_NMI_SetIRQ(NMI_INTR_MCLK, &PRV_SCUCLK_NMIHandler, ptCfg->pContext, ptCcb->bNmiEnable);
    }
#if defined(CONFIG_NMI_ANY_INTERRUPT)
    else
    {
        ptCcb->bNmiEnable = ptCfg->bNmiEnable;
        (void)HPL_NMI_SetSource(eIrq, &PRV_SCUCLK_NMIHandler, ptCfg->pContext, ptCcb->bNmiEnable);
    }
#endif
#endif /* _NMI */
        
    if(ptCcb->bEnable == true)
    {
#if defined(SCU_FEATURE_CLOCK_MONITOR_RESOURCE)
        if(s_un32MonRes == 0)
        {
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, ptCfg->un32Prio);
            NVIC_EnableIRQ(eIrq);
        } 
        s_un32MonRes |= BIT((uint8_t)eMon);
#else
        NVIC_ClearPendingIRQ(eIrq);
        NVIC_SetPriority(eIrq, ptCfg->un32Prio);
        NVIC_EnableIRQ(eIrq);
#endif
        ptCcb->pfnHandler = ptCfg->pfnHandler;
        ptCcb->pContext = ptCfg->pContext;
    }
    else
    {
#if defined(SCU_FEATURE_CLOCK_MONITOR_RESOURCE)
        s_un32MonRes &= ~BIT((uint8_t)eMon);
        if(s_un32MonRes == 0)
        {
            NVIC_DisableIRQ(eIrq);
        }
#else
        NVIC_DisableIRQ(eIrq);
#endif
        ptCcb->pfnHandler = NULL;
        ptCcb->pContext = NULL;
    }

    return eErr;
}

#elif defined(SCU_FEATURE_FX_CLOCK_MONITOR)
static HAL_ERR_e PRV_SCUCLK_SetMonitor(SCUCLK_MON_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCUCLK_Type *ptScuClk = (SCUCLK_Type *)SCUCLK_REG_BASE;
    SCUCLK_CTRL_BLK_t *ptCcb = NULL;
    PRV_SCUCLK_MON_e eMon = PRV_SCUCLK_MON_MAX;

    switch(ptCfg->eSrc)
    {
        case SCUCLK_SRC_MCLK:
            eMon = PRV_SCUCLK_MON_MCLK;
        case SCUCLK_SRC_HSI:
        case SCUCLK_SRC_HSE:
        case SCUCLK_SRC_LSE:
            SET_SCU_CMR_CLK_SEL(ptScuClk, (uint8_t)ptCfg->eSrc); 
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    ptCcb = &s_tCcb[(uint8_t)eMon];
    ptCcb->bEnable = ptCfg->bEnable;

#if defined(_NMI)
    if(eMon == PRV_SCUCLK_MON_MCLK)
    {
        ptCcb->bNmiEnable = ptCfg->bEnable;
        eErr = HPL_NMI_SetIRQ(NMI_INTR_MCLK, &PRV_SCUCLK_NMIHandler, ptCfg->pContext, ptCcb->bNmiEnable);
    }
#endif /* _NMI */
        
    if(ptCcb->bEnable == true)
    {
        ptCcb->bNmiEnable = false;
        ptCcb->pfnHandler = ptCfg->pfnHandler;
        ptCcb->pContext = ptCfg->pContext;
    }
    else
    {
        ptCcb->pfnHandler = NULL;
        ptCcb->pContext = NULL;
        SET_SCU_CMR_ACT_CLR(ptScuClk);
    }

    SET_SCU_CMR_CLKEN(ptScuClk, ptCcb->bEnable);

    /* Need to check MONFLAG bit ?? */

    return eErr;
}
#endif

HAL_ERR_e HAL_SCU_CLK_GetMonitorStatus(SCUCLK_SRC_e eSrc, bool *pbStatus)
{
#if defined(SCU_FEATURE_VX_CLOCK_MONITOR)
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCUCLK_Type *ptScuClk = (SCUCLK_Type *)SCUCLK_REG_BASE;

    switch(eSrc)
    {
#if defined(SCU_FEATURE_UNSUPPORT_HSE)
#else
        case SCUCLK_SRC_HSE:
             *pbStatus ^= (bool)GET_SCU_CMR_HSESTS(ptScuClk);
             break;
#endif
        case SCUCLK_SRC_MCLK:
             *pbStatus ^= (bool)GET_SCU_CMR_MCLKSTS(ptScuClk);
             break;
#if defined(SCU_FEATURE_UNSUPPORT_LSE)
#else
        case SCUCLK_SRC_LSE:
             *pbStatus ^= (bool)GET_SCU_CMR_LSESTS(ptScuClk);
             break;
#endif
        default:
             eErr = HAL_ERR_PARAMETER;
             break;
    }
    return eErr;
#else
    (void)eSrc;
    (void)*pbStatus;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_SCU_CLK_SetMonitor(SCUCLK_MON_CFG_t *ptCfg)
{
    return PRV_SCUCLK_SetMonitor(ptCfg);
}

HAL_ERR_e HAL_SCU_CLK_SetMClk(SCUCLK_MCLK_CFG_t *ptCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
#if defined(SCU_FEATURE_VX_PLL_BLOCK)
    SCUCLK_Type *ptScuClk = (SCUCLK_Type*)SCUCLK_REG_BASE;

    bool bPllHSE = false;

    if(ptCfg->eMClk == SCUCLK_SRC_PLL)
    {
        SystemCoreClock = s_un32PLLClock;
    }
    else
    {
        if(ptCfg->eMClk == SCUCLK_SRC_HSE)
        {
            bPllHSE = true;
        }

        SET_SCU_SCCR_PLLCLKSEL(ptScuClk,bPllHSE);
    }
#endif
    eErr = SCUCLK_SetMClk((P_SCUCLK_SRC_e)ptCfg->eMClk, (P_SCUCLK_DIV_e)ptCfg->ePreMClkDiv,
                          (P_SCUCLK_DIV_e)ptCfg->ePostMClkDiv);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    SystemDelayMSCount = (uint32_t)((((uint64_t)SystemCoreClock * 1000) / 1000000)) / 6; /* SW Delay Loop almost 6 cycle */
    SystemDelayUSCount = (uint32_t)((SystemCoreClock / 1000000) / 6); /* SW Delay Loop almost 6 cycle */

    /* Adjust delay count value when using low system clock */
    if(SystemDelayUSCount == 0)
    {
        SystemDelayUSCount = 1;
    }

    /* Need minimum 200us delay for clock stabilization */
    SystemDelayUS(200);

    /* Flash wait delay by System Core Clock value */
    SCUCLK_SetFlashLatency(SystemCoreClock);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_SCU_CLK_SetSrcEnable(SCUCLK_SRC_e eSrc, bool bEnable)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCUCLK_Type *ptScuClk = (SCUCLK_Type*)SCUCLK_REG_BASE;
    uint32_t un32Data = 0;

    un32Data = (bEnable << SCUCLK_SRC_ENABLE_POS);

    switch(eSrc)
    {
        case SCUCLK_SRC_HSE:
             SET_SCU_CSCR_HSE(ptScuClk, un32Data);
             break;
        case SCUCLK_SRC_HSI:
             SET_SCU_CSCR_HSI(ptScuClk, un32Data);
             break;
        case SCUCLK_SRC_LSI:
             SET_SCU_CSCR_LSI(ptScuClk, un32Data);
             break;
        case SCUCLK_SRC_LSE:
             SET_SCU_CSCR_LSE(ptScuClk, un32Data);
             break;
        default:
             eErr = HAL_ERR_PARAMETER;
             break;
    }
   
    return eErr;
}

HAL_ERR_e HAL_SCU_CLK_SetPLLConfig(bool bEnable, SCUCLK_PLL_CFG_t *ptCfg)
{
#if defined(SCU_FEATURE_VX_PLL_BLOCK)
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCUCLK_Type *ptScuClk = (SCUCLK_Type*)SCUCLK_REG_BASE;
    uint32_t un32Data = 0, un32PllClk = 0, un32Div = 0;
    bool bPllHSE = false;

    if(bEnable == false)
    {
        SET_SCU_PLLCON_PLLEN(ptScuClk, false);
    }
    else
    {
#if defined(SCU_FEATURE_PLL_ENABLE_AFTER_SETTING)
#else
        SET_SCU_PLLCON_PLLEN(ptScuClk, true);

        /* Need minimum 2us delay */
        PRV_SCUCLK_PLLDelay(2);
#endif
        if(ptCfg->eSrc == SCUCLK_PLL_SRC_HSE)
        {
            bPllHSE = true;
        }

        SET_SCU_SCCR_PLLCLKSEL(ptScuClk,bPllHSE);

        eErr = SCUCLK_SetPLLSrcDiv((P_SCUCLK_PLL_SRC_e)ptCfg->eSrc, (P_SCUCLK_DIV_e)ptCfg->eSrcDiv, &un32PllClk);
        if(eErr != HAL_ERR_OK)
        {
            return eErr;
        }

#if defined(SCU_FEATURE_PLL_PRE_KEY_VALUE)
        SET_SCU_PLLCON(ptScuClk, SCUCLK_PLLCON_KEY_VALUE);
#endif
 
        un32Data = SET_SCU_PLLCON_PLLEN_POS(true)
                   | SET_SCU_PLLCON_OUTDIV_POS(ptCfg->un8OutDiv)
                   | SET_SCU_PLLCON_POSTDIV1_POS(ptCfg->un8PostDiv1)
                   | SET_SCU_PLLCON_POSTDIV2_POS(ptCfg->un8PostDiv2)
                   | SET_SCU_PLLCON_PREDIV_POS(ptCfg->un8PreDiv)
                   | SET_SCU_PLLCON_PLLMODE_POS(ptCfg->ePllMode)
                   | SET_SCU_PLLCON_RESET_POS(true)
                   | SET_SCU_PLLCON_BYPASS_POS(true);

#if defined(SCU_FEATURE_PLL_CURRENT)
        un32Data = un32Data 
                   | SET_SCU_PLLCON_CUROPT_POS(ptCfg->eCurOpt)
                   | SET_SCU_PLLCON_VCOBIAS_POS(ptCfg->eVcoBias);
#endif
        SET_SCU_PLLCON(ptScuClk, un32Data);

#if defined(SCU_FEATURE_PLL_ENABLE_AFTER_SETTING)
        SET_SCU_PLLCON_PLLEN(ptScuClk, true);
#endif
        /* Need minimum 500us delay for clock stabilization */
        PRV_SCUCLK_PLLDelay(500);

        un32Data = SystemDelayUSCount * 500;

        while(!GET_SCU_PLLCON_LOCK(ptScuClk))
        {
            if(un32Data == 0)
            {
                eErr = HAL_ERR_TIMEOUT;
                break;
            }
            un32Data--;
        }

#if defined(SCU_FEATURE_HAS_PLL_READY_BIT)
        un32Data = SystemDelayUSCount * 500;
        while((GET_SCU_PLLCON(ptScuClk) & (1UL << 30)) == 0)
        {
            if(un32Data == 0)
            {
                eErr = HAL_ERR_TIMEOUT;
                break;
            }
            un32Data--;
        }
#endif

        if(eErr != HAL_ERR_OK)
        {
            return eErr;
        }
#if defined (SCU_FEATURE_PLL_OUTPUT_FORMULA_V2)
        /* - PLL Clock Frequency Formula */ 
        /*                               */ 
        /*                     ( FIN(un32PllClk) * ( FB(un8OutDiv) + 1 )                     */
        /* Fout = -------------------------------------------------------------------------  */
        /*        (( R(un8PreDiv) + 1 ) * ( N1(un8PostDiv1) + 1 ) * ( N2(un8PostDiv2 + 1 ))  */

        un32Div = (ptCfg->un8PreDiv + 1) * (ptCfg->un8PostDiv1 + 1) * (ptCfg->un8PostDiv2 + 1);
        un32Data = un32PllClk / un32Div;
        s_un32PLLClock = un32Data * (ptCfg->un8OutDiv + 1);
#elif defined (SCU_FEATURE_PLL_OUTPUT_FORMULA_V3)
        /* - PLL Clock Frequency Formula */ 
        /*                               */ 
        /*                     ( FIN(un32PllClk) * ( N(un8PostDiv1) + 1 )                     */
        /* Fout = -------------------------------------------------------------------------  */
        /*                  (( R(un8PreDiv) + 1 ) * ( P(un8OutDiv) + 1 ) )                */

        un32Div = (ptCfg->un8PreDiv + 1) * (ptCfg->un8OutDiv + 1);
        un32Data = un32PllClk / un32Div;
        s_un32PLLClock = un32Data * (ptCfg->un8PostDiv1 + 1);
#elif defined (SCU_FEATURE_PLL_OUTPUT_FORMULA_V4)
        /* - PLL Clock Frequency Formula */ 
        /*                               */ 
        /*                     ( FIN(un32PllClk) * ( N(un8PostDiv1) + 1 )                    */
        /* Fout = -------------------------------------------------------------------------  */
        /*                   2 * (( R(un8PreDiv) + 1 ) * ( P(un8OutDiv) + 1 ) )              */

        un32Div = 2 * (ptCfg->un8PreDiv + 1) * (ptCfg->un8OutDiv + 1);
        un32Data = un32PllClk / un32Div;
        s_un32PLLClock = un32Data * (ptCfg->un8PostDiv1 + 1);
#else
        /* - PLL Clock Frequency Formula */ 
        /*                               */ 
        /*          ( FIN(un32PllClk) * ( N1(un8PostDiv1) + 1 ) * ( D(ePllMode) + 1 ))    */
        /* Fout = ----------------------------------------------------------------------  */
        /*        (( R(un8PreDiv) + 1 ) * ( N2(un8PostDiv) + 1 ) * ( P(un8OutDiv + 1 ))   */

        un32Div = (ptCfg->un8PreDiv + 1) * (ptCfg->un8PostDiv2 + 1) * (ptCfg->un8OutDiv + 1);
        un32Data = un32PllClk / un32Div;
        s_un32PLLClock = un32Data * (ptCfg->un8PostDiv1 + 1) * (ptCfg->ePllMode + 1); 
#endif
    }

    return eErr;
#else
    (void)bEnable;
    (void)ptCfg;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_SCU_CLK_SetAutoRecovery(bool bEnable)
{
    SCUCLK_Type *ptScuClk = (SCUCLK_Type*)SCUCLK_REG_BASE;

    if(bEnable)
    {
        SET_SCU_CMR_MCLKREC(ptScuClk, SCUCLK_AUTO_RECOVERY_ON);
    }
    else
    {
        SET_SCU_CMR_MCLKREC(ptScuClk, SCUCLK_AUTO_RECOVERY_OFF);
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_SCU_CLK_SetOutput(SCUCLK_SRC_e eSrc, uint8_t un8OutputDiv, bool bEnable)
{
    SCUCLK_Type *ptScuClk = (SCUCLK_Type*)SCUCLK_REG_BASE;
    HAL_ERR_e eErr = HAL_ERR_OK;

    eErr = SCUCLK_SetClkOut((P_SCUCLK_SRC_e)eSrc, un8OutputDiv);
    if (eErr != HAL_ERR_OK)
    {
        return eErr;
    }

    SET_SCU_COR_CLKOEN(ptScuClk, bEnable);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_SCU_CLK_SetResetSrc(SCUCLK_SRC_e eSrc, bool bEnable)
{
#if defined(SCU_FEATURE_VX_CLOCK_RESET_SOURCE)
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCUCLK_Type *ptScuClk = (SCUCLK_Type*)SCUCLK_REG_BASE;

    switch(eSrc)
    {
#if defined(SCU_FEATURE_UNSUPPORT_HSE)
#else
        case SCUCLK_SRC_HSE:
            SET_SCU_CLK_RST_SRC_HSE_EN(ptScuClk, bEnable);
            break;
#endif
        case SCUCLK_SRC_MCLK:
            SET_SCU_CLK_RST_SRC_MCLK_EN(ptScuClk, bEnable);
            break;
#if defined(SCU_FEATURE_UNSUPPORT_LSE) || defined(SCU_FEATURE_UNSUPPORT_RESET_LSE)
#else
        case SCUCLK_SRC_LSE:
            SET_SCU_CLK_RST_SRC_LSE_EN(ptScuClk, bEnable);
            break;
#endif
        default:
            eErr = HAL_ERR_NOT_SUPPORTED;
            break;
    }

    return eErr;
#else
    (void)eSrc;
    (void)bEnable;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_SCU_CLK_GetResetSrcEvent(SCUCLK_SRC_e eSrc, bool *pbEvent)
{
#if defined(SCU_FEATURE_VX_CLOCK_RESET_SOURCE)
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCUCLK_Type *ptScuClk = (SCUCLK_Type*)SCUCLK_REG_BASE;

    switch(eSrc)
    {
#if defined(SCU_FEATURE_UNSUPPORT_HSE)
#else
        case SCUCLK_SRC_HSE:
            if(GET_SCU_CLK_RST_SRC_HSE_EN(ptScuClk))
            {
                *pbEvent = GET_SCU_CLK_RST_SRC_HSE_FLAG(ptScuClk);
                SET_SCU_CLK_RST_SRC_HSE_FLAG(ptScuClk, true);
            }
            break;
#endif
        case SCUCLK_SRC_MCLK:
            if(GET_SCU_CLK_RST_SRC_MCLK_EN(ptScuClk))
            {
                *pbEvent = GET_SCU_CLK_RST_SRC_MCLK_FLAG(ptScuClk);
                SET_SCU_CLK_RST_SRC_MCLK_FLAG(ptScuClk, true);
            }
            break;
#if defined(SCU_FEATURE_UNSUPPORT_LSE) || defined(SCU_FEATURE_UNSUPPORT_RESET_LSE)
#else
        case SCUCLK_SRC_LSE:
            if(GET_SCU_CLK_RST_SRC_LSE_EN(ptScuClk))
            {
                *pbEvent = GET_SCU_CLK_RST_SRC_LSE_FLAG(ptScuClk);
                SET_SCU_CLK_RST_SRC_LSE_FLAG(ptScuClk, true);
            }
            break;
#endif
        default:
            eErr = HAL_ERR_NOT_SUPPORTED;
            break;
    }

    return eErr;
#else
    (void)eSrc;
    (void)pbEvent;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_SCU_CLK_SetExtHSE(SCUCLK_HSE_FREQ_e eFreq, bool bNCEnable)
{
#if defined(SCU_FEATURE_VX_EXT_HSE_CONTROL)
#if defined(SCU_FEATURE_UNSUPPORT_HSE)
     (void)eFreq;
     (void)bNCEnable;
     return HAL_ERR_NOT_SUPPORTED;
#else
     SCUCLK_Type *ptScuClk = (SCUCLK_Type*)SCUCLK_REG_BASE;
     uint32_t un32Data = 0;

     un32Data = GET_SCU_EOS(ptScuClk);
     un32Data = (un32Data & SCUCLK_EXT_HSE_MSK)
                | SCUCLK_EXT_HSE_CURR(eFreq) << BIT_SCU_EOS_HSE_CURR
                | SCUCLK_EXT_HSE_FREQ(eFreq) << BIT_SCU_EOS_HSENC_DELAY
                | bNCEnable << BIT_SCU_EOS_HSENC_EN;

     SET_SCU_EOS_HSE(ptScuClk,un32Data);

     return HAL_ERR_OK;
#endif
#else
     (void)eFreq;
     (void)bNCEnable;
     return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_SCU_CLK_SetExtLSE(SCUCLK_LSE_CURR_e eCurr, bool bNCEnable)
{
#if defined(SCU_FEATURE_VX_EXT_LSE_CONTROL)
#if defined(SCU_FEATURE_UNSUPPORT_LSE)
     (void)eCurr;
     (void)bNCEnable;
     return HAL_ERR_NOT_SUPPORTED;
#else
     SCUCLK_Type *ptScuClk = (SCUCLK_Type*)SCUCLK_REG_BASE;
     uint32_t un32Data = 0;

     un32Data = GET_SCU_EOS(ptScuClk);
     un32Data = (un32Data & SCUCLK_EXT_LSE_MSK)
                | SCUCLK_EXT_LSE_CURR(eCurr) << BIT_SCU_EOS_LSE_CURR;
#if defined(SCU_FEATURE_UNSUPPORT_LSE_NC_ENABLE)
#else
     un32Data |= bNCEnable << BIT_SCU_EOS_LSENC_EN;
#endif

     SET_SCU_EOS_LSE(ptScuClk, un32Data);

     return HAL_ERR_OK;
#endif
#else
     (void)eCurr;
     (void)bNCEnable;
     return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_SCU_CLK_SetExtLSI(bool bLDOEnable, bool bLSEnable)
{
#if defined(SCU_FEATURE_VX_EXT_LSI_CONTROL)
#if defined(SCU_FEATURE_LSI_INTERNAL_LEVEL_SHIFTER)
     SCUCLK_Type *ptScuClk = (SCUCLK_Type*)SCUCLK_REG_BASE;
     
     SET_SCU_LSI_LS_EN(ptScuClk, bLSEnable);
#if defined(SCU_FEATURE_LSI_LOW_DROPOUT)
     SET_SCU_LSI_LDO_EN(ptScuClk, bLDOEnable);
#else
     (void)bLSEnable;
#endif
     return HAL_ERR_OK;
#else
     (void)bLDOEnable;
     (void)bLSEnable;
     return HAL_ERR_NOT_SUPPORTED;
#endif
#else
     (void)bLDOEnable;
     (void)bLSEnable;
     return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_SCU_CLK_SetPClkDiv(SCUCLK_DIV_e ePClkDiv)
{
#if defined(SCU_FEATURE_PERI_CLK_DIV)
     SCUCLK_Type *ptScuClk = (SCUCLK_Type*)SCUCLK_REG_BASE;

     if(ePClkDiv > (SCUCLK_DIV_e)SCUCLK_PCLK_DIV_MAX)
     {
         return HAL_ERR_PARAMETER;
     }

     SET_SCU_SCCR_PCLKDIV(ptScuClk, (uint8_t)ePClkDiv);
     SystemPeriClock = SystemCoreClock / SCUCLK_EXPO2((uint8_t)ePClkDiv);
     return HAL_ERR_OK;
#else
     (void)ePClkDiv;
     return HAL_ERR_NOT_SUPPORTED;
#endif
}

#if defined(SCU_FEATURE_VX_SCU_CLOCK_IRQ_HANDLER)
static void PRV_SCUCLK_IRQHandler(PRV_SCUCLK_MON_e eMon)
{
    SCUCLK_Type *ptScuClk = (SCUCLK_Type*)SCUCLK_REG_BASE;
    SCUCLK_CTRL_BLK_t *ptCcb = NULL;
#if (CONFIG_SCU_VER_MAJOR == 1)
    (void)eMon;

    if(s_tCcb[(uint8_t)PRV_SCUCLK_MON_MCLK].bEnable == true)
    {
        if(GET_SCU_CMR_MCLKFAIL(ptScuClk))
        {
            SET_SCU_CMR_MCLKFAIL(ptScuClk, true);
            ptCcb = &s_tCcb[(uint8_t)PRV_SCUCLK_MON_MCLK];
            if(ptCcb->pfnHandler)
            {
                ptCcb->pfnHandler(SCUCLK_MON_EVENT_MCLKFAIL, ptCcb->pContext);
            }
        }
    }
#if defined(SCU_FEATURE_UNSUPPORT_HSE)
#else
    if(s_tCcb[(uint8_t)PRV_SCUCLK_MON_HSE].bEnable == true)
    {
        if(GET_SCU_CMR_HSEFAIL(ptScuClk))
        {
            SET_SCU_CMR_HSEFAIL(ptScuClk, true);
            ptCcb = &s_tCcb[(uint8_t)PRV_SCUCLK_MON_HSE];
            if(ptCcb->pfnHandler)
            {
                ptCcb->pfnHandler(SCUCLK_MON_EVENT_HSEFAIL, ptCcb->pContext);
            }
        }
    }
#endif
#if defined(SCU_FEATURE_UNSUPPORT_LSE)
#else
    if(s_tCcb[(uint8_t)PRV_SCUCLK_MON_LSE].bEnable == true)
    {
        if(GET_SCU_CMR_LSEFAIL(ptScuClk))
        {
            SET_SCU_CMR_LSEFAIL(ptScuClk, true);
            ptCcb = &s_tCcb[(uint8_t)PRV_SCUCLK_MON_LSE];
            if(ptCcb->pfnHandler)
            {
                ptCcb->pfnHandler(SCUCLK_MON_EVENT_LSEFAIL, ptCcb->pContext);
            }
        }
    }
#endif

#else
    uint32_t un32Event = 0;

    switch(eMon)
    {
        case PRV_SCUCLK_MON_MCLK:
            if(GET_SCU_CMR_MCLKFAIL(ptScuClk))
            {
                un32Event = SCUCLK_MON_EVENT_MCLKFAIL;
                SET_SCU_CMR_MCLKFAIL(ptScuClk, true);
            }
            break;
#if defined(SCU_FEATURE_UNSUPPORT_HSE)
#else
        case PRV_SCUCLK_MON_HSE:
            if(GET_SCU_CMR_HSEFAIL(ptScuClk))
            {
                un32Event = SCUCLK_MON_EVENT_HSEFAIL;
                SET_SCU_CMR_HSEFAIL(ptScuClk, true);
            }
            break;
#endif
#if defined(SCU_FEATURE_UNSUPPORT_LSE)
#else
        case PRV_SCUCLK_MON_LSE:
            if(GET_SCU_CMR_LSEFAIL(ptScuClk))
            {
                un32Event = SCUCLK_MON_EVENT_LSEFAIL;
                SET_SCU_CMR_LSEFAIL(ptScuClk, true);
            }
            break;
#endif
        default:
            break;
    }

    ptCcb = &s_tCcb[(uint8_t)eMon];

    if(ptCcb->pfnHandler)
    {
         ptCcb->pfnHandler(un32Event, ptCcb->pContext);
    }

#endif
}

#elif defined(SCU_FEATURE_FX_SCU_CLOCK_IRQ_HANDLER)
static void PRV_SCUCLK_IRQHandler(PRV_SCUCLK_MON_e eMon)
{
}
#endif


#if (CONFIG_SCU_VER_MAJOR == 1)
void SCUCLK_SysClkIRQHandler(void)
{
    PRV_SCUCLK_IRQHandler(PRV_SCUCLK_MON_MCLK);
}
#else
void SCUCLK_SysClkIRQHandler(void)
{
    PRV_SCUCLK_IRQHandler(PRV_SCUCLK_MON_MCLK);
}
void SCUCLK_HSEIRQHandler(void)
{
    PRV_SCUCLK_IRQHandler(PRV_SCUCLK_MON_HSE);
}

void SCUCLK_LSEIRQHandler(void)
{
    PRV_SCUCLK_IRQHandler(PRV_SCUCLK_MON_LSE);
}
#endif
