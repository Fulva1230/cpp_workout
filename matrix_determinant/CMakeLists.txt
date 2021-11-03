cmake_minimum_required(VERSION 3.18)

project(matrix_determinant)

add_executable(${PROJECT_NAME} matrix_determinant.cpp)
target_link_libraries(${PROJECT_NAME} gtest_main)