/**
 *******************************************************************************
 * @file        hal_pcu.c
 * @author      ABOV R&D Division
 * @brief       Port Control Unit
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

#include "hal_pcu.h"
#include "hal_pcu_prv.h"

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
#include "hpl_nmi.h"
#endif

typedef struct
{
    PCU_OPS_e               eOps;
    pfnPCU_IRQ_Handler_t    pfnHandler;
    void                    *pContext;

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
    bool                    bNmiEnable;
#endif

} PCU_CTRL_BLK_t;

static PCU_CTRL_BLK_t s_tPcb[PCU_PORT_GROUP_NUM];

#if defined(PCU_FEATURE_EXT_INTERRUPT_CONFIGURATION)
static void PRV_PCU_IRQHandler(P_PCU_EINT_ID_e eEIntId);
#else
static void PRV_PCU_IRQHandler(PCU_ID_e eId, PORT_Type *ptPcu, uint32_t un32Status);
#endif

#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
static void PRV_PCU_NMIHandler(uint32_t un32Event, void *pContext)
{
    PORT_Type *ptPcu;
    uint32_t un32Status = 0;

    for (int i = 0; i < PCU_PORT_GROUP_NUM; i++)
    {
        if(s_tPcb[i].bNmiEnable == true)
        {
            ptPcu = (PORT_Type *)(PCU_REG_BASE + (PCU_REG_OFFSET * (PCU_ID_e)i));
            un32Status = GET_PCU_ISR_REG(ptPcu);
            if(un32Status)
            {
                PRV_PCU_IRQHandler((PCU_ID_e)i, ptPcu, un32Status);
            }
        }
    }
}
#endif

static HAL_ERR_e PRV_PCU_GetVaildPort(PCU_ID_e eId)
{
    return PCU_GetValidPort((P_PCU_ID_e)eId);
}

HAL_ERR_e HAL_PCU_SetAltMode(PCU_ID_e eId, PCU_PIN_ID_e ePinId, PCU_ALT_e eAlt)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    PORT_Type *ptPcu;

    eErr = PRV_PCU_GetVaildPort(eId);
    if(eErr != HAL_ERR_OK)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptPcu = PCU_GetReg(eId);

    SET_PCU_ACCESS_EN();

    SET_PCU_MODE_ALT(ptPcu, PCU_ALTMODE, (PCU_ALTMODE_BIT((uint32_t)ePinId)));

    if(ePinId < PCU_PIN_ID_8)
    {
        SET_PCU_ALT1(ptPcu, PCU_ALTMODE_TYPE((uint8_t)eAlt),(PCU_ALTTYPE_BIT((uint32_t)ePinId)));
    }
    else
    {
        SET_PCU_ALT2(ptPcu, PCU_ALTMODE_TYPE((uint8_t)eAlt),(PCU_ALT2TYPE_BIT((uint32_t)(ePinId))));
    }

    SET_PCU_ACCESS_DIS();

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_PCU_SetInOutMode(PCU_ID_e eId, PCU_PIN_ID_e ePinId, PCU_INOUT_e eInOut)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    PORT_Type *ptPcu;

    eErr = PRV_PCU_GetVaildPort(eId);
    if(eErr != HAL_ERR_OK)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptPcu = PCU_GetReg(eId);

    SET_PCU_ACCESS_EN();

    switch(eInOut)
    {
        case PCU_INOUT_INPUT:
             SET_PCU_MODE(ptPcu, PCU_INPUTMODE, (((uint32_t)ePinId)*2));
             break;
        case PCU_INOUT_ANG_INPUT:
             SET_PCU_MODE(ptPcu, PCU_INPUTMODE_ANG, (((uint32_t)ePinId)*2));
             break;
        case PCU_INOUT_OUTPUT_PUSH_PULL:
        case PCU_INOUT_OUTPUT_OPEN_DRAIN:
             SET_PCU_MODE(ptPcu, PCU_OUTPUTMODE((uint8_t)eInOut), (((uint32_t)ePinId)*2));
             SET_PCU_MODE_TYPE(ptPcu, PCU_OUTPUTMODE_TYP((uint8_t)eInOut), (((uint32_t)ePinId)));
             break;
        default:
             break;
    } 

#if defined(PCU_FEATURE_RTC_PORT)
    PCU_SetRTCPortInOutMode((P_PCU_ID_e)eId, (P_PCU_PIN_ID_e)ePinId, (P_PCU_INOUT_e)eInOut);
#endif

    SET_PCU_ACCESS_DIS();

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_PCU_SetPullUpDown(PCU_ID_e eId, PCU_PIN_ID_e ePinId, PCU_PUPD_e ePupd)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    PORT_Type *ptPcu;

    eErr = PRV_PCU_GetVaildPort(eId);
    if(eErr != HAL_ERR_OK)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptPcu = PCU_GetReg(eId);

    SET_PCU_ACCESS_EN();

    SET_PCU_PULL_MODE(ptPcu, PCU_PULLMODE_TYPE((uint8_t)ePupd), PCU_PULLMODE_BIT((uint32_t)ePinId));

    SET_PCU_ACCESS_DIS();

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_PCU_GetInputValue(PCU_ID_e eId, PCU_PIN_ID_e ePinId, PCU_PORT_e *peInput)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    GPIO_Type *ptGpio;

    eErr = PRV_PCU_GetVaildPort(eId);
    if(eErr != HAL_ERR_OK)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptGpio = PCU_GPIO_GetReg(eId);

    *peInput = (PCU_PORT_e)GET_PCU_INPUT_DATA(ptGpio, (uint8_t)ePinId);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_PCU_SetOutputValue(PCU_ID_e eId, PCU_PIN_ID_e ePinId, PCU_PORT_e eOutput)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    GPIO_Type *ptGpio;

    eErr = PRV_PCU_GetVaildPort(eId);
    if(eErr != HAL_ERR_OK)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptGpio = PCU_GPIO_GetReg(eId);

    SET_PCU_OUTPUT_DATA(ptGpio, (uint8_t)eOutput, (uint32_t)ePinId);

#if defined(PCU_FEATURE_RTC_PORT)
    PCU_SetRTCPortOutputValue((P_PCU_ID_e)eId, (P_PCU_PIN_ID_e)ePinId, (P_PCU_PORT_e)eOutput);
#endif

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_PCU_SetOutputSustain(PCU_ID_e eId, PCU_PIN_ID_e ePinId, bool bEnable)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    GPIO_Type *ptGpio;

    ptGpio = PCU_GPIO_GetReg(eId);

    eErr = PRV_PCU_GetVaildPort(eId);
    if(eErr != HAL_ERR_OK)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_PCU_OUTPUT_SUSTAIN(ptGpio, bEnable, (uint32_t)ePinId);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_PCU_SetOutputBit(PCU_ID_e eId, PCU_PIN_ID_e ePinId, PCU_OUTPUT_BIT_e eBit)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    GPIO_Type *ptGpio;

    eErr = PRV_PCU_GetVaildPort(eId);
    if(eErr != HAL_ERR_OK)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptGpio = PCU_GPIO_GetReg(eId);

    if(eBit == PCU_OUTPUT_BIT_SET)
    {
        SET_PCU_OUTPUT_BIT(ptGpio, true, (uint32_t)ePinId);
#if defined(PCU_FEATURE_RTC_PORT)
        PCU_SetRTCPortOutputValue((P_PCU_ID_e)eId, (P_PCU_PIN_ID_e)ePinId, P_PCU_PORT_HIGH);
#endif
    }
    else
    {
        SET_PCU_OUTPUT_CLEAR_BIT(ptGpio, true, (uint32_t)ePinId);
#if defined(PCU_FEATURE_RTC_PORT)
        PCU_SetRTCPortOutputValue((P_PCU_ID_e)eId, (P_PCU_PIN_ID_e)ePinId, P_PCU_PORT_LOW);
#endif
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_PCU_SetIntrPort(PCU_ID_e eId, PCU_PIN_ID_e ePinId, PCU_INTR_MODE_e eMode, PCU_INTR_TRG_e eTrg, uint8_t un8IntNum)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    eErr = PRV_PCU_GetVaildPort(eId);
    if(eErr != HAL_ERR_OK)
    {
        return HAL_ERR_INVALID_ID;
    }

    return PCU_SetIntrPort((P_PCU_ID_e)eId, (P_PCU_PIN_ID_e)ePinId,
                           (P_PCU_INTR_MODE_e)eMode, (P_PCU_INTR_TRG_e)eTrg,
                           un8IntNum);

}

HAL_ERR_e HAL_PCU_GetIntrStatus(PCU_ID_e eId, PCU_PIN_ID_e ePinId, PCU_INTR_STATUS_e *peStatus)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    eErr = PRV_PCU_GetVaildPort(eId);
    if(eErr != HAL_ERR_OK)
    {
        return HAL_ERR_INVALID_ID;
    }

    return PCU_GetIntrPort((P_PCU_ID_e)eId, (P_PCU_PIN_ID_e)ePinId, (P_PCU_INTR_STATUS_e *)peStatus);

}

HAL_ERR_e HAL_PCU_SetPortDebounce(PCU_ID_e eId, PCU_PIN_ID_e ePinId, bool bEnable)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    PORT_Type *ptPcu;

    eErr = PRV_PCU_GetVaildPort(eId);
    if(eErr != HAL_ERR_OK)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptPcu = PCU_GetReg(eId);

    SET_PCU_ACCESS_EN();
    SET_PCU_DEBOUNCE_EN(ptPcu, bEnable, (uint32_t)ePinId);
    SET_PCU_ACCESS_DIS();

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_PCU_SetClkDebounce(PCU_ID_e eId, PCU_DEBOUNCE_CLK_CFG_t *ptClkCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    eErr = PRV_PCU_GetVaildPort(eId);
    if(eErr != HAL_ERR_OK)
    {
        return HAL_ERR_INVALID_ID;
    }

    return PCU_SetDebounceClk((P_PCU_ID_e)eId, (P_PCU_CLK_MCCR_e)ptClkCfg->eMccr, ptClkCfg->un8MccrDiv);
}

HAL_ERR_e HAL_PCU_SetPortFInputLevel(PCU_ID_e eId, PCU_PIN_ID_e ePinId, bool bLevel)
{
#if defined(PCU_FEATURE_PORT_F_LEVEL)
    PORTF_Type *ptPortF;

    if(eId != PCU_ID_F || (ePinId != PCU_PIN_ID_5 
       && ePinId != PCU_PIN_ID_6 && ePinId != PCU_PIN_ID_7))
    {
        return HAL_ERR_INVALID_ID;
    }

    ptPortF = (PORTF_Type *)PCU_GPIO_GetReg(eId);

    SET_PCU_INPUT_LEVEL(ptPortF, bLevel, ((uint8_t)ePinId - PCU_PORTF_LEVEL_OFFSET));

    return HAL_ERR_OK;
#else
    (void)eId;
    (void)ePinId;
    (void)bLevel;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_PCU_SetPortStrength(PCU_ID_e eId, PCU_PIN_ID_e ePinId, bool bEnable)
{
#if defined(PCU_FEATURE_PORT_STRENGTH)

#if (CONFIG_PCU_VER_MAJOR == 1)
    HAL_ERR_e eErr = HAL_ERR_OK;
    GPIO_Type *ptGpio;

    ptGpio = PCU_GPIO_GetReg(eId);
 
    switch(eId)
    {
        case PCU_ID_B:
            if(ePinId > PCU_PIN_ID_2)
            {
                eErr = HAL_ERR_INVALID_ID;
            }
            break;
        case PCU_ID_C:
            if((ePinId > PCU_PIN_ID_5) || (ePinId < PCU_PIN_ID_2))
            {
                eErr = HAL_ERR_INVALID_ID;
            }
            break;
        default:
            eErr = HAL_ERR_PARAMETER;
            break;
    }

    if(eErr == HAL_ERR_OK)
    {
        SET_PCU_ACCESS_EN();
        SET_PCU_STR_EN(ptGpio, bEnable, PCU_STR_BIT((uint8_t)ePinId));
        SET_PCU_ACCESS_DIS();
    }

    return eErr;
#elif (CONFIG_PCU_VER_MAJOR == 2)
    HAL_ERR_e eErr = HAL_ERR_OK;
    GPIO_Type *ptGpio;

    eErr = PRV_PCU_GetVaildPort(eId);
    if(eErr != HAL_ERR_OK)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptGpio = PCU_GPIO_GetReg(eId);

    SET_PCU_STR_EN(ptGpio, bEnable, (uint8_t)ePinId);

    return eErr;
#endif

#else
    (void)eId;
    (void)ePinId;
    (void)bEnable;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_PCU_SetPortLowVoltageInput(PCU_ID_e eId, PCU_PIN_ID_e ePinId, bool bEnable)
{
#if defined(PCU_FEATURE_SUPPORT_LOW_VOLTAGE)
    HAL_ERR_e eErr = HAL_ERR_OK;
    LVINER_Type *ptLvin;
    uint16_t u16LvenPort = 0;
    uint8_t u8Lven = 0;
    uint8_t u8Pos = 0;

    ptLvin = PCU_LVINER_GetReg(eId);

    u16LvenPort = PCU_LVINER_ID_PIN(eId, ePinId);

    switch (u16LvenPort)
    {
    case PCU_LVINER_ID_PIN(PCU_ID_F, PCU_PIN_ID_1): u8Pos++;
    case PCU_LVINER_ID_PIN(PCU_ID_F, PCU_PIN_ID_0): u8Pos++;
    case PCU_LVINER_ID_PIN(PCU_ID_E, PCU_PIN_ID_7): u8Pos++;
    case PCU_LVINER_ID_PIN(PCU_ID_E, PCU_PIN_ID_6): u8Pos++;
    case PCU_LVINER_ID_PIN(PCU_ID_E, PCU_PIN_ID_3): u8Pos++;
    case PCU_LVINER_ID_PIN(PCU_ID_E, PCU_PIN_ID_2): u8Pos++;
    case PCU_LVINER_ID_PIN(PCU_ID_E, PCU_PIN_ID_1): u8Pos++;
    case PCU_LVINER_ID_PIN(PCU_ID_E, PCU_PIN_ID_0): u8Pos++;
    case PCU_LVINER_ID_PIN(PCU_ID_D, PCU_PIN_ID_1): u8Pos++;
    case PCU_LVINER_ID_PIN(PCU_ID_D, PCU_PIN_ID_0): u8Pos++;
    case PCU_LVINER_ID_PIN(PCU_ID_C, PCU_PIN_ID_9): u8Pos++;
    case PCU_LVINER_ID_PIN(PCU_ID_B, PCU_PIN_ID_5): u8Pos++;
    case PCU_LVINER_ID_PIN(PCU_ID_B, PCU_PIN_ID_4): u8Pos++;
    case PCU_LVINER_ID_PIN(PCU_ID_B, PCU_PIN_ID_3): u8Pos++;
    case PCU_LVINER_ID_PIN(PCU_ID_B, PCU_PIN_ID_2): u8Pos++;
    case PCU_LVINER_ID_PIN(PCU_ID_B, PCU_PIN_ID_1): u8Pos++;
    case PCU_LVINER_ID_PIN(PCU_ID_B, PCU_PIN_ID_0): u8Pos++;
    case PCU_LVINER_ID_PIN(PCU_ID_A, PCU_PIN_ID_7): u8Pos++;
        u8Lven = u8Pos - 1;
        break;
    default:
        eErr = HAL_ERR_INVALID_ID;
        break;
    }

    if(eErr == HAL_ERR_OK)
    {
        SET_PCU_ACCESS_EN();
        SET_PCU_LVINER_EN(ptLvin, bEnable, u8Lven);
        SET_PCU_ACCESS_DIS();
    }

    return eErr;
#else
    (void)eId;
    (void)ePinId;
    (void)bEnable;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_PCU_SetPortAltOpenDrain(PCU_ID_e eId, PCU_PIN_ID_e ePinId, bool bEnable)
{
#if defined(PCU_FEATURE_SUPPORT_OPENDRAIN)
    HAL_ERR_e eErr = HAL_ERR_OK;
    AFODCR_Type *ptAfodcr;
    uint16_t u16AfodPort = 0;
    uint8_t u8Foden = 0;

    ptAfodcr = PCU_AFODCR_GetReg(eId);

    u16AfodPort = PCU_AFODCR_ID_PIN(eId, ePinId);

    switch (u16AfodPort)
    {
    case PCU_AFODCR_ID_PIN(PCU_ID_F, PCU_PIN_ID_0):
        u8Foden = 16;
        break;
    case PCU_AFODCR_ID_PIN(PCU_ID_B, PCU_PIN_ID_4):
        u8Foden = 5;
        break;
    case PCU_AFODCR_ID_PIN(PCU_ID_B, PCU_PIN_ID_0):
        u8Foden = 1;
        break;
    default:
        eErr = HAL_ERR_INVALID_ID;
        break;
    }

    if(eErr == HAL_ERR_OK)
    {
        SET_PCU_ACCESS_EN();
        SET_PCU_AFODCR_EN(ptAfodcr, bEnable, u8Foden);
        SET_PCU_ACCESS_DIS();
    }

    return eErr;
#else
    (void)eId;
    (void)ePinId;
    (void)bEnable;
    return HAL_ERR_NOT_SUPPORTED;
#endif
}

HAL_ERR_e HAL_PCU_SetIRQ(PCU_IRQ_CFG_t *ptIRQCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    PCU_CTRL_BLK_t *ptPcb;
    IRQn_Type eIrq;

#if defined(PCU_FEATURE_EXT_INTERRUPT_CONFIGURATION)
    ptPcb = &s_tPcb[(uint8_t)ptIRQCfg->un8IntNum];
    eIrq = PCU_GetIRQNum((P_PCU_EINT_ID_e)ptIRQCfg->un8IntNum);
#else
    ptPcb = &s_tPcb[(uint32_t)ptIRQCfg->eId];
    eIrq = PCU_GetIRQNum((P_PCU_ID_e)PCU_GROUP_INTR_IDX((uint32_t)ptIRQCfg->eId));
#endif

    switch(ptIRQCfg->eOps)
    {
        case PCU_OPS_INTR:
#if defined(PCU_FEATURE_IRQ_UNMASK_ENABLE)
            PCU_SetIntrUnMask(eIrq, true);
#endif
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            if(ptPcb->bNmiEnable == true)
            {
                (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
                ptPcb->bNmiEnable = false;
            }
#endif
            ptPcb->pfnHandler = ptIRQCfg->pfnHandler;
            ptPcb->pContext = ptIRQCfg->pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, ptIRQCfg->un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            break;
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
        case PCU_OPS_NMI:
            eErr = HPL_NMI_SetSource(eIrq, &PRV_PCU_NMIHandler, ptIRQCfg->pContext, true);
            if(eErr == HAL_ERR_OK)
            {
                ptPcb->pfnHandler = ptIRQCfg->pfnHandler;
                ptPcb->pContext = ptIRQCfg->pContext;
            }
            ptPcb->bNmiEnable = true;
            break;
#endif
        case PCU_OPS_POLL:
        default:
#if defined(PCU_FEATURE_IRQ_UNMASK_ENABLE)
            PCU_SetIntrUnMask(eIrq, false);
#endif
#if defined(_NMI) && defined(CONFIG_NMI_ANY_INTERRUPT)
            (void)HPL_NMI_SetSource(eIrq, NULL, NULL, false);
            ptPcb->bNmiEnable = false;
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptPcb->pContext = NULL;
            ptPcb->pfnHandler = NULL;
            break;
    }

    ptPcb->eOps = ptIRQCfg->eOps;

    return eErr;
}

#if defined(PCU_FEATURE_EXT_INTERRUPT_CONFIGURATION)
static void PRV_PCU_IRQHandler(P_PCU_EINT_ID_e eEIntId)
{
    PCU_CTRL_BLK_t *ptPcb;
    uint32_t un32Status = 0;
    uint32_t un32Addr = 0;

    ptPcb = &s_tPcb[(uint32_t)eEIntId];

    for(int i = 0; i < CONFIG_PCU_MAX_COUNT; i++)
    {
        un32Addr = (PCU_INTC_FLAG_REG_BASE + (i * PCU_INTC_REG_OFFSET));
        un32Status = GET_PCU_ISR_REG(un32Addr);
        if(un32Status != 0)
        {
            ((PCU_Context_t *)ptPcb->pContext)->eId = (PCU_ID_e)i;
            SET_PCU_ISR_REG(un32Addr, un32Status);
            break;
        }
    }

    if (ptPcb->pfnHandler)
    {
        ptPcb->pfnHandler(un32Status, ptPcb->pContext);
    }
}

void PCU0_IRQHandler(void)
{
    PRV_PCU_IRQHandler(P_PCU_EINT_ID_0);
}

void PCU1_IRQHandler(void)
{
    PRV_PCU_IRQHandler(P_PCU_EINT_ID_1);
}

void PCU2_IRQHandler(void)
{
    PRV_PCU_IRQHandler(P_PCU_EINT_ID_2);
}

void PCU3_IRQHandler(void)
{
    PRV_PCU_IRQHandler(P_PCU_EINT_ID_3);
}
#else
static void PRV_PCU_IRQHandler(PCU_ID_e eId, PORT_Type *ptPcu, uint32_t un32Status)
{
    PCU_CTRL_BLK_t *ptPcb;

    ptPcb = &s_tPcb[(uint32_t)eId];

    SET_PCU_ACCESS_EN();
    SET_PCU_ISR_REG(ptPcu, un32Status);
    SET_PCU_ACCESS_DIS();

    if (ptPcb->pfnHandler)
    {
        ptPcb->pfnHandler(un32Status, ptPcb->pContext);
    }
}

void PCU0_IRQHandler(void)
{
    PCU0_INT_IRQHandler();
}

void PCU1_IRQHandler(void)
{
    PCU1_INT_IRQHandler();
}

void PCU2_IRQHandler(void)
{
    PCU2_INT_IRQHandler();
}

void PCU3_IRQHandler(void)
{
    PCU3_INT_IRQHandler();
}

void PCU4_IRQHandler(void)
{
    PCU4_INT_IRQHandler();
}

void PCU5_IRQHandler(void)
{
    PCU5_INT_IRQHandler();
}

void PCU6_IRQHandler(void)
{
    PCU6_INT_IRQHandler();
}
#endif
