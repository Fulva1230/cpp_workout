//
// Created by fulva on 9/7/2021.
//

#include "gtest/gtest.h"

class X {
public:
  X(int x, X g) {}

private:
  int y;
};

TEST(test_for_constness, test1) {}