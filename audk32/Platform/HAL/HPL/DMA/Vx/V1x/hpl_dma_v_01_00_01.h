/**
 *******************************************************************************
 * @file        hpl_dma_v_01_00_01.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.01 typed DMA
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HPL_DMA_V_01_00_01_H_
#define _HPL_DMA_V_01_00_01_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#if (CONFIG_DMA_REG_NAME == 0)
typedef DMAC_Type                                     DMA_Type;
#define SET_DMA_BIT(Peri,Data,RegName,BitName)        SET_BIT(Peri,Data,DMAC0,RegName,BitName)
#define GET_DMA_BIT(Peri,RegName,BitName)             GET_BIT(Peri,DMAC0,RegName,BitName)
#define DMA_REG_BASE                                  DMAC0_BASE
#elif (CONFIG_DMA_REG_NAME == 1)
#define SET_DMA_BIT(Peri,Data,RegName,BitName)        SET_BIT(Peri,Data,DMA,RegName,BitName)
#define GET_DMA_BIT(Peri,RegName,BitName)             GET_BIT(Peri,DMA,RegName,BitName)
#define DMA_REG_BASE                                  DMA0_BASE
#endif
#define DMA_REG_OFFSET                                0x10

#define SET_DMA_CR_PERISEL(Peri,Data)                 SET_DMA_BIT(Peri,Data,CR,PERISEL)
#define SET_DMA_CR_SIZE(Peri,Data)                    SET_DMA_BIT(Peri,Data,CR,SIZE)
#define SET_DMA_CR_DIR(Peri,Data)                     SET_DMA_BIT(Peri,Data,CR,DIR)
#define SET_DMA_CR_LEN(Peri,Data)                     SET_DMA_BIT(Peri,Data,CR,TRANSCNT)
#define SET_DMA_CR_EN(Peri,Data)                      SET_DMA_BIT(Peri,Data,SR,DMAEN)
#define SET_DMA_ADDR_PAR(Peri,Data)                   SET_DMA_BIT(Peri,Data,PAR,PAR)
#define SET_DMA_ADDR_MAR(Peri,Data)                   SET_DMA_BIT(Peri,Data,MAR,MAR)
#define GET_DMA_SR_EOT(Peri)                          GET_DMA_BIT(Peri,SR,EOT)
#define GET_DMA_CR_DIR(Peri)                          GET_DMA_BIT(Peri,CR,DIR)
#define SET_DMA_CR_CLEAR(Peri,Data)                   SET_DMA_BIT(Peri,Data,SR,DMARC)

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_DMA_PER(Peri,Data)                    SET_BIT(Peri,Data,SCU,PER1,DMA)
#define SET_SCU_DMA_PCER(Peri,Data)                   SET_BIT(Peri,Data,SCU,PCER1,DMA)

#endif /* _HPL_DMA_V_01_00_01_H_ */
