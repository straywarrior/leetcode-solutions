/*
 * arrange_coins.cpp
 * Copyright (C) 2017 StrayWarrior <i@straywarrior.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "common.hpp"

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

using Matrix = std::vector<std::vector<int>>;
using Result = std::vector<std::pair<int, int>>;

using namespace std;

class PacificAtlanticWaterFlow {
public:
    vector<vector<int>> flags_;
    vector<pair<int, int>> stack_;

    /** DFS helper
     */
    void dfs(vector<vector<int>>& _matrix, int x, int y, int _flag) {
        stack_.emplace_back(x, y);
        int rows = _matrix.size();
        int cols = _matrix[0].size();
        while (stack_.size() != 0) {
            auto pos = stack_.back();
            stack_.pop_back();
            flags_[pos.first][pos.second] |= _flag;
            int cur_val = _matrix[pos.first][pos.second];
            int x_offset[4] = {0, 0, -1, 1};
            int y_offset[4] = {-1, 1, 0, 0};
            for (int i = 0; i < 4; ++i) {
                x = pos.first + x_offset[i];
                y = pos.second + y_offset[i];
                if (x < 0 || x >= rows || y < 0 || y >= cols || flags_[x][y] & _flag)
                    continue;
                if (_matrix[x][y] >= cur_val)
                    stack_.emplace_back(x, y);
            }
        }
    }

    /** DFS version solution
     */
    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
        vector<pair<int, int>> result;
        int rows = matrix.size();
        int cols = rows > 0 ? matrix[0].size() : 0;
        if (rows == 0 || cols == 0)
            return result;
        flags_.resize(rows, vector<int>(cols, 0));
        for (int i = 0; i < rows; ++i) {
            dfs(matrix, i, 0, 0x01);
            dfs(matrix, i, cols - 1, 0x02);
        }
        for (int i = 0; i < cols; ++i) {
            dfs(matrix, 0, i, 0x01);
            dfs(matrix, rows - 1, i, 0x02);
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (flags_[i][j] == 0x03)
                    result.emplace_back(i, j);
            }
        }

        return result;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.all_anagrams_in_string" ) {
    PacificAtlanticWaterFlow sol;
    using TestCase = std::tuple<Matrix, Result>;
    std::vector<TestCase> test_cases {
        TestCase(
                Matrix{ { 1, 2, 2, 3, 5 },
                        { 3, 2, 3, 4, 4 },
                        { 2, 4, 5, 3, 1 },
                        { 6, 7, 1, 4, 5 },
                        { 5, 1, 1, 2, 4 }}, 
                Result{ make_pair<int, int>(0, 4),
                        make_pair<int, int>(1, 3),
                        make_pair<int, int>(1, 4),
                        make_pair<int, int>(2, 2),
                        make_pair<int, int>(3, 0),
                        make_pair<int, int>(3, 1),
                        make_pair<int, int>(4, 0) }
        ),
    };

    for (auto & t : test_cases) {
        CHECK(sol.pacificAtlantic(std::get<0>(t)) == std::get<1>(t));
    }
}
