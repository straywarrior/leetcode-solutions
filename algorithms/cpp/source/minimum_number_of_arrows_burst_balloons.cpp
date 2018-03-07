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

class FindMinArrowShots {
public:
    int findMinArrowShots(vector<pair<int, int>> & points) {
        return solve_via_sort(points);
    }

    int solve_trivial(vector<pair<int, int>> & points) {
        // For each new interval, intersect with existed union or interval
        // without a union. The worst case is O(n^2)
    }

    int solve_via_sort(vector<pair<int, int>> & points) {
        if (points.size() == 0)
            return 0;
        std::sort(
            points.begin(), points.end(),
            [] (const pair<int, int> & a, const pair<int, int> & b) {
                return a.first < b.first ? true : (a.first == b.first && a.second < b.second);
            }
        );
        int arrow_cnt = 1;
        int cur_arrow = points[0].second;
        for (auto iter = points.cbegin() + 1; iter != points.cend(); ++iter) {
            if (iter->first > cur_arrow) {
                cur_arrow = iter->second;
                ++arrow_cnt;
                continue;
            }
            if (iter->second < cur_arrow)
                cur_arrow = iter->second;
        }
        return arrow_cnt;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.minimum_number_of_arrows_to_burst_balloons" ) {
    FindMinArrowShots sol;
    using TestCase = std::tuple< vector<pair<int, int>>, int >;
    std::vector<TestCase> test_cases {
        TestCase{ {{0, 0}}, 1 },
        TestCase{ {{10, 16}, {2, 8}, {1, 6}, {7, 12}}, 2 },
        TestCase{ {{9, 12}, {1, 10}, {4, 11}, {8, 12}, {3, 9}, {6, 9}, {6, 7}}, 2 },
    };

    for (auto & t : test_cases) {
        CHECK(sol.findMinArrowShots(std::get<0>(t)) == std::get<1>(t));
        std::cout << std::endl;
    }
}
