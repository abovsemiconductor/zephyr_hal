/**
 *******************************************************************************
 * @file        board_a33g52x.h
 * @author      ABOV R&D Division
 * @brief       Board configuration on which A33G52x is mounted
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _BOARD_A33G52X_H_
#define _BOARD_A33G52X_H_

#if defined(_RTE_)
#undef TARGET_BOARD

#if defined (EXTRN_VARIANT_A33G527VQN)
#define TARGET_BOARD BD_STK_A33G527_VQN_A
#include "Board/stk_a33g527_vqn_a.h"
#elif defined (EXTRN_VARIANT_A33G526RLN)
#define TARGET_BOARD BD_STK_A33G526_RLN_A
#include "Board/stk_a33g526_rln_a.h"
#else
#error "Invalid board selection"
#endif

#else
#if (TARGET_BOARD == BD_BARE)
#include "../A33G52x/Config/Board/bare.h"
#elif (TARGET_BOARD == BD_STK_A33G527_VQN_A)
#include "../A33G52x/Config/Board/stk_a33g527_vqn_a.h"
#elif (TARGET_BOARD == BD_STK_A33G526_RLN_A)
#include "../A33G52x/Config/Board/stk_a33g526_rln_a.h"
#else
#error "Invalid board selection"
#endif /* End of (TARGET_BOARD == BD_BARE) */

#endif /* End of (_RTE_) */

#endif /* _BOARD_A33G52X_H_ */
