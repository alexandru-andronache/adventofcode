#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>

namespace aoc2017_day11 {
    void move(std::string_view command, int& x, int& y) {
        if (command.compare("n") == 0) {
            x--;
        }
        else if (command.compare("ne") == 0) {
            if (y % 2 == 0) {
                x--;
            }
            y++;
        }
        else if (command.compare("se") == 0) {
            if (y % 2 != 0) {
                x++;
            }
            y++;
        }
        else if (command.compare("s") == 0) {
            x++;
        }
        else if (command.compare("sw") == 0) {
            if (y % 2 != 0) {
                x++;
            }
            y--;
        }
        else if (command.compare("nw") == 0) {
            if (y % 2 == 0) {
                x--;
            }
            y--;
        }
    }

    int calculateDistance(int startX, int startY, int endX, int endY) {
        if (startY == endY) {
            return std::abs(startX - endX);
        }

        int extraX = 0;
        if (startY % 2 != 0 && startX < endX) extraX = 1;
        if (startY % 2 == 0 && startX > endX) extraX = -1;

        if (endY < startY) {
            return 1 + calculateDistance(startX + extraX, startY - 1, endX, endY);
        }
        else {
            return 1 + calculateDistance(startX + extraX, startY + 1, endX, endY);
        }
    }

    int part_1(std::string_view path) {
        std::string input = file::readFileAsString(path);

        int i = 0;
        int startX = 0, startY = 0;
        while (i < input.size()) {
            int j = i;
            while (input[j] != ',' && input[j] != '\n') {
                j++;
            }
            move(input.substr(i, j - i), startX, startY);
            i = j + 1;
        }

        return calculateDistance(0, 0, startX, startY);
    }

    int part_2(std::string_view path) {
        std::string input = file::readFileAsString(path);

        int i = 0;
        int startX = 0, startY = 0;
        int max = std::numeric_limits<int>::min();
        while (i < input.size()) {
            int j = i;
            while (input[j] != ',' && input[j] != '\n') {
                j++;
            }
            move(input.substr(i, j - i), startX, startY);
            max = std::max(max, calculateDistance(0, 0, startX, startY));
            i = j + 1;
        }

        return max;
    }
}
#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day11::part_1("../2017/day11/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day11::part_2("../2017/day11/input.in") << std::endl;

    return 0;
}
#endif
