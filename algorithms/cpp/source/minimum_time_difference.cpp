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

class MinimumTimeDifference {
public:
    int diffTime(const string & a, const string & b) {
        int sum = 0;
        sum += (b[0] - a[0]) * 10;
        sum += (b[1] - a[1]);
        sum *= 60;
        sum += (b[3] - a[3]) * 10;
        sum += (b[4] - a[4]);
        return sum;
    }
    int findMinDifference(vector<string>& timePoints) {
        std::sort(timePoints.begin(), timePoints.end());
        int result = 1440;
        for (int i = 0; i < timePoints.size() - 1; ++i) {
            int t = diffTime(timePoints[i], timePoints[i + 1]);
            result = std::min({result, std::abs(1440 - t), t});
        }
        int t = diffTime(timePoints.front(), timePoints.back());
        result = std::min({result, std::abs(1440 - t), t});
        return result;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.minimum_time_difference" ) {
    MinimumTimeDifference sol;
    using TestCase = std::tuple< vector<string>, int >;
    std::vector<TestCase> test_cases {
        TestCase{ {"05:31", "22:08", "00:35"}, 147 },
    };

    for (auto & t : test_cases) {
        CHECK(sol.findMinDifference(std::get<0>(t)) == std::get<1>(t));
    }
}
