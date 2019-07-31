# Copyright (C) 2016-2017 HiPro IT Solutions Private Limited,
# Chennai. All rights reserved.
#
# This program and the accompanying materials are made available under
# the terms described in the LICENSE file which accompanies this
# distribution. If the LICENSE file was not attached to this
# distribution or for further clarifications, please contact
# legal@hipro.co.in.

set (CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} -std=gnu++1y -Wall -Werror")

add_executable (runtests
  test_util.cxx
  main.cxx
  )

target_include_directories (runtests
  PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  )

target_link_libraries(runtests
  app
  gmock
  gtest
  )
