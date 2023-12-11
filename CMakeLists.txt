cmake_minimum_required(VERSION 3.15)
project(pluginTest C)

add_library(p4_test SHARED
    src/main.c
    src/interface.h
    src/interface.c
    src/plugin_callbacks.h
    src/plugin_callbacks.c
    src/interfaces/ns_interface.h
    src/interfaces/ns_interface.c
    src/log/log.h
    src/log/log.c
  )

SET_TARGET_PROPERTIES(p4_test PROPERTIES PREFIX "") # remove the 'lib' prefix for dlls
