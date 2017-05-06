/*
 * arrange_coins.cpp
 * Copyright (C) 2017 StrayWarrior <i@straywarrior.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "common.hpp"
#include <limits>

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class PathSum3 {
public:
    int pathSum(TreeNode *root, int sum, int last) {
        if (!root)
            return 0;
        int current = last + root->val;
        return (current == sum) + \
               pathSum(root->left, sum, current) + \
               pathSum(root->right, sum, current);
    }
    int pathSum(TreeNode *root, int sum) {
        if (!root)
            return 0;
        return pathSum(root->left, sum) + \
               pathSum(root->right, sum) + \
               pathSum(root, sum, 0);
    }
};

static constexpr int kNullValue = std::numeric_limits<int>::min();

static std::vector<TreeNode> createTree(const std::vector<int> &_values) {
    std::vector<TreeNode> tree(_values.size(), TreeNode(kNullValue));
    for (size_t i = 0; i < _values.size(); ++i) {
        tree[i].val = _values[i];
        size_t left = i * 2 + 1;
        if (left < _values.size() && _values[left] != kNullValue)
            tree[i].left = &(tree[left]);
        size_t right = i * 2 + 2;
        if (right < _values.size() && _values[right] != kNullValue)
            tree[i].right = &(tree[right]);
    }
    return tree;
}

TEST_CASE( "test corectness", "leetcode.cpp.all_anagrams_in_string" ) {
    PathSum3 sol;
    std::vector<int> tree_values {10, 5, -3, 3, 2, kNullValue, 11, 3, -2, kNullValue, 1};
    std::vector<TreeNode> tree = createTree(tree_values);
    using TestCase = std::tuple<TreeNode*, int, int>;
    std::vector<TestCase> test_cases {
        TestCase(tree.data(), 8, 3),
    };

    for (auto & t : test_cases) {
        CHECK(sol.pathSum(std::get<0>(t), std::get<1>(t)) == std::get<2>(t));
    }
}
