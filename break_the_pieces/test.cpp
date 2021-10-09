//
// Created by fulva on 9/7/2021.
//

#include "gtest/gtest.h"

#include "break_the_pieces.h"

TEST(break_the_pieces, generate_graph) {
  auto res = generate_graph("+------+\n"
                            "|      |\n"
                            "+------+");
  EXPECT_EQ(res[0][0], Point::Vertex);
  EXPECT_EQ(res[1][7], Point::Connected);
  EXPECT_EQ(res[1][0], Point::Connected);
  EXPECT_EQ(res[1][3], Point::Unconnected);
  EXPECT_EQ(res[1][4], Point::Unconnected);
  EXPECT_EQ(res[0][3], Point::Connected);
  EXPECT_EQ(res[2][3], Point::Connected);
  EXPECT_EQ(res[2][0], Point::Vertex);
}

TEST(break_the_pieces, drawer_normal) {
  auto res = generate_graph("+------+\n|      |\n+------+");
  Drawer drawer{res, {0, 0}};
  auto drawResult = drawer.draw().value();
  EXPECT_EQ(drawResult[0][0], Point::Vertex);
  EXPECT_EQ(drawResult[1][7], Point::Connected);
  EXPECT_EQ(drawResult[1][0], Point::Connected);
  EXPECT_EQ(drawResult[1][3], Point::Unconnected);
  EXPECT_EQ(drawResult[1][4], Point::Unconnected);
  EXPECT_EQ(drawResult[0][3], Point::Connected);
  EXPECT_EQ(drawResult[2][3], Point::Connected);
  EXPECT_EQ(drawResult[2][0], Point::Vertex);
}

TEST(break_the_pieces, drawer_init_on_line) {
  auto res = generate_graph("+------+\n|      |\n+------+");
  Drawer drawer{res, {1, 0}};
  auto drawResult = drawer.draw();
  EXPECT_TRUE(!drawResult.has_value());
}

TEST(break_the_pieces, drawer_init_on_left_down) {
  auto res = generate_graph("+------+\n|      |\n+------+");
  Drawer drawer{res, {2, 0}};
  auto drawResult = drawer.draw();
  EXPECT_TRUE(!drawResult.has_value());
}

TEST(break_the_pieces, drawer_init_on_unconnected) {
  auto res = generate_graph("+------+\n|      |\n+------+");
  Drawer drawer{res, {1, 3}};
  auto drawResult = drawer.draw();
  EXPECT_TRUE(!drawResult.has_value());
}

TEST(break_the_pieces, shrink_draw) {
  auto res = generate_graph(""
                            "   +---+\n"
                            "   |   |\n"
                            "+--+---+\n"
                            "|      |\n"
                            "+------+");
  Drawer drawer{res, {2, 3}};
  auto drawResult = drawer.draw().value();
  auto res1 = generate_graph(""
                             "+------+\n"
                             "|      |\n"
                             "+------+"
                             "");
  EXPECT_EQ(drawResult, res1);
}