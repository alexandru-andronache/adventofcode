#include "file.h"
#include <iostream>
#include <vector>

namespace aoc2018_day08 {
    void parseSol1(const std::vector<int>& numbers, int& index, int& sum) {
        int metadata = numbers[index + 1];
        int child = numbers[index];
        index += 2;
        for (int i = 0; i < child; ++i) {
            parseSol1(numbers, index, sum);
        }
        for (int i = index; i < index + metadata; ++i) {
            sum += numbers[i];
        }
        index += metadata;
    }

    int parseSol2(const std::vector<int>& numbers, int& index) {
        int metadata = numbers[index + 1];
        int nrChildren = numbers[index];
        std::vector<int> values;
        index += 2;
        for (int i = 0; i < nrChildren; ++i) {
            values.push_back(parseSol2(numbers, index));
        }
        int value = 0;
        if (nrChildren == 0) {
            for (int i = index; i < index + metadata; ++i) {
                value += numbers[i];
            }
        }
        else {
            for (int i = index; i < index + metadata; ++i) {
                if (numbers[i] - 1 < nrChildren) {
                    value += values[numbers[i] - 1];
                }
            }
        }
        index += metadata;
        return value;
    }

    int part_1(std::string_view path) {
        std::vector<int> numbers = file::readFileAsArrayInt(path);
        int i = 0;
        int sum = 0;
        parseSol1 (numbers, i, sum);
        return sum;
    }

    int part_2(std::string_view path) {
        std::vector<int> numbers = file::readFileAsArrayInt(path);

        int i = 0;
        return parseSol2(numbers, i);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day08::part_1("../2018/day08/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2018_day08::part_2("../2018/day08/input.in") << std::endl;

    return 0;
}
#endif
