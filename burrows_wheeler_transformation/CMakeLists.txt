cmake_minimum_required(VERSION 3.18)

project(burrows_wheeler_transformation)


add_executable(${PROJECT_NAME} burrows_wheeler_transformation.cpp)
target_link_libraries(${PROJECT_NAME} gtest_main)

gtest_discover_tests(${PROJECT_NAME})