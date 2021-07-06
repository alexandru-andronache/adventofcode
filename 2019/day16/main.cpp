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
        std::array<int, 4> pattern{0, 1, 0, -1};

        for (int phase = 0; phase < phases; ++phase) {
            std::vector<long long> t(numbers.size(), 0);
            std::vector<long long> sums(numbers.size(), 0);
            sums[0] = numbers[0];
            for (int i = 1; i < numbers.size(); ++i) {
                sums[i] = numbers[i] + sums[i - 1];
            }

            for (int i = 0; i < numbers.size(); ++i) {
                int startPos = i - 1;
                int steps = i + 1;
                while (startPos < (int)numbers.size()) {
                    t[i] += sums[std::min(startPos + steps, (int)numbers.size() - 1)] - (startPos >= 0 ? sums[startPos] : 0);
                    startPos += 2 * steps;
                    if (startPos < (int)numbers.size()) {
                        t[i] -= sums[std::min(startPos + steps, (int) numbers.size() - 1)] -
                                (startPos >= 0 ? sums[startPos] : 0);
                        startPos += 2 * steps;
                    }
                }
                t[i] = t[i] % 10;
                if (t[i] < 0) {
                    t[i] = -t[i];
                }
            }
            numbers = t;
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

        std::vector<long long> newNumbers;
        for (int i = offset; i < numbers.size(); ++i) {
            newNumbers.push_back(numbers[i]);
        }
        offset = 0;

        for (int phase = 0; phase < phases; ++phase) {
            std::vector<long long> sums(newNumbers.size(), 0);
            sums[offset] = newNumbers[offset];
            for (int i = offset + 1; i < newNumbers.size(); ++i) {
                sums[i] = newNumbers[i] + sums[i - 1];
            }
            for (int i = offset; i < newNumbers.size(); ++i) {
                newNumbers[i] = sums.back() - sums[i - 1];
                newNumbers[i] = newNumbers[i] % 10;
                if (newNumbers[i] < 0) {
                    newNumbers[i] = -newNumbers[i];
                }
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
