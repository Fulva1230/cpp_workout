//
// Created by fulva on 2021/8/21.
//

#include <algorithm>
#include <array>
#include <catch2/catch_test_macros.hpp>

std::array unit = {1, 2, 3, 4, 5, 6, 7, 8, 9};

template <class T> bool validateUnit(T begin, T end) {
  return std::is_permutation(begin, end, std::begin(unit));
}

template <class T>
std::array<unsigned int, 9> columnView(const T &toView, int index) {
  std::array<unsigned int, 9> result{};
  for (int i = 0; i < 9; ++i) {
    result[i] = toView[i][index];
  }
  return result;
}

template <class T>
std::array<unsigned int, 9> rowView(const T &toView, int index) {
  std::array<unsigned int, 9> result{};
  for (int i = 0; i < 9; ++i) {
    result[i] = toView[index][i];
  }
  return result;
}

template <class T>
std::array<unsigned int, 9> gridView(const T &toView, int index) {
  std::array<unsigned int, 9> result{};
  int columnBase = index % 3;
  int rowBase = index / 3;
  for (int i = 0; i < 9; ++i) {
    int column = i % 3;
    int row = i / 3;
    result[i] = toView[rowBase * 3 + row][columnBase * 3 + column];
  }
  return result;
}

bool validSolution(unsigned int board[9][9]) {
  for (int i = 0; i < 9; ++i) {
    auto rowTest = rowView(board, i);
    if (!validateUnit(std::begin(rowTest), std::end(rowTest))) {
      return false;
    }
    auto columnTest = columnView(board, i);
    if (!validateUnit(std::begin(columnTest), std::end(columnTest))) {
      return false;
    }
    auto gridTest = gridView(board, i);
    if (!validateUnit(std::begin(gridTest), std::end(gridTest))) {
      return false;
    }
  }
  return true;
}

unsigned int example1[9][9] = {
    {5, 3, 4, 6, 7, 8, 9, 1, 2}, {6, 7, 2, 1, 9, 5, 3, 4, 8},
    {1, 9, 8, 3, 4, 2, 5, 6, 7}, {8, 5, 9, 7, 6, 1, 4, 2, 3},
    {4, 2, 6, 8, 5, 3, 7, 9, 1}, {7, 1, 3, 9, 2, 4, 8, 5, 6},
    {9, 6, 1, 5, 3, 7, 2, 8, 4}, {2, 8, 7, 4, 1, 9, 6, 3, 5},
    {3, 4, 5, 2, 8, 6, 1, 7, 9}};

unsigned int example2[9][9] = {
    {5, 3, 4, 6, 7, 8, 9, 1, 2}, {6, 7, 2, 1, 9, 0, 3, 4, 8},
    {1, 0, 0, 3, 4, 2, 5, 6, 0}, {8, 5, 9, 7, 6, 1, 0, 2, 0},
    {4, 2, 6, 8, 5, 3, 7, 9, 1}, {7, 1, 3, 9, 2, 4, 8, 5, 6},
    {9, 0, 1, 5, 3, 7, 2, 1, 4}, {2, 8, 7, 4, 1, 9, 6, 3, 5},
    {3, 0, 0, 4, 8, 1, 1, 7, 9}};

TEST_CASE("test sudoku") {
  CHECK(validSolution(example1) == true);
  CHECK(validSolution(example2) == false);
}