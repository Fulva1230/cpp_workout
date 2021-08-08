//
// Created by fulva on 2021/8/8.
//

#include <algorithm>
#include <vector>

#include <catch2/catch_test_macros.hpp>

class BestTravel {
public:
  template <class Iter>
  static int chooseBestSumRange(int t, int k, const Iter begin,
                                const Iter end) {
    int localmax = -1;
    if (k > 1) {
      for (auto curIter = begin; curIter != end; ++curIter) {
        if (t >= *curIter) {
          int res =
              chooseBestSumRange(t - *curIter, k - 1, std::next(curIter), end);
          if (res != -1) {
            int candidate = res + *curIter;
            if (candidate > localmax) {
              localmax = candidate;
            }
          }
        }
        if (localmax == t) {
          return t;
        }
      }
    } else if (k == 1) {
      for (auto curIter = begin; curIter != end; ++curIter) {
        int candidate = *curIter;
        if (candidate < t && candidate > localmax)
          localmax = candidate;
        if (candidate == t)
          return t;
      }
    }
    return localmax;
  }

  static int chooseBestSum(int t, int k, std::vector<int> &ls) {
    return chooseBestSumRange(t, k, std::begin(ls), std::end(ls));
  }
};

TEST_CASE("test_best_travel") {
  std::vector<int> x = {3, 3, 3, 5, 5, 5, 9};
  int t = 13;
  int k = 3;
  REQUIRE(BestTravel::chooseBestSum(t, k, x) == 13);
}