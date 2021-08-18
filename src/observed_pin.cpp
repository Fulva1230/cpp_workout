//
// Created by b1050 on 8/18/2021.
//

#include <algorithm>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <catch2/catch_test_macros.hpp>

std::unordered_map<char, std::string> associate_keys{
    {'1', "124"},  {'2', "1235"}, {'3', "236"},   {'4', "1457"}, {'5', "24568"},
    {'6', "3569"}, {'7', "478"},  {'8', "57890"}, {'9', "689"},  {'0', "80"}};

void inserter(std::vector<char> preceding, std::vector<std::string> remaining,
              std::vector<std::string> &container) {
  if (remaining.empty()) {
    std::string output{std::begin(preceding), std::end(preceding)};
    container.push_back(output);
  } else {
    auto next = remaining[std::size(remaining) - 1];
    remaining.pop_back();
    for (auto e : next) {
      preceding.push_back(e);
      inserter(preceding, remaining, container);
      preceding.pop_back();
    }
  }
}

std::vector<std::string> get_pins(std::string observed) {
  std::vector<std::string> output{};
  std::vector<std::string> remaining{};
  std::vector<char> preceding{};
  for (char e : observed) {
    remaining.push_back(associate_keys[e]);
  }
  std::reverse(std::begin(remaining), std::end(remaining));
  inserter(preceding, remaining, output);
  return output;
}

TEST_CASE("test istringstream") {
  std::istringstream stream{"  aaa bbb ccc"};
  std::string buf{};
  stream >> buf;
  CHECK(buf == "aaa");
  stream >> buf;
  CHECK(buf == "bbb");
  CHECK(stream.eof() != true);
  stream >> buf;
  CHECK(buf == "ccc");
  CHECK(stream.eof());

  std::ostringstream ss{};
  ss << '3';
  ss << '4';
  CHECK(ss.str() == "34");

  auto ret = get_pins("11");
  ret.size();
}