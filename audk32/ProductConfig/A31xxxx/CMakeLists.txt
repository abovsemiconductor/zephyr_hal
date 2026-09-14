# AUDK32 SDK - A31xxxx product line (Cortex-M0+)
#
# Copyright (c) 2026 ABOV Semiconductor Co.,Ltd.
#
# SPDX-License-Identifier: BSD-3-Clause

# Only the series selected by Kconfig is added; see
# .../A31C15x/CMakeLists.txt for what that series-level file sets up.
add_subdirectory_ifdef(CONFIG_SOC_SERIES_A31C15X A31C15x)
# add_subdirectory_ifdef(CONFIG_SOC_SERIES_A31T51X A31T51x)
