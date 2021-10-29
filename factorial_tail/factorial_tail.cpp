//
// Created by fulva on 10/29/2021.
//

#include <array>
#include <map>
#include <numeric>

#include <gtest/gtest.h>

std::array<int, 54> primes{
    2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,  37,  41,  43,
    47,  53,  59,  61,  67,  71,  73,  79,  83,  89,  97,  101, 103, 107,
    109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181,
    191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251};

void collect_primes(std::map<int, int> &factor_collector, int num) {
  auto prime_iter = primes.begin();
  while (num != 1) {
    if (num % *prime_iter == 0) {
      factor_collector[*prime_iter] += 1;
      num /= *prime_iter;
    } else {
      ++prime_iter;
    }
  }
}

// collect too many common factor so f overflows
int Zeroes(int base, int number) {
  std::map<int, int> factor_collector;
  for (int i = 1; i <= number; ++i) {
    int i_tmp = i;
    int gcd = std::gcd(base, i_tmp);
    while (gcd != 1) {
      i_tmp /= gcd;
      collect_primes(factor_collector, gcd);
      gcd = std::gcd(base, i_tmp);
    }
  }

  int z = 0;
  auto begin_iter = std::begin(factor_collector);
  while (begin_iter != std::end(factor_collector)) {
    int zero_checker = base;
    auto next_divisor = std::find_if(begin_iter, std::end(factor_collector),
                                     [&](std::pair<const int, int> &entry) {
                                       return zero_checker % entry.first == 0 &&
                                              entry.second > 0;
                                     });
    while (zero_checker != 1 && next_divisor != std::end(factor_collector)) {
      zero_checker /= next_divisor->first;
      next_divisor->second -= 1;
      if (zero_checker == 1) {
        ++z;
      } else {
        next_divisor = std::find_if(begin_iter, std::end(factor_collector),
                                    [&](std::pair<const int, int> &entry) {
                                      return zero_checker % entry.first == 0 &&
                                             entry.second > 0;
                                    });
      }
    }
    if (next_divisor == std::end(factor_collector)) {
      ++begin_iter;
    }
  }
  //  std::cout << "base:　" << base << " number: " << number << "return: " << z
  //  << std::endl;
  return z;
}

TEST(Factorial, TestBasic) {
  //  EXPECT_EQ(Zeroes(7, 50), 8);
  //  EXPECT_EQ(Zeroes(12, 26), 10);
  //  EXPECT_EQ(Zeroes(17, 100), 5);
  //  EXPECT_EQ(Zeroes(22, 3929), 391);
  EXPECT_EQ(Zeroes(192, 2305), 383);
}
