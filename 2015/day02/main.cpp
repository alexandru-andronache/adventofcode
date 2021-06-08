#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2015_day02 {
    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        unsigned long long sol = 0;
        for (const auto& line : input) {
            std::vector<std::string> matches = utils::splitString(line, "x");
            int l = std::stoi(matches[0]);
            int h = std::stoi(matches[1]);
            int w = std::stoi(matches[2]);
            sol += 2 * l * h +  2 * l * w + 2 * h * w + std::min({l * w, h * w, l * h});
        }
        return sol;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        unsigned long long sol = 0;
        for (const auto& line : input) {
            std::vector<std::string> matches = utils::splitString(line, "x");
            int l = std::stoi(matches[0]);
            int h = std::stoi(matches[1]);
            int w = std::stoi(matches[2]);
            sol += l * h * w + std::min({2 * l + 2 * h, 2 * l + 2 * w, 2 * h + 2 * w});
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day02::part_1("../2015/day02/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2015_day02::part_2("../2015/day02/input.in") << std::endl;

    return 0;
}
#endif
