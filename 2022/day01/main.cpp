#include "file.h"
#include <iostream>
#include <vector>
#include <string>

namespace aoc2022_day01 {
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::vector<int> sums;
        int sum = 0;

        for (const auto& line : input) {
            if (line == "") {
                sums.push_back(sum);
                sum = 0;
            }
            else {
                sum += std::stoi(line);
            }
        }
        sums.push_back(sum);
        std::sort(sums.begin(), sums.end(), std::greater<int>{});

        return sums[0];
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::vector<int> sums;
        int sum = 0;

        for (const auto& line : input) {
            if (line == "") {
                sums.push_back(sum);
                sum = 0;
            }
            else {
                sum += std::stoi(line);
            }
        }
        sums.push_back(sum);
        std::sort(sums.begin(), sums.end(), std::greater<int>{});

        return sums[0] + sums[1] + sums[2];
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day01::part_1("../2022/day01/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day01::part_2("../2022/day01/input.in") << std::endl;

    return 0;
}
#endif
