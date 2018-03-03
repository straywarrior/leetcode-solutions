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

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class FindRightInterval {
public:
    vector<int> findRightInterval(vector<Interval> & intervals) {
        vector<int> result(intervals.size());
        map<int, int> tree;
        for (int i = 0; i < (int)intervals.size(); ++i) {
            tree.insert(std::make_pair(intervals[i].start, i));
        }
        for (int i = 0; i < (int)intervals.size(); ++i) {
            auto iter = tree.lower_bound(intervals[i].end);
            if (iter == tree.end())
                result[i] = -1;
            else
                result[i] = iter->second;
        }
        return result;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.all_anagrams_in_string" ) {
    FindRightInterval sol;
    using TestCase = std::tuple<vector<Interval>, vector<int>>;
    std::vector<TestCase> test_cases {
        TestCase{ {Interval(1, 2)}, {-1} },
    };

    for (auto & t : test_cases) {
        CHECK(sol.findRightInterval(std::get<0>(t)) == std::get<1>(t));
        std::cout << std::endl;
    }
}
