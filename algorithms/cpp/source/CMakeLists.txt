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
leetcode_add_case(sum_of_square_numbers)
leetcode_add_case(convert_a_number_to_hexadecimal)
leetcode_add_case(sliding_window_median)
leetcode_add_case(arithmetic_slices)
leetcode_add_case(map_sum_pairs)
leetcode_add_case(create_maximum_number)
leetcode_add_case(maximum_length_of_pair_chain)
leetcode_add_case(kth_symbol_in_grammar)
leetcode_add_case(minimum_number_of_arrows_burst_balloons)
leetcode_add_case(odd_even_linked_list)
leetcode_add_case(minimum_ascii_delete_sum_for_two_strings)
leetcode_add_case(delete_operation_for_two_strings)
leetcode_add_case(edit_distance)
leetcode_add_case(max_chunks_to_make_sorted)
leetcode_add_case(toeplitz_matrix)
leetcode_add_case(wildchard_matching)
leetcode_add_case(verify_preorder_serialization_of_a_binary_tree)
leetcode_add_case(queue_reconstruction_by_height)
leetcode_add_case(minimum_time_difference)
leetcode_add_case(frog_jump)
leetcode_add_case(rabbits_in_forest)
leetcode_add_case(min_moves_to_equal_array_elements)
