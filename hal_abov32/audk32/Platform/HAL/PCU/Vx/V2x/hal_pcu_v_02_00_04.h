/**
 *******************************************************************************
 * @file        hal_pcu_v_02_00_04.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 02.00.04 typed PCU
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_PCU_V_02_00_04_H_
#define _HAL_PCU_V_02_00_04_H_

/* Internal Macro */
typedef PCU_Type                                      PORT_Type;
typedef PCU_Type                                      GPIO_Type;
typedef PORTEN_Type                                   PCU_PORTEN_Type;
#define PCU_REG_BASE                                  PA_BASE
#define PCU_REG_OFFSET                                0x100
#define PCU_PORT_EN_BASE                              PORTEN_BASE
#define PCU_IRQ_MAX_COUNT                             7

#define PCU_INPUTMODE                                 0x03
#define PCU_INPUTMODE_ANG                             0x03
#define PCU_OUTPUTMODE(x)                             (x & 0x01)
#define PCU_OUTPUTMODE_TYP(x)                         0x00
#define PCU_ALTMODE                                   0x00
#define PCU_ALTMODE_BIT(x)                            (x*2)
#define PCU_ALTMODE_TYPE(x)                           (x < 6 ? x : 0x07)
#define PCU_ALTTYPE_BIT(x)                            (x*4)
#define PCU_ALT2TYPE_BIT(x)                           ((x-8)*4)
#define PCU_PULLMODE_TYPE(x)                          (x + 1)
#define PCU_PULLMODE_BIT(x)                           (x*2)
#define PCU_INTR_BIT(x)                               (x*2)
#define PCU_GROUP_INTR_IDX(x)                         (x)
#define PCU_MCCR_CLK(x)                               (x > 1 ? x+2 : x)

/* Bit/Register Macro */
#define GET_PCU_ISR_REG(Peri)                         GET_REG(Peri,ISR)
#define SET_PCU_ISR_REG(Peri,Data)                    SET_REG(Peri,Data,ISR)
#define SET_PCU_MODE(Peri,Data,Pos)                   SET_REG_BIT(Peri,Data,CR,MASK_2BITS,Pos)
#define SET_PCU_ALT1(Peri,Data,Pos)                   SET_REG_BIT(Peri,(0x8|Data),MR1,MASK_4BITS,Pos)
#define SET_PCU_ALT2(Peri,Data,Pos)                   SET_REG_BIT(Peri,(0x8|Data),MR2,MASK_4BITS,Pos)
#define SET_PCU_PULL_MODE(Peri,Data,Pos)              SET_REG_BIT(Peri,Data,PRCR,MASK_2BITS,Pos)
#define SET_PCU_PORTEN(Peri,Data)                     SET_BIT(Peri,Data,PORTEN,EN,PORTEN)
#define GET_PCU_INPUT_DATA(Peri,Pos)                  GET_REG_BIT(Peri,IDR,MASK_1BIT,Pos)
#define SET_PCU_OUTPUT_DATA(Peri,Data,Pos)            SET_REG_BIT(Peri,Data,ODR,MASK_1BIT,Pos)
#define SET_PCU_OUTPUT_BIT(Peri,Data,Pos)             SET_REG_BIT(Peri,Data,BSR,MASK_1BIT,Pos)
#define SET_PCU_OUTPUT_CLEAR_BIT(Peri,Data,Pos)       SET_REG_BIT(Peri,Data,BCR,MASK_1BIT,Pos)
#define SET_PCU_DEBOUNCE_EN(Peri,Data,Pos)            SET_REG_BIT(Peri,Data,DER,MASK_1BIT,Pos)
#define SET_PCU_STR_EN(Peri,Data,Pos)                 SET_REG_BIT(Peri,Data,STR,MASK_1BIT,Pos)
#define SET_PCU_ICR_EN(Peri,Data,Pos)                 SET_REG_BIT(Peri,Data,ICR,MASK_2BITS,Pos)
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

/* Unused Macro */
#define SET_PCU_MODE_TYPE(Peri,Data,Pos)              (void)0
#define SET_PCU_MODE_ALT(Peri,Data,Pos)               (void)0
#define SET_PCU_OUTPUT_SUSTAIN(Peri,Data,Pos)         (void)Peri

/* SCU Register Macro */
#define SCU_ADDR                                       SCU_BASE
/* A/B Port Debounce Clock */
#define SET_SCU_PCU_MCCR_SEL0(Peri,Data)               SET_BIT(Peri,Data,SCU,MCCR4,PGADCSEL)
#define SET_SCU_PCU_MCCR_DIV0(Peri,Data)               SET_BIT(Peri,Data,SCU,MCCR4,PGADCDIV)
/* C/D Port Debounce Clock */
#define SET_SCU_PCU_MCCR_SEL1(Peri,Data)               SET_BIT(Peri,Data,SCU,MCCR5,PGBDCSEL)
#define SET_SCU_PCU_MCCR_DIV1(Peri,Data)               SET_BIT(Peri,Data,SCU,MCCR5,PGBDCDIV)
/* E/F/G Port Debounce Clock */
#define SET_SCU_PCU_MCCR_SEL2(Peri,Data)               SET_BIT(Peri,Data,SCU,MCCR5,PGCDCSEL)
#define SET_SCU_PCU_MCCR_DIV2(Peri,Data)               SET_BIT(Peri,Data,SCU,MCCR5,PGCDCDIV)


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
    ;
}

#endif /* _HAL_PCU_V_02_00_04_H_ */
