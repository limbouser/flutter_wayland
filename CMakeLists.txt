# Copyright 2018 The Flutter Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

cmake_minimum_required(VERSION 3.5.2)

project(flutter_wayland)

find_package(PkgConfig)
pkg_check_modules(DEPS REQUIRED wayland-client wayland-egl egl)

set(FLUTTER_WAYLAND_SRC
    src/flutter_application.cc
    src/main.cc
    src/utils.cc
    src/wayland_display.cc
)

add_executable(flutter_wayland ${FLUTTER_WAYLAND_SRC})

target_compile_options(flutter_wayland PUBLIC ${DEPS_CFLAGS})

if(NOT FLUTTER_ENGINE_LIBRARY)
    set(FLUTTER_ENGINE_LIBRARY ${CMAKE_SYSROOT}/usr/lib/libflutter_engine.so)
endif()

target_link_libraries(flutter_wayland PUBLIC 
    ${FLUTTER_ENGINE_LIBRARY}
    ${DEPS_LINK_LIBRARIES}
)

target_include_directories(flutter_wayland PUBLIC ${DEPS_INCLUDE_DIRS} ${FLUTTER_INCLUDE_DIR})

install(TARGETS flutter_wayland RUNTIME DESTINATION bin)

