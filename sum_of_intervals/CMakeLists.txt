cmake_minimum_required(VERSION 3.18)

project(sum_of_intervals)

add_executable(${PROJECT_NAME} sum_of_intervals.cpp)
target_link_libraries(${PROJECT_NAME} gtest_main)