#include "file.h"
#include "intcode.h"
#include <vector>
#include <iostream>

namespace aoc2019_day13 {
    int joystickdirection(unsigned long long ballPosX, unsigned long long joystickPosX) {
        if (joystickPosX < ballPosX) {
            return 1;
        }
        if (joystickPosX > ballPosX) {
            return -1;
        }
        return 0;
    }

    int part_1(std::string_view path) {
        std::vector<unsigned long long> input = file::readFileAsArrayULL(path, ",");

        const int SIZE = 50;
        std::vector<std::vector<int>> board(SIZE, std::vector<int>(SIZE, 0));
        intcode::IntCode<unsigned long long>calc{input, {}};
        intcode::IntCode<unsigned long long>::exitState exit{0, 0, false};
        while (!exit.halt) {
            int x = calc.advance().returnValue;
            int y = calc.advance().returnValue;
            exit = calc.advance();
            board[x][y] = exit.returnValue;
        }
        int blocks = 0;
        for (const auto& line : board) {
            blocks += std::count(line.begin(), line.end(), 2);
        }

        return blocks;
    }

    int part_2(std::string_view path) {
        std::vector<unsigned long long> input = file::readFileAsArrayULL(path, ",");

        const int SIZE = 20000;
        std::vector<std::vector<int>> board(SIZE, std::vector<int>(SIZE, 0));
        intcode::IntCode<unsigned long long>calc{input, {0}};
        intcode::IntCode<unsigned long long>::exitState exit{0, 0, false};
        calc.values[0] = 2;
        unsigned long long score = 0;
        int joystickPosX = 0;
        int ballPosX = 0;
        while (!exit.halt) {
            calc.inputIDs.clear();
            calc.inputIDs.push_back(joystickdirection(ballPosX, joystickPosX));
            int x = calc.advance().returnValue;
            calc.inputIDs.clear();
            calc.inputIDs.push_back(joystickdirection(ballPosX, joystickPosX));
            int y = calc.advance().returnValue;
            calc.inputIDs.clear();
            calc.inputIDs.push_back(joystickdirection(ballPosX, joystickPosX));
            exit = calc.advance();
            if (x != -1) {
                board[x][y] = exit.returnValue;
            }
            if (exit.returnValue == 3) {
                joystickPosX = x;
            }
            else if (exit.returnValue == 4) {
                ballPosX = x;
            }
            if (x == -1 && y == 0) {
                score = exit.returnValue;
            }
        }
        return score;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day13::part_1("../2019/day13/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day13::part_2("../2019/day13/input.in") << std::endl;

    return 0;
}
#endif
