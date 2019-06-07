cmake_minimum_required(VERSION 3.7)
project(ztools)

set(SLUTION_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#set(CMAKE_CXX_STANDARD 11)

include_directories(
        ${SLUTION_DIR}/
        ${SLUTION_DIR}/include/
)

#add_compile_options("-std=c99")
add_compile_options("-std=gnu99" "-g")
#add_compile_options("-g3")
#add_compile_options("-DPACKAGE='util-linux'")
#add_compile_options("-DPACKAGE_STRING='util-linux UNKNOWN'")
#add_compile_options("-include config.h")


#set(SOURCE_FILES main.c)
#add_executable(ztool ${SOURCE_FILES})

add_subdirectory(${SLUTION_DIR}/misc-utils/)
add_subdirectory(${SLUTION_DIR}/crc-test/)
