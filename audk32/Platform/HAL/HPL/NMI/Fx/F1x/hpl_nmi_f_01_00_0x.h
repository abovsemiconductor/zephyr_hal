/**
 *******************************************************************************
 * @file        hpl_nmi_f_01_00_0x.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.0x typed SCU NMI 
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HPL_NMI_F_01_00_0X_H_
#define _HPL_NMI_F_01_00_0X_H_

/* Internal Define */
typedef SCUCC_Type                                    SCU_Type;
#define SCU_REG_BASE                                  SCUCC_BASE

/* Bit/Register Macro */
#define SET_SCU_NMI_MCLK_IER_EN(Peri,Data)            SET_BIT(Peri,Data,SCUCC,NMISRCR,MONINT)
#define GET_SCU_NMI_STATUS(Peri)                      0; (void)Peri; 

#endif /* _HPL_NMI_F_01_00_0X_H_ */
