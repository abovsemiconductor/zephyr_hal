/**
 *******************************************************************************
 * @file        hll_crc.c
 * @author      ABOV R&D Division
 * @brief       Cyclic Redundancy Check (Low Level)
 *
 * Copyright 2026 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#include "abov_config.h"

/*
 * This file is picked up unconditionally by the audk32 HAL library's
 * file(GLOB_RECURSE ...) over every .c file under Platform/HAL/ (see
 * modules/hal/abov32/audk32/CMakeLists.txt) regardless of whether any app
 * actually uses the CRC
 * driver. hll_crc.h pulls in hal_crc_prv.h's CRC-IP-version dispatch, which
 * #errors unless _MODULE_CRC (and thus CONFIG_CRC_VER_VENDOR etc.) is
 * defined -- so, like hal_crc.c below, this whole file must stay inert
 * unless _CRC is actually set, instead of only compiling correctly by
 * accident whenever some other translation unit happens to already need
 * CONFIG_HAL_CRC == 1.
 */
#if defined(_CRC)
#include "hll_crc.h"

void HLL_CRC_SetInputConfig(CRC_ID_e eId, CRC_INP_DATA_e eInDataSize, bool bComplement)
{
#if defined(CRC_FEATURE_INPUT_CONF_MODE)
    CRC_Type *ptCrc = HLL_CRC_REG(eId);

    SET_CRC_CR_INDATA_SIZE(ptCrc, (uint32_t)eInDataSize);
    SET_CRC_CR_INDATA_COMPLE(ptCrc, bComplement);
#else
    (void)eId;
    (void)eInDataSize;
    (void)bComplement;
#endif
}

void HLL_CRC_SetDmaIntrEnable(CRC_ID_e eId, bool bEnable)
{
#if defined(CRC_FEATURE_UNSUPPORT_IRQ)
    (void)eId;
    (void)bEnable;
#else
    SET_CRC_IER_DMA_EN(HLL_CRC_REG(eId), bEnable);
#endif
}

void HLL_CRC_ClearDmaFlag(CRC_ID_e eId)
{
#if defined(CRC_FEATURE_UNSUPPORT_IRQ)
    (void)eId;
#else
    SET_CRC_IER_DMA_FLAG(HLL_CRC_REG(eId), true);
#endif
}

bool HLL_CRC_GetDmaFlag(CRC_ID_e eId)
{
#if defined(CRC_FEATURE_UNSUPPORT_IRQ)
    (void)eId;
    return false;
#else
    return (bool)GET_CRC_IER_DMA_FLAG(HLL_CRC_REG(eId));
#endif
}

#endif /* _CRC */
