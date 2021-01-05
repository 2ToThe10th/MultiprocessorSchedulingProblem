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

Answer HeuristicAlgorithm(std::vector<Task> tasks, size_t number_of_machine) {
  if (tasks.size() <= number_of_machine) {
    std::vector<Machine*> machines(number_of_machine);
    size_t max_task_time = 0;
    for (size_t i = 0; i < number_of_machine; ++i) {
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

  std::vector<Machine*> result_machine;
  size_t answer = 0;

  while (!machine_heap.empty()) {
    result_machine.push_back(machine_heap.top());
    answer = std::max(result_machine.back()->GetCurrentWorkload(), answer);
    machine_heap.pop();
  }

  return Answer(answer, result_machine);
}