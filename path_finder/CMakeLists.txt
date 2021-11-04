cmake_minimum_required(VERSION 3.18)

project(path_finder)

add_executable(${PROJECT_NAME}_reachable reachable.cpp)
target_link_libraries(${PROJECT_NAME}_reachable gtest_main)

add_executable(${PROJECT_NAME}_minimal_step minimal_step.cpp)
target_link_libraries(${PROJECT_NAME}_minimal_step gtest_main)

add_executable(${PROJECT_NAME}_the_alpinist the_alpinist.cpp)
target_link_libraries(${PROJECT_NAME}_the_alpinist gtest_main)