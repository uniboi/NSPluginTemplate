cmake_minimum_required(VERSION 3.15)
project(ExamplePlugin C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(example_plugin SHARED
  src/main.c
  src/interfaces/interface.h
  src/interfaces/interface.c
  src/interfaces/ns_interface.h
  src/interfaces/ns_interface.c
  src/interfaces/engine_interface.h
  src/interfaces/engine_interface.c
  src/interfaces/plugin_callbacks.h
  src/interfaces/plugin_callbacks.c
  src/interfaces/sys.h
  src/interfaces/sys.c
  src/interfaces/cvar.h
  src/interfaces/cvar.c
  src/squirrel/squirrel.h
  src/squirrel/squirrel.c
  src/squirrel/sqvm.h
  src/cvar/cvar.h
  src/cvar/cvar.c
  src/bindings/native_closures.h
  src/bindings/native_closures.c
  src/bindings/module.h
  src/bindings/module.c
  src/bindings/relay.h
  src/bindings/relay.c
  src/bindings/assert.h
)

target_include_directories(example_plugin PRIVATE
  ${CMAKE_SOURCE_DIR}/src
)

SET_TARGET_PROPERTIES(example_plugin PROPERTIES PREFIX "") # remove the 'lib' prefix for dlls
