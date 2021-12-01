#include "file.h"
#include <iostream>
#include <vector>

namespace aoc2021_day01 {
    int part_1(std::string_view path) {
        std::vector<int> input = file::readFileAsArrayInt(path);

        int sol = 0;
        for (int i = 1; i < input.size(); ++i) {
            sol += (input[i] > input[i - 1]);
        }

        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<int> input = file::readFileAsArrayInt(path);

        int sol = 0;
        for (int i = 1; i < input.size() - 2; ++i) {
            sol += (input[i] + input[i + 1] + input[i + 2] > input[i - 1] + input[i] + input[i + 1]);
        }

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day01::part_1("../2021/day01/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day01::part_2("../2021/day01/input.in") << std::endl;

    return 0;
}
#endif
