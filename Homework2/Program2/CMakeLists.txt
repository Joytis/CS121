# SKELETON CMAKE FILE
#======================================================================
cmake_minimum_required(VERSION 3.3)
project(cs121projhw2p2)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Project include (Missed by recurse)
#======================================================================
file(GLOB_RECURSE SOURCES "src/*.cpp")
include_directories(${PROJECT_SOURCE_DIR}/inc)

# Project include (Missed by recurse)
#======================================================================
add_executable (${PROJECT_NAME} ${SOURCES})

# Set the VS build properties
#======================================================================
set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")