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

class BinaryTreeValidSerialization {
public:
    bool isValidSerialization(string preorder) {
        return solve_ver1(preorder);
    }

    bool solve_ver1(string preorder) {
        // This solution is something tricky
        // Since we can treat empty nodes as leaf nodes, the binary tree is
        // similar to full binary tree, which has a good property that
        // Num. of leaves = Num. of non-leaves + 1
        // Is it possible to work with in-order / post-order traversal?
        if (preorder.empty()) return false;
        preorder += ',';
        int sz = preorder.size(), idx = 0;
        int capacity = 1;
        for (idx = 0; idx < sz; idx++){
            if (preorder[idx] != ',') continue;
            capacity--;
            if (capacity < 0) return false;
            if (preorder[idx - 1] != '#') capacity += 2;

        }
        return capacity == 0;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.verify_preorder_serialization_of_a_binary_tree" ) {
    BinaryTreeValidSerialization sol;
    using TestCase = std::tuple< string, bool >;
    std::vector<TestCase> test_cases {
        TestCase{ "9,3,4,#,#,1,#,#,2,#,6,#,#", true }, // pre-order
        TestCase{ "#,4,#,3,#,1,#,9,#,2,#,6,#", false }, // in-order
        TestCase{ "1,#", false },
        TestCase{ "9,#,#,1", false },
    };

    for (auto & t : test_cases) {
        CHECK(sol.isValidSerialization(std::get<0>(t)) == std::get<1>(t));
    }
}
