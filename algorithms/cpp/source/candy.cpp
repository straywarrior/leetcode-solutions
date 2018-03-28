/*
 * candy.cpp
 * Copyright (C) 2018 StrayWarrior <i@straywarrior.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "common.hpp"

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

using namespace std;

class Candy {
public:
    int candy(vector<int> & ratings) {
        return this->solve_trivial(ratings);
    }

    int solve_trivial(vector<int> & ratings) {
        int m = ratings.size();
        vector<int> candies(m, 1);
        for (int i = 0; i < m - 1; ++i) {
            if (ratings[i + 1] > ratings[i])
                candies[i + 1] = candies[i] + 1;
        }
        // Here I use max operation to make sure the left neighbor get enough 
        // candies. After the first pass, children with higher scores than
        // their right neighbors should have at least same number of candies as
        // their neighbors. It's obvious, so why do I type so many words here?
        for (int i = m - 1; i > 0; --i) {
            if (ratings[i - 1] > ratings[i])
                candies[i - 1] = std::max(candies[i - 1], candies[i] + 1);
        }
        int sum = 0;
        for (auto c : candies)
            sum += c;
        return sum;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.candy" ) {
    Candy sol;
    using TestCase = std::tuple< vector<int>, int >;
    std::vector<TestCase> test_cases {
        TestCase{ {1, 2}, 3 },
        TestCase{ {1, 2, 3}, 6 },
        TestCase{ {1, 4, 2, 3}, 6 },
        TestCase{ {}, 0 },
    };

    for (auto & t : test_cases) {
        CHECK(sol.candy(std::get<0>(t)) == std::get<1>(t));
    }
}
