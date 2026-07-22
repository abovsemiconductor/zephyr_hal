/**
 *******************************************************************************
 * @file        hal_i2c.h
 * @author      ABOV R&D Division
 * @brief       I2C communication
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
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
 * @defgroup    HAL_I2C I2C
 * @{
 * @brief       Inter-Integrated Circuit (I2C)
 */

#ifndef _HAL_I2C_H_
#define _HAL_I2C_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief I2C Instance Id
 */
typedef enum
{
    I2C_ID_0,
    I2C_ID_1,
    I2C_ID_2,
    I2C_ID_3,
    I2C_ID_4,
    I2C_ID_5,
    I2C_ID_6,
    I2C_ID_7,
    I2C_ID_8,
    I2C_ID_9,
    I2C_ID_MAX
} I2C_ID_e;

/**
 * @brief I2C Mode
 */
typedef enum
{
    I2C_MODE_MASTER,    /**< Master */
    I2C_MODE_SLAVE,     /**< Slave */
    I2C_MODE_MAX
} I2C_MODE_e;

/**
 * @brief I2C Event
 */
typedef enum
{
    I2C_EVENT_TX_DONE            = BIT(0),    /**< Transmit complete */
    I2C_EVENT_RX_DONE            = BIT(1),    /**< Receive complete */
    I2C_EVENT_MASTERSHIP_LOSS    = BIT(2),    /**< Mastership lose */
    I2C_EVENT_RX_NO_ACK          = BIT(3),    /**< Receive No Ack */
    I2C_EVENT_SCL_LOW_TIMEOUT    = BIT(4),    /**< SCL low timeout */
    I2C_EVENT_MAX
} I2C_EVENT_e;

/**
 * @brief I2C Operation
 */
typedef enum
{
    I2C_OPS_POLL,        /**< Operation Polling */
    I2C_OPS_INTR,        /**< Operation Interrupt */
    I2C_OPS_INTR_DMA,    /**< Operation Interrupt with DMA */
    I2C_OPS_NMI,         /**< Operation NMI */
    I2C_OPS_NMI_DMA,     /**< Operation NMI with DMA */
    I2C_OPS_MAX
} I2C_OPS_e;

/**
 * @brief I2C SDA Hold Time
 */
typedef struct
{
    bool       bEnable;
    uint16_t    un16Hold;
} I2C_SDHT_CFG_t;

/**
 * @brief I2C SCL Low Timeout
 */
typedef struct
{
    bool        bEnable;
    bool        bIntrEnable;
    uint32_t    un32Timeout;
} I2C_SLTP_CFG_t;

/**
 * @brief I2C SCL/SDA Manual
 */
typedef struct
{
    bool bSclMaulEnable;
    bool bSdaMaulEnable;
} I2C_MAUL_CFG_t;

/**
 * @brief I2C Mode Configuration
 */
typedef struct
{
    I2C_MODE_e          eMode;
    uint8_t             un8OwnSlvAddr;    /**< Slave Address 0 */
    bool                bSaGcEnable;      /**< Slave Address 0 General Call Enable */
    uint8_t             un8OwnSlvAddr2;   /**< Slave Address 1 */
    bool                bSa2GcEnable;     /**< Slave Address 1 General Call Enable */

    union
    {
        struct
        {
            uint32_t    un32Freq;         /**< Period by Frequence value */
        } tFreq;

        struct
        {
            uint16_t    un16Low;          /**< Period by SCH/SCL value */
            uint16_t    un16High;
        } tDuty;
    } uPeriod;

    I2C_SDHT_CFG_t      tSdht;
} I2C_CFG_t;

/**
 * @brief I2C IRQ handler context
 */
typedef struct
{
    I2C_ID_e eId;        /**< I2C Instance Id */
    bool     bWakeup;    /**< Wake-up flag */
} I2C_Context_t;

/**
 *******************************************************************************
 * @brief       I2C Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::I2C_EVENT_e.
 * @param[in]   *pContext : Context provided during SetIRQ.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnI2C_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 *******************************************************************************
 * @brief       Initialize I2C.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_I2C_Init(I2C_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize I2C.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_I2C_Uninit(I2C_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration I2C.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : I2C Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_I2C_SetConfig(I2C_ID_e eId, I2C_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set IRQ I2C.
 * @param[in]   eId : Instance Id.
 * @param[in]   eOps : Operation.
 * @param[in]   pfnHandler : Callback Function to receive Event.
 * @param[in]   *pContext : Caller's Context.
 * @param[in]   un32IRQPrio : Interrupt Priority.
 * @param[in]   bNonMask : Enable non-maskable Interrupt.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_I2C_SetIRQ(I2C_ID_e eId, I2C_OPS_e eOps, pfnI2C_IRQ_Handler_t pfnHandler,
                         void *pContext, uint32_t un32IRQPrio);

/**
 *******************************************************************************
 * @brief       Transmit Data I2C.
 * @param[in]   eId : Instance Id.
 * @param[in]   un8SlaveAddr : Slave Address.
 * @param[in]   *pun8Out : Transmit Data.
 * @param[in]   un32Len : Data Length.
 * @param[in]   bEnForcePoll : En-force polling Operation (Ignored IO Operation by SetIRQ).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_I2C_Transmit(I2C_ID_e eId, uint8_t un8SlaveAddr, uint8_t *pun8Out,
                           uint32_t un32Len, bool bEnForcePoll);

/**
 *******************************************************************************
 * @brief       Receive Data I2C.
 * @param[in]   eId : Instance Id.
 * @param[in]   un8SlaveAddr : Slave Address.
 * @param[in]   *pun8In : Receive Data.
 * @param[in]   un32Len : Data Length.
 * @param[in]   bEnForcePoll : En-force polling Operation (Ignored IO Operation by SetIRQ).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_I2C_Receive(I2C_ID_e eId, uint8_t un8SlaveAddr, uint8_t *pun8In,
                          uint32_t un32Len, bool bEnForcePoll);

/**
 *******************************************************************************
 * @brief       Set SCL Low Timeout Configuration I2C.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : I2C SCL Low Timeout Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_I2C_SetSltpConfig(I2C_ID_e eId, I2C_SLTP_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set SCL/SDA Manual Configuration I2C.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : I2C SCL/SDA Manual Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_I2C_SetMaulConfig(I2C_ID_e eId, I2C_MAUL_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set SCL Manual Level I2C.
 * @param[in]   eId : Instance Id.
 * @param[in]   bLevel : true = High, false = Low.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_I2C_SetSclMaul(I2C_ID_e eId, bool bLevel);

/**
 *******************************************************************************
 * @brief       Set SDA Manual Level I2C.
 * @param[in]   eId : Instance Id.
 * @param[in]   bLevel : true = High, false = Low.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_I2C_SetSdaMaul(I2C_ID_e eId, bool bLevel);

/**
 *******************************************************************************
 * @brief       Set Wake-up source I2C.
 * @param[in]   eId : Instance Id.
 * @param[in]   bEnable : Enable Wake-up source.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_I2C_SetWakeupSrc(I2C_ID_e eId, bool bEnable);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_I2C_H_ */

/** @} */
/** @} */

