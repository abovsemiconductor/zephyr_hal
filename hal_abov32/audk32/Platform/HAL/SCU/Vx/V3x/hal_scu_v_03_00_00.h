/**
 *******************************************************************************
 * @file        hal_scu_v_03_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 03.00.00 typed SCU
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_SCU_V_03_00_00_H_
#define _HAL_SCU_V_03_00_00_H_

/* Feature(Function) Configuration Define */
#define SCU_FEATURE_PLL_PRE_KEY_VALUE
#define SCU_FEATURE_PERI_CLK_DIV
#define SCU_FEATURE_VX_PLL_BLOCK
#define SCU_FEATURE_SELECT_OUTPUT_CLK

/* Internal Macro */
typedef PMU_Type                                      SCU_Type;
typedef PMU_Type                                      SCULV_Type;
typedef PMU_Type                                      SCUCLK_Type;
typedef PMU_Type                                      SCUCONF_Type;
#define SCU_REG_BASE                                  PMU_BASE
#define SCULV_REG_BASE                                PMU_BASE
#define SCUCLK_REG_BASE                               PMU_BASE
#define SCUCONF_REG_BASE                              PMU_BASE

#define SCU_SOFTWARE_RST                              0x01

#define CLK_MON_NUM                                   CONFIG_SCU_CLK_MON_MAX_COUNT
#define SCUCLK_MCLK_IRQ                               SCUCLK_0_IRQ
#define SCUCLK_HSE_IRQ                                SCUCLK_1_IRQ
#define SCUCLK_LSE_IRQ                                SCUCLK_2_IRQ

#if defined(_SCU_LVD)
#define SCULVD_IRQ                                    SCULVD_0_IRQ
#endif

#define SCUCLK_EXPO2(x)                               (1 << x)
#define SCUCLK_EXT_HSE_FREQ(x)                        (~x & 0x3)
#define SCUCLK_EXT_HSE_CURR(x)                        (~x & 0x3)
#define SCUCLK_EXT_LSE_CURR(x)                        (x & 0x3)
#define SCUCLK_EXT_HSE_MSK                            0xFFFFFFC0
#define SCUCLK_EXT_LSE_MSK                            0xFFFF0FFF

#define SCUCLK_MCLKSEL_LSI                            0x00
#define SCUCLK_MCLKSEL_LSE                            0x01
#define SCUCLK_MCLKSEL_PLL                            0x02
#define SCUCLK_MCLKSEL_PLL_BYPASS                     0x03

#define SCULVD_RST_EN                                 0x01
#define SCULVD_RST_DIS                                0x00
#define SCULVD_RST_OP_MASTER                          0xFF 
#define SCULVD_RST_OP_LVREN                           0xAA 

#define SCU_PREVMODE_SLEEP                            0x01
#define SCU_PREVMODE_DEEPSLEEP                        0x02

#define SCUCLK_SRC_ENABLE_POS                         0x01
#define SCUCLK_SRC_MODE_MSK                           0x01

#define SCUCLK_FMC_CLK_WAIT_0                         38000000
#define SCUCLK_FMC_CLK_WAIT_1                         57000000
#define SCUCLK_FMC_CLK_WAIT_2                         75000000
#define SCUCLK_FMC_CLK_WAIT_3                         75000000

#define SCUCLK_OUTPUT_INCLK_PLL                       0x00
#define SCUCLK_OUTPUT_INCLK_MCLK                      0x01

#define SCUCLK_PLLCON_KEY_VALUE                       0x80750000

#define SCUCLK_AUTO_RECOVERY_OFF                      0x00
#define SCUCLK_AUTO_RECOVERY_ON                       0x01

#define SCUPWR_AON_VDC_EN
#define SCUPWR_AON_EXTCLK_EN

#define SCUCLK_HCLK(x)                                (x > 0 ? x + 1 : x)
#define SCUCLK_PCLK_DIV_MAX                           1 /* SCUCLK_DIV_e */

/* Bit/Register Macro */
#define SET_SCU_COR_CLKOEN(Peri,Data)                 SET_BIT(Peri,Data,PMU,COR,CLKOEN)
#define SET_SCU_COR_CLKODIV(Peri,Data)                SET_BIT(Peri,Data,PMU,COR,CLKODIV)
#define SET_SCU_COR_CLKOSEL(Peri,Data)                SET_BIT(Peri,Data,PMU,COR,CLKOSEL)
#define SET_SCU_CMR_MCLKMNT(Peri,Data)                SET_BIT(Peri,Data,PMU,MCMR,MCKMNT)
#define SET_SCU_CMR_MCLKIE(Peri,Data)                 SET_BIT(Peri,Data,PMU,MCMR,MCKIE)
#define SET_SCU_CMR_MCLKFAIL(Peri,Data)               SET_BIT(Peri,Data,PMU,MCMR,MCKIF)
#define GET_SCU_CMR_MCLKSTS(Peri)                     GET_BIT(Peri,PMU,MCMR,MCKSTS)
#define GET_SCU_CMR_MCLKFAIL(Peri)                    GET_BIT(Peri,PMU,MCMR,MCKIF)
#define SET_SCU_CMR_MCLKREC(Peri,Data)                SET_BIT(Peri,Data,PMU,MCMR,RECOVER) 
#define SET_SCU_PLLCON_OUTDIV(Peri,Data)              SET_BIT(Peri,Data,PMU,PLLCON,POSTDIV)
#define SET_SCU_PLLCON_PREDIV(Peri,Data)              SET_BIT(Peri,Data,PMU,PLLCON,PREDIV)
#define SET_SCU_PLLCON_PLLMODE(Peri,Data)             SET_BIT(Peri,Data,PMU,PLLCON,VCOMODE)
#define SET_SCU_PLLCON_PLLEN(Peri,Data)               SET_BIT(Peri,Data,PMU,PLLCON,PLLEN)
#define SET_SCU_PLLCON_BYPASS(Peri,Data)              SET_BIT(Peri,Data,PMU,PLLCON,BYPASS)
#define SET_SCU_PLLCON_RESET(Peri,Data)               SET_BIT(Peri,Data,PMU,PLLCON,PLLRESB)

#define SET_SCU_PLLCON_PLLEN_POS(Data)                SET_POS(Data,PMU,PLLCON,PLLEN)
#define SET_SCU_PLLCON_OUTDIV_POS(Data)               SET_POS(Data,PMU,PLLCON,POSTDIV)
#define SET_SCU_PLLCON_POSTDIV1_POS(Data)             SET_POS((Data & 0xFF),PMU,PLLCON,MULT)
#define SET_SCU_PLLCON_POSTDIV2_POS(Data)             SET_POS((Data & 0x03),PMU,PLLCON,DIV)
#define SET_SCU_PLLCON_PREDIV_POS(Data)               SET_POS((Data & 0x07),PMU,PLLCON,PREDIV)
#define SET_SCU_PLLCON_BYPASS_POS(Data)               SET_POS((Data & 0x01),PMU,PLLCON,BYPASS)
#define SET_SCU_PLLCON_RESET_POS(Data)                SET_POS((Data & 0x01),PMU,PLLCON,PLLRESB)
#define SET_SCU_PLLCON_PLLMODE_POS(Data)              SET_POS((Data & 0x01),PMU,PLLCON,VCOMODE)
#define SET_SCU_PLLCON(Peri,Data)                     SET_REG(Peri,Data,PLLCON)
#define GET_SCU_PLLCON(Peri)                          GET_REG(Peri,PLLCON)

#define SET_SCU_CSCR_HSI(Peri,Data)                   SET_BIT(Peri,Data,PMU,CCR,IOSC16EN)
#define SET_SCU_CSCR_LSI(Peri,Data)                   SET_BIT(Peri,Data,PMU,CCR,ROSCEN)
#define SET_SCU_CSCR_HSE(Peri,Data)                   SET_BIT(Peri,Data,PMU,CCR,MXOSCEN)
#define SET_SCU_CSCR_LSE(Peri,Data)                   SET_BIT(Peri,Data,PMU,CCR,SXOSCEN)

#define SET_SCU_CMR_HSEMNT(Peri,Data)                 SET_BIT(Peri,Data,PMU,CMR,MXOSCMNT)
#define SET_SCU_CMR_HSEIE(Peri,Data)                  SET_BIT(Peri,Data,PMU,CMR,MXOSCIE)
#define SET_SCU_CMR_HSEFAIL(Peri,Data)                SET_BIT(Peri,Data,PMU,CMR,MXOSCIF)
#define GET_SCU_CMR_HSEFAIL(Peri)                     GET_BIT(Peri,PMU,CMR,MXOSCIF)
#define GET_SCU_CMR_HSESTS(Peri)                      GET_BIT(Peri,PMU,CMR,MXOSCSTS)
#define SET_SCU_SCCR_MCLKSEL(Peri,Data)               SET_BIT(Peri,Data,PMU,BCCR,MCLKSEL)
#define SET_SCU_COR_CLKOINSEL(Peri,Data)              SET_BIT(Peri,Data,PMU,COR,CLKOSEL)
#define SET_SCU_SCCR_PLLCLKSEL(Peri,Data)             SET_BIT(Peri,Data,PMU,BCCR,PLLCLKSEL)
#define GET_SCU_PLLCON_LOCK(Peri)                     GET_BIT(Peri,PMU,PLLCON,LOCKSTS)
#define SET_SCU_SCCR_PCLKDIV(Peri,Data)               SET_BIT(Peri,Data,PMU,BCCR,PCLKDIV)
#define GET_SCU_SCCR_PCLKDIV(Peri)                    GET_BIT(Peri,PMU,BCCR,PCLKDIV)
#define SET_SCU_SCCR_HCLKDIV(Peri,Data)               SET_BIT(Peri,Data,PMU,BCCR,HCLKDIV)

#define SET_SCU_LVD_IND_SEL(Peri,Data)                SET_BIT(Peri,Data,PMU,LVDCON,LVDIL)
#define SET_SCU_LVD_IND_INTR_EN(Peri,Data)            SET_BIT(Peri,Data,PMU,LVDCON,LVDIEN)
#define SET_SCU_LVD_IND_INTR_FLAG(Peri,Data)          SET_BIT(Peri,Data,PMU,LVDCON,LVDIF)
#define SET_SCU_LVD_RST_SEL(Peri,Data)                SET_BIT(Peri,Data,PMU,LVDCON,LVDRL)
#define SET_SCU_LVD_RST_EN(Peri,Data)                 SET_BIT(Peri,Data,PMU,LVDCON,LVDREN)

#define SET_SCU_CLK_RST_SRC_HSE_EN(Peri,Data)         SET_BIT(Peri,Data,PMU,RSER,MXFAILRSTE)
#define GET_SCU_CLK_RST_SRC_HSE_EN(Peri)              GET_BIT(Peri,PMU,RSER,MXFAILRSTE)
#define SET_SCU_CLK_RST_SRC_HSE_FLAG(Peri,Data)       SET_BIT(Peri,Data,PMU,RSSR,MXFAILRST)
#define GET_SCU_CLK_RST_SRC_HSE_FLAG(Peri)            GET_BIT(Peri,PMU,RSSR,MXFAILRST)
#define SET_SCU_CLK_RST_SRC_MCLK_EN(Peri,Data)        SET_BIT(Peri,Data,PMU,RSER,MCLKFAILRSTE)
#define GET_SCU_CLK_RST_SRC_MCLK_EN(Peri)             GET_BIT(Peri,PMU,RSER,MCLKFAILRSTE)
#define SET_SCU_CLK_RST_SRC_MCLK_FLAG(Peri,Data)      SET_BIT(Peri,Data,PMU,RSSR,MCLKFAILRST)
#define GET_SCU_CLK_RST_SRC_MCLK_FLAG(Peri)           GET_BIT(Peri,PMU,RSSR,MCLKFAILRST)

#define GET_SCU_EOS(Peri)                             GET_REG(Peri,EOSCCON)
#define SET_SCU_EOS(Peri,Data)                        SET_REG(Peri,Data,EOSCCON)
#define SET_SCU_EOS_HSE(Peri,Data)                    SET_REG(Peri,(Data | 0xFF),EOSCCON)
#define BIT_SCU_EOS_HSENC_EN                          BIT_NAME_POS(PMU_,EOSCCON_,MOSCNFOFF_)
#define BIT_SCU_EOS_HSENC_DELAY                       BIT_NAME_POS(PMU_,EOSCCON_,MOSCNFSEL_)
#define BIT_SCU_EOS_HSE_CURR                          BIT_NAME_POS(PMU_,EOSCCON_,MOSCISEL_)
#define SET_SCU_EOS_LSE(Peri,Data)                    SET_REG(Peri,(Data | 0xFF00),EOSCCON)
#define BIT_SCU_EOS_LSENC_EN                          BIT_NAME_POS(PMU_,EOSCCON_,SOSCNFOFF_)
#define BIT_SCU_EOS_LSE_CURR                          BIT_NAME_POS(PMU_,EOSCCON_,SOSCISEL_)

#define SET_SCU_LVD_WKUP_EN(Peri,Data)                SET_BIT(Peri,Data,PMU,WSER,LVDE)
#define GET_SCU_LVD_WKUP_EN(Peri)                     GET_BIT(Peri,PMU,WSER,LVDE)
#define GET_SCU_LVD_WKUP_FLAG(Peri)                   GET_BIT(Peri,PMU,WSSR,LVD)
#define SET_SCU_LVD_RST_SRC_EN(Peri,Data)             SET_BIT(Peri,Data,PMU,RSER,LVDRSTE)
#define GET_SCU_LVD_RST_SRC_EN(Peri)                  GET_BIT(Peri,PMU,RSER,LVDRSTE)
#define SET_SCU_LVD_RST_SRC_FLAG(Peri,Data)           SET_BIT(Peri,Data,PMU,RSSR,LVDRST)
#define GET_SCU_LVD_RST_SRC_FLAG(Peri)                GET_BIT(Peri,PMU,RSSR,LVDRST)
#define GET_SCU_LVD_PREVMODE(Peri)                    GET_BIT(Peri,PMU,MR,PREVMODE)

#define SET_SCU_SRCR_SW_RST(Peri,Data)                SET_BIT(Peri,Data,PMU,CFG,SOFTRST)
#define SET_SCU_RSER_SW_EN(Peri,Data)                 SET_BIT(Peri,Data,PMU,RSER,SWRSTE)
#define GET_SCU_RSER_SW_EN(Peri)                      GET_BIT(Peri,PMU,RSER,SWRSTE)
#define SET_SCU_RSER_CPU_EN(Peri,Data)                SET_BIT(Peri,Data,PMU,RSER,SYSRSTE)
#define GET_SCU_RSER_CPU_EN(Peri)                     GET_BIT(Peri,PMU,RSER,SYSRSTE)
#define SET_SCU_RSER_EXTPIN_EN(Peri,Data)             SET_BIT(Peri,Data,PMU,RSER,RSTRSTE)
#define GET_SCU_RSER_EXTPIN_EN(Peri)                  GET_BIT(Peri,PMU,RSER,RSTRSTE)
#define SET_SCU_RSSR_SW_FLAG(Peri,Data)               SET_BIT(Peri,Data,PMU,RSSR,SWRST)
#define GET_SCU_RSSR_SW_FLAG(Peri)                    GET_BIT(Peri,PMU,RSSR,SWRST)
#define SET_SCU_RSSR_CPU_FLAG(Peri,Data)              SET_BIT(Peri,Data,PMU,RSSR,SYSRST)
#define GET_SCU_RSSR_CPU_FLAG(Peri)                   GET_BIT(Peri,PMU,RSSR,SYSRST)
#define SET_SCU_RSSR_EXTPIN_FLAG(Peri,Data)           SET_BIT(Peri,Data,PMU,RSSR,RSTRST)
#define GET_SCU_RSSR_EXTPIN_FLAG(Peri)                GET_BIT(Peri,PMU,RSSR,RSTRST)

#define BIT_SCU_SMR_VDC_POS                           BIT_NAME_POS(PMU_,MR_,VDCLP_)
#define BIT_SCU_SMR_EXTCLK_POS                        BIT_NAME_POS(PMU_,MR_,ECLKMD_)
#define SET_SCU_SMR(Peri,Data)                        SET_REG(Peri,Data,MR)

/* Unused Macro */
#define GET_SCU_CMR_LSEFAIL(Peri)                     0
#define SET_SCU_CMR_LSEMNT(Peri,Data)                 (void)Peri
#define SET_SCU_CMR_LSEIE(Peri,Data)                  (void)Peri
#define SET_SCU_CMR_LSEFAIL(Peri,Data)                (void)Peri
#define GET_SCU_CMR_LSESTS(Peri)                      0
#define GET_SCU_RSSR_POR_FLAG(Peri)                   0
#define SET_SCU_PLLCON_POSTDIV1(Peri,Data)            (void)Peri
#define SET_SCU_PLLCON_POSTDIV2(Peri,Data)            (void)Peri
#define SET_SCU_PLLCON_PLLICP(Peri,Data)              (void)Peri
#define SET_SCU_PLLCON_PLLVCOC(Peri,Data)             (void)Peri
#define SET_SCU_DATA_VDC_DELAY(Peri,Data)             (void)Peri
#define SET_SCU_VDC_DEEPSLEEP(Peri,Data)              (void)Peri
#define SET_SCU_LVD_RST_ENM(Peri,Data)                (void)Peri
#define SET_SCU_LVD_IND_EN(Peri,Data)                 (void)Peri
#define SET_SCU_CLK_RST_SRC_LSE_EN(Peri,Data)         (void)Peri
#define GET_SCU_CLK_RST_SRC_LSE_EN(Peri)              0
#define SET_SCU_CLK_RST_SRC_LSE_FLAG(Peri,Data)       (void)Peri
#define GET_SCU_CLK_RST_SRC_LSE_FLAG(Peri)            0

#define SCU_FMC_ADDR                                  FMC_BASE
#define SET_SCU_CFMC_LATENCY(Peri,Data)               SET_BIT(Peri,Data,FMC,CFG,CWAIT)
#define SET_SCU_DFMC_LATENCY(Peri,Data)               SET_BIT(Peri,Data,FMC,CFG,DWAIT)
#define SCU_FMC_DEFAULT_LATENCY                       3

#endif /* _HAL_SCH_V_03_00_00_H_ */
