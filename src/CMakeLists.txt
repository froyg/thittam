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

add_library (app
  app_impl.cxx
  log.cxx
  common.cxx
  config_impl.cxx
  latex_impl.cxx
  main-view_impl.cxx
  req-tree_impl.cxx
  req-tree-view_impl.cxx
  req-view_impl.cxx
  )

target_include_directories(app
  PUBLIC ${GTKMM_INCLUDE_DIRS}
  )

target_link_libraries (app
  ${Threads}
  ${Boost_LIBRARIES}
  ${GTKMM_LIBRARIES}  
  )

add_executable (thittam
  main.cxx
  interfaces.gresources.c  
  )

target_link_libraries (thittam
  app
  )

install (TARGETS thittam DESTINATION bin)
