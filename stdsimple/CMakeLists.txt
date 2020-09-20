# ----------------------------------------------------------------------------
#  Root CMake file for stdsimple project.
#
#  Author: StrayWarrior
#  Copyright (C) 2020 StrayWarrior
# ----------------------------------------------------------------------------

cmake_minimum_required (VERSION 3.0)

project(stdsimple)

add_definitions('-g')
add_definitions('-Wall')
if (NOT MSVC)
    add_definitions('-std=c++11')
endif()

enable_testing()

include_directories("include")
add_subdirectory("source")
