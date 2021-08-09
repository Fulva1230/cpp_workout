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

class ParseIntUtil {
public:
  ParseIntUtil() { initializeBelowHundreds(); }

  int processSection(const std::string &str) {
    int number = 0;
    std::string curString{};
    std::istringstream inputStream{str};
    while (!inputStream.eof()) {
      inputStream >> curString;
      if (curString != "and") {
        auto optionalDigitIter = digits.find(curString);
        if (optionalDigitIter != std::end(digits)) {
          number += optionalDigitIter->second;
        } else {
          if (curString == "hundred") {
            number *= 100;
          } else {
            auto optionalBelowHundredIter = belowHundreds.find(curString);
            if (optionalBelowHundredIter != std::end(belowHundreds)) {
              number += optionalBelowHundredIter->second;
            }
          }
        }
      }
    }
    return number;
  }

  void initializeBelowHundreds() {
    std::unordered_map<std::string, int> tens{
        {"", 0},        {"twenty", 2}, {"thirty", 3},
        {"forty", 4},   {"fifty", 5},  {"sixty", 6},
        {"seventy", 7}, {"eighty", 8}, {"ninety", 9},
    };
    std::unordered_map<std::string, int> digits{
        {"", 0},     {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
        {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

    for (const auto &ten : tens) {
      for (const auto &digit : digits) {
        if (!ten.first.empty() && !digit.first.empty()) {
          belowHundreds[ten.first + "-" + digit.first] =
              ten.second * 10 + digit.second;
        } else {
          belowHundreds[ten.first + digit.first] =
              ten.second * 10 + digit.second;
        }
      }
    }
  }

private:
  std::unordered_map<std::string, int> digits{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  std::unordered_map<std::string, int> belowHundreds{
      {"ten", 10},      {"eleven", 11},   {"twelve", 12},  {"thirteen", 13},
      {"fourteen", 14}, {"fifteen", 15},  {"sixteen", 16}, {"seventeen", 17},
      {"eighteen", 18}, {"nineteen", 19},
  };
};

std::unordered_map<std::string, int> constructBelowHundreds() {
  std::unordered_map<std::string, int> res{
      {"ten", 10},      {"eleven", 11},   {"twelve", 12},  {"thirteen", 13},
      {"fourteen", 14}, {"fifteen", 15},  {"sixteen", 16}, {"seventeen", 17},
      {"eighteen", 18}, {"nineteen", 19},
  };
  std::unordered_map<std::string, int> tens{
      {"", 0},      {"twenty", 2},  {"thirty", 3}, {"forty", 4},  {"fifty", 5},
      {"sixty", 6}, {"seventy", 7}, {"eighty", 8}, {"ninety", 9},
  };
  std::unordered_map<std::string, int> digits{
      {"", 0},     {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
      {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  for (const auto &ten : tens) {
    for (const auto &digit : digits) {
      if (!ten.first.empty() && !digit.first.empty()) {
        res[ten.first + "-" + digit.first] = ten.second * 10 + digit.second;
      } else {
        res[ten.first + digit.first] = ten.second * 10 + digit.second;
      }
    }
  }
  return res;
}

int processSection(const std::string &str,
                   const std::unordered_map<std::string, int> &belowHundreds) {
  std::unordered_map<std::string, int> digits{
      {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
      {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  int number = 0;
  std::string curString{};
  std::istringstream inputStream{str};
  while (!inputStream.eof()) {
    inputStream >> curString;
    if (curString != "and") {
      auto optionalDigitIter = digits.find(curString);
      if (optionalDigitIter != std::end(digits)) {
        number += optionalDigitIter->second;
      } else {
        if (curString == "hundred") {
          number *= 100;
        } else {
          auto optionalBelowHundredIter = belowHundreds.find(curString);
          if (optionalBelowHundredIter != std::end(belowHundreds)) {
            number += optionalBelowHundredIter->second;
          }
        }
      }
    }
  }
  return number;
}

long parse_int(std::string number) {
  std::unordered_map<std::string, int> multipliers{
      {"thousand", 1000},
      {"million", 1000000},
  };
  std::unordered_map<std::string, int> belowHundreds = constructBelowHundreds();

  std::istringstream inputStream{number};
  std::vector<MultipliedNumber> finalNumbers{};
  std::string procStr{};
  std::ostringstream holdBuffer{};

  while (!inputStream.eof()) {
    inputStream >> procStr;
    auto multiplierIter = multipliers.find(procStr);
    if (multiplierIter != std::end(multipliers)) {
      finalNumbers.push_back({processSection(holdBuffer.str(), belowHundreds),
                              multiplierIter->second});
      holdBuffer.str("");
    } else {
      holdBuffer << " " << procStr;
    }
  }
  finalNumbers.push_back({processSection(holdBuffer.str(), belowHundreds), 1});
  int finalNumber{};
  for (const auto &ele : finalNumbers) {
    finalNumber += ele.number * ele.multiplier;
  }
  return finalNumber;
}
TEST_CASE("test_inputsteam") {
  REQUIRE(parse_int("one") == 1);
  REQUIRE(parse_int(
              "two hundred and forty-six thousand two hundred and forty-six") ==
          246246);
  REQUIRE(parse_int("twenty") == 20);
  REQUIRE(parse_int("one hundred and one") == 101);
}