/**
 *******************************************************************************
 * @file        hal_led_v_01_01_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.01.00 typed LED
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_LED_V_01_01_00_H_
#define _HAL_LED_V_01_01_00_H_

/* Feature(Function) Configuration Define */

/* Internal Macro */
#define LED_REG_BASE                                  LED_BASE
#define LED_DIMM_OFFSET                               4
#define LED_DIMM_DATA_WIDTH                           8
#define LED_DIMM_ADDR_OFFSET(x)                       ((x/LED_DIMM_OFFSET)*LED_DIMM_OFFSET)
#define LED_DIMM_DATA_OFFSET(x)                       ((x%LED_DIMM_OFFSET)*LED_DIMM_DATA_WIDTH)
#define LED_MODE(x)                                   (x == 4 ? 0 : \
                                                      (x == 0 ? 5 : x))

/* Bit/Register Macro */
#define GET_LED_COMOE_ADDR(Peri)                      GET_REG_ADDR(Peri,COMOE)
#define GET_LED_SEGOE_ADDR(Peri)                      GET_REG_ADDR(Peri,SEGOE)
#define GET_LED_COMER_ADDR(Peri)                      GET_REG_ADDR(Peri,COMER)
#define SET_LED_PRESD_PRESCALER(Peri,Data)            SET_BIT(Peri,Data,LED,PRESD,PRESD)
#define SET_LED_COMPWID_PULSEWIDTH(Peri,Data)         SET_BIT(Peri,Data,LED,COMPWID,COMPWID)
#define SET_LED_STPD_DURATION(Peri,Data)              SET_BIT(Peri,Data,LED,LEDPD,LEDPD)
#define SET_LED_CON2_COMSEG(Peri,Data)                SET_BIT(Peri,Data,LED,LEDCON2,COM_SEGN)
#define SET_LED_CON2_OVERLAP(Peri,Data)               SET_BIT(Peri,Data,LED,LEDCON2,OVERLAP)
#define SET_LED_CON2_OVERLAPTIME(Peri,Data)           SET_BIT(Peri,Data,LED,LEDCON2,OVERTS)
#define SET_LED_CON1_MODESEL(Peri,Data)               SET_BIT(Peri,Data,LED,LEDCON1,LED_MODE)
#define SET_LED_CON1_LEDEN(Peri,Data)                 SET_BIT(Peri,Data,LED,LEDCON1,LED_EN)
#define SET_LED_CON1_START(Peri,Data)                 SET_BIT(Peri,Data,LED,LEDCON1,LED_ST)
#define GET_LED_DIMMING_BASE_ADDR(Peri)               GET_REG_ADDR(Peri,COMDIMM0)
#define SET_LED_DR_DIMMING(Addr,Id,Data)              SET_BIT_ADDR_DATA_OFFSET(Addr,LED_DIMM_ADDR_OFFSET(Id),LED_DIMM_DATA_OFFSET(Id),Data,LED,COMDIMM0,COM0DIMM)
#define GET_LED_DISPRAM_BASE_ADDR(Peri)               GET_REG_ADDR(Peri,DISPRAM0)

/* Interrupt Macro */
#define SET_LED_INTR_MATCHF(Peri,Data)                SET_BIT(Peri,Data,LED,SR,MATCHF)
#define GET_LED_INTR_MATCHF(Peri)                     GET_BIT(Peri,LED,SR,MATCHF)
#define SET_LED_INTR_LEDINTR(Peri,Data)               SET_BIT(Peri,Data,LED,SR,LED_INTF)
#define GET_LED_INTR_LEDINTR(Peri)                    GET_BIT(Peri,LED,SR,LED_INTF)
#define SET_LED_INTR_LEDINTE(Peri,Data)               SET_BIT(Peri,Data,LED,SR,LED_INTE)
#define SET_LED_INTR_LEDENDF(Peri,Data)               SET_BIT(Peri,Data,LED,SR,LED_ENDF)
#define GET_LED_INTR_LEDENDF(Peri)                    GET_BIT(Peri,LED,SR,LED_ENDF)

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SCU_MCCR_MODE(x)                              (x == 0 ? x : x + 2)
#define SET_SCU_LED_PER(Peri,Id,Data)                 SET_BIT_ID(Peri,Id,Data,SCU,PER2,LED)
#define SET_SCU_LED_PCER(Peri,Id,Data)                SET_BIT_ID(Peri,Id,Data,SCU,PCER2,LED)
#define SET_SCU_LED_PPCLKSR(Peri,Data)                SET_BIT(Peri,Data,SCU,PPCLKSR,LEDCLK)
#define SET_SCU_LED_MCCR_SEL(Peri,Data)               SET_BIT(Peri,Data,SCU,MCCR5,LEDCSEL)
#define SET_SCU_LED_MCCR_DIV(Peri,Data)               SET_BIT(Peri,Data,SCU,MCCR5,LEDDIV)

#endif /* _HAL_LED_V_01_01_00_H_ */
