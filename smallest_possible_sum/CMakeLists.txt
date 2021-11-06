cmake_minimum_required(VERSION 3.18)

project(smallest_possible_sum)

add_executable(${PROJECT_NAME} smallest_possible_sum.cpp)
target_link_libraries(${PROJECT_NAME} gtest_main)