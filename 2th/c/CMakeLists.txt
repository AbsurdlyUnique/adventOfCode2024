
cmake_minimum_required(VERSION 3.10)
project(RedNosedReports C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_STANDARD 11)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/includes)

# Add sources
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")
add_executable(red_nosed_reports ${SOURCES})
