cmake_minimum_required(VERSION 3.18)

project(range_extraction)

add_executable(${PROJECT_NAME} range_extraction.cpp)
target_link_libraries(${PROJECT_NAME} gtest_main)