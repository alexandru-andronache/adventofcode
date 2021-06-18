#include "file.h"
#include "utilities.h"
#include "intcode.h"
#include <iostream>

namespace aoc2019_day19 {
    int calculate(const std::vector<unsigned long long>& input, int x, int y) {
        intcode::IntCode<unsigned long long>calc{input, {}};
        intcode::IntCode<unsigned long long>::exitState exit{0, 0, false, false};
        calc.inputIDs.push_back(x);
        calc.inputIDs.push_back(y);

        return calc.advance().returnValue;
    }

    int part_1(std::string_view path) {
        std::vector<unsigned long long> input = file::readFileAsArrayULL(path, ",");
        const int SIZE = 50;

        std::vector<std::vector<bool>> board(SIZE, std::vector<bool>(SIZE, false));

        int sol = 0;
        int startPos = 0;
        for (int i = 0; i < SIZE; ++i) {
            bool found = false;
            int nextStartPos = 0;
            for (int j = startPos; j < SIZE; ++j) {
                if (calculate(input, i, j) == 1) {
                    board[i][j] = true;
                    sol++;
                    if (!found) {
                        nextStartPos = j;
                    }
                    found = true;
                }
                else if (found) {
                    startPos = nextStartPos;
                    j = SIZE;
                }
            }
        }

        return sol;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<unsigned long long> input = file::readFileAsArrayULL(path, ",");
        const int SIZE = 99;

        int x = 2, y = 0;
        while (calculate(input, x, y) == 0) {
            y++;
        }
        while (true) {
            x++;
            while (calculate(input, x, y) == 0) {
                y++;
            }
            if (x > SIZE && calculate(input, x - SIZE, y) == 1 &&
                    calculate(input, x - SIZE, y + SIZE) == 1 &&
                    calculate(input, x, y + SIZE) == 1) {
                return (x - SIZE) * 10000 + y;
            }
        }
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day19::part_1("../2019/day19/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day19::part_2("../2019/day19/input.in") << std::endl;

    return 0;
}
#endif
