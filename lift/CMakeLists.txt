cmake_minimum_required(VERSION 3.18)

project(lift)

add_executable(${PROJECT_NAME} lift.cpp)
target_link_libraries(${PROJECT_NAME} gtest_main)