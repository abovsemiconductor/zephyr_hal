/**
 *******************************************************************************
 * @file        hal_timer3_f_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed timer3
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER3_F_01_00_00_H_
#define _HAL_TIMER3_F_01_00_00_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
typedef TIMER30_Type                                  TIMER3_Type;
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
#define TIMER3_PRESCALE_MAX                           1024
#define TIMER3_OUTCR_WTIDKY                           0xE06CUL
#define TIMER3_OUTCR_WTIDKY_POS                       16
#define TIMER3_OUTCR_EN_LVL_MSK                       0x3FFF
#define TIMER3_OUTCR_EN_POS                           0x08
#define TIMER3_OUTCR_EN_MSK                           0x3F
#define TIMER3_OUTCR_LVL_MSK                          0x77

/* Position & Mask Macro */
#define SET_TIMER3_CR_MODE_POS(Data)                  SET_POS(Data,TIMER30,CR,T30MS)
#define SET_TIMER3_CR_FORCA_POS(Data)                 SET_POS(Data,TIMER30,CR,FORCA)
#define SET_TIMER3_CR_DLYEN_POS(Data)                 SET_POS(Data,TIMER30,CR,DLYEN)
#define SET_TIMER3_CR_DLYPOS_POS(Data)                SET_POS(Data,TIMER30,CR,DLYPOS)
#define SET_TIMER3_CR_CAPPORT_POS(Data)               SET_POS(Data,TIMER30,CR,T30CPOL)
#define SET_TIMER3_CR_RELOAD_POS(Data)                SET_POS(Data,TIMER30,CR,UPDT)
#define SET_TIMER3_CR_PMOC_POS(Data)                  SET_POS(Data,TIMER30,CR,PMOC)
#define TIMER3_CR_MODE_MSK                            BIT_NAME_MSK(TIMER30_,CR_,T30MS_)
#define TIMER3_CR_FORCA_MSK                           BIT_NAME_MSK(TIMER30_,CR_,FORCA_)
#define TIMER3_CR_DLYEN_MSK                           BIT_NAME_MSK(TIMER30_,CR_,DLYEN_)
#define TIMER3_CR_DLYPOS_MSK                          BIT_NAME_MSK(TIMER30_,CR_,DLYPOS_)
#define TIMER3_CR_CAPPORT_MSK                         BIT_NAME_MSK(TIMER30_,CR_,CPOL_)
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
#define CLEAR_TIMER3_CR(Peri)                         SET_REG(Peri,0,CR)
#define SET_TIMER3_CR_MODE(Peri,Data)                 SET_BIT(Peri,Data,TIMER30,CR,T30MS)
#define GET_TIMER3_CR_MODE(Peri)                      GET_BIT(Peri,TIMER30,CR,T30MS)
#define SET_TIMER3_CR_EN(Peri,Data)                   SET_BIT(Peri,Data,TIMER30,CR,T30EN)
#define GET_TIMER3_CR_EN(Peri)                        GET_BIT(Peri,TIMER30,CR,T30EN)
#define SET_TIMER3_CR_XA_PORT_POL(Peri,Data)          SET_BIT_KEY(Peri,TIMER3_OUTCR_WTIDKY,Data,TIMER30,OUTCR,POLA)
#define SET_TIMER3_CR_XB_PORT_POL(Peri,Data)          SET_BIT_KEY(Peri,TIMER3_OUTCR_WTIDKY,Data,TIMER30,OUTCR,POLB)
#define SET_TIMER3_CR_CAPPORT_POL(Peri,Data)          SET_BIT(Peri,Data,TIMER30,CR,T30CPOL)
#define GET_TIMER3_CR_CAPPORT_POL(Peri)               GET_BIT(Peri,TIMER30,CR,T30CPOL)
#define SET_TIMER3_CR_CLK(Peri,Data)                  SET_BIT(Peri,Data,TIMER30,CR,T30CLK)
#define GET_TIMER3_CR_CLK(Peri)                       GET_BIT(Peri,TIMER30,CR,T30CLK)
#define SET_TIMER3_CR_CLR(Peri,Data)                  SET_BIT(Peri,Data,TIMER30,CR,T30CLR)
#define GET_TIMER3_CR_CLR(Peri)                       GET_BIT(Peri,TIMER30,CR,T30CLR)
#define SET_TIMER3_CR_EXTCLK_EDGE(Peri,Data)          SET_BIT(Peri,Data,TIMER30,CR,T30ECE)
#define SET_TIMER3_CR_HIZ_EN(Peri,Data)               SET_BIT(Peri,Data,TIMER30,HIZCR,HIZEN)
#define SET_TIMER3_CR_HIZ_EDGE(Peri,Data)             SET_BIT(Peri,Data,TIMER30,HIZCR,HEDGE)
#define SET_TIMER3_CR_OUTPUT_MODE(Peri,Data)          SET_BIT(Peri,Data,TIMER30,CR,FORCA)
#define SET_TIMER3_CR_OUTPUT_DLY(Peri,Data)           SET_BIT(Peri,Data,TIMER30,CR,DLYEN)
#define SET_TIMER3_CR_OUTPUT_DLY_POS(Peri,Data)       SET_BIT(Peri,Data,TIMER30,CR,DLYPOS)
#define SET_TIMER3_CR_OUTPUT_DLY_VALUE(Peri,Data)     SET_BIT(Peri,Data,TIMER30,DLY,DLY)
#define SET_TIMER3_CR_PERIOD_MATCH_CNT(Peri,Data)     SET_BIT(Peri,Data,TIMER30,CR,PMOC)
#define SET_TIMER3_CR_RELOAD(Peri,Data)               SET_BIT(Peri,Data,TIMER30,CR,UPDT)

/* Interrup Bit Macro */
#define SET_TIMER3_IER_MATCH_A_EN(Peri,Data)          SET_BIT(Peri,Data,TIMER30,INTCR,T30AMIEN)
#define GET_TIMER3_IER_MATCH_A_EN(Peri)               GET_BIT(Peri,TIMER30,INTCR,T30AMIEN)
#define SET_TIMER3_IER_MATCH_B_EN(Peri,Data)          SET_BIT(Peri,Data,TIMER30,INTCR,T30BMIEN)
#define GET_TIMER3_IER_MATCH_B_EN(Peri)               GET_BIT(Peri,TIMER30,INTCR,T30BMIEN)
#define SET_TIMER3_IER_MATCH_C_EN(Peri,Data)          SET_BIT(Peri,Data,TIMER30,INTCR,T30CMIEN)
#define GET_TIMER3_IER_MATCH_C_EN(Peri)               GET_BIT(Peri,TIMER30,INTCR,T30CMIEN)
#define SET_TIMER3_IER_MATCH_P_EN(Peri,Data)          SET_BIT(Peri,Data,TIMER30,INTCR,T30PMIEN)
#define GET_TIMER3_IER_MATCH_P_EN(Peri)               GET_BIT(Peri,TIMER30,INTCR,T30PMIEN)
#define SET_TIMER3_IER_BOTTOM_EN(Peri,Data)           SET_BIT(Peri,Data,TIMER30,INTCR,T30BTIEN)
#define GET_TIMER3_IER_BOTTOM_EN(Peri)                GET_BIT(Peri,TIMER30,INTCR,T30BTIEN)
#define SET_TIMER3_IER_CAP_EN(Peri,Data)              SET_BIT(Peri,Data,TIMER30,INTCR,T30CIEN)
#define GET_TIMER3_IER_CAP_EN(Peri)                   GET_BIT(Peri,TIMER30,INTCR,T30CIEN)
#define SET_TIMER3_IER_HIZ_EN(Peri,Data)              SET_BIT(Peri,Data,TIMER30,INTCR,HIZIEN)
#define GET_TIMER3_IER_HIZ_EN(Peri)                   GET_BIT(Peri,TIMER30,INTCR,HIZIEN)

#define SET_TIMER3_IER_MATCH_A_FLAG(Peri,Data)        SET_BIT(Peri,Data,TIMER30,INTFLAG,T30AMIFLAG)
#define GET_TIMER3_IER_MATCH_A_FLAG(Peri)             GET_BIT(Peri,TIMER30,INTFLAG,T30AMIFLAG)
#define SET_TIMER3_IER_MATCH_B_FLAG(Peri,Data)        SET_BIT(Peri,Data,TIMER30,INTFLAG,T30BMIFLAG)
#define GET_TIMER3_IER_MATCH_B_FLAG(Peri)             GET_BIT(Peri,TIMER30,INTFLAG,T30BMIFLAG)
#define SET_TIMER3_IER_MATCH_C_FLAG(Peri,Data)        SET_BIT(Peri,Data,TIMER30,INTFLAG,T30CMIFLAG)
#define GET_TIMER3_IER_MATCH_C_FLAG(Peri)             GET_BIT(Peri,TIMER30,INTFLAG,T30CMIFLAG)
#define SET_TIMER3_IER_MATCH_P_FLAG(Peri,Data)        SET_BIT(Peri,Data,TIMER30,INTFLAG,T30PMIFLAG)
#define GET_TIMER3_IER_MATCH_P_FLAG(Peri)             GET_BIT(Peri,TIMER30,INTFLAG,T30PMIFLAG)
#define SET_TIMER3_IER_BOTTOM_FLAG(Peri,Data)         SET_BIT(Peri,Data,TIMER30,INTFLAG,T30BTIFLAG)
#define GET_TIMER3_IER_BOTTOM_FLAG(Peri)              GET_BIT(Peri,TIMER30,INTFLAG,T30BTIFLAG)
#define SET_TIMER3_IER_CAP_FLAG(Peri,Data)            SET_BIT(Peri,Data,TIMER30,INTFLAG,T30CIFLAG)
#define GET_TIMER3_IER_CAP_FLAG(Peri)                 GET_BIT(Peri,TIMER30,INTFLAG,T30CIFLAG)
#define SET_TIMER3_IER_HIZ_FLAG(Peri,Data)            SET_BIT(Peri,Data,TIMER30,INTFLAG,HIZIFLAG)
#define GET_TIMER3_IER_HIZ_FLAG(Peri)                 GET_BIT(Peri,TIMER30,INTFLAG,HIZIFLAG)
#define SET_TIMER3_IER_CLR(Peri) \
                                                      SET_TIMER3_IER_MATCH_A_FLAG(Peri,0x01); \
                                                      SET_TIMER3_IER_CAP_FLAG(Peri,0x01)

/* Unused Macro */
#define SET_TIMER3_CR_HIZ_SRC(Peri,Data)              (void)Peri
               
/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SET_SCU_TIMER3_MCCR_SEL0(Peri,Data)           SET_BIT(Peri,Data,SCU,MCCR2,TEXT3CSEL)
#define SET_SCU_TIMER3_MCCR_DIV0(Peri,Data)           SET_BIT(Peri,Data,SCU,MCCR2,TEXT3DIV)
#define SET_SCU_TIMER3_PPCLKSR_CLK0(Peri,Data)        SET_BIT(Peri,Data,SCU,PPCLKSR,T30CLK)
#define SET_SCU_TIMER3_PER(Peri,Id,Data)              SET_BIT_ID(Peri,Id,Data,SCU,PER1,TIMER30)
#define SET_SCU_TIMER3_PCER(Peri,Id,Data)             SET_BIT_ID(Peri,Id,Data,SCU,PCER1,TIMER30)

#endif /* _HAL_TIMER3_F_01_00_00_H_ */
