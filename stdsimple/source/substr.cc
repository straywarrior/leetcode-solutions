#include "catch/catch.hpp"

#include <tuple>
#include <string>
#include <cctype>
#include <iostream>

using namespace std;

namespace simplestd {

/**
 * @param str1 string to search
 * @param str2 substring to search for
 * @return -1 if the substring not found
 */
int substr(const char* str1, int size1, const char* str2, int size2) {
    if (str1 == nullptr || str2 == nullptr) {
        return -1;
    }
    if (size1 == 0 || size2 == 0) {
        // it's undefined if size2 == 0
        return -1;
    }

    const char* str1end = str1 + size1;
    const char* str2end = str2 + size2;

    // construct dp table, for ascii character
    // for ascii string, char should >= 0
    auto dp = new int[size2][128];
    for (int i = 0; i < size2; ++i) {
        memset(dp[i], 0, sizeof(int) * 128);
    }

    // initial transform
    dp[0][(unsigned char)str2[0]] = 1;
    int X = 0;
    int j = 0; // j is state, [0, j) has been matched
    for (int j = 1; j < size2; ++j) {
        char s_char = str2[j];
        for (unsigned char c = 'A'; c <= 'Z'; ++c) {
            if (s_char == c) {
                // matched, go to next state
                dp[j][c] = j + 1;
            } else {
                // unmatched, return to previous state (denoted by shadow state X)
                dp[j][c] = dp[X][c];
            }
        }
        // update shadow state
        X = dp[X][s_char];
        std::cout << s_char << ", " << X << " ";
    }
    cout << endl;
    for (char j = 'A'; j <= 'Z'; ++j) {
        cout << j << " ";
    }
    cout << endl;

    for (int i = 0; i < size2; ++i) {
        for (int j = 'A'; j <= 'Z'; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    
    // use dp table to do match
    j = 0;
    for (const char* p1 = str1; p1 != str1end; ++p1) {
        j = dp[j][(unsigned char)*p1];
        std::cout << j << " ";
        if (j == size2) {
            return (p1 - size2) - str1 - 1;
        }
    }
    return -1;
}

}

static int substr(const std::string &s1, const std::string &s2) {
    return simplestd::substr(s1.data(), s1.size(), s2.data(), s2.size());
}

TEST_CASE("substr", "base") {
    using TestCase = std::tuple<std::string, std::string, int>;
    std::vector<TestCase> test_cases {
        {"ABABABC", "ABABABD", -1},
        // {"ABABABC", "BAB", 1},
        // {"ABABABC", "ABC", 4},
    };

    for (auto& t : test_cases) {
        CHECK(substr(get<0>(t), get<1>(t)) == get<2>(t));
    }
}
