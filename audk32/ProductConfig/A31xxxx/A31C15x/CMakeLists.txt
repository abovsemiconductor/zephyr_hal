# AUDK32 SDK - A31C15x series
#
# Copyright (c) 2026 ABOV Semiconductor Co.,Ltd.
#
# SPDX-License-Identifier: BSD-3-Clause

# a31c15x.h/config_a31c15x.h are reached both from soc/abov/abov32/a31xxxx/
# a31c15x/soc.h (included from core Zephyr arch/kernel code via
# <zephyr/kernel.h> -> cmsis_core.h, regardless of which driver libraries are
# enabled -- e.g. arch/arm/core/offsets/offsets.c) and from every hal_*.c/
# hll_*.c under Platform/HAL/ in the audk32 library itself (it compiles that
# whole tree unconditionally; see audk32/CMakeLists.txt). Both the paths and
# the EXTRN_SUBFAMILY_A31C15x/EXTRN_VARIANT_A31C156RLN defines that pick the
# right branch inside abov_config.h are therefore needed well beyond the
# zephyr/drivers/*_abov32.c wrappers, so both are global here rather than
# scoped to those drivers' targets.
zephyr_include_directories(
  ${ZEPHYR_ABOV32_MODULE_DIR}/audk32/ProductConfig/A31xxxx/Config
  ${ZEPHYR_ABOV32_MODULE_DIR}/audk32/ProductConfig/A31xxxx/A31C15x/Config
  ${ZEPHYR_ABOV32_MODULE_DIR}/audk32/Framework/CMSIS/Device/ABOV/Include
)

zephyr_compile_definitions(EXTRN_SUBFAMILY_A31C15x)
if(CONFIG_SOC_A31C156)
  zephyr_compile_definitions(EXTRN_VARIANT_A31C156RLN)
endif()
