//
// Created by fulva on 2021/8/6.
//

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int solution(string roman) {
    int sum{0};
    std::unordered_map<std::string, int> romanPairs{
            {"IV", 4},
            {"IX", 9},
            {"XL", 40},
            {"XC", 90},
            {"CD", 400},
            {"CM", 900},
    };
    std::unordered_map<char, int> romanSingle{
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000},
    };
    auto curIter{std::begin(roman)};
    auto curNextIter{std::next(curIter)};
    auto endIter{std::end(roman)};
    for (; curIter != endIter; ++curIter, ++curNextIter) {
        if (curNextIter != endIter) {
            std::string followingTwo{*curIter, *curNextIter};
            auto tryFoundIter = romanPairs.find(followingTwo);
            if (tryFoundIter != std::end(romanPairs)) {
                sum += tryFoundIter->second;
                ++curIter;
                ++curNextIter;
            } else {
                sum += romanSingle[*curIter];
            }
        } else {
            sum += romanSingle[*curIter];
        }
    }
    return sum;
}