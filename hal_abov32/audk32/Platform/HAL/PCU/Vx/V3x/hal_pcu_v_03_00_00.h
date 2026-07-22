/**
 *******************************************************************************
 * @file        hal_pcu_v_03_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 03.00.00 typed PCU
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_PCU_V_03_00_00_H_
#define _HAL_PCU_V_03_00_00_H_

/* Internal Macro */
typedef PCA_Type                                      PORT_Type;
typedef PA_Type                                       GPIO_Type;

#define PCU_REG_BASE                                  PCA_BASE
#define PCU_REG_GPIO_BASE                             PA_BASE
#define PCU_REG_OFFSET                                0x20
#define PCU_GPIO_REG_OFFSET                           0x10
#define PCU_IRQ_MAX_COUNT                             6

#define PCU_INPUTMODE                                 0x02
#define PCU_INPUTMODE_ANG                             0x03
#define PCU_OUTPUTMODE(x)                             (x & 0x01)
#define PCU_OUTPUTMODE_TYP(x)                         0
#define PCU_ALTMODE                                   0x00
#define PCU_ALTMODE_BIT(x)                            (x*2)
#define PCU_ALTMODE_TYPE(x)                           (x < 4 ? x : 0x7)
#define PCU_ALTTYPE_BIT(x)                            (x*2)
#define PCU_ALT2TYPE_BIT(x)                           (x*2)
#define PCU_PULLMODE_TYPE(x)                          (x == 2 ? ((((x+1) & 0x2) << 14) | ((x+1) & 0x01)) : (((x & 0x2) << 14) | (x & 0x01)))
#define PCU_PULLMODE_BIT(x)                           (x)
#define PCU_INTR_BIT(x)                               (x*2)
#define PCU_GROUP_INTR_IDX(x)                         (x)

/* Bit/Register Macro */
#define GET_PCU_ISR_REG(Peri)                         GET_REG(Peri,ISR)
#define SET_PCU_ISR_REG(Peri,Data)                    SET_REG(Peri,Data,ISR)
#define SET_PCU_MODE(Peri,Data,Pos)                   SET_REG_BIT(Peri,Data,CR,MASK_2BITS,Pos)
#define SET_PCU_ALT1(Peri,Data,Pos)                   SET_REG_BIT(Peri,Data,MR,MASK_2BITS,Pos)
#define SET_PCU_ALT2(Peri,Data,Pos)                   SET_PCU_ALT1(Peri,Data,Pos)
#define SET_PCU_PULL_MODE(Peri,Data,Pos)              SET_REG_BIT(Peri,Data,PCR,MASK_1BIT,Pos)
#define GET_PCU_INPUT_DATA(Peri,Pos)                  GET_REG_BIT(Peri,IDR,MASK_1BIT,Pos)
#define SET_PCU_OUTPUT_DATA(Peri,Data,Pos)            SET_REG_BIT(Peri,Data,ODR,MASK_1BIT,Pos)
#define SET_PCU_OUTPUT_BIT(Peri,Data,Pos)             SET_REG_BIT(Peri,0x1,SRR,MASK_1BIT,Pos)
#define SET_PCU_OUTPUT_CLEAR_BIT(Peri,Data,Pos)       SET_REG_BIT(Peri,Data,SRR,MASK_1BIT,(Pos+16))
#define SET_PCU_DEBOUNCE_EN(Peri,Data,Pos)            SET_REG_BIT(Peri,Data,DER,MASK_1BIT,Pos)
#define SET_PCU_IER_EN(Peri,Data,Pos)                 SET_REG_BIT(Peri,Data,IER,MASK_2BITS,Pos)
#define SET_PCU_ICR_EN(Peri,Data,Pos)                 SET_REG_BIT(Peri,Data,ICR,MASK_2BITS,Pos)
#define SET_PCU_IER_ST(Peri,Data,Pos)                 SET_REG_BIT(Peri,Data,ISR,MASK_2BITS,Pos)
#define GET_PCU_IER_ST(Peri,Pos)                      GET_REG_BIT(Peri,ISR,MASK_2BITS,Pos)

#define SET_PCU_OUTPUT_SUSTAIN(Peri,Data,Pos)         (void)Peri
#define SET_PCU_MODE_TYPE(Peri,Data,Pos)              (void)Peri
#define SET_PCU_MODE_ALT(Peri,Data,Pos)               (void)Peri
#define SET_PCU_ACCESS_EN()                           (void)0
#define SET_PCU_ACCESS_DIS()                          (void)0

static void PRV_PCU_IRQHandler(PCU_ID_e eId, PORT_Type *ptPcu, uint32_t un32Status);

static __inline void PCU0_INT_IRQHandler(void)
{
    PORT_Type *ptPcu = (PORT_Type *)(PCU_REG_BASE);
    uint32_t un32Status = GET_PCU_ISR_REG(ptPcu);
    if(un32Status)
    {
        PRV_PCU_IRQHandler(PCU_ID_A, ptPcu, un32Status);
    }
}

static __inline void PCU1_INT_IRQHandler(void)
{
    PORT_Type *ptPcu = (PORT_Type *)(PCU_REG_BASE + (PCU_REG_OFFSET * PCU_ID_B));
    uint32_t un32Status = GET_PCU_ISR_REG(ptPcu);
    if(un32Status)
    {
        PRV_PCU_IRQHandler(PCU_ID_B, ptPcu, un32Status);
    }
}

static __inline void PCU2_INT_IRQHandler(void)
{
    PORT_Type *ptPcu = (PORT_Type *)(PCU_REG_BASE + (PCU_REG_OFFSET * PCU_ID_C));
    uint32_t un32Status = GET_PCU_ISR_REG(ptPcu);
    if(un32Status)
    {
        PRV_PCU_IRQHandler(PCU_ID_C, ptPcu, un32Status);
    }
}

static __inline void PCU3_INT_IRQHandler(void)
{
    PORT_Type *ptPcu = (PORT_Type *)(PCU_REG_BASE + (PCU_REG_OFFSET * PCU_ID_D));
    uint32_t un32Status = GET_PCU_ISR_REG(ptPcu);
    if(un32Status)
    {
        PRV_PCU_IRQHandler(PCU_ID_D, ptPcu, un32Status);
    }
}

static __inline void PCU4_INT_IRQHandler(void)
{
    PORT_Type *ptPcu = (PORT_Type *)(PCU_REG_BASE + (PCU_REG_OFFSET * PCU_ID_E));
    uint32_t un32Status = GET_PCU_ISR_REG(ptPcu);
    if(un32Status)
    {
        PRV_PCU_IRQHandler(PCU_ID_E, ptPcu, un32Status);
    }
}

static __inline void PCU5_INT_IRQHandler(void)
{
    PORT_Type *ptPcu = (PORT_Type *)(PCU_REG_BASE + (PCU_REG_OFFSET * PCU_ID_F));
    uint32_t un32Status = GET_PCU_ISR_REG(ptPcu);
    if(un32Status)
    {
        PRV_PCU_IRQHandler(PCU_ID_F, ptPcu, un32Status);
    }
}

static __inline void PCU6_INT_IRQHandler(void)
{
    PORT_Type *ptPcu = (PORT_Type *)(PCU_REG_BASE + (PCU_REG_OFFSET * PCU_ID_G));
    uint32_t un32Status = GET_PCU_ISR_REG(ptPcu);
    if(un32Status)
    {
        PRV_PCU_IRQHandler(PCU_ID_G, ptPcu, un32Status);
    }
}

#endif /* _HAL_PCU_V_03_00_00_H_ */
