# AUDK32 SDK - HAL/HLL sources
#
# Copyright (c) 2026 ABOV Semiconductor Co.,Ltd.
#
# SPDX-License-Identifier: BSD-3-Clause

# Public HAL/HLL headers (hll_*.h, hal_*.h, type/*.h) and the HPL support headers
# (hpl_nmi.h, hpl_dma.h) are included unqualified (e.g. <hll_usart.h>) by both the
# vendor sources below and by the zephyr/drivers/*_abov32.c wrappers, so these
# directories must be on the global include path, not just this library's.
#
# Framework/CMSIS/Core/Include is where the ARM CMSIS-Core headers
# (core_cm0plus.h, cmsis_compiler.h, ...) are expected to land -- not yet
# present in this checkout. a31c15x.h and system_a31xxxx.c both need them to
# compile; nothing in this module can build until they're added.
#
zephyr_include_directories(
  Platform/HAL/Include
  Platform/HAL/HPL/Include
  Framework/CMSIS/Core/Include
)

# _RTE_ just tells abov_config.h to honor its Keil-RTE-style overrides instead
# of the hand-edited TARGET_BOARD default meant for Keil's Configuration
# Wizard; it's the same switch for every product line, so it's fine here.
#
# AUDK32_FEATURE_HLL_SUPPORT selects the portable HLL_*() wrapper layer
# (hll_*.h) over direct SFR-macro access inside the hal_*.c sources -- an
# implementation choice of this common HAL tree itself, not a per-chip
# trait, so it belongs here rather than in a per-series CMakeLists.txt like
# EXTRN_SUBFAMILY_*/EXTRN_VARIANT_* below.
zephyr_compile_definitions(
  _RTE_
  AUDK32_FEATURE_HLL_SUPPORT
)

# Each hal_*.c/hll_*.c/hpl_*.c file guards its entire body with #if defined(_XXX),
# where _XXX is only defined for the peripherals present on the selected chip
# (see config_a31c15x.h). Compiling the whole tree and letting those guards
# no-op unused peripherals matches how the vendor SDK is meant to be consumed.
file(GLOB_RECURSE AUDK32_HAL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Platform/HAL/*.c)

zephyr_library()
zephyr_library_sources(
  ${AUDK32_HAL_SOURCES}
  Framework/CMSIS/Device/ABOV/Source/system_a31xxxx.c
)

# ProductConfig/<product line> is where the product-line/series/soc-specific
# config headers and CMSIS device headers live (see ProductConfig/A31xxxx/
# CMakeLists.txt). Each one wires its own include paths/defines directly into
# the specific zephyr driver targets that need them (gpio/serial/clock_control/
# pinctrl), so adding a new product line here never touches those drivers.
add_subdirectory_ifdef(CONFIG_SOC_PRODUCT_LINE_A31XXXX ProductConfig/A31xxxx)
# add_subdirectory_ifdef(CONFIG_SOC_PRODUCT_LINE_A33XXXX ProductConfig/A33xxxx)
# add_subdirectory_ifdef(CONFIG_SOC_PRODUCT_LINE_A34XXXX ProductConfig/A34xxxx)
