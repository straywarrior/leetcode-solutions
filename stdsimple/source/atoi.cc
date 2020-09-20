#include "catch/catch.hpp"

#include <tuple>
#include <string>
#include <cctype>
#include <iostream>

namespace simplestd {

// Discards any whitespace characters until the first non-whitespace character
// is found, then takes as many characters as possible to form a valid integer
// number representation and converts them to an integer value.
int atoi(const char* str) {
    if (str == nullptr) {
        return 0;
    }
    int r = 0;
    int negative = 1;
    const char* cursor = str;
    // use a finite-state-machine
    // first skip leading white spaces
    for (;*cursor != '\0'; ++cursor) {
        if (!isspace(*cursor)) {
            break;
        }
    }
    if (*cursor == '\0') {
        return 0;
    }
    if (*cursor == '-') {
        negative = -1;
        ++cursor;
    }
    for (;*cursor != '\0'; ++cursor) {
        if (!isdigit(*cursor)) {
            break;
        }
        r = r * 10 + (*cursor - '0');
    }
    // even though INT_MIN is actually overflowed, the result is still correct
    // due to the complement calculation.
    return negative * r;
}

}

TEST_CASE("correctness", "simplestd.atoi") {
    using TestCase = std::tuple<std::string, int>;
    std::vector<TestCase> test_cases {
        TestCase { "42", 42 },
        TestCase { "3.14159", 3},
        TestCase { "-3.14159", -3},
        TestCase { "31337 with words", 31337},
        TestCase { "words and 2", 0},
        TestCase { "\r\t\n42", 42},
        TestCase { "0x23", 0},
        TestCase { "0123", 123},
        TestCase { std::to_string(INT_MAX), INT_MAX},
        TestCase { std::to_string(INT_MIN), INT_MIN},
    };

    for (auto& t : test_cases) {
        const char* str = std::get<0>(t).c_str();
        CHECK(simplestd::atoi(str) == std::get<1>(t));
        CHECK(simplestd::atoi(str) == atoi(str));
    }
}