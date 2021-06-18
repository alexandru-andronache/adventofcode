#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <set>

namespace aoc2016_day01 {
    int part_1(std::string_view path) {
        std::string input = file::readFileAsString(path);

        int x = 0, y = 0;
        std::pair<int, int> dir(-1, 0);
        int i = 0;
        while (i < input.size()) {
            char d = input[i++];
            int nr = utils::getNumber(input, i);
            i = i + 2;
            std::pair<int, int> newDir(dir.second, dir.first);
            if (dir.first != 0 && d == 'R') {
                newDir.second = -newDir.second;
            }
            else if (dir.second != 0 && d == 'L') {
                newDir.first = -newDir.first;
            }
            x += newDir.first * nr;
            y += newDir.second * nr;
            dir = newDir;
        }
        return std::abs(x) + std::abs(y);
    }

    int part_2(std::string_view path) {
        std::string input = file::readFileAsString(path);

        std::set<std::pair<int, int>> prevLocations;
        int x = 0, y = 0;
        std::pair<int, int> dir(-1, 0);
        int i = 0;
        prevLocations.insert({0, 0});
        while (i < input.size()) {
            char d = input[i++];
            int nr = utils::getNumber(input, i);
            i = i + 2;
            std::pair<int, int> newDir(dir.second, dir.first);
            if (dir.first != 0 && d == 'R') {
                newDir.second = -newDir.second;
            }
            else if (dir.second != 0 && d == 'L') {
                newDir.first = -newDir.first;
            }
            for (int k = 0; k < nr; ++k) {
                x += newDir.first;
                y += newDir.second;
                auto result = prevLocations.insert({x, y});
                if (!result.second) {
                    return std::abs(x) + std::abs(y);
                }
            }
            dir = newDir;
        }
        return std::abs(x) + std::abs(y);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day01::part_1("../2016/day01/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2016_day01::part_2("../2016/day01/input.in") << std::endl;

    return 0;
}
#endif
