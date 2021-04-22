/*
 * single_threaaded_cpu.cpp
 * Copyright (C) 2021 StrayWarrior <i@straywarrior.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "common.hpp"
#include <queue>
#include <list>

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

using namespace std;
namespace {

class Solution {
public:
    vector<int> solve(vector<vector<int>>& tasks) {
        vector<int> ret = solve_incompletev1(tasks);
        return ret;
    }

    struct Task {
        int idx;
        int enqueue_time;
        int process_time;
    };

    vector<int> solve_incompletev1(vector<vector<int>>& tasks) {
        int n = tasks.size();
        vector<Task> sorted_tasks(n);
        for (int i = 0; i < n; ++i) {
            sorted_tasks[i].idx = i;
            sorted_tasks[i].enqueue_time = tasks[i][0];
            sorted_tasks[i].process_time = tasks[i][1];
        }
        std::stable_sort(
            sorted_tasks.begin(), sorted_tasks.end(),
            [](const Task& a, const Task& b) {
                return a.enqueue_time < b.enqueue_time;
            }
        );
        vector<int> ret;
        priority_queue<int, std::vector<int>, std::greater<int>> runtime_types;
        // unordered_map<int, vector<pair<int, vector<int, int>>> task_map;
        // process_time -> task_idx, enqueue_time
        unordered_map<int, list<pair<int, int>>> task_map;
        int current_time = 0;
        int next_idle_time = 0;
        int event_time = 0;
        for (int i = 0; i < n; ++i) {
            const auto& front_task = sorted_tasks[i];
            int event_time = front_task.enqueue_time;
            int process_time = front_task.process_time;
            std::cout << "add task " << front_task.idx
                << ", enqueue time: " << event_time
                << ", process time: " << process_time << std::endl;
            task_map[process_time].push_back(
                    std::make_pair(front_task.idx, event_time));
            runtime_types.push(process_time);
            int next_enqueue_time = INT_MAX;
            if (i + 1 < n) {
                next_enqueue_time = sorted_tasks[i + 1].enqueue_time;
                if (event_time == next_enqueue_time) {
                    // do not schedule until all the tasks at the same time
                    // are considered
                    continue;
                }
                // do not schedule if cpu is not idle and
                // there are other tasks to be read.
                if (next_idle_time > event_time) {
                    continue;
                }
            }

            // try to schedule
            while (!runtime_types.empty() &&
                    next_idle_time < next_enqueue_time) {
                int process_time = runtime_types.top();
                runtime_types.pop();
                auto& tasks = task_map[process_time];
                const auto& task = tasks.front();
                int task_idx = task.first;
                int enqueue_time = task.second;
                tasks.pop_front();
                ret.push_back(task_idx);
                next_idle_time = std::max(next_idle_time, enqueue_time);
                std::cout << "schedule at time " << next_idle_time
                    << ", task " << task_idx
                    << ", process_time: " << process_time << std::endl;
                next_idle_time += process_time;
            }
        }
        return ret;
    }
};

}

TEST_CASE( "test corectness", "leetcode.cpp.single_threaded_cpu" ) {
    Solution sol;
    using TestCase = std::tuple<vector<vector<int>>, vector<int>>;
    std::vector<TestCase> test_cases {
        TestCase({{1, 2}, {2, 4}, {3, 2}, {4, 1}}, {0, 2, 3, 1}),
        TestCase({{7, 10}, {7, 12}, {7, 5}, {7, 4}, {7, 2}}, {4, 3, 2, 0, 1}),
        TestCase({{19,13},{16,9},{21,10},{32,25},{37,4},{49,24},{2,15},{38,41},{37,34},{33,6},{45,4},{18,18},{46,39},{12,24}}, {{6,1,2,9,4,10,0,11,5,13,3,8,12,7}})
    };

    for (auto & t : test_cases) {
        CHECK(sol.solve(std::get<0>(t)) == std::get<1>(t));
        std::cout << std::endl;
    }
}
