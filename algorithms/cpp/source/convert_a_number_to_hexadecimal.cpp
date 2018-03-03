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

class ToHex {
public:
    string toHex(int num) {
        unsigned int a = (unsigned int)num;
        if (num == 0)
            return "0";
        char char_map[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
        std::vector<char> digits_stack;
        string result;
        while (a > 0) {
            int r = a % 16;
            a = a >> 4;
            digits_stack.push_back(char_map[r]);
        }
        for (auto iter = digits_stack.crbegin(); iter != digits_stack.crend(); ++iter)
            result.push_back(*iter);
        return result;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.all_anagrams_in_string" ) {
    ToHex sol;
    using TestCase = std::tuple<int, string>;
    std::vector<TestCase> test_cases {
        TestCase{ 0, "0" },
        TestCase{ 26, "1a" },
        TestCase{ -1, "ffffffff" },
    };

    for (auto & t : test_cases) {
        CHECK(sol.toHex(std::get<0>(t)) == std::get<1>(t));
        std::cout << std::endl;
    }
}
