cmake_minimum_required(VERSION 3.15)
project(pluginTest C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(p4_test SHARED
  src/main.c
  src/interfaces/interface.h
  src/interfaces/interface.c
  src/interfaces/plugin_callbacks.h
  src/interfaces/plugin_callbacks.c
  src/interfaces/ns_interface.h
  src/interfaces/ns_interface.c
  src/interfaces/sys.h
  src/interfaces/sys.c
)

target_include_directories(p4_test PRIVATE
  ${CMAKE_SOURCE_DIR}/src
)

SET_TARGET_PROPERTIES(p4_test PROPERTIES PREFIX "") # remove the 'lib' prefix for dlls
