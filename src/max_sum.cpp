//
// Created by fulva on 2021/8/8.
//

#include <vector>
#include <algorithm>
#include <list>
#include <numeric>

#include <catch2/catch_test_macros.hpp>
#include <iostream>

template<class T>
T searchForward(std::list<int> &contiList, T beginIter, T endIter) {
    std::vector<int> tempHold{};
    auto curIter = beginIter;
    int sum = 0;
    for (; curIter != endIter; ++curIter) {
        sum += *curIter;
        tempHold.push_back(*curIter);
        if (sum > 0) {
            contiList.insert(std::cend(contiList), std::cbegin(tempHold), std::cend(tempHold));
            return std::next(curIter);
        }
    }
    return curIter;
}

template<class Iter>
int searchFromCenter(const Iter &center, const Iter &begin, const Iter &end) {
    std::list<int> contiList{};
    contiList.push_back(*center);
    auto curForwardIter = std::next(center);
    while (curForwardIter != end) {
        curForwardIter = searchForward(contiList, curForwardIter, end);
    }
    auto curBackwardIter = std::reverse_iterator(
            center); // the reverse iterator will return the previous element of normal iterator
    auto reverseEnd = std::reverse_iterator(begin);
    while (curBackwardIter != reverseEnd) {
        curBackwardIter = searchForward(contiList, curBackwardIter, reverseEnd);
    }
    return std::accumulate(std::cbegin(contiList), std::cend(contiList), 0);
}

int maxSequence(const std::vector<int> &arr) {
    if (arr.empty()) {
        return 0;
    }
    if (*std::max_element(std::cbegin(arr), std::cend(arr)) < 0)
        return 0;
    std::vector<int> solCandidates{};
    for (auto curIter = std::begin(arr); curIter != std::cend(arr); ++curIter) {
        solCandidates.push_back(searchFromCenter(curIter, std::cbegin(arr), std::cend(arr)));
    }
    return *std::max_element(std::cbegin(solCandidates), std::cend(solCandidates));
}

TEST_CASE("test_max_sum") {
    REQUIRE(maxSequence({4, 1, 1, 4, 1, 1, -1, -1, 1, 1, 4, -1, 1, 2}) == 18);
}