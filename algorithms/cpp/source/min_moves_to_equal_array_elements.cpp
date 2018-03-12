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

class MinMoves {
public:
    int minMoves(vector<int> & nums) {
        return solve_sort(nums);
        //return solve_constant(nums);
    }

    int solve_constant(vector<int> & nums) {
        // It's a math problem. Assume after m moves all elements equal to A
        // we can get: Sum(nums) + m * (n - 1) = n * A
        // However, A = Min(nums) + m
        // So it's easy to find that m = Sum - n * Min
        int m = std::numeric_limits<int>::max();
        int sum = 0;
        for (auto p : nums) {
            m = std::min(m, p);
            sum += p;
        }
        return sum - nums.size() * m;
    }

    int solve_sort(vector<int> & nums) {
        std::sort(nums.begin(), nums.end());
        int sum = 0;
        // We always fill the gap between the lowest to the current
        for (int i = 1; i < (int)nums.size(); ++i) {
            sum += nums[i] - nums[0];
        }
        return sum;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.min_moves_to_equal_array_elements" ) {
    MinMoves sol;
    using TestCase = std::tuple< vector<int>, int >;
    std::vector<TestCase> test_cases {
        TestCase{ {1, 2}, 1 },
        TestCase{ {1, 1, 2}, 1 },
        TestCase{ {1, 2, 3}, 3 },
        TestCase{ {1, 2, 3, 4}, 6 },
        TestCase{ {}, 0 },
    };

    for (auto & t : test_cases) {
        CHECK(sol.minMoves(std::get<0>(t)) == std::get<1>(t));
    }
}
