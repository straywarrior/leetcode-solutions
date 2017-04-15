/*
 * arrange_coins.cpp
 * Copyright (C) 2017 StrayWarrior <i@straywarrior.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "common.hpp"

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

class ArrangeCoins {
public:
    int arrageCoins(int n) {
        int rows = 0;
        while (n > 0) {
            rows++;
            n -= rows;
        }
        if (n < 0)
            return rows - 1;
        else
            return rows;
    }

    int arrageCoinsV2(int n) {
        return floor(-0.5 + 0.5 * sqrt(1 + 8 * (double)n));
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.all_anagrams_in_string" ) {
    ArrangeCoins sol;
    using TestCase = std::tuple<int, int>;
    std::vector<TestCase> test_cases {
        TestCase(0, 0),
        TestCase(1, 1),
        TestCase(3, 2),
        TestCase(5, 2),
        TestCase(8, 3),
        TestCase(10, 4),
        TestCase(1804289383, 60070),
    };

    for (auto & t : test_cases) {
        CHECK(sol.arrageCoins(std::get<0>(t)) == std::get<1>(t));
    }
    for (auto & t : test_cases) {
        CHECK(sol.arrageCoinsV2(std::get<0>(t)) == std::get<1>(t));
    }
}
