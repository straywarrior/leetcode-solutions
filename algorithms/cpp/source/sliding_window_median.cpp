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

class MedianSlidingWindow {
public:
    vector<double> medianSlidingWindow(vector<int> & nums, int k) {
        // This solution heavily depends on std::multiset
        // and its BidirectionalIterator.
        // std::multiset is most often implemented as a threaded red-black tree
        // If we do not have std::multiset, what should we do?
        multiset<int> window;
        vector<double> medians;
        for (int i = 0; i < (int)nums.size(); ++i) {
            window.insert(nums[i]);
            if ((int)window.size() >= k) {
                auto mid = std::next(window.begin(), k / 2);
                medians.push_back(((double)*mid + *std::prev(mid, 1 - k % 2)) / 2.0);
                window.erase(window.find(nums[i - k + 1]));
            }
        }
        return medians;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.all_anagrams_in_string" ) {
    MedianSlidingWindow sol;
    using TestCase = std::tuple<vector<int>, int, vector<double>>;
    std::vector<TestCase> test_cases {
        TestCase{
            {1, 3, -1, -3, 5, 3, 6, 7}, 3, {1, -1, -1, 3, 5, 6}
        },
        TestCase {
            {2147483647, 2147483647}, 2, {2147483647.0}
        },
    };

    for (auto & t : test_cases) {
        CHECK(sol.medianSlidingWindow(std::get<0>(t), std::get<1>(t)) == std::get<2>(t));
        std::cout << std::endl;
    }
}
