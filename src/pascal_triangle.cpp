//
// Created by fulva on 2021/8/7.
//

#include <vector>
#include <array>
#include <iostream>

#include <catch2/catch_test_macros.hpp>

std::vector<long long> pascalsTriangle(int n) {
    std::vector<std::vector<long long>> triangle{static_cast<unsigned int>(n), std::vector<long long>(static_cast<unsigned int>(n), 0)};
    std::vector<long long> outputFlatten{};
    outputFlatten.reserve(n * n / 2 + n);
    for (int row = 0; row != n; ++row) {
        for (int col = 0; col != row + 1; ++col) {
            if (col == 0 || col == row) {
                std::cout << "row: " << row << " col: " << col << std::endl;
                triangle[row][col] = 1;
            } else {
                std::cout << "row: " << row << " col: " << col << std::endl;
                triangle[row][col] = triangle[row - 1][col - 1] + triangle[row - 1][col];
            }
            outputFlatten.push_back(triangle[row][col]);
        }
    }
    return outputFlatten;
}

TEST_CASE("test numerical conversion") {
    int n = 4;
    std::vector<std::vector<long long>> triangle{static_cast<unsigned int>(n), std::vector<long long>(static_cast<unsigned int>(n), 0)};
    triangle[3][3]= 1;

    pascalsTriangle(n);
}

