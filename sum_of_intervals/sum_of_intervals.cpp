//
// Created by fulva on 11/3/2021.
//

#include "gtest/gtest.h"

#include <unordered_set>
#include <utility>
#include <vector>

int sum_intervals(std::vector<std::pair<int, int>> intervals) {
  std::unordered_set<int> interval_set;
  for (const auto &interval : intervals) {
    for (int i = interval.first; i < interval.second; ++i) {
      interval_set.insert(i);
    }
  }
  return std::size(interval_set);
}

TEST(SumOfIntervals, TestBasic) {}
