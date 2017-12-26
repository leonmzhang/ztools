cmake_minimum_required(VERSION 3.7)
project(ztools)

set(SLUTION_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 11)

add_compile_options("-std=c99")

include_directories(
        ${SLUTION_DIR}/include/
)

set(SOURCE_FILES main.c)
add_executable(ztool ${SOURCE_FILES})

add_subdirectory(${SLUTION_DIR}/misc-utils/)
