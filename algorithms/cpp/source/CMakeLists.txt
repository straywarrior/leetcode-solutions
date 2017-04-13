# ----------------------------------------------------------------------------
#  CMake file for Leetcode Algorithm Solutions
#
#  Author: StrayWarrior
#  Copyright (C) 2017 StrayWarrior
# ----------------------------------------------------------------------------

macro(leetcode_add_case _name)
    add_executable(${_name} ${_name}.cpp)
    add_test(NAME "test_${_name}" COMMAND ${_name})
endmacro(leetcode_add_case)

leetcode_add_case(string_segment_number)
#add_executable(string_segment_number string_segment_number.cpp)
