cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchain_config.cmake)

project(kernel7 VERSION 0.1)
enable_language(C CXX ASM)

add_subdirectory(src)