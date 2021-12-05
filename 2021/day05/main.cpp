#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>

namespace aoc2021_day05 {
    const int N = 1000;

    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::vector<std::vector<int>> map(N, std::vector<int>(N, 0));

        for (const auto& line : input) {
            std::vector<int> tokens = utils::splitStringToInt(line, " ,->");
            if (tokens[0] == tokens[2]) {
                for (int i = std::min(tokens[1], tokens[3]); i <= std::max(tokens[1], tokens[3]); ++i) {
                    map[tokens[0]][i]++;
                }
            }
            else if (tokens[1] == tokens[3]) {
                for (int i = std::min(tokens[0], tokens[2]); i <= std::max(tokens[0], tokens[2]); ++i) {
                    map[i][tokens[1]]++;
                }
            }
        }
        int sol = 0;
        for (const auto& line : map) {
            sol += std::count_if(line.begin(), line.end(), [](const auto& x) {
                return x > 1;
            });
        }
        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::vector<std::vector<int>> map(N, std::vector<int>(N, 0));

        for (const auto& line : input) {
            std::vector<int> tokens = utils::splitStringToInt(line, " ,->");
            if (tokens[0] == tokens[2]) {
                for (int i = std::min(tokens[1], tokens[3]); i <= std::max(tokens[1], tokens[3]); ++i) {
                    map[tokens[0]][i]++;
                }
            }
            else if (tokens[1] == tokens[3]) {
                for (int i = std::min(tokens[0], tokens[2]); i <= std::max(tokens[0], tokens[2]); ++i) {
                    map[i][tokens[1]]++;
                }
            }
            else {
                if (tokens[0] > tokens[2]) {
                    std::swap(tokens[0], tokens[2]);
                    std::swap(tokens[1], tokens[3]);
                }
                for (int i = tokens[0], j = 0; i <= tokens[2]; ++i, ++j) {
                    if (tokens[1] < tokens[3]) {
                        map[i][tokens[1] + j]++;
                    }
                    else {
                        map[i][tokens[1] - j]++;
                    }
                }
            }
        }
        int sol = 0;
        for (const auto& line : map) {
            sol += std::count_if(line.begin(), line.end(), [](const auto& x) {
                return x > 1;
            });
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day05::part_1("../2021/day05/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day05::part_2("../2021/day05/input.in") << std::endl;

    return 0;
}
#endif
