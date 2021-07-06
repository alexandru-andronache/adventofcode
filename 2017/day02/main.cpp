#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>

namespace aoc2017_day02 {
    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::vector<int>> input;
        for (const auto& line : lines) {
            input.push_back(utils::splitStringToInt(line, " \t"));
        }

        int sol = 0;
        for (const auto& line : input) {
            int min = *std::min_element(line.begin(), line.end());
            int max = *std::max_element(line.begin(), line.end());
            sol += max - min;
        }
        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::vector<int>> input;
        for (const auto& line : lines) {
            input.push_back(utils::splitStringToInt(line, " \t"));
        }

        int sol = 0;
        for (const auto& line : input) {
            for (int i = 0; i < line.size(); ++i) {
                for (int j = i + 1; j < line.size(); ++j) {
                    if (line[i] % line[j] == 0 || line[j] % line[i] == 0) {
                        sol += line[i] / line[j] + line[j] / line[i];
                    }
                }
            }
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day02::part_1("../2017/day02/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day02::part_2("../2017/day02/input.in") << std::endl;

    return 0;
}
#endif
