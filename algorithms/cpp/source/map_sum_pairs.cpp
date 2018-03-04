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

struct TrieNode {
    int sum = 0;
    TrieNode * children[26] = {0};
    // Here we do not care about memory leak
};

class MapSum {
public:
    MapSum() {
        trie_root = new TrieNode();
    }

    void insert(string key, int val) {
        if (key.size() == 0)
            return;
        auto map_iter = this->key_value_map.find(key);
        int last_value = 0;
        if (map_iter != this->key_value_map.end())
            last_value = map_iter->second;
        TrieNode * p = this->trie_root;
        for (char ch : key) {
            if (p->children[ch - 'a'] == nullptr) {
                p->children[ch - 'a'] = new TrieNode();
            }
            p = p->children[ch - 'a'];
            p->sum += val - last_value;
        }
        this->key_value_map[key] = val;
    }

    int sum(string prefix) {
        TrieNode * p = this->trie_root;
        for (auto ch : prefix) {
            if (p->children[ch - 'a'] == nullptr)
                return 0;
            p = p->children[ch - 'a'];
        }
        return p->sum;
    }

private:
    std::unordered_map<string, int> key_value_map;
    TrieNode * trie_root;
};

class MapSumTest {
public:
    int test_case(std::vector<std::pair<string, int>> & inputs, string prefix) {
        MapSum map_sum;
        for (auto p : inputs) {
            map_sum.insert(p.first, p.second);
        }
        return map_sum.sum(prefix);
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.map_sum_pairs" ) {
    MapSumTest sol;
    using TestCase = std::tuple<vector<pair<string, int>>, string, int>;
    std::vector<TestCase> test_cases {
        TestCase{ {{"apple", 3}, {"app", 2}}, "ap", 5 },
        TestCase{ {{"apple", 3}, {"app", 2}}, "apx", 0 },
        TestCase{ {{"apple", 3}, {"app", 5}, {"apple", 2}}, "ap", 7 },
    };

    for (auto & t : test_cases) {
        CHECK(sol.test_case(std::get<0>(t), std::get<1>(t)) == std::get<2>(t));
        std::cout << std::endl;
    }
}
