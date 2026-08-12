/**
 *******************************************************************************
 * @file        hal_common.h
 * @author      ABOV R&D Division
 * @brief       Driver common
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
 * @brief       HAL (Hardware Abstraction Layer) is just reference software for customer to 
 *              understand ABOV MCU and implement their software easily.
 * @defgroup    HAL_COMMON Common
 * @{
 * @brief       HAL Common 
 */

#ifndef _HAL_COMMON_H_
#define _HAL_COMMON_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* place a function into a ram section macro */
#if defined ( NO_RAMFUNCS )
#define RAMFUNC

#elif defined (__ICCARM__)
#define RAMFUNC                                       __ramfunc
#ifndef __inline
#define __inline                                      inline
#endif

#elif defined (__CC_ARM) || defined (__ARMCC_VERSION)
#define RAMFUNC                                       __attribute__ ((section ("code_section_on_ram")))

#elif defined (__GNUC__)
#define RAMFUNC                                       __attribute__ ((long_call, section (".code_section_on_ram")))

#endif

/**
 * @brief HAL General error code
 */
typedef enum
{
    HAL_ERR_OK                 = 0,        /**< operation succeeded */
    HAL_ERR_UNKNOWN            = -1,       /**< unspecified error */
    HAL_ERR_INVALID_ID         = -2,       /**< peripheral id is invalid */
    HAL_ERR_BUSY               = -3,       /**< busy */
    HAL_ERR_TIMEOUT            = -4,       /**< timeout occurred */
    HAL_ERR_NOT_SUPPORTED      = -5,       /**< operation not supported */
    HAL_ERR_PARAMETER          = -6,       /**< parameter error */
    HAL_ERR_NO_RESOURCE        = -7,       /**< not enough resource */
    HAL_ERR_INVALID_USE        = -8,       /**< not configured properly */
    HAL_ERR_HW                 = -9,       /**< hardware error */
    HAL_ERR_SPECIFIC           = -10,      /**< driver specific errors */
    HAL_ERR_INVALID_INTERRUPT  = -11,      /**< interrupt is invalid */
} HAL_ERR_e;

/**
 * @brief HAL Priority, Smaller number means Higher Priority
 */
typedef enum
{
    HAL_PRIO_0   = 0,            /**< priority 0 */
    HAL_PRIO_1   = 1,            /**< priority 1 */
    HAL_PRIO_2   = 2,            /**< priority 2 */
    HAL_PRIO_3   = 3,            /**< priority 3 */
    HAL_PRIO_4   = 4,            /**< priority 4 */
    HAL_PRIO_5   = 5,            /**< priority 5 */
    HAL_PRIO_6   = 6,            /**< priority 6 */
    HAL_PRIO_7   = 7,            /**< priority 7 */
    HAL_PRIO_8   = 8,            /**< priority 8 */
    HAL_PRIO_9   = 9,            /**< priority 0 */
    HAL_PRIO_10  = 10,           /**< priority 10 */
    HAL_PRIO_11  = 11,           /**< priority 11 */
    HAL_PRIO_12  = 12,           /**< priority 12 */
    HAL_PRIO_13  = 13,           /**< priority 13 */
    HAL_PRIO_14  = 14,           /**< priority 14 */
    HAL_PRIO_15  = 15,           /**< priority 15 */
    /* (1 << __NVIC_PRIO_BITS) - 1 */
} HAL_PRIO_e;

#define HAL_PRIO_HIGHEST 0
#define HAL_PRIO_LOWEST  15

/**
 * @brief Assert function specific to the application
 */
extern void Assert(char *file, uint32_t line);

/**
 * @brief Assert, application needs to declare a custom assert function
 */
#if (CONFIG_DEBUG == 1)
#define HAL_ASSERT(cond)     ((cond) ? ((void)0) : Assert(__FILE__, __LINE__))
#else
#define HAL_ASSERT(cond)     ((void)(cond))
#endif

/**
 * maximum value macro
 */
#if !defined(MAX)
#define MAX(a, b)               (((a) > (b)) ? (a) : (b))
#endif

/**
 * minimum value macro
 */
#if !defined(MIN)
#define MIN(a, b)               (((a) < (b)) ? (a) : (b))
#endif

/**
 * bit macro
 */
#if !defined(BIT)
#define BIT(n)                  (0x1UL << (n))
#endif

/**
 * Register bit macro
 */

#if !defined(BIT_NAME_MSK)
#define BIT_NAME_MSK(PeriName,RegName,BitName) (PeriName##RegName##BitName##Msk)
#endif

#if !defined(BIT_NAME_POS)
#define BIT_NAME_POS(PeriName,RegName,BitName) (PeriName##RegName##BitName##Pos)
#endif

#if !defined(SET_BIT)
#define SET_BIT(Peri,Data,PeriName,RegName,BitName) \
            (Peri->RegName = ((Peri->RegName & ~(BIT_NAME_MSK(PeriName##_,RegName##_,BitName##_))) \
            | (Data << BIT_NAME_POS(PeriName##_,RegName##_,BitName##_))))
#endif

#if !defined(SET_BIT_KEY)
#define SET_BIT_KEY(Peri,Key,Data,PeriName,RegName,BitName) \
            (Peri->RegName = ((uint32_t)Key << BIT_NAME_POS(PeriName##_,RegName##_,WTIDKY_)) | ((Peri->RegName & ~(BIT_NAME_MSK(PeriName##_,RegName##_,BitName##_))) \
            | (Data << BIT_NAME_POS(PeriName##_,RegName##_,BitName##_))))

#endif

#if !defined(SET_BIT_KEY_BITNAME)
#define SET_BIT_KEY_BITNAME(Peri,Key,KeyBitName,Data,PeriName,RegName,BitName) \
            (Peri->RegName = ((uint32_t)Key << BIT_NAME_POS(PeriName##_,RegName##_,KeyBitName##_)) | ((Peri->RegName & ~(BIT_NAME_MSK(PeriName##_,RegName##_,BitName##_))) \
            | (Data << BIT_NAME_POS(PeriName##_,RegName##_,BitName##_))))

#endif

#if !defined(SET_BIT_ID)
#define SET_BIT_ID(Peri,Id,Data,PeriName,RegName,BitName) \
            (Peri->RegName = ((Peri->RegName & ~(0x01UL << (BIT_NAME_POS(PeriName##_,RegName##_,BitName##_) + Id))) \
            | (Data << (BIT_NAME_POS(PeriName##_,RegName##_,BitName##_) + Id))))
#endif

#if !defined(SET_BIT_OFFSET)
#define SET_BIT_OFFSET(Peri,Offset,Data,PeriName,RegName,BitName) \
            (Peri->RegName = ((Peri->RegName & ~(BIT_NAME_MSK(PeriName##_,RegName##_,BitName##_) << Offset)) \
            | (Data << (BIT_NAME_POS(PeriName##_,RegName##_,BitName##_) + Offset))))
#endif

#if !defined(SET_BIT_ADDR_OFFSET)
#define SET_BIT_ADDR_OFFSET(Addr,Offset,Data,PeriName,RegName,BitName) \
            ((*(volatile uint32_t *)((uint32_t)Addr+Offset)) = (((*(volatile uint32_t *)((uint32_t)Addr+Offset)) & ~(BIT_NAME_MSK(PeriName##_,RegName##_,BitName##_))) \
            | (Data << BIT_NAME_POS(PeriName##_,RegName##_,BitName##_))))
#endif

#if !defined(SET_BIT_ADDR_DATA_OFFSET)
#define SET_BIT_ADDR_DATA_OFFSET(Addr,AOffset,DOffset,Data,PeriName,RegName,BitName) \
            ((*(volatile uint32_t *)((uint32_t)Addr+AOffset)) = (((*(volatile uint32_t *)((uint32_t)Addr+AOffset)) & ~(BIT_NAME_MSK(PeriName##_,RegName##_,BitName##_) << DOffset)) \
            | (Data << (BIT_NAME_POS(PeriName##_,RegName##_,BitName##_) + DOffset))))
#endif

#if !defined(SET_BIT_ADDR_DATA_MASK_OFFSET)
#define SET_BIT_ADDR_DATA_MASK_OFFSET(Addr,AOffset,DOffset,DMask,Data) \
            ((*(volatile uint32_t *)((uint32_t)Addr + AOffset)) = (((*(volatile uint32_t *)((uint32_t)Addr + AOffset)) & ~(DMask << DOffset)) \
            | (Data << DOffset)))
#endif

#if !defined(SET_BIT_ADDR_KEY_DATA_MASK_OFFSET)
#define SET_BIT_ADDR_KEY_DATA_MASK_OFFSET(Addr,AOffset,Key,DOffset,DMask,Data,PeriName,RegName) \
            ((*(volatile uint32_t *)((uint32_t)Addr + AOffset)) = ((uint32_t)Key << BIT_NAME_POS(PeriName##_,RegName##_,WTIDKY_)) \
            | (((*(volatile uint32_t *)((uint32_t)Addr + AOffset)) & ~(DMask << DOffset)) \
            | (Data << DOffset)))
#endif

#if !defined(SET_BIT_FLAG)
#define SET_BIT_FLAG(Peri,Data,PeriName,RegName,BitName) \
            (Peri->RegName = (Data << BIT_NAME_POS(PeriName##_,RegName##_,BitName##_)))
#endif

#if !defined(SET_POS)
#define SET_POS(Data,PeriName,RegName,BitName) \
            (Data << BIT_NAME_POS(PeriName##_,RegName##_,BitName##_))
#endif

#if !defined(GET_BIT)
#define GET_BIT(Peri,PeriName,RegName,BitName) \
            ((Peri->RegName & BIT_NAME_MSK(PeriName##_,RegName##_,BitName##_)) \
            >> BIT_NAME_POS(PeriName##_,RegName##_,BitName##_))
#endif

#if !defined(GET_BIT_ADDR)
#define GET_BIT_ADDR(Addr,PeriName,RegName,BitName) \
            (((*(volatile uint32_t *)Addr) & BIT_NAME_MSK(PeriName##_,RegName##_,BitName##_)) \
            >> BIT_NAME_POS(PeriName##_,RegName##_,BitName##_))
#endif

#if !defined(GET_BIT_ADDR_MSK)
#define GET_BIT_ADDR_MSK(Addr,Msk,PeriName,RegName,BitName) \
            (((*(volatile uint32_t *)Addr) & (Msk << BIT_NAME_POS(PeriName##_,RegName##_,BitName##_))) \
            >> BIT_NAME_POS(PeriName##_,RegName##_,BitName##_))
#endif

#if !defined(GET_BIT_OFFSET)
#define GET_BIT_OFFSET(Peri,Offset,PeriName,RegName,BitName) \
            ((Peri->RegName & (BIT_NAME_MSK(PeriName##_,RegName##_,BitName##_) << Offset)) \
            >> (BIT_NAME_POS(PeriName##_,RegName##_,BitName##_) + Offset))
#endif

#if !defined(SET_REG)
#define SET_REG(Peri,Data,RegName) (Peri->RegName = Data)
#endif

#if !defined(SET_REG_MASK)
#define SET_REG_MASK(Peri,Data,Mask,RegName) (Peri->RegName = (Peri->RegName & (~Mask)) | Data)
#endif

#if !defined(GET_REG)
#define GET_REG(Peri,RegName) (Peri->RegName)
#endif

#if !defined(GET_REG_ADDR)
#define GET_REG_ADDR(Peri,RegName) (&Peri->RegName)
#endif

#if !defined(GET_REG_ADDR_DATA)
#define GET_REG_ADDR_DATA(Addr) (*(volatile uint32_t *)Addr)
#endif

#if !defined(SET_REG_ADDR)
#define SET_REG_ADDR(Addr,Data) ((*(volatile uint32_t *)Addr) = Data)
#endif

#if !defined(GET_REG_ADDR_OFFSET)
#define GET_REG_ADDR_OFFSET(Addr,Offset) (*(volatile uint32_t *)((uint32_t)Addr+Offset))
#endif

#if !defined(GET_BIT_ADDR_OFFSET)
#define GET_BIT_ADDR_OFFSET(Addr,Offset,PeriName,RegName,BitName) \
            ((GET_REG_ADDR_OFFSET(Addr,Offset) & BIT_NAME_MSK(PeriName##_,RegName##_,BitName##_)) \
            >> BIT_NAME_POS(PeriName##_,RegName##_,BitName##_))
#endif

#if !defined(SET_REG_ADDR_OFFSET)
#define SET_REG_ADDR_OFFSET(Addr,Offset,Data) (*(volatile uint32_t *)((uint32_t)Addr+Offset) = Data)
#endif

#ifdef __cplusplus
}
#endif

#endif /* _HAL_COMMON_H_ */

/** @} */
/** @} */

