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

void max_heapify(int* p_arr, int i, int n) {
    int l = i * 2 + 1;
    int r = i * 2 + 2;
    int max_node = i;
    if (l < n && p_arr[l] > p_arr[max_node]) {
        max_node = l;
    }
    if (r < n && p_arr[r] > p_arr[max_node]) {
        max_node = r;
    }
    if (max_node != i) {
        std::swap(p_arr[i], p_arr[max_node]);
        max_heapify(p_arr, max_node, n);
    }
}

// range is [lo, hi)
void build_max_heap(std::vector<int>& arr, int lo, int hi) {
    // printf("before build heap: ");
    // for (int i = lo; i < hi; ++i) printf("%d ", arr[i]); printf("\n");
    if (lo + 1 >= hi) {
        // empty or only 1 elements
        return;
    }
    // lo + 2 <= hi
    int* p_arr = arr.data() + lo;
    int n = hi - lo;
    int last_internal_node = (n - 2) / 2;
    for (int i = last_internal_node; i >= 0; --i) {
        max_heapify(p_arr, i, n);
    }
    // printf("after build heap: ");
    // for (int i = lo; i < hi; ++i) printf("%d ", arr[i]); printf("\n");
}

void heap_sort(std::vector<int>& arr, int lo, int hi) {
    build_max_heap(arr, lo, hi);
    int* p_arr = arr.data() + lo;
    int n = hi - lo;
    // i == lo, the vector is ordered
    for (int i = hi - 1; i > lo; --i) {
        std::swap(arr[i], arr[lo]);
        max_heapify(p_arr, 0, i - lo);
    }
    return;
}

}

TEST_CASE("simplestd.heap_sort", "basic") {
    using namespace std;
    using TestCase = std::tuple<vector<int>>;
    std::vector<TestCase> test_cases {
        TestCase { {} },
        TestCase { {0} },
        TestCase { {2,1} },
        TestCase { {3,1,5,2,8,4} },
        TestCase { {25,17,19,27,3,15,14,0,22,22,22,2,20,26,12,5,13,6,9,10,16,11,24,21,29,18,8,28,1,4,7,23} },
        TestCase { {1,2,3,4,5,0} }
    };

    for (auto& t : test_cases) {
        vector<int> arr = get<0>(t);
        vector<int> ans = arr;
        simplestd::heap_sort(arr, 0, arr.size());
        std::sort(ans.begin(), ans.end());
        CHECK(arr == ans);
    }

    for (auto& t : test_cases) {
        vector<int> arr = get<0>(t);
        if (arr.size() < 10) continue;
        vector<int> ans = arr;
        simplestd::heap_sort(arr, 5, arr.size());
        std::sort(ans.begin() + 5, ans.end());
        CHECK(arr == ans);
    }
}
