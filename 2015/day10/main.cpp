#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>

namespace aoc2015_day10 {
    int solve(std::string input, int repetitions) {
        for (int i = 0; i < repetitions; ++i) {
            std::string result;
            int j = 0;
            while (j < input.size()) {
                int nr = 1;
                std::string letter = input.substr(j, 1);
                while (j + 1 < input.size() && input[j] == input[j + 1]) {
                    nr++;
                    j++;
                }
                j++;
                result += std::to_string(nr) + letter;
            }
            input = result;
        }
        return input.size();
    }

    int part_1(const std::string& input) {
        return solve(input, 40);
    }

    int part_2(const std::string& input) {
        return solve(input, 50);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day10::part_1("3113322113") << std::endl;
    std::cout << "Part 2: " << aoc2015_day10::part_2("3113322113") << std::endl;

    return 0;
}
#endif
