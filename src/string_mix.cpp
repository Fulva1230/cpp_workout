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
  bool operator()(const PreoutputEntryType &lhs,
                  const PreoutputEntryType &rhs) const {
    if (std::get<0>(lhs) == std::get<0>(rhs)) {
      if (std::get<2>(lhs) == std::get<2>(rhs)) {
        return std::get<1>(lhs) < std::get<1>(rhs);
      } else {
        return std::get<2>(lhs) < std::get<2>(rhs);
      }
    } else {
      return std::get<0>(lhs) > std::get<0>(rhs);
    }
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

void populateMixOrderedCounter(
    CharCounterType &charCounter1, CharCounterType &charCounter2,
    CharCounterType &mixCounter,
    std::vector<PreoutputEntryType> &mixOrderedCounter) {
  for (auto entry : mixCounter) {
    int s1has = charCounter1[entry.first];
    int s2has = charCounter2[entry.first];
    if (entry.second > 1) {
      if (s1has > s2has) {
        mixOrderedCounter.emplace_back(s1has, entry.first, Owner::first);
      } else if (s1has < s2has) {
        mixOrderedCounter.emplace_back(s2has, entry.first, Owner::second);
      } else {
        mixOrderedCounter.emplace_back(entry.second, entry.first, Owner::both);
      }
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
    std::vector<PreoutputEntryType> mixOrderedCounter{};
    populateMixOrderedCounter(charCounter1, charCounter2, mixCounter,
                              mixOrderedCounter);

    std::sort(std::begin(mixOrderedCounter), std::end(mixOrderedCounter),
              EntryCompare{});
    //    remove entry with count 1
    std::ostringstream output{};
    {
      bool firstRunFlag = true;
      for (auto entry : mixOrderedCounter) {
        if (firstRunFlag) {
          firstRunFlag = false;
        } else {
          output << '/';
        }
        switch (std::get<2>(entry)) {
        case Owner::first:
          output << "1:";
          break;
        case Owner::second:
          output << "2:";
          break;
        case Owner::both:
          output << "=:";
          break;
        }
        output << std::string(std::get<0>(entry), std::get<1>(entry));
      }
    }
    return output.str();
  };
};

TEST_CASE("test_string_mix") {
  REQUIRE(std::isblank(' ', std::locale()) == true);

  EntryCompare compare{};
  REQUIRE(compare({3, '3', Owner::both}, {3, '5', Owner::both}) == true);

  REQUIRE(Mix::mix("Are they here", "yes, they are here") ==
          "2:eeeee/2:yy/=:hh/=:rr");
}