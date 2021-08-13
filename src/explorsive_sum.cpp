//
// Created by b1050 on 8/12/2021.
//

#include <iostream>
#include <unordered_map>

#include <catch2/catch_test_macros.hpp>

using ull = unsigned long long;

std::unordered_map<unsigned int, std::unordered_map<unsigned int, ull>> cache{};

int i = 2;

ull exp_sum(unsigned int n) {
  cache[0][0] = 1;
  cache[1][0] = 1;
  for (; i <= n; ++i) {
    for (int j = 0; j < i; ++j) {
      cache[i][j] = 1;
      for (int q = 1; q <= (i / 2) - j; ++q) {
        cache[i][j] += cache[i - j - q][j + q - 1];
      }
    }
  }
  return cache[n][0];
}

TEST_CASE("exp_sum") {
  CHECK(exp_sum(2) == 2);
  CHECK(exp_sum(3) == 3);
  CHECK(exp_sum(5) == 7);
  CHECK(exp_sum(6) == 11);
  CHECK(exp_sum(8) == 22);

  CHECK(exp_sum(10) == 42);
  CHECK(exp_sum(20) == 627);
  CHECK(exp_sum(100) == 190569292);
  CHECK(exp_sum(230) == 47826239745920);
  CHECK(exp_sum(408) == 10990600063775926994LL);
}