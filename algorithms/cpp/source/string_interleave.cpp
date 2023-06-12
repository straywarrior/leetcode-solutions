/*
 * Copyright (C) 2020 StrayWarrior <i@straywarrior.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "common.hpp"

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

using namespace std;

class StringInterleave {
public:
    bool solve(string s1, string s2, string s3) {
        if (s1.size() + s2.size() != s3.size()) {
            return false;
        }
        return solve_trivial(s1, s2, s3);
    }

    bool solve_by_dp(string s1, string s2, string s3) {
        bool cache[256][256];
        memset(cache, 0, sizeof(cache));
        cache[0][0] = true;
        // if s1 is empty

        // if s2 is empty
        for (size_t i = 0; i < s1.size(); ++i) {
            for (size_t j = 0; j < s2.size(); ++j) {

            }
        }
    }

    bool solve_trivial(string s1, string s2, string s3) {
        char cache[205][205];
        memset(cache, 0xFF, 205 * 205);

        return solve_trivial_recursion_func(0, 0, s1, s2, s3, cache);
    }

    bool solve_trivial_recursion_func(
            size_t i, size_t j,
            const std::string &s1, const std::string &s2, const std::string& s3,
            char cache[][205]) {
        if (i == s1.size() && j == s2.size()) {
            return true;
        }
        if (cache[i][j] != (char)0xFF) {
            return (bool)cache[i][j];
        }
        char next_char = s3[i + j];
        bool ret = false;
        if (i < s1.size() && s1[i] == next_char) {
            ret |= solve_trivial_recursion_func(i + 1, j, s1, s2, s3, cache);
        }
        if (j < s2.size() && s2[j] == next_char) {
            ret |= solve_trivial_recursion_func(i, j + 1, s1, s2, s3, cache);
        }
        cache[i][j] = (char)ret;
        return ret;
    }
};

TEST_CASE("test corectness", "leetcode.cpp.string_interleave") {
    using std::tuple;
    using std::get;
    StringInterleave sol;
    using TestCase = tuple<string, string, string, bool>;
    std::vector<TestCase> test_cases {
        TestCase{ "", "", "", true },
        TestCase{ "ab", "", "", false },
        TestCase{ "ab", "", "ab", true },
        TestCase{ "aabcc", "dbbca", "aadbbcbcac", true }
    };

    for (size_t i = 0; i < test_cases.size(); ++i) {
        const auto& t = test_cases[i];
        CHECK(sol.solve(get<0>(t), get<1>(t), get<2>(t)) == std::get<3>(t));
    }
}
