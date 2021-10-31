cmake_minimum_required(VERSION 3.18)

project(path_finder)

add_executable(${PROJECT_NAME}_reachable reachable.cpp)
target_link_libraries(${PROJECT_NAME}_reachable gtest_main)