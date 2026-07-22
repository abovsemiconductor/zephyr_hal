# Makefile - AUDK32 SDK
#
# Copyright (c) 2026 ABOV Semiconductor Co.,Ltd.
#
# SPDX-License-Identifier: BSD-3-Clause

add_subdirectory_ifdef(CONFIG_HAS_AUDK32 audk32)
