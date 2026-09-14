/*
 * Copyright (c) 2026 ABOV Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* Only included from abov_config.h, and only when __ZEPHYR__ is defined
 * (see the Zephyr-only #include there). Translates the Kconfig symbols a
 * Zephyr build already selected for the A31xxxx product line into the
 * EXTRN_SUBFAMILY_xxx/EXTRN_VARIANT_xxx macros abov_config.h and the
 * per-subfamily board_*.h files key off of, so a Keil/IAR build of this
 * same SDK keeps picking them via its own project settings, unaffected.
 *
 * CONFIG_SOC_SERIES_A31C15X/CONFIG_SOC_A31C156 are visible here without any
 * CMake compile definition: every translation unit in a Zephyr build gets
 * Kconfig symbols via the toolchain's -imacros <autoconf.h>
 * (see zephyr/CMakeLists.txt).
 *
 * Add one block per subfamily/variant below as Zephyr support for more
 * A31xxxx series is added.
 */

#if defined(CONFIG_SOC_SERIES_A31C15X)
#define EXTRN_SUBFAMILY_A31C15x
#if defined(CONFIG_SOC_A31C156)
#define EXTRN_VARIANT_A31C156RLN
#endif
#endif
