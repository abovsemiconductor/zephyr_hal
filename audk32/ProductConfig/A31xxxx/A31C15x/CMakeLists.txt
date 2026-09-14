# AUDK32 SDK - A31C15x series
#
# Copyright (c) 2026 ABOV Semiconductor Co.,Ltd.
#
# SPDX-License-Identifier: BSD-3-Clause

# a31c15x.h/config_a31c15x.h/board_a31c15x.h are reached both from
# abov_config.h (used by every hal_*.c/hll_*.c under Platform/HAL/, which the
# audk32 library compiles unconditionally) and, for a31c15x.h itself, from
# soc/abov/abov32/a31xxxx/a31c15x/soc.h, which core Zephyr arch/kernel code
# includes via <zephyr/kernel.h> -> cmsis_core.h regardless of which driver
# libraries are enabled (e.g. arch/arm/core/offsets/offsets.c).
#
# EXTRN_SUBFAMILY_A31C15x/EXTRN_VARIANT_A31C156RLN (which abov_config.h and
# board_a31c15x.h need) are no longer injected from here as compile
# definitions -- abov_config.h itself #defines them from CONFIG_SOC_SERIES_
# A31C15X/CONFIG_SOC_A31C156 when __ZEPHYR__ is set, via
# ../Config/abov_config_zephyr_product.h.
zephyr_include_directories(
  ${ZEPHYR_ABOV32_MODULE_DIR}/audk32/ProductConfig/A31xxxx/Config
  ${ZEPHYR_ABOV32_MODULE_DIR}/audk32/ProductConfig/A31xxxx/A31C15x/Config
  ${ZEPHYR_ABOV32_MODULE_DIR}/audk32/Framework/CMSIS/Device/ABOV/Include
)
