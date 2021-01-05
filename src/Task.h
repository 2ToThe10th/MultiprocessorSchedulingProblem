//
// Created by 2ToThe10th on 05.01.2021.
//

#ifndef MULTIPROCESSORSCHEDULINGPROBLEM_SRC_TASK_H_
#define MULTIPROCESSORSCHEDULINGPROBLEM_SRC_TASK_H_

#include <cstdlib>
class Task {
 private:
  size_t time;

 public:
  Task& operator=(Task&&) = default;
  constexpr Task(const Task&) = default;

  explicit Task(size_t time);
  size_t GetTime() const;
};

#endif //MULTIPROCESSORSCHEDULINGPROBLEM_SRC_TASK_H_
