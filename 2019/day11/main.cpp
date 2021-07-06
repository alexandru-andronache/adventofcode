#include "file.h"
#include "intcode.h"
#include <iostream>
#include <map>

namespace aoc2019_day11 {
    unsigned long long part_1(std::string_view path) {
        std::vector<unsigned long long> input = file::readFileAsArrayULL(path, ",");
        // 0 - black, 1 - white
        const int SIZE = 100;
        intcode::IntCode<unsigned long long>calc{input, {}};
        intcode::IntCode<unsigned long long>::exitState exit{0, 0, false};
        std::vector<std::vector<std::pair<int, bool>>> board(SIZE, std::vector<std::pair<int, bool>>(SIZE, {0, false}));
        std::pair<int, int> direction{-1, 0}; // UP
        int x = SIZE / 2, y = SIZE / 2;
        while (!exit.halt) {
            unsigned long long startValue = board[x][y].first;
            calc.inputIDs = {startValue};
            exit = calc.advance();
            board[x][y].first = exit.returnValue;
            board[x][y].second = true;
            exit = calc.advance();
            int newDir = exit.returnValue;
            if ((newDir == 1 && direction.first != 0) || (newDir == 0 && direction.second != 0)) {
                direction.first = -direction.first;
                direction.second = -direction.second;
            }
            std::swap(direction.first, direction.second);
            x += direction.first;
            y += direction.second;
        }

        long long sol = 0;
        for (const auto& line : board) {
            sol += std::count_if(line.begin(), line.end(), [](auto el) {
                return el.second == true;
            });
        }

        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<unsigned long long> input = file::readFileAsArrayULL(path, ",");

        // 0 - black, 1 - white
        const int SIZE = 100;
        intcode::IntCode<unsigned long long> calc{input, {}};
        intcode::IntCode<unsigned long long>::exitState exit{0, 0, false};
        std::vector<std::vector<unsigned long long>> board(SIZE, std::vector<unsigned long long>(SIZE, 0));
        std::pair<int, int> direction{-1, 0}; // UP
        int x = SIZE / 2, y = SIZE / 2;
        board[x][y] = 1;
        while (!exit.halt) {
            unsigned long long startValue = board[x][y];
            calc.inputIDs = {startValue};
            board[x][y] = calc.advance().returnValue;
            exit = calc.advance();
            int newDir = exit.returnValue;
            if ((newDir == 1 && direction.first != 0) || (newDir == 0 && direction.second != 0)) {
                direction.first = -direction.first;
                direction.second = -direction.second;
            }
            std::swap(direction.first, direction.second);
            x += direction.first;
            y += direction.second;
        }

        int minX = std::numeric_limits<int>::max(), minY = std::numeric_limits<int>::max();
        int maxX = 0, maxY = 0;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (board[i][j]) {
                    minX = std::min(minX, i);
                    minY = std::min(minY, j);
                    maxX = std::max(maxX, i);
                    maxY = std::max(maxY, j);
                }
            }
        }

        for (int i = minX; i <= maxX; ++i) {
            for (int j = minY; j <= maxY; ++j) {
                if (board[i][j] == 1) {
                    std::cout << "#";
                }
                else {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }

        return 0;
    }
}
#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day11::part_1("../2019/day11/input.in") << std::endl;
    std::cout << "Part 2: " << std::endl;
    aoc2019_day11::part_2("../2019/day11/input.in");

    return 0;
}
#endif
