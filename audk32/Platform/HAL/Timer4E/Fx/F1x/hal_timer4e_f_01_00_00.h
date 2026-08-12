/**
 *******************************************************************************
 * @file        hal_timer4e_f_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed timer4e
 *
 * Copyright 2024 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_TIMER4E_F_01_00_00_H_
#define _HAL_TIMER4E_F_01_00_00_H_

/* Feature(Function) Configuration Define */
#define TIMER4E_FEATURE_IRQ_UNMASK_ENABLE

/* Internal Macro */
typedef TIMER4n_Type                                   TIMER4E_Type;
#define TIMER4E_REG_BASE                               TIMER40_BASE
#define TIMER4E_REG_OFFSET                             0x80
#define TIMER4E_REG_OFFSET_CNT                         0
#define TIMER4E_CLK_SRC_INT                            0x00
#define TIMER4E_CLK_SRC_EXT                            0x01
#define TIMER4E_POLARITY_LOW                           0x01
#define TIMER4E_POLARITY_HIGH                          0x00
#define TIMER4E_ONLY_PWM_PERIOD                        1
#define TIMER4E_PRESCALE_MAX                           4096
#define TIMER4E_OUTCR_WTIDKY                           0xE06CUL
#define TIMER4E_OUTCR_WTIDKY_POS                       16
#define TIMER4E_OUTCR_EN_LVL_MSK                       0x3FFF
#define TIMER4E_OUTCR_EN_POS                           0x08
#define TIMER4E_OUTCR_EN_MSK                           0x3F
#define TIMER4E_OUTCR_LVL_MSK                          0x77

#define TIMER4E_INTR_FLAG_MA                           0x01
#define TIMER4E_INTR_FLAG_MB                           0x02
#define TIMER4E_INTR_FLAG_PM                           0x10
#define TIMER4E_INTR_FLAG_BT                           0x20
#define TIMER4E_INTR_FLAG_CA                           0x40
#define TIMER4E_INTR_FLAG_OF                           0x80

/* Position & Mask Macro */
#define SET_TIMER4E_CR_MODE_POS(Data)                  SET_POS(Data,TIMER4n,CR,T4nMS)
#define SET_TIMER4E_CR_DLYEN_POS(Data)                 SET_POS(Data,TIMER4n,CR,DLYEN)
#define SET_TIMER4E_CR_DLYPOS_POS(Data)                SET_POS(Data,TIMER4n,CR,DLYPOS)
#define SET_TIMER4E_CR_CAPPORT_POS(Data)               SET_POS(Data,TIMER4n,CR,T4nINPOL)
#define SET_TIMER4E_CR_RELOAD_POS(Data)                SET_POS(Data,TIMER4n,CR,UPDT)
#define TIMER4E_CR_MODE_MSK                            BIT_NAME_MSK(TIMER4n_,CR_,T4nMS_)
#define TIMER4E_CR_DLYEN_MSK                           BIT_NAME_MSK(TIMER4n_,CR_,DLYEN_)
#define TIMER4E_CR_DLYPOS_MSK                          BIT_NAME_MSK(TIMER4n_,CR_,DLYPOS_)
#define TIMER4E_CR_CAPPORT_MSK                         BIT_NAME_MSK(TIMER4n_,CR_,T4nINPOL_)
#define TIMER4E_CR_RELOAD_MSK                          BIT_NAME_MSK(TIMER4n_,CR_,UPDT_)

/* Bit/Register Macro */
#define SET_TIMER4E_PREDR(Peri,Data)                   SET_REG(Peri,Data,PREDR)
#define GET_TIMER4E_PREDR(Peri)                        GET_REG(Peri,PREDR)
#define SET_TIMER4E_DR_P(Peri,Data)                    SET_REG(Peri,Data,PDR)
#define GET_TIMER4E_DR_P(Peri)                         GET_REG(Peri,PDR)
#define SET_TIMER4E_DR_A(Peri,Data)                    SET_REG(Peri,Data,ADR)
#define GET_TIMER4E_DR_A(Peri)                         GET_REG(Peri,ADR)
#define SET_TIMER4E_DR_B(Peri,Data)                    SET_REG(Peri,Data,BDR)
#define GET_TIMER4E_DR_B(Peri)                         GET_REG(Peri,BDR)
#define GET_TIMER4E_DR_CAP(Peri)                       GET_REG(Peri,CAPDR)
#define SET_TIMER4E_CR(Peri,Data)                      SET_REG(Peri,Data,CR)
#define GET_TIMER4E_CR(Peri)                           GET_REG(Peri,CR)
#define SET_TIMER4E_IER(Peri,Data)                     SET_REG(Peri,Data,INTCR)
#define GET_TIMER4E_IER_FLAG(Peri)                     GET_REG(Peri,INTFLAG)
#define SET_TIMER4E_IER_FLAG(Peri,Data)                SET_REG(Peri,Data,INTFLAG)
#define SET_TIMER4E_ADCTRG(Peri,Data)                  SET_REG(Peri,Data,ADTCR)
#define SET_TIMER4E_OUTCR(Peri,Data)                   SET_REG(Peri,Data,OUTCR)
#define GET_TIMER4E_OUTCR(Peri)                        GET_REG(Peri,OUTCR)
#define CLEAR_TIMER4E_CR(Peri)                         SET_REG(Peri,0,CR)
#define SET_TIMER4E_CR_MODE(Peri,Data)                 SET_BIT(Peri,Data,TIMER4n,CR,T4nMS)
#define GET_TIMER4E_CR_MODE(Peri)                      GET_BIT(Peri,TIMER4n,CR,T4nMS)
#define SET_TIMER4E_CR_EN(Peri,Data)                   SET_BIT(Peri,Data,TIMER4n,CR,T4nEN)
#define GET_TIMER4E_CR_EN(Peri)                        GET_BIT(Peri,TIMER4n,CR,T4nEN)
#define SET_TIMER4E_CR_A_PORT_OUTSTART_POL(Peri,Data)  SET_BIT(Peri,Data,TIMER4n,OUTCR,POLA)
#define SET_TIMER4E_CR_A_PORT_OUTDEF_POL(Peri,Data)    SET_BIT(Peri,Data,TIMER4n,OUTCR,LVLA)
#define SET_TIMER4E_CR_A_PORT_OUTEN(Peri,Data)         SET_BIT(Peri,Data,TIMER4n,OUTCR,T4nAOE)
#define SET_TIMER4E_CR_B_PORT_OUTSTART_POL(Peri,Data)  SET_BIT(Peri,Data,TIMER4n,OUTCR,POLB)
#define SET_TIMER4E_CR_B_PORT_OUTDEF_POL(Peri,Data)    SET_BIT(Peri,Data,TIMER4n,OUTCR,LVLB)
#define SET_TIMER4E_CR_B_PORT_OUTEN(Peri,Data)         SET_BIT(Peri,Data,TIMER4n,OUTCR,T4nBOE)
#define SET_TIMER4E_CR_CAPPORT_POL(Peri,Data)          SET_BIT(Peri,Data,TIMER4n,CR,T4nINPOL)
#define GET_TIMER4E_CR_CAPPORT_POL(Peri)               GET_BIT(Peri,TIMER4n,CR,T4nINPOL)
#define SET_TIMER4E_CR_CLK(Peri,Data)                  SET_BIT(Peri,Data,TIMER4n,CR,T4nCLK)
#define GET_TIMER4E_CR_CLK(Peri)                       GET_BIT(Peri,TIMER4n,CR,T4nCLK)
#define SET_TIMER4E_CR_CLR(Peri,Data)                  SET_BIT(Peri,Data,TIMER4n,CR,T4nCLR)
#define GET_TIMER4E_CR_CLR(Peri)                       GET_BIT(Peri,TIMER4n,CR,T4nCLR)
#define SET_TIMER4E_CR_EXTCLK_EDGE(Peri,Data)          SET_BIT(Peri,Data,TIMER4n,CR,T4nECE)
#define SET_TIMER4E_CR_OUTPUT_DLY(Peri,Data)           SET_BIT(Peri,Data,TIMER4n,CR,DLYEN)
#define SET_TIMER4E_CR_OUTPUT_DLY_POS(Peri,Data)       SET_BIT(Peri,Data,TIMER4n,CR,DLYPOS)
#define SET_TIMER4E_CR_OUTPUT_DLY_VALUE(Peri,Data)     SET_BIT(Peri,Data,TIMER4n,DLY,DLY)
#define SET_TIMER4E_CR_PERIOD_MATCH_CNT(Peri,Data)     SET_BIT(Peri,Data,TIMER4n,CR,DLYPOS)
#define SET_TIMER4E_CR_RELOAD(Peri,Data)               SET_BIT(Peri,Data,TIMER4n,CR,UPDT)
#define SET_TIMER4E_CR_SYNCNT_EN(Peri,Data)            SET_BIT(Peri,Data,TIMER4n,CR,CNTSHEN)
#define SET_TIMER4E_CR_SYNCNT_ID(Peri,Data)            SET_BIT(Peri,Data,TIMER4n,CR,CNTSH)
#define SET_TIMER4E_CR_FRC_EN(Peri,Data)               SET_BIT(Peri,Data,TIMER4n,CR,T4nFRCEN)
#define SET_TIMER4E_CR_FRC_ID(Peri,Data)               SET_BIT(Peri,Data,TIMER4n,CR,T4nFRCS)

/* Interrup Bit Macro */
#define SET_TIMER4E_IER_MATCH_A_EN(Peri,Data)          SET_BIT(Peri,Data,TIMER4n,INTCR,T4nAMIEN)
#define GET_TIMER4E_IER_MATCH_A_EN(Peri)               GET_BIT(Peri,TIMER4n,INTCR,T4nAMIEN)
#define SET_TIMER4E_IER_MATCH_B_EN(Peri,Data)          SET_BIT(Peri,Data,TIMER4n,INTCR,T4nBMIEN)
#define GET_TIMER4E_IER_MATCH_B_EN(Peri)               GET_BIT(Peri,TIMER4n,INTCR,T4nBMIEN)
#define SET_TIMER4E_IER_MATCH_P_EN(Peri,Data)          SET_BIT(Peri,Data,TIMER4n,INTCR,T4nPMIEN)
#define GET_TIMER4E_IER_MATCH_P_EN(Peri)               GET_BIT(Peri,TIMER4n,INTCR,T4nPMIEN)
#define SET_TIMER4E_IER_BOTTOM_EN(Peri,Data)           SET_BIT(Peri,Data,TIMER4n,INTCR,T4nBTIEN)
#define GET_TIMER4E_IER_BOTTOM_EN(Peri)                GET_BIT(Peri,TIMER4n,INTCR,T4nBTIEN)
#define SET_TIMER4E_IER_CAP_EN(Peri,Data)              SET_BIT(Peri,Data,TIMER4n,INTCR,T4nCIEN)
#define GET_TIMER4E_IER_CAP_EN(Peri)                   GET_BIT(Peri,TIMER4n,INTCR,T4nCIEN)
#define SET_TIMER4E_IER_FRC_EN(Peri,Data)              SET_BIT(Peri,Data,TIMER4n,INTCR,T4nFRCIEN)
#define GET_TIMER4E_IER_FRC_EN(Peri)                   GET_BIT(Peri,TIMER4n,INTCR,T4nFRCIEN)

#define SET_TIMER4E_IER_MATCH_A_FLAG(Peri,Data)        SET_BIT(Peri,Data,TIMER4n,INTFLAG,T4nAMIFLAG)
#define GET_TIMER4E_IER_MATCH_A_FLAG(Peri)             GET_BIT(Peri,TIMER4n,INTFLAG,T4nAMIFLAG)
#define SET_TIMER4E_IER_MATCH_B_FLAG(Peri,Data)        SET_BIT(Peri,Data,TIMER4n,INTFLAG,T4nBMIFLAG)
#define GET_TIMER4E_IER_MATCH_B_FLAG(Peri)             GET_BIT(Peri,TIMER4n,INTFLAG,T4nBMIFLAG)
#define SET_TIMER4E_IER_MATCH_C_FLAG(Peri,Data)        SET_BIT(Peri,Data,TIMER4n,INTFLAG,T4nCMIFLAG)
#define GET_TIMER4E_IER_MATCH_C_FLAG(Peri)             GET_BIT(Peri,TIMER4n,INTFLAG,T4nCMIFLAG)
#define SET_TIMER4E_IER_MATCH_P_FLAG(Peri,Data)        SET_BIT(Peri,Data,TIMER4n,INTFLAG,T4nPMIFLAG)
#define GET_TIMER4E_IER_MATCH_P_FLAG(Peri)             GET_BIT(Peri,TIMER4n,INTFLAG,T4nPMIFLAG)
#define SET_TIMER4E_IER_BOTTOM_FLAG(Peri,Data)         SET_BIT(Peri,Data,TIMER4n,INTFLAG,T4nBTIFLAG)
#define GET_TIMER4E_IER_BOTTOM_FLAG(Peri)              GET_BIT(Peri,TIMER4n,INTFLAG,T4nBTIFLAG)
#define SET_TIMER4E_IER_CAP_FLAG(Peri,Data)            SET_BIT(Peri,Data,TIMER4n,INTFLAG,T4nCIFLAG)
#define GET_TIMER4E_IER_CAP_FLAG(Peri)                 GET_BIT(Peri,TIMER4n,INTFLAG,T4nCIFLAG)
#define SET_TIMER4E_IER_FRC_FLAG(Peri,Data)            SET_BIT(Peri,Data,TIMER4n,INTFLAG,T4nFRCIFLAG)
#define GET_TIMER4E_IER_FRC_FLAG(Peri)                 GET_BIT(Peri,TIMER4n,INTFLAG,T4nFRCIFLAG)

/* Unused Macro */
               
/* SCU Macro */
typedef SCUCG_Type                                     SCU_Type;
#define SCU_ADDR                                       SCUCG_BASE
#define SET_SCU_TIMER4E_PER(Peri,Id,Data)              (void)Peri
#define SET_SCU_TIMER4E_PPCLKSR_CLK0(Peri,Data)        (void)Peri
#define SET_SCU_TIMER4E_PCER(Peri,Id,Data)             SET_BIT_ID(Peri,Id,Data,SCUCG,PPCLKEN1,T40CLKE)
#define SET_INTC_IRQ_UNMASK_EN(Peri,Irq,Data)          SET_BIT_ID(Peri,Irq,Data,INTC,MSK,IMSK0_LVI)

#endif /* _HAL_TIMER4E_F_01_00_00_H_ */
