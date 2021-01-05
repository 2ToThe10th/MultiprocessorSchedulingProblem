//
// Created by 2ToThe10th on 05.01.2021.
//

#include "Task.h"
Task::Task(const size_t time) : time(time) {}
size_t Task::GetTime() const {
  return time;
}
