cmake_minimum_required(VERSION 3.26)
project(game VERSION 1.0)

set(BUILD_SHARED_LIBS OFF)

set(LIBCXX_HARDENING_MODE debug)

include(cmake/ExternalLibraries.cmake)

include(cmake/CompilerOptions.cmake)

#set(CMAKE_CXX_CLANG_TIDY /opt/homebrew/opt/llvm/bin/clang-tidy
#    --config-file=${CMAKE_SOURCE_DIR}/.clang-tidy
#)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

#set(CMAKE_INTERPROCEDURAL_OPTIMIZATION true)
# TODO: on mac with LTO add -Wl,-object_path_lto,lto.o to stop debug info from being stripped

add_subdirectory(src)