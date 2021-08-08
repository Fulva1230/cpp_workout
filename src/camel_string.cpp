//
// Created by fulva on 2021/8/7.
//

#include <string>
#include <sstream>

std::string to_camel_case(std::string text) {
    std::ostringstream outputStream;
    auto curIter = std::begin(text);
    auto endIter = std::end(text);
    for (; curIter != endIter; ++curIter) {
        if (*curIter == '_' || *curIter == '-')
            outputStream << static_cast<char>(std::toupper(*(++curIter)));
        else
            outputStream << *curIter;
    }
    return outputStream.str();
}
