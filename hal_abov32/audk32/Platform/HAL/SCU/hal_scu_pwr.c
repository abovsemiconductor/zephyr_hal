/**
 *******************************************************************************
 * @file        hal_scu_pwr.c
 * @author      ABOV R&D Division 
 * @brief       Power sub system in System Control Unit
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

#if defined(_SCU_PWR)
#include "hal_scu.h"
#include "hal_scu_pwr.h"
#include "hal_scu_prv.h"

#if defined(_NMI)
#include "hpl_nmi.h"
#endif

#if defined (SCU_FEATURE_POWER_HAS_WAKEUP_INTERRUPT)
typedef struct
{
    bool                           bNonMask;
    pfnSCUPWR_WKUP_IRQ_Handler_t   pfnHandler;
    void                           *pContext;
} SCUPWR_CTRL_BLK_t;

static SCUPWR_CTRL_BLK_t s_tPcb;
#endif

HAL_ERR_e HAL_SCU_PWR_SetIRQWakeUp(pfnSCUPWR_WKUP_IRQ_Handler_t pfnHandler, void *pContext, uint32_t un32IRQPrio, SCUPWR_WKUP_INTR_e eIntr)
{
#if defined (SCU_FEATURE_POWER_HAS_WAKEUP_INTERRUPT)
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCUPMU_Type *ptPmu = (SCUPMU_Type *)SCUPMU_REG_BASE;
    bool bEnable = false;

    switch(eIntr)
    {
        case SCUPWR_WKUP_INTR_NONE:
#if defined(SCU_FEATURE_IRQ_UNMASK_ENABLE)
            SCU_SetIntrUnMask(SCUPMU_WKUP_IRQ, false);
#endif
            s_tPcb.pfnHandler = NULL;
            s_tPcb.pContext = NULL; 
            NVIC_ClearPendingIRQ(SCUPMU_WKUP_IRQ);
            NVIC_DisableIRQ(SCUPMU_WKUP_IRQ);
            s_tPcb.bNonMask = false;
            break;
        case SCUPWR_WKUP_INTR_MASK:
#if defined(SCU_FEATURE_IRQ_UNMASK_ENABLE)
            SCU_SetIntrUnMask(SCUPMU_WKUP_IRQ, true);
#endif
            NVIC_ClearPendingIRQ(SCUPMU_WKUP_IRQ);
            NVIC_SetPriority(SCUPMU_WKUP_IRQ, un32IRQPrio);
            NVIC_EnableIRQ(SCUPMU_WKUP_IRQ);
            s_tPcb.pfnHandler = pfnHandler;
            s_tPcb.pContext = pContext; 
            s_tPcb.bNonMask = false;
            bEnable = true;
            break;
        case SCUPWR_WKUP_INTR_NON_MASK:
#if defined(SCU_FEATURE_IRQ_UNMASK_ENABLE)
            SCU_SetIntrUnMask(SCUPMU_WKUP_IRQ, false);
#endif
#if defined(_NMI)
            eErr = HPL_NMI_SetIRQ(NMI_INTR_SOURCE, (pfnNMI_IRQ_Handler_t)pfnHandler, pContext, s_tPcb.bNonMask);
#endif
            s_tPcb.bNonMask = true;
            s_tPcb.pfnHandler = NULL;
            s_tPcb.pContext = NULL; 
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }


    SET_SCU_PMU_DS1_WKUP_EN(ptPmu, bEnable);

    return eErr;
#else
    (void)pfnHandler;
    (void)pContext;
    (void)un32IRQPrio;
    (void)eIntr;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_SCU_PWR_SetMode(SCUPWR_MODE_e eMode)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;
#if defined (SCU_FEATURE_DEEPSLEEP_SUB_MODE)
    SCUPMU_Type *ptPmu = (SCUPMU_Type *)(SCUPMU_REG_BASE);
    SCUPWR_DS_MODE_e eDsMode = SCUPWR_DS_MODE_MAX;
#endif

    switch(eMode)
    {
        case SCUPWR_MODE_SLEEP:
            SCB->SCR = 0;
            __WFI();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            break;
        case SCUPWR_MODE_DEEPSLEEP:
            SET_SCU_VDC_DEEPSLEEP(ptScu, false);
#if defined (SCU_FEATURE_DEEPSLEEP_SUB_MODE)
            eDsMode = (SCUPWR_DS_MODE_e)GET_SCU_PMU_DS_MODE(ptPmu);
            if (eDsMode == SCUPWR_DS_MODE_1)
            {
                SCUPWR_SetPostProcess();
            }
#endif
            SCB->SCR = 0x04;
            __WFI();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            break;
        case SCUPWR_MODE_DEEPSLEEP2:
            SET_SCU_VDC_DEEPSLEEP(ptScu, true);
            SCB->SCR = 0x04;
            __WFI();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            break;
        case SCUPWR_MODE_INIT:
        case SCUPWR_MODE_RUN:
        default:
            /* Nothing to do */
            break;
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_SCU_PWR_SetDeepSleepMode(SCUPWR_DS_CFG_t *ptDs)
{
#if defined (SCU_FEATURE_DEEPSLEEP_SUB_MODE)
    HAL_ERR_e eErr = HAL_ERR_OK;
    SCUPMU_Type *ptPmu = (SCUPMU_Type *)(SCUPMU_REG_BASE);
#if defined (SCU_FEATURE_DEEPSLEEP_WKUP_PORT_CONTROL)
    uint32_t un32RegAddr = 0;
#endif

    if (ptDs->eDsMode < SCUPWR_DS_MODE_MAX)
    {
        SET_SCU_PMU_DS_MODE(ptPmu, ptDs->eDsMode);
#if defined (SCU_FEATURE_DEEPSLEEP_WKUP_PORT_CONTROL)
        if (ptDs->eDsMode != SCUPWR_DS_MODE_0)
        {
            un32RegAddr = (uint32_t)GET_SCU_PMU_ADDR(ptPmu);
            SET_SCU_PMU_WKUP_EN(un32RegAddr, ptDs->un8WkUpPinEnable); 
        }
#endif
    }
    else
    {
        eErr = HAL_ERR_PARAMETER;
    }

    return eErr;
#else
    (void)ptDs;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_SCU_PWR_SetAlwaysOn(uint32_t un32Aon, uint32_t un32Enable)
{

#if defined(SCU_FEATURE_VX_AON_SOURCE)
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;
    uint32_t un32Data = 0;

#if defined(SCUPWR_AON_VDC_EN)
    if((un32Aon & SCUPWR_AON_VDC) && (un32Enable & SCUPWR_AON_VDC))
    {
       un32Data |= (1UL << BIT_SCU_SMR_VDC_POS); 
    }    
#endif

#if defined(SCUPWR_AON_BGR_EN)
    if((un32Aon & SCUPWR_AON_BGR) && (un32Enable & SCUPWR_AON_BGR))
    {
       un32Data |= (1UL << BIT_SCU_SMR_BGR_POS); 
    }    
#endif

#if defined(SCUPWR_AON_LSI_EN)
    if((un32Aon & SCUPWR_AON_LSI) && (un32Enable & SCUPWR_AON_LSI))
    {
       un32Data |= (1UL << BIT_SCU_SMR_LSI_POS); 
    }    
#endif

#if defined(SCUPWR_AON_LSE_EN)
    if((un32Aon & SCUPWR_AON_LSE) && (un32Enable & SCUPWR_AON_LSE))
    {
       un32Data |= (1UL << BIT_SCU_SMR_LSE_POS); 
    }    
#endif

#if defined(SCUPWR_AON_HSI_EN)
    if((un32Aon & SCUPWR_AON_HSI) && (un32Enable & SCUPWR_AON_HSI))
    {
       un32Data |= (1UL << BIT_SCU_SMR_HSI_POS); 
    }    
#endif

#if defined(SCUPWR_AON_HSE_EN)
    if((un32Aon & SCUPWR_AON_HSE) && (un32Enable & SCUPWR_AON_HSE))
    {
       un32Data |= (1UL << BIT_SCU_SMR_HSE_POS); 
    }    
#endif

#if defined(SCUPWR_AON_PLL_EN)
    if((un32Aon & SCUPWR_AON_PLL) && (un32Enable & SCUPWR_AON_PLL))
    {
       un32Data |= (1UL << BIT_SCU_SMR_PLL_POS); 
    }    
#endif

#if defined(SCUPWR_AON_EXTCLK_EN)
    if((un32Aon & SCUPWR_AON_EXTCLK) && (un32Enable & SCUPWR_AON_EXTCLK))
    {
       un32Data |= (1UL << BIT_SCU_SMR_EXTCLK_POS); 
    }    
#endif

    SET_SCU_SMR(ptScu,un32Data);
#else
    (void)un32Aon;
    (void)un32Enable;
#endif

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_SCU_PWR_SetVdcDelay(uint8_t un8VdcDelay)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;

    SET_SCU_DATA_VDC_DELAY(ptScu, un8VdcDelay);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_SCU_PWR_SetPDIndicator(bool bLevel)
{
#if defined(SCU_FEATURE_POWER_DOWN_PIN_LEVEL)
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;
    SET_SCU_PD_IND_LVL(ptScu, bLevel);
    return HAL_ERR_OK;
#else
    (void)bLevel;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_SCU_PWR_SetBackupMode(bool bEnable)
{
#if defined(SCU_FEATURE_POWER_BACKUP_MODE)
    SCU_Type *ptScu = (SCU_Type *)SCU_REG_BASE;
    SET_SCU_PDR_EN(ptScu, bEnable);
    return HAL_ERR_OK;
#else
    (void)bEnable;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_SCU_PWR_SetBackupData(SCUPWR_BAK_DATA_t *ptBak, uint8_t un8Len)
{
#if defined(SCU_FEATURE_BACKUP_DATA)
    if(un8Len > CONFIG_SCU_PWR_BACKUP_DATA_COUNT)
    {
        return HAL_ERR_PARAMETER;
    }

    for(int i = 0; i < un8Len; i++)
    {
        SCUPWR_SetBackupData(ptBak[i].un8Num, ptBak[i].un32Data);
    }
    return HAL_ERR_OK;
#else
    (void)ptBak;
    (void)un8Len;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_SCU_PWR_GetBackupData(SCUPWR_BAK_DATA_t *ptBak, uint8_t un8Len)
{
#if defined(SCU_FEATURE_BACKUP_DATA)
    if(un8Len > CONFIG_SCU_PWR_BACKUP_DATA_COUNT)
    {
        return HAL_ERR_PARAMETER;
    }

    for(int i = 0; i < un8Len; i++)
    {
       SCUPWR_GetBackupData(ptBak[i].un8Num, &ptBak[i].un32Data);
    }
    return HAL_ERR_OK;
#else
    (void)ptBak;
    (void)un8Len;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_SCU_PWR_SetExtension(SCUPWR_EPC_CFG_t *ptEpc)
{
#if defined (SCU_FEATURE_FLASH_POWER_CONTROL)
    SCUPMU_Type *ptPmu = (SCUPMU_Type *)(SCUPMU_REG_BASE);
#if defined (_DFMC)
    SET_SCU_PMU_DFLASH_EN(ptPmu, ptEpc->bDFlashPwrOff);
#endif
    SET_SCU_PMU_CFLASH_EN(ptPmu, ptEpc->bFlashPwrOff);
    return HAL_ERR_OK;
#else
    (void)ptEpc;
    return HAL_ERR_NOT_SUPPORTED;
#endif

}

HAL_ERR_e HAL_SCU_PWR_SetPortPupd(SCUPWR_PORT_ID_e ePortId, uint32_t un32Pupd)
{
#if defined (SCU_FEATURE_DEEPSLEEP_PORT_CONTROL)
    uint32_t un32RegAddr = 0;
    SCUPMU_Type *ptPmu = (SCUPMU_Type *)(SCUPMU_REG_BASE);
    if (ePortId >= SCUPMU_PORT_MAX)
    {
        return HAL_ERR_PARAMETER;
    }
    if ((SCUPWR_DS_MODE_e)GET_SCU_PMU_DS_MODE(ptPmu) != SCUPWR_DS_MODE_3)
    {
        return HAL_ERR_INVALID_USE;
    }
    un32RegAddr = (uint32_t)(GET_SCU_PMU_PUPD_BASE_ADDR(ptPmu) + ((uint8_t)ePortId * SCUPMU_PUPD_ADDR_OFFSET));
    SET_SCU_PMU_PUPD(un32RegAddr, un32Pupd);  
    return HAL_ERR_OK;
#else
    (void)ePortId;
    (void)un32Pupd;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_SCU_PWR_GetDsWkUpReason(SCUPWR_DS_WKUP_REASON_e *peWkUpReason)
{
#if defined (SCU_FEATURE_DEEPSLEEP_SUB_MODE)
#if defined (SCU_FEATURE_DEEPSLEEP_WKUP_PORT_CONTROL)
    SCUPMU_Type *ptPmu = (SCUPMU_Type *)(SCUPMU_REG_BASE);
    if (GET_SCU_PMU_DS2_WKUP_FLAG(ptPmu))
    {
        *peWkUpReason = SCUPWR_DS_WKUP_REASON_2;
    }
    else if (GET_SCU_PMU_DS3_WKUP_FLAG(ptPmu))
    {
        *peWkUpReason = SCUPWR_DS_WKUP_REASON_3;
    }
    else
    {
        *peWkUpReason = SCUPWR_DS_WKUP_REASON_MAX;
    }
#endif

    return HAL_ERR_OK;
#else
    (void)peWkUpReason;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

#if defined (SCU_FEATURE_POWER_HAS_WAKEUP_INTERRUPT)
void PRV_SCU_PWR_WkUpIRQHandler(void)
{ 
    SCUPMU_Type *ptPmu = (SCUPMU_Type *)SCUPMU_REG_BASE;
    uint32_t un32Event = 0;
    
    if (GET_SCU_PMU_DS1_WKUP_FLAG(ptPmu))
    {
        SET_SCU_PMU_DS1_WKUP_FLAG(ptPmu, true);
        un32Event = SCUPWR_DS_WKUP_REASON_1;
    }

    if(s_tPcb.pfnHandler != NULL && un32Event != 0)
    {
        s_tPcb.pfnHandler(un32Event, s_tPcb.pContext);
    }
}

void SCUPWR_WkUpIRQHandler(void)
{
    PRV_SCU_PWR_WkUpIRQHandler();
}
#endif

#endif /* _SCU_PWR */
