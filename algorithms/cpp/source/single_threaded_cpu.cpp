/*
 * single_threaaded_cpu.cpp
 * Copyright (C) 2021 StrayWarrior <i@straywarrior.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "common.hpp"
#include <queue>
#include <list>
#include <climits>

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

using namespace std;
namespace {

class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        vector<int> ret = solve_v2(tasks);
        return ret;
    }

    struct Task {
        int idx;
        int enqueue_time;
        int process_time;
    };

    using TaskQueueValue = pair<int, int>;
    struct TaskQueueValueComp {
        // see TaskQueueValue as <idx, enqueue_time>
        bool operator()(const TaskQueueValue& a, const TaskQueueValue& b) {
            return a.first > b.first;
        }
    };

    vector<int> solve_trivial(vector<vector<int>>& tasks) {
        vector<int> ret;
        int n = tasks.size();
        priority_queue<TaskQueueValue, vector<TaskQueueValue>, greater<TaskQueueValue>> task_queue;
        vector<Task> sorted_tasks(n);
        for (int i = 0; i < n; ++i) {
            sorted_tasks[i].idx = i;
            sorted_tasks[i].enqueue_time = tasks[i][0];
            sorted_tasks[i].process_time = tasks[i][1];
        }
        std::sort(
            sorted_tasks.begin(), sorted_tasks.end(),
            [](const Task& a, const Task& b) {
                return a.enqueue_time < b.enqueue_time;
            }
        );

        int i = 0;
        int64_t current_time = 0;
        int64_t next_idle_time = 0;
        const int64_t max_enqueue_time = sorted_tasks.back().enqueue_time + 1;
        while (current_time < max_enqueue_time) {
            while (i < n && current_time == sorted_tasks[i].enqueue_time) {
                task_queue.emplace(sorted_tasks[i].process_time, sorted_tasks[i].idx);
                // std::cout << "time: " << current_time << ", add task " << sorted_tasks[i].idx << " process_time: " << sorted_tasks[i].process_time << std::endl;
                ++i;
            }
            if (current_time >= next_idle_time && !task_queue.empty()) {
                auto task = std::move(task_queue.top());
                task_queue.pop();
                next_idle_time = current_time + task.first;
                ret.push_back(task.second);
                // std::cout << "time: " << current_time << ", run task " << task.second << std::endl;
            }
            ++current_time;
        }
        while (!task_queue.empty()) {
            auto task = std::move(task_queue.top());
            task_queue.pop();
            ret.push_back(task.second);
            // std::cout << "run task " << task.second << std::endl;
        }
        return ret;
    }

    vector<int> solve_v2(vector<vector<int>>& tasks) {
        vector<int> ret;
        int n = tasks.size();
        priority_queue<TaskQueueValue, vector<TaskQueueValue>, greater<TaskQueueValue>> task_queue;
        vector<Task> sorted_tasks(n);
        for (int i = 0; i < n; ++i) {
            sorted_tasks[i].idx = i;
            sorted_tasks[i].enqueue_time = tasks[i][0];
            sorted_tasks[i].process_time = tasks[i][1];
        }
        std::sort(
            sorted_tasks.begin(), sorted_tasks.end(),
            [](const Task& a, const Task& b) {
                return a.enqueue_time < b.enqueue_time;
            }
        );

        int i = 0;
        int64_t current_time = 0;
        int64_t next_idle_time = 0;
        while (!task_queue.empty() || i < n) {
            current_time = std::max<int64_t>(next_idle_time, sorted_tasks[i].enqueue_time);
            if (task_queue.empty()) {
                next_idle_time = current_time;
            }
            while (i < n && sorted_tasks[i].enqueue_time <= current_time) {
                // std::cout << "time: " << current_time << ", add task " << sorted_tasks[i].idx << ", process_time: " << sorted_tasks[i].process_time << std::endl;
                task_queue.emplace(sorted_tasks[i].process_time, sorted_tasks[i].idx);
                ++i;
            }
            if (i < n) {
                current_time = sorted_tasks[i].enqueue_time;
            } else {
                current_time = INT_MAX;
            }
            while (next_idle_time < current_time && !task_queue.empty()) {
                auto task = std::move(task_queue.top());
                task_queue.pop();
                next_idle_time += task.first;
                ret.push_back(task.second);
                // std::cout << "time: " << current_time << ", run task " << task.second << ", process_time: " << task.first << std::endl;
            }
        }
        return ret;
    }

    vector<int> solve_v1(vector<vector<int>>& tasks) {
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
        using TaskQueue = priority_queue<TaskQueueValue,
                                         vector<TaskQueueValue>,
                                         TaskQueueValueComp>;
        unordered_map<int, TaskQueue> task_map;
        task_map.reserve(20000);
        int64_t next_idle_time = 0;
        int event_time = 0;

        auto do_schedule_to = [&](int64_t next_enqueue_time) {
            while (!runtime_types.empty() &&
                    next_idle_time < next_enqueue_time) {
                int process_time = runtime_types.top();
                runtime_types.pop();
                auto& tasks = task_map[process_time];
                const auto& task = tasks.top();
                int task_idx = task.first;
                int64_t enqueue_time = task.second;
                tasks.pop();
                ret.push_back(task_idx);
                next_idle_time = std::max(next_idle_time, enqueue_time);
                // std::cout << "schedule at time " << next_idle_time
                //     << ", task " << task_idx
                //     << ", process_time: " << process_time << std::endl;
                next_idle_time += process_time;
            }
        };

        bool wait_same_time_tasks = false;
        for (int i = 0; i < n; ++i) {
            const auto& front_task = sorted_tasks[i];
            int event_time = front_task.enqueue_time;
            int process_time = front_task.process_time;
            if (next_idle_time < event_time && wait_same_time_tasks == false) {
                do_schedule_to(event_time);
            }
            // std::cout << "add task " << front_task.idx
            //     << ", enqueue time: " << event_time
            //     << ", process time: " << process_time << std::endl;
            task_map[process_time].push(
                    std::make_pair(front_task.idx, event_time));
            runtime_types.push(process_time);
            int next_enqueue_time = INT_MAX;
            if (i + 1 < n) {
                next_enqueue_time = sorted_tasks[i + 1].enqueue_time;
                if (event_time == next_enqueue_time) {
                    // do not schedule until all the tasks at the same time
                    // are considered
                    wait_same_time_tasks = true;
                    continue;
                } else {
                    wait_same_time_tasks = false;
                }
            }
        }
        // try to schedule
        do_schedule_to(INT64_MAX);
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
        TestCase({{19,13},{16,9},{21,10},{32,25},{37,4},{49,24},{2,15},{38,41},{37,34},{33,6},{45,4},{18,18},{46,39},{12,24}}, {6,1,2,9,4,10,0,11,5,13,3,8,12,7}),
        TestCase({{46,9},{46,42},{30,46},{30,13},{30,24},{30,5},{30,21},{29,46},{29,41},{29,18},{29,16},{29,17},{29,5},{22,15},{22,13},{22,25},{22,49},{22,44}}, {14,5,12,3,0,13,10,11,9,6,4,15,8,1,17,2,7,16})
    };

    for (auto & t : test_cases) {
        CHECK(sol.getOrder(std::get<0>(t)) == std::get<1>(t));
        std::cout << std::endl;
    }
}
