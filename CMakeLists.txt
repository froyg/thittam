# Copyright (C) 2016-2017 HiPro IT Solutions Private Limited,
# Chennai. All rights reserved.
#
# This program and the accompanying materials are made available under
# the terms described in the LICENSE file which accompanies this
# distribution. If the LICENSE file was not attached to this
# distribution or for further clarifications, please contact
# legal@hipro.co.in.

cmake_minimum_required (VERSION 2.8)
project (thittam)

add_definitions (-DBOOST_LOG_DYN_LINK)
find_package (Boost REQUIRED COMPONENTS
  log log_setup thread date_time system program_options
  )

find_package (Threads)
find_package (PkgConfig)

pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

add_subdirectory (googletest)
add_subdirectory (src)
# add_subdirectory (tests)
