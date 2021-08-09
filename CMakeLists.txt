cmake_minimum_required(VERSION 3.20)
project(cpp_workout)

set(CMAKE_CXX_STANDARD 17)

Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.0.0-preview3
)
FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

add_executable(cpp_workout src/stray_number.cpp src/roman_decoder.cpp src/two_sum.cpp src/camel_string.cpp src/score_a_dice.cpp src/pascal_triangle.cpp src/max_sum.cpp src/scarmblies_string.cpp src/best_travel.cpp src/premutation_string.cpp src/parse_int.cpp src/multiply_string_number.cpp)
target_include_directories(cpp_workout PUBLIC include)
target_link_libraries(cpp_workout Catch2::Catch2WithMain)
catch_discover_tests(cpp_workout)
