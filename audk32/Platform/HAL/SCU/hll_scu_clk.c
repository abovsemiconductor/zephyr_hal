/**
 *******************************************************************************
 * @file        hal_scu_clk.c
 * @author      ABOV R&D Division
 * @brief       Clock sub system in System Control Unit (Low Level)
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
#include "hal_scu.h"
#include "hal_scu_clk.h"
#include "hal_scu_prv.h"

#if defined(_NMI)
#include "hpl_nmi.h"
#endif
