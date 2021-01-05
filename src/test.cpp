//
// Created by 2ToThe10th on 03.01.2021.
//

#include <gtest/gtest.h>
#include <random>
#include <chrono>
#include "MultiprocessorSchedulingAlgorihtm.h"

TEST(HeuristicAlgorithm, Example) {
  auto answer = HeuristicAlgorithm({Task(3), Task(3), Task(2), Task(2), Task(2)}, 2);

  ASSERT_EQ(7, answer.GetAnswer());

  std::cout << answer.ToString();
}

TEST(HeuristicAlgorithm, Example2) {
  auto answer = HeuristicAlgorithm({Task(500), Task(500), Task(250), Task(250), Task(250)}, 2);

  ASSERT_EQ(1000, answer.GetAnswer());
}

TEST(HeuristicAlgorithm, Example3) {
  auto answer = HeuristicAlgorithm({Task(1), Task(1), Task(2), Task(2), Task(3)}, 3);

  ASSERT_EQ(3, answer.GetAnswer());

  std::cout << answer.ToString();
}

void SpeedTest(size_t number_of_test,
               size_t number_of_task_rand_min,
               size_t number_of_task_rand_max,
               size_t time_for_task_rand_min,
               size_t time_for_task_rand_max,
               size_t number_of_machine_rand_min,
               size_t number_of_machine_rand_max,
               size_t time_expected_max_ms) {
  std::mt19937 gen(42);
  std::uniform_int_distribution<> number_of_task_rand(number_of_task_rand_min, number_of_task_rand_max);
  std::uniform_int_distribution<> time_for_task_rand(time_for_task_rand_min, time_for_task_rand_max);
  std::uniform_int_distribution<> number_of_machine_rand(number_of_machine_rand_min, number_of_machine_rand_max);

  size_t full_time_in_millisecond = 0;

  for (size_t test = 0; test < number_of_test; ++test) {
    size_t number_of_task = number_of_task_rand(gen);
    std::vector<Task> tasks;
    tasks.reserve(number_of_task);
    for (size_t i = 0; i < number_of_task; ++i) {
      tasks.emplace_back(time_for_task_rand(gen));
    }
    auto clock_start = std::chrono::steady_clock::now();
    HeuristicAlgorithm(tasks, number_of_machine_rand(gen));
    full_time_in_millisecond +=
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - clock_start).count();
  }

  size_t time_for_one_operation = full_time_in_millisecond / number_of_test;

  std::cout << time_for_one_operation << std::endl;

  ASSERT_LT(time_for_one_operation, time_expected_max_ms);
}

TEST(HeuristicAlgorithm, SpeedTest1) {
  SpeedTest(10, 3e5, 1e6, 1, 1e7, 1e5, 3e5, 10000);
}

TEST(HeuristicAlgorithm, SpeedTest2) {
  SpeedTest(10, 3e5, 1e6, 1, 1e7, 1e2, 3e3, 5000);
}

TEST(HeuristicAlgorithm, SpeedTest3) {
  SpeedTest(3, 3e6, 1e7, 1, 1e7, 1e5, 3e5, 100000);
}

TEST(HeuristicAlgorithm, SpeedTest4) {
  SpeedTest(100, 3e3, 1e4, 1, 1e7, 1e2, 3e3, 30);
}
