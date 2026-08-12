/**
 *******************************************************************************
 * @file        hal_scu_clk.h
 * @author      ABOV R&D Division
 * @brief       Clock sub system in System Control Unit
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/**
 * @addtogroup  HAL HAL (Hardware Abstraction Layer)
 * @{
 * @defgroup    HAL_SCU_CLK SCU_CLK
 * @{
 * @brief       Clock sub system in System Control Unit (SCU)
 */

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"
#include "type/scu_clk_type.h"

#ifndef _HAL_SCU_CLK_H_
#define _HAL_SCU_CLK_H_

/**
 * @brief SCUCLK Phase-Locked Loop (PLL) Configuration
 */
typedef struct
{
    SCUCLK_PLL_SRC_e        eSrc;           /**< HSI, HSE Clock Source Only */
    SCUCLK_DIV_e            eSrcDiv;        /**< Source Clock Divider */
    uint8_t                 un8OutDiv;      /**< Output Divider or Feedback Divider */
    uint8_t                 un8PostDiv1;    /**< Feedback Multiplier 1 or Post Divider 1 */
    uint8_t                 un8PostDiv2;    /**< Feedback Divider 2 or Post Divider 2 */
    uint8_t                 un8PreDiv;      /**< PLL in Clock Pre-Divider */
    SCUCLK_PLL_CTRLOPT_e    eCurOpt;        /**< PLL Current Option */
    SCUCLK_PLL_VCOBIAS_e    eVcoBias;       /**< PLL VCO bias */
    SCUCLK_PLL_MODE_e       ePllMode;       /**< VCO Double */
} SCUCLK_PLL_CFG_t;

/**
 * @brief SCUCLK Main Clock Configuration
 */
typedef struct
{
    SCUCLK_SRC_e eMClk;           /**< Main Clock Selection */
    SCUCLK_DIV_e ePreMClkDiv;     /**< Pre Main Clock Divider */
    SCUCLK_DIV_e ePostMClkDiv;    /**< Post Main Clock Divider (System Core Clock : FCLK and HCLK) */
} SCUCLK_MCLK_CFG_t;

/**
 *******************************************************************************
 * @brief       SCUCLK Monitor Interrupt Callback Function Type.
 * @param[in]   un32Event : Event type ::SCUCLK_MON_EVENT_e.
 * @param[in]   *pContext : Context provided during SetMonitor.
 * @return      void : None
 ******************************************************************************/
typedef void (*pfnSCUCLK_IRQ_Handler_t)(uint32_t un32Event, void *pContext);

/**
 * @brief SCUCLK Clock Monitor Configuration
 */
typedef struct
{
    SCUCLK_SRC_e               eSrc;           /**< Only MCLK, HSE, LSE */   
    bool                       bEnable;        /**< Monitor Enable */
    bool                       bNmiEnable;     /**< NMI Enable */
    pfnSCUCLK_IRQ_Handler_t    pfnHandler;     /**< Interrupt Callback */
    void                       *pContext;      /**< Interrupt Context */
    uint32_t                   un32Prio;       /**< Interrupt Priority */
} SCUCLK_MON_CFG_t;

/**
 *******************************************************************************
 * @brief       Set Clock Source Enable SCUCLK.
 * @param[in]   eSrc : Clock Source.
 * @param[in]   bEnable : Enable Clock Source.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_CLK_SetSrcEnable(SCUCLK_SRC_e eSrc, bool bEnable);

/**
 *******************************************************************************
 * @brief       Set Main Clock Source SCUCLK.
 * @param[in]   *ptCfg : SCUCLK Main Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_CLK_SetMClk(SCUCLK_MCLK_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set PLL Configuration SCUCLK.
 * @param[in]   bEnable : Enable PLL.
 * @param[in]   *ptCfg : SCUCLK PLL Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_CLK_SetPLLConfig(bool bEnable, SCUCLK_PLL_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Set Clock Monitor Configuration SCUCLK.
 * @param[in]   *ptCfg : SCUCLK Clock Monitor Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_CLK_SetMonitor(SCUCLK_MON_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Get Clock Montior Status SCUCLK.
 * @param[in]   eSrc : Clock Source (Only MCLK, HSE, LSE).
 * @param[out]  *pbStatus : Status (true = working normally, false = not oscillating).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_CLK_GetMonitorStatus(SCUCLK_SRC_e eSrc, bool *pbStatus);

/**
 *******************************************************************************
 * @brief       Set Main Clock Auto Recovery if failed SCUCLK.
 * @param[in]   bEnable : Enable Auto Recovery.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_CLK_SetAutoRecovery(bool bEnable);

/**
 *******************************************************************************
 * @brief       Set Clock Out to Specific Port SCUCLK.
 * @param[in]   eSrc : Clock Source.
 * @param[in]   un8OutputDiv : Clock Source Output Divider.
 * @param[in]   bEnable : Enable Clock Out.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_CLK_SetOutput(SCUCLK_SRC_e eSrc, uint8_t un8OutputDiv, bool bEnable);

/**
 *******************************************************************************
 * @brief       Set Reset Source SCUCLK.
 * @param[in]   eSrc : Clock Source.
 * @param[in]   bEnable : Enable Clock Source.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_CLK_SetResetSrc(SCUCLK_SRC_e eSrc, bool bEnable);

/**
 *******************************************************************************
 * @brief       Get Reset Source Event SCUCLK.
 * @param[in]   eSrc : Clock Source.
 * @param[out]  *pbEvent : Event (true = reset event, false = no event).
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_CLK_GetResetSrcEvent(SCUCLK_SRC_e eSrc, bool *pbEvent);

/**
 *******************************************************************************
 * @brief       Set Extend HSE Clock Configuration (Noise Cancel, Current) SCUCLK.
 * @param[in]   eExt : HSE Clock Range.
 * @param[in]   bNCEnable : Enable Noise Cancel.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_CLK_SetExtHSE(SCUCLK_HSE_FREQ_e eFreq, bool bNCEnable);

/**
 *******************************************************************************
 * @brief       Set Extend LSE Clock Configuration (Noise Cancel, Current) SCUCLK.
 * @param[in]   eCurr : LSE Current.
 * @param[in]   bNCEnable : Enable Noise Cancel.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_CLK_SetExtLSE(SCUCLK_LSE_CURR_e eCurr, bool bNCEnable);

/**
 *******************************************************************************
 * @brief       Set Extend LSI Clock Configuration (LDO, Level Shifter) SCUCLK.
 *              some of ABOV chipsets are only supported.
 * @param[in]   bLDOEnable : Enable LDO.
 * @param[in]   bLSEnable : Enable Level Shifter.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_CLK_SetExtLSI(bool bLDOEnable, bool bLSEnable);

/**
 *******************************************************************************
 * @brief       Set to divide Peripheral Clock.
 *              some of ABOV chipsets are only supported.
 * @param[in]   eClkDiv : Dividing Peripheral Clock.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_SCU_CLK_SetPClkDiv(SCUCLK_DIV_e ePClkDiv);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_SCU_CLK_H_ */

/** @} */
/** @} */
