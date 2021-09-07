//
// Created by fulva on 9/7/2021.
//

#include "gtest/gtest.h"

#include "break_the_pieces.h"

TEST(break_the_pieces, generate_graph) {
  auto res = generate_graph("+------+\n|      |\n+------+");
  EXPECT_EQ(res[0][0], Point::Vertex);
  EXPECT_EQ(res[1][7], Point::Connected);
  EXPECT_EQ(res[1][0], Point::Connected);
  EXPECT_EQ(res[1][3], Point::Unconnected);
  EXPECT_EQ(res[1][4], Point::Unconnected);
  EXPECT_EQ(res[0][3], Point::Connected);
  EXPECT_EQ(res[2][3], Point::Connected);
  EXPECT_EQ(res[2][0], Point::Vertex);
}