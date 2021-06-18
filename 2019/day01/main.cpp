#include "file.h"
#include <iostream>
#include <vector>

namespace aoc2019_day01 {
    int getCost(int fuel) {
        return std::max((fuel / 3) - 2, 0);
    }

    int getTotalCost(int fuel) {
        int totalCost = 0;
        while (fuel > 0) {
            fuel = getCost(fuel);
            totalCost += fuel;
        }
        return totalCost;
    }

    int part_1(std::string_view path) {
        std::vector<int> input = file::readFileAsArrayInt(path);
        int sol = 0;
        for (const auto& it : input) {
            sol += getCost(it);
        }
        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<int> input = file::readFileAsArrayInt(path);
        int sol = 0;
        for (const auto& it : input) {
            sol += getTotalCost(it);
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day01::part_1("../2019/day01/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day01::part_2("../2019/day01/input.in") << std::endl;

    return 0;
}
#endif
