#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2016_day18 {
    int solve(const std::string& input, int rows) {
        std::vector<std::vector<bool>> map(rows, std::vector<bool>(input.size(), false));
        for (int i = 0; i < input.size(); ++i) {
            if (input[i] == '.') {
                map[0][i] = true;
            }
        }

        for (int i = 0; i < rows - 1; ++i) {
            for (int j = 0; j < map[i].size(); ++j) {
                if (j > 0 && !map[i][j - 1] && !map[i][j] && ((j + 1 < map[i].size() && map[i][j + 1]) || j + 1 == map[i].size())) {
                    map[i + 1][j] = false;
                }
                else if (((j > 0 && map[i][j - 1]) || j == 0)  && !map[i][j] && (j + 1 < map[i].size()) && !map[i][j + 1]) {
                    map[i + 1][j] = false;
                }
                else if (j > 0 && !map[i][j - 1] && map[i][j] && (((j + 1 < map[i].size()) && map[i][j + 1]) || j + 1 == map[i].size())) {
                    map[i + 1][j] = false;
                }
                else if (((j > 0 && map[i][j - 1]) || (j == 0)) && map[i][j] && (j + 1 < map[i].size()) && !map[i][j + 1]) {
                    map[i + 1][j] = false;
                }
                else {
                    map[i + 1][j] = true;
                }
            }
        }

        int sol = 0;
        for (const auto& row : map) {
            for (const auto& el : row) {
                sol += el;
            }
        }
        return sol;
    }

    int part_1(std::string_view path, int rows) {
        return solve(file::readFileAsString(path), rows);
    }

    int part_2(std::string_view path, int rows) {
        return solve(file::readFileAsString(path), rows);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day18::part_1("../2016/day18/input.in", 40) << std::endl;
    std::cout << "Part 2: " << aoc2016_day18::part_2("../2016/day18/input.in", 400000) << std::endl;

    return 0;
}
#endif
