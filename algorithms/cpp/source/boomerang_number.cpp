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

class NumberOfBoomerangs {
public:
    inline void printTuple(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
#ifdef LEETCODE_DEBUG
        printf("[%d, %d], [%d, %d], [%d, %d]\n",
                a.first, a.second, b.first, b.second, c.first, c.second);
#endif
    }

    inline int square(int x) { return x * x; }

    int distance(const pair<int, int> &lhs, const pair<int, int> &rhs) {
        return square(lhs.first - rhs.first) + square(lhs.second - rhs.second);
    }

    int numberOfBoomerangs(vector<pair<int, int>>& points) {
        if (points.empty())
            return 0;
        size_t n = points.size();
        int ret = 0;
        std::unordered_map<int, int> distance_count;
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0;j < n; ++j) {
                if (j == i) continue;
                int dist = distance(points[i], points[j]);
                auto iter = distance_count.find(dist);
                if (iter == distance_count.end()) {
                    distance_count.insert(std::make_pair(dist, 1));
                } else {
                    ++(iter->second);
                }
            }
            for (auto & p : distance_count) {
                int val = p.second;
                ret += (val * (val - 1));
            }
            distance_count.clear();
        }
        return ret;
    }

    //! @deprecated
    int numberOfBoomerangs_v1(vector<pair<int, int>>& points) {
        if (points.empty())
            return 0;
        size_t n = points.size();
        vector<vector<int>> pairwise_distances(n, vector<int>(n, 0));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                pairwise_distances[i][j] = distance(points[i], points[j]);
            }
        }

        int count = 0;
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                int dist = pairwise_distances[i][j];
                for (size_t k = j + 1; k < n; ++k) {
                    if (pairwise_distances[i][k] == dist) {
                        count++;
                        printTuple(points[i], points[j], points[k]);
                    }
                    if (pairwise_distances[j][k] == dist) {
                        count++;
                        printTuple(points[j], points[i], points[k]);
                    }
                    if (pairwise_distances[j][k] == pairwise_distances[i][k]) {
                        count++;
                        printTuple(points[k], points[i], points[j]);
                    }
                }
            }
        }
        return count * 2;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.all_anagrams_in_string" ) {
    using Pt = std::pair<int, int>;
    NumberOfBoomerangs sol;
    using TestCase = std::tuple<std::vector<std::pair<int, int>>, int>;
    std::vector<TestCase> test_cases {
        TestCase{ { Pt(0, 0), Pt(1, 0), Pt(2, 0) }, 2},
        TestCase{ { Pt(0, 0), Pt(1, 0), Pt(2, 0), Pt(-1, 0) }, 4},
        TestCase{ { Pt(0, 0), Pt(1, 0), Pt(-1, 0), Pt(0, 1), Pt(0, -1) }, 20},
    };

    for (auto & t : test_cases) {
        CHECK(sol.numberOfBoomerangs(std::get<0>(t)) == std::get<1>(t));
        std::cout << std::endl;
    }
}
