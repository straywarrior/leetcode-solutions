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

// if not found, returns false
std::pair<bool, int> find_majority(const std::vector<int>& arr) {
    int candidate = 0;
    int count = 0;
    for (auto x : arr) {
        if (count == 0) {
            candidate = x;
            ++count;
        } else {
            if (candidate == x) count += 1;
            else count -= 1;
        }
    }
    if (count > 0) {
        return std::make_pair(true, candidate);
    } else {
        return std::make_pair(false, -1);
    }
}

void max_heapify(std::vector<int>& arr, int i, int n) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest = i;
    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        max_heapify(arr, largest, n);
    }
}

void build_max_heap(std::vector<int>& arr, int n) {
    for (int i = (n - 2) / 2; i >= 0; --i) {
        max_heapify(arr, i, n);
    }
}

// find top kth element
int find_kth_element_by_heap(const std::vector<int>& arr, int k) {
    std::vector<int> heap = arr;
    build_max_heap(heap, heap.size());
    int n = heap.size();
    for (int i = 0; i < k - 1; ++i) {
        std::swap(heap[0], heap[n - 1]);
        max_heapify(heap, 0, n - 1);
        --n;
    }
    return heap[0];
}

int find_pivot(std::vector<int>& arr, int lo, int hi) {
    if (lo == hi) {
        return lo;
    }
    if (lo + 1 == hi) {
        if (arr[lo] > arr[hi]) std::swap(arr[lo], arr[hi]);
        return lo;
    }
    int rand_idx = lo + rand() % (hi - lo + 1);
    std::swap(arr[rand_idx], arr[0]);
    int target = arr[0];
    while (lo < hi) {
        while (lo < hi && arr[hi] >= target) --hi;
        arr[lo] = arr[hi];
        std::swap(arr[lo], arr[hi]);
        while (lo < hi && arr[lo] <= target) ++lo;
        arr[hi] = arr[lo];
    }
    arr[lo] = target;
    return lo;
}

int find_kth_element_by_partition(const std::vector<int>& arr, int k) {
    std::vector<int> arr_copy = arr;
    int n = arr_copy.size();
    int pivot = -1;
    int lo = 0;
    int hi = n - 1;
    // for (int x : arr_copy) printf("%d ", x); printf("\n");
    while (pivot != n - k) {
        // pivot is init as -1, so this is true in first execution
        if (pivot < n - k) {
            lo = pivot + 1;
        } else {
            hi = pivot - 1;
        }
        pivot = find_pivot(arr_copy, lo, hi);
        // printf("pivot[%d]: %d\n", pivot, arr_copy[pivot]);
        // for (int x : arr_copy) printf("%d ", x); printf("\n");
    }
    return arr_copy[pivot];
}

int find_kth_element(const std::vector<int>& arr, int k) {
    return find_kth_element_by_partition(arr, k);
}

int find_kth_element_by_sort(const std::vector<int>& arr, int k) {
    std::vector<int> arr_copy = arr;
    std::sort(arr_copy.begin(), arr_copy.end());
    std::reverse(arr_copy.begin(), arr_copy.end());
    return arr_copy[k - 1];
}

}

TEST_CASE("simplestd.find_majority", "base") {
    using namespace std;
    using TestCase = std::tuple<vector<int>, pair<bool, int>>;
    std::vector<TestCase> test_cases {
        TestCase { {}, {false, -1} },
        TestCase { {0}, {true, 0} },
        TestCase { {1,1,5,2,8,4}, {false, -1} },
        TestCase { {1,1,2,3}, {false, -1}},
        TestCase { {1,1,1,1,0,0}, {true, 1} }
    };

    for (auto& t : test_cases) {
        const vector<int>& arr = get<0>(t);
        CHECK(simplestd::find_majority(arr) == get<1>(t));
    }
}

TEST_CASE("simplestd.find_kth_element", "base") {
    using namespace std;
    using TestCase = std::tuple<vector<int>, int>;
    std::vector<TestCase> test_cases {
        TestCase { {3,5,1,4,2,6}, 3 },
        TestCase { {3,5,1,4,2,6,2}, 3 }
    };

    for (auto& t : test_cases) {
        const vector<int>& arr = get<0>(t);
        int k = get<1>(t);
        CHECK(simplestd::find_kth_element(arr, k)
                == simplestd::find_kth_element_by_sort(arr, k));
    }
}
