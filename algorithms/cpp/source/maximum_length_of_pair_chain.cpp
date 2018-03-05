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

class FindLongestChain {
public:
    int findLongestChain(vector<vector<int>> & pairs) {
        auto cmp = [](const vector<int> & a, const vector<int> & b) {
            return a[1] < b[1];
        };
        std::sort(pairs.begin(), pairs.end(), cmp);
        int cnt = 0;
        int last_idx = 0;
        for (int i = 0; i < (int)pairs.size(); ++i) {
            if (i == 0 || pairs[last_idx][1] < pairs[i][0]) {
                ++cnt;
                last_idx = i;
            }
        }
        return cnt;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.maximum_length_of_pair_chain" ) {
    FindLongestChain sol;
    using TestCase = std::tuple< vector<vector<int>>, int >;
    std::vector<TestCase> test_cases {
        TestCase{ {{1, 2}, {2, 3}, {3, 4}}, 2 },
    };

    for (auto & t : test_cases) {
        CHECK(sol.findLongestChain(std::get<0>(t)) == std::get<1>(t));
        std::cout << std::endl;
    }
}
