//
// Created by fulva on 11/3/2021.
//

#include "gtest/gtest.h"

#include <iostream>
#include <vector>

using namespace std;

vector<vector<long long>> get_minor(const vector<vector<long long>> &m, int row,
                                    int col) {
  vector<vector<long long>> minor{};
  for (int row_i = 0; row_i < std::size(m); ++row_i) {
    if (row_i != row) {
      vector<long long> row;
      for (int col_i = 0; col_i < std::size(m[row_i]); ++col_i) {
        if (col_i != col) {
          row.push_back(m[row_i][col_i]);
        }
      }
      minor.push_back(row);
    }
  }
  return minor;
}

long long determinant(vector<vector<long long>> m) {
  if (std::size(m) == 1 && std::size(m[0]) == 1) {
    return m[0][0];
  } else {
    long long determinant_accu = 0;
    for (int row_i = 0; row_i < std::size(m); ++row_i) {
      if (row_i % 2 == 0) {
        determinant_accu += m[row_i][0] * determinant(get_minor(m, row_i, 0));
      } else {
        determinant_accu -= m[row_i][0] * determinant(get_minor(m, row_i, 0));
      }
    }
    return determinant_accu;
  }
}

TEST(MatrixDeterminant, TestBasic){
  EXPECT_EQ(determinant(vector< vector<long long> > {
      vector<long long> {1, 3},
      vector<long long> {2, 5}
  }), -1);
}
