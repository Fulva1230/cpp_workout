//
// Created by fulva on 10/29/2021.
//

#include <numeric>

#include <gtest/gtest.h>

// collect too many common factor so f overflows
int Zeroes(int base, int number) {
  unsigned long long f = 1;
  int z = 0;
  for (int i = 1; i <= number; ++i) {
    int i_tmp = i;
    int gcd = std::gcd(base, i_tmp);
    while (gcd != 1) {
      i_tmp /= gcd;
      f *= gcd;
      if (f % base == 0) {
        f /= base;
        z++;
      }
      gcd = std::gcd(base, i_tmp);
    }
  }
  return z;
}

TEST(Factorial, TestBasic) {
  //  EXPECT_EQ(Zeroes(7, 50), 8);
  //  EXPECT_EQ(Zeroes(12, 26), 10);
  //  EXPECT_EQ(Zeroes(17, 100), 5);
  EXPECT_EQ(Zeroes(22, 3929), 391);
}
