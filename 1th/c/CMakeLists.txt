cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

project(polarPairMatch LANGUAGES C)

set(CMAKE_C_COMPILER "clang")

set(CMAKE_C_STANDART 11)
set(CMAKE_C_STANDART_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(SOURCES
  src/distanceCalculator.c
  src/main.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)
