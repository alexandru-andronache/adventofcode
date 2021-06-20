#include "file.h"
#include <iostream>
#include <vector>

namespace aoc2017_day01 {
    int part_1(std::string_view path) {
        std::string input = file::readFileAsString(path);

        char prev = input.back();
        int sol = 0;
        for (const auto& c : input) {
            if (c == prev) {
                sol += c - '0';
            }
            prev = c;
        }
        return sol;
    }

    int part_2(std::string_view path) {
        std::string input = file::readFileAsString(path);

        int sol = 0;
        int extra = input.size() / 2;
        int i = 0;
        for (const auto& c : input) {
            if (c == input[(extra + i) % input.size()]) {
                sol += c - '0';
            }
            i++;
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day01::part_1("../2017/day01/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day01::part_2("../2017/day01/input.in") << std::endl;

    return 0;
}
#endif
