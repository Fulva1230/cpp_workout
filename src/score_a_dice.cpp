//
// Created by fulva on 2021/8/7.
//

#include <vector>
#include <unordered_map>

int score(const std::vector<int> &dice) {
    int score_sum = 0;
    std::unordered_map<int, int> point_counter{};
    for (auto aThrow : dice) {
        point_counter[aThrow] += 1;
    }
    if (point_counter[1] >= 3) {
        score_sum += 1000;
        score_sum += (point_counter[1] - 3) * 100;
    } else {
        score_sum += point_counter[1] * 100;
    }
    if (point_counter[5] >= 3) {
        score_sum += 500;
        score_sum += (point_counter[5] - 3) * 50;
    } else {
        score_sum += point_counter[5] * 50;
    }
    for (auto point : {2, 3, 4, 6}) {
        if (point_counter[point] >= 3) {
            score_sum += point * 100;
        }
    }
    return score_sum;
}
