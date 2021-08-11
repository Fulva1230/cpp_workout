//
// Created by b1050 on 8/11/2021.
//

#include <algorithm>
#include <vector>

#include <catch2/catch_test_macros.hpp>

class DoubleLinear {
public:
  static int dblLinear(int n) {
    int sol = 0;
    std::vector<int> unfinished_min_heap{1};
    int previous{};
    for (int i = 0; i < n + 1; ++i) {
      std::pop_heap(std::begin(unfinished_min_heap),
                    std::end(unfinished_min_heap), std::greater());
      int cur_min = *std::prev(std::end(unfinished_min_heap));
      unfinished_min_heap.pop_back();
      if (cur_min != previous) {
        unfinished_min_heap.push_back(2 * cur_min + 1);
        std::push_heap(std::begin(unfinished_min_heap),
                       std::end(unfinished_min_heap), std::greater());
        unfinished_min_heap.push_back(3 * cur_min + 1);
        std::push_heap(std::begin(unfinished_min_heap),
                       std::end(unfinished_min_heap), std::greater());
      } else {
        --i;
      }
      previous = cur_min;
    }
    sol = previous;
    return sol;
  };
};

TEST_CASE("test_twice_linear") {
  CHECK(DoubleLinear::dblLinear(10) == 22);
  CHECK(DoubleLinear::dblLinear(20) == 57);
  CHECK(DoubleLinear::dblLinear(30) == 91);
}