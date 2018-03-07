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

class KthGrammar {
public:
    int kthGrammar(int N, int K) {
        // It's just a state machine
        return solve_state_machine(N, K);
    }

    int solve_state_machine(int N, int K) {
        vector<pair<int, int>> positions;
        K -= 1;
        while (N > 1) {
            positions.emplace_back(K / 2, K % 2);
            K >>= 1;
            --N;
        }
        int result = 0;
        for (auto iter = positions.rbegin(); iter != positions.rend(); ++iter) {
            result = (result + iter->second) % 2;
        }
        return result;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.additive_number" ) {
    KthGrammar sol;
    using TestCase = std::tuple< int, int, int >;
    std::vector<TestCase> test_cases {
        TestCase{ 1, 1, 0 },
        TestCase{ 2, 1, 0 },
        TestCase{ 2, 2, 1 },
        TestCase{ 4, 5, 1 },
    };

    for (auto & t : test_cases) {
        CHECK(sol.kthGrammar(std::get<0>(t), std::get<1>(t)) == std::get<2>(t));
        std::cout << std::endl;
    }
}
