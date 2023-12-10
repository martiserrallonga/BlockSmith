cmake_minimum_required(VERSION 3.25)
project(BlockSmith)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(submodules)

option(BUILD_ADVENT_OF_CODE "Build AdventOfCode project" ON)
if(BUILD_ADVENT_OF_CODE)
  add_subdirectory(adventOfCode)
endif()
