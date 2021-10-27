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
  for (auto i = str_size - 1; i > n; --i) {
    char cur_char = table[i].first[0];
    auto found_concat_iter =
        std::find_if(std::next(table.rbegin()), table.rend(), [&](auto pair) {
          auto concat_condidate = pair.second;
          return concat_condidate[std::size(concat_condidate) - 1] == cur_char;
        });
    found_concat_iter->second = found_concat_iter->second + table[i].second;
    table.pop_back();
  }
  for (auto i = 0; i < n; ++i) {
    char cur_char = table[0].first[0];
    auto found_concat_iter =
        std::find_if(std::next(table.begin()), table.end(), [&](auto pair) {
          auto concat_condidate = pair.second;
          return concat_condidate[std::size(concat_condidate) - 1] == cur_char;
        });
    found_concat_iter->second = found_concat_iter->second + table[0].second;
    table.pop_front();
  }
  return table[0].second.substr(0, str_size);
}

TEST(burrows_wheeler_transformation, test_encode) {
  std::pair<std::string, int> res1{"nnbbraaaa", 4};
  EXPECT_EQ(encode("bananabar"), res1);
  std::pair<std::string, int> res2{"e emnllbduuHB", 2};
  EXPECT_EQ(encode("Humble Bundle"), res2);
  std::pair<std::string, int> res3{"ww MYeelllloo", 1};
  EXPECT_EQ(encode("Mellow Yellow"), res3);

//  EXPECT_EQ(decode("nnbbraaaa", 4), "bananabar");
  EXPECT_EQ(decode("e emnllbduuHB", 2), "Humble Bundle");
}
