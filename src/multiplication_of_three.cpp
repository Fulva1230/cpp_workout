//
// Created by fulva on 2021/8/21.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <string>

const std::string multiple_of_3_regex =
    "(0|1(00)*1|1(0(00)*)1((00)*1)*(0(00)*)1)*";

TEST_CASE("test regex") {
  Catch::Matchers::RegexMatcher regex_matcher{multiple_of_3_regex,
                                              Catch::CaseSensitive::Yes};
  CHECK(!regex_matcher.match("001"));
  CHECK(regex_matcher.match("110"));
  CHECK(regex_matcher.match("101111000110000101001110"));
}
