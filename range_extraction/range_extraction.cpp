//
// Created by fulva on 10/29/2021.
//

#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

std::vector<int> find_diffs(const std::vector<int> &args) {
  std::vector<int> diffs;
  diffs.reserve(std::size(args));
  auto cur_iter = args.begin();
  auto end_iter = args.end();
  for (; cur_iter != end_iter && std::next(cur_iter) != end_iter; ++cur_iter) {
    diffs.emplace_back(*std::next(cur_iter) - *cur_iter);
  }
  return diffs;
}

std::string range_extraction(std::vector<int> args) {
  std::vector<int> diffs = find_diffs(args);
  diffs.emplace_back(-1);
  std::ostringstream output_stream;
  auto cur_iter = args.begin();
  auto end_iter = args.end();
  auto diff_iter = diffs.begin();
  for (; cur_iter != end_iter; ++cur_iter, ++diff_iter) {
    if(cur_iter != args.begin()){
      output_stream << ",";
    }
    output_stream << *cur_iter;
    if (*diff_iter == 1 && *std::next(diff_iter) == 1) {
      while (*diff_iter == 1) {
        ++cur_iter;
        ++diff_iter;
      }
      output_stream << "-" << *cur_iter;
    }
  }
  return output_stream.str();
}

TEST(RangeExtraction, basic_test) {
  EXPECT_EQ(find_diffs({1, 2, 3, 4, 5}), (std::vector<int>{1, 1, 1, 1}));
  EXPECT_EQ(range_extraction({-6,-3,-2,-1,0,1,3,4,5,7,8,9,10,11,14,15,17,18,19,20}), "-6,-3-1,3-5,7-11,14,15,17-20");
}