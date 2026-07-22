/**
 *******************************************************************************
 * @file        hal_lcd.h
 * @author      ABOV R&D Division
 * @brief       LCD Driver
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
 * @defgroup    HAL_LCD LCD
 * @{
 * @brief       Liquid Crystal Display (LCD) Controller
 */

#ifndef _HAL_LCD_H_
#define _HAL_LCD_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"

/**
 * @brief LCD Instance Id
 */
typedef enum
{
    LCD_ID_0,
    LCD_ID_1,
    LCD_ID_2,
    LCD_ID_3,
    LCD_ID_4,
    LCD_ID_5,
    LCD_ID_6,
    LCD_ID_7,
    LCD_ID_8,
    LCD_ID_9,
    LCD_ID_MAX
} LCD_ID_e;

/**
 * @brief LCD clock source
 */
typedef enum
{
    LCD_CLK_MCCR,    /**< Misc Clock source ::LCD_CLK_MCCR_e */
    LCD_CLK_LSE,     /**< Low Speed External Clock source */
    LCD_CLK_WDTRC,   /**< Watch Dog Timer Ring Osillator Clock source */
    LCD_CLK_MAX
} LCD_CLK_e;

/**
 * @brief LCD MCCR (Misc Clock) Source
 */
typedef enum
{
    LCD_CLK_MCCR_LSI,    /**< Low Speed Internal Clock source */
    LCD_CLK_MCCR_LSE,    /**< Low Speed External Clock source */
    LCD_CLK_MCCR_MCLK,   /**< Master Clock source */
    LCD_CLK_MCCR_HSI,    /**< High Speed Internal Clock source */
    LCD_CLK_MCCR_HSE,    /**< High Speed External Clock source */
    LCD_CLK_MCCR_PLL,    /**< Phase-Locked Loop (PLL) Clock source */
    LCD_CLK_MCCR_MAX
} LCD_CLK_MCCR_e;

/**
 * @brief LCE Internal Bias Driving Resistor
 */
typedef enum
{
    LCD_RLCD3_105_105_80,     /**< 105K/105K/80K @ (1/2)(1/3)(1/4) Bias */
    LCD_RLCD3_100 = LCD_RLCD3_105_105_80,
    LCD_RLCD1_10_10_10,       /**< 10K/10K/10K @ (1/2)(1/3)(1/4) Bias */
    LCD_RLCD1_100 = LCD_RLCD1_10_10_10,
    LCD_RLCD2_66_66_50,       /**< 66K/66K/50K @ (1/2)(1/3)(1/4) Bias */
    LCD_RLCD2_50 = LCD_RLCD2_66_66_50,
    LCD_RLCD4_320_320_240,    /**< 320K/320K/240K @ (1/2)(1/3)(1/4) Bias */
    LCD_RLCD_MAX
} LCD_RLCD_e;

/**
 * @brief LCD Duty and Bias
 */
typedef enum
{
    LCD_DUTY_1_8_BIAS_1_4,    /**< 1/8 Duty & 1/4 Bias */
    LCD_DUTY_1_6_BIAS_1_4,    /**< 1/6 Duty & 1/4 Bias */
    LCD_DUTY_1_5_BIAS_1_3,    /**< 1/5 Duty & 1/3 Bias */
    LCD_DUTY_1_4_BIAS_1_3,    /**< 1/4 Duty & 1/3 Bias */
    LCD_DUTY_1_3_BIAS_1_3,    /**< 1/3 Duty & 1/3 Bias */
    LCD_DUTY_1_3_BIAS_1_2,    /**< 1/3 Duty & 1/2 Bias */
    LCD_DUTY_1_2_BIAS_1_2,    /**< 1/2 Duty & 1/2 Bias */
    LCD_DUTY_BIAS_MAX
} LCD_DUTY_BIAS_e;

/**
 * @brief LCD CLK Pre-Divider
 */
typedef enum
{
    LCD_CLK_PREDIV_256,
    LCD_CLK_PREDIV_128,
    LCD_CLK_PREDIV_64,
    LCD_CLK_PREDIV_32,
    LCD_CLK_PREDIV_MAX
} LCD_CLK_PREDIV_e;

/**
 * @brief LCD Bias Mode A Clock
 */
typedef enum {
    LCD_BIAS_MODE_A_1CLK,
    LCD_BIAS_MODE_A_2CLK,
    LCD_BIAS_MODE_A_3CLK,
    LCD_BIAS_MODE_A_4CLK,
    LCD_BIAS_MODE_A_5CLK,
    LCD_BIAS_MODE_A_6CLK,
    LCD_BIAS_MODE_A_7CLK,
    LCD_BIAS_MODE_A_8CLK,
    LCD_BIAS_MODE_A_MAX
} LCD_BIAS_MODE_A_CLK_e;

/**
 * @brief LCD VLC0 Voltage Control (Contrast Enabled)
 */
typedef enum {
    LCD_VLC0_VDD16_31_STEP,    /**< VDD x 16/31 step */
    LCD_VLC0_0_STEP = LCD_VLC0_VDD16_31_STEP,
    LCD_VLC0_VDD16_30_STEP,    /**< VDD x 16/30 step */
    LCD_VLC0_1_STEP = LCD_VLC0_VDD16_30_STEP,
    LCD_VLC0_VDD16_29_STEP,    /**< VDD x 16/29 step */
    LCD_VLC0_2_STEP = LCD_VLC0_VDD16_29_STEP,
    LCD_VLC0_VDD16_28_STEP,    /**< VDD x 16/28 step */
    LCD_VLC0_3_STEP = LCD_VLC0_VDD16_28_STEP,
    LCD_VLC0_VDD16_27_STEP,    /**< VDD x 16/27 step */
    LCD_VLC0_4_STEP = LCD_VLC0_VDD16_27_STEP,
    LCD_VLC0_VDD16_26_STEP,    /**< VDD x 16/26 step */
    LCD_VLC0_5_STEP = LCD_VLC0_VDD16_26_STEP,
    LCD_VLC0_VDD16_25_STEP,    /**< VDD x 16/25 step */
    LCD_VLC0_6_STEP = LCD_VLC0_VDD16_25_STEP,
    LCD_VLC0_VDD16_24_STEP,    /**< VDD x 16/24 step */
    LCD_VLC0_7_STEP = LCD_VLC0_VDD16_24_STEP,
    LCD_VLC0_VDD16_23_STEP,    /**< VDD x 16/23 step */
    LCD_VLC0_VDD16_22_STEP,    /**< VDD x 16/22 step */
    LCD_VLC0_VDD16_21_STEP,    /**< VDD x 16/21 step */
    LCD_VLC0_VDD16_20_STEP,    /**< VDD x 16/20 step */
    LCD_VLC0_VDD16_19_STEP,    /**< VDD x 16/19 step */
    LCD_VLC0_VDD16_18_STEP,    /**< VDD x 16/18 step */
    LCD_VLC0_VDD16_17_STEP,    /**< VDD x 16/17 step */
    LCD_VLC0_VDD16_16_STEP,    /**< VDD x 16/16 step */
    LCD_VLC0_VDD_STEP_MAX
} LCD_VLC0_VDD16_e;

/**
 * @brief LCD Bias Resistor Mode
 */
typedef enum {
    LCD_BIAS_INTERNAL,
    LCD_BIAS_EXTERNAL,
    LCD_BIAS_CAPACITOR,    /**< Voltage booster */
    LCD_BIAS_MAX
} LCD_BIAS_e;

/**
 * @brief LCD External Bias VLC0/1/2/3
 */
typedef enum {
    LCD_VLC0,
    LCD_VLC1,
    LCD_VLC2,
    LCD_VLC3
} LCD_VLC_EN_PATH_e;

/**
 * @brief LCD Clock Configuration
 */
typedef struct
{
    LCD_CLK_e           eClk;
    LCD_CLK_MCCR_e      eMccr;         /**< When selecting MCCR at eClk */
    uint8_t             un8MccrDiv;    /**< When selecting MCCR at eClk */
    LCD_CLK_PREDIV_e    ePreDiv;
} LCD_CLK_CFG_t;

/**
 * @brief LCD Auto Bias Configuration
 */
typedef struct
{
    bool                     bEnable;
    LCD_BIAS_MODE_A_CLK_e    eBiasModeA;
} LCD_AUTOBIAS_CFG_t;

/**
 * @brief LCD Constrast Configuration
 */
typedef struct
{
    bool                  bEnable;
    LCD_VLC0_VDD16_e      eVlc0Volt;
} LCD_CONTRAST_CFG_t;

/**
 * @brief LCD Mode Configuration
 */
typedef struct
{
    LCD_BIAS_e            eDriveBias;
    union
    {
        struct
        {
            LCD_RLCD_e    eIntBiasResistor;   /**< When selecting LCD_BIAS_INTERNAL ::LCD_BIAS_e*/
        } tInt;

        struct
        {
            bool          bVLC0Enable;
            bool          bVLC1Enable;
            bool          bVLC2Enable;
            bool          bVLC3Enable;
        } tExt;
    } uType;

    LCD_DUTY_BIAS_e       eDutyBias;
    LCD_AUTOBIAS_CFG_t    tAutoBias;
    LCD_CONTRAST_CFG_t    tContrast;

} LCD_CFG_t;

/**
 * @brief LCD Control Data Buffer
 */
typedef struct
{
    uint8_t    un8SegNum;
    uint8_t    un8Data;
} LCD_DATA_t;

/**
 *******************************************************************************
 * @brief       Initialize LCD.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LCD_Init(LCD_ID_e eId);

/**
 *******************************************************************************
 * @brief       Uninitialize ADC.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LCD_Uninit(LCD_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Clock Configuration LCD.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptClkCfg : LCD Clock Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LCD_SetClkConfig(LCD_ID_e eId, LCD_CLK_CFG_t *ptClkCfg);

/**
 *******************************************************************************
 * @brief       Set Mode Configuration LCD.
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptCfg : LCD Mode Configuration.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LCD_SetConfig(LCD_ID_e eId, LCD_CFG_t *ptCfg);

/**
 *******************************************************************************
 * @brief       Start Display LCD.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LCD_Start(LCD_ID_e eId);

/**
 *******************************************************************************
 * @brief       Stop Display LCD.
 * @param[in]   eId : Instance Id.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LCD_Stop(LCD_ID_e eId);

/**
 *******************************************************************************
 * @brief       Set Data LCD (or Update Data).
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptLcdData : Display Data (Seg and Com).
 * @param[in]   un8SegCnt : Display Data count.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LCD_SetData(LCD_ID_e eId, LCD_DATA_t *ptLcdData, uint8_t un8SegCnt);

/**
 *******************************************************************************
 * @brief       Get Data LCD (or Update Data).
 * @param[in]   eId : Instance Id.
 * @param[in]   *ptLcdData : Display Data (Seg and Com).
 * @param[in]   un8SegCnt : Display Data count.
 * @return      ::HAL_ERR_e : HAL ERR code
 ******************************************************************************/
HAL_ERR_e HAL_LCD_GetData(LCD_ID_e eId, LCD_DATA_t *ptLcdData, uint8_t un8SegCnt);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_LCD_H_ */

/** @} */
/** @} */
