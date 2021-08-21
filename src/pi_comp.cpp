//
// Created by fulva on 2021/8/21.
//

#include <catch2/catch_test_macros.hpp>
#include <iostream>

double pi_compute(double ratio) {
  double m1 = 1;
  double m2 = ratio;
  double v1i = 0;
  double v2i = -1;
  double v1f = 0;
  double v2f = 0;
  unsigned long long count = 0;
  while (v2i < v1i) {
    count += 2;
    v1f = (m1 - m2) / (m1 + m2) * v1i + 2 * m2 / (m1 + m2) * v2i;
    v2f = (m2 - m1) / (m1 + m2) * v2i + 2 * m1 / (m1 + m2) * v1i;
    v1i = v1f;
    v1i = -v1i;
    v2i = v2f;
  }
  return static_cast<double>(count) / std::sqrt(ratio);
}

TEST_CASE("test pi") {
  std::cout << "pi is " << pi_compute(1000000000000) << std::endl;
}