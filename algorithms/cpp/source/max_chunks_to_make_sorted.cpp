/*
 * boomerange_number.cpp
 * Copyright (C) 2017 StrayWarrior <i@straywarrior.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "common.hpp"

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

using namespace std;

class MaxChunksToSorted {
public:
    int maxChunksToSorted(vector<int> & arr) {
        return solve_faster(arr);
    }

    /*** Version 1 ***/
    int solve_recursive(vector<int> & arr) {
        // In fact, it's a process to find a pivot
        return find_pivot(arr, 0, 0);
    }

    int find_pivot(vector<int> & arr, int s, int left_max) {
        for (int i = s; i < (int)arr.size(); ++i) {
            int right_min = arr.size() + 1;
            left_max = std::max(left_max, arr[i]);
            for (int j = i + 1; j < (int)arr.size(); ++j) {
                right_min = std::min(arr[j], right_min);
            }
            if (right_min > left_max)
                return 1 + find_pivot(arr, i + 1, left_max);
        }
        return 0;
    }

    /*** Version 2 ***/
    int solve_faster(vector<int> & arr) {
        // Due to characteristic of permutation, we can simplify the process
        // This solution is O(n) time
        int visit_max = 0;
        int cnt = 0;
        for (int i = 0; i < (int)arr.size(); ++i) {
            visit_max = std::max(visit_max, arr[i]);
            if (visit_max == i)
                ++cnt;
        }
        return cnt;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.max_chunks_to_make_sorted" ) {
    MaxChunksToSorted sol;
    using TestCase = std::tuple< vector<int>, int >;
    std::vector<TestCase> test_cases {
        TestCase{ {4, 3, 2, 1, 0}, 1 },
        TestCase{ {1, 0, 2, 3, 4}, 4 },
    };

    for (auto & t : test_cases) {
        CHECK(sol.maxChunksToSorted(std::get<0>(t)) == std::get<1>(t));
        std::cout << std::endl;
    }
}
