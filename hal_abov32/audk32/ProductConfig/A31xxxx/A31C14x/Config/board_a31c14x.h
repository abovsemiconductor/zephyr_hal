/**
 *******************************************************************************
 * @file        board_a31c14x.h
 * @author      ABOV R&D Division
 * @brief       Board configuration on which A31C14x is mounted
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _BOARD_A31C14X_H_
#define _BOARD_A31C14X_H_

#if defined(_RTE_)
#undef TARGET_BOARD

#if defined (EXTRN_VARIANT_A31C144RLN)
#define TARGET_BOARD BD_STK_A31C144_RLN_A
#include "Board/stk_a31c144_rln_a.h"
#else
#error "Invalid board selection"
#endif

#else
#if (TARGET_BOARD == BD_BARE)
#if defined (EXTRN_VARIANT_A31C144RLN_ADK)
#include "../A31C14x/Config/Board/evb_a31c144_rln_adk_a.h"
#else
#include "../A31C14x/Config/Board/bare.h"
#endif /* End of (TARGET_BOARD == EXTRN_VARIANT_A31C144RLN_ADK) */
#elif (TARGET_BOARD == BD_STK_A31C144_RLN_A)
#include "../A31C14x/Config/Board/stk_a31c144_rln_a.h"
#else
#error "Invalid board selection"
#endif /* End of (TARGET_BOARD == BD_BARE) */

#endif /* End of (_RTE_) */

#endif /* _BOARD_A31C14X_H_ */
