//
// Created by fulva on 10/9/2021.
//

#include <cmath>

#include <gtest/gtest.h>

#include <magic_compare.h>

TEST(TestMagiceCompare, Basic) {
  MagicCompare<double> n{9.0};
  if (!n) {
    EXPECT_TRUE(false);
  }
  EXPECT_TRUE(static_cast<bool>(3.0 < n));
  EXPECT_FALSE(static_cast<bool>(3.0 < n < 8));
  EXPECT_TRUE(static_cast<bool>(3.0 < n<10.7 < 11.5> 3.0));
  EXPECT_TRUE(static_cast<bool>(10.5 > n));
  EXPECT_FALSE(static_cast<bool>(3.3 > n));
  EXPECT_TRUE(static_cast<bool>(n > 3.3));
  EXPECT_FALSE(static_cast<bool>(n > 11.4));
  EXPECT_TRUE(static_cast<bool>(n >= 3.3));
  EXPECT_FALSE(static_cast<bool>(n >= 11.4));
  EXPECT_TRUE(static_cast<bool>(3.0 <= n));
  EXPECT_FALSE(static_cast<bool>(10.0 <= n));

  sin(n);
}
