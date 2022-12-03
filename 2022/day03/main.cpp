#include "file.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

namespace aoc2022_day03 {
    template<size_t SIZE>
    int compare(const std::vector<const std::array<int, SIZE>> items) {
        for (int i = 0; i < SIZE; ++i) {
            bool sol = true;
            for (const auto& item : items) {
                sol = sol && (item[i] > 0);
            }
            if (sol) {
                return i + 1;
            }
        }
        return 0;
    }
    template<size_t SIZE>
    void calculate(std::string_view str, std::array<int, SIZE>& items) {
        for (const auto& c : str) {
            if (c >= 'a' && c <= 'z') {
                items[c - 'a']++;
            }
            else {
                items['z' - 'a' + 1 + c - 'A']++;
            }
        }
    }
    int part_1(std::string_view path) {
        int sol = 0;

        std::vector<std::string> input = file::readFileAsArrayString(path);
        for (const auto& line : input) {
            std::array<int, 52> items1 {0};
            std::array<int, 52> items2 {0};
            calculate(line.substr(0, line.size() / 2), items1);
            calculate(line.substr(line.size() / 2), items2);
            sol += compare<52>({items1, items2});
        }

        return sol;
    }

    int part_2(std::string_view path) {
        int sol = 0;

        std::vector<std::string> input = file::readFileAsArrayString(path);
        for (int k = 0; k < input.size(); k += 3) {
            std::array<int, 52> items1 {0};
            std::array<int, 52> items2 {0};
            std::array<int, 52> items3 {0};
            calculate(input[k], items1);
            calculate(input[k + 1], items2);
            calculate(input[k + 2], items3);
            sol += compare<52>({items1, items2, items3});
        }

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day03::part_1("../2022/day03/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day03::part_2("../2022/day03/input.in") << std::endl;

    return 0;
}
#endif
