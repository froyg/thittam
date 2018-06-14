# Copyright (C) 2016-2017 HiPro IT Solutions Private Limited,
# Chennai. All rights reserved.
#
# This program and the accompanying materials are made available under
# the terms described in the LICENSE file which accompanies this
# distribution. If the LICENSE file was not attached to this
# distribution or for further clarifications, please contact
# legal@hipro.co.in.

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  string(REGEX REPLACE "\\..*$" "" GCC_MAJOR_VERSION ${CMAKE_CXX_COMPILER_VERSION})
  if ("${GCC_MAJOR_VERSION}" STREQUAL "8")
    set (CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} -std=gnu++1y -Wall -Werror -Wno-parentheses")
  endif()
else()
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1y -Wall -Werror")
endif()

set (RESOURCE_DIR ${CMAKE_SOURCE_DIR}/src/resources)
set (GRESOURCE_XML ${RESOURCE_DIR}/interfaces.gresources.xml)
set (GRESOURCE_C interfaces.gresources.c)

# Target: interfaces.gresources.c
# Depends: All .glade files and .xml configuration
# Command: glib-compile-resources
# Directory: /src/resources
add_custom_command(OUTPUT ${GRESOURCE_C}
  COMMAND glib-compile-resources --target ${GRESOURCE_C} --generate-source --sourcedir ${RESOURCE_DIR} ${GRESOURCE_XML}
  MAIN_DEPENDENCY ${GRESOURCE_XML}
  DEPENDS
  ${RESOURCE_DIR}/gantt-view.glade
  ${RESOURCE_DIR}/main.glade
  ${RESOURCE_DIR}/main-view.glade
  ${RESOURCE_DIR}/project-view.glade
  ${RESOURCE_DIR}/req-form.glade
  ${RESOURCE_DIR}/resources-view.glade
  ${RESOURCE_DIR}/resource-usage-view.glade
  ${RESOURCE_DIR}/wbs-view.glade
  COMMENT "Generating ${GRESOURCE_C}")

add_library (app
  app_impl.cxx
  common.cxx
  config_impl.cxx
  gantt-controller_impl.cxx
  gantt-view_impl.cxx
  log.cxx
  main-controller_impl.cxx
  main-view_impl.cxx
  project-controller_impl.cxx
  project-factory_impl.cxx
  project-ui-factory_impl.cxx
  project-view_impl.cxx
  project_impl.cxx
  resource-usage-controller_impl.cxx
  resource-usage-view_impl.cxx
  resources-controller_impl.cxx
  resources-view_impl.cxx
  task.cxx
  util.cxx
  wbs-controller_impl.cxx
  wbs-gtk-tree-model.cxx
  wbs-view_impl.cxx
  wbs_impl.cxx
  )


target_include_directories(app
  PUBLIC ${GTKMM_INCLUDE_DIRS}
  )

target_link_libraries (app
  ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES}
  ${GTKMM_LIBRARIES}
  )

add_executable (thittam
  main.cxx
  ${GRESOURCE_C}
  )

target_link_libraries (thittam
  app
  )

install (TARGETS thittam DESTINATION bin)
