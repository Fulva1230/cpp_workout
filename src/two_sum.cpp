//
// Created by fulva on 2021/8/7.
//

#include <utility>
#include <vector>

std::pair<std::size_t, std::size_t> two_sum(const std::vector<int> &numbers, int target) {
    auto beginIter = std::begin(numbers);
    auto curIter = beginIter;
    auto endIter = std::end(numbers);
    for (; curIter != endIter; ++curIter) {
        auto advanIter = std::next(curIter);
        for (; advanIter != endIter; ++advanIter) {
            if (*advanIter + *curIter == target) {
                return {std::distance(beginIter, curIter), std::distance(beginIter, advanIter)};
            }
        }
    }
    return {0, 0};
}