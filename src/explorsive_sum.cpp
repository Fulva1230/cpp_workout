//
// Created by b1050 on 8/12/2021.
//

#include <unordered_map>

#include <catch2/catch_test_macros.hpp>

using ull = unsigned long long;

std::unordered_map<unsigned int, ull> cache{};

ull exp_sum_without_lowerequal(unsigned int n, unsigned int wo) {
  if (wo == 1) {
    return cache[n] - cache[n - 1];
  } else {
    ull sum = cache[n] - cache[n - 1];
    for (int wx = 2; wx <= wo; ++wx) {
      sum -= exp_sum_without_lowerequal(n - wx, wx - 1);
    }
    return sum;
  }
}

ull exp_sum(unsigned int n) {
  cache[0] = 1;
  cache[1] = 1;
  for (unsigned int i = 2; i <= n; ++i) {
    cache[i] = 1;
    cache[i] += cache[i - 1];
    for (int j = 2; j <= (i / 2); ++j) {
      cache[i] += exp_sum_without_lowerequal(i - j, j - 1);
    }
  }
  return cache[n];
}

TEST_CASE("exp_sum") {
  CHECK(exp_sum(5) == 7);
  CHECK(exp_sum(6) == 11);
  CHECK(exp_sum(8) == 22);
  CHECK(exp_sum(10) == 42);
  CHECK(exp_sum(20) == 627);
}