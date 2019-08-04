/*
 * copy_list_with_random_pointer.cpp
 * Copyright (C) 2019 StrayWarrior <i@straywarrior.com>
 *
 * Distributed under terms of the MIT license.
 */


#include "common.hpp"

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

using namespace std;

struct Node {
    int val;
    Node * next;
    Node * random;
    Node() {}
    Node(int _val, Node * _next, Node * _random) {
        val = _val;
        next = _next;
        random = _random;
    }
};

class CopyRandomList {
public:
    Node * copyRandomList(Node * head) {
        if (head == nullptr)
            return nullptr;
        // 1st pass, copy the list without the "random" pointer,
        // create a map<Node *, size_t> for the source list
        // create a vector<Node *> for the destination list
        std::unordered_map<Node *, size_t> src_node_indexes;
        std::vector<Node *> dst_node_ptrs;
        Node sentinel;
        size_t node_cnt = 0;
        Node * last_dst_ptr = &sentinel;
        for (Node * iter = head; iter != nullptr; iter = iter->next) {
            Node * dst_node_ptr = new Node(iter->val, nullptr, nullptr);
            src_node_indexes[iter] = node_cnt;
            dst_node_ptrs.push_back(dst_node_ptr);
            last_dst_ptr->next = dst_node_ptr;
            last_dst_ptr = dst_node_ptr;
            ++node_cnt;
        }
        // 2nd pass, complete the "random" pointer
        Node * dst_ptr = &sentinel;
        for (Node * src_ptr = head; src_ptr != nullptr; src_ptr = src_ptr->next) {
            dst_ptr = dst_ptr->next;
            Node * random_ptr = src_ptr->random;
            if (random_ptr == nullptr) {
                dst_ptr->random = nullptr;
                continue;
            }
            dst_ptr->random = dst_node_ptrs[src_node_indexes[random_ptr]];
        }
        return sentinel.next;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.copy_list_with_random_pointer" ) {
    CopyRandomList sol;
    using TestCase = std::tuple< Node*, Node* >;
    std::vector<TestCase> test_cases {
    };

    for (auto & t : test_cases) {
        CHECK(sol.copyRandomList(std::get<0>(t)) == std::get<1>(t));
        std::cout << std::endl;
    }
}
