#include "file.h"
#include <iostream>
#include <vector>
#include <array>

namespace aoc2019_day16 {
    std::string part_1(std::string_view path, int phases = 100) {
        std::string input = file::readFileAsString(path);

        std::vector<long long> numbers;
        for (const auto& c : input) {
            numbers.push_back(c - '0');
        }

        for (int phase = 0; phase < phases; ++phase) {
            std::vector<long long> sums(numbers.size() + 1, 0);
            sums[0] = 0;
            for (int i = 0; i < numbers.size(); ++i) {
                sums[i + 1] += sums[i] + numbers[i];
            }

            int N = sums.size() - 1;

            for (int i = 0; i < numbers.size(); ++i) {
                int j = i;
                int steps = i + 1;
                numbers[i] = 0;
                while (j < numbers.size()) {
                    numbers[i] += sums[std::min(j + steps, N)] - sums[j];
                    j += steps * 2;
                    if (j < numbers.size()) {
                        numbers[i] -= sums[std::min(j + steps, N)] - sums[j];
                    }
                    j += steps * 2;
                }
                numbers[i] = numbers[i] % 10;
                if (numbers[i] < 0) {
                    numbers[i] = -numbers[i];
                }
            }
        }

        std::string sol;
        for (int i = 0; i < 8; ++i) {
            sol += std::to_string(numbers[i]);
        }
        return sol;
    }

    std::string part_2(std::string_view path, int phases = 100, int repeat = 10000) {
        std::string input = file::readFileAsString(path);

        std::vector<long long> numbers;
        for (int i = 0; i < repeat; ++i) {
            for (const auto &c : input) {
                numbers.push_back(c - '0');
            }
        }

        int offset = 0;
        for (int i = 0; i < 7; ++i) {
            offset = offset * 10 + numbers[i];
        }

        std::vector<long long> newNumbers = numbers;

        for (int phase = 0; phase < phases; ++phase) {
            for (int i = newNumbers.size() - 2; i >= offset; --i) {
                newNumbers[i] = (newNumbers[i] + newNumbers[i + 1]) % 10;
            }
        }

        std::string sol;
        for (int i = offset; i < offset + 8; ++i) {
            sol += std::to_string(newNumbers[i]);
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day16::part_1("../2019/day16/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day16::part_2("../2019/day16/input.in") << std::endl;

    return 0;
}
#endif
