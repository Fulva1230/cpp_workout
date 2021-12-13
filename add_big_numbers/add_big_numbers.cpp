//
// Created by fulva on 12/13/2021.
//

#include <algorithm>
#include <string>

#include "gtest/gtest.h"

std::string add(const std::string &a, const std::string &b) {
  std::cout << "a is " << a << " and b is " << b << std::endl;
  if (a.empty()) {
    return b;
  }
  if (b.empty()) {
    return a;
  }
  std::string aCopy = a;
  std::string bCopy = b;
  auto size = std::max(a.size(), b.size());
  if (aCopy.size() < size) {
    aCopy.insert(0, size - aCopy.size(), '0');
  }
  if (bCopy.size() < size) {
    bCopy.insert(0, size - bCopy.size(), '0');
  }
  std::vector<int> sums{};
  int i = size - 9;
  for (; i > 0; i -= 9) {
    auto sum = std::stoi(aCopy.substr(i, 9)) + std::stoi(bCopy.substr(i, 9));
    sums.push_back(sum);
  }
  auto sum =
      std::stoi(aCopy.substr(0, i + 9)) + std::stoi(bCopy.substr(0, i + 9));
  sums.push_back(sum);

  for (auto iter = sums.begin();
       iter != sums.end() && std::next(iter) != sums.end(); ++iter) {
    *std::next(iter) += *iter / 1000000000;
    *iter = *iter % 1000000000;
  }

  std::ostringstream output{};
  for (auto iter = sums.rbegin(); iter != sums.rend(); ++iter) {
    if (iter != sums.rbegin()) {
      auto output_str = std::to_string(*iter);
      output_str.insert(0, 9 - output_str.size(), '0');
      output << output_str;
    } else {
      output << *iter;
    }
  }
  return output.str();
}

TEST(String, Reverse) {
  std::string x{"12345"};
  std::reverse(x.begin(), x.end());
  ASSERT_EQ(x, "54321");
}

TEST(Sum, Basic) {
  //  ASSERT_EQ(add("10", "35679"), "35689");
  //  ASSERT_EQ(add("197420730927359237509273509", "190740917340917394710394"),
  //            "197611471844700154903983903");
  //  ASSERT_EQ(add("6924186904311505770552856588316092251990397794971153124267366273352653285398872602493873474579094567155491541814774",
  //                "56"),
  //            "6924186904311505770552856588316092251990397794971153124267366273352653285398872602493873474579094567155491541814830");
  ASSERT_EQ(add("28843251403738007183881604996567553651862003892469510062535602"
                "45814743596407704780804846428661289200304942380797276490429697"
                "4055290716355863369097642814",
                "77785928185300236579763991415078239978026314925389005630266372"
                "65574926785732"),
            "288432514037380071838816049965675536518620038924695100625356024581"
            "474359640848264008669943102708684021909316319705675357895129558537"
            "42993128944024428546");
}