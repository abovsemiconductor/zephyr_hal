/**
 *******************************************************************************
 * @file        abov_config.h
 * @author      ABOV R&D Division
 * @brief       Top level configuration file
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/** @addtogroup VENDOR ABOV Semiconductor Co., Ltd.
  * @{
*/


/* @addtogroup ABOV CONFIG
  * @{
*/

#ifndef ABOV_CONFIG_H
#define ABOV_CONFIG_H

/* Device list */
#define SUBFAMILY_A34M41X 0x00010000
#define SUBFAMILY_A34M62X 0x00020000
#define SUBFAMILY_A34G43X 0x00030000
#define SUBFAMILY_A34M42X 0x00040000
#define SUBFAMILY_A34L71X 0x00050000

/* Board list : Device information reserves 20bits and Board information reserves 12bit */
/* Board information 12bits are composed of below */
/* Bare board       : 0x00008000 */
/* Any STK board    : 0x0000000F */
/* Any STKS board   : 0x000000F0 */
/* Any other boards : 0x00007F00 */
#define BD_BARE_MASK          (0x00008000)
#define BD_STK_MASK           (0x0000000F)
#define BD_STKS_MASK          (0x000000F0)

#define BD_BARE               (0x00008000)
#define BD_STK_A34M418_VLN_A  (SUBFAMILY_A34M41X + 0x01)
#define BD_STK_A34M418_YLN_A  (SUBFAMILY_A34M41X + 0x02)
#define BD_STK_A34G43A_YLN_A  (SUBFAMILY_A34G43X + 0x03)
#define BD_STK_A34M420_YLN_A  (SUBFAMILY_A34M42X + 0x01)
#define BD_STK_A34L716_VLN_A  (SUBFAMILY_A34L71X + 0x01)

/* Target Board Serial Module */
#define BD_SERIAL_MODULE_NONE     (0)
#define BD_SERIAL_MODULE_UART     (1)
#define BD_SERIAL_MODULE_USART    (2)

/* Target Board Serial Channel Id */
#define BD_SERIAL_CHANNEL_ID_0    (0)
#define BD_SERIAL_CHANNEL_ID_1    (1)
#define BD_SERIAL_CHANNEL_ID_2    (2)
#define BD_SERIAL_CHANNEL_ID_3    (3)
#define BD_SERIAL_CHANNEL_ID_4    (4)
#define BD_SERIAL_CHANNEL_ID_5    (5)
#define BD_SERIAL_CHANNEL_ID_6    (6)
#define BD_SERIAL_CHANNEL_ID_7    (7)
#define BD_SERIAL_CHANNEL_ID_8    (8)
#define BD_SERIAL_CHANNEL_ID_9    (9)

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> -------------------
*/

// <h> ABOV Target Board Selection
// <i> Select one of target board list
//  <o TARGET_BOARD> Board list
//     <BD_BARE=> BARE
//     <BD_STK_A34M418_VLN_A=> STK_A34M418_VLN_A
//     <BD_STK_A34M418_YLN_A=> STK_A34M418_YLN_A
//     <BD_STK_A34G43A_YLN_A=> STK_A34G43A_YLN_A
//     <BD_STK_A34M420_YLN_A=> STK_A34M420_YLN_A
//     <BD_STK_A34L716_VLN_A=> STK_A34L716_VLN_A
//  <i> Select one of A34Mxxx products
//  <i> Default: BARE
#define TARGET_BOARD BD_BARE /* Don't edit this value */

// </h> End of ABOV Board Selection

// <h> ABOV Target Debug Configuration (Read a user's manual of the target device carefully)
//  <e> Configuration Debug Output
//  <i> Configuration Debug Module and Id
#define TARGET_BOARD_DEBUG_ENABLE    1

//   <o TARGET_SERIAL_MODULE> Serial Module List
//      <BD_SERIAL_MODULE_NONE=> NONE (Default)
//      <BD_SERIAL_MODULE_UART=> UART
//      <BD_SERIAL_MODULE_USART=> USART
//   <i> Select one of target serial module for debug output
//   <i> Default: BD_SERIAL_MODULE_NONE
#define TARGET_SERIAL_MODULE BD_SERIAL_MODULE_NONE /* Don't edit this value */

//   <o TARGET_SERIAL_CHANNEL_ID> Serial Channel Id List
//      <BD_SERIAL_CHANNEL_ID_0=> ID_0
//      <BD_SERIAL_CHANNEL_ID_1=> ID_1
//      <BD_SERIAL_CHANNEL_ID_2=> ID_2
//      <BD_SERIAL_CHANNEL_ID_3=> ID_3
//      <BD_SERIAL_CHANNEL_ID_4=> ID_4
//      <BD_SERIAL_CHANNEL_ID_5=> ID_5
//      <BD_SERIAL_CHANNEL_ID_6=> ID_6
//      <BD_SERIAL_CHANNEL_ID_7=> ID_7
//      <BD_SERIAL_CHANNEL_ID_8=> ID_8
//      <BD_SERIAL_CHANNEL_ID_9=> ID_9
//   <i> Select one of serial port id for debug output
//   <i> Default: BD_SERIAL_CHANNEL_ID_0
//  </e>
// </h> End of ABOV Target Debug Configuration
#define TARGET_SERIAL_CHANNEL_ID BD_SERIAL_CHANNEL_ID_0 /* Don't edit this value */

/* Product configuration by external development environment (PACK, CLI and Promotion Build) */
#if defined (EXTRN_SUBFAMILY_A34M41x)
#define A34MXXX 1
#define A34GXXX 0
#define A34LXXX 0
#define A34MXXX_PRODUCT SUBFAMILY_A34M41X

#elif defined (EXTRN_SUBFAMILY_A34M42x)
#define A34MXXX 1
#define A34GXXX 0
#define A34LXXX 0
#define A34MXXX_PRODUCT SUBFAMILY_A34M42X

#elif defined (EXTRN_SUBFAMILY_A34G43x)
#define A34MXXX 0
#define A34GXXX 1
#define A34LXXX 0
#define A34GXXX_PRODUCT SUBFAMILY_A34G43X

#elif defined (EXTRN_SUBFAMILY_A34L71x)
#define A34MXXX 0
#define A34GXXX 0
#define A34LXXX 1
#define A34LXXX_PRODUCT SUBFAMILY_A34L71X

#else
#error "Unknown sub family"
#endif

/* Must add new series product define for condition build */
#define PRODUCT_SERIES A34MXXX + A34GXXX + A34LXXX

/*
//------------- <<< end of configuration section >>> --------------------------
*/
#include <stdint.h>

#if (PRODUCT_SERIES == 1 && A34MXXX == 1)

#if (A34MXXX_PRODUCT == SUBFAMILY_A34M41X)
#if defined(_RTE_)
#include "a34m41x.h"
#include "config_a34m41x.h"
#include "startup_a34m41x.h"
#include "debug_a34m41x.h"
#include "board_a34m41x.h"
#else
#include "../A34M41x/Config/a34m41x.h"
#include "../A34M41x/Config/config_a34m41x.h"
#include "../A34M41x/Config/startup_a34m41x.h"
#include "../A34M41x/Config/debug_a34m41x.h"
#include "../A34M41x/Config/board_a34m41x.h"
#endif

#elif (A34MXXX_PRODUCT == SUBFAMILY_A34M62X)
#if defined(_RTE_)
#include "a34m62x.h"
#include "config_a34m62x.h"
#include "startup_a34m62x.h"
#include "debug_a34m62x.h"
#include "board_a34m62x.h"
#else
#include "../A34M62x/Config/a34m62x.h"
#include "../A34M62x/Config/config_a34m62x.h"
#include "../A34M62x/Config/startup_a34m62x.h"
#include "../A34M62x/Config/debug_a34m62x.h"
#include "../A34M62x/Config/board_a34m62x.h"
#endif

#elif (A34MXXX_PRODUCT == SUBFAMILY_A34M42X)
#if defined(_RTE_)
#include "a34m42x.h"
#include "config_a34m42x.h"
#include "startup_a34m42x.h"
#include "debug_a34m42x.h"
#include "board_a34m42x.h"
#else
#include "../A34M42x/Config/a34m42x.h"
#include "../A34M42x/Config/config_a34m42x.h"
#include "../A34M42x/Config/startup_a34m42x.h"
#include "../A34M42x/Config/debug_a34m42x.h"
#include "../A34M42x/Config/board_a34m42x.h"
#endif

#else
#error "Select one of A34Mxxx products for configuration at abov_config.h."
#endif /*End of A34MXXX_PRODUCT == DEV_A34M41X */

#elif (PRODUCT_SERIES == 1 && A34GXXX == 1)

#if (A34GXXX_PRODUCT == SUBFAMILY_A34G43X)
#if defined(_RTE_)
#include "a34g43x.h"
#include "config_a34g43x.h"
#include "startup_a34g43x.h"
#include "debug_a34g43x.h"
#include "board_a34g43x.h"
#else
#include "../A34G43x/Config/a34g43x.h"
#include "../A34G43x/Config/config_a34g43x.h"
#include "../A34G43x/Config/startup_a34g43x.h"
#include "../A34G43x/Config/debug_a34g43x.h"
#include "../A34G43x/Config/board_a34g43x.h"
#endif

#else
#error "Select one of A34Gxxx products for configuration at abov_config.h."
#endif /*End of A34GXXX_PRODUCT == DEV_A34G43X */

#elif (PRODUCT_SERIES == 1 && A34LXXX == 1)

#if (A34LXXX_PRODUCT == SUBFAMILY_A34L71X)
#if defined(_RTE_)
#include "a34l71x.h"
#include "config_a34l71x.h"
#include "startup_a34l71x.h"
#include "debug_a34l71x.h"
#include "board_a34l71x.h"
#else
#include "../A34L71x/Config/a34l71x.h"
#include "../A34L71x/Config/config_a34l71x.h"
#include "../A34L71x/Config/startup_a34l71x.h"
#include "../A34L71x/Config/debug_a34l71x.h"
#include "../A34L71x/Config/board_a34l71x.h"
#endif

#else
#error "Select one of A34Gxxx products for configuration at abov_config.h."
#endif /*End of A34GXXX_PRODUCT == DEV_A34G43X */

#else
#error "Select only one of series product for configuration at abov_config.h."
#endif /* End of PRODUCT_SERIES == 1 && A34MXXX == 1 */

#endif /* ABOV_CONFIG_H */
/** @} */ /* End of group ABOV CONFIG */

/** @} */ /* End of group VENDOR ABOV Semiconductor Co., Ltd. */
