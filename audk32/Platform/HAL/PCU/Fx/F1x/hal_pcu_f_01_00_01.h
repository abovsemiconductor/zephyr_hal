/**
 *******************************************************************************
 * @file        hal_pcu_f_01_00_01.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.01 typed PCU
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_PCU_F_01_00_01_H_
#define _HAL_PCU_F_01_00_01_H_

/* Feature(Function) Configuration Define */
#define PCU_FEATURE_EXT_INTERRUPT_CONFIGURATION
#define PCU_FEATURE_IRQ_UNMASK_ENABLE

/* Internal Macro */
typedef PA_Type                                       GPIO_Type;
typedef PA_Type                                       PORT_Type;
#define PCU_REG_BASE                                  PA_BASE
#define PCU_REG_OFFSET                                0x100
#define PCU_INTC_REG_BASE                             INTC_BASE
#define PCU_INTC_MODE_REG_BASE                        INTC_BASE + 0x100
#define PCU_INTC_TRG_REG_BASE                         INTC_BASE
#define PCU_INTC_FLAG_REG_BASE                        INTC_BASE + 0x200
#define PCU_INTC_REG_OFFSET                           0x04
#define PCU_IRQ_MAX_COUNT                             4

#define PCU_INTC_CFG_REG_OFFSET                       0x04
#define PCU_INTC_CFG_BIT_OFFSET                       0x04
#define PCU_INTC_CFG_REG_OFFSET2                      0x10

#define PCU_INTC_MODE_BIT_OFFSET                      0x02

#define PCU_INTC_TRG(x)                               (x == 3 ? 0 : 1)

#define PCU_INPUTMODE                                 0x00
#define PCU_INPUTMODE_ANG                             0x00
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
#define PCU_GROUP_INTR_IDX(x)                         (x < 4 ? (x / 2) : (x - 2))
#define PCU_MCCR_CLK(x)                               (x > 0 ? x+2 : x)
#define PCU_IRQ_MODE(x)                               (x == 3 ? 0x0 : 0x1)

/* Bit/Register Macro */
#define SET_PCU_MODE(Peri,Data,Pos)                   SET_REG_BIT(Peri,Data,MOD,MASK_2BITS,Pos)
#define SET_PCU_MODE_TYPE(Peri,Data,Pos)              SET_REG_BIT(Peri,Data,TYP,MASK_1BIT,Pos)
#define SET_PCU_MODE_ALT(Peri,Data,Pos)               SET_REG_BIT(Peri,Data,MOD,MASK_2BITS,Pos)
#define SET_PCU_ALT1(Peri,Data,Pos)                   SET_REG_BIT(Peri,Data,AFSR1,MASK_4BITS,Pos)
#define SET_PCU_ALT2(Peri,Data,Pos)                   (void)Peri
#define SET_PCU_PULL_MODE(Peri,Data,Pos)              SET_REG_BIT(Peri,Data,PUPD,MASK_2BITS,Pos)
#define GET_PCU_INPUT_DATA(Peri,Pos)                  GET_REG_BIT(Peri,INDR,MASK_1BIT,Pos)
#define SET_PCU_OUTPUT_DATA(Peri,Data,Pos)            SET_REG_BIT(Peri,Data,OUTDR,MASK_1BIT,Pos)
#define SET_PCU_OUTPUT_BIT(Peri,Data,Pos)             SET_REG_BIT(Peri,Data,BSR,MASK_1BIT,Pos)
#define SET_PCU_OUTPUT_CLEAR_BIT(Peri,Data,Pos)       SET_REG_BIT(Peri,Data,BCR,MASK_1BIT,Pos)
#define SET_PCU_OUTPUT_SUSTAIN(Peri,Data,Pos)         SET_REG_BIT(Peri,Data,OUTDMSK,MASK_1BIT,Pos)
#define SET_PCU_DEBOUNCE_EN(Peri,Data,Pos)            SET_REG_BIT(Peri,Data,DBCR,MASK_1BIT,Pos)
#define SET_PCU_DEBOUNCE_CLK(Peri,Data)               SET_BIT(Peri,(Data & 0x07),Pn,DBCR,DBCLK)


/* Interrupt Macro */ 
#define GET_PCU_IER_CFG_BASE_ADDR(Peri)               GET_REG_ADDR(Peri,EINT0CONF1);
#define GET_PCU_IER_TRG_BASE_ADDR(Peri)               GET_REG_ADDR(Peri,PBTRIG);
#define GET_PCU_IER_MODE_BASE_ADDR(Peri)              GET_REG_ADDR(Peri,PBCR);
#define SET_PCU_IER_CFG_PORT_SEL(Addr,RegOff,DataOff,Data) \
                                                      SET_BIT_ADDR_DATA_OFFSET(Addr,RegOff,DataOff,Data,INTC,EINT0CONF1,CONF0)
#define SET_PCU_IER_CFG_PORT_MODE(Addr,RegOff,DataOff,Data) \
                                                      SET_BIT_ADDR_DATA_OFFSET(Addr,RegOff,DataOff,Data,INTC,PBTRIG,ITRIG0)
#define SET_PCU_IER_CFG_PORT_TRG(Addr,RegOff,DataOff,Data) \
                                                      SET_BIT_ADDR_DATA_OFFSET(Addr,RegOff,DataOff,Data,INTC,PBCR,INTCTL0)
#define SET_PCU_IER_EN(Peri,Data,Pos)                 SET_REG_BIT(Peri,Data,IER,MASK_2BITS,Pos)
#define SET_PCU_IER_ST(Peri,Data,Pos)                 SET_REG_BIT(Peri,Data,ISR,MASK_2BITS,Pos)

#define GET_PCU_ISR_REG(Addr)                         GET_REG_ADDR_DATA(Addr)
#define SET_PCU_ISR_REG(Addr,Data)                    SET_REG_ADDR(Addr,Data)

/* Unused Macro */
#define SET_PCU_ACCESS_EN()                           
#define SET_PCU_ACCESS_DIS()                          
#define SET_PCU_INPUT_LEVEL(Peri,Data,Pos)            (void)Peri
#define SET_PCU_STR_EN(Peri,Data,Pos)                 (void)Peri
#define GET_PCU_IER_ST(Peri,Pos)                      0 

#define SET_PCU_ICR_EN(Peri,Data,Pos)                 SET_REG_BIT(Peri,Data,ICR,MASK_2BITS,Pos)

/* SCU Macro */
#define SET_SCU_PCU_MCCR_SEL0(Peri,Data)              SET_BIT(Peri,Data,SCU,MCCR4,PD0CSEL)
#define SET_SCU_PCU_MCCR_DIV0(Peri,Data)              SET_BIT(Peri,Data,SCU,MCCR4,PD0DIV)
#define SET_SCU_PCU_MCCR_SEL1(Peri,Data)              SET_BIT(Peri,Data,SCU,MCCR4,PD1CSEL)
#define SET_SCU_PCU_MCCR_DIV1(Peri,Data)              SET_BIT(Peri,Data,SCU,MCCR4,PD1DIV)

typedef SCUCG_Type                                    SCU_Type;
#define SCU_ADDR                                      SCUCG_BASE
#define SET_INTC_IRQ_UNMASK_EN(Peri,Irq,Data)         SET_BIT_ID(Peri,Irq,Data,INTC,MSK,IMSK0_LVI)

#endif /* _HAL_PCU_F_01_00_00_H_ */
