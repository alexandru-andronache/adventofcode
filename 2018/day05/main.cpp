#include "file.h"
#include <iostream>

namespace aoc2018_day05 {
    std::string solvePolymer(const std::string& input, char polymer = '\0') {
        std::string result = "";
        int i = 0;
        while (i < input.size()) {
            if (result.size() > 0 && std::abs(result.back() - input[i]) == std::abs('A' - 'a')) {
                result.pop_back();
            }
            else {
                if (std::abs(input[i] - polymer) != std::abs('A' - 'a') && input[i] != polymer) {
                    result += input[i];
                }
            }
            i++;
        }
        return result;
    }

    int part_1(std::string_view path) {
        std::string input = file::readFileAsString(path);
        return solvePolymer(input).size();
    }

    int part_2(std::string_view path) {
        std::string input = file::readFileAsString(path);

        int min = input.size();
        for (int i = 'a'; i <= 'z'; ++i) {
            int l = solvePolymer(input, i).size();
            min = std::min(min, l);
        }
        return min;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day05::part_1("../2018/day05/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2018_day05::part_2("../2018/day05/input.in") << std::endl;

    return 0;
}
#endif
