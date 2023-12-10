set(ADVENT_OF_CODE "AdventOfCode" CACHE STRING "AdventOfCode executable name")

add_executable(${ADVENT_OF_CODE})

target_sources(${ADVENT_OF_CODE} PRIVATE
  main.cpp
  day01.h
)
