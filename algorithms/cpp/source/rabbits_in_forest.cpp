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

class RabbitsInForest {
public:
    int numRabbits(vector<int> & answers) {
        std::map<int, int> color_maps;
        int sum = 0;
        for (auto n : answers) {
            auto iter = color_maps.find(n);
            if (iter == color_maps.end()) {
                sum += (n + 1);
                color_maps[n] = n;
            } else {
                if (iter->second-- == 0) {
                    iter->second = n;
                    sum += (n + 1);
                }
            }
        }
        return sum;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.rabbits_in_forest" ) {
    RabbitsInForest sol;
    using TestCase = std::tuple< vector<int>, int >;
    std::vector<TestCase> test_cases {
        TestCase{ {1, 1, 2}, 5 },
        TestCase{ {10, 10, 10}, 11 },
        TestCase{ {}, 0 },
        TestCase{ {3,3,3,3,3}, 8 },
    };

    for (auto & t : test_cases) {
        CHECK(sol.numRabbits(std::get<0>(t)) == std::get<1>(t));
    }
}
