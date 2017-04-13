# ----------------------------------------------------------------------------
#  Root CMake file for Leetcode Algorithm Solutions
#
#  Author: StrayWarrior
#  Copyright (C) 2017 StrayWarrior
# ----------------------------------------------------------------------------

cmake_minimum_required (VERSION 3.0)

project(leetcode-algorithm)

add_definitions('-g')
add_definitions('-Wall')
if (NOT MSVC)
    add_definitions('-std=c++11')
endif()

enable_testing()

include_directories("include")
add_subdirectory("source")
