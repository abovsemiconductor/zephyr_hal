/**
 *******************************************************************************
 * @file        hll_scu.h
 * @author      ABOV R&D Division
 * @brief       System Control Unit (Low Level)
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
 * @addtogroup  HLL HLL (Hardware Low Level)
 * @{
 * @defgroup    HLL_SCU SCU
 * @{
 * @brief       Core sub system in System Control Unit (SCU)
 */

#ifndef _HLL_SCU_H_
#define _HLL_SCU_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_common.h"
#include "type/scu_type.h"
#include "../SCU/hal_scu_prv.h"

#define HLL_SCU_REG    ((SCU_Type *)SCU_REG_BASE)
#define HLL_RSTDBCR_REG ((SCUDB_Type *)SCU_RSTDBCR_BASE)

/* inline function */

__STATIC_INLINE void HLL_SCU_SetSWReset(void)
{
    SET_SCU_SRCR_SW_RST(HLL_SCU_REG, SCU_SOFTWARE_RST);
}

__STATIC_INLINE void HLL_SCU_SetSWResetEnable(bool bEnable)
{
    SET_SCU_RSER_SW_EN(HLL_SCU_REG, bEnable);
}

__STATIC_INLINE bool HLL_SCU_GetSWResetEnable(void)
{
    return (bool)GET_SCU_RSER_SW_EN(HLL_SCU_REG);
}

__STATIC_INLINE bool HLL_SCU_GetSWResetEvent(void)
{
    return (bool)GET_SCU_RSSR_SW_FLAG(HLL_SCU_REG);
}

__STATIC_INLINE void HLL_SCU_SetSWResetEvent(bool bEvent)
{
    SET_SCU_RSSR_SW_FLAG(HLL_SCU_REG, bEvent);
}

__STATIC_INLINE void HLL_SCU_SetCPUResetEnable(bool bEnable)
{
    SET_SCU_RSER_CPU_EN(HLL_SCU_REG, bEnable);
}

__STATIC_INLINE bool HLL_SCU_GetCPUResetEnable(void)
{
    return (bool)GET_SCU_RSER_CPU_EN(HLL_SCU_REG);
}

__STATIC_INLINE bool HLL_SCU_GetCPUResetEvent(void)
{
    return (bool)GET_SCU_RSSR_CPU_FLAG(HLL_SCU_REG);
}

__STATIC_INLINE void HLL_SCU_SetCPUResetEvent(bool bEvent)
{
    SET_SCU_RSSR_CPU_FLAG(HLL_SCU_REG, bEvent);
}

__STATIC_INLINE void HLL_SCU_SetExtPinResetEnable(bool bEnable)
{
    SET_SCU_RSER_EXTPIN_EN(HLL_SCU_REG, bEnable);
}

__STATIC_INLINE bool HLL_SCU_GetExtPinResetEnable(void)
{
    return (bool)GET_SCU_RSER_EXTPIN_EN(HLL_SCU_REG);
}

__STATIC_INLINE bool HLL_SCU_GetExtPinResetEvent(void)
{
    return (bool)GET_SCU_RSSR_EXTPIN_FLAG(HLL_SCU_REG);
}

__STATIC_INLINE void HLL_SCU_SetExtPinResetEvent(bool bEvent)
{
    SET_SCU_RSSR_EXTPIN_FLAG(HLL_SCU_REG, bEvent);
}

__STATIC_INLINE bool HLL_SCU_GetPORResetEvent(void)
{
    return (bool)GET_SCU_RSSR_POR_FLAG(HLL_SCU_REG);
}

__STATIC_INLINE void HLL_SCU_SetCPULockupResetEnable(bool bEnable)
{
    SET_SCU_RSER_CPU_LOCKUP_EN(HLL_SCU_REG, bEnable);
}

__STATIC_INLINE bool HLL_SCU_GetCPULockupResetEnable(void)
{
    return (bool)GET_SCU_RSER_CPU_LOCKUP_EN(HLL_SCU_REG);
}

__STATIC_INLINE bool HLL_SCU_GetCPULockupResetEvent(void)
{
    return (bool)GET_SCU_RSSR_CPU_LOCKUP_FLAG(HLL_SCU_REG);
}

__STATIC_INLINE void HLL_SCU_SetCPULockupResetEvent(bool bEvent)
{
    SET_SCU_RSSR_CPU_LOCKUP_FLAG(HLL_SCU_REG, bEvent);
}

__STATIC_INLINE bool HLL_SCU_GetBootPinLevel(void) 
{
    return (bool)GET_SCU_BOOTPIN_ST(HLL_SCU_REG); 
}

__STATIC_INLINE void HLL_SCU_SetResetPinDebounceCount(uint8_t un8Count)
{
    SET_SCU_RSTDB_CNT(HLL_RSTDBCR_REG, un8Count);
}

__STATIC_INLINE void HLL_SCU_SetResetPinDebounceEnable(bool bEnable)
{
    SET_SCU_RSTDB_EN(HLL_RSTDBCR_REG, bEnable);
}

/* end of inline function */

HAL_ERR_e HLL_SCU_SetReset(SCU_RST_e eRst, bool bEnable);


#ifdef __cplusplus
}
#endif

#endif /* _HLL_SCU_H_ */

/** @} */
/** @} */
