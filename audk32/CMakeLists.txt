# AUDK32 SDK - HAL/HLL sources
#
# Copyright (c) 2026 ABOV Semiconductor Co.,Ltd.
#
# SPDX-License-Identifier: BSD-3-Clause

zephyr_include_directories(
  Platform/HAL/Include
  Platform/HAL/HPL/Include
  Framework/CMSIS/Core/Include
)

file(GLOB_RECURSE AUDK32_HAL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Platform/HAL/*.c)

zephyr_library()
zephyr_library_sources(
  ${AUDK32_HAL_SOURCES}
  Framework/CMSIS/Device/ABOV/Source/system_a31xxxx.c
)

add_subdirectory_ifdef(CONFIG_SOC_PRODUCT_LINE_A31XXXX ProductConfig/A31xxxx)
# add_subdirectory_ifdef(CONFIG_SOC_PRODUCT_LINE_A33XXXX ProductConfig/A33xxxx)
# add_subdirectory_ifdef(CONFIG_SOC_PRODUCT_LINE_A34XXXX ProductConfig/A34xxxx)
