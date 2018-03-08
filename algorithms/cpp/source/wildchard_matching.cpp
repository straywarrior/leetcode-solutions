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

class WildchardMatching {
    int m, n;
public:
    bool isMatch(string s, string p) {
        return solve_two_pointers(s.c_str(), p.c_str());
    }

    bool solve_two_pointers(const char * s, const char * p) {
        // This solution is actually a DFS back tracking
        // The time complexity is O(mn)
        const char * p_star = nullptr;
        const char * s_star = s;
        while (*s) {
            if ((*p == '?') || (*p == *s)) {
                ++s;
                ++p;
                continue;
            }
            if (*p == '*') {
                p_star = p++;
                s_star = s;
                continue;
            }
            if (p_star) {
                p = p_star + 1;
                s = s_star + 1;
                ++s_star;
                continue;
            }
            return false;
        }
        while (*p == '*') {
            ++p;
        }
        return *p == '\0';
    }

    bool solve_recursive(string s, string p) {
        m = s.size();
        n = p.size();
        return isMatch(s, 0, p, 0);
    }

    bool isMatch(const string & s, int i, const string & p, int j) {
        // This solution is TLE
        if (j == n) {
            return i == m;
        }
        if (i == m) {
            if (p[j] == '*')
                return isMatch(s, i, p, j + 1);
            else
                return false;
        }
        if (p[j] == '*') {
            return isMatch(s, i + 1, p, j) || isMatch(s, i + 1, p, j + 1) || isMatch(s, i, p, j + 1);
        }
        if (p[j] == '?') {
            return isMatch(s, i + 1, p, j + 1);
        }
        if (s[i] != p[j])
            return false;
        else
            return isMatch(s, i + 1, p, j + 1);
    }
};

TEST_CASE( "test corectness", "leetcode.cpp.wildchard_matching" ) {
    WildchardMatching sol;
    using TestCase = std::tuple< string, string, bool >;
    std::vector<TestCase> test_cases {
        TestCase{ "", "*", true },
        TestCase{ "c", "*?*", true },
        TestCase{ "c", "?*", true },
        TestCase{ "c", "*??*", false },
        TestCase{ "c", "*?*?*", false },
        TestCase{ "aa", "*?*?*", true },
        TestCase{ "ho", "ho**", true },
        TestCase{ "aa", "a", false },
        TestCase{ "aa", "aa", true },
        TestCase{ "aaa", "aa", false },
        TestCase{ "aa", "*", true },
        TestCase{ "aa", "a*", true },
        TestCase{ "aa", "?*", true },
        TestCase{ "aab", "c*a*b", false },
        TestCase{ "aaaaaaaaaaaaaaaaaaaaaaa", "a", false },
        TestCase{ "aaaaaaaaaaaaaaaaaaaaaaa", "a***", true },
        TestCase{ "aaabababaaabaababbbaaaabbbbbbabbbbabbbabbaabbababab", "*ab***ba**b*b*aaab*b", true },
    };

    for (auto & t : test_cases) {
        CHECK(sol.isMatch(std::get<0>(t), std::get<1>(t)) == std::get<2>(t));
        std::cout << std::get<0>(t) << " " << std::get<1>(t) << std::endl;
    }
}
