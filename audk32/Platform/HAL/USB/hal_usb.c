/**
 *******************************************************************************
 * @file        hal_usb.c
 * @author      ABOV R&D Division
 * @brief       Universal Serial Bus (USB)
 *
 * Copyright 2026 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#include "abov_config.h"

#if defined(_USB)
#include "hal_usb.h"
#include "hal_usb_prv.h"
#if defined(_NMI) && defined(USB_FEATURE_NMI)
#include "hpl_nmi.h"
#endif

#include "debug_log.h"

/* Reserved */
#ifdef _NMI
#undef _NMI
#endif

#define USB_EP0_MAX_PKT_SIZE    64

typedef struct
{
    USB_OPS_e               eOps;
    pfnUSB_IRQ_Handler_t    pfnHandler;
    void                    *pContext;

    uint8_t                 un8Mode;
    uint8_t                 un8IntrEnable;
    uint32_t                un32InitCnt;
} USB_CTRL_BLK_t;

static USB_CTRL_BLK_t s_tUcb[USB_CH_NUM];

static void PRV_USB_IRQHandler(USB_ID_e eId);

#if defined(_NMI) && defined(USB_FEATURE_NMI)
static void PRV_USB_NMIHandler(uint32_t un32Event, void *pContext)
{
    /* Need to get Id */
    PRV_USB_IRQHandler(USB_ID_0);
}
#endif

static USB_Type *PRV_USB_GetReg(USB_ID_e eId)
{
    return USB_GetReg((P_USB_ID_e)eId);
}

static HAL_ERR_e PRV_USB_SetScuEnable(P_USB_ID_e eId, bool bEnable)
{
    return USB_SetScuEnable(eId, bEnable);
}

HAL_ERR_e HAL_USB_Init(USB_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= USB_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    eErr = PRV_USB_SetScuEnable((P_USB_ID_e)eId, true);
    if(eErr != HAL_ERR_OK)
    {
        return eErr;
    }
		
    memset(&s_tUcb[(uint32_t)eId], 0x00, sizeof(USB_CTRL_BLK_t));

    return eErr;
}

HAL_ERR_e HAL_USB_Uninit(USB_ID_e eId)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    IRQn_Type eIrq;

    /* Forcily, disable NVIC Interrupt */
    eIrq = USB_GetIRQNum((P_USB_ID_e)eId);
    NVIC_ClearPendingIRQ(eIrq);
    NVIC_DisableIRQ(eIrq);

    /* clear local context by id */
    memset(&s_tUcb[(uint32_t)eId], 0x00, sizeof(USB_CTRL_BLK_t));

    return eErr;
}

HAL_ERR_e HAL_USB_SetClkConfig(USB_ID_e eId, USB_CLK_CFG_t *ptClkCfg)
{
    HAL_ERR_e eErr = HAL_ERR_OK;

    if((uint32_t)eId >= USB_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    /* USB Clock must be PLL 48MHz */
    eErr = USB_SetClk((P_USB_ID_e)eId, (P_USB_CLK_e)ptClkCfg->eClk, (P_USB_CLK_MCCR_e)ptClkCfg->eMccr, ptClkCfg->un8MccrDiv);

    return eErr;
}

HAL_ERR_e HAL_USB_SetConnect(USB_ID_e eId, bool bConn)
{
    USB_Type *ptUsb;

    if((uint32_t)eId >= USB_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUsb = PRV_USB_GetReg(eId);

    if (bConn)
    {
        /* Full Speed Pull-up/down */
        SET_USB_EP0_PULLUP(ptUsb, USB_FULL_PULLUP);
        SET_USB_SUSPEND_EN(ptUsb, false);
        /* Power clear */
        SET_USB_POWER(ptUsb, 0x01);
    }
    else
    {
        SET_USB_EP0_PULLUP(ptUsb, USB_FULL_PULLDOWN);
        SET_USB_SUSPEND_EN(ptUsb, true);
        SET_USB_POWER(ptUsb, 0x00);
    }

    return HAL_ERR_OK;

}

HAL_ERR_e HAL_USB_SetConfig(USB_ID_e eId, USB_CFG_t *ptCfg)
{
    USB_Type *ptUsb;

    if((uint32_t)eId >= USB_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUsb = PRV_USB_GetReg(eId);

    ptUsb->INTRUSBE |= 0x04;
    ptUsb->INTRUSBE |= 0x01;
    ptUsb->INTRUSBE |= 0x02;
    ptUsb->INTRUSBE |= 0x08;

    SET_USB_SUSPEND_EN(ptUsb, false);

    ptUsb->PUPDCR = 0;

    SET_USB_EP0_PULLUP(ptUsb, USB_FULL_PULLUP);

    SET_USB_POWER(ptUsb, 0x01);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_USB_SetIRQ(USB_ID_e eId, USB_OPS_e eOps, pfnUSB_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio, bool bNonMask)
{
    HAL_ERR_e eErr = HAL_ERR_OK;
    USB_CTRL_BLK_t *ptUcb;
    IRQn_Type eIrq;

    if((uint32_t)eId >= USB_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUcb = &s_tUcb[(uint32_t)eId];
    eIrq = USB_GetIRQNum((P_USB_ID_e)eId);

    switch(eOps)
    {

        case USB_OPS_INTR:
#if defined(USB_FEATURE_IRQ_UNMASK_ENABLE)
            USB_SetIntrUnMask(eIrq, true);
#endif
            ptUcb->pfnHandler = pfnHandler;
            ptUcb->pContext = pContext;
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_SetPriority(eIrq, un32IRQPrio);
            NVIC_EnableIRQ(eIrq);
            break;

        case USB_OPS_POLL:
        default:
#if defined(USB_FEATURE_IRQ_UNMASK_ENABLE)
            USB_SetIntrUnMask(eIrq, false);
#endif
#if defined(_NMI) && defined(USB_FEATURE_NMI)
            eErr = HPL_NMI_SetIRQ(NMI_INTR_USB, NULL, NULL, false);
#endif
            NVIC_ClearPendingIRQ(eIrq);
            NVIC_DisableIRQ(eIrq);
            ptUcb->pContext = NULL;
            ptUcb->pfnHandler = NULL;
            break;
    }
    ptUcb->eOps = eOps;

    return eErr;
}

HAL_ERR_e HAL_USB_SetEPxInControl(USB_ID_e eId, uint8_t un8EpNum, uint32_t un32Ctrl)
{
    USB_Type *ptUsb;

    if((uint32_t)eId >= USB_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUsb = PRV_USB_GetReg(eId);

    SET_USB_INDEX(ptUsb, un8EpNum);

    SET_USB_EP0_SR0(ptUsb, un32Ctrl);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_USB_SetEPxOutControl(USB_ID_e eId, uint8_t un8EpNum, uint32_t un32Ctrl)
{
    USB_Type *ptUsb;

    if((uint32_t)eId >= USB_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUsb = PRV_USB_GetReg(eId);

    SET_USB_INDEX(ptUsb, un8EpNum);

    SET_USB_EPX_OUTSR1(ptUsb,un32Ctrl);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_USB_SetEPxConfig(USB_ID_e eId, USB_EPX_CFG_t *ptCfg)
{
    USB_Type *ptUsb;
    bool bIso = false;

    if((uint32_t)eId >= USB_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUsb = PRV_USB_GetReg(eId);

    SET_USB_INDEX(ptUsb, ptCfg->un8Num);

    if (ptCfg->bDir)
    {
        SET_USB_INMAXP(ptUsb, ptCfg->un16PktSize);

        switch(ptCfg->un8Attr)
        {
            case USB_EPX_ATTR_ISO:
                bIso = true;
                break;
            case USB_EPX_ATTR_BULK:
            case USB_EPX_ATTR_INTERRUPT:
                break;
            default:
                break;
        }
        SET_USB_EPX_CR_IN_ISO(ptUsb, bIso);
    }
    else
    {
        SET_USB_OUTMAXP(ptUsb, ptCfg->un16PktSize);

        switch(ptCfg->un8Attr)
        {
            case USB_EPX_ATTR_ISO:
                bIso = true;
                break;
            case USB_EPX_ATTR_BULK:
            case USB_EPX_ATTR_INTERRUPT:
                break;
            default:
                break;
        }
        SET_USB_EPX_CR_OUT_ISO(ptUsb, bIso);
    }

    SET_USB_EPX_CR_DIR(ptUsb, ptCfg->bDir);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_USB_GetEPxFifo(USB_ID_e eId, uint8_t un8EpNum, uint8_t *pun8Buf, uint8_t un8Length)
{
    USB_Type *ptUsb;
#if defined(USB_FEATURE_FIFO_4BYTE_ALIGN)
    uint32_t *pun32Buffer = (uint32_t *)pun8Buf;
    uint8_t *pun8Buffer;
    uint32_t un32Quot = un8Length >> 2;
    uint32_t un32Remind = un8Length & 0x3;
    uint32_t un32Fifo;
#endif
    uint32_t *pun32AddrReg;

    if((uint32_t)eId >= USB_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUsb = PRV_USB_GetReg(eId);

    /* Set EPx */
    SET_USB_INDEX(ptUsb, un8EpNum);

    /* Get FIFOx Reg Address */
    pun32AddrReg = (uint32_t *)((uint32_t)GET_USB_EPX_FIFO_BASE_ADDR(ptUsb) + un8EpNum*USB_FIFO_ADDR_OFFSET);

#if defined(USB_FEATURE_FIFO_4BYTE_ALIGN)
    for (int i = 0; i < un32Quot; i++) 
    {
        pun32Buffer[i] = *pun32AddrReg;
    }

    if (un32Remind)
    {
        un32Fifo = *pun32AddrReg;
        pun8Buffer = (uint8_t *)&pun32Buffer;
        for (int i = 0; i < un32Remind; i++)
        {
            pun8Buffer[i] = (uint8_t)(un32Fifo >> (i << 3));
        } 
    }
#else
    for (uint8_t i = 0; i < un8Length; i++)
    {
        pun8Buf[i] = *pun32AddrReg;
    }
#endif

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_USB_SetEPxFifo(USB_ID_e eId, uint8_t un8EpNum, const uint8_t *pun8Buf, uint8_t un8Length)
{

    USB_Type *ptUsb;
#if defined(USB_FEATURE_FIFO_4BYTE_ALIGN)
    uint32_t un32Quot = un8Length >> 2;
    uint32_t un32Remind = un8Length & 0x03;
    const uint32_t *pun32Buffer = (const uint32_t *)pun8Buf;
    const uint8_t *pun8Buffer;
#endif
    uint32_t  *pun32AddrReg;

    if((uint32_t)eId >= USB_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUsb = PRV_USB_GetReg(eId);

    /* Set EPx */
    SET_USB_INDEX(ptUsb, un8EpNum);
     
    /* Get FIFOx Reg Address */
    pun32AddrReg = (uint32_t *)((uint32_t)GET_USB_EPX_FIFO_BASE_ADDR(ptUsb) + un8EpNum*USB_FIFO_ADDR_OFFSET);

#if defined(USB_FEATURE_FIFO_4BYTE_ALIGN)
    for (uint32_t i = 0; i < un32Quot; i++)
    {
        *pun32AddrReg = pun32Buffer[i];
    }

    if (un32Remind)
    {
        pun8Buffer = pun8Buf + (un32Quot << 2);
        for (uint32_t i = 0; i < un32Remind; i++)
        {
            *((volatile uint8_t *)pun32AddrReg) = pun8Buffer[i];
        }
    }
#else
    for (uint8_t i = 0; i < un8Length; i++)
    {
        *((volatile uint8_t *)pun32AddrReg) = pun8Buf[i];
    }
#endif

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_USB_GetEPxFifoCount(USB_ID_e eId, uint8_t un8EpNum, uint16_t *pun16Count)
{
    USB_Type *ptUsb;

    if((uint32_t)eId >= USB_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUsb = PRV_USB_GetReg(eId);

    SET_USB_INDEX(ptUsb, un8EpNum);

    *pun16Count = GET_USB_EP0_RX_CNT(ptUsb);

    if (un8EpNum != 0)
    {
        uint32_t un32HCnt = (GET_USB_EP0_RX_CNT1(ptUsb) << 8);
        *pun16Count |= un32HCnt;
        
    }

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_USB_SetEPxDir(USB_ID_e eId, uint8_t un8EpNum, bool bDir)
{
    USB_Type *ptUsb;

    if((uint32_t)eId >= USB_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUsb = PRV_USB_GetReg(eId);

    SET_USB_INDEX(ptUsb, un8EpNum);

    SET_USB_EPX_CR_DIR(ptUsb, bDir);

    return HAL_ERR_OK;
}

HAL_ERR_e HAL_USB_SetAddress(USB_ID_e eId, uint8_t un8Addr)
{
    USB_Type *ptUsb;

    if((uint32_t)eId >= USB_CH_NUM)
    {
        return HAL_ERR_INVALID_ID;
    }

    ptUsb = PRV_USB_GetReg(eId);

    SET_USB_FADDR(ptUsb, un8Addr);

    return HAL_ERR_OK;
}

static void PRV_USB_IRQHandler(USB_ID_e eId)
{

    USB_Type *ptUsb;
    USB_CTRL_BLK_t *ptUcb;
    volatile uint32_t un32InEpEvent = 0, un32OutEpEvent = 0;
    volatile uint32_t un32CommonEvent = 0, un32Ep0Event = 0;

    ptUsb = PRV_USB_GetReg(eId);
    ptUcb = &s_tUcb[(uint32_t)eId];

#if defined (USB_FEATURE_ONLY_SEND_COMMON_EVENT)
    ptUcb->pfnHandler(un32CommonEvent, (void *)(uintptr_t)USB_EVENT_COMMON);
    return;
#else
    if (!ptUcb || !ptUcb->pfnHandler) 
    {
        return;
    }

    un32CommonEvent = GET_USB_SR(ptUsb);
    un32OutEpEvent = GET_USB_IER_OUTEP_SR(ptUsb);
    un32InEpEvent = GET_USB_IER_INEP_SR(ptUsb);
    
    /* EP0 Interrupt */
    if (un32InEpEvent & USB_EP0_INTR_MASK) 
    {
        SET_USB_INDEX(ptUsb, 0);
        un32Ep0Event = GET_USB_EP0_SR0(ptUsb);
        ptUcb->pfnHandler(un32Ep0Event, (void *)(uintptr_t)USB_EVENT_EP0);
    }

    /* EPx In Interrupt */
    un32InEpEvent = un32InEpEvent & USB_EP1_5_INTR_MASK;
    if (un32InEpEvent != 0) 
    {
        ptUcb->pfnHandler(un32InEpEvent, (void *)(uintptr_t)USB_EVENT_EPINX);
    }

    /* EPx Out Interrupt */
    if (un32OutEpEvent != 0) 
    {
        ptUcb->pfnHandler(un32OutEpEvent, (void *)(uintptr_t)USB_EVENT_EPOUTX);
        SET_USB_EPX_OUTSR1(ptUsb, 0);
    }

    /* Common Usb Interrupt */
    if (un32CommonEvent != 0) 
    {
        ptUcb->pfnHandler(un32CommonEvent, (void *)(uintptr_t)USB_EVENT_COMMON);
    }
#endif
}

void USB0_IRQHandler(void)
{
    PRV_USB_IRQHandler(USB_ID_0);
}

void USB1_IRQHandler(void)
{
    PRV_USB_IRQHandler(USB_ID_1);
}

#endif /* _USB */
