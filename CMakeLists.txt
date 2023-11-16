#---------------------------------------------------------------------------------------------------
#      Copyright (c) 2018 Nordic Semiconductor
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#---------------------------------------------------------------------------------------------------
# Project  : Droid Demo Audio..
#---------------------------------------------------------------------------------------------------
# Date     : 04.10.2023 16:00
# Author   : Datsii Vladislav
# Email    : 3exesh@gmail.com
#---------------------------------------------------------------------------------------------------
#<< COMPILE PARAMS : >>
set(CMAKE_C_CXX_PARAMS_LIST__GLOBAL -std=c++20 -O0  -fpermissive -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-function )
set(CMAKE_C_CXX_PARAMS_LIST__ZEPHYR -std=c++20 -O0  -fpermissive -isystem -w )
#<< COMPILE PARAMS / >>


cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(NONE LANGUAGES C CXX)
 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE DEBUG)


string(REPLACE ";" " " CMAKE_C_CXX_PARAMS_STR__GLOBAL "${CMAKE_C_CXX_PARAMS_LIST__GLOBAL}")
set(CMAKE_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS_DEBUG}   ${CMAKE_C_CXX_PARAMS_STR__GLOBAL}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_C_CXX_PARAMS_STR__GLOBAL}")



file(GLOB_RECURSE SRC_DIR_FILES "${CMAKE_SOURCE_DIR}/src/*.c" "${CMAKE_SOURCE_DIR}/src/*.cpp")
STRING(REPLACE "${CMAKE_SOURCE_DIR}/" "" SRC_DIR_FILES "${SRC_DIR_FILES}")
message(STATUS "[ Source files : ]")
foreach(line IN LISTS SRC_DIR_FILES)
    message(STATUS "${line}")
endforeach() 
message(STATUS "")


zephyr_library_compile_options (${CMAKE_C_CXX_PARAMS_LIST__ZEPHYR})
target_sources                 (app PRIVATE ${SRC_DIR_FILES})
target_include_directories     (app PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src")

#target_compile_options (app PRIVATE ${CMAKE_C_CXX_PARAMS_LIST})
#set_target_properties  (app PROPERTIES COMPILE_FLAGS ${CMAKE_C_CXX_PARAMS_LIST})
zephyr_library_include_directories(.)
