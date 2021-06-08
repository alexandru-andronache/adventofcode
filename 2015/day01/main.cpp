#include "file.h"
#include <iostream>
#include <vector>

namespace aoc2015_day01 {
    int part_1(std::string_view path) {
        std::string input = file::readFileAsString(path);
        int sol = 0;
        for (const auto& l : input) {
            sol += 1 * (l == '(') + (-1) * (l == ')');
        }
        return sol;
    }

    int part_2(std::string_view path, int basement = -1) {
        std::string input = file::readFileAsString(path);
        int currentFloor = 0;
        for (int i = 0; i < input.size(); ++i) {
            currentFloor += 1 * (input[i] == '(') + (-1) * (input[i] == ')');
            if (currentFloor == basement) {
                return i + 1;
            }
        }
        return 0;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day01::part_1("../2015/day01/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2015_day01::part_2("../2015/day01/input.in") << std::endl;

    return 0;
}
#endif
