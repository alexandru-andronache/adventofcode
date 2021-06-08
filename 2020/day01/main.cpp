#include "file.h"
#include <iostream>
#include <vector>

namespace aoc2020_day01 {
    int part_1(std::string_view path, int total_sum = 2020) {
        std::vector<int> input = file::readFileAsArrayInt(path);
        std::sort(input.begin(), input.end());
        for (int i = 0; i < input.size(); ++i) {
            if (std::binary_search(input.begin() + i + 1, input.end(), total_sum - input[i])) {
                return input[i] * (total_sum - input[i]);
            }
        }
        return 0;
    }

    int part_2(std::string_view path, int total_sum = 2020) {
        std::vector<int> input = file::readFileAsArrayInt(path);
        std::sort(input.begin(), input.end());
        for (int i = 0; i < input.size(); ++i) {
            for (int j = i + 1; j < input.size(); ++j) {
                if (std::binary_search(input.begin() + j + 1, input.end(), total_sum - input[i] - input[j])) {
                    return (total_sum - input[i] - input[j]) * input[i] * input[j];
                }
            }
        }
        return 0;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day01::part_1("../2020/day01/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day01::part_2("../2020/day01/input.in") << std::endl;

    return 0;
}
#endif
