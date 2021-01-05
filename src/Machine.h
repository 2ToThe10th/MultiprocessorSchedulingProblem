//
// Created by 2ToThe10th on 05.01.2021.
//

#ifndef MULTIPROCESSORSCHEDULINGPROBLEM_SRC_MACHINE_H_
#define MULTIPROCESSORSCHEDULINGPROBLEM_SRC_MACHINE_H_

#include <cstdlib>
#include <vector>
#include <string>
#include "Task.h"
class Machine {
 private:
  size_t current_workload = 0;
  std::vector<Task> tasks;
 public:
  size_t GetCurrentWorkload() const;
  const std::vector<Task> &GetTasks() const;
  void InsertTask(Task task);
  std::string ToString() const;
};

#endif //MULTIPROCESSORSCHEDULINGPROBLEM_SRC_MACHINE_H_
