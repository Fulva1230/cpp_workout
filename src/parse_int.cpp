//
// Created by fulva on 2021/8/8.
//

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include <catch2/catch_test_macros.hpp>

struct MultipliedNumber {
  int number;
  int multiplier;
};

std::unordered_map<std::string, int> constructBelowHundreds() {
  std::unordered_map<std::string, int> res{
      {"ten", 10},      {"eleven", 11},   {"twelve", 12},  {"thirteen", 13},
      {"fourteen", 14}, {"fifteen", 15},  {"sixteen", 16}, {"seventeen", 17},
      {"eighteen", 18}, {"nineteen", 19},
  };
  std::unordered_map<std::string, int> tens{
      {"", 0},         {"twenty-", 2}, {"thirsty-", 3},
      {"forty-", 4},   {"fifty-", 5},  {"sixty-", 6},
      {"seventy-", 7}, {"eighty-", 8}, {"ninety-", 9},
  };
  std::unordered_map<std::string, int> digits{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  for (const auto &ten : tens) {
    for (const auto &digit : digits) {
      res[ten.first + digit.first] = ten.second * 10 + digit.second;
    }
  }
}

long parse_int(std::string number) {
  std::unordered_map<std::string, int> multipliers{
      {"hundred", 100},
      {"thousand", 1000},
      {"million", 1000000},
  };
  std::unordered_map<std::string, int> multiplierPrefixes{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  std::unordered_map<std::string, int> belowHundreds = constructBelowHundreds();

  std::istringstream inputStream{number};
  std::vector<MultipliedNumber> finalNumbers{};
  std::string procStr{};
  MultipliedNumber mnumber{};

  while (inputStream.eof()) {
    inputStream >> procStr;
  }
  return 0;
}
TEST_CASE("test_inputsteam") {
  std::istringstream inputStream{"aaaa bbbb cccc"};
  std::string x{};
  inputStream >> x;
  std::cout << x << std::endl;
  std::cout << inputStream.eof() << std::endl;
  inputStream >> x;
  std::cout << x << std::endl;
  std::cout << inputStream.eof() << std::endl;
  inputStream >> x;
  std::cout << x << std::endl;
  std::cout << inputStream.eof() << std::endl;
  inputStream >> x;
  std::cout << inputStream.eof() << std::endl;
}