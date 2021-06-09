#include "file.h"
#include <iostream>
#include <vector>

namespace aoc2015_day08 {
    unsigned int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        unsigned int totalLength = 0;
        unsigned int stringLength = 0;
        for (const auto& line : input) {
            totalLength += line.size();
            for (int i = 1; i < line.size() - 1; ++i) {
                if (line[i] == '\\') {
                    if (line[i + 1] == 'x') {
                        i = i + 3;
                    }
                    else {
                        i = i + 1;
                    }
                }
                stringLength++;
            }
        }
        return totalLength - stringLength;
    }

    unsigned int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        unsigned int totalLength = 0;
        unsigned int stringLength = 0;

        for (const auto& line : input) {
            totalLength += line.size();
            for (const auto& c : line) {
                stringLength += ((c == '"') || (c == '\\')) + 1;
            }
            stringLength += 2;
        }

        return stringLength - totalLength;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day08::part_1("../2015/day08/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2015_day08::part_2("../2015/day08/input.in") << std::endl;

    return 0;
}
#endif
