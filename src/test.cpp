//
// Created by 2ToThe10th on 03.01.2021.
//

#include <gtest/gtest.h>
#include <random>
#include <chrono>
#include "MultiprocessorSchedulingAlgorihtm.h"

// one random for all tests
std::mt19937 kRandomGenerator(42);

TEST(HeuristicAlgorithmWithHistory, Example) {
  auto answer = HeuristicAlgorithmWithHistory({Task(3), Task(3), Task(2), Task(2), Task(2)}, 2);

  ASSERT_EQ(7, answer.GetAnswer());
  std::cout << answer.ToString();
}

TEST(HeuristicAlgorithmWithHistory, Example2) {
  auto answer = HeuristicAlgorithmWithHistory({Task(5), Task(5), Task(3), Task(3), Task(3)}, 2);

  ASSERT_EQ(11, answer.GetAnswer());
  std::cout << answer.ToString();
}

TEST(HeuristicAlgorithmWithHistory, Example3) {
  auto answer = HeuristicAlgorithmWithHistory({Task(1), Task(1), Task(2), Task(2), Task(3)}, 3);

  ASSERT_EQ(3, answer.GetAnswer());
  std::cout << answer.ToString();
}

void CheckEqualAlgorithm(size_t number_of_test,
                         size_t number_of_task_rand_min,
                         size_t number_of_task_rand_max,
                         size_t time_for_task_rand_min,
                         size_t time_for_task_rand_max,
                         size_t number_of_machine_rand_min,
                         size_t number_of_machine_rand_max) {
  std::uniform_int_distribution<> number_of_task_rand(number_of_task_rand_min, number_of_task_rand_max);
  std::uniform_int_distribution<> time_for_task_rand(time_for_task_rand_min, time_for_task_rand_max);
  std::uniform_int_distribution<> number_of_machine_rand(number_of_machine_rand_min, number_of_machine_rand_max);

  for (size_t test = 0; test < number_of_test; ++test) {
    size_t number_of_task = number_of_task_rand(kRandomGenerator);
    std::vector<Task> tasks;
    tasks.reserve(number_of_task);
    for (size_t i = 0; i < number_of_task; ++i) {
      tasks.emplace_back(time_for_task_rand(kRandomGenerator));
    }
    size_t number_of_machine = number_of_machine_rand(kRandomGenerator);
    ASSERT_EQ(HeuristicAlgorithm(tasks, number_of_machine),
              HeuristicAlgorithmWithHistory(tasks, number_of_machine).GetAnswer());
  }
}

TEST(HeuristicAlgorithm, CheckEqualAlgorithm1) {
  CheckEqualAlgorithm(5, 3e5, 1e6, 1, 1e7, 1e5, 3e5);
}

TEST(HeuristicAlgorithm, CheckEqualAlgorithm2) {
  CheckEqualAlgorithm(5, 1e2, 1e3, 1, 1e7, 1e5, 3e5);
}

TEST(HeuristicAlgorithm, CheckEqualAlgorithm3) {
  CheckEqualAlgorithm(5, 3e5, 1e6, 1, 1e2, 1e3, 3e5);
}

void SpeedTest(size_t number_of_test,
               size_t number_of_task_rand_min,
               size_t number_of_task_rand_max,
               size_t time_for_task_rand_min,
               size_t time_for_task_rand_max,
               size_t number_of_machine_rand_min,
               size_t number_of_machine_rand_max,
               size_t time_expected_max_ms) {
  std::uniform_int_distribution<> number_of_task_rand(number_of_task_rand_min, number_of_task_rand_max);
  std::uniform_int_distribution<> time_for_task_rand(time_for_task_rand_min, time_for_task_rand_max);
  std::uniform_int_distribution<> number_of_machine_rand(number_of_machine_rand_min, number_of_machine_rand_max);

  size_t full_time_in_millisecond = 0;

  for (size_t test = 0; test < number_of_test; ++test) {
    size_t number_of_task = number_of_task_rand(kRandomGenerator);
    std::vector<Task> tasks;
    tasks.reserve(number_of_task);
    for (size_t i = 0; i < number_of_task; ++i) {
      tasks.emplace_back(time_for_task_rand(kRandomGenerator));
    }
    auto clock_start = std::chrono::steady_clock::now();
    HeuristicAlgorithm(tasks, number_of_machine_rand(kRandomGenerator));
    full_time_in_millisecond +=
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - clock_start).count();
  }

  size_t time_for_one_operation = full_time_in_millisecond / number_of_test;

  std::cout << "mean time: " << time_for_one_operation << std::endl;

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

TEST(BruteForceAlgorithm, EasyTask) {
  ASSERT_EQ(BruteForceAlgorithm({Task(3), Task(3), Task(2), Task(2), Task(2)}, 2, 10), 6);
  ASSERT_EQ(BruteForceAlgorithm({Task(3), Task(3), Task(2), Task(2), Task(2)}, 2, 6), 6);
  ASSERT_EQ(BruteForceAlgorithm({Task(3), Task(3), Task(2), Task(2), Task(2)}, 2, 5),
            std::numeric_limits<size_t>::max());
  ASSERT_EQ(BruteForceAlgorithm({Task(1), Task(1), Task(1), Task(1), Task(1), Task(1),
                                 Task(1), Task(1), Task(1)}, 2, 10), 5);
}

void CompareToBruteForce(size_t number_of_test,
                         size_t number_of_task_rand_min,
                         size_t number_of_task_rand_max,
                         size_t time_for_task_rand_min,
                         size_t time_for_task_rand_max,
                         size_t number_of_machine_rand_min,
                         size_t number_of_machine_rand_max) {
  std::uniform_int_distribution<> number_of_task_rand(number_of_task_rand_min, number_of_task_rand_max);
  std::uniform_int_distribution<> time_for_task_rand(time_for_task_rand_min, time_for_task_rand_max);
  std::uniform_int_distribution<> number_of_machine_rand(number_of_machine_rand_min, number_of_machine_rand_max);

  double kMaxAttitudeOfAnswers = 4. / 3.;

  double mean_attitude = 0;

  for (size_t test = 0; test < number_of_test; ++test) {
    size_t number_of_task = number_of_task_rand(kRandomGenerator);
    std::vector<Task> tasks;
    tasks.reserve(number_of_task);
    for (size_t i = 0; i < number_of_task; ++i) {
      tasks.emplace_back(time_for_task_rand(kRandomGenerator));
    }
    size_t number_of_machine = number_of_machine_rand(kRandomGenerator);
    size_t heuristic_answer = HeuristicAlgorithm(tasks, number_of_machine);
    size_t brute_force_answer = BruteForceAlgorithm(tasks, number_of_machine, heuristic_answer);
    double attitude = ((double) heuristic_answer) / brute_force_answer;
    std::cout << "Attitude on test number " << test + 1 << ": " << attitude << '\n';
    ASSERT_LE(attitude, kMaxAttitudeOfAnswers);
    mean_attitude += attitude;
  }

  mean_attitude /= number_of_test;

  std::cout << "Mean attitude of heuristic answer to brute force answer: " << mean_attitude << '\n';
}

TEST(HeuristicAlgorithm, CheckToBruteForce1) {
  CompareToBruteForce(10, 5, 10, 1, 1e7, 2, 4);
}

TEST(HeuristicAlgorithm, CheckToBruteForce2) {
  CompareToBruteForce(10, 10, 15, 1, 1e7, 3, 6);
}

TEST(HeuristicAlgorithm, CheckToBruteForce3) {
  CompareToBruteForce(10, 15, 20, 1, 1e7, 2, 3);
}

TEST(HeuristicAlgorithm, CheckToBruteForce4) {
  CompareToBruteForce(10, 11, 15, 1, 1e7, 3, 5);
}