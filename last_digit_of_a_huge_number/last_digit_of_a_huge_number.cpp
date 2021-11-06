//
// Created by fulva on 11/6/2021.
//

#include <iostream>
#include <list>
#include <unordered_map>

#include <gtest/gtest.h>

using namespace std;

int power_cycle_num(int base, int module) {
  int i = 2;
  int remaining = base % module;
  int power = base * base;
  int power_remaining = power % module;
  while (power_remaining != remaining) {
    ++i;
    power *= base;
    power_remaining = power % module;
  }
  return i-1;
}

int my_pow(int x, unsigned int p) {
  if (p == 0)
    return 1;
  if (p == 1)
    return x;

  int tmp = my_pow(x, p / 2);
  if (p % 2 == 0)
    return tmp * tmp;
  else
    return x * tmp * tmp;
}

int last_digit(list<int> array) {
  std::vector<int> cycle_array;
  cycle_array.push_back(10);
  int i = 0;
  for (auto cur_iter = std::begin(array);
       cur_iter != std::end(array); ++cur_iter, ++i) {
    cycle_array.push_back(power_cycle_num(*cur_iter, cycle_array[i]));
  }

  auto cur_iter_r = array.rbegin();
  auto end_iter_r = array.rend();
  auto cur_cycle_array_iter_r = std::next(cycle_array.rbegin());
  int power = (*cur_iter_r-1) % *cur_cycle_array_iter_r + 1;
  ++cur_iter_r;
  ++cur_cycle_array_iter_r;
  for (; cur_iter_r != end_iter_r;
       ++cur_iter_r, ++cur_cycle_array_iter_r) {
    int reduced_base = (*cur_iter_r-1) % *cur_cycle_array_iter_r + 1;
    power = (my_pow(reduced_base, power)-1) % *cur_cycle_array_iter_r + 1;
  }
  return power;
}

TEST(LastDigitOfAHugeNumber, TestCycleNum) {
  EXPECT_EQ(power_cycle_num(2, 10), 4);
  EXPECT_EQ(power_cycle_num(3, 10), 4);
  EXPECT_EQ(power_cycle_num(9, 10), 2);
}

TEST(LastDigitOfAHugeNumber, TestLastDeigit) {
//  EXPECT_EQ(last_digit({1,2}), 1);
//  EXPECT_EQ(last_digit({3, 4, 2}), 1);
//  EXPECT_EQ(last_digit({12,30,21}), 6);
  EXPECT_EQ(last_digit({7,6,21}),   1);
}