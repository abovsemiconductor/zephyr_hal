/**
 *******************************************************************************
 * @file        hal_scu_f_01_00_00.h
 * @author      ABOV R&D Division
 * @brief       Private APIs for ver 01.00.00 typed SCU
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _HAL_SCU_F_01_00_00_H_
#define _HAL_SCU_F_01_00_00_H_

/* Feature(Function) Configuration Define */
#define SCU_FEATURE_LVI_CLOCK_ENABLE
#define SCU_FEATURE_IRQ_UNMASK_ENABLE
#define SCU_FEATURE_FX_RESET_ENABLE
#define SCU_FEATURE_BOOT_PIN_LEVEL
#define SCU_FEATURE_PERI_CLK_DIV

/* Internal Macro */
typedef SCUCG_Type                                    SCUCLK_Type;
typedef SCUCC_Type                                    SCU_Type;
typedef COA1_Type                                     SCUCONF_Type;
#define SCU_REG_BASE                                  SCUCC_BASE
#define SCULV_REG_BASE                                SCULV_BASE
#define SCUCLK_REG_BASE                               SCUCG_BASE
#define SCUCONF_REG_BASE                              COA1_BASE

#define SCU_SOFTWARE_RST                              0x2D

#define CLK_MON_NUM                                   CONFIG_SCU_CLK_MON_MAX_COUNT
#define SCUCLK_MCLK_IRQ                               SCUCLK_0_IRQ
#define SCUCLK_HSE_IRQ                                SCUCLK_0_IRQ
#define SCUCLK_LSE_IRQ                                SCUCLK_0_IRQ

#if defined(_SCU_LVD)
#define SCULVD_IRQ                                    SCULVD_0_IRQ
#endif

#define SCUCLK_EXPO2(x)                               (1 << x)
#define SCUCLK_EXT_HSE_FREQ(x)                        (x & 0x3)
#define SCUCLK_EXT_HSE_CURR(x)                        (~x & 0x3)
#define SCUCLK_EXT_LSE_CURR(x)                        (x & 0x3)
#define SCUCLK_EXT_HSE_MSK                            0xFFFFFF00
#define SCUCLK_EXT_LSE_MSK                            0xFFFF00FF

#define SCUCLK_OUTPUT_INCLK_MCLK                      0x00
#define SCUCLK_OUTPUT_INCLK_WDT                       0x01
#define SCUCLK_OUTPUT_INCLK_HSI                       0x02
#define SCUCLK_OUTPUT_INCLK_HCLK                      0x03
#define SCUCLK_OUTPUT_INCLK_PCLK                      0x04

#define SCUCLK_MCLKSEL_HSI                            0x00
#define SCUCLK_MCLKSEL_HSE                            0x01
#define SCUCLK_MCLKSEL_LSE                            0x02
#define SCUCLK_MCLKSEL_WDT                            0x03

#define SCUCLK_MCLKREC(x)                             (x == 1 ? 0x01 : 0x02)
#define SCUCLK_CLK_MON_SEL(x)                         (x == P_SCUCLK_SRC_MCLK ? 0x00 : \
                                                      (x == P_SCUCLK_SRC_HSI ? 0x01 : \
                                                      (x == P_SCUCLK_SRC_HSE ? 0x02 : \
                                                      (x == P_SCUCLK_SRC_LSE ? 0x03 : 0x00))))
#define SCUCLK_HDIV(x)                                (x == P_SCUCLK_DIV_NONE ? 4 : \
                                                      (x == P_SCUCLK_DIV_2 ? 3 : \
                                                      (x == P_SCUCLK_DIV_4 ? 2 : \
                                                      (x == P_SCUCLK_DIV_8 ? 1 : \
                                                      (x == P_SCUCLK_DIV_16 ? 0 : 5)))))

#define SCULVD_RST_EN                                 0xFF
#define SCULVD_RST_DIS                                0x55
#define SCULVD_RST_OP_MASTER                          0xFF 
#define SCULVD_RST_OP_LVREN                           0xAA 

#define SCU_PREVMODE_SLEEP                            0x01
#define SCU_PREVMODE_DEEPSLEEP                        0x03

#define SCUCLK_SRC_ENABLE_POS                         0x00
#define SCUCLK_SRC_MODE_MSK                           0x07

#define SCUCLK_FMC_CLK_WAIT_0                         20000000
#define SCUCLK_FMC_CLK_WAIT_1                         40000000
#define SCUCLK_FMC_CLK_WAIT_2                         48000000

#define SCUCLK_AUTO_RECOVERY_OFF                      0x01
#define SCUCLK_AUTO_RECOVERY_ON                       0x00

#define SCUCLK_PCLK_DIV_MAX                           3 /* SCUCLK_DIV_e */

/* Bit/Register Macro */
#define SET_SCU_COR_CLKOEN(Peri,Data)                 SET_BIT(Peri,Data,SCUCG,CLKOCR,CLKOEN)
#define SET_SCU_COR_CLKODIV(Peri,Data)                SET_BIT(Peri,(Data & 0x07),SCUCG,CLKOCR,CLKODIV)
#define SET_SCU_COR_CLKOINSEL(Peri,Data)              SET_BIT(Peri,Data,SCUCG,CLKOCR,CLKOS)

#define SET_SCU_CMR_CLKEN(Peri,Data)                  SET_BIT(Peri,Data,SCUCG,CMONCR,MONEN)
#define SET_SCU_CMR_MCLKREC(Peri,Data)                SET_BIT(Peri,SCUCLK_MCLKREC(Data),SCUCG,CMONCR,MACTS)
#define SET_SCU_CMR_CLK_SEL(Peri,Data)                SET_BIT(Peri,SCUCLK_CLK_MON_SEL(Data),SCUCG,CMONCR,MONCS)
#define SET_SCU_CMR_ACT_CLR(Peri)                     SET_BIT(Peri,0x00,SCUCG,CMONCR,MACTS)

#define SET_SCU_CSCR_HSI(Peri,Data)                   SET_BIT_KEY(Peri,0xA507,Data,SCUCG,CLKSRCR,HIRCEN)
#define SET_SCU_CSCR_HSI_SEL(Peri,Data)               SET_BIT_KEY(Peri,0xA507,(Data & 0x03),SCUCG,CLKSRCR,HIRCSEL)
#define SET_SCU_CSCR_WDT(Peri,Data)                   SET_BIT_KEY(Peri,0xA507,Data,SCUCG,CLKSRCR,WDTRCEN)
#define SET_SCU_CSCR_HSE(Peri,Data)                   SET_BIT_KEY(Peri,0xA507,Data,SCUCG,CLKSRCR,XMOSCEN)
#define SET_SCU_CSCR_LSE(Peri,Data)                   SET_BIT_KEY(Peri,0xA507,Data,SCUCG,CLKSRCR,XSOSCEN)
#define SET_SCU_CSCR_LSI(Peri,Data)                   SET_SCU_CSCR_WDT(Peri,Data)

#define SET_SCU_SCCR_MCLKSEL(Peri,Data)               SET_BIT_KEY(Peri,0x570A,Data,SCUCG,SCCR,MCLKSEL)
#define SET_SCU_SCCR_HCLKDIV(Peri,Data)               SET_BIT(Peri,Data,SCUCG,SCDIVR1,HDIV) 
#define SET_SCU_SCCR_PCLKDIV(Peri,Data)               SET_BIT(Peri,Data,SCUCG,SCDIVR2,PDIV)
#define GET_SCU_SCCR_PCLKDIV(Peri)                    GET_BIT(Peri,SCUCG,SCDIVR2,PDIV)

#define SET_SCU_CMR_HSEMNT(Peri,Data)                 SET_BIT(Peri,Data,SCU,CMR,MOSCMNT)
#define SET_SCU_CMR_HSEIE(Peri,Data)                  SET_BIT(Peri,Data,SCU,CMR,MOSCIE)
#define SET_SCU_CMR_HSEFAIL(Peri,Data)                SET_BIT(Peri,Data,SCU,CMR,MOSCFAIL)
#define GET_SCU_CMR_HSEFAIL(Peri)                     GET_BIT(Peri,SCU,CMR,MOSCFAIL)
#define GET_SCU_CMR_HSESTS(Peri)                      GET_BIT(Peri,SCU,CMR,MOSCSTS)
#define SET_SCU_CMR_LSEMNT(Peri,Data)                 SET_BIT(Peri,Data,SCU,CMR,SOSCMNT)
#define SET_SCU_CMR_LSEIE(Peri,Data)                  SET_BIT(Peri,Data,SCU,CMR,SOSCIE)
#define SET_SCU_CMR_LSEFAIL(Peri,Data)                SET_BIT(Peri,Data,SCU,CMR,SOSCFAIL)
#define GET_SCU_CMR_LSEFAIL(Peri)                     GET_BIT(Peri,SCU,CMR,SOSCFAIL)
#define GET_SCU_CMR_LSESTS(Peri)                      GET_BIT(Peri,SCU,CMR,SOSCSTS)

#define SET_SCU_SRCR_SW_RST(Peri,Data)                SET_BIT_KEY(Peri,0x9EB3,Data,SCUCC,SWRSTR,SWRST)


#define GET_SCU_BOOTPIN_ST(Peri)                      GET_BIT(Peri,SCUCC,BTPSCR,BTPSTA)

#define GET_SCU_EOS(Peri)                             GET_REG(Peri,EOSCR)
#define SET_SCU_EOS_HSE(Peri,Data)                    SET_REG(Peri,(Data | 0x80),EOSCR)
#define BIT_SCU_EOS_HSENC_EN                          BIT_NAME_POS(SCU_,EOSCR_,NCSKIP_)
#define BIT_SCU_EOS_HSENC_DELAY                       BIT_NAME_POS(SCU_,EOSCR_,NCOPT_)
#define BIT_SCU_EOS_HSE_CURR                          BIT_NAME_POS(SCU_,EOSCR_,ISE_)

#define BIT_SCU_EOS_LSENC_EN                          BIT_NAME_POS(SCU_,EOSCR_,ESNCBYPS_)
#define BIT_SCU_EOS_LSE_CURR                          BIT_NAME_POS(SCU_,EOSCR_,ESISEL_)
#define SET_SCU_EOS_LSE(Peri,Data)                    SET_REG(Peri,(Data | 0x8000),EOSCR)

#define SET_SCU_LSI_LS_EN(Peri,Data)                  SET_BIT(Peri,Data,SCU,ROSCCON,SKIP_LS)
#define SET_SCU_LSI_LDO_EN(Peri,Data)                 SET_BIT(Peri,Data,SCU,ROSCCON,EN_LDO)

#define BIT_SCU_SMR_VDC_POS                           BIT_NAME_POS(SCU_,SMR_,VDCAON_)
#define BIT_SCU_SMR_BGR_POS                           BIT_NAME_POS(SCU_,SMR_,BGRAON_)
#define BIT_SCU_SMR_LSI_POS                           BIT_NAME_POS(SCU_,SMR_,ROSCAON_)
#define BIT_SCU_SMR_LSE_POS                           BIT_NAME_POS(SCU_,SMR_,LSEAON_)



/* Low Voltage Detector */
#define SET_SCU_LVD_IND_SEL(Peri,Data)                SET_BIT(Peri,Data,SCULV,LVICR,LVIVS)
#define SET_SCU_LVD_IND_EN(Peri,Data)                 SET_BIT(Peri,Data,SCULV,LVICR,LVIEN)
#define SET_SCU_LVD_IND_INTR_EN(Peri,Data)            SET_BIT(Peri,Data,SCULV,LVICR,LVINTEN)
#define SET_SCU_LVD_IND_INTR_FLAG(Peri,Data)          SET_BIT(Peri,Data,SCULV,LVICR,LVIFLAG)
#define SET_SCU_LVD_RST_EN(Peri,Data)                 SET_BIT(Peri,Data,SCULV,LVRCR,LVREN)
#define SET_SCU_LVD_RST_SRC_FLAG(Peri,Data)           SET_BIT(Peri,Data,SCUCC,RSTSSR,LVRSTA)
#define GET_SCU_LVD_RST_SRC_FLAG(Peri)                GET_BIT(Peri,SCUCC,RSTSSR,LVRSTA)
#define SET_SCU_LVD_WKUP_EN(Peri,Data)                SET_BIT(Peri,Data,SCU,WUER,LVDWUE)
#define GET_SCU_LVD_WKUP_EN(Peri)                     GET_BIT(Peri,SCU,WUER,LVDWUE)
#define GET_SCU_LVD_WKUP_FLAG(Peri)                   GET_BIT(Peri,SCU,WUSR,LVDWU)
#define GET_SCU_LVD_PREVMODE(Peri)                    GET_BIT(Peri,SCU,SMR,PREVMODE)

#define SET_SCU_CLK_RST_SRC_HSE_EN(Peri,Data)         SET_BIT(Peri,Data,SCU,RSER,MOFRST)
#define GET_SCU_CLK_RST_SRC_HSE_EN(Peri)              GET_BIT(Peri,SCU,RSER,MOFRST)
#define SET_SCU_CLK_RST_SRC_HSE_FLAG(Peri,Data)       SET_BIT(Peri,Data,SCU,RSSR,MOFRST)
#define GET_SCU_CLK_RST_SRC_HSE_FLAG(Peri)            GET_BIT(Peri,SCU,RSSR,MOFRST)
#define SET_SCU_CLK_RST_SRC_MCLK_EN(Peri,Data)        SET_BIT(Peri,Data,SCU,RSER,MCKFRST)
#define GET_SCU_CLK_RST_SRC_MCLK_EN(Peri)             GET_BIT(Peri,SCU,RSER,MCKFRST)
#define SET_SCU_CLK_RST_SRC_MCLK_FLAG(Peri,Data)      SET_BIT(Peri,Data,SCU,RSSR,MCKFRST)
#define GET_SCU_CLK_RST_SRC_MCLK_FLAG(Peri)           GET_BIT(Peri,SCU,RSSR,MCKFRST)

/* Unused Macro */
#define SET_SCU_SCCR_PLLPREDIV(Peri,Data)             (void)Peri
#define SET_SCU_PLLCON_PLLICP(Peri,Data)              (void)Peri
#define SET_SCU_PLLCON_PLLVCOC(Peri,Data)             (void)Peri
#define SET_SCU_PLLCON_OUTDIV(Peri,Data)              (void)Peri
#define SET_SCU_PLLCON_POSTDIV1(Peri,Data)            (void)Peri
#define SET_SCU_PLLCON_POSTDIV2(Peri,Data)            (void)Peri
#define SET_SCU_PLLCON_PREDIV(Peri,Data)              (void)Peri  
#define SET_SCU_PLLCON_PLLMODE(Peri,Data)             (void)Peri 
#define SET_SCU_PLLCON_PLLEN(Peri,Data)               (void)Peri
#define SET_SCU_PLLCON_BYPASS(Peri,Data)              (void)Peri
#define SET_SCU_PLLCON_RESET(Peri,Data)               (void)Peri
#define SET_SCU_PLLCON(Peri,Data)                     (void)Peri
#define SET_SCU_SCCR_PLLCLKSEL(Peri,Data)             (void)Peri
#define GET_SCU_PLLCON_LOCK(Peri)                     0
#define GET_SCU_PLLCON(Peri)                          0
#define SET_SCU_PLLCON_PLLEN_POS(Data)                0
#define SET_SCU_PLLCON_OUTDIV_POS(Data)               0
#define SET_SCU_PLLCON_POSTDIV1_POS(Data)             0
#define SET_SCU_PLLCON_POSTDIV2_POS(Data)             0
#define SET_SCU_PLLCON_PREDIV_POS(Data)               0
#define SET_SCU_PLLCON_BYPASS_POS(Data)               0
#define SET_SCU_PLLCON_RESET_POS(Data)                0
#define SET_SCU_PLLCON_PLLMODE_POS(Data)              0
#define SET_SCU_RSER_SW_EN(Peri,Data)                 (void)Peri
#define GET_SCU_RSER_SW_EN(Peri)                      0 
#define SET_SCU_RSER_CPU_EN(Peri,Data)                (void)Peri
#define GET_SCU_RSER_CPU_EN(Peri)                     0
#define SET_SCU_RSER_EXTPIN_EN(Peri,Data)             (void)Peri
#define GET_SCU_RSER_EXTPIN_EN(Peri)                  0
#define SET_SCU_RSSR_SW_FLAG(Peri,Data)               (void)Peri
#define GET_SCU_RSSR_SW_FLAG(Peri)                    0
#define SET_SCU_RSSR_CPU_FLAG(Peri,Data)              (void)Peri
#define GET_SCU_RSSR_CPU_FLAG(Peri)                   0
#define SET_SCU_RSSR_EXTPIN_FLAG(Peri,Data)           (void)Peri
#define GET_SCU_RSSR_EXTPIN_FLAG(Peri)                0
#define GET_SCU_RSSR_POR_FLAG(Peri)                   0
#define SET_SCU_VDC_DEEPSLEEP(Peri,Data)              (void)Peri
#define SET_SCU_DATA_VDC_DELAY(Peri,Data)             (void)Peri
#define SET_SCU_SMR(Peri,Data)                        (void)Peri
#define SET_SCU_LVD_RST_SRC_EN(Peri,Data)             (void)Peri
#define GET_SCU_LVD_RST_SRC_EN(Peri)                  0
#define SET_SCU_LVD_RST_SEL(Peri,Data)                (void)Peri
#define SET_SCU_LVD_RST_ENM(Peri,Data)                (void)Peri

typedef FMC_Type                                      CFMC_Type;
#define SCU_CFMC_ADDR                                 FMC_BASE
#define SET_SCU_CFMC_LATENCY(Peri,Data)               SET_BIT_KEY(Peri,0x7858,Data,FMC,CFG,WAIT)
#define SET_SCU_FMC_ACCESS_EN(Peri)                   SET_REG(Peri,0x81,MR); \
                                                      SET_REG(Peri,0x28,MR) 
#define SET_SCU_FMC_ACCESS_DIS(Peri)                  SET_REG(Peri,0x00,MR)
#define SCU_FMC_DEFAULT_LATENCY                       2

#define SET_SCU_LVD_PCER(Peri,Data)                   SET_BIT(Peri,Data,SCUCG,PPCLKEN2,LVICLKE)
#define SET_INTC_IRQ_UNMASK_EN(Peri,Irq,Data)         SET_BIT_ID(Peri,Irq,Data,INTC,MSK,IMSK0_LVI)

#endif /* _HAL_SCH_F_01_00_00_H_ */
