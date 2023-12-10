#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>

namespace aoc2023_day10 {
    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<bool>> v(input.size(), std::vector<bool>(input.size(), false));
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

        int cX = sX, cY = sY;
        cY++;
        v[cX][cY] = true;
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
                if (cY - 1 >= 0 && !v[cX][cY - 1]) {
                    cY = cY - 1;
                }
                else {
                    cY = cY + 1;
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
        }
        while (cX != sX || cY != sY);

        return sol / 2;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<bool>> v(input.size(), std::vector<bool>(input.size(), false));
        

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

        int cX = sX, cY = sY;
        cY++;
        v[cX][cY] = true;
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
