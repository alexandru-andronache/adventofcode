#include "file.h"
#include <iostream>
#include <vector>
#include <array>

namespace aoc2016_day02 {
    std::string part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::array<std::array<int, 3>, 3> keyboard {{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};
        int x = 1, y = 1;
        std::string sol;
        for (const auto& line : input) {
            for (const auto& c : line) {
                if (c == 'U' && x > 0) {
                    x--;
                }
                else if (c == 'D' && x < 2) {
                    x++;
                }
                else if (c == 'R' && y < 2) {
                    y++;
                }
                else if (c == 'L' && y > 0) {
                    y--;
                }
            }
            sol += keyboard[x][y] + '0';
        }
        return sol;
    }

    std::string part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::array<std::array<char, 5>, 5> keyboard {{{'0', '0', '1', '0', '0'},
                                                      {'0', '2', '3', '4', '0'},
                                                      {'5', '6', '7', '8', '9'},
                                                      {'0', 'A', 'B', 'C', '0'},
                                                      {'0', '0', 'D', '0', '0'}}};
        int x = 2, y = 0;
        std::string sol;
        for (const auto& line : input) {
            for (const auto& c : line) {
                if (c == 'U' && x > 0 && keyboard[x - 1][y] != '0') {
                    x--;
                }
                else if (c == 'D' && x < 4 && keyboard[x + 1][y] != '0') {
                    x++;
                }
                else if (c == 'R' && y < 4 && keyboard[x][y + 1] != '0') {
                    y++;
                }
                else if (c == 'L' && y > 0 && keyboard[x][y - 1] != '0') {
                    y--;
                }
            }
            sol += keyboard[x][y];
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day02::part_1("../2016/day02/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2016_day02::part_2("../2016/day02/input.in") << std::endl;

    return 0;
}
#endif
