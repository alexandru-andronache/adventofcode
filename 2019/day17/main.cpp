#include "file.h"
#include "intcode.h"
#include <iostream>

namespace aoc2019_day17 {
    int part_1(std::string_view path) {
        std::vector<unsigned long long> input = file::readFileAsArrayULL(path, ",");

        const int SIZE = 100;
        intcode::IntCode<unsigned long long>calc{input, {}};
        intcode::IntCode<unsigned long long>::exitState exit{0, 0, false, false};
        std::vector<std::vector<int>> board(SIZE, std::vector<int>(SIZE, 0));
        int i = 0, j = 0;
        int maxX = 0, maxY = 0;
        while (!exit.halt) {
            exit = calc.advance();
            if (!exit.halt) {
                if (exit.returnValue == 10) {
                    i++;
                    maxY = std::max(maxY, j);
                    j = 0;
                }
                else {
                    if (exit.returnValue == 35) {
                        board[i][j] = 1;
                    }
                    else if (exit.returnValue != 46) {
                        board[i][j] = 1;
                    }
                    j++;
                }
            }
        }
        maxX = i;

        int sol = 0;
        for (int i = 0; i <= maxX; ++i) {
            for (int j = 0; j <= maxY; ++j) {
                if (i > 0 && i < maxX && j > 0 && j < maxY) {
                    if (board[i - 1][j] && board[i + 1][j] && board[i][j - 1] && board[i][j + 1] && board[i][j]) {
                        sol += i * j;
                    }
                }
            }
        }

        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<unsigned long long> input = file::readFileAsArrayULL(path, ",");

        const int SIZE = 100;
        intcode::IntCode<unsigned long long>calc{input, {}};
        intcode::IntCode<unsigned long long>::exitState exit{0, 0, false, false};
        std::vector<std::vector<int>> board(SIZE, std::vector<int>(SIZE, 0));
        int startX = 0, startY = 0;
        std::pair<int, int> direction;
        int i = 0, j = 0;
        int maxX = 0, maxY = 0;
        while (!exit.halt) {
            exit = calc.advance();
            if (!exit.halt) {
                if (exit.returnValue == 10) {
                    i++;
                    maxY = std::max(maxY, j);
                    j = 0;
                }
                else {
                    if (exit.returnValue == 35) {
                        board[i][j] = 1;
                    }
                    else if (exit.returnValue != 46) {
                        startX = i;
                        startY = j;
                        if (exit.returnValue == '^') {
                            direction = {-1, 0};
                        }
                        else if (exit.returnValue == '<') {
                            direction = {0, -1};
                        }
                        else if (exit.returnValue == '>') {
                            direction = {0, 1};
                        }
                        else if (exit.returnValue == 'v') {
                            direction = {1, 0};
                        }
                        board[i][j] = 1;
                    }
                    j++;
                }
            }
        }
        maxX = i;

        std::vector<int> instructions;

        while (true) {
            int steps = 0;
            while (startX + direction.first >= 0 && startX + direction.first < SIZE &&
            startY + direction.second >= 0 && startY + direction.second < SIZE &&
            board[startX + direction.first][startY + direction.second] == 1) {
                steps++;
                startX += direction.first;
                startY += direction.second;
            }
            if (steps > 0) {
                if (steps > 9) {
                    instructions.push_back('0' + (steps / 10));
                    instructions.push_back('0' + (steps % 10));
                    instructions.push_back(',');
                }
                else {
                    instructions.push_back('0' + (steps));
                    instructions.push_back(',');
                }
            }
            else {
                std::pair<int, int> rightDir {0, 0};
                std::pair<int, int> leftDir {0, 0};

                if (direction.first == 0) {
                    rightDir.first = direction.second;
                    leftDir.first = -direction.second;
                }
                else {
                    rightDir.second = -direction.first;
                    leftDir.second = direction.first;
                }

                if (board[startX + rightDir.first][startY + rightDir.second] == 1) {
                    instructions.push_back('R');
                    instructions.push_back(',');
                    direction = rightDir;
                }
                else {
                    instructions.push_back('L');
                    instructions.push_back(',');
                    direction = leftDir;
                }
            }

            int nr = 0;
            std::vector<std::pair<int, int>> directions {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            for (const auto& d : directions) {
                if (startX + d.first >= 0 && startX + d.first < SIZE &&
                startY + d.second >= 0 && startY + d.second < SIZE &&
                board[startX + d.first][startY + d.second] == 1) {
                    nr++;
                }
            }

            if (nr == 1 && instructions.size() > 2) {
                break;
            }
        }

        std::vector<int> A {82, 44, 56, 44, 76, 44, 52, 44, 82, 44, 52, 44, 82, 44, 49, 48, 44, 82, 44, 56, '\n'};
        std::vector<int> B {76, 44, 49, 50, 44, 76, 44, 49, 50, 44, 82, 44, 56, 44, 82, 44, 56, '\n'};
        std::vector<int> C {82, 44, 49, 48, 44, 82, 44, 52, 44, 82, 44, 52, '\n'};
        std::vector<int> ins {65, 44, 65, 44, 66, 44, 67, 44, 66, 44, 67, 44, 66, 44, 67, 44, 67, 44, 65, '\n'};
        std::vector<int> cont {'n', '\n'};

        std::vector<int> allInput = ins;
        allInput.insert(allInput.end(), A.begin(), A.end());
        allInput.insert(allInput.end(), B.begin(), B.end());
        allInput.insert(allInput.end(), C.begin(), C.end());
        allInput.insert(allInput.end(), cont.begin(), cont.end());


        std::vector<unsigned long long> input2 = input;
        input2[0] = 2;
        intcode::IntCode<unsigned long long>calc2{input2, {}};
        intcode::IntCode<unsigned long long>::exitState exit2{0, 0, false, false};

        int index = 0;
        while (true) {
            exit2 = calc2.advance();
            if (exit2.halt) {
                return exit2.returnValue;
            }
            if (exit2.needInput) {
                if (index < allInput.size()) {
                    calc2.inputIDs.push_back((allInput[index]));
                    index++;
                }
            }
        }
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day17::part_1("../2019/day17/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day17::part_2("../2019/day17/input.in") << std::endl;

    return 0;
}
#endif
