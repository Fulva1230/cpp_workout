//
// Created by b1050 on 8/10/2021.
//

#include <algorithm>
#include <locale>
#include <sstream>
#include <string>
#include <unordered_map>

#include <catch2/catch_test_macros.hpp>

enum class Owner { first, second, both };

using CharCounterType = std::unordered_map<char, int>;
using EntryType = std::pair<char, int>;
using PreoutputEntryType = std::tuple<int, char, Owner>;

class EntryCompare {
public:
  bool operator()(const EntryType &lhs, const EntryType &rhs) const {
    if (lhs.second > rhs.second) {
      return true;
    } else if (lhs.second == rhs.second) {
      if (lhs.first < rhs.first) {
        return true;
      }
    }
    return false;
  }
};

void generateCharCount(const std::string &str, CharCounterType &counter) {
  for (auto c : str) {
    if (!std::isblank(c, std::locale()) && std::islower(c, std::locale())) {
      counter[c] += 1;
    }
  }
}

void addIfGreater(CharCounterType &filled, const CharCounterType &refer) {
  for (auto entry : refer) {
    if (filled[entry.first] < entry.second) {
      filled[entry.first] = entry.second;
    }
  }
}

class Mix {
public:
  static std::string mix(const std::string &s1, const std::string &s2) {
    CharCounterType charCounter1{};
    CharCounterType charCounter2{};
    generateCharCount(s1, charCounter1);
    generateCharCount(s2, charCounter2);
    CharCounterType mixCounter{};
    addIfGreater(mixCounter, charCounter1);
    addIfGreater(mixCounter, charCounter2);
    std::vector<std::pair<char, int>> mixOrderedCounter{std::cbegin(mixCounter),
                                                        std::cend(mixCounter)};
    std::sort(std::begin(mixOrderedCounter), std::end(mixOrderedCounter),
              EntryCompare{});
    //    remove entry with count 1
    auto newEnd = std::remove_if(
        std::begin(mixOrderedCounter), std::end(mixOrderedCounter),
        [](const EntryType &element) { return element.second <= 1; });
    mixOrderedCounter.erase(newEnd, std::end(mixOrderedCounter));
    std::ostringstream output{};
    {
      bool firstRunFlag = true;
      for (auto entry : mixOrderedCounter) {
        if (firstRunFlag) {
          firstRunFlag = false;
        } else {
          output << '/';
        }
        int s1has = charCounter1[entry.first];
        int s2has = charCounter2[entry.first];
        if (s1has > s2has) {
          output << "1:";
        } else if (s1has < s2has) {
          output << "2:";
        } else {
          output << "=:";
        }
        output << std::string(entry.second, entry.first);
      }
    }
    return output.str();
  };
};

TEST_CASE("test_string_mix") {
  REQUIRE(std::isblank(' ', std::locale()) == true);

  EntryCompare compare{};
  REQUIRE(compare({'1', 3}, {'2', 5}) == false);
  REQUIRE(compare({'a', 5}, {'d', 5}) == true);
  REQUIRE(compare({'d', 6}, {'d', 5}) == true);
  REQUIRE(compare({'b', 3}, {'b', 3}) == false);

  REQUIRE(Mix::mix("Are they here", "yes, they are here") ==
          "2:eeeee/2:yy/=:hh/=:rr");
}