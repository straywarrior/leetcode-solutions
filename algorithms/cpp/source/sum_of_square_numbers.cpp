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

class JudgeSquareSum {
public:
    bool judgeSquareSum(int c) {
        return version_a(c);
    }

    bool version_a(int c) {
        for (int i = 0; i <= (int)sqrt(c); ++i) {
            int t = (int)sqrt(c - i * i);
            if (t * t + i * i == c)
                return true;
        }
        return false;
    }

    bool version_b(int c) {
        // Do prime factorization. TLE
        for (int i = 2; i < c; ++i) {
            int cnt = 0;
            while (c % i == 0) {
                ++cnt;
                c /= i;
            }
            if (cnt % 2 == 1 && i % 4 == 3) {
                return false;
            }
        }
        if (c % 4 == 3)
            return false;
        return true;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.all_anagrams_in_string" ) {
    JudgeSquareSum sol;
    using TestCase = std::tuple<int, bool>;
    std::vector<TestCase> test_cases {
        TestCase{ 1, true },
        TestCase{ 2, true },
        TestCase{ 5, true },
        TestCase{ 6, false },
        TestCase{ 3, false },
        TestCase{ 7, false },
        TestCase{ 10, true },
        TestCase{ 730663106, true },
    };

    for (auto & t : test_cases) {
        CHECK(sol.judgeSquareSum(std::get<0>(t)) == std::get<1>(t));
        std::cout << std::endl;
    }
}
