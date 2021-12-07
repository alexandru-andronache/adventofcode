#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>

namespace aoc2021_day07 {
    int part_1(std::string_view path) {
        std::string input = file::readFileAsString(path);
        std::vector<int> numbers = utils::splitStringToInt(input, " ,");

        int min = std::numeric_limits<int>::max();
        for (int fuel = 1; fuel <= 1000; ++fuel) {
            int n = 0;
            for (const auto& f : numbers) {
                n += std::abs(f - fuel);
            }
            min = std::min(min, n);
        }
        return min;
    }

    unsigned long long sum(int n) {
        return n * (n + 1) / 2;
    }

    unsigned long long part_2(std::string_view path) {
        std::string input = file::readFileAsString(path);
        std::vector<int> numbers = utils::splitStringToInt(input, " ,");

        unsigned long long min = std::numeric_limits<unsigned long long>::max();
        for (int fuel = 1; fuel <= 1000; ++fuel) {
            unsigned long long n = 0;
            for (const auto& f : numbers) {
                n += sum(std::abs(f - fuel));
            }
            min = std::min(min, n);
        }
        return min;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day07::part_1("../2021/day07/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day07::part_2("../2021/day07/input.in") << std::endl;

    return 0;
}
#endif
