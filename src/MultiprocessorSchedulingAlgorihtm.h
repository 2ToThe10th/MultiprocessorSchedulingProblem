//
// Created by 2ToThe10th on 05.01.2021.
//

#include <algorithm>
#include <utility>
#include <queue>
#include "Machine.h"
#include "Answer.h"

struct CompareByCurrentWorkload {
  bool operator()(Machine *first, Machine *second) {
    return first->GetCurrentWorkload() > second->GetCurrentWorkload();
  }
};

struct CompareTaskByTime {
  bool operator()(const Task &first, const Task &second) {
    return first.GetTime() > second.GetTime();
  }
};

size_t HeuristicAlgorithm(std::vector<Task> tasks, size_t number_of_machine) {
  if (tasks.size() <= number_of_machine) {
    size_t max_task_time = 0;
    for (auto task: tasks) {
      max_task_time = std::max(max_task_time, task.GetTime());
    }
    return max_task_time;
  }

  std::sort(tasks.begin(), tasks.end(), CompareTaskByTime());

  std::priority_queue<size_t, std::vector<size_t>, std::greater<>> machine_heap;

  for (size_t i = 0; i < number_of_machine; ++i) {
    machine_heap.push(tasks[i].GetTime());
  }

  for (size_t i = number_of_machine; i < tasks.size(); ++i) {
    auto machine_time = machine_heap.top();
    machine_heap.pop();
    machine_time += tasks[i].GetTime();
    machine_heap.push(machine_time);
  }

  size_t answer = 0;

  while (!machine_heap.empty()) {
    answer = machine_heap.top();
    machine_heap.pop();
  }

  return answer;
}

Answer HeuristicAlgorithmWithHistory(std::vector<Task> tasks, size_t number_of_machine) {
  if (tasks.size() <= number_of_machine) {
    std::vector<Machine *> machines(tasks.size());
    size_t max_task_time = 0;
    for (size_t i = 0; i < tasks.size(); ++i) {
      machines[i] = new Machine();
      machines[i]->InsertTask(tasks[i]);
      max_task_time = std::max(max_task_time, tasks[i].GetTime());
    }
    return Answer(max_task_time, machines);
  }

  std::sort(tasks.begin(), tasks.end(), CompareTaskByTime());

  std::priority_queue<Machine *, std::vector<Machine *>, CompareByCurrentWorkload> machine_heap;

  for (size_t i = 0; i < number_of_machine; ++i) {
    auto machine = new Machine();
    machine->InsertTask(tasks[i]);
    machine_heap.push(machine);
  }

  for (size_t i = number_of_machine; i < tasks.size(); ++i) {
    Machine *machine = machine_heap.top();
    machine_heap.pop();
    machine->InsertTask(tasks[i]);
    machine_heap.push(machine);
  }

  std::vector<Machine *> result_machine;
  size_t answer = 0;

  while (!machine_heap.empty()) {
    result_machine.push_back(machine_heap.top());
    answer = std::max(result_machine.back()->GetCurrentWorkload(), answer);
    machine_heap.pop();
  }

  return Answer(answer, result_machine);
}

void BruteForceAlgorithmDFS(const std::vector<Task> &tasks,
                            std::vector<size_t> &machines,
                            size_t upper_bound,
                            size_t current_position,
                            size_t *answer,
                            size_t current_answer);

size_t BruteForceAlgorithm(const std::vector<Task> &tasks, size_t number_of_machine, size_t upper_bound) {
  size_t answer = std::numeric_limits<size_t>::max();
  std::vector<size_t> machines(number_of_machine, 0);
  BruteForceAlgorithmDFS(tasks, machines, upper_bound, 0, &answer, 0);
  return answer;
}

void BruteForceAlgorithmDFS(const std::vector<Task> &tasks,
                            std::vector<size_t> &machines,
                            size_t upper_bound,
                            size_t current_position,
                            size_t *answer,
                            size_t current_answer) {
  if (current_position == tasks.size()) {
    *answer = std::min(*answer, current_answer);
    return;
  }

  auto task = tasks[current_position];

  for (auto &machine: machines) {
    if (machine + task.GetTime() <= upper_bound) {
      machine += task.GetTime();
      BruteForceAlgorithmDFS(tasks,
                             machines,
                             upper_bound,
                             current_position + 1,
                             answer,
                             std::max(machine, current_answer));
      machine -= task.GetTime();
    }
  }
}
