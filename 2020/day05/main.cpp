#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <limits>

namespace aoc2020_day05 {
    std::pair<int, int> processSeat(const std::string_view seat) {
        int column = utils::decimalToInt(seat.substr(0, 7), 'B');
        int row = utils::decimalToInt(seat.substr((7, 3)), 'R');
        return {column, row};
    }

    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int max = std::numeric_limits<int>::min();
        for (const auto &line : input) {
            auto r = processSeat(line);
            max = std::max(max, r.first * 8 + r.second);
        }
        return max;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<bool>> matrix(128, std::vector<bool>(8, false));
        for (const auto &line : input) {
            auto r = processSeat(line);
            matrix[r.first][r.second] = true;
        }

        for (int i = 1; i < matrix.size() - 1; ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                bool valid = true;
                if (j > 0) {
                    valid = matrix[i - 1][j - 1] && matrix[i][j - 1] && matrix[i + 1][j - 1];
                }
                valid = valid && matrix[i - 1][j] && matrix[i + 1][j] && !matrix[i][j];
                if (j < 7) {
                    valid = valid && matrix[i - 1][j + 1] && matrix[i][j + 1] && matrix[i + 1][j + 1];
                }
                if (valid) {
                    return i * 8 + j;
                }
            }
        }
        return 0;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day05::part_1("../2020/day05/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day05::part_2("../2020/day05/input.in") << std::endl;

    return 0;
}
#endif
