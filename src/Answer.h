//
// Created by 2ToThe10th on 05.01.2021.
//

#ifndef MULTIPROCESSORSCHEDULINGPROBLEM_SRC_ANSWER_H_
#define MULTIPROCESSORSCHEDULINGPROBLEM_SRC_ANSWER_H_

#include <vector>
#include <string>
#include "Machine.h"
class Answer {
 private:
  int answer;
  std::vector<Machine*> machines;

 public:
  int GetAnswer() const;

  Answer(int answer, std::vector<Machine*> machines);

  std::string ToString();

  virtual ~Answer();
};

#endif //MULTIPROCESSORSCHEDULINGPROBLEM_SRC_ANSWER_H_
