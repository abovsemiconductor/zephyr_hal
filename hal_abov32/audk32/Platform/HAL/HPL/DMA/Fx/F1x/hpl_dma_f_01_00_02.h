/**
 *******************************************************************************
 * @file        hpl_dma_v_01_00_02.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.02 typed DMA
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HPL_DMA_F_01_00_02_H_
#define _HPL_DMA_F_01_00_02_H_

/* Feature(Function) Configuration Define */
#define DMA_FEATURE_INTERNAL_INTERRUPT
#define DMA_FEATURE_IRQ_UNMASK_ENABLE

/* Internal Macro */
typedef DMACn_Type                                    DMA_Type;
#define DMA_REG_BASE                                  DMAC0_BASE
#define DMA_REG_OFFSET                                0x20
#if (CONFIG_DMA_REG_NAME == 1)
#define DMA_MAX_IRQ                                   2
#define DMA_IRQ_0_START_IDX                           0
#define DMA_IRQ_0_END_IDX                             0
#define DMA_IRQ_1_START_IDX                           1
#define DMA_IRQ_1_END_IDX                             1
#else
#define DMA_MAX_IRQ                                   2
#define DMA_IRQ_0_START_IDX                           0
#define DMA_IRQ_0_END_IDX                             1
#define DMA_IRQ_1_START_IDX                           2
#define DMA_IRQ_1_END_IDX                             3
#endif

/* Bit/Register Macro */
#define SET_DMA_CR_PERISEL(Peri,Data)                 SET_BIT(Peri,Data,DMACn,CR,PERSEL)
#define GET_DMA_CR_PERISEL(Peri)                      GET_BIT(Peri,DMACn,CR,PERSEL)
#define SET_DMA_CR_SIZE(Peri,Data)                    SET_BIT(Peri,Data,DMACn,CR,SIZE)
#define SET_DMA_CR_DIR(Peri,Data)                     SET_BIT(Peri,Data,DMACn,CR,DIR)
#define SET_DMA_CR_LEN(Peri,Data)                     SET_BIT(Peri,Data,DMACn,CR,TRANSCNT)
#define SET_DMA_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,DMACn,CR,CHnEN)
#define SET_DMA_ADDR_PAR(Peri,Data)                   SET_BIT(Peri,Data,DMACn,PAR,POADR)
#define SET_DMA_ADDR_MAR(Peri,Data)                   SET_BIT(Peri,Data,DMACn,MAR,MAR)
#define GET_DMA_SR_EOT(Peri)                          GET_DMA_IER_FLAG(Peri)
#define GET_DMA_CR_DIR(Peri)                          GET_BIT(Peri,DMACn,CR,DIR)

/* Interrupt Macro */
#define SET_DMA_IER_EN(Peri,Data)                     SET_BIT(Peri,Data,DMACn,IESR,TRCIENn)
#define SET_DMA_IER_FLAG(Peri,Data)                   SET_BIT(Peri,Data,DMACn,IESR,TRCIFGn)
#define GET_DMA_IER_FLAG(Peri)                        GET_BIT(Peri,DMACn,IESR,TRCIFGn)
#define SET_DMA_IER_ERR_EN(Peri,Data)                 SET_BIT(Peri,Data,DMACn,IESR,TRERIENn)
#define SET_DMA_IER_ERR_FLAG(Peri,Data)               SET_BIT(Peri,Data,DMACn,IESR,TRERIFGn)
#define GET_DMA_IER_ERR_FLAG(Peri)                    GET_BIT(Peri,DMACn,IESR,TRERIFGn)

/* Unused Macro */
#define SET_DMA_CR_CLEAR(Peri,Data)                   (void)Peri

/* SCU Macro */
typedef SCUCG_Type                                    SCU_Type;
#define SCU_ADDR                                      SCUCG_BASE
#define SET_SCU_DMA_PER(Peri,Data)                    (void)Peri
#define SET_SCU_DMA_PCER(Peri,Data)                   SET_BIT(Peri,Data,SCUCG,PPCLKEN2,DMACLKE)
#define SET_INTC_IRQ_UNMASK_EN(Peri,Irq,Data)         SET_BIT_ID(Peri,Irq,Data,INTC,MSK,IMSK0_LVI_ECCC)

#endif /* _HPL_DMA_F_01_00_02_H_ */
