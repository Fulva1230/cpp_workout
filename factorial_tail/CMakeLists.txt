cmake_minimum_required(VERSION 3.18)

project(factorial_tail)
add_executable(${PROJECT_NAME} factorial_tail.cpp)

target_link_libraries(${PROJECT_NAME} gtest_main)