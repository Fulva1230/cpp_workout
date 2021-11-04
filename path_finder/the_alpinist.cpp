//
// Created by fulva on 11/4/2021.
//

#include <deque>
#include <set>

#include "gtest/gtest.h"

using altitude_map_t = std::vector<std::vector<int>>;
using potential_map_t = std::vector<std::vector<int>>;

std::vector<std::pair<int, int>> shifts{{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

altitude_map_t get_altitude_map(const std::string &maze) {
  altitude_map_t altitude_map{};
  altitude_map.push_back({});
  for (char e : maze) {
    if (e != '\n') {
      std::prev(std::end(altitude_map))->push_back(std::stoi(std::string{e}));
    } else {
      altitude_map.push_back({});
    }
  }
  return altitude_map;
}

std::vector<std::pair<int, int>> available_moves(const int length,
                                                 std::pair<int, int> point) {
  std::vector<std::pair<int, int>> moves;
  for (auto [row_shift, col_shift] : shifts) {
    int row_index = row_shift + point.first;
    int col_index = col_shift + point.second;
    if (0 <= row_index && row_index < length && 0 <= col_index &&
        col_index < length) {
      moves.emplace_back(row_index, col_index);
    }
  }
  return moves;
}

void update_point(const int length, std::pair<int, int> point,
                  std::deque<std::pair<int, int>> &update_points,
                  const altitude_map_t &altitude_map,
                  potential_map_t &potential_map) {
  std::set<int> candidate;
  for (auto [row_index, col_index] : available_moves(length, point)) {
    if (potential_map[row_index][col_index] != -1) {
      candidate.insert(potential_map[row_index][col_index] +
                       abs(altitude_map[point.first][point.second] -
                           altitude_map[row_index][col_index]));
    }
  }
  int next_potential = *candidate.begin();
  if (next_potential != potential_map[point.first][point.second]) {
    potential_map[point.first][point.second] = next_potential;
    for (auto [row_index, col_index] : available_moves(length, point)) {
      if (row_index != length - 1 || col_index != length - 1)
        update_points.push_front({row_index, col_index});
    }
  }
}

int path_finder(std::string maze) {
  altitude_map_t altitude_map = get_altitude_map(maze);
  std::deque<std::pair<int, int>> update_points;
  const int length = std::size(altitude_map);
  if (length == 1) {
    return 0;
  }
  potential_map_t potential_map{};
  for (int i = 0; i < length; ++i) {
    potential_map.push_back(std::vector<int>(length, -1));
  }
  potential_map[length - 1][length - 1] = 0;
  update_points.emplace_back(length - 2, length - 1);
  while (!update_points.empty()) {
    update_point(length, *(--update_points.end()), update_points, altitude_map,
                 potential_map);
    update_points.pop_back();
  }
  return potential_map[0][0];
}

TEST(PathFinder, TheAlpinist) {
  std::string s2 = "010\n"
                   "010\n"
                   "010";
  EXPECT_EQ(path_finder(s2), 2);
}