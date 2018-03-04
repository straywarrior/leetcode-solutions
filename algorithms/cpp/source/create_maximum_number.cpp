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

class MaxNumber {
public:
    vector<int> maxNumber(vector<int> & nums1, vector<int> & nums2, int k) {
        vector<int> result;
        /* This problem is hard to some degree.
         * Here are tree steps:
         *  enumerate possibilities of number distribution between two arrays
         *  find max sub-array of each array for each possiblity
         *  compare and merge the two sub-arrays
         */
        for (int i = std::max(k - (int)nums2.size(), 0);
                 i <= k && i <= (int)nums1.size(); ++i) {
            auto cur_result = this->mergeArray(this->maxSubArray(nums1, i),
                                               this->maxSubArray(nums2, k - i), k);
            if (this->greater(cur_result, 0, result, 0))
                result = cur_result;
        }
        return result;
    }

    vector<int> maxSubArray(const vector<int> & nums, int k) {
        int n = nums.size();
        vector<int> sub_array(k, 0); // behaves like a stack
        int sp = 0;
        for (int i = 0; i < n; ++i) {
            while (n - i > k - sp && // there are enough numbers left
                   sp > 0 &&         // basic boundary condition
                   sub_array[sp - 1] < nums[i]) {
                sp -= 1; // pop number from the stack
            }
            if (sp < k)
                sub_array[sp++] = nums[i];
        }
        return sub_array;
    }

    vector<int> mergeArray(const vector<int> & nums1, const vector<int> & nums2, int k) {
        vector<int> result(k);
        int i = 0; int j = 0;
        for (int sp = 0; sp < k; ++sp)
            result[sp] = this->greater(nums1, i, nums2, j) ? nums1[i++] : nums2[j++];
        return result;

    }

    bool greater(const vector<int> & nums1, int i, const vector<int> & nums2, int j) {
        int m = (int)nums1.size();
        int n = (int)nums2.size();
        while (i < m && j < n && nums1[i] == nums2[j]) {
            ++i;
            ++j;
        }
        return j == n || (i < m && nums1[i] > nums2[j]);

    }
};

TEST_CASE( "test corectness", "leetcode.cpp.create_maximum_number" ) {
    MaxNumber sol;
    using TestCase = std::tuple< vector<int>, vector<int>, int, vector<int> >;
    std::vector<TestCase> test_cases {
        TestCase{ {3, 4, 6, 5}, {9, 1, 2, 5, 8, 3}, 5, {9, 8, 6, 5, 3} },
    };

    for (auto & t : test_cases) {
        CHECK(sol.maxNumber(std::get<0>(t), std::get<1>(t), std::get<2>(t)) == std::get<3>(t));
        std::cout << std::endl;
    }
}
