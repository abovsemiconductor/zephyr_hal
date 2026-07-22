/**
 *******************************************************************************
 * @file        hal_adc_f_02_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for F2x typed ADC
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_ADC_F_02_00_00_H_
#define _HAL_ADC_F_02_00_00_H_

/* Feature(Function) Configuration Define */
#define ADC_FEATURE_IRQ_UNMASK_ENABLE
#define ADC_FEATURE_HAS_OVER_SAMPLING
#define ADC_FEATURE_SEQ_TRG_TYPE_SHARE
#define ADC_FEATURE_OVERRUN_INTR
#define ADC_FEATURE_STABLE_INTR
#define ADC_FEATURE_READY_BIT
#define ADC_FEATURE_DMA_INTERNAL_INTERRUPT

/* Internal Macro */
#define ADC_REG_BASE                                  ADC_BASE
#define ADC_REG_OFFSET                                0x100
#define ADC_RESOLUTION                                65535
#define ADC_MAX_SEQUENCE                              19
#define ADC_SEQ_OFFSET(x)                             0
#define ADC_SEQ_CH_OFFSET                             0
#define ADC_MODE_SEL(x)                               (x == 4 ? 2 : \
                                                      (x == 2 ? 1 : \
                                                      (x == 3 ? 1 : \
                                                       x )))
#define ADC_TRG_SRC(x)                                (void)x
#define ADC_CH_OFFSET(x)                              (x)
#define ADC_SEQTRG_SRC(x,y)                           (x == 4 ? 1 + y : x != 7 ? 0 : x)
#define ADC_EXTERNAL_PIN                              1
#define ADC_MODE_ONLY_SINGLE                          1
#define ADC_SHIFT_DATA                                4

/* Bit/Register Macro */
#define SET_ADC_CR_START(Peri,Data)                   SET_BIT(Peri,true,ADC,CR,ADST)
#define SET_ADC_CR_STOP(Peri,Data)                    SET_BIT(Peri,false,ADC,CR,ADST)
#define SET_ADC_CR_MODE(Peri,Data)                    SET_BIT(Peri,Data,ADC,CR,MDSEL)
#define SET_ADC_CR_READY(Peri,Data)                   SET_BIT(Peri,Data,ADC,CR,ADRDY)
#define SET_ADC_DR_SAMPLETIME(Peri,Data)              SET_BIT(Peri,Data,ADC,SAMR,SAMCK)
#define SET_ADC_CR_CH_SEL0(Peri,Data)                 SET_REG(Peri,Data,CHSELR)
#define SET_ADC_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,ADC,CR,ADCEN)
#define SET_ADC_CR_SEQTRG_SRC(Peri,Data)              SET_BIT(Peri,Data,ADC,CR,TRIG)
#define SET_ADC_CR_SEQTRG_EXT_EDGE(Peri,Data)         SET_BIT(Peri,Data,ADC,CR,ETRGP)
#define SET_ADC_DR_PREDIV(Peri,Data)                  SET_BIT(Peri,Data,ADC,PREDR,PRED)
#define GET_ADC_DR_OUT(Addr)                          GET_BIT_ADDR(Addr,ADC,DR,ADDATA)
#define GET_ADC_DR_BASE_ADDR(Peri)                    GET_REG_ADDR(Peri,DR)
#define SET_ADC_CR_OVS_EN(Peri,Data)                  SET_BIT(Peri,Data,ADC,OVSCR,OVSMPEN)
#define SET_ADC_CR_OVS_RATIO(Peri,Data)               SET_BIT(Peri,Data,ADC,OVSCR,OVSMPR)
#define SET_ADC_CR_OVS_DATA_SHIFT(Peri,Data)          SET_BIT(Peri,Data,ADC,OVSCR,OVSHT)
#define GET_ADC_DR_DDR_ADDR(Peri)                     GET_REG_ADDR(Peri,DR)

/* Interrupt Macro */
#define BIT_ADC_IER_SINGLE_FLAG                       (0x1UL << BIT_NAME_POS(ADC_,IESR_,EOCIFLAG_))
#define BIT_ADC_IER_SEQ_FLAG                          (0x1UL << BIT_NAME_POS(ADC_,IESR_,EOSIFLAG_))
#define BIT_ADC_IER_OVR_FLAG                          (0x1UL << BIT_NAME_POS(ADC_,IESR_,OVRUNIFLAG_))
#define BIT_ADC_IER_STB_FLAG                          (0x1UL << BIT_NAME_POS(ADC_,IESR_,STBIFLAG_))
#define SET_ADC_IER_SINGLE_EN(Peri,Data)              SET_BIT(Peri,Data,ADC,IESR,EOCIEN)
#define SET_ADC_IER_SINGLE_FLAG(Peri,Data)            SET_BIT(Peri,Data,ADC,IESR,EOCIFLAG)
#define GET_ADC_IER_SINGLE_FLAG(Peri)                 GET_BIT(Peri,ADC,IESR,EOCIFLAG)
#define SET_ADC_IER_SEQ_EN(Peri,Data)                 SET_BIT(Peri,Data,ADC,IESR,EOSIEN)
#define SET_ADC_IER_SEQ_FLAG(Peri,Data)               SET_BIT_FLAG(Peri,Data,ADC,IESR,EOSIFLAG)
#define GET_ADC_IER_SEQ_FLAG(Peri)                    GET_BIT(Peri,ADC,IESR,EOSIFLAG)
#define SET_ADC_IER_OVR_EN(Peri,Data)                 SET_BIT(Peri,Data,ADC,IESR,OVRUNIEN)
#define SET_ADC_IER_OVR_FLAG(Peri,Data)               SET_BIT(Peri,Data,ADC,IESR,OVRUNIFLAG)
#define GET_ADC_IER_OVR_FLAG(Peri)                    GET_BIT(Peri,ADC,IESR,OVRUNIFLAG)
#define SET_ADC_IER_STB_EN(Peri,Data)                 SET_BIT(Peri,Data,ADC,IESR,STBIEN)
#define SET_ADC_IER_STB_FLAG(Peri,Data)               SET_BIT(Peri,Data,ADC,IESR,STBIFLAG)
#define GET_ADC_IER_STB_FLAG(Peri)                    GET_BIT(Peri,ADC,IESR,STBIFLAG)
#define GET_ADC_IER_FLAG(Peri)                        GET_REG(Peri,IESR)
#define SET_ADC_IER_FLAG(Peri,Data)                   SET_REG(Peri,Data,IESR)

/* Unused Macro */
#define SET_ADC_CR_REF(Peri,Data)                     (void)Peri
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
#define SET_ADC_CR_SEQCNT(Peri,Data)                  (void)Peri 
#define SET_ADC_CR_ADCPD(Peri,Data)                   (void)Peri
#define SET_ADC_CR_DMA_EN(Peri,Data)                  (void)Peri
#define BIT_ADC_IER_CMP_FLAG(Id)                      0
#define BIT_ADC_IER_TRG_FLAG                          0
#define SET_ADC_IER_TRG_EN(Peri,Data)                 (void)Peri
#define SET_ADC_IER_DMA_EN(Peri,Data)                 (void)Peri
#define SET_ADC_IER_TRG_FLAG(Peri,Data)               (void)Peri
#define GET_ADC_IER_TRG_FLAG(Peri)                    0
#define SET_ADC_IER_DMA_FLAG(Peri,Data)               (void)Peri
#define GET_ADC_IER_DMA_FLAG(Peri)                    0
#define SET_ADC_IER_DMAOVR_FLAG(Peri,Data)            (void)Peri
#define GET_ADC_IER_DMAOVR_FLAG(Peri)                 0

/* SCU Macro */
typedef SCUCG_Type                                    SCU_Type;
#define SCU_ADDR                                      SCUCG_BASE
#define SET_SCU_ADC_PER(Peri,Id,Data)                 (void)Peri
#define SET_SCU_ADC_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCUCG,PPCLKEN2,ADCLKE)
#define SET_INTC_IRQ_UNMASK_EN(Peri,Irq,Data)         SET_BIT_ID(Peri,Irq,Data,INTC,MSK,IMSK0_LVI)

#endif /* _HAL_ADC_F_02_00_00_H_ */
