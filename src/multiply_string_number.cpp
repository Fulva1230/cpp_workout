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
    char buf[2]{};
    std::for_each(std::rbegin(init), std::rend(init),
                  [&buf, this](const char e) {
                    buf[0] = e;
                    internalNumbers.push_back(std::atoi(buf));
                  });
  }

  BigInt() = default;

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
    auto outputIter = std::begin(output.internalNumbers);
    auto outputEndIter = std::cend(output.internalNumbers);
    for (; std::next(outputIter) != outputEndIter; ++outputIter) {
      *std::next(outputIter) += *outputIter / 10;
      *outputIter = *outputIter % 10;
    }
    return output;
  }

  explicit operator string() {
    std::ostringstream output{};
    std::for_each(std::crbegin(internalNumbers), std::crend(internalNumbers),
                  [&output](int digit) { output << digit; });
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
  void procCarry() const {};
  ContainerType internalNumbers{};
};

string multiply(string a, string b) {
  // Your code here
  BigInt ai{a};
  BigInt bi{b};
  return static_cast<string>(ai * bi);
}

TEST_CASE("test multiply string") {
  BigInt a("50");
  BigInt b("3");
  REQUIRE(static_cast<string>(a * b) == "150");

  BigInt c("234232");
  BigInt d("2123134");
  REQUIRE(static_cast<string>(c * d) == "497305923088");
}
