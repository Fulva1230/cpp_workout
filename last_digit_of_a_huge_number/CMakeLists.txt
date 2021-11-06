cmake_minimum_required(VERSION 3.18)

project(last_digit_of_a_huge_number)

add_executable(${PROJECT_NAME} last_digit_of_a_huge_number.cpp)
target_link_libraries(${PROJECT_NAME} gtest_main)