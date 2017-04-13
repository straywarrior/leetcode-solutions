/*
 * string_segment_number.cpp
 * Copyright (C) 2017 StrayWarrior <i@straywarrior.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "common.hpp"

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

class StringSegmentNumeber {
public:
    int countSegments(std::string s) {
        int count = 0;
        int last_pos = -1;
        int cur_pos = 0;
        while (cur_pos < s.length()) {
            if (s[cur_pos] == ' ') {
                if (cur_pos - last_pos > 1)
                    count++;
                last_pos = cur_pos;
            }
            cur_pos++;
        }
        if (cur_pos - last_pos > 1)
            count++;
        return count;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.string_segment_number" ) {
    StringSegmentNumeber sol;
    using TestCase = std::pair<std::string, int>;
    std::vector<TestCase> test_cases {
        TestCase("Hello, my name is John", 5),
        TestCase("", 0),
        TestCase("a", 1),
        TestCase("Uh-huh", 1),
        TestCase("    Uh-huh", 1),
        TestCase("Uh-huh    ", 1),
        TestCase("   ", 0),
        TestCase(" Hello world!  ", 2),
    };

    for (auto & t : test_cases) {
        CHECK(sol.countSegments(t.first) == t.second);
    }
}
