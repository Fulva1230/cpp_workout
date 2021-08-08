//
// Created by fulva on 2021/8/8.
//

#include <string>
#include <unordered_map>

using CharCountType = std::unordered_map<char, int>;

CharCountType charCountInit(const std::string &str) {
    std::unordered_map<char, int> charCount{};
    for (auto c : str) {
        charCount[c] += 1;
    }
    return charCount;
}

bool scramble(const std::string &s1, const std::string &s2) {
    CharCountType s1CharCount = charCountInit(s1);
    CharCountType s2CharCount = charCountInit(s2);
    for (auto e : s2CharCount) {
        if (s1CharCount[e.first] < e.second) {
            return false;
        }
    }
    return true;
}


