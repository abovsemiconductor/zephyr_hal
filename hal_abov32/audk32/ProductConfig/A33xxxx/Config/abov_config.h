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
#define SUBFAMILY_A33G52X 0x00010000
#define SUBFAMILY_A33G72X 0x00020000
#define SUBFAMILY_A33M11X 0x00030000
#define SUBFAMILY_A33M12X 0x00040000
#define SUBFAMILY_A33G53X 0x00050000

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
#define BD_STK_A33G526_RLN_A  (SUBFAMILY_A33G52X+0x01)
#define BD_STK_A33G527_VQN_A  (SUBFAMILY_A33G52X+0x02)
#define BD_STK_A33G539_VLN_A  (SUBFAMILY_A33G53X+0x01)
#define BD_STK_A33M116_RLN_A  (SUBFAMILY_A33M11X+0x01)

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
//     <BD_STK_A33G526_RLN_A=> STK_A33G526_RLN_A
//     <BD_STK_A33G527_VQN_A=> STK_A33G527_VQN_A
//     <BD_STK_A33G539_VLN_A=> STK_A33G539_VLN_A
//     <BD_STK_A33M116_RLN_A=> STK_A33M116_RLN_A
//  <i> Select one of A31Mxxx products
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
#define TARGET_SERIAL_CHANNEL_ID BD_SERIAL_CHANNEL_ID_0 /* Don't edit this value */

//  </e>
// </h> End of ABOV Target Debug Configuration 


/* Product configuration by external development environment (PACK, CLI and Promotion Build) */
#if defined (EXTRN_SUBFAMILY_A33G52x)
#define A33GXXX 1
#define A33MXXX 0
#define A33GXXX_PRODUCT SUBFAMILY_A33G52X

#elif defined (EXTRN_SUBFAMILY_A33G53x)
#define A33GXXX 1
#define A33MXXX 0
#define A33GXXX_PRODUCT SUBFAMILY_A33G53X

#elif defined (EXTRN_SUBFAMILY_A33M11x)
#define A33GXXX 0
#define A33MXXX 1
#define A33MXXX_PRODUCT SUBFAMILY_A33M11X

#else
#error "Unknown sub family"
#endif

/* Must add new series product define for condition build */
#define PRODUCT_SERIES A33GXXX + A33MXXX

/*
//------------- <<< end of configuration section >>> --------------------------
*/

#include <stdint.h>

#if (PRODUCT_SERIES == 1 && A33GXXX == 1)

#if (A33GXXX_PRODUCT == SUBFAMILY_A33G52X)
#if defined(_RTE_)
#include "a33g52x.h"
#include "config_a33g52x.h"
#include "startup_a33g52x.h"
#include "debug_a33g52x.h"
#include "board_a33g52x.h"
#else
#include "../A33G52x/Config/a33g52x.h"
#include "../A33G52x/Config/config_a33g52x.h"
#include "../A33G52x/Config/startup_a33g52x.h"
#include "../A33G52x/Config/debug_a33g52x.h"
#include "../A33G52x/Config/board_a33g52x.h"
#endif


#elif (A33GXXX_PRODUCT == SUBFAMILY_A33G53X)
#if defined(_RTE_)
#include "a33g53x.h"
#include "config_a33g53x.h"
#include "startup_a33g53x.h"
#include "debug_a33g53x.h"
#include "board_a33g53x.h"
#else
#include "../A33G53x/Config/a33g53x.h"
#include "../A33G53x/Config/config_a33g53x.h"
#include "../A33G53x/Config/startup_a33g53x.h"
#include "../A33G53x/Config/debug_a33g53x.h"
#include "../A33G53x/Config/board_a33g53x.h"
#endif

#elif (A33GXXX_PRODUCT == SUBFAMILY_A33G72X)
#if defined(_RTE_)
#include "a33g72x.h"
#include "config_a33g72x.h"
#include "startup_a33g72x.h"
#include "debug_a33g72x.h"
#include "board_a33g72x.h"
#else
#include "../A33G72x/Config/a33g72x.h"
#include "../A33G72x/Config/config_a33g72x.h"
#include "../A33G72x/Config/startup_a33g72x.h"
#include "../A33G72x/Config/debug_a33g72x.h"
#include "../A33G72x/Config/board_a33g72x.h"
#endif

#else
#error "Select one of A33Gxxx products for configuration at abov_config.h."
#endif /* End of A33GXXX_PRODUCT == DEV_A33G52X */

#elif (PRODUCT_SERIES == 1 && A33MXXX == 1)

#if (A33MXXX_PRODUCT == SUBFAMILY_A33M11X)
#if defined(_RTE_)
#include "a33m11x.h"
#include "config_a33m11x.h"
#include "startup_a33m11x.h"
#include "debug_a33m11x.h"
#include "board_a33m11x.h"
#else
#include "../A33M11x/Config/a33m11x.h"
#include "../A33M11x/Config/config_a33m11x.h"
#include "../A33M11x/Config/startup_a33m11x.h"
#include "../A33M11x/Config/debug_a33m11x.h"
#include "../A33M11x/Config/board_a33m11x.h"
#endif

#else
#error "Select one of A33Mxxx products for configuration at abov_config.h."
#endif /* End of A33MXXX_PRODUCT == DEV_A33M11X */

#else
#error "Select only one of series product for configuration at abov_config.h."
#endif /* End of PRODUCT_SERIES == 1 && A33GXXX == 1 */

#endif /* ABOV_CONFIG_H */
/** @} */ /* End of group ABOV CONFIG */

/** @} */ /* End of group VENDOR ABOV Semiconductor Co., Ltd. */
