/**
 *******************************************************************************
 * @file        hal_i2c_f1x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed I2C
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_I2C_F1X_H_
#define _HAL_I2C_F1X_H_

#include "abov_config.h"

/* Configuration Define from config_xxx.h */
#define I2C_CH_NUM                                    CONFIG_I2C_MAX_COUNT

/* I2C Status */
#define I2C_STATUS_RXACK                              (1UL << 0)
#define I2C_STATUS_TX                                 (1UL << 1)
#define I2C_STATUS_BUSY                               (1UL << 2)
#define I2C_STATUS_MASTERSHIP_LOSS                    (1UL << 3)
#define I2C_STATUS_SLAVE                              (1UL << 4)
#define I2C_STATUS_STOP                               (1UL << 5)
#define I2C_STATUS_XFER_DONE                          (1UL << 6)
#define I2C_STATUS_RX_ADDR                            (1UL << 7)
#define I2C_STATUS_SLT_TO                             (1UL << 31)

/* Transmit/Receive Status */
#define I2C_TX_DATA_ACK                               (I2C_STATUS_RXACK | I2C_STATUS_TX | I2C_STATUS_BUSY | I2C_STATUS_XFER_DONE)
#define I2C_RX_DATA_ACK                               (I2C_STATUS_RXACK | I2C_STATUS_BUSY | I2C_STATUS_XFER_DONE)

/* Master Transmit/Receive Status */
#define I2C_MASTER_TX_ADDR_ACK                        (I2C_STATUS_RXACK | I2C_STATUS_TX | I2C_STATUS_BUSY | I2C_STATUS_RX_ADDR)
#define I2C_MASTER_TX_ADDR_NOACK                      (I2C_STATUS_TX | I2C_STATUS_BUSY | I2C_STATUS_RX_ADDR)
#define I2C_MASTER_TX_DATA_ACK                        I2C_TX_DATA_ACK
#define I2C_MASTER_RX_ADDR_ACK                        (I2C_STATUS_RXACK | I2C_STATUS_BUSY | I2C_STATUS_RX_ADDR)
#define I2C_MASTER_RX_DATA_ACK                        I2C_RX_DATA_ACK
#define I2C_MASTER_RX_DATA_NOACK                      (I2C_STATUS_BUSY | I2C_STATUS_XFER_DONE)

/* Slave Transmit/Receive Status */
#define I2C_SLAVE_TX_SEL_ACK                          (I2C_STATUS_RXACK | I2C_STATUS_TX | I2C_STATUS_BUSY | I2C_STATUS_SLAVE)
#define I2C_SLAVE_TX_DATA_ACK                         I2C_TX_DATA_ACK
#define I2C_SLAVE_TX_DATA_NOACK                       (I2C_STATUS_TX | I2C_STATUS_BUSY | I2C_STATUS_XFER_DONE)
#define I2C_SLAVE_TX_GC_ACK                           (I2C_STATUS_RXACK | I2C_STATUS_TX | I2C_STATUS_BUSY | I2C_STATUS_SLAVE | I2C_STATUS_RX_ADDR)
#define I2C_SLAVE_RX_SEL_ACK                          (I2C_STATUS_RXACK | I2C_STATUS_BUSY | I2C_STATUS_SLAVE)
#define I2C_SLAVE_RX_DATA_ACK                         I2C_RX_DATA_ACK
#define I2C_SLAVE_RX_GC_ACK                           (I2C_STATUS_RXACK | I2C_STATUS_BUSY | I2C_STATUS_SLAVE | I2C_STATUS_RX_ADDR)
#define I2C_SLAVE_TX_DONE                             (I2C_STATUS_TX | I2C_STATUS_STOP)
#define I2C_SLAVE_RX_DONE                             (I2C_STATUS_STOP)

#if (CONFIG_I2C_VER_EXT == 0)

#if (CONFIG_I2C_VER_MINOR == 0)
#include "hal_i2c_f_01_00_00.h"
#elif (CONFIG_I2C_VER_MINOR == 1)
#include "hal_i2c_f_01_00_01.h"
#elif (CONFIG_I2C_VER_MINOR == 2)
#include "hal_i2c_f_01_00_02.h"
#else
#error "define CONFIG_I2C_VER_MINOR of F-type I2C at config_xxx.h"
#endif

#elif (CONFIG_I2C_VER_EXT == 1)

#if (CONFIG_I2C_VER_MINOR == 0)
#include "hal_i2c_f_01_01_00.h"
#else
#error "define CONFIG_I2C_VER_MINOR of F-type I2C at config_xxx.h"
#endif

#elif (CONFIG_I2C_VER_EXT == 2)

#if (CONFIG_I2C_VER_MINOR == 0)
#include "hal_i2c_f_01_02_00.h"
#else
#error "define CONFIG_I2C_VER_MINOR of F-type I2C at config_xxx.h"
#endif

#else
#error "define CONFIG_I2C_VER_EXT of F-type I2C at config_xxx.h"
#endif

static __inline HAL_ERR_e I2C_SetScuEnable(P_I2C_ID_e eId, uint32_t un32Enable)
{
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    if((uint32_t)eId >= CONFIG_I2C_MAX_COUNT)
    {
        return HAL_ERR_INVALID_ID;
    }

    SET_SCU_I2C_PER(ptScu, (uint32_t)eId, un32Enable);
    SET_SCU_I2C_PCER(ptScu, (uint32_t)eId, un32Enable);

    return HAL_ERR_OK;
}

static __inline I2C_Type *I2C_GetReg(P_I2C_ID_e eId)
{
    return (I2C_Type *)(I2C_REG_BASE + (I2C_REG_OFFSET * (uint32_t)eId));
}

static __inline IRQn_Type I2C_GetIRQNum(P_I2C_ID_e eId)
{
    IRQn_Type eIrq = (IRQn_Type)0xEF;

    switch(eId)
    {
#if defined(I2C_0_IRQ)
        case P_I2C_ID_0:
            eIrq = I2C_0_IRQ;
            break;
#endif
#if defined(I2C_1_IRQ)
        case P_I2C_ID_1:
            eIrq = I2C_1_IRQ;
            break;
#endif
#if defined(I2C_2_IRQ)
        case P_I2C_ID_2:
            eIrq = I2C_2_IRQ;
            break;
#endif
#if defined(I2C_3_IRQ)
        case P_I2C_ID_3:
            eIrq = I2C_3_IRQ;
            break;
#endif
#if defined(I2C_4_IRQ)
        case P_I2C_ID_4:
            eIrq = I2C_4_IRQ;
            break;
#endif
#if defined(I2C_5_IRQ)
        case P_I2C_ID_5:
            eIrq = I2C_5_IRQ;
            break;
#endif
#if defined(I2C_6_IRQ)
        case P_I2C_ID_6:
            eIrq = I2C_6_IRQ;
            break;
#endif
#if defined(I2C_7_IRQ)
        case P_I2C_ID_7:
            eIrq = I2C_7_IRQ;
            break;
#endif
#if defined(I2C_8_IRQ)
        case P_I2C_ID_8:
            eIrq = I2C_8_IRQ;
            break;
#endif
#if defined(I2C_9_IRQ)
        case P_I2C_ID_9:
            eIrq = I2C_9_IRQ;
            break;
#endif
        default:
            break;
    }

    return eIrq;
}

static __inline void I2C_SetWkupSrc(P_I2C_ID_e eId, bool bEnable)
{
#if defined(I2C_FEATURE_WAKEUP)
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;
    SET_SCU_I2C_WKUP_EN(ptScu, (uint32_t)eId, bEnable);
#else
    (void)bEnable;
#endif
}

static __inline void I2C_GetWkupEvent(P_I2C_ID_e eId, bool *bEvent)
{
#if defined(I2C_FEATURE_WAKEUP)
    SCU_Type *ptScu = (SCU_Type *)SCU_ADDR;

    uint8_t un8Prev = GET_SCU_I2C_PREVMODE(ptScu);

    if(GET_SCU_I2C_WKUP_EN(ptScu, (uint32_t)eId))
    {
        if(un8Prev == 0x01 || un8Prev == 0x07)
        {
            *bEvent = GET_SCU_I2C_WKUP_FLAG(ptScu, (uint32_t)eId);
        }
    }
    else
    {
        *bEvent = false;
    }
#else
    *bEvent = false;
#endif
}

#if defined(I2C_FEATURE_IRQ_UNMASK_ENABLE)
static __inline void I2C_SetIntrUnMask(IRQn_Type eIrq, bool bEnable)
{
    INTC_Type *ptIntc = (INTC_Type *)INTC_BASE; 
    SET_INTC_IRQ_UNMASK_EN(ptIntc, (uint8_t)eIrq, bEnable);
}
#endif

#endif /* _HAL_I2C_F1X_H_ */
