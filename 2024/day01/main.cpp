#include "file.h"
#include <iostream>
#include <vector>

namespace aoc2024_day01 {
    int part_1(std::string_view path) {
        int sol = 0;

        std::vector<int> numbers = file::readFileAsArrayInt(path);
        std::vector<int> numbers1;
        std::vector<int> numbers2;
        for (int i = 0; i < numbers.size(); i += 2) {
            numbers1.push_back(numbers[i]);
            numbers2.push_back(numbers[i + 1]);
        }

        std::ranges::sort(numbers1);
        std::ranges::sort(numbers2);

        for (int i = 0; i < numbers1.size(); ++i) {
            sol += std::abs(numbers1[i] - numbers2[i]);
        }

        return sol;
    }

    int part_2(std::string_view path) {
        int sol = 0;

        std::vector<int> numbers = file::readFileAsArrayInt(path);
        std::vector<int> numbers1;
        std::vector<int> numbers2;
        for (int i = 0; i < numbers.size(); i += 2) {
            numbers1.push_back(numbers[i]);
            numbers2.push_back(numbers[i + 1]);
        }

        for (int n : numbers1) {
            sol += n * std::ranges::count(numbers2, n);
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day01::part_1("../2024/day01/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day01::part_2("../2024/day01/input.in") << std::endl;

    return 0;
}
#endif
