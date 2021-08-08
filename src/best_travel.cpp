//
// Created by fulva on 2021/8/8.
//

#include <vector>
#include <algorithm>

class BestTravel {
public:
    static int chooseBestSum(int t, int k, std::vector<int> &ls) {
        std::vector<int> copy = ls;
        for (int i = 0; i < k - 1; ++i) {
            copy.push_back(0);
        }
        std::sort(std::begin(copy), std::end(copy));
        std::reverse(copy.begin(), copy.end());
        auto curIter = std::begin(ls);
        std::vector<decltype(curIter)> iterVector{};
        for (int i = 0; i != k; ++i, ++curIter) {
            iterVector.push_back(curIter);
        }
    }
};