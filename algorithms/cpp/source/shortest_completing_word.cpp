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

class ShortestCompletingWord {
public:
    string shortestCompletingWord(string licensePlate, vector<string> & words) {
        string result;
        int shortest_length = 10000;
        vector<int> template_counter(26, 0);
        const int offset = 'a' - 'A';
        for (char c : licensePlate) {
            if (c < 'A' || c > 'z')
                continue;
            if (c > 'Z')
                c -= offset;
            template_counter[c - 'A'] += 1;
        }
        vector<int> current_counter(26, 0);
        for (auto word : words) {
            for (char c : word) {
                if (c < 'A' || c > 'z')
                    continue;
                if (c > 'Z')
                    c -= offset;
                current_counter[c - 'A'] += 1;
            }
            bool valid = true;
            for (int i = 0; i < 26; ++i) {
                if (template_counter[i] != 0 && template_counter[i] > current_counter[i])
                    valid = false;
                current_counter[i] = 0;
            }
            if (valid && word.length() < shortest_length) {
                result = word;
                shortest_length = word.length();
            }
        }
        return result;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.all_anagrams_in_string" ) {
    ShortestCompletingWord sol;
    using TestCase = std::tuple<string, vector<string>, string>;
    std::vector<TestCase> test_cases {
        TestCase{ "1s3 PSt", {"step", "steps", "stripe", "stepple"}, "steps" }
    };

    for (auto & t : test_cases) {
        CHECK(sol.shortestCompletingWord(std::get<0>(t), std::get<1>(t)) == std::get<2>(t));
        std::cout << std::endl;
    }
}
