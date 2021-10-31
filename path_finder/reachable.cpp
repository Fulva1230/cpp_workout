//
// Created by fulva on 10/31/2021.
//

#include <algorithm>
#include <iostream>
#include <set>
#include <string>

#include "gtest/gtest.h"

using namespace std;

enum class PointState { CLEAR, BLOCKED };

using point_set_t = std::set<std::pair<int, int>>;
using maze_t = std::vector<std::vector<PointState>>;

std::vector<std::pair<int, int>> shifts{{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

void eval_point(const maze_t &maze, point_set_t &eval_set,
                std::pair<int, int> point) {
  for (auto [row_shift, col_shift] : shifts) {
    int row_index = point.first + row_shift;
    int col_index = point.second + col_shift;
    if (0 <= row_index && row_index < std::size(maze) && 0 <= col_index &&
        col_index < std::size(maze[row_index])) {
      if (maze[row_index][col_index] == PointState::CLEAR) {
        eval_set.insert({row_index, col_index});
      }
    }
  }
}

maze_t maze_build(const string &maze) {
  maze_t new_maze;
  new_maze.emplace_back(std::vector<PointState>{});
  for (char e : maze) {
    if (e == '\n') {
      new_maze.emplace_back(std::vector<PointState>{});
    } else {
      if (e == 'W')
        std::prev(std::end(new_maze))->emplace_back(PointState::BLOCKED);
      else
        std::prev(std::end(new_maze))->emplace_back(PointState::CLEAR);
    }
  }
  return new_maze;
}

bool path_finder(string maze) {
  point_set_t reachable_set;
  point_set_t eval_set;
  maze_t new_maze = maze_build(maze);
  int len = std::size(new_maze);
  eval_set.insert({0, 0});
  while (!eval_set.empty()) {
    std::pair<int, int> point = *eval_set.begin();
    reachable_set.insert(point);
    eval_point(new_maze, eval_set, point);
    point_set_t next_eval_set;
    std::set_difference(eval_set.begin(), eval_set.end(), reachable_set.begin(),
                        reachable_set.end(),
                        std::inserter(next_eval_set, next_eval_set.begin()));
    eval_set = next_eval_set;
  }
  return reachable_set.find({len - 1, len - 1}) != std::end(reachable_set);
}

TEST(PathFinder, test_rechable) {
  EXPECT_EQ(path_finder(".W.\n"
                        ".W.\n"
                        "..."),
            true);
  EXPECT_EQ(path_finder("......\n......\n......\n......\n.....W\n....W."), false);
}
