/**
 *******************************************************************************
 * @file        hal_pcu_v_01_00_02.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.02 typed PCU
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_PCU_V_01_00_02_H_
#define _HAL_PCU_V_01_00_02_H_

/* Feature(Function) Configuration Define */
#define PCU_FEATURE_RTC_PORT

/* Internal Macro */
typedef PORT_Type                                     GPIO_Type;
typedef PCU_Type                                      PCU_PORTEN_Type;
#define PCU_REG_BASE                                  PA_BASE
#define PCU_REG_OFFSET                                0x100
#define PCU_PORT_EN_BASE                              PCU_BASE
#define PCU_IRQ_MAX_COUNT                             2

#define PCU_INPUTMODE                                 0x00
#define PCU_INPUTMODE_ANG                             0x03
#define PCU_OUTPUTMODE(x)                             0x01
#define PCU_OUTPUTMODE_TYP(x)                         (x & 0x1)
#define PCU_ALTMODE                                   0x02
#define PCU_ALTMODE_BIT(x)                            (x*2)
#define PCU_ALTMODE_TYPE(x)                           x
#define PCU_ALTTYPE_BIT(x)                            (x*4)
#define PCU_ALT2TYPE_BIT(x)                           ((x-8)*4)
#define PCU_PULLMODE_TYPE(x)                          x
#define PCU_PULLMODE_BIT(x)                           (x*2)
#define PCU_INTR_BIT(x)                               (x*2)
#define PCU_STR_BIT(x)                                (x*2)
#define PCU_GROUP_INTR_IDX(x)                         (x < 3 ? (x / 2) : x == 5 ? (1) : 7)
#define PCU_MCCR_CLK(x)                               (x > 0 ? x+2 : x)
//#define PCU_PORTF_LEVEL_OFFSET                        5

/* Bit/Register Macro */
#define GET_PCU_ISR_REG(Peri)                         GET_REG(Peri,ISR)
#define SET_PCU_ISR_REG(Peri,Data)                    SET_REG(Peri,Data,ISR)
#define SET_PCU_MODE(Peri,Data,Pos)                   SET_REG_BIT(Peri,Data,MOD,MASK_2BITS,Pos)
#define SET_PCU_MODE_TYPE(Peri,Data,Pos)              SET_REG_BIT(Peri,Data,TYP,MASK_1BIT,Pos)
#define SET_PCU_MODE_ALT(Peri,Data,Pos)               SET_REG_BIT(Peri,Data,MOD,MASK_2BITS,Pos)
#define SET_PCU_ALT1(Peri,Data,Pos)                   SET_REG_BIT(Peri,Data,AFSR1,MASK_4BITS,Pos)
#define SET_PCU_ALT2(Peri,Data,Pos)                   SET_REG_BIT(Peri,Data,AFSR2,MASK_4BITS,Pos)
#define SET_PCU_PULL_MODE(Peri,Data,Pos)              SET_REG_BIT(Peri,Data,PUPD,MASK_2BITS,Pos)
#define GET_PCU_INPUT_DATA(Peri,Pos)                  GET_REG_BIT(Peri,INDR,MASK_1BIT,Pos)
#define SET_PCU_OUTPUT_DATA(Peri,Data,Pos)            SET_REG_BIT(Peri,Data,OUTDR,MASK_1BIT,Pos)
#define SET_PCU_OUTPUT_BIT(Peri,Data,Pos)             SET_REG_BIT(Peri,Data,BSR,MASK_1BIT,Pos)
#define SET_PCU_OUTPUT_CLEAR_BIT(Peri,Data,Pos)       SET_REG_BIT(Peri,Data,BCR,MASK_1BIT,Pos)
#define SET_PCU_OUTPUT_SUSTAIN(Peri,Data,Pos)         SET_REG_BIT(Peri,Data,OUTDMSK,MASK_1BIT,Pos)
#define SET_PCU_DEBOUNCE_EN(Peri,Data,Pos)            SET_REG_BIT(Peri,Data,DBCR,MASK_1BIT,Pos)
#define SET_PCU_INPUT_LEVEL(Peri,Data,Pos)            SET_REG_BIT(Peri,Data,PLSR,MASK_1BIT,Pos)
#define SET_PCU_STR_EN(Peri,Data,Pos)                 SET_REG_BIT(Peri,Data,STR,MASK_2BITS,Pos)
#define SET_PCU_ICR_EN(Peri,Data,Pos)                 SET_REG_BIT(Peri,Data,ICR,MASK_2BITS,Pos)
#define SET_PCU_PORTEN(Peri,Data)                     SET_BIT(Peri,Data,PCU,PORTEN,PORTEN)
#define SET_PCU_ACCESS_EN() \
            do { \
                   PCU_PORTEN_Type *pPcuPortEn = (PCU_PORTEN_Type *)PCU_PORT_EN_BASE; \
                   SET_PCU_PORTEN(pPcuPortEn,0x15); \
                   SET_PCU_PORTEN(pPcuPortEn,0x51); \
            } while(0)

#define SET_PCU_ACCESS_DIS() \
            do { \
                   PCU_PORTEN_Type *pPcuPortEn = (PCU_PORTEN_Type *)PCU_PORT_EN_BASE; \
                   SET_PCU_PORTEN(pPcuPortEn,0x00); \
            } while(0)

/* Interrupt Macro */
#define SET_PCU_IER_EN(Peri,Data,Pos)                 SET_REG_BIT(Peri,Data,IER,MASK_2BITS,Pos)
#define SET_PCU_IER_ST(Peri,Data,Pos)                 SET_REG_BIT(Peri,Data,ISR,MASK_2BITS,Pos)
#define GET_PCU_IER_ST(Peri,Pos)                      GET_REG_BIT(Peri,ISR,MASK_2BITS,Pos)

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_PCU_MCCR_SEL0(Peri,Data)              SET_BIT(Peri,Data,SCU,MCCR4,PD0CSEL)
#define SET_SCU_PCU_MCCR_DIV0(Peri,Data)              SET_BIT(Peri,Data,SCU,MCCR4,PD0DIV)

/* RTC Macro */
#define RTC_REG_BASE                                  RTC_BASE 
#define RTC_PC13_MODE(x)                              (x == 2 ? 2 : 0)
#define RTC_PCXX_MODE(x)                              (x == 2 ? 1 : 0) 
#define SET_RTC_CR_PC13MODE(Peri,Data)                SET_BIT(Peri,Data,RTC,RTCPFCR,PC13MODE)
#define SET_RTC_CR_PC13VAL(Peri,Data)                 SET_BIT(Peri,Data,RTC,RTCPFCR,PC13VALUE)
#define SET_RTC_CR_PC14MODE(Peri,Data)                SET_BIT(Peri,Data,RTC,RTCPFCR,PC14MODE)
#define SET_RTC_CR_PC14VAL(Peri,Data)                 SET_BIT(Peri,Data,RTC,RTCPFCR,PC14VALUE)
#define SET_RTC_CR_PC15MODE(Peri,Data)                SET_BIT(Peri,Data,RTC,RTCPFCR,PC15MODE)
#define SET_RTC_CR_PC15VAL(Peri,Data)                 SET_BIT(Peri,Data,RTC,RTCPFCR,PC15VALUE)

/* inline function */
static __inline void PCU_SetRTCPortInOutMode(P_PCU_ID_e eId, P_PCU_PIN_ID_e ePinId, P_PCU_INOUT_e eInOut)
{
    RTC_Type *ptRtc = (RTC_Type *)RTC_REG_BASE;

    if(eId != P_PCU_ID_C)
    {
        return;
    }

    switch(ePinId)
    {
        case P_PCU_PIN_ID_13:
            SET_RTC_CR_PC13MODE(ptRtc, RTC_PC13_MODE((uint8_t)eInOut)); 
            break;
        case P_PCU_PIN_ID_14:
            SET_RTC_CR_PC14MODE(ptRtc, RTC_PCXX_MODE((uint8_t)eInOut)); 
            break;
        case P_PCU_PIN_ID_15:
            SET_RTC_CR_PC15MODE(ptRtc, RTC_PCXX_MODE((uint8_t)eInOut)); 
            break;
        default:
            break;
    }
}

static __inline void PCU_SetRTCPortOutputValue(P_PCU_ID_e eId, P_PCU_PIN_ID_e ePinId, P_PCU_PORT_e eOutput)
{
    RTC_Type *ptRtc = (RTC_Type *)RTC_REG_BASE;

    if(eId != P_PCU_ID_C)
    {
        return;
    }

    switch(ePinId)
    {
        case P_PCU_PIN_ID_13:
            SET_RTC_CR_PC13VAL(ptRtc, (bool)eOutput); 
            break;
        case P_PCU_PIN_ID_14:
            SET_RTC_CR_PC14VAL(ptRtc, (bool)eOutput); 
            break;
        case P_PCU_PIN_ID_15:
            SET_RTC_CR_PC15VAL(ptRtc, (bool)eOutput); 
            break;
        default:
            break;
    }
}

/* PCU IRQ Handler */
static void PRV_PCU_IRQHandler(PCU_ID_e eId, PORT_Type *ptPcu, uint32_t un32Status);

static __inline void PCU0_INT_IRQHandler(void)
{
    PORT_Type *ptPcu = (PORT_Type *)(PCU_REG_BASE);
    uint32_t un32Status = GET_PCU_ISR_REG(ptPcu);
    if(un32Status)
    {
        PRV_PCU_IRQHandler(PCU_ID_A, ptPcu, un32Status);
    }
    ptPcu = (PORT_Type *)(PCU_REG_BASE + (PCU_REG_OFFSET * PCU_ID_B));
    un32Status = GET_PCU_ISR_REG(ptPcu);
    if(un32Status)
    {
        PRV_PCU_IRQHandler(PCU_ID_B, ptPcu, un32Status);
    }
}

static __inline void PCU1_INT_IRQHandler(void)
{
    PORT_Type *ptPcu = (PORT_Type *)(PCU_REG_BASE + (PCU_REG_OFFSET * PCU_ID_C));
    uint32_t un32Status = GET_PCU_ISR_REG(ptPcu);
    if(un32Status)
    {
        PRV_PCU_IRQHandler(PCU_ID_C, ptPcu, un32Status);
    }
    ptPcu = (PORT_Type *)(PCU_REG_BASE + (PCU_REG_OFFSET * PCU_ID_F));
    un32Status = GET_PCU_ISR_REG(ptPcu);
    if(un32Status)
    {
        PRV_PCU_IRQHandler(PCU_ID_F, ptPcu, un32Status);
    }
}

static __inline void PCU2_INT_IRQHandler(void)
{
    ;
}

static __inline void PCU3_INT_IRQHandler(void)
{
    ;
}

static __inline void PCU4_INT_IRQHandler(void)
{
    ;
}

static __inline void PCU5_INT_IRQHandler(void)
{
    ;
}

static __inline void PCU6_INT_IRQHandler(void)
{
    ;
}

#endif /* _HAL_PCU_V_01_00_02_H_ */
