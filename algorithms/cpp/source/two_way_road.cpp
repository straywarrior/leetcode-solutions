/*
 * two_way_road.cpp
 * Copyright (C) 2020 StrayWarrior <i@straywarrior.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "common.hpp"

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

using namespace std;

namespace {
static constexpr char X = 'X';
static constexpr char Y = 'Y';
}

// This problem actually does not come from leetcode.
class TwoWayRoad {
public:
    using RoadType = std::vector<std::vector<char>>;
    int countPaths(const RoadType& road) {
        if (road.empty()) {
            return 0;
        }
        return this->version_dp(road);
    }

    int version_dp(const RoadType& road) {
        size_t rows = road.size();
        size_t cols = road[0].size();
        if (cols == 0) {
            return 0;
        }
        std::vector<std::vector<int>> dp_count(rows);
        for (size_t i = 0; i < rows; ++i) {
            if (road[i].size() != cols) {
                return 0;
            }
            dp_count[i].resize(cols, 0);
        }
        dp_count[0][0] = 1;
        for (size_t j = 0; j < cols; ++j) {
            for (size_t i = 0; i < rows; ++i) {
                if (road[i][j] == X) {
                    dp_count[i][j] = 0;
                    continue;
                }
                if (j > 0) {
                    dp_count[i][j] += dp_count[i][j - 1];
                }
                if (i > 0 && j > 0) {
                    dp_count[i][j] += dp_count[i - 1][j - 1];
                }
                if (i + 1 < rows && j > 0) {
                    dp_count[i][j] += dp_count[i + 1][j - 1];
                }
            }
        }
        return dp_count[rows - 1][cols - 1];
    }

    int version_recursive(const RoadType& road) {
        size_t rows = road.size();
        if (rows == 0) {
            return 0;
        }
        size_t cols = road[0].size();
        // be careful of corner case
        if (cols == 0) {
            return 0;
        }
        return this->version_recursive(road, rows - 1, cols - 1, rows, cols);
    }

    int version_recursive(const RoadType& road, size_t i, size_t j,
                          size_t rows, size_t cols) {
        if (i == 0 && j == 0) {
            return road[i][j] == X ? 0 : 1;
        }
        // be careful of recursive base
        if (road[i][j] == X) {
            return 0;
        }
        int ret = 0;
        if (j > 0) {
            ret += version_recursive(road, i, j - 1, rows, cols);
            if (i > 0) {
                ret += version_recursive(road, i - 1, j - 1, rows, cols);
            }
            if (i + 1 < rows) {
                ret += version_recursive(road, i + 1, j - 1, rows, cols);
            }
        }
        return ret;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.two_way_road" ) {
    TwoWayRoad sol;
    using TestCase = std::tuple<TwoWayRoad::RoadType, int>;
    std::vector<TestCase> test_cases {
        TestCase{ {{}, {}}, 0 },
        TestCase{ {{X}, {X}}, 0 },
        TestCase{ {{Y, Y}, {Y, Y}}, 1 },
        TestCase{ {{Y, X, Y}, {Y, Y, Y}}, 1 },
        TestCase{ {{Y, Y, X, Y, X}, {X, X, Y, Y, Y}}, 2 },
    };

    for (auto & t : test_cases) {
        auto& t_input = std::get<0>(t);
        CHECK(sol.countPaths(t_input) == std::get<1>(t));
        CHECK(sol.version_recursive(t_input) == sol.countPaths(t_input));
        // std::cout << sol.countPaths(std::get<0>(t)) << std::endl;
    }
}
