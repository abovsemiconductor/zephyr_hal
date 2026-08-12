/**
 *******************************************************************************
 * @file        hal_adc_f_01_00_01.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F1x typed ADC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_ADC_F_01_00_01_H_
#define _HAL_ADC_F_01_00_01_H_

/* Feature(Function) Configuration Define */
#define ADC_FEATURE_SEQ_TRG_TYPE_SINGLE

/* Internal Macro */
#define ADC_REG_BASE                                  ADC_BASE
#define ADC_REG_OFFSET                                0x100
#define ADC_RESOLUTION                                4095
#define ADC_MAX_SEQUENCE                              1
#define ADC_SEQ_OFFSET(x)                             0
#define ADC_SEQ_CH_OFFSET                             0
#define ADC_MODE_SEL(x)                               (x)
#define ADC_TRG_SRC(x)                                (void)x
#define ADC_CH_OFFSET(x)                              (x)
#define ADC_SEQTRG_SRC(x,y)                           (x == 1 ? y + 8 : 0)
#define ADC_EXTERNAL_PIN                              1
#define ADC_MODE_ONLY_SINGLE                          1
#define ADC_SHIFT_DATA                                4

/* Bit/Register Macro */
#define SET_ADC_CR_START(Peri,Data)                   SET_BIT(Peri,true,ADC,CR,ADST)
#define SET_ADC_CR_STOP(Peri,Data)                    SET_BIT(Peri,false,ADC,CR,ADST)
#define SET_ADC_CR_CH_SEL0(Peri,Data,Offset)          SET_BIT_OFFSET(Peri,Offset,Data,ADC,CR,ADSEL)
#define SET_ADC_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,ADC,MR,ADCEN)
#define SET_ADC_CR_ADCPD(Peri,Data)                   SET_BIT(Peri,Data,ADC,MR,ADSTBY)
#define SET_ADC_CR_REF(Peri,Data)                     (void)Peri
#define SET_ADC_CR_SEQTRG_SRC(Peri,Data,Offset)       \
                                                      SET_BIT_OFFSET(Peri,0x00,((Data & 0x8) >> 3),ADC,MR,EXTRG); \
                                                      SET_BIT_OFFSET(Peri,0x00,(Data & 0x7),ADC,MR,TSEL)
#define SET_ADC_DR_PREDIV(Peri,Data)                  SET_BIT(Peri,Data,ADC,MR,ADCS)
#define GET_ADC_DR_OUT(Addr)                          (GET_REG_ADDR_DATA(Addr) >> ADC_SHIFT_DATA)
#define GET_ADC_DR_BASE_ADDR(Peri)                    GET_REG_ADDR(Peri,DR)


/* Interrupt Macro */
#define SET_ADC_IER_SINGLE_EN(Peri,Data)              SET_BIT(Peri,Data,ADC,MR,ADIE)
#define SET_ADC_IER_SINGLE_FLAG(Peri,Data)            SET_BIT(Peri,Data,ADC,CR,ADIF)
#define GET_ADC_IER_SINGLE_FLAG(Peri)                 GET_BIT(Peri,ADC,CR,ADIF)
#define GET_ADC_IER_FLAG                              GET_ADC_IER_SINGLE_FLAG
#define SET_ADC_IER_FLAG                              SET_ADC_IER_SINGLE_FLAG
#define BIT_ADC_IER_SINGLE_FLAG                       (0x1UL)

/* Unused Macro */
#define SET_ADC_DR_SAMPLETIME(Peri,Data)              (void)Peri
#define GET_ADC_DR_ADDR(Peri)                         (void)Peri
#define SET_ADC_CR_EXTCLK(Peri,Data)                  (void)Peri
#define GET_ADC_DR_CHINFO(Addr)                       0
#define GET_ADC_DR_TRGINFO(Addr)                      0
#define SET_ADC_CR_CHINFO(Peri,Data)                  (void)Peri
#define SET_ADC_CR_TRGINFO(Peri,Data)                 (void)Peri
#define SET_ADC_CR_ARST(Peri,Data)                    (void)Peri 
#define SET_ADC_CR_PCLKINV(Peri,Data)                 (void)Peri
#define SET_ADC_CR_TRG_SRC(Peri,Data)                 (void)Peri
#define SET_ADC_CR_TRG_CLR(Peri,Data)                 (void)Peri
#define SET_ADC_CR_CH_SEL1(Peri,Data,Offset)          (void)Peri
#define SET_ADC_CR_MODE(Peri,Data)                    (void)Peri
#define SET_ADC_CR_SEQCNT(Peri,Data)                  (void)Peri 
#define SET_ADC_CR_DMA_EN(Peri,Data)                  (void)Peri
#define GET_ADC_DR_DDR_ADDR(Peri)                     0
#define BIT_ADC_IER_CMP_FLAG(Id)                      0
#define BIT_ADC_IER_SEQ_FLAG                          0
#define BIT_ADC_IER_TRG_FLAG                          0
#define SET_ADC_IER_SEQ_EN(Peri,Data)                 (void)Peri
#define SET_ADC_IER_TRG_EN(Peri,Data)                 (void)Peri
#define SET_ADC_IER_DMA_EN(Peri,Data)                 (void)Peri
#define SET_ADC_IER_SEQ_FLAG(Peri,Data)               (void)Peri
#define GET_ADC_IER_SEQ_FLAG(Peri)                    0
#define SET_ADC_IER_TRG_FLAG(Peri,Data)               (void)Peri
#define GET_ADC_IER_TRG_FLAG(Peri)                    0
#define SET_ADC_IER_DMA_FLAG(Peri,Data)               (void)Peri
#define GET_ADC_IER_DMA_FLAG(Peri)                    0
#define SET_ADC_IER_DMAOVR_FLAG(Peri,Data)            (void)Peri
#define GET_ADC_IER_DMAOVR_FLAG(Peri)                 0

/* SCU Register Macro */
typedef PMU_Type                                      SCU_Type;
#define SCU_ADDR                                      PMU_BASE
#define SET_SCU_ADC_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,PMU,PER,ADC)
#define SET_SCU_ADC_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,PMU,PCCR,ADC)

#endif /* _HAL_ADC_F_01_00_01_H_ */
