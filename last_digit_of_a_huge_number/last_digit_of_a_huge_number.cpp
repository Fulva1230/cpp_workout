//
// Created by fulva on 11/6/2021.
//

#include <iostream>
#include <limits>
#include <list>
#include <unordered_map>

#include <gtest/gtest.h>

using namespace std;

enum class SpecType { MAXIMUM, MODULE };

struct Spec {
  SpecType type = SpecType::MODULE;
  int value = 0;
};

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

Spec get_power_spec(int base, Spec base_spec) {
  if (base_spec.type == SpecType::MAXIMUM) {
    if (base == 0 || base == 1) {
      return {SpecType::MODULE, 1};
    }
    int agg_mul = 1;
    for (int i = 1;; ++i) {
      agg_mul *= base;
      if (agg_mul >= base_spec.value) {
        return {SpecType::MAXIMUM, i};
      }
    }
  } else {
    int agg_mul = base;
    int remaining = base % base_spec.value;
    for (int i = 2;; ++i) {
      agg_mul *= base;
      if (agg_mul % base_spec.value == remaining) {
        return {SpecType::MODULE, i - 1};
      }
      if (agg_mul % base_spec.value == 0) {
        return {SpecType::MAXIMUM, i};
      }
    }
  }
}

int last_digit(int base, list<int> powers, Spec base_spec) {
  if (base_spec.type == SpecType::MODULE && base != 0) {
    base = (base - 1) % base_spec.value + 1;
  }
  if (std::size(powers) == 0) {
    if (base == 0) {
      return 0;
    }
    if (base_spec.type == SpecType::MODULE) {
      return (base - 1) % base_spec.value + 1;
    } else if (base_spec.type == SpecType::MAXIMUM) {
      return (base_spec.value > base) ? base : base_spec.value;
    }
  } else {
    Spec power_spec = get_power_spec(base, base_spec);
    int power = last_digit(
        powers.front(), std::list<int>(std::next(powers.begin()), powers.end()),
        power_spec);
    if (base == 0) {
      if (power == 0) {
        return 1;
      } else {
        return 0;
      }
    }
    if (power_spec.type == SpecType::MAXIMUM && power == power_spec.value) {
      return base_spec.value;
    } else {
      if (base_spec.type == SpecType::MODULE) {
        return (my_pow(base, power) - 1) % base_spec.value + 1;
      } else {
        return my_pow(base, power);
      }
    }
  }
}

int last_digit(list<int> array) {
  if (array.empty()) {
    return 1;
  }

  int res = last_digit(array.front(),
                       std::list<int>(std::next(array.begin()), array.end()),
                       {SpecType::MODULE, 10});
  if (res == 10) {
    return 0;
  } else {
    return res;
  }
}

TEST(LastDigitOfAHugeNumber, TestCycleNum) {}

TEST(LastDigitOfAHugeNumber, TestLastDeigit) {
  EXPECT_EQ(last_digit({1, 2}), 1);
  EXPECT_EQ(last_digit({3, 4, 2}), 1);
  EXPECT_EQ(last_digit({12, 30, 21}), 6);
  EXPECT_EQ(last_digit({7, 6, 21}), 1);
  EXPECT_EQ(last_digit({499942, 898102, 846073}), 6);
  EXPECT_EQ(last_digit({0, 0, 0}), 0);
  EXPECT_EQ(last_digit({0, 0}), (1));
  EXPECT_EQ(last_digit({3, 2, 0, 0, 2, 0}), 9);
  EXPECT_EQ(last_digit({3, 2, 0, 0, 0}), 3);
}