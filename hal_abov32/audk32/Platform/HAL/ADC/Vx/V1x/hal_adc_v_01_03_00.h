/**
 *******************************************************************************
 * @file        hal_adc_v_01_01_00.h
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

#ifndef _HAL_ADC_V_01_03_00_H_
#define _HAL_ADC_V_01_03_00_H_

/* Feature(Function) Configuration Define */
#define ADC_FEATURE_COMPARATOR

/* Internal Macro */
#define ADC_REG_BASE                                  ADC_BASE
#define ADC_REG_OFFSET                                0x100
#define ADC_RESOLUTION                                4095
#define ADC_MAX_SEQUENCE                              8
#define ADC_SEQ_OFFSET                                4
#define ADC_SEQ_CH_OFFSET                             8
#define ADC_NO_TRG_SOURCE                             11
#define ADC_MODE_SEL(x)                               (x < 2 ? 0 : x-1)
#define ADC_TRG_SRC(x)                                (x == 0 ? 0 : \
                                                      (x < 5) ? 1 : \
                                                      (x == 5) ? 2 : \
                                                      (x == 6) ? 3 : ADC_NO_TRG_SOURCE)
#define ADC_SEQTRG_SRC(x,y)                           (x == 1 ? y : \
                                                      (x == 5) ? y : \
                                                      (x == 6) ? y : 15)
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
#define SET_ADC_CR_CH_SAMPLING0(Peri,Data,Offset)     SET_BIT_OFFSET(Peri,Offset,Data,ADC,CSTR1,ST0CH)
#define SET_ADC_CR_CH_SAMPLING1(Peri,Data,Offset)     SET_BIT_OFFSET(Peri,Offset,Data,ADC,CSTR2,ST4CH)
#define SET_ADC_CR_CH_SEL0(Peri,Data,Offset)          SET_BIT_OFFSET(Peri,Offset,Data,ADC,SCSR1,SEQ0CH)
#define SET_ADC_CR_CH_SEL1(Peri,Data,Offset)          SET_BIT_OFFSET(Peri,Offset,Data,ADC,SCSR2,SEQ4CH)
#define SET_ADC_CR_MODE(Peri,Data)                    SET_BIT(Peri,Data,ADC,MR,ADMOD)
#define SET_ADC_CR_TRG_SRC(Peri,Data)                 SET_BIT(Peri,Data,ADC,MR,TRGSEL)
#define SET_ADC_CR_SEQTRG_SRC(Peri,Data,Offset)       SET_BIT_OFFSET(Peri,Offset,Data,ADC,TRG,SEQTRG0_BSTTRG)
#define SET_ADC_CR_TRGTYPE(Peri,Data)                 SET_BIT(Peri,Data,ADC,MR,SEQTRGT)
#define GET_ADC_DR_OUT(Addr)                          GET_BIT_ADDR(Addr,ADC,DR0,ADDATA)
#define SET_ADC_CR_CDATA(Peri,Data)                   SET_BIT(Peri,Data,ADC,MR,CDATA)
#define SET_ADC_CR_SEQCNT(Peri,Data)                  SET_BIT(Peri,Data,ADC,MR,SEQCNT)
#define SET_ADC_DR_PREDIV(Peri,Data)                  SET_BIT(Peri,Data,ADC,CCR,CLKDIV)
#define SET_ADC_CR_DMA_INJ(Peri,Data)                 SET_BIT(Peri,Data,ADC,MR,DMAIDE)
#define SET_ADC_CR_DMA_EN(Peri,Data)                  SET_BIT(Peri,Data,ADC,MR,DMAEN)
#define SET_ADC_CR_CSEQN(Peri,Data)                   SET_BIT(Peri,Data,ADC,CSCR,CSEQN)
#define SET_ADC_CR_CHINFO(Peri,Data)                  SET_BIT(Peri,Data,ADC,MR,CHINFO)
#define SET_ADC_CR_TRGINFO(Peri,Data)                 SET_BIT(Peri,Data,ADC,MR,TRGINFO)
#define SET_ADC_CR_ARST(Peri,Data)                    SET_BIT(Peri,Data,ADC,MR,ARST)
#define SET_ADC_CR_CMP0_MATCHCNT(Peri,Data)           SET_BIT(Peri,Data,ADC,CMP0R,MATCH_CNT)
#define SET_ADC_CR_CMP0_IRQEN(Peri,Data)              SET_BIT(Peri,Data,ADC,CMP0R,COMPIEN)
#define SET_ADC_CR_CMP0_EN(Peri,Data)                 SET_BIT(Peri,Data,ADC,CMP0R,CMPEN)
#define SET_ADC_CR_CMP0_TRG(Peri,Data)                SET_BIT(Peri,Data,ADC,CMP0R,CMPM)
#define SET_ADC_CR_CMP0_CH(Peri,Data)                 SET_BIT(Peri,Data,ADC,CMP0R,CCH)
#define SET_ADC_DR_CMP0(Peri,Data)                    SET_BIT(Peri,Data,ADC,CMP0R,CVAL)
#define SET_ADC_CR_CMP1_MATCHCNT(Peri,Data)           SET_BIT(Peri,Data,ADC,CMP1R,MATCH_CNT)
#define SET_ADC_CR_CMP1_IRQEN(Peri,Data)              SET_BIT(Peri,Data,ADC,CMP1R,COMPIEN)
#define SET_ADC_CR_CMP1_EN(Peri,Data)                 SET_BIT(Peri,Data,ADC,CMP1R,CMPEN)
#define SET_ADC_CR_CMP1_TRG(Peri,Data)                SET_BIT(Peri,Data,ADC,CMP1R,CMPM)
#define SET_ADC_CR_CMP1_CH(Peri,Data)                 SET_BIT(Peri,Data,ADC,CMP1R,CCH)
#define SET_ADC_DR_CMP1(Peri,Data)                    SET_BIT(Peri,Data,ADC,CMP1R,CVAL)
#define SET_ADC_CR_INJ_MODE(Peri,Data)								SET_BIT(Peri,Data,ADC,IMR,INJECTMODE)
#define SET_ADC_CR_INJ_TRGSEL(Peri,Data)							SET_BIT(Peri,Data,ADC,IMR,TRGSEL)
#define SET_ADC_CR_INJ_CHSEL(Peri,Data)								SET_BIT(Peri,Data,ADC,IMR,CHSEL)
#define SET_ADC_CR_INJ_CST(Peri,Data)							  	SET_BIT(Peri,Data,ADC,IMR,CST)
#define SET_ADC_CR_INJ_TRGSRC(Peri,Data)						  SET_BIT(Peri,Data,ADC,IMR,TRGSRC)
#define SET_ADC_CR_INJ_START(Peri,Data)					   	  SET_BIT(Peri,Data,ADC,IMR,ASTART)
#define SET_ADC_DR_INJ_DATA(Peri,Data)					   	  SET_BIT(Peri,Data,ADC,IMR,ADDATA)
#define SET_ADC_DR_INJ_CH(Peri,Data)					   	    SET_BIT(Peri,Data,ADC,IMR,ACH)



/* Interrupt Macro */
#define GET_ADC_IER_FLAG(Peri)                        GET_REG(Peri,SR)
#define SET_ADC_IER_FLAG(Peri,Data)                   SET_REG(Peri,Data,SR)
#define BIT_ADC_IER_SINGLE_FLAG                       (0x1UL << BIT_NAME_POS(ADC_,SR_,EOCIF_))
#define BIT_ADC_IER_SEQ_FLAG                          (0x1UL << BIT_NAME_POS(ADC_,SR_,EOSIF_))
#define BIT_ADC_IER_TRG_FLAG                          (0x1UL << BIT_NAME_POS(ADC_,SR_,TRGIF_))
#define SET_ADC_IER_SINGLE_EN(Peri,Data)              SET_BIT(Peri,Data,ADC,IER,EOCIE)
#define SET_ADC_IER_INJ_EN(Peri,Data)                 SET_BIT(Peri,Data,ADC,IER,IOCIE)
#define SET_ADC_IER_SEQ_EN(Peri,Data)                 SET_BIT(Peri,Data,ADC,IER,EOSIE)
#define SET_ADC_IER_TRG_EN(Peri,Data)                 SET_BIT(Peri,Data,ADC,IER,TRGIE)
#define SET_ADC_IER_DMA_EN(Peri,Data)                 SET_BIT(Peri,Data,ADC,IER,DMAIE)
#define SET_ADC_IER_CMP0_EN(Peri,Data)                SET_BIT(Peri,Data,ADC,IER,CMP0IE)
#define SET_ADC_IER_CMP1_EN(Peri,Data)                SET_BIT(Peri,Data,ADC,IER,CMP1IE)
#define SET_ADC_IER_SINGLE_FLAG(Peri,Data)            SET_BIT_FLAG(Peri,Data,ADC,SR,EOCIF)
#define GET_ADC_IER_SINGLE_FLAG(Peri)                 GET_BIT(Peri,ADC,SR,EOCIF)
#define SET_ADC_IER_INJ_FLAG(Peri,Data)               SET_BIT_FLAG(Peri,Data,ADC,SR,IOCIF)
#define GET_ADC_IER_INJ_FLAG(Peri)                    GET_BIT(Peri,ADC,SR,IOCIF)
#define SET_ADC_IER_SEQ_FLAG(Peri,Data)               SET_BIT_FLAG(Peri,Data,ADC,SR,EOSIF)
#define GET_ADC_IER_SEQ_FLAG(Peri)                    GET_BIT(Peri,ADC,SR,EOSIF)
#define SET_ADC_IER_TRG_FLAG(Peri,Data)               SET_BIT_FLAG(Peri,Data,ADC,SR,TRGIF)
#define GET_ADC_IER_TRG_FLAG(Peri)                    GET_BIT(Peri,ADC,SR,TRGIF)
#define SET_ADC_IER_DMAOVR_FLAG(Peri,Data)            SET_BIT_FLAG(Peri,Data,ADC,SR,DOVRUN)
#define GET_ADC_IER_DMAOVR_FLAG(Peri)                 GET_BIT(Peri,ADC,SR,DOVRUN)
#define SET_ADC_IER_DMA_FLAG(Peri,Data)               SET_BIT_FLAG(Peri,Data,ADC,SR,DMAF)
#define GET_ADC_IER_DMA_FLAG(Peri)                    GET_BIT(Peri,ADC,SR,DMAF)
#define BIT_ADC_IER_CMP_FLAG(Id)                      (0x1UL << BIT_NAME_POS(ADC_,SR_,CMP0IF_))
#define GET_ADC_IER_CMP0_FLAG(Peri)                   GET_BIT(Peri,ADC,SR,CMP0IF)
#define SET_ADC_IER_CMP0_FLAG(Peri,Data)              SET_BIT_FLAG(Peri,Data,ADC,SR,CMP0IF)
#define GET_ADC_IER_CMP1_FLAG(Peri)                   GET_BIT(Peri,ADC,SR,CMP1IF)
#define SET_ADC_IER_CMP1_FLAG(Peri,Data)              SET_BIT_FLAG(Peri,Data,ADC,SR,CMP1IF)
#define GET_ADC_IER_BUSY_FLAG(Peri)                   GET_BIT(Peri,ADC,SR,ABUSY)
#define SET_ADC_IER_BUSY_FLAG(Peri,Data)              SET_BIT_FLAG(Peri,Data,ADC,SR,ABUSY)

/* Unused Macro */
#define SET_ADC_CR_REF(Peri,Data)                     (void)Peri
#define SET_ADC_CR_BUF_DLY_EN(Peri,Data)              (void)Peri
#define SET_ADC_CR_BUF_DLY_SEL(Peri,Data)             (void)Peri
#define SET_ADC_CR_BUF_DLY_BYPASS(Peri,Data)          (void)Peri

/* SCU Register Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_ADC_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PER2,ADC)
#define SET_SCU_ADC_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PCER2,ADC)
#define SET_SCU_ADC_MCCR_SEL(Peri,Data)               SET_BIT(Peri,Data,SCU,MCCR4,ADCCSEL)
#define SET_SCU_ADC_MCCR_DIV(Peri,Data)               SET_BIT(Peri,Data,SCU,MCCR4,ADCCDIV)

#endif /* _HAL_ADC_V_01_01_00_H_ */
