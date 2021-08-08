//
// Created by fulva on 2021/8/8.
//

#include <algorithm>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <iostream>

std::vector<std::string> permutations(std::string s) {
  std::vector<std::string> res{};
  std::sort(std::begin(s), std::end(s));
  res.push_back(s);
  while (std::next_permutation(std::begin(s), std::end(s)))
    res.push_back(s);
  // Your code here
  return res;
}

TEST_CASE("permutation") {
  std::string x{"aabb"};
  std::cout << std::size(permutations(x));
}
