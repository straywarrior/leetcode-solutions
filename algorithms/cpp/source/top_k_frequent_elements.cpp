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

class TopKFrequent {
public:
    vector<int> topKFrequent(vector<int> & nums, int k) {
        std::vector<std::vector<int>> bucket_container(nums.size() + 5);
        std::unordered_map<int, int> element_count;

        for (int x : nums) {
            if (element_count.find(x) == element_count.end())
                element_count.insert(std::pair<int, int>(x, 1));
            else
                element_count.at(x) += 1;
        }
        for (auto pr : element_count) {
            bucket_container[pr.second].push_back(pr.first);
        }
        std::vector<int> result;
        for (int i = bucket_container.size() - 1; i >= 0 && k > 0; --i) {
            if (bucket_container[i].empty())
                continue;
            int j;
            for (j = 0; j < k && j < bucket_container[i].size(); ++j)
                result.push_back(bucket_container[i][j]);
            k -= j;
        }
        return result;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.all_anagrams_in_string" ) {
    TopKFrequent sol;
    using TestCase = std::tuple<std::vector<int>, int, std::vector<int>>;
    std::vector<TestCase> test_cases {
        TestCase{ std::vector<int> {1}, 1, std::vector<int> {1} },
        TestCase{ std::vector<int> {1, 1, 1, 2, 2, 3, 4}, 2, std::vector<int> {1, 2} },
    };

    for (auto & t : test_cases) {
        CHECK(sol.topKFrequent(std::get<0>(t), std::get<1>(t)) == std::get<2>(t));
        std::cout << std::endl;
    }
}
