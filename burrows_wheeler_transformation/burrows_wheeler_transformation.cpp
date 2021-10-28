//
// Created by fulva on 10/24/2021.
//

#include <algorithm>
#include <deque>
#include <string>
#include <utility>

#include "gtest/gtest.h"

std::pair<std::string, int> encode(const std::string &s) {
  auto str_size = std::size(s);
  std::vector<std::string> to_sort_vec;
  to_sort_vec.reserve(std::size(s));
  for (int i = 0; i < std::size(s); ++i) {
    to_sort_vec.emplace_back(s.substr(i) + s.substr(0, i));
  }
  std::sort(to_sort_vec.begin(), to_sort_vec.end());
  std::string encoded_str = {};
  std::for_each(to_sort_vec.begin(), to_sort_vec.end(),
                [&](auto e) { encoded_str.push_back(e[str_size - 1]); });
  int original_index =
      std::distance(to_sort_vec.begin(),
                    std::find(to_sort_vec.begin(), to_sort_vec.end(), s));
  return {encoded_str, original_index};
}

std::string decode(const std::string &s, int n) {
  auto str_size = std::size(s);
  std::deque<std::pair<std::string, std::string>> table;
  auto sorted_str = s;
  std::sort(sorted_str.begin(), sorted_str.end());
  for (int i = 0; i < str_size; ++i) {
    table.emplace_back(std::string{s[i]}, std::string{sorted_str[i]});
  }
//  Try always pop front and find the immediate next fitting one
  while (std::size(table) > 1) {
    char cur_char = table[0].first[0];
    auto found_concat_iter =
        std::find_if(std::next(table.begin()), table.end(), [&](auto pair) {
          auto concat_condidate = pair.second;
          return concat_condidate[std::size(concat_condidate) - 1] == cur_char;
        });
    found_concat_iter->second = found_concat_iter->second + table[0].second;
    table.pop_front();
  }

  auto wrong_permutation = table[0].second;
  std::vector<std::string> to_sort_vec;
  to_sort_vec.reserve(str_size);
  for (int i = 0; i < std::size(wrong_permutation); ++i) {
    to_sort_vec.emplace_back(wrong_permutation.substr(i) + wrong_permutation.substr(0, i));
  }
  std::sort(to_sort_vec.begin(), to_sort_vec.end());
  return to_sort_vec[n];
}

TEST(burrows_wheeler_transformation, test_encode) {
  std::pair<std::string, int> res1{"nnbbraaaa", 4};
  EXPECT_EQ(encode("bananabar"), res1);
  std::pair<std::string, int> res2{"e emnllbduuHB", 2};
  EXPECT_EQ(encode("Humble Bundle"), res2);
  std::pair<std::string, int> res3{"ww MYeelllloo", 1};
  EXPECT_EQ(encode("Mellow Yellow"), res3);

//  EXPECT_EQ(decode("nnbbraaaa", 4), "bananabar");
//  EXPECT_EQ(decode("e emnllbduuHB", 2), "Humble Bundle");
  EXPECT_EQ(decode("ww MYeelllloo", 1), "Mellow Yellow");
}
