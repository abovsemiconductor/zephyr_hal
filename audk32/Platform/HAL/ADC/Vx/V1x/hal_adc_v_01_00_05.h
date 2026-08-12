/**
 *******************************************************************************
 * @file        hal_adc_v_01_00_05.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for V1x typed ADC
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_ADC_V_01_00_05_H_
#define _HAL_ADC_V_01_00_05_H_

/* Feature(Function) Configuration Define */
#define ADC_FEATURE_COMPARATOR
#define ADC_FEATURE_SEQ_TRG_TYPE_INDEPENDENT
#define ADC_FEATURE_SEQ_SAMPLING_TIME_INDEPENDENT

/* Internal Macro */
#define ADC_REG_BASE                                  ADC0_BASE
#define ADC_REG_OFFSET                                0x100
#define ADC_RESOLUTION                                4095
#define ADC_MAX_SEQUENCE                              8
#define ADC_SEQ_OFFSET                                4
#define ADC_SEQ_CH_OFFSET                             8
#define ADC_NO_TRG_SOURCE                             11
#define ADC_MODE_SEL(x)                               (x < 2 ? 0 : x-1)
#define ADC_TRG_SRC(x)                                (x == P_ADC_TRG_ADST    ? 0 : \
                                                      (x == P_ADC_TRG_TIMER1) ? 1 : ADC_NO_TRG_SOURCE)
#define ADC_SEQTRG_SRC(x,y)                           (x == P_ADC_TRG_TIMER1 ? y : 15)
#define ADC_CH_OFFSET(x)                              (x%4)
#define ADC_SEQTRG_OFFSET(x)                          (x*4)
#define ADC_MCCR_CLK(x)                               (x > 0 ? x+2 : x)
#define ADC_EXTERNAL_PIN                              0
#define ADC_MODE_ONLY_SINGLE                          1

/* Bit/Register Macro */
#define GET_ADC_DR_BASE_ADDR(Peri)                    GET_REG_ADDR(Peri,DR0)
#define GET_ADC_DR_DDR_ADDR(Peri)                     GET_REG_ADDR(Peri,DDR)
#define SET_ADC_CR_EN(Peri,Data)                      SET_BIT(Peri,Data,ADC,MR,ADEN)
#define SET_ADC_CR_START(Peri,Data)                   SET_BIT(Peri,Data,ADC,CR,ASTART)
#define SET_ADC_CR_STOP(Peri,Data)                    SET_BIT(Peri,Data,ADC,CR,ASTOP)
#define SET_ADC_CR_TRG_CLR(Peri,Data)                 SET_BIT(Peri,Data,ADC,CR,TRGCLR)
#define SET_ADC_CR_CH_SEL0(Peri,Data,Offset)          SET_BIT_OFFSET(Peri,Offset,Data,ADC,SCSR1,SEQ0CH)
#define SET_ADC_CR_CH_SEL1(Peri,Data,Offset)          SET_BIT_OFFSET(Peri,Offset,Data,ADC,SCSR2,SEQ4CH)
#define SET_ADC_CR_MODE(Peri,Data)                    SET_BIT(Peri,Data,ADC,MR,ADMOD)
#define SET_ADC_CR_TRG_SRC(Peri,Data)                 SET_BIT(Peri,Data,ADC,MR,TRGSEL)
#define SET_ADC_CR_SEQTRG_SRC(Peri,Data,Offset)       SET_BIT_OFFSET(Peri,Offset,Data,ADC,TRG,SEQTRG0_BSTTRG)
#define SET_ADC_CR_EXTCLK(Peri,Data)                  (void)Peri
#define SET_ADC_DR_SAMPLETIME(Peri,Data)              (void)Peri
#define GET_ADC_DR_OUT(Addr)                          GET_BIT_ADDR(Addr,ADC,DR0,ADDATA)
#define GET_ADC_DR_CHINFO(Addr)                       GET_BIT_ADDR(Addr,ADC,DR0,ACH)
#define GET_ADC_DR_TRGINFO(Addr)                      GET_BIT_ADDR_MSK(Addr,0xFFUL,ADC,DR0,TRGINFO0)
#define SET_ADC_CR_SEQCNT(Peri,Data)                  SET_BIT(Peri,Data,ADC,MR,SEQCNT)
#define SET_ADC_DR_PREDIV(Peri,Data)                  SET_BIT(Peri,Data,ADC,CCR,CLKDIV)
#define SET_ADC_CR_ADCPD(Peri,Data)                   (void)Peri
#define SET_ADC_CR_DMA_EN(Peri,Data)                  SET_BIT(Peri,Data,ADC,MR,DMAEN)
#define SET_ADC_CR_CSEQN(Peri,Data)                   SET_BIT(Peri,Data,ADC,CSCR,CSEQN)
#define SET_ADC_CR_CHINFO(Peri,Data)                  (void)Peri
#define SET_ADC_CR_TRGINFO(Peri,Data)                 (void)Peri
#define SET_ADC_CR_ARST(Peri,Data)                    SET_BIT(Peri,Data,ADC,MR,ARST)
#define SET_ADC_CR_PCLKINV(Peri,Data)                 (void)Peri
#define SET_ADC_CR_CMP_EN(Peri,Id,Data)               SET_BIT_OFFSET(Peri,(Id*4),Data,ADC,CMPR1,CMPEN)
#define SET_ADC_CR_CMP_TRG(Peri,Id,Data)              SET_BIT_OFFSET(Peri,(Id*4),Data,ADC,CMPR1,CMPM)
#define SET_ADC_CR_CMP_CH(Peri,Id,Data)               SET_BIT_OFFSET(Peri,(Id*4),Data,ADC,CMPR1,CCH)
#define SET_ADC_DR_CMP(Peri,Id,Data)                  SET_BIT_OFFSET(Peri,(Id*4),Data,ADC,CMPR1,CVAL)
#define SET_ADC_DR_CMP_MATCH(Peri,Id,Data)            SET_BIT_OFFSET(Peri,(Id*4),Data,ADC,CMPR1,MATCH_CNT)
#define GET_ADC_CSTR_BASE_ADDR(Peri)                  GET_REG_ADDR(Peri,CSTR1)
#define SET_ADC_CSTR_SEQCH_SAMPLING(Addr,Seq,Data)    SET_BIT_ADDR_DATA_OFFSET(Addr,((Seq/4)*4),((Seq%4)*8),Data,ADC,CSTR1,ST0CH)

/* Interrupt Macro */
#define GET_ADC_IER_FLAG(Peri)                        GET_REG(Peri,SR)
#define SET_ADC_IER_FLAG(Peri,Data)                   SET_REG(Peri,Data,SR)
#define BIT_ADC_IER_SINGLE_FLAG                       (0x1UL << BIT_NAME_POS(ADC_,SR_,EOCIF_))
#define BIT_ADC_IER_SEQ_FLAG                          (0x1UL << BIT_NAME_POS(ADC_,SR_,EOSIF_))
#define BIT_ADC_IER_TRG_FLAG                          (0x1UL << BIT_NAME_POS(ADC_,SR_,TRGIF_))
#define SET_ADC_IER_SINGLE_EN(Peri,Data)              SET_BIT(Peri,Data,ADC,IER,EOCIE)
#define SET_ADC_IER_SEQ_EN(Peri,Data)                 SET_BIT(Peri,Data,ADC,IER,EOSIE)
#define SET_ADC_IER_TRG_EN(Peri,Data)                 SET_BIT(Peri,Data,ADC,IER,TRGIE)
#define SET_ADC_IER_DMA_EN(Peri,Data)                 SET_BIT(Peri,Data,ADC,IER,DMAIE)
#define SET_ADC_IER_SINGLE_FLAG(Peri,Data)            SET_BIT_FLAG(Peri,Data,ADC,SR,EOCIF)
#define GET_ADC_IER_SINGLE_FLAG(Peri)                 GET_BIT(Peri,ADC,SR,EOCIF)
#define SET_ADC_IER_SEQ_FLAG(Peri,Data)               SET_BIT_FLAG(Peri,Data,ADC,SR,EOSIF)
#define GET_ADC_IER_SEQ_FLAG(Peri)                    GET_BIT(Peri,ADC,SR,EOSIF)
#define SET_ADC_IER_TRG_FLAG(Peri,Data)               SET_BIT_FLAG(Peri,Data,ADC,SR,TRGIF)
#define GET_ADC_IER_TRG_FLAG(Peri)                    GET_BIT(Peri,ADC,SR,TRGIF)
#define SET_ADC_IER_DMAOVR_FLAG(Peri,Data)            SET_BIT_FLAG(Peri,Data,ADC,SR,DOVRUN)
#define GET_ADC_IER_DMAOVR_FLAG(Peri)                 GET_BIT(Peri,ADC,SR,DOVRUN)
#define SET_ADC_IER_DMA_FLAG(Peri,Data)               SET_BIT_FLAG(Peri,Data,ADC,SR,DMAIF)
#define BIT_ADC_IER_CMP_FLAG(Id)                      (0x1UL << (BIT_NAME_POS(ADC_,SR_,CMP0IF_)+Id))
#define SET_ADC_IER_CMP_EN(Peri,Id,Data)              SET_BIT_OFFSET(Peri,Id,Data,ADC,IER,CMP0IE)
#define GET_ADC_IER_CMP_FLAG(Peri,Id)                 GET_BIT_OFFSET(Peri,Id,ADC,SR,CMP0IF)
#define SET_ADC_IER_CMP_FLAG(Peri,Id,Data)            SET_BIT_OFFSET(Peri,Id,Data,ADC,SR,CMP0IF)

/* Unused Macro */
#define SET_ADC_CR_BUF_DLY_EN(Peri,Data)              (void)Peri
#define SET_ADC_CR_BUF_DLY_SEL(Peri,Data)             (void)Peri
#define SET_ADC_CR_BUF_DLY_BYPASS(Peri,Data)          (void)Peri
#define SET_ADC_CR_REF(Peri,Data)                     (void)Peri

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_ADC_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PER2,ADC0)
#define SET_SCU_ADC_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PCER2,ADC0)

#define SET_SCU_ADC_MCCR_SEL(Peri,Data)               SET_BIT(Peri,Data,SCU,MCCR4,ADCCSEL)
#define SET_SCU_ADC_MCCR_DIV(Peri,Data)               SET_BIT(Peri,Data,SCU,MCCR4,ADCCDIV)

#endif /* _HAL_ADC_V_01_00_05_H_ */
