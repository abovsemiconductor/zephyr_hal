/**
 *******************************************************************************
 * @file        hal_usb_v_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed USB
 *
 * Copyright 2025 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_USB_V_01_00_00_H_
#define _HAL_USB_V_01_00_00_H_

/* Feature(Function) Configuration Define */
#define USB_FEATURE_USE_MCCR_CLOCK
#define USB_FEATURE_FIFO_4BYTE_ALIGN
#define USB_FEATURE_NMI

/* Internal Macro */
#define USB_REG_BASE                                  USB_BASE
#define USB_REG_OFFSET                                0x100

#define USB_FULL_PULLUP                               0x01
#define USB_FULL_PULLDOWN                             0x00

#define USB_FIFO_ADDR_OFFSET                          0x10

#define USB_EP0_INTR_MASK                             0x01
#define USB_EP1_5_INTR_MASK                           0x1E

#define SET_USB_FADDR(Peri,Data)                      SET_REG(Peri,Data,FADDR)
#define SET_USB_POWER(Peri,Data)                      SET_REG(Peri,Data,POWER)
#define SET_USB_INDEX(Peri,Data)                      SET_REG(Peri,Data,INDEX)
#define SET_USB_INMAXP(Peri,Data)                     SET_REG(Peri,Data,INMAXP)
#define SET_USB_OUTMAXP(Peri,Data)                    SET_REG(Peri,Data,OUTMAXP)
#define GET_USB_SR(Peri)                              GET_REG(Peri,INTRUSB)
#define SET_USB_SUSPEND_EN(Peri,Data)                 SET_BIT(Peri,Data,USB,PHYCR,PHYSUSP_MODE)

#define SET_USB_EP0_SR0(Peri,Data)                    SET_REG(Peri,Data,CSR0_INCSR1)
#define GET_USB_EP0_SR0(Peri)                         GET_REG(Peri,CSR0_INCSR1)
#define SET_USB_EPX_OUTSR1(Peri,Data)                 SET_REG(Peri,Data,OUTCSR1)
#define GET_USB_EPX_OUTSR1(Peri)                      GET_REG(Peri,OUTCSR1)
#define SET_USB_EPX_OUTSR2(Peri,Data)                 SET_REG(Peri,Data,OUTCSR2)
#define GET_USB_EPX_OUTSR2(Peri)                      GET_REG(Peri,OUTCSR2)
#define SET_USB_EP0_FIFO(Peri,Data)                   SET_REG(Peri,Data,EP0_FIFO0)
#define GET_USB_EP0_FIFO(Peri)                        GET_REG(Peri,EP0_FIFO0)

#define SET_USB_EP0_PULLUP(Peri,Data)                 SET_REG(Peri,Data,PUPDCR)
#define SET_USB_EP0_SR0_SENTSTALL(Peri,Data)          SET_BIT(Peri,Data,USB,CSR0_INCSR1,SENTSTALL_UNDERRUN)
#define SET_USB_EP0_SR0_SENDSTALL(Peri,Data)          SET_BIT(Peri,Data,USB,CSR0_INCSR1,SENDSTALL_SENTSTALL)
#define SET_USB_EP0_SR0_SETUPEND(Peri,Data)           SET_BIT(Peri,Data,USB,CSR0_INCSR1,SETUPEND_SENDSTALL)
#define SET_USB_EP0_SR0_SRVSETUPEND(Peri,Data)        SET_BIT(Peri,Data,USB,CSR0_INCSR1,SERVICEDSETUPEND)
#define SET_USB_EP0_SR0_SRVOUTPKTRDY(Peri,Data)       SET_BIT(Peri,Data,USB,CSR0_INCSR1,SERVICEDOUTPKTRDY_CLRDATATOG)
#define SET_USB_EP0_SR0_INPKTRDY(Peri,Data)           SET_BIT(Peri,Data,USB,CSR0_INCSR1,INPKTRDY_FIFONOTEMPTY)
#define SET_USB_EP0_SR0_DATAEND(Peri,Data)            SET_BIT(Peri,Data,USB,CSR0_INCSR1,DATAEND_FLUSHFIFO)
#define GET_USB_EP0_RX_CNT(Peri)                      GET_REG(Peri,COUNT0_OUTCOUNT1)
#define GET_USB_EP0_RX_CNT1(Peri)                     GET_REG(Peri,OUTCOUNT2)
#define SET_USB_EP0_SR0_OUTPKTRDY(Peri,Data)          SET_BIT(Peri,Data,USB,CSR0_INCSR1,OUTPKTRDY_INPKTRDY)

#define SET_USB_EPX_CR_IN_ISO(Peri,Data)              SET_BIT(Peri,Data,USB,INCSR2,ISO)
#define SET_USB_EPX_CR_DIR(Peri,Data)                 SET_BIT(Peri,Data,USB,INCSR2,MODE)

#define SET_USB_EPX_CR_OUT_ISO(Peri,Data)             SET_BIT(Peri,Data,USB,OUTCSR2,ISO)
#define GET_USB_EPX_FIFO_BASE_ADDR(Peri)              GET_REG_ADDR(Peri,FIFO_EP0)

/* Interrupt Macro */
#define SET_USB_IER(Peri,Data)                        SET_REG(Peri,Data,INTRUSBE)
#define SET_USB_IER_SR(Peri,Data)                     SET_REG(Peri,Data,INTRUSB)
#define GET_USB_IER_SR(Peri)                          GET_REG(Peri,INTRUSB)
#define SET_USB_IER_RESET_EN(Peri,Data)               SET_BIT(Peri,Data,USB,INTRUSBE,RESETIEN)
#define GET_USB_IER_INEP_SR(Peri)                     GET_REG(Peri,INTRIN1)
#define GET_USB_IER_OUTEP_SR(Peri)                    GET_REG(Peri,INTROUT1)
#define SET_USB_IER_OUTEP_EN(Peri,Data)               SET_REG(Peri,Data,INTROUT1E)
#define GET_USB_IER_OUTEP_EN(Peri)                    GET_REG(Peri,INTROUT1E)
#define SET_USB_IER_INEP0_EN(Peri,Data)               SET_BIT(Peri,Data,USB,INTRIN1E,EP0IEN)

/* SCU Macro */
#define SCU_ADDR                                      SCU_BASE
#define SCU_USB_MCCR_MODE(x)                          (x < 2 ? x : x + 2)
#define SET_SCU_USB_PER(Peri,Id,Data)                 SET_BIT(Peri,Data,SCU,PER2,USB)
#define SET_SCU_USB_PCER(Peri,Id,Data)                SET_BIT(Peri,Data,SCU,PCER2,USB)
#define SET_SCU_USB_MCCR_SEL0(Peri,Data)              SET_BIT(Peri,Data,SCU,MCCR6,USBCSEL)
#define SET_SCU_USB_MCCR_DIV0(Peri,Data)              SET_BIT(Peri,Data,SCU,MCCR6,USBCDIV)


#define SET_SCU_USB_RST_CLR(Peri,Data)                (void)Peri
#define SET_SCU_USB_RST_EN(Peri,Data)                 (void)Peri
#endif /* _HAL_USB_V_01_00_00_H_ */
