#include "file.h"
#include <iostream>
#include <utilities.h>

namespace aoc2024_day04 {
    unsigned long long part_1(std::string_view path) {
        std::vector<std::vector<char>> input = file::readFileAsMapChar(path);
        int sol = 0;

        // horizontal
        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[i].size() - 3; ++j) {
                if (input[i][j] == 'X' && input[i][j + 1] == 'M' && input[i][j + 2] == 'A' && input[i][j + 3] == 'S') {
                    sol++;
                }
            }
        }
        for (int i = 0; i < input.size(); ++i) {
            for (int j = input.size() - 1; j >= 3; --j) {
                if (input[i][j] == 'X' && input[i][j - 1] == 'M' && input[i][j - 2] == 'A' && input[i][j - 3] == 'S') {
                    sol++;
                }
            }
        }

        // vertical
        for (int j = 0; j < input[0].size(); ++j) {
            for (int i = 0; i < input.size() - 3; ++i) {
                if (input[i][j] == 'X' && input[i + 1][j] == 'M' && input[i + 2][j] == 'A' && input[i + 3][j] == 'S') {
                    sol++;
                }
            }
        }
        for (int j = 0; j < input[0].size(); ++j) {
            for (int i = input.size() - 1; i >= 3; --i) {
                if (input[i][j] == 'X' && input[i - 1][j] == 'M' && input[i - 2][j] == 'A' && input[i - 3][j] == 'S') {
                    sol++;
                }
            }
        }

        // diagonal
        for (int i = 0; i < input.size() - 3; ++i) {
            for (int j = 0; j < input[0].size() - 3; ++j) {
                if (input[i][j] == 'X' && input[i + 1][j + 1] == 'M' && input[i + 2][j + 2] == 'A' && input[i + 3][j + 3] == 'S') {
                    sol++;
                }
            }
        }

        for (int i = 0; i < input.size() - 3; ++i) {
            for (int j = 3; j < input[0].size(); ++j) {
                if (input[i][j] == 'X' && input[i + 1][j - 1] == 'M' && input[i + 2][j - 2] == 'A' && input[i + 3][j - 3] == 'S') {
                    sol++;
                }
            }
        }

        // reverse diagonal
        for (int i = input.size() - 1; i >= 3; --i) {
            for (int j = input[0].size(); j >= 3; --j) {
                if (input[i][j] == 'X' && input[i - 1][j - 1] == 'M' && input[i - 2][j - 2] == 'A' && input[i - 3][j - 3] == 'S') {
                    sol++;
                }
            }
        }

        for (int i = input.size() - 1; i >= 3; --i) {
            for (int j = 0; j < input[0].size() - 3; ++j) {
                if (input[i][j] == 'X' && input[i - 1][j + 1] == 'M' && input[i - 2][j + 2] == 'A' && input[i - 3][j + 3] == 'S') {
                    sol++;
                }
            }
        }

        return sol;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::vector<char>> input = file::readFileAsMapChar(path);
        int sol = 0;

        for (int i = 1; i < input.size() - 1; ++i)
        {
            for (int j = 1; j < input[0].size() - 1; ++j)
            {
                if (input[i][j] == 'A')
                {
                    if (input[i - 1][j - 1] == 'M' && input[i - 1][j + 1] == 'M' && input[i + 1][j - 1] == 'S' && input[i + 1][j + 1] == 'S')
                    {
                        sol++;
                    }
                    if (input[i - 1][j - 1] == 'S' && input[i - 1][j + 1] == 'S' && input[i + 1][j - 1] == 'M' && input[i + 1][j + 1] == 'M')
                    {
                        sol++;
                    }
                    if (input[i - 1][j - 1] == 'M' && input[i - 1][j + 1] == 'S' && input[i + 1][j - 1] == 'M' && input[i + 1][j + 1] == 'S')
                    {
                        sol++;
                    }
                    if (input[i - 1][j - 1] == 'S' && input[i - 1][j + 1] == 'M' && input[i + 1][j - 1] == 'S' && input[i + 1][j + 1] == 'M')
                    {
                        sol++;
                    }
                }
            }
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day04::part_1("../2024/day04/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day04::part_2("../2024/day04/input.in") << std::endl;

    return 0;
}
#endif
