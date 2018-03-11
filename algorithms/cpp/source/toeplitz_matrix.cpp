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

class ToeplitzMatrix {
public:
    bool isToeplitzMatrix(vector<vector<int>> & matrix) {
        int m = matrix.size();
        if (m == 0)
            return false;
        int n = matrix[0].size();
        for (int i = 0; i < m; ++i) {
            int x = matrix[i][0];
            for (int j = i + 1, k = 1; j < m && k < n; ++j, ++k) {
                if (matrix[j][k] != x)
                    return false;
            }
        }
        for (int i = 1; i < n; ++i) {
            int x= matrix[0][i];
            for (int j = 1, k = i + 1; j < m && k < n; ++j, ++k) {
                if (matrix[j][k] != x)
                    return false;
            }
        }
        return true;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.toeplitz_matrix" ) {
    ToeplitzMatrix sol;
    using TestCase = std::tuple< vector<vector<int>>, bool >;
    std::vector<TestCase> test_cases {
        TestCase{ {{1,2,3,4},{5,1,2,3},{9,5,1,2}}, true },
        TestCase{ {{1,2},{2,2}}, false },
    };

    for (auto & t : test_cases) {
        CHECK(sol.isToeplitzMatrix(std::get<0>(t)) == std::get<1>(t));
        std::cout << std::endl;
    }
}
