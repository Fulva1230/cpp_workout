#include <algorithm>
#include <set>
#include <string>

#include "gtest/gtest.h"

using namespace std;

enum class PointState { CLEAR, BLOCKED };

using point_set_t = std::set<std::pair<int, int>>;
using maze_t = std::vector<std::vector<PointState>>;
using potential_map_t = std::vector<std::vector<int>>;

std::vector<std::pair<int, int>> shifts{{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

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

potential_map_t construct_potential_map(const maze_t &maze) {
  potential_map_t potential_map{};
  for (const auto &row : maze) {
    potential_map.emplace_back(std::vector(std::size(row), -1));
  }
  return potential_map;
}

void find_potential(maze_t &maze, const potential_map_t &potential_map,
                    potential_map_t &next_potential_map) {
  for (int r = 0; r < std::size(potential_map); ++r) {
    for (int c = 0; c < std::size(potential_map[r]); ++c) {
      if (maze[r][c] != PointState::BLOCKED) {
        std::vector<int> potential_candidate;
        for (auto [row_shift, col_shift] : shifts) {
          int row_index = r + row_shift;
          int col_index = c + col_shift;
          if (0 <= row_index && row_index < std::size(maze) && 0 <= col_index &&
              col_index < std::size(maze[row_index])) {
            if (maze[row_index][col_index] == PointState::CLEAR &&
                potential_map[row_index][col_index] != -1) {
              potential_candidate.emplace_back(
                  potential_map[row_index][col_index]);
            }
          }
        }
        auto min_element = std::min_element(potential_candidate.begin(),
                                            potential_candidate.end());
        if (min_element != potential_candidate.end()) {
          next_potential_map[r][c] = *min_element + 1;
        }
      }
    }
  }
}

int path_finder(string maze) {
  auto new_maze = maze_build(maze);
  int len = std::size(new_maze);
  potential_map_t potential_map = construct_potential_map(new_maze);
  potential_map[0][0] = 0;
  potential_map_t next_potential_map = construct_potential_map(new_maze);
  next_potential_map[0][0] = 0;
  find_potential(new_maze, potential_map, next_potential_map);
  while (next_potential_map != potential_map) {
    potential_map = next_potential_map;
    find_potential(new_maze, potential_map, next_potential_map);
    next_potential_map[0][0] = 0;
  }
  return potential_map[len - 1][len - 1];
}

TEST(PathFinder, test_steps) {
  EXPECT_EQ(path_finder(".W.\n"
                        ".W.\n"
                        "..."),
            4);
  EXPECT_EQ(path_finder("......\n......\n......\n......\n.....W\n....W."),
            -1);
}