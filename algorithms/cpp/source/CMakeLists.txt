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
leetcode_add_case(find_anagrams_in_string)
leetcode_add_case(arrange_coins)
leetcode_add_case(pacific_atlantic_water_flow)
