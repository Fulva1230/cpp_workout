cmake_minimum_required(VERSION 3.20)
project(cpp_workout CXX)

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

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

add_subdirectory(break_the_pieces)
add_subdirectory(drafting)
add_subdirectory(magic_compare)
add_subdirectory(burrows_wheeler_transformation)
add_subdirectory(range_extraction)
add_subdirectory(factorial_tail)
add_subdirectory(path_finder)
add_subdirectory(matrix_determinant)
add_subdirectory(sum_of_intervals)
add_subdirectory(become_immortal)

add_executable(cpp_workout src/stray_number.cpp src/roman_decoder.cpp src/two_sum.cpp src/camel_string.cpp src/score_a_dice.cpp src/pascal_triangle.cpp src/max_sum.cpp src/scarmblies_string.cpp src/best_travel.cpp src/premutation_string.cpp src/parse_int.cpp src/multiply_string_number.cpp src/string_mix.cpp src/twice_linear.cpp src/explorsive_sum.cpp src/observed_pin.cpp src/multiplication_of_three.cpp src/sudoku_validator.cpp src/pi_comp.cpp)
target_include_directories(cpp_workout PUBLIC include)
target_link_libraries(cpp_workout Catch2::Catch2WithMain)