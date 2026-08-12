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
#define SUBFAMILY_A31G11X 0x00010000
#define SUBFAMILY_A31G12X 0x00020000
#define SUBFAMILY_A31G21X 0x00030000
#define SUBFAMILY_A31G22X 0x00040000
#define SUBFAMILY_A31G31X 0x00050000
#define SUBFAMILY_A31G32X 0x00060000
#define SUBFAMILY_A31M22X 0x00070000
#define SUBFAMILY_A31T21X 0x00080000
#define SUBFAMILY_A31L12X 0x00090000
#define SUBFAMILY_A31L21X 0x000A0000
#define SUBFAMILY_A31L22X 0x000B0000
#define SUBFAMILY_A31C14X 0x000C0000
#define SUBFAMILY_A31C12X 0x000D0000
#define SUBFAMILY_A31S13X 0x000E0000
#define SUBFAMILY_A31G33X 0x000F0000
#define SUBFAMILY_A31G34X 0x00100000
#define SUBFAMILY_A31T41X 0x00200000
#define SUBFAMILY_A31C11X 0x00300000
#define SUBFAMILY_A31C15X 0x00400000
#define SUBFAMILY_A31T51X 0x00500000

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
#define BD_STK_A31G112_CLN_A  (SUBFAMILY_A31G11X + 0x01)
#define BD_STK_A31G123_MLN_A  (SUBFAMILY_A31G12X + 0x01)
#define BD_STK_A31G213_CL2N_A (SUBFAMILY_A31G21X + 0x01)
#define BD_STK_A31T216_RLN_A  (SUBFAMILY_A31T21X + 0x01)
#define BD_STK_A31G226_ML2N_A (SUBFAMILY_A31G22X + 0x01)
#define BD_STK_A31G314_MMN_A  (SUBFAMILY_A31G31X + 0x01)
#define BD_STK_A31G324_RLN_A  (SUBFAMILY_A31G32X + 0x01)
#define BD_STK_A31L123_RLN_A  (SUBFAMILY_A31L12X + 0x01)
#define BD_STK_A31L214_MLN_A  (SUBFAMILY_A31L21X + 0x01)
#define BD_STK_A31L222_FRN_A  (SUBFAMILY_A31L22X + 0x01)
#define BD_STK_A31C144_RLN_A  (SUBFAMILY_A31C14X + 0x01)
#define BD_STK_A31C122_KYN_A  (SUBFAMILY_A31C12X + 0x01)
#define BD_STK_A31S134_RLN_A  (SUBFAMILY_A31S13X + 0x01)
#define BD_STK_A31G336_RLN_A  (SUBFAMILY_A31G33X + 0x01)
#define BD_STK_A31G346_RLN_A  (SUBFAMILY_A31G34X + 0x01)
#define BD_STK_A31T413_RLN_A  (SUBFAMILY_A31T41X + 0x01)
#define BD_STK_A31C111_FUN_A  (SUBFAMILY_A31C11X + 0x01)
#define BD_STK_A31C156_RLN_A  (SUBFAMILY_A31C15X + 0x01)
#define BD_STK_A31T518_RLN_A  (SUBFAMILY_A31T51X + 0x01)

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
//     <BD_STK_A31G112_CLN_A=> StarterKit-A31G112CLN
//     <BD_STK_A31G123_MLN_A=> StarterKit-A31G123MLN
//     <BD_STK_A31G213_CL2N_A=> StarterKit-A31G213CL2N
//     <BD_STK_A31T216_RLN_A=> StarterKit-A31T216RLN
//     <BD_STK_A31G226_ML2N_A=> StarterKit-A31G226ML2N
//     <BD_STK_A31G314_MMN_A=> StarterKit-A31G314MMN
//     <BD_STK_A31G324_RLN_A=> StarterKit-A31G324RLN
//     <BD_STK_A31G336_RLN_A=> StarterKit-A31G336RLN
//     <BD_STK_A31G346_RLN_A=> StarterKit-A31G346RLN
//     <BD_STK_A31L123_RLN_A=> StarterKit-A31L123RLN
//     <BD_STK_A31L214_MLN_A=> StarterKit-A31L214MLN
//     <BD_STK_A31L222_FRN_A=> StarterKit-A31L222FRN
//     <BD_STK_A31C144_RLN_A=> StarterKit-A31C144RLN
//     <BD_STK_A31C122_KYN_A=> StarterKit-A31C122KYN
//     <BD_STK_A31S134_RLN_A=> StarterKit-A31S134RLN
//     <BD_STK_A31C111_FUN_A=> StarterKit-A31C111FUN
//     <BD_STK_A31C156_RLN_A=> StarterKit-A31C156RLN
//     <BD_STK_A31T518_RLN_A=> StarterKit-A31T518RLN
//  <i> Select one of A31xxxx products
//  <i> Default: BARE
#define TARGET_BOARD BD_BARE

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
#if defined (EXTRN_SUBFAMILY_A31G11x)
#define A31GXXX 1
#define A31MXXX 0
#define A31TXXX 0
#define A31LXXX 0
#define A31CXXX 0
#define A31SXXX 0
#define A31GXXX_PRODUCT SUBFAMILY_A31G11X

#elif defined (EXTRN_SUBFAMILY_A31G12x)
#define A31GXXX 1
#define A31MXXX 0
#define A31TXXX 0
#define A31LXXX 0
#define A31CXXX 0
#define A31SXXX 0
#define A31GXXX_PRODUCT SUBFAMILY_A31G12X

#elif defined (EXTRN_SUBFAMILY_A31G21x)
#define A31GXXX 1
#define A31MXXX 0
#define A31TXXX 0
#define A31LXXX 0
#define A31CXXX 0
#define A31SXXX 0
#define A31GXXX_PRODUCT SUBFAMILY_A31G21X

#elif defined (EXTRN_SUBFAMILY_A31G22x)
#define A31GXXX 1
#define A31MXXX 0
#define A31TXXX 0
#define A31LXXX 0
#define A31CXXX 0
#define A31SXXX 0
#define A31GXXX_PRODUCT SUBFAMILY_A31G22X

#elif defined (EXTRN_SUBFAMILY_A31G31x)
#define A31GXXX 1
#define A31MXXX 0
#define A31TXXX 0
#define A31LXXX 0
#define A31CXXX 0
#define A31SXXX 0
#define A31GXXX_PRODUCT SUBFAMILY_A31G31X

#elif defined (EXTRN_SUBFAMILY_A31G32x)
#define A31GXXX 1
#define A31MXXX 0
#define A31TXXX 0
#define A31LXXX 0
#define A31CXXX 0
#define A31SXXX 0
#define A31GXXX_PRODUCT SUBFAMILY_A31G32X

#elif defined (EXTRN_SUBFAMILY_A31M22x)
#define A31GXXX 0
#define A31MXXX 1
#define A31TXXX 0
#define A31LXXX 0
#define A31CXXX 0
#define A31SXXX 0
#define A31MXXX_PRODUCT SUBFAMILY_A31M22X

#elif defined (EXTRN_SUBFAMILY_A31T21x)
#define A31GXXX 0
#define A31MXXX 0
#define A31TXXX 1
#define A31LXXX 0
#define A31CXXX 0
#define A31SXXX 0
#define A31TXXX_PRODUCT SUBFAMILY_A31T21X

#elif defined (EXTRN_SUBFAMILY_A31L12x)
#define A31GXXX 0
#define A31MXXX 0
#define A31TXXX 0
#define A31LXXX 1
#define A31CXXX 0
#define A31SXXX 0
#define A31LXXX_PRODUCT SUBFAMILY_A31L12X

#elif defined (EXTRN_SUBFAMILY_A31L21x)
#define A31GXXX 0
#define A31MXXX 0
#define A31TXXX 0
#define A31LXXX 1
#define A31CXXX 0
#define A31SXXX 0
#define A31LXXX_PRODUCT SUBFAMILY_A31L21X

#elif defined (EXTRN_SUBFAMILY_A31L22x)
#define A31GXXX 0
#define A31MXXX 0
#define A31TXXX 0
#define A31LXXX 1
#define A31CXXX 0
#define A31SXXX 0
#define A31LXXX_PRODUCT SUBFAMILY_A31L22X

#elif defined (EXTRN_SUBFAMILY_A31C14x)
#define A31GXXX 0
#define A31MXXX 0
#define A31TXXX 0
#define A31LXXX 0
#define A31CXXX 1
#define A31SXXX 0
#define A31CXXX_PRODUCT SUBFAMILY_A31C14X

#elif defined (EXTRN_SUBFAMILY_A31C12x)
#define A31GXXX 0
#define A31MXXX 0
#define A31TXXX 0
#define A31LXXX 0
#define A31CXXX 1
#define A31SXXX 0
#define A31CXXX_PRODUCT SUBFAMILY_A31C12X

#elif defined (EXTRN_SUBFAMILY_A31S13x)
#define A31GXXX 0
#define A31MXXX 0
#define A31TXXX 0
#define A31LXXX 0
#define A31CXXX 0
#define A31SXXX 1
#define A31SXXX_PRODUCT SUBFAMILY_A31S13X

#elif defined (EXTRN_SUBFAMILY_A31G33x)
#define A31GXXX 1
#define A31MXXX 0
#define A31TXXX 0
#define A31LXXX 0
#define A31CXXX 0
#define A31SXXX 0
#define A31GXXX_PRODUCT SUBFAMILY_A31G33X

#elif defined (EXTRN_SUBFAMILY_A31G34x)
#define A31GXXX 1
#define A31MXXX 0
#define A31TXXX 0
#define A31LXXX 0
#define A31CXXX 0
#define A31SXXX 0
#define A31GXXX_PRODUCT SUBFAMILY_A31G34X

#elif defined (EXTRN_SUBFAMILY_A31T41x)
#define A31GXXX 0
#define A31MXXX 0
#define A31TXXX 1
#define A31LXXX 0
#define A31CXXX 0
#define A31SXXX 0
#define A31TXXX_PRODUCT SUBFAMILY_A31T41X

#elif defined (EXTRN_SUBFAMILY_A31C11x)
#define A31GXXX 0
#define A31MXXX 0
#define A31TXXX 0
#define A31LXXX 0
#define A31CXXX 1
#define A31SXXX 0
#define A31CXXX_PRODUCT SUBFAMILY_A31C11X

#elif defined (EXTRN_SUBFAMILY_A31C15x)
#define A31GXXX 0
#define A31MXXX 0
#define A31TXXX 0
#define A31LXXX 0
#define A31CXXX 1
#define A31SXXX 0
#define A31CXXX_PRODUCT SUBFAMILY_A31C15X

#elif defined (EXTRN_SUBFAMILY_A31T51x)
#define A31GXXX 0
#define A31MXXX 0
#define A31TXXX 1
#define A31LXXX 0
#define A31CXXX 0
#define A31SXXX 0
#define A31TXXX_PRODUCT SUBFAMILY_A31T51X

#else
#error "Unknown sub family"
#endif

/* Must add new series product define for condition build */
#define PRODUCT_SERIES A31GXXX + A31MXXX + A31TXXX + A31LXXX + A31CXXX + A31SXXX

/*
//------------- <<< end of configuration section >>> --------------------------
*/
#include <stdint.h>

#if (PRODUCT_SERIES == 1 && A31GXXX == 1)

#if (A31GXXX_PRODUCT == SUBFAMILY_A31G11X)
#if defined(_RTE_)
#include "a31g11x.h"
#include "config_a31g11x.h"
#include "startup_a31g11x.h"
#include "debug_a31g11x.h"
#include "board_a31g11x.h"
#else
#include "../A31G11x/Config/a31g11x.h"
#include "../A31G11x/Config/config_a31g11x.h"
#include "../A31G11x/Config/startup_a31g11x.h"
#include "../A31G11x/Config/debug_a31g11x.h"
#include "../A31G11x/Config/board_a31g11x.h"
#endif

#elif (A31GXXX_PRODUCT == SUBFAMILY_A31G12X)
#if defined(_RTE_)
#include "a31g12x.h"
#include "config_a31g12x.h"
#include "startup_a31g12x.h"
#include "debug_a31g12x.h"
#include "board_a31g12x.h"
#else
#include "../A31G12x/Config/a31g12x.h"
#include "../A31G12x/Config/config_a31g12x.h"
#include "../A31G12x/Config/startup_a31g12x.h"
#include "../A31G12x/Config/debug_a31g12x.h"
#include "../A31G12x/Config/board_a31g12x.h"
#endif

#elif (A31GXXX_PRODUCT == SUBFAMILY_A31G21X)
#if defined(_RTE_)
#include "a31g21x.h"
#include "config_a31g21x.h"
#include "startup_a31g21x.h"
#include "debug_a31g21x.h"
#include "board_a31g21x.h"
#else
#include "../A31G21x/Config/a31g21x.h"
#include "../A31G21x/Config/config_a31g21x.h"
#include "../A31G21x/Config/startup_a31g21x.h"
#include "../A31G21x/Config/debug_a31g21x.h"
#include "../A31G21x/Config/board_a31g21x.h"
#endif

#elif (A31GXXX_PRODUCT == SUBFAMILY_A31G22X)
#if defined(_RTE_)
#include "a31g22x.h"
#include "config_a31g22x.h"
#include "startup_a31g22x.h"
#include "debug_a31g22x.h"
#include "board_a31g22x.h"
#else
#include "../A31G22x/Config/a31g22x.h"
#include "../A31G22x/Config/config_a31g22x.h"
#include "../A31G22x/Config/startup_a31g22x.h"
#include "../A31G22x/Config/debug_a31g22x.h"
#include "../A31G22x/Config/board_a31g22x.h"
#endif

#elif (A31GXXX_PRODUCT == SUBFAMILY_A31G31X)
#if defined(_RTE_)
#include "a31g31x.h"
#include "config_a31g31x.h"
#include "startup_a31g31x.h"
#include "debug_a31g31x.h"
#include "board_a31g31x.h"
#else
#include "../A31G31x/Config/a31g31x.h"
#include "../A31G31x/Config/config_a31g31x.h"
#include "../A31G31x/Config/startup_a31g31x.h"
#include "../A31G31x/Config/debug_a31g31x.h"
#include "../A31G31x/Config/board_a31g31x.h"
#endif

#elif (A31GXXX_PRODUCT == SUBFAMILY_A31G32X)
#if defined(_RTE_)
#include "a31g32x.h"
#include "config_a31g32x.h"
#include "startup_a31g32x.h"
#include "debug_a31g32x.h"
#include "board_a31g32x.h"
#else
#include "../A31G32x/Config/a31g32x.h"
#include "../A31G32x/Config/config_a31g32x.h"
#include "../A31G32x/Config/startup_a31g32x.h"
#include "../A31G32x/Config/debug_a31g32x.h"
#include "../A31G32x/Config/board_a31g32x.h"
#endif

#elif (A31GXXX_PRODUCT == SUBFAMILY_A31G33X)
#if defined(_RTE_)
#include "a31g33x.h"
#include "config_a31g33x.h"
#include "startup_a31g33x.h"
#include "debug_a31g33x.h"
#include "board_a31g33x.h"
#else
#include "../A31G33x/Config/a31g33x.h"
#include "../A31G33x/Config/config_a31g33x.h"
#include "../A31G33x/Config/startup_a31g33x.h"
#include "../A31G33x/Config/debug_a31g33x.h"
#include "../A31G33x/Config/board_a31g33x.h"
#endif

#elif (A31GXXX_PRODUCT == SUBFAMILY_A31G34X)
#if defined(_RTE_)
#include "a31g34x.h"
#include "config_a31g34x.h"
#include "startup_a31g34x.h"
#include "debug_a31g34x.h"
#include "board_a31g34x.h"
#else
#include "../A31G34x/Config/a31g34x.h"
#include "../A31G34x/Config/config_a31g34x.h"
#include "../A31G34x/Config/startup_a31g34x.h"
#include "../A31G34x/Config/debug_a31g34x.h"
#include "../A31G34x/Config/board_a31g34x.h"
#endif

#else
#error "Select one of A31Gxxx products for configuration at abov_config.h."
#endif /* End of A31GXXX_PRODUCT == SUBFAMILY_A31G11X */

#elif (PRODUCT_SERIES == 1 && A31MXXX == 1)

#if (A31MXXX_PRODUCT == SUBFAMILY_A31M22X)
#if defined(_RTE_)
#include "a31m22x.h"
#include "config_a31m22x.h"
#include "startup_a31m22x.h"
#include "debug_a31m22x.h"
#include "board_a31m22x.h"
#else
#include "../A31M22x/Config/a31m22x.h"
#include "../A31M22x/Config/config_a31m22x.h"
#include "../A31M22x/Config/startup_a31m22x.h"
#include "../A31M22x/Config/debug_a31m22x.h"
#include "../A31M22x/Config/board_a31m22x.h"
#endif /* End of A31MXXX_PRODUCT == SUBFAMILY_A31M22X */

#else
#error "Select one of A31Mxxx products for configuration at abov_config.h."
#endif /* End of A31MXXX_PRODUCT == SUBFAMILY_A31G11X */

#elif (PRODUCT_SERIES == 1 && A31TXXX == 1)

#if (A31TXXX_PRODUCT == SUBFAMILY_A31T21X)
#if defined(_RTE_)
#include "a31t21x.h"
#include "config_a31t21x.h"
#include "startup_a31t21x.h"
#include "debug_a31t21x.h"
#include "board_a31t21x.h"
#else
#include "../A31T21x/Config/a31t21x.h"
#include "../A31T21x/Config/config_a31t21x.h"
#include "../A31T21x/Config/startup_a31t21x.h"
#include "../A31T21x/Config/debug_a31t21x.h"
#include "../A31T21x/Config/board_a31t21x.h"
#endif

#elif (A31TXXX_PRODUCT == SUBFAMILY_A31T41X)
#if defined(_RTE_)
#include "a31t41x.h"
#include "config_a31t41x.h"
#include "startup_a31t41x.h"
#include "debug_a31t41x.h"
#include "board_a31t41x.h"
#else
#include "../A31T41x/Config/a31t41x.h"
#include "../A31T41x/Config/config_a31t41x.h"
#include "../A31T41x/Config/startup_a31t41x.h"
#include "../A31T41x/Config/debug_a31t41x.h"
#include "../A31T41x/Config/board_a31t41x.h"
#endif

#elif (A31TXXX_PRODUCT == SUBFAMILY_A31T51X)
#if defined(_RTE_)
#include "a31t51x.h"
#include "config_a31t51x.h"
#include "startup_a31t51x.h"
#include "debug_a31t51x.h"
#include "board_a31t51x.h"
#else
#include "../A31T51x/Config/a31t51x.h"
#include "../A31T51x/Config/config_a31t51x.h"
#include "../A31T51x/Config/startup_a31t51x.h"
#include "../A31T51x/Config/debug_a31t51x.h"
#include "../A31T51x/Config/board_a31t51x.h"
#endif

#else
#error "Select one of A31Txxx products for configuration at abov_config.h."
#endif /* End of A31TXXX_PRODUCT == SUBFAMILY_A31T21X */

#elif (PRODUCT_SERIES == 1 && A31LXXX == 1)

#if (A31LXXX_PRODUCT == SUBFAMILY_A31L12X)
#if defined(_RTE_)
#include "a31l12x.h"
#include "config_a31l12x.h"
#include "startup_a31l12x.h"
#include "debug_a31l12x.h"
#include "board_a31l12x.h"
#else
#include "../A31L12x/Config/a31l12x.h"
#include "../A31L12x/Config/config_a31l12x.h"
#include "../A31L12x/Config/startup_a31l12x.h"
#include "../A31L12x/Config/debug_a31l12x.h"
#include "../A31L12x/Config/board_a31l12x.h"
#endif

#elif (A31LXXX_PRODUCT == SUBFAMILY_A31L21X)
#if defined(_RTE_)
#include "a31l21x.h"
#include "config_a31l21x.h"
#include "startup_a31l21x.h"
#include "debug_a31l21x.h"
#include "board_a31l21x.h"
#else
#include "../A31L21x/Config/a31l21x.h"
#include "../A31L21x/Config/config_a31l21x.h"
#include "../A31L21x/Config/startup_a31l21x.h"
#include "../A31L21x/Config/debug_a31l21x.h"
#include "../A31L21x/Config/board_a31l21x.h"
#endif

#elif (A31LXXX_PRODUCT == SUBFAMILY_A31L22X)
#if defined(_RTE_)
#include "a31l22x.h"
#include "config_a31l22x.h"
#include "startup_a31l22x.h"
#include "debug_a31l22x.h"
#include "board_a31l22x.h"
#else
#include "../A31L22x/Config/a31l22x.h"
#include "../A31L22x/Config/config_a31l22x.h"
#include "../A31L22x/Config/startup_a31l22x.h"
#include "../A31L22x/Config/debug_a31l22x.h"
#include "../A31L22x/Config/board_a31l22x.h"
#endif

#else
#error "Select one of A31Lxxx products for configuration at abov_config.h."
#endif /* End of A31LXXX_PRODUCT == SUBFAMILY_A31L12X */

#elif (PRODUCT_SERIES == 1 && A31CXXX == 1)

#if (A31CXXX_PRODUCT == SUBFAMILY_A31C14X)
#if defined(_RTE_)
#include "a31c14x.h"
#include "config_a31c14x.h"
#include "startup_a31c14x.h"
#include "debug_a31c14x.h"
#include "board_a31c14x.h"
#else
#include "../A31C14x/Config/a31c14x.h"
#include "../A31C14x/Config/config_a31c14x.h"
#include "../A31C14x/Config/startup_a31c14x.h"
#include "../A31C14x/Config/debug_a31c14x.h"
#include "../A31C14x/Config/board_a31c14x.h"
#endif

#elif (A31CXXX_PRODUCT == SUBFAMILY_A31C12X)
#if defined(_RTE_)
#include "a31c12x.h"
#include "config_a31c12x.h"
#include "startup_a31c12x.h"
#include "debug_a31c12x.h"
#include "board_a31c12x.h"
#else
#include "../A31C12x/Config/a31c12x.h"
#include "../A31C12x/Config/config_a31c12x.h"
#include "../A31C12x/Config/startup_a31c12x.h"
#include "../A31C12x/Config/debug_a31c12x.h"
#include "../A31C12x/Config/board_a31c12x.h"
#endif

#elif (A31CXXX_PRODUCT == SUBFAMILY_A31C11X)
#if defined(_RTE_)
#include "a31c11x.h"
#include "config_a31c11x.h"
#include "startup_a31c11x.h"
#include "debug_a31c11x.h"
#include "board_a31c11x.h"
#else
#include "../A31C11x/Config/a31c11x.h"
#include "../A31C11x/Config/config_a31c11x.h"
#include "../A31C11x/Config/startup_a31c11x.h"
#include "../A31C11x/Config/debug_a31c11x.h"
#include "../A31C11x/Config/board_a31c11x.h"
#endif

#elif (A31CXXX_PRODUCT == SUBFAMILY_A31C15X)
#if defined(_RTE_)
#include "a31c15x.h"
#include "config_a31c15x.h"
#include "startup_a31c15x.h"
#include "debug_a31c15x.h"
#include "board_a31c15x.h"
#else
#include "../A31C15x/Config/a31c15x.h"
#include "../A31C15x/Config/config_a31c15x.h"
#include "../A31C15x/Config/startup_a31c15x.h"
#include "../A31C15x/Config/debug_a31c15x.h"
#include "../A31C15x/Config/board_a31c15x.h"
#endif

#else
#error "Select one of A31Cxxx products for configuration at abov_config.h."
#endif /* End of A31CXXX_PRODUCT == SUBFAMILY_A31C14X */

#elif (PRODUCT_SERIES == 1 && A31SXXX == 1)

#if (A31SXXX_PRODUCT == SUBFAMILY_A31S13X)
#if defined(_RTE_)
#include "a31s13x.h"
#include "config_a31s13x.h"
#include "startup_a31s13x.h"
#include "debug_a31s13x.h"
#include "board_a31s13x.h"
#else
#include "../A31S13x/Config/a31s13x.h"
#include "../A31S13x/Config/config_a31s13x.h"
#include "../A31S13x/Config/startup_a31s13x.h"
#include "../A31S13x/Config/debug_a31s13x.h"
#include "../A31S13x/Config/board_a31s13x.h"
#endif

#else
#error "Select one of A31Sxxx products for configuration at abov_config.h."
#endif /* End of A31SXXX_PRODUCT == SUBFAMILY_A31S13X */

#else
#error "Select only one of series product for configuration at abov_config.h."
#endif /* End of PRODUCT_SERIES == 1 && A31GXXX == 1 */

#endif /* ABOV_CONFIG_H */
/** @} */ /* End of group ABOV CONFIG */

/** @} */ /* End of group VENDOR ABOV Semiconductor Co., Ltd. */
