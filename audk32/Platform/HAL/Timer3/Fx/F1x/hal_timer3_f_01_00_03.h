/**
 *******************************************************************************
 * @file        hal_timer3_f_01_00_03.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.03 typed timer3
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER3_F_01_00_03_H_
#define _HAL_TIMER3_F_01_00_03_H_

/* Feature(Function) Configuration Define */
#define TIMER3_FEATURE_ONLY_MAIN_CLOCK
#define TIMER3_FEATURE_IRQ_UNMASK_ENABLE

/* Internal Macro */
typedef TIMER3n_Type                                  TIMER3_Type;
#define TIMER3_REG_BASE                               TIMER30_BASE
#define TIMER3_REG_OFFSET                             0x100
#define TIMER3_REG_OFFSET_CNT                         0
#define TIMER3_CLK_SRC_INT                            0x00
#define TIMER3_CLK_SRC_EXT                            0x01
#define TIMER3_CLK_MCCR_SRC_LSI                       0x00
#define TIMER3_CLK_MCCR_SRC_LSE                       0x03
#define TIMER3_CLK_MCCR_SRC_MCLK                      0x04
#define TIMER3_CLK_MCCR_SRC_HSI                       0x05
#define TIMER3_CLK_MCCR_SRC_HSE                       0x06
#define TIMER3_CLK_MCCR_SRC_PLL                       0x07
#define TIMER3_POLARITY_LOW                           0x01
#define TIMER3_POLARITY_HIGH                          0x00
#define TIMER3_ONLY_PWM_PERIOD                        1
#define TIMER3_PRESCALE_MAX                           4096
#define TIMER3_OUTCR_WTIDKY                           0xE06CUL
#define TIMER3_OUTCR_WTIDKY_POS                       16
#define TIMER3_OUTCR_EN_LVL_MSK                       0x3FFF
#define TIMER3_OUTCR_EN_POS                           0x08
#define TIMER3_OUTCR_EN_MSK                           0x3F
#define TIMER3_OUTCR_LVL_MSK                          0x77

/* Position & Mask Macro */
#define SET_TIMER3_CR_MODE_POS(Data)                  SET_POS(Data,TIMER3n,CR,T3nMS)
#define SET_TIMER3_CR_FORCA_POS(Data)                 SET_POS(Data,TIMER3n,CR,FORCA)
#define SET_TIMER3_CR_DLYEN_POS(Data)                 SET_POS(Data,TIMER3n,CR,DLYEN)
#define SET_TIMER3_CR_DLYPOS_POS(Data)                SET_POS(Data,TIMER3n,CR,DLYPOS)
#define SET_TIMER3_CR_CAPPORT_POS(Data)               SET_POS(Data,TIMER3n,CR,T3nCPOL)
#define SET_TIMER3_CR_RELOAD_POS(Data)                SET_POS(Data,TIMER3n,CR,UPDT)
#define SET_TIMER3_CR_PMOC_POS(Data)                  SET_POS(Data,TIMER3n,CR,PMOC)
#define TIMER3_CR_MODE_MSK                            BIT_NAME_MSK(TIMER30_,CR_,T3nMS_)
#define TIMER3_CR_FORCA_MSK                           BIT_NAME_MSK(TIMER30_,CR_,FORCA_)
#define TIMER3_CR_DLYEN_MSK                           BIT_NAME_MSK(TIMER30_,CR_,DLYEN_)
#define TIMER3_CR_DLYPOS_MSK                          BIT_NAME_MSK(TIMER30_,CR_,DLYPOS_)
#define TIMER3_CR_CAPPORT_MSK                         BIT_NAME_MSK(TIMER30_,CR_,T3nCPOL_)
#define TIMER3_CR_RELOAD_MSK                          BIT_NAME_MSK(TIMER30_,CR_,UPDT_)
#define TIMER3_CR_PMOC_MSK                            BIT_NAME_MSK(TIMER30_,CR_,PMOC_)

/* Bit/Register Macro */
#define SET_TIMER3_PREDR(Peri,Data)                   SET_REG(Peri,Data,PREDR)
#define GET_TIMER3_PREDR(Peri)                        GET_REG(Peri,PREDR)
#define SET_TIMER3_DR_P(Peri,Data)                    SET_REG(Peri,Data,PDR)
#define GET_TIMER3_DR_P(Peri)                         GET_REG(Peri,PDR)
#define SET_TIMER3_DR_A(Peri,Data)                    SET_REG(Peri,Data,ADR)
#define GET_TIMER3_DR_A(Peri)                         GET_REG(Peri,ADR)
#define SET_TIMER3_DR_B(Peri,Data)                    SET_REG(Peri,Data,BDR)
#define GET_TIMER3_DR_B(Peri)                         GET_REG(Peri,BDR)
#define SET_TIMER3_DR_C(Peri,Data)                    SET_REG(Peri,Data,CDR)
#define GET_TIMER3_DR_C(Peri)                         GET_REG(Peri,CDR)
#define GET_TIMER3_DR_CAP(Peri)                       GET_REG(Peri,CAPDR)
#define SET_TIMER3_DR_ADC(Peri,Data)                  SET_REG(Peri,Data,ADTDR)
#define GET_TIMER3_DR_ADC(Peri)                       GET_REG(Peri,ADTDR)
#define SET_TIMER3_CR(Peri,Data)                      SET_REG(Peri,Data,CR)
#define GET_TIMER3_CR(Peri)                           GET_REG(Peri,CR)
#define SET_TIMER3_IER(Peri,Data)                     SET_REG(Peri,Data,INTCR)
#define GET_TIMER3_IER_FLAG(Peri)                     GET_REG(Peri,INTFLAG)
#define SET_TIMER3_IER_FLAG(Peri,Data)                SET_REG(Peri,Data,INTFLAG)
#define SET_TIMER3_ADCTRG(Peri,Data)                  SET_REG(Peri,Data,ADTCR)
#define SET_TIMER3_OUTCR(Peri,Data)                   SET_REG(Peri,Data,OUTCR)
#define GET_TIMER3_OUTCR(Peri)                        GET_REG(Peri,OUTCR)
#define SET_TIMER3_CR_MODE(Peri,Data)                 SET_BIT(Peri,Data,TIMER3n,CR,T3nMS)
#define GET_TIMER3_CR_MODE(Peri)                      GET_BIT(Peri,TIMER3n,CR,T3nMS)
#define SET_TIMER3_CR_EN(Peri,Data)                   SET_BIT(Peri,Data,TIMER3n,CR,T3nEN)
#define GET_TIMER3_CR_EN(Peri)                        GET_BIT(Peri,TIMER3n,CR,T3nEN)
#define SET_TIMER3_CR_XA_PORT_POL(Peri,Data)          SET_BIT_KEY(Peri,TIMER3_OUTCR_WTIDKY,Data,TIMER3n,OUTCR,POLA)
#define SET_TIMER3_CR_XB_PORT_POL(Peri,Data)          SET_BIT_KEY(Peri,TIMER3_OUTCR_WTIDKY,Data,TIMER3n,OUTCR,POLB)
#define SET_TIMER3_CR_CAPPORT_POL(Peri,Data)          SET_BIT(Peri,Data,TIMER3n,CR,T3nCPOL)
#define GET_TIMER3_CR_CAPPORT_POL(Peri)               GET_BIT(Peri,TIMER3n,CR,T3nCPOL)
#define SET_TIMER3_CR_CLK(Peri,Data)                  SET_BIT(Peri,Data,TIMER3n,CR,T3nCLK)
#define GET_TIMER3_CR_CLK(Peri)                       GET_BIT(Peri,TIMER3n,CR,T3nCLK)
#define SET_TIMER3_CR_CLR(Peri,Data)                  SET_BIT(Peri,Data,TIMER3n,CR,T3nCLR)
#define GET_TIMER3_CR_CLR(Peri)                       GET_BIT(Peri,TIMER3n,CR,T3nCLR)
#define SET_TIMER3_CR_EXTCLK_EDGE(Peri,Data)          SET_BIT(Peri,Data,TIMER3n,CR,T3nECE)
#define SET_TIMER3_CR_HIZ_EN(Peri,Data)               SET_BIT(Peri,Data,TIMER3n,HIZCR,HIZEN)
#define SET_TIMER3_CR_HIZ_EDGE(Peri,Data)             SET_BIT(Peri,Data,TIMER3n,HIZCR,HEDGE)
#define SET_TIMER3_CR_OUTPUT_MODE(Peri,Data)          SET_BIT(Peri,Data,TIMER3n,CR,FORCA)
#define SET_TIMER3_CR_OUTPUT_DLY(Peri,Data)           SET_BIT(Peri,Data,TIMER3n,CR,DLYEN)
#define SET_TIMER3_CR_OUTPUT_DLY_POS(Peri,Data)       SET_BIT(Peri,Data,TIMER3n,CR,DLYPOS)
#define SET_TIMER3_CR_OUTPUT_DLY_VALUE(Peri,Data)     SET_BIT(Peri,Data,TIMER3n,DLY,DLY)
#define SET_TIMER3_CR_PERIOD_MATCH_CNT(Peri,Data)     SET_BIT(Peri,Data,TIMER3n,CR,PMOC)
#define SET_TIMER3_CR_RELOAD(Peri,Data)               SET_BIT(Peri,Data,TIMER3n,CR,UPDT)
#define CLEAR_TIMER3_CR(Peri)                         SET_REG(Peri,0,CR)

/* Interrup Bit Macro */
#define SET_TIMER3_IER_MATCH_A_EN(Peri,Data)          SET_BIT(Peri,Data,TIMER3n,INTCR,T3nAMIEN)
#define GET_TIMER3_IER_MATCH_A_EN(Peri)               GET_BIT(Peri,TIMER3n,INTCR,T3nAMIEN)
#define SET_TIMER3_IER_MATCH_B_EN(Peri,Data)          SET_BIT(Peri,Data,TIMER3n,INTCR,T3nBMIEN)
#define GET_TIMER3_IER_MATCH_B_EN(Peri)               GET_BIT(Peri,TIMER3n,INTCR,T3nBMIEN)
#define SET_TIMER3_IER_MATCH_C_EN(Peri,Data)          SET_BIT(Peri,Data,TIMER3n,INTCR,T3nCMIEN)
#define GET_TIMER3_IER_MATCH_C_EN(Peri)               GET_BIT(Peri,TIMER3n,INTCR,T3nCMIEN)
#define SET_TIMER3_IER_MATCH_P_EN(Peri,Data)          SET_BIT(Peri,Data,TIMER3n,INTCR,T3nPMIEN)
#define GET_TIMER3_IER_MATCH_P_EN(Peri)               GET_BIT(Peri,TIMER3n,INTCR,T3nPMIEN)
#define SET_TIMER3_IER_BOTTOM_EN(Peri,Data)           SET_BIT(Peri,Data,TIMER3n,INTCR,T3nBTIEN)
#define GET_TIMER3_IER_BOTTOM_EN(Peri)                GET_BIT(Peri,TIMER3n,INTCR,T3nBTIEN)
#define SET_TIMER3_IER_CAP_EN(Peri,Data)              SET_BIT(Peri,Data,TIMER3n,INTCR,T3nCIEN)
#define GET_TIMER3_IER_CAP_EN(Peri)                   GET_BIT(Peri,TIMER3n,INTCR,T3nCIEN)
#define SET_TIMER3_IER_HIZ_EN(Peri,Data)              SET_BIT(Peri,Data,TIMER3n,INTCR,HIZIEN)
#define GET_TIMER3_IER_HIZ_EN(Peri)                   GET_BIT(Peri,TIMER3n,INTCR,HIZIEN)
#define SET_TIMER3_IER_MATCH_A_FLAG(Peri,Data)        SET_BIT(Peri,Data,TIMER3n,INTFLAG,T3nAMIFLAG)
#define GET_TIMER3_IER_MATCH_A_FLAG(Peri)             GET_BIT(Peri,TIMER3n,INTFLAG,T3nAMIFLAG)
#define SET_TIMER3_IER_MATCH_B_FLAG(Peri,Data)        SET_BIT(Peri,Data,TIMER3n,INTFLAG,T3nBMIFLAG)
#define GET_TIMER3_IER_MATCH_B_FLAG(Peri)             GET_BIT(Peri,TIMER3n,INTFLAG,T3nBMIFLAG)
#define SET_TIMER3_IER_MATCH_C_FLAG(Peri,Data)        SET_BIT(Peri,Data,TIMER3n,INTFLAG,T3nCMIFLAG)
#define GET_TIMER3_IER_MATCH_C_FLAG(Peri)             GET_BIT(Peri,TIMER3n,INTFLAG,T3nCMIFLAG)
#define SET_TIMER3_IER_MATCH_P_FLAG(Peri,Data)        SET_BIT(Peri,Data,TIMER3n,INTFLAG,T3nPMIFLAG)
#define GET_TIMER3_IER_MATCH_P_FLAG(Peri)             GET_BIT(Peri,TIMER3n,INTFLAG,T3nPMIFLAG)
#define SET_TIMER3_IER_BOTTOM_FLAG(Peri,Data)         SET_BIT(Peri,Data,TIMER3n,INTFLAG,T3nBTIFLAG)
#define GET_TIMER3_IER_BOTTOM_FLAG(Peri)              GET_BIT(Peri,TIMER3n,INTFLAG,T3nBTIFLAG)
#define SET_TIMER3_IER_CAP_FLAG(Peri,Data)            SET_BIT(Peri,Data,TIMER3n,INTFLAG,T3nCIFLAG)
#define GET_TIMER3_IER_CAP_FLAG(Peri)                 GET_BIT(Peri,TIMER3n,INTFLAG,T3nCIFLAG)
#define SET_TIMER3_IER_HIZ_FLAG(Peri,Data)            SET_BIT(Peri,Data,TIMER3n,INTFLAG,HIZIFLAG)
#define GET_TIMER3_IER_HIZ_FLAG(Peri)                 GET_BIT(Peri,TIMER3n,INTFLAG,HIZIFLAG)
#define SET_TIMER3_IER_CLR(Peri) \
                                                      SET_TIMER3_IER_MATCH_A_FLAG(Peri,0x01); \
                                                      SET_TIMER3_IER_CAP_FLAG(Peri,0x01)

/* Unused Macro */
#define SET_TIMER3_CR_HIZ_SRC(Peri,Data)              (void)Peri

/* SCU Macro */
typedef SCUCG_Type                                    SCU_Type;
#define SCU_ADDR                                      SCUCG_BASE
#define SET_SCU_TIMER3_PER(Peri,Id,Data)              (void)Peri
#define SET_SCU_TIMER3_PCER(Peri,Id,Data)             SET_BIT_ID(Peri,Id,Data,SCUCG,PPCLKEN1,T30CLKE)
#define SET_SCU_TIMER3_PPCLKSR_CLK0(Peri,Data)        SET_BIT(Peri,Data,SCUCG,PPCLKSR,T30CLK)
#define SET_INTC_IRQ_UNMASK_EN(Peri,Irq,Data)         SET_BIT_ID(Peri,Irq,Data,INTC,MSK,IMSK0_LVI)

#endif /* _HAL_TIMER3_F_01_00_03_H_ */
