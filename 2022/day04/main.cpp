#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <algorithm>

namespace aoc2022_day04 {
    int part_1(std::string_view path) {
        int sol = 0;
        std::vector<std::string> input = file::readFileAsArrayString(path);
        for (const auto& line : input) {
            std::vector<int> tokens = utils::splitStringToInt(line, " -,");
            if ((tokens[0] <= tokens[2] && tokens[3] <= tokens[1]) ||
                (tokens[2] <= tokens[0] && tokens[1] <= tokens[3])) {
                sol++;
            }
        }
        return sol;
    }

    int part_2(std::string_view path) {
        int sol = 0;
        std::vector<std::string> input = file::readFileAsArrayString(path);
        for (const auto& line : input) {
            std::vector<int> tokens = utils::splitStringToInt(line, " -,");
            if ((tokens[0] <= tokens[2] && tokens[2] <= tokens[1]) ||
                (tokens[0] <= tokens[3] && tokens[3] <= tokens[1]) ||
                (tokens[2] <= tokens[0] && tokens[0] <= tokens[3]) ||
                (tokens[2] <= tokens[1] && tokens[1] <= tokens[3])) {
                sol++;
            }
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day04::part_1("../2022/day04/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day04::part_2("../2022/day04/input.in") << std::endl;

    return 0;
}
#endif
