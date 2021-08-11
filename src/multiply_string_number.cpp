//
// Created by b1050 on 8/9/2021.
//

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

using namespace std;

class BigInt {
public:
  using ContainerType = vector<int>;
  explicit BigInt(const string &init) {
    char buf[3]{};
    auto curIter = std::rbegin(init);
    auto endIter = std::rend(init);
    for (; curIter != endIter; ++curIter) {
      buf[1] = *curIter;
      if (std::next(curIter) != endIter) {
        buf[0] = *(++curIter);
      } else {
        buf[0] = ' ';
      }
      internalNumbers.push_back(std::atoi(buf));
    }
  }

  BigInt() = default;

  BigInt operator+(const BigInt &another) const {
    auto thisIter = std::begin(internalNumbers);
    const auto thisEndIter = std::cend(internalNumbers);
    auto anotherIter = std::begin(another.internalNumbers);
    const auto anotherEndIter = std::cend(another.internalNumbers);
    BigInt output{};
    bool thisIterAvailable = thisIter != thisEndIter;
    bool anotherIterAvailable = anotherIter != anotherEndIter;
    while (thisIterAvailable || anotherIterAvailable) {
      int lhs = thisIterAvailable ? *(thisIter++) : 0;
      int rhs = anotherIterAvailable ? *(anotherIter++) : 0;
      output.internalNumbers.push_back(lhs + rhs);
      thisIterAvailable = thisIter != thisEndIter;
      anotherIterAvailable = anotherIter != anotherEndIter;
    }
    output.carry();
    return output;
  }

  BigInt operator*(const BigInt &another) const {
    auto thisIter = std::begin(internalNumbers);
    const auto thisEndIter = std::cend(internalNumbers);
    BigInt output{};
    output.internalNumbers.insert(
        std::cend(output.internalNumbers),
        size(internalNumbers) + size(another.internalNumbers), 0);
    for (int thisIndex = 1; thisIter != thisEndIter; ++thisIter, ++thisIndex) {
      auto anotherIter = std::begin(another.internalNumbers);
      const auto anotherEndIter = std::cend(another.internalNumbers);
      for (int anotherIndex = 1; anotherIter != anotherEndIter;
           ++anotherIter, ++anotherIndex) {
        output.internalNumbers[thisIndex + anotherIndex - 2] +=
            (*thisIter) * (*anotherIter);
      }
    }
    output.carry();
    return output;
  }

  explicit operator string() {
    std::ostringstream output{};
    std::for_each(std::crbegin(internalNumbers), std::crend(internalNumbers),
                  [&output](int digit) {
                    if (digit < 10) {
                      output << '0';
                    }
                    output << digit;
                  });
    std::string outputStr{output.str()};

    auto curIter = std::cbegin(outputStr);
    auto endIter = std::cend(outputStr);
    for (; curIter != std::prev(endIter) && *curIter == '0';) {
      ++curIter;
    }
    std::string modifiedOutputStr{curIter, endIter};
    return modifiedOutputStr;
  }

private:
  void carry() {
    auto curIter = std::begin(internalNumbers);
    auto endIter = std::cend(internalNumbers);
    if (curIter != endIter) {
      for (; std::next(curIter) != endIter; ++curIter) {
        *std::next(curIter) += *curIter / 100;
        *curIter = *curIter % 100;
      }
    }
  };

  void procCarry() const {};
  ContainerType internalNumbers{};
};

string multiply(string a, string b) {
  // Your code here
  BigInt ai{a};
  BigInt bi{b};
  return static_cast<string>(ai * bi);
}

std::string sum_strings(const std::string &a, const std::string &b) {
  BigInt ai{a};
  BigInt bi{b};
  return static_cast<string>(ai + bi);
}

TEST_CASE("test multiply string") {
  BigInt a("50");
  BigInt b("3");
  REQUIRE(static_cast<string>(a * b) == "150");

  BigInt e("99");
  BigInt f("300");
  REQUIRE(static_cast<string>(e * f) == "29700");

  BigInt c("234232");
  BigInt d("2123134");
  REQUIRE(static_cast<string>(c * d) == "497305923088");

  BigInt g("123121");
  BigInt h("0000234345554");
  REQUIRE(static_cast<string>(g + h) == "234468675");
}
