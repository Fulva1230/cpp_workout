cmake_minimum_required(VERSION 3.18)

project(become_immortal)

add_executable(${PROJECT_NAME} become_immortal.cpp)
target_link_libraries(${PROJECT_NAME} gtest_main)