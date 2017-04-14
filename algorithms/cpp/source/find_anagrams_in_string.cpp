/*
 * find_anagrams_in_string.cpp
 * Copyright (C) 2017 StrayWarrior <i@straywarrior.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "common.hpp"

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

class AllAnagramsInString {
public:
    std::vector<int> findAnagrams(std::string s, std::string p) {
        std::vector<int> result;
        std::vector<int> p_char_counter(26, 0);
        std::vector<int> p_char_order(26, -1);
        std::vector<int> s_char_counter(26, 0);
        int p_bitmap(0), s_bitmap(0);
        int order(0);
        for (size_t i = 0; i < p.length(); ++i) {
            int idx = p[i] - 'a';
            if (p_char_counter[idx] == 0) {
                p_char_order[idx] = order;
                p_bitmap |= (1 << order);
                order++;
            }
            p_char_counter[idx]++;
        }
        for (size_t i = 0; i < s.length(); ++i) {
            int idx = s[i] - 'a';
            if (p_char_order[idx] >= 0) {
                s_char_counter[idx]++;
                if (s_char_counter[idx] == p_char_counter[idx])
                    s_bitmap |= (1 << p_char_order[idx]);
                else
                    s_bitmap &= ~(1 << p_char_order[idx]);
            }
            if (i >= p.length()) {
                idx = s[i - p.length()] - 'a';
                if (p_char_order[idx] >= 0) {
                    s_char_counter[idx]--;
                    if (s_char_counter[idx] == p_char_counter[idx])
                        s_bitmap |= (1 << p_char_order[idx]);
                    else
                        s_bitmap &= ~(1 << p_char_order[idx]);
                }
            }
            if (s_bitmap == p_bitmap)
                result.push_back(i + 1 - p.length());
        }
        return result;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.all_anagrams_in_string" ) {
    AllAnagramsInString sol;
    using TestCase = std::tuple<std::string, std::string, std::vector<int>>;
    std::vector<TestCase> test_cases {
        TestCase("cbaebabacd", "abc", {0, 6}),
        TestCase("cb", "abc", {}),
        TestCase("abab", "ab", {0, 1, 2}),
        TestCase("ababa", "ab", {0, 1, 2, 3}),
        TestCase("abbbacbbcab", "bb", {1, 2, 6}),
    };

    for (auto & t : test_cases) {
        CHECK(sol.findAnagrams(std::get<0>(t), std::get<1>(t)) == std::get<2>(t));
    }
}
