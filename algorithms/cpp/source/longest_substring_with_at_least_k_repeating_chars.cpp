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

class LongestSubstring {
public:
    int longestSubstring(string s, int k) {
        std::vector<int> char_counter(26, 0);
        if (s.length() < k)
            return 0;
        for (char c : s) {
            char_counter[c - 'a'] += 1;
        }
        char split_char = 0;
        for (int i = 0; i < 26; ++i)
            if (char_counter[i] > 0 && char_counter[i] < k)
                split_char = static_cast<char>(i + 'a');
        if (split_char == 0)
            return s.length();
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == split_char)
                return std::max(longestSubstring(s.substr(0, i), k),
                                longestSubstring(s.substr(i + 1), k));
        }
        return 0;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.all_anagrams_in_string" ) {
    LongestSubstring sol;
    using TestCase = std::tuple<string, int, int>;
    std::vector<TestCase> test_cases {
        TestCase{ "aaabb", 3, 3 },
        TestCase{ "ababbc", 2, 5 }
    };

    for (auto & t : test_cases) {
        CHECK(sol.longestSubstring(std::get<0>(t), std::get<1>(t)) == std::get<2>(t));
        std::cout << std::endl;
    }
}
