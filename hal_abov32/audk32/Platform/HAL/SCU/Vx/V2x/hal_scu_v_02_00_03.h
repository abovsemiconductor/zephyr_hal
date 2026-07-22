/**
 *******************************************************************************
 * @file        hal_scu_v_02_00_03.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for v 02.00.03 typed SCU
 *
 * Copyright 2025 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_SCU_V_02_00_03_H_
#define _HAL_SCU_V_02_00_03_H_

/* Feature(Function) Configuration Define */
#define SCU_FEATURE_RST_CPU_LOCKUP
#define SCU_FEATURE_PERI_CLK_DIV
#define SCU_FEATURE_SELECT_OUTPUT_CLK
#define SCU_FEATURE_POWER_DOWN_PIN_LEVEL
#define SCU_FEATURE_PLL_CURRENT
#define SCU_FEATURE_VX_PLL_BLOCK
#define SCU_FEATURE_PLL_OUTPUT_FORMULA_V3

/* Internal Macro */
typedef SCU_Type                                      SCULV_Type;
typedef SCU_Type                                      SCUCLK_Type;
typedef SCU_Type                                      SCUCONF_Type;
#define SCU_REG_BASE                                  SCU_BASE
#define SCULV_REG_BASE                                SCU_BASE
#define SCUCLK_REG_BASE                               SCU_BASE
#define SCUCONF_REG_BASE                              SCU_BASE

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
#define SCUCLK_EXT_HSE_MSK                            0xFFFFFC00
#define SCUCLK_EXT_LSE_MSK                            0xFCFEFFFF

#define SCUCLK_OUTPUT_INCLK_HSE                       0x06
#define SCUCLK_OUTPUT_INCLK_HSI                       0x05
#define SCUCLK_OUTPUT_INCLK_LSE                       0x01
#define SCUCLK_OUTPUT_INCLK_LSI                       0x00
#define SCUCLK_OUTPUT_INCLK_PLL                       0x07
#define SCUCLK_OUTPUT_INCLK_MCLK                      0x04

#define SCUCLK_MCLKSEL_LSI                            0x00
#define SCUCLK_MCLKSEL_LSE                            0x01
#define SCUCLK_MCLKSEL_HSI                            0x02
#define SCUCLK_MCLKSEL_HSE                            0x06
#define SCUCLK_MCLKSEL_PLL                            0x07

#define SCUPWR_AON_VDC_EN
#define SCUPWR_AON_LSI_EN

#define SCULVD_RST_EN                                 0xFF
#define SCULVD_RST_DIS                                0x55
#define SCULVD_RST_OP_MASTER                          0xFF 
#define SCULVD_RST_OP_LVREN                           0xAA 

#define SCU_PREVMODE_SLEEP                            0x01
#define SCU_PREVMODE_DEEPSLEEP                        0x03

#define SCUCLK_SRC_ENABLE_POS                         0x00
#define SCUCLK_SRC_MODE_MSK                           0x00

#define SCUCLK_FMC_CLK_WAIT_0                         33000000
#define SCUCLK_FMC_CLK_WAIT_1                         66000000
#define SCUCLK_FMC_CLK_WAIT_2                         100000000
#define SCUCLK_FMC_CLK_WAIT_3                         133000000
#define SCUCLK_FMC_CLK_WAIT_4                         166000000
#define SCUCLK_FMC_CLK_WAIT_5                         200000000

#define SCUCLK_AUTO_RECOVERY_OFF                      0x01
#define SCUCLK_AUTO_RECOVERY_ON                       0x00

#define SCUCLK_PCLK_DIV_MAX                           4 /* SCUCLK_DIV_e */

/* Bit/Register Macro */
#define SET_SCU_COR_CLKOEN(Peri,Data)                 SET_BIT(Peri,Data,SCU,COR,CLKOEN)
#define SET_SCU_COR_CLKODIV(Peri,Data)                SET_BIT(Peri,(Data & 0xF),SCU,COR,CLKODIV)
#define SET_SCU_COR_CLKOSEL(Peri,Data)                SET_BIT(Peri,(Data & 0x7),SCU,COR,CLKOINSEL)
#define SET_SCU_CMR_MCLKMNT(Peri,Data)                SET_BIT(Peri,Data,SCU,CMR,MCLKMNT)
#define SET_SCU_CMR_MCLKIE(Peri,Data)                 SET_BIT(Peri,Data,SCU,CMR,MCLKIE)
#define SET_SCU_CMR_MCLKFAIL(Peri,Data)               SET_BIT(Peri,Data,SCU,CMR,MCLKFAIL)
#define GET_SCU_CMR_MCLKFAIL(Peri)                    GET_BIT(Peri,SCU,CMR,MCLKFAIL)
#define GET_SCU_CMR_MCLKSTS(Peri)                     GET_BIT(Peri,SCU,CMR,MCLKSTS)
#define SET_SCU_PLLCON_OUTDIV(Peri,Data)              SET_BIT(Peri,Data,SCU,PLLCON,POSTDIV)
#define SET_SCU_PLLCON_POSTDIV1(Peri,Data)            SET_BIT(Peri,Data,SCU,PLLCON,LOOPDIV)
#define SET_SCU_PLLCON_PREDIV(Peri,Data)              SET_BIT(Peri,Data,SCU,PLLCON,PREDIV)
#define SET_SCU_PLLCON_PLLEN(Peri,Data)               SET_BIT(Peri,Data,SCU,PLLCON,PLLEN)
#define SET_SCU_PLLCON_BYPASS(Peri,Data)              SET_BIT(Peri,Data,SCU,PLLCON,BYPASSB)
#define SET_SCU_PLLCON(Peri,Data)                     SET_REG(Peri,Data,PLLCON)
#define GET_SCU_PLLCON(Peri)                          GET_REG(Peri,PLLCON)
#define SET_SCU_PLLCON_PLLEN_POS(Data)                SET_POS(Data,SCU,PLLCON,PLLEN)
#define SET_SCU_PLLCON_OUTDIV_POS(Data)               SET_POS((Data & 0x0F),SCU,PLLCON,POSTDIV)
#define SET_SCU_PLLCON_POSTDIV1_POS(Data)             SET_POS((Data & 0xFF),SCU,PLLCON,LOOPDIV)
#define SET_SCU_PLLCON_PREDIV_POS(Data)               SET_POS((Data & 0x0F),SCU,PLLCON,PREDIV)
#define SET_SCU_PLLCON_BYPASS_POS(Data)               SET_POS(Data,SCU,PLLCON,BYPASSB)
#define SET_SCU_PLLCON_CUROPT_POS(Data)               ((Data & 0x3) << 26)
#define SET_SCU_PLLCON_VCOBIAS_POS(Data)              ((Data & 0x3) << 24)
#define SET_SCU_CSCR_HSI(Peri,Data)                   SET_BIT(Peri,Data,SCU,CSCR,HSICON)
#define SET_SCU_CSCR_LSI(Peri,Data)                   SET_BIT(Peri,Data,SCU,CSCR,LSICON)
#define SET_SCU_CSCR_HSE(Peri,Data)                   SET_BIT(Peri,Data,SCU,CSCR,HSECON)
#define SET_SCU_CMR_HSEMNT(Peri,Data)                 SET_BIT(Peri,Data,SCU,CMR,HSEMNT)
#define SET_SCU_CMR_HSEIE(Peri,Data)                  SET_BIT(Peri,Data,SCU,CMR,HSEIE)
#define SET_SCU_CMR_HSEFAIL(Peri,Data)                SET_BIT(Peri,Data,SCU,CMR,HSEFAIL)
#define GET_SCU_CMR_HSEFAIL(Peri)                     GET_BIT(Peri,SCU,CMR,HSEFAIL)
#define GET_SCU_CMR_HSESTS(Peri)                      GET_BIT(Peri,SCU,CMR,HSESTS)
#define SET_SCU_SCCR_MCLKSEL(Peri,Data)               SET_BIT(Peri,Data,SCU,SCCR,MCLKSEL)
#define SET_SCU_COR_CLKOINSEL(Peri,Data)              SET_BIT(Peri,Data,SCU,COR,CLKOINSEL)
#define SET_SCU_SCCR_PLLCLKSEL(Peri,Data)             SET_BIT(Peri,Data,SCU,SCCR,PLLCLKSEL)
#define GET_SCU_PLLCON_LOCK(Peri)                     GET_BIT(Peri,SCU,PLLCON,PLLLOCK)
#define SET_SCU_SCCR_PLLPREDIV(Peri,Data)             SET_BIT(Peri,Data,SCU,SCCR,PLLPREDIV)
#define SET_SCU_PLLCON_PLLICP(Peri,Data)              SET_BIT(Peri,Data,SCU,PLLCON,PLLICP)
#define SET_SCU_PLLCON_PLLVCOC(Peri,Data)             SET_BIT(Peri,Data,SCU,PLLCON,PLLVCOC)
#define SET_SCU_SCCR_HCLKDIV(Peri,Data)               SET_BIT(Peri,Data,SCU,SCCR,HCLKDIV)

#define SET_SCU_SCCR_PCLKDIV(Peri,Data)               SET_BIT(Peri,Data,SCU,SCCR,PCLKDIV)
#define GET_SCU_SCCR_PCLKDIV(Peri)                    GET_BIT(Peri,SCU,SCCR,PCLKDIV)

#define SET_SCU_CSCR_LSE(Peri,Data)                   SET_BIT(Peri,Data,SCU,CSCR,LSECON)
#define SET_SCU_CMR_LSEMNT(Peri,Data)                 SET_BIT(Peri,Data,SCU,CMR,LSEMNT)
#define SET_SCU_CMR_LSEIE(Peri,Data)                  SET_BIT(Peri,Data,SCU,CMR,LSEIE)
#define SET_SCU_CMR_LSEFAIL(Peri,Data)                SET_BIT(Peri,Data,SCU,CMR,LSEFAIL)
#define GET_SCU_CMR_LSEFAIL(Peri)                     GET_BIT(Peri,SCU,CMR,LSEFAIL)
#define GET_SCU_CMR_LSESTS(Peri)                      GET_BIT(Peri,SCU,CMR,LSESTS)

#define SET_SCU_SRCR_SW_RST(Peri,Data)                SET_BIT(Peri,Data,SCU,SRCR,SWRST)
#define SET_SCU_RSER_SW_EN(Peri,Data)                 SET_BIT(Peri,Data,SCU,RSER,SWRST)
#define GET_SCU_RSER_SW_EN(Peri)                      GET_BIT(Peri,SCU,RSER,SWRST)
#define SET_SCU_RSER_CPU_EN(Peri,Data)                SET_BIT(Peri,Data,SCU,RSER,CPURST)
#define GET_SCU_RSER_CPU_EN(Peri)                     GET_BIT(Peri,SCU,RSER,CPURST)
#define SET_SCU_RSER_EXTPIN_EN(Peri,Data)             SET_BIT(Peri,Data,SCU,RSER,PINRST)
#define GET_SCU_RSER_EXTPIN_EN(Peri)                  GET_BIT(Peri,SCU,RSER,PINRST)
#define SET_SCU_RSSR_SW_FLAG(Peri,Data)               SET_BIT(Peri,Data,SCU,RSSR,SWRST)
#define GET_SCU_RSSR_SW_FLAG(Peri)                    GET_BIT(Peri,SCU,RSSR,SWRST)
#define SET_SCU_RSSR_CPU_FLAG(Peri,Data)              SET_BIT(Peri,Data,SCU,RSSR,CPURST)
#define GET_SCU_RSSR_CPU_FLAG(Peri)                   GET_BIT(Peri,SCU,RSSR,CPURST)
#define SET_SCU_RSSR_EXTPIN_FLAG(Peri,Data)           SET_BIT(Peri,Data,SCU,RSSR,PINRST)
#define GET_SCU_RSSR_EXTPIN_FLAG(Peri)                GET_BIT(Peri,SCU,RSSR,PINRST)
#define GET_SCU_RSSR_POR_FLAG(Peri)                   GET_BIT(Peri,SCU,RSSR,PORST)

#define SET_SCU_RSER_CPU_LOCKUP_EN(Peri,Data)         SET_BIT(Peri,Data,SCU,RSER,LOCKUPRST)
#define GET_SCU_RSER_CPU_LOCKUP_EN(Peri)              GET_BIT(Peri,SCU,RSER,LOCKUPRST)
#define SET_SCU_RSSR_CPU_LOCKUP_FLAG(Peri,Data)       SET_BIT(Peri,Data,SCU,RSSR,LOCKUPRST)
#define GET_SCU_RSSR_CPU_LOCKUP_FLAG(Peri)            GET_BIT(Peri,SCU,RSSR,LOCKUPRST)

#define GET_SCU_EOS(Peri)                             GET_REG(Peri,EOSCR)
#define SET_SCU_EOS(Peri,Data)                        SET_REG(Peri,Data,EOSCR)
#define SET_SCU_EOS_HSE(Peri,Data)                    SET_REG(Peri,(Data | 0x3FF),EOSCR)
#define BIT_SCU_EOS_HSENC_EN                          BIT_NAME_POS(SCU_,EOSCR_,HSENFEN_)
#define BIT_SCU_EOS_HSENC_DELAY                       BIT_NAME_POS(SCU_,EOSCR_,HSENFSEL_)
#define BIT_SCU_EOS_HSE_CURR                          BIT_NAME_POS(SCU_,EOSCR_,HSEISEL_)
#define SET_SCU_EOS_LSE(Peri,Data)                    SET_REG(Peri,(Data | 0x03010000),EOSCR)
#define BIT_SCU_EOS_LSENC_EN                          BIT_NAME_POS(SCU_,EOSCR_,LSENFEN_)
#define BIT_SCU_EOS_LSE_CURR                          BIT_NAME_POS(SCU_,EOSCR_,LSEISEL_)
#define SET_SCU_PD_IND_LVL(Peri,Data)                 SET_BIT(Peri,Data,SCU,SRCR,STBYO)

#define BIT_SCU_SMR_VDC_POS                           BIT_NAME_POS(SCU_,SMR_,VDCAON_)
#define BIT_SCU_SMR_LSI_POS                           BIT_NAME_POS(SCU_,SMR_,LSIAON_)
#define BIT_SCU_SMR_LSE_POS                           BIT_NAME_POS(SCU_,SMR_,LSEAON_)
#define SET_SCU_SMR(Peri,Data)                        SET_REG(Peri,Data,SMR)

#define SET_SCU_DATA_VDC_DELAY(Peri,Data)             SET_BIT(Peri,Data,SCU,VDCCON,VDCWDLY)

#define SET_SCU_LVD_IND_SEL(Peri,Data)                SET_BIT(Peri,Data,SCU,LVICR,LVIVS)
#define SET_SCU_LVD_IND_EN(Peri,Data)                 SET_BIT(Peri,Data,SCU,LVICR,LVIEN)
#define SET_SCU_LVD_IND_INTR_EN(Peri,Data)            SET_BIT(Peri,Data,SCU,LVICR,LVIINTEN)
#define SET_SCU_LVD_IND_INTR_FLAG(Peri,Data)          SET_BIT_KEY(Peri,0x7A,Data,SCU,LVISR,LVIFLAG)
#define SET_SCU_LVD_RST_SEL(Peri,Data)                SET_BIT(Peri,Data,SCU,LVRCR,LVRVS)
#define SET_SCU_LVD_RST_EN(Peri,Data)                 SET_BIT(Peri,Data,SCU,LVRCR,LVREN)

#define SET_SCU_LVD_WKUP_EN(Peri,Data)                SET_BIT(Peri,Data,SCU,WUER,LVIWUE)
#define GET_SCU_LVD_WKUP_EN(Peri)                     GET_BIT(Peri,SCU,WUER,LVIWUE)
#define GET_SCU_LVD_WKUP_FLAG(Peri)                   GET_BIT(Peri,SCU,WUSR,LVIWU)
#define SET_SCU_LVD_RST_SRC_EN(Peri,Data)             SET_BIT(Peri,Data,SCU,RSER,LVDRST)
#define GET_SCU_LVD_RST_SRC_EN(Peri)                  GET_BIT(Peri,SCU,RSER,LVDRST)
#define SET_SCU_LVD_RST_SRC_FLAG(Peri,Data)           SET_BIT(Peri,Data,SCU,RSSR,LVDRST)
#define GET_SCU_LVD_RST_SRC_FLAG(Peri)                GET_BIT(Peri,SCU,RSSR,LVDRST)
#define GET_SCU_LVD_PREVMODE(Peri)                    GET_BIT(Peri,SCU,SMR,PREVMODE)

#define SET_SCU_CLK_RST_SRC_HSE_EN(Peri,Data)         SET_BIT(Peri,Data,SCU,RSER,HSEFRST)
#define GET_SCU_CLK_RST_SRC_HSE_EN(Peri)              GET_BIT(Peri,SCU,RSER,HSEFRST)
#define SET_SCU_CLK_RST_SRC_HSE_FLAG(Peri,Data)       SET_BIT(Peri,Data,SCU,RSSR,HSEFRST)
#define GET_SCU_CLK_RST_SRC_HSE_FLAG(Peri)            GET_BIT(Peri,SCU,RSSR,HSEFRST)
#define SET_SCU_CLK_RST_SRC_MCLK_EN(Peri,Data)        SET_BIT(Peri,Data,SCU,RSER,MCLKFRST)
#define GET_SCU_CLK_RST_SRC_MCLK_EN(Peri)             GET_BIT(Peri,SCU,RSER,MCLKFRST)
#define SET_SCU_CLK_RST_SRC_MCLK_FLAG(Peri,Data)      SET_BIT(Peri,Data,SCU,RSSR,MCLKFRST)
#define GET_SCU_CLK_RST_SRC_MCLK_FLAG(Peri)           GET_BIT(Peri,SCU,RSSR,MCLKFRST)
#define SET_SCU_CLK_RST_SRC_LSE_EN(Peri,Data)         SET_BIT(Peri,Data,SCU,RSER,LSEFRST)
#define GET_SCU_CLK_RST_SRC_LSE_EN(Peri)              GET_BIT(Peri,SCU,RSER,LSEFRST)
#define SET_SCU_CLK_RST_SRC_LSE_FLAG(Peri,Data)       SET_BIT(Peri,Data,SCU,RSSR,LSEFRST)
#define GET_SCU_CLK_RST_SRC_LSE_FLAG(Peri)            GET_BIT(Peri,SCU,RSSR,LSEFRST)

/* Unused Macro */
#define SET_SCU_CMR_MCLKREC(Peri,Data)                (void)Peri
#define SET_SCU_EOS_HSE_ACCESS(Peri,Data)             (void)Peri
#define SET_SCU_EOS_LSE_ACCESS(Peri,Data)             (void)Peri
#define SET_SCU_VDC_DEEPSLEEP(Peri,Data)              (void)Peri
#define SET_SCU_LVD_RST_ENM(Peri,Data)                (void)Peri
#define SET_SCU_PLLCON_POSTDIV2(Peri,Data)            (void)Peri
#define SET_SCU_PLLCON_POSTDIV2_POS(Data)             0
#define SET_SCU_PLLCON_PLLMODE(Peri,Data)             (void)Peri
#define SET_SCU_PLLCON_PLLMODE_POS(Data)              0
#define SET_SCU_PLLCON_RESET(Peri,Data)               (void)Peri
#define SET_SCU_PLLCON_RESET_POS(Data)                0

/* FMC Macro */
#define SCU_CFMC_ADDR                                 CFMC_BASE
#define SET_SCU_CFMC_LATENCY(Peri,Data)               SET_BIT(Peri,Data,CFMC,CONF,LATENCY)
#define SCU_FMC_DEFAULT_LATENCY                       5

#endif /* _HAL_SCH_V_02_00_03_H_ */
