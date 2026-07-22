/**
 *******************************************************************************
 * @file        board_a34l71x.h
 * @author      ABOV R&D Division
 * @brief       Board configuration on which A34L71x is mounted
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _BOARD_A34L71X_H_
#define _BOARD_A34L71X_H_

#if defined(_RTE_)
#undef TARGET_BOARD

#if defined (EXTRN_VARIANT_A34L716VLN)
#define TARGET_BOARD BD_STK_A34L716_VLN_A
#include "Board/stk_a34l716_vln_a.h"
#else
#error "Invalid board selection"
#endif /* End of EXTRN_VARIANT_A34L716VLN */

#else
#if (TARGET_BOARD == BD_BARE)
#include "../A34L71x/Config/Board/bare.h"
#elif (TARGET_BOARD == BD_STK_A34L716_VLN_A)
#include "../A34L71x/Config/Board/stk_a34l716_vln_a.h"
#else
#error "Invalid board selection"
#endif /* End of (TARGET_BOARD == BD_BARE) */

#endif /* End of _RTE_ */

#endif /* _BOARD_A34L71X_H_ */
