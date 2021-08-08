//
// Created by fulva on 2021/8/6.
//

#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include <functional>

#include <catch2/catch_test_macros.hpp>

int stray(std::vector<int> numbers) {
    int theFirst = numbers[0];
    std::vector<int> minus{};
    minus.reserve(std::size(numbers));
    std::copy_if(numbers.begin(), numbers.end(), std::inserter(minus, minus.end()), [&](int e) {
        return e != theFirst;
    });
    return std::size(minus) == 1 ? minus[0] : theFirst;
};

using FooFunc = void (*)();

void foo() {
}

auto returnFun() {
    int x = 3;
    return [=]() {
        std::cout << x << std::endl;
    };
}

TEST_CASE("lambda") {
    auto x = returnFun();
    x();
}