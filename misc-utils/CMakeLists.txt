cmake_minimum_required(VERSION 3.7)
project(ztools)

set(MODULE_NAME misc-utils)

set(MODULE_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/lsblk.c
)

add_executable(lsblk ${MODULE_SRC_FILES})
