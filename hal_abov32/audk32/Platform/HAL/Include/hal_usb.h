/**
 *******************************************************************************
 * @file        hal_usb.h
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

/**
 * @addtogroup  HAL HAL (Hardware Abstraction Layer)
 * @{
 * @defgroup    HAL_USB USB
 * @{
 * @brief       Universal Serial Bus (USB)
 */

#ifndef _HAL_USB_H_
#define _HAL_USB_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief USB Instance Id
 */
typedef enum
{
    USB_ID_0,
    USB_ID_1,
    USB_ID_2,
    USB_ID_3,
    USB_ID_4,
    USB_ID_5,
    USB_ID_6,
    USB_ID_7,
    USB_ID_8,
    USB_ID_9,
    USB_ID_MAX
} USB_ID_e;

/**
 * @brief USB Clock Source
 */
typedef enum
{
    USB_CLK_MCCR,     /**< Misc Clock source ::USB_CLK_MCCR_e */
    USB_CLK_MAX
} USB_CLK_e;

/**
 * @brief USB MCCR (Misc Clock) Source
 */
typedef enum
{
    USB_CLK_MCCR_LSI,    /**< Low Speed Internal Clock source */
    USB_CLK_MCCR_LSE,    /**< Low Speed External Clock source */
    USB_CLK_MCCR_MCLK,   /**< Master Clock source */
    USB_CLK_MCCR_HSI,    /**< High Speed Internal Clock source */
    USB_CLK_MCCR_HSE,    /**< High Speed External Clock source */
    USB_CLK_MCCR_PLL,    /**< Phase-Locked Loop (PLL) Clock source */
    USB_CLK_MCCR_MAX
} USB_CLK_MCCR_e;

/**
 * @brief USB Common Event
 */
typedef enum
{
    USB_EVENT_COMMON    = BIT(0),
    USB_EVENT_EP0       = BIT(1),
    USB_EVENT_EPINX     = BIT(2),
    USB_EVENT_EPOUTX    = BIT(3),
    USB_EVENT_MAX,      
} USB_EVENT_e;

/**
 * @brief USB Common Event
 */
typedef enum
{
    USB_CM_EVENT_SUSPEND      = BIT(0),
    USB_CM_EVENT_RESUME       = BIT(1),
    USB_CM_EVENT_RESET        = BIT(2),
    USB_CM_EVENT_SOF          = BIT(3),
    USB_CM_EVENT_MAX
} USB_CM_EVENT_e;

/**
 * @brief USB EP0 Event
 */
typedef enum
{
    USB_EP0_EVENT_OUTPKTRDY    = BIT(0),
    USB_EP0_EVENT_INPKTRDY     = BIT(1),
    USB_EP0_EVENT_SENTSTALL    = BIT(2),
    USB_EP0_EVENT_DATAEND      = BIT(3),
    USB_EP0_EVENT_SETUPEND     = BIT(4),
    USB_EP0_EVENT_SENDSTALL    = BIT(5),
    USB_EP0_EVENT_SRVOUTPKTRDY = BIT(6),
    USB_EP0_EVENT_SRVSETUPEND  = BIT(7),
    USB_EP0_EVENT_MAX
} USB_EP0_EVENT_e;

/**
 * @brief USB EP0 Control
 */
typedef enum
{
    USB_EP0_CTRL_OUTPKTRDY    = BIT(0),
    USB_EP0_CTRL_INPKTRDY     = BIT(1),
    USB_EP0_CTRL_SENTSTALL    = BIT(2),
    USB_EP0_CTRL_DATAEND      = BIT(3),
    USB_EP0_CTRL_SETUPEND     = BIT(4),
    USB_EP0_CTRL_SENDSTALL    = BIT(5),
    USB_EP0_CTRL_SRVOUTPKTRDY = BIT(6),
    USB_EP0_CTRL_SRVSETUPEND  = BIT(7),
    USB_EP0_CTRL_MAX
} USB_EP0_CTRL_e;

/**
 * @brief USB EPx Control (EP1 ~ EPn)
 */
typedef enum
{
    USB_EPX_IN_CTRL_INPKTRDY        = BIT(0),
    USB_EPX_IN_CTRL_FIFONOTEMPTY    = BIT(1),
    USB_EPX_IN_CTRL_UNDERRUN        = BIT(2),
    USB_EPX_IN_CTRL_FLUSHFIFO       = BIT(3),
    USB_EPX_IN_CTRL_SENDSTALL       = BIT(4),
    USB_EPX_IN_CTRL_SENTSTALL       = BIT(5),
    USB_EPX_IN_CTRL_CLRDATATOG      = BIT(6),
    USB_EPX_IN_CTRL_MAX
} USB_EPX_IN_CTRL_e;


/**
 * @brief USB EPx Control (EP1 ~ EPn)
 */
typedef enum
{
    USB_EPX_OUT_CTRL_OUTPKTRDY       = BIT(0),
    USB_EPX_OUT_CTRL_FIFOFULL        = BIT(1),
    USB_EPX_OUT_CTRL_OVERRUN         = BIT(2),
    USB_EPX_OUT_CTRL_DATAERR         = BIT(3),
    USB_EPX_OUT_CTRL_FLUSHFIFO       = BIT(4),
    USB_EPX_OUT_CTRL_SENDSTALL       = BIT(5),
    USB_EPX_OUT_CTRL_SENTSTALL       = BIT(6),
    USB_EPX_OUT_CTRL_CLRDATATOG      = BIT(7),
    USB_EPX_OUT_CTRL_MAX
} USB_EPX_OUT_CTRL_e;


/**
 * @brief USB EPx Attribute
 */
typedef enum
{
    USB_EPX_ATTR_CONTROL      = 0,
    USB_EPX_ATTR_ISO          = 1,
    USB_EPX_ATTR_BULK         = 2,
    USB_EPX_ATTR_INTERRUPT    = 3,
    USB_EPX_ATTR_MAX
} USB_EPX_ATTR_e;

/**
 * @brief USB Operation
 */
typedef enum
{
    USB_OPS_POLL,        /**< Operation Polling */
    USB_OPS_INTR,        /**< Operation Interrupt */
    USB_OPS_MAX
} USB_OPS_e;

/**
 * @brief USB Clock Configuration
 */
typedef struct
{
    USB_CLK_e           eClk;
    USB_CLK_MCCR_e      eMccr;         /**< When selecting MCCR at eClk */
    uint8_t             un8MccrDiv;    /**< When selecting MCCR at eClk */
} USB_CLK_CFG_t;

/**
 * @brief USB Mode Configuration (Reserved)
 */
typedef struct
{
    uint32_t            un32InitCnt;      /**< Initial counter value */
} USB_CFG_t;

/**
 * @brief USB EPx Configuration
 */
typedef struct
{
    uint8_t             un8Num;           /**< EndPoint Number */
    bool                bDir;             /**< Input : true or Output : false */
    uint16_t            un16PktSize;      /**< Max Packet Size */
    uint8_t             un8Attr;          /**< Attributes */ 
} USB_EPX_CFG_t;

/**
 * @brief USB IRQ handler context
 */
typedef struct
{
    USB_ID_e        eId;        /**< USB Instance Id */
} USB_Context_t;

/**
 *******************************************************************************
 * @brief       USB Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::USB_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnUSB_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize USB.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USB_Init(USB_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize USB.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USB_Uninit(USB_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration USB.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClkCfg : USB Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USB_SetClkConfig(USB_ID_e eId, USB_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration USB.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : USB Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USB_SetConfig(USB_ID_e eId, USB_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ USB.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @param[in]   bNonMask : Enable non-maskable Interrupt.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USB_SetIRQ(USB_ID_e eId, USB_OPS_e eOps, pfnUSB_IRQ_Handler_t pfnHandler,
                            void *pContext, uint32_t un32IRQPrio, bool bNonMask);

/**
 *******************************************************************************
 * @brief       Set Config EP1 ~ EPn
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : EPx Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USB_SetEPxConfig(USB_ID_e eId, USB_EPX_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set In Stage Control EPx (EP0 ~ EPn)
 * @param[in]   eId : Instance Id.
 * @param[in]   un32Ctrl : Stage Control Bit.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USB_SetEPxInControl(USB_ID_e eId, uint8_t un8EpNum, uint32_t un32Ctrl);

/**
 *******************************************************************************
 * @brief       Set Out Stage Control EPx (EP1 ~ EPn)
 * @param[in]   eId : Instance Id.
 * @param[in]   un8EpNum : Endpoint Number.
 * @param[in]   un32Ctrl : Stage Control Bit.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USB_SetEPxOutControl(USB_ID_e eId, uint8_t un8EpNum, uint32_t un32Ctrl);

/**
 *******************************************************************************
 * @brief       Get Fifo Data (EP0 ~ EPn)
 * @param[in]   eId : Instance Id.
 * @param[in]   un8EpNum : Endpoint Number.
 * @param[out]  *pun8Buf : Fifo Data.
 * @param[in]   un8Length : Length.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USB_GetEPxFifo(USB_ID_e eId, uint8_t un8EpNum, uint8_t *pun8Buf, uint8_t un8Length);

/**
 *******************************************************************************
 * @brief       Get Fifo Count (EP0 ~ EPn)
 * @param[in]   eId : Instance Id.
 * @param[in]   un8EpNum : Endpoint Number.
 * @param[in]   un16Count : Length.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USB_GetEPxFifoCount(USB_ID_e eId, uint8_t un8EpNum, uint16_t *pun16Count);

/**
 *******************************************************************************
 * @brief       Set Fifo Data (EP0 ~ EPn)
 * @param[in]   eId : Instance Id.
 * @param[in]   un8EpNum : Endpoint Number.
 * @param[in]  *pun8Buf : Fifo Data.
 * @param[in]   un8Length : Data Length.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USB_SetEPxFifo(USB_ID_e eId, uint8_t un8EpNum, const uint8_t *pun8Buf, uint8_t un8Length);

/**
 *******************************************************************************
 * @brief       Set Device Address
 * @param[in]   eId : Instance Id.
 * @param[in]   un8Addr : Device Address.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USB_SetAddress(USB_ID_e eId, uint8_t un8Addr);

/**
 *******************************************************************************
 * @brief       Set Connect/Disconnect
 * @param[in]   eId : Instance Id.
 * @param[in]   bConn : true : connect / false : disconnect.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USB_SetConnect(USB_ID_e eId, bool bConn);

/**
 *******************************************************************************
 * @brief       Set EPx direction
 * @param[in]   eId : Instance Id.
 * @param[in]   un8EpNum : Endpoint Number.
 * @param[in]   bDir : true : IN / false : OUT
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_USB_SetEPxDir(USB_ID_e eId, uint8_t un8EpNum, bool bDir);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_USB_H_ */

/** @} */
/** @} */
