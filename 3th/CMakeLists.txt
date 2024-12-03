
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(MulSumCalculator VERSION 1.0)

# Specify the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add executables for Part 1 and Part 2
add_executable(mulSumFileReader src/main.c)  # Part 1
add_executable(mulSumWithConditions src/part2.c)  # Part 2
