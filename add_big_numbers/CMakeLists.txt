cmake_minimum_required(VERSION 3.18)

project(add_big_numbers)

add_executable(${PROJECT_NAME} add_big_numbers.cpp)
target_link_libraries(${PROJECT_NAME} gtest_main)