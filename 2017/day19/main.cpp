#include "file.h"
#include "utilities.h"
#include "direction.h"
#include <iostream>

namespace aoc2017_day19 {
    std::string part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);

        std::string sol;
        int startY = 0;
        while (lines[0][startY] == ' ') {
            startY++;
        }
        int startX = 0;
        utils::point dir = direction::Direction::DOWN;
        while (true) {
            startX += dir.x;
            startY += dir.y;

            if (lines[startX][startY] >= 'A' && lines[startX][startY] <= 'Z') {
                sol += lines[startX][startY];
            }
            else if (lines[startX][startY] == '+') {
                if (dir.x == 0) {
                    if (startX > 0 && lines[startX - 1][startY] == ' ') {
                        dir = direction::Direction::DOWN;
                    }
                    else {
                        dir = direction::Direction::UP;
                    }
                }
                else {
                    if (startY > 0 && lines[startX][startY - 1] == ' ') {
                        dir = direction::Direction::RIGHT;
                    }
                    else {
                        dir = direction::Direction::LEFT;
                    }
                }
            }
            else if (lines[startX][startY] == ' ') {
                return sol;
            }
        }
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);

        int sol = 0;
        int startY = 0;
        while (lines[0][startY] == ' ') {
            startY++;
        }
        int startX = 0;
        utils::point dir = direction::Direction::DOWN;
        while (true) {
            startX += dir.x;
            startY += dir.y;
            sol++;

            if (lines[startX][startY] == '+') {
                if (dir.x == 0) {
                    if (startX > 0 && lines[startX - 1][startY] == ' ') {
                        dir = direction::Direction::DOWN;
                    }
                    else {
                        dir = direction::Direction::UP;
                    }
                }
                else {
                    if (startY > 0 && lines[startX][startY - 1] == ' ') {
                        dir = direction::Direction::RIGHT;
                    }
                    else {
                        dir = direction::Direction::LEFT;
                    }
                }
            }
            else if (lines[startX][startY] == ' ') {
                return sol;
            }
        }
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day19::part_1("../2017/day19/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day19::part_2("../2017/day19/input.in") << std::endl;

    return 0;
}
#endif
