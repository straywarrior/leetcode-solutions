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

struct ListNode {
    int val;
    ListNode * next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class OddEvenList {
public:
    ListNode * oddEvenList(ListNode * head) {
        if (head == nullptr)
            return nullptr;
        ListNode * last_odd = head;
        if (head->next == nullptr)
            return head;
        ListNode * last_even = head->next;
        ListNode * even_head = last_even;

        even_head->next = nullptr;
        ListNode * iter = last_even->next;
        int i = 0;
        for (; iter != nullptr; ++i, iter = iter->next) {
            if (i % 2 == 0) {
                last_odd->next = iter;
                last_odd = iter;
            } else {
                last_even->next = iter;
                last_even = iter;
            }
        }
        last_odd->next = even_head;
        last_even->next = nullptr;
        return head;
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.odd_even_linked_list" ) {
    OddEvenList sol;
    using TestCase = std::tuple< ListNode*, ListNode* >;
    std::vector<TestCase> test_cases {
    };

    for (auto & t : test_cases) {
        CHECK(sol.oddEvenList(std::get<0>(t)) == std::get<1>(t));
        std::cout << std::endl;
    }
}
