/*
 * count_interesting_sub_sequences.cpp
 * Copyright (C) 2020 StrayWarrior <i@straywarrior.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "common.hpp"

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

using namespace std;

// This problem actually does not come from leetcode.
class CountInterestingSubSequences {
public:
    static constexpr int m = 998244353;
    int count(const std::vector<int>& seq) {
        sub_counters_.clear();
        size_t n = seq.size();
        sub_counters_.resize(n);
        for (auto& x : sub_counters_) {
            x.resize(n + 1, -1);
        }
        int counter = 0;
        if (n == 0) {
            return 0;
        }
        for (size_t i = 0; i < n; ++i) {
            counter += count_recursive(seq, i, 1, n) % m;
        }
        counter = counter % m;
        return counter;
    }

    int count_recursive(const std::vector<int>& seq, size_t a_i, size_t s_i, size_t n) {
        assert(s_i != 0);
        if (a_i == n - 1) {
            int ret = seq[a_i] % s_i == 0 ? 1 : 0;
            sub_counters_[a_i][s_i] = ret;
            return ret;
        }
        int counter = 0;
        // this element at this place can not construct a valid sub sequence
        if (seq[a_i] % s_i != 0) {
            return 0;
        }
        if (sub_counters_[a_i][s_i] > 0) {
            return sub_counters_[a_i][s_i];
        }
        for (size_t i = a_i + 1; i < n; ++i) {
            counter += count_recursive(seq, i, s_i + 1, n) % m;
        }
        // if this is the last element in the sub sequence
        counter = (counter + 1) % m;
        sub_counters_[a_i][s_i] = counter;
        return counter;
    }
private:
    std::vector<std::vector<int>> sub_counters_;
};

TEST_CASE( "test corectness", "leetcode.count_interesting_sub_sequences" ) {
    CountInterestingSubSequences sol;
    using TestCase = std::tuple<std::vector<int>, int>;
    std::vector<TestCase> test_cases {
        TestCase{ {3, 1}, 2 },
        TestCase{ {1, 2, 3}, 5 },
        TestCase{ {1, 1, 1, 1}, 4 },
        TestCase{ {1, 2, 4}, 6 },
    };

    for (auto & t : test_cases) {
        auto& t_input = std::get<0>(t);
        CHECK(sol.count(t_input) == std::get<1>(t));
        // std::cout << sol.countPaths(std::get<0>(t)) << std::endl;
    }
}
