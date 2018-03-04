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

class ArithmeticSlices {
public:
    int numberOfArithmeticSlices(vector<int> & A) {
        // Is it similar to substring problems?
        // Solve it by dynamic programming
        return this->version_dp_less_space(A);
    }

    int version_dp(vector<int> & A) {
        std::vector<int> dp_counts(A.size(), 0);
        int result = 0;
        for (int i = 2; i < (int)A.size(); ++i) {
            if (A[i] - A[i - 1] == A[i - 1] - A[i - 2])
                dp_counts[i] = dp_counts[i - 1] + 1;
            result += dp_counts[i];
        }
        return result;
    }

    int version_dp_less_space(vector<int> & A) {
        int last_count = 0;
        int result = 0;
        if (A.size() < 3)
            return 0;
        int last_interval = A[1] - A[0];
        for (int i = 2; i < (int)A.size(); ++i) {
            int cur_interval = A[i] - A[i - 1];
            if (cur_interval == last_interval) {
                last_count += 1;
                result += last_count;
            } else {
                last_count = 0;
            }
            last_interval = cur_interval;
        }
        return result;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.all_anagrams_in_string" ) {
    ArithmeticSlices sol;
    using TestCase = std::tuple<vector<int>, int>;
    std::vector<TestCase> test_cases {
        TestCase{ {1, 2}, 0 },
        TestCase{ {1, 2, 3}, 1 },
        TestCase{ {1, 2, 3, 4}, 3 },
        TestCase{ {1, 2, 3, 5, 7}, 2 },
    };

    for (auto & t : test_cases) {
        CHECK(sol.numberOfArithmeticSlices(std::get<0>(t)) == std::get<1>(t));
        std::cout << std::endl;
    }
}
