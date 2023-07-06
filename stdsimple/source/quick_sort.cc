#include "catch/catch.hpp"

#include <tuple>
#include <string>
#include <stack>
#include <cctype>
#include <climits>
#include <iostream>
#include <cstdlib>
#include <cstdio>

namespace simplestd {

// lo and hi are both included in partition, which is different with sort
int partition_v1(std::vector<int>& arr, int lo, int hi) {
    const int bl(lo), bh(hi);
    int rand_idx = rand() % (hi - lo) + lo;
    int target = arr[rand_idx];
    arr[rand_idx] = arr[lo];
    arr[lo] = target;
    while (lo < hi) {
        while (lo < hi && arr[hi] >= target) {
            --hi;
        }
        // arr[hi] < target, current arr[lo] is held by variable or arr[hi]
        arr[lo] = arr[hi];
        while (lo < hi && arr[lo] <= target) {
            ++lo;
        }
        // current arr[hi] has been moved to arr[lo]
        arr[hi] = arr[lo];
    }
    arr[lo] = target;
    return lo;
}

int partition_v2(std::vector<int>& arr, int lo, int hi) {
    int rand_idx = rand() % (hi - lo) + lo;
    int target = arr[rand_idx];
    arr[rand_idx] = arr[lo];
    arr[lo] = target;
    while (lo < hi) {
        while (lo < hi) {
            if (arr[hi] > target) --hi;
            else {
                arr[lo] = arr[hi];
                ++lo;
                break;
            }
        }
        while (lo < hi) {
            if (arr[lo] < target) ++lo;
            else {
                arr[hi] = arr[lo];
                --hi;
                break;
            }
        }
    }
    arr[lo] = target;
    return lo;
}

void quick_sort_v1(std::vector<int>& arr, int lo, int hi) {
    if (lo + 1 >= hi) {
        // only 0 or 1 element
        return;
    }
    if (lo + 2 == hi) {
        // only 2 elements
        if (arr[lo] > arr[lo + 1]) {
            int t = arr[lo];
            arr[lo] = arr[lo + 1];
            arr[lo + 1] = t;
        }
        return;
    }
    int mi = partition_v2(arr, lo, hi - 1);
    quick_sort_v1(arr, lo, mi);
    quick_sort_v1(arr, mi + 1, hi);
    return;
}

void quick_sort_v2(std::vector<int>& arr, int lo, int hi) {
    std::stack<std::pair<int, int>> partition_results;
    partition_results.push(std::make_pair(lo, hi));
    while (!partition_results.empty()) {
        std::tie(lo, hi) = partition_results.top();
        partition_results.pop();
        if (lo + 1 >= hi) {
            // only 0 or 1 element
            continue;
        }
        if (lo + 2 == hi) {
            // only 2 elements
            if (arr[lo] > arr[lo + 1]) {
                int t = arr[lo];
                arr[lo] = arr[lo + 1];
                arr[lo + 1] = t;
            }
            continue;
        }
        int mi = partition_v2(arr, lo, hi - 1);
        partition_results.push(std::make_pair(lo, mi));
        partition_results.push(std::make_pair(mi + 1, hi));
    }
    return;
}

}

TEST_CASE("simplestd.quick_sort", "basic") {
    using namespace std;
    using TestCase = std::tuple<vector<int>, vector<int>>;
    std::vector<TestCase> test_cases {
        TestCase { {}, {} },
        TestCase { {0}, {0} },
        TestCase { {2,1}, {1,2} },
        TestCase { {3,1,5,2,8,4}, {1,2,3,4,5,8} },
        TestCase { {25,17,19,27,3,15,14,0,22,22,22,2,20,26,12,5,13,6,9,10,16,11,24,21,29,18,8,28,1,4,7,23},
            {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,22,22,23,24,25,26,27,28,29} },
        TestCase { {1,2,3,4,5,0}, {0,1,2,3,4,5} }
    };

    for (auto& t : test_cases) {
        vector<int>& arr = get<0>(t);
        simplestd::quick_sort_v2(arr, 0, arr.size());
        CHECK(arr == get<1>(t));
    }
}
