# ----------------------------------------------------------------------------
#  CMake file for Leetcode Algorithm Solutions
#
#  Author: StrayWarrior
#  Copyright (C) 2017 StrayWarrior
# ----------------------------------------------------------------------------

option(LEETCODE_DEBUG "Enable debug output." OFF)
if (LEETCODE_DEBUG)
    add_definitions("-DLEETCODE_DEBUG")
endif()

macro(leetcode_add_case _name)
    add_executable(${_name} ${_name}.cpp)
    add_test(NAME "test_${_name}" COMMAND ${_name})
endmacro(leetcode_add_case)

leetcode_add_case(string_segment_number)
leetcode_add_case(find_anagrams_in_string)
leetcode_add_case(arrange_coins)
leetcode_add_case(pacific_atlantic_water_flow)
leetcode_add_case(path_sum_3)
leetcode_add_case(boomerang_number)
leetcode_add_case(top_k_frequent_elements)
leetcode_add_case(shortest_completing_word)
leetcode_add_case(longest_substring_with_at_least_k_repeating_chars)
leetcode_add_case(find_right_interval)
