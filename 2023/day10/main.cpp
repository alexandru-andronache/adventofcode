#include "file.h"
#include "utilities.h"
#include "direction.h"
#include <iostream>
#include <array>

namespace aoc2023_day10 {
    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<bool>> v(input.size(), std::vector<bool>(input.size(), false));
        unsigned long long sol = 0;
        auto [sX, sY] = utils::findValue(input, 'S');

        int cX = sX, cY = sY;

        if (cY - 1 >= 0 && (input[cX][cY - 1] == '-' || input[cX][cY - 1] == 'L' || input[cX][cY - 1] == 'F')) {
            cY = cY - 1;
        } else if (cY + 1 < input[0].size() &&
                   (input[cX][cY + 1] == '-' || input[cX][cY + 1] == 'J' || input[cX][cY + 1] == '7')) {
            cY = cY + 1;
        } else if (cX - 1 >= 0 &&
                   (input[cX - 1][cY] == '|' || input[cX - 1][cY] == 'F' || input[cX - 1][cY] == '7')) {
            cX = cX - 1;
        } else if (cX + 1 < input.size() &&
                   (input[cX + 1][cY] == '|' || input[cX + 1][cY] == 'J' || input[cX + 1][cY] == 'L')) {
            cX = cX + 1;
        }
        v[cX][cY] = true;
        sol++;

        while (cX != sX || cY != sY) {
            switch (input[cX][cY]) {
                case '|':
                    if (cX - 1 >= 0 && !v[cX - 1][cY]) {
                        cX--;
                    }
                    else {
                        cX++;
                    }
                    break;
                case '-':
                    if (cY + 1 >= 0 && !v[cX][cY + 1]) {
                        cY++;
                    }
                    else {
                        cY--;
                    }
                    break;
                case 'L':
                    if (cX - 1 >= 0 && !v[cX - 1][cY]) {
                        cX--;
                    }
                    else {
                        cY++;
                    }
                    break;
                case 'J':
                    if (cX - 1 >= 0 && !v[cX - 1][cY]) {
                        cX--;
                    }
                    else {
                        cY--;
                    }
                    break;
                case '7':
                    if (cX + 1 < input.size() && !v[cX + 1][cY]) {
                        cX++;
                    }
                    else {
                        cY--;
                    }
                    break;
                case 'F':
                    if (cX + 1 < input.size() && !v[cX + 1][cY]) {
                        cX++;
                    }
                    else {
                        cY++;
                    }
                    break;
            }
            v[cX][cY] = true;
            sol++;
        }

        return sol / 2;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<bool>> v(input.size(), std::vector<bool>(input[0].size(), false));
        std::vector<std::vector<int>> index(input.size(), std::vector<int>(input[0].size(), 0));

        unsigned long long sol = 0;
        int sX = 0, sY = 0;

        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[0].size(); ++j) {
                if (input[i][j] == 'S') {
                    sX = i;
                    sY = j;
                }
            }
        }

        int p = 2;
        int cX = sX, cY = sY;
        index[cX][cY] = p++;
        cY++;
        v[cX][cY] = true;
        index[cX][cY] = p++;
        sol++;

        do {
            sol++;
            if (input[cX][cY] == '|') {
                if (cX - 1 >= 0 && !v[cX - 1][cY]) {
                    cX = cX - 1;
                }
                else {
                    cX = cX + 1;
                }
            }
            else if (input[cX][cY] == '-') {
                if (cY + 1 >= 0 && !v[cX][cY + 1]) {
                    cY = cY + 1;
                }
                else {
                    cY = cY - 1;
                }
            }
            else if (input[cX][cY] == 'L') {
                if (cX - 1 >= 0 && !v[cX - 1][cY]) {
                    cX--;
                }
                else {
                    cY++;
                }
            }
            else if (input[cX][cY] == 'J') {
                if (cX - 1 >= 0 && !v[cX - 1][cY]) {
                    cX--;
                }
                else {
                    cY--;
                }
            }
            else if (input[cX][cY] == '7') {
                if (cX + 1 < input.size() && !v[cX + 1][cY]) {
                    cX++;
                }
                else {
                    cY--;
                }
            }
            else if (input[cX][cY] == 'F') {
                if (cX + 1 < input.size() && !v[cX + 1][cY]) {
                    cX++;
                }
                else {
                    cY++;
                }
            }
            v[cX][cY] = true;
            if (index[cX][cY] == 0)
                index[cX][cY] = p++;
        }
        while (cX != sX || cY != sY);

        int nr = 0;

        for (int i = 0; i < v.size(); ++i) {
            for (int j = 0; j < v[0].size(); ++j) {
                if (!v[i][j]) {
                    int vertical = 0;
                    for (int k = 0; k < j; ++k) {
                        if (input[i][k] == '|' && v[i][k]) {
                            vertical++;
                        }
                        if (input[i][k] == 'L' && v[i][k]) {
                            vertical++;
                        }
                        if (input[i][k] == 'J' && v[i][k]) {
                            vertical++;
                        }
                    }
                    if (vertical % 2 == 1) {
                        nr++;
                    }
                }
            }
        }


        return nr;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day10::part_1("../2023/day10/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day10::part_2("../2023/day10/input.in") << std::endl;

    return 0;
}
#endif
