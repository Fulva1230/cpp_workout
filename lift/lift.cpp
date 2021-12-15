//
// Created by fulva on 12/15/2021.
//

#include "gtest/gtest.h"

#include <algorithm>
#include <list>
#include <set>
#include <vector>

bool is_anyone_waiting(const std::vector<std::list<int>> &queues) {
  return std::any_of(
      queues.begin(), queues.end(),
      [](const std::list<int> &queue) { return !queue.empty(); });
}

std::vector<int> the_lift(const std::vector<std::vector<int>> &queues,
                          int capacity) {
  std::vector<std::list<int>> queues_copy{};
  queues_copy.reserve(queues.size());
  for (const auto &queue : queues) {
    queues_copy.emplace_back(queue.begin(), queue.end());
  }
  std::vector<int> stops{0};
  std::multiset<int> lift_content{};
  int current_floor = 0;
  int current_direction = 1;
  while (is_anyone_waiting(queues_copy) || !lift_content.empty()) {
    bool should_stop = false;
    if (lift_content.erase(current_floor) > 0) {
      should_stop = true;
    }
    auto &current_queue = queues_copy[current_floor];
    for (auto iter = current_queue.begin(); iter != current_queue.end();) {
      if ((*iter - current_floor) * current_direction > 0 &&
          lift_content.size() < capacity) {
        lift_content.insert(*iter);
        iter = current_queue.erase(iter);
        should_stop = true;
      } else {
        ++iter;
      }
    }
    if (should_stop) {
      stops.push_back(current_floor);
    }
    if (current_floor == queues_copy.size() - 1 && current_direction == 1) {
      current_direction = -1;
    } else if (current_floor == 0 && current_direction == -1) {
      current_direction = 1;
    }
    current_floor += current_direction;
  }
  if (*std::prev(stops.end()) != 0) {
    stops.push_back(0);
  }
  return stops;
}

TEST(Lift, Basic) {
  ASSERT_EQ(the_lift({{}, {}, {5, 5, 5}, {}, {}, {}, {}}, 5),
            (std::vector<int>{0, 2, 5, 0}));
  ASSERT_EQ(the_lift({{}, {3}, {4}, {}, {5}, {}, {}}, 5),
            (std::vector<int>{0, 1, 2, 3, 4, 5, 0}));
}