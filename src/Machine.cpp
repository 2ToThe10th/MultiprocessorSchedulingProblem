//
// Created by 2ToThe10th on 05.01.2021.
//

#include <iostream>
#include "Machine.h"
size_t Machine::GetCurrentWorkload() const {
  return current_workload;
}
const std::vector<Task> &Machine::GetTasks() const {
  return tasks;
}
void Machine::InsertTask(Task task) {
  tasks.push_back(task);
  current_workload += task.GetTime();
}
std::string Machine::ToString() const {
  std::string res;
  for (auto task: GetTasks()) {
    res += "|";
    res += std::string(task.GetTime() - 1, '-');
  }
  return res;
}
