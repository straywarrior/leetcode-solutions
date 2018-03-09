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

class QueueReconstruction {
public:
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>> & people) {
        // Solve by sorting and inserting lower groups iteratively
        map<int, vector<int>> counter;
        for (auto pt : people) {
            auto iter = counter.find(pt.first);
            if (iter == counter.end())
                counter.insert(std::make_pair(pt.first, vector<int>{pt.second}));
            else
                iter->second.push_back(pt.second);
        }
        vector<pair<int, int>> result;
        result.reserve(people.size());
        for (auto iter = counter.rbegin(); iter != counter.rend(); ++iter) {
            sort(iter->second.begin(), iter->second.end());
            for (auto pt : iter->second) {
                result.insert(result.begin() + pt,
                              std::make_pair(iter->first, pt));
            }
        }
        return result;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.queue_reconstruction_by_height" ) {
    QueueReconstruction sol;
    using TestCase = std::tuple< vector<pair<int, int>>, vector<pair<int, int>> >;
    std::vector<TestCase> test_cases {
        TestCase{
            {{7, 0}, {4, 4}, {7, 1}, {5, 0}, {6, 1}, {5, 2}},
            {{5, 0}, {7, 0}, {5, 2}, {6, 1}, {4, 4}, {7, 1}}
        },
    };

    for (auto & t : test_cases) {
        CHECK(sol.reconstructQueue(std::get<0>(t)) == std::get<1>(t));
    }
}
