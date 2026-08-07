/**
 *******************************************************************************
 * @file        scu_type.h
 * @author      ABOV R&D Division
 * @brief       System Control Unit (Common)
 *
 * Copyright 2026 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/**
 * @addtogroup  TYPE TYPE (Common Type)
 * @{
 * @defgroup    TYPE_SCU SCU
 * @{
 * @brief       Core sub system in System Control Unit (SCU)
 */

#ifndef _SCU_TYPE_H_
#define _SCU_TYPE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * @brief SCU Reset Source
 */
typedef enum
{
    SCU_RST_SW,            /**< Software Reset */
    SCU_RST_CPU,           /**< CPU Request Reset */
    SCU_RST_CPU_LOCKUP,    /**< CPU Lock-up Reset */
    SCU_RST_EXT_PIN,       /**< External Pin Reset */
    SCU_RST_POR,           /**< Power-on Reset */
    SCU_RST_MAX
} SCU_RST_e;

#ifdef __cplusplus
}
#endif

#endif /* _SCU_TYPE_H_ */

/** @} */
/** @} */
