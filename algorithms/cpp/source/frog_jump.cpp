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

class FrogJump {
public:
    bool canCross(vector<int> & stones) {
        // It's kind of a dynamic programming problem
        // From stone[i], it's possible to reach stone[j] only if
        // the step between the two stones is available for stone[i]
        // Record and update all possible steps for each stone.
        unordered_map<int, unordered_set<int>> steps;
        for (auto unit : stones) {
            steps.insert(std::make_pair(unit, unordered_set<int>()));
        }
        steps[0].insert(1);
        int n = stones.size();
        for (int i = 0; i < n; ++i) {
            int unit = stones[i];
            for (auto step : steps.at(unit)) {
                for (int j = i + 1; j < n; ++j) {
                    int interval = stones[j] - unit;
                    if (interval > step + 1)
                        break;
                    if (interval == step) {
                        if (j == n - 1)
                            return true;
                        steps.at(stones[j]).insert(step - 1);
                        steps.at(stones[j]).insert(step);
                        steps.at(stones[j]).insert(step + 1);
                    }
                }
            }
        }
        return false;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.frog_jump" ) {
    FrogJump sol;
    using TestCase = std::tuple< vector<int>, bool >;
    std::vector<TestCase> test_cases {
        TestCase{ {0,2}, false },
        TestCase{ {0,1,2,3,4,8,9,11}, false },
        TestCase{ {0,1,3,5,6,8,12,17}, true },
    };

    for (auto & t : test_cases) {
        CHECK(sol.canCross(std::get<0>(t)) == std::get<1>(t));
    }
}
