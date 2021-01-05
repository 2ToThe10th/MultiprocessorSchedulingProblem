//
// Created by 2ToThe10th on 05.01.2021.
//

#include "Answer.h"

#include <utility>
Answer::Answer(size_t answer, std::vector<Machine *> machines) : answer(answer), machines(std::move(machines)) {}

std::string Answer::ToString() {
  std::string res;
  for (size_t i = 0; i < machines.size(); ++i) {
    res += std::to_string(i + 1);
    res += ": ";
    res += machines[i]->ToString();
    res += '\n';
  }
  return res;
}

Answer::~Answer() {
  for (auto machine: machines) {
    delete machine;
  }
}
int Answer::GetAnswer() const {
  return answer;
}
